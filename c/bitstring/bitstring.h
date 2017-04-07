#ifndef __BITSTRING_H_
#define __BITSTRING_H_

#include <stdint.h>
#include <stdlib.h>

// Contains the possible types of a bitstring object
typedef enum
{
	BS_INIT_ME = 0,
	BS_S8,
	BS_S16,
	BS_S32,
	BS_S64,
	BS_U8,
	BS_U16,
	BS_U32,
	BS_U64,
} bs_type_t;

// The bitstring numerical object
typedef union
{
	uint64_t u;
	int64_t s;
} bs_param_t;

// The bitstring object
typedef struct
{
	bs_param_t	num;
	bs_type_t		type;
} bs_t;

// Possible return values for functions that can fail
typedef enum
{
	BS_ERR_NONE = 0,
	BS_NULL_ARG,
	BS_INVALID_ARG,
	BS_ALLOC_FAIL,
	BS_UNINITIALIZED,
	BS_BUF_SHORT,
} bs_error_t;

/// UI
// Create a bitstring object in the memory pointed to by bst
bs_error_t bitstring_create(bs_t* bst);

// Create a dynamically allocated bitstring object in the pointer-pointer bst
bs_error_t bitstring_create_alloc(bs_t** bst);

// Reset a bitstring object to the freshly created state
bs_error_t bitstring_reset(bs_t* bst);

// Pack a signed number into a bitstring
bs_error_t bitstring_make_signed(bs_t* bst, int64_t num);

// Pack an unsigned number into a bitstring
bs_error_t bitstring_make_unsigned(bs_t* bst, int64_t num);

// Serialize the bitstring as a string of bits into buf
// Prefixed with an 's' for signed, 'u' for unsigned, null terminated
bs_error_t bitstring_serialize(bs_t* bst, void* buf, size_t buf_len);

// Destroys a dynamically allocated bitstring
bs_error_t bitstring_destroy(bs_t* bst);



// not UI
bs_type_t bitstring_type_unsigned(uint64_t num);
bs_type_t bitstring_type_signed(int64_t num);

#endif

