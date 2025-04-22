#include "as5600.h"
#include "i2c.h"

Motor_Measure N5065_Data;

extern I2C_HandleTypeDef hi2c2;

uint8_t i2c_rx_buffer[2];  
uint8_t i2c_tx_buffer[1];  

// ��ȡ AS5600 �Ƕ�
float AS5600_ReadAngle()
{
    uint8_t highByte, lowByte;
    uint16_t rawAngle;

    i2c_tx_buffer[0] = 0x0C;  // �Ƕȸ� 8 λ�Ĵ���
    HAL_I2C_Master_Transmit(&hi2c2, AS5600_I2C_ADDR, i2c_tx_buffer, 1, 100);
    HAL_I2C_Master_Receive(&hi2c2, AS5600_I2C_ADDR, &highByte, 1, 100);

    i2c_tx_buffer[0] = 0x0D;  // �Ƕȵ� 4 λ�Ĵ���
    HAL_I2C_Master_Transmit(&hi2c2, AS5600_I2C_ADDR, i2c_tx_buffer, 1, 100);
    HAL_I2C_Master_Receive(&hi2c2, AS5600_I2C_ADDR, &lowByte, 1, 100);

    rawAngle = ((highByte << 8) | lowByte) & 0x0FFF;
    return (rawAngle * 360.0) / 4096.0;
}

// ����ת��
float calculate_rpm()
{
    static float last_angle = 0;
    static uint32_t last_time = 0;

    float current_angle = AS5600_ReadAngle();
    // uint32_t current_time = HAL_GetTick();  // ��ȡ��ǰʱ�䣨ms��

    float delta_angle = current_angle - last_angle;
    if (delta_angle > 180) delta_angle -= 360;  // �����������
    if (delta_angle < -180) delta_angle += 360;

    // uint32_t delta_time = current_time - last_time;  // ʱ��ms��
    float rpm = (delta_angle / SAMPLE_RATE_MS) * 1000 * (60.0 / 360.0);  // ���� RPM

    // ������һ�ε�ֵ
    last_angle = current_angle;
    // last_time = current_time;

    return rpm;
}


float filtered_speed = 0;

float low_pass_filter(float new_speed) {
    filtered_speed = ALPHA * new_speed + (1 - ALPHA) * filtered_speed;
    return filtered_speed;
}

