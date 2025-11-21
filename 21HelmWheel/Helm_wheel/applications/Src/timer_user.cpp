#include "timer_user.h"
#include "chassic.h"

fp32 motor_traget[4];
extern ROBOT::Rxbuffer rxbuffer;

extern "C"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{


    if(htim->Instance == TIM7)
    {
        robot.chassic.Helm_Move_Calc(rxbuffer.remote_sense[0], rxbuffer.remote_sense[1], rxbuffer.remote_sense[2]);
	     robot.chassic.Chassic_Move();
    }

}