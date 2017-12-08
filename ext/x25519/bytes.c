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
#include <stdio.h>
#include "bytes.h"

void print_bytes(uint8_t * A, int num_bytes)
{
	int i;

	printf("0x");
	for(i=num_bytes-1;i>=0;i--)
	{
		printf("%02x", A[i]);
	}
	printf("\n");
}

int compare_bytes(uint8_t* A, uint8_t* B,unsigned int num_bytes)
{
	unsigned int i=0;
	uint8_t ret=0;
	for(i=0;i<num_bytes;i++)
	{
		ret += A[i]^B[i];
	}
	return ret;
}