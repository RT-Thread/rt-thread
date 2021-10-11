/*
  ******************************************************************************
  * @file    HAL_Can.c
  * @version V1.0.0
  * @date    2020
  * @brief   CAN HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Universal Asynchronous Receiver Transmitter Peripheral (CAN).
  *           @ Initialization and de-initialization functions
  *           @ IO operation functions
  *           @ Peripheral Control functions
  ******************************************************************************
*/
#include "ACM32Fxx_HAL.h"

/*********************************************************************************
* Function    : HAL_CAN_OperatingModeRequest
* Description : Select the CAN Operation mode.
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Input       : CAN_OperatingMode:CAN Operating Mode. This parameter can be one  of @ref CAN_OperatingMode enumeration.
* Output      : HAL status
* Author      : CWT                         Data : 2020
**********************************************************************************/
HAL_StatusTypeDef HAL_CAN_OperatingModeRequest(CAN_HandleTypeDef *hcan, uint8_t CAN_OperatingMode)
{
    uint8_t status = HAL_ERROR;
    /* Check the parameters */
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return HAL_ERROR;
    if(!IS_CAN_OPERATING_MODE(CAN_OperatingMode)) return HAL_ERROR;
    if (CAN_OperatingMode == CAN_OperatingMode_Initialization)
    {
        hcan->Instance->MOD |= CAN_OperatingMode_Initialization;  // enter Initialization 
        if ((hcan->Instance->MOD & CAN_MOD_RM) != CAN_OperatingMode_Initialization)
        {
            status = HAL_ERROR;
        }
        else
        {
            status = HAL_OK;
        }
    }
    else if(CAN_OperatingMode == CAN_OperatingMode_Normal)
    {
        hcan->Instance->MOD &=~ CAN_OperatingMode_Initialization;   //1-->0 enter Normal 
        if ((hcan->Instance->MOD & CAN_MOD_RM) != CAN_OperatingMode_Normal)
        {
            status = HAL_ERROR;
        }
        else
        {
            status = HAL_OK;
        }
    }
    else if (CAN_OperatingMode == CAN_OperatingMode_Sleep)
    {
        hcan->Instance->MOD |= CAN_OperatingMode_Sleep;  // enter Normal 
        if ((hcan->Instance->MOD & CAN_MOD_SM) != CAN_OperatingMode_Sleep)
        {
            status = HAL_ERROR;
        }
        else
        {
            status = HAL_OK;
        }
    }
    else if(CAN_OperatingMode == CAN_OperatingMode_Listen)
    {
        hcan->Instance->MOD |= CAN_OperatingMode_Listen;  // enter Normal 
        if((hcan->Instance->MOD & CAN_MOD_LOM) != CAN_OperatingMode_Listen)
        {
            status = HAL_ERROR;
        }
        else
        {
            status = HAL_OK;
        }
    }
    else
    {
        status = HAL_ERROR;
    }
    return  (uint8_t) status;
}


/*********************************************************************************
* Function    : HAL_CAN_MspInit
* Description : Initialize the CAN MSP.
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Output      : 
* Author      : CWT                         Data : 2020
**********************************************************************************/

