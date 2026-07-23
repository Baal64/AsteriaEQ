#include <asteria/hardware/simulation/FakeStepperDriver.h>

namespace asteria::hardware
{

    FakeStepperDriver::FakeStepperDriver()
        : enabled_(false),
          velocityDegPerSec_(0.0F)
    {
    }

    void FakeStepperDriver::enable()
    {
        enabled_ = true;
    }

    void FakeStepperDriver::disable()
    {
        enabled_ = false;
        velocityDegPerSec_ = 0.0F;
    }

    bool FakeStepperDriver::isEnabled() const
    {
        return enabled_;
    }

    void FakeStepperDriver::setVelocityDegPerSec(
        float velocityDegPerSec)
    {
        velocityDegPerSec_ = velocityDegPerSec;
    }

    void FakeStepperDriver::update(float deltaTimeSec)
    {
        (void)deltaTimeSec;
    }

    float FakeStepperDriver::velocityDegPerSec() const
    {
        return velocityDegPerSec_;
    }

} // namespace asteria::hardware