#pragma once
#include <cmath>
#include <cstdint>
#include <utility>

namespace minerva
{

/*
    Utilities to save and load floating point numbers.
    We work with the mantissa and the exponent as we can't assume the size
    of 'float' and 'double' on different platforms.
*/

inline std::pair<int64_t, int32_t> serializeReal(double x)
{
    if (x == 0.0)
        return std::make_pair<>(0, 0);

    int exponent;
    double mantissa = std::frexp(x, &exponent);

    int64_t intMantissa = static_cast<int64_t>(mantissa * (1LL << 53));
    exponent -= 53;

    return std::make_pair<>(intMantissa, exponent);
}

inline double deserializeReal(std::pair<int64_t, int32_t> data)
{
    return std::ldexp(static_cast<double>(data.first), data.second);
}

class SerializableReal
{
  public:
    int64_t mantissa;
    int32_t exponent;

    SerializableReal() : mantissa(0), exponent(0)
    {
    }

    SerializableReal(int64_t mantissa, int32_t exponent) : mantissa(mantissa), exponent(exponent)
    {
    }

    SerializableReal(double x)
    {
        auto [mantissa, exponent] = serializeReal(x);
        this->mantissa = mantissa;
        this->exponent = exponent;
    }

    operator double() const
    {
        return deserializeReal({mantissa, exponent});
    }

    // SPACESHIP OPERATOR!!!
    auto operator<=>(const SerializableReal &other) const noexcept = default;
};

} // namespace minerva
