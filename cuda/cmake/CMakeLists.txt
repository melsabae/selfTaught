cmake_minimum_required(VERSION 3.0)
project(cmake_and_cuda LANGUAGES CXX CUDA)




add_executable(test test.cu)

set_target_properties(test PROPERTIES CUDA_ARCHITECTURES "native")
target_compile_features(test PUBLIC cuda_std_20)




add_executable(multiple_streams multiple_streams.cu)

set_target_properties(multiple_streams PROPERTIES CUDA_ARCHITECTURES "native")
target_compile_features(multiple_streams PUBLIC cuda_std_20)




add_executable(grid_stride grid_stride.cu)

set_target_properties(grid_stride PROPERTIES CUDA_ARCHITECTURES "native")
target_compile_features(grid_stride PUBLIC cuda_std_20)




add_executable(small_transfers small_transfers.cu)

set_target_properties(small_transfers PROPERTIES CUDA_ARCHITECTURES "native")
target_compile_features(small_transfers PUBLIC cuda_std_20)


add_executable(indexing indexing.cu)

set_target_properties(indexing PROPERTIES CUDA_ARCHITECTURES "native")
target_compile_features(indexing PUBLIC cuda_std_20)

