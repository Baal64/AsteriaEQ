#pragma once

namespace asteria::hardware
{

    class IStepPulseGenerator
    {
    public:
        virtual ~IStepPulseGenerator() = default;

        virtual void start(float frequencyHz) = 0;
        virtual void stop() = 0;

        virtual bool isRunning() const = 0;
        virtual float frequencyHz() const = 0;
    };

} // namespace asteria::hardware