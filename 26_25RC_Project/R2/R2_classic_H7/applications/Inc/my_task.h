#ifndef __MY_TASK_H_
#define __MY_TASK_H_


#ifdef __cplusplus
extern "C"
{
#endif 


#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "usbd_cdc_if.h"
#include "usb_device.h"
#include "usart.h"
#include "fdcan.h"
#include "gpio.h"
#include "tim.h"



//3 ���� 
//4 ��λ��������������
//5 �̶�����Ͷ��

typedef enum 
{
    ASK_START_POS = 0X01,                   //1 ���󷵻�ԭ��
    ALLOW_START_POS,                        //2 ��λ�����ص� vx,vy,vomega
    ASK_LAUNCH_SPEED,                       //3����Ͷ��(�Զ���׼)
    ALLOW_LAUNCH,                           //4��λ����������Ͷ�����������Vomega��speed_rpm��
    ASK_FIXED_POS_LAUNCH,                   //5Ԥѡ���̶���λͶ��
    ALLOW_FIXED_POS_LAUNCH,                 //6��λ�����ع̶���λλ��(Vx��Vy,Vomega,speed_rpm)
    UPPER_OK = 0xff                         //��λ���յ�����(���Բ���)
}CMD_PACKAGE;

//ѡ�������ģʽ ͨ���ұ߲���
#define MANUAL_MODE  3//�ֶ�ģʽ
#define AUTO_MODE    1//�Զ�ģʽ


#define ROD_BOTTOM_PUSH  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET)        //0��ʱ����������
#define ROD_BOTTOM_BACK  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET)
#define ROD_TOP_PUSH     HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET)
#define ROD_TOP_BACK     HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET)

#define BALL_SWITCH      HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)   
//��������0 û��������1
#define BALL_IN 0
#define BALL_OUT 1



void Start_Dribble();
void Catch_the_Ball();
bool Judge_ball(void);
void UpdateSpeedFromBluetooth(int16_t new_speed);
void DT7_Switch_Update();

void StartLaunchTask(void *argument);


#ifdef __cplusplus
}
#endif 
#endif