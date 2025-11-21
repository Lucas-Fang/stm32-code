#include "bsp_timer.h"

extern "C"
	
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM4)
	{
		
		Motor_Move();
		
	}
}
