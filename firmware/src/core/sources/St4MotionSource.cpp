#include <asteria/core/sources/St4MotionSource.h>

#include <asteria/config/AsteriaConfig.h>
#include <asteria/core/MotionCommand.h>

namespace asteria::core
{

    St4MotionSource::St4MotionSource(
        platform::mcp23017::Mcp23017DigitalInput &plusInput,
        platform::mcp23017::Mcp23017DigitalInput &minusInput)
        : plusInput_(plusInput),
          minusInput_(minusInput)
    {
    }

    MotionProposal St4MotionSource::update(
        float deltaTimeSec)
    {
        (void)deltaTimeSec;

        conflict_ = false;
        correctionVelocityDegPerSec_ = 0.0F;

        if (!enabled_)
        {
            return MotionProposal::none();
        }

        const bool plusActive =
            !plusInput_.read();

        const bool minusActive =
            !minusInput_.read();

        if (plusActive && minusActive)
        {
            conflict_ = true;

            return MotionProposal::none();
        }

        if (plusActive)
        {
            correctionVelocityDegPerSec_ =
                config::motion::ST4_GUIDING_RATE_DEG_PER_SEC;

            return MotionProposal::with(
                MotionCommand::correctionVelocity(
                    correctionVelocityDegPerSec_));
        }

        if (minusActive)
        {
            correctionVelocityDegPerSec_ =
                -config::motion::ST4_GUIDING_RATE_DEG_PER_SEC;

            return MotionProposal::with(
                MotionCommand::correctionVelocity(
                    correctionVelocityDegPerSec_));
        }

        return MotionProposal::none();
    }

    void St4MotionSource::setEnabled(
        const bool enabled)
    {
        enabled_ = enabled;
    }

    bool St4MotionSource::isEnabled() const
    {
        return enabled_;
    }

    bool St4MotionSource::hasConflict() const
    {
        return conflict_;
    }

    float St4MotionSource::
        correctionVelocityDegPerSec() const
    {
        return correctionVelocityDegPerSec_;
    }

} // namespace asteria::core