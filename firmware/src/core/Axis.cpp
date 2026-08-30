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

    Axis::Axis(
        hardware::IStepperDriver &driver,
        IPositionSensor &positionSensor,
        const float minimumPositionDeg,
        const float maximumPositionDeg,
        const float maximumPositionUncertaintyDeg,
        const float maximumPositionInvalidSec)
        : driver_(driver),
          positionSensor_(positionSensor),
          minimumPositionDeg_(minimumPositionDeg),
          maximumPositionDeg_(maximumPositionDeg),
          maximumPositionUncertaintyDeg_(
              maximumPositionUncertaintyDeg),
          maximumPositionInvalidSec_(
              maximumPositionInvalidSec)
    {
        {
            status_.enabled = driver_.isEnabled();
        }
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
        if (deltaTimeSec <= 0.0F)
        {
            return;
        }
        state_.positionDeg =
            positionSensor_.positionDeg();

        const bool positionValid =
            positionSensor_.isValid();

        float velocityDegPerSec = 0.0F;

        switch (target_.type)
        {
        case AxisTargetType::Idle:
            break;

        case AxisTargetType::Stop:
            break;

        case AxisTargetType::Velocity:
            velocityDegPerSec = target_.velocityDegPerSec;
            break;

        case AxisTargetType::Position:
            velocityDegPerSec =
                calculateVelocityForPosition(deltaTimeSec);
            break;
        }

        if (state_.positionHealth == PositionHealth::Lost)
        {
            velocityDegPerSec = 0.0F;
        }

        if (!isVelocityAllowed(velocityDegPerSec))
        {
            velocityDegPerSec = 0.0F;
        }

        if (!status_.enabled)
        {
            velocityDegPerSec = 0.0F;
        }

        driver_.setVelocityDegPerSec(velocityDegPerSec);
        driver_.update(deltaTimeSec);

        state_.velocityDegPerSec =
            velocityDegPerSec;

        if (state_.positionHealth != PositionHealth::Lost)
        {
            if (positionValid)
            {
                state_.positionHealth =
                    PositionHealth::Valid;

                positionInvalidDurationSec_ = 0.0F;
                positionUncertaintyDeg_ = 0.0F;
            }
            else
            {
                state_.positionHealth =
                    PositionHealth::TemporarilyInvalid;

                positionInvalidDurationSec_ +=
                    deltaTimeSec;

                positionUncertaintyDeg_ +=
                    absoluteValue(velocityDegPerSec) *
                    deltaTimeSec;

                if (
                    positionUncertaintyDeg_ >
                        maximumPositionUncertaintyDeg_ ||
                    positionInvalidDurationSec_ >
                        maximumPositionInvalidSec_)
                {
                    state_.positionHealth =
                        PositionHealth::Lost;
                }
            }
        }
        else if (
            positionReacquisitionPending_ &&
            positionValid)
        {
            state_.positionHealth =
                PositionHealth::Valid;

            positionInvalidDurationSec_ = 0.0F;
            positionUncertaintyDeg_ = 0.0F;

            positionReacquisitionPending_ = false;
        }

        state_.withinLimits =
            state_.positionDeg >= minimumPositionDeg_ &&
            state_.positionDeg <= maximumPositionDeg_;
    }

    const AxisState &Axis::state() const
    {
        return state_;
    }

    const AxisStatus &Axis::status() const
    {
        return status_;
    }

    float Axis::positionInvalidDurationSec() const
    {
        return positionInvalidDurationSec_;
    }

    float Axis::positionUncertaintyDeg() const
    {
        return positionUncertaintyDeg_;
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

    bool Axis::isVelocityAllowed(
        const float velocityDegPerSec) const
    {
        if (velocityDegPerSec == 0.0F)
        {
            return true;
        }

        if (state_.positionDeg >= maximumPositionDeg_)
        {
            return velocityDegPerSec < 0.0F;
        }

        if (state_.positionDeg <= minimumPositionDeg_)
        {
            return velocityDegPerSec > 0.0F;
        }

        return true;
    }

    void Axis::requestPositionReacquisition()
    {
        if (state_.positionHealth != PositionHealth::Lost)
        {
            return;
        }

        positionSensor_.requestReacquisition();

        positionInvalidDurationSec_ = 0.0F;
        positionUncertaintyDeg_ = 0.0F;

        positionReacquisitionPending_ = true;
    }

} // namespace asteria::core