#include "timer_user.h"
#include "chassic.h"
#include "stm32f103xb.h"
#include "stm32f1xx_hal_tim.h"
#include "tim.h"

#define P 0.5

ROBOT::CHASSIC::Motor motor1;
ROBOT::CHASSIC::Motor motor2;



extern "C"
/**
 * @brief       回调函数，定时器中断服务函数调用
 * @param       htim：触发中断的定时器句柄
 * @retval      void
 * @note        该函数由中断公共服务函数调用，不用用户去调用。且为一个弱函数，所以在C++中要在该函数前面加上extern "C"，或直接用extern "C"{}括起来
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM1)  //定时器溢出中断周期为10ms
	{
		robot.chassic.encoder.Encoder_Obtain();
		robot.chassic.encoder.Encoder_filtering();
		Motor_Move();
	}


//编码器溢出中断
	if(htim->Instance == TIM2)
	{

	}
	if(htim->Instance == TIM3)
	{

	}

}

void ROBOT::CHASSIC::ENCODER::Encoder_Obtain()
{
   if (__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim2)) /*判断编码器是正转还是反转*/
   {
     motor1.Encoder = __HAL_TIM_GetCounter(&htim2) -65535;         /* CR1的DIR位是1，就是向下溢出，则反转*/
     __HAL_TIM_SetCounter(&htim2, 0);

   } 
   else 																 /*CR1的DIR位是0，就是向上溢出，则正转*/
   {
     motor1.Encoder =__HAL_TIM_GetCounter(&htim2);               
     __HAL_TIM_SetCounter(&htim2, 0);

   }

   if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3))
   {
     motor2.Encoder = __HAL_TIM_GetCounter(&htim3) - 65535;
	 __HAL_TIM_SetCounter(&htim3, 0);
   }
   else
   {
     motor2.Encoder = __HAL_TIM_GetCounter(&htim3);	
	 __HAL_TIM_SetCounter(&htim3, 0);
   }
}

void ROBOT::CHASSIC::ENCODER::Encoder_filtering()
{
	if (motor1.Encoder == -65535)
	{
		motor1.Encoder=0;
	}
	if(motor2.Encoder == -65535)
	{
		motor2.Encoder=0;
	}

	motor1.Encoder=P*motor1.Encoder+(1-P)*motor1.last_speed;
	motor1.last_speed=motor1.Encoder;
	motor2.Encoder=P*motor2.Encoder+(1-P)*motor2.last_speed;
	motor2.last_speed=motor2.Encoder;

}