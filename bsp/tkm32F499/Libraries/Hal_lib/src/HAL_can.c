/**
******************************************************************************
* @file  HAL_can.c
* @author  IC Applications Department
* @version  V0.8
* @date  2019_08_02
* @brief  This file provides all the CAN firmware functions.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, HOLOCENE SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2016 HOLOCENE</center></h2>
*/

/* Includes ------------------------------------------------------------------*/
#include "HAL_can.h"
#include "HAL_rcc.h"

/**
* @brief: Deinitialinzes the CAN registers to their default reset values
* @retval: None
*/
void CAN_DeInit(CAN_TypeDef* CANx)
{
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    switch (*(uint32_t*)&CANx)
    {
        case CAN1_BASE:
            /* Enable CAN1 reset state */
            RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN1, ENABLE);
            /* Release CAN1 from reset state */
            RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN1, DISABLE);
            break;
                case CAN2_BASE:
            /* Enable CAN1 reset state */
            RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN2, ENABLE);
            /* Release CAN1 from reset state */
            RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN2, DISABLE);
            break;
        default:
            break;
    }

}

/**
* @brief  Initializes the CAN peripheral according to the specified
*   parameters in the CAN_InitStruct.
* @param CANx: where x can be 1 to select the CAN peripheral.
* @param CAN_InitStruct: pointer to a CAN_InitTypeDef structure that
*   contains the configuration information for the CAN peripheral.
* @retval : Constant indicates initialization succeed which will be
*   CANINITFAILED or CANINITOK.
*/
uint8_t CAN_Init(CAN_TypeDef* CANx, CAN_Basic_InitTypeDef* CAN_Basic_InitStruct)
{
    uint8_t InitStatus = CANINITFAILED;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(CAN_Basic_InitStruct->SJW));
    assert_param(IS_FUNCTIONAL_STATE(CAN_Basic_InitStruct->BRP));
    assert_param(IS_FUNCTIONAL_STATE(CAN_Basic_InitStruct->SAM));
    assert_param(IS_FUNCTIONAL_STATE(CAN_Basic_InitStruct->TESG2));
    assert_param(IS_FUNCTIONAL_STATE(CAN_Basic_InitStruct->TESG1));

    CANx->BTR0 = ((uint32_t)(CAN_Basic_InitStruct->SJW) << 6) | ((uint32_t)(CAN_Basic_InitStruct->BRP));
    CANx->BTR1 = ((uint32_t)(CAN_Basic_InitStruct->SAM) << 7) | ((uint32_t)(CAN_Basic_InitStruct->TESG2) << 4) | \
                 ((uint32_t)(CAN_Basic_InitStruct->TESG1));
    if(CAN_Basic_InitStruct->GTS == ENABLE)
    {
        CANx->CMR |= (uint32_t)CAN_SleepMode;
    }
    else
    {
        CANx->CMR &= ~(uint32_t)CAN_SleepMode;
    }

    CANx->CDR |= ((CAN_Basic_InitStruct->CBP) << 6) | ((CAN_Basic_InitStruct->RXINTEN) << 5) | \
                 ((CAN_Basic_InitStruct->CLOSE_OPEN_CLK) << 3) | (CAN_Basic_InitStruct->CDCLK);

    InitStatus = CANINITOK;
    return InitStatus;
}

/**
* @brief  Configures the CAN_Basic reception filter according to the specified
*         parameters in the CAN_Basic_FilterInitStruct.
* @param  CAN_Basic_FilterInitStruct: pointer to a CAN_Basic_FilterInitTypeDef structure that
*         contains the configuration information.
* @retval None
*/
void CAN_FilterInit(CAN_TypeDef* CANx, CAN_Basic_FilterInitTypeDef* CAN_Basic_FilterInitStruct)
{
    /* Filter Mode */
    CANx->ACR = CAN_Basic_FilterInitStruct->CAN_FilterId;
    CANx->AMR = CAN_Basic_FilterInitStruct->CAN_FilterMaskId;
}


/**
* @brief  Fills each CAN_Basic_InitStruct member with its default value.
* @param CAN_Basic_InitStruct : pointer to a CAN_Basic_InitTypeDef structure
*   which will be initialized.
* @retval : None
*/
void CAN_StructInit(CAN_Basic_InitTypeDef* CAN_Basic_InitStruct)
{
    /*--------------- Reset CAN_Basic init structure parameters values -----------------*/


    /* initialize the BRP member(where can be set with (0..63))*/
    CAN_Basic_InitStruct->BRP = 0x0;
    /* initialize the SJW member(where can be set with (0..3)) */
    CAN_Basic_InitStruct->SJW = 0x0;
    /* Initialize the TESG1 member(where can be set with (0..15)) */
    CAN_Basic_InitStruct->TESG1 = 0x0;
    /* Initialize the TESG2 member(where can be set with(0..7)) */
    CAN_Basic_InitStruct->TESG2 = 0x0;
    /* Initialize the SAM member(where can be set (SET or RESET)) */
    CAN_Basic_InitStruct->SAM = RESET;
    /* Initialize the GTS member to Sleep Mode(where can be set (ENABLE or DISABLE)) */
    CAN_Basic_InitStruct->GTS = DISABLE;
    /* Initialize the external pin CLKOUT frequence */
    CAN_Basic_InitStruct->CDCLK = 0x0;
    /* Initialize the external clk is open or close */
    CAN_Basic_InitStruct->CLOSE_OPEN_CLK = 0x0;
    /* Initialize the TX1 pin work as rx interrupt output */
    CAN_Basic_InitStruct->RXINTEN = 0x0;
    /* Initialize the CBP of CDR register */
    CAN_Basic_InitStruct->CBP = 0x0;
}

/**
* @brief  Enables or disables the specified CAN interrupts.
* @param CANx: where x can be 1 to select the CAN peripheral.
* @param CAN_IT: specifies the CAN interrupt sources to be enabled or
*   disabled.
*   This parameter can be: CAN_IT_OIE, CAN_IT_EIE, CAN_IT_TIE,
*   CAN_IT_RIE,.
* @param Newstate: new state of the CAN interrupts.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None.
*/
void CAN_ITConfig(CAN_TypeDef* CANx, uint32_t CAN_IT, FunctionalState Newstate)
{
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_ITConfig(CAN_IT));
    assert_param(IS_FUNCTIONAL_STATE(Newstate));
    if (Newstate != DISABLE)
    {
        /* Enable the selected CAN interrupt */
        CANx->CR |= CAN_IT;
    }
    else
    {
        /* Disable the selected CAN interrupt */
        CANx->CR &= ~CAN_IT;
    }
}


