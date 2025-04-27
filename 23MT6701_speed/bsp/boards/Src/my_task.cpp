#include "my_task.h"
#include "i2c.h"
#include "pid_user.h"
#include "pid.h"
#include "FreeRTOS.h"
#include "stm32f103xb.h"
#include "stm32f1xx_hal_tim.h"
#include "task.h"
#include "cmsis_os.h"
#include "MT6701.h"
#include "bsp_usart.h"
#include "stdio.h"
#include "tim.h"

int32_t target_speed[2]={0,0};
int32_t target_speed_pwm[2]={1000,1000};
extern DMA_HandleTypeDef hdma_i2c2_rx;
extern uint8_t rx_buffer[1];
extern Motor_Measure N5065_Data[2];
TickType_t xLastWakeTime;
int status;
extern uint8_t buffer[2];

extern "C"
{
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  
  HAL_UART_Receive_IT(&huart1, rx_buffer, 1);
  HAL_TIM_Base_Start_IT(&htim4);
  Motor_PWM_Init(&htim3);
  /* Infinite loop */
  for(;;)
  {
// MT6701_ReadAngle(&hi2c1);

    // N5065_Action(
    //   pid_controller.can_motor.N5065_Velocity_Realize(target_speed[0],1),
    //   pid_controller.can_motor.N5065_Velocity_Realize(target_speed[01],2));
    
    N5065_Action(target_speed_pwm[0],target_speed_pwm[1]);
    printf("%f,%f\n",N5065_Data[1].angle,N5065_Data[1].speed_rpm);

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
    
    status = HAL_DMA_GetState(&hdma_i2c2_rx);
    // MT6701_ReadAngle(&hi2c2);
    // calculate_rpm(&hi2c1, N5065_Data, 1);
    // calculate_rpm(&hi2c2, N5065_Data, 2);
    
    BlueTooth_Send_Data();
    
//    vTaskDelayUntil(&xLastWakeTime, xPeriod);
			osDelay(1);
  }
  /* USER CODE END Motor_Task */
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM4) {
    MT6701_ReadAngle(&hi2c2);
    calculate_rpm(&hi2c1, N5065_Data, 1);
    calculate_rpm(&hi2c2, N5065_Data, 2);
    
  }
}

}

