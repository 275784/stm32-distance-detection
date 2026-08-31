#include "hcsr04.h"

// Funkcja ustawiająca początkowe parametry czujnika
void HCSR04_Init(HCSR04_Handle *sensor, TIM_HandleTypeDef *htim, uint32_t Channel, GPIO_TypeDef *TRIG_Port, uint16_t TRIG_Pin)
{
	sensor->htim = htim;
	sensor->Channel = Channel;
	sensor->TRIG_Port = TRIG_Port;
	sensor->TRIG_Pin = TRIG_Pin;

	sensor->IC_Val1 = 0;
	sensor->IC_Val2 = 0;
	sensor->Difference = 0;
	sensor->Is_First_Captured = 0;
	sensor->Distance = 0;

	// Ustalenie odpowiedniego kanału przerwania
	if (Channel == TIM_CHANNEL_1) sensor->ActiveChannel = HAL_TIM_ACTIVE_CHANNEL_1;
	else if (Channel == TIM_CHANNEL_2) sensor->ActiveChannel = HAL_TIM_ACTIVE_CHANNEL_2;
	else if (Channel == TIM_CHANNEL_3) sensor->ActiveChannel = HAL_TIM_ACTIVE_CHANNEL_3;
	else if (Channel == TIM_CHANNEL_4) sensor->ActiveChannel = HAL_TIM_ACTIVE_CHANNEL_4;

	// Odpalenie Timera z automatu
	HAL_TIM_Base_Start(htim);
	HAL_TIM_IC_Start_IT(htim, Channel);
}

// Funkcja wyzwalająca impuls (zamiast pętli FOR, używany precyzyjny stoper)
void HCSR04_Trigger(HCSR04_Handle *sensor)
{
	// Czyścimy flagę przerwania kanału 2, żeby nie czytać śmieci z przeszłości
	__HAL_TIM_CLEAR_FLAG(sensor->htim, TIM_FLAG_CC2);

	sensor->Is_First_Captured = 0;
	__HAL_TIM_SET_CAPTUREPOLARITY(sensor->htim, sensor->Channel, TIM_INPUTCHANNELPOLARITY_RISING);

	// Generujemy impuls 10us
	HAL_GPIO_WritePin(sensor->TRIG_Port, sensor->TRIG_Pin, GPIO_PIN_SET);

	uint16_t start_tick = __HAL_TIM_GET_COUNTER(sensor->htim);
	// Czekamy 10 ticków (przy 1MHz to 10us)
	while ((uint16_t)(__HAL_TIM_GET_COUNTER(sensor->htim) - start_tick) < 10) {}

	HAL_GPIO_WritePin(sensor->TRIG_Port, sensor->TRIG_Pin, GPIO_PIN_RESET);
}

// Funkcja przerwania
void HCSR04_CaptureCallback(HCSR04_Handle *sensor, TIM_HandleTypeDef *htim)
{
	// Sprawdzamy, czy przerwanie przyszło z timera i kanału konkretnego czujnika
	if (htim == sensor->htim && htim->Channel == sensor->ActiveChannel)
	{
		if (sensor->Is_First_Captured == 0)
		{
			sensor->IC_Val1 = HAL_TIM_ReadCapturedValue(htim, sensor->Channel);
			sensor->Is_First_Captured = 1;
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, sensor->Channel, TIM_INPUTCHANNELPOLARITY_FALLING);
		}
		else if (sensor->Is_First_Captured == 1)
		{
			sensor->IC_Val2 = HAL_TIM_ReadCapturedValue(htim, sensor->Channel);

			if (sensor->IC_Val2 > sensor->IC_Val1)
			{
				sensor->Difference = sensor->IC_Val2 - sensor->IC_Val1;
			}
			else if (sensor->IC_Val1 > sensor->IC_Val2)
			{
				sensor->Difference = (0xFFFF - sensor->IC_Val1) + sensor->IC_Val2 + 1;
			}

			// Surowe obliczenie dystansu
			uint16_t raw_distance = sensor->Difference / 58;

			// Odcięcie błędnego echa
			if (raw_distance > 400)
			{
				raw_distance = 400;
			}

			sensor->Distance = raw_distance;

			sensor->Is_First_Captured = 0;
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, sensor->Channel, TIM_INPUTCHANNELPOLARITY_RISING);
		}
	}
}
