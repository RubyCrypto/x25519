/**
 * Copyright (c) 2017 Armando Faz <armfazh@ic.unicamp.br>.
 * Institute of Computing.
 * University of Campinas, Brazil.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef ED25519_PRECOMPUTED_H
#define ED25519_PRECOMPUTED_H

#include <stdint.h>

#define ALIGN_BYTES 32
#ifdef __INTEL_COMPILER
#define ALIGN __declspec(align(ALIGN_BYTES))
#else
#define ALIGN __attribute__ ((aligned (ALIGN_BYTES)))
#endif

#define X25519_KEYSIZE_BYTES 32
typedef ALIGN uint8_t X25519_KEY[X25519_KEYSIZE_BYTES];

void x25519_precomputed_scalarmult(uint8_t *shared, uint8_t *private_key, uint8_t *session_key);
void x25519_precomputed_scalarmult_base(uint8_t *session_key, uint8_t *private_key);
int check_4th_gen_intel_core_features();

#endif /* ED25519_PRECOMPUTED_H */
