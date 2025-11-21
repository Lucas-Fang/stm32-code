#include "startup_main.h"
#include "bsp_delay.h"
#include "can_receive.h"
#include "chassic.h"
#include "pid_user.h"
#include "usart.h"



extern ROBOT::Rxbuffer rxbuffer;
extern uint8_t rxbuf_odometer[1];
extern fp32 motor_traget[4];
extern bool motor_flag;

//  int16_t speed = 100 ;
void startup_main(void)
{
  bsp_delay.f4.Init(168);

//   NRF24L01_Init();
//   while (NRF24L01_Check())
//   {
//     HAL_Delay(30);
//   }
//   NRF24L01_RX_Mode();

  pid_controller.All_Device_Init();

  can_bus.bsp.Filter_Init(&hcan1);
  can_bus.bsp.CAN_Start(&hcan1);

  HAL_TIM_Base_Start_IT(&htim7);
 HAL_UART_Receive_IT(&huart2, rxbuf_odometer, 1);



	
//  robot.chassic.chassic_Init();


#if isRTOS==1    	//如果是裸机开发
	for(;;)  //等同于while(true)
	{
//    			if(NRF24L01_RxPacket(rxbuffer.remote_control))
//     {
//       HAL_Delay(10);
//     }
//        decode(&rxbuffer.remote_control[3],rxbuffer.remote_sense);
    // if(speed==100)
    // {
    //   for (int16_t i = 100;i >-100;i--)
    //   {
    //    speed --;
	  //    printf("%d,%d\r\n ",speed,can_bus.motor_6020[0].speed_rpm);

    //    HAL_Delay(10);
    //   }
    // }
    // if(speed==-100)
    // {
    //   for (int16_t i=-100;i<100;i++)
    //   {
    //    speed ++;
	  //    printf("%d,%d\r\n ",speed,can_bus.motor_6020[0].speed_rpm);
	
    //    HAL_Delay(10);
    //   }
    // }

	 
	}
#endif
}