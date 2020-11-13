/**
 **************************************************************************
 * File Name    : at32f4xx_can.c
 * Description  : at32f4xx CAN source file
 * Date         : 2018-02-26
 * Version      : V1.0.4
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_can.h"
#include "at32f4xx_rcc.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup CAN
  * @brief CAN driver modules
  * @{
  */

/** @defgroup CAN_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup CAN_Private_Defines
  * @{
  */

/* CAN Master Control Register bits */

#define MCR_DBF                     ((uint32_t)0x00010000) /* software master reset */

/* CAN Mailbox Transmit Request */
#define TMIDxR_TXRQ                 ((uint32_t)0x00000001) /* Transmit mailbox request */

/* CAN Filter Master Register bits */
#define FM_FINIT                    ((uint32_t)0x00000001) /* Filter init mode */

/* Time out for INAK bit */
#define IAK_TIMEOUT                 ((uint32_t)0x0000FFFF)
/* Time out for SLAK bit */
#define SAK_TIMEOUT                 ((uint32_t)0x0000FFFF)



/* Flags in TSR register */
#define CAN_FLAGS_TTST              ((uint32_t)0x08000000)
/* Flags in RF1R register */
#define CAN_FLAGS_RF1               ((uint32_t)0x04000000)
/* Flags in RF0R register */
#define CAN_FLAGS_RF0               ((uint32_t)0x02000000)
/* Flags in MSR register */
#define CAN_FLAGS_MSTS              ((uint32_t)0x01000000)
/* Flags in ESR register */
#define CAN_FLAGS_ESTS              ((uint32_t)0x00F00000)

/* Mailboxes definition */
#define CAN_TXMAILBOX_0             ((uint8_t)0x00)
#define CAN_TXMAILBOX_1             ((uint8_t)0x01)
#define CAN_TXMAILBOX_2             ((uint8_t)0x02)



#define CAN_MODE_MSK                ((uint32_t) 0x00000003)
/**
  * @}
  */

/** @defgroup CAN_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup CAN_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup CAN_Private_FunctionPrototypes
  * @{
  */

static ITStatus CheckINTStatus(uint32_t CAN_Reg, uint32_t It_Bit);

/**
  * @}
  */

/** @defgroup CAN_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the CAN peripheral registers to their default reset values.
  * @param  CANx: where x can be only 1 to select the CAN peripheral.
  * @retval None.
  */
void CAN_Reset(CAN_Type* CANx)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));

  if (CANx == CAN1)
  {
    /* Enable CAN1 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_CAN1, ENABLE);
    /* Release CAN1 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_CAN1, DISABLE);
  }
#ifdef AT32F413xx
#ifndef AT32FEBKCx_MD
  if (CANx == CAN2)
  {
    /* Enable CAN1 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_CAN2, ENABLE);
    /* Release CAN1 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_CAN2, DISABLE);
  }
#endif
#endif
}

/**
  * @brief  Initializes the CAN peripheral according to the specified
  *         parameters in the CAN_InitStruct.
  * @param  CANx:           where x can be only 1 to to select the CAN
  *                         peripheral.
  * @param  CAN_InitStruct: pointer to a CAN_InitType structure that
  *                         contains the configuration information for the
  *                         CAN peripheral.
  * @retval Constant indicates initialization succeed which will be
  *         CAN_InitStatus_Failed or CAN_InitStatus_Success.
  */
uint8_t CAN_Init(CAN_Type* CANx, CAN_InitType* CAN_InitStruct)
{
  uint8_t InitStatus = CAN_InitStatus_Failed;
  uint32_t wait_ack = 0x00000000;
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_TTC));
  assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_ABO));
  assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_AWU));
  assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_NART));
  assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_RFL));
  assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_TFP));
  assert_param(IS_CAN_MODE(CAN_InitStruct->CAN_Mode));
  assert_param(IS_CAN_SJW(CAN_InitStruct->CAN_SJW));
  assert_param(IS_CAN_BS1(CAN_InitStruct->CAN_BS1));
  assert_param(IS_CAN_BS2(CAN_InitStruct->CAN_BS2));
  assert_param(IS_CAN_PRESCALER(CAN_InitStruct->CAN_Prescaler));

  /* Exit from sleep mode */
  CANx->MCTRL &= (~(uint32_t)CAN_MCTRL_SLP);

  /* Request initialisation */
  CANx->MCTRL |= CAN_MCTRL_INRQ ;

  /* Wait the acknowledge */
  while (((CANx->MSTS & CAN_MSTS_IAK) != CAN_MSTS_IAK) && (wait_ack != IAK_TIMEOUT))
  {
    wait_ack++;
  }

  /* Check acknowledge */
  if ((CANx->MSTS & CAN_MSTS_IAK) != CAN_MSTS_IAK)
  {
    InitStatus = CAN_InitStatus_Failed;
  }
  else
  {
    /* Set the time triggered communication mode */
    if (CAN_InitStruct->CAN_TTC == ENABLE)
    {
      CANx->MCTRL |= CAN_MCTRL_TTC;
    }
    else
    {
      CANx->MCTRL &= ~(uint32_t)CAN_MCTRL_TTC;
    }

    /* Set the automatic bus-off management */
    if (CAN_InitStruct->CAN_ABO == ENABLE)
    {
      CANx->MCTRL |= CAN_MCTRL_ABO;
    }
    else
    {
      CANx->MCTRL &= ~(uint32_t)CAN_MCTRL_ABO;
    }

    /* Set the automatic wake-up mode */
    if (CAN_InitStruct->CAN_AWU == ENABLE)
    {
      CANx->MCTRL |= CAN_MCTRL_AWU;
    }
    else
    {
      CANx->MCTRL &= ~(uint32_t)CAN_MCTRL_AWU;
    }

    /* Set the no automatic retransmission */
    if (CAN_InitStruct->CAN_NART == ENABLE)
    {
      CANx->MCTRL |= CAN_MCTRL_NART;
    }
    else
    {
      CANx->MCTRL &= ~(uint32_t)CAN_MCTRL_NART;
    }

    /* Set the receive FIFO locked mode */
    if (CAN_InitStruct->CAN_RFL == ENABLE)
    {
      CANx->MCTRL |= CAN_MCTRL_RFL;
    }
    else
    {
      CANx->MCTRL &= ~(uint32_t)CAN_MCTRL_RFL;
    }

    /* Set the transmit FIFO priority */
    if (CAN_InitStruct->CAN_TFP == ENABLE)
    {
      CANx->MCTRL |= CAN_MCTRL_TFP;
    }
    else
    {
      CANx->MCTRL &= ~(uint32_t)CAN_MCTRL_TFP;
    }

    /* Set the bit timing register */
    CANx->BTMG = (uint32_t)((uint32_t)CAN_InitStruct->CAN_Mode << 30) | \
                 ((uint32_t)CAN_InitStruct->CAN_SJW << 24) | \
                 ((uint32_t)CAN_InitStruct->CAN_BS1 << 16) | \
                 ((uint32_t)CAN_InitStruct->CAN_BS2 << 20) | \
                 ((uint32_t)CAN_InitStruct->CAN_Prescaler - 1);

    /* Request leave initialisation */
    CANx->MCTRL &= ~(uint32_t)CAN_MCTRL_INRQ;

    /* Wait the acknowledge */
    wait_ack = 0;

    while (((CANx->MSTS & CAN_MSTS_IAK) == CAN_MSTS_IAK) && (wait_ack != IAK_TIMEOUT))
    {
      wait_ack++;
    }

    /* ...and check acknowledged */
    if ((CANx->MSTS & CAN_MSTS_IAK) == CAN_MSTS_IAK)
    {
      InitStatus = CAN_InitStatus_Failed;
    }
    else
    {
      InitStatus = CAN_InitStatus_Success ;
    }
  }

  /* At this step, return the status of initialization */
  return InitStatus;
}

