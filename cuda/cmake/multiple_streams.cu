#include <iostream>
#include <math.h>
#include <unistd.h>
#include <memory>
#include <array>
#include <algorithm>
#include <vector>


const std::size_t NUMBER_STREAMS = 1;
const std::size_t N = 1 << 20;


struct test_struct
{
    cudaStream_t stream;

    std::unique_ptr<std::array<float, N>> h_a;
    std::unique_ptr<std::array<float, N>> h_b;
    std::unique_ptr<std::array<float, N>> h_c;

    float* d_a;
    float* d_b;
    float* d_c;

    std::size_t error_count;
};


typedef struct test_struct test_struct_t;


int make_test_struct(test_struct_t& t)
{
    t.h_a.reset(new std::array<float, N>);
    t.h_b.reset(new std::array<float, N>);
    t.h_c.reset(new std::array<float, N>);

    if (nullptr == t.h_a)
    {
        std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (nullptr == t.h_a)
    {
        std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (nullptr == t.h_a)
    {
        std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaStreamCreate(&t.stream))
    {
        std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaMalloc(&t.d_a, N * sizeof(t.d_a[0])))
    {
        std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaMalloc(&t.d_b, N * sizeof(t.d_b[0])))
    {
        std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaMalloc(&t.d_c, N * sizeof(t.d_c[0])))
    {
        std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
        return -__LINE__;
    }

    std::fill(t.h_a->begin(), t.h_a->end(), 1.0);
    std::fill(t.h_b->begin(), t.h_b->end(), 2.0);

    t.error_count = 0;

    return 0;
}


int destroy_test_struct(test_struct_t& t)
{
    if (cudaSuccess != cudaFree(t.d_a))
    {
        std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaFree(t.d_b))
    {
        std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaFree(t.d_c))
    {
        std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
        return -__LINE__;
    }

    if (cudaSuccess != cudaStreamDestroy(t.stream))
    {
        std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
        return -__LINE__;
    }

    return 0;
}


__global__
void vec_add(float* const c, const float* const a, const float* const b, const std::size_t n)
{
    for (std::size_t i = threadIdx.x + (blockIdx.x * blockDim.x); i < n; i += (blockDim.x * gridDim.x))
    {
        c[i] = a[i] + b[i] + 1;
    }
}


int main(void)
{
    const dim3 grid_size (1, 1, 1);
    const dim3 block_size (1024, 1, 1);

    std::array<test_struct_t, NUMBER_STREAMS> streams;

    std::for_each(streams.begin(), streams.end(), make_test_struct);

    for (test_struct_t& t: streams)
    {
        if (cudaSuccess != cudaMemcpyAsync(t.d_a, t.h_a->data(), N * sizeof(t.d_a[0]), cudaMemcpyHostToDevice, t.stream))
        {
            std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
            return -__LINE__;
        }

        if (cudaSuccess != cudaMemcpyAsync(t.d_b, t.h_b->data(), N * sizeof(t.d_b[0]), cudaMemcpyHostToDevice, t.stream))
        {
            std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
            return -__LINE__;
        }

        vec_add<<<grid_size, block_size, 0, t.stream>>>(t.d_c, t.d_a, t.d_b, N);

        if (cudaSuccess != cudaMemcpyAsync(t.h_c->data(), t.d_c, N * sizeof(t.d_c[0]), cudaMemcpyDeviceToHost, t.stream))
        {
            std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
            return -__LINE__;
        }
    }

    for (test_struct_t& t: streams)
    {
        if (cudaSuccess != cudaStreamSynchronize(t.stream))
        {
            std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
            return -__LINE__;
        }
    }

    for (test_struct_t& t: streams)
    {
        for (std::size_t i = 0; i < N; ++ i)
        {
            if (4 != t.h_c->at(i))
            {
                ++ t.error_count;
            }
        }


        if (0 != t.error_count)
        {
            std::cout << t.error_count << std::endl << std::flush;
        }
    }

    std::for_each(streams.begin(), streams.end(), destroy_test_struct);

    return 0;
}

