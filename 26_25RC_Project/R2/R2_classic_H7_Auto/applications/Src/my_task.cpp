#include "my_task.h"
#include "FreeRTOSConfig.h"
#include "chassic.h"
#include "fdcan_receive.h"
#include "pid.h"
#include "pid_user.h"
#include "Communition.h"
#include <cstddef>


extern "C"{
extern osThreadId ChangeAngleTaskHandle;
extern osThreadId StartLaunchTaskHandle;
}

bool wake_fireball_task;
   uint8_t current_val;
extern Rxbuffer all_rxbuff;
extern int16_t N5065_traget_speed[2];

//�Զ���⵽�ٶȴ���0�����ȶ���ʼ��ʱ3s���Զ�Ͷ����������¼��������ʱʹ�ø�ģʽ������
/*����ʱ�Զ���ʱ���������߼�
     ͨӴ����ģ�����÷���Ŀ���ٶȣ�1s֮�ڷ����ٶ��ȶ�����Ϊ���䣬
     ��������ٶ�һֱ�ڱ仯�����±�Ϊ0����ôȡ������*/
volatile int16_t target_launch_speed = 0;
volatile int16_t last_speed = 0;
volatile uint32_t last_change_tick = 0;
volatile uint8_t launch_triggered = 0;


// INCLUDE_vTaskDelayUntil

extern "C"{
void StartDefaultTask(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartDefaultTask */
  HAL_TIM_Base_Start_IT(&htim7);  
  HAL_UART_Receive_IT(&huart7, &all_rxbuff.Buletooth, 1);
	HAL_UART_Receive_IT(&huart1, all_rxbuff.upper, 1);

  pid_controller.All_Device_Init();
	can_bus.bsp.Filter_Init(&hfdcan1);
	can_bus.bsp.FDCAN_Start(&hfdcan1);
  can_bus.bsp.Filter_Init(&hfdcan2);
	can_bus.bsp.FDCAN_Start(&hfdcan2);
	osDelay(1500);

  /* Infinite loop */
  for(;;)
  {

    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}


void Classic_Move(void const * argument)
{
  /* USER CODE BEGIN Classic_Move */
      TickType_t last = xTaskGetTickCount();
      const TickType_t xFrequency = 1;  // 50ms = 50 ticks
  /* Infinite loop */
  for(;;)
  {
    robot.chassic.Chassic_Mode();
    robot.chassic.Omni_Move_Calc();
    robot.chassic.Chassic_Move();

    DT7_Switch_Update();

    vTaskDelayUntil(&last, xFrequency);
    // INCLUDE_vTaskDelayUntil 
  }
  /* USER CODE END Classic_Move */
}


void Chat_with_upper(void const * argument)
{
  /* USER CODE BEGIN Chat_with_upper */
    uint8_t cmd = 0;
      TickType_t last = xTaskGetTickCount();

  /* Infinite loop */
  for(;;)
  {
    if (all_rxbuff.s2 == AUTO_MODE || all_rxbuff.s2==3) {
            cmd = ASK_LAUNCH_SPEED;
    }
    else if (all_rxbuff.s2 == 2) {
        switch (all_rxbuff.s1) {
        case 3:
          cmd = ASK_START_POS;
          break;
        case 1:
          cmd = ASK_FIXED_POS_LAUNCH;
          break;
      }
    }
      
  // CDC_Transmit_HS(&cmd,1);
  HAL_UART_Transmit(&huart1, &cmd, 1, 100);
  vTaskDelayUntil(&last, 10);
  }
  /* USER CODE END Chat_with_upper */
}


void Shout_Ball(void const * argument)
{
  /* USER CODE BEGIN Shout_Ball */
  /* Infinite loop */
  TickType_t last = xTaskGetTickCount();
  for(;;)
  {
    if (robot.Distance!=0 && robot.buzzer_flag==0) {
      HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);

      __HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,2000);
      osDelay(400);
      __HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,0);
			 //osDelay(500);
      robot.buzzer_flag = 1;
    }
//���������Զ�����
    bool current = BALL_SWITCH;

    if (Judge_ball() == BALL_IN) {
    // ������ �� ���������������
    ROD_TOP_PUSH;
    } 
    else if (Judge_ball() == BALL_OUT){
    // ������ �� �����ջ�
    ROD_TOP_BACK;
    }
    vTaskDelayUntil(&last, 5);//������ʱ5ms
  }
  /* USER CODE END Shout_Ball */
}
//������
void Chang_Shout_Angle(void const * argument)
{
  /* USER CODE BEGIN Chang_Shout_Angle */
      TickType_t last = xTaskGetTickCount();
      TickType_t now;
      // const TickType_t xFrequency = 50;  // 50ms = 50 ticks
  /* Infinite loop */
  for(;;)
  {
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);//����ʽ�ȴ������������ֶ�����
    // N5065_traget_speed[0] = N5065_traget_speed[1] = robot.upper_data[4];
    // TickType_t start_t =  xTaskGetTickCount();
//    for (;;) {
//      TickType_t now = xTaskGetTickCount();
//      if (now - start_t == 1000) {
//        break;
//      }
//    }
    vTaskDelay(850);
    ROD_BOTTOM_PUSH;
    vTaskDelay(500);
    ROD_BOTTOM_BACK;
    N5065_traget_speed[0] = N5065_traget_speed[1] = 0;
    wake_fireball_task =0;



  //   uint16_t target_shoot_rpm = interpolate_rpm(shoot_table_2pt,robot.upper_data[3], SHOOT_TABLE_SIZE);
  //   N5065_traget_speed[0] = N5065_traget_speed[1] = target_shoot_rpm; 

  //   osDelay(1000);

  //   ROD_BOTTOM_PUSH;

  //   if (Judge_ball() == BALL_OUT) {
  //     osDelay(500);
  //     ROD_BOTTOM_BACK;
  //     N5065_traget_speed[0] = N5065_traget_speed[1] = 0;
  //  }

  // vTaskDelayUntil(&last, 1000);//������ʱ1s

  }
  /* USER CODE END Chang_Shout_Angle */
}

