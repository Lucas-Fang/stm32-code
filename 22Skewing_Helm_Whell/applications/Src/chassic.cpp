#include "chassic.h"
#include "bsp_uart.h"
#include "can_receive.h"
#include <math.h>

ROBOT::CHASSIC chassic;

extern Rxbuffer all_rxbuff;

/**
 * @brief ƫ�ö��ֳ�ʼ������
 * 
 */
void ROBOT::CHASSIC::Helm_wheel_GetReady()
{
    chassic_msgs.Vx=all_rxbuff.remote_sense[2]/55.0f;
    chassic_msgs.Vy=all_rxbuff.remote_sense[3]/55.0f;
    chassic_msgs.Vomega=(all_rxbuff.remote_sense[0]/40.0f);//rad/s ���㹫ʽ��ʹ�ù��ʵ�λ������omegaΪrad/s
    
}

/**
 * @brief ���ߵ�����㺯��
 * @param void 
 */
void ROBOT::CHASSIC::Chassic_Drive_calc()
{
    fp32 Vx, Vy, Vomega;
    for (uint8_t i = 0; i < 3; i++)
    {
        wheel_msgs[i].A_P=wheel_msgs[i].Alpha-degreesToRadians(wheel_msgs[i].Phi);
    }
    //m/s -> rpm c620����������ǵ��ƨ�ɵ��ٶȣ�������Ҫ���ϵ���ļ��ٱ�*(3591.0/187.0)
    Vx = chassic_msgs.Vx *(3591.0/187.0);//* (60/(2*PI*R))*(3591.0/187.0);
    Vy = chassic_msgs.Vy *(3591.0/187.0);//* (60/(2*PI*R))*(3591.0/187.0);
    Vomega = chassic_msgs.Vomega *(3591.0/187.0);//* 60/(2*PI)*(3591.0/187.0); 

    this->wheel_msgs[0].Drive_omega = 
        (1.0f/R)*(Vy*std::sin(wheel_msgs[0].Alpha)+Vx*std::cos(wheel_msgs[0].Alpha) +
        Vomega*L*std::sin(wheel_msgs[0].A_P));

    this->wheel_msgs[1].Drive_omega =
        (1.0f/R)*(Vy*std::sin(wheel_msgs[1].Alpha)+Vx*std::cos(wheel_msgs[1].Alpha) +
        Vomega*L*std::sin(wheel_msgs[1].A_P));

    this->wheel_msgs[2].Drive_omega =
        (1.0f/R)*(Vy*std::sin(wheel_msgs[2].Alpha)+Vx*std::cos(wheel_msgs[2].Alpha) +
        Vomega*L*std::sin(wheel_msgs[2].A_P));
}
/**
 * @brief �������㺯��   ԭ��ʽomegaΪ�����óɼ�������
 * @param void 
 */
void ROBOT::CHASSIC::Chassic_Steer_calc()//(60/(2*PI*B))*
{
    fp32 Vx,Vy ,Vomega;
    for (uint8_t i = 0; i < 3; i++)
    {
        wheel_msgs[i].P_A=degreesToRadians(wheel_msgs[i].Phi)-wheel_msgs[i].Alpha;
    }
    //m/s -> rpm  �˴��뾶Ӧȡƫ�þ��룬��Ϊ6020����������������Ϊ���ģ�ƫ�þ���Ϊ�뾶��Բ 
    /*

    */
    Vx = chassic_msgs.Vx ;//*(60/(2*PI*B));
    Vy = chassic_msgs.Vy ;//* (60/(2*PI*B));
    Vomega = chassic_msgs.Vomega ;//* 60/(2*PI);

    this->wheel_msgs[0].Steer_omega = 
        (1.0f/B)*(Vx*std::sin(wheel_msgs[0].Alpha)-Vy*std::cos(wheel_msgs[0].Alpha)) -
        (1.0f/B)*(Vomega*L*std::cos(wheel_msgs[0].P_A))-Vomega;
    this->wheel_msgs[1].Steer_omega = 
        (1.0f/B)*(Vx*std::sin(wheel_msgs[1].Alpha)-Vy*std::cos(wheel_msgs[1].Alpha)) -
        (1.0f/B)*(Vomega*L*std::cos(wheel_msgs[1].P_A))-Vomega;
    this->wheel_msgs[2].Steer_omega = 
        (1.0f/B)*(Vx*std::sin(wheel_msgs[2].Alpha)-Vy*std::cos(wheel_msgs[2].Alpha)) -
        (1.0f/B)*(Vomega*L*std::cos(wheel_msgs[2].P_A))-Vomega;

}

/**
 * @brief alpha������ʼ������
 *        �����ϵ�λ��δ֪���ȼ���һ���ϵ�λ�ú�0��֮��Ĳ�ǣ��ӵ�total_angle���棬��can_receive����ʵ��
 * 
 */
void ROBOT::CHASSIC::Alpha_Init()
{
    static bool Init_Alpha=1;
        if(Init_Alpha==1) {
            can_bus.motor_6020[0].init_angle = can_bus.motor_6020[0].angle-4649;
            can_bus.motor_6020[1].init_angle = can_bus.motor_6020[1].angle-6631;
            can_bus.motor_6020[2].init_angle = can_bus.motor_6020[2].angle-3900;

            Init_Alpha = 0;
        }
}

/**
 * @brief alpha�Ƕ���Ҫ�������һ��
 * 
 */   
void ROBOT::CHASSIC::Alpha_Calc()
{
    /*  ��Ϊ��������ֵ��ʱ��ת��ʱ��С����������ϵ������ʱ��ת��ʱ�Ƕ����󲻷�������360��ȥ��ýǶȣ�ʹ�ò�ֵ
        ͬʱ��init angle Ҫ����total angle��ֵ���棬ʹ��Ȧ����ȷ���ӣ������ڽṹ�������¼���һ��Init angle
    */
    wheel_msgs[0].Alpha=360.0f-Encoder_To_Angle(can_bus.motor_6020[0].total_angle-can_bus.motor_6020[0].round_cnt*8192);
    wheel_msgs[1].Alpha=360.0f-Encoder_To_Angle(can_bus.motor_6020[1].total_angle-can_bus.motor_6020[1].round_cnt*8192);
    wheel_msgs[2].Alpha=360.0f-Encoder_To_Angle(can_bus.motor_6020[2].total_angle-can_bus.motor_6020[2].round_cnt*8192);
    
   for (uint8_t i = 0; i < 3; i++)
   {
       wheel_msgs[i].Alpha=degreesToRadians(wheel_msgs[i].Alpha);//ת��Ϊ������
   }
}
/**
 * @brief ����ֵת��Ϊ�Ƕȣ���λ�Ƕ�
 * 
 * @param encoder 
 * @return angle ��
 */
 fp32 Encoder_To_Angle(uint32_t encoder)
 {
     if(encoder<0)
     {
         encoder +=8192;
     }
     // ȷ��������ֵ�� 0 �� 8191 �ķ�Χ��
     encoder = encoder % 8193; // 8192 �� 8191 + 1
     // ����Ƕ�
     fp32 angle = (encoder / 8192.0f) * 360.0f;
     return angle;
 }

// ���Ƕ�ת��Ϊ����
double degreesToRadians(double degrees) {
    return degrees * (PI / 180.0);
}
// ������ת��Ϊ�Ƕ�
double radiansToDegrees(double radians) {
   return radians * (180.0 / PI);
}