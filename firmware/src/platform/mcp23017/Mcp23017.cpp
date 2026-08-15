#include <Arduino.h>
#include <Wire.h>

#include <asteria/platform/mcp23017/Mcp23017.h>

namespace asteria::platform::mcp23017
{

    namespace
    {

        constexpr uint8_t IODIRA = 0x00U;
        constexpr uint8_t IODIRB = 0x01U;

        constexpr uint8_t OLATA = 0x14U;
        constexpr uint8_t OLATB = 0x15U;

        constexpr uint8_t GPPUA = 0x0CU;
        constexpr uint8_t GPPUB = 0x0DU;

        constexpr uint8_t GPIOA = 0x12U;
        constexpr uint8_t GPIOB = 0x13U;

    } // namespace

    Mcp23017::Mcp23017(uint8_t address)
        : address_(address)
    {
    }

    void Mcp23017::begin()
    {
        Wire.begin();

        // Start from a known and safe state:
        // all pins configured as inputs.
        directionA_ = 0xFFU;
        directionB_ = 0xFFU;

        // Output latches start LOW.
        outputA_ = 0x00U;
        outputB_ = 0x00U;

        writeRegister(OLATA, outputA_);
        writeRegister(OLATB, outputB_);

        writeRegister(IODIRA, directionA_);
        writeRegister(IODIRB, directionB_);
    }

    void Mcp23017::writeRegister(
        uint8_t registerAddress,
        uint8_t value)
    {
        Wire.beginTransmission(address_);

        Wire.write(registerAddress);
        Wire.write(value);

        Wire.endTransmission();
    }

    void Mcp23017::configureOutput(
        const Mcp23017Port port,
        const uint8_t pin,
        const bool initialState)
    {
        if (pin > 7U)
        {
            return;
        }

        const uint8_t mask =
            static_cast<uint8_t>(1U << pin);

        if (port == Mcp23017Port::PortA)
        {
            if (initialState)
            {
                outputA_ |= mask;
            }
            else
            {
                outputA_ &= static_cast<uint8_t>(~mask);
            }

            writeRegister(OLATA, outputA_);

            directionA_ &=
                static_cast<uint8_t>(~mask);

            writeRegister(IODIRA, directionA_);
        }
        else
        {
            if (initialState)
            {
                outputB_ |= mask;
            }
            else
            {
                outputB_ &= static_cast<uint8_t>(~mask);
            }

            writeRegister(OLATB, outputB_);

            directionB_ &=
                static_cast<uint8_t>(~mask);

            writeRegister(IODIRB, directionB_);
        }
    }

    void Mcp23017::write(
        const Mcp23017Port port,
        const uint8_t pin,
        const bool state)
    {
        if (pin > 7U)
        {
            return;
        }

        const uint8_t mask =
            static_cast<uint8_t>(1U << pin);

        if (port == Mcp23017Port::PortA)
        {
            if (state)
            {
                outputA_ |= mask;
            }
            else
            {
                outputA_ &= static_cast<uint8_t>(~mask);
            }

            writeRegister(OLATA, outputA_);
        }
        else
        {
            if (state)
            {
                outputB_ |= mask;
            }
            else
            {
                outputB_ &= static_cast<uint8_t>(~mask);
            }

            writeRegister(OLATB, outputB_);
        }
    }

    uint8_t Mcp23017::readRegister(
        const uint8_t registerAddress)
    {
        Wire.beginTransmission(address_);
        Wire.write(registerAddress);
        Wire.endTransmission(false);

        Wire.requestFrom(address_, static_cast<uint8_t>(1U));

        if (Wire.available() == 0)
        {
            return 0U;
        }

        return Wire.read();
    }

    void Mcp23017::configureInput(
        const Mcp23017Port port,
        const uint8_t pin,
        const bool pullUp)
    {
        if (pin > 7U)
        {
            return;
        }

        const uint8_t mask =
            static_cast<uint8_t>(1U << pin);

        if (port == Mcp23017Port::PortA)
        {
            directionA_ |= mask;
            writeRegister(IODIRA, directionA_);

            uint8_t pullUpRegister =
                readRegister(GPPUA);

            if (pullUp)
            {
                pullUpRegister |= mask;
            }
            else
            {
                pullUpRegister &=
                    static_cast<uint8_t>(~mask);
            }

            writeRegister(GPPUA, pullUpRegister);
        }
        else
        {
            directionB_ |= mask;
            writeRegister(IODIRB, directionB_);

            uint8_t pullUpRegister =
                readRegister(GPPUB);

            if (pullUp)
            {
                pullUpRegister |= mask;
            }
            else
            {
                pullUpRegister &=
                    static_cast<uint8_t>(~mask);
            }

            writeRegister(GPPUB, pullUpRegister);
        }
    }

    bool Mcp23017::read(
        const Mcp23017Port port,
        const uint8_t pin)
    {
        if (pin > 7U)
        {
            return false;
        }

        const uint8_t mask =
            static_cast<uint8_t>(1U << pin);

        const uint8_t value =
            port == Mcp23017Port::PortA
                ? readRegister(GPIOA)
                : readRegister(GPIOB);

        return (value & mask) != 0U;
    }

} // namespace asteria::platform::mcp23017