#pragma once

#include <asteria/hardware/IDigitalOutput.h>
#include <asteria/hardware/IStepperDriver.h>
#include <asteria/hardware/IStepPulseGenerator.h>
#include <asteria/config/StepperDriverConfiguration.h>
#include <asteria/hardware/StepperKinematics.h>

namespace asteria::hardware
{

    class StepDirMotorDriver final : public IStepperDriver
    {
    public:
        StepDirMotorDriver(
            const StepperDriverConfiguration &configuration,
            IDigitalOutput &directionOutput,
            IDigitalOutput &enableOutput,
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
        void updateDirectionOutput();
        void updateEnableOutput();

        StepperKinematics stepperKinematics_;

        IDigitalOutput &directionOutput_;
        IDigitalOutput &enableOutput_;
        IStepPulseGenerator &pulseGenerator_;

        float velocityDegPerSec_ = 0.0F;

        bool isEnabled_ = false;
        bool enableActiveLow_ = true;
        bool invertDirection_ = false;
    };

} // namespace asteria::hardware