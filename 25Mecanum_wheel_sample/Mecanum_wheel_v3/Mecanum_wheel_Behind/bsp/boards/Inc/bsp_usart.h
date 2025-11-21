#ifndef __BSP_USART_H_
#define __BSP_USART_H_

#ifdef __cplusplus
extern "C" 
{
#endif


#include "main.h"
#include "usart.h"
#include "hwt101ct_rs232.h"


#define DATA_LEN   6



typedef struct 
{

	int16_t ch[4];      //通锟斤拷锟斤拷0 1锟斤拷锟斤拷遥锟斤拷X Y , 2 3锟斤拷锟斤拷遥锟斤拷X Y锟斤拷
	
	
	
}remote_data;      //遥锟斤拷锟斤拷锟斤拷






void SendByte(uint8_t date);
void Send(const uint8_t *data,uint8_t len);
void Send_Cmd_Data(const uint8_t *datas,uint8_t len);
void DataAnalysis(uint8_t *Data);
uint8_t SUMCRC(uint8_t *Message,uint16_t DataLen);
void Receive_data(uint8_t Bytedata,uint8_t Data_len);

void Send_Data();

#ifdef __cplusplus
}
#endif

#endif
