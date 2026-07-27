#include <math.h>

#include <asteria/hardware/StepDirMotorDriver.h>

namespace asteria::hardware
{

    StepDirMotorDriver::StepDirMotorDriver(
        const StepperKinematics &stepperKinematics,
        IStepPulseGenerator &pulseGenerator)
        : stepperKinematics_(stepperKinematics),
          pulseGenerator_(pulseGenerator)
    {
    }

    void StepDirMotorDriver::enable()
    {
        isEnabled_ = true;
        updatePulseGenerator();
    }

    void StepDirMotorDriver::disable()
    {
        isEnabled_ = false;
        pulseGenerator_.stop();
    }

    bool StepDirMotorDriver::isEnabled() const
    {
        return isEnabled_;
    }

    void StepDirMotorDriver::setVelocityDegPerSec(
        float velocityDegPerSec)
    {
        velocityDegPerSec_ = velocityDegPerSec;

        updatePulseGenerator();
    }

    float StepDirMotorDriver::velocityDegPerSec() const
    {
        return velocityDegPerSec_;
    }

    void StepDirMotorDriver::update(float deltaTimeSec)
    {
        (void)deltaTimeSec;
    }

    void StepDirMotorDriver::updatePulseGenerator()
    {
        if (!isEnabled_)
        {
            pulseGenerator_.stop();
            return;
        }

        const float frequency =
            fabsf(
                stepperKinematics_.stepFrequencyFromAxisVelocity(
                    velocityDegPerSec_));

        if (frequency <= 0.0F)
        {
            pulseGenerator_.stop();
        }
        else
        {
            pulseGenerator_.start(frequency);
        }
    }

} // namespace asteria::hardware