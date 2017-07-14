#ifndef CLOCKS_H
#define CLOCKS_H

#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>

#ifdef __INTEL_COMPILER
#define BARRIER __memory_barrier()
#else
#define BARRIER __asm__ __volatile__ ("" ::: "memory")
#endif

#define CLOCKS_RANDOM(RANDOM,LABEL,FUNCTION) \
do{ \
	uint64_t start,end;int64_t i_bench,j_bench; \
	unsigned cycles_high0,cycles_low0; \
	unsigned cycles_high1,cycles_low1;  \
	__asm__ __volatile__ (\
	"mfence\n\t" \
	"RDTSC\n\t" \
	"mov %%edx, %0\n\t" \
	"mov %%eax, %1\n\t": "=r" (cycles_high0), "=r" (cycles_low0)::  \
	"%rax", "%rbx", "%rcx", "%rdx"); \
	BARRIER;\
	i_bench=BENCH;\
	do{\
		j_bench=BENCH;\
		RANDOM;\
		do{\
			FUNCTION;\
			j_bench--;\
		}while( j_bench != 0 );\
		i_bench--;\
	}while( i_bench != 0 );\
	BARRIER;\
	__asm__ __volatile__("RDTSCP\n\t"  \
	"mov %%edx, %0\n\t"   \
	"mov %%eax, %1\n\t"   \
	"mfence\n\t" \
	: "=r" (cycles_high1), "=r" (cycles_low1):: \
	"%rax", "%rbx", "%rcx", "%rdx"); \
	start= (((uint64_t)cycles_high0)<<32)|cycles_low0;\
	end  = (((uint64_t)cycles_high1)<<32)|cycles_low1;\
	printf("%-8s: %5lu cc\n",LABEL,(end-start)/(BENCH*BENCH));\
}while(0)

#define CLOCKS(LABEL,FUNCTION) CLOCKS_RANDOM(while(0),LABEL,FUNCTION)

#define oper_second(RANDOM,LABEL,FUNCTION) \
do{\
	printf("%-8s: ",LABEL);\
	RANDOM;\
\
	unsigned i;\
	uint64_t start, end;\
	const unsigned iterations = 100000;\
	uint64_t start_c, end_c;\
\
	/* Load the caches*/\
	for (i = 0; i < 1000; ++i) {\
	     FUNCTION ;\
	}\
\
	start = time_now();\
	start_c = cycles_now();\
	for (i = 0; i < iterations; ++i) {\
		FUNCTION; \
	}\
	end = time_now();\
	end_c = cycles_now();\
\
	printf("%3lu µs, %8.1f oper/s, %6lu cycles/op\n",\
			(unsigned long) ((end - start) / iterations),\
			iterations*(double)1e6 / (end - start),\
			(unsigned long)((end_c-start_c)/iterations) );\
}while(0)

uint64_t time_now();
uint64_t cycles_now(void);

#endif /* CLOCKS_H */
