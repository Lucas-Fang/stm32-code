#include "Communition.h"
#include "bsp_usart.h"
#include "chassic.h"
#include "usart.h"
#include "usbd_cdc.h"

Rxbuffer all_rxbuff;

extern "C"
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */
 HAL_UART_Receive_IT(&huart1, all_rxbuff.upper, 1);
  /* USER CODE END USART1_IRQn 1 */
}


uint16_t CRC16_Check(const uint8_t *data, uint8_t len)
{
	uint16_t CRC16 = 0xFFFF;
	uint8_t state, i, j;
	for (i = 0; i < len; i++)
	{
		CRC16 ^= data[i];
		for (j = 0; j < 8; j++)
		{
			state = CRC16 & 0x01;
			CRC16 >>= 1;
			if (state)
			{
				CRC16 ^= 0xA001;
			}
		}
	}
	return CRC16;
}
void SendByte(uint8_t date)
{
        uint8_t buffer[1];
        buffer[0] = date;  
	HAL_UART_Transmit( &huart1 , buffer , 1,100 );
}

void Send(const uint8_t *data,uint8_t len)
{
        uint8_t i;
        for (i = 0; i < len; i++)
        {
            SendByte(data[i]);//����һ���ֽ�
        }
}


//�������ݰ�
void Send_Cmd_Data_by_UART(uint8_t cmd,const uint8_t *datas,uint8_t len)
{
    uint8_t buf[300],i,cnt=0;
    uint16_t crc16;
    buf[cnt++] = 0xA5;
    buf[cnt++] = 0x5A;
    buf[cnt++] = len;
    buf[cnt++] = cmd;
    for(i=0;i<len;i++)
    {
        buf[cnt++] = datas[i];
    }
    crc16 = CRC16_Check(buf,len+4);
    buf[cnt++] = crc16>>8;
    buf[cnt++] = crc16&0xFF;
    buf[cnt++] = 0xFF;
	HAL_UART_Transmit( &huart1 , buf , cnt,100 );
    // Send(buf,cnt);//��������֡���ͺ���������õ�����֡���ͳ�ȥ
}


void Send_Cmd_Data_by_USB(uint8_t cmd,const uint8_t *datas,uint8_t len)
{
    uint8_t buf[300],i,cnt=0;
    uint16_t crc16;
    buf[cnt++] = 0xA5;
    buf[cnt++] = 0x5A;
    buf[cnt++] = len;
    buf[cnt++] = cmd;
    for(i=0;i<len;i++)
    {
        buf[cnt++] = datas[i];
    }
    crc16 = CRC16_Check(buf,len+4);
    buf[cnt++] = crc16>>8;
    buf[cnt++] = crc16&0xFF;
    buf[cnt++] = 0xFF;
    CDC_Transmit_HS(buf,cnt);
}

//����֡����
void Data_Analysis_From_upper(uint8_t cmd,uint8_t *datas,uint8_t len)
{
        robot.robot_commend = cmd;
        
        memcpy(&robot.upper_data[0],&datas[0],4);//X
        memcpy(&robot.upper_data[1],&datas[4],4);//Y
        memcpy(&robot.upper_data[2],&datas[8],4); //OMEGA
        memcpy(&robot.upper_data[3],&datas[12],4); //����
        memcpy(&robot.upper_data[4],&datas[16],4); //SPEED_rpm

        robot.Distance = robot.upper_data[3];

}

//��������
extern "C"
void Receive_From_upper(uint8_t bytedata)
{

        static uint8_t step=0;//״̬������ʼ��Ϊ0 �ں����б���Ϊ��̬����
        static uint8_t cnt=0,Buf[300],len,cmd,*data_ptr;
        static uint16_t crc16;
        //�������ݽ��� ״̬��
        switch(step)
        {
            case 0://����֡ͷ1״̬
                if(bytedata== 0xA5)
                {
                    step++;
                    cnt = 0;
                    Buf[cnt++] = bytedata;
                }break;
            case 1://����֡ͷ2״̬
                if(bytedata== 0x5A)
                {
                    step++;
                    Buf[cnt++] = bytedata;
                }
                else if(bytedata== 0xA5)
                {
                    step = 1;
                }
                else
                {
                    step = 0;
                }
                break;
            case 2://�������ݳ����ֽ�״̬
                step++;
                Buf[cnt++] = bytedata;
                len = bytedata;
                break;
            case 3://���������ֽ�״̬
                step++;
                Buf[cnt++] = bytedata;
                cmd = bytedata;
                data_ptr = &Buf[cnt];//��¼����ָ���׵�ַ
                if(len == 0)step++;//�����ֽڳ���Ϊ0���������ݽ���״̬
                break;
            case 4://����len�ֽ�����״̬
                Buf[cnt++] = bytedata;
                if(data_ptr + len == &Buf[cnt])//����ָ���ַƫ���ж��Ƿ������lenλ����
                {
                    step++;
                }
                break;
            case 5://����crc16У���8λ�ֽ�
                step++;
                crc16 = bytedata;
                break;
            case 6://����crc16У���8λ�ֽ�
                crc16 <<= 8;
                crc16 += bytedata;
                if(crc16 == CRC16_Check(Buf,cnt))//У����ȷ������һ״̬
                {
                    step ++;
                }
                else if(bytedata == 0xA5)
                {
                    step = 1;
                }
                else
                {
                    step = 0;
                }
                break;
            case 7://����֡β
                if(bytedata== 0xFF)//֡β������ȷ
                {
                        Data_Analysis_From_upper(cmd,data_ptr,len);//���ݽ���
                    step = 0;
                }
                else if(bytedata == 0xA5)
                {
                    step = 1;
                }
                else
                {
                    step = 0;
                }
                break;
            default:step=0;break;//����״̬����������²����ܳ���
        }
}