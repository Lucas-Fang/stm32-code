#include "timer.h"


extern "C"
	
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	if (htim ->Instance== TIM2)
	{
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
	}
}
