#include "my_task.h"
#include "FreeRTOS.h"
#include "as5600.h"
#include "task.h"
#include "cmsis_os.h"



extern Motor_Measure N5065_Data;
TickType_t xLastWakeTime;
extern "C"
{
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  // HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  // __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,2000);
  // vTaskDelay(3000);
  // __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,1000);
  // vTaskDelay(3000);

  // __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,1100);

  /* Infinite loop */
  for(;;)
  {
    N5065_Data.angle=AS5600_ReadAngle();
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Motor_Task */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Motor_Task */
void Motor_Task(void const * argument)
{
  /* USER CODE BEGIN Motor_Task */
 
  const TickType_t xPeriod = pdMS_TO_TICKS(SAMPLE_RATE_MS);  // 周期 1ms
    // 初始化：获取当前系统时间戳
  xLastWakeTime = xTaskGetTickCount();
  /* Infinite loop */
  for(;;)
  {
//    N5065_Data.speed_rpm = low_pass_filter(calculate_rpm());
    // N5065_Data.speed_rpm = calculate_rpm();
    vTaskDelayUntil(&xLastWakeTime, xPeriod);
    // osDelay(2);
  }
  /* USER CODE END Motor_Task */
}
}