#include "pid_user.h"
#include "pid.h"

extern motor_measure_t motor_6020[8];
extern int16_t delta_x , delta_y;
extern imu_t imu;
extern float filtered_x,filtered_y;
pid_type_def pid_v_1[8];
pid_type_def pid_pos_x,pid_pos_y;
pid_type_def pid_yaw;

fp32 motor_speed_6020_pid[3] = {25,0, 5};

fp32 motor_position_x_6020_pid[3] = {0.4, 0.01, 1};
fp32 servo_motor_pos_y_pid[3] = {-0.1, -0.005, -0.1};

fp32 motor_yaw_6020_pid[3] = {10, 0.02, 1};



void PID_devices_Init(void)
{
	for(int i=0;i<4;i++)
	{
   		PID_init(&pid_v_1[i], PID_POSITION, motor_speed_6020_pid, 12000, 2000,0.5);
	}

	PID_init(&pid_pos_x, PID_POSITION, motor_position_x_6020_pid , 45, 20,4);
  	PID_init(&pid_pos_y, PID_POSITION, servo_motor_pos_y_pid  , 100, 50,4);
	PID_init(&pid_yaw, PID_POSITION, motor_yaw_6020_pid, 5000, 3500, 0.1);

}


float PID_velocity_realize_1(float set_speed,int i)
{
		PID_calc(&pid_v_1[i-1],motor_6020[i-1].speed_rpm , set_speed);
		return pid_v_1[i-1].out;
}

fp32 PID_pos_x_realize(int8_t set_pos)//6020
{
//		if(delta_x >= 500)
//		{
//			return 0;
//		}
    PID_calc(&pid_pos_x,delta_x, set_pos);
    return pid_pos_x.out;
}

int16_t PID_pos_y_realize(int8_t set_pos)//servo
{
//		if( delta_y >= 500)
//		{
//			return 0;
//		}
    PID_calc(&pid_pos_y,delta_y, set_pos);
    return pid_pos_y.out;
}

fp32 PID_pos_Yaw_realize(fp32 set_yaw)
{
	PID_calc(&pid_yaw, imu.yaw, set_yaw);
	return pid_yaw.out;
}
