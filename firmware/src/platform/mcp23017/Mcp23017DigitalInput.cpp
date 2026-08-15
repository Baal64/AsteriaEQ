#include <asteria/platform/mcp23017/Mcp23017.h>
#include <asteria/platform/mcp23017/Mcp23017DigitalInput.h>

namespace asteria::platform::mcp23017
{

    Mcp23017DigitalInput::Mcp23017DigitalInput(
        Mcp23017 &device,
        const Mcp23017Port port,
        const uint8_t pin)
        : device_(device),
          port_(port),
          pin_(pin)
    {
    }

    void Mcp23017DigitalInput::begin(
        const bool pullUp)
    {
        device_.configureInput(
            port_,
            pin_,
            pullUp);

        initialized_ = true;
    }

    bool Mcp23017DigitalInput::read() const
    {
        if (!initialized_)
        {
            return false;
        }

        return device_.read(
            port_,
            pin_);
    }

} // namespace asteria::platform::mcp23017