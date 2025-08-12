<<<<<<< HEAD
#ifndef __CHASSIC_H_ 
#define __CHASSIC_H_

#include <cstdint>
#ifdef __cplusplus

extern "C"
{
#endif

#include "struct_typedef.h"
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_usart.h"
#include "pid_user.h"

	
#define FRONT_WHEEL_DISTANCE	0.255//M
#define SIDE_WHELL_DISTANCE   0.105//M
	
	
void Front_L(int16_t speed);
void Front_R(int16_t speed);
void Back_L(int16_t speed);
void Back_R(int16_t speed);
void Motor_Move(void);


class ROBOT
{
	public:
		class CHASSIC
		{
			public:
			int16_t Motor_Speed_Target[4];
			
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
			
			typedef struct 
			{
				int Encoder;
				fp32 last_speed;
				int16_t temperature;
				fp32 angle;

			}Motor;

			void chassic_speed_calc(int16_t pwm_x,int16_t pwm_y,int16_t pwm_yaw);
			
			class ENCODER
			{
				public:

				void Encoder_Obtain();
				void Encoder_filtering();
			}encoder;
		}chassic;
};

//robot类的对象
extern ROBOT robot;

#ifdef __cplusplus
}
#endif


#endif
=======
#ifndef __CHASSIC_H_ 
#define __CHASSIC_H_

#include <cstdint>
#ifdef __cplusplus

extern "C"
{
#endif

#include "struct_typedef.h"
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_usart.h"
#include "pid_user.h"

	
#define FRONT_WHEEL_DISTANCE	0.255//M
#define SIDE_WHELL_DISTANCE   0.105//M
	
	
void Front_L(int16_t speed);
void Front_R(int16_t speed);
void Back_L(int16_t speed);
void Back_R(int16_t speed);
void Motor_Move(void);


class ROBOT
{
	public:
		class CHASSIC
		{
			public:
			int16_t Motor_Speed_Target[4];
			
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
			
			typedef struct 
			{
				int Encoder;
				fp32 last_speed;
				int16_t temperature;
				fp32 angle;

			}Motor;

			void chassic_speed_calc(int16_t pwm_x,int16_t pwm_y,int16_t pwm_yaw);
			
			class ENCODER
			{
				public:

				void Encoder_Obtain();
				void Encoder_filtering();
			}encoder;
		}chassic;
};

//robot类的对象
extern ROBOT robot;

#ifdef __cplusplus
}
#endif


#endif
>>>>>>> 00ac74e (9.6)
