<<<<<<< HEAD
#include "./BSP/TIMER/gtim.h"


TIM_HandleTypeDef g_timx_cap_chy_handle;


/*通用定时器输入捕获初始化函数*/
void gtim_timx_pwm_chy_init(uint16_t arr,uint16_t psc)
{
    TIM_IC_InitTypeDef timx_ic_cap_chy = {0};
    
    g_timx_cap_chy_handle.Instance =TIM3;                                       /*寄存器基地址*/
    g_timx_cap_chy_handle.Init.Prescaler =psc;                                  /*预分频系数*/
    g_timx_cap_chy_handle.Init.Period = arr;                                    /*自动重装载值*/
    g_timx_cap_chy_handle.Init.CounterMode=TIM_COUNTERMODE_UP;                  /*递增计数模式*/
    g_timx_cap_chy_handle.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_IC_Init(&g_timx_cap_chy_handle);
    
    timx_ic_cap_chy.ICPolarity =TIM_ICPOLARITY_RISING;                          /*上升沿捕获*/
    timx_ic_cap_chy.ICSelection = TIM_ICSELECTION_DIRECTTI;                     /*映射到TI1上*/
    timx_ic_cap_chy.ICPrescaler =TIM_ICPSC_DIV1;                                /*配置输入分频系数（这里是不分频）*/
    timx_ic_cap_chy.ICFilter = 0;                                               /*配置输入滤波器（这里是不滤波）*/
    HAL_TIM_IC_ConfigChannel(&g_timx_cap_chy_handle, &timx_ic_cap_chy,TIM_CHANNEL_1);
    
    __HAL_TIM_ENABLE_IT(&g_timx_cap_chy_handle,TIM_IT_UPDATE);
    HAL_TIM_IC_Start_IT(&g_timx_cap_chy_handle, TIM_CHANNEL_1);
}


/*定时器输入捕获 MSP初始化函数*/
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
  if(htim ->Instance == TIM3)
  {
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    __HAL_RCC_TIM3_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    gpio_init_struct.Pin=GPIO_PIN_6;
    gpio_init_struct.Mode=GPIO_MODE_AF_PP;                                      /*推挽输出（也可以读取输入信号）*/
    gpio_init_struct.Pull=GPIO_PULLUP;
    gpio_init_struct.Speed=GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);

    HAL_NVIC_SetPriority(TIM3_IRQn,0,0);                                       /*配置中断优先级*/
    HAL_NVIC_EnableIRQ(TIM3_IRQn);                                             /*开启ITMX中断*/
   }
}

/*输入捕获状态（g_timxchp_cap_sta）：
 *位【7】  ：=0（）时，说明没有成功捕获；=1（），说明成功捕获
 *位【6】  ：=0，说明没有捕获；= 1时说明已经成功捕获到高电平
 *位【0~5】：捕获高电平之后溢出的次数，总共可以记63次
*/


uint8_t g_timxchp_cap_sta = 0;                                                  /* 输入捕获状态 */
uint16_t g_timxchy_cap_val = 0;                                                 /* 输入捕获值 */

/*定时器3中断服务函数*/
void TIM3_IRQHandler (void)
{
    HAL_TIM_IRQHandler(&g_timx_cap_chy_handle);
}

/*定时输入捕获中断处理回调函数*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{ 
    if (htim->Instance == TIM3)
    {
        if ((g_timxchp_cap_sta & 0X80) == 0)                                    /*代表寄存器的位【7】 代表还没成功捕获*/
        {
            if((g_timxchp_cap_sta & 0X40))                                      /*捕获到下降沿 （因为上次捕获到是高电平上升沿，所以下一次的捕获到的是下降沿）*/
            {
                g_timxchp_cap_sta |= 0X80;                                      /*把位【7】置1，标记成功捕获到一次高电平脉宽*/
                g_timxchy_cap_val = HAL_TIM_ReadCapturedValue(&g_timx_cap_chy_handle,TIM_CHANNEL_1);/*获取当前的捕获值*/
                TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1);/*一定清楚原来的设置！！*/
                TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);/*把定时器二通道一改为上升沿捕获*/
                
            }
            else/*还未开始，第一次捕获到了上升沿*/
            {
                g_timxchp_cap_sta = 0;
                g_timxchy_cap_val = 0;                                          /*清空*/
                g_timxchp_cap_sta |= 0X40;                                      /*标记捕获到了上升沿*/
                __HAL_TIM_DISABLE(&g_timx_cap_chy_handle);                      /*关闭定时器2*/
                __HAL_TIM_SET_COUNTER(&g_timx_cap_chy_handle,0);                /*定时器2清零*/
                TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1);/*一定清楚原来的设置！！*/
                TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);/*把定时器二通道一改为下降沿捕获*/
                __HAL_TIM_ENABLE(&g_timx_cap_chy_handle);                       /*使能定时器2*/
            }
        }
    }
        
}
/*定时器更新中断回调函数*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim ->Instance ==TIM3)
    {
        if ((g_timxchp_cap_sta & 0X80) == 0)                                    /*还未成功捕获高电平脉冲*/
        {
            if((g_timxchp_cap_sta & 0X40))                                      /*已经捕获到高电平了*/
            {
                if((g_timxchp_cap_sta & 0X3F) == 0X3F )                                  /*捕获的高电平太长了*/
                {
                    TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1);/*一定清楚原来的设置！！*/
                    TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);/*把定时器二通道一改为上升沿捕获*/
                    g_timxchp_cap_sta |= 0X80;
                    g_timxchy_cap_val = 0XFFFF;
                }
            }
               else/*累计定时器溢出次数*/
               {
                   g_timxchp_cap_sta++;
               }
        }
    }
}







