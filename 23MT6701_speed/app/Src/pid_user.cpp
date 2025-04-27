#include "pid_user.h"
#include "pid.h"


/*PID控制器对象*/
PID_Controller pid_controller;
/***************/
extern Motor_Measure N5065_Data[2];
//PID参数句柄(结构体)
pid_type_def pid_v_1[2];

//电机PID三参
fp32 motor_speed_5065_pid[3] = {6, 0 , 3};//底盘3508参数
fp32 motor_position_5065_pid[3] = {3, 0, 2};


/**
 * @brief       PID设备初始化
 * @param       void
 * @retval      void
 * @note        这里将所有的PID设备的参数进行初始化，包括Kp,Ki,Kd,I_limit(积分限幅),O_limit(总限幅)共五个参数,将其值保存至pid_type_def句柄中。
 */
void PID_Controller::All_Device_Init(void)
{
	//底盘PID
	for(int i=0;i<4;i++)
	{
    	this->core.PID_Init(&pid_v_1[i], PID_POSITION, motor_speed_5065_pid, 10000, 6000);
		// this->core.PID_Init(&pid_pos_1[i], PID_POSITION, motor_position_5065_pid, 3000, 300);
	}

}

fp32 PID_Controller::CAN_MOTOR::N5065_Velocity_Realize(fp32 set_speed,uint8_t i)
{
	pid_controller.core.PID_Calc(&pid_v_1[i-1], N5065_Data[i-1].speed_rpm, set_speed);
	return pid_v_1[i-1].out;
}

