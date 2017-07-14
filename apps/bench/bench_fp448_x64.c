#include <stdio.h>
#include <fp448_x64.h>
#include "clocks.h"

void bench_fp448_x64(void)
{
	int BENCH = 3000;

	EltFp448_1w_x64 a,b,c;
	EltFp448_1w_Buffer_x64 buffer_1w;

	random_EltFp448_1w_x64(a);
	random_EltFp448_1w_x64(b);
	random_EltFp448_1w_x64(c);

	printf("= GF(2^448-2^224-1) =\n");
	printf("== 1-way x64 \n");
	CLOCKS("add",add_EltFp448_1w_x64(c,a,b));
	CLOCKS("sub",sub_EltFp448_1w_x64(c,a,b));
	CLOCKS("mul",mul_EltFp448_1w_x64(c,c,b));
	CLOCKS("m24",mul_a24_EltFp448_1w_x64(c,a));
	CLOCKS("sqr",sqr_EltFp448_1w_x64(c));

	BENCH /= 10;
	CLOCKS("inv",inv_EltFp448_1w_x64(c,a));
}
