#ifndef __CHASSIC_H_
#define __CHASSIC_H_

#include <cstdint>
#ifndef __cplusplus

extern "C"
{
#endif 


#include "main.h"
#include "struct_typedef.h"
#include "nrf.h"
	
	
// #define ABS(x) ( (x)>0?(x):-(x) )
typedef struct 
{
	int Encoder;
	fp32 last_speed;
	fp32 speed;
	int16_t temperature;
	fp32 angle;
	fp32 position;

}motor_target;

class ROBOT
{
	public:
/**********************************************************************************/
		class CHASSIC
		{
			public:

			int16_t Motor_Speed_Target[4];
			//底盘结构体
			typedef struct
			{
				int16_t vx;
				int16_t vy;
				int16_t vomega;
				
			}remote_control_speed;
			
			typedef struct
			{
				int16_t pitch;
				int16_t yaw;
				int16_t roll;
			}Euler;
			

			void chassic_Init();
			void Helm_Move_Calc(fp32 v_y,fp32 v_x,fp32 v_omega);
			void Chassic_Move();
			fp32 Angle_To_Encoder(fp64 theta);
			fp32 Encoder_To_Angle(fp32 encoder);
			fp32 rad2deg(fp32 rad);
			fp32 Angle_Calc(fp32 vx,fp32 vy);

			// class ENCODER
			// {
			// 	public:
			// 	void Encoder_Obtain();
			// 	void Encoder_filtering();
			// }encoder;
		}chassic;
/******************************************************************************************/
		typedef struct 
		{
			uint8_t odometer[1];
			uint8_t remote_control[10];
			int16_t remote_sense[4];
			uint8_t upper[1];
			// typedef struct
			// {
			// 	fp32 pos_x;
			// 	fp32 pos_y;
			// 	fp32 yaw;
			// 	fp32 omega;
			// }Odometer;
			// typedef struct
			// {
			// 	fp32 V_X;
			// 	fp32 V_Y;
			// 	fp32 V_Omega;
			// }Upper;
		}Rxbuffer;
};

//robot类的对象
extern ROBOT robot;




#ifndef __cplusplus
}
#endif // !1

#endif // !