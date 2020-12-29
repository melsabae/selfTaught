#include <cstddef>
#include "test_struct.h"

int main(int argc, char** argv)
{
  serialize_test_struct(NULL, NULL);
  deserialize_test_struct(NULL, NULL);
  return 0;
}
