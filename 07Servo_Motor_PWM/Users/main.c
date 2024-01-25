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
    
    HAL_Init();                              /* ��ʼ��HAL�� */
    SystemClock_Config();                    /* ����ʱ��, 72Mhz */
    delay_init(72);                          /* ��ʱ��ʼ�� */
    led_init();                              /* LED��ʼ�� */
    gtim_timx_pwm_chy_init(200-1,7200-1);      /*��ʼ����ʱ��*/
    
    
    while(1)
    { 
        delay_ms(1000);

        /*�޸ıȽ�ֵռ�ձ�*/
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



