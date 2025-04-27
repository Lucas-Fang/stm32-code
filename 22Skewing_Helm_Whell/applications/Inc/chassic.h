#ifndef __CHASSIC_H_
#define __CHASSIC_H_


#ifndef __cplusplus

extern "C"
{
#endif 

#include "main.h"
#include "struct_typedef.h"
/*
B      偏置距离
R      轮子的半径
L      轮子转轴到机器人底盘的距离
theta  轮子转过的角度（轮电机带动）
Alpha  偏置轮相对于车体坐标系的夹角（舵电机角度）
Eta    偏置轮相对于世界坐标系的夹角
Phi    某一个轮子与车体坐标系原点连线相对于x轴正向的夹角


Drive_omega     轮电机速度
Steer_omega     舵电机速度
*/

#define B   0.03582 //m
#define R   0.05  //m
#define L   0.13  //m
#define CHASSIC_RADIUS 0.25 
#define PI 3.1415927



namespace ROBOT {

    struct CHASSIC_MSGS
    {
        fp32 Vx;
        fp32 Vy;
        fp32 Vomega;
    };

    struct WHEEL_MSGS
    {
        fp64 Drive_omega;       //轮电机速度
        fp64 Steer_omega;       //舵电机速度
        fp32 Alpha;             //偏置轮相对于车体坐标系的夹角（舵电机角度）
        fp32 Phi;               //某一个轮子与车体坐标系原点连线相对于x轴正向的夹角
            fp32 A_P;
            fp32 P_A;
        /**
         * @brief Construct a new wheel msgs object结构体构造函数
         * 
         * @param drive_omega 
         * @param steer_omega 
         * @param alpha 
         * @param phi 
         */
        WHEEL_MSGS(fp32 drive_omega,fp32 steer_omega,fp32 alpha,fp32 phi)
            :Drive_omega(drive_omega),Steer_omega(steer_omega),Alpha(alpha),Phi(phi)
            {

            }
    };

    class CHASSIC
    {
        public:
        WHEEL_MSGS wheel_msgs[3];
        CHASSIC_MSGS chassic_msgs;

        void Helm_wheel_GetReady();
        void Chassic_Drive_calc();
        void Chassic_Steer_calc();
        void Alpha_Calc();
        void Alpha_Init();

       CHASSIC()
           :wheel_msgs
           {
               //使用初始化列表初始化成员变量 phi的值和轮子轴固定位置有关，是个定值
               WHEEL_MSGS(0.0f,0.0f,0.0f,135.0f),
               WHEEL_MSGS(0.0f,0.0f,0.0f,45.0f),
               WHEEL_MSGS(0.0f,0.0f,0.0f,270.0f)
           }{
               //此处为函数体；
           }
    };
}
double degreesToRadians(double degrees);
double radiansToDegrees(double radians);
fp32 Encoder_To_Angle(uint32_t encoder);

extern ROBOT::CHASSIC chassic;

#ifndef __cplusplus
}
#endif 

#endif 
