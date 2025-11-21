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
			
			case '2'://左平移
				Front_L(-200);
				Front_R(200);
				Back_L(200);
				Back_R(-200);
			break;
			
			case '3'://右平移
				Front_L(200);
				Front_R(-200);
				Back_L(-200);
				Back_R(200);
			break;
			
			case '4'://逆时针
				Front_L(-200);
				Front_R(200);
				Back_L(-200);
				Back_R(200);
			break;
			
			case '5'://顺时针
				Front_L(200);
				Front_R(-200);
				Back_L(200);
				Back_R(-200);
			break;
			
			case '6'://右上
				Front_L(0);
				Front_R(200);
				Back_L(200);
				Back_R(0);
			break;
			
			case '7'://左上
				Front_L(200);
				Front_R(0);
				Back_L(0);
				Back_R(200);
			break;
			
			case '8'://左转
				Front_L(0);
				Front_R(0);
				Back_L(-200);
				Back_R(200);
			break;
			
			case '9'://右转
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
