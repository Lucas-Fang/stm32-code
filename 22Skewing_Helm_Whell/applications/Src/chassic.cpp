#include "chassic.h"
#include "bsp_uart.h"
#include "can_receive.h"
#include <math.h>

ROBOT::CHASSIC chassic;

extern Rxbuffer all_rxbuff;

/**
 * @brief 偏置多轮初始化函数
 * 
 */
void ROBOT::CHASSIC::Helm_wheel_GetReady()
{
    chassic_msgs.Vx=all_rxbuff.remote_sense[2]/55.0f;
    chassic_msgs.Vy=all_rxbuff.remote_sense[3]/55.0f;
    chassic_msgs.Vomega=(all_rxbuff.remote_sense[0]/40.0f);//rad/s 解算公式中使用国际单位，所以omega为rad/s
    
}

/**
 * @brief 行走电机计算函数
 * @param void 
 */
void ROBOT::CHASSIC::Chassic_Drive_calc()
{
    fp32 Vx, Vy, Vomega;
    for (uint8_t i = 0; i < 3; i++)
    {
        wheel_msgs[i].A_P=wheel_msgs[i].Alpha-degreesToRadians(wheel_msgs[i].Phi);
    }
    //m/s -> rpm c620电调反馈的是电机屁股的速度，所以需要乘上电机的减速比*(3591.0/187.0)
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
 * @brief 舵电机计算函数   原公式omega为减，该成加来测试
 * @param void 
 */
void ROBOT::CHASSIC::Chassic_Steer_calc()//(60/(2*PI*B))*
{
    fp32 Vx,Vy ,Vomega;
    for (uint8_t i = 0; i < 3; i++)
    {
        wheel_msgs[i].P_A=degreesToRadians(wheel_msgs[i].Phi)-wheel_msgs[i].Alpha;
    }
    //m/s -> rpm  此处半径应取偏置距离，因为6020带动轮子以中心轴为中心，偏置距离为半径画圆 
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
 * @brief alpha测量初始化函数
 *        由于上电位置未知，先计算一下上电位置和0°之间的差角，加到total_angle上面，在can_receive里面实现
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
 * @brief alpha角度需要额外计算一下
 * 
 */   
void ROBOT::CHASSIC::Alpha_Calc()
{
    /*  因为编码器的值逆时针转动时减小，和在坐标系下面逆时针转动时角度增大不符所以用360减去测得角度，使用差值
        同时：init angle 要加在total angle的值里面，使记圈数正确增加，所以在结构体里面新加了一个Init angle
    */
    wheel_msgs[0].Alpha=360.0f-Encoder_To_Angle(can_bus.motor_6020[0].total_angle-can_bus.motor_6020[0].round_cnt*8192);
    wheel_msgs[1].Alpha=360.0f-Encoder_To_Angle(can_bus.motor_6020[1].total_angle-can_bus.motor_6020[1].round_cnt*8192);
    wheel_msgs[2].Alpha=360.0f-Encoder_To_Angle(can_bus.motor_6020[2].total_angle-can_bus.motor_6020[2].round_cnt*8192);
    
   for (uint8_t i = 0; i < 3; i++)
   {
       wheel_msgs[i].Alpha=degreesToRadians(wheel_msgs[i].Alpha);//转换为弧度制
   }
}
/**
 * @brief 编码值转换为角度，单位是度
 * 
 * @param encoder 
 * @return angle 度
 */
 fp32 Encoder_To_Angle(uint32_t encoder)
 {
     if(encoder<0)
     {
         encoder +=8192;
     }
     // 确保编码器值在 0 到 8191 的范围内
     encoder = encoder % 8193; // 8192 是 8191 + 1
     // 计算角度
     fp32 angle = (encoder / 8192.0f) * 360.0f;
     return angle;
 }

// 将角度转换为弧度
double degreesToRadians(double degrees) {
    return degrees * (PI / 180.0);
}
// 将弧度转换为角度
double radiansToDegrees(double radians) {
   return radians * (180.0 / PI);
}