#include "bitstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char* GenerateBitStringUnsigned(const uint64_t num)
{
  static uint8_t size;
  static char *bitstr;
  static int8_t bitpos;

  // find the minimum number of bits, worst case, to make a bitstring
  size = ceil(log2(num));

  if(pow(2, size) == num)
  {
    size++; // 2^n - 1 max value for N bits, add 1 if 2^n is the number
  }

  // based on the exponent in size, find the number of bits
  if(size > 32)
  {
    size = 64;
  }
  else if(size > 16)
  {
    size = 32;
  }
  else if(size > 8)
  {
    size = 16;
  }
  else
  {
    size = 8;
  }

  bitstr = calloc(1, size + 1); // 1 space for \0, calloc for auto null terminated
  size --; // decrement for array access

  if(bitstr != NULL)
  {
    // build from MSB to LSB
    for(bitpos = size; bitpos >= 0; bitpos--)
    {
      if(num & (1 << bitpos))
      {
        bitstr[size - bitpos] = '1';
      }
      else
      {
        bitstr[size - bitpos] = '0';
      }
    }
  }

  return bitstr;
}

char* GenerateBitStringSigned(const int64_t num)
{
  static uint8_t size;
  static char *bitstr;
  static int8_t bitpos;

  if(num < 0)
  {
    size = ceil(log2(num * -1));
    size++; // add a bit for sign bit
  }
  else
  {
    size = ceil(log2(num));
  }

  if(pow(2, size) == num)
  {
    size++; // 2^n - 1 max value for N bits, add 1 if 2^n is the number
  }

  if(size > 32)
  {
    size = 64;
  }
  else if(size > 16)
  {
    size = 32;
  }
  else if(size > 8)
  {
    size = 16;
  }
  else
  {
    size = 8;
  }

  bitstr = calloc(1, size + 1); // 1 space for \0, calloc for auto null terminated
  size --; // decrement for array access

  if(bitstr != NULL)
  {
    // build from MSB to LSB
    for(bitpos = size; bitpos >= 0; bitpos--)
    {
      if(num & (1 << bitpos))
      {
        bitstr[size - bitpos] = '1';
      }
      else
      {
        bitstr[size - bitpos] = '0';
      }
    }
  }

  return bitstr;
}

