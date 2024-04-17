#include "can_rx.h"


motor_measure_t motor_can1[8];


void get_motor_measure (motor_measure_t *ptr,uint8_t data[])
{
	(ptr)->last_angle = (ptr)->angle;
	(ptr)->angle = data[0] << 8 | data[1];
	(ptr)->speed_rpm = data[2] << 8 | data[3];
	(ptr)->given_current = data[4] << 8 | data[5];
	(ptr)->temperature = data[6];
	//				((ptr)->angle) = (int32_t)(((ptr)->ecd) - ((ptr)->last_ecd));
	
	/*通过角度计算转了几圈*/
		if(ptr->angle - ptr->last_angle > 4096)
			ptr->round_cnt --;
		else if (ptr->angle - ptr->last_angle < -4096)
			ptr->round_cnt ++;
		ptr->total_angle = ptr->round_cnt * 8192 + ptr->angle - ptr->offset_angle;
}

void get_motor_offset (motor_measure_t *ptr ,uint8_t data[])
{
	ptr->angle = data[0] << 8 | data[1];
	ptr->offset_angle = ptr->angle;
}


//暂时无用函数
#define ABS(x)	( (x>0) ? (x) : (-x) )


void get_total_angle(motor_measure_t *p)
	{
	
	int res1, res2, delta;
	if(p->angle < p->last_angle){			//可能的情况
		res1 = p->angle + 8192 - p->last_angle;	//正转，delta=+
		res2 = p->angle - p->last_angle;				//反转	delta=-
	}else{	//angle > last
		res1 = p->angle - 8192 - p->last_angle ;//反转	delta -
		res2 = p->angle - p->last_angle;				//正转	delta +
	}
	//不管正反转，肯定是转的角度小的那个是真的
	if(ABS(res1)<ABS(res2))
		delta = res1;
	else
		delta = res2;

	p->total_angle += delta;
	p->last_angle = p->angle;
}



void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	CAN_RxHeaderTypeDef rx_header;
	uint8_t rx_data_1[8];
	
if(hcan->Instance == CAN1)
{
		HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&rx_header,rx_data_1);
		
		switch (rx_header.StdId)
		{
			case CAN_3508_M1_ID:
			case CAN_3508_M2_ID:
			case CAN_3508_M3_ID:
			case CAN_3508_M4_ID:
			case CAN_3508_M5_ID:
			case CAN_3508_M6_ID:
			case CAN_3508_M7_ID:
		 
	 	  { static uint8_t i = 0;
//get motor id  获得电机ID
	 		 i = rx_header.StdId - CAN_3508_M1_ID;
			 motor_can1[i].msg_cnt++ <= 50	?	get_motor_offset(&motor_can1[i], rx_data_1) : get_motor_measure(&motor_can1[i], rx_data_1);
			 get_motor_measure(&motor_can1[i], rx_data_1);
			 break;
			}
			 default :
		  {
		 	 break;
		  }
		}
}
	
}








