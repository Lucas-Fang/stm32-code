<<<<<<< HEAD
#include "./BSP/TIMER/gtim.h"


TIM_HandleTypeDef g_timx_cap_chy_handle;


/*ͨ�ö�ʱ�����벶���ʼ������*/
void gtim_timx_pwm_chy_init(uint16_t arr,uint16_t psc)
{
    TIM_IC_InitTypeDef timx_ic_cap_chy = {0};
    
    g_timx_cap_chy_handle.Instance =TIM3;                                       /*�Ĵ�������ַ*/
    g_timx_cap_chy_handle.Init.Prescaler =psc;                                  /*Ԥ��Ƶϵ��*/
    g_timx_cap_chy_handle.Init.Period = arr;                                    /*�Զ���װ��ֵ*/
    g_timx_cap_chy_handle.Init.CounterMode=TIM_COUNTERMODE_UP;                  /*��������ģʽ*/
    g_timx_cap_chy_handle.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_IC_Init(&g_timx_cap_chy_handle);
    
    timx_ic_cap_chy.ICPolarity =TIM_ICPOLARITY_RISING;                          /*�����ز���*/
    timx_ic_cap_chy.ICSelection = TIM_ICSELECTION_DIRECTTI;                     /*ӳ�䵽TI1��*/
    timx_ic_cap_chy.ICPrescaler =TIM_ICPSC_DIV1;                                /*���������Ƶϵ���������ǲ���Ƶ��*/
    timx_ic_cap_chy.ICFilter = 0;                                               /*���������˲����������ǲ��˲���*/
    HAL_TIM_IC_ConfigChannel(&g_timx_cap_chy_handle, &timx_ic_cap_chy,TIM_CHANNEL_1);
    
    __HAL_TIM_ENABLE_IT(&g_timx_cap_chy_handle,TIM_IT_UPDATE);
    HAL_TIM_IC_Start_IT(&g_timx_cap_chy_handle, TIM_CHANNEL_1);
}


/*��ʱ�����벶�� MSP��ʼ������*/
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
  if(htim ->Instance == TIM3)
  {
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    __HAL_RCC_TIM3_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    gpio_init_struct.Pin=GPIO_PIN_6;
    gpio_init_struct.Mode=GPIO_MODE_AF_PP;                                      /*���������Ҳ���Զ�ȡ�����źţ�*/
    gpio_init_struct.Pull=GPIO_PULLUP;
    gpio_init_struct.Speed=GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);

    HAL_NVIC_SetPriority(TIM3_IRQn,0,0);                                       /*�����ж����ȼ�*/
    HAL_NVIC_EnableIRQ(TIM3_IRQn);                                             /*����ITMX�ж�*/
   }
}

/*���벶��״̬��g_timxchp_cap_sta����
 *λ��7��  ��=0����ʱ��˵��û�гɹ�����=1������˵���ɹ�����
 *λ��6��  ��=0��˵��û�в���= 1ʱ˵���Ѿ��ɹ����񵽸ߵ�ƽ
 *λ��0~5��������ߵ�ƽ֮������Ĵ������ܹ����Լ�63��
*/


uint8_t g_timxchp_cap_sta = 0;                                                  /* ���벶��״̬ */
uint16_t g_timxchy_cap_val = 0;                                                 /* ���벶��ֵ */

/*��ʱ��3�жϷ�����*/
void TIM3_IRQHandler (void)
{
    HAL_TIM_IRQHandler(&g_timx_cap_chy_handle);
}

