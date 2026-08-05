#include <asteria/platform/avr/StepTimerCalculator.h>

namespace asteria::platform::avr
{

    namespace
    {

        constexpr uint16_t MAX_COMPARE_VALUE = 65535U;

        constexpr uint16_t PRESCALERS[]{
            1U,
            8U,
            64U,
            256U,
            1024U};

        constexpr uint8_t PRESCALER_COUNT =
            sizeof(PRESCALERS) / sizeof(PRESCALERS[0]);

    } // namespace

    bool StepTimerCalculator::calculate(
        const uint32_t timerClockHz,
        const float requestedFrequencyHz,
        StepTimerSettings &settings)
    {
        if (timerClockHz == 0UL ||
            requestedFrequencyHz <= 0.0F)
        {
            return false;
        }

        for (uint8_t index = 0U;
             index < PRESCALER_COUNT;
             ++index)
        {
            const uint16_t prescaler =
                PRESCALERS[index];

            const float compareValue =
                static_cast<float>(timerClockHz) /
                    (2.0F *
                     static_cast<float>(prescaler) *
                     requestedFrequencyHz) -
                1.0F;

            if (compareValue < 0.0F ||
                compareValue >
                    static_cast<float>(MAX_COMPARE_VALUE))
            {
                continue;
            }

            const uint16_t roundedCompareValue =
                static_cast<uint16_t>(
                    compareValue + 0.5F);

            settings.compareValue =
                roundedCompareValue;

            settings.prescaler =
                prescaler;

            settings.actualFrequencyHz =
                static_cast<float>(timerClockHz) /
                (2.0F *
                 static_cast<float>(prescaler) *
                 static_cast<float>(
                     roundedCompareValue + 1UL));

            return true;
        }

        return false;
    }

} // namespace asteria::platform::avr