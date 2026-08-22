#pragma once

#include <stdint.h>

namespace asteria::platform::as5048a
{

    class As5048a
    {
    public:
        explicit As5048a(uint8_t chipSelectPin);

        void begin();

        uint16_t readRawAngle();

        float angleDeg();

        static float rawToDegrees(uint16_t rawAngle);

        bool hasError() const;

        void clearError();

    private:
        uint16_t transfer16(uint16_t command);

        uint8_t chipSelectPin_;

        static bool hasEvenParity(uint16_t value);

        bool error_;
    };

} // namespace asteria::platform::as5048a