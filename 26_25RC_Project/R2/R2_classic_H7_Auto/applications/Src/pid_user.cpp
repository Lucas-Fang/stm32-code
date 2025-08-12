#include "pid_user.h"
#include "chassic.h"
#include "fdcan_receive.h"
#include "pid.h"
#include "struct_typedef.h"


/*PID����������*/
PID_Controller pid_controller;
/***************/

//PID�������(�ṹ��)
pid_type_def pid_v_1[8],pid_pos_1[8];
pid_type_def pid_v_2[8],pid_pos_2[8];
pid_type_def pid_yaw;
pid_type_def pid_pos_x;
pid_type_def pid_pos_y;

pid_type_def pid_pos_mt6701_handel;

//���PID����
fp32 motor_speed_3508_pid[3] = {18, 0, 2};//����3508����
fp32 motor_speed_3508_pid_p[3] = {15,0, 4};//��̨�Ƕ�3508����
// fp32 motor_position_3508_pid[3] = {0.6, 0.001, 0.1};

fp32 MT6701_pos_pid[3] = {-62,-0,-5};

//��λPID����
// fp32 motor_yaw_pid[3] = {120,0,0.1};
// fp32 motor_pos_x_pid[3] = {6,0,0};
// fp32 motor_pos_y_pid[3] = {6,0,0};


/**
 * @brief       PID�豸��ʼ��
 * @param       void
 * @retval      void
 * @note        ���ｫ���е�PID�豸�Ĳ������г�ʼ��������Kp,Ki,Kd,I_limit(�����޷�),O_limit(���޷�)���������,����ֵ������pid_type_def����С�
 */
void PID_Controller::All_Device_Init(void)
{
	//����PID
	for(int i=0;i<4;i++)
	{
    this->core.PID_Init(&pid_v_1[i], PID_POSITION, motor_speed_3508_pid, 10000, 6000,10);
	// this->core.PID_Init(&pid_pos_1[i], PID_POSITION, motor_position_3508_pid, 2000, 300);
	}
	// //������λ���PID
	for(int i=4;i<8;i++)
	{		
    this->core.PID_Init(&pid_v_1[i], PID_POSITION, motor_speed_3508_pid_p, 9000, 2000,10);
	//this->core.PID_Init(&pid_pos_1[i], PID_POSITION, motor_position_3508_pid, 1500, 300,100);
	}
	
	this->core.PID_Init(&pid_pos_mt6701_handel, PID_POSITION, MT6701_pos_pid, 1000, 300, 0.5);
//   //��λPID
// 	this->core.PID_Init(&pid_yaw,PID_POSITION,motor_yaw_pid,3000,1500);
// 	this->core.PID_Init(&pid_pos_x,PID_POSITION,motor_pos_x_pid,1500,1500);
// 	this->core.PID_Init(&pid_pos_y,PID_POSITION,motor_pos_y_pid,1500,1500);
}

fp32 PID_Controller::CAN_MOTOR::MT6701_Position_Realize(fp32 set_pos)
{//-34.66�� - 46��

	if (set_pos >= -34.66 || set_pos <= 46) {
		set_pos = set_pos;
	}
	else if (set_pos < -34.6 ) {
		set_pos = -34.5;
	} 
	else if (set_pos > 46) {
		set_pos = 46;
	}

	pid_controller.core.PID_Calc(&pid_pos_mt6701_handel, robot.Launch_Angle, set_pos);
	return pid_pos_mt6701_handel.out;

}



/**
 * @brief       CAN1�ٶȻ�
 * @param       set_speed���ٶ�rpm
 * @param       i��������Ϊ��ŵģ�Ҳ����i=���ID��-1
 * @retval      ���ֵ
 * @note        ���ֵ������ʲôֵ����Ҫ���ú��������ֵ��������ʲô��
 */
fp32 PID_Controller::CAN_MOTOR::CAN1_Velocity_Realize(fp32 set_speed,int i)
{
	pid_controller.core.PID_Calc(&pid_v_1[i-1],can_bus.motor_can1[i-1].speed_rpm , set_speed);
	return pid_v_1[i-1].out;
}

/**
 * @brief       CAN1λ�û�
 * @param       set_pos���Ƕ�ֵ��Ϊ��ԽǶ�ֵ�����꿴��˵����
 * @param       i��������Ϊ��ŵģ�Ҳ����i=���ID��-1
 * @retval      ���ֵ
 * @note        ���ֵ������ʲôֵ����Ҫ���ú��������ֵ��������ʲô��
 */
fp32 PID_Controller::CAN_MOTOR::CAN1_Position_Realize(fp32 set_pos,int i)
{
	pid_controller.core.PID_Calc(&pid_pos_1[i-1],can_bus.motor_can1[i-1].total_angle , set_pos);
	return pid_pos_1[i-1].out;
}

