#include "encoder.h"

void Encoder_Init(Encoder_Handle *enc, TIM_HandleTypeDef *htim, int16_t start_val, int16_t min, int16_t max, uint8_t pulses)
{
    enc->htim = htim;
    enc->current_value = start_val;
    enc->min_value = min;
    enc->max_value = max;
    enc->pulses_per_click = pulses;

    HAL_TIM_Encoder_Start(enc->htim, TIM_CHANNEL_ALL);
    __HAL_TIM_SET_COUNTER(enc->htim, 0);
}

uint8_t Encoder_Update(Encoder_Handle *enc)
{
    // Pobierz stan licznika
    int16_t count = (int16_t)__HAL_TIM_GET_COUNTER(enc->htim);

    // Oblicz ile pełnych kliknięć wykonano
    int16_t clicks = count / enc->pulses_per_click;

    if (clicks != 0)
    {
        int16_t old_val = enc->current_value;
        int16_t next_val = enc->current_value + clicks;

        // Sprawdź limity
        if (next_val < enc->min_value) next_val = enc->min_value;
        if (next_val > enc->max_value) next_val = enc->max_value;

        enc->current_value = next_val;

        // Zawsze zerowany licznik sprzętowy po wykryciu kliku,
        // nawet jeśli wartość current_value się nie zmieniła (bo dobiła do limitu).
        __HAL_TIM_SET_COUNTER(enc->htim, 0);

        // Zwraca 1 tylko wtedy, gdy wartość faktycznie drgnęła
        return (enc->current_value != old_val);
    }

    return 0;
}
