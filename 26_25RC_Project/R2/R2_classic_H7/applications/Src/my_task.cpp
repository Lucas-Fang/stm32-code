#include "my_task.h"
#include "chassic.h"
#include "fdcan_receive.h"
#include "pid.h"
#include "pid_user.h"
#include "Communition.h"
#include "shoot_param.h"

extern "C"{
extern osThreadId ChangeAngleTaskHandle;
extern osThreadId StartLaunchTaskHandle;
}


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




extern "C"{
void StartDefaultTask(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartDefaultTask */
  HAL_TIM_Base_Start_IT(&htim7);  
  HAL_UART_Receive_IT(&huart7, &all_rxbuff.Buletooth, 1);

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

    vTaskDelayUntil(&last, xFrequency);
    // INCLUDE_vTaskDelayUntil 
  }
  /* USER CODE END Classic_Move */
}


void Chat_with_upper(void const * argument)
{
  /* USER CODE BEGIN Chat_with_upper */
    uint8_t cmd = 0;
  /* Infinite loop */
  for(;;)
  {
    // if (all_rxbuff.s2 == AUTO_MODE) {
        switch (all_rxbuff.s1) {
          case 1:
            cmd = ASK_START_POS;
            break;
          case 3:
            cmd = ASK_LAUNCH_SPEED;
            break;
          case 2:
            cmd = ASK_FIXED_POS_LAUNCH;
            break;
        }
      CDC_Transmit_HS(&cmd,1);
    // }

  osDelay(10);
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
    // 

    //����Ŀ���ٶȣ����ڲ�������ʱʹ�ô�ģʽ
  //  UpdateSpeedFromBluetooth(N5065_traget_speed[0]);

      //   VESC_CAN_Speedrpm(0x0311,N5065_traget_speed[0]);
      //  VESC_CAN_Speedrpm(0x0346,N5065_traget_speed[1]);

  //  VESC_CAN_Speedrpm(0x0311,target_launch_speed);
  //  VESC_CAN_Speedrpm(0x0346,target_launch_speed);



//�ײ������ֶ�����

//���������Զ�����
    bool current = BALL_SWITCH;

    if (Judge_ball() == BALL_IN) {
    // ������ �� ���������������
    osDelay(500);
    ROD_TOP_PUSH;
    } else {
    // ������ �� �����ջ�
    osDelay(100);
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
    //   if (abs(N5065_traget_speed[0] - last_speed)>0) {
      
    //     last_change_tick = xTaskGetTickCount();
    //     launch_triggered = 0;
    //     last_speed = N5065_traget_speed[0];
    //   }  
    //     now = xTaskGetTickCount();
    //     if ((now - last_change_tick) >= pdMS_TO_TICKS(1000) && launch_triggered == 0 && N5065_traget_speed[0] > 0) {

    //         launch_triggered = 1;
    //         //��������������
    //     xTaskCreate(
    //     StartLaunchTask,   // ������
    //     "LaunchTask",      // �������ƣ������ã�
    //     128,               // ��ջ��С����λ��words������ bytes��
    //     NULL,              // ����
    //     osPriorityNormal,  // ���ȼ�   tskIDLE_PRIORITY + 1
    //     NULL               // ��ѡ����������
    // );

    //     }
        // osDelay(50);
    // vTaskDelayUntil(&last, 10);//������ʱ5ms

/*--------------------------------------------------------------------------------------------------------------------*/
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);//����ʽ�ȴ������������ֶ�����
    vTaskDelay(2000);

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
      // switch (robot.robot_commend) {
      //   case ALLOW_LAUNCH:
       robot.chassic.Chassic_Move_Data.vx = 5.0*(all_rxbuff.remote_sense[3]-1024);
       robot.chassic.Chassic_Move_Data.vy = -5.0*(all_rxbuff.remote_sense[2]-1024);
       robot.chassic.Chassic_Move_Data.vomega = robot.upper_data[2]*Radius*(60/(2*PI*WHEEL_Radius)*3591.0/187.0);

          // N5065_traget_speed[0] = N5065_traget_speed[1] = robot.upper_data[3];

        //  xTaskNotifyGive(ChangeAngleTaskHandle);//����Ͷ������
    //       break;
    //     case ALLOW_CATCH_BALL:
    //       robot.chassic.Chassic_Move_Data.vomega = robot.upper_data[2];
    //       break;
    //     case ALLOW_HANDOFF:
    //       robot.chassic.Chassic_Move_Data.vomega = robot.upper_data[2];
    //       // N5065_traget_speed[0] = N5065_traget_speed[1] = robot.upper_data[3];
    //       break;
    // }
    }
    vTaskDelayUntil(&last, 1);//������ʱ5ms

  }
  /* USER CODE END Task_Changes */
}

}
void StartLaunchTask(void  *argument){
  // vTaskDelay(200);
  ROD_BOTTOM_PUSH;
  vTaskDelay(1000);
  ROD_BOTTOM_BACK;
  vTaskDelete(NULL);
}

bool Judge_ball(void)
{
    static bool last_state = BALL_OUT;  // �ϴ��ȶ�״̬����ʼ����
    bool current = BALL_SWITCH;

    if (current != last_state) {
        osDelay(30);  // ���������30ms
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
   uint8_t current_val = all_rxbuff.s1;

  if (all_rxbuff.s2 == 1) {

    if (current_val >= '1' && current_val <= '3') {
        uint8_t parsed = current_val - '0';

        if (last_val != parsed) {
            // �����ش���
            switch (parsed) {
                case 1:
                    N5065_traget_speed[0] += 5;
                    N5065_traget_speed[1] += 5;
                    break;
                case 3:

                    break;
                case 2:
                    N5065_traget_speed[0] -= 5;
                    N5065_traget_speed[1] -= 5;
                    break;
            }
        }
        last_val = parsed;
    }
  }
  else if (all_rxbuff.s2 == 2) {

    if (current_val >= '1' && current_val <= '3') {
        uint8_t parsed = current_val - '0';

        if (last_val != parsed) {
            // �����ش���
            switch (parsed) {
                case 1:
                    // xTaskNotifyGive(Shoot2ptHandle);����������
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