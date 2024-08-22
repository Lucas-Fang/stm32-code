#include "bluetooth.h"

uint8_t rx_buffer[1];

extern "C"
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart ->Instance == USART1)
	{
		switch(*rx_buffer)
		{
			case '0':
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
				break;
			
			case '1':
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
				break;
		}
	}
}

