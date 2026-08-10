#pragma once

#include <stdint.h>

#include <asteria/hardware/IDigitalOutput.h>

namespace asteria::platform::mcp23017
{

    enum class Mcp23017Port : uint8_t
    {
        PortA,
        PortB
    };

    class Mcp23017DigitalOutput final
        : public hardware::IDigitalOutput
    {
    public:
        Mcp23017DigitalOutput(
            Mcp23017Port port,
            uint8_t pin);

        void begin(bool initialState = false);

        void write(bool state) override;

        bool state() const override;

    private:
        Mcp23017Port port_;
        uint8_t pin_;

        bool state_ = false;
        bool initialized_ = false;
    };

} // namespace asteria::platform::mcp23017