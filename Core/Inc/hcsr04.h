#ifndef HCSR04_H_
#define HCSR04_H_

#include "stm32l1xx_hal.h"

typedef struct {
	TIM_HandleTypeDef *htim;  // Wskaźnik na Timer
	uint32_t Channel;         // Kanał Timera
	uint32_t ActiveChannel;   // Aktywny kanał dla przerwania
	GPIO_TypeDef *TRIG_Port;  // Port pinu TRIG
	uint16_t TRIG_Pin;        // Numer pinu TRIG

	// Zmienne stanu
	uint32_t IC_Val1;
	uint32_t IC_Val2;
	uint32_t Difference;
	uint8_t Is_First_Captured;

	// Wynik
	uint16_t Distance;
} HCSR04_Handle;

// Deklaracje funkcji
void HCSR04_Init(HCSR04_Handle *sensor, TIM_HandleTypeDef *htim, uint32_t Channel, GPIO_TypeDef *TRIG_Port, uint16_t TRIG_Pin);
void HCSR04_Trigger(HCSR04_Handle *sensor);
void HCSR04_CaptureCallback(HCSR04_Handle *sensor, TIM_HandleTypeDef *htim);

#endif /* HCSR04_H_ */