/*��ʱ���벶���жϴ���ص�����*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{ 
    if (htim->Instance == TIM3)
    {
        if ((g_timxchp_cap_sta & 0X80) == 0)                                    /*����Ĵ�����λ��7�� ����û�ɹ�����*/
        {
            if((g_timxchp_cap_sta & 0X40))                                      /*�����½��� ����Ϊ�ϴβ����Ǹߵ�ƽ�����أ�������һ�εĲ��񵽵����½��أ�*/
            {
                g_timxchp_cap_sta |= 0X80;                                      /*��λ��7����1����ǳɹ�����һ�θߵ�ƽ����*/
                g_timxchy_cap_val = HAL_TIM_ReadCapturedValue(&g_timx_cap_chy_handle,TIM_CHANNEL_1);/*��ȡ��ǰ�Ĳ���ֵ*/
                TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1);/*һ�����ԭ�������ã���*/
                TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);/*�Ѷ�ʱ����ͨ��һ��Ϊ�����ز���*/
                
            }
            else/*��δ��ʼ����һ�β�����������*/
            {
                g_timxchp_cap_sta = 0;
                g_timxchy_cap_val = 0;                                          /*���*/
                g_timxchp_cap_sta |= 0X40;                                      /*��ǲ�����������*/
                __HAL_TIM_DISABLE(&g_timx_cap_chy_handle);                      /*�رն�ʱ��2*/
                __HAL_TIM_SET_COUNTER(&g_timx_cap_chy_handle,0);                /*��ʱ��2����*/
                TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1);/*һ�����ԭ�������ã���*/
                TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);/*�Ѷ�ʱ����ͨ��һ��Ϊ�½��ز���*/
                __HAL_TIM_ENABLE(&g_timx_cap_chy_handle);                       /*ʹ�ܶ�ʱ��2*/
            }
        }
    }
        
}
/*��ʱ�������жϻص�����*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim ->Instance ==TIM3)
    {
        if ((g_timxchp_cap_sta & 0X80) == 0)                                    /*��δ�ɹ�����ߵ�ƽ����*/
        {
            if((g_timxchp_cap_sta & 0X40))                                      /*�Ѿ����񵽸ߵ�ƽ��*/
            {
                if((g_timxchp_cap_sta & 0X3F) == 0X3F )                                  /*����ĸߵ�ƽ̫����*/
                {
                    TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1);/*һ�����ԭ�������ã���*/
                    TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);/*�Ѷ�ʱ����ͨ��һ��Ϊ�����ز���*/
                    g_timxchp_cap_sta |= 0X80;
                    g_timxchy_cap_val = 0XFFFF;
                }
            }
               else/*�ۼƶ�ʱ���������*/
               {
                   g_timxchp_cap_sta++;
               }
        }
    }
}







=======
#include "./BSP/TIMER/gtim.h"


TIM_HandleTypeDef g_timx_cap_chy_handle;


/*ͨ�ö�ʱ�����벶���ʼ������*/
void gtim_timx_pwm_chy_init(uint16_t arr,uint16_t psc)
{
    TIM_IC_InitTypeDef timx_ic_cap_chy = {0};
    
    g_timx_cap_chy_handle.Instance =TIM3;                                       /*�Ĵ�������ַ*/
    g_timx_cap_chy_handle.Init.Prescaler =psc;                                  /*Ԥ��Ƶϵ��*/
    g_timx_cap_chy_handle.Init.Period = arr;                                    /*�Զ���װ��ֵ*/
    g_timx_cap_chy_handle.Init.CounterMode=TIM_COUNTERMODE_UP;                  /*��������ģʽ*/
    g_timx_cap_chy_handle.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_IC_Init(&g_timx_cap_chy_handle);
    
    timx_ic_cap_chy.ICPolarity =TIM_ICPOLARITY_RISING;                          /*�����ز���*/
    timx_ic_cap_chy.ICSelection = TIM_ICSELECTION_DIRECTTI;                     /*ӳ�䵽TI1��*/
    timx_ic_cap_chy.ICPrescaler =TIM_ICPSC_DIV1;                                /*���������Ƶϵ���������ǲ���Ƶ��*/
    timx_ic_cap_chy.ICFilter = 0;                                               /*���������˲����������ǲ��˲���*/
    HAL_TIM_IC_ConfigChannel(&g_timx_cap_chy_handle, &timx_ic_cap_chy,TIM_CHANNEL_1);
    
    __HAL_TIM_ENABLE_IT(&g_timx_cap_chy_handle,TIM_IT_UPDATE);
    HAL_TIM_IC_Start_IT(&g_timx_cap_chy_handle, TIM_CHANNEL_1);
}


