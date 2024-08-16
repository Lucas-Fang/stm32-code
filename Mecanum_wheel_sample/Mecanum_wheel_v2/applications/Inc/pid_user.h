#ifndef __PID_USER_H_
#define __PID_USER_H_


#ifdef __cplusplus

extern "C"
{
#endif


#include "main.h"
#include "chassic.h"
#include "pid.h"
#include "bsp_usart.h"



void PID_Device_Init();
fp32 PID_position_Yaw(fp32 set_angle);
	
	#ifdef __cplusplus
}
#endif


#endif