fp32 PID_Controller::CAN_MOTOR::CAN1_Absolute_Pos_Realize(fp32 set_pos , int i)
{
	pid_controller.core.PID_Calc(&pid_pos_1[i-1], can_bus.motor_can1[i-1].angle, set_pos);
	return pid_pos_1[i-1].out;
}
/**
 * @brief       CAN1�����ٶ�˫��
 * @param       set_pos���Ƕ�ֵ��Ϊ��ԽǶ�ֵ�����꿴��˵����
 * @param       i��������Ϊ��ŵģ�Ҳ����i=���ID��-1
 * @retval      ���ֵ
 * @note        ���ֵ������ʲôֵ����Ҫ���ú��������ֵ��������ʲô��
 */
fp32 PID_Controller::CAN_MOTOR::CAN1_VP_Dual_Loop_Realize(fp32 set_pos,int i,int mode)
{
	if (mode == PID_ABSOLUTE_POS) {
		return CAN1_Velocity_Realize(CAN1_Absolute_Pos_Realize(set_pos,i),i);
	} 

	if (mode == PID_RELATIVE_POS) {
		return CAN1_Velocity_Realize(CAN1_Position_Realize(set_pos,i),i);
	}

	if (mode == PID_EXTERNAL_POS) {
		
		return CAN1_Velocity_Realize(MT6701_Position_Realize(set_pos),i);
	}
	else {
		return 0;
	}
}

/**
 * @brief       CAN2�ٶȻ�
 * @param       set_speed���ٶ�rpm
 * @param       i��������Ϊ��ŵģ�Ҳ����i=���ID��-1
 * @retval      ���ֵ
 * @note        ���ֵ������ʲôֵ����Ҫ���ú��������ֵ��������ʲô��
 */
fp32 PID_Controller::CAN_MOTOR::CAN2_Velocity_Realize(fp32 set_speed,int i)
{
	pid_controller.core.PID_Calc(&pid_v_2[i-1],can_bus.motor_can2[i-1].speed_rpm , set_speed);
	return pid_v_2[i-1].out;
}

/**
 * @brief       CAN2λ�û�
 * @param       set_pos���Ƕ�ֵ��Ϊ��ԽǶ�ֵ�����꿴��˵����
 * @param       i��������Ϊ��ŵģ�Ҳ����i=���ID��-1
 * @retval      ���ֵ
 * @note        ���ֵ������ʲôֵ����Ҫ���ú��������ֵ��������ʲô��
 */
fp32 PID_Controller::CAN_MOTOR::CAN2_Position_Realize(fp32 set_pos,int i)
{
	pid_controller.core.PID_Calc(&pid_pos_2[i-1],can_bus.motor_can2[i-1].total_angle , set_pos);
	return pid_pos_2[i-1].out;
}

/**
 * @brief       CAN2�����ٶ�˫��
 * @param       set_pos���Ƕ�ֵ��Ϊ��ԽǶ�ֵ�����꿴��˵����
 * @param       i��������Ϊ��ŵģ�Ҳ����i=���ID��-1
 * @retval      ���ֵ
 * @note        ���ֵ������ʲôֵ����Ҫ���ú��������ֵ��������ʲô��
 */
fp32 PID_Controller::CAN_MOTOR::CAN2_VP_Dual_Loop_Realize(fp32 set_pos,int i)
{
	return CAN2_Velocity_Realize(CAN2_Position_Realize(set_pos,i),i);
}

/**
 * @brief       �����PID
 * @param       set_yaw��Ŀ�꺽���
 * @retval      ���ֵ
 * @note        ���ֵ������ʲôֵ����Ҫ���ú��������ֵ��������ʲô��
 */
fp32 PID_Controller::SENSORS::Yaw_Realize(fp32 set_yaw)
{
	//PID_calc(&pid_yaw,absolute_chassis_measure.Euler.yaw_total,set_yaw);
	//return pid_yaw.out;
	(void)set_yaw;
	return 0;
}

/**
 * @brief       X����PID
 * @param       set_pos_x��Ŀ��X����ֵ
 * @retval      ���ֵ
 * @note        ���ֵ������ʲôֵ����Ҫ���ú��������ֵ��������ʲô��
 */
fp32 PID_Controller::SENSORS::Pos_X_Realize(fp32 set_pos_x)
{
	//PID_calc(&pid_pos_x,absolute_chassis_measure.Position.Pos_X,set_pos_x);
	//return pid_pos_x.out;
	(void)set_pos_x;
	return 0;
}

/**
 * @brief       Y����PID
 * @param       set_pos_y��Ŀ��Y����ֵ
 * @retval      ���ֵ
 * @note        ���ֵ������ʲôֵ����Ҫ���ú��������ֵ��������ʲô��
 */
fp32 PID_Controller::SENSORS::Pos_Y_Realize(fp32 set_pos_y)
{
	//PID_calc(&pid_pos_y,absolute_chassis_measure.Position.Pos_Y,set_pos_y);
	//return pid_pos_y.out;
	(void)set_pos_y;
	return 0;
}

