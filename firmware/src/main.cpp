#include <Arduino.h>

#include <asteria/config/AsteriaConfig.h>

#include <asteria/core/Axis.h>
#include <asteria/core/AxisController.h>
#include <asteria/core/IMotionSource.h>
#include <asteria/core/Mount.h>
#include <asteria/core/sources/NullMotionSource.h>
#include <asteria/core/sources/TrackingMotionSource.h>

#include <asteria/hardware/StepDirMotorDriver.h>

#include <asteria/simulation/SimulatedDigitalOutput.h>
#include <asteria/simulation/SimulatedStepPulseGenerator.h>
#include <asteria/platform/avr/Atmega32u4StepPulseGenerator.h>

namespace
{

    asteria::simulation::SimulatedDigitalOutput
        rightAscensionDirectionOutput;

    asteria::simulation::SimulatedDigitalOutput
        rightAscensionEnableOutput;

    asteria::platform::avr::Atmega32u4StepPulseGenerator
        rightAscensionPulseGenerator(
            asteria::platform::avr::StepTimer::Timer1);

    asteria::hardware::StepDirMotorDriver
        rightAscensionDriver(
            asteria::config::mechanics::RIGHT_ASCENSION_STEPPER,
            rightAscensionDirectionOutput,
            rightAscensionEnableOutput,
            rightAscensionPulseGenerator);

    asteria::simulation::SimulatedDigitalOutput
        declinationDirectionOutput;

    asteria::simulation::SimulatedDigitalOutput
        declinationEnableOutput;

    asteria::platform::avr::Atmega32u4StepPulseGenerator
        declinationPulseGenerator(
            asteria::platform::avr::StepTimer::Timer3);

    asteria::hardware::StepDirMotorDriver
        declinationDriver(
            asteria::config::mechanics::DECLINATION_STEPPER,
            declinationDirectionOutput,
            declinationEnableOutput,
            declinationPulseGenerator);

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

    // Initialise le générateur STEP matériel RA.
    rightAscensionPulseGenerator.begin();
    // Initialise le générateur STEP matériel DEC.
    declinationPulseGenerator.begin();

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

        Serial.print(F("RA | velocity = "));
        Serial.print(
            rightAscensionDriver.velocityDegPerSec(),
            6);

        Serial.print(F(" deg/s | enabled = "));
        Serial.print(
            rightAscensionDriver.isEnabled()
                ? F("true")
                : F("false"));

        Serial.print(F(" | EN pin = "));
        Serial.print(
            rightAscensionEnableOutput.state()
                ? F("HIGH")
                : F("LOW"));

        Serial.print(F(" | DIR pin = "));
        Serial.print(
            rightAscensionDirectionOutput.state()
                ? F("HIGH")
                : F("LOW"));

        Serial.print(F(" | STEP = "));
        Serial.print(
            rightAscensionPulseGenerator.frequencyHz(),
            3);

        Serial.print(F(" Hz | running = "));
        Serial.println(
            rightAscensionPulseGenerator.isRunning()
                ? F("true")
                : F("false"));

        Serial.print(F("DEC | velocity = "));
        Serial.print(
            declinationDriver.velocityDegPerSec(),
            6);

        Serial.print(F(" deg/s | enabled = "));
        Serial.print(
            declinationDriver.isEnabled()
                ? F("true")
                : F("false"));

        Serial.print(F(" | EN pin = "));
        Serial.print(
            declinationEnableOutput.state()
                ? F("HIGH")
                : F("LOW"));

        Serial.print(F(" | DIR pin = "));
        Serial.print(
            declinationDirectionOutput.state()
                ? F("HIGH")
                : F("LOW"));

        Serial.print(F(" | STEP = "));
        Serial.print(
            declinationPulseGenerator.frequencyHz(),
            3);

        Serial.print(F(" Hz | running = "));
        Serial.println(
            declinationPulseGenerator.isRunning()
                ? F("true")
                : F("false"));

        Serial.println();
    }
}