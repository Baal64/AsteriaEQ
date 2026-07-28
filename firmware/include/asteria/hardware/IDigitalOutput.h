#pragma once

namespace asteria::hardware
{

    class IDigitalOutput
    {
    public:
        virtual ~IDigitalOutput() = default;

        virtual void write(bool state) = 0;

        virtual bool state() const = 0;
    };

} // namespace asteria::hardware