=======
#include "./BSP/TIMER/gtim.h"


TIM_HandleTypeDef g_timx_cap_chy_handle;


/*通用定时器输入捕获初始化函数*/
void gtim_timx_pwm_chy_init(uint16_t arr,uint16_t psc)
{
    TIM_IC_InitTypeDef timx_ic_cap_chy = {0};
    
    g_timx_cap_chy_handle.Instance =TIM3;                                       /*寄存器基地址*/
    g_timx_cap_chy_handle.Init.Prescaler =psc;                                  /*预分频系数*/
    g_timx_cap_chy_handle.Init.Period = arr;                                    /*自动重装载值*/
    g_timx_cap_chy_handle.Init.CounterMode=TIM_COUNTERMODE_UP;                  /*递增计数模式*/
    g_timx_cap_chy_handle.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_IC_Init(&g_timx_cap_chy_handle);
    
    timx_ic_cap_chy.ICPolarity =TIM_ICPOLARITY_RISING;                          /*上升沿捕获*/
    timx_ic_cap_chy.ICSelection = TIM_ICSELECTION_DIRECTTI;                     /*映射到TI1上*/
    timx_ic_cap_chy.ICPrescaler =TIM_ICPSC_DIV1;                                /*配置输入分频系数（这里是不分频）*/
    timx_ic_cap_chy.ICFilter = 0;                                               /*配置输入滤波器（这里是不滤波）*/
    HAL_TIM_IC_ConfigChannel(&g_timx_cap_chy_handle, &timx_ic_cap_chy,TIM_CHANNEL_1);
    
    __HAL_TIM_ENABLE_IT(&g_timx_cap_chy_handle,TIM_IT_UPDATE);
    HAL_TIM_IC_Start_IT(&g_timx_cap_chy_handle, TIM_CHANNEL_1);
}


/*定时器输入捕获 MSP初始化函数*/
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
  if(htim ->Instance == TIM3)
  {
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    __HAL_RCC_TIM3_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    gpio_init_struct.Pin=GPIO_PIN_6;
    gpio_init_struct.Mode=GPIO_MODE_AF_PP;                                      /*推挽输出（也可以读取输入信号）*/
    gpio_init_struct.Pull=GPIO_PULLUP;
    gpio_init_struct.Speed=GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);

    HAL_NVIC_SetPriority(TIM3_IRQn,0,0);                                       /*配置中断优先级*/
    HAL_NVIC_EnableIRQ(TIM3_IRQn);                                             /*开启ITMX中断*/
   }
}

/*输入捕获状态（g_timxchp_cap_sta）：
 *位【7】  ：=0（）时，说明没有成功捕获；=1（），说明成功捕获
 *位【6】  ：=0，说明没有捕获；= 1时说明已经成功捕获到高电平
 *位【0~5】：捕获高电平之后溢出的次数，总共可以记63次
*/


uint8_t g_timxchp_cap_sta = 0;                                                  /* 输入捕获状态 */
uint16_t g_timxchy_cap_val = 0;                                                 /* 输入捕获值 */

/*定时器3中断服务函数*/
void TIM3_IRQHandler (void)
{
    HAL_TIM_IRQHandler(&g_timx_cap_chy_handle);
}

/*定时输入捕获中断处理回调函数*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{ 
    if (htim->Instance == TIM3)
    {
        if ((g_timxchp_cap_sta & 0X80) == 0)                                    /*代表寄存器的位【7】 代表还没成功捕获*/
        {
            if((g_timxchp_cap_sta & 0X40))                                      /*捕获到下降沿 （因为上次捕获到是高电平上升沿，所以下一次的捕获到的是下降沿）*/
            {
                g_timxchp_cap_sta |= 0X80;                                      /*把位【7】置1，标记成功捕获到一次高电平脉宽*/
                g_timxchy_cap_val = HAL_TIM_ReadCapturedValue(&g_timx_cap_chy_handle,TIM_CHANNEL_1);/*获取当前的捕获值*/
                TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1);/*一定清楚原来的设置！！*/
                TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);/*把定时器二通道一改为上升沿捕获*/
                
            }
            else/*还未开始，第一次捕获到了上升沿*/
            {
                g_timxchp_cap_sta = 0;
                g_timxchy_cap_val = 0;                                          /*清空*/
                g_timxchp_cap_sta |= 0X40;                                      /*标记捕获到了上升沿*/
                __HAL_TIM_DISABLE(&g_timx_cap_chy_handle);                      /*关闭定时器2*/
                __HAL_TIM_SET_COUNTER(&g_timx_cap_chy_handle,0);                /*定时器2清零*/
                TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1);/*一定清楚原来的设置！！*/
                TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);/*把定时器二通道一改为下降沿捕获*/
                __HAL_TIM_ENABLE(&g_timx_cap_chy_handle);                       /*使能定时器2*/
            }
        }
    }
        
}
/*定时器更新中断回调函数*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim ->Instance ==TIM3)
    {
        if ((g_timxchp_cap_sta & 0X80) == 0)                                    /*还未成功捕获高电平脉冲*/
        {
            if((g_timxchp_cap_sta & 0X40))                                      /*已经捕获到高电平了*/
            {
                if((g_timxchp_cap_sta & 0X3F) == 0X3F )                                  /*捕获的高电平太长了*/
                {
                    TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1);/*一定清楚原来的设置！！*/
                    TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);/*把定时器二通道一改为上升沿捕获*/
                    g_timxchp_cap_sta |= 0X80;
                    g_timxchy_cap_val = 0XFFFF;
                }
            }
               else/*累计定时器溢出次数*/
               {
                   g_timxchp_cap_sta++;
               }
        }
    }
}







>>>>>>> 00ac74e (9.6)
