<<<<<<< HEAD
#ifndef __USART_H
#define __USART_H

#include "stdio.h"
#include "./SYSTEM/sys/sys.h"




extern UART_HandleTypeDef g_uart1_handle;       /* HAL UART句柄 */
extern uint8_t g_rx_buffer[1];                  /*HAL库使用的串口接收数据缓冲区*/



void usart_init(uint32_t baudrate);                /* 串口初始化函数 */

#endif


=======
#ifndef __USART_H
#define __USART_H

#include "stdio.h"
#include "./SYSTEM/sys/sys.h"




extern UART_HandleTypeDef g_uart1_handle;       /* HAL UART句柄 */
extern uint8_t g_rx_buffer[1];                  /*HAL库使用的串口接收数据缓冲区*/



void usart_init(uint32_t baudrate);                /* 串口初始化函数 */

#endif


>>>>>>> 00ac74e (9.6)
