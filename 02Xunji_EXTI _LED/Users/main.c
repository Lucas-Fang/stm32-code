<<<<<<< HEAD
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/EXTI/exti.h"


int main(void)
{
    HAL_Init();                              /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);      /* ����ʱ��, 72Mhz */
    delay_init(72);                          /* ��ʱ��ʼ�� */
    led_init ();
    exti_init();

    while(1)
    { 

    }
}
=======
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/EXTI/exti.h"


int main(void)
{
    HAL_Init();                              /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);      /* ����ʱ��, 72Mhz */
    delay_init(72);                          /* ��ʱ��ʼ�� */
    led_init ();
    exti_init();

    while(1)
    { 

    }
}
>>>>>>> 00ac74e (9.6)
