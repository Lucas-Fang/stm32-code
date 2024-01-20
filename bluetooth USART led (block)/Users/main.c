#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"


int main(void)
{
    HAL_Init();                               /* ��ʼ��HAL�� */
    SystemClock_Config();                     /* ����ʱ��, 72Mhz */
    delay_init(72);                           /* ��ʱ��ʼ�� */
    led_init();                               /* LED��ʼ�� */
    usart_init(9600);                         /*������*/

    while(1)
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

