#include <Arduino.h>

#include <asteria/diagnostics/Diagnostics.h>

#include <asteria/core/Joystick.h>

#include <asteria/hardware/StepDirMotorDriver.h>

#include <asteria/platform/as5048a/As5048a.h>

#include <asteria/platform/avr/Atmega32u4DigitalOutput.h>
#include <asteria/platform/avr/Atmega32u4StepPulseGenerator.h>

#include <asteria/platform/mcp23017/Mcp23017DigitalOutput.h>

namespace asteria::diagnostics
{

    Diagnostics::Diagnostics(
        hardware::StepDirMotorDriver &rightAscensionDriver,
        hardware::StepDirMotorDriver &declinationDriver,
        platform::mcp23017::Mcp23017DigitalOutput &
            rightAscensionEnableOutput,
        platform::mcp23017::Mcp23017DigitalOutput &
            declinationEnableOutput,
        platform::avr::Atmega32u4DigitalOutput &
            rightAscensionDirectionOutput,
        platform::avr::Atmega32u4DigitalOutput &
            declinationDirectionOutput,
        platform::avr::Atmega32u4StepPulseGenerator &
            rightAscensionPulseGenerator,
        platform::avr::Atmega32u4StepPulseGenerator &
            declinationPulseGenerator,
        core::Joystick &joystick,
        platform::as5048a::As5048a &declinationEncoder)
        : rightAscensionDriver_(rightAscensionDriver),
          declinationDriver_(declinationDriver),
          rightAscensionEnableOutput_(
              rightAscensionEnableOutput),
          declinationEnableOutput_(
              declinationEnableOutput),
          rightAscensionDirectionOutput_(
              rightAscensionDirectionOutput),
          declinationDirectionOutput_(
              declinationDirectionOutput),
          rightAscensionPulseGenerator_(
              rightAscensionPulseGenerator),
          declinationPulseGenerator_(
              declinationPulseGenerator),
          joystick_(joystick),
          declinationEncoder_(declinationEncoder),
          previousMillis_(0UL)
    {
    }

    void Diagnostics::update(
        const unsigned long currentMillis)
    {
        if (currentMillis - previousMillis_ <
            PERIOD_MS)
        {
            return;
        }

        previousMillis_ = currentMillis;

        print();
    }

    void Diagnostics::print()
    {
        // -------------------------------------------------------------------------
        // Right ascension
        // -------------------------------------------------------------------------

        Serial.print(F("RA | velocity = "));
        Serial.print(
            rightAscensionDriver_.velocityDegPerSec(),
            6);

        Serial.print(F(" deg/s | enabled = "));
        Serial.print(
            rightAscensionDriver_.isEnabled()
                ? F("true")
                : F("false"));

        Serial.print(F(" | EN pin = "));
        Serial.print(
            rightAscensionEnableOutput_.state()
                ? F("HIGH")
                : F("LOW"));

        Serial.print(F(" | DIR pin = "));
        Serial.print(
            rightAscensionDirectionOutput_.state()
                ? F("HIGH")
                : F("LOW"));

        Serial.print(F(" | STEP = "));
        Serial.print(
            rightAscensionPulseGenerator_.frequencyHz(),
            3);

        Serial.print(F(" Hz | running = "));
        Serial.println(
            rightAscensionPulseGenerator_.isRunning()
                ? F("true")
                : F("false"));

        // -------------------------------------------------------------------------
        // Declination
        // -------------------------------------------------------------------------

        Serial.print(F("DEC | velocity = "));
        Serial.print(
            declinationDriver_.velocityDegPerSec(),
            6);

        Serial.print(F(" deg/s | enabled = "));
        Serial.print(
            declinationDriver_.isEnabled()
                ? F("true")
                : F("false"));

        Serial.print(F(" | EN pin = "));
        Serial.print(
            declinationEnableOutput_.state()
                ? F("HIGH")
                : F("LOW"));

        Serial.print(F(" | DIR pin = "));
        Serial.print(
            declinationDirectionOutput_.state()
                ? F("HIGH")
                : F("LOW"));

        Serial.print(F(" | STEP = "));
        Serial.print(
            declinationPulseGenerator_.frequencyHz(),
            3);

        Serial.print(F(" Hz | running = "));
        Serial.println(
            declinationPulseGenerator_.isRunning()
                ? F("true")
                : F("false"));

        // -------------------------------------------------------------------------
        // Joystick
        // -------------------------------------------------------------------------

        Serial.print(F("JOY | X = "));
        Serial.print(
            joystick_.x(),
            3);

        Serial.print(F(" | Y = "));
        Serial.print(
            joystick_.y(),
            3);

        Serial.print(F(" | SW = "));
        Serial.println(
            joystick_.pressed()
                ? F("PRESSED")
                : F("RELEASED"));

        // -------------------------------------------------------------------------
        // Encoders
        // -------------------------------------------------------------------------

        const uint16_t declinationRawAngle =
            declinationEncoder_.readRawAngle();

        Serial.print(F("ENC DEC | raw = "));
        Serial.print(declinationRawAngle);

        Serial.print(F(" | angle = "));
        Serial.print(
            platform::as5048a::As5048a::rawToDegrees(
                declinationRawAngle),
            3);

        Serial.print(F(" deg | status = "));

        Serial.println(
            declinationEncoder_.hasError()
                ? F("ERROR")
                : F("OK"));
    }

} // namespace asteria::diagnostics