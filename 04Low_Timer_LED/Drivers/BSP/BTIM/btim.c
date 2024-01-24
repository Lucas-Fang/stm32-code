#include "./BSP/BTIM/btim.h"
#include "./SYSTEM/delay/delay.h"


TIM_HandleTypeDef g_timx_handle;
/*定时器中断初始化函数*/

void bitm_timx_int_init( uint16_t arr,uint16_t psc)
{
    g_timx_handle.Instance = TIM6;                              /*外设寄存器基地址*/
    g_timx_handle.Init.Prescaler = psc;                         /*分频系数*/
    g_timx_handle.Init.Period=arr;                              /*自动重载值ARR*/
    g_timx_handle.Init.CounterMode=TIM_COUNTERMODE_UP;
    HAL_TIM_Base_Init (&g_timx_handle);
    
    HAL_TIM_Base_Start_IT(&g_timx_handle);                      /*使能更新中断并启动定时器*/
}
/*定时器基础MSP初始化函数*/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM6)
    {
        __HAL_RCC_TIM6_CLK_ENABLE();                            /*时钟使能*/
        HAL_NVIC_SetPriority(TIM6_IRQn,0,0);                    /*中断优先级设置*/
        HAL_NVIC_EnableIRQ(TIM6_IRQn);                          /*使能中断*/
    }
}

/*定时器6中断服务函数*/
void TIM6_IRQHandler (void)
{
    HAL_TIM_IRQHandler(&g_timx_handle);                         /*中断公共服务函数*/
}

/*定时器溢出中断回调函数*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    //HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
        //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);    /* PC13置1 */  

        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);  /* PC13置0 */
}










