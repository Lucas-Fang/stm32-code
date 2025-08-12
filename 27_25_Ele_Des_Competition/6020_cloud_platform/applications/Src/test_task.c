#include "test_task.h"
#include "math.h"
#include "cmsis_os.h"
#include <stdint.h>


TaskHandle_t xSeekTargetTaskHandle = NULL;
extern CAN_HandleTypeDef hcan1;
extern uint8_t openmv_buffer[9];
extern LowPassFilter x_filter, y_filter;
extern osThreadId myTask03Handle;
int16_t delta_x , delta_y;
int8_t key_flag;
int _6020_deadline ;
extern uint16_t pos_x,pos_y;
/*���ʱ��ͼ
0    45    90 	 135 	180 
500  1000  1500	 2000	2500
*/
/**
  * @brief          test task
  * @param[in]      pvParameters: NULL
  * @retval         none
  */
void test_task(void const * argument)
{
	PID_devices_Init();

	CAN1_Filter_Init();
	CAN2_Filter_Init();
	CAN_Start(&hcan1);
	CAN_Start(&hcan2);

	HAL_UART_Receive_IT(&huart1,openmv_buffer,1);

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_Base_Start_IT(&htim9);

	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_RESET);
	LowPassFilter_Init(&x_filter, 0.5f, 0.0f); // alpha=0.2
	LowPassFilter_Init(&y_filter, 0.5f, 0.0f);
	osThreadSuspend(myTask03Handle);
	xTaskCreate(
	ButtonTask,   // ������
	"ButtonTask",      // �������ƣ������ã�
	125,               // ��ջ��С����λ��words������ bytes��
	NULL,              // ����
	osPriorityNormal,  // ���ȼ�   tskIDLE_PRIORITY + 1
	NULL               // ��ѡ����������
	);
    while(1)
    {	
//6020��+��ʱ��ת
			// CAN1_CMD_1(0,
			// 0,
			// PID_velocity_realize_1(20,3),
			// 0);
			
		if (key_flag == 1) {
			xTaskCreate(
			Seek_Target_Task,   // ������
			"Seek_Target_Task",      // �������ƣ������ã�
			256,               // ��ջ��С����λ��words������ bytes��
			NULL,              // ����
			osPriorityNormal,  // ���ȼ�   tskIDLE_PRIORITY + 1
			&xSeekTargetTaskHandle               // ��ѡ����������
			);

			vTaskDelete(NULL);
			
		}
        osDelay(1);
    }
}
//Ѱ�Ұ�������
void Seek_Target_Task(void  *argument){
   // ��ʼ������
    int openmv_data = 0;
    int lost_count = 0;
    float swing_time = 0.0f;
    float target_angle = 0.0f;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xPeriod = pdMS_TO_TICKS(10); // 100Hz����Ƶ��

    while(1) {
        // 1. ��ȡOpenMV���ݣ������к�������ֱ�Ӷ�ȡ��
        openmv_data = pos_x;

        // 2. Ŀ�궪ʧ�ж�
        // if(openmv_data == 0xffff)//1000   openmv_data == 0xFFFF
		// {
            // lost_count++;
        // } else {
            // ����Ŀ�꣬������������
            // xTaskNotifyGive( myTask03Handle);
		if (delta_x !=0) {
			osThreadResume(myTask03Handle);
            lost_count = 0;
            swing_time = 0.0f; // ���ðڶ���ʱ��
			vTaskDelete(xSeekTargetTaskHandle);
		}	
	
        // }

        // 3. ���Ŀ�궪ʧ������ֵ����ʼ�ڶ�����
        // if(lost_count >= LOST_THRESHOLD) {
        swing_time += 0.01f; // 10ms����
            // �������Ұڶ��Ƕ�
      	target_angle = MAX_SWING_ANGLE * sin(2 * 3.14159f * SWING_FREQUENCY * swing_time);
		CAN1_CMD_1(0,
		0,
		(PID_pos_Yaw_realize(target_angle)),
		0);
			
        // }
		vTaskDelayUntil(&xLastWakeTime,xPeriod);
}
}

//��׼����
void AIM_Task(void const * argument)
{
  /* USER CODE BEGIN AIM_Task */
	TickType_t last = xTaskGetTickCount();
	const TickType_t xFrequency = 4;  // 50ms = 50 ticks

	uint8_t count = 0;
	int16_t last_deltax = 0;
  /* Infinite loop */
  for(;;)
  {
	// ulTaskNotifyTake(pdTRUE, portMAX_DELAY);//����ʽ�ȴ������������ֶ�����
	
	// if (last_deltax == delta_x) {
	// 	count ++;
	// 	last_deltax = delta_x;
	// }

	// if (pos_x == 0xFFFF) {
	// 	osThreadSuspend(NULL);
	// }
	if(delta_x > 0){
		_6020_deadline = -600;
	}
	else if(delta_x < 0)
	{
		_6020_deadline = 600;
	}

	// CAN1_CMD_1(0,
	// 0,
	// (PID_velocity_realize_1(PID_pos_x_realize(0),3)+_6020_deadline),
	// 0);



	Judge_Range();
		
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,1480 + PID_pos_y_realize(0));
	if (pos_y < 20 && delta_y> -20 || delta_x <20 && delta_x > -20) {

		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET);
	}
    vTaskDelayUntil(&last, xFrequency);
  }//INCLUDE_vTaskDelayUntil  configUSE_TIMERS
  /* USER CODE END AIM_Task */
}



void Judge_Range()
{
	uint16_t last_x = 0;
	uint8_t right_flag,left_flag;
	if((last_x - delta_x ) > 0 && pos_x == 0xFFFF)//���ҳ�����Χ
	{
		right_flag ++ ;
		if (right_flag == 3) {
			CAN1_CMD_1(0,
			0,
			1500,
			0);
			right_flag = 0;
		}
	
	}
	else if((last_x - delta_x ) < 0 && pos_x == 0XFFFF)//��zuo������Χ
	{
			left_flag ++;
		if (left_flag == 1) {

			CAN1_CMD_1(0,
			0,
			-1500,
			0);
			left_flag = 0;
		}
			
	}
	else
	{
			CAN1_CMD_1(0,
			0,
			(PID_velocity_realize_1(PID_pos_x_realize(0),3) ),
			0);
	}
	
	last_x = delta_x;
}

void ButtonTask(void *argument) {
    const TickType_t debounce_delay = pdMS_TO_TICKS(50); // ����ʱ��50ms
    TickType_t last_press_time = 0;
    
    while(1) {
        // ��ⰴ�����£�����͵�ƽ��Ч��
        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET) {
            TickType_t now = xTaskGetTickCount();
            
            // �����жϣ��״ΰ��»򳬹����������
            if(last_press_time == 0 || (now - last_press_time) > debounce_delay) {
 
                // ִ�а�������...
				    key_flag++;
    // ������Է����¼���֪ͨ��������
				vTaskDelete(NULL);
            }
            last_press_time = now;
        } else {
            last_press_time = 0;
        }
        
        vTaskDelay(pdMS_TO_TICKS(10)); // 10ms�������
    }
}


// ���Ƕ�ת��Ϊ����
double degreesToRadians(double degrees) {
    return degrees * (PI / 180.0);
}
// ������ת��Ϊ�Ƕ�
double radiansToDegrees(double radians) {
   return radians * (180.0 / PI);
}
