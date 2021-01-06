/**
  ******************************************************************************
  * @brief   CAN functions of the firmware library.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x_can.h"
#include "gd32f10x_rcc.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @defgroup CAN
  * @brief CAN driver modules
  * @{
  */

/** @defgroup CAN_Private_Defines
  * @{
  */


/* CAN Mailbox Transmit Request */
#define CAN_TMIR_TE                       ((uint32_t)0x00000001)

/* CAN Filter Master Register bits */
#define FMR_FINIT                         ((uint32_t)0x00000001)

/* Time out for IWS bit */
#define IWS_TIMEOUT                       ((uint32_t)0x0000FFFF)
/* Time out for SWS bit */
#define SWS_TIMEOUT                       ((uint32_t)0x0000FFFF)

/* CAN TMIR_StdId masks */
#define CAN_TMIR_StdId_Mask               ((uint32_t)0x000007FF)

/* CAN TMIR_ExtId masks */
#define CAN_TMIR_ExtId_Mask               ((uint32_t)0x1FFFFFFF)

/* CAN TMIR_ExtId masks */
#define CAN_FLAG_Mask                     ((uint32_t)0x000FFFFF)

/* Flags in TSTR register */
#define CAN_FLAGS_TSTR                    ((uint32_t)0x08000000)

/* Flags in RFR1 register */
#define CAN_FLAGS_RFR1                    ((uint32_t)0x04000000)

/* Flags in RFR0register */
#define CAN_FLAGS_RFR0                    ((uint32_t)0x02000000)

/* Flags in STR register */
#define CAN_FLAGS_STR                     ((uint32_t)0x01000000)

/* Flags in ER register */
#define CAN_FLAGS_ER                      ((uint32_t)0x00F00000)

/* Mailboxes definition */
#define CAN_TXMAILBOX_0                   ((uint8_t)0x00)
#define CAN_TXMAILBOX_1                   ((uint8_t)0x01)
#define CAN_TXMAILBOX_2                   ((uint8_t)0x02)

/* CAN Master Control Register bit */
#define MCR_DBF                           ((uint32_t)0x00010000)


#define CAN_MODE_MASK                     ((uint32_t)0x00000003)
/**
  * @}
  */


/** @defgroup CAN_Private_Functions
  * @{
  */

/**
  * @brief  Deinitialize the CAN peripheral registers.
  * @param  CANx: where x:[1,2] to select the CAN peripheral.
  * @retval None.
  */
void CAN_DeInit(CAN_TypeDef *CANx)
{
    if (CANx == CAN1) {
        /* Force CAN1 reset state */
        RCC_APB1PeriphReset_Enable(RCC_APB1PERIPH_CAN1, ENABLE);
        /* Release CAN1 from reset state */
        RCC_APB1PeriphReset_Enable(RCC_APB1PERIPH_CAN1, DISABLE);
    } else {
        /* Force CAN2 reset state */
        RCC_APB1PeriphReset_Enable(RCC_APB1PERIPH_CAN2, ENABLE);
        /* Release CAN2 from reset state */
        RCC_APB1PeriphReset_Enable(RCC_APB1PERIPH_CAN2, DISABLE);
    }
}

/**
  * @brief  Initialize the CAN peripheral according to the CAN_InitParaStruct.
  * @param  CANx:where x:[1,2]
  * @param  CAN_InitParaStruct: contain the configuration information for the CAN peripheral.
  * @retval It will be returned the status of CAN_INITSTATE_FAILED or CAN_INITSTATE_SUCCESS.
  */
uint8_t CAN_Init(CAN_TypeDef *CANx, CAN_InitPara *CAN_InitParaStruct)
{
    uint32_t wait_ack = 0x00000000;

    /* Out of sleep mode */
    CANx->CTLR &= (~(uint32_t)CAN_CTLR_SWM);

    /* Enable initial working */
    CANx->CTLR |= CAN_CTLR_IWM ;

    /* Wait the acknowledge */
    while (((CANx->STR & CAN_STR_IWS) != CAN_STR_IWS) && (wait_ack != IWS_TIMEOUT)) {
        wait_ack++;
    }

    /* Check whether initial working is success */
    if ((CANx->STR & CAN_STR_IWS) != CAN_STR_IWS) {
        return CAN_INITSTATE_FAILED;
    } else {
        /* Set the time triggered communication mode */
        if (CAN_InitParaStruct->CAN_TTC == ENABLE) {
            CANx->CTLR |= CAN_CTLR_TTC;
        } else {
            CANx->CTLR &= ~(uint32_t)CAN_CTLR_TTC;
        }

        /* Set the automatic bus-off management */
        if (CAN_InitParaStruct->CAN_ABOR == ENABLE) {
            CANx->CTLR |= CAN_CTLR_ABOR;
        } else {
            CANx->CTLR &= ~(uint32_t)CAN_CTLR_ABOR;
        }

        /* Set the automatic wake-up mode */
        if (CAN_InitParaStruct->CAN_AWK == ENABLE) {
            CANx->CTLR |= CAN_CTLR_AWK;
        } else {
            CANx->CTLR &= ~(uint32_t)CAN_CTLR_AWK;
        }

        /* Set the automatic retransmission mode */
        if (CAN_InitParaStruct->CAN_ARD == ENABLE) {
            CANx->CTLR |= CAN_CTLR_ARD;
        } else {
            CANx->CTLR &= ~(uint32_t)CAN_CTLR_ARD;
        }

        /* Set receive FIFO overwrite mode */
        if (CAN_InitParaStruct->CAN_RFOD == ENABLE) {
            CANx->CTLR |= CAN_CTLR_RFOD;
        } else {
            CANx->CTLR &= ~(uint32_t)CAN_CTLR_RFOD;
        }

        /* Set the Transmit FIFO order */
        if (CAN_InitParaStruct->CAN_TFO == ENABLE) {
            CANx->CTLR |= CAN_CTLR_TFO;
        } else {
            CANx->CTLR &= ~(uint32_t)CAN_CTLR_TFO;
        }

        /* Set the bit timing register */
        CANx->BTR = (uint32_t)((uint32_t)CAN_InitParaStruct->CAN_Mode << 30) | \
                    ((uint32_t)CAN_InitParaStruct->CAN_SJW << 24) | \
                    ((uint32_t)CAN_InitParaStruct->CAN_BS1 << 16) | \
                    ((uint32_t)CAN_InitParaStruct->CAN_BS2 << 20) | \
                    ((uint32_t)CAN_InitParaStruct->CAN_Prescaler - 1);

        /* leave initialisation */
        CANx->CTLR &= ~(uint32_t)CAN_CTLR_IWM;

        /* Wait the acknowledge */
        wait_ack = 0;

        while (((CANx->STR & CAN_STR_IWS) == CAN_STR_IWS) && (wait_ack != IWS_TIMEOUT)) {
            wait_ack++;
        }

        /* Check whether qiut initial working mode */
        if ((CANx->STR & CAN_STR_IWS) == CAN_STR_IWS) {
            return CAN_INITSTATE_FAILED;
        } else {
            return CAN_INITSTATE_SUCCESS;
        }
    }

}

