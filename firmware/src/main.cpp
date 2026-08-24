#include <Arduino.h>

#include <asteria/config/AsteriaConfig.h>
#include <asteria/config/JoystickConfiguration.h>
#include <asteria/config/JoystickMotionConfiguration.h>
#include <asteria/config/Mcp23017Configuration.h>
#include <asteria/config/PinConfiguration.h>

#include <asteria/core/Axis.h>
#include <asteria/core/AxisController.h>
#include <asteria/core/IMotionSource.h>
#include <asteria/core/Joystick.h>
#include <asteria/core/Mount.h>
#include <asteria/core/sources/JoystickMotionSource.h>
#include <asteria/core/sources/NullMotionSource.h>
#include <asteria/core/sources/TrackingMotionSource.h>

#include <asteria/hardware/StepDirMotorDriver.h>

#include <asteria/platform/avr/Atmega32u4AnalogInput.h>
#include <asteria/platform/avr/Atmega32u4DigitalOutput.h>
#include <asteria/platform/avr/Atmega32u4StepPulseGenerator.h>

#include <asteria/platform/mcp23017/Mcp23017.h>
#include <asteria/platform/mcp23017/Mcp23017DigitalInput.h>
#include <asteria/platform/mcp23017/Mcp23017DigitalOutput.h>

#include <asteria/platform/as5048a/As5048a.h>

#include <asteria/config/AxisPositionConfiguration.h>
#include <asteria/core/AbsoluteAxisPosition.h>

#include <asteria/diagnostics/Diagnostics.h>

namespace
{
    // -----------------------------------------------------------------------------
    // AS5048A
    // -----------------------------------------------------------------------------

    asteria::platform::as5048a::As5048a
        rightAscensionEncoder(
            asteria::config::pins::
                RIGHT_ASCENSION_ENCODER_CS);

    asteria::platform::as5048a::As5048a
        declinationEncoder(
            asteria::config::pins::
                DECLINATION_ENCODER_CS);

    asteria::core::AbsoluteAxisPosition
        rightAscensionPosition(
            rightAscensionEncoder,
            asteria::config::axisPosition::
                RIGHT_ASCENSION_ZERO_OFFSET_DEG,
            asteria::config::axisPosition::
                RIGHT_ASCENSION_INVERT);

    asteria::core::AbsoluteAxisPosition
        declinationPosition(
            declinationEncoder,
            asteria::config::axisPosition::
                DECLINATION_ZERO_OFFSET_DEG,
            asteria::config::axisPosition::
                DECLINATION_INVERT);

    // -----------------------------------------------------------------------------
    // MCP23017 I/O expander
    // -----------------------------------------------------------------------------

    asteria::platform::mcp23017::Mcp23017
        ioExpander(
            asteria::config::mcp23017::I2C_ADDRESS);

    asteria::platform::mcp23017::Mcp23017DigitalOutput
        rightAscensionEnableHardwareOutput(
            ioExpander,
            asteria::platform::mcp23017::Mcp23017Port::PortA,
            asteria::config::mcp23017::
                RIGHT_ASCENSION_ENABLE_PIN);

    asteria::platform::mcp23017::Mcp23017DigitalOutput
        declinationEnableHardwareOutput(
            ioExpander,
            asteria::platform::mcp23017::Mcp23017Port::PortA,
            asteria::config::mcp23017::
                DECLINATION_ENABLE_PIN);

    asteria::platform::mcp23017::Mcp23017DigitalOutput
        statusLedOutput(
            ioExpander,
            asteria::platform::mcp23017::Mcp23017Port::PortA,
            asteria::config::mcp23017::STATUS_LED_PIN);

    asteria::platform::mcp23017::Mcp23017DigitalInput
        joystickSwitchInput(
            ioExpander,
            asteria::platform::mcp23017::Mcp23017Port::PortA,
            asteria::config::mcp23017::JOYSTICK_SWITCH_PIN);

    // -----------------------------------------------------------------------------
    // Right ascension hardware
    // -----------------------------------------------------------------------------

    asteria::platform::avr::Atmega32u4DigitalOutput
        rightAscensionDirectionOutput(
            asteria::config::pins::RIGHT_ASCENSION_DIR);

    asteria::platform::avr::Atmega32u4StepPulseGenerator
        rightAscensionPulseGenerator(
            asteria::platform::avr::StepTimer::Timer1);

    asteria::hardware::StepDirMotorDriver
        rightAscensionDriver(
            asteria::config::mechanics::RIGHT_ASCENSION_STEPPER,
            rightAscensionDirectionOutput,
            rightAscensionEnableHardwareOutput,
            rightAscensionPulseGenerator);

    // -----------------------------------------------------------------------------
    // Declination hardware
    // -----------------------------------------------------------------------------

    asteria::platform::avr::Atmega32u4DigitalOutput
        declinationDirectionOutput(
            asteria::config::pins::DECLINATION_DIR);

    asteria::platform::avr::Atmega32u4StepPulseGenerator
        declinationPulseGenerator(
            asteria::platform::avr::StepTimer::Timer3);

    asteria::hardware::StepDirMotorDriver
        declinationDriver(
            asteria::config::mechanics::DECLINATION_STEPPER,
            declinationDirectionOutput,
            declinationEnableHardwareOutput,
            declinationPulseGenerator);

