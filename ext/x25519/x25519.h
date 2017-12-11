#include "rfc7748_precomputed.h"

/* Detect support for 4th gen (e.g. Haswell) or newer CPUs */
int check_4th_gen_intel_core_features();

/**********************************
 * rfc7748_precomputed prototypes *
 **********************************/

/* Fixed-base scalar multiplication */
void x25519_rfc7748_precomputed_scalarmult_base(uint8_t *session_key, uint8_t *private_key);

/* Variable-base scalar multiplication */
void x25519_rfc7748_precomputed_scalarmult(uint8_t *shared, uint8_t *private_key, uint8_t *session_key);

/********************
 * ref10 prototypes *
 ********************/

/* Fixed-base scalar multiplication */
int x25519_ref10_scalarmult_base(uint8_t *q, const uint8_t *n);

/* Variable-base scalar multiplication */
int x25519_ref10_scalarmult(uint8_t *q, const uint8_t *n, const uint8_t *p);
