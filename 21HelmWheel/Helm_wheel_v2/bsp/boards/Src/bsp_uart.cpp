#include "bsp_uart.h"


uint8_t rxbuf_odometer[1];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

    if(huart->Instance==UART4)
    {
        ReceivefromMapan(rxbuf_odometer[0]);
    }

}
