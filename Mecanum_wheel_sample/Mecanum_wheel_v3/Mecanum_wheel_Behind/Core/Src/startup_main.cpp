#include "startup_main.h"
#include "pid.h"
#include "bsp_usart.h"
#include "stm32f1xx_hal_dma.h"

extern uint8_t HWT101CT_buffer[1];
extern uint8_t rx_buffer[1];


void startup_main(void)
{

	HAL_ALL_Init();
	
#if isRTOS==0    	//如果是裸机开发
	for(;;)  //等同于while(true)
	{
		
	}
#endif
}


void HAL_ALL_Init(void)
{
	pid_controller.All_Device_Init();
	HAL_UART_Receive_IT(&huart1, rx_buffer, 1);
	HAL_UART_Receive_IT(&huart3,HWT101CT_buffer,1);

	

	HAL_TIM_Base_Start_IT(&htim1);

	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_1|TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_1|TIM_CHANNEL_2);
	
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
	

}

