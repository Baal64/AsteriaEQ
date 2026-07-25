#include <Arduino.h>

#include <asteria/config/AsteriaConfig.h>

#include <asteria/core/Axis.h>
#include <asteria/core/AxisController.h>
#include <asteria/core/IMotionSource.h>
#include <asteria/core/Mount.h>
#include <asteria/core/sources/NullMotionSource.h>
#include <asteria/core/sources/TrackingMotionSource.h>

#include <asteria/hardware/simulation/FakeStepperDriver.h>
#include <asteria/hardware/StepperKinematics.h>

namespace
{

    asteria::hardware::FakeStepperDriver rightAscensionDriver;
    asteria::hardware::FakeStepperDriver declinationDriver;

    asteria::hardware::StepperKinematics rightAscensionKinematics(
        asteria::config::mechanics::RIGHT_ASCENSION_STEPPER);

    asteria::core::Axis rightAscensionAxis(
        rightAscensionDriver);

    asteria::core::Axis declinationAxis(
        declinationDriver);

    asteria::core::TrackingMotionSource trackingSource(
        asteria::config::motion::SIDEREAL_RATE_DEG_PER_SEC);

    asteria::core::NullMotionSource declinationIdleSource;

    asteria::core::IMotionSource *rightAscensionSources[]{
        &trackingSource};

    asteria::core::IMotionSource *declinationSources[]{
        &declinationIdleSource};

    asteria::core::AxisController rightAscensionController(
        rightAscensionAxis,
        rightAscensionSources,
        1U);

    asteria::core::AxisController declinationController(
        declinationAxis,
        declinationSources,
        1U);

    asteria::core::Mount mount(
        rightAscensionController,
        declinationController);

    unsigned long previousUpdateMicros = 0UL;

    constexpr unsigned long SERIAL_PERIOD_MS = 1000UL;

    unsigned long previousSerialMillis = 0UL;

} // namespace

void setup()
{
    Serial.begin(
        asteria::config::system::SERIAL_BAUD_RATE);

    rightAscensionAxis.enable();
    declinationAxis.enable();

    mount.enable();

    previousUpdateMicros = micros();
}

void loop()
{
    const unsigned long currentMicros = micros();

    const unsigned long elapsedMicros =
        currentMicros - previousUpdateMicros;

    previousUpdateMicros = currentMicros;

    const float deltaTimeSec =
        static_cast<float>(elapsedMicros) / 1000000.0F;

    mount.update(deltaTimeSec);

    const unsigned long currentMillis = millis();

    if (currentMillis - previousSerialMillis >= SERIAL_PERIOD_MS)
    {
        previousSerialMillis = currentMillis;

        Serial.print(F("RA = "));
        Serial.print(
            rightAscensionDriver.velocityDegPerSec(),
            6);
        Serial.print(F(" deg/s"));

        const float rightAscensionStepFrequency =
            rightAscensionKinematics
                .stepFrequencyFromAxisVelocity(
                    rightAscensionDriver
                        .velocityDegPerSec());

        Serial.print(F(" | STEP = "));
        Serial.print(rightAscensionStepFrequency, 3);
        Serial.println(F(" Hz"));
    }
}