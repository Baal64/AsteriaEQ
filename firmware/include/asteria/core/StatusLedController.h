#pragma once

#include <stdint.h>

#include <asteria/core/PositionHealth.h>
#include <asteria/core/TrackingMode.h>

namespace asteria::platform::mcp23017
{
    class Mcp23017DigitalOutput;
}

namespace asteria::core
{

    class StatusLedController
    {
    public:
        explicit StatusLedController(
            platform::mcp23017::Mcp23017DigitalOutput &output);

        void update(
            unsigned long currentMillis,
            PositionHealth rightAscensionHealth,
            PositionHealth declinationHealth,
            TrackingMode trackingMode);

    private:
        void updateLost(unsigned long currentMillis);
        void updateTemporaryInvalid(unsigned long currentMillis);
        void updateTracking(
            unsigned long currentMillis,
            TrackingMode trackingMode);

        void setOutput(bool state);

        platform::mcp23017::Mcp23017DigitalOutput &output_;

        bool outputState_{false};
    };

} // namespace asteria::core