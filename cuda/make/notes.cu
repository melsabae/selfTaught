#include <iostream>
#include <math.h>
#include <unistd.h>
#include <memory>

const std::size_t N = 1 << 20;

__global__
void vec_add(float* const c, const float* const a, const float* const b, const std::size_t n)
{
    // shared memory spaces are block-scoped and for intra-thread communication, 10 was meaningless here
    //__shared__ int shared_memory[10];

    // grids have blocks, blocks have threads
    // thread indices are not unique within a grid, so unique-ify it using block information
    const std::size_t i = threadIdx.x + (blockIdx.x * blockDim.x);
    //threadIdx.y + (blockIdx.y * blockDim.y);
    //threadIdx.z + (blockIdx.z * blockDim.z);

    // sometimes the grid is oversized statically for a problem that has an upper bound, though an instance may be smaller
    // so this guard is used in those cases
    // otherwise if the problem is the same size every time, the grid can be exactly sized, and the guard can be removed
    if (i < n)
    {
        c[i] = a[i] + b[i];
    }

    // barriers
    //__syncthreads(); all threads must hit this point before the kernel can finish
}

int main(void)
{
    // grids and blocks are topologically laid out similar to the problem
    // for 1D arrays, a grid size of (1,1,1) = 1D, and a block size of (N,1,1) = N, would be enough to fully cover the array
    const dim3 grid_size(1, 1, 1);
    const dim3 block_size(N, 1, 1);

    std::unique_ptr<float[]> h_a(new float[N]);
    std::unique_ptr<float[]> h_b(new float[N]);
    std::unique_ptr<float[]> h_c(new float[N]);

    std::size_t error_count = 0;

    float* d_a = NULL;
    float* d_b = NULL;
    float* d_c = NULL;

    cudaMalloc(&d_a, N * sizeof(h_a[0]));
    cudaMalloc(&d_b, N * sizeof(h_b[0]));
    cudaMalloc(&d_c, N * sizeof(h_c[0]));

    for (std::size_t i = 0; i < N; ++ i)
    {
        h_a[i] = 1;
        h_b[i] = 2;
    }

    // for the time being, this code does not work
    cudaMemcpy(d_a, h_a.get(), N * sizeof(h_a[0]), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b.get(), N * sizeof(h_b[0]), cudaMemcpyHostToDevice);
    cudaMemset(d_c, 0, N * sizeof(h_c[0]));
    vec_add<<<grid_size, block_size>>>(d_c, d_a, d_b, N);

    cudaDeviceSynchronize(); // kernels are launched async, host immediately returns, so block until the computation is done

    // kernels are launched async from the host, but are scheduled serially per device
    // since this machine has a single GPU, they'd be scheduled sequentially, but the host would be operating async

    cudaMemcpy(h_c.get(), d_c, sizeof(h_c), cudaMemcpyDeviceToHost);

    for (std::size_t i = 0; i < N; ++ i)
    {
        //if ((3 * (i + 1)) != h_c[i])
        std::cout << h_c[i] << std::endl;
        if (3 != h_c[i])
        {
            //std::cout << i << std::endl;
            //++ error_count;
        }
    }

    std::cout << 100.0 * (static_cast<double>(error_count) / N) << "% mismatched" << std::endl << std::flush;

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    return 0;
}

