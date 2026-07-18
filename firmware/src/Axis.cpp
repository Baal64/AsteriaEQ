#include <asteria/core/Axis.h>

namespace asteria::core
{

    namespace
    {

        float absoluteValue(float value)
        {
            return value < 0.0F ? -value : value;
        }

        float directionOf(float value)
        {
            if (value > 0.0F)
            {
                return 1.0F;
            }

            if (value < 0.0F)
            {
                return -1.0F;
            }

            return 0.0F;
        }

    } // namespace

    Axis::Axis(hardware::IStepperDriver &driver)
        : driver_(driver)
    {
        status_.enabled = driver_.isEnabled();
    }

    void Axis::enable()
    {
        driver_.enable();
        status_.enabled = driver_.isEnabled();
    }

    void Axis::disable()
    {
        driver_.setVelocityDegPerSec(0.0F);
        driver_.disable();

        state_.velocityDegPerSec = 0.0F;
        status_.enabled = driver_.isEnabled();
    }

    void Axis::setTarget(const AxisTarget &target)
    {
        target_ = target;

        if (target_.type == AxisTargetType::Position && target_.relative)
        {
            target_.positionDeg += state_.positionDeg;
            target_.relative = false;
        }
    }

    void Axis::update(float deltaTimeSec)
    {
        if (!status_.enabled || deltaTimeSec <= 0.0F)
        {
            return;
        }

        float velocityDegPerSec = 0.0F;

        switch (target_.type)
        {
        case AxisTargetType::Velocity:
            velocityDegPerSec = target_.velocityDegPerSec;
            break;

        case AxisTargetType::Position:
            velocityDegPerSec =
                calculateVelocityForPosition(deltaTimeSec);
            break;
        }

        driver_.setVelocityDegPerSec(velocityDegPerSec);
        driver_.update(deltaTimeSec);

        state_.velocityDegPerSec = velocityDegPerSec;
        state_.positionDeg += velocityDegPerSec * deltaTimeSec;
    }

    const AxisState &Axis::state() const
    {
        return state_;
    }

    const AxisStatus &Axis::status() const
    {
        return status_;
    }

    float Axis::calculateVelocityForPosition(float deltaTimeSec) const
    {
        const float errorDeg =
            target_.positionDeg - state_.positionDeg;

        const float absoluteErrorDeg = absoluteValue(errorDeg);

        if (absoluteErrorDeg <= POSITION_TOLERANCE_DEG)
        {
            return 0.0F;
        }

        const float requestedSpeedDegPerSec =
            absoluteValue(target_.velocityDegPerSec);

        if (requestedSpeedDegPerSec <= 0.0F)
        {
            return 0.0F;
        }

        const float maximumTravelThisUpdateDeg =
            requestedSpeedDegPerSec * deltaTimeSec;

        if (absoluteErrorDeg <= maximumTravelThisUpdateDeg)
        {
            return errorDeg / deltaTimeSec;
        }

        return directionOf(errorDeg) * requestedSpeedDegPerSec;
    }

} // namespace asteria::core