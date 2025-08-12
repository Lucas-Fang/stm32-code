#ifndef __CHASSIC_H_
#define __CHASSIC_H_

#ifdef __cplusplus
extern "C"
{
#endif 

#include "main.h"
#include "struct_typedef.h"

#define Radius  0.35//m	
#define WHEEL_Radius 0.07//m
#define PI 3.1415926 
 //true:����ң������Ϣ   false��������λ��������Ϣ
	
// #define ABS(x) ( (x)>0?(x):-(x) )


typedef struct
{
    bool top;
    bool bottom;
}ROD_STATE;
//���̽ṹ��
typedef struct
{
	fp32 vx;
	fp32 vy;
	fp32 vomega;
				
}remote_control_speed;
			
typedef struct
{
	int16_t pitch;
	int16_t yaw;
	int16_t roll;
}Euler;

class ROBOT
{
	public:
		ROD_STATE rod_state;
		bool stop;
		fp32 Launch_Angle;
		fp32 upper_data[5];
		fp32 target_ball_angle;
		uint8_t robot_commend;
		int8_t BT_target_angle;
		class CHASSIC
		{
			public:
			remote_control_speed Chassic_Move_Data;

			void Omni_Move_Calc();
			void Chassic_Move();
			void Chassic_Mode();
			void Coordinate_Transformation();
			fp32 rad2deg(fp32 rad);


	private:
			fp32 Motor_Speed_Target[4];

		}chassic;
};

//robot��Ķ���
extern ROBOT robot;


#ifdef __cplusplus
}
#endif 

#endif 