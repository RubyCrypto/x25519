#include "bench.h"
#include <stdio.h>

int main(void)
{
	printf("== Start of Benchmark ===\n");
	bench_fp25519_x64();
	bench_x25519();
	bench_fp448_x64();
	bench_x448();
	printf("== End of Benchmark =====\n");
	return 0;
}

