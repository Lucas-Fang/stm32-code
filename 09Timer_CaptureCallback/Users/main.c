#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/TIMER/gtim.h"


extern uint8_t g_timxchp_cap_sta;
extern uint16_t g_timxchy_cap_val;

uint16_t distance ;


int main(void)
{
    uint32_t temp = 0;
    
    HAL_Init();                                         /* 初始化HAL库 */
    SystemClock_Config();                               /* 设置时钟, 72Mhz */
    delay_init(72);                                     /* 延时初始化 */
    led_init();                                         /* LED初始化 */
    gtim_timx_pwm_chy_init(0XFFFF,72-1);                /*以1Mhz的频率计数 进行捕获*/
    //usart_init(9600);
    
    
    while(1)
    { 
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
        delay_us(10);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
        //delay_ms(10);

        if (g_timxchp_cap_sta & 0X80)
        {
            temp =g_timxchp_cap_sta & 0X3F;             /*获取捕获次数*/
            temp *= 65536;
            temp +=g_timxchy_cap_val;                   /*得到总得高电平时间*/
            
            g_timxchp_cap_sta = 0;                      /*开启下一次输入捕获*/
            
             distance =  temp * (34000/1000000) / 2;
        }
        
       //HAL_UART_Transmit(&g_uart1_handle, (uint8_t *)&distance,2,100);

        delay_ms(200);

    }
    
    
    
    
    
    
    
}



