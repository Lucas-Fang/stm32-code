#ifndef __HWT101CT_RS232_H_
#define __HWT101CT_RS232_H_

#ifdef __cpluscplus
extern "C"
{
#endif

#include "main.h"
#include "struct_typedef.h"
#include <stdio.h>
#include <stdbool.h>
	
typedef struct
{
	__packed struct
	{
		fp32 X;
		fp32 Y;
		fp32 Z;
	}Accel;

	__packed struct
	{
		fp32 X;
		fp32 Y;
		fp32 Z;
	}Gyro;
	
	__packed struct
	{
		fp32 X;
		fp32 Y;
		fp32 Z;
	}Magnet;
	
	__packed struct
	{
		fp32 yaw;    //偏锟斤拷锟斤拷  前锟斤拷锟斤拷偏锟斤拷
		fp32 pitch;  //锟斤拷锟斤拷锟斤拷	 前锟斤拷锟斤拷锟斤拷掳诙锟?
		fp32 roll;   //锟斤拷锟斤拷锟斤拷  锟斤拷锟揭碉拷锟斤拷锟铰摆讹拷
	}Euler;//欧锟斤拷锟斤拷 
	
	__packed struct
	{
		fp32 quat[4];
	}Quaternion;
	
	__packed struct
	{
		fp32 temp;
	}Other_Data;
	
}HWT101CT_t;

bool IMU_Read_Euler(uint8_t *msg_data);
uint8_t __SUMCRC(uint8_t *puchMsg, uint16_t usDataLen);


#ifdef __cpluscplus
}
#endif

#endif
