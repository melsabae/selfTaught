cmake_minimum_required(VERSION 3.0)
project(cmake_and_cuda LANGUAGES CXX CUDA)

add_executable(test test.cu)

set_target_properties(test PROPERTIES CUDA_ARCHITECTURES "native")
target_compile_features(test PUBLIC cuda_std_17)

