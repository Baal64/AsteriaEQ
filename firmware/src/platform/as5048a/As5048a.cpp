#include <Arduino.h>
#include <SPI.h>

#include <asteria/platform/as5048a/As5048a.h>

namespace asteria::platform::as5048a
{

    namespace
    {

        constexpr uint16_t ANGLE_REGISTER = 0x3FFFU;
        constexpr uint16_t READ_FLAG = 0x4000U;

        constexpr uint16_t DATA_MASK = 0x3FFFU;
        constexpr uint16_t PARITY_BIT = 0x8000U;

        constexpr uint32_t SPI_CLOCK_HZ = 1000000UL;

        uint16_t addEvenParity(
            uint16_t value)
        {
            uint16_t parityValue = value;

            bool oddParity = false;

            while (parityValue != 0U)
            {
                oddParity =
                    !oddParity;

                parityValue &=
                    static_cast<uint16_t>(
                        parityValue - 1U);
            }

            if (oddParity)
            {
                value |= PARITY_BIT;
            }

            return value;
        }

        bool As5048a::hasParityError() const
        {
            return parityError_;
        }

        bool As5048a::hasSensorError() const
        {
            return sensorError_;
        }

    } // namespace

    As5048a::As5048a(
        const uint8_t chipSelectPin)
        : chipSelectPin_(chipSelectPin),
          error_(false),
          parityError_(false),
          sensorError_(false)
    {
    }

    void As5048a::begin()
    {
        digitalWrite(
            chipSelectPin_,
            HIGH);

        pinMode(
            chipSelectPin_,
            OUTPUT);

        SPI.begin();

        clearError();
    }

    uint16_t As5048a::readRawAngle()
    {
        constexpr uint16_t ERROR_FLAG =
            0x4000U;

        const uint16_t command =
            addEvenParity(
                static_cast<uint16_t>(
                    READ_FLAG |
                    ANGLE_REGISTER));

        transfer16(command);

        const uint16_t response =
            transfer16(0x0000U);

        const bool parityValid =
            hasEvenParity(response);

        parityError_ =
            !parityValid;

        sensorError_ =
            (response & ERROR_FLAG) != 0U;

        error_ =
            parityError_ ||
            sensorError_;

        if (error_)
        {
            clearError();
        }

        return static_cast<uint16_t>(
            response &
            DATA_MASK);
    }

    uint16_t As5048a::transfer16(
        const uint16_t command)
    {
        SPI.beginTransaction(
            SPISettings(
                SPI_CLOCK_HZ,
                MSBFIRST,
                SPI_MODE1));

        digitalWrite(
            chipSelectPin_,
            LOW);

        delayMicroseconds(1U);

        const uint8_t highByte =
            SPI.transfer(
                static_cast<uint8_t>(
                    command >> 8U));

        const uint8_t lowByte =
            SPI.transfer(
                static_cast<uint8_t>(
                    command & 0xFFU));

        digitalWrite(
            chipSelectPin_,
            HIGH);

        SPI.endTransaction();

        return static_cast<uint16_t>(
            (static_cast<uint16_t>(
                 highByte)
             << 8U) |
            lowByte);
    }

    float As5048a::rawToDegrees(
        const uint16_t rawAngle)
    {
        return static_cast<float>(rawAngle) *
               360.0F /
               16384.0F;
    }

    float As5048a::angleDeg()
    {
        return rawToDegrees(
            readRawAngle());
    }

    bool As5048a::hasEvenParity(
        uint16_t value)
    {
        bool oddParity = false;

        while (value != 0U)
        {
            oddParity = !oddParity;

            value &=
                static_cast<uint16_t>(
                    value - 1U);
        }

        return !oddParity;
    }

    bool As5048a::hasError() const
    {
        return error_;
    }

    void As5048a::clearError()
    {
        constexpr uint16_t CLEAR_ERROR_REGISTER = 0x0001U;

        const uint16_t command =
            addEvenParity(
                static_cast<uint16_t>(
                    READ_FLAG |
                    CLEAR_ERROR_REGISTER));

        transfer16(command);

        // Retrieve the error register response.
        transfer16(0x0000U);

        error_ = false;
        parityError_ = false;
        sensorError_ = false;
    }

} // namespace asteria::platform::as5048a