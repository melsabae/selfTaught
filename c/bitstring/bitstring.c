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
	bs_param_t param =
	{
		.s = num,
	};

	bs_type_t type = bitstring_type_unsigned(param.u);

	switch(type)
	{
		case BS_U8:
			return BS_S8;
		case BS_U16:
			return BS_S16;
		case BS_U32:
			return BS_S32;

		case BS_U64:
			/* intentional fall-through in case statement */
		default:
			return BS_S64;
	}
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

	// if the user's pointer was not set, free the allocated memory
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
			len = 8u;
			break;
		case BS_S16:
			len = 16u;
			break;
		case BS_S32:
			len = 32u;
			break;
		case BS_S64:
			len = 64u;
			break;

		default:
			return (BS_INVALID_ARG);
	}

	if((len + 1) < buf_len)
	{
		return (BS_BUF_SHORT);
	}

	buffer = buf;

	for(i = 0; i < len; i++)
	{
		if(bst -> num.u & (1 << i))
		{
			buffer[i] = '1';
		}
		else
		{
			buffer[i] = '0';
		}
	}

	return (BS_ERR_NONE);
}
