#ifndef __CAN_RX_H
#define __CAN_RX_H


#include "main.h"
#include "can.h"
#include "gpio.h"
#include "pid_user.h"

/* CAN send and receive ID */
typedef enum
{
    CAN_CHASSIS_ALL_ID = 0x200,
    CAN_3508_M1_ID = 0x201,
    CAN_3508_M2_ID = 0x202,
    CAN_3508_M3_ID = 0x203,
    CAN_3508_M4_ID = 0x204,
    CAN_3508_M5_ID = 0x205,
    CAN_3508_M6_ID = 0x206,
    CAN_3508_M7_ID = 0x207,
    CAN_3508_ALL_ID = 0x1FF,
} can_msg_id_e;

typedef struct
{
	uint16_t angle;
	int16_t speed_rpm;
	int16_t given_current;					 //电流
	uint8_t temperature;
	int16_t last_angle;
			int32_t total_angle;				 //总圈数
	    int32_t round_cnt;           //计数圈数
			uint16_t offset_angle;			 //上电角度
			uint32_t			msg_cnt;
}motor_measure_t;


void get_motor_measure (motor_measure_t *ptr,uint8_t data[]);
void get_motor_offset (motor_measure_t *ptr ,uint8_t data[]);
void get_total_angle(motor_measure_t *p);

#endif