/**
  * @brief  Initialize the CAN peripheral according to the CAN_FilterInitStruct.
  * @param  CAN_FilterInitParaStruct:contain the information for the CAN peripheral.
  * @retval None.
  */
void CAN_FilterInit(CAN_FilterInitPara *CAN_FilterInitParaStruct)
{
    uint32_t filter_number = 0;

    filter_number = ((uint32_t)1) << CAN_FilterInitParaStruct->CAN_FilterNumber;

    /* Set filter lock disable */
    CAN1->FCTLR |= CAN_FCTLR_FLD;

    /* Disable Filter */
    CAN1->FWR &= ~(uint32_t)filter_number;

    /* Filter Scale */
    if (CAN_FilterInitParaStruct->CAN_FilterScale == CAN_FILTERSCALE_16BIT) {
        /* Set the filter 16-bit scale*/
        CAN1->FSR &= ~(uint32_t)filter_number;

        /* First 16-bit list and First 16-bit mask */
        /* Or First 16-bit list and Second 16-bit list */
        CAN1->FilterRegister[CAN_FilterInitParaStruct->CAN_FilterNumber].FD0R =
            ((0x0000FFFF & (uint32_t)CAN_FilterInitParaStruct->CAN_FilterMaskListLow) << 16) |
            (0x0000FFFF & (uint32_t)CAN_FilterInitParaStruct->CAN_FilterListLow);

        /* Second 16-bit identifier and Second 16-bit mask */
        /* Or Third 16-bit identifier and Fourth 16-bit identifier */
        CAN1->FilterRegister[CAN_FilterInitParaStruct->CAN_FilterNumber].FD1R =
            ((0x0000FFFF & (uint32_t)CAN_FilterInitParaStruct->CAN_FilterMaskListHigh) << 16) |
            (0x0000FFFF & (uint32_t)CAN_FilterInitParaStruct->CAN_FilterListHigh);
    }

    if (CAN_FilterInitParaStruct->CAN_FilterScale == CAN_FILTERSCALE_32BIT) {
        /* 32-bit scale for the filter */
        CAN1->FSR |= filter_number;
        /* 32-bit identifier or First 32-bit identifier */
        CAN1->FilterRegister[CAN_FilterInitParaStruct->CAN_FilterNumber].FD0R =
            ((0x0000FFFF & (uint32_t)CAN_FilterInitParaStruct->CAN_FilterListHigh) << 16) |
            (0x0000FFFF & (uint32_t)CAN_FilterInitParaStruct->CAN_FilterListLow);
        /* 32-bit mask or Second 32-bit identifier */
        CAN1->FilterRegister[CAN_FilterInitParaStruct->CAN_FilterNumber].FD1R =
            ((0x0000FFFF & (uint32_t)CAN_FilterInitParaStruct->CAN_FilterMaskListHigh) << 16) |
            (0x0000FFFF & (uint32_t)CAN_FilterInitParaStruct->CAN_FilterMaskListLow);
    }

    /* Filter Mode */
    if (CAN_FilterInitParaStruct->CAN_FilterMode == CAN_FILTERMODE_MASK) {
        /*Filter with Mask mode*/
        CAN1->FMR &= ~(uint32_t)filter_number;
    } else { /* CAN_FilterInitStruct->CAN_FilterMode == CAN_FILTERMODE_LIST */
        /*Filter with List mode*/
        CAN1->FMR |= (uint32_t)filter_number;
    }

    /* Filter associated with FIFO */
    if (CAN_FilterInitParaStruct->CAN_FilterFIFOAssociation == CAN_FILTER_FIFO0) {
        /* Filter associated with FIFO 0 */
        CAN1->FAFR &= ~(uint32_t)filter_number;
    }

    if (CAN_FilterInitParaStruct->CAN_FilterFIFOAssociation == CAN_FILTER_FIFO1) {
        /* Filter associated with FIFO 1 */
        CAN1->FAFR |= (uint32_t)filter_number;
    }

    /* Filter working */
    if (CAN_FilterInitParaStruct->CAN_FilterWork == ENABLE) {
        CAN1->FWR |= filter_number;
    }

    /* Exit the initialisation mode for the filter */
    CAN1->FCTLR &= ~CAN_FCTLR_FLD;
}

/**
  * @brief  Configure each CAN_InitParaStruct member with default value.
  * @param  CAN_InitParaStruct: pointer to a CAN_InitPara structure to initialize.
  * @retval None.
  */
