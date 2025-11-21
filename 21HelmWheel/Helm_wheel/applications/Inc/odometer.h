#ifndef __ODOMETER_H_
#define __ODOMETER_H_

#ifndef __cplusplus

extern "C"
{
#endif 


#include "main.h"
#include "struct_typedef.h"
#include "string.h"


void SendByte2Mapan(uint8_t buffer);
void Send2Mapan(const uint8_t *data, uint8_t len);
uint16_t CRC16_Check(const uint8_t *data, uint8_t len);
void Send_Cmd_Data2Mapan(uint8_t cmd, const uint8_t *datas, uint8_t len);
void Data_AnalysisfromActuator(uint8_t cmd, const uint8_t *datas, uint8_t len);
void Data_AnalysisfromMapan(uint8_t cmd, const uint8_t *datas, uint8_t len);
void ReceivefromMapan(uint8_t bytedata);



#ifndef __cplusplus
}
#endif // !1

#endif // !