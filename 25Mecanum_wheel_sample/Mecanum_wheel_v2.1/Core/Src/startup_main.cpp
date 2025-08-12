#include "startup_main.h"
#include "bsp_delay.h"

extern uint8_t rx_buffer[1];
void startup_main(void)
{
	

	HAL_TIM_Base_Start_IT(&htim4);
	
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);
	
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	
#if isRTOS==0    	//如果是裸机开发
	for(;;)  //等同于while(true)
	{

	}
#endif
}
