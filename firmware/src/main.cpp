#include <Arduino.h>

#include <asteria/core/Axis.h>
#include <asteria/core/AxisController.h>
#include <asteria/core/IMotionSource.h>
#include <asteria/core/Mount.h>
#include <asteria/core/sources/NullMotionSource.h>
#include <asteria/core/sources/TrackingMotionSource.h>
#include <asteria/hardware/simulation/FakeStepperDriver.h>

namespace
{

    constexpr unsigned long SERIAL_BAUD_RATE = 115200UL;

    constexpr float SIDEREAL_RATE_DEG_PER_SEC =
        360.0F / 86164.0905F;

    asteria::hardware::FakeStepperDriver rightAscensionDriver;
    asteria::hardware::FakeStepperDriver declinationDriver;

    asteria::core::Axis rightAscensionAxis(
        rightAscensionDriver);

    asteria::core::Axis declinationAxis(
        declinationDriver);

    asteria::core::TrackingMotionSource trackingSource(
        SIDEREAL_RATE_DEG_PER_SEC);

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
    Serial.begin(SERIAL_BAUD_RATE);

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
        Serial.print(rightAscensionDriver.velocityDegPerSec(), 6);
        Serial.print(F(" deg/s"));

        Serial.print(F(" | DEC = "));
        Serial.print(declinationDriver.velocityDegPerSec(), 6);
        Serial.println(F(" deg/s"));
    }
}