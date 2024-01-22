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

    }
}

