#include "./BSP/EXTI/exti.h"
#include "./SYSTEM/delay/delay.h"

//初始化
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

    
    
        //循迹模块引脚
    GPIO_InitTypeDef gpio_init_struct_2={0};
    
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    gpio_init_struct_2.Pin=GPIO_PIN_1;
    gpio_init_struct_2.Mode=GPIO_MODE_IT_RISING_FALLING;       //外部中断上升/下降沿触发
    gpio_init_struct_2.Speed=GPIO_SPEED_FREQ_LOW;
    gpio_init_struct_2.Pull=GPIO_PULLUP;
    
    HAL_GPIO_Init(GPIOB, &gpio_init_struct_2);
    
    
    HAL_NVIC_SetPriority(EXTI1_IRQn,0,0);               //设置中断优先级（抢占优先级，响应优先级）数字越小优先级越高
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);                     //使能中断
    

}

void EXTI1_IRQHandler(void)                             //中断服务函数（在startup文件里面被宏定义）
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);               //中断公共服务函数   调用回调函数（Callback函数（下面的那个）
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);               //HAL默认先清理中断在处理回调，退出时再清理一次中断，避免按键抖动误触发
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)          //回调函数（需要用户自己写   产生中断时执行什么命令）
{
    delay_ms(20);                                       /*消抖*/
    if(GPIO_Pin == GPIO_PIN_1)                          //判断是0-15哪一个中断线产生的中断 确认是否是这个引脚产生的中断
    {
        if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)==0)       //判断是不是有信号从循迹模块传来了
        {
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
            //HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);//反转函数  使高低电平翻转
        }
        else 
        {
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
        }
    }
}




