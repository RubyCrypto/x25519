#ifndef X25519_REF10_H
#define X25519_REF10_H

#include <stdint.h>

#define X25519_KEYSIZE_BYTES 32
typedef uint8_t X25519_KEY[X25519_KEYSIZE_BYTES];

/* Fixed-base scalar multiplication */
int x25519_ref10_scalarmult(uint8_t *q, const uint8_t *n, const uint8_t *p);

/* Variable-base scalar multiplication */
int x25519_ref10_scalarmult_base(uint8_t *q, const uint8_t *n);

#endif /* X25519_REF10_H */
