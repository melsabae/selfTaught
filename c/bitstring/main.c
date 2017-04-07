#include "bitstring.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	bs_t bs;
	bs_error_t err = BS_ERR_NONE;
	char buffer[65] = { 0 };

	assert(bitstring_create(&bs) == BS_ERR_NONE);

	for(int i = 0; i <= UINT8_MAX; i++)
	{
		assert(bitstring_make_unsigned(&bs, i) == BS_ERR_NONE);
		err = bitstring_serialize(&bs, buffer, 65);
		printf("%d %d %s\n", i, err, buffer);
	}

}
