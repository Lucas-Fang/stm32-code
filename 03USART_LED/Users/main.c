<<<<<<< HEAD
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"


int main(void)
{
    HAL_Init();                               /* ��ʼ��HAL�� */
    SystemClock_Config();                     /* ����ʱ��, 72Mhz */
    delay_init(72);                           /* ��ʱ��ʼ�� */
    usart_init(9600);                         /*������*/

    while(1)
    {

    }
}

=======
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"


int main(void)
{
    HAL_Init();                               /* ��ʼ��HAL�� */
    SystemClock_Config();                     /* ����ʱ��, 72Mhz */
    delay_init(72);                           /* ��ʱ��ʼ�� */
    usart_init(9600);                         /*������*/

    while(1)
    {

    }
}

>>>>>>> 00ac74e (9.6)
