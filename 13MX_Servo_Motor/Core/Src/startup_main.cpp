#include "startup_main.h"
#include "bsp_delay.h"
#include "tim.h"

void startup_main(void)
{
  bsp_delay.f1.Init(72);
	uint16_t ledrpwmval = 10;

#if isRTOS==0    	//如果是裸机开发
	for(;;)  //等同于while(true)
	{
		
		HAL_Delay(1000);
           /*修改比较值占空比*/
        if(ledrpwmval==10)
        {
            ledrpwmval=ledrpwmval+5;
            __HAL_TIM_SET_COMPARE( &htim3,TIM_CHANNEL_2,ledrpwmval);
        }
        else if (ledrpwmval==15)
        {
            ledrpwmval=10;
            __HAL_TIM_SET_COMPARE( &htim3,TIM_CHANNEL_2,ledrpwmval);
        }
	}
#endif
}
