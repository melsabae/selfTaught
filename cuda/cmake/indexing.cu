#include <iostream>
#include <math.h>
#include <unistd.h>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cassert>


constexpr size_t side = 2;
constexpr size_t num_el = side * side * side;


__global__
void f(int32_t* data, const size_t x)
{
    // assume data is being horizontally striped by blocks
    for (size_t i = (blockIdx.x * blockDim.x) + threadIdx.x; i < x; i += blockDim.x * gridDim.x)
    {
        data[i] = i + 2;
    }
}


__global__
void g(int32_t* data, const size_t x, const size_t y)
{
    // assume data is being horizontally striped by blocks
    for (size_t i = (blockIdx.x * blockDim.x) + threadIdx.x; i < x; i += blockDim.x * gridDim.x)
    {
        data[y * threadIdx.y + i] = (threadIdx.y * 2 + threadIdx.x + 1) * 20;
    }
}


__global__
void h(int32_t* data, const size_t x, const size_t y, const size_t z)
{
    // assume data is being horizontally striped by blocks
    for (size_t i = (blockIdx.x * blockDim.x) + threadIdx.x; i < x; i += blockDim.x * gridDim.x)
    {
        data[z * (y * threadIdx.y + x * threadIdx.x) + (y * threadIdx.y) + i] = (threadIdx.z * 4 + threadIdx.y * 2 + threadIdx.x + 1) * 20;
    }
}


void reset(int32_t* data)
{
    memset(data, -1, sizeof(*data) * num_el * 3);

    for (size_t i = 0; i < 3 * num_el; ++ i)
    {
        if (i >= num_el and i < 2 * num_el)
        {
            data[i] = i;
        }
    }
}


void print(int32_t* data)
{
    for (size_t i = 0; i < 3 * num_el; ++ i)
    {
        if (data[i] == -1)
        {
            std::cout << ",";
        }
        else
        {
            std::cout << data[i] << ",";
        }
    }
    std::cout << std::endl;
}


size_t num_diff(int32_t* data)
{
    size_t n = 0;

    for (size_t i = 0; i < 3 * num_el; ++ i)
    {
        if (i >= num_el and i < 2 * num_el)
        {
            if (data[i] != i)
            {
                n += 1;
            }
        }
        else
        {
            if (data[i] != -1)
            {
                n += 1;
            }
        }
    }

    return n;
}


void test_f(int32_t* data, cudaStream_t& stream)
{
    constexpr dim3 grid_size { 1, 1, 1 };
    constexpr dim3 block_size { 1024, 1, 1 };

    std::cout << ">>> test_f" << std::endl;
    reset(data);
    print(data);

    f<<<grid_size, block_size, 0, stream>>>(data + num_el, side);

    if (cudaSuccess != cudaStreamSynchronize(stream))
    {
        std::cerr << "bailing " << __LINE__ << std::endl;
        exit(__LINE__);
    }

    print(data);
    std::cout << "<<< test_f " << num_diff(data) << std::endl << std::endl;
}


void test_g(int32_t* data, cudaStream_t& stream)
{
    constexpr dim3 grid_size { 1, 1, 1 };
    constexpr dim3 block_size { 1024 / side, side, 1 };

    std::cout << ">>> test_g" << std::endl;
    reset(data);
    print(data);

    g<<<grid_size, block_size, 0, stream>>>(data + num_el, side, side);

    if (cudaSuccess != cudaStreamSynchronize(stream))
    {
        std::cerr << "bailing " << __LINE__ << std::endl;
        exit(__LINE__);
    }

    print(data);
    std::cout << "<<< test_g " << num_diff(data) << std::endl << std::endl;
}


void test_h(int32_t* data, cudaStream_t& stream)
{
    constexpr dim3 grid_size { 1, 1, 1 };
    constexpr dim3 block_size { 1024 / (side * side), side, side };

    std::cout << ">>> test_h" << std::endl;
    reset(data);
    print(data);

    h<<<grid_size, block_size, 0, stream>>>(data + num_el, side, side, side);

    if (cudaSuccess != cudaStreamSynchronize(stream))
    {
        std::cerr << "bailing " << __LINE__ << std::endl;
        exit(__LINE__);
    }

    print(data);
    std::cout << "<<< test_h " << num_diff(data) << std::endl << std::endl;
}


int main(void)
{
    static_assert(1 < side);
    static_assert(1 < num_el && num_el <= 1024);

    cudaStream_t stream;
    int32_t* data_f = nullptr;
    int32_t* data_g = nullptr;
    int32_t* data_h = nullptr;

    if (
           // pad the area of data with just some canary zeros
           cudaSuccess != cudaMallocManaged(&data_f, 3 * num_el * sizeof(*data_f))
        or cudaSuccess != cudaMallocManaged(&data_g, 3 * num_el * sizeof(*data_g))
        or cudaSuccess != cudaMallocManaged(&data_h, 3 * num_el * sizeof(*data_h))
        or cudaSuccess != cudaStreamCreate(&stream)
       )
    {
        std::cerr << "bailing " << __LINE__ << std::endl;
        return -__LINE__;
    }

    test_f(data_f, stream);
    test_g(data_g, stream);
    test_h(data_h, stream);

    cudaFree(data_f);
    cudaFree(data_g);
    cudaFree(data_h);
    cudaStreamDestroy(stream);
    return 0;
}

