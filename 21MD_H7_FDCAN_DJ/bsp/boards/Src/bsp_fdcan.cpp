#include "bsp_fdcan.h"
#include "stm32h723xx.h"

/**
 * @brief       FDCANͨ�ſ�������
 * @param       hcan��FDCANͨ�ž��
 * @retval      void
 * @note        �����ȳ�ʼ��FDCANͨ���˲��������ٿ���CANͨ��
 */
void CAN_BUS::BSP::FDCAN_Start(FDCAN_HandleTypeDef *hfdcan)
{
	if(HAL_FDCAN_Start(hfdcan) != HAL_OK)
	{
		Error_Handler();
	}

	if(HAL_FDCAN_ActivateNotification(hfdcan,FDCAN_IT_RX_FIFO0_NEW_MESSAGE,0) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief       FDCANͨ���˲�����
 * @param       hcan��FDCANͨ�ž��
 * @retval      void
 * @note        ����FDCANͨ�Ž���ʱ�������ʼ���ú��������齫�ú�����FDCANͨ�ſ���ǰ�ͱ���ʼ��
 */
void CAN_BUS::BSP::Filter_Init(FDCAN_HandleTypeDef *hfdcan)
{
	if(hfdcan->Instance == FDCAN1)	
	{
		FDCAN_FilterTypeDef  FDCAN_Filter_st;
		FDCAN_Filter_st.IdType = FDCAN_STANDARD_ID;//��׼ID 
		FDCAN_Filter_st.FilterIndex = 0;			//�˲�������
		FDCAN_Filter_st.FilterType = FDCAN_FILTER_MASK; // ʹ���������
		FDCAN_Filter_st.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;//������0������FIFO0  
		FDCAN_Filter_st.FilterID1 = 0x200; // ��ʼID��λ�� 0x200
		FDCAN_Filter_st.FilterID2 = 0x7F8; // ������Ե�3λ��2^3=8

	    if(HAL_FDCAN_ConfigFilter(hfdcan, &FDCAN_Filter_st)!=HAL_OK)       //�˲�����ʼ��
		{
				Error_Handler();
		}
		//
		if (HAL_FDCAN_ConfigGlobalFilter(hfdcan, FDCAN_ACCEPT_IN_RX_FIFO0,// ��ƥ���׼֡����� FIFO0
			FDCAN_REJECT,										 // ��ƥ����չ֡bu����� FIFO0
			FDCAN_FILTER_REMOTE, 
			FDCAN_FILTER_REMOTE) != HAL_OK)
		{
		   	Error_Handler();
		}
		//���� FIFO0 ˮλ���ж�֪ͨ,ˮλ����ֵ��0~63������ʾ�� FIFO �е���Ϣ���ﵽ���ֵʱ�����ж�
		if (HAL_FDCAN_ConfigFifoWatermark(&hfdcan1, FDCAN_RX_FIFO0, 1) != HAL_OK) 
		{
			Error_Handler();
		}
	}

	if(hfdcan->Instance == FDCAN2)	
	{
		FDCAN_FilterTypeDef  FDCAN_Filter_st;
		FDCAN_Filter_st.IdType = FDCAN_STANDARD_ID;//��׼ID 
		FDCAN_Filter_st.FilterIndex = 0;			//�˲�������
		FDCAN_Filter_st.FilterType = FDCAN_FILTER_MASK; // ʹ���������
		FDCAN_Filter_st.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;//������0������FIFO0  
		FDCAN_Filter_st.FilterID1 = 0x200; // ��ʼID��λ�� 0x200
		FDCAN_Filter_st.FilterID2 = 0x7F8; // ������Ե�3λ��2^3=8

	    if(HAL_FDCAN_ConfigFilter(hfdcan, &FDCAN_Filter_st)!=HAL_OK)       //�˲�����ʼ��
		{
				Error_Handler();
		}
		//
		if (HAL_FDCAN_ConfigGlobalFilter(hfdcan, FDCAN_ACCEPT_IN_RX_FIFO0,// ��ƥ���׼֡����� FIFO0
			FDCAN_REJECT,										 // ��ƥ����չ֡bu����� FIFO0
			FDCAN_FILTER_REMOTE, 
			FDCAN_FILTER_REMOTE) != HAL_OK)
		{
		   	Error_Handler();
		}
		//���� FIFO0 ˮλ���ж�֪ͨ,ˮλ����ֵ��0~63������ʾ�� FIFO �е���Ϣ���ﵽ���ֵʱ�����ж�
		if (HAL_FDCAN_ConfigFifoWatermark(hfdcan, FDCAN_RX_FIFO0, 1) != HAL_OK) 
		{
			Error_Handler();
		}
	}
	
}
