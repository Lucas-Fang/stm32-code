#include "bsp_can.h"
#include "can.h"


void CAN_BUS::BSP::CAN_Start(CAN_HandleTypeDef *hcan)
{
    if(HAL_CAN_Start(hcan) != HAL_OK)
    {
        Error_Handler();
    }
    if(HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
        Error_Handler();
    }
}


void CAN_BUS::BSP::Filter_Init(CAN_HandleTypeDef *hcan)
{
    if(hcan->Instance==CAN1)
    {
        CAN_FilterTypeDef CAN_Filter_st;

        CAN_Filter_st.FilterActivation = ENABLE;
        CAN_Filter_st.FilterMode = CAN_FILTERMODE_IDMASK;
        CAN_Filter_st.FilterScale = CAN_FILTERSCALE_32BIT;
        CAN_Filter_st.FilterIdHigh = 0x0000;
        CAN_Filter_st.FilterIdLow = 0x0000;
        CAN_Filter_st.FilterMaskIdHigh = 0x0000;
        CAN_Filter_st.FilterMaskIdLow = 0x0000;
        CAN_Filter_st.FilterBank = 0;
        CAN_Filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;

        if(HAL_CAN_ConfigFilter(hcan, &CAN_Filter_st)!=HAL_OK)       //ÂË²¨Æ÷³õÊ¼»¯
        {
            Error_Handler();
        }

    }
    else if(hcan->Instance == CAN2)
	{
	// 	CAN_FilterTypeDef CAN_Filter_st;
    //     CAN_Filter_st.FilterActivation = ENABLE;
    //     CAN_Filter_st.FilterMode = CAN_FILTERMODE_IDMASK;
    //     CAN_Filter_st.FilterScale = CAN_FILTERSCALE_32BIT;
    //     CAN_Filter_st.FilterIdHigh = 0x0000;
    //     CAN_Filter_st.FilterIdLow = 0x0000;
    //     CAN_Filter_st.FilterMaskIdHigh = 0x0000;
    //     CAN_Filter_st.FilterMaskIdLow = 0x0000;
    //     CAN_Filter_st.FilterBank = 14;
    //     CAN_Filter_st.SlaveStartFilterBank = 14;
    //     CAN_Filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
	//   if(HAL_CAN_ConfigFilter(hcan, &CAN_Filter_st)!=HAL_OK)        //??????
	// 	{
	// 		Error_Handler();
	// 	}

        CAN_FilterTypeDef sFilterConfig;    
        sFilterConfig.FilterBank = 14;//can2 ?????????13???can2???????
        sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
        sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
        sFilterConfig.FilterIdHigh =0x0000;
        sFilterConfig.FilterIdLow = 0x0000;
        sFilterConfig.FilterMaskIdHigh = 0x0000;
        sFilterConfig.FilterMaskIdLow = 0x0000;
        sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
        sFilterConfig.FilterActivation = ENABLE;
        sFilterConfig.SlaveStartFilterBank = 14;
        if(HAL_CAN_ConfigFilter(&hcan2, &sFilterConfig) != HAL_OK){
        /* Filter configuration Error */
        Error_Handler();
        }

	}

}