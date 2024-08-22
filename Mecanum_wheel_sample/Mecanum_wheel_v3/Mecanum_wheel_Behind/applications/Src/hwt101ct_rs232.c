#include "hwt101ct_rs232.h"

HWT101CT_t hwt101ct;
uint8_t HWT101CT_buffer[1];



// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
// {
// 	if(huart->Instance == USART1)
// 	{
//		Receive_data(rx_buffer[0],DATA_LEN);
// 		IMU_Read_Euler(rx_buffer); 
// 	}
// }


bool IMU_Read_Euler(uint8_t *msg_data)
{
	static uint8_t CheckSum;
    static uint8_t msg_data_pre;
	static uint8_t buffer[11];
	static int16_t rx_cnt = 1;
	static uint8_t finded_flag;

    if(msg_data_pre == 0x55 && *msg_data == 0x53)
    {
        finded_flag = 1;
    }
    if(finded_flag == 1)
    {
        buffer[0] = msg_data_pre;
        buffer[rx_cnt++] = *msg_data;
        if(rx_cnt == 11)
        {
            finded_flag = 0;
			rx_cnt = 1;
            msg_data_pre = 0;

            CheckSum = __SUMCRC(buffer,10);
            if(CheckSum != buffer[10])
		    {
		    	return false;
		    }
//		    imu.Euler.roll = (int16_t)((int16_t)buffer[3] << 8 | buffer[2]);
//		    imu.Euler.pitch = (int16_t)((int16_t)buffer[5] << 8 | buffer[4]);
		    hwt101ct.Euler.yaw = (int16_t)((int16_t)buffer[7] << 8 | buffer[6]);

//		    imu.Euler.roll = imu.Euler.roll / 32768.0f * 180.0f;
//		    imu.Euler.pitch = imu.Euler.pitch / 32768.0f * 180.0f;
		    hwt101ct.Euler.yaw = hwt101ct.Euler.yaw / 32768.0f * 180.0f;
		
		    return true;
        }
    }
    else
    {
        msg_data_pre = *msg_data;
    }
    return false;
}


uint8_t __SUMCRC(uint8_t *puchMsg, uint16_t usDataLen)
{
    int16_t i = 0;
		uint8_t uchSUMCRC = 0x00;
    for (; i < usDataLen; i++)
    {
			uchSUMCRC += puchMsg[i];
    }
    return uchSUMCRC;
}




