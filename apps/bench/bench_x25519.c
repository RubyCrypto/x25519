#include "clocks.h"
#include <rfc7748_precompted.h>

void bench_x25519(void)
{
	X25519_KEY secret_key;
	X25519_KEY public_key;
	X25519_KEY shared_secret;

	printf("===== X225519  =====\n");
	oper_second(
		random_X25519_key(secret_key),
		"KeyGen",
		X25519_KeyGen_x64(public_key, secret_key)
	);
	oper_second(
	    random_X25519_key(secret_key);
		random_X25519_key(public_key),
		"Shared",
		X25519_Shared_x64(shared_secret, public_key, secret_key)
	);
}
