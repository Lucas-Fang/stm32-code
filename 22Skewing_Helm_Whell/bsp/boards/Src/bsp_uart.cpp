#include "bsp_uart.h"
#include "chassic.h"
#include <cstdint>

remote_data receive_data;
Rxbuffer all_rxbuff;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

    if(huart->Instance==USART2)
    {
    //    Receive_data(Rxbuffer::BT_buff[0],DATA_LEN);
    }

}
void DataAnalysis(uint8_t *Data)
{
	
	receive_data.ch[0]=(int16_t)(Data[1]<<8|(int16_t)Data[0]);
  	receive_data.ch[1]=(int16_t)(Data[3]<<8|(int16_t)Data[2]);
	receive_data.ch[2]=(int16_t)(Data[5]<<8|(int16_t)Data[4]);
	
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
				count=0;
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
			}
			else
			{
				step=0;
			}
			break;
		default: break;
	}
}

void Get_Remote_Date()
{
    all_rxbuff.remote_sense[0]= ((int16_t)all_rxbuff.DR16[0]| ((int16_t)all_rxbuff.DR16[1] << 8)) & 0x07ff;   
    //!< Channel 0 右手的x，此处作为omega
    all_rxbuff.remote_sense[1] =(((int16_t)all_rxbuff.DR16[1] >> 3) | ((int16_t)all_rxbuff.DR16[2] << 5)) & 0x07ff; 
    //!< Channel 1 有点问题，收到的数据不准确，此处不使用
    all_rxbuff.remote_sense[2] = (((int16_t)all_rxbuff.DR16[2] >> 6) | ((int16_t)all_rxbuff.DR16[3] << 2) |((int16_t)all_rxbuff.DR16[4] << 10))& 0x07ff; 
    //!< Channel 2  左手的x
    all_rxbuff.remote_sense[3] =(((int16_t)all_rxbuff.DR16[4] >> 1) | ((int16_t)all_rxbuff.DR16[5] << 7)) & 0x07ff;
    //!< Channel 3  左手的y
    all_rxbuff.s1 = ((all_rxbuff.DR16[5] >> 4) & 0x000C) >> 2;
    all_rxbuff.s2 = ((all_rxbuff.DR16[5] >> 4) & 0x0003);

	for (uint8_t i = 0; i < 4; i++)
	{
		all_rxbuff.remote_sense[i]-=1024;
		// all_rxbuff.remote_sense[i]/=24;
	}
}


