#include "bsp_uart.h"
#include "stm32f407xx.h"
#include "usart.h"
#include "chassic.h"

float x1,y1,w1;
extern ROBOT::Rxbuffer rxbuffer;
uint8_t rxbuf_odometer[1];
extern uint8_t odometer_data[12];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

    if(huart->Instance==USART2)
    {
        ReceivefromMapan(rxbuf_odometer[0]);
    }

}
void SendByte(uint8_t date)
{

        uint8_t buffer[1];
        buffer[0] = date;  
	HAL_UART_Transmit( &huart4 , buffer , 1,100 );
       

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
void Send_Cmd_Data(uint8_t cmd,const uint8_t *datas,uint8_t len)
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
	HAL_UART_Transmit_DMA( &huart4 , buf , cnt );
    // Send(buf,cnt);//调用数据帧发送函数将打包好的数据帧发送出去
}

//数据帧解析
void Data_Analysis(uint8_t cmd,const uint8_t *datas,uint8_t len)
{
        //根据需要处理数据
        // Remote_Data.ch[0]=datas[0];
        // Remote_Data.ch[1]=datas[1];
        // Remote_Data.ch[2]=datas[2];
        // Remote_Data.ch[3]=datas[3];


    memcpy(&x1,&datas[0],4);
    memcpy(&y1,&datas[4],4);
    memcpy(&w1,&datas[8],4);
//if(Remote_Data.ch[0]==0xFF)
//{
//	task_flag=1;
//}
	

//        Remote_Data.ch[4]=datas[4];
//        Remote_Data.key[0]=datas[5];
//        Remote_Data.key[1]=datas[6];

}

//接收数据
void Receive(uint8_t bytedata)
{

        static uint8_t step=0;//状态变量初始化为0 在函数中必须为静态变量
        static uint8_t cnt=0,Buf[300],len,cmd,*data_ptr;
        static uint16_t crc16;
        //进行数据解析 状态机
        switch(step)
        {
            case 0://接收帧头1状态
                if(bytedata== 0xA5)
                {
                    step++;
                    cnt = 0;
                    Buf[cnt++] = bytedata;
                }break;
            case 1://接收帧头2状态
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
            case 2://接收数据长度字节状态
                step++;
                Buf[cnt++] = bytedata;
                len = bytedata;
                break;
            case 3://接收命令字节状态
                step++;
                Buf[cnt++] = bytedata;
                cmd = bytedata;
                data_ptr = &Buf[cnt];//记录数据指针首地址
                if(len == 0)step++;//数据字节长度为0则跳过数据接收状态
                break;
            case 4://接收len字节数据状态
                Buf[cnt++] = bytedata;
                if(data_ptr + len == &Buf[cnt])//利用指针地址偏移判断是否接收完len位数据
                {
                    step++;
                }
                break;
            case 5://接收crc16校验高8位字节
                step++;
                crc16 = bytedata;
                break;
            case 6://接收crc16校验低8位字节
                crc16 <<= 8;
                crc16 += bytedata;
                if(crc16 == CRC16_Check(Buf,cnt))//校验正确进入下一状态
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
            case 7://接收帧尾
                if(bytedata== 0xFF)//帧尾接收正确
                {
                        Data_Analysis(cmd,data_ptr,len);//数据解析
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
            default:step=0;break;//多余状态，正常情况下不可能出现
        }
}
extern "C"
void tx_to_upper(void const * argument)
{
  /* USER CODE BEGIN tx_to_upper */
  /* Infinite loop */
  for(;;)
  {
    Send_Cmd_Data(0,odometer_data,12);
    osDelay(20);
  }
  /* USER CODE END tx_to_upper */
}


// void USART2_IRQHandler(void)
// {
//   /* USER CODE BEGIN USART2_IRQn 0 */

//   /* USER CODE END USART2_IRQn 0 */
//   HAL_UART_IRQHandler(&huart2);
//   /* USER CODE BEGIN USART2_IRQn 1 */
//  HAL_UART_Receive_IT(&huart2, rxbuffer.upper, 1);

//   /* USER CODE END USART2_IRQn 1 */
// }
