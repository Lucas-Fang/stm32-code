#include "pid_user.h"


extern ROBOT robot;
extern ROBOT::CHASSIC::Euler euler;
pid_type_def pid_position_yaw;
fp32 yaw_pid[3]={0,0,0};




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
		
		
		
void PID_Device_Init()
{
	PID_init(&pid_position_yaw,PID_POSITION,yaw_pid,0,0);
}


fp32 PID_position_Yaw(fp32 set_angle)
{
	PID_calc(&pid_position_yaw,euler.yaw,set_angle);
	
	return pid_position_yaw.out;
}