/**
  * @brief  Initializes the CAN peripheral according to the specified
  *         parameters in the CAN_FilterInitStruct.
  * @param  CANx:           where x can be only 1 to to select the CAN
  *                         peripheral.
  * @param  CAN_FilterInitStruct: pointer to a CAN_FilterInitType
  *                               structure that contains the configuration
  *                               information.
  * @retval None.
  */
void CAN_FilterInit(CAN_Type* CANx, CAN_FilterInitType* CAN_FilterInitStruct)
{
  uint32_t filter_number_bit_pos = 0;
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_FILTER_NUMBER(CAN_FilterInitStruct->CAN_FilterNumber));
  assert_param(IS_CAN_FILTER_MODE(CAN_FilterInitStruct->CAN_FilterMode));
  assert_param(IS_CAN_FILTER_SCALE(CAN_FilterInitStruct->CAN_FilterScale));
  assert_param(IS_CAN_FILTER_FIFO(CAN_FilterInitStruct->CAN_FilterFIFOAssignment));
  assert_param(IS_FUNCTIONAL_STATE(CAN_FilterInitStruct->CAN_FilterActivation));

  filter_number_bit_pos = ((uint32_t)1) << CAN_FilterInitStruct->CAN_FilterNumber;

  /* Initialisation mode for the filter */
  CANx->FM |= FM_FINIT;

  /* Filter Deactivation */
  CANx->FA1 &= ~(uint32_t)filter_number_bit_pos;

  /* Filter Scale */
  if (CAN_FilterInitStruct->CAN_FilterScale == CAN_FilterScale_16bit)
  {
    /* 16-bit scale for the filter */
    CANx->FS1 &= ~(uint32_t)filter_number_bit_pos;

    /* First 16-bit identifier and First 16-bit mask */
    /* Or First 16-bit identifier and Second 16-bit identifier */
    CANx->FilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FBR1 =
      ((0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterMskIdLow) << 16) |
      (0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterIdLow);

    /* Second 16-bit identifier and Second 16-bit mask */
    /* Or Third 16-bit identifier and Fourth 16-bit identifier */
    CANx->FilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FBR2 =
      ((0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterMskIdHigh) << 16) |
      (0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterIdHigh);
  }

  if (CAN_FilterInitStruct->CAN_FilterScale == CAN_FilterScale_32bit)
  {
    /* 32-bit scale for the filter */
    CANx->FS1 |= filter_number_bit_pos;
    /* 32-bit identifier or First 32-bit identifier */
    CANx->FilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FBR1 =
      ((0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterIdHigh) << 16) |
      (0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterIdLow);
    /* 32-bit mask or Second 32-bit identifier */
    CANx->FilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FBR2 =
      ((0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterMskIdHigh) << 16) |
      (0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterMskIdLow);
  }

  /* Filter Mode */
  if (CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdMask)
  {
    /*Id/Mask mode for the filter*/
    CANx->FM1 &= ~(uint32_t)filter_number_bit_pos;
  }
  else /* CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdList */
  {
    /*Identifier list mode for the filter*/
    CANx->FM1 |= (uint32_t)filter_number_bit_pos;
  }

  /* Filter FIFO assignment */
  if (CAN_FilterInitStruct->CAN_FilterFIFOAssignment == CAN_Filter_FIFO0)
  {
    /* FIFO 0 assignation for the filter */
    CANx->FFA1 &= ~(uint32_t)filter_number_bit_pos;
  }

  if (CAN_FilterInitStruct->CAN_FilterFIFOAssignment == CAN_Filter_FIFO1)
  {
    /* FIFO 1 assignation for the filter */
    CANx->FFA1 |= (uint32_t)filter_number_bit_pos;
  }

  /* Filter activation */
  if (CAN_FilterInitStruct->CAN_FilterActivation == ENABLE)
  {
    CANx->FA1 |= filter_number_bit_pos;
  }

  /* Leave the initialisation mode for the filter */
  CANx->FM &= ~FM_FINIT;
}

/**
  * @brief  Fills each CAN_InitStruct member with its default value.
  * @param  CAN_InitStruct: pointer to a CAN_InitType structure which
  *                         will be initialized.
  * @retval None.
  */
