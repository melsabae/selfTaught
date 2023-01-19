#!/usr/bin/env python3


import pycuda.driver


__attributes__ = [
      pycuda.driver.device_attribute.MAX_THREADS_PER_BLOCK
    , pycuda.driver.device_attribute.MAX_BLOCK_DIM_X
    , pycuda.driver.device_attribute.MAX_BLOCK_DIM_Y
    , pycuda.driver.device_attribute.MAX_BLOCK_DIM_Z
    , pycuda.driver.device_attribute.MAX_GRID_DIM_X
    , pycuda.driver.device_attribute.MAX_GRID_DIM_Y
    , pycuda.driver.device_attribute.MAX_GRID_DIM_Z
    #, pycuda.driver.device_attribute.TOTAL_CONSTANT_MEMORY
    #, pycuda.driver.device_attribute.MULTIPROCESSOR_COUNT
    , pycuda.driver.device_attribute.MAX_SHARED_MEMORY_PER_BLOCK
    , pycuda.driver.device_attribute.MAX_REGISTERS_PER_BLOCK
    #, pycuda.driver.device_attribute.COMPUTE_MODE
    #, pycuda.driver.device_attribute.CONCURRENT_KERNELS
    #, pycuda.driver.device_attribute.PCI_BUS_ID
    #, pycuda.driver.device_attribute.PCI_DEVICE_ID
    , pycuda.driver.device_attribute.MAX_THREADS_PER_MULTIPROCESSOR
]


pycuda.driver.init()


for i in range(pycuda.driver.Device.count()):
    current_gpu = pycuda.driver.Device(i)
    print("gpu {}".format(i))

    for attr in __attributes__:
        print("\t {} = {}".format(attr, current_gpu.get_attribute(attr)))