void CAN_StructInit(CAN_InitPara *CAN_InitParaStruct)
{
    /* Set the time triggered communication mode */
    CAN_InitParaStruct->CAN_TTC = DISABLE;

    /* Set the automatic bus-off recovery */
    CAN_InitParaStruct->CAN_ABOR = DISABLE;

    /* Set the automatic wake up mode */
    CAN_InitParaStruct->CAN_AWK = DISABLE;

    /* Set the automatic retransmission disable */
    CAN_InitParaStruct->CAN_ARD = DISABLE;

    /* Set the receive FIFO overwrite mode */
    CAN_InitParaStruct->CAN_RFOD = DISABLE;

    /* Set the transmit FIFO order */
    CAN_InitParaStruct->CAN_TFO = DISABLE;

    /* Set the CAN_Mode member */
    CAN_InitParaStruct->CAN_Mode = CAN_MODE_NORMAL;

    /* Set the CAN_SJW member */
    CAN_InitParaStruct->CAN_SJW = CAN_SJW_1TQ;

    /* Set the CAN_BS1 member */
    CAN_InitParaStruct->CAN_BS1 = CAN_BS1_4TQ;

    /* Set the CAN_BS2 member */
    CAN_InitParaStruct->CAN_BS2 = CAN_BS2_3TQ;

    /* Set the CAN_Prescaler member */
    CAN_InitParaStruct->CAN_Prescaler = 1;
}

/**
  * @brief  Set header bank of CAN2 filter.
  * @param  CAN2_HeaderBankNumber: Select header bank of CAN2 filter.It can be 1 to 27.
  * @retval None.
  */
void CAN_HeaderBank(uint8_t CAN_HeaderBankNumber)
{
    /* Set filter lock disable */
    CAN1->FCTLR |= CAN_FCTLR_FLD;

    /* Select filter start number for slave CAN */
    CAN1->FCTLR &= (uint32_t)0xFFFFC0F1 ;
    CAN1->FCTLR |= (uint32_t)(CAN_HeaderBankNumber) << 8;

    /* Filter out the initialization mode */
    CAN1->FCTLR |= ~CAN_FCTLR_FLD;
}

/**
  * @brief  Enable or disable the Debug Freeze for CAN.
  * @param  CANx: where x :[1,2] for selecting the CAN peripheral.
  * @param  NewValue: new state of the CAN peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void CAN_DebugFreeze(CAN_TypeDef *CANx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        CANx->CTLR |= CAN_CTLR_DFZ;
    } else {
        CANx->CTLR &= ~CAN_CTLR_DFZ;
    }
}


/**
  * @brief  Enable or disabe the CAN Time Triggered communication mode.
  * @param  CANx:where x :[1,2] for selecting the CAN peripheral.
  * @param  NewValue : Mode new state , This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CAN_TimeTrigComMode_Enable(CAN_TypeDef *CANx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the TTC mode */
        CANx->CTLR |= CAN_CTLR_TTC;

        /* Set TSEbits */
        CANx->TxMailBox[0].TMPR |= ((uint32_t)CAN_TMPR0_TSE);
        CANx->TxMailBox[1].TMPR |= ((uint32_t)CAN_TMPR1_TSE);
        CANx->TxMailBox[2].TMPR |= ((uint32_t)CAN_TMPR2_TSE);
    } else {
        /* Disable the TTC mode */
        CANx->CTLR &= (uint32_t)(~(uint32_t)CAN_CTLR_TTC);

        /* Reset TSE bits */
        CANx->TxMailBox[0].TMPR &= ((uint32_t)~CAN_TMPR0_TSE);
        CANx->TxMailBox[1].TMPR &= ((uint32_t)~CAN_TMPR1_TSE);
        CANx->TxMailBox[2].TMPR &= ((uint32_t)~CAN_TMPR2_TSE);
    }
}
/**
  * @brief  Initiate to transmit a message.
  * @param  CANx: where x:[1,2]to to select the CAN peripheral.
  * @param  TxMessage: contain CAN Id, CAN DLC and CAN data for the structure.
  * @retval The number of the mailbox that is used for transmission
  *         or CAN_TxState_NoMailBox if there is no empty mailbox.
  */
uint8_t CAN_Transmit(CAN_TypeDef *CANx, CanTxMessage *TxMessage)
{
    uint8_t transmit_mailbox_number = 0;

    /* Select one empty transmit mailbox */
    if ((CANx->TSTR & CAN_TSTR_TME0) == CAN_TSTR_TME0) {
        transmit_mailbox_number = 0;
    } else if ((CANx->TSTR & CAN_TSTR_TME1) == CAN_TSTR_TME1) {
        transmit_mailbox_number = 1;
    } else if ((CANx->TSTR & CAN_TSTR_TME2) == CAN_TSTR_TME2) {
        transmit_mailbox_number = 2;
    } else {
        transmit_mailbox_number = CAN_TXSTATE_NOMAILBOX;
    }

    if (transmit_mailbox_number != CAN_TXSTATE_NOMAILBOX) {
        /* Set up the Id */
        CANx->TxMailBox[transmit_mailbox_number].TMIR &= CAN_TMIR_TE;
        if (TxMessage->FF == CAN_FF_STANDARD) {
            CANx->TxMailBox[transmit_mailbox_number].TMIR |= ((TxMessage->StdId << 21) | \
                    TxMessage->FT);
        } else {
            CANx->TxMailBox[transmit_mailbox_number].TMIR |= ((TxMessage->ExtId << 3) | \
                    TxMessage->FF | \
                    TxMessage->FT);
        }

        /* Set up the DLC */
        TxMessage->DLC &= ((uint8_t)CAN_TMPR0_DLC);
        CANx->TxMailBox[transmit_mailbox_number].TMPR &= ((uint32_t)~CAN_TMPR0_DLC);
        CANx->TxMailBox[transmit_mailbox_number].TMPR |= TxMessage->DLC;

        /* Set up the data field */
        CANx->TxMailBox[transmit_mailbox_number].TMD0R = (((uint32_t)TxMessage->Data[3] << 24) |
                ((uint32_t)TxMessage->Data[2] << 16) |
                ((uint32_t)TxMessage->Data[1] << 8) |
                ((uint32_t)TxMessage->Data[0]));
        CANx->TxMailBox[transmit_mailbox_number].TMD1R = (((uint32_t)TxMessage->Data[7] << 24) |
                ((uint32_t)TxMessage->Data[6] << 16) |
                ((uint32_t)TxMessage->Data[5] << 8) |
                ((uint32_t)TxMessage->Data[4]));
        /* Request transmission */
        CANx->TxMailBox[transmit_mailbox_number].TMIR |= CAN_TMIR0_TE;
    }
    return transmit_mailbox_number;
}

