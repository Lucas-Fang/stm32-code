#include "uart_user.h"
#include <stdint.h>



extern int16_t delta_x , delta_y;
float filtered_x,filtered_y;
uint8_t openmv_buffer[9];
LowPassFilter x_filter, y_filter;
uint16_t pos_x,pos_y;
uint16_t length;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1) {
    Receive_K230_data(openmv_buffer[0],6);
    }

    if (huart->Instance == USART6) {
   
    }
}


void Receive_K230_data(uint8_t Bytedata ,uint8_t Data_len)
{
    // if (data_ptr[1] != 0x2c && data_ptr[2] != 0x12) {
    //     return false;
    // }
    // if (data_ptr[7] != 0x5b) {
    //     return false;
    // }

    // delta_x = data_ptr[3] | data_ptr[4] << 8;
    // delta_y = data_ptr[5] | data_ptr[6] << 8;
	// 	VisionData_Received(delta_x,delta_y);
    // return true;
	static uint8_t step=0;
	static uint8_t count=0,Buff[300]={0},*data_ptr;


	switch(step)
	{
		case 0:
		  if(Bytedata == 0xA5)
	  	{
  			step++;
			Buff[count++]=Bytedata;
  		}break;

		case 1:
			if(Bytedata == 0x5A)
	  		{
  				step++;
				Buff[count++]=Bytedata;
				data_ptr=&Buff[count];
  			}else {
				step = 0;
			}
			break;

		case 2:
			Buff[count++]=Bytedata;
			if((count)==Data_len + 2 )//6
			{
				step++;
			}break;
		case 3:
			if(Bytedata==0xFE)
			{
				DataAnalysis(data_ptr);

				step=0;
				count=0;
			}
			else
			{
				step=0;
			}
			break;
		default: break;
	}


	// if (data_ptr[0] != 0XA5  || data_ptr[1] != 0X5A) {
    //     return false;
    // }
    // if (data_ptr[8] != 0xFE) {
    //     return false;
    // }
//中心  x:211 y:120


	// if (pos_x != 0xffff) {
	// 	delta_x = (int16_t)pos_x - 211;
	// }
	// if (pos_y != 0xffff) {
	// 	delta_y = (int16_t)pos_y - 120;
	// }
	// VisionData_Received(delta_x,delta_y);
    // return true;
}


fp32 uint8_2_fp32(uint8_t *data_ptr)
{
    fp32 out = data_ptr[0] 
             | data_ptr[1] << 8 
             | data_ptr[2] << 16
             | data_ptr[3] << 24;  
    return out;
}


/*--------------------------------------------*/



// 初始化滤波器
void LowPassFilter_Init(LowPassFilter* filter, float alpha, float init_val) {
    filter->alpha = alpha;
    filter->prev_val = init_val;
}

// 更新滤波器并返回滤波后的值
float LowPassFilter_Update(LowPassFilter* filter, float new_val) {
    filter->prev_val = filter->alpha * new_val + (1.0f - filter->alpha) * filter->prev_val;
    return filter->prev_val;
}

// 每次收到视觉数据时调用
void VisionData_Received(float x_error, float y_error) {
   filtered_x = LowPassFilter_Update(&x_filter, x_error);
   filtered_y = LowPassFilter_Update(&y_filter, y_error);
    // 使用filtered_x和filtered_y作为PID和前馈控制的输入
}

/*--------------------------------------------*/
void DataAnalysis(uint8_t *Data)
{
	pos_x = (int16_t)((Data[0] << 8) | Data[1]);
	pos_y = (int16_t)((Data[2] << 8) | Data[3]);
	length  = ((Data[4] << 8 )| Data[5]);

	if (pos_x != 0xffff) {
		delta_x = ((int16_t)pos_x) ;//- 211
	}
	if (pos_y != 0xffff) {
		delta_y = ((int16_t)pos_y) ;//- 120
	}
}

uint8_t SUMCRC(uint8_t *Message,uint16_t DataLen)
{
	uint16_t i=1;
	uint8_t SUM=0x00;
	for(;i<=DataLen;i++)
	{
		SUM+=Message[i];
	}

	return SUM;

}

void Receive_data(uint8_t Bytedata,uint8_t Data_len)
{
	static uint8_t step=0;
	static uint8_t count=0,Buff[300]={0},*data_ptr;
//	static uint16_t checksum=0;
	switch(step)
	{
		case 0:
		  if(Bytedata == 0xA5)
	  	{
  			step++;
				
				Buff[count++]=Bytedata;
				data_ptr=&Buff[count];
  		}break;
		case 1:
			Buff[count++]=Bytedata;
			if((count-1)==Data_len )
			{
				step++;
			}break;
		case 2:
			Buff[count++]=Bytedata;
			if(SUMCRC(Buff,Data_len)==Bytedata)
			{
				step++;
			}
			else
			{
				step=0;
			}break;
		case 3:
			if(Bytedata==0x5A)
			{
				DataAnalysis(data_ptr);
				step=0;
				count=0;
			}
			else
			{
				step=0;
			}
			break;
		default: break;
	}
}


