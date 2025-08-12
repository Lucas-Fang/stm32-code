#include "shoot_param.h"

//���Էֶβ�ֵ
uint16_t interpolate_rpm(const ShootParam_t* table, float dist, int size) {
    for (int i = 0; i < size - 1; i++) {
        float d0 = table[i].distance_m;
        float d1 = table[i + 1].distance_m;

        if (dist >= d0 && dist <= d1) {
            float t = (dist - d0) / (d1 - d0);
            return (uint16_t)(table[i].rpm + t * (table[i + 1].rpm - table[i].rpm));
        }
    }

    // Խ�紦��
    if (dist < table[0].distance_m) return table[0].rpm;
    return table[size - 1].rpm;
}


void auto_set_shoot_param(float current_distance) {
    uint16_t rpm;
    float angle;

    // if (current_distance <= THREE_POINT_DISTANCE_THRESHOLD) {
    //     // 2����
    //     angle = ANGLE_2_POINT;
    //     rpm = interpolate_rpm(shoot_table_2pt, current_distance, TABLE_2PT_SIZE);
    // } else {
    //     // 3����
    //     angle = ANGLE_3_POINT;
    //     rpm = interpolate_rpm(shoot_table_3pt, current_distance, TABLE_3PT_SIZE);
    // }

    // // �������
    // set_angle(angle);         // ���ýǶȣ���������ף�
    // vesc_can_set_rpm(rpm);    // ���õ���ٶ�
}