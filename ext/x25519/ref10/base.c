#include "fe.h"

int x25519_ref10_scalarmult(uint8_t *q,
  const uint8_t *n,
  const uint8_t *p);

static const uint8_t x25519_basepoint[32] = {9};

int x25519_ref10_scalarmult_base(uint8_t *q, const uint8_t *n)
{
  return x25519_ref10_scalarmult(q,n,x25519_basepoint);
}
