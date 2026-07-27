#include <asteria/simulation/SimulatedStepperDriver.h>

namespace asteria::hardware
{

    SimulatedStepperDriver::SimulatedStepperDriver()
        : enabled_(false),
          velocityDegPerSec_(0.0F)
    {
    }

    void SimulatedStepperDriver::enable()
    {
        enabled_ = true;
    }

    void SimulatedStepperDriver::disable()
    {
        enabled_ = false;
        velocityDegPerSec_ = 0.0F;
    }

    bool SimulatedStepperDriver::isEnabled() const
    {
        return enabled_;
    }

    void SimulatedStepperDriver::setVelocityDegPerSec(
        float velocityDegPerSec)
    {
        velocityDegPerSec_ = velocityDegPerSec;
    }

    void SimulatedStepperDriver::update(float deltaTimeSec)
    {
        (void)deltaTimeSec;
    }

    float SimulatedStepperDriver::velocityDegPerSec() const
    {
        return velocityDegPerSec_;
    }

} // namespace asteria::hardware