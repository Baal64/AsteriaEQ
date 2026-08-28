#include <Arduino.h>

#include <asteria/diagnostics/Diagnostics.h>

#include <asteria/core/AbsoluteAxisPosition.h>
#include <asteria/core/Axis.h>
#include <asteria/core/Joystick.h>

#include <asteria/hardware/StepDirMotorDriver.h>

#include <asteria/platform/as5048a/As5048a.h>

#include <asteria/platform/avr/Atmega32u4DigitalOutput.h>
#include <asteria/platform/avr/Atmega32u4StepPulseGenerator.h>

#include <asteria/platform/mcp23017/Mcp23017DigitalOutput.h>

#include <asteria/core/MountStateMachine.h>
#include <asteria/core/MountState.h>

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
        core::Axis &rightAscensionAxis,
        core::Axis &declinationAxis,
        core::Joystick &joystick,
        platform::mcp23017::Mcp23017DigitalInput &
            st4RightAscensionPlusInput,
        platform::mcp23017::Mcp23017DigitalInput &
            st4RightAscensionMinusInput,
        platform::mcp23017::Mcp23017DigitalInput &
            st4DeclinationPlusInput,
        platform::mcp23017::Mcp23017DigitalInput &
            st4DeclinationMinusInput,
        core::MountStateMachine &mountStateMachine,
        platform::as5048a::As5048a &rightAscensionEncoder,
        platform::as5048a::As5048a &declinationEncoder,
        core::AbsoluteAxisPosition &rightAscensionPosition,
        core::AbsoluteAxisPosition &declinationPosition)
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
          rightAscensionAxis_(rightAscensionAxis),
          declinationAxis_(declinationAxis),
          joystick_(joystick),
          st4RightAscensionPlusInput_(st4RightAscensionPlusInput),
          st4RightAscensionMinusInput_(st4RightAscensionMinusInput),
          st4DeclinationPlusInput_(st4DeclinationPlusInput),
          st4DeclinationMinusInput_(st4DeclinationMinusInput),
          mountStateMachine_(mountStateMachine),
          rightAscensionEncoder_(rightAscensionEncoder),
          declinationEncoder_(declinationEncoder),
          rightAscensionPosition_(rightAscensionPosition),
          declinationPosition_(declinationPosition),
          previousMillis_(0UL)
    {
    }
    namespace
    {
        const __FlashStringHelper *positionHealthText(
            const core::PositionHealth health)
        {
            switch (health)
            {
            case core::PositionHealth::Valid:
                return F("VALID");

            case core::PositionHealth::TemporarilyInvalid:
                return F("TEMP_INVALID");

            case core::PositionHealth::Lost:
                return F("LOST");
            }

            return F("UNKNOWN");
        }

        const __FlashStringHelper *mountStateText(
            const core::MountState state)
        {
            switch (state)
            {
            case core::MountState::Initializing:
                return F("INITIALIZING");

            case core::MountState::WaitingForHome:
                return F("WAITING_FOR_HOME");

            case core::MountState::Homing:
                return F("HOMING");

            case core::MountState::Ready:
                return F("READY");

            case core::MountState::Tracking:
                return F("TRACKING");

            case core::MountState::Parked:
                return F("PARKED");

            case core::MountState::Error:
                return F("ERROR");
            }

            return F("UNKNOWN");
        }
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
        Serial.print(F("MOUNT | state = "));
        Serial.println(
            mountStateText(
                mountStateMachine_.state()));
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
        Serial.print(
            joystick_.pressed()
                ? F("PRESSED")
                : F("RELEASED"));

        Serial.print(F(" | CLICKS = "));
        Serial.print(
            joystick_.clickCount());

        Serial.print(F(" | LONGS = "));
        Serial.println(
            joystick_.longPressCount());

        // -------------------------------------------------------------------------
        // ST-4
        // -------------------------------------------------------------------------

        Serial.print(F("ST4 | RA+ = "));
        Serial.print(
            st4RightAscensionPlusInput_.read()
                ? F("HIGH")
                : F("LOW"));

        Serial.print(F(" | RA- = "));
        Serial.print(
            st4RightAscensionMinusInput_.read()
                ? F("HIGH")
                : F("LOW"));

        Serial.print(F(" | DEC+ = "));
        Serial.print(
            st4DeclinationPlusInput_.read()
                ? F("HIGH")
                : F("LOW"));

        Serial.print(F(" | DEC- = "));
        Serial.println(
            st4DeclinationMinusInput_.read()
                ? F("HIGH")
                : F("LOW"));

        // -------------------------------------------------------------------------
        // Encoders
        // -------------------------------------------------------------------------

        const uint16_t rightAscensionRawAngle =
            rightAscensionEncoder_.lastRawAngle();

        const float rightAscensionEncoderAngleDeg =
            platform::as5048a::As5048a::rawToDegrees(
                rightAscensionRawAngle);

        const float rightAscensionMechanicalPositionDeg =
            rightAscensionPosition_.fromEncoderAngleDeg(
                rightAscensionEncoderAngleDeg);

        Serial.print(F("ENC RA  | raw = "));
        Serial.print(rightAscensionRawAngle);

        Serial.print(F(" | angle = "));
        Serial.print(
            rightAscensionEncoderAngleDeg,
            3);

        Serial.print(F(" deg | status = "));

        Serial.println(
            rightAscensionEncoder_.hasError()
                ? F("ERROR")
                : F("OK"));

        Serial.print(F("POS RA  | mechanical = "));
        Serial.print(
            rightAscensionMechanicalPositionDeg,
            3);

        Serial.println(F(" deg"));

        const uint16_t declinationRawAngle =
            declinationEncoder_.lastRawAngle();

        const float declinationEncoderAngleDeg =
            platform::as5048a::As5048a::rawToDegrees(
                declinationRawAngle);

        const float declinationMechanicalPositionDeg =
            declinationPosition_.fromEncoderAngleDeg(
                declinationEncoderAngleDeg);

        Serial.print(F("ENC DEC | raw = "));
        Serial.print(declinationRawAngle);

        Serial.print(F(" | angle = "));
        Serial.print(
            declinationEncoderAngleDeg,
            3);

        Serial.print(F(" deg | status = "));

        Serial.println(
            declinationEncoder_.hasError()
                ? F("ERROR")
                : F("OK"));

        Serial.print(F("POS DEC | mechanical = "));
        Serial.print(
            declinationMechanicalPositionDeg,
            3);

        Serial.println(F(" deg"));

        // -------------------------------------------------------------------------
        // Axis state
        // -------------------------------------------------------------------------

        Serial.print(F("STATE RA  | position = "));
        Serial.print(
            rightAscensionAxis_.state().positionDeg,
            3);

        Serial.print(F(" deg | health = "));
        Serial.print(
            positionHealthText(
                rightAscensionAxis_.state().positionHealth));

        Serial.print(F(" | velocity = "));
        Serial.print(
            rightAscensionAxis_.state().velocityDegPerSec,
            6);

        Serial.println(F(" deg/s"));

        Serial.print(F("STATE DEC | position = "));
        Serial.print(
            declinationAxis_.state().positionDeg,
            3);

        Serial.print(F(" deg | health = "));
        Serial.print(
            positionHealthText(
                declinationAxis_.state().positionHealth));

        Serial.print(F(" | velocity = "));
        Serial.print(
            declinationAxis_.state().velocityDegPerSec,
            6);

        Serial.println(F(" deg/s"));

        Serial.print(F("ERR RA   | parity = "));
        Serial.print(
            rightAscensionEncoder_.hasParityError()
                ? F("ERROR")
                : F("OK"));

        Serial.print(F(" | sensor = "));
        Serial.print(
            rightAscensionEncoder_.hasSensorError()
                ? F("ERROR")
                : F("OK"));

        Serial.print(F(" | limits = "));
        Serial.println(
            rightAscensionAxis_.state().withinLimits
                ? F("OK")
                : F("OUT"));

        Serial.print(F("ERR DEC  | parity = "));
        Serial.print(
            declinationEncoder_.hasParityError()
                ? F("ERROR")
                : F("OK"));

        Serial.print(F(" | sensor = "));
        Serial.print(
            declinationEncoder_.hasSensorError()
                ? F("ERROR")
                : F("OK"));

        Serial.print(F(" | limits = "));
        Serial.println(
            declinationAxis_.state().withinLimits
                ? F("OK")
                : F("OUT"));

        Serial.print(F("HEALTH RA  | invalid = "));
        Serial.print(
            rightAscensionAxis_.positionInvalidDurationSec(),
            3);

        Serial.print(F(" s | uncertainty = "));
        Serial.print(
            rightAscensionAxis_.positionUncertaintyDeg(),
            3);

        Serial.println(F(" deg"));

        Serial.print(F("HEALTH DEC | invalid = "));
        Serial.print(
            declinationAxis_.positionInvalidDurationSec(),
            3);

        Serial.print(F(" s | uncertainty = "));
        Serial.print(
            declinationAxis_.positionUncertaintyDeg(),
            3);

        Serial.println(F(" deg"));

        Serial.println();
    }

} // namespace asteria::diagnostics