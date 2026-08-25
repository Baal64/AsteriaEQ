#pragma once

#include <asteria/core/AxisState.h>
#include <asteria/core/AxisStatus.h>
#include <asteria/core/AxisTarget.h>
#include <asteria/hardware/IStepperDriver.h>
#include <asteria/core/IPositionSensor.h>

namespace asteria::core
{

    class Axis
    {
    public:
        explicit Axis(
            hardware::IStepperDriver &driver,
            IPositionSensor &positionSensor,
            float minimumPositionDeg,
            float maximumPositionDeg);

        void enable();
        void disable();

        void setTarget(const AxisTarget &target);

        void update(float deltaTimeSec);

        const AxisState &state() const;
        const AxisStatus &status() const;

    private:
        static constexpr float POSITION_TOLERANCE_DEG = 0.001F;

        float calculateVelocityForPosition(float deltaTimeSec) const;

        bool isVelocityAllowed(
            float velocityDegPerSec) const;

        hardware::IStepperDriver &driver_;
        IPositionSensor &positionSensor_;

        AxisTarget target_{};
        AxisState state_{};
        AxisStatus status_{};

        float minimumPositionDeg_;
        float maximumPositionDeg_;
    };

} // namespace asteria::core