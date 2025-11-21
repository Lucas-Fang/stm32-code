#include "pid_user.h"
#include "can_receive.h"
#include "pid.h"
#include "chassic.h"
#include "struct_typedef.h"


extern ROBOT::CHASSIC::Euler euler;
/*PID控制器对象*/
PID_Controller pid_controller;
/***************/

//PID参数句柄(结构体)
pid_type_def pid_v_1[8],pid_pos_1[8];
pid_type_def pid_v_6020[3],pid_pos_6020[3];
pid_type_def pid_yaw;
//电机PID三参
fp32 motor_speed_3508_pid[3] = {10,0.01,1};//底盘3508参数
fp32 motor_position_3508_pid[3] = {0.2,0,1};
fp32 motor_speed_6020_pid[3]={9,0.001,0};		//底盘6020参数
fp32 motor_position_6020_pid[3]={2,0,5.5};

fp32 motor_yaw_pid[3] = {10,0.1,0};//yaw轴pid参数



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
    this->core.PID_Init(&pid_v_1[i], PID_POSITION, motor_speed_3508_pid, 10000, 5000);
	this->core.PID_Init(&pid_pos_1[i], PID_POSITION, motor_position_3508_pid, 500, 300);
	
	this->core.PID_Init(&pid_v_6020[i], PID_POSITION, motor_speed_6020_pid, 15000, 500);
	this->core.PID_Init(&pid_pos_6020[i], PID_POSITION, motor_position_6020_pid, 10000, 600);
	}

	this->core.PID_Init(&pid_yaw, PID_POSITION, motor_yaw_pid,500, 100);
}

/**
 * @brief       CAN1速度环
 * @param       set_speed：速度rpm
 * @param       i：以数组为序号的，也就是i=电调ID号-1
 * @retval      输出值
 * @note        输出值究竟是什么值，需要看该函数的输出值被当作了什么量
 */
fp32 PID_Controller::CAN_MOTOR::CAN1_Velocity_Realize(fp32 set_speed,int i)
{
	pid_controller.core.PID_Calc(&pid_v_1[i-1],can_bus.motor_can1[i-1].speed_rpm , set_speed);
	return pid_v_1[i-1].out;
}

/**
 * @brief       CAN1位置环
 * @param       set_pos：角度值，为相对角度值，请详看大疆说明书
 * @param       i：以数组为序号的，也就是i=电调ID号-1
 * @retval      输出值
 * @note        输出值究竟是什么值，需要看该函数的输出值被当作了什么量
 */
fp32 PID_Controller::CAN_MOTOR::CAN1_Position_Realize(fp32 set_pos,int i)
{
	pid_controller.core.PID_Calc(&pid_pos_1[i-1],can_bus.motor_can1[i-1].total_angle , set_pos);
	return pid_pos_1[i-1].out;
}

/**
 * @brief       CAN1电流速度双环
 * @param       set_pos：角度值，为相对角度值，请详看大疆说明书
 * @param       i：以数组为序号的，也就是i=电调ID号-1
 * @retval      输出值
 * @note        输出值究竟是什么值，需要看该函数的输出值被当作了什么量
 */
fp32 PID_Controller::CAN_MOTOR::CAN1_VP_Dual_Loop_Realize(fp32 set_pos,int i)
{
	return CAN1_Velocity_Realize(CAN1_Position_Realize(set_pos,i),i);
}


/**
 * @brief       6020速度环
 * @param       set_speed：速度值
 * @param       i：以数组为序号的，也就是i=电调ID号-1
 * @retval      输出值
 * @note        输出值究竟是什么值，需要看该函数的输出值被当作了什么量
 */

fp32 PID_Controller::CAN_MOTOR::GM6020_Velocity_Realize(fp32 set_speed,int i)
{
	pid_controller.core.PID_Calc(&pid_v_6020[i-1], can_bus.motor_6020[i-1].speed_rpm,set_speed);
	return pid_v_6020[i-1].out;
}

fp32 PID_Controller::CAN_MOTOR::GM6020_Position_Realize(fp32 set_pos,int i)
{
	if(set_pos<0)
	{
		set_pos+=8191;
	}
	pid_controller.core.PID_Calc(&pid_pos_6020[i-1], can_bus.motor_6020[i-1].angle, set_pos);
	return pid_pos_6020[i-1].out;
}

fp32 PID_Controller::CAN_MOTOR::GM6020_VP_Dual_Loop_Realize(fp32 set_pos,int i)
{
 return GM6020_Velocity_Realize(GM6020_Position_Realize(set_pos,  i), i);
}

/**
 * @brief       yaw轴pid
 * @param       set_pos：角度值-180-180
 * @retval      输出值
 * @note        输出值究竟是什么值，需要看该函数的输出值被当作了什么量
 */
fp32 PID_Controller::SENSORS::Yaw_Realize(fp32 set_yaw)
{
	pid_controller.core.PID_Calc(&pid_yaw, euler.yaw, set_yaw);
	return pid_yaw.out;
}