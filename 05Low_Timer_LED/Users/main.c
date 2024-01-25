#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BTIM/btim.h"

int main(void)
{
    HAL_Init();                              /* ��ʼ��HAL�� */
    SystemClock_Config();                    /* ����ʱ��, 72Mhz */
    delay_init(72);                          /* ��ʱ��ʼ�� */
    led_init();                              /* LED��ʼ�� */
    bitm_timx_int_init(7200-1,5000-1);       /* ��Ԥ��Ƶϵ�����Զ���װ��ֵ��*/
    
    while(1)
    { 

    }
}
