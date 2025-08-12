#include "timer_user.h"
#include <stdint.h>
#include <stdlib.h> 


extern int16_t delta_x,delta_y;
extern uint8_t openmv_buffer[9];
extern uint16_t pos_x,pos_y;
/**
 * @brief       回调函数，定时器中断服务函数调用
 * @param       htim：触发中断的定时器句柄
 * @retval      void
 * @note        该函数由中断公共服务函数调用，不用用户去调用。且为一个弱函数，所以在C++中要在该函数前面加上extern "C"，或直接用extern "C"{}括起来
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM9)  //周期为1ms
	{
		IMU_RequestData(&hcan2,0x01,0x03);
		// Receive_OpenMV_data(openmv_buffer);
	}
}
