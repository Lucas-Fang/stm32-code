#ifndef __UART_USER_H_
#define __UART_USER_H_


#include "struct_typedef.h"
#include "main.h"
#include <stdbool.h>

// һ�׵�ͨ�˲����ṹ��
typedef struct {
    float alpha;    // �˲�ϵ�� (0 < alpha < 1)
    float prev_val; // ��һ���˲����ֵ
} LowPassFilter;


void DataAnalysis(uint8_t *Data);
uint8_t SUMCRC(uint8_t *Message,uint16_t DataLen);
void Receive_data(uint8_t Bytedata,uint8_t Data_len);
void Receive_K230_data(uint8_t Bytedata ,uint8_t Data_len);

void LowPassFilter_Init(LowPassFilter* filter, float alpha, float init_val);
float LowPassFilter_Update(LowPassFilter* filter, float new_val);
void VisionData_Received(float x_error, float y_error);
#endif
