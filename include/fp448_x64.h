/**
 * Copyright (c) 2017 Armando Faz <armfazh@ic.unicamp.br>.
 * Institute of Computing.
 * University of Campinas, Brazil.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU Lesser General Public License as   
 * published by the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef FP448_X64_H
#define FP448_X64_H

#include <stdint.h>

#define ALIGN_BYTES 32
#ifdef __INTEL_COMPILER
#define ALIGN __declspec(align(ALIGN_BYTES))
#else
#define ALIGN __attribute__ ((aligned (ALIGN_BYTES)))
#endif

#define SIZE_ELEMENT_BYTES 56
#define NUM_WORDS_ELTFP448_X64 7
typedef ALIGN uint64_t EltFp448_1w_x64[NUM_WORDS_ELTFP448_X64];
typedef ALIGN uint64_t EltFp448_1w_Buffer_x64[2*NUM_WORDS_ELTFP448_X64];

void print_bytes(uint8_t * A,int num_bytes);

/* Integer Arithmetic */
void mul_448x448_integer_x64(uint64_t * const c, uint64_t * const a, uint64_t * const b);
void sqr_448x448_integer_x64(uint64_t * const c, uint64_t * const a);
void red_EltFp448_1w_x64(uint64_t * const c, uint64_t * const a);

/* Prime Field Util */
void random_EltFp448_1w_x64(uint64_t *A);
void print_EltFp448_1w_x64(uint64_t *A);
int compare_EltFp448_1w_x64(uint64_t *A, uint64_t *B);

/* Prime Field Arithmetic */
void add_EltFp448_1w_x64(uint64_t * const c, uint64_t * const a, uint64_t * const b);
void sub_EltFp448_1w_x64(uint64_t * const c, uint64_t * const a, uint64_t * const b);
void mul_a24_EltFp448_1w_x64(uint64_t * const c, uint64_t * const a);
void inv_EltFp448_1w_x64(uint64_t * const pC, uint64_t * const pA);
void fred_EltFp448_1w_x64(uint64_t * const c);

#define mul_EltFp448_1w_x64(C,A,B)\
    mul_448x448_integer_x64(buffer_1w,A,B);\
    red_EltFp448_1w_x64(C,buffer_1w);

#define sqr_EltFp448_1w_x64(A)\
    sqr_448x448_integer_x64(buffer_1w,A);\
    red_EltFp448_1w_x64(A,buffer_1w);

#define copy_EltFp448_1w_x64(C,A)\
	C[0] = A[0];\
	C[1] = A[1];\
	C[2] = A[2];\
	C[3] = A[3];\
	C[4] = A[4];\
	C[5] = A[5];\
	C[6] = A[6];

#endif /* FP448_X64_H */
