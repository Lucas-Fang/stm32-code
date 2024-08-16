/*

引脚关系：
PA0 PA1           PA2 PA3
前轮左            前轮右
 
PB12 PB13         PB14 PB15
后轮左(PA6)       后轮右(PA7)
  
*/

#include "chassic.h"


void Front_L(int16_t speed)
{
	if(speed>=0)
	{
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,speed);
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);
	}
	if(speed<0) 
	{
		speed=-speed;
		
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,0);
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,speed);
	}
}
/***************************************************/
void Front_R(int16_t speed)
{
	if(speed>=0)
	{
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,speed);
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);
	}
	if(speed<0) 
	{
		speed=-speed;
		
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,speed);
	}
}
/***************************************************/
void Back_L(int16_t speed)
{
	if(speed>=0)
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
	}
	if(speed<0) 
	{
		speed=-speed;
		
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);
	}
	
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,speed);
}
/******************************************************/
void Back_R(int16_t speed)
{
	if(speed>=0)
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET);
	}
	if(speed<0) 
	{
		speed=-speed;
		
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET);
	}
	
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,speed);
}







