<<<<<<< HEAD
#include "startup_main.h"
#include "bsp_delay.h"
#include "tim.h"

void startup_main(void)
{
  bsp_delay.f1.Init(72);
	uint16_t ledrpwmval = 10;

#if isRTOS==0    	//������������
	for(;;)  //��ͬ��while(true)
	{
		
		HAL_Delay(1000);
           /*�޸ıȽ�ֵռ�ձ�*/
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
=======
#include "startup_main.h"
#include "bsp_delay.h"
#include "tim.h"

void startup_main(void)
{
  bsp_delay.f1.Init(72);
	uint16_t ledrpwmval = 10;

#if isRTOS==0    	//������������
	for(;;)  //��ͬ��while(true)
	{
		
		HAL_Delay(1000);
           /*�޸ıȽ�ֵռ�ձ�*/
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
>>>>>>> 00ac74e (9.6)
