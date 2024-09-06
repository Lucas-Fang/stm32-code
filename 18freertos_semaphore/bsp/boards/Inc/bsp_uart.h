#ifndef __BSP_UART_H_
#define __BSP_UART_H_

#include "usart.h"



typedef struct
{
	
	uint8_t ch[5];
	uint8_t key[5];	
	uint8_t cmd;
	
}remote_data;




void SendByte(uint8_t date);
void Send(const uint8_t *data,uint8_t len);
uint16_t CRC16_Check(const uint8_t *data,uint8_t len);
void Send_Cmd_Data(uint8_t cmd,const uint8_t *datas,uint8_t len);
void Data_Analysis(uint8_t cmd,const uint8_t *datas,uint8_t len);
void Receive(uint8_t bytedata);
//void Task_Date_pack(void const * argument);



void receive_data(uint8_t *datas);

#endif
