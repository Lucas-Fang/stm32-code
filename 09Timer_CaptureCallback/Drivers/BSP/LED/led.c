<<<<<<< HEAD
#include "./BSP/LED/led.h"


//初始化
void led_init (void)
{

    GPIO_InitTypeDef gpio_init_struct = {0};
    
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    gpio_init_struct.Pin=GPIO_PIN_13;
    gpio_init_struct.Mode=GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Speed=GPIO_SPEED_FREQ_LOW;
    
    HAL_GPIO_Init(GPIOC, &gpio_init_struct);


    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
    
    
    
    GPIO_InitTypeDef gpio_init_struct0 = {0};
    
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    gpio_init_struct0.Pin=GPIO_PIN_1;
    gpio_init_struct0.Mode=GPIO_MODE_OUTPUT_PP;
    gpio_init_struct0.Speed=GPIO_SPEED_FREQ_HIGH;
    
    HAL_GPIO_Init(GPIOA, &gpio_init_struct0);


    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
}
=======
#include "./BSP/LED/led.h"


//初始化
void led_init (void)
{

    GPIO_InitTypeDef gpio_init_struct = {0};
    
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    gpio_init_struct.Pin=GPIO_PIN_13;
    gpio_init_struct.Mode=GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Speed=GPIO_SPEED_FREQ_LOW;
    
    HAL_GPIO_Init(GPIOC, &gpio_init_struct);


    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
    
    
    
    GPIO_InitTypeDef gpio_init_struct0 = {0};
    
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    gpio_init_struct0.Pin=GPIO_PIN_1;
    gpio_init_struct0.Mode=GPIO_MODE_OUTPUT_PP;
    gpio_init_struct0.Speed=GPIO_SPEED_FREQ_HIGH;
    
    HAL_GPIO_Init(GPIOA, &gpio_init_struct0);


    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
}
>>>>>>> 00ac74e (9.6)
