#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"



UART_HandleTypeDef g_uart1_handle;                                          /*UART���*/

/* ���ջ���, ���USART_REC_LEN���ֽ�. */
uint8_t g_rx_buffer[1];                                                     /*HAL��ʹ�õĴ��ڽ������ݻ�����*/

 
 //����һ��ʼ������
void usart_init(uint32_t baudrate)
{
    /*UART ��ʼ������*/
    g_uart1_handle.Instance = USART1;                                         /* USART1 */
    g_uart1_handle.Init.BaudRate = baudrate;                                  /* ������ */
    g_uart1_handle.Init.WordLength = UART_WORDLENGTH_8B;                      /* �ֳ�Ϊ8λ���ݸ�ʽ */
    g_uart1_handle.Init.StopBits = UART_STOPBITS_1;                           /* һ��ֹͣλ */
    g_uart1_handle.Init.Parity = UART_PARITY_NONE;                            /* ����żУ��λ */
    g_uart1_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;                      /* ��Ӳ������ */
    g_uart1_handle.Init.Mode = UART_MODE_TX_RX;                               /* �շ�ģʽ */
    HAL_UART_Init(&g_uart1_handle);                                           /* ���ڳ�ʼ������   �β�Ϊ1 ����ʹ��UART1���� */

    HAL_UART_Receive_IT(&g_uart1_handle, g_rx_buffer, 1); 
    /* �ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ��������������� */
}

//����MSP�ص�����     ������ʼ������      �������ʼ����������
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef gpio_init_struct={0};

    if (huart->Instance == USART1)                            /* ����Ǵ���1�����д���1 MSP��ʼ�� */
    {
        __HAL_RCC_USART1_CLK_ENABLE();                          /*ʹ��ʱ�ӵĺ�*/
        __HAL_RCC_GPIOA_CLK_ENABLE();                           /*ʹ��GPIOʱ��*/

    //��ʼ������PA9������TX��
        gpio_init_struct.Pin = GPIO_PIN_9;                      /* ���ڷ������ź� */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* ����������� ������ߵ͵�ƽ��*/
        gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* IO�ٶ�����Ϊ���� */
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);

    //��ʼ������PA10������RX��
        gpio_init_struct.Pin = GPIO_PIN_10;                      /* ���ڽ������ź� */
        gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;              /* ����*/
        gpio_init_struct.Pull = GPIO_PULLUP;                     /* ���� */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;           /* IO�ٶ�����Ϊ���� */
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);
        
        
        HAL_NVIC_SetPriority(USART1_IRQn,0,0);                      /*�������ȼ�*/
        HAL_NVIC_EnableIRQ(USART1_IRQn);                            /*ʹ���ж�*/
    }
}
//����һ�жϷ�����
void USART1_IRQHandler (void)
{
    HAL_UART_IRQHandler(&g_uart1_handle);                           /*�жϹ���������    ������ж�ʧ�ܵ���CpltCallback����*/
    HAL_UART_Receive_IT(&g_uart1_handle, (uint8_t *)g_rx_buffer, 1); /*��Ϊ����ĺ���ʧ���ˣ��������µ����ж�*/
}

//�������ݽ�����ɻص�����
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







