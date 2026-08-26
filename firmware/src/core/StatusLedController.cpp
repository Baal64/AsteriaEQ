#include <asteria/core/StatusLedController.h>

#include <asteria/config/StatusLedConfiguration.h>
#include <asteria/platform/mcp23017/Mcp23017DigitalOutput.h>

namespace asteria::core
{
    StatusLedController::StatusLedController(
        platform::mcp23017::Mcp23017DigitalOutput &output)
        : output_(output)
    {
    }

    void StatusLedController::update(
        const unsigned long currentMillis,
        const PositionHealth rightAscensionHealth,
        const PositionHealth declinationHealth,
        const TrackingMode trackingMode)
    {
        if (
            rightAscensionHealth == PositionHealth::Lost ||
            declinationHealth == PositionHealth::Lost)
        {
            updateLost(currentMillis);
            return;
        }

        if (
            rightAscensionHealth ==
                PositionHealth::TemporarilyInvalid ||
            declinationHealth ==
                PositionHealth::TemporarilyInvalid)
        {
            updateTemporaryInvalid(currentMillis);
            return;
        }

        updateTracking(
            currentMillis,
            trackingMode);
    }

    void StatusLedController::updateLost(
        const unsigned long currentMillis)
    {
        const unsigned long periodMs =
            config::statusLed::LOST_ON_MS +
            config::statusLed::LOST_OFF_MS;

        const unsigned long phaseMs =
            currentMillis % periodMs;

        setOutput(
            phaseMs <
            config::statusLed::LOST_ON_MS);
    }

    void StatusLedController::updateTemporaryInvalid(
        const unsigned long currentMillis)
    {
        const unsigned long firstOnEndMs =
            config::statusLed::TEMP_INVALID_ON_MS;

        const unsigned long firstOffEndMs =
            firstOnEndMs +
            config::statusLed::TEMP_INVALID_OFF_MS;

        const unsigned long secondOnEndMs =
            firstOffEndMs +
            config::statusLed::TEMP_INVALID_ON_MS;

        const unsigned long periodMs =
            secondOnEndMs +
            config::statusLed::TEMP_INVALID_PAUSE_MS;

        const unsigned long phaseMs =
            currentMillis % periodMs;

        const bool firstFlash =
            phaseMs < firstOnEndMs;

        const bool secondFlash =
            phaseMs >= firstOffEndMs &&
            phaseMs < secondOnEndMs;

        setOutput(
            firstFlash ||
            secondFlash);
    }

    void StatusLedController::updateTracking(
        const unsigned long currentMillis,
        const TrackingMode trackingMode)
    {
        unsigned long onMs = 0UL;
        unsigned long offMs = 0UL;

        switch (trackingMode)
        {
        case TrackingMode::Sidereal:
            onMs =
                config::statusLed::SIDEREAL_ON_MS;
            offMs =
                config::statusLed::SIDEREAL_OFF_MS;
            break;

        case TrackingMode::Lunar:
            onMs =
                config::statusLed::LUNAR_ON_MS;
            offMs =
                config::statusLed::LUNAR_OFF_MS;
            break;

        case TrackingMode::Solar:
            onMs =
                config::statusLed::SOLAR_ON_MS;
            offMs =
                config::statusLed::SOLAR_OFF_MS;
            break;
        }

        const unsigned long periodMs =
            onMs + offMs;

        if (periodMs == 0UL)
        {
            setOutput(false);
            return;
        }

        const unsigned long phaseMs =
            currentMillis % periodMs;

        setOutput(
            phaseMs < onMs);
    }

    void StatusLedController::setOutput(
        const bool state)
    {
        if (state == outputState_)
        {
            return;
        }

        outputState_ = state;
        output_.write(outputState_);
    }

} // namespace asteria::core