#include <Arduino.h>

#include <asteria/core/MotionCommand.h>
#include <asteria/core/MotionProposal.h>

namespace
{

    constexpr unsigned long SERIAL_BAUD_RATE = 115200UL;

} // namespace

void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);

    using asteria::core::MotionCommand;
    using asteria::core::MotionPriority;
    using asteria::core::MotionProposal;

    const MotionCommand tracking =
        MotionCommand::baseVelocity(0.004178F);

    const MotionCommand guiding =
        MotionCommand::correctionVelocity(0.0001F);

    const MotionCommand joystick =
        MotionCommand::overrideVelocity(
            2.0F,
            MotionPriority::High);

    const MotionCommand gotoTarget =
        MotionCommand::overridePosition(
            42.0F,
            false,
            MotionPriority::High);

    const MotionProposal trackingProposal =
        MotionProposal::with(tracking);

    const MotionProposal noProposal =
        MotionProposal::none();

    (void)guiding;
    (void)joystick;
    (void)gotoTarget;
    (void)trackingProposal;
    (void)noProposal;
}

void loop()
{
}