#include "startup_main.h"
#include "can.h"
#include "can_receive.h"
#include "bsp_delay.h"
#include "bsp_uart.h"
#include "chassic.h"
#include "pid.h"
#include "pid_user.h"


extern Rxbuffer all_rxbuff;

void startup_main(void)
{
	bsp_delay.f4.Init(168);
	pid_controller.All_Device_Init();

	// can_bus.bsp.Filter_Init(&hcan1);
	// can_bus.bsp.CAN_Start(&hcan1);
	can_bus.bsp.Filter_Init(&hcan2);
	can_bus.bsp.CAN_Start(&hcan2);
	
	HAL_UART_Receive_DMA(&huart1, all_rxbuff.DR16, 18);

	bsp_delay.f4.ms(1000);//确保所有设备已经启动，编码器角度获取正常
	chassic.Alpha_Init();

	HAL_TIM_Base_Start_IT(&htim7);
#if isRTOS==0    	//如果是裸机开发
	for(;;)  //等同于while(true)
	{

	}
#endif
}

extern "C"
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	Get_Remote_Date();
	
	chassic.Helm_wheel_GetReady();
	chassic.Alpha_Calc();  
	chassic.Chassic_Steer_calc();
	chassic.Chassic_Drive_calc();

	can_bus.cmd.CAN2_Front(
		pid_controller.can_motor.CAN2_Velocity_Realize(chassic.wheel_msgs[0].Drive_omega, 1),
		pid_controller.can_motor.CAN2_Velocity_Realize(chassic.wheel_msgs[2].Drive_omega, 2), 
		pid_controller.can_motor.CAN2_Velocity_Realize(chassic.wheel_msgs[1].Drive_omega, 3), 
		0);
    can_bus.cmd.CAN2_Behind(
		pid_controller.can_motor.GM6020_Velocity_Realize(chassic.wheel_msgs[0].Steer_omega, 1), 
	    pid_controller.can_motor.GM6020_Velocity_Realize(chassic.wheel_msgs[1].Steer_omega, 2),
	   pid_controller.can_motor.GM6020_Velocity_Realize(chassic.wheel_msgs[2].Steer_omega,3) ,
	   0);


/*--------------------------------- 以下为测试电机代码 -------------------------------------------- */
	// can_bus.cmd.CAN2_Behind(
	// 	pid_controller.can_motor.GM6020_Velocity_Realize((PI)*60/(2*PI), 1), 
	//     0,
	//     0,
	//     0);
	// can_bus.cmd.CAN2_Front(
	// 	0,
	// 	0,
	// 	pid_controller.can_motor.CAN2_Velocity_Realize(1500, 3),
	// 	0);
}