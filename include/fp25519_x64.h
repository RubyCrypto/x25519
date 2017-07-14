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
#ifndef FP25519_X64_H
#define FP25519_X64_H

#include <stdint.h>

#define ALIGN_BYTES 32
#ifdef __INTEL_COMPILER
#define ALIGN __declspec(align(ALIGN_BYTES))
#else
#define ALIGN __attribute__ ((aligned (ALIGN_BYTES)))
#endif

#define SIZE_ELEMENT_BYTES 32
#define NUM_WORDS_ELTFP25519_X64 4
typedef ALIGN uint64_t EltFp25519_1w_x64[NUM_WORDS_ELTFP25519_X64];
typedef ALIGN uint64_t EltFp25519_1w_Buffer_x64[2*NUM_WORDS_ELTFP25519_X64];
typedef ALIGN uint64_t EltFp25519_2w_x64[2*NUM_WORDS_ELTFP25519_X64];
typedef ALIGN uint64_t EltFp25519_2w_Buffer_x64[4*NUM_WORDS_ELTFP25519_X64];

void print_bytes(uint8_t * A,int num_bytes);

/* Integer Arithmetic */
void mul2_256x256_integer_x64(uint64_t *const c, uint64_t *const a, uint64_t *const b);
void sqr2_256x256_integer_x64(uint64_t *const c, uint64_t *const a);
void red_EltFp25519_2w_x64(uint64_t *const c, uint64_t *const a);

void mul_256x256_integer_x64(uint64_t *const c, uint64_t *const a, uint64_t *const b);
void sqr_256x256_integer_x64(uint64_t *const c, uint64_t *const a);
void red_EltFp25519_1w_x64(uint64_t *const c, uint64_t *const a);

/* Prime Field Util */
void random_EltFp25519_1w_x64(uint64_t *A);
void print_EltFp25519_1w_x64(uint64_t *A);
int compare_EltFp25519_1w_x64(uint64_t *A, uint64_t *B);
void random_EltFp25519_2w_x64(uint64_t *A);
void print_EltFp25519_2w(uint64_t *A);
int compare_EltFp25519_2w(uint64_t *A, uint64_t *B);

/* Prime Field Arithmetic */
void add_EltFp25519_1w_x64(uint64_t *const c, uint64_t *const a, uint64_t *const b);
void sub_EltFp25519_1w_x64(uint64_t *const c, uint64_t *const a, uint64_t *const b);
void mul_a24_EltFp25519_1w_x64(uint64_t *const c, uint64_t *const a);
void inv_EltFp25519_1w_x64(uint64_t *const pC, uint64_t *const pA);
void fred_EltFp25519_1w_x64(uint64_t *const c);

#define mul_EltFp25519_1w_x64(c,a,b)  \
	mul_256x256_integer_x64(buffer_1w,a,b);\
    red_EltFp25519_1w_x64(c,buffer_1w);

#define sqr_EltFp25519_1w_x64(a)\
    sqr_256x256_integer_x64(buffer_1w,a);\
    red_EltFp25519_1w_x64(a,buffer_1w);

#define mul_EltFp25519_2w_x64(c,a,b)  \
	mul2_256x256_integer_x64(buffer_2w,a,b);\
    red_EltFp25519_2w_x64(c,buffer_2w);

#define sqr_EltFp25519_2w_x64(a)\
    sqr2_256x256_integer_x64(buffer_2w,a);\
    red_EltFp25519_2w_x64(a,buffer_2w);

#define copy_EltFp25519_1w_x64(C,A)\
    (C)[0] = (A)[0];\
    (C)[1] = (A)[1];\
    (C)[2] = (A)[2];\
    (C)[3] = (A)[3];

#define setzero_EltFp25519_1w_x64(C)\
    (C)[0] = 0;\
    (C)[1] = 0;\
    (C)[2] = 0;\
    (C)[3] = 0;

#endif /* FP25519_X64_H */
