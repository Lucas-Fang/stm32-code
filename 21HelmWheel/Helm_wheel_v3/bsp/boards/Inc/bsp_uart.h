#ifndef __BSP_UART_H_
#define __BSP_UART_H_

#ifndef __cplusplus

extern "C"
{
#endif 


#include "main.h"
#include "odometer.h"



typedef struct
{
	
	uint8_t ch[5];
	uint8_t key[5];	
	uint8_t cmd;
	
}remote_data;



void SendByte(uint8_t date);
void Send(const uint8_t *data,uint8_t len);
void Send_Cmd_Data(uint8_t cmd,const uint8_t *datas,uint8_t len);
void Data_Analysis(uint8_t cmd,const uint8_t *datas,uint8_t len);
void Receive(uint8_t bytedata);


#ifndef __cplusplus
}
#endif // !1

#endif // !
