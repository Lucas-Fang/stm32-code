#include "startup_main.h"
#include "bsp_delay.h"

void startup_main(void)
{
bsp_delay.f1.Init(72);
	
#if isRTOS==0    	//如果是裸机开发
	for(;;)  //等同于while(true)
	{

	}
#endif
}


extern "C"
	
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	if (htim ->Instance== TIM4)
	{
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
	}
}
