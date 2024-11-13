#include "l1s.h"
#include "usart.h"
#include <stdio.h>


int32_t Laser_Data;
uint8_t rx_buffer[1];
uint8_t a[8],b;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART2)
    {
        
        b++;
        a[b]=rx_buffer[0];
        if (b==7)
        {
            b=0;
        }
				Read_L1S(rx_buffer[0]);
//				Read_LaserData(rx_buffer);
    }
}

/**
* @brief LI1激光测距任务发送函数，通过此函数使用不同的模式
*
* @param cmd 入口参数为命令模式选择，可以从头文件中的宏定义选择模式
*
*/
void Send_L1S_cmd_data(uint8_t cmd)
{
    uint8_t uchArr[5]={0XA5, 0X5A, cmd, 0X00, 0XFB};
    uchArr[4]=BBC_Check(uchArr,4);

    HAL_UART_Transmit_DMA(&huart2, uchArr, 5);
}

/**
* @brief BBC异或校验函数
*
* @param *puchMsg   通过指针输入需要校验的数据首地址
* @param uchDataLen 需要校验的数据总长度
* @return uchBBC    返回值为校验位
*/
uint8_t BBC_Check(uint8_t *puchMsg,uint8_t uchDataLen)
{
	uint8_t uchBBC = 0x00;
	int8_t i = 0;
	for (; i <uchDataLen; i++)
	{
		uchBBC ^= puchMsg[i];
	}
	return uchBBC;
}
//bool Read_LaserData(uint8_t *msg_data_point)
//{
//    static uint8_t flag=0;
//    static uint8_t msg_data_pre=0;
//    static uint8_t buff[L1S_DATA_lEN];
//    static uint8_t CheckBBC;
//    static uint8_t rx_cent=1;

//    if(msg_data_pre==0xB4&& *msg_data_point==0x69)
//    {
//        flag = 1;
//        if(flag==1)
//        {
//            buff[0] = msg_data_pre;
//            buff[rx_cent++] = *msg_data_point;
////            if (buff[2]==0x80) 
////            {
////                return false;
////            }
//            if(rx_cent==L1S_DATA_lEN-1)
//            {
//                CheckBBC = BBC_Check(buff,L1S_DATA_lEN-7);
//                if (CheckBBC==buff[L1S_DATA_lEN-1])
//                {
//                    Laser_Data = (int32_t)(buff[3]<<24) | (buff[4]<<16) | (buff[5]<<8) | buff[6];
//									  rx_cent=1;
//										msg_data_pre=0;
//									
//                    return true;
//                }
//            }
//        }
//    }
//    else
//    {
//        msg_data_pre=*msg_data_point;
//    }
//    return false;
//}

/**
* @brief LI1激光测距数据接收函数
*
* @param msg_data_point 入口参数为通过串口接收到的数据，每次只接受一字节
* @return void
*
*/
void Read_L1S(uint8_t msg_data_point)
{
	static uint8_t step=0;
	static uint8_t count=0,Buff[100]={0},*data_ptr;
	
	
	switch(step)
	{
		case 0:
		  if(msg_data_point == 0xB4)
	  	{
  			step++;
				Buff[count++]=msg_data_point;
  		}break;
		case 1:
			if(msg_data_point == 0x69)
			{
  			step++;
				Buff[count++]=msg_data_point;		
				data_ptr=&Buff[count];//此处的buff为cmd
			}
			else
			{
				step =0;
				count = 0;
			}break;
		case 2:
			Buff[count++]=msg_data_point;
			if(count==L1S_DATA_lEN-1 )
			{
				step++;
			}break;
		case 3:
			Buff[count++]=msg_data_point;
			if(BBC_Check(Buff,L1S_DATA_lEN-1)==Buff[L1S_DATA_lEN-1])
			{
				DataAnalysis(data_ptr);
				step =0;
				count = 0;
			}
			else
			{
				step=0;
				count=0;
			}break;
		default: break;
	}
}
/**
* @brief LI1激光测距数据解析函数，将4字节的数据合成一个int类型的数据
*
* @param *buff 使用指针获取数据首地址
* @return void
*
*/
void DataAnalysis(uint8_t *buff)
{
	//uint8_t cmd = buff[0];
	
  Laser_Data = (int32_t)(buff[1]<<24) | (buff[2]<<16) | (buff[3]<<8) | buff[4];

}
