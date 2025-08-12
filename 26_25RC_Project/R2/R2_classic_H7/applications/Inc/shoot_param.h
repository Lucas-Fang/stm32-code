#ifndef __SHOOT_PARAM_H_
#define __SHOOT_PARAM_H_

#ifdef __cplusplus
extern "C"
{
#endif 

#include "main.h"

#define ANGLE_2_POINT 35.0f  // ���� 2������35��
#define ANGLE_3_POINT 45.0f  // ���� 3������45��

#define SHOOT_TABLE_SIZE 10

typedef struct {
    float distance_m;
    uint16_t rpm;
} ShootParam_t;

// ���ֶ���Ӳ��Գɹ��ĵ㣨���������ȣ�
const ShootParam_t shoot_table_2pt[SHOOT_TABLE_SIZE] = {
    {1.0, 2800},
    {1.5, 3200},
    {2.0, 3600},
    {2.5, 4000},
};

const ShootParam_t shoot_table_3pt[SHOOT_TABLE_SIZE] = {
    {1.0, 3000},
    {1.5, 3500},
    {2.0, 4000},
    {2.5, 4600},
};

uint16_t interpolate_rpm(const ShootParam_t* table, float dist, int size);
void auto_set_shoot_param(float current_distance);
#ifdef __cplusplus
}
#endif 
#endif