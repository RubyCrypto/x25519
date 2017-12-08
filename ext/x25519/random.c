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
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/** Random number Generator:
 * Taken from: https://github.com/relic-toolkit/relic/src/rand/relic_rand_call.c
 *
 * @warning Provide a secure random number generator.
 * @param buffer
 * @param num_bytes
 */
#include <unistd.h>
#include <fcntl.h>
void random_bytes(uint8_t *buffer, int num_bytes)
{
	int c, l, fd = open("/dev/urandom", O_RDONLY);

	if (fd == -1)
	{
		printf("Error opening /dev/urandom\n");
	}

	l = 0;
	do {
		c = read(fd, buffer + l, num_bytes - l);
		l += c;
		if (c == -1)
		{
			printf("Error reading /dev/urandom\n");
		}
	} while (l < num_bytes);

	close(fd);
}
