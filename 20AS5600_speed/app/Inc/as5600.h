#ifndef __AS5600_H_
#define __AS5600_H_

#include "struct_typedef.h"
#include "main.h"
#include "i2c.h"




#define ALPHA 0.1  // 取值 0~1，值越小滤波越强
#define PI 3.1415927

#define AS5600_I2C_ADDR  (0x36 << 1)  // AS5600 的 7 位地址是 0x36，HAL 需要 8 位地址
#define AS5600_DATA_DAAR_H 0x0e         //as5600 数据高八位寄数据储存地址
#define AS5600_DATA_DAAR_L 0x0f         //as5600 数据第八位寄数据储存地址，最后四位没有用，因为一共有12位

#define SAMPLE_RATE_HZ     1000       // 采样频率1kHz（适合>10万RPM）
#define FILTER_CUTOFF_HZ   50         // 低通截止频率
#define DEBOUNCE_THRESHOLD 5          // 最小有效脉冲阈值
#define SAMPLE_RATE_MS     1           //采样频率 ms


#define MAX_RPM     9600  // 根据电机规格设置



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
