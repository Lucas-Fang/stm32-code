#ifndef __PID_USER_H
#define __PID_USER_H
#include "pid.h"
#include "include.h"
#include "DM_imu.h"

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

void PID_devices_Init(void);

float PID_velocity_realize_1(float set_speed,int i);
fp32 PID_pos_x_realize(int8_t set_pos);//6020
int16_t PID_pos_y_realize(int8_t set_pos);//servo
fp32 PID_pos_Yaw_realize(fp32 set_yaw);



#endif