void Task_Changes(void const * argument)
{
  /* USER CODE BEGIN Task_Changes */
  TickType_t last = xTaskGetTickCount();

  /* Infinite loop */
  for(;;)
  {
    if (all_rxbuff.s2 == AUTO_MODE) {
      switch (robot.robot_commend) {
        case ALLOW_LAUNCH://��������
          robot.chassic.Chassic_Move_Data.vx = 5.0*(all_rxbuff.remote_sense[3]-1024);
          robot.chassic.Chassic_Move_Data.vy = -5.0*(all_rxbuff.remote_sense[2]-1024);
          robot.chassic.Chassic_Move_Data.vomega = robot.upper_data[2]*Radius*(60/(2*PI*WHEEL_Radius)*3591.0/187.0);
          break;
        }
    }
    else if (all_rxbuff.s2 == 2) {
          robot.chassic.Chassic_Move_Data.vx = 5.0*(all_rxbuff.remote_sense[3]-1024);
          robot.chassic.Chassic_Move_Data.vy = -5.0*(all_rxbuff.remote_sense[2]-1024);
          robot.chassic.Chassic_Move_Data.vomega = robot.upper_data[2]*Radius*(60/(2*PI*WHEEL_Radius)*3591.0/187.0);
          if (robot.bt_auto_fire_flag == 0 && all_rxbuff.s1 == 1) {
          N5065_traget_speed[0] = N5065_traget_speed[1] = 2560;

          xTaskCreate(
          StartLaunchTask,   // ������
          "LaunchTask",      // �������ƣ������ã�
          128,               // ��ջ��С����λ��words������ bytes��
          NULL,              // ����
          osPriorityNormal,  // ���ȼ�   tskIDLE_PRIORITY + 1
          NULL               // ��ѡ����������
         );
            robot.bt_auto_fire_flag = 1;

          }

          // if (robot.fixed_point_flag == 1) {
          //   xTaskCreate(BT_Auto_Fire_Task,
          //      "BT_AUTO_FIRE_TASK", 
          //      128, 
          //      NULL, 
          //      osPriorityNormal, 
          //      NULL);
          // }

      //  switch (robot.robot_commend) {
      //     case ALLOW_START_POS://����ԭ��
      //       robot.chassic.Chassic_Move_Data.vx = 
      //           robot.upper_data[0]*(60/(2*PI*WHEEL_Radius))*3591.0/187.0;
      //       robot.chassic.Chassic_Move_Data.vy = 
      //           robot.upper_data[1]*(60/(2*PI*WHEEL_Radius))*3591.0/187.0;
      //       robot.chassic.Chassic_Move_Data.vomega = 
      //           robot.upper_data[2]*Radius*(60/(2*PI*WHEEL_Radius)*3591.0/187.0);
      //       break;
      //   case ALLOW_FIXED_POS_LAUNCH://ȥ�̶��ĵ�λͶ��
      //       robot.chassic.Chassic_Move_Data.vx = 
      //           robot.upper_data[0]*(60/(2*PI*WHEEL_Radius))*3591.0/187.0;
      //       robot.chassic.Chassic_Move_Data.vy = 
      //           robot.upper_data[1]*(60/(2*PI*WHEEL_Radius))*3591.0/187.0;
      //       robot.chassic.Chassic_Move_Data.vomega = 
      //           robot.upper_data[2]*Radius*(60/(2*PI*WHEEL_Radius)*3591.0/187.0);
      //     break;

    // }
    }
    vTaskDelayUntil(&last, 1);//������ʱ5ms

  }
  /* USER CODE END Task_Changes */
}

}
void StartLaunchTask(void  *argument){

  vTaskDelay(1000);
  ROD_BOTTOM_PUSH;
  vTaskDelay(500);
  ROD_BOTTOM_BACK;
  N5065_traget_speed[0] = N5065_traget_speed[1] = 0;
  robot.bt_auto_fire_flag = 0;
  vTaskDelete(NULL);

}

