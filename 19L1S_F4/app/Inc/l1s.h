#ifndef __L1S_H_
#define __L1S_H_



#define L1S_DATA_lEN   8 
//Ä£Ê½Ñ¡Ôñ
#define L1SMODE_CIRCLE 0X03
#define L1SMODE_ONCE 0X02
#define L1SMODE_HIGHSPEED_CIRCLE 0X04
#define L1SMODE_DISABLE 0X05


#include "main.h"
#include "usart.h"
#include <stdbool.h>



bool Read_LaserData(uint8_t *msg_data_point);
uint8_t BBC_Check(uint8_t *puchMsg,uint8_t uchDataLen);
void Send_L1S_cmd_data(uint8_t cmd);
void DataAnalysis(uint8_t *buff);
void Read_L1S(uint8_t msg_data_point);


#endif