/*��ʱ�����벶�� MSP��ʼ������*/
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
  if(htim ->Instance == TIM3)
  {
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    __HAL_RCC_TIM3_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    gpio_init_struct.Pin=GPIO_PIN_6;
    gpio_init_struct.Mode=GPIO_MODE_AF_PP;                                      /*���������Ҳ���Զ�ȡ�����źţ�*/
    gpio_init_struct.Pull=GPIO_PULLUP;
    gpio_init_struct.Speed=GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);

    HAL_NVIC_SetPriority(TIM3_IRQn,0,0);                                       /*�����ж����ȼ�*/
    HAL_NVIC_EnableIRQ(TIM3_IRQn);                                             /*����ITMX�ж�*/
   }
}

/*���벶��״̬��g_timxchp_cap_sta����
 *λ��7��  ��=0����ʱ��˵��û�гɹ�����=1������˵���ɹ�����
 *λ��6��  ��=0��˵��û�в���= 1ʱ˵���Ѿ��ɹ����񵽸ߵ�ƽ
 *λ��0~5��������ߵ�ƽ֮������Ĵ������ܹ����Լ�63��
*/


uint8_t g_timxchp_cap_sta = 0;                                                  /* ���벶��״̬ */
uint16_t g_timxchy_cap_val = 0;                                                 /* ���벶��ֵ */

/*��ʱ��3�жϷ�����*/
void TIM3_IRQHandler (void)
{
    HAL_TIM_IRQHandler(&g_timx_cap_chy_handle);
}

/*��ʱ���벶���жϴ���ص�����*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{ 
    if (htim->Instance == TIM3)
    {
        if ((g_timxchp_cap_sta & 0X80) == 0)                                    /*����Ĵ�����λ��7�� ����û�ɹ�����*/
        {
            if((g_timxchp_cap_sta & 0X40))                                      /*�����½��� ����Ϊ�ϴβ����Ǹߵ�ƽ�����أ�������һ�εĲ��񵽵����½��أ�*/
            {
                g_timxchp_cap_sta |= 0X80;                                      /*��λ��7����1����ǳɹ�����һ�θߵ�ƽ����*/
                g_timxchy_cap_val = HAL_TIM_ReadCapturedValue(&g_timx_cap_chy_handle,TIM_CHANNEL_1);/*��ȡ��ǰ�Ĳ���ֵ*/
                TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1);/*һ�����ԭ�������ã���*/
                TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);/*�Ѷ�ʱ����ͨ��һ��Ϊ�����ز���*/
                
            }
            else/*��δ��ʼ����һ�β�����������*/
            {
                g_timxchp_cap_sta = 0;
                g_timxchy_cap_val = 0;                                          /*���*/
                g_timxchp_cap_sta |= 0X40;                                      /*��ǲ�����������*/
                __HAL_TIM_DISABLE(&g_timx_cap_chy_handle);                      /*�رն�ʱ��2*/
                __HAL_TIM_SET_COUNTER(&g_timx_cap_chy_handle,0);                /*��ʱ��2����*/
                TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1);/*һ�����ԭ�������ã���*/
                TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);/*�Ѷ�ʱ����ͨ��һ��Ϊ�½��ز���*/
                __HAL_TIM_ENABLE(&g_timx_cap_chy_handle);                       /*ʹ�ܶ�ʱ��2*/
            }
        }
    }
        
}
/*��ʱ�������жϻص�����*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim ->Instance ==TIM3)
    {
        if ((g_timxchp_cap_sta & 0X80) == 0)                                    /*��δ�ɹ�����ߵ�ƽ����*/
        {
            if((g_timxchp_cap_sta & 0X40))                                      /*�Ѿ����񵽸ߵ�ƽ��*/
            {
                if((g_timxchp_cap_sta & 0X3F) == 0X3F )                                  /*����ĸߵ�ƽ̫����*/
                {
                    TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1);/*һ�����ԭ�������ã���*/
                    TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);/*�Ѷ�ʱ����ͨ��һ��Ϊ�����ز���*/
                    g_timxchp_cap_sta |= 0X80;
                    g_timxchy_cap_val = 0XFFFF;
                }
            }
               else/*�ۼƶ�ʱ���������*/
               {
                   g_timxchp_cap_sta++;
               }
        }
    }
}







>>>>>>> 00ac74e (9.6)
