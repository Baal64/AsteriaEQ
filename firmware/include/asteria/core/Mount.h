#pragma once

#include "AxisController.h"

namespace asteria::core
{

    /**
     * @brief Représente une monture équatoriale complète.
     *
     * Responsabilités :
     *  - coordonner les deux axes
     *  - propager les mises à jour temporelles
     *  - activer ou désactiver la monture
     *
     * Cette classe ne contient aucune logique de suivi, de guidage
     * ou de GoTo. Elle orchestre uniquement les composants qui lui
     * sont confiés.
     */
    class Mount
    {
    public:
        Mount(
            AxisController &rightAscension,
            AxisController &declination);

        void enable();

        void disable();

        void update(float deltaTimeSec);

    private:
        AxisController &rightAscension_;
        AxisController &declination_;

        bool enabled_;
    };

} // namespace asteria::core