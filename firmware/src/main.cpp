#include <Arduino.h>

#include <asteria/hardware/IAbsoluteEncoder.h>
#include <asteria/hardware/IStepperDriver.h>

namespace
{

    constexpr unsigned long SerialBaudRate = 115200UL;

} // namespace

void setup()
{
    Serial.begin(SerialBaudRate);
}

void loop()
{
}
