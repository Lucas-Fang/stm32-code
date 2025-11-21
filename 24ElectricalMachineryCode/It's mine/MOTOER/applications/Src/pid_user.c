#include "pid_user.h"

extern motor_measure_t motor_can1[8];                 /*八个电机各自的各项参数*/

pid_type_def pid_v_1[8],pid_pos_1[8];									/*八个电机各自的pid各项参数,（速度环的，位置环的）*/
pid_type_def pid_v_2[8],pid_pos_2[8];

//3508参数
float motor_speed_3508_pid[3] = {10, 0.1, 0};					//速度环
float motor_position_3508_pid[3] = {0.1, 0, 1};		  	//位置环
//2006参数
float motor_speed_2006_pid[3] = {9, 0.1, 0};					//速度环
float motor_position_2006_pid[3] = {0.2, 0, 0};				//位置环
	

#define LimitMax(input, max)   \
    {                          \
        if (input > max)       \
        {                      \
            input = max;       \
        }                      \
        else if (input < -max) \
        {                      \
            input = -max;      \
        }                      \
    }

		
		
		//PID初始化
void PID_devices_Init(void)
{
	for(int i=0;i<4;i++)
	{
    PID_init(&pid_v_1[i], PID_POSITION, motor_speed_3508_pid, 10000, 6000);/*前四个电机的pid各项参数，pid模式，速度环pid的比例微分积分三参，总限幅，积分限幅*/
		PID_init(&pid_pos_1[i], PID_POSITION, motor_position_3508_pid, 400, 300);/*前四个电机的pid各项参数，pid模式，位置环pid的比例微分积分三参，总限幅，积分限幅*/
		
		PID_init(&pid_v_2[i], PID_POSITION, motor_speed_3508_pid, 10000, 6000);
		PID_init(&pid_pos_2[i], PID_POSITION, motor_position_3508_pid, 1500, 300);
	}
	
	for(int i=4;i<8;i++)
	{																																							/*后面四个电机的*/
    PID_init(&pid_v_1[i], PID_POSITION, motor_speed_3508_pid, 10000, 6000);
		PID_init(&pid_pos_1[i], PID_POSITION, motor_position_3508_pid, 400, 300);
		
		PID_init(&pid_v_2[i], PID_POSITION, motor_speed_3508_pid, 10000, 6000);
		PID_init(&pid_pos_2[i], PID_POSITION, motor_position_3508_pid, 400, 300);
	}
}


float PID_velocity_realize_1(float set_speed,int i)     											/*速度环（期望速度，电机序号）*/
{
		PID_calc(&pid_v_1[i-1],motor_can1[i-1].speed_rpm , set_speed);						/*调用pid计算函数（电机有关pid计算的各项参数，电机当前速度，期望速度）*/
		return pid_v_1[i-1].out;																									/*返回值*/
}

float PID_position_realize_1(float set_pos,int i)															/*位置环 （期望位置，电机序号）(目标角度值0-8191，电调ID)*/
{

		PID_calc(&pid_pos_1[i-1],motor_can1[i-1].total_angle , set_pos);					/*调用pid计算函数（电机有关pid计算的各项参数，电机当前位置，期望位置）*/
		return pid_pos_1[i-1].out;																								/*返回值*/
}

float pid_call_1(float position,int i)																				/*PID双环 外环位置 内环速度*/
{
		return PID_velocity_realize_1(PID_position_realize_1(position,i),i);			/*位置环返回的参数作为速度环的入口参数（也就是期望速度）*/
}

/*





速度环：传入电机当前的参数，设置好预期的参数，pid计算函数里面比较这两个参数的大小，算出差值，
通过计算之后在电机驱动函数里面用，返回电流值的大小来控制速度的快慢，以达到期望的速度。

位置环：传入当前电机所在的位置，设置好希望电机达到的位置，pid计算函数里面计算这两个参数的差，
在电机驱动函数里面使用时，返回电流值以让电机转动达到期望的位置

双环：外环位置环，传入期望位置，通过位置环的控制电机需要达到的速度，此数值作为电机速度环的期望值，
再通过速度环的计算返回最终控制电机该有的电流传入电机驱动函数以驱动电机。





*/



