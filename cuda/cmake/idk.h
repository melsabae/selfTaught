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
    // num_threads >= 32
    // if num_blocks != num_threads, num_threads > num_blocks
    const uint32_t shift = static_cast<uint32_t>(std::ceil(std::log2(n)));
    const uint32_t nt = std::max({ 32, 1 << (shift - (shift >> 1)) });

    // warp sizes are at least 32 threads
    return { static_cast<uint32_t>(n) / nt, nt };
}


#endif // IDK_H