/**
  * @brief  Check the state of message transmission.
  * @param  CANx: where x:[1,2] to to select the CAN peripheral.
  * @param  TransmitMailbox: the number of the used transmission mailbox.
  * @retval Return CAN_TXSTATE_OK or CAN_TXSTATE_FAILED.
  */
uint8_t CAN_TransmitState(CAN_TypeDef *CANx, uint8_t TransmitMailbox)
{
    uint32_t state = 0;

    switch (TransmitMailbox) {
    case (CAN_TXMAILBOX_0):
        state =   CANx->TSTR & (CAN_TSTR_MTF0 | CAN_TSTR_MTFNE0 | CAN_TSTR_TME0);
        break;
    case (CAN_TXMAILBOX_1):
        state =   CANx->TSTR & (CAN_TSTR_MTF1 | CAN_TSTR_MTFNE1 | CAN_TSTR_TME1);
        break;
    case (CAN_TXMAILBOX_2):
        state =   CANx->TSTR & (CAN_TSTR_MTF2 | CAN_TSTR_MTFNE2 | CAN_TSTR_TME2);
        break;
    default:
        state = CAN_TXSTATE_FAILED;
        break;
    }
    switch (state) {
    /* transmit pending  */
    case (0x0):
        state = CAN_TXSTATE_PENDING;
        break;
    /* transmit failed  */
    case (CAN_TSTR_MTF0 | CAN_TSTR_TME0):
        state = CAN_TXSTATE_FAILED;
        break;
    case (CAN_TSTR_MTF1 | CAN_TSTR_TME1):
        state = CAN_TXSTATE_FAILED;
        break;
    case (CAN_TSTR_MTF2 | CAN_TSTR_TME2):
        state = CAN_TXSTATE_FAILED;
        break;
    /* transmit succeeded  */
    case (CAN_TSTR_MTF0 | CAN_TSTR_MTFNE0 | CAN_TSTR_TME0):
        state = CAN_TXSTATE_OK;
        break;
    case (CAN_TSTR_MTF1 | CAN_TSTR_MTFNE1 | CAN_TSTR_TME1):
        state = CAN_TXSTATE_OK;
        break;
    case (CAN_TSTR_MTF2 | CAN_TSTR_MTFNE2 | CAN_TSTR_TME2):
        state = CAN_TXSTATE_OK;
        break;
    default:
        state = CAN_TXSTATE_FAILED;
        break;
    }
    return (uint8_t) state;
}

/**
  * @brief  Stop a transmit mission.
  * @param  CANx: where x:[1,2] to to select the CAN peripheral.
  * @param  Mailbox:  Mailbox number.
  * @retval None.
  */
void CAN_StopTransmit(CAN_TypeDef *CANx, uint8_t Mailbox)
{
    /* Stop transmission */
    switch (Mailbox) {
    case (CAN_TXMAILBOX_0):
        CANx->TSTR |= CAN_TSTR_MST0;
        break;
    case (CAN_TXMAILBOX_1):
        CANx->TSTR |= CAN_TSTR_MST1;
        break;
    case (CAN_TXMAILBOX_2):
        CANx->TSTR |= CAN_TSTR_MST2;
        break;
    default:
        break;
    }
}


/**
  * @brief  Receive a message.
  * @param  CANx: where x:[1,2] to to select the CAN peripheral.
  * @param  FIFONumber: Receive FIFO number, CAN_FIFO0 or CAN_FIFO1.
  * @param  RxMessage: a structure receive message which contains
  *                    CAN Id, CAN DLC, CAN datas and FI number.
  * @retval None.
  */
void CAN_Receive(CAN_TypeDef *CANx, uint8_t FIFONumber, CanRxMessage *RxMessage)
{
    /* Get the frame identifier */
    RxMessage->FF = (uint8_t)0x04 & CANx->FIFOMailBox[FIFONumber].RFMIR;
    if (RxMessage->FF == CAN_FF_STANDARD) {
        RxMessage->StdId = CAN_TMIR_StdId_Mask & (CANx->FIFOMailBox[FIFONumber].RFMIR >> 21);
    } else {
        RxMessage->ExtId = CAN_TMIR_ExtId_Mask & (CANx->FIFOMailBox[FIFONumber].RFMIR >> 3);
    }

    RxMessage->FT = (uint8_t)0x02 & CANx->FIFOMailBox[FIFONumber].RFMIR;
    /* Get the data length code */
    RxMessage->DLC = (uint8_t)0x0F & CANx->FIFOMailBox[FIFONumber].RFMPR;
    /* Get the filtering index */
    RxMessage->FI = (uint8_t)0xFF & (CANx->FIFOMailBox[FIFONumber].RFMPR >> 8);
    /* Get FIFO mailbox data */
    RxMessage->Data[0] = (uint8_t)0xFF & CANx->FIFOMailBox[FIFONumber].RFMD0R;
    RxMessage->Data[1] = (uint8_t)0xFF & (CANx->FIFOMailBox[FIFONumber].RFMD0R >> 8);
    RxMessage->Data[2] = (uint8_t)0xFF & (CANx->FIFOMailBox[FIFONumber].RFMD0R >> 16);
    RxMessage->Data[3] = (uint8_t)0xFF & (CANx->FIFOMailBox[FIFONumber].RFMD0R >> 24);
    RxMessage->Data[4] = (uint8_t)0xFF & CANx->FIFOMailBox[FIFONumber].RFMD1R;
    RxMessage->Data[5] = (uint8_t)0xFF & (CANx->FIFOMailBox[FIFONumber].RFMD1R >> 8);
    RxMessage->Data[6] = (uint8_t)0xFF & (CANx->FIFOMailBox[FIFONumber].RFMD1R >> 16);
    RxMessage->Data[7] = (uint8_t)0xFF & (CANx->FIFOMailBox[FIFONumber].RFMD1R >> 24);
    /* Release the FIFO */
    if (FIFONumber == CAN_FIFO0) {
        CANx->RFR0 |= CAN_RFR0_RFD0;
    }

    /* FIFONumber == CAN_FIFO1 */
    else {
        CANx->RFR1 |= CAN_RFR1_RFD1;
    }
}

