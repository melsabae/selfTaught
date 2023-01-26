#!/usr/bin/env python3


import pycuda.autoinit
import pycuda.driver as drv
import numpy
from pycuda.compiler import SourceModule


N = numpy.uint32(2 ** 3)

mod = SourceModule("""
    __global__
    void vec_inc(float* const c, const std::size_t n)
    {
        for (std::size_t x = threadIdx.x + (blockIdx.x * blockDim.x); x < n; x += (blockDim.x * gridDim.x))
        {
            for (std::size_t y = threadIdx.y + (blockIdx.y * blockDim.y); y < n; y += (blockDim.y * gridDim.y))
            {
                for (std::size_t z = threadIdx.z + (blockIdx.z * blockDim.z); z < n; z += (blockDim.z * gridDim.z))
                {
                    c[(x * n * n) + (y * n) + z] = 4;
                }
            }
        }
    }
""")

do_the_thing = mod.get_function("vec_inc")

a = numpy.arange(N, dtype=float)

block=(16,1,1)
grid=(1,1,1)
#drv.In, drv.Out, drv.InOut
do_the_thing(drv.InOut(a), N, block=block, grid=grid)

max_elem = numpy.argmax(a)
print(max_elem, a[max_elem])
print(a)

