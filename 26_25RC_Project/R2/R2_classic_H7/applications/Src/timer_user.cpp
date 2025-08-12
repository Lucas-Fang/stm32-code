#include "timer_user.h"
#include "chassic.h"
#include "fdcan_receive.h"
#include "Communition.h"
#include "my_task.h"
#include "pid.h"
#include "pid_user.h"
#include "MT6701.h"
#include "DR16.h"
#include "bsp_usart.h"

extern Rxbuffer all_rxbuff;
extern int16_t N5065_traget_speed[2];
extern remote_data receive_data;


extern "C"
/**
 * @brief       �ص���������ʱ���жϷ���������
 * @param       htim�������жϵĶ�ʱ�����
 * @retval      void
 * @note        �ú������жϹ������������ã������û�ȥ���á���Ϊһ����������������C++��Ҫ�ڸú���ǰ�����extern "C"����ֱ����extern "C"{}������
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM7)  //����Ϊ1ms
	{
        //��̨�Ƕ�2500-5850 / -34.66�� - 46��
        Get_Remote_Date();
        MT6701_ReadAngle(&hi2c2);
        BlueTooth_Send_Data(4);
        if (robot.rod_state.bottom == true)  ROD_BOTTOM_PUSH;
        if (robot.rod_state.bottom == false) ROD_BOTTOM_BACK;


        if (robot.stop == true)  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
        if (robot.stop == false) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
        N5065_traget_speed[0] = N5065_traget_speed[1] = receive_data.ch[0];
        VESC_CAN_Speedrpm(0x0311,N5065_traget_speed[0]);
        VESC_CAN_Speedrpm(0x0346,N5065_traget_speed[1]);

        if (all_rxbuff.s2 == MANUAL_MODE){
        can_bus.cmd.FDCAN1_Behind(
            pid_controller.can_motor.CAN1_VP_Dual_Loop_Realize(robot.target_ball_angle, 5,PID_EXTERNAL_POS),
        	0,
        	0,
        	0);
        }
        if (all_rxbuff.s2 != MANUAL_MODE){
            can_bus.cmd.FDCAN1_Behind(
            pid_controller.can_motor.CAN1_VP_Dual_Loop_Realize(robot.BT_target_angle, 5,PID_EXTERNAL_POS),
        	0,
        	0,
        	0);


	}
}
}