void CAN_StructInit(CAN_InitType* CAN_InitStruct)
{
  /* Reset CAN init structure parameters values */

  /* Initialize the time triggered communication mode */
  CAN_InitStruct->CAN_TTC = DISABLE;

  /* Initialize the automatic bus-off management */
  CAN_InitStruct->CAN_ABO = DISABLE;

  /* Initialize the automatic wake-up mode */
  CAN_InitStruct->CAN_AWU = DISABLE;

  /* Initialize the no automatic retransmission */
  CAN_InitStruct->CAN_NART = DISABLE;

  /* Initialize the receive FIFO locked mode */
  CAN_InitStruct->CAN_RFL = DISABLE;

  /* Initialize the transmit FIFO priority */
  CAN_InitStruct->CAN_TFP = DISABLE;

  /* Initialize the CAN_Mode member */
  CAN_InitStruct->CAN_Mode = CAN_Mode_Normal;

  /* Initialize the CAN_SJW member */
  CAN_InitStruct->CAN_SJW = CAN_SJW_1tq;

  /* Initialize the CAN_BS1 member */
  CAN_InitStruct->CAN_BS1 = CAN_BS1_4tq;

  /* Initialize the CAN_BS2 member */
  CAN_InitStruct->CAN_BS2 = CAN_BS2_3tq;

  /* Initialize the CAN_Prescaler member */
  CAN_InitStruct->CAN_Prescaler = 1;
}

/**
  * @brief  Select the start bank filter for slave CAN.
  * @note   None.
  * @param  CAN_BankNumber: Select the start slave bank filter from 1..27.
  * @retval None.
  */
void CAN_SlaveStartBank(uint8_t CAN_BankNumber)
{
  /* Check the parameters */
  assert_param(IS_CAN_BANKNUMBER(CAN_BankNumber));

  /* Enter Initialisation mode for the filter */
  CAN1->FM |= FM_FINIT;

  /* Select the start slave bank */
  CAN1->FM &= (uint32_t)0xFFFFC0F1 ;
  CAN1->FM |= (uint32_t)(CAN_BankNumber) << 8;

  /* Leave Initialisation mode for the filter */
  CAN1->FM &= ~FM_FINIT;
}

/**
  * @brief  Enables or disables the DBG Freeze for CAN.
  * @param  CANx:     where x can be only 1 to to select the CAN peripheral.
  * @param  NewState: new state of the CAN peripheral. This parameter can
  *                   be: ENABLE or DISABLE.
  * @retval None.
  */
void CAN_DBGFreeze(CAN_Type* CANx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable Debug Freeze  */
    CANx->MCTRL |= MCR_DBF;
  }
  else
  {
    /* Disable Debug Freeze */
    CANx->MCTRL &= ~MCR_DBF;
  }
}


/**
  * @brief  Enables or disabes the CAN Time TriggerOperation communication mode.
  * @param  CANx:      where x can be only 1 to to select the CAN peripheral.
  * @param  NewState : Mode new state , can be one of @ref FunctionalState.
  * @note   when enabled, Time stamp (TIME[15:0]) value is sent in the last
  *         two data bytes of the 8-byte message: TIME[7:0] in data byte 6
  *         and TIME[15:8] in data byte 7
  * @note   DLC must be programmed as 8 in order Time Stamp (2 bytes) to be
  *         sent over the CAN bus.
  * @retval None
  */
void CAN_TTComModeCtrl(CAN_Type* CANx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the TTCM mode */
    CANx->MCTRL |= CAN_MCTRL_TTC;

    /* Set TGT bits */
    CANx->TxMailBox[0].TDT |= ((uint32_t)CAN_TDT0_TMEN);
    CANx->TxMailBox[1].TDT |= ((uint32_t)CAN_TDT1_TMEN);
    CANx->TxMailBox[2].TDT |= ((uint32_t)CAN_TDT2_TMEN);
  }
  else
  {
    /* Disable the TTCM mode */
    CANx->MCTRL &= (uint32_t)(~(uint32_t)CAN_MCTRL_TTC);

    /* Reset TGT bits */
    CANx->TxMailBox[0].TDT &= ((uint32_t)~CAN_TDT0_TMEN);
    CANx->TxMailBox[1].TDT &= ((uint32_t)~CAN_TDT1_TMEN);
    CANx->TxMailBox[2].TDT &= ((uint32_t)~CAN_TDT2_TMEN);
  }
}
/**
  * @brief  Initiates the transmission of a message.
  * @param  CANx:      where x can be only 1 to to select the CAN peripheral.
  * @param  TxMessage: pointer to a structure which contains CAN Id, CAN
  *                    DLC and CAN data.
  * @retval The number of the mailbox that is used for transmission
  *                    or CAN_TxStatus_NoMailBox if there is no empty mailbox.
  */
uint8_t CAN_Transmit(CAN_Type* CANx, CanTxMsg* TxMessage)
{
  uint8_t transmit_mailbox = 0;
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_IDTYPE(TxMessage->IDT));
  assert_param(IS_CAN_RTR(TxMessage->RTR));
  assert_param(IS_CAN_DLC(TxMessage->DLC));

  /* Select one empty transmit mailbox */
  if ((CANx->TSTS & CAN_TSTS_TSME0) == CAN_TSTS_TSME0)
  {
    transmit_mailbox = 0;
  }
  else if ((CANx->TSTS & CAN_TSTS_TSME1) == CAN_TSTS_TSME1)
  {
    transmit_mailbox = 1;
  }
  else if ((CANx->TSTS & CAN_TSTS_TSME2) == CAN_TSTS_TSME2)
  {
    transmit_mailbox = 2;
  }
  else
  {
    transmit_mailbox = CAN_TxStatus_NoMailBox;
  }

  if (transmit_mailbox != CAN_TxStatus_NoMailBox)
  {
    /* Set up the Id */
    CANx->TxMailBox[transmit_mailbox].TMI &= TMIDxR_TXRQ;

    if (TxMessage->IDT == CAN_Id_Standard)
    {
      assert_param(IS_CAN_STDID(TxMessage->StdId));
      CANx->TxMailBox[transmit_mailbox].TMI |= ((TxMessage->StdId << 21) | \
          TxMessage->RTR);
    }
    else
    {
      assert_param(IS_CAN_EXTID(TxMessage->ExtId));
      CANx->TxMailBox[transmit_mailbox].TMI |= ((TxMessage->ExtId << 3) | \
          TxMessage->IDT | \
          TxMessage->RTR);
    }

    /* Set up the DLC */
    TxMessage->DLC &= (uint8_t)0x0000000F;
    CANx->TxMailBox[transmit_mailbox].TDT &= (uint32_t)0xFFFFFFF0;
    CANx->TxMailBox[transmit_mailbox].TDT |= TxMessage->DLC;

    /* Set up the data field */
    CANx->TxMailBox[transmit_mailbox].TDL = (((uint32_t)TxMessage->Data[3] << 24) |
                                            ((uint32_t)TxMessage->Data[2] << 16) |
                                            ((uint32_t)TxMessage->Data[1] << 8) |
                                            ((uint32_t)TxMessage->Data[0]));
    CANx->TxMailBox[transmit_mailbox].TDH = (((uint32_t)TxMessage->Data[7] << 24) |
                                            ((uint32_t)TxMessage->Data[6] << 16) |
                                            ((uint32_t)TxMessage->Data[5] << 8) |
                                            ((uint32_t)TxMessage->Data[4]));
    /* Request transmission */
    CANx->TxMailBox[transmit_mailbox].TMI |= TMIDxR_TXRQ;
  }

  return transmit_mailbox;
}