/**
* @brief  Initiates and transmits a CAN frame message.
* @param CANx: where x can be 1 to select the CAN peripheral.
* @param  TxMessage: pointer to a structure which contains CAN Id, CAN DLC and CAN data.
* @retval CANTXOK if the CAN driver transmits the message
*/
uint8_t CAN_Transmit(CAN_TypeDef* CANx, CanBasicTxMsg* BasicTxMessage)
{
    /* TXOK and TME bits */
    uint8_t state = 0;
    /* Check the parameters */
    assert_param(IS_CAN_RTR(BasicTxMessage->RTR));
    assert_param(IS_CAN_DLC(BasicTxMessage->DLC));

    CANx->TXID0 = (BasicTxMessage->IDH);
    CANx->TXID1 = (BasicTxMessage->IDL << 5) | (BasicTxMessage->RTR << 4) | (BasicTxMessage->DLC);
    if((FunctionalState)(BasicTxMessage->RTR) != ENABLE)
    {
        CANx->TXDR0 = BasicTxMessage->Data[0];
        CANx->TXDR1 = BasicTxMessage->Data[1];
        CANx->TXDR2 = BasicTxMessage->Data[2];
        CANx->TXDR3 = BasicTxMessage->Data[3];
        CANx->TXDR4 = BasicTxMessage->Data[4];
        CANx->TXDR5 = BasicTxMessage->Data[5];
        CANx->TXDR6 = BasicTxMessage->Data[6];
        CANx->TXDR7 = BasicTxMessage->Data[7];
    }

    CANx->CMR = CAN_CMR_TR;

    return state;
}

/**
* @brief  Cancels a transmit request.
* @param CANx: where x can be 1 to select the CAN peripheral.

* @retval None
*/
void CAN_CancelTransmit(CAN_TypeDef* CANx)
{
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_TRANSMITMAILBOX(Mailbox));
    /* abort transmission */
    CANx->CMR = CAN_AT;

}

/**
* @brief  Releases the specified receive FIFO.
* @param CANx: where x can be 1 to select the CAN peripheral.
* @retval None
*/
void CAN_FIFORelease(CAN_TypeDef* CANx)
{
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    /* Release FIFO */
    CANx->CMR |= (uint32_t)CAN_RRB;

}

/**
* @brief  Receives a correct CAN frame.
* @param CANx: where x can be 1 to select the CAN peripheral.
* @param  RxMessage: pointer to a structure receive frame which contains CAN Id,
*         CAN DLC, CAN data and FMI number.
* @retval None
*/
void CAN_Receive(CAN_TypeDef* CANx, CanBasicRxMsg* BasicRxMessage)
{
    uint16_t tempid;
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_FIFO(FIFONumber));
    BasicRxMessage->RTR = (uint8_t)((CANx->RXID1) >> 4) & 0x1;
    BasicRxMessage->DLC = (uint8_t)((CANx->RXID1) & 0xf);
    tempid = (uint16_t)(((CANx->RXID1) & 0xe0) >> 5);
    tempid |= (uint16_t)(CANx->RXID0 << 3);
    BasicRxMessage->ID = tempid;
    BasicRxMessage->Data[0] = CANx->RXDR0;
    BasicRxMessage->Data[1] = CANx->RXDR1;
    BasicRxMessage->Data[2] = CANx->RXDR2;
    BasicRxMessage->Data[3] = CANx->RXDR3;
    BasicRxMessage->Data[4] = CANx->RXDR4;
    BasicRxMessage->Data[5] = CANx->RXDR5;
    BasicRxMessage->Data[6] = CANx->RXDR6;
    BasicRxMessage->Data[7] = CANx->RXDR7;
    CAN_FIFORelease( CANx);
}

/**
* @brief: Select the Sleep mode or not in Basic workmode
* @param: NewState to go into the Sleep mode or go out
* @retval: None
*/
uint8_t CAN_Sleep(CAN_TypeDef* CANx)
{
    uint8_t sleepstatus = CANSLEEPFAILED;

    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    CANx->CMR |= CAN_SleepMode;
    if((CANx->CMR & 0x10) == CAN_SleepMode)
    {
        sleepstatus =  CANSLEEPOK;
    }
    /* At this step, sleep mode status */
    return (uint8_t)sleepstatus;

}

/**
* @brief  Wakes the CAN up.
* @param CANx: where x can be 1 to select the CAN peripheral.
* @retval : CANWAKEUPOK if sleep mode left, CANWAKEUPFAILED in an other
*   case.
*/
uint8_t CAN_WakeUp(CAN_TypeDef* CANx)
{
    uint8_t wakeupstatus = CANWAKEUPFAILED;

    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    /* Wake up request */
    CANx->CMR &= ~CAN_SleepMode;

    /* Sleep mode status */
    if((CANx->CMR & 0x01) == 0)
    {
        /* Sleep mode exited */
        wakeupstatus = CANWAKEUPOK;
    }
    /* At this step, sleep mode status */
    return (uint8_t)wakeupstatus;
}


/**
* @brief  Checks whether the specified CAN flag is set or not.
* @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
* @param  CAN_FLAG: specifies the flag to check.
*          This parameter can be one of the following values:
*            @arg CAN_STATUS_RBS: Receive buffer status
*            @arg CAN_STATUS_DOS: Data overflow status
*            @arg CAN_STATUS_TBS: Transmit buffer status
*            @arg CAN_STATUS_TCS: Transmit complete status
*            @arg CAN_STATUS_RS: Receiving status
*            @arg CAN_STATUS_TS: Transmiting status
*            @arg CAN_STATUS_ES: Error status
*            @arg CAN_STATUS_BS: bus status, close or open
* @retval The new state of CAN_FLAG (SET or RESET).
*/
FlagStatus CAN_GetFlagStatus(CAN_TypeDef* CANx, uint32_t CAN_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_GET_FLAG(CAN_FLAG));


    if((CANx->SR & CAN_FLAG) == CAN_FLAG)
    {
        /* CAN_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* CAN_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the CAN_FLAG status */
    return bitstatus;
}

