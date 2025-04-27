#ifndef __BSP_UART_H_
#define __BSP_UART_H_

#include <cstdint>
#ifndef __cplusplus

extern "C"
{
#endif 


#include "main.h"
#include "usart.h"

#define DATA_LEN   6



typedef struct 
{

	int16_t ch[4];      //通道（0 1左手遥感X Y , 2 3右手遥感X Y）
}remote_data;      //遥控数据

// namespace Rxbuffer {
// 	uint8_t BT_buff[1];
// }
	typedef struct 
	{
		uint8_t odometer[1];
		uint8_t DR16[18];
		uint8_t remote_control[10];
		int16_t remote_sense[4];
		uint8_t s1,s2;
		uint8_t upper[1];
	}Rxbuffer;



uint8_t SUMCRC(uint8_t *Message,uint16_t DataLen);
void DataAnalysis(uint8_t *Data);
void Receive_data(uint8_t Bytedata,uint8_t Data_len);
void Get_Remote_Date();

#ifndef __cplusplus
}
#endif // !1

#endif // !
