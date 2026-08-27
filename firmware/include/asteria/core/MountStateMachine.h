#pragma once

#include <asteria/core/MountState.h>
#include <asteria/core/TrackingMode.h>
namespace asteria::core
{

    class Axis;
    class PositionMotionSource;
    class TrackingMotionSource;

    class MountStateMachine
    {
    public:
        MountStateMachine(
            Axis &rightAscensionAxis,
            Axis &declinationAxis,
            PositionMotionSource &rightAscensionHomeSource,
            PositionMotionSource &declinationHomeSource,
            TrackingMotionSource &trackingSource);

        void begin();

        void update(
            float deltaTimeSec,
            bool clicked,
            bool longPressed);

        MountState state() const;

        TrackingMode displayTrackingMode() const;

        void forceReadyForTest();

    private:
        bool isHomeReached() const;
        void selectNextTrackingMode();
        void confirmTrackingModeSelection();
        void cancelTrackingModeSelection();

        Axis &rightAscensionAxis_;
        Axis &declinationAxis_;

        PositionMotionSource &rightAscensionHomeSource_;
        PositionMotionSource &declinationHomeSource_;
        TrackingMotionSource &trackingSource_;

        MountState state_{
            MountState::Initializing};

        TrackingMode selectedTrackingMode_{
            TrackingMode::Sidereal};

        bool trackingModeSelectionActive_{false};
        float trackingModeSelectionElapsedSec_{0.0F};

        void updateTrackingModeSelection(
            float deltaTimeSec);
    };

} // namespace asteria::core