#include "bitstring.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	bs_t bs;
	bs_error_t err = BS_ERR_NONE;
	char buffer[128] = { 0 };

	assert(bitstring_create(&bs) == BS_ERR_NONE);

	for(int i = INT16_MIN; i <= INT16_MAX; i++)
	{
		assert(bitstring_make_signed(&bs, i) == BS_ERR_NONE);
		err = bitstring_serialize(&bs, buffer, 128);
		printf("%d %d %s\n", i, err, buffer);
		memset(buffer, 0, 65);
	}
}
