#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BTIM/btim.h"

int main(void)
{
    HAL_Init();                              /* 初始化HAL库 */
    SystemClock_Config();                    /* 设置时钟, 72Mhz */
    delay_init(72);                          /* 延时初始化 */
    led_init();                              /* LED初始化 */
    bitm_timx_int_init(5000-1,7200-1);       /* （预分频系数，自动重装载值）*/

    while(1)
    { 
        //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);  /* PC13置0 */
        //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
    }
}



