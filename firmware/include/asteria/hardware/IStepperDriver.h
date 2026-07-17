#pragma once

namespace asteria::hardware
{

    class IStepperDriver
    {
    public:
        virtual ~IStepperDriver() = default;

        virtual void enable() = 0;

        virtual void disable() = 0;

        virtual bool isEnabled() const = 0;

        virtual void setVelocityDegPerSec(float velocityDegPerSec) = 0;

        virtual void update() = 0;
    };

} // namespace asteria::hardware