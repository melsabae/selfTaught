#include <iostream>
#include <math.h>
#include <unistd.h>
#include <memory>
#include <algorithm>
#include <array>
#include <numeric>


//const std::size_t N = 1 << 10;
//const std::size_t N = 1 << 8; // any higher of a shift and this will fail for a N*N*N matrix
const std::size_t N = 1 << 6; // any higher of a shift and this will fail for a N*N matrix


__global__
// increment all elements in parallel
void vec_inc(float* const c, const std::size_t n)
{
    for (std::size_t x = threadIdx.x + (blockIdx.x * blockDim.x); x < n; x += (blockDim.x * gridDim.x))
    {
        for (std::size_t y = threadIdx.y + (blockIdx.y * blockDim.y); y < n; y += (blockDim.y * gridDim.y))
        {
            for (std::size_t z = threadIdx.z + (blockIdx.z * blockDim.z); z < n; z += (blockDim.z * gridDim.z))
            {
                ++ c[(x * n * n) + (y * n) + z];
            }
        }
    }
}


int main(void)
{
    // grids and blocks are topologically laid out similar to the problem
    // for 1D arrays, a grid size of (1,1,1) = 1D, and a block size of (N,1,1) = N, would be enough to fully cover the array
    const dim3 grid_size(1, 1, 1);
    const dim3 block_size(512, 1, 1);

    std::size_t error_count = 0; // track errors found
    float* d_a = nullptr; // handle on CUDA memory
    //std::shared_ptr<std::array<float, N * N * N>> h_mat(new std::array<float, N * N * N>()); // matrix we want to do grid-strides
    std::shared_ptr<std::array<float, N * N>> h_mat(new std::array<float, N * N>()); // matrix we want to do grid-strides

    std::iota(h_mat->begin(), h_mat->end(), 0);

    cudaStream_t stream;

    if (nullptr == h_mat)
    {
        std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaStreamCreate(&stream))
    {
        std::cout << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaMalloc(&d_a, h_mat->size() * sizeof(d_a[0])))
    {
        std::cout << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaMemcpyAsync(d_a, h_mat->data(), h_mat->size() * sizeof(d_a[0]), cudaMemcpyHostToDevice, stream))
    {
        std::cout << __LINE__ << std::endl;
        return -__LINE__;
    }

    vec_inc<<<grid_size, block_size, 0, stream>>>(d_a, N);

    if (cudaSuccess != cudaMemcpyAsync(h_mat->data(), d_a, h_mat->size() * sizeof(d_a[0]), cudaMemcpyDeviceToHost, stream))
    {
        std::cout << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaStreamSynchronize(stream))
    {
        std::cout << __LINE__ << std::endl;
        return -__LINE__;
    }

    for (std::size_t i = 0; i < h_mat->size(); ++i)
    {
        if ((*h_mat)[i] != i + 1)
        {
            ++ error_count;
        }
    }

    std::cout << error_count << "/" << h_mat->size() << std::endl << std::flush;

    cudaFree(d_a);
    cudaStreamDestroy(stream);
    return 0;
}

