#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/EXTI/exti.h"


int main(void)
{
    HAL_Init();                              /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);      /* 设置时钟, 72Mhz */
    delay_init(72);                          /* 延时初始化 */
    led_init ();
    exti_init();

    while(1)
    { 

    }
}
