#ifndef __AS5600_H_
#define __AS5600_H_

#include "struct_typedef.h"
#include "main.h"
#include "i2c.h"




#define ALPHA 0.1  // ȡֵ 0~1��ֵԽС�˲�Խǿ
#define PI 3.1415927

#define AS5600_I2C_ADDR  (0x36 << 1)  // AS5600 �� 7 λ��ַ�� 0x36��HAL ��Ҫ 8 λ��ַ
#define AS5600_DATA_DAAR_H 0x0e         //as5600 ���ݸ߰�λ�����ݴ����ַ
#define AS5600_DATA_DAAR_L 0x0f         //as5600 ���ݵڰ�λ�����ݴ����ַ�������λû���ã���Ϊһ����12λ

#define SAMPLE_RATE_HZ     1000       // ����Ƶ��1kHz���ʺ�>10��RPM��
#define FILTER_CUTOFF_HZ   50         // ��ͨ��ֹƵ��
#define DEBOUNCE_THRESHOLD 5          // ��С��Ч������ֵ
#define SAMPLE_RATE_MS     1           //����Ƶ�� ms


#define MAX_RPM     9600  // ���ݵ���������



typedef struct 
{
    int16_t angle;
    int16_t last_angle;
    int total_angle;
    int last_total_angle;
    fp64 delta_angle;
    int16_t offset_angle;
    int offset_cnt;
    int32_t round_count;

    fp64 speed_rpm;
}Motor_Measure;

typedef struct {
    float alpha; 
    float prev_output;
} LowPassFilter;


float AS5600_ReadAngle();
float calculate_rpm();
float low_pass_filter(float new_speed);


#endif 
