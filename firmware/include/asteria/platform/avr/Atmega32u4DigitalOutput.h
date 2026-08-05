#pragma once

#include <stdint.h>

#include <asteria/hardware/IDigitalOutput.h>

namespace asteria::platform::avr
{

    class Atmega32u4DigitalOutput final
        : public hardware::IDigitalOutput
    {
    public:
        explicit Atmega32u4DigitalOutput(uint8_t pin);

        /**
         * Configure la broche comme sortie et lui applique son état initial.
         *
         * Cette méthode doit être appelée depuis setup(), une fois
         * l'environnement Arduino initialisé.
         */
        void begin(bool initialState = false);

        void write(bool state) override;

        bool state() const override;

    private:
        uint8_t pin_;
        bool state_ = false;
        bool initialized_ = false;
    };

} // namespace asteria::platform::avr