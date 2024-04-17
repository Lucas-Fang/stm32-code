#include "pid_user.h"

extern motor_measure_t motor_can1[8];                 /*�˸�������Եĸ������*/

pid_type_def pid_v_1[8],pid_pos_1[8];									/*�˸�������Ե�pid�������,���ٶȻ��ģ�λ�û��ģ�*/
pid_type_def pid_v_2[8],pid_pos_2[8];

//3508����
float motor_speed_3508_pid[3] = {10, 0.1, 0};					//�ٶȻ�
float motor_position_3508_pid[3] = {0.1, 0, 1};		  	//λ�û�
//2006����
float motor_speed_2006_pid[3] = {9, 0.1, 0};					//�ٶȻ�
float motor_position_2006_pid[3] = {0.2, 0, 0};				//λ�û�
	

#define LimitMax(input, max)   \
    {                          \
        if (input > max)       \
        {                      \
            input = max;       \
        }                      \
        else if (input < -max) \
        {                      \
            input = -max;      \
        }                      \
    }

		
		
		//PID��ʼ��
void PID_devices_Init(void)
{
	for(int i=0;i<4;i++)
	{
    PID_init(&pid_v_1[i], PID_POSITION, motor_speed_3508_pid, 10000, 6000);/*ǰ�ĸ������pid���������pidģʽ���ٶȻ�pid�ı���΢�ֻ������Σ����޷��������޷�*/
		PID_init(&pid_pos_1[i], PID_POSITION, motor_position_3508_pid, 400, 300);/*ǰ�ĸ������pid���������pidģʽ��λ�û�pid�ı���΢�ֻ������Σ����޷��������޷�*/
		
		PID_init(&pid_v_2[i], PID_POSITION, motor_speed_3508_pid, 10000, 6000);
		PID_init(&pid_pos_2[i], PID_POSITION, motor_position_3508_pid, 1500, 300);
	}
	
	for(int i=4;i<8;i++)
	{																																							/*�����ĸ������*/
    PID_init(&pid_v_1[i], PID_POSITION, motor_speed_3508_pid, 10000, 6000);
		PID_init(&pid_pos_1[i], PID_POSITION, motor_position_3508_pid, 400, 300);
		
		PID_init(&pid_v_2[i], PID_POSITION, motor_speed_3508_pid, 10000, 6000);
		PID_init(&pid_pos_2[i], PID_POSITION, motor_position_3508_pid, 400, 300);
	}
}


float PID_velocity_realize_1(float set_speed,int i)     											/*�ٶȻ��������ٶȣ������ţ�*/
{
		PID_calc(&pid_v_1[i-1],motor_can1[i-1].speed_rpm , set_speed);						/*����pid���㺯��������й�pid����ĸ�������������ǰ�ٶȣ������ٶȣ�*/
		return pid_v_1[i-1].out;																									/*����ֵ*/
}

float PID_position_realize_1(float set_pos,int i)															/*λ�û� ������λ�ã������ţ�(Ŀ��Ƕ�ֵ0-8191�����ID)*/
{

		PID_calc(&pid_pos_1[i-1],motor_can1[i-1].total_angle , set_pos);					/*����pid���㺯��������й�pid����ĸ�������������ǰλ�ã�����λ�ã�*/
		return pid_pos_1[i-1].out;																								/*����ֵ*/
}

float pid_call_1(float position,int i)																				/*PID˫�� �⻷λ�� �ڻ��ٶ�*/
{
		return PID_velocity_realize_1(PID_position_realize_1(position,i),i);			/*λ�û����صĲ�����Ϊ�ٶȻ�����ڲ�����Ҳ���������ٶȣ�*/
}

/*





�ٶȻ�����������ǰ�Ĳ��������ú�Ԥ�ڵĲ�����pid���㺯������Ƚ������������Ĵ�С�������ֵ��
ͨ������֮���ڵ���������������ã����ص���ֵ�Ĵ�С�������ٶȵĿ������Դﵽ�������ٶȡ�

λ�û������뵱ǰ������ڵ�λ�ã����ú�ϣ������ﵽ��λ�ã�pid���㺯��������������������Ĳ
�ڵ��������������ʹ��ʱ�����ص���ֵ���õ��ת���ﵽ������λ��

˫�����⻷λ�û�����������λ�ã�ͨ��λ�û��Ŀ��Ƶ����Ҫ�ﵽ���ٶȣ�����ֵ��Ϊ����ٶȻ�������ֵ��
��ͨ���ٶȻ��ļ��㷵�����տ��Ƶ�����еĵ����������������������������





*/



