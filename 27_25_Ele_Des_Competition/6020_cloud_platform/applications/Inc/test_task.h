#ifndef TEST_TASK_H
#define TEST_TASK_H


#include "include.h"
#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include "tim.h"
#include "uart_user.h"
#include "DM_imu.h"
#include "FreeRTOS.h"


#define PI 3.1415927
#define LOST_THRESHOLD 3
#define MAX_SWING_ANGLE 200.0f
#define SWING_FREQUENCY 0.18f

void Judge_Range(void);
double degreesToRadians(double degrees);
double radiansToDegrees(double radians);
void Seek_Target_Task(void  *argument);
void ButtonTask(void *argument);
#endif