/**
  * @brief  Checks the transmission of a message.
  * @param  CANx:            where x can be only 1 to to select the
  *                          CAN peripheral.
  * @param  TransmitMailbox: the number of the mailbox that is used for
  *                          transmission.
  * @retval CAN_TxStatus_Ok if the CAN driver transmits the message, CAN_TxStatus_Failed
  *         in an other case.
  */
uint8_t CAN_TransmitStatus(CAN_Type* CANx, uint8_t TransmitMailbox)
{
  uint32_t state = 0;

  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_TRANSMITMAILBOX(TransmitMailbox));

  switch (TransmitMailbox)
  {
  case (CAN_TXMAILBOX_0):
    state =   CANx->TSTS &  (CAN_TSTS_RQC0 | CAN_TSTS_TOK0 | CAN_TSTS_TSME0);
    break;

  case (CAN_TXMAILBOX_1):
    state =   CANx->TSTS &  (CAN_TSTS_RQC1 | CAN_TSTS_TOK1 | CAN_TSTS_TSME1);
    break;

  case (CAN_TXMAILBOX_2):
    state =   CANx->TSTS &  (CAN_TSTS_RQC2 | CAN_TSTS_TOK2 | CAN_TSTS_TSME2);
    break;

  default:
    state = CAN_TxStatus_Failed;
    break;
  }

  switch (state)
  {
    /* transmit pending  */
  case (0x0):
    state = CAN_TxStatus_Pending;
    break;

    /* transmit failed  */
  case (CAN_TSTS_RQC0 | CAN_TSTS_TSME0):
    state = CAN_TxStatus_Failed;
    break;

  case (CAN_TSTS_RQC1 | CAN_TSTS_TSME1):
    state = CAN_TxStatus_Failed;
    break;

  case (CAN_TSTS_RQC2 | CAN_TSTS_TSME2):
    state = CAN_TxStatus_Failed;
    break;

    /* transmit succeeded  */
  case (CAN_TSTS_RQC0 | CAN_TSTS_TOK0 | CAN_TSTS_TSME0):
    state = CAN_TxStatus_Ok;
    break;

  case (CAN_TSTS_RQC1 | CAN_TSTS_TOK1 | CAN_TSTS_TSME1):
    state = CAN_TxStatus_Ok;
    break;

  case (CAN_TSTS_RQC2 | CAN_TSTS_TOK2 | CAN_TSTS_TSME2):
    state = CAN_TxStatus_Ok;
    break;

  default:
    state = CAN_TxStatus_Failed;
    break;
  }

  return (uint8_t) state;
}

/**
  * @brief  Cancels a transmit request.
  * @param  CANx:     where x can be only 1 to to select the CAN peripheral.
  * @param  Mailbox:  Mailbox number.
  * @retval None.
  */
void CAN_CancelTransmit(CAN_Type* CANx, uint8_t Mailbox)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_TRANSMITMAILBOX(Mailbox));

  /* abort transmission */
  switch (Mailbox)
  {
  case (CAN_TXMAILBOX_0):
    CANx->TSTS |= CAN_TSTS_ARQ0;
    break;

  case (CAN_TXMAILBOX_1):
    CANx->TSTS |= CAN_TSTS_ARQ1;
    break;

  case (CAN_TXMAILBOX_2):
    CANx->TSTS |= CAN_TSTS_ARQ2;
    break;

  default:
    break;
  }
}


/**
  * @brief  Receives a message.
  * @param  CANx:       where x can be only 1 to to select the CAN peripheral.
  * @param  FIFONumber: Receive FIFO number, CAN_FIFO0 or CAN_FIFO1.
  * @param  RxMessage:  pointer to a structure receive message which contains
  *                     CAN Id, CAN DLC, CAN datas and FMI number.
  * @retval None.
  */
void CAN_Receive(CAN_Type* CANx, uint8_t FIFONumber, CanRxMsg* RxMessage)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_FIFO(FIFONumber));
  /* Get the Id */
  RxMessage->IDT = (uint8_t)0x04 & CANx->FIFOMailBox[FIFONumber].RFI;

  if (RxMessage->IDT == CAN_Id_Standard)
  {
    RxMessage->StdId = (uint32_t)0x000007FF & (CANx->FIFOMailBox[FIFONumber].RFI >> 21);
  }
  else
  {
    RxMessage->ExtId = (uint32_t)0x1FFFFFFF & (CANx->FIFOMailBox[FIFONumber].RFI >> 3);
  }

  RxMessage->RTR = (uint8_t)0x02 & CANx->FIFOMailBox[FIFONumber].RFI;
  /* Get the DLC */
  RxMessage->DLC = (uint8_t)0x0F & CANx->FIFOMailBox[FIFONumber].RDT;
  /* Get the FMI */
  RxMessage->FID = (uint8_t)0xFF & (CANx->FIFOMailBox[FIFONumber].RDT >> 8);
  /* Get the data field */
  RxMessage->Data[0] = (uint8_t)0xFF & CANx->FIFOMailBox[FIFONumber].RDL;
  RxMessage->Data[1] = (uint8_t)0xFF & (CANx->FIFOMailBox[FIFONumber].RDL >> 8);
  RxMessage->Data[2] = (uint8_t)0xFF & (CANx->FIFOMailBox[FIFONumber].RDL >> 16);
  RxMessage->Data[3] = (uint8_t)0xFF & (CANx->FIFOMailBox[FIFONumber].RDL >> 24);
  RxMessage->Data[4] = (uint8_t)0xFF & CANx->FIFOMailBox[FIFONumber].RDH;
  RxMessage->Data[5] = (uint8_t)0xFF & (CANx->FIFOMailBox[FIFONumber].RDH >> 8);
  RxMessage->Data[6] = (uint8_t)0xFF & (CANx->FIFOMailBox[FIFONumber].RDH >> 16);
  RxMessage->Data[7] = (uint8_t)0xFF & (CANx->FIFOMailBox[FIFONumber].RDH >> 24);

  /* Release the FIFO */
  /* Release FIFO0 */
  if (FIFONumber == CAN_FIFO0)
  {
    CANx->RF0 |= CAN_RF0_RRFM0;
  }
  /* Release FIFO1 */
  else /* FIFONumber == CAN_FIFO1 */
  {
    CANx->RF1 |= CAN_RF1_RRFM1;
  }
}

