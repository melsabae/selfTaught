#ifndef IDK_H
#define IDK_H


#include <tuple>
#include <cinttypes>
#include <algorithm>
#include <cmath>


[[nodiscard]]
std::tuple<uint32_t, uint32_t> compute_blocks_threads(const size_t n)
{
    // num_blocks * num_threads >= n
    // 32 <= num_threads <= 1024
    // ideally, num_blocks is about the same size as num_threads
    const uint32_t shift = static_cast<uint32_t>(std::ceil(std::log2(n)));

    // warp sizes are at least 32 threads, blocks no more than 1024 threads
    const uint32_t nt = std::min({ 1024, std::max({ 32, 1 << (shift - (shift >> 1)) }) });

    return { static_cast<uint32_t>(n) / nt, nt };
}


#endif // IDK_H

