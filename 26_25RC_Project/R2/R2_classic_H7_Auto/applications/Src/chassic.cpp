#include "chassic.h"
#include "DR16.h"
#include "fdcan_receive.h"
#include "pid.h"
#include "pid_user.h"
#include <math.h>
#include "cmsis_os.h"
#include "Communition.h"
#include "my_task.h"
/************************** 

����˳��CANid����    
          1��1��      2��2��
                3��3��        
*/

extern Rxbuffer all_rxbuff;
ROBOT robot;


void ROBOT::CHASSIC::Omni_Move_Calc()
{
//������������ȫ��
this->Motor_Speed_Target[0]=-Chassic_Move_Data.vy *sin(PI/6.0f)+Chassic_Move_Data.vx *cos(PI/6.0f) -Chassic_Move_Data.vomega;
this->Motor_Speed_Target[1]=-Chassic_Move_Data.vy *sin(PI/6.0f)-Chassic_Move_Data.vx *cos(PI/6.0f) -Chassic_Move_Data.vomega;
this->Motor_Speed_Target[2]= Chassic_Move_Data.vy-0-Chassic_Move_Data.vomega;

}

void ROBOT::CHASSIC::Chassic_Move()
{
    fp32 v_3508[4]={0};

    v_3508[0]=pid_controller.can_motor.CAN1_Velocity_Realize(Motor_Speed_Target[0], 1);
    v_3508[1]=pid_controller.can_motor.CAN1_Velocity_Realize(Motor_Speed_Target[1], 2);
    v_3508[2]=pid_controller.can_motor.CAN1_Velocity_Realize(Motor_Speed_Target[2], 3);

    can_bus.cmd.FDCAN1_Front(v_3508[0], v_3508[1], v_3508[2], 0);
		
}
void ROBOT::CHASSIC::Chassic_Mode()
{
  //�ֱ�
    if (all_rxbuff.s2 == MANUAL_MODE)
    {
       this->Chassic_Move_Data.vx=6.0*(all_rxbuff.remote_sense[3]-1024);
       this->Chassic_Move_Data.vy=-6.0*(all_rxbuff.remote_sense[2]-1024);
       this->Chassic_Move_Data.vomega=-3.5 * (all_rxbuff.remote_sense[0]-1024);
    }
    //��λ��
    if (all_rxbuff.s2 == AUTO_MODE)
    {
		// robot.chassic.Chassic_Move_Data.vx = 
        //     robot.upper_data[0]*(60/(2*PI*WHEEL_Radius))*3591.0/187.0;
        // robot.chassic.Chassic_Move_Data.vy = 
        //     robot.upper_data[1]*(60/(2*PI*WHEEL_Radius))*3591.0/187.0;
        // robot.chassic.Chassic_Move_Data.vomega = 
        //     robot.upper_data[2]*Radius*(60/(2*PI*WHEEL_Radius)*3591.0/187.0);
    }

}

/**
 * @brief  ����ת��Ϊ�Ƕ�
 * @param  rad ����ֵ
 * @retval deg �Ƕ�ֵ
 * @attention
 */
fp32 ROBOT::CHASSIC::rad2deg(fp32 rad)
{
	fp32 deg;
	deg = (fp32)(rad * (180.0f / PI));
	return deg;
}