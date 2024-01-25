#include "./BSP/TIMER/gtim.h"


TIM_HandleTypeDef g_timx_pwm_chy_handle;


/*ͨ�ö�ʱ��PWM�����ʼ������*/
void gtim_timx_pwm_chy_init(uint16_t arr,uint16_t psc)
{
    TIM_OC_InitTypeDef timx_oc_pwm_chy = {0};
    
    g_timx_pwm_chy_handle.Instance =TIM3;                                       /*�Ĵ�������ַ*/
    g_timx_pwm_chy_handle.Init.Prescaler =psc;                                  /*Ԥ��Ƶϵ��*/
    g_timx_pwm_chy_handle.Init.Period = arr;                                    /*�Զ���װ��ֵ*/
    g_timx_pwm_chy_handle.Init.CounterMode=TIM_COUNTERMODE_UP;                  /*����ģʽ*/
    
    HAL_TIM_PWM_Init(&g_timx_pwm_chy_handle);
    
    timx_oc_pwm_chy.OCMode=TIM_OCMODE_PWM1;                                     /*ģʽѡ��*/
    timx_oc_pwm_chy.Pulse= (0.5/20)*arr;                                        /*�Ƚ�ֵ(ʹ�����ʼ�Ƕ���0)*/
    timx_oc_pwm_chy.OCPolarity=TIM_BREAKPOLARITY_HIGH;                           /*�������Ϊ��*/
    HAL_TIM_PWM_ConfigChannel(&g_timx_pwm_chy_handle, &timx_oc_pwm_chy,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&g_timx_pwm_chy_handle, TIM_CHANNEL_2);
}


/*��ʱ�����PWM MSP��ʼ������*/
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    
    
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_TIM3_CLK_ENABLE();
    
    gpio_init_struct.Pin=GPIO_PIN_5;
    gpio_init_struct.Mode=GPIO_MODE_AF_PP;                                      /*���츴��*/
    gpio_init_struct.Pull=GPIO_PULLUP;
    gpio_init_struct.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &gpio_init_struct);

    __HAL_RCC_AFIO_CLK_ENABLE();                                                /*�ض��幦��ʹ��*/
    __HAL_AFIO_REMAP_TIM3_PARTIAL();
}











