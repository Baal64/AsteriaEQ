#pragma once

#include <asteria/core/MountState.h>

namespace asteria::core
{

    class Axis;
    class PositionMotionSource;

    class MountStateMachine
    {
    public:
        MountStateMachine(
            Axis &rightAscensionAxis,
            Axis &declinationAxis,
            PositionMotionSource &rightAscensionHomeSource,
            PositionMotionSource &declinationHomeSource);

        void begin();

        void update(bool clicked);

        MountState state() const;

    private:
        bool isHomeReached() const;

        Axis &rightAscensionAxis_;
        Axis &declinationAxis_;

        PositionMotionSource &rightAscensionHomeSource_;
        PositionMotionSource &declinationHomeSource_;

        MountState state_{
            MountState::Initializing};
    };

} // namespace asteria::core