#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/TIMER/gtim.h"


extern TIM_HandleTypeDef g_timx_pwm_chy_handle;



int main(void)
{
    uint16_t ledrpwmval = 25;
//    uint8_t dir = 1;
    
    HAL_Init();                              /* ��ʼ��HAL�� */
    SystemClock_Config();                    /* ����ʱ��, 72Mhz */
    delay_init(72);                          /* ��ʱ��ʼ�� */
    led_init();                              /* LED��ʼ�� */
    gtim_timx_pwm_chy_init(50-1,72-1);      /*��ʼ����ʱ��*/
    
    
    while(1)
    { 
        delay_ms(1000);

//        if (dir) ledrpwmval++;              /*dir==1 ��ledrpwmval��ֵ������*/
//        else ledrpwmval--;                  /*dir==0 ��ledrpwmval��ֵ�ڼ�С*/
//        
//        if (ledrpwmval >=300) dir = 0;
//        if (ledrpwmval ==0 )  dir = 1;


        /*�޸ıȽ�ֵռ�ձ�*/
        if(ledrpwmval==25)
        {
            ledrpwmval=ledrpwmval+25;
            __HAL_TIM_SET_COMPARE( &g_timx_pwm_chy_handle,TIM_CHANNEL_2,ledrpwmval);
        }
        if(ledrpwmval==50)
        {
            ledrpwmval=25;
            __HAL_TIM_SET_COMPARE( &g_timx_pwm_chy_handle,TIM_CHANNEL_2,ledrpwmval);
        }
    }
}



