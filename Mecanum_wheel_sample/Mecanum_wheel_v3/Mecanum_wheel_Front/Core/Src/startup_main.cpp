#include "startup_main.h"
#include "pid_user.h"

extern uint8_t rx_buffer[1];

void startup_main(void)
{
	 Hal_ALL_Init();
//	 pid_controller.All_Device_Init();

	
#if isRTOS==0    	//������������
	for(;;)  //��ͬ��while(true)
	{

	}
#endif
}


void Hal_ALL_Init(void)
{
	pid_controller.All_Device_Init();
	HAL_UART_Receive_IT(&huart1,rx_buffer,1);

	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_1|TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_1|TIM_CHANNEL_2);
	
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);
}
