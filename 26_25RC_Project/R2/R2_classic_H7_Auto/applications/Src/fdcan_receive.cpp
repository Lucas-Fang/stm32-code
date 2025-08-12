#include "fdcan_receive.h"
#include "fdcan.h"


/*******����*******/
CAN_BUS can_bus;

//vesc���can����
void VESC_CAN_Speedrpm(int id,int speed_rpm)
{
 FDCAN_TxHeaderTypeDef fdcan_tx_message={0};
 uint8_t can_send_data[4];

int32_t erpm = speed_rpm * 7;
 fdcan_tx_message.Identifier = id;//Identifier����F4ϵ�е�StdId�����͵ı�ʶ��
 fdcan_tx_message.IdType = FDCAN_EXTENDED_ID;//��չ֡
 fdcan_tx_message.TxFrameType = FDCAN_DATA_FRAME;//����֡
 fdcan_tx_message.DataLength = 0x04;				//һ֡���ݳ���
 fdcan_tx_message.ErrorStateIndicator = FDCAN_ESI_ACTIVE;//
 fdcan_tx_message.BitRateSwitch = FDCAN_BRS_OFF;//
 fdcan_tx_message.FDFormat = FDCAN_CLASSIC_CAN;
 fdcan_tx_message.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
 fdcan_tx_message.MessageMarker = 0;

 can_send_data[0] = erpm >> 24;
 can_send_data[1] = erpm >> 16;
 can_send_data[2] = erpm >> 8;
 can_send_data[3] = erpm ;

 HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &fdcan_tx_message, can_send_data);
}

//DJ���canͨѶ����

/**
 * @brief       FDCAN1���ͺ���(ǰ4�����)
 * @param       motor1�����������Ϊ0�����IDΪ1���ĵ��������Ե���ֵ
 * @param       motor2�����������Ϊ1�����IDΪ2���ĵ��������Ե���ֵ
 * @param       motor3�����������Ϊ2�����IDΪ3���ĵ��������Ե���ֵ
 * @param       motor4�����������Ϊ3�����IDΪ4���ĵ��������Ե���ֵ
 * @retval      void
 * @note        ��
 */
void CAN_BUS::CMD::FDCAN1_Front(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4)
{
 FDCAN_TxHeaderTypeDef fdcan_tx_message={0};
 uint8_t	can_send_data[8];

	
 fdcan_tx_message.Identifier = 0x200;//Identifier����F4ϵ�е�StdId�����͵ı�ʶ��
 fdcan_tx_message.IdType = FDCAN_STANDARD_ID;//��׼֡
 fdcan_tx_message.TxFrameType = FDCAN_DATA_FRAME;//����֡
 fdcan_tx_message.DataLength = 0x08;				//һ֡���ݳ���
 fdcan_tx_message.ErrorStateIndicator = FDCAN_ESI_ACTIVE;//
 fdcan_tx_message.BitRateSwitch = FDCAN_BRS_OFF;//
 fdcan_tx_message.FDFormat = FDCAN_CLASSIC_CAN;
 fdcan_tx_message.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
 fdcan_tx_message.MessageMarker = 0;

 can_send_data[0] = motor1 >> 8;
 can_send_data[1] = motor1;
 can_send_data[2] = motor2 >> 8;
 can_send_data[3] = motor2;
 can_send_data[4] = motor3 >> 8;
 can_send_data[5] = motor3;
 can_send_data[6] = motor4 >> 8;
 can_send_data[7] = motor4;
 HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &fdcan_tx_message, can_send_data);
}



/**
 * @brief       FDCAN1���ͺ���(��4�����)
 * @param       motor1�����������Ϊ4�����IDΪ5���ĵ��������Ե���ֵ
 * @param       motor2�����������Ϊ5�����IDΪ6���ĵ��������Ե���ֵ
 * @param       motor3�����������Ϊ6�����IDΪ7���ĵ��������Ե���ֵ
 * @param       motor4�����������Ϊ7�����IDΪ8���ĵ��������Ե���ֵ
 * @retval      void
 * @note        ��
 */
 void CAN_BUS::CMD::FDCAN1_Behind(int16_t motor5, int16_t motor6, int16_t motor7, int16_t motor8)
{
 uint8_t	can_send_data[8];
 
 FDCAN_TxHeaderTypeDef fdcan_tx_message ={0};
	
 fdcan_tx_message.Identifier  = 0x1FF;
 fdcan_tx_message.IdType = FDCAN_STANDARD_ID;//��׼֡
 fdcan_tx_message.TxFrameType = FDCAN_DATA_FRAME;//����֡
 fdcan_tx_message.DataLength = 0x08;				//һ֡���ݳ���
 fdcan_tx_message.ErrorStateIndicator = FDCAN_ESI_ACTIVE;//
 fdcan_tx_message.BitRateSwitch = FDCAN_BRS_OFF;//
 fdcan_tx_message.FDFormat = FDCAN_CLASSIC_CAN;
 fdcan_tx_message.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
 fdcan_tx_message.MessageMarker = 0;

 can_send_data[0] = motor5 >> 8;
 can_send_data[1] = motor5;
 can_send_data[2] = motor6 >> 8;
 can_send_data[3] = motor6;
 can_send_data[4] = motor7 >> 8;
 can_send_data[5] = motor7;
 can_send_data[6] = motor8 >> 8;
 can_send_data[7] = motor8;
 HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &fdcan_tx_message, can_send_data);
}


