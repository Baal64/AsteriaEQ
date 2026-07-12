#pragma once

#include <cstdint>

namespace asteria
{

    class IStepperDriver
    {
    public:
        virtual ~IStepperDriver() = default;

        virtual bool begin() = 0;

        virtual void enable() = 0;
        virtual void disable() = 0;
        virtual bool isEnabled() const = 0;

        virtual void setDirection(bool positive) = 0;

        /**
         * Génère une impulsion STEP unique.
         *
         * La durée minimale de l'impulsion est gérée par
         * l'implémentation concrète du driver.
         */
        virtual void step() = 0;

        /**
         * Indique si le driver a détecté un défaut.
         *
         * En V1, l'implémentation STEP/DIR simple pourra
         * retourner false si aucun diagnostic n'est disponible.
         */
        virtual bool hasFault() const = 0;
    };

} // namespace asteria