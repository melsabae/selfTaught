#include <iostream>
#include <math.h>
#include <unistd.h>
//#include <memory>
#include <algorithm>
#include <vector>


const std::size_t N = 1 << 20;


__device__ // can only be called from within a kernel, not from the host
void vec_inc(float* const c, const std::size_t n)
{
    for (std::size_t i = threadIdx.x + (blockIdx.x * blockDim.x); i < n; i += (blockDim.x * gridDim.x))
    {
        ++ c[i];
    }
}


__host__ // explicitly disallow this to run on the GPU, cannot be launched nor called from kernels
void vec_inc2(float* const c, const std::size_t n)
{
    for (std::size_t i = 0; i < n; ++ i)
    {
        ++ c[i];
    }
}



__global__
void vec_add(float* const c, const float* const a, const float* const b, const std::size_t n)
{
    for (std::size_t i = threadIdx.x + (blockIdx.x * blockDim.x); i < n; i += (blockDim.x * gridDim.x))
    {
        c[i] = a[i] + b[i];
    }

    vec_inc(c, n);
}


int main(void)
{
    // grids and blocks are topologically laid out similar to the problem
    // for 1D arrays, a grid size of (1,1,1) = 1D, and a block size of (N,1,1) = N, would be enough to fully cover the array
    const dim3 grid_size(1, 1, 1);
    const dim3 block_size(1024, 1, 1);

    std::vector<float> h_a(N);
    std::vector<float> h_b(N);
    std::vector<float> h_c(N);
    std::size_t error_count = 0;

    float* d_a = NULL;
    float* d_b = NULL;
    float* d_c = NULL;

    cudaStream_t stream;

    std::fill(h_a.begin(), h_a.end(), 1.0);
    std::fill(h_b.begin(), h_b.end(), 2.0);

    if (cudaSuccess != cudaStreamCreate(&stream))
    {
        std::cout << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaMalloc(&d_a, N * sizeof(h_a[0])))
    {
        std::cout << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaMalloc(&d_b, N * sizeof(h_b[0])))
    {
        std::cout << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaMalloc(&d_c, N * sizeof(h_c[0])))
    {
        std::cout << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaMemcpyAsync(d_a, h_a.data(), N * sizeof(h_a[0]), cudaMemcpyHostToDevice, stream))
    {
        std::cout << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaMemcpyAsync(d_b, h_b.data(), N * sizeof(h_b[0]), cudaMemcpyHostToDevice, stream))
    {
        std::cout << __LINE__ << std::endl;
        return -__LINE__;
    }

    vec_add<<<grid_size, block_size, 0, stream>>>(d_c, d_a, d_b, N);

    // this is slower to execute since we can just +1 in the prior kernel
    // however we want it in a separate function to keep code clean
    // so its not able to be launched like a kernel regularly can
    //vec_inc<<<grid_size, block_size, 0, stream>>>(d_c, N);

    if (cudaSuccess != cudaMemcpyAsync(h_c.data(), d_c, N * sizeof(h_c[0]), cudaMemcpyDeviceToHost, stream))
    {
        std::cout << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaStreamSynchronize(stream))
    {
        std::cout << __LINE__ << std::endl;
        return -__LINE__;
    }

    // now add 1 to everything again, once h_c has been received from the GPU via d_c
    vec_inc2(h_c.data(), h_c.size());

    for (std::size_t i = 0; i < N; ++i)
    {
        if (h_a[i] + h_b[i] + 2 != h_c[i])
        {
            //std::cout << i << " " << h_c[i] << std::endl;
            ++ error_count;
        }
    }

    std::cout << error_count << " " << 100.0 * (static_cast<double>(error_count) / N) << "% mismatched" << std::endl << std::flush;

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    cudaStreamDestroy(stream);
    return 0;
}

