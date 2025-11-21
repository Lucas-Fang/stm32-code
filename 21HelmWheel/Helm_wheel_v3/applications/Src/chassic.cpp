#include "chassic.h"
#include "FreeRTOSConfig.h"
#include "can_receive.h"
#include "pid.h"
#include "pid_user.h"
#include <cstdint>
#include <math.h>


#define PI 3.1415926



ROBOT robot;
ROBOT::CHASSIC::Euler euler;
ROBOT::Rxbuffer rxbuffer;
motor_target motor_6020[3];
motor_target motor_3508[3];
bool motor_flag=0;

/*舵轮方向归位*/
void ROBOT::CHASSIC::chassic_Init()
{
    fp32 motor_traget[4];

    for(;;)
    {
			if(NRF24L01_RxPacket(rxbuffer.remote_control))
     {
       HAL_Delay(10);
     }
        decode(&rxbuffer.remote_control[3],rxbuffer.remote_sense);
        // motor_traget[0]=pid_controller.can_motor.GM6020_VP_Dual_Loop_Realize_1(5500, 1);
        // motor_traget[1]=pid_controller.can_motor.GM6020_VP_Dual_Loop_Realize_1(1310, 2);
        // motor_traget[2]=pid_controller.can_motor.GM6020_VP_Dual_Loop_Realize_1(7550, 3);

        // can_bus.cmd.CAN1_Behind_gm6020(motor_traget[0],motor_traget[1], motor_traget[2], 0);
        // HAL_Delay(10);
        
        if((can_bus.motor_6020[0].angle>5450)&&(can_bus.motor_6020[0].angle<5550)
        &&(can_bus.motor_6020[2].angle>7500)&&(can_bus.motor_6020[2].angle<7600)
        &&(can_bus.motor_6020[1].angle>1250)&&(can_bus.motor_6020[1].angle<1350))
        {
            motor_flag=1;
            for(uint8_t i = 0;i<3;i++){
                can_bus.motor_6020[i].last_angle=0;
                can_bus.motor_6020[i].offset_angle=0;
                can_bus.motor_6020[i].total_angle=0;
                can_bus.motor_6020[i].msg_cnt=0;
                can_bus.motor_6020[i].round_cnt=0;
            }
            break;
        }
    }
}


void ROBOT::CHASSIC::Helm_Move_Calc(fp32 v_y,fp32 v_x,fp32 v_omega)
{
    fp32 speed_x[3]={0};
    fp32 speed_y[3]={0};
    fp32 theta[3]={0};

    speed_x[0]=(v_x-v_omega*1.0f);
    speed_x[1]=(v_x+v_omega*0.5f);
    speed_x[2]=(v_x+v_omega*0.5f);

    speed_y[0]=(v_y+v_omega*0.0f);
    speed_y[1]=(v_y-v_omega*(sqrt(3)/2));
    speed_y[2]=(v_y+v_omega*(sqrt(3)/2));

    for(uint8_t i=0;i<3;i++)
    {
        motor_3508[i].speed=std::sqrt(pow((speed_x[i]),2)+pow(speed_y[i],2));
    }
    
    for(uint8_t i=0;i<3;i++)
    {
        if(speed_x[i]==0&&speed_y[i]!=0)
        {
            if(speed_y[i]<0)
            {
                theta[i]=270.0f;
            }
            if(speed_y[i]>0)
            {
                theta[i]=90.0f;
            }
            motor_6020[i].position=robot.chassic.Angle_To_Encoder(theta[i]);
        }
        else
        {
            // motor_6020[i].position=robot.chassic.Angle_Calc(speed_x[i], speed_y[i]); 
            motor_6020[i].angle=robot.chassic.Angle_Calc(speed_x[i], speed_y[i]);
            motor_6020[i].position=robot.chassic.Angle_To_Encoder(motor_6020[i].angle);
        }
//        for(uint8_t i =0;i<3;i++)
//        {
//            if(motor_6020[i].position<=4092) motor_6020[i].position=-motor_6020[i].position;
//            if(motor_6020[i].position>4092)  motor_6020[i].position=8191-motor_6020[i].position;
    //    }

    }
}

void ROBOT::CHASSIC::Chassic_Move()
{
    fp32 v_3508[3]   = {0};
    fp32 pos_6020[3] = {0};
    // for(uint8_t i=0;i<3;i++)
    // {
    //     motor_3508[i].speed*=pow(cos((double)Encoder_To_Angle(ABS(motor_6020[i].position
    //     -can_bus.motor_6020[i].total_angle))),2);
    //  }
   v_3508[0]=pid_controller.can_motor.CAN1_Velocity_Realize(motor_3508[2].speed, 1);
   v_3508[1]=pid_controller.can_motor.CAN1_Velocity_Realize(motor_3508[0].speed, 2);
   v_3508[2]=pid_controller.can_motor.CAN1_Velocity_Realize(motor_3508[1].speed, 3);
/*计算编码器要偏移的角度*/
   pos_6020[0]=pid_controller.can_motor.GM6020_VP_Dual_Loop_Realize_2(-motor_6020[2].position, 1);
   pos_6020[1]=pid_controller.can_motor.GM6020_VP_Dual_Loop_Realize_2(-motor_6020[0].position, 2);
   pos_6020[2]=pid_controller.can_motor.GM6020_VP_Dual_Loop_Realize_2(-motor_6020[1].position, 3);   

   can_bus.cmd.CAN1_Behind_gm6020(pos_6020[0], pos_6020[1], pos_6020[2], 0);
   can_bus.cmd.CAN1_Front_gm3508(v_3508[0], v_3508[1], v_3508[2], 0);
		
}

/**
 * @brief  弧度转换为角度
 * @param  rad 弧度值
 * @retval deg 角度值
 * @attention
 */
fp32 ROBOT::CHASSIC::rad2deg(fp32 rad)
{
	fp32 deg;
	deg = (fp32)(rad * (180.0f / PI));
	return deg;
}
//角度换算编码值
fp32 ROBOT::CHASSIC::Angle_To_Encoder(fp64 theta)
{
    fp32 encoder=0;
    encoder = (theta/360.0f)*8191.0f;
    return encoder;
}
//编码值换算角度(弧度制)
fp32 ROBOT::CHASSIC::Encoder_To_Angle(fp32 encoder)
{
    fp32 angle=0;
    angle=(encoder/8191.0f)*2*PI;
    return angle;
}

/**
 * @brief  舵电机角度计算，最后输出舵电机要转过的角度
 * @param  vx 每个轮子的x方向速度
 * @param  vy 每个轮子的y方向速度
 * @retval angle 角度值（0°-360°）
 * @attention 此函数是将-180°-180°的角度转换为0°-360°
 */
fp32 ROBOT::CHASSIC::Angle_Calc(fp32 vx,fp32 vy)
{
    fp32 angle;
    fp32 theta;

    theta=std::atan2(vy,vx);
    //第一象限
    if(vx>0&&vy>=0)
    {
        angle=robot.chassic.rad2deg(theta);
    }
    //第二象限
    else if (vx<0&&vy>=0)
    {
        angle=robot.chassic.rad2deg(theta);
    }
    //第三象限
    else if(vx<0&&vy<0)
    {
        angle=robot.chassic.rad2deg(theta)+360.0f;
    }
    //第四象限
    else if(vx>0&&vy<0)
    {
        angle=robot.chassic.rad2deg(theta)+360.0f;
    }

    return angle;
}