/**
  * @brief  Dequeue the FIFO.
  * @param  CANx: where x:[1,2] to to select the CAN peripheral.
  * @param  FIFONumber: FIFO to dequeue, it can be CAN_FIFO0 or CAN_FIFO1.
  * @retval None.
  */
void CAN_FIFODequeue(CAN_TypeDef *CANx, uint8_t FIFONumber)
{

    if (FIFONumber == CAN_FIFO0) {
        /* Release FIFO 0 */
        CANx->RFR0 |= CAN_RFR0_RFD0;
    } else { /* FIFONumber == CAN_FIFO1 */
        /* Release FIFO1 */
        CANx->RFR1 |= CAN_RFR1_RFD1;
    }
}

/**
  * @brief  Return the length of receiving messages.
  * @param  CANx: where x:[1,2] to to select the CAN peripheral.
  * @param  FIFONumber: Receive FIFO number, CAN_FIFO0 or CAN_FIFO1.
  * @retval message_length : which is the Length of pending message.
  */
uint8_t CAN_MessageLength(CAN_TypeDef *CANx, uint8_t FIFONumber)
{
    uint8_t message_length = 0;
    if (FIFONumber == CAN_FIFO0) {
        message_length = (uint8_t)(CANx->RFR0 & (uint32_t)0x03);
    } else if (FIFONumber == CAN_FIFO1) {
        message_length = (uint8_t)(CANx->RFR1 & (uint32_t)0x03);
    } else {
        message_length = 0;
    }
    return message_length;
}


/**
  * @brief   Select the CAN Working mode.
  * @param CAN_WorkingMode : CAN Working Mode.It can be the following one.
  *     @arg CAN_WORKINGMODE_INITIAL
  *     @arg CAN_WORKINGMODE_NORMAL
  *     @arg CAN_WORKINGMODE_SLEEP
  * @retval state of the requested mode which can be
  *     @arg CAN_MODESTATE_FAILED
  *     @arg CAN_MODESTATE_SUCCESS
  */
uint8_t CAN_WorkingMode(CAN_TypeDef *CANx, uint8_t CAN_WorkingMode)
{
    uint8_t state = CAN_MODESTATE_FAILED;

    /* Timeout for IWS or also for SWS bits*/
    uint32_t timeout = IWS_TIMEOUT;

    if (CAN_WorkingMode == CAN_WORKINGMODE_INITIAL) {
        /* Set initialisation */
        CANx->CTLR = (uint32_t)((CANx->CTLR & (uint32_t)(~(uint32_t)CAN_CTLR_SWM)) | CAN_CTLR_IWM);

        /* Wait the acknowledge */
        while (((CANx->STR & CAN_MODE_MASK) != CAN_STR_IWS) && (timeout != 0)) {
            timeout--;
        }
        if ((CANx->STR & CAN_MODE_MASK) != CAN_STR_IWS) {
            state = CAN_MODESTATE_FAILED;
        } else {
            state = CAN_MODESTATE_SUCCESS;
        }
    } else  if (CAN_WorkingMode == CAN_WORKINGMODE_NORMAL) {
        /* Enter Normal mode */
        CANx->CTLR &= (uint32_t)(~(CAN_CTLR_SWM | CAN_CTLR_IWM));

        /* Wait the acknowledge */
        while (((CANx->STR & CAN_MODE_MASK) != 0) && (timeout != 0)) {
            timeout--;
        }
        if ((CANx->STR & CAN_MODE_MASK) != 0) {
            state = CAN_MODESTATE_FAILED;
        } else {
            state = CAN_MODESTATE_SUCCESS;
        }
    } else  if (CAN_WorkingMode == CAN_WORKINGMODE_SLEEP) {
        /* Set Sleep mode */
        CANx->CTLR = (uint32_t)((CANx->CTLR & (uint32_t)(~(uint32_t)CAN_CTLR_IWM)) | CAN_CTLR_SWM);

        /* Wait the acknowledge */
        while (((CANx->STR & CAN_MODE_MASK) != CAN_STR_SWS) && (timeout != 0)) {
            timeout--;
        }
        if ((CANx->STR & CAN_MODE_MASK) != CAN_STR_SWS) {
            state = CAN_MODESTATE_FAILED;
        } else {
            state = CAN_MODESTATE_SUCCESS;
        }
    } else {
        state = CAN_MODESTATE_FAILED;
    }

    return (uint8_t) state;
}

/**
  * @brief  Enter the Sleep mode.
  * @param  CANx: where x:[1,2] to to select the CAN peripheral.
  * @retval state: CAN_SLEEP_OK or CAN_SLEEP_FAILED.
  */
uint8_t CAN_EnterSleep(CAN_TypeDef *CANx)
{
    /* Set Sleep mode */
    CANx->CTLR = (((CANx->CTLR) & (uint32_t)(~(uint32_t)CAN_CTLR_IWM)) | CAN_CTLR_SWM);

    if ((CANx->STR & (CAN_STR_SWS | CAN_STR_IWS)) == CAN_STR_SWS) {
        /* Sleep mode entered success*/
        return (uint8_t)CAN_SLEEP_OK;
    } else {
        /* Sleep mode entered failure */
        return (uint8_t)CAN_SLEEP_FAILED;
    }
}

/**
  * @brief  Wake up CAN.
  * @param  CANx: where x:[1,2] to to select the CAN peripheral.
  * @retval status:  CAN_WAKEUP_OK or CAN_WAKEUP_FAILED.
  */
