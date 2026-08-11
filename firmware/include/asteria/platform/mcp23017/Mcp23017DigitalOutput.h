#pragma once

#include <stdint.h>

#include <asteria/hardware/IDigitalOutput.h>
#include <asteria/platform/mcp23017/Mcp23017Types.h>

namespace asteria::platform::mcp23017
{

    class Mcp23017;

    class Mcp23017DigitalOutput final
        : public hardware::IDigitalOutput
    {
    public:
        Mcp23017DigitalOutput(
            Mcp23017 &device,
            Mcp23017Port port,
            uint8_t pin);

        void begin(bool initialState = false);

        void write(bool state) override;

        bool state() const override;

    private:
        Mcp23017 &device_;

        Mcp23017Port port_;
        uint8_t pin_;

        bool state_ = false;
        bool initialized_ = false;
    };

} // namespace asteria::platform::mcp23017