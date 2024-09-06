<<<<<<< HEAD
#include "startup_main.h"
#include "bsp_delay.h"
#include "usart.h"

uint8_t rx_buffer[1]={0};
void startup_main(void)
{
	bsp_delay.f1.Init(72);
	

	
   __HAL_UART_CLEAR_IDLEFLAG(&huart1); // 清除空闲中断标志位
   __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);//开启串口空闲中断
	
	if(HAL_UART_Receive_DMA(&huart1,rx_buffer,1)!=HAL_OK)
	{
		Error_Handler();
	}
	
	
	
#if isRTOS==0    	//如果是裸机开发
	for(;;)  //等同于while(true)
	{
		if(rx_buffer[0]=='1')
		{
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
		}
		
	}
#endif
}
=======
#include "startup_main.h"
#include "bsp_delay.h"
#include "usart.h"

uint8_t rx_buffer[1]={0};
void startup_main(void)
{
	bsp_delay.f1.Init(72);
	

	
   __HAL_UART_CLEAR_IDLEFLAG(&huart1); // 清除空闲中断标志位
   __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);//开启串口空闲中断
	
	if(HAL_UART_Receive_DMA(&huart1,rx_buffer,1)!=HAL_OK)
	{
		Error_Handler();
	}
	
	
	
#if isRTOS==0    	//如果是裸机开发
	for(;;)  //等同于while(true)
	{
		if(rx_buffer[0]=='1')
		{
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
		}
		
	}
#endif
}
>>>>>>> 00ac74e (9.6)
