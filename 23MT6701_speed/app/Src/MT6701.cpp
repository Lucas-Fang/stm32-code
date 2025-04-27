#include "MT6701.h"

Motor_Measure N5065_Data[2];

uint8_t buffer[4];
void MT6701_ReadAngle(I2C_HandleTypeDef *hi2c) 
{
    if (hi2c->Instance == I2C1) {
    
        HAL_I2C_Mem_Read(hi2c, MT6701_I2C_ADDR, MT6701_I2C_DATA_ADDR_H, 
            I2C_MEMADD_SIZE_8BIT, buffer, 2,100);
       N5065_Data[0].angle  = ((buffer[0] << 6) | buffer[1] << 2) & 0x3FFF;
       N5065_Data[0].angle = (N5065_Data[0].angle * 360.0f) / 16384.0f ;

    }

    if (hi2c->Instance == I2C2) {
    
        HAL_I2C_Mem_Read(hi2c, MT6701_I2C_ADDR, MT6701_I2C_DATA_ADDR_H, 
            I2C_MEMADD_SIZE_8BIT, &buffer[2], 2,100);
       N5065_Data[1].angle  = ((buffer[2] << 6) | buffer[3] << 2) & 0x3FFF;
       N5065_Data[1].angle = (N5065_Data[1].angle * 360.0f) / 16384.0f ;

    }
		
//	return (raw_angle * 360.0f) / 16384.0f;
}
extern "C"{
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c) {
    if (hi2c->Instance == I2C1) {
        N5065_Data[0].angle = (buffer[0] << 6) | (buffer[1] << 2 & 0x3F);
        N5065_Data[0].angle = (N5065_Data[0].angle * 360.0f) / 16384.0f ;
    }
    if (hi2c->Instance == I2C2) {
        N5065_Data[1].angle = (buffer[2] << 6) | (buffer[3] << 2 & 0x3F);
        N5065_Data[1].angle = (N5065_Data[1].angle * 360.0f) / 16384.0f ;
    }
}
}

// 计算转速
void calculate_rpm(I2C_HandleTypeDef *hi2c,Motor_Measure *N5065,uint8_t id)
{

    static uint32_t last_time = 0;
  
 

    uint32_t current_time = HAL_GetTick();  // 获取当前时间（ms）
    N5065[id-1].delta_angle = N5065[id-1].angle-N5065[id-1].last_angle;
    if (N5065[id-1].delta_angle > 180) N5065[id-1].delta_angle -= 360;  // 处理过零问题
    if (N5065[id-1].delta_angle < -180) N5065[id-1].delta_angle += 360;

    uint32_t delta_time = current_time - last_time;  // 时间差（ms）SAMPLE_RATE_MS
    N5065[id-1].speed_rpm = ((N5065[id-1].delta_angle / SAMPLE_RATE_MS) * 1000 * 60.0f )/ 360.0f;  // 计算 RPM
   N5065[id-1].speed_rpm = low_pass_filter(N5065[id-1].speed_rpm);
    // 更新上一次的值
    N5065[id-1].last_angle = N5065[id-1].angle;
    last_time = current_time;
}


float filtered_speed = 0;

float low_pass_filter(float new_speed) {
    filtered_speed = ALPHA * new_speed + (1 - ALPHA) * filtered_speed;
    return filtered_speed;
}

void Motor_PWM_Init(TIM_HandleTypeDef *htim)
{
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1 );
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_2 );
    __HAL_TIM_SetCompare(htim,TIM_CHANNEL_1 ,2000);
    __HAL_TIM_SetCompare(htim,TIM_CHANNEL_2 ,2000);
    // HAL_Delay(3000);
    osDelay(3000);
    __HAL_TIM_SetCompare(htim,TIM_CHANNEL_1 ,1000);
    __HAL_TIM_SetCompare(htim,TIM_CHANNEL_2 ,1000);
    // HAL_Delay(3000);
    osDelay(3000);
    
}

void N5065_Action(fp32 speed1,fp32 speed2)
{
    if(speed1<0) speed1=-speed1;
    if(speed2<0) speed2=-speed2;

    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,speed1);
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,speed2);
}