#include <asteria/core/MountStateMachine.h>

#include <asteria/config/AsteriaConfig.h>
#include <asteria/core/Axis.h>
#include <asteria/core/sources/PositionMotionSource.h>
#include <asteria/core/sources/TrackingMotionSource.h>
#include <asteria/core/sources/St4MotionSource.h>

namespace asteria::core
{

    MountStateMachine::MountStateMachine(
        Axis &rightAscensionAxis,
        Axis &declinationAxis,
        PositionMotionSource &rightAscensionHomeSource,
        PositionMotionSource &declinationHomeSource,
        TrackingMotionSource &trackingSource,
        St4MotionSource &rightAscensionSt4Source,
        St4MotionSource &declinationSt4Source)
        : rightAscensionAxis_(rightAscensionAxis),
          declinationAxis_(declinationAxis),
          rightAscensionHomeSource_(rightAscensionHomeSource),
          declinationHomeSource_(declinationHomeSource),
          trackingSource_(trackingSource),
          rightAscensionSt4Source_(rightAscensionSt4Source),
          declinationSt4Source_(declinationSt4Source)
    {
    }

    void MountStateMachine::begin()
    {
        rightAscensionHomeSource_.setEnabled(false);
        declinationHomeSource_.setEnabled(false);

        trackingSource_.setEnabled(false);

        rightAscensionSt4Source_.setEnabled(false);
        declinationSt4Source_.setEnabled(false);

        state_ =
            MountState::WaitingForHome;
    }

    void MountStateMachine::update(
        const float deltaTimeSec,
        const bool clicked,
        const bool longPressed)
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
            if (longPressed)
            {
                confirmTrackingModeSelection();

                trackingSource_.setEnabled(true);

                rightAscensionSt4Source_.setEnabled(true);
                declinationSt4Source_.setEnabled(true);

                state_ =
                    MountState::Tracking;
            }
            else if (clicked)
            {
                selectNextTrackingMode();
            }

            updateTrackingModeSelection(
                deltaTimeSec);
            break;

        case MountState::Tracking:
            if (longPressed)
            {
                cancelTrackingModeSelection();

                trackingSource_.setEnabled(false);

                rightAscensionSt4Source_.setEnabled(false);
                declinationSt4Source_.setEnabled(false);

                state_ =
                    MountState::Ready;
            }
            else if (clicked)
            {
                selectNextTrackingMode();
            }

            updateTrackingModeSelection(
                deltaTimeSec);
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

    void MountStateMachine::selectNextTrackingMode()
    {
        if (!trackingModeSelectionActive_)
        {
            selectedTrackingMode_ =
                trackingSource_.mode();

            trackingModeSelectionActive_ = true;
        }
        trackingModeSelectionElapsedSec_ = 0.0F;

        switch (selectedTrackingMode_)
        {
        case TrackingMode::Sidereal:
            selectedTrackingMode_ =
                TrackingMode::Lunar;
            break;

        case TrackingMode::Lunar:
            selectedTrackingMode_ =
                TrackingMode::Solar;
            break;

        case TrackingMode::Solar:
            selectedTrackingMode_ =
                TrackingMode::Sidereal;
            break;
        }
    }

    void MountStateMachine::confirmTrackingModeSelection()
    {
        if (!trackingModeSelectionActive_)
        {
            return;
        }

        trackingSource_.setMode(
            selectedTrackingMode_);

        trackingModeSelectionActive_ = false;
        trackingModeSelectionElapsedSec_ = 0.0F;
    }

    TrackingMode MountStateMachine::displayTrackingMode() const
    {
        if (trackingModeSelectionActive_)
        {
            return selectedTrackingMode_;
        }

        return trackingSource_.mode();
    }

    void MountStateMachine::cancelTrackingModeSelection()
    {
        trackingModeSelectionActive_ = false;
        trackingModeSelectionElapsedSec_ = 0.0F;

        selectedTrackingMode_ =
            trackingSource_.mode();
    }

    void MountStateMachine::updateTrackingModeSelection(
        const float deltaTimeSec)
    {
        if (!trackingModeSelectionActive_)
        {
            return;
        }

        trackingModeSelectionElapsedSec_ +=
            deltaTimeSec;

        if (
            trackingModeSelectionElapsedSec_ >=
            config::motion::
                TRACKING_MODE_SELECTION_TIMEOUT_SEC)
        {
            confirmTrackingModeSelection();
        }
    }

    void MountStateMachine::forceReadyForTest()
    {
        rightAscensionHomeSource_.setEnabled(false);
        declinationHomeSource_.setEnabled(false);

        trackingSource_.setEnabled(false);

        rightAscensionSt4Source_.setEnabled(false);
        declinationSt4Source_.setEnabled(false);

        cancelTrackingModeSelection();

        state_ =
            MountState::Ready;
    }

} // namespace asteria::core"