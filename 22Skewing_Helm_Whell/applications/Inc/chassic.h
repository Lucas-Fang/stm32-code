#ifndef __CHASSIC_H_
#define __CHASSIC_H_


#ifndef __cplusplus

extern "C"
{
#endif 

#include "main.h"
#include "struct_typedef.h"
/*
B      ƫ�þ���
R      ���ӵİ뾶
L      ����ת�ᵽ�����˵��̵ľ���
theta  ����ת���ĽǶȣ��ֵ��������
Alpha  ƫ��������ڳ�������ϵ�ļнǣ������Ƕȣ�
Eta    ƫ�����������������ϵ�ļн�
Phi    ĳһ�������복������ϵԭ�����������x������ļн�


Drive_omega     �ֵ���ٶ�
Steer_omega     �����ٶ�
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
        fp64 Drive_omega;       //�ֵ���ٶ�
        fp64 Steer_omega;       //�����ٶ�
        fp32 Alpha;             //ƫ��������ڳ�������ϵ�ļнǣ������Ƕȣ�
        fp32 Phi;               //ĳһ�������복������ϵԭ�����������x������ļн�
            fp32 A_P;
            fp32 P_A;
        /**
         * @brief Construct a new wheel msgs object�ṹ�幹�캯��
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
               //ʹ�ó�ʼ���б��ʼ����Ա���� phi��ֵ��������̶�λ���йأ��Ǹ���ֵ
               WHEEL_MSGS(0.0f,0.0f,0.0f,135.0f),
               WHEEL_MSGS(0.0f,0.0f,0.0f,45.0f),
               WHEEL_MSGS(0.0f,0.0f,0.0f,270.0f)
           }{
               //�˴�Ϊ�����壻
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
