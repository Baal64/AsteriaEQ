#pragma once

namespace asteria::hardware
{

    class IStepperDriver
    {
    public:
        virtual ~IStepperDriver() = default;

        virtual bool begin() = 0;

        virtual void enable() = 0;
        virtual void disable() = 0;

        [[nodiscard]] virtual bool isEnabled() const = 0;

        virtual void setDirection(bool positive) = 0;
        virtual void step() = 0;

        [[nodiscard]] virtual bool hasFault() const = 0;
    };

} // namespace asteria::hardware