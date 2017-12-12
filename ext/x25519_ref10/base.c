#include "fe.h"
#include "x25519_ref10.h"

static const uint8_t x25519_basepoint[32] = {9};

int x25519_ref10_scalarmult_base(uint8_t *q, const uint8_t *n)
{
  return x25519_ref10_scalarmult(q,n,x25519_basepoint);
}
