#include "pid_user.h"
#include "pid.h"
#include "N5065_speed.h"
#include <cstdint>

/*PID����������*/
PID_Controller pid_controller;
/***************/
extern motor_measure N5065[2];
//PID�������(�ṹ��)
pid_type_def pid_v_1[2];

//���PID����
fp32 motor_speed_5065_pid[3] = {0.4, 0.002, 0.5};		
fp32 motor_position_5065_pid[3] = {3, 0, 2};


/**
 * @brief       PID�豸��ʼ��
 * @param       void
 * @retval      void
 * @note        ���ｫ���е�PID�豸�Ĳ������г�ʼ��������Kp,Ki,Kd,I_limit(�����޷�),O_limit(���޷�)���������,����ֵ������pid_type_def����С�
 */
void PID_Controller::All_Device_Init(void)
{
	//����PID
	for(int i=0;i<4;i++)
	{
    	this->core.PID_Init(&pid_v_1[i], PID_POSITION, motor_speed_5065_pid, 700, 200);
		// this->core.PID_Init(&pid_pos_1[i], PID_POSITION, motor_position_5065_pid, 3000, 300);
	}

}

int32_t PID_Controller::CAN_MOTOR::N5065_Velocity_Realize(fp32 set_speed,uint8_t i)
{
	int16_t last_pid_out = 0;
	pid_controller.core.PID_Calc(&pid_v_1[i-1], N5065[i-1].speed_filtered, set_speed);

	if (pid_v_1[i-1].out < 0) {
		last_pid_out --;
		return last_pid_out;
	}
	if (pid_v_1[i-1].out > 0) {
	
		last_pid_out = pid_v_1[i-1].out;
	}
	return pid_v_1[i-1].out;
}

