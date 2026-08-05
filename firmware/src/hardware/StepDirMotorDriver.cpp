#include <math.h>

#include <asteria/hardware/StepDirMotorDriver.h>

namespace asteria::hardware
{

    StepDirMotorDriver::StepDirMotorDriver(
        const StepperDriverConfiguration &configuration,
        IDigitalOutput &directionOutput,
        IDigitalOutput &enableOutput,
        IStepPulseGenerator &pulseGenerator)
        : stepperKinematics_(configuration),
          directionOutput_(directionOutput),
          enableOutput_(enableOutput),
          pulseGenerator_(pulseGenerator),
          enableActiveLow_(configuration.enableActiveLow),
          invertDirection_(configuration.invertDirection)
    {
    }

    void StepDirMotorDriver::enable()
    {
        isEnabled_ = true;

        updateEnableOutput();
        updatePulseGenerator();
    }

    void StepDirMotorDriver::disable()
    {
        pulseGenerator_.stop();

        isEnabled_ = false;
        updateEnableOutput();
    }

    bool StepDirMotorDriver::isEnabled() const
    {
        return isEnabled_;
    }

    void StepDirMotorDriver::setVelocityDegPerSec(
        const float velocityDegPerSec)
    {
        velocityDegPerSec_ = velocityDegPerSec;

        updateDirectionOutput();
        updatePulseGenerator();
    }

    float StepDirMotorDriver::velocityDegPerSec() const
    {
        return velocityDegPerSec_;
    }

    void StepDirMotorDriver::update(const float deltaTimeSec)
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

        const float frequencyHz =
            fabsf(
                stepperKinematics_.stepFrequencyFromAxisVelocity(
                    velocityDegPerSec_));

        if (frequencyHz <= 0.0F)
        {
            pulseGenerator_.stop();
            return;
        }

        pulseGenerator_.start(frequencyHz);
    }

    void StepDirMotorDriver::updateDirectionOutput()
    {
        const bool positiveDirection =
            velocityDegPerSec_ >= 0.0F;

        const bool outputState =
            positiveDirection != invertDirection_;

        directionOutput_.write(outputState);
    }

    void StepDirMotorDriver::updateEnableOutput()
    {
        const bool outputState =
            enableActiveLow_
                ? !isEnabled_
                : isEnabled_;

        enableOutput_.write(outputState);
    }

} // namespace asteria::hardware