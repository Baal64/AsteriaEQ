#pragma once

#include <cstdint>

namespace asteria
{

    struct EncoderReading
    {
        uint16_t rawPosition;
        float angleDeg;
        bool valid;
    };

    class IAbsoluteEncoder
    {
    public:
        virtual ~IAbsoluteEncoder() = default;

        virtual bool begin() = 0;

        /**
         * Lit la position actuelle de l'encodeur.
         *
         * La validité regroupe les contrôles propres au capteur :
         * communication, parité, bit d'erreur, etc.
         */
        virtual EncoderReading read() = 0;
    };

} // namespace asteria