#include <iostream>
#include <math.h>
#include <unistd.h>
#include <memory>
#include <algorithm>
#include <array>
#include <numeric>



// the output incorrectly says that the data mismatches, but it appears to be an issue with doubles
// changing all types to integral types showed 0 issues, which for small N, was also hand verified
// moving to double reduced the error rate


const std::size_t N = 1 << 3;
const double h_m = 7.2;
const double h_b = 3.4;


struct linear_params
{
    double m;
    double b;
};


typedef struct linear_params linear_params_t;


__global__
void linear(double* y, const std::size_t n, const double* x, const double m, const double b)
{
    for (std::size_t i = threadIdx.x + (blockIdx.x * blockDim.x); i < n; i += (blockDim.x * gridDim.x))
    {
        y[i] = m * x[i] + b;
    }
}


int main(void)
{
    const dim3 grid_size(1, 1, 1);
    const dim3 block_size(1024, 1, 1);

    std::unique_ptr<std::array<double, N>> h_x (new std::array<double, N>());
    std::unique_ptr<std::array<double, N>> h_y (new std::array<double, N>());
    double* d_y = NULL;
    double* d_x = NULL;
    cudaStream_t stream;

    std::iota(h_x->begin(), h_x->end(), 0);

    if (cudaSuccess != cudaStreamCreate(&stream))
    {
        std::cout << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaMallocHost(&d_y, sizeof(d_y[0]) * h_y->size()))
    {
        std::cout << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaMallocHost(&d_x, sizeof(d_x[0]) * h_x->size()))
    {
        std::cout << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaMemcpyAsync(d_x, h_x->data(), sizeof(d_x[0]) * N, cudaMemcpyHostToDevice, stream))
    {
        std::cout << __LINE__ << std::endl;
        return -__LINE__;
    }

    linear<<<grid_size, block_size, 0, stream>>>(d_y, N, d_x, h_m, h_b);

    if (cudaSuccess != cudaMemcpyAsync(h_y->data(), d_y, sizeof(d_y[0]) * N, cudaMemcpyDeviceToHost, stream))
    {
        std::cout << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaStreamSynchronize(stream))
    {
        std::cout << __LINE__ << std::endl;
        return -__LINE__;
    }

    std::size_t error_count = 0;

    for (std::size_t i = 0; i < h_x->size(); ++i)
    {
        if (((h_m * (*h_x)[i]) + h_b) != (*h_y)[i])
        {
            // because the GPU and CPU compute differences in floats, output what the difference is
            // it should be very small
            std::cout << (((h_m * (*h_x)[i]) + h_b) - (*h_y)[i]) << std::endl;
            ++ error_count;
        }
    }

    //for (std::size_t i = 0; i < h_x->size(); ++i)
    //{
    //    std::cout << h_y(i) << " = (" << m << ")" << h_x(i) << " + " << b << std::endl;
    //}

    //for (std::size_t i = 0; i < h_x->size(); ++i)
    //{
    //    std::cout << h_y(i) << "," << m << "," << h_x(i) << "," << b << std::endl;
    //}

    std::cout << error_count << "/" <<  N << std::endl << std::flush;

    cudaFreeHost(d_x);
    cudaFreeHost(d_y);
    cudaStreamDestroy(stream);
    return 0;
}