/**
  * @brief  Releases the specified FIFO.
  * @param  CANx:       where x can be only 1 to to select the CAN peripheral.
  * @param  FIFONumber: FIFO to release, CAN_FIFO0 or CAN_FIFO1.
  * @retval None.
  */
void CAN_FIFORelease(CAN_Type* CANx, uint8_t FIFONumber)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_FIFO(FIFONumber));

  /* Release FIFO0 */
  if (FIFONumber == CAN_FIFO0)
  {
    CANx->RF0 |= CAN_RF0_RRFM0;
  }
  /* Release FIFO1 */
  else /* FIFONumber == CAN_FIFO1 */
  {
    CANx->RF1 |= CAN_RF1_RRFM1;
  }
}

/**
  * @brief  Returns the number of pending messages.
  * @param  CANx:       where x can be only 1 to to select the CAN peripheral.
  * @param  FIFONumber: Receive FIFO number, CAN_FIFO0 or CAN_FIFO1.
  * @retval NbMessage : which is the number of pending message.
  */
uint8_t CAN_MessagePending(CAN_Type* CANx, uint8_t FIFONumber)
{
  uint8_t message_pending = 0;
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_FIFO(FIFONumber));

  if (FIFONumber == CAN_FIFO0)
  {
    message_pending = (uint8_t)(CANx->RF0 & (uint32_t)0x03);
  }
  else if (FIFONumber == CAN_FIFO1)
  {
    message_pending = (uint8_t)(CANx->RF1 & (uint32_t)0x03);
  }
  else
  {
    message_pending = 0;
  }

  return message_pending;
}


/**
  * @brief   Select the CAN Operation mode.
  * @param CAN_OperatingMode : CAN Operating Mode. This parameter can be one
  *                            of @ref CAN_Operating_Mode enumeration.
  * @retval status of the requested mode which can be
  *         - CAN_ModeStatus_Failed    CAN failed entering the specific mode
  *         - CAN_ModeStatus_Success   CAN Succeed entering the specific mode

  */
uint8_t CAN_OperatingModeRequest(CAN_Type* CANx, uint8_t CAN_OperatingMode)
{
  uint8_t status = CAN_ModeStatus_Failed;

  /* Timeout for INAK or also for SLAK bits*/
  uint32_t timeout = IAK_TIMEOUT;

  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_OPERATING_MODE(CAN_OperatingMode));

  if (CAN_OperatingMode == CAN_OperatingMode_Initialization)
  {
    /* Request initialisation */
    CANx->MCTRL = (uint32_t)((CANx->MCTRL & (uint32_t)(~(uint32_t)CAN_MCTRL_SLP)) | CAN_MCTRL_INRQ);

    /* Wait the acknowledge */
    while (((CANx->MSTS & CAN_MODE_MSK) != CAN_MSTS_IAK) && (timeout != 0))
    {
      timeout--;
    }

    if ((CANx->MSTS & CAN_MODE_MSK) != CAN_MSTS_IAK)
    {
      status = CAN_ModeStatus_Failed;
    }
    else
    {
      status = CAN_ModeStatus_Success;
    }
  }
  else  if (CAN_OperatingMode == CAN_OperatingMode_Normal)
  {
    /* Request leave initialisation and sleep mode  and enter Normal mode */
    CANx->MCTRL &= (uint32_t)(~(CAN_MCTRL_SLP | CAN_MCTRL_INRQ));

    /* Wait the acknowledge */
    while (((CANx->MSTS & CAN_MODE_MSK) != 0) && (timeout != 0))
    {
      timeout--;
    }

    if ((CANx->MSTS & CAN_MODE_MSK) != 0)
    {
      status = CAN_ModeStatus_Failed;
    }
    else
    {
      status = CAN_ModeStatus_Success;
    }
  }
  else  if (CAN_OperatingMode == CAN_OperatingMode_Sleep)
  {
    /* Request Sleep mode */
    CANx->MCTRL = (uint32_t)((CANx->MCTRL & (uint32_t)(~(uint32_t)CAN_MCTRL_INRQ)) | CAN_MCTRL_SLP);

    /* Wait the acknowledge */
    while (((CANx->MSTS & CAN_MODE_MSK) != CAN_MSTS_SAK) && (timeout != 0))
    {
      timeout--;
    }

    if ((CANx->MSTS & CAN_MODE_MSK) != CAN_MSTS_SAK)
    {
      status = CAN_ModeStatus_Failed;
    }
    else
    {
      status = CAN_ModeStatus_Success;
    }
  }
  else
  {
    status = CAN_ModeStatus_Failed;
  }

  return  (uint8_t) status;
}

/**
  * @brief  Enters the low power mode.
  * @param  CANx:   where x can be only 1 to to select the CAN peripheral.
  * @retval status: CAN_Sleep_Ok if sleep entered, CAN_Sleep_Failed in an
  *                 other case.
  */
uint8_t CAN_Sleep(CAN_Type* CANx)
{
  uint8_t sleepstatus = CAN_Sleep_Failed;

  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));

  /* Request Sleep mode */
  CANx->MCTRL = (((CANx->MCTRL) & (uint32_t)(~(uint32_t)CAN_MCTRL_INRQ)) | CAN_MCTRL_SLP);

  /* Sleep mode status */
  if ((CANx->MSTS & (CAN_MSTS_SAK | CAN_MSTS_IAK)) == CAN_MSTS_SAK)
  {
    /* Sleep mode not entered */
    sleepstatus =  CAN_Sleep_Ok;
  }

  /* return sleep mode status */
  return (uint8_t)sleepstatus;
}

/**
  * @brief  Wakes the CAN up.
  * @param  CANx:    where x can be only 1 to to select the CAN peripheral.
  * @retval status:  CAN_WakeUp_Ok if sleep mode left, CAN_WakeUp_Failed in an
  *                  other case.
  */
