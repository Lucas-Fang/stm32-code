#include "bsp_usart.h"
#include "chassic.h"
#include "main.h"
#include "stm32f1xx_hal_def.h"
#include "stm32f1xx_hal_dma_ex.h"
#include "stm32f1xx_hal_uart.h"
#include "usart.h"

bool stop_flag=0;
uint8_t rx_buffer[1];
extern uint8_t HWT101CT_buffer[1];

uint8_t data[7];

 uint8_t a[DATA_LEN+3];
 uint8_t b;
remote_data receive_data;
extern ROBOT::CHASSIC::remote_control_speed speed;


extern "C"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//ï¿½ï¿½ï¿½ï¿½Ò£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ï¢
	if(huart->Instance == USART1)
	{
		Receive_data(rx_buffer[0],DATA_LEN);
	  	
	if(stop_flag)
	{
		while (1) 
		{
		Back_L(0);
		Back_R(0);
		
		}
	}
		 
// /*²âÊÔËùÓÃ*/
// 		a[b]=rx_buffer[0];
// 		b++;
// 		if(b == DATA_LEN) 
// 		{
// 			b = 0;
//		}
 		}	


	//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ï¢
	if(huart->Instance == USART3)
	{
		IMU_Read_Euler(HWT101CT_buffer); 
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
                SendByte(data[i]);//ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½ï¿½Ö½ï¿½
        }
}

//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý°ï¿½
void Send_Cmd_Data(const uint8_t *datas,uint8_t len)
{
    uint8_t buf[300],i,cnt=0;
    uint8_t sumcheck;
    buf[cnt++] = 0xA5;

    for(i=0;i<len;i++)
    {
        buf[cnt++] = datas[i];
    }
    sumcheck = SUMCRC(buf,len);
    buf[cnt++] = sumcheck;		
    buf[cnt++] = 0x5A;
    Send(buf,cnt);//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ö¡ï¿½ï¿½ï¿½Íºï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ãµï¿½ï¿½ï¿½ï¿½ï¿½Ö¡ï¿½ï¿½ï¿½Í³ï¿½È?
}
//ï¿½ï¿½ï¿½Ý½ï¿½ï¿½ï¿½
void DataAnalysis(uint8_t *Data)
{
	 receive_data.ch[0]=(int16_t)(Data[1]<<8|(int16_t)Data[0]);
     receive_data.ch[1]=(int16_t)(Data[3]<<8|(int16_t)Data[2]);
	 receive_data.ch[2]=(int16_t)(Data[5]<<8|(int16_t)Data[4]);
   
	speed.vx=receive_data.ch[0];
	speed.vy=receive_data.ch[1];
	speed.vomega=receive_data.ch[2];
}
//ï¿½ï¿½Ð£ï¿½ï¿½
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
//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
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



void Send_Data()
{
	uint8_t flag=0;

	data[0]=0xA5;
	data[1]=robot.chassic.Motor_Speed_Target[0];
	data[2]=robot.chassic.Motor_Speed_Target[0]>>8;
	data[3]=robot.chassic.Motor_Speed_Target[1];
	data[4]=robot.chassic.Motor_Speed_Target[1]>>8;
	data[5]=SUMCRC(data,4);
	data[6]=0X5A;

	if(flag==0)
	{
		HAL_UART_Transmit_DMA(&huart2, data, 7);
		flag=1;
	}

	if(__HAL_DMA_GET_FLAG(hdma_usart2_tx, DMA_FLAG_TC1)==1)
	{
		HAL_UART_Transmit_DMA(&huart2, data, 7);

		__HAL_DMA_CLEAR_FLAG(hdma_usart2_tx,DMA_FLAG_TC1);
	}
	// if(HAL_UART_Transmit_DMA(&huart2, data, 7)!=HAL_OK)
	// {
	// 	Error_Handler();
	// }
	//  HAL_UART_Transmit(&huart2, data, 7, 1000);
//	HAL_UART_Transmit_DMA(&huart2, data, 7);
}