/**
* @brief  Checks whether the specified CAN interrupt has occurred or not.
* @param CANx: where x can be 1 to select the CAN peripheral.
* @param  CAN_IT: specifies the CAN interrupt source to check.
*          This parameter can be one of the following values:
*            @arg CAN_IT_RI: Receive FIFO not empty Interrupt
*            @arg CAN_IT_TI: Transmit Interrupt
*            @arg CAN_IT_EI: ERROR Interrupt
*            @arg CAN_IT_DOI: Data voerflow Interrupt
*            @arg CAN_IT_WUI: Wakeup Interrupt
*            @arg CAN_IT_ALL: use it can enble all Interrupt
* @retval The current state of CAN_IT (SET or RESET).
*/
ITStatus CAN_GetITStatus(CAN_TypeDef* CANx, uint32_t CAN_IT)
{
    ITStatus itstatus = RESET;

    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_IT(CAN_IT));

    /* check the interrupt enable bit */
    if((CANx->IR & CAN_IT) != CAN_IT)
    {
        itstatus = RESET;
    }
    else
    {
        itstatus = SET;
    }

    return itstatus;
}


/**
* @brief: Select the can work as peli mode or basic mode
* @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
* @param  CAN_MODE: specifies the work mode:CAN_BASICMode,CAN_PELIMode
* @retval: None
*/
void CAN_Mode_Cmd(CAN_TypeDef* CANx, uint32_t CAN_MODE)
{
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    CANx->CDR |= CAN_MODE;
}


/**
* @brief: Select the Reset mode or not
* @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
* @param: NewState to go into the Reset mode or go out
* @retval: None
*/
void CAN_ResetMode_Cmd(CAN_TypeDef* CANx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    if(NewState == ENABLE)
    {
        CANx->CR |= CAN_ResetMode;
    }
    else
    {
        CANx->CR &= ~CAN_ResetMode;
    }
}

/**
* @brief  Clear the data overflow.
* @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
* @retval None
*/
void CAN_ClearDataOverflow(CAN_TypeDef* CANx)
{
    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    CANx->CMR |= (uint32_t)CAN_CDO;

}

/**
* @brief  Clears the CAN's IT pending.
* @param  CANx: where x can be 1 or 2 to to select the CAN peripheral.
* @retval None
*/
void CAN_ClearITPendingBit(CAN_TypeDef* CANx)
{
    uint32_t temp = 0;
    temp = temp;
    temp = CANx->IR; //read this register clear all interrupt

}



/**
* @brief: Select the Sleep mode or not in Peli workmode
* @param: NewState to go into the Sleep mode or go out
* @retval: None
*/
void CAN_Peli_SleepMode_Cmd(CAN_TypeDef* CANx, FunctionalState NewState)
{
        switch (*(uint32_t*)&CANx)
    {
        case CAN1_BASE:
            if(NewState == ENABLE)
                            CAN1_PELI->MOD |= CAN_SleepMode;
                        else
                            CAN1_PELI->MOD &= ~CAN_SleepMode;
            break;
                case CAN2_BASE:
            if(NewState == ENABLE)
                            CAN2_PELI->MOD |= CAN_SleepMode;
                        else
                            CAN2_PELI->MOD &= ~CAN_SleepMode;
            break;
        default:
            break;
    }
}


/**
* @brief  Fills each CAN1_PELI_InitStruct member with its default value.
* @param CAN_Peli_InitStruct : pointer to a CAN_Peli_InitTypeDef structure
*   which will be initialized.
* @retval : None
*/
void CAN_Peli_StructInit(CAN_Peli_InitTypeDef* CAN_Peli_InitStruct)
{
    /*--------------- Reset CAN_Peli init structure parameters values -----------------*/

    /* initialize the BRP member(where can be set with (0..63))*/
    CAN_Peli_InitStruct->BRP = 0x0;
    /* initialize the SJW member(where can be set with (0..3)) */
    CAN_Peli_InitStruct->SJW = 0x0;
    /* Initialize the TESG1 member(where can be set with (0..15)) */
    CAN_Peli_InitStruct->TESG1 = 0x0;
    /* Initialize the TESG2 member(where can be set with(0..7)) */
    CAN_Peli_InitStruct->TESG2 = 0x0;
    /* Initialize the SAM member(where can be set (SET or RESET)) */
    CAN_Peli_InitStruct->SAM = RESET;
    /* Initialize the LOM member*/
    CAN_Peli_InitStruct->LOM = DISABLE;
    /* Initialize the STM member*/
    CAN_Peli_InitStruct->STM = DISABLE;
    /* Initialize the SM member*/
    CAN_Peli_InitStruct->SM = DISABLE;
    CAN_Peli_InitStruct->SRR = DISABLE;
    CAN_Peli_InitStruct->EWLR = 0x96;
}

/**
* @brief  Initializes the CAN_Peli peripheral according to the specified
*         parameters in the CAN_Peli_InitStruct.
* @param  CAN_Basic_InitStruct: pointer to a CAN_Peli_InitTypeDef structure that contains
*         the configuration information for the CAN peripheral in the peli workmode.
* @retval None
*/
void CAN_Peli_Init(CAN_TypeDef* CANx, CAN_Peli_InitTypeDef* CAN_Peli_InitStruct)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->SJW));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->BRP));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->SAM));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->TESG2));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->TESG1));

        switch (*(uint32_t*)&CANx)
            {
                    case CAN1_BASE:
                            CAN1_PELI->BTR0 = ((uint32_t)CAN_Peli_InitStruct->SJW << 6) | ((uint32_t)CAN_Peli_InitStruct->BRP);
                            CAN1_PELI->BTR1 = ((uint32_t)CAN_Peli_InitStruct->SAM << 7) | ((uint32_t)CAN_Peli_InitStruct->TESG2 << 4) | \
                                                                ((uint32_t)CAN_Peli_InitStruct->TESG1);
                            if(CAN_Peli_InitStruct->LOM == ENABLE)
                                    CAN1_PELI->MOD |= (uint32_t)CAN_ListenOnlyMode;
                            else
                                    CAN1_PELI->MOD &= ~(uint32_t)CAN_ListenOnlyMode;
                            if(CAN_Peli_InitStruct->STM == ENABLE)
                                    CAN1_PELI->MOD |= (uint32_t)CAN_SeftTestMode;
                            else
                                    CAN1_PELI->MOD &= ~(uint32_t)CAN_SeftTestMode;
                            if(CAN_Peli_InitStruct->SM == ENABLE)
                                    CAN1_PELI->MOD |= (uint32_t)CAN_SleepMode;
                            else
                                    CAN1_PELI->MOD &= ~(uint32_t)CAN_SleepMode;
                            CAN1_PELI->EWLR = (uint32_t)CAN_Peli_InitStruct->EWLR;
                            break;
                    case CAN2_BASE:
                            CAN2_PELI->BTR0 = ((uint32_t)CAN_Peli_InitStruct->SJW << 6) | ((uint32_t)CAN_Peli_InitStruct->BRP);
                            CAN2_PELI->BTR1 = ((uint32_t)CAN_Peli_InitStruct->SAM << 7) | ((uint32_t)CAN_Peli_InitStruct->TESG2 << 4) | \
                                                                ((uint32_t)CAN_Peli_InitStruct->TESG1);
                            if(CAN_Peli_InitStruct->LOM == ENABLE)
                                    CAN2_PELI->MOD |= (uint32_t)CAN_ListenOnlyMode;
                            else
                                    CAN2_PELI->MOD &= ~(uint32_t)CAN_ListenOnlyMode;
                            if(CAN_Peli_InitStruct->STM == ENABLE)
                                    CAN2_PELI->MOD |= (uint32_t)CAN_SeftTestMode;
                            else
                                    CAN2_PELI->MOD &= ~(uint32_t)CAN_SeftTestMode;
                            if(CAN_Peli_InitStruct->SM == ENABLE)
                                    CAN2_PELI->MOD |= (uint32_t)CAN_SleepMode;
                            else
                                    CAN2_PELI->MOD &= ~(uint32_t)CAN_SleepMode;
                            CAN2_PELI->EWLR = (uint32_t)CAN_Peli_InitStruct->EWLR;
                            break;
                    default:
                            break;
            }
}



