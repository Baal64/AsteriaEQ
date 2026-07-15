#pragma once

#include <stdint.h>

namespace asteria::hardware
{

    struct EncoderReading
    {
        uint16_t rawPosition{0};
        float angleDeg{0.0F};
        bool valid{false};
    };

    class IAbsoluteEncoder
    {
    public:
        virtual ~IAbsoluteEncoder() = default;

        virtual bool begin() = 0;

        [[nodiscard]] virtual EncoderReading read() = 0;
    };

} // namespace asteria::hardware