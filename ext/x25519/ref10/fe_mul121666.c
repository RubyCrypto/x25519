#include "fe.h"

/*
h = f * 121666
Can overlap h with f.

Preconditions:
   |f| bounded by 1.1*2^26,1.1*2^25,1.1*2^26,1.1*2^25,etc.

Postconditions:
   |h| bounded by 1.1*2^25,1.1*2^24,1.1*2^25,1.1*2^24,etc.
*/

void fe_mul121666(fe h,fe f)
{
  int32_t f0 = f[0];
  int32_t f1 = f[1];
  int32_t f2 = f[2];
  int32_t f3 = f[3];
  int32_t f4 = f[4];
  int32_t f5 = f[5];
  int32_t f6 = f[6];
  int32_t f7 = f[7];
  int32_t f8 = f[8];
  int32_t f9 = f[9];
  int64_t h0 = f0 * (int64_t) 121666;
  int64_t h1 = f1 * (int64_t) 121666;
  int64_t h2 = f2 * (int64_t) 121666;
  int64_t h3 = f3 * (int64_t) 121666;
  int64_t h4 = f4 * (int64_t) 121666;
  int64_t h5 = f5 * (int64_t) 121666;
  int64_t h6 = f6 * (int64_t) 121666;
  int64_t h7 = f7 * (int64_t) 121666;
  int64_t h8 = f8 * (int64_t) 121666;
  int64_t h9 = f9 * (int64_t) 121666;
  int64_t carry0;
  int64_t carry1;
  int64_t carry2;
  int64_t carry3;
  int64_t carry4;
  int64_t carry5;
  int64_t carry6;
  int64_t carry7;
  int64_t carry8;
  int64_t carry9;

  carry9 = (h9 + (int64_t) (1<<24)) >> 25; h0 += carry9 * 19; h9 -= carry9 << 25;
  carry1 = (h1 + (int64_t) (1<<24)) >> 25; h2 += carry1; h1 -= carry1 << 25;
  carry3 = (h3 + (int64_t) (1<<24)) >> 25; h4 += carry3; h3 -= carry3 << 25;
  carry5 = (h5 + (int64_t) (1<<24)) >> 25; h6 += carry5; h5 -= carry5 << 25;
  carry7 = (h7 + (int64_t) (1<<24)) >> 25; h8 += carry7; h7 -= carry7 << 25;

  carry0 = (h0 + (int64_t) (1<<25)) >> 26; h1 += carry0; h0 -= carry0 << 26;
  carry2 = (h2 + (int64_t) (1<<25)) >> 26; h3 += carry2; h2 -= carry2 << 26;
  carry4 = (h4 + (int64_t) (1<<25)) >> 26; h5 += carry4; h4 -= carry4 << 26;
  carry6 = (h6 + (int64_t) (1<<25)) >> 26; h7 += carry6; h6 -= carry6 << 26;
  carry8 = (h8 + (int64_t) (1<<25)) >> 26; h9 += carry8; h8 -= carry8 << 26;

  h[0] = (int32_t)h0;
  h[1] = (int32_t)h1;
  h[2] = (int32_t)h2;
  h[3] = (int32_t)h3;
  h[4] = (int32_t)h4;
  h[5] = (int32_t)h5;
  h[6] = (int32_t)h6;
  h[7] = (int32_t)h7;
  h[8] = (int32_t)h8;
  h[9] = (int32_t)h9;
}
