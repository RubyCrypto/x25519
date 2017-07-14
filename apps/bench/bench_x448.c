#include <stdio.h>
#include <rfc7748_precompted.h>
#include "clocks.h"

void bench_x448(void)
{
	X448_KEY secret_key;
	X448_KEY public_key;
	X448_KEY shared_secret;

	printf("===== X448  =====\n");
	oper_second(
			random_X448_key(secret_key),
			"KeyGen",
			X448_KeyGen_x64(public_key, secret_key)
	);
	oper_second(
			random_X448_key(secret_key);
			random_X448_key(public_key),
			"Shared",
			X448_Shared_x64(shared_secret, public_key, secret_key)
	);
}
