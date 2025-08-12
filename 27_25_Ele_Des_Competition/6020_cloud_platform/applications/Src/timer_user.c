#include "timer_user.h"
#include <stdint.h>
#include <stdlib.h> 


extern int16_t delta_x,delta_y;
extern uint8_t openmv_buffer[9];
extern uint16_t pos_x,pos_y;
/**
 * @brief       �ص���������ʱ���жϷ���������
 * @param       htim�������жϵĶ�ʱ�����
 * @retval      void
 * @note        �ú������жϹ������������ã������û�ȥ���á���Ϊһ����������������C++��Ҫ�ڸú���ǰ�����extern "C"����ֱ����extern "C"{}������
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM9)  //����Ϊ1ms
	{
		IMU_RequestData(&hcan2,0x01,0x03);
		// Receive_OpenMV_data(openmv_buffer);
	}
}
