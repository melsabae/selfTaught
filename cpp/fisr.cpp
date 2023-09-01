#include <cstdint>
#include <bit>
#include <iostream>
#include <valarray>


constexpr uint32_t float_hack(const float number)
{
    static const uint32_t magic = static_cast<uint32_t>(0x5f3759df);
    return magic - (std::bit_cast<uint32_t>(number) >> 1);
}


constexpr float fisr2(const float number)
{
    const float y = std::bit_cast<float>(float_hack(number));

    return y * (1.5f - ((number * 0.5f) * y * y));
}


float fisr(const float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;                       // evil floating point bit level hacking
    i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
                                                // y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}


int main(int argc, char** argv)
{
    const float v = 6.9f;

    const uint32_t v_hack = float_hack(v);

    std::cout << v_hack << std::endl;

    uint32_t test_hack = std::bit_cast<uint32_t>(v);
    std::cout << test_hack << std::endl;
    test_hack >>= 1;
    std::cout << test_hack << std::endl;
    test_hack &= 0x80FFFFFF;
    std::cout << test_hack << std::endl;
    test_hack |= 0x01000000;
    std::cout << test_hack << std::endl;

    //std::valarray<float> values = { 0.0, 1.0, 4.0, 9.0, 16.0 };

    //std::valarray<float> sqrts = values.apply(fisr);
    //std::valarray<float> sqrts2 = values.apply(fisr2);

    //for (const float f: sqrts)
    //{
    //    std::cout << 1.0 / f << std::endl;
    //}

    //std::cout << std::endl;

    //for (const float f: sqrts2)
    //{
    //    std::cout << 1.0 / f << std::endl;
    //}

    return 0;
}