/**
* @brief  Configures the CAN_Peli reception filter according to the specified
*         parameters in the CAN_Peli_FilterInitStruct.
* @param  CAN_Peli_FilterInitStruct: pointer to a CAN_Peli_FilterInitTypeDef structure that
*         contains the configuration information.
* @retval None
*/
void CAN_Peli_FilterInit(CAN_TypeDef* CANx, CAN_Peli_FilterInitTypeDef* CAN_Peli_FilterInitStruct)
{
        switch (*(uint32_t*)&CANx)
            {
                    case CAN1_BASE:
                            if(CAN_Peli_FilterInitStruct->AFM == CAN_FilterMode_Singal)
                                CAN1_PELI->MOD |= (uint32_t)CAN_FilterMode_Singal;
                            else
                                CAN1_PELI->MOD &= (uint32_t)CAN_FilterMode_Double;

                                CAN1_PELI->FF = CAN_Peli_FilterInitStruct->CAN_FilterId0;
                                CAN1_PELI->ID0 = CAN_Peli_FilterInitStruct->CAN_FilterId1;
                                CAN1_PELI->ID1 = CAN_Peli_FilterInitStruct->CAN_FilterId2;
                                CAN1_PELI->DATA0 = CAN_Peli_FilterInitStruct->CAN_FilterId3;

                                CAN1_PELI->DATA1 = CAN_Peli_FilterInitStruct->CAN_FilterMaskId0;
                                CAN1_PELI->DATA2 = CAN_Peli_FilterInitStruct->CAN_FilterMaskId1;
                                CAN1_PELI->DATA3 = CAN_Peli_FilterInitStruct->CAN_FilterMaskId2;
                                CAN1_PELI->DATA4 = CAN_Peli_FilterInitStruct->CAN_FilterMaskId3;
                            break;
                    case CAN2_BASE:
                            if(CAN_Peli_FilterInitStruct->AFM == CAN_FilterMode_Singal)
                                CAN2_PELI->MOD |= (uint32_t)CAN_FilterMode_Singal;
                            else
                                CAN2_PELI->MOD &= (uint32_t)CAN_FilterMode_Double;

                                CAN2_PELI->FF = CAN_Peli_FilterInitStruct->CAN_FilterId0;
                                CAN2_PELI->ID0 = CAN_Peli_FilterInitStruct->CAN_FilterId1;
                                CAN2_PELI->ID1 = CAN_Peli_FilterInitStruct->CAN_FilterId2;
                                CAN2_PELI->DATA0 = CAN_Peli_FilterInitStruct->CAN_FilterId3;

                                CAN2_PELI->DATA1 = CAN_Peli_FilterInitStruct->CAN_FilterMaskId0;
                                CAN2_PELI->DATA2 = CAN_Peli_FilterInitStruct->CAN_FilterMaskId1;
                                CAN2_PELI->DATA3 = CAN_Peli_FilterInitStruct->CAN_FilterMaskId2;
                                CAN2_PELI->DATA4 = CAN_Peli_FilterInitStruct->CAN_FilterMaskId3;
                            break;
                    default:
                            break;
            }

}

/**
* @brief  Fills each CAN_Peli_FilterInitStruct member with its default value.
* @param  CAN_Peli_FilterInitStruct: pointer to a CAN_InitTypeDef structure which ill be initialized.
* @retval None
*/
void CAN_Peli_FilterStructInit(CAN_Peli_FilterInitTypeDef* CAN_Peli_FilterInitStruct)
{
    CAN_Peli_FilterInitStruct->CAN_FilterId0 = 0;
    CAN_Peli_FilterInitStruct->CAN_FilterId1 = 0;
    CAN_Peli_FilterInitStruct->CAN_FilterId2 = 0;
    CAN_Peli_FilterInitStruct->CAN_FilterId3 = 0;

    CAN_Peli_FilterInitStruct->CAN_FilterMaskId0 = 0;
    CAN_Peli_FilterInitStruct->CAN_FilterMaskId1 = 0;
    CAN_Peli_FilterInitStruct->CAN_FilterMaskId2 = 0;
    CAN_Peli_FilterInitStruct->CAN_FilterMaskId3 = 0;
}