__weak void HAL_CAN_MspInit(CAN_HandleTypeDef *hcan)
{
    /* NOTE : This function should not be modified, when the callback is needed,
                the HAL_UART_MspInit can be implemented in the user file
    */
    /* For Example */
    GPIO_InitTypeDef   GPIO_InitStruct;
    if(hcan->Instance==CAN1)
    {
        /* Enable CAN clock */
        System_Module_Enable(EN_CAN1);
        GPIO_InitTypeDef GPIO_InitStructure;   	
        /* Initialization GPIO */
        /* PA11:Rx */  /* PA12:Tx */
        GPIO_InitStructure.Pin = GPIO_PIN_11|GPIO_PIN_12;	
        GPIO_InitStructure.Alternate=GPIO_FUNCTION_5;
        GPIO_InitStructure.Pull=GPIO_PULLUP;
        GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
        
    }
    else if(hcan->Instance==CAN2)
    {
        /* Enable CAN clock */
        System_Module_Enable(EN_CAN2);
        GPIO_InitTypeDef GPIO_InitStructure;   	
        /* Initialization GPIO */
        /* PB5:Rx */  /* PB6:Tx */
        GPIO_InitStructure.Pin = GPIO_PIN_5|GPIO_PIN_6;	
        GPIO_InitStructure.Alternate=GPIO_FUNCTION_5;
        GPIO_InitStructure.Pull=GPIO_PULLUP;
        GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
        
        /* Enable the CAN Receive interrupt */
        hcan->Instance->IER |= CAN_IER_RIE;
        NVIC_ClearPendingIRQ(CAN2_IRQn);
        NVIC_SetPriority(CAN2_IRQn, 5);
        NVIC_EnableIRQ(CAN2_IRQn);
    }
    
}
/*********************************************************************************
* Function    : HAL_CAN_MspDeInit
* Description :	CAN MSP De-Initialization 
*               This function frees the hardware resources used in this example:
*              - Disable the Peripheral's clock
*              - Revert GPIO configuration to their default state
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Output      : 
* Author      : CWT                         Data : 2020
**********************************************************************************/
void HAL_CAN_MspDeInit(CAN_HandleTypeDef *hcan)
{
    if(hcan->Instance==CAN1)
    {
        /* Reset CAN clock */
        System_Module_Disable(EN_CAN1);
        GPIO_InitTypeDef GPIO_InitStructure;   	
        /* Initialization GPIO */
        /* PA11:Rx */  /* PA12:Tx */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11);
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_12);
        }
        else if(hcan->Instance==CAN2)
        {
        /* Reset CAN clock */
        System_Module_Disable(EN_CAN2);
        GPIO_InitTypeDef GPIO_InitStructure;   	
        /* Initialization GPIO */
        /* PB5:Rx */  /* PB6:Tx */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_5);
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);
    }
}
/*********************************************************************************
* Function    : HAL_CAN_Init
* Description :	Initializes the CAN peripheral according to the specified  parameters in the CAN_HandleTypeDef..
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Output      : HAL status
* Author      : CWT                         Data : 2020
**********************************************************************************/
HAL_StatusTypeDef HAL_CAN_Init(CAN_HandleTypeDef *hcan)
{
    uint8_t InitStatus = HAL_ERROR;
    /* Check the parameters */
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return HAL_ERROR;
    if(!IS_CAN_MODE(hcan->Init.CAN_Mode)) return HAL_ERROR;
    if(!IS_CAN_SJW(hcan->Init.CAN_SJW)) return HAL_ERROR;
    if(!IS_CAN_TSEG1(hcan->Init.CAN_TSEG1)) return HAL_ERROR;
    if(!IS_CAN_TSEG2(hcan->Init.CAN_TSEG2)) return HAL_ERROR;
    if(!IS_CAN_BRP(hcan->Init.CAN_BRP)) return HAL_ERROR;
    if(!IS_CAN_SAM(hcan->Init.CAN_SAM)) return HAL_ERROR;
    /* Reset the CANx */
    if(hcan->Instance==CAN1)
    {
        System_Module_Reset(RST_CAN1);
    }
    else
    {
        System_Module_Reset(RST_CAN2);
    }
    HAL_CAN_MspInit(hcan);
    HAL_CAN_OperatingModeRequest(hcan,CAN_OperatingMode_Initialization);//enter CAN_OperatingMode_Initialization
    hcan->Instance->BTR0=0xff;
    hcan->Instance->BTR0=(hcan->Init.CAN_SJW<<6)|(hcan->Init.CAN_BRP);
    hcan->Instance->BTR1=(hcan->Init.CAN_SAM<<7)|(hcan->Init.CAN_TSEG2<<4)|(hcan->Init.CAN_TSEG1);
    HAL_CAN_OperatingModeRequest(hcan,CAN_OperatingMode_Normal);//enter CAN_OperatingMode_Normal
    return HAL_OK;
}


