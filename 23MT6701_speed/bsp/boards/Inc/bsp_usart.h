#ifndef __BSP_USART_H_
#define __BSP_USART_H_

#include "main.h"
#include "usart.h"
#include "MT6701.h"
#define DATA_LEN   6



typedef struct 
{

	int16_t ch[2];      
	
	
	
}remote_data;      //Ò£¿ØÊý¾Ý






void DataAnalysis(uint8_t *Data);
uint8_t SUMCRC(uint8_t *Message,uint16_t DataLen);
void Receive_data(uint8_t Bytedata,uint8_t Data_len);
void BlueTooth_Send_Data();

#endif
