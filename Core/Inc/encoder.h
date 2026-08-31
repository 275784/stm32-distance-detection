#ifndef ENCODER_H_
#define ENCODER_H_

#include "stm32l1xx_hal.h"

typedef struct {
    TIM_HandleTypeDef *htim;   // Wskaźnik na Timer
    int16_t current_value;     // Aktualna wartość
    int16_t min_value;         // Limit dolny
    int16_t max_value;         // Limit górny
    uint8_t pulses_per_click;  // Ile impulsów na jeden klik
} Encoder_Handle;

// Inicjalizacja enkodera
void Encoder_Init(Encoder_Handle *enc, TIM_HandleTypeDef *htim, int16_t start_val, int16_t min, int16_t max, uint8_t pulses);

// Aktualizacja wartości (zwraca 1 jeśli wartość się zmieniła, 0 jeśli stoi w miejscu)
uint8_t Encoder_Update(Encoder_Handle *enc);

#endif /* ENCODER_H_ */