uint8_t CAN_WakeUp(CAN_TypeDef *CANx)
{
    uint32_t wait_sws = SWS_TIMEOUT;

    /*set wake up */
    CANx->CTLR &= ~(uint32_t)CAN_CTLR_SWM;

    /* Sleep mode state */
    while (((CANx->CTLR & CAN_CTLR_SWM) == CAN_CTLR_SWM) && (wait_sws != 0x00)) {
        wait_sws--;
    }
    if ((CANx->CTLR & CAN_CTLR_SWM) != CAN_CTLR_SWM) {
        /*Sleep mode exited */
        return (uint8_t)CAN_WAKEUP_OK;
    } else {
        /*Sleep mode exited failure */
        return (uint8_t)CAN_WAKEUP_FAILED;
    }
}


/**
  * @brief  Return the CANx's last error type (LEC).
  * @param  CANx: where x:[1,2] to to select the CAN peripheral.
  * @retval CAN_ErrorType: specify the Error type:
  *     @arg CAN_ERRORTYPE_NOERR
  *     @arg CAN_ERRORTYPE_STUFFERR
  *     @arg CAN_ERRORTYPE_FORMERR
  *     @arg CAN_ERRORTYPE_ACKERR
  *     @arg CAN_ERRORTYPE_BITRECESSIVEERR
  *     @arg CAN_ERRORTYPE_BITDOMINANTERR
  *     @arg CAN_ERRORTYPE_CRCERR
  *     @arg CAN_ERRORTYPE_SOFTWARESETERR
  */

uint8_t CAN_GetErrorType(CAN_TypeDef *CANx)
{
    uint8_t error_type = 0;

    /* Get the error type*/
    error_type = (((uint8_t)CANx->ER) & (uint8_t)CAN_ER_ET);

    /* Return the error type*/
    return error_type;
}

/**
  * @brief  Get the Counter of CANx Receive Error(REC).
  * @note   According to the error condition as defined by the CAN standard,
  *         the counter of CANx Receive Error is increased by 1 or by 8.
  *         When CAN received success everytime, the counter is decreased by 1
  *         or reset to 120 if its value was over than 128.
  *         When the counter value is over 127, the CAN controller enters the
  *         error passive state.
  * @param  CANx: where x:[1,2] to to select the CAN peripheral.
  * @retval CAN Receive Error Counter.
  */
uint8_t CAN_GetReceiveErrorCounter(CAN_TypeDef *CANx)
{
    uint8_t receive_counter = 0;

    /* Get the counter of CANx Receive Error*/
    receive_counter = (uint8_t)((CANx->ER & CAN_ER_REC) >> 24);

    /* Return the Receive Error Counter*/
    return receive_counter;
}


/**
  * @brief  Get the Counter of CANx Transmit Error (TEC).
  * @param  CANx: where x:[1,2] to to select the CAN peripheral.
  * @retval CAN Transmit Error Counter.
  */
uint8_t CAN_GetTransmitErrorCounter(CAN_TypeDef *CANx)
{
    uint8_t transmit_counter = 0;

    /* Get the Counter of CANx Transmit Error(TEC) */
    transmit_counter = (uint8_t)((CANx->ER & CAN_ER_TEC) >> 16);

    /* Return the Transmit Error Counter*/
    return transmit_counter;
}


/**
  * @brief  Enable or disable the specified CANx interrupts.
  * @param  CANx: where x:[1,2] to to select the CAN peripheral.
  * @param  CAN_INT: specify the CAN interrupt sources to be enabled or disabled.
  *   This parameter can be:
  *     @arg CAN_INT_TME
  *     @arg CAN_INT_RFNE0
  *     @arg CAN_INT_RFF0
  *     @arg CAN_INT_RFO0
  *     @arg CAN_INT_RFNE1
  *     @arg CAN_INT_RFF1
  *     @arg CAN_INT_RFO1
  *     @arg CAN_INT_WE
  *     @arg CAN_INT_PE
  *     @arg CAN_INT_BOE
  *     @arg CAN_INT_ET
  *     @arg CAN_INT_ERR
  *     @arg CAN_INT_WU
  *     @arg CAN_INT_SLP
  * @param  NewValue: new state of the CAN interrupts.
  *                   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void CAN_INTConfig(CAN_TypeDef *CANx, uint32_t CAN_INT, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable interrupt */
        CANx->IER |= CAN_INT;
    } else {
        /* Disable interrupt */
        CANx->IER &= ~CAN_INT;
    }
}
/**
  * @brief  Check whether the specified CAN flag is set or not.
  * @param  CANx: where x:[1,2] to to select the CAN peripheral.
  * @param  CAN_FLAG: specify the flag to check.
  *   This parameter can be one of the following flags:
  *     @arg CAN_FLAG_WE:   Warning error Flag
  *     @arg CAN_FLAG_PE:   Passive error Flag
  *     @arg CAN_FLAG_BOE:  Bus-off error Flag
  *     @arg CAN_FLAG_MTF0: Mailbox 0 transmit finished Flag
  *     @arg CAN_FLAG_MTF1: Mailbox 1 transmit finished Flag
  *     @arg CAN_FLAG_MTF2: Mailbox 2 transmit finished Flag
  *     @arg CAN_FLAG_RFL0: the length of the receive FIFO0 Flag
  *     @arg CAN_FLAG_RFF0: Receive FIFO 0 full Flag
  *     @arg CAN_FLAG_RFO0: Receive FIFO 0 overfull  Flag
  *     @arg CAN_FLAG_RFL1: the length of the receive FIFO1 Flag
  *     @arg CAN_FLAG_RFF1: Receive FIFO 1 full Flag
  *     @arg CAN_FLAG_RFO1: Receive FIFO 0 overfull  Flag
  *     @arg CAN_FLAG_WU:   Wake up Flag
  *     @arg CAN_FLAG_SLP:  Sleep working state Flag
  *     @arg CAN_FLAG_ET:   Error type Flag
  * @retval The new state of CAN_FLAG (SET or RESET).
  */
