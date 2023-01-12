#include <iostream>
#include <math.h>
#include <unistd.h>
#include <memory>
#include <algorithm>
#include <vector>

const std::size_t N = 1 << 20;

__global__
void vec_add(float* const c, const float* const a, const float* const b, const std::size_t n)
{
    for (std::size_t i = threadIdx.x + (blockIdx.x * blockDim.x); i < n; i += (blockDim.x * gridDim.x))
    {
        c[i] = a[i] + b[i];
    }
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

    cudaMalloc(&d_a, N * sizeof(h_a[0]));
    cudaMalloc(&d_b, N * sizeof(h_b[0]));
    cudaMalloc(&d_c, N * sizeof(h_c[0]));

    std::fill(h_a.begin(), h_a.end(), 1.0);
    std::fill(h_b.begin(), h_b.end(), 2.0);

    cudaMemcpy(d_a, h_a.data(), N * sizeof(h_a[0]), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b.data(), N * sizeof(h_b[0]), cudaMemcpyHostToDevice);

    vec_add<<<grid_size, block_size>>>(d_c, d_a, d_b, N);

    cudaMemcpy(h_c.data(), d_c, N * sizeof(h_c[0]), cudaMemcpyDeviceToHost);
    cudaDeviceSynchronize(); // kernels are launched async, host immediately returns, so block until the computation is done

    for (std::size_t i = 0; i < N; ++ i)
    {
        if (h_a[i] + h_b[i] != h_c[i])
        {
            //std::cout << i << " " << h_c[i] << std::endl;
            ++ error_count;
        }
    }

    std::cout << error_count << " " << 100.0 * (static_cast<double>(error_count) / N) << "% mismatched" << std::endl << std::flush;

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    return 0;
}

