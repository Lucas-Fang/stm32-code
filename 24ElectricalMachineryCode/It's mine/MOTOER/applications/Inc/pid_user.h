#ifndef __PID_USER_H
#define __PID_USER_H


#include "stm32f4xx_hal.h"
#include "main.h"
#include "can.h"
#include "gpio.h"
#include "can_tx.h"
#include "can_rx.h"
#include "pid.h"


void PID_devices_Init(void);
float PID_velocity_realize_1(float set_speed,int i);
float PID_position_realize_1(float set_pos,int i);		
float pid_call_1(float position,int i);


#endif