/**
* @brief  Initiates and transmits a CAN frame message.
* @param  TxMessage: pointer to a structure which contains CAN Id, CAN DLC and CAN data.
* @retval None
*/
void CAN_Peli_Transmit(CAN_TypeDef* CANx, CanPeliTxMsg* PeliTxMessage)
{
    /* Check the parameters */
    assert_param(IS_CAN_RTR(PeliTxMessage->RTR));
    assert_param(IS_CAN_DLC(PeliTxMessage->DLC));
        switch (*(uint32_t*)&CANx)
            {
                    case CAN1_BASE:
                            CAN1_PELI->FF = (PeliTxMessage->FF << 7) | (PeliTxMessage->RTR << 6) | (PeliTxMessage->DLC);
                            if(((FunctionalState)PeliTxMessage->FF) != ENABLE)
                                {
                                        CAN1_PELI->ID0 = (PeliTxMessage->IDHH);
                                        //    CAN1_PELI->ID1 = ((PeliTxMessage->IDHL)<<5);
                                        CAN1_PELI->ID1 = (PeliTxMessage->IDHL & 0xE0);
                                        if((FunctionalState)(PeliTxMessage->RTR) != ENABLE)
                                        {
                                                CAN1_PELI->DATA0 = PeliTxMessage->Data[0];
                                                CAN1_PELI->DATA1 = PeliTxMessage->Data[1];
                                                CAN1_PELI->DATA2 = PeliTxMessage->Data[2];
                                                CAN1_PELI->DATA3 = PeliTxMessage->Data[3];
                                                CAN1_PELI->DATA4 = PeliTxMessage->Data[4];
                                                CAN1_PELI->DATA5 = PeliTxMessage->Data[5];
                                                CAN1_PELI->DATA6 = PeliTxMessage->Data[6];
                                                CAN1_PELI->DATA7 = PeliTxMessage->Data[7];
                                        }
                                }
                            else
                                {
                                        CAN1_PELI->ID0 = PeliTxMessage->IDHH;
                                        CAN1_PELI->ID1 = PeliTxMessage->IDHL;
                                        CAN1_PELI->DATA0 = PeliTxMessage->IDLH;
                                        CAN1_PELI->DATA1 = PeliTxMessage->IDLL;
                                        if((FunctionalState)(PeliTxMessage->RTR) != ENABLE)
                                        {
                                                CAN1_PELI->DATA2 = PeliTxMessage->Data[0];
                                                CAN1_PELI->DATA3 = PeliTxMessage->Data[1];
                                                CAN1_PELI->DATA4 = PeliTxMessage->Data[2];
                                                CAN1_PELI->DATA5 = PeliTxMessage->Data[3];
                                                CAN1_PELI->DATA6 = PeliTxMessage->Data[4];
                                                CAN1_PELI->DATA7 = PeliTxMessage->Data[5];
                                                CAN1_PELI->DATA8 = PeliTxMessage->Data[6];
                                                CAN1_PELI->DATA9 = PeliTxMessage->Data[7];
                                        }
                                }
                            if(CAN1_PELI->MOD & CAN_MOD_STM)
                                {
                                        CANx->CMR = CAN_CMR_GTS | CAN_CMR_AT;
                                }
                            else
                                {
                                        CANx->CMR = CAN_TR | CAN_AT;
                                }
                            break;
                    case CAN2_BASE:
                            CAN2_PELI->FF = (PeliTxMessage->FF << 7) | (PeliTxMessage->RTR << 6) | (PeliTxMessage->DLC);
                            if(((FunctionalState)PeliTxMessage->FF) != ENABLE)
                                {
                                        CAN2_PELI->ID0 = (PeliTxMessage->IDHH);
                                        //    CAN2_PELI->ID1 = ((PeliTxMessage->IDHL)<<5);
                                        CAN2_PELI->ID1 = (PeliTxMessage->IDHL & 0xE0);
                                        if((FunctionalState)(PeliTxMessage->RTR) != ENABLE)
                                        {
                                                CAN2_PELI->DATA0 = PeliTxMessage->Data[0];
                                                CAN2_PELI->DATA1 = PeliTxMessage->Data[1];
                                                CAN2_PELI->DATA2 = PeliTxMessage->Data[2];
                                                CAN2_PELI->DATA3 = PeliTxMessage->Data[3];
                                                CAN2_PELI->DATA4 = PeliTxMessage->Data[4];
                                                CAN2_PELI->DATA5 = PeliTxMessage->Data[5];
                                                CAN2_PELI->DATA6 = PeliTxMessage->Data[6];
                                                CAN2_PELI->DATA7 = PeliTxMessage->Data[7];
                                        }
                                }
                            else
                                {
                                        CAN2_PELI->ID0 = PeliTxMessage->IDHH;
                                        CAN2_PELI->ID1 = PeliTxMessage->IDHL;
                                        CAN2_PELI->DATA0 = PeliTxMessage->IDLH;
                                        CAN2_PELI->DATA1 = PeliTxMessage->IDLL;
                                        if((FunctionalState)(PeliTxMessage->RTR) != ENABLE)
                                        {
                                                CAN2_PELI->DATA2 = PeliTxMessage->Data[0];
                                                CAN2_PELI->DATA3 = PeliTxMessage->Data[1];
                                                CAN2_PELI->DATA4 = PeliTxMessage->Data[2];
                                                CAN2_PELI->DATA5 = PeliTxMessage->Data[3];
                                                CAN2_PELI->DATA6 = PeliTxMessage->Data[4];
                                                CAN2_PELI->DATA7 = PeliTxMessage->Data[5];
                                                CAN2_PELI->DATA8 = PeliTxMessage->Data[6];
                                                CAN2_PELI->DATA9 = PeliTxMessage->Data[7];
                                        }
                                }
                            if(CAN2_PELI->MOD & CAN_MOD_STM)
                                {
                                        CANx->CMR = CAN_CMR_GTS | CAN_CMR_AT;
                                }
                            else
                                {
                                        CANx->CMR = CAN_TR | CAN_AT;
                                }
                            break;
                    default:
                            break;
            }
}