///**
// * @brief       FDCAN2���ͺ���(ǰ4�����)
// * @param       motor1�����������Ϊ0�����IDΪ1���ĵ��������Ե���ֵ
// * @param       motor2�����������Ϊ1�����IDΪ2���ĵ��������Ե���ֵ
// * @param       motor3�����������Ϊ2�����IDΪ3���ĵ��������Ե���ֵ
// * @param       motor4�����������Ϊ3�����IDΪ4���ĵ��������Ե���ֵ
// * @retval      void
// * @note        ��
// */
// void CAN_BUS::CMD::FDCAN2_Front(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4)
//{
// uint8_t	can_send_data[8];
//	
// FDCAN_TxHeaderTypeDef fdcan_tx_message;
//	
// fdcan_tx_message.Identifier  = 0x200;
// fdcan_tx_message.IdType = FDCAN_STANDARD_ID;//��׼֡
// fdcan_tx_message.TxFrameType = FDCAN_DATA_FRAME;//����֡
// fdcan_tx_message.DataLength = 0x08;				//һ֡���ݳ���
// fdcan_tx_message.ErrorStateIndicator = FDCAN_ESI_ACTIVE;//
// fdcan_tx_message.BitRateSwitch = FDCAN_BRS_OFF;//
// fdcan_tx_message.FDFormat = FDCAN_CLASSIC_CAN;
// fdcan_tx_message.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
// fdcan_tx_message.MessageMarker = 0;

// can_send_data[0] = motor1 >> 8;
// can_send_data[1] = motor1;
// can_send_data[2] = motor2 >> 8;
// can_send_data[3] = motor2;
// can_send_data[4] = motor3 >> 8;
// can_send_data[5] = motor3;
// can_send_data[6] = motor4 >> 8;
// can_send_data[7] = motor4;
// HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &fdcan_tx_message, can_send_data);

//}

///**
// * @brief       FDCAN2���ͺ���(��4�����)
// * @param       motor1�����������Ϊ4�����IDΪ5���ĵ��������Ե���ֵ
// * @param       motor2�����������Ϊ5�����IDΪ6���ĵ��������Ե���ֵ
// * @param       motor3�����������Ϊ6�����IDΪ7���ĵ��������Ե���ֵ
// * @param       motor4�����������Ϊ7�����IDΪ8���ĵ��������Ե���ֵ
// * @retval      void
// * @note        ��
// */
// void CAN_BUS::CMD::FDCAN2_Behind(int16_t motor5, int16_t motor6, int16_t motor7, int16_t motor8)
//{
// uint8_t	can_send_data[8];
// FDCAN_TxHeaderTypeDef fdcan_tx_message;

// fdcan_tx_message.Identifier = 0x200;//Identifier����F4ϵ�е�StdId�����͵ı�ʶ��
// fdcan_tx_message.IdType = FDCAN_STANDARD_ID;//��׼֡
// fdcan_tx_message.TxFrameType = FDCAN_DATA_FRAME;//����֡
// fdcan_tx_message.DataLength = 0x08;				//һ֡���ݳ���
// fdcan_tx_message.ErrorStateIndicator = FDCAN_ESI_ACTIVE;//
// fdcan_tx_message.BitRateSwitch = FDCAN_BRS_OFF;//
// fdcan_tx_message.FDFormat = FDCAN_CLASSIC_CAN;
// fdcan_tx_message.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
// fdcan_tx_message.MessageMarker = 0;

// can_send_data[0] = motor5 >> 8;
// can_send_data[1] = motor5;
// can_send_data[2] = motor6 >> 8;
// can_send_data[3] = motor6;
// can_send_data[4] = motor7 >> 8;
// can_send_data[5] = motor7;
// can_send_data[6] = motor8 >> 8;
// can_send_data[7] = motor8;
// HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &fdcan_tx_message, can_send_data);

//}

extern "C"
/**
 * @brief       �ص���������ʱ���жϷ���������
 * @param       hcan�������жϵ�CANͨ�ž��
 * @retval      void
 * @note        �ú������жϹ������������ã������û�ȥ���á���Ϊһ����������������C++��Ҫ�ڸú���ǰ�����extern "C"����ֱ����extern "C"{}������
 */
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
		FDCAN_RxHeaderTypeDef fdcan_rx_header;
		uint8_t rx_data_1[8];
		uint8_t rx_data_2[8];
	
	if(hfdcan->Instance==FDCAN1)
	{
		HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &fdcan_rx_header, rx_data_1);

		switch (fdcan_rx_header.Identifier)
		{
			case CAN_3508_M1_ID:
			case CAN_3508_M2_ID:
			case CAN_3508_M3_ID:
			case CAN_3508_M4_ID:
			case CAN_3508_M5_ID:
			case CAN_3508_M6_ID:
			case CAN_3508_M7_ID:
			{
				static uint8_t i = 0;
				//get motor id
				i = fdcan_rx_header.Identifier - CAN_3508_M1_ID;
				can_bus.motor_can1[i].msg_cnt++ <= 50	?	
					can_bus.dji_encoder.get_moto_offset(&can_bus.motor_can1[i], rx_data_1) :
					can_bus.dji_encoder.get_motor_measure(&can_bus.motor_can1[i], rx_data_1);

				// can_bus.dji_encoder.get_motor_measure(&can_bus.motor_can1[i], rx_data_1);
				break;
			}
			default:
			{
			break;
			}	
		}
	}
		
	if(hfdcan->Instance==FDCAN2)
	{
		HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &fdcan_rx_header, rx_data_2);


