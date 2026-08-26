#pragma once

namespace asteria::core
{

    enum class MountState
    {
        Initializing,
        WaitingForHome,
        Homing,
        Ready,
        Tracking,
        Parked,
        Error
    };

    inline const char *mountStateName(
        const MountState state)
    {
        switch (state)
        {
        case MountState::Initializing:
            return "INITIALIZING";

        case MountState::WaitingForHome:
            return "WAITING_FOR_HOME";

        case MountState::Homing:
            return "HOMING";

        case MountState::Ready:
            return "READY";

        case MountState::Tracking:
            return "TRACKING";

        case MountState::Parked:
            return "PARKED";

        case MountState::Error:
            return "ERROR";
        }

        return "UNKNOWN";
    }

} // namespace asteria::core