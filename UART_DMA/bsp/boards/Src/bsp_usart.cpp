#include "bsp_usart.h"



extern uint8_t rx_buffer[1];


	
void HAL_UART_IDLE_Callback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1)
	{
		__HAL_DMA_DISABLE(huart->hdmarx);//失能DMA接收
		
		HAL_UART_Receive_DMA(&huart1,rx_buffer,1);
		__HAL_DMA_ENABLE(huart->hdmarx);//使能DMA接收
		
	}
}
