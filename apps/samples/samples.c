#include <stdio.h>
#include <rfc7748_precompted.h>

static void x25519_sample()
{
	X25519_KEY alice_private_key, alice_session_key, alice_shared;
	X25519_KEY bob_private_key, bob_session_key, bob_shared;

	random_X25519_key(alice_private_key);
	printf("Alice's Private Key:   ");print_X25519_key(alice_private_key);

	random_X25519_key(bob_private_key);
	printf("Bob's Private Key:     ");print_X25519_key(bob_private_key);

	X25519_KeyGen_x64(alice_session_key,alice_private_key);
	printf("Alice's Session Key:   ");print_X25519_key(alice_session_key);

	X25519_KeyGen_x64(bob_session_key,bob_private_key);
	printf("Bob's Session Key:     ");print_X25519_key(bob_session_key);

	X25519_Shared_x64(alice_shared,bob_session_key,alice_private_key);
	printf("Alice's Shared Secreet:");print_X25519_key(alice_shared);

	X25519_Shared_x64(bob_shared,alice_session_key,bob_private_key);
	printf("Bob's Shared Secreet:  ");print_X25519_key(bob_shared);
}

static void x448_sample()
{
	X448_KEY alice_private_key, alice_session_key, alice_shared;
	X448_KEY bob_private_key, bob_session_key, bob_shared;

	random_X448_key(alice_private_key);
	printf("Alice's Private Key:   ");print_X448_key(alice_private_key);

	random_X448_key(bob_private_key);
	printf("Bob's Private Key:     ");print_X448_key(bob_private_key);

	X448_KeyGen_x64(alice_session_key,alice_private_key);
	printf("Alice's Session Key:   ");print_X448_key(alice_session_key);

	X448_KeyGen_x64(bob_session_key,bob_private_key);
	printf("Bob's Session Key:     ");print_X448_key(bob_session_key);

	X448_Shared_x64(alice_shared,bob_session_key,alice_private_key);
	printf("Alice's Shared Secreet:");print_X448_key(alice_shared);

	X448_Shared_x64(bob_shared,alice_session_key,bob_private_key);
	printf("Bob's Shared Secreet:  ");print_X448_key(bob_shared);
	
}

int main(void)
{
	x25519_sample();
	x448_sample();
    return 0;
}
