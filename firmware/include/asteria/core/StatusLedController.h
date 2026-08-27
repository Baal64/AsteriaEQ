#pragma once

#include <stdint.h>

#include <asteria/core/PositionHealth.h>
#include <asteria/core/TrackingMode.h>
#include <asteria/core/MountState.h>

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
            MountState mountState,
            TrackingMode activeTrackingMode,
            TrackingMode displayTrackingMode);

    private:
        void updateLost(unsigned long currentMillis);
        void updateTemporaryInvalid(unsigned long currentMillis);
        void updateTracking(
            unsigned long currentMillis,
            TrackingMode trackingMode);

        void setOutput(bool state);

        platform::mcp23017::Mcp23017DigitalOutput &output_;

        bool outputState_{false};

        void updateConfirmation(
            unsigned long currentMillis);

        void detectChange(
            unsigned long currentMillis,
            MountState mountState,
            TrackingMode activeTrackingMode);

        MountState previousMountState_{
            MountState::Initializing};

        TrackingMode previousTrackingMode_{
            TrackingMode::Sidereal};

        bool previousStateInitialized_{false};

        bool confirmationActive_{false};

        unsigned long confirmationStartMillis_{0UL};
    };

} // namespace asteria::core