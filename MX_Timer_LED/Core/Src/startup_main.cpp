#include "startup_main.h"
#include "bsp_delay.h"

void startup_main(void)
{
 
	bsp_delay.f1.Init(72);
	
#if isRTOS==0    	//������������
	for(;;)  //��ͬ��while(true)
	{

	}
#endif
}
