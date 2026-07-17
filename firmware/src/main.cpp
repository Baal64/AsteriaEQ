#include <Arduino.h>

#include <asteria/hardware/IAbsoluteEncoder.h>
#include <asteria/hardware/IStepperDriver.h>

#include <asteria/core/MotionCommand.h>
#include <asteria/core/AxisTarget.h>
#include <asteria/hardware/IStepperDriver.h>
#include <asteria/core/Axis.h>

namespace
{

    constexpr unsigned long SerialBaudRate = 115200UL;

} // namespace

void setup()
{
    Serial.begin(SerialBaudRate);

    const asteria::core::MotionCommand command{
        asteria::core::AxisId::Ra,
        asteria::core::MotionType::Velocity,
        asteria::core::MotionSource::Tracking,
        asteria::core::MotionPriority::Low,
        0.0F,
        0.004178F,
        0U,
        false};

    (void)command;

    const asteria::core::AxisTarget target{
        asteria::core::AxisTargetType::Velocity,
        0.0F,
        0.004178F,
        false};

    (void)target;
}

void loop()
{
}