uint8_t CAN_WakeUp(CAN_Type* CANx)
{
  uint32_t wait_slak = SAK_TIMEOUT;
  uint8_t wakeupstatus = CAN_WakeUp_Failed;

  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));

  /* Wake up request */
  CANx->MCTRL &= ~(uint32_t)CAN_MCTRL_SLP;

  /* Sleep mode status */
  while(((CANx->MSTS & CAN_MSTS_SAK) == CAN_MSTS_SAK) && (wait_slak != 0x00))
  {
    wait_slak--;
  }

  if((CANx->MSTS & CAN_MSTS_SAK) != CAN_MSTS_SAK)
  {
    /* wake up done : Sleep mode exited */
    wakeupstatus = CAN_WakeUp_Ok;
  }

  /* return wakeup status */
  return (uint8_t)wakeupstatus;
}


/**
  * @brief  Returns the CANx's last error code (LEC).
  * @param  CANx:          where x can be only 1 to to select the CAN peripheral.
  * @retval CAN_ErrorCode: specifies the Error code :
  *                        - CAN_ErrorCode_NoErr            No Error
  *                        - CAN_ErrorCode_StuffErr         Stuff Error
  *                        - CAN_ErrorCode_FormErr          Form Error
  *                        - CAN_ErrorCode_ACKErr           Acknowledgment Error
  *                        - CAN_ErrorCode_BitRecessiveErr  Bit Recessive Error
  *                        - CAN_ErrorCode_BitDominantErr   Bit Dominant Error
  *                        - CAN_ErrorCode_CRCErr           CRC Error
  *                        - CAN_ErrorCode_SoftwareSetErr   Software Set Error
  */

uint8_t CAN_GetLastErrorCode(CAN_Type* CANx)
{
  uint8_t errorcode = 0;

  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));

  /* Get the error code*/
  errorcode = (((uint8_t)CANx->ESTS) & (uint8_t)CAN_ESTS_ERC);

  /* Return the error code*/
  return errorcode;
}
/**
  * @brief  Returns the CANx Receive Error Counter (REC).
  * @note   In case of an error during reception, this counter is incremented
  *         by 1 or by 8 depending on the error condition as defined by the CAN
  *         standard. After every successful reception, the counter is
  *         decremented by 1 or reset to 120 if its value was higher than 128.
  *         When the counter value exceeds 127, the CAN controller enters the
  *         error passive state.
  * @param  CANx: where x can be only 1 to to select the CAN peripheral.
  * @retval CAN Receive Error Counter.
  */
uint8_t CAN_GetReceiveErrorCounter(CAN_Type* CANx)
{
  uint8_t counter = 0;

  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));

  /* Get the Receive Error Counter*/
  counter = (uint8_t)((CANx->ESTS & CAN_ESTS_REC) >> 24);

  /* Return the Receive Error Counter*/
  return counter;
}


/**
  * @brief  Returns the LSB of the 9-bit CANx Transmit Error Counter(TEC).
  * @param  CANx:   where x can be only 1 to to select the CAN peripheral.
  * @retval LSB of the 9-bit CAN Transmit Error Counter.
  */
uint8_t CAN_GetLSBTransmitErrorCounter(CAN_Type* CANx)
{
  uint8_t counter = 0;

  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));

  /* Get the LSB of the 9-bit CANx Transmit Error Counter(TEC) */
  counter = (uint8_t)((CANx->ESTS & CAN_ESTS_TEC) >> 16);

  /* Return the LSB of the 9-bit CANx Transmit Error Counter(TEC) */
  return counter;
}


/**
  * @brief  Enables or disables the specified CANx interrupts.
  * @param  CANx:   where x can be only 1 to to select the CAN peripheral.
  * @param  CAN_INT: specifies the CAN interrupt sources to be enabled or disabled.
  *                 This parameter can be:
  *                 - CAN_INT_TSME,
  *                 - CAN_INT_RFP0,
  *                 - CAN_INT_RFFU0,
  *                 - CAN_INT_RFOV0,
  *                 - CAN_INT_RFP1,
  *                 - CAN_INT_RFFU1,
  *                 - CAN_INT_RFOV1,
  *                 - CAN_INT_ERG,
  *                 - CAN_INT_ERP,
  *                 - CAN_INT_LEC,
  *                 - CAN_INT_ERR,
  *                 - CAN_INT_WK or
  *                 - CAN_INT_SAK.
  * @param  NewState: new state of the CAN interrupts.
  *                   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void CAN_INTConfig(CAN_Type* CANx, uint32_t CAN_INT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_INT(CAN_INT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected CANx interrupt */
    CANx->INTEN |= CAN_INT;
  }
  else
  {
    /* Disable the selected CANx interrupt */
    CANx->INTEN &= ~CAN_INT;
  }
}
/**
  * @brief  Checks whether the specified CAN flag is set or not.
  * @param  CANx:     where x can be only 1 to to select the CAN peripheral.
  * @param  CAN_FLAG: specifies the flag to check.
  *                   This parameter can be one of the following flags:
  *                  - CAN_FLAG_ERG
  *                  - CAN_FLAG_ERP
  *                  - CAN_FLAG_BU
  *                  - CAN_FLAG_RQCP0
  *                  - CAN_FLAG_RQCP1
  *                  - CAN_FLAG_RQCP2
  *                  - CAN_FLAG_RFP1
  *                  - CAN_FLAG_RFFU1
  *                  - CAN_FLAG_RFOV1
  *                  - CAN_FLAG_RFP0
  *                  - CAN_FLAG_RFFU0
  *                  - CAN_FLAG_RFOV0
  *                  - CAN_FLAG_WK
  *                  - CAN_FLAG_SAK
  *                  - CAN_FLAG_ERC
  * @retval The new state of CAN_FLAG (SET or RESET).
  */
