#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"



UART_HandleTypeDef g_uart1_handle;                                          /*UART句柄*/

/* 接收缓冲, 最大USART_REC_LEN个字节. */
uint8_t g_rx_buffer[1];                                                     /*HAL库使用的串口接收数据缓冲区*/

 
 //串口一初始换函数
void usart_init(uint32_t baudrate)
{
    /*UART 初始化设置*/
    g_uart1_handle.Instance = USART1;                                         /* USART1 */
    g_uart1_handle.Init.BaudRate = baudrate;                                  /* 波特率 */
    g_uart1_handle.Init.WordLength = UART_WORDLENGTH_8B;                      /* 字长为8位数据格式 */
    g_uart1_handle.Init.StopBits = UART_STOPBITS_1;                           /* 一个停止位 */
    g_uart1_handle.Init.Parity = UART_PARITY_NONE;                            /* 无奇偶校验位 */
    g_uart1_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;                      /* 无硬件流控 */
    g_uart1_handle.Init.Mode = UART_MODE_TX_RX;                               /* 收发模式 */
    HAL_UART_Init(&g_uart1_handle);                                           /* 串口初始化函数   形参为1 所以使能UART1串口 */

    HAL_UART_Receive_IT(&g_uart1_handle, g_rx_buffer, 1); 
    /* 该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量 */
}

//串口MSP回调函数     用来初始化外设      被外设初始化函数调用
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef gpio_init_struct={0};

    if (huart->Instance == USART1)                            /* 如果是串口1，进行串口1 MSP初始化 */
    {
        __HAL_RCC_USART1_CLK_ENABLE();                          /*使能时钟的宏*/
        __HAL_RCC_GPIOA_CLK_ENABLE();                           /*使能GPIO时钟*/

    //初始化引脚PA9（发送TX）
        gpio_init_struct.Pin = GPIO_PIN_9;                      /* 串口发送引脚号 */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* 复用推挽输出 （输出高低电平）*/
        gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* IO速度设置为高速 */
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);

    //初始化引脚PA10（接收RX）
        gpio_init_struct.Pin = GPIO_PIN_10;                      /* 串口接收引脚号 */
        gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;              /* 输入*/
        gpio_init_struct.Pull = GPIO_PULLUP;                     /* 上拉 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;           /* IO速度设置为高速 */
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);
        
        
        HAL_NVIC_SetPriority(USART1_IRQn,0,0);                      /*设置优先级*/
        HAL_NVIC_EnableIRQ(USART1_IRQn);                            /*使能中断*/
    }
}
//串口一中断服务函数
void USART1_IRQHandler (void)
{
    HAL_UART_IRQHandler(&g_uart1_handle);                           /*中断公共服务函数    会清除中断失能调用CpltCallback函数*/
    HAL_UART_Receive_IT(&g_uart1_handle, (uint8_t *)g_rx_buffer, 1); /*因为上面的函数失能了，所以重新调用中断*/
}

//串口数据接收完成回调函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
      switch(g_rx_buffer[0])
      {
        case 1:
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);         //liang
        break;
        
        case 0:
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);        //bu liang 
        break;
        
        default:
        break;
       }
   }
}







