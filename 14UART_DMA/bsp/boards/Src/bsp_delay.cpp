#include "bsp_delay.h"

#if isRTOS == 1
    #include "cmsis_os.h"
#endif

static uint32_t g_fac_us = 0;       /* us寤舵椂鍊嶄箻鏁?*/

/*******瀵硅薄*******/
BSP_Delay bsp_delay;

/**
 * @brief       鍒濆鍖栧欢杩熷嚱鏁? * @param       sysclk: 绯荤粺鏃堕挓棰戠巼, 鍗矯PU棰戠巼(HCLK)
 * @retval      鏃? */
 void BSP_Delay::F1::Init(uint16_t sysclk)
{
    SysTick->CTRL = 0;                                          /* 娓匰ystick鐘舵€侊紝浠ヤ究涓嬩竴姝ラ噸璁撅紝濡傛灉杩欓噷寮€浜嗕腑鏂細鍏抽棴鍏朵腑鏂?*/
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);   /* SYSTICK浣跨敤鍐呮牳鏃堕挓婧?鍒嗛,鍥爏ystick鐨勮鏁板櫒鏈€澶у€煎彧鏈?^24 */

    g_fac_us = sysclk / 8;                                      /* 涓嶈鏄惁浣跨敤OS,g_fac_us閮介渶瑕佷娇鐢?浣滀负1us鐨勫熀纭€鏃跺熀 */
}

/**
 * @brief       寤舵椂nus
 * @param       nus: 瑕佸欢鏃剁殑us鏁?
 * @note        娉ㄦ剰: nus鐨勫€?涓嶈澶т簬1864135us(鏈€澶у€煎嵆2^24 / g_fac_us  @g_fac_us = 9)
 * @retval      鏃? */
void BSP_Delay::F1::us(uint32_t nus)
{
    uint32_t temp;
    SysTick->LOAD = nus * g_fac_us; /* 鏃堕棿鍔犺浇 */
    SysTick->VAL = 0x00;            /* 娓呯┖璁℃暟鍣?*/
    SysTick->CTRL |= 1 << 0 ;       /* 寮€濮嬪€掓暟 */

    do
    {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16))); /* CTRL.ENABLE浣嶅繀椤讳负1, 骞剁瓑寰呮椂闂村埌杈?*/

    SysTick->CTRL &= ~(1 << 0) ;    /* 鍏抽棴SYSTICK */
    SysTick->VAL = 0X00;            /* 娓呯┖璁℃暟鍣?*/
}

/**
 * @brief       寤舵椂nms
 * @param       nms: 瑕佸欢鏃剁殑ms鏁?(0< nms <= 65535)
 * @retval      鏃? */
void BSP_Delay::F1::ms(uint16_t nms)
{
    uint32_t repeat = nms / 1000;   /*  杩欓噷鐢?000,鏄€冭檻鍒板彲鑳芥湁瓒呴搴旂敤,
                                     *  姣斿128Mhz鐨勬椂鍊? delay_us鏈€澶у彧鑳藉欢鏃?048576us宸﹀彸浜?                                     */
    uint32_t remain = nms % 1000;

    while (repeat)
    {
        us(1000 * 1000);      /* 鍒╃敤delay_us 瀹炵幇 1000ms 寤舵椂 */
        repeat--;
    }

    if (remain)
    {
        us(remain * 1000);    /* 鍒╃敤delay_us, 鎶婂熬鏁板欢鏃?remain ms)缁欏仛浜?*/
    }
}



/**
 * @brief     鍒濆鍖栧欢杩熷嚱鏁? * @param     sysclk: 绯荤粺鏃堕挓棰戠巼, 鍗矯PU棰戠巼(rcc_c_ck), 168MHz
 * @retval    鏃? */  
void BSP_Delay::F4::Init(uint16_t sysclk)
{
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);/* SYSTICK浣跨敤澶栭儴鏃堕挓婧?棰戠巼涓篐CLK */
    g_fac_us = sysclk;                                  /* 涓嶈鏄惁浣跨敤OS,g_fac_us閮介渶瑕佷娇鐢?*/
}


/**
 * @brief       寤舵椂nus
 * @param       nus: 瑕佸欢鏃剁殑us鏁?
 * @note        nus鍙栧€艰寖鍥?: 0~190887435(鏈€澶у€煎嵆 2^32 / fac_us @fac_us = 21)
 * @retval      鏃? */
void BSP_Delay::F4::us(uint32_t nus)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD;        /* LOAD鐨勫€?*/
    ticks = nus * g_fac_us;                 /* 闇€瑕佺殑鑺傛媿鏁?*/
    told = SysTick->VAL;                    /* 鍒氳繘鍏ユ椂鐨勮鏁板櫒鍊?*/
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;        /* 杩欓噷娉ㄦ剰涓€涓婼YSTICK鏄竴涓€掑噺鐨勮鏁板櫒灏卞彲浠ヤ簡 */
            }
            else 
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;                      /* 鏃堕棿瓒呰繃/绛変簬瑕佸欢杩熺殑鏃堕棿,鍒欓€€鍑?*/
            }
        }
    }
}

/**
 * @brief       寤舵椂nms
 * @param       nms: 瑕佸欢鏃剁殑ms鏁?(0< nms <= 65535)
 * @retval      鏃? */
void BSP_Delay::F4::ms(uint16_t nms)
{
    uint32_t repeat = nms / 540;    /*  杩欓噷鐢?40,鏄€冭檻鍒板彲鑳芥湁瓒呴搴旂敤, 姣斿248M鐨勬椂鍊?delay_us鏈€澶у彧鑳藉欢鏃?41ms宸﹀彸浜?*/
    uint32_t remain = nms % 540;

    while (repeat)
    {
        us(540 * 1000);        /* 鍒╃敤delay_us 瀹炵幇 540ms 寤舵椂 */
        repeat--;
    }

    if (remain)
    {
        us(remain * 1000);    /* 鍒╃敤delay_us, 鎶婂熬鏁板欢鏃?remain ms)缁欏仛浜?*/
    }
}

void BSP_Delay::FreeRTOS::Init(void)
{
	//璋冪敤FreeRTOS鑷甫鐨勫欢鏃跺嵆鍙€?	//osDelay
	//vTaskDelay
	//vTaskDelayUntil
}


extern "C"
/**
  * @brief HAL搴撳唴閮ㄥ嚱鏁扮敤鍒扮殑寤舵椂
           HAL搴撶殑寤舵椂榛樿鐢⊿ystick锛屽鏋滄垜浠病鏈夊紑Systick鐨勪腑鏂細瀵艰嚧璋冪敤杩欎釜寤舵椂鍚庢棤娉曢€€鍑?  * @param Delay 瑕佸欢鏃剁殑姣鏁?  * @retval None
  */
void HAL_Delay(uint32_t Delay)
{
#if isRTOS==0   //濡傛灉鏄８鏈哄紑鍙?	
	#ifdef STM32F1  //濡傛灉鏄８鏈哄紑鍙戜笖涓篎1
			bsp_delay.f1.ms(Delay);
	#endif
	
	#ifdef STM32F4  //濡傛灉鏄８鏈哄紑鍙戜笖涓篎4
			bsp_delay.f4.ms(Delay);
	#endif
	
#elif isRTOS==1          //濡傛灉鏄疐reeRTOS寮€鍙?		 osDelay(Delay);
#endif
}
