#include "./BSP/EXTI/exti.h"
#include "./SYSTEM/delay/delay.h"

//��ʼ��
void led_init (void)
{
            //LED
    GPIO_InitTypeDef gpio_init_struct={0};
    
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    gpio_init_struct.Pin=GPIO_PIN_13;
    gpio_init_struct.Mode=GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Speed=GPIO_SPEED_FREQ_LOW;
    gpio_init_struct.Pull=GPIO_PULLUP;
    
    HAL_GPIO_Init(GPIOC, &gpio_init_struct);


    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
}



void exti_init (void)
{

    
    
        //ѭ��ģ������
    GPIO_InitTypeDef gpio_init_struct_2={0};
    
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    gpio_init_struct_2.Pin=GPIO_PIN_1;
    gpio_init_struct_2.Mode=GPIO_MODE_IT_RISING_FALLING;       //�ⲿ�ж�����/�½��ش���
    gpio_init_struct_2.Speed=GPIO_SPEED_FREQ_LOW;
    gpio_init_struct_2.Pull=GPIO_PULLUP;
    
    HAL_GPIO_Init(GPIOB, &gpio_init_struct_2);
    
    
    HAL_NVIC_SetPriority(EXTI1_IRQn,0,0);               //�����ж����ȼ�����ռ���ȼ�����Ӧ���ȼ�������ԽС���ȼ�Խ��
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);                     //ʹ���ж�
    

}

void EXTI1_IRQHandler(void)                             //�жϷ���������startup�ļ����汻�궨�壩
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);               //�жϹ���������   ���ûص�������Callback������������Ǹ���
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);               //HALĬ���������ж��ڴ���ص����˳�ʱ������һ���жϣ����ⰴ�������󴥷�
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)          //�ص���������Ҫ�û��Լ�д   �����ж�ʱִ��ʲô���
{
    delay_ms(20);                                       /*����*/
    if(GPIO_Pin == GPIO_PIN_1)                          //�ж���0-15��һ���ж��߲������ж� ȷ���Ƿ���������Ų������ж�
    {
        if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)==0)       //�ж��ǲ������źŴ�ѭ��ģ�鴫����
        {
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
            //HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);//��ת����  ʹ�ߵ͵�ƽ��ת
        }
        else 
        {
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
        }
    }
}




