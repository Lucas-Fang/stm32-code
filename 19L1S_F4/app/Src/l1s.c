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
* @brief LI1�����������ͺ�����ͨ���˺���ʹ�ò�ͬ��ģʽ
*
* @param cmd ��ڲ���Ϊ����ģʽѡ�񣬿��Դ�ͷ�ļ��еĺ궨��ѡ��ģʽ
*
*/
void Send_L1S_cmd_data(uint8_t cmd)
{
    uint8_t uchArr[5]={0XA5, 0X5A, cmd, 0X00, 0XFB};
    uchArr[4]=BBC_Check(uchArr,4);

    HAL_UART_Transmit_DMA(&huart2, uchArr, 5);
}

/**
* @brief BBC���У�麯��
*
* @param *puchMsg   ͨ��ָ��������ҪУ��������׵�ַ
* @param uchDataLen ��ҪУ��������ܳ���
* @return uchBBC    ����ֵΪУ��λ
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
* @brief LI1���������ݽ��պ���
*
* @param msg_data_point ��ڲ���Ϊͨ�����ڽ��յ������ݣ�ÿ��ֻ����һ�ֽ�
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
				data_ptr=&Buff[count];//�˴���buffΪcmd
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
* @brief LI1���������ݽ�����������4�ֽڵ����ݺϳ�һ��int���͵�����
*
* @param *buff ʹ��ָ���ȡ�����׵�ַ
* @return void
*
*/
void DataAnalysis(uint8_t *buff)
{
	//uint8_t cmd = buff[0];
	
  Laser_Data = (int32_t)(buff[1]<<24) | (buff[2]<<16) | (buff[3]<<8) | buff[4];

}
