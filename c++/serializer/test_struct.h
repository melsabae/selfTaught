#ifndef __TEST_STRUCT_H__
# define __TEST_STRUCT_H__

#include "serialization.h"

DECLARE_SERIALIZATION(
    test_struct
    , { int a; float b; }
    )

#endif //__TEST_STRUCT_H__
