#include <iostream>
#include "test_struct.h"

SERIALIZATION(test_struct)
{
  std::cout << __FUNCTION__ << std::endl;
}

DESERIALIZATION(test_struct)
{
  std::cout << __FUNCTION__ << std::endl;
}

