#pragma once

#include <asteria/core/IMotionSource.h>
#include <asteria/platform/mcp23017/Mcp23017DigitalInput.h>

namespace asteria::core
{

    class St4MotionSource final
        : public IMotionSource
    {
    public:
        St4MotionSource(
            platform::mcp23017::Mcp23017DigitalInput &plusInput,
            platform::mcp23017::Mcp23017DigitalInput &minusInput);

        MotionProposal update(
            float deltaTimeSec) override;

        void setEnabled(bool enabled);

        bool isEnabled() const;

        bool hasConflict() const;

        float correctionVelocityDegPerSec() const;

    private:
        platform::mcp23017::Mcp23017DigitalInput &plusInput_;
        platform::mcp23017::Mcp23017DigitalInput &minusInput_;

        bool enabled_{false};
        bool conflict_{false};

        float correctionVelocityDegPerSec_{0.0F};
    };

} // namespace asteria::core