#include "./BSP/TIMER/gtim.h"


TIM_HandleTypeDef g_timx_pwm_chy_handle;


/*通用定时器PWM输出初始化函数*/
void gtim_timx_pwm_chy_init(uint16_t arr,uint16_t psc)
{
    TIM_OC_InitTypeDef timx_oc_pwm_chy = {0};
    
    g_timx_pwm_chy_handle.Instance =TIM3;                                       /*寄存器基地址*/
    g_timx_pwm_chy_handle.Init.Prescaler =psc;                                  /*预分频系数*/
    g_timx_pwm_chy_handle.Init.Period = arr;                                    /*自动重装载值*/
    g_timx_pwm_chy_handle.Init.CounterMode=TIM_COUNTERMODE_UP;                  /*计数模式*/
    
    HAL_TIM_PWM_Init(&g_timx_pwm_chy_handle);
    
    timx_oc_pwm_chy.OCMode=TIM_OCMODE_PWM1;                                     /*模式选择*/
    timx_oc_pwm_chy.Pulse= (0.5/20)*arr;                                        /*比较值(使舵机初始角度是0)*/
    timx_oc_pwm_chy.OCPolarity=TIM_BREAKPOLARITY_HIGH;                           /*输出极性为高*/
    HAL_TIM_PWM_ConfigChannel(&g_timx_pwm_chy_handle, &timx_oc_pwm_chy,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&g_timx_pwm_chy_handle, TIM_CHANNEL_2);
}


/*定时器输出PWM MSP初始化函数*/
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    
    
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_TIM3_CLK_ENABLE();
    
    gpio_init_struct.Pin=GPIO_PIN_5;
    gpio_init_struct.Mode=GPIO_MODE_AF_PP;                                      /*推挽复用*/
    gpio_init_struct.Pull=GPIO_PULLUP;
    gpio_init_struct.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &gpio_init_struct);

    __HAL_RCC_AFIO_CLK_ENABLE();                                                /*重定义功能使能*/
    __HAL_AFIO_REMAP_TIM3_PARTIAL();
}