TypeState CAN_GetBitState(CAN_TypeDef *CANx, uint32_t CAN_FLAG)
{
    if ((CAN_FLAG & CAN_FLAGS_ER) != (uint32_t)RESET) {
        /* Check the state of the specified CAN flag */
        if ((CANx->ER & (CAN_FLAG & CAN_FLAG_Mask)) != (uint32_t)RESET) {
            /* CAN_FLAG is set */
            return SET;
        } else {
            /* CAN_FLAG is reset */
            return RESET;
        }
    } else if ((CAN_FLAG & CAN_FLAGS_STR) != (uint32_t)RESET) {
        /* Check the state of the specified CAN flag */
        if ((CANx->STR & (CAN_FLAG & CAN_FLAG_Mask)) != (uint32_t)RESET) {
            /* CAN_FLAG is set */
            return SET;
        } else {
            /* CAN_FLAG is reset */
            return RESET;
        }
    } else if ((CAN_FLAG & CAN_FLAGS_TSTR) != (uint32_t)RESET) {
        /* Check the state of the specified CAN flag */
        if ((CANx->TSTR & (CAN_FLAG & CAN_FLAG_Mask)) != (uint32_t)RESET) {
            /* CAN_FLAG is set */
            return SET;
        } else {
            /* CAN_FLAG is reset */
            return RESET;
        }
    } else if ((CAN_FLAG & CAN_FLAGS_RFR0) != (uint32_t)RESET) {
        /* Check the state of the specified CAN flag */
        if ((CANx->RFR0 & (CAN_FLAG & CAN_FLAG_Mask)) != (uint32_t)RESET) {
            /* CAN_FLAG is set */
            return SET;
        } else {
            /* CAN_FLAG is reset */
            return RESET;
        }
    }
    /* If(CAN_FLAG & CAN_FLAGS_RFR1 != (uint32_t)RESET) */
    else {
        /* Check the state of the specified CAN flag */
        if ((uint32_t)(CANx->RFR1 & (CAN_FLAG & CAN_FLAG_Mask)) != (uint32_t)RESET) {
            /* CAN_FLAG is set */
            return SET;
        } else {
            /* CAN_FLAG is reset */
            return RESET;
        }
    }
}

/**
  * @brief  Clear the CAN's flags.
  * @param  CANx: where x:[1,2] to to select the CAN peripheral.
  * @param  CAN_FLAG: specify the flag to clear.
  *   This parameter can be one of the following flags:
  *     @arg CAN_FLAG_MTF0: Mailbox 0 transmit finished Flag
  *     @arg CAN_FLAG_MTF1: Mailbox 1 transmit finished Flag
  *     @arg CAN_FLAG_MTF2: Mailbox 2 transmit finished Flag
  *     @arg CAN_FLAG_RFF0: Receive FIFO 0 full Flag
  *     @arg CAN_FLAG_RFO0: Receive FIFO 0 overfull  Flag
  *     @arg CAN_FLAG_RFF1: Receive FIFO 1 full Flag
  *     @arg CAN_FLAG_RFO1: Receive FIFO 0 overfull  Flag
  *     @arg CAN_FLAG_WU:   Wake up Flag
  *     @arg CAN_FLAG_SLP:  Sleep working state Flag
  *     @arg CAN_FLAG_ET:   Error type Flag
  * @retval None.
  */
void CAN_ClearBitState(CAN_TypeDef *CANx, uint32_t CAN_FLAG)
{
    uint32_t temp = 0;

    /* ER register */
    if (CAN_FLAG == CAN_FLAG_ET) {
        /* Clear the selected CAN flags */
        CANx->ER = (uint32_t)RESET;
    }
    /* STR or TSTR or RFR0 or RFR1 */
    else {
        temp = CAN_FLAG & CAN_FLAG_Mask;

        if ((CAN_FLAG & CAN_FLAGS_RFR0) != (uint32_t)RESET) {
            /* Receive Flags */
            CANx->RFR0 = (uint32_t)(temp);
        } else if ((CAN_FLAG & CAN_FLAGS_RFR1) != (uint32_t)RESET) {
            /* Receive Flags */
            CANx->RFR1 = (uint32_t)(temp);
        } else if ((CAN_FLAG & CAN_FLAGS_TSTR) != (uint32_t)RESET) {
            /* Transmit Flags */
            CANx->TSTR = (uint32_t)(temp);
        }
        /* If((CAN_FLAG & CAN_FLAGS_STR)!=(uint32_t)RESET) */
        else {
            CANx->STR = (uint32_t)(temp);
        }
    }
}

/**
  * @brief  Check whether the specified CANx interrupt has occurred or not.
  * @param  CANx: where x:[1,2] to to select the CAN peripheral.
  * @param  CAN_INT:  specify the CAN interrupt source to check.
  *   This parameter can be:
  *     @arg CAN_INT_TME
  *     @arg CAN_INT_RFNE0
  *     @arg CAN_INT_RFF0
  *     @arg CAN_INT_RFO0
  *     @arg CAN_INT_RFNE1
  *     @arg CAN_INT_RFF1
  *     @arg CAN_INT_RFO1
  *     @arg CAN_INT_WE
  *     @arg CAN_INT_PE
  *     @arg CAN_INT_BOE
  *     @arg CAN_INT_ET
  *     @arg CAN_INT_ERR
  *     @arg CAN_INT_WU
  *     @arg CAN_INT_SLP
  * @retval The current state of CAN_INT (SET or RESET).
  */