/**
* @brief  Initiates and transmits a CAN frame message.
* @param  TxMessage: pointer to a structure which contains CAN Id, CAN DLC and CAN data.
* @retval None
*/
void CAN_Peli_TransmitRepeat(CAN_TypeDef* CANx, CanPeliTxMsg* PeliTxMessage)
{
    /* Check the parameters */
    assert_param(IS_CAN_RTR(PeliTxMessage->RTR));
    assert_param(IS_CAN_DLC(PeliTxMessage->DLC));
        switch (*(uint32_t*)&CANx)
            {
                    case CAN1_BASE:
                            CAN1_PELI->FF = (PeliTxMessage->FF << 7) | (PeliTxMessage->RTR << 6) | (PeliTxMessage->DLC);
                            if(((FunctionalState)PeliTxMessage->FF) != ENABLE)
                                {
                                        CAN1_PELI->ID0 = (PeliTxMessage->IDHH);
                                        CAN1_PELI->ID1 = ((PeliTxMessage->IDHL) << 5);
                                        if((FunctionalState)(PeliTxMessage->RTR) != ENABLE)
                                        {
                                                CAN1_PELI->DATA0 = PeliTxMessage->Data[0];
                                                CAN1_PELI->DATA1 = PeliTxMessage->Data[1];
                                                CAN1_PELI->DATA2 = PeliTxMessage->Data[2];
                                                CAN1_PELI->DATA3 = PeliTxMessage->Data[3];
                                                CAN1_PELI->DATA4 = PeliTxMessage->Data[4];
                                                CAN1_PELI->DATA5 = PeliTxMessage->Data[5];
                                                CAN1_PELI->DATA6 = PeliTxMessage->Data[6];
                                                CAN1_PELI->DATA7 = PeliTxMessage->Data[7];
                                        }
                                }
                            else
                                {
                                        CAN1_PELI->ID0 = PeliTxMessage->IDHH;
                                        CAN1_PELI->ID1 = PeliTxMessage->IDHL;
                                        CAN1_PELI->DATA0 = PeliTxMessage->IDLH;
                                        CAN1_PELI->DATA1 = PeliTxMessage->IDLL;
                                        if((FunctionalState)(PeliTxMessage->RTR) != ENABLE)
                                        {
                                                CAN1_PELI->DATA2 = PeliTxMessage->Data[0];
                                                CAN1_PELI->DATA3 = PeliTxMessage->Data[1];
                                                CAN1_PELI->DATA4 = PeliTxMessage->Data[2];
                                                CAN1_PELI->DATA5 = PeliTxMessage->Data[3];
                                                CAN1_PELI->DATA6 = PeliTxMessage->Data[4];
                                                CAN1_PELI->DATA7 = PeliTxMessage->Data[5];
                                                CAN1_PELI->DATA8 = PeliTxMessage->Data[6];
                                                CAN1_PELI->DATA9 = PeliTxMessage->Data[7];
                                        }
                                }

                            if(CAN1_PELI->MOD & CAN_MOD_STM)
                                {
                                        CANx->CMR = CAN_CMR_GTS | CAN_CMR_AT;
                                }
                            else
                                {
                                        CANx->CMR = CAN_CMR_TR;
                                }
                            break;
                    case CAN2_BASE:
                            CAN2_PELI->FF = (PeliTxMessage->FF << 7) | (PeliTxMessage->RTR << 6) | (PeliTxMessage->DLC);
                            if(((FunctionalState)PeliTxMessage->FF) != ENABLE)
                                {
                                        CAN2_PELI->ID0 = (PeliTxMessage->IDHH);
                                        CAN2_PELI->ID1 = ((PeliTxMessage->IDHL) << 5);
                                        if((FunctionalState)(PeliTxMessage->RTR) != ENABLE)
                                        {
                                                CAN2_PELI->DATA0 = PeliTxMessage->Data[0];
                                                CAN2_PELI->DATA1 = PeliTxMessage->Data[1];
                                                CAN2_PELI->DATA2 = PeliTxMessage->Data[2];
                                                CAN2_PELI->DATA3 = PeliTxMessage->Data[3];
                                                CAN2_PELI->DATA4 = PeliTxMessage->Data[4];
                                                CAN2_PELI->DATA5 = PeliTxMessage->Data[5];
                                                CAN2_PELI->DATA6 = PeliTxMessage->Data[6];
                                                CAN2_PELI->DATA7 = PeliTxMessage->Data[7];
                                        }
                                }
                            else
                                {
                                        CAN2_PELI->ID0 = PeliTxMessage->IDHH;
                                        CAN2_PELI->ID1 = PeliTxMessage->IDHL;
                                        CAN2_PELI->DATA0 = PeliTxMessage->IDLH;
                                        CAN2_PELI->DATA1 = PeliTxMessage->IDLL;
                                        if((FunctionalState)(PeliTxMessage->RTR) != ENABLE)
                                        {
                                                CAN2_PELI->DATA2 = PeliTxMessage->Data[0];
                                                CAN2_PELI->DATA3 = PeliTxMessage->Data[1];
                                                CAN2_PELI->DATA4 = PeliTxMessage->Data[2];
                                                CAN2_PELI->DATA5 = PeliTxMessage->Data[3];
                                                CAN2_PELI->DATA6 = PeliTxMessage->Data[4];
                                                CAN2_PELI->DATA7 = PeliTxMessage->Data[5];
                                                CAN2_PELI->DATA8 = PeliTxMessage->Data[6];
                                                CAN2_PELI->DATA9 = PeliTxMessage->Data[7];
                                        }
                                }

                            if(CAN2_PELI->MOD & CAN_MOD_STM)
                                {
                                        CANx->CMR = CAN_CMR_GTS | CAN_CMR_AT;
                                }
                            else
                                {
                                        CANx->CMR = CAN_CMR_TR;
                                }
                            break;
                    default:
                            break;
            }

}

/** @defgroup CAN_Group3 CAN Frames Reception functions
*  @brief    CAN Frames Reception functions
*
@verbatim
===============================================================================
##### CAN Frames Reception functions #####
===============================================================================
[..] This section provides functions allowing to
(+) Receive a correct CAN frame.
(+) Release a specified receive FIFO
(+) Return the number of the pending received CAN frames.

@endverbatim
* @{
*/


