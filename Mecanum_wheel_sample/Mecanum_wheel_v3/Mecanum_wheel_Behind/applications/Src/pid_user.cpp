#include "pid_user.h"
#include "hwt101ct_rs232.h"
#include "struct_typedef.h"
#include "chassic.h"
#include "pid.h"

extern ROBOT::CHASSIC::Motor motor1;
extern ROBOT::CHASSIC::Motor motor2;
extern ROBOT::CHASSIC::Euler euler;
extern HWT101CT_t hwt101ct;
//�涨1����  2����
/*PID����������*/
PID_Controller pid_controller;
/***************/

pid_type_def pid_speed[2];
pid_type_def pid_yaw;

fp32 motor_speed_pid_1[3]={1.1,0.01,0};
fp32 motor_speed_pid_2[3]={1.1,0.01,0};
fp32 yaw_pid[3]={100,1,0};

/** 
* @brief PID��ʼ������
*
* @param void void
* @return void
*    @retval void
 */
void PID_Controller::All_Device_Init()
{
    this->core.PID_Init(&pid_speed[0], PID_POSITION, motor_speed_pid_1, 4000, 10);
    this->core.PID_Init(&pid_speed[1], PID_POSITION, motor_speed_pid_1, 4000, 10);

    this->core.PID_Init(&pid_yaw, PID_POSITION, yaw_pid, 3000, 200);
}

/** 
* @brief PID�ٶȻ����㺯��
*
* @param set_speed Ŀ���ٶ�
* @return pid_speed[0].out�����ص���pwmռ�ձ�ֵ
*    @retval PID�ṹ�����fp32����
 */
fp32 PID_Controller::BRUSHED_MOTOR::MOTOR_Velocity_Realize_1(int16_t set_speed)
{
    pid_controller.core.PID_Calc(&pid_speed[0], motor1.Encoder, set_speed);

    return pid_speed[0].out;
}

/** 
* @brief PID�ٶȻ����㺯��
*
* @param set_speed Ŀ���ٶ�
* @return pid_speed[0].out�����ص���pwmռ�ձ�ֵ
*    @retval PID�ṹ�����fp32����
 */
fp32 PID_Controller::BRUSHED_MOTOR::MOTOR_Velocity_Realize_2(int16_t set_speed)
{
    pid_controller.core.PID_Calc(&pid_speed[1], motor2.Encoder, set_speed);

    return pid_speed[1].out;
}

/** 
* @brief PIDƫ���Ǽ��㺯��
*
* @param set_yaw Ŀ��Ƕ�
* @return pid_yaw.out�����ص���pwmռ�ձ�ֵ
*    @retval PID�ṹ�����fp32����
 */
fp32 PID_Controller::SENSORS::Yaw_Realize(fp32 set_yaw)
{
    euler.yaw=hwt101ct.Euler.yaw;
    pid_controller.core.PID_Calc(&pid_yaw, euler.yaw, set_yaw);

    return pid_yaw.out;
}