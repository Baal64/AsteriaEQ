#include <asteria/platform/mcp23017/Mcp23017.h>
#include <asteria/platform/mcp23017/Mcp23017DigitalOutput.h>

namespace asteria::platform::mcp23017
{

    Mcp23017DigitalOutput::Mcp23017DigitalOutput(
        Mcp23017 &device,
        const Mcp23017Port port,
        const uint8_t pin)
        : device_(device),
          port_(port),
          pin_(pin)
    {
    }

    void Mcp23017DigitalOutput::begin(
        const bool initialState)
    {
        state_ = initialState;

        device_.configureOutput(
            port_,
            pin_,
            initialState);

        initialized_ = true;
    }

    void Mcp23017DigitalOutput::write(
        const bool state)
    {
        if (!initialized_)
        {
            return;
        }

        device_.write(
            port_,
            pin_,
            state);

        state_ = state;
    }

    bool Mcp23017DigitalOutput::state() const
    {
        return state_;
    }

} // namespace asteria::platform::mcp23017