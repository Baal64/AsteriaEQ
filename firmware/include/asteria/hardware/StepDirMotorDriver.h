#pragma once

#include <asteria/hardware/IStepperDriver.h>
#include <asteria/hardware/IStepPulseGenerator.h>
#include <asteria/hardware/StepperKinematics.h>

namespace asteria::hardware
{

    class StepDirMotorDriver final : public IStepperDriver
    {
    public:
        StepDirMotorDriver(
            const StepperKinematics &stepperKinematics,
            IStepPulseGenerator &pulseGenerator);

        void enable() override;
        void disable() override;

        bool isEnabled() const override;

        void setVelocityDegPerSec(
            float velocityDegPerSec) override;

        void update(float deltaTimeSec) override;

        float velocityDegPerSec() const;

    private:
        void updatePulseGenerator();

        StepperKinematics stepperKinematics_;
        IStepPulseGenerator &pulseGenerator_;

        float velocityDegPerSec_ = 0.0F;
        bool isEnabled_ = false;
    };

} // namespace asteria::hardware