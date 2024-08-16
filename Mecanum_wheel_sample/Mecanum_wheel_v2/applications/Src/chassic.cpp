/*

���Ź�ϵ��
PA0 PA1           PA2 PA3
ǰ����            ǰ����
 
PB12 PB13         PB14 PB15
������(PA6)       ������(PA7)
  
*/

#include "chassic.h"

ROBOT robot;
ROBOT::CHASSIC::Euler euler;


extern remote_data receive_data;
extern HWT101CT_t hwt101ct;


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



void Motor_Move(void)
{
	int16_t pwm_x,pwm_y,pwm_z;
	
	euler.yaw= hwt101ct.Euler.yaw;

	pwm_x=receive_data.ch[0];
	pwm_y=receive_data.ch[1];
	// pwm_z=PID_position_Yaw(receive_data.ch[3]);
	
	robot.chassic.chassic_speed_calc(pwm_x,pwm_y,receive_data.ch[3]);

		Front_L(robot.chassic.Motor_Speed_Target[0]);
		Front_R(robot.chassic.Motor_Speed_Target[1]);
		Back_L(robot.chassic.Motor_Speed_Target[2]);
		Back_R(robot.chassic.Motor_Speed_Target[3]);
}



void ROBOT::CHASSIC::chassic_speed_calc(int16_t pwm_x,int16_t pwm_y,int16_t pwm_yaw)
{
	
	robot.chassic.Motor_Speed_Target[0]=pwm_y+pwm_x-pwm_yaw;
	robot.chassic.Motor_Speed_Target[1]=pwm_y-pwm_x+pwm_yaw;
	robot.chassic.Motor_Speed_Target[2]=pwm_y-pwm_x-pwm_yaw;
	robot.chassic.Motor_Speed_Target[3]=pwm_y+pwm_x+pwm_yaw;
	
}