/**
* @brief  Receives a correct CAN frame.
* @param  RxMessage: pointer to a structure receive frame which contains CAN Id,
*         CAN DLC, CAN data and FMI number.
* @retval None
*/
void CAN_Peli_Receive(CAN_TypeDef* CANx, CanPeliRxMsg* PeliRxMessage)
{
    uint32_t tempid;
        switch (*(uint32_t*)&CANx)
            {
                    case CAN1_BASE:
                            PeliRxMessage->FF = (CAN1_PELI->FF) >> 7;
                            PeliRxMessage->RTR = ((CAN1_PELI->FF) >> 6) & 0x1;
                            PeliRxMessage->DLC = (CAN1_PELI->FF) & 0xf;

                            if(((FunctionalState)PeliRxMessage->FF) != ENABLE)
                                {
                                        tempid = (uint32_t)(CAN1_PELI->ID1 >> 5);
                                        tempid |= (uint32_t)(CAN1_PELI->ID0 << 3);
                                        PeliRxMessage->ID = tempid;
                                        PeliRxMessage->Data[0] = CAN1_PELI->DATA0;
                                        PeliRxMessage->Data[1] = CAN1_PELI->DATA1;
                                        PeliRxMessage->Data[2] = CAN1_PELI->DATA2;
                                        PeliRxMessage->Data[3] = CAN1_PELI->DATA3;
                                        PeliRxMessage->Data[4] = CAN1_PELI->DATA4;
                                        PeliRxMessage->Data[5] = CAN1_PELI->DATA5;
                                        PeliRxMessage->Data[6] = CAN1_PELI->DATA6;
                                        PeliRxMessage->Data[7] = CAN1_PELI->DATA7;
                                }
                            else
                                {
                                        tempid = (uint32_t)((CAN1_PELI->DATA1 & 0xf8) >> 3);
                                        tempid |= (uint32_t)(CAN1_PELI->DATA0 << 5);
                                        tempid |= (uint32_t)(CAN1_PELI->ID1 << 13);
                                        tempid |= (uint32_t)(CAN1_PELI->ID0 << 21);
                                        PeliRxMessage->ID = tempid;
                                        PeliRxMessage->Data[0] = CAN1_PELI->DATA2;
                                        PeliRxMessage->Data[1] = CAN1_PELI->DATA3;
                                        PeliRxMessage->Data[2] = CAN1_PELI->DATA4;
                                        PeliRxMessage->Data[3] = CAN1_PELI->DATA5;
                                        PeliRxMessage->Data[4] = CAN1_PELI->DATA6;
                                        PeliRxMessage->Data[5] = CAN1_PELI->DATA7;
                                        PeliRxMessage->Data[6] = CAN1_PELI->DATA8;
                                        PeliRxMessage->Data[7] = CAN1_PELI->DATA9;
                                }
                            CAN_FIFORelease(CANx);
                            break;
                    case CAN2_BASE:
                            PeliRxMessage->FF = (CAN2_PELI->FF) >> 7;
                            PeliRxMessage->RTR = ((CAN2_PELI->FF) >> 6) & 0x1;
                            PeliRxMessage->DLC = (CAN2_PELI->FF) & 0xf;

                            if(((FunctionalState)PeliRxMessage->FF) != ENABLE)
                                {
                                        tempid = (uint32_t)(CAN2_PELI->ID1 >> 5);
                                        tempid |= (uint32_t)(CAN2_PELI->ID0 << 3);
                                        PeliRxMessage->ID = tempid;
                                        PeliRxMessage->Data[0] = CAN2_PELI->DATA0;
                                        PeliRxMessage->Data[1] = CAN2_PELI->DATA1;
                                        PeliRxMessage->Data[2] = CAN2_PELI->DATA2;
                                        PeliRxMessage->Data[3] = CAN2_PELI->DATA3;
                                        PeliRxMessage->Data[4] = CAN2_PELI->DATA4;
                                        PeliRxMessage->Data[5] = CAN2_PELI->DATA5;
                                        PeliRxMessage->Data[6] = CAN2_PELI->DATA6;
                                        PeliRxMessage->Data[7] = CAN2_PELI->DATA7;
                                }
                            else
                                {
                                        tempid = (uint32_t)((CAN2_PELI->DATA1 & 0xf8) >> 3);
                                        tempid |= (uint32_t)(CAN2_PELI->DATA0 << 5);
                                        tempid |= (uint32_t)(CAN2_PELI->ID1 << 13);
                                        tempid |= (uint32_t)(CAN2_PELI->ID0 << 21);
                                        PeliRxMessage->ID = tempid;
                                        PeliRxMessage->Data[0] = CAN2_PELI->DATA2;
                                        PeliRxMessage->Data[1] = CAN2_PELI->DATA3;
                                        PeliRxMessage->Data[2] = CAN2_PELI->DATA4;
                                        PeliRxMessage->Data[3] = CAN2_PELI->DATA5;
                                        PeliRxMessage->Data[4] = CAN2_PELI->DATA6;
                                        PeliRxMessage->Data[5] = CAN2_PELI->DATA7;
                                        PeliRxMessage->Data[6] = CAN2_PELI->DATA8;
                                        PeliRxMessage->Data[7] = CAN2_PELI->DATA9;
                                }
                            CAN_FIFORelease(CANx);
                            break;
                    default:
                            break;
            }
}


/**
* @brief  Get available current informatoin in receive FIFO only in Peli workmode.
* @retval The value in reg RMC
*/
uint32_t CAN_Peli_GetRxFIFOInfo(CAN_TypeDef* CANx)
{
        switch (*(uint32_t*)&CANx)
            {
                    case CAN1_BASE:
                            return CAN1_PELI->RMC;
                            break;
                    case CAN2_BASE:
                            return CAN2_PELI->RMC;
                            break;
                    default:
                            break;
            }

}


/** @defgroup CAN_Group5 CAN Bus Error management functions
*  @brief    CAN Bus Error management functions
*
@verbatim
===============================================================================
##### CAN Bus Error management functions #####
===============================================================================

@endverbatim
* @{
*/

/**
* @brief  Returns the CAN's last error code (LEC).
* @retval Error code:
*          - CAN_ERRORCODE_NoErr: No Error
*          - CAN_ERRORCODE_StuffErr: Stuff Error
*          - CAN_ERRORCODE_FormErr: Form Error
*          - CAN_ERRORCODE_ACKErr : Acknowledgment Error
*          - CAN_ERRORCODE_BitRecessiveErr: Bit Recessive Error
*          - CAN_ERRORCODE_BitDominantErr: Bit Dominant Error
*          - CAN_ERRORCODE_CRCErr: CRC Error
*          - CAN_ERRORCODE_SoftwareSetErr: Software Set Error
*/
uint8_t CAN_Peli_GetLastErrorCode(CAN_TypeDef* CANx)
{
    uint8_t errorcode = 0;

        switch (*(uint32_t*)&CANx)
            {
                    case CAN1_BASE:
                            /* Get the error code*/
                            errorcode = ((uint8_t)CAN1_PELI->ECC);
                            break;
                    case CAN2_BASE:
                            /* Get the error code*/
                            errorcode = ((uint8_t)CAN2_PELI->ECC);
                            break;
                    default:
                            break;
            }
    /* Return the error code*/
    return errorcode;
}
/**
* @brief  Returns the CAN Receive Error Counter (REC).
* @note   In case of an error during reception, this counter is incremented
*         by 1 or by 8 depending on the error condition as defined by the CAN
*         standard. After every successful reception, the counter is
*         decremented by 1 or reset to 120 if its value was higher than 128.
*         When the counter value exceeds 127, the CAN controller enters the
*         error passive state.
* @retval CAN Receive Error Counter.
*/
uint8_t CAN_Peli_GetReceiveErrorCounter(CAN_TypeDef* CANx)
{
    uint8_t counter = 0;

    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

        switch (*(uint32_t*)&CANx)
            {
                    case CAN1_BASE:
                            /* Get the Receive Error Counter*/
                            counter = (uint8_t)(CAN1_PELI->RXERR);
                            break;
                    case CAN2_BASE:
                            /* Get the Receive Error Counter*/
                            counter = (uint8_t)(CAN2_PELI->RXERR);
                            break;
                    default:
                            break;
            }

    /* Return the Receive Error Counter*/
    return counter;
}