void BT_Auto_Fire_Task(void *argument)
{
  vTaskDelay(500);
  ROD_BOTTOM_PUSH;
  vTaskDelay(500);
  ROD_BOTTOM_BACK;
  // N5065_traget_speed[0] = N5065_traget_speed[1] = 0;
  robot.fixed_point_flag = 0;
  vTaskDelete(NULL);
}

bool Judge_ball(void)
{
    static bool last_state = BALL_OUT;  // �ϴ��ȶ�״̬����ʼ����
    bool current = BALL_SWITCH;

    if (current != last_state) {
        osDelay(40);  // ���������30ms
        current = BALL_SWITCH;

        if (current != last_state) {
            last_state = current;
        }
    }

    return last_state;  // ���ص�ǰ�ȶ�״̬��BALL_IN / BALL_OUT��
}
// �����ڲ��Լ�¼��λ����ʱʹ�ô˺�������
void UpdateSpeedFromBluetooth(int16_t new_speed) {
    if (abs(new_speed - target_launch_speed) > 5) { // ������ֵ������
        target_launch_speed = new_speed;
        last_change_tick = xTaskGetTickCount();
        launch_triggered = 0;
    }
}

//ң�������˱��ش���ѡ����
void DT7_Switch_Update()
{
   static uint8_t last_val = 0;
   current_val  = all_rxbuff.s1;

   if (all_rxbuff.s2 == 1) {

    if (current_val >= 1 && current_val <= 3) {
        uint8_t parsed = current_val - 0;

        if (last_val != parsed) {
            // �����ش���
            switch (parsed) {
                case 1:
                if (wake_fireball_task == 0) {
                  xTaskNotifyGive(ChangeAngleTaskHandle);//����Ͷ������
                  wake_fireball_task = 1;
                }
                    break;
                case 3:
                    // xTaskNotifyGive(CancelHandle);
                    break;
                case 2:
                    // xTaskNotifyGive(Shoot3ptHandle);
                    break;
            }
        }
        last_val = parsed;
    }
   }
}


















//����������
// void Start_Dribble()
// {
//   N5065_traget_speed[0] = -3000;
//   N5065_traget_speed[1] = 1200;
//   osDelay(400);
//   ROD_BOTTOM_PUSH;
//   if(BALL_SWITCH == 1) 
//   {
//     osDelay(500);
//     ROD_BOTTOM_BACK;
//     N5065_traget_speed[0] = 0;
//     N5065_traget_speed[1] = 0;
//   }

// }
// //����������
// void Catch_the_Ball()
// {
//     N5065_traget_speed[0] = 400;
//     N5065_traget_speed[1] = -400;

//   if(BALL_SWITCH == 1) 
//   {
//     osDelay(500);
//     N5065_traget_speed[0] = 0;
//     N5065_traget_speed[1] = 0;
//   }
// }