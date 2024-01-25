#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/TIMER/gtim.h"


extern TIM_HandleTypeDef g_timx_pwm_chy_handle;



int main(void)
{
    uint16_t ledrpwmval = 10;
//    uint8_t dir = 1;
    
    HAL_Init();                              /* 初始化HAL库 */
    SystemClock_Config();                    /* 设置时钟, 72Mhz */
    delay_init(72);                          /* 延时初始化 */
    led_init();                              /* LED初始化 */
    gtim_timx_pwm_chy_init(200-1,7200-1);      /*初始化定时器*/
    
    
    while(1)
    { 
        delay_ms(1000);

        /*修改比较值占空比*/
        if(ledrpwmval==10)
        {
            ledrpwmval=ledrpwmval+5;
            __HAL_TIM_SET_COMPARE( &g_timx_pwm_chy_handle,TIM_CHANNEL_2,ledrpwmval);
        }
        else if (ledrpwmval==15)
        {
            ledrpwmval=10;
            __HAL_TIM_SET_COMPARE( &g_timx_pwm_chy_handle,TIM_CHANNEL_2,ledrpwmval);
        }
    }
}



