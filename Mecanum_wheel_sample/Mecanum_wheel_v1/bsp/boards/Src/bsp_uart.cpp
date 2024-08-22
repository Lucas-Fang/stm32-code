#include "bsp_uart.h"


uint8_t rx_buff[1];

extern "C"
	
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		switch(rx_buff[0])
		{
			case '0':
				Front_L(200);
				Front_R(200);
				Back_L(200);
				Back_R(200);
			break;
			
			case '1':
				Front_L(-200);
				Front_R(-200);
				Back_L(-200);
				Back_R(-200);
			break;			
			
			case '2'://��ƽ��
				Front_L(-200);
				Front_R(200);
				Back_L(200);
				Back_R(-200);
			break;
			
			case '3'://��ƽ��
				Front_L(200);
				Front_R(-200);
				Back_L(-200);
				Back_R(200);
			break;
			
			case '4'://��ʱ��
				Front_L(-200);
				Front_R(200);
				Back_L(-200);
				Back_R(200);
			break;
			
			case '5'://˳ʱ��
				Front_L(200);
				Front_R(-200);
				Back_L(200);
				Back_R(-200);
			break;
			
			case '6'://����
				Front_L(0);
				Front_R(200);
				Back_L(200);
				Back_R(0);
			break;
			
			case '7'://����
				Front_L(200);
				Front_R(0);
				Back_L(0);
				Back_R(200);
			break;
			
			case '8'://��ת
				Front_L(0);
				Front_R(0);
				Back_L(-200);
				Back_R(200);
			break;
			
			case '9'://��ת
				Front_L(0);
				Front_R(0);
				Back_L(200);
				Back_R(-200);
			break;
			
			case 'a':
				Front_L(0);
				Front_R(0);
				Back_L(0);
				Back_R(0);
			break;
			
			
		}
		
		
		
	}
}