    // -----------------------------------------------------------------------------
    // Axes
    // -----------------------------------------------------------------------------

    asteria::core::Axis
        rightAscensionAxis(
            rightAscensionDriver);

    asteria::core::Axis
        declinationAxis(
            declinationDriver);

    // -----------------------------------------------------------------------------
    // Joystick hardware
    // -----------------------------------------------------------------------------

    asteria::platform::avr::Atmega32u4AnalogInput
        joystickXInput(
            asteria::config::pins::JOYSTICK_X);

    asteria::platform::avr::Atmega32u4AnalogInput
        joystickYInput(
            asteria::config::pins::JOYSTICK_Y);

    // -----------------------------------------------------------------------------
    // Joystick
    // -----------------------------------------------------------------------------

    asteria::core::Joystick
        joystick(
            joystickXInput,
            joystickYInput,
            joystickSwitchInput,
            asteria::config::joystick::X_CENTER,
            asteria::config::joystick::Y_CENTER,
            asteria::config::joystick::DEAD_ZONE);

    // -----------------------------------------------------------------------------
    // Motion sources
    // -----------------------------------------------------------------------------

    asteria::core::TrackingMotionSource
        trackingSource(
            asteria::config::motion::
                SIDEREAL_RATE_DEG_PER_SEC);

    asteria::core::NullMotionSource
        declinationIdleSource;

    asteria::core::JoystickMotionSource
        rightAscensionJoystickSource(
            joystick,
            true,
            asteria::config::joystickMotion::
                MAX_RA_VELOCITY_DEG_PER_SEC,
            asteria::config::joystickMotion::
                INVERT_RA);

    asteria::core::JoystickMotionSource
        declinationJoystickSource(
            joystick,
            false,
            asteria::config::joystickMotion::
                MAX_DEC_VELOCITY_DEG_PER_SEC,
            asteria::config::joystickMotion::
                INVERT_DEC);

    asteria::core::IMotionSource *
        rightAscensionSources[]{
            &trackingSource,
            &rightAscensionJoystickSource};

    asteria::core::IMotionSource *
        declinationSources[]{
            &declinationIdleSource,
            &declinationJoystickSource};

    // -----------------------------------------------------------------------------
    // Controllers
    // -----------------------------------------------------------------------------

    asteria::core::AxisController
        rightAscensionController(
            rightAscensionAxis,
            rightAscensionSources,
            2U);

    asteria::core::AxisController
        declinationController(
            declinationAxis,
            declinationSources,
            2U);

    asteria::core::Mount
        mount(
            rightAscensionController,
            declinationController);

    // -----------------------------------------------------------------------------
    // Runtime
    // -----------------------------------------------------------------------------

    unsigned long previousUpdateMicros = 0UL;

    // -----------------------------------------------------------------------------
    // Diagnostics
    // -----------------------------------------------------------------------------

    asteria::diagnostics::Diagnostics
        diagnostics(
            rightAscensionDriver,
            declinationDriver,
            rightAscensionEnableHardwareOutput,
            declinationEnableHardwareOutput,
            rightAscensionDirectionOutput,
            declinationDirectionOutput,
            rightAscensionPulseGenerator,
            declinationPulseGenerator,
            joystick,
            rightAscensionEncoder,
            declinationEncoder,
            rightAscensionPosition,
            declinationPosition);

} // namespace

void setup()
{
    Serial.begin(
        asteria::config::system::SERIAL_BAUD_RATE);

    // -------------------------------------------------------------------------
    // MCP23017
    // -------------------------------------------------------------------------

    ioExpander.begin();

    // ENABLE is active-low.
    // HIGH keeps the TMC2209 drivers disabled during initialization.
    rightAscensionEnableHardwareOutput.begin(true);
    declinationEnableHardwareOutput.begin(true);

    // Status LED starts OFF.
    statusLedOutput.begin(false);

    // Joystick switch uses the MCP23017 internal pull-up.
    // Released = HIGH
    // Pressed  = LOW
    joystickSwitchInput.begin(true);

    // -------------------------------------------------------------------------
    // Joystick analog inputs
    // -------------------------------------------------------------------------

    joystickXInput.begin();
    joystickYInput.begin();

    // -------------------------------------------------------------------------
    // Motor control hardware
    // -------------------------------------------------------------------------

    rightAscensionDirectionOutput.begin(false);
    declinationDirectionOutput.begin(false);

    rightAscensionPulseGenerator.begin();
    declinationPulseGenerator.begin();

    // -------------------------------------------------------------------------
    // Mount
    // -------------------------------------------------------------------------

    rightAscensionAxis.enable();
    declinationAxis.enable();

    mount.enable();

    rightAscensionEncoder.begin();
    declinationEncoder.begin();

    // Initialization complete.
    statusLedOutput.write(true);

    previousUpdateMicros = micros();
}

void loop()
{
    const unsigned long currentMicros =
        micros();

    const unsigned long elapsedMicros =
        currentMicros - previousUpdateMicros;

    previousUpdateMicros =
        currentMicros;

    const float deltaTimeSec =
        static_cast<float>(elapsedMicros) /
        1000000.0F;

    mount.update(deltaTimeSec);

    diagnostics.update(millis());
}