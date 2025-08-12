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
/*舵机时序图
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
	ButtonTask,   // 任务函数
	"ButtonTask",      // 任务名称（调试用）
	125,               // 堆栈大小（单位：words，不是 bytes）
	NULL,              // 参数
	osPriorityNormal,  // 优先级   tskIDLE_PRIORITY + 1
	NULL               // 可选返回任务句柄
	);
    while(1)
    {	
//6020给+逆时针转
			// CAN1_CMD_1(0,
			// 0,
			// PID_velocity_realize_1(20,3),
			// 0);
			
		if (key_flag == 1) {
			xTaskCreate(
			Seek_Target_Task,   // 任务函数
			"Seek_Target_Task",      // 任务名称（调试用）
			256,               // 堆栈大小（单位：words，不是 bytes）
			NULL,              // 参数
			osPriorityNormal,  // 优先级   tskIDLE_PRIORITY + 1
			&xSeekTargetTaskHandle               // 可选返回任务句柄
			);

			vTaskDelete(NULL);
			
		}
        osDelay(1);
    }
}
//寻找靶子任务
void Seek_Target_Task(void  *argument){
   // 初始化变量
    int openmv_data = 0;
    int lost_count = 0;
    float swing_time = 0.0f;
    float target_angle = 0.0f;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xPeriod = pdMS_TO_TICKS(10); // 100Hz控制频率

    while(1) {
        // 1. 获取OpenMV数据（假设有函数可以直接读取）
        openmv_data = pos_x;

        // 2. 目标丢失判断
        // if(openmv_data == 0xffff)//1000   openmv_data == 0xFFFF
		// {
            // lost_count++;
        // } else {
            // 发现目标，启动自瞄任务
            // xTaskNotifyGive( myTask03Handle);
		if (delta_x !=0) {
			osThreadResume(myTask03Handle);
            lost_count = 0;
            swing_time = 0.0f; // 重置摆动计时器
			vTaskDelete(xSeekTargetTaskHandle);
		}	
	
        // }

        // 3. 如果目标丢失超过阈值，开始摆动搜索
        // if(lost_count >= LOST_THRESHOLD) {
        swing_time += 0.01f; // 10ms周期
            // 生成正弦摆动角度
      	target_angle = MAX_SWING_ANGLE * sin(2 * 3.14159f * SWING_FREQUENCY * swing_time);
		CAN1_CMD_1(0,
		0,
		(PID_pos_Yaw_realize(target_angle)),
		0);
			
        // }
		vTaskDelayUntil(&xLastWakeTime,xPeriod);
}
}

//瞄准任务
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
	// ulTaskNotifyTake(pdTRUE, portMAX_DELAY);//阻塞式等待任务唤醒无需手动挂起
	
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
	if((last_x - delta_x ) > 0 && pos_x == 0xFFFF)//向右超出范围
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
	else if((last_x - delta_x ) < 0 && pos_x == 0XFFFF)//向zuo超出范围
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
    const TickType_t debounce_delay = pdMS_TO_TICKS(50); // 消抖时间50ms
    TickType_t last_press_time = 0;
    
    while(1) {
        // 检测按键按下（假设低电平有效）
        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET) {
            TickType_t now = xTaskGetTickCount();
            
            // 消抖判断（首次按下或超过消抖间隔）
            if(last_press_time == 0 || (now - last_press_time) > debounce_delay) {
 
                // 执行按键处理...
				    key_flag++;
    // 这里可以发送事件或通知其他任务
				vTaskDelete(NULL);
            }
            last_press_time = now;
        } else {
            last_press_time = 0;
        }
        
        vTaskDelay(pdMS_TO_TICKS(10)); // 10ms检测周期
    }
}


// 将角度转换为弧度
double degreesToRadians(double degrees) {
    return degrees * (PI / 180.0);
}
// 将弧度转换为角度
double radiansToDegrees(double radians) {
   return radians * (180.0 / PI);
}