//		switch (fdcan_rx_header.Identifier)
//		{
//			case CAN_3508_M1_ID:
//			case CAN_3508_M2_ID:
//			case CAN_3508_M3_ID:
//			case CAN_3508_M4_ID:
//			case CAN_3508_M5_ID:
//			case CAN_3508_M6_ID:
//			case CAN_3508_M7_ID:
////			case CAN_3508_ALL_ID:
//			{
//				static uint8_t i = 0;
//				//get motor id
//				i = fdcan_rx_header.Identifier - CAN_3508_M1_ID;
//				can_bus.motor_can2[i].msg_cnt++ <= 50	?
//					can_bus.dji_encoder.get_moto_offset(&can_bus.motor_can2[i], rx_data_2) :
//					can_bus.dji_encoder.get_motor_measure(&can_bus.motor_can2[i], rx_data_2);

//				// can_bus.dji_encoder.get_motor_measure(&can_bus.motor_can2[i], rx_data_2);
//				break;
//			}
//			default:
//			{
//			break;
//			}	
//		}
 }
}

/**
 * @brief       ������������ݻ�ȡ�����Ϣ����
 * @param       ptr��@motor_measure_t���;�������洦���ĵ��״̬��Ϣ
 * @param       data��CANͨ�Ž��յ����������ԭ����
 * @retval      void
 * @note        ��
 */
void CAN_BUS::DJI_ENCODER::get_motor_measure(motor_measure_t *ptr,uint8_t data[])                                                     
{   

        (ptr)->last_angle = (ptr)->angle;                                                          
        (ptr)->angle = data[0] << 8 | data[1];           
        (ptr)->speed_rpm = data[2] << 8 | data[3];     
        (ptr)->given_current = data[4] << 8 | data[5]; 
        (ptr)->temperate = data[6];                                              
//				((ptr)->angle) = (int32_t)(((ptr)->ecd) - ((ptr)->last_ecd));
		int16_t delta = (ptr)->angle - (ptr)->last_angle;
			if(ptr->angle - ptr->last_angle > 4096)
				ptr->round_cnt --;
			else if (ptr->angle - ptr->last_angle < -4096)
				ptr->round_cnt ++;
		
			// if (abs(delta) < 6000)  // ��ֹ�쳣����
			// {
			// 	if (delta > 4096)
			// 		ptr->round_cnt--;
			// 	else if (delta < -4096)
			// 		ptr->round_cnt++;
			// }
			ptr->total_angle = ptr->round_cnt * 8192 + ptr->angle - ptr->offset_angle;
}

/**
 * @brief       ������������ݻ�ȡ����տ�ʼ�ĽǶȳ�ʼֵ����
 * @param       ptr��@motor_measure_t���;�������洦���ĵ��״̬��Ϣ
 * @param       data��CANͨ�Ž��յ����������ԭ����
 * @retval      void
 * @note        �ú����ǽ����Ա�����ת��Ϊ�����������Ĺؼ�����ȡ�˵��ͨ��ʱ�ĽǶ�ֵ
 */
void CAN_BUS::DJI_ENCODER::get_moto_offset(motor_measure_t *ptr, uint8_t data[])
{
	ptr->angle = data[0]<<8 |data[1] ;
	ptr->offset_angle = ptr->angle;
}


/**
 * @brief       �������Ƕ�ֵ
 * @param       p��@motor_measure_t���;�������洦���ĵ��״̬��Ϣ
 * @retval      void
 * @note        �ú���û�б����ã���ʱû��
 */
void CAN_BUS::DJI_ENCODER::get_total_angle(motor_measure_t *p)
{
	
	int res1, res2, delta;
	if(p->angle < p->last_angle){			//���ܵ����
		res1 = p->angle + 8192 - p->last_angle;	//��ת��delta=+
		res2 = p->angle - p->last_angle;				//��ת	delta=-
	}else{	//angle > last
		res1 = p->angle - 8192 - p->last_angle ;//��ת	delta -
		res2 = p->angle - p->last_angle;				//��ת	delta +
	}
	//��������ת���϶���ת�ĽǶ�С���Ǹ������
	if(ABS(res1)<ABS(res2))
		delta = res1;
	else
		delta = res2;

	p->total_angle += delta;
	p->last_angle = p->angle;
}


