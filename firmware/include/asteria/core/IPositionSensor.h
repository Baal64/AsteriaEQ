#pragma once

namespace asteria::core
{

    class IPositionSensor
    {
    public:
        virtual ~IPositionSensor() = default;

        virtual float positionDeg() = 0;

        virtual bool isValid() const = 0;
    };

} // namespace asteria::core