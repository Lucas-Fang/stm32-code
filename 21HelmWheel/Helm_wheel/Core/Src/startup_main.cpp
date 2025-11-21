#include "startup_main.h"
#include "bsp_delay.h"
#include "can_receive.h"
#include "chassic.h"
#include "pid_user.h"



extern ROBOT::Rxbuffer rxbuffer;
extern fp32 motor_traget[4];
void startup_main(void)
{
  bsp_delay.f4.Init(168);

  NRF24L01_Init();
  while (NRF24L01_Check())
  {
    HAL_Delay(30);
  }
  NRF24L01_RX_Mode();

  pid_controller.All_Device_Init();

  can_bus.bsp.Filter_Init(&hcan1);
  can_bus.bsp.CAN_Start(&hcan1);

  HAL_TIM_Base_Start_IT(&htim7);
//  HAL_UART_Receive_IT(&huart4, rxbuffer.odometer, 1);
  robot.chassic.chassic_Init();

	
#if isRTOS==0    	//如果是裸机开发
	for(;;)  //等同于while(true)
	{

   if(NRF24L01_RxPacket(rxbuffer.remote_control))
   {
     HAL_Delay(10);
   }
   decode(&rxbuffer.remote_control[3],rxbuffer.remote_sense);


		

//can_bus.cmd.CAN1_Behind_gm6020(2000, 0, 0, 0);
	
	
	}
#endif
}