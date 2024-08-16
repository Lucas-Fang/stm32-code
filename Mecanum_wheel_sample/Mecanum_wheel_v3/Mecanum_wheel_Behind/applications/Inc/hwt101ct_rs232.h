#ifndef __HWT101CT_RS232_H_
#define __HWT101CT_RS232_H_

// #ifdef __cpluscplus
// extern "C"
// {
// #endif

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
		fp32 yaw;    //ƫ����  ǰ����ƫ��
		fp32 pitch;  //������	 ǰ������°ڶ�??
		fp32 roll;   //������  ���ҵ����°ڶ�
	}Euler;//ŷ���� 
	
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


// #ifdef __cpluscplus
// }
// #endif

#endif
