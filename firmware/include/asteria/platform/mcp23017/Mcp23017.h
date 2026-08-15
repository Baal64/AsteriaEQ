#pragma once

#include <stdint.h>
#include <asteria/platform/mcp23017/Mcp23017Types.h>

namespace asteria::platform::mcp23017
{

    class Mcp23017
    {
    public:
        explicit Mcp23017(uint8_t address);

        void begin();

        void configureOutput(
            Mcp23017Port port,
            uint8_t pin,
            bool initialState = false);

        void write(
            Mcp23017Port port,
            uint8_t pin,
            bool state);

        void configureInput(
            Mcp23017Port port,
            uint8_t pin,
            bool pullUp = false);

        bool read(
            Mcp23017Port port,
            uint8_t pin);

    private:
        void writeRegister(
            uint8_t registerAddress,
            uint8_t value);

        uint8_t address_;

        uint8_t directionA_ = 0xFFU;
        uint8_t directionB_ = 0xFFU;

        uint8_t outputA_ = 0x00U;
        uint8_t outputB_ = 0x00U;

        uint8_t readRegister(
            uint8_t registerAddress);
    };

} // namespace asteria::platform::mcp23017