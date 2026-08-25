#pragma once

namespace asteria::hardware
{
    class StepDirMotorDriver;
}

namespace asteria::core
{
    class Axis;
    class Joystick;
    class AbsoluteAxisPosition;
}

namespace asteria::platform::avr
{
    class Atmega32u4DigitalOutput;
    class Atmega32u4StepPulseGenerator;
}

namespace asteria::platform::mcp23017
{
    class Mcp23017DigitalOutput;
}

namespace asteria::platform::as5048a
{
    class As5048a;
}

namespace asteria::diagnostics
{

    class Diagnostics
    {
    public:
        Diagnostics(
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
            platform::as5048a::As5048a &rightAscensionEncoder,
            platform::as5048a::As5048a &declinationEncoder,
            core::AbsoluteAxisPosition &rightAscensionPosition,
            core::AbsoluteAxisPosition &declinationPosition);

        void update(unsigned long currentMillis);

    private:
        void print();

        hardware::StepDirMotorDriver &
            rightAscensionDriver_;

        hardware::StepDirMotorDriver &
            declinationDriver_;

        platform::mcp23017::Mcp23017DigitalOutput &
            rightAscensionEnableOutput_;

        platform::mcp23017::Mcp23017DigitalOutput &
            declinationEnableOutput_;

        platform::avr::Atmega32u4DigitalOutput &
            rightAscensionDirectionOutput_;

        platform::avr::Atmega32u4DigitalOutput &
            declinationDirectionOutput_;

        platform::avr::Atmega32u4StepPulseGenerator &
            rightAscensionPulseGenerator_;

        platform::avr::Atmega32u4StepPulseGenerator &
            declinationPulseGenerator_;

        core::Axis &
            rightAscensionAxis_;

        core::Axis &
            declinationAxis_;

        core::Joystick &joystick_;

        platform::as5048a::As5048a &
            rightAscensionEncoder_;

        platform::as5048a::As5048a &
            declinationEncoder_;

        core::AbsoluteAxisPosition &
            rightAscensionPosition_;

        core::AbsoluteAxisPosition &
            declinationPosition_;

        unsigned long previousMillis_;

        static constexpr unsigned long PERIOD_MS =
            1000UL;
    };

} // namespace asteria::diagnostics