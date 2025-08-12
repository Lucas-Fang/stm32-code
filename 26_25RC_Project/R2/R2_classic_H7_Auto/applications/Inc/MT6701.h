#ifndef __MT6701_H_
#define __MT6701_H_



#ifdef __cplusplus
extern "C"
{
#endif

#include "struct_typedef.h"
#include "main.h"
#include "i2c.h"
#include "tim.h"



#define ALPHA 0.1  // ȡֵ 0~1��ֵԽС�˲�Խǿ

#define MT6701_I2C_ADDR 0x06 << 1 //�豸��ַ
#define MT6701_I2C_DATA_ADDR_H 0x03       //����Ƕ����ݵ�ַ
#define MT6701_I2C_DATA_ADDR_L 0x04       //����Ƕ����ݵ�ַ

void MT6701_ReadAngle(I2C_HandleTypeDef *hi2c);
void calculate_rpm(I2C_HandleTypeDef *hi2c);
static uint8_t MT6701_ReadOneByte(uint8_t ReadAddr);
uint16_t MT6701_ReadTwoByte(uint8_t higher,uint8_t lower);



#ifdef __cplusplus
}
#endif







#endif 
