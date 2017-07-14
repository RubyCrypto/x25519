#include <stdio.h>
#include "tests.h"

int main(void)
{
	printf("== Start of Test ==\n");
	test_fp25519_x64();
	test_x25519();
	test_fp448_x64();
	test_x448();
	printf("==  End of Test ===\n");
	return 0;
}
