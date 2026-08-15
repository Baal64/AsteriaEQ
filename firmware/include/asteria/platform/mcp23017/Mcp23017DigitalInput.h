#pragma once

#include <stdint.h>

#include <asteria/platform/mcp23017/Mcp23017Types.h>

namespace asteria::platform::mcp23017
{

    class Mcp23017;

    class Mcp23017DigitalInput
    {
    public:
        Mcp23017DigitalInput(
            Mcp23017 &device,
            Mcp23017Port port,
            uint8_t pin);

        void begin(bool pullUp = false);

        bool read() const;

    private:
        Mcp23017 &device_;

        Mcp23017Port port_;
        uint8_t pin_;

        bool initialized_ = false;
    };

} // namespace asteria::platform::mcp23017