FlagStatus CAN_GetFlagStatus(CAN_Type* CANx, uint32_t CAN_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_GET_FLAG(CAN_FLAG));


  if((CAN_FLAG & CAN_FLAGS_ESTS) != (uint32_t)RESET)
  {
    /* Check the status of the specified CAN flag */
    if ((CANx->ESTS & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET)
    {
      /* CAN_FLAG is set */
      bitstatus = SET;
    }
    else
    {
      /* CAN_FLAG is reset */
      bitstatus = RESET;
    }
  }
  else if((CAN_FLAG & CAN_FLAGS_MSTS) != (uint32_t)RESET)
  {
    /* Check the status of the specified CAN flag */
    if ((CANx->MSTS & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET)
    {
      /* CAN_FLAG is set */
      bitstatus = SET;
    }
    else
    {
      /* CAN_FLAG is reset */
      bitstatus = RESET;
    }
  }
  else if((CAN_FLAG & CAN_FLAGS_TTST) != (uint32_t)RESET)
  {
    /* Check the status of the specified CAN flag */
    if ((CANx->TSTS & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET)
    {
      /* CAN_FLAG is set */
      bitstatus = SET;
    }
    else
    {
      /* CAN_FLAG is reset */
      bitstatus = RESET;
    }
  }
  else if((CAN_FLAG & CAN_FLAGS_RF0) != (uint32_t)RESET)
  {
    /* Check the status of the specified CAN flag */
    if ((CANx->RF0 & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET)
    {
      /* CAN_FLAG is set */
      bitstatus = SET;
    }
    else
    {
      /* CAN_FLAG is reset */
      bitstatus = RESET;
    }
  }
  else /* If(CAN_FLAG & CAN_FLAGS_RF1 != (uint32_t)RESET) */
  {
    /* Check the status of the specified CAN flag */
    if ((uint32_t)(CANx->RF1 & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET)
    {
      /* CAN_FLAG is set */
      bitstatus = SET;
    }
    else
    {
      /* CAN_FLAG is reset */
      bitstatus = RESET;
    }
  }

  /* Return the CAN_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clears the CAN's pending flags.
  * @param  CANx:     where x can be only 1 to to select the CAN peripheral.
  * @param  CAN_FLAG: specifies the flag to clear.
  *                   This parameter can be one of the following flags:
  *                    - CAN_FLAG_RQCP0
  *                    - CAN_FLAG_RQCP1
  *                    - CAN_FLAG_RQCP2
  *                    - CAN_FLAG_RFFU1
  *                    - CAN_FLAG_RFOV1
  *                    - CAN_FLAG_RFFU0
  *                    - CAN_FLAG_RFOV0
  *                    - CAN_FLAG_WK
  *                    - CAN_FLAG_SAK
  *                    - CAN_FLAG_ERC
  * @retval None.
  */
void CAN_ClearFlag(CAN_Type* CANx, uint32_t CAN_FLAG)
{
  uint32_t flagtmp = 0;
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_CLEAR_FLAG(CAN_FLAG));

  if (CAN_FLAG == CAN_FLAG_ERC) /* ESR register */
  {
    /* Clear the selected CAN flags */
    CANx->ESTS = (uint32_t)RESET;
  }
  else /* MSR or TSR or RF0R or RF1R */
  {
    flagtmp = CAN_FLAG & 0x000FFFFF;

    if ((CAN_FLAG & CAN_FLAGS_RF0) != (uint32_t)RESET)
    {
      /* Receive Flags */
      CANx->RF0 = (uint32_t)(flagtmp);
    }
    else if ((CAN_FLAG & CAN_FLAGS_RF1) != (uint32_t)RESET)
    {
      /* Receive Flags */
      CANx->RF1 = (uint32_t)(flagtmp);
    }
    else if ((CAN_FLAG & CAN_FLAGS_TTST) != (uint32_t)RESET)
    {
      /* Transmit Flags */
      CANx->TSTS = (uint32_t)(flagtmp);
    }
    else /* If((CAN_FLAG & CAN_FLAGS_MSTS)!=(uint32_t)RESET) */
    {
      /* Operating mode Flags */
      CANx->MSTS = (uint32_t)(flagtmp);
    }
  }
}

/**
  * @brief  Checks whether the specified CANx interrupt has occurred or not.
  * @param  CANx:    where x can be only 1 to to select the CAN peripheral.
  * @param  CAN_INT:  specifies the CAN interrupt source to check.
  *                  This parameter can be one of the following flags:
  *                 -  CAN_INT_TSME
  *                 -  CAN_INT_RFP0
  *                 -  CAN_INT_RFFU0
  *                 -  CAN_INT_RFOV0
  *                 -  CAN_INT_RFP1
  *                 -  CAN_INT_RFFU1
  *                 -  CAN_INT_RFOV1
  *                 -  CAN_INT_WK
  *                 -  CAN_INT_SAK
  *                 -  CAN_INT_ERG
  *                 -  CAN_INT_ERP
  *                 -  CAN_INT_BU
  *                 -  CAN_INT_LEC
  *                 -  CAN_INT_ERR
  * @retval The current state of CAN_INT (SET or RESET).
  */
ITStatus CAN_GetINTStatus(CAN_Type* CANx, uint32_t CAN_INT)
{
  ITStatus itstatus = RESET;
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_INT(CAN_INT));

  /* check the enable interrupt bit */
  if((CANx->INTEN & CAN_INT) != RESET)
  {
    /* in case the Interrupt is enabled, .... */
    switch (CAN_INT)
    {
    case CAN_INT_TSME:
      /* Check CAN_TSR_RQCPx bits */
      itstatus = CheckINTStatus(CANx->TSTS, CAN_TSTS_RQC0 | CAN_TSTS_RQC1 | CAN_TSTS_RQC2);
      break;

    case CAN_INT_RFP0:
      /* Check CAN_RF0_RFP0 bit */
      itstatus = CheckINTStatus(CANx->RF0, CAN_RF0_RFP0);
      break;

    case CAN_INT_RFFU0:
      /* Check CAN_RF0_RFFU0 bit */
      itstatus = CheckINTStatus(CANx->RF0, CAN_RF0_RFFU0);
      break;

    case CAN_INT_RFOV0:
      /* Check CAN_RF0_RFOV0 bit */
      itstatus = CheckINTStatus(CANx->RF0, CAN_RF0_RFOV0);
      break;

    case CAN_INT_RFP1:
      /* Check CAN_RF1_RFP1 bit */
      itstatus = CheckINTStatus(CANx->RF1, CAN_RF1_RFP1);
      break;

    case CAN_INT_RFFU1:
      /* Check CAN_RF1_RFFU1 bit */
      itstatus = CheckINTStatus(CANx->RF1, CAN_RF1_RFFU1);
      break;

    case CAN_INT_RFOV1:
      /* Check CAN_RF1_RFOV1 bit */
      itstatus = CheckINTStatus(CANx->RF1, CAN_RF1_RFOV1);
      break;

    case CAN_INT_WK:
      /* Check CAN_MSTS_WKIT bit */
      itstatus = CheckINTStatus(CANx->MSTS, CAN_MSTS_WKIT);
      break;

    case CAN_INT_SAK:
      /* Check CAN_MSTS_SAKIT bit */
      itstatus = CheckINTStatus(CANx->MSTS, CAN_MSTS_SAKIT);
      break;

    case CAN_INT_ERG:
      /* Check CAN_ESTS_ERWF bit */
      itstatus = CheckINTStatus(CANx->ESTS, CAN_ESTS_ERWF);
      break;

    case CAN_INT_ERP:
      /* Check CAN_ESTS_ERPF bit */
      itstatus = CheckINTStatus(CANx->ESTS, CAN_ESTS_ERPF);
      break;

    case CAN_INT_BU:
      /* Check CAN_ESTS_BFF bit */
      itstatus = CheckINTStatus(CANx->ESTS, CAN_ESTS_BFF);
      break;

    case CAN_INT_LEC:
      /* Check CAN_ESTS_ERC bit */
      itstatus = CheckINTStatus(CANx->ESTS, CAN_ESTS_ERC);
      break;

    case CAN_INT_ERR:
      /* Check CAN_MSTS_ERIT bit */
      itstatus = CheckINTStatus(CANx->MSTS, CAN_MSTS_ERIT);
      break;

    default :
      /* in case of error, return RESET */
      itstatus = RESET;
      break;
    }
  }
  else
  {
    /* in case the Interrupt is not enabled, return RESET */
    itstatus  = RESET;
  }

  /* Return the CAN_INT status */
  return  itstatus;
}

/**
  * @brief  Clears the CANx's interrupt pending bits.
  * @param  CANx:    where x can be only 1 to to select the CAN peripheral.
  * @param  CAN_INT: specifies the interrupt pending bit to clear.
  *                  -  CAN_INT_TSME
  *                  -  CAN_INT_RFFU0
  *                  -  CAN_INT_RFOV0
  *                  -  CAN_INT_RFFU1
  *                  -  CAN_INT_RFOV1
  *                  -  CAN_INT_WK
  *                  -  CAN_INT_SAK
  *                  -  CAN_INT_ERG
  *                  -  CAN_INT_ERP
  *                  -  CAN_INT_BU
  *                  -  CAN_INT_LEC
  *                  -  CAN_INT_ERR
  * @retval None.
  */
void CAN_ClearINTPendingBit(CAN_Type* CANx, uint32_t CAN_INT)
{
  /* Check the parameters */
  assert_param(IS_CAN_ALL_PERIPH(CANx));
  assert_param(IS_CAN_CLEAR_INT(CAN_INT));

  switch (CAN_INT)
  {
  case CAN_INT_TSME:
    /* Clear CAN_TSR_RQCPx (rc_w1)*/
    CANx->TSTS = CAN_TSTS_RQC0 | CAN_TSTS_RQC1 | CAN_TSTS_RQC2;
    break;

  case CAN_INT_RFFU0:
    /* Clear CAN_RF0_RFFU0 (rc_w1)*/
    CANx->RF0 = CAN_RF0_RFFU0;
    break;

  case CAN_INT_RFOV0:
    /* Clear CAN_RF0_RFOV0 (rc_w1)*/
    CANx->RF0 = CAN_RF0_RFOV0;
    break;

  case CAN_INT_RFFU1:
    /* Clear CAN_RF1_RFFU1 (rc_w1)*/
    CANx->RF1 = CAN_RF1_RFFU1;
    break;

  case CAN_INT_RFOV1:
    /* Clear CAN_RF1_RFOV1 (rc_w1)*/
    CANx->RF1 = CAN_RF1_RFOV1;
    break;

  case CAN_INT_WK:
    /* Clear CAN_MSTS_WKIT (rc_w1)*/
    CANx->MSTS = CAN_MSTS_WKIT;
    break;

  case CAN_INT_SAK:
    /* Clear CAN_MSTS_SAKIT (rc_w1)*/
    CANx->MSTS = CAN_MSTS_SAKIT;
    break;

  case CAN_INT_ERG:
    /* Clear CAN_MSTS_ERIT (rc_w1) */
    CANx->MSTS = CAN_MSTS_ERIT;
    /* Note : the corresponding Flag is cleared by hardware depending
              of the CAN Bus status*/
    break;

  case CAN_INT_ERP:
    /* Clear CAN_MSTS_ERIT (rc_w1) */
    CANx->MSTS = CAN_MSTS_ERIT;
    /* Note : the corresponding Flag is cleared by hardware depending
              of the CAN Bus status*/
    break;

  case CAN_INT_BU:
    /* Clear CAN_MSTS_ERIT (rc_w1) */
    CANx->MSTS = CAN_MSTS_ERIT;
    /* Note : the corresponding Flag is cleared by hardware depending
              of the CAN Bus status*/
    break;

  case CAN_INT_LEC:
    /*  Clear LEC bits */
    CANx->ESTS = RESET;
    /* Clear CAN_MSTS_ERIT (rc_w1) */
    CANx->MSTS = CAN_MSTS_ERIT;
    break;

  case CAN_INT_ERR:
    /*Clear LEC bits */
    CANx->ESTS = RESET;
    /* Clear CAN_MSTS_ERIT (rc_w1) */
    CANx->MSTS = CAN_MSTS_ERIT;
    /* Note : BOFF, EPVF and EWGF Flags are cleared by hardware depending
            of the CAN Bus status*/
    break;

  default :
    break;
  }
}

/**
  * @brief  Checks whether the CAN interrupt has occurred or not.
  * @param  CAN_Reg: specifies the CAN interrupt register to check.
  * @param  It_Bit:  specifies the interrupt source bit to check.
  * @retval The new state of the CAN Interrupt (SET or RESET).
  */
static ITStatus CheckINTStatus(uint32_t CAN_Reg, uint32_t It_Bit)
{
  ITStatus pendingbitstatus = RESET;

  if ((CAN_Reg & It_Bit) != (uint32_t)RESET)
  {
    /* CAN_INT is set */
    pendingbitstatus = SET;
  }
  else
  {
    /* CAN_INT is reset */
    pendingbitstatus = RESET;
  }

  return pendingbitstatus;
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


