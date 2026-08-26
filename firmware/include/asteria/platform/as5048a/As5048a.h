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
        bool hasParityError() const;
        bool hasSensorError() const;

        uint16_t lastRawAngle() const;

        void clearError();

    private:
        uint16_t transfer16(uint16_t command);

        static bool hasEvenParity(uint16_t value);

        uint8_t chipSelectPin_;

        uint16_t lastRawAngle_;

        bool error_;
        bool parityError_;
        bool sensorError_;
    };

} // namespace asteria::platform::as5048a