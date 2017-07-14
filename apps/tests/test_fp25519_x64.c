#include <stdio.h>
#include <fp25519_x64.h>
#include "tests.h"

void test_fp25519_x64()
{
	int64_t i;
	int64_t cnt =0 , match=0;
	EltFp25519_1w_x64 a,b,c,d,e,f;
	EltFp25519_1w_Buffer_x64 buffer_1w;

	printf("=== GF(2^255-19) ====\n");
	/**
	* Test identity:
	*    (a^2-b^2) == (a+b)(a-b)
	*/
	printf("Test mul/sqr:\n");
	cnt = 0;
	for(i=0;i<TEST_TIMES;i++)
	{
		random_EltFp25519_1w_x64(a);
		random_EltFp25519_1w_x64(b);

		add_EltFp25519_1w_x64(e, a, b);
		sub_EltFp25519_1w_x64(f, a, b);
		mul_EltFp25519_1w_x64(e, e, f);

		sqr_EltFp25519_1w_x64(a);
		sqr_EltFp25519_1w_x64(b);
		sub_EltFp25519_1w_x64(c, a, b);

		match = compare_EltFp25519_1w_x64(c, e)==0;
		if(!match)
		{
			printf("A:\n");
			print_EltFp25519_1w_x64(a);
			printf("B:\n");
			print_EltFp25519_1w_x64(b);
			printf("c:\n");
			print_EltFp25519_1w_x64(c);
			printf("e:\n");
			print_EltFp25519_1w_x64(e);
			break;
		}
		cnt += match;
	}
	printf(" %ld %s\n",cnt , cnt == TEST_TIMES? "OK" : "FAIL" );

	/**
	* Test identity:
	*    (a*b*a^1) == b
	*/
	printf("Test mul/inv:\n");
	cnt = 0;
	for(i=0;i<TEST_TIMES;i++)
	{
		random_EltFp25519_1w_x64(a);
		random_EltFp25519_1w_x64(b);

		inv_EltFp25519_1w_x64(d, a);
		mul_EltFp25519_1w_x64(a, a, b);
		mul_EltFp25519_1w_x64(a, a, d);
		fred_EltFp25519_1w_x64(a);
		fred_EltFp25519_1w_x64(b);
		match = compare_EltFp25519_1w_x64(a, b)==0;
		if(!match)
		{
			printf("A:\n");
			print_EltFp25519_1w_x64(a);
			printf("B:\n");
			print_EltFp25519_1w_x64(b);
			break;
		}
		cnt += match;
	}
	printf(" %ld %s\n",cnt , cnt == TEST_TIMES? "OK" : "FAIL" );
}
