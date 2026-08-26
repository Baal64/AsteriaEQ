#include <asteria/core/MountStateMachine.h>

#include <asteria/config/AsteriaConfig.h>
#include <asteria/core/Axis.h>
#include <asteria/core/sources/PositionMotionSource.h>

namespace asteria::core
{

    MountStateMachine::MountStateMachine(
        Axis &rightAscensionAxis,
        Axis &declinationAxis,
        PositionMotionSource &rightAscensionHomeSource,
        PositionMotionSource &declinationHomeSource)
        : rightAscensionAxis_(rightAscensionAxis),
          declinationAxis_(declinationAxis),
          rightAscensionHomeSource_(rightAscensionHomeSource),
          declinationHomeSource_(declinationHomeSource)
    {
    }

    void MountStateMachine::begin()
    {
        rightAscensionHomeSource_.setEnabled(false);
        declinationHomeSource_.setEnabled(false);

        state_ =
            MountState::WaitingForHome;
    }

    void MountStateMachine::update(
        const bool clicked)
    {
        switch (state_)
        {
        case MountState::Initializing:
            break;

        case MountState::WaitingForHome:
            if (clicked)
            {
                rightAscensionHomeSource_.setEnabled(true);
                declinationHomeSource_.setEnabled(true);

                state_ =
                    MountState::Homing;
            }
            break;

        case MountState::Homing:
            if (isHomeReached())
            {
                rightAscensionHomeSource_.setEnabled(false);
                declinationHomeSource_.setEnabled(false);

                state_ =
                    MountState::Ready;
            }
            break;

        case MountState::Ready:
            break;

        case MountState::Tracking:
            break;

        case MountState::Parked:
            break;

        case MountState::Error:
            break;
        }
    }

    MountState MountStateMachine::state() const
    {
        return state_;
    }

    bool MountStateMachine::isHomeReached() const
    {
        const float rightAscensionErrorDeg =
            rightAscensionAxis_.state().positionDeg -
            config::homing::RIGHT_ASCENSION_POSITION_DEG;

        const float declinationErrorDeg =
            declinationAxis_.state().positionDeg -
            config::homing::DECLINATION_POSITION_DEG;

        const bool rightAscensionHomeReached =
            rightAscensionErrorDeg <=
                config::homing::POSITION_TOLERANCE_DEG &&
            rightAscensionErrorDeg >=
                -config::homing::POSITION_TOLERANCE_DEG;

        const bool declinationHomeReached =
            declinationErrorDeg <=
                config::homing::POSITION_TOLERANCE_DEG &&
            declinationErrorDeg >=
                -config::homing::POSITION_TOLERANCE_DEG;

        return rightAscensionHomeReached &&
               declinationHomeReached;
    }

} // namespace asteria::core"