<<<<<<< HEAD
#ifndef __BSP_USART_H_
#define __BSP_USART_H_

#include "main.h"
#include "usart.h"

#define DATA_LEN   6



typedef struct 
{

	uint8_t ch[4];      //ͨ����0 1����ң��X Y , 2 3����ң��X Y��
	
	
	
}remote_data;      //ң������







void DataAnalysis(uint8_t *Data);
uint8_t SUMCRC(uint8_t *Message,uint16_t DataLen);
void Receive_data(uint8_t Bytedata,uint8_t Data_len);


#endif
=======
#ifndef __BSP_USART_H_
#define __BSP_USART_H_

#include "main.h"
#include "usart.h"

#define DATA_LEN   6



typedef struct 
{

	uint8_t ch[4];      //ͨ����0 1����ң��X Y , 2 3����ң��X Y��
	
	
	
}remote_data;      //ң������







void DataAnalysis(uint8_t *Data);
uint8_t SUMCRC(uint8_t *Message,uint16_t DataLen);
void Receive_data(uint8_t Bytedata,uint8_t Data_len);


#endif
>>>>>>> 00ac74e (9.6)
