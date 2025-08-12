<<<<<<< HEAD
#include "can_tx.h"

 
 CAN_TxHeaderTypeDef can_tx_message;
 uint8_t	can_send_data[8];
 
 void CAN1_CMD_1(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4)
{
 uint32_t send_mail_box;
	
 can_tx_message.StdId = 0x200;
 can_tx_message.IDE = CAN_ID_STD;
 can_tx_message.RTR = CAN_RTR_DATA;
 can_tx_message.DLC = 0x08;
 can_send_data[0] = motor1 >> 8;
 can_send_data[1] = motor1;
 can_send_data[2] = motor2 >> 8;
 can_send_data[3] = motor2;
 can_send_data[4] = motor3 >> 8;
 can_send_data[5] = motor3;
 can_send_data[6] = motor4 >> 8;
 can_send_data[7] = motor4;
 HAL_CAN_AddTxMessage(&hcan1, &can_tx_message, can_send_data, &send_mail_box);
}




 void CAN1_CMD_2(int16_t motor5, int16_t motor6, int16_t motor7, int16_t motor8)
{
 uint32_t send_mail_box;
	
 can_tx_message.StdId = 0x1FF;
 can_tx_message.IDE = CAN_ID_STD;
 can_tx_message.RTR = CAN_RTR_DATA;
 can_tx_message.DLC = 0x08;
 can_send_data[0] = motor5 >> 8;
 can_send_data[1] = motor5;
 can_send_data[2] = motor6 >> 8;
 can_send_data[3] = motor6;
 can_send_data[4] = motor7 >> 8;
 can_send_data[5] = motor7;
 can_send_data[6] = motor8 >> 8;
 can_send_data[7] = motor8;
 HAL_CAN_AddTxMessage(&hcan1, &can_tx_message, can_send_data, &send_mail_box);
}


=======
#include "can_tx.h"

 
 CAN_TxHeaderTypeDef can_tx_message;
 uint8_t	can_send_data[8];
 
 void CAN1_CMD_1(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4)
{
 uint32_t send_mail_box;
	
 can_tx_message.StdId = 0x200;
 can_tx_message.IDE = CAN_ID_STD;
 can_tx_message.RTR = CAN_RTR_DATA;
 can_tx_message.DLC = 0x08;
 can_send_data[0] = motor1 >> 8;
 can_send_data[1] = motor1;
 can_send_data[2] = motor2 >> 8;
 can_send_data[3] = motor2;
 can_send_data[4] = motor3 >> 8;
 can_send_data[5] = motor3;
 can_send_data[6] = motor4 >> 8;
 can_send_data[7] = motor4;
 HAL_CAN_AddTxMessage(&hcan1, &can_tx_message, can_send_data, &send_mail_box);
}




 void CAN1_CMD_2(int16_t motor5, int16_t motor6, int16_t motor7, int16_t motor8)
{
 uint32_t send_mail_box;
	
 can_tx_message.StdId = 0x1FF;
 can_tx_message.IDE = CAN_ID_STD;
 can_tx_message.RTR = CAN_RTR_DATA;
 can_tx_message.DLC = 0x08;
 can_send_data[0] = motor5 >> 8;
 can_send_data[1] = motor5;
 can_send_data[2] = motor6 >> 8;
 can_send_data[3] = motor6;
 can_send_data[4] = motor7 >> 8;
 can_send_data[5] = motor7;
 can_send_data[6] = motor8 >> 8;
 can_send_data[7] = motor8;
 HAL_CAN_AddTxMessage(&hcan1, &can_tx_message, can_send_data, &send_mail_box);
}


>>>>>>> 00ac74e (9.6)
