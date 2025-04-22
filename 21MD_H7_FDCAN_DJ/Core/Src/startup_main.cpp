#include "startup_main.h"
#include "fdcan.h"
#include "fdcan_receive.h"
#include "pid_user.h"



void startup_main(void)
{	
	pid_controller.All_Device_Init();
	can_bus.bsp.Filter_Init(&hfdcan1);
	can_bus.bsp.FDCAN_Start(&hfdcan1);
	
#if isRTOS==0    	//如果是裸机开发
	for(;;)  //等同于while(true)
	{
		// can_bus.cmd.FDCAN1_Front(0, 1500, 0, 0);
		 can_bus.cmd.FDCAN1_Front(0, pid_controller.can_motor.CAN1_Position_Realize(8191*19, 2), 0, 0);
		HAL_Delay(2);
	}
#endif
}