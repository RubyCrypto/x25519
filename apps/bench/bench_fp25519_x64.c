#include <stdio.h>
#include <fp25519_x64.h>
#include "clocks.h"

void bench_fp25519_x64(void)
{
	int BENCH = 3000;

	EltFp25519_1w_x64 a,b,c;
	EltFp25519_2w_x64 BB,CC;
	EltFp25519_1w_Buffer_x64 buffer_1w;
	EltFp25519_2w_Buffer_x64 buffer_2w;

	random_EltFp25519_1w_x64(a);
	random_EltFp25519_1w_x64(b);
	random_EltFp25519_1w_x64(c);

	printf("=== GF(2^255-19) ===\n");
	printf("== 1-way x64 \n");
	CLOCKS("add",add_EltFp25519_1w_x64(c, a, b));
	CLOCKS("sub",sub_EltFp25519_1w_x64(c, a, b));
	CLOCKS("mul",mul_EltFp25519_1w_x64(c,c,b));
	CLOCKS("m24",mul_a24_EltFp25519_1w_x64(c,a));
	CLOCKS("sqr",sqr_EltFp25519_1w_x64(c));

	BENCH /= 10;
	CLOCKS("inv",inv_EltFp25519_1w_x64(c, a));
	BENCH *= 10;

	printf("== 2-way x64 \n");
	CLOCKS("mul",mul_EltFp25519_2w_x64(CC,CC,BB));
	CLOCKS("sqr",sqr_EltFp25519_2w_x64(CC));
}