/*********************************************************************************
* Function    : HAL_CAN_DeInit
* Description :	Deinitializes the CAN peripheral registers to their default
*               reset values.
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Output      : HAL status
* Author      : CWT                         Data : 2020
**********************************************************************************/
HAL_StatusTypeDef HAL_CAN_DeInit(CAN_HandleTypeDef *hcan)
{
    /* Check CAN handle */
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return HAL_ERROR;

    HAL_CAN_MspDeInit(hcan);
    
    /* Reset the CAN peripheral */
    SET_BIT(hcan->Instance->MOD, CAN_MOD_RM);
    
    /* Return function status */
    return HAL_OK;
}
/*********************************************************************************
* Function    : HAL_CAN_Transmit
* Description :	Initiates the transmission of a message.
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Input       : TxMessage : ppointer to a structure which contains CAN Id, CAN
  *                         DLC and CAN data.
* Output      : 
* Author      : CWT                         Data : 2020
**********************************************************************************/
HAL_StatusTypeDef HAL_CAN_Transmit(CAN_HandleTypeDef *hcan, CanTxRxMsg* TxMessage)
{
    uint8_t i = 0;
    uint8_t can_id[4];  
    uint32_t frame_header;  
    /* Check the parameters */
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return HAL_ERROR ;
    if(!IS_CAN_IDTYPE(TxMessage->IDE)) return HAL_ERROR;
    if(!IS_CAN_RTR(TxMessage->RTR)) return HAL_ERROR;
    if(!IS_CAN_DLC(TxMessage->DLC)) return HAL_ERROR;
    /* Set up the DLC */
    frame_header =TxMessage->DLC & 0x0F;  // standard data frame 
    /* Set up the Id */
    if(TxMessage->IDE==CAN_Id_Standard)//Standard ID
    {
        can_id[0] = TxMessage->StdId >>3; 
        can_id[1] = (TxMessage->StdId&0x07)<<5;   
        for(i=0;i<2;i++)
        {
            hcan->Instance->DF.DATABUF[1+i] = can_id[i];  
        }
    }
    else//Id_Extended
    {
        can_id[0] = TxMessage->ExtId>>21; 
        can_id[1] = (TxMessage->ExtId&0x1FE000)>>13;   
        can_id[2] = (TxMessage->ExtId&0x1FE0)>>5; 
        can_id[3] = (TxMessage->ExtId&0x1F)<<3;
        frame_header |= (CAN_Id_Extended<<7);  // extended data frame 
        for(i=0;i<4;i++)
        {
            hcan->Instance->DF.DATABUF[1+i] = can_id[i];  
        }
    }
    if(TxMessage->RTR==CAN_RTR_Data)//CAN_RTR_Data
    {
        frame_header&=~(CAN_RTR_Remote<<6);
        for(i=0; i<TxMessage->DLC; i++)  
        {
            hcan->Instance->DF.DATABUF[3+(TxMessage->IDE*2)+i] = TxMessage->Data[i];      
        }
    }
    else//CAN_RTR_Remote
    {
        frame_header|=(CAN_RTR_Remote<<6);
    }
    hcan->Instance->DF.DATABUF[0]=frame_header;
    hcan->Instance->CMR = CAN_CMR_TR;  // transfer request
    while((hcan->Instance->SR & CAN_SR_TCS)==0x00); //wait for send ok	
    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_CAN_CancelTransmit
* Description :	Cancels a transmit request.
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Output      : 
* Author      : CWT                         Data : 2020
**********************************************************************************/
void HAL_CAN_CancelTransmit(CAN_HandleTypeDef *hcan)
{
    /* Check the parameters */
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return ;
    /* abort transmission */
    hcan->Instance->CMR |= CAN_CMR_AT; //Abort Transmission 
}

/*********************************************************************************
* Function    : HAL_CAN_Receive
* Description :	Receives a message.
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Input       : RxMessage : pointer to a structure receive message which contains 
*                           CAN Id, CAN DLC, CAN datas  .
* Output      : 
* Author      : CWT                         Data : 2020
**********************************************************************************/
HAL_StatusTypeDef HAL_CAN_Receive_IT(CAN_HandleTypeDef *hcan, CanTxRxMsg* RxMessage)
{
    /* Check the parameters */
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return HAL_ERROR ;
    
    hcan->RxMessage=RxMessage;

    /* Enable the CAN Receive interrupt */
    hcan->Instance->IER |= CAN_IER_RIE;
    NVIC_ClearPendingIRQ(CAN1_IRQn);
    NVIC_SetPriority(CAN1_IRQn, 5);
    NVIC_EnableIRQ(CAN1_IRQn);

    return HAL_OK;
}


/*********************************************************************************
* Function    : HAL_CAN_Receive
* Description :	Receives a message.
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Input       : RxMessage : pointer to a structure receive message which contains 
*                           CAN Id, CAN DLC, CAN datas  .
* Output      : 
* Author      : CWT                         Data : 2020
**********************************************************************************/
HAL_StatusTypeDef HAL_CAN_Receive(CAN_HandleTypeDef *hcan, CanTxRxMsg* RxMessage)
{
    /* Check the parameters */
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return HAL_ERROR ;
    while(!(hcan->Instance->SR & CAN_SR_RBS));
    HAL_CAN_GetRxMessage(hcan, RxMessage);
    return HAL_OK;
}

void HAL_CAN_GetRxMessage(CAN_HandleTypeDef *hcan, CanTxRxMsg* RxMessage)
{
    uint8_t i=0;
    /* Check the parameters */
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return ;
    if(0 == (hcan->Instance->SR & CAN_SR_RBS) ) return;  // receive fifo not empty  
    /* Get the IDE */
    RxMessage->IDE = (uint8_t)(0x80 & hcan->Instance->DF.DATABUF[0])>>7;
    /* Get the RTR */
    RxMessage->RTR = (uint8_t)(0x40 & hcan->Instance->DF.DATABUF[0])>>6;
    /* Get the DLC */
    RxMessage->DLC = (uint8_t)0x0F & hcan->Instance->DF.DATABUF[0];
    if (RxMessage->IDE == CAN_Id_Standard)
    {
        RxMessage->StdId = (uint32_t)(( hcan->Instance->DF.DATABUF[1]<<8) |  hcan->Instance->DF.DATABUF[2])>>5;;
        for(i=0; i<RxMessage->DLC; i++)  
        {
            RxMessage->Data[i] = hcan->Instance->DF.DATABUF[3+i];       
        }
    }
    else
    {
        RxMessage->ExtId = (uint32_t)(( hcan->Instance->DF.DATABUF[1]<<24) | ( hcan->Instance->DF.DATABUF[2]<<16) | ( hcan->Instance->DF.DATABUF[3]<<8) | (hcan->Instance->DF.DATABUF[4] ))>>3;;
        for(i=0; i<RxMessage->DLC; i++)  
        {
            RxMessage->Data[i] = hcan->Instance->DF.DATABUF[5+i];       
        }
    }
    /* Release the FIFO */
    hcan->Instance->CMR |= CAN_CMR_RRB; //Release Receive Buffer
}

/**
  * @brief  Initializes the CAN peripheral according to the specified
  *         parameters in the CAN_FilterInitStruct.
  * @param  CANx:   where x can be 1 or 2 to to select the CAN peripheral.
            CAN_FilterInitStruct: pointer to a CAN_FilterInitTypeDef
  *                               structure that contains the configuration 
  *                               information.
  * @retval None.
  */

/*********************************************************************************
* Function    : HAL_CAN_ConfigFilter
* Description :	Initializes the CAN peripheral according to the specified  parameters in the CAN_FilterInitStruct.
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Input       : CAN_FilterInitStruct : pointer to a CAN_FilterInitTypeDef structure that contains the configuration 
*                                       information.
* Output      : 
* Author      : CWT                         Data : 2020
**********************************************************************************/
void HAL_CAN_ConfigFilter(CAN_HandleTypeDef *hcan,CAN_FilterInitTypeDef* CAN_FilterInitStruct)
{
    HAL_CAN_OperatingModeRequest(hcan,CAN_OperatingMode_Initialization);//enter CAN_OperatingMode_Initialization
    /* Filter Mode */
    if (CAN_FilterInitStruct->CAN_FilterMode ==CAN_FilterMode_Dual) /*Dual mode*/
    {
        hcan->Instance->MOD &= ~CAN_MOD_AFM;
        /*Dual mode ACR set*/    
        hcan->Instance->DF.FILTER.ACR[0] = (CAN_FilterInitStruct->CAN_FilterId1&0x1FE00000)>>21;	/*Dual mode ACR0=ID28...ID21 of ID1*/
        hcan->Instance->DF.FILTER.ACR[1] = (CAN_FilterInitStruct->CAN_FilterId1&0x1FE000)>>13; 		/*Dual mode ACR0=ID20...ID13 of ID1*/
        hcan->Instance->DF.FILTER.ACR[2] = (CAN_FilterInitStruct->CAN_FilterId2&0x1FE00000)>>21;  /*Dual mode ACR0=ID28...ID21 of ID2*/
        hcan->Instance->DF.FILTER.ACR[3] = (CAN_FilterInitStruct->CAN_FilterId2&0x1FE000)>>13;     /*Dual mode ACR0=ID20...ID13 of ID2*/
        /*Dual mode AMR set*/   
        hcan->Instance->DF.FILTER.AMR[0] = (CAN_FilterInitStruct->CAN_FilterMaskId1)>>24; 
        hcan->Instance->DF.FILTER.AMR[1] = (CAN_FilterInitStruct->CAN_FilterMaskId1&0xFF0000)>>16; 
        hcan->Instance->DF.FILTER.AMR[2] = (CAN_FilterInitStruct->CAN_FilterMaskId2)>>24; 
        hcan->Instance->DF.FILTER.AMR[3] = (CAN_FilterInitStruct->CAN_FilterMaskId2&0xFF0000)>>16; 
    }
    else /*Single mode*/
    {
        hcan->Instance->MOD |= CAN_MOD_AFM;
        /*Single mode ACR set*/    
        hcan->Instance->DF.FILTER.ACR[0] = (CAN_FilterInitStruct->CAN_FilterId1&0x1FE00000)>>21;	/*Single mode ACR0=ID28...ID21*/
        hcan->Instance->DF.FILTER.ACR[1] = (CAN_FilterInitStruct->CAN_FilterId1&0x1FE000)>>13; 		/*Single mode ACR1=ID20...ID13*/
        hcan->Instance->DF.FILTER.ACR[2] = (CAN_FilterInitStruct->CAN_FilterId1&0x1FE0)>>5; 			/*Single mode ACR2=ID12...ID5*/
        hcan->Instance->DF.FILTER.ACR[3] = (CAN_FilterInitStruct->CAN_FilterId1&0x1F)<<3;  				/*Single mode ACR3=ID4...ID0*/
        /*Single mode AMR set*/   
        hcan->Instance->DF.FILTER.AMR[0] = (CAN_FilterInitStruct->CAN_FilterMaskId1)>>24; 
        hcan->Instance->DF.FILTER.AMR[1] = (CAN_FilterInitStruct->CAN_FilterMaskId1&0xFF0000)>>16; 
        hcan->Instance->DF.FILTER.AMR[2] = (CAN_FilterInitStruct->CAN_FilterMaskId1&0xFF00)>>8; 
        hcan->Instance->DF.FILTER.AMR[3] = (CAN_FilterInitStruct->CAN_FilterMaskId1&0xFF);   
    }

    HAL_CAN_OperatingModeRequest(hcan,CAN_OperatingMode_Normal);//enter CAN_OperatingMode_Initialization
}


/*********************************************************************************
* Function    : HAL_CAN_Sleep
* Description :	Enters the sleep mode.
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Output      : 
* Author      : CWT                         Data : 2020
**********************************************************************************/
HAL_StatusTypeDef HAL_CAN_Sleep(CAN_HandleTypeDef *hcan)
{
    HAL_StatusTypeDef status;
    /* Check the parameters */
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return HAL_ERROR;
    /* Request Sleep mode */
    hcan->Instance->MOD |= CAN_MOD_SM; //Enter Sleep Mode
   
    /* Sleep mode status */
    if ((hcan->Instance->MOD & CAN_MOD_SM) == CAN_MOD_SM)
    {
    /* Sleep mode entered */
        status= HAL_OK;
    }else
    {
        status=HAL_ERROR;
    }
    /* return sleep mode status */
    return status;
}

/*********************************************************************************
* Function    : HAL_CAN_WakeUp
* Description :	Wakes the CAN up.
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Output      : 
* Author      : CWT                         Data : 2020
**********************************************************************************/
HAL_StatusTypeDef HAL_CAN_WakeUp(CAN_HandleTypeDef *hcan)
{
    HAL_StatusTypeDef status;
    /* Check the parameters */
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return HAL_ERROR;
    /* sleep wake mode */
    hcan->Instance->MOD &=~ CAN_MOD_SM; //Enter Sleep Mode
   
    /* sleep wake status */
    if ((hcan->Instance->MOD & CAN_MOD_SM)== CAN_MOD_SM)
    {
        /* sleep wake not entered */
        status= HAL_ERROR;
    }else
    {
        status=HAL_OK;
    }
    /* return sleep mode status */
    return status;
}

/*********************************************************************************
* Function    : HAL_CAN_GetTransmitErrorCounter
* Description :	Returns the CANx Transmit Error Counter(TXERR).
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Output      : 
* Author      : CWT                         Data : 2020
**********************************************************************************/
int8_t HAL_CAN_GetTransmitErrorCounter(CAN_HandleTypeDef *hcan)
{
    uint8_t counter=0;
    /* Check the parameters */
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return -1;
    /* Get the  CANx Transmit Error Counter(TXERR) */
    counter = (uint8_t)(hcan->Instance->TXERR);
    /* Return the CANx Transmit Error Counter(TXERR) */
    return counter;
}


/*********************************************************************************
* Function    : HAL_CAN_GetReceiveErrorCounter
* Description :	Returns the  CANx Receive Error Counter(RXERR).
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Output      : 
* Author      : CWT                         Data : 2020
**********************************************************************************/
int8_t HAL_CAN_GetReceiveErrorCounter(CAN_HandleTypeDef *hcan)
{
    uint8_t counter=0;
    /* Check the parameters */
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return -1;
    /* Get the  CANx Receive Error Counter(RXERR) */
    counter = (uint8_t)(hcan->Instance->RXERR);
    /* Return the CANx Receive Error Counter(RXERR) */
    return counter;
}


/*********************************************************************************
* Function    : HAL_CAN_GetErrorCode
* Description :	Returns the CANx's  error code (ECC).
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Input       : Error_Type:This parameter can be one of the following flags: 
*														CAN_ErrorType_SegCode
*														CAN_ErrorType_Direction
*														CAN_ErrorType_ErrCode
* Output      : 
* Author      : CWT                         Data : 2020
**********************************************************************************/
int8_t HAL_CAN_GetErrorCode(CAN_HandleTypeDef *hcan,uint32_t Error_Type)
{
    uint8_t ErrorCode=0;
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return -1;
    if(!IS_CAN_ErrorType(Error_Type)) return -1;
    /* Get the CANx  Error SegCode */
    if(Error_Type==CAN_ErrorType_SegCode)
    {
        ErrorCode= (uint8_t)(hcan->Instance->ECC & CAN_ErrorType_SegCode);
    }
    /* Get the CANx  Error Direction */
    else if(Error_Type==CAN_ErrorType_Direction)
    {
        ErrorCode= (uint8_t)((hcan->Instance->ECC & CAN_ErrorType_Direction)>>5);
    }
    /* Get the CANx  Error ErrCode */
    else
    {
        ErrorCode= (uint8_t)((hcan->Instance->ECC & CAN_ErrorType_ErrCode)>>6);
    }
    return ErrorCode;
}

/*********************************************************************************
* Function    : HAL_CAN_GetErrorAlarmCounter
* Description :	Returns the  CANx Error  Alarm Counter(EWLR).
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Output      : 
* Author      : CWT                         Data : 2020
**********************************************************************************/
int8_t HAL_CAN_GetErrorAlarmCounter(CAN_HandleTypeDef *hcan)
{
    uint8_t counter=0;
    /* Check the parameters */
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return -1;
    /* Get the  CANx Error Alarm Counter(EWLR) */
    counter = (uint8_t)(hcan->Instance->EWLR);
    /* Return the CANx Error Alarm Counter(EWLR) */
    return counter;
}

/*********************************************************************************
* Function    : HAL_CAN_GetArbitrationErrorPosition
* Description :	Returns the  CANx Arbitration Error Position(ALC).
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Output      : 
* Author      : CWT                         Data : 2020
**********************************************************************************/
int8_t HAL_CAN_GetArbitrationErrorPosition(CAN_HandleTypeDef *hcan)
{
    uint8_t position=0;
    /* Check the parameters */
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return -1;
    /* Get the  CANx Arbitration Error Counter(ALC) */
    position = (uint8_t)((hcan->Instance->ALC)+1);
    /* Return the CANx Arbitration Error Counter(ALC) */
    return position;
}


/*********************************************************************************
* Function    : HAL_CAN_GetReceiveFiFoCounter
* Description :	Returns the  CANx Receive FiFo Counter(RMC).
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Output      : 
* Author      : CWT                         Data : 2020
**********************************************************************************/
int8_t HAL_CAN_GetReceiveFiFoCounter(CAN_HandleTypeDef *hcan)
{
    uint8_t counter=0;
    /* Check the parameters */
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return -1;
    /* Get the  CANx Receive FiFo Counter(RMC) */
    counter = (uint8_t)(hcan->Instance->RMC);
    /* Return the CANx Receive FiFo Counter(RMC) */
    return counter;
}


/*********************************************************************************
* Function    : HAL_CAN_GetReceiveFiFoAddr
* Description :	 Returns the  CANx Receive FiFo start address(RBSA).
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Output      : 
* Author      : CWT                         Data : 2020
**********************************************************************************/
int8_t HAL_CAN_GetReceiveFiFoAddr(CAN_HandleTypeDef *hcan)
{
    uint8_t addr=0;
    /* Check the parameters */
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return -1;
    /* Get the  CANx Receive FiFo start address(RBSA) */
    addr = (uint8_t)(hcan->Instance->RBSA);
    /* Return the CANx Receive FiFo start address(RBSA) */
    return addr;
}


/*********************************************************************************
* Function    : HAL_CAN_ReleaseReceiveFIFO
* Description :	Releases the Receive FIFO.
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Output      : 
* Author      : CWT                         Data : 2020
**********************************************************************************/
void HAL_CAN_ReleaseReceiveFIFO(CAN_HandleTypeDef *hcan)
{
    /* Check the parameters */
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return;
    /* Releases the Receive FIFO. */
    hcan->Instance->CMR|=CAN_CMR_RRB;	
}


/*********************************************************************************
* Function    : HAL_CAN_ClearOverload
* Description : Clear Overload
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Output      : 
* Author      : CWT                         Data : 2020
**********************************************************************************/
void HAL_CAN_ClearOverload(CAN_HandleTypeDef *hcan)
{
    /* Check the parameters */
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return;
    /* Clear Overload. */
    hcan->Instance->CMR|=CAN_CMR_CDO;	
}


/*********************************************************************************
* Function    : HAL_CAN_SlefReceive
* Description : Slef Receive
* Input       : hcan : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Output      : 
* Author      : CWT                         Data : 2020
**********************************************************************************/
void HAL_CAN_SelfReceive(CAN_HandleTypeDef *hcan)
{
    /* Check the parameters */
    if(!IS_CAN_ALL_PERIPH(hcan->Instance)) return;
    /* Slef Receive. */
    hcan->Instance->CMR|=CAN_CMR_SRR;	
    while((hcan->Instance->SR & CAN_SR_TCS)==0x00); //wait for send ok	
}

/*********************************************************************************
* Function    : HAL_CAN_IRQHandler
* Description : This function handles CAN interrupt request.
* Input       : hdma : pointer to a CAN_HandleTypeDef structure that contains
*                      the configuration information for CAN module
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020
**********************************************************************************/
void HAL_CAN_IRQHandler(CAN_HandleTypeDef *hcan)
{
    volatile uint32_t lu32_IR;
    lu32_IR = hcan->Instance->IR;//read clear 

    if(lu32_IR & CAN_IR_RI) //RI
    {
        /* CAN ReceiveIT complete callback */ 
        HAL_CAN_GetRxMessage(hcan, hcan->RxMessage);  
        hcan->CAN_ReceiveIT_Callback(hcan);  
    }
    if(lu32_IR & CAN_IR_TI) //TI
    {
        /* CAN TransmitIT complete callback */ 
        hcan->CAN_TransmitIT_Callback(hcan);  
    }
}