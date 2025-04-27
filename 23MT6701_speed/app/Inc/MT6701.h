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
#include "cmsis_os.h"


#define ALPHA 0.1  // 取值 0~1，值越小滤波越强
#define PI 3.1415927

#define MT6701_I2C_ADDR 0x06 << 1 //设备地址
#define MT6701_I2C_DATA_ADDR_H 0x03       //储存角度数据地址
#define MT6701_I2C_DATA_ADDR_L 0x04       //储存角度数据地址

#define SAMPLE_RATE_HZ     1000       // 采样频率1kHz（适合>10万RPM）
#define FILTER_CUTOFF_HZ   50         // 低通截止频率
#define DEBOUNCE_THRESHOLD 5          // 最小有效脉冲阈值
#define SAMPLE_RATE_MS     1           //采样频率 ms


#define MAX_RPM     9600  // 根据电机规格设置



typedef struct 
{
    fp32 angle;
    fp32 last_angle;
    fp32 delta_angle;
    int offset_cnt;
    int32_t round_count;

    fp32 speed_rpm;
}Motor_Measure;

typedef struct {
    float alpha; 
    float prev_output;
} LowPassFilter;


void MT6701_ReadAngle(I2C_HandleTypeDef *hi2c);
void calculate_rpm(I2C_HandleTypeDef *hi2c,Motor_Measure *N5065,uint8_t id);
float low_pass_filter(float new_speed);
void Motor_PWM_Init(TIM_HandleTypeDef *htim);
void N5065_Action(fp32 speed1,fp32 speed2);


#ifdef __cplusplus
}
#endif







#endif 
