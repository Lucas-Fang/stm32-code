#include "timer_user.h"
#include "chassic.h"
#include "pid_user.h"
#include "can_receive.h"
#include "bsp_uart.h"

extern float x1,y1,w1;


fp32 motor_traget[4];
extern ROBOT::Rxbuffer rxbuffer;
extern ROBOT::CHASSIC::Euler euler;
extern bool motor_flag;
fp32 set_yaw=0;
extern int16_t speed;
extern uint8_t odometer_data[12];

extern "C"
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

  Send_Cmd_Data(0,odometer_data,12);

  if(htim->Instance == TIM7)
  {
        if(motor_flag==1)
        {

//            robot.chassic.Helm_Move_Calc(
//            rxbuffer.remote_sense[0],
//            rxbuffer.remote_sense[1], 
//            rxbuffer.remote_sense[2]);//+pid_controller.sensors.Yaw_Realize(set_yaw)
//           
//            robot.chassic.Helm_Move_Calc(
//            y1*1000,
//            x1*1000, 
//            w1);//+pid_controller.sensors.Yaw_Realize(set_yaw)

//	         robot.chassic.Chassic_Move();
        }
        if(motor_flag==0)
        {
          can_bus.cmd.CAN1_Behind_gm6020(
         pid_controller.can_motor.GM6020_VP_Dual_Loop_Realize_1(5500, 1),
          pid_controller.can_motor.GM6020_VP_Dual_Loop_Realize_1(1310, 2), 
          pid_controller.can_motor.GM6020_VP_Dual_Loop_Realize_1(7550, 3),
         0);
        }		
  }//pid_controller.can_motor.CAN1_Velocity_Realize(500, 1)
  //  can_bus.cmd.CAN1_Behind_gm6020(pid_controller.can_motor.GM6020_VP_Dual_Loop_Realize_2(4068, 1),
  //   pid_controller.can_motor.GM6020_VP_Dual_Loop_Realize_2(4068, 2), 
  //   pid_controller.can_motor.GM6020_VP_Dual_Loop_Realize_2(4068, 3),
  //   0);
  //   can_bus.cmd.CAN1_Front_gm3508(
  //     pid_controller.can_motor.CAN1_Velocity_Realize(500, 1), 
  //     pid_controller.can_motor.CAN1_Velocity_Realize(500, 2), 
  //     pid_controller.can_motor.CAN1_Velocity_Realize(500, 3), 
  //     0);
}