/**
* @brief  Returns the LSB of the 9-bit CANx Transmit Error Counter(TEC).
* @retval LSB of the 8-bit CAN Transmit Error Counter.
*/
uint8_t CAN_Peli_GetLSBTransmitErrorCounter(CAN_TypeDef* CANx)
{
    uint8_t counter = 0;

    /* Check the parameters */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

        switch (*(uint32_t*)&CANx)
            {
                    case CAN1_BASE:
                            /* Get the LSB of the 8-bit CAN Transmit Error Counter(TEC) */
                            counter = (uint8_t)(CAN1_PELI->TXERR);
                            break;
                    case CAN2_BASE:
                            /* Get the LSB of the 8-bit CAN Transmit Error Counter(TEC) */
                            counter = (uint8_t)(CAN2_PELI->TXERR);
                            break;
                    default:
                            break;
            }

    /* Return the LSB of the 8-bit CAN Transmit Error Counter(TEC) */
    return counter;
}
/** @defgroup CAN_Group6 Interrupts and flags management functions
*  @brief   Interrupts and flags management functions
*
@verbatim
===============================================================================
##### Interrupts and flags management functions #####
===============================================================================
[..] This section provides functions allowing to configure the CAN Interrupts
and to get the status and clear flags and Interrupts pending bits.
[..] The CAN provides 14 Interrupts sources and 15 Flags:

*** Flags ***
=============
*/
/**
* @brief  Enables or disables the specified CAN interrupts in peli workmode.
* @param  CAN_IT: specifies the CAN interrupt sources to be enabled or disabled.
*          This parameter can be:
*            @arg CAN_IT_RI: Receive FIFO not empty Interrupt
*            @arg CAN_IT_TI: Transmit Interrupt
*            @arg CAN_IT_EI: ERROR Interrupt
*            @arg CAN_IT_DOI: Data voerflow Interrupt
*            @arg CAN_IT_WUI: Wakeup Interrupt
*            @arg CAN_IT_EPI(only Peli): passive error Interrupt
*            @arg CAN_IT_ALI(only Peli): arbiter lose Interrupt
*            @arg CAN_IT_BEI(only Peli): bus error Interrupt
@arg CAN_IT_ALL: use it can enble all Interrupt
* @param  NewState: new state of the CAN interrupts.
*          This parameter can be: ENABLE or DISABLE.
* @retval None
*/
void CAN_Peli_ITConfig(CAN_TypeDef* CANx,uint32_t CAN_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_CAN_IT(CAN_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

        switch (*(uint32_t*)&CANx)
            {
                    case CAN1_BASE:
                            if (NewState != DISABLE)
                                {
                                        /* Enable the selected CAN interrupt */
                                        CAN1_PELI->IER |= CAN_IT;
                                }
                            else
                                {
                                        /* Disable the selected CAN interrupt */
                                        CAN1_PELI->IER &= ~CAN_IT;
                                }
                            break;
                    case CAN2_BASE:
                            if (NewState != DISABLE)
                                {
                                        /* Enable the selected CAN interrupt */
                                        CAN2_PELI->IER |= CAN_IT;
                                }
                            else
                                {
                                        /* Disable the selected CAN interrupt */
                                        CAN2_PELI->IER &= ~CAN_IT;
                                }
                            break;
                    default:
                            break;
            }

}


/**
* @brief  Checks whether the specified CAN interrupt has occurred or not.
* @param  CAN_IT: specifies the CAN interrupt source to check.
*          This parameter can be one of the following values:
*            @arg CAN_IT_RI: Receive FIFO not empty Interrupt
*            @arg CAN_IT_TI: Transmit Interrupt
*            @arg CAN_IT_EI: ERROR Interrupt
*            @arg CAN_IT_DOI: Data voerflow Interrupt
*            @arg CAN_IT_WUI: Wakeup Interrupt
*            @arg CAN_IT_EPI(only Peli): passive error Interrupt
*            @arg CAN_IT_ALI(only Peli): arbiter lose Interrupt
*            @arg CAN_IT_BEI(only Peli): bus error Interrupt
@arg CAN_IT_ALL: use it can enble all Interrupt
* @retval The current state of CAN_IT (SET or RESET).
*/
ITStatus CAN_Peli_GetITStatus(CAN_TypeDef* CANx, uint32_t CAN_IT)
{
    ITStatus itstatus = RESET;
    /* Check the parameters */
    assert_param(IS_CAN_IT(CAN_IT));

        switch (*(uint32_t*)&CANx)
            {
                    case CAN1_BASE:
                            /* check the interrupt enable bit */
                            if((CAN1_PELI->IR & CAN_IT) != CAN_IT)
                            {
                                    itstatus = RESET;
                            }
                            else
                            {
                                    itstatus = SET;
                            }
                            break;
                    case CAN2_BASE:
                            /* check the interrupt enable bit */
                            if((CAN2_PELI->IR & CAN_IT) != CAN_IT)
                            {
                                    itstatus = RESET;
                            }
                            else
                            {
                                    itstatus = SET;
                            }
                            break;
                    default:
                            break;
            }

    return itstatus;
}

/**
* @brief  Config CAN_Peli_InitTypeDef baud parameter.
* @param  CAN_Peli_InitTypeDef: CAN struct.
* @param  SrcClk: CAN module clock.
* @param  baud: specified baud.
* @retval The current state of CAN_IT (SET or RESET).
*/
void CAN_AutoCfg_BaudParam(CAN_Peli_InitTypeDef  *CAN_Peli_InitStruct, unsigned int SrcClk, unsigned int baud )
{
    unsigned int i, value = baud, record = 1;
    unsigned int remain = 0, sumPrescaler = 0;
    while(( baud == 0 ) || ( SrcClk == 0 )); //防止波特率及时钟为0
    sumPrescaler = SrcClk / baud; //总分频
    sumPrescaler = sumPrescaler / 2; //
    for( i = 25; i > 3; i -- )
    {
        remain = sumPrescaler - ((sumPrescaler / i) * i);
        if( remain == 0 )       //整除
        {
            record = i;
            break;
        }
        else
        {
            if(remain < value)
            {
                value = remain;
                record = i;
            }
        }
    }
    CAN_Peli_InitStruct->SJW = 0;
    CAN_Peli_InitStruct->BRP = (sumPrescaler / record) - 1;
    CAN_Peli_InitStruct->TESG2 = (record - 3) / 3;
    CAN_Peli_InitStruct->TESG1 = (record - 3) - CAN_Peli_InitStruct->TESG2;
}

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/



/*-------------------------(C) COPYRIGHT 2016 HOLOCENE ----------------------*/

