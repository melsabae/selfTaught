cmake_minimum_required(VERSION 3.0)
project(cmake_and_cuda LANGUAGES CXX CUDA)


add_executable(test test.cu)

set_target_properties(test PROPERTIES CUDA_ARCHITECTURES "native")
target_compile_features(test PUBLIC cuda_std_17)


add_executable(multiple_streams multiple_streams.cu)

set_target_properties(multiple_streams PROPERTIES CUDA_ARCHITECTURES "native")
target_compile_features(multiple_streams PUBLIC cuda_std_17)

