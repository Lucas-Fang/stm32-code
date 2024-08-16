#include "bsp_usart.h"

uint8_t rx_buffer[1];

uint8_t a[DATA_LEN];
uint8_t b;
remote_data receive_data;



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		Receive_data(rx_buffer[0],DATA_LEN);
	  	
/*测试所用*/
		a[b]=rx_buffer[0];
		b++;
		if(b == DATA_LEN) 
		{
			b = 0;
		}	
	}

}


void SendByte(uint8_t date)
{

        uint8_t buffer[1];
        buffer[0] = date;       
        HAL_UART_Transmit( &huart1 , buffer , 1 ,1000 );

}

void Send(const uint8_t *data,uint8_t len)
{
        uint8_t i;
        for (i = 0; i < len; i++)
        {
                SendByte(data[i]);//发送一个字节
        }
}

//发送数据包
void Send_Cmd_Data(const uint8_t *datas,uint8_t len)
{
    uint8_t buf[300],i,cnt=0;
    uint16_t sumcheck;
    buf[cnt++] = 0xA5;

    for(i=0;i<len;i++)
    {
        buf[cnt++] = datas[i];
    }
    sumcheck = SUMCRC(buf,len);
    buf[cnt++] = sumcheck;		
    buf[cnt++] = 0x5A;
    Send(buf,cnt);//调用数据帧发送函数将打包好的数据帧发送出去
}
//数据解析
void DataAnalysis(uint8_t *Data)
{
		receive_data.ch[0]=(int16_t)(Data[1]<<8|Data[0]);
  	receive_data.ch[1]=(int16_t)(Data[3]<<8|Data[2]);
	  receive_data.ch[2]=(int16_t)(Data[5]<<8|Data[4]);
}
//和校验
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
//接收数据
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

