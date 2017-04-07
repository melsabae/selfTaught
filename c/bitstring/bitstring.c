#include "bitstring.h"

#define ERROR_OUT(x) { err = x; goto cleanup; }

bs_type_t bitstring_type_unsigned(uint64_t num)
{
	if(UINT32_MAX < num)
	{
		return (BS_U64);
	}

	if(UINT16_MAX < num)
	{
		return (BS_U32);
	}

	if(UINT8_MAX < num)
	{
		return (BS_U16);
	}

	return (BS_U8);
}

bs_type_t bitstring_type_signed(int64_t num)
{
	if(INT32_MIN > num)
	{
		return (BS_S64);
	}

	if(INT16_MIN > num)
	{
		return (BS_S32);
	}

	if(INT8_MIN > num)
	{
		return (BS_S16);
	}

	if(INT8_MAX >= num)
	{
		return (BS_S8);
	}

	if(INT32_MAX < num)
	{
		return (BS_S64);
	}

	if(INT16_MAX < num)
	{
		return (BS_S32);
	}

	if(INT8_MAX < num)
	{
		return (BS_S16);
	}

	return (BS_S8);
}

bs_error_t bitstring_reset(bs_t* bst)
{
	if(NULL == bst)
	{
		return (BS_NULL_ARG);
	}

	bst -> num.u = 0;
	bst -> type = BS_INIT_ME;

	return (BS_ERR_NONE);
}

bs_error_t bitstring_create(bs_t* bst)
{
	return (bitstring_reset(bst));
}

bs_error_t bitstring_create_alloc(bs_t** bst)
{
	bs_t* _bst							= NULL;
	bs_error_t err					= BS_ERR_NONE;

	if(NULL == bst)					{ ERROR_OUT(BS_NULL_ARG) }
	if(NULL != (*bst))			{ ERROR_OUT(BS_INVALID_ARG) }

	_bst										= calloc(1, sizeof(bst));
	if(NULL == _bst)				{ ERROR_OUT(BS_ALLOC_FAIL) }

	err											= bitstring_create(_bst);
	if(BS_ERR_NONE != err)	{ ERROR_OUT(err) }

	(*bst)									= _bst;

cleanup:
	// if the user's pointer was not set, free the allocated memory due to error
	if(NULL == (*bst))
	{
		free(_bst);
	}

	return									(err);
}

bs_error_t bitstring_make_signed(bs_t* bst, int64_t num)
{
	if(NULL == bst)
	{
		return (BS_NULL_ARG);
	}

	bst -> num.s = num;
	bst -> type = bitstring_type_signed(num);

	return (BS_ERR_NONE);
}

bs_error_t bitstring_make_unsigned(bs_t* bst, int64_t num)
{
	if(NULL == bst)
	{
		return (BS_NULL_ARG);
	}

	bst -> num.u = num;
	bst -> type = bitstring_type_unsigned(num);

	return (BS_ERR_NONE);
}

bs_error_t bitstring_serialize(bs_t* bst, void* buf, size_t buf_len)
{
	size_t len = 0;
	size_t i = 0;
	uint8_t* buffer = NULL;

	if(NULL == bst)
	{
		return (BS_NULL_ARG);
	}

	if(NULL == buf)
	{
		return (BS_NULL_ARG);
	}

	if(BS_INIT_ME == bst -> type)
	{
		return (BS_UNINITIALIZED);
	}

	switch(bst -> type)
	{
		case BS_S8:
		case BS_U8:
			len = 8u;
			break;
		case BS_S16:
		case BS_U16:
			len = 16u;
			break;
		case BS_S32:
		case BS_U32:
			len = 32u;
			break;
		case BS_S64:
		case BS_U64:
			len = 64u;
			break;

		default:
			return (BS_INVALID_ARG);
	}

	if((len + 2) > buf_len)
	{
		return (BS_BUF_SHORT);
	}

	buffer = buf;

	switch(bst -> type)
	{
		case BS_U8:
		case BS_U16:
		case BS_U32:
		case BS_U64:
			buffer[0] = 'u';
			break;
		case BS_S8:
		case BS_S16:
		case BS_S32:
		case BS_S64:
			buffer[0] = 's';
			break;

		default:
			return (BS_INVALID_ARG);
	}

	++ buffer;

	for(i = 0; i < len; i++)
	{
		if(0 != ((bst -> num.u) & (1 << i)))
		{
			buffer[len - i - 1] = '1';
		}
		else
		{
			buffer[len - i - 1] = '0';
		}
	}

	buffer[len] = 0;

	return (BS_ERR_NONE);
}

bs_error_t bitstring_destroy(bs_t* bst)
{
	if(NULL == bst)
	{
		return (BS_NULL_ARG);
	}

	free(bst);
	return (BS_ERR_NONE);
}