TypeState CAN_GetIntBitState(CAN_TypeDef *CANx, uint32_t CAN_INT)
{
    TypeState intstate = RESET;

    /* Get the enable interrupt bit */
    if ((CANx->IER & CAN_INT) != RESET) {
        switch (CAN_INT) {
        case CAN_INT_TME:
            /* Check CAN_TSTR_MTFx bits */
            intstate = CheckINTState(CANx->TSTR, CAN_TSTR_MTF0 | CAN_TSTR_MTF1 | CAN_TSTR_MTF2);
            break;
        case CAN_INT_RFNE0:
            /* Check CAN_RFR0_RFL0 bit */
            intstate = CheckINTState(CANx->RFR0, CAN_RFR0_RFL0);
            break;
        case CAN_INT_RFF0:
            /* Check CAN_RFR0_RFF0 bit */
            intstate = CheckINTState(CANx->RFR0, CAN_RFR0_RFF0);
            break;
        case CAN_INT_RFO0:
            /* Check CAN_RFR0_RFO0 bit */
            intstate = CheckINTState(CANx->RFR0, CAN_RFR0_RFO0);
            break;
        case CAN_INT_RFNE1:
            /* Check CAN_RFR1_RFL1 bit */
            intstate = CheckINTState(CANx->RFR1, CAN_RFR1_RFL1);
            break;
        case CAN_INT_RFF1:
            /* Check CAN_RFR1_RFF1 bit */
            intstate = CheckINTState(CANx->RFR1, CAN_RFR1_RFF1);
            break;
        case CAN_INT_RFO1:
            /* Check CAN_RFR1_RFO1 bit */
            intstate = CheckINTState(CANx->RFR1, CAN_RFR1_RFO1);
            break;
        case CAN_INT_WU:
            /* Check CAN_STR_WIF bit */
            intstate = CheckINTState(CANx->STR, CAN_STR_WIF);
            break;
        case CAN_INT_SLP:
            /* Check CAN_STR_SEIF bit */
            intstate = CheckINTState(CANx->STR, CAN_STR_SEIF);
            break;
        case CAN_INT_WE:
            /* Check CAN_INT_WE bit */
            intstate = CheckINTState(CANx->ER, CAN_ER_WE);
            break;
        case CAN_INT_PE:
            /* Check CAN_INT_EP bit */
            intstate = CheckINTState(CANx->ER, CAN_ER_PE);
            break;
        case CAN_INT_BOE:
            /* Check CAN_ER_BOE bit */
            intstate = CheckINTState(CANx->ER, CAN_ER_BOE);
            break;
        case CAN_INT_ET:
            /* Check CAN_ER_ET bit */
            intstate = CheckINTState(CANx->ER, CAN_ER_ET);
            break;
        case CAN_INT_ERR:
            /* Check CAN_STR_EIF bit */
            intstate = CheckINTState(CANx->STR, CAN_STR_EIF);
            break;
        default :
            /* in case of error, return RESET */
            intstate = RESET;
            break;
        }
    } else {
        /* in case the Interrupt is not enabled, return RESET */
        intstate  = RESET;
    }

    /* Return the CAN_INT status */
    return  intstate;
}

/**
  * @brief  Clear the CANx's interrupt pending bits.
  * @param  CANx: where x:[1,2] to to select the CAN peripheral.
  * @param  CAN_INT: specify the interrupt pending bit to clear.
  *   This parameter can be:
  *     @arg CAN_INT_TME
  *     @arg CAN_INT_RFF0
  *     @arg CAN_INT_RFO0
  *     @arg CAN_INT_RFF1
  *     @arg CAN_INT_RFO1
  *     @arg CAN_INT_WE
  *     @arg CAN_INT_PE
  *     @arg CAN_INT_BOE
  *     @arg CAN_INT_ET
  *     @arg CAN_INT_ERR
  *     @arg CAN_INT_WU
  *     @arg CAN_INT_SLP
  * @retval None.
  */
void CAN_ClearIntBitState(CAN_TypeDef *CANx, uint32_t CAN_INT)
{
    switch (CAN_INT) {
    case CAN_INT_TME:
        /* Clear CAN_TSTR_MTFx (rc_w1)*/
        CANx->TSTR = CAN_TSTR_MTF0 | CAN_TSTR_MTF1 | CAN_TSTR_MTF2;
        break;
    case CAN_INT_RFF0:
        /* Clear CAN_RFR0_RFF0 (rc_w1)*/
        CANx->RFR0 = CAN_RFR0_RFF0;
        break;
    case CAN_INT_RFO0:
        /* Clear CAN_RFR0_RFO0 (rc_w1)*/
        CANx->RFR0 = CAN_RFR0_RFO0;
        break;
    case CAN_INT_RFF1:
        /* Clear CAN_RFR1_RFF1 (rc_w1)*/
        CANx->RFR1 = CAN_RFR1_RFF1;
        break;
    case CAN_INT_RFO1:
        /* Clear CAN_RFR1_RFO1 (rc_w1)*/
        CANx->RFR1 = CAN_RFR1_RFO1;
        break;
    case CAN_INT_WU:
        /* Clear CAN_STR_WIF (rc_w1)*/
        CANx->STR = CAN_STR_WIF;
        break;
    case CAN_INT_SLP:
        /* Clear CAN_STR_SEIF (rc_w1)*/
        CANx->STR = CAN_STR_SEIF;
        break;
    case CAN_INT_WE:
        /* Clear CAN_STR_EIF (rc_w1) */
        CANx->STR = CAN_STR_EIF;
        break;
    case CAN_INT_PE:
        /* Clear CAN_MSR_ERRI (rc_w1) */
        CANx->STR = CAN_STR_EIF;
        break;
    case CAN_INT_BOE:
        /* Clear CAN_STR_EIF (rc_w1) */
        CANx->STR = CAN_STR_EIF;
        break;
    case CAN_INT_ET:
        /*  Clear ET bits */
        CANx->ER = RESET;
        /* Clear CAN_STR_EIF (rc_w1) */
        CANx->STR = CAN_STR_EIF;
        break;
    case CAN_INT_ERR:
        /*Clear ET bits */
        CANx->ER = RESET;
        /* Clear CAN_STR_EIF (rc_w1) */
        CANx->STR = CAN_STR_EIF;
        break;
    default :
        break;
    }
}

/**
  * @brief  Check whether the CAN interrupt has occurred or not.
  * @param  CAN_Reg: the register of CAN interrupt to check.
  * @param  Int_Bit: the bit of interrupt source to check.
  * @retval The new state of the CAN Interrupt (SET or RESET).
  */
static TypeState CheckINTState(uint32_t CAN_Reg, uint32_t Int_Bit)
{
    if ((CAN_Reg & Int_Bit) != (uint32_t)RESET) {
        /* CAN_INT is set */
        return SET;
    } else {
        /* CAN_IT is reset */
        return RESET;
    }
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
