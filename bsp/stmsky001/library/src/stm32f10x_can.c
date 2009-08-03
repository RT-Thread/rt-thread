/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_can.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file provides all the CAN firmware functions.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_can.h"
#include "stm32f10x_rcc.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* CAN Master Control Register bits */
#define MCR_INRQ     ((u32)0x00000001) /* Initialization request */
#define MCR_SLEEP    ((u32)0x00000002) /* Sleep mode request */
#define MCR_TXFP     ((u32)0x00000004) /* Transmit FIFO priority */
#define MCR_RFLM     ((u32)0x00000008) /* Receive FIFO locked mode */
#define MCR_NART     ((u32)0x00000010) /* No automatic retransmission */
#define MCR_AWUM     ((u32)0x00000020) /* Automatic wake up mode */
#define MCR_ABOM     ((u32)0x00000040) /* Automatic bus-off management */
#define MCR_TTCM     ((u32)0x00000080) /* time triggered communication */

/* CAN Master Status Register bits */
#define MSR_INAK     ((u32)0x00000001)    /* Initialization acknowledge */
#define MSR_WKUI     ((u32)0x00000008)    /* Wake-up interrupt */
#define MSR_SLAKI    ((u32)0x00000010)    /* Sleep acknowledge interrupt */

/* CAN Transmit Status Register bits */
#define TSR_RQCP0    ((u32)0x00000001)    /* Request completed mailbox0 */
#define TSR_TXOK0    ((u32)0x00000002)    /* Transmission OK of mailbox0 */
#define TSR_ABRQ0    ((u32)0x00000080)    /* Abort request for mailbox0 */
#define TSR_RQCP1    ((u32)0x00000100)    /* Request completed mailbox1 */
#define TSR_TXOK1    ((u32)0x00000200)    /* Transmission OK of mailbox1 */
#define TSR_ABRQ1    ((u32)0x00008000)    /* Abort request for mailbox1 */
#define TSR_RQCP2    ((u32)0x00010000)    /* Request completed mailbox2 */
#define TSR_TXOK2    ((u32)0x00020000)    /* Transmission OK of mailbox2 */
#define TSR_ABRQ2    ((u32)0x00800000)    /* Abort request for mailbox2 */
#define TSR_TME0     ((u32)0x04000000)    /* Transmit mailbox 0 empty */
#define TSR_TME1     ((u32)0x08000000)    /* Transmit mailbox 1 empty */
#define TSR_TME2     ((u32)0x10000000)    /* Transmit mailbox 2 empty */

/* CAN Receive FIFO 0 Register bits */
#define RF0R_FULL0   ((u32)0x00000008)    /* FIFO 0 full */
#define RF0R_FOVR0   ((u32)0x00000010)    /* FIFO 0 overrun */
#define RF0R_RFOM0   ((u32)0x00000020)    /* Release FIFO 0 output mailbox */

/* CAN Receive FIFO 1 Register bits */
#define RF1R_FULL1   ((u32)0x00000008)    /* FIFO 1 full */
#define RF1R_FOVR1   ((u32)0x00000010)    /* FIFO 1 overrun */
#define RF1R_RFOM1   ((u32)0x00000020)    /* Release FIFO 1 output mailbox */

/* CAN Error Status Register bits */
#define ESR_EWGF     ((u32)0x00000001)    /* Error warning flag */
#define ESR_EPVF     ((u32)0x00000002)    /* Error passive flag */
#define ESR_BOFF     ((u32)0x00000004)    /* Bus-off flag */

/* CAN Mailbox Transmit Request */
#define TMIDxR_TXRQ  ((u32)0x00000001) /* Transmit mailbox request */

/* CAN Filter Master Register bits */
#define FMR_FINIT    ((u32)0x00000001) /* Filter init mode */


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static ITStatus CheckITStatus(u32 CAN_Reg, u32 It_Bit);

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : CAN_DeInit
* Description    : Deinitializes the CAN peripheral registers to their default
*                  reset values.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CAN_DeInit(void)
{
  /* Enable CAN reset state */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN, ENABLE);
  /* Release CAN from reset state */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN, DISABLE);
}

/*******************************************************************************
* Function Name  : CAN_Init
* Description    : Initializes the CAN peripheral according to the specified
*                  parameters in the CAN_InitStruct.
* Input          : CAN_InitStruct: pointer to a CAN_InitTypeDef structure that
                   contains the configuration information for the CAN peripheral.
* Output         : None.
* Return         : Constant indicates initialization succeed which will be 
*                  CANINITFAILED or CANINITOK.
*******************************************************************************/
u8 CAN_Init(CAN_InitTypeDef* CAN_InitStruct)
{
  u8 InitStatus = 0;
  u16 WaitAck = 0;

  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_TTCM));
  assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_ABOM));
  assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_AWUM));
  assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_NART));
  assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_RFLM));
  assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_TXFP));
  assert_param(IS_CAN_MODE(CAN_InitStruct->CAN_Mode));
  assert_param(IS_CAN_SJW(CAN_InitStruct->CAN_SJW));
  assert_param(IS_CAN_BS1(CAN_InitStruct->CAN_BS1));
  assert_param(IS_CAN_BS2(CAN_InitStruct->CAN_BS2));
  assert_param(IS_CAN_PRESCALER(CAN_InitStruct->CAN_Prescaler));

  /* Request initialisation */
  CAN->MCR = MCR_INRQ;

  /* ...and check acknowledged */
  if ((CAN->MSR & MSR_INAK) == 0)
  {
    InitStatus = CANINITFAILED;
  }
  else
  {
    /* Set the time triggered communication mode */
    if (CAN_InitStruct->CAN_TTCM == ENABLE)
    {
      CAN->MCR |= MCR_TTCM;
    }
    else
    {
      CAN->MCR &= ~MCR_TTCM;
    }

    /* Set the automatic bus-off management */
    if (CAN_InitStruct->CAN_ABOM == ENABLE)
    {
      CAN->MCR |= MCR_ABOM;
    }
    else
    {
      CAN->MCR &= ~MCR_ABOM;
    }

    /* Set the automatic wake-up mode */
    if (CAN_InitStruct->CAN_AWUM == ENABLE)
    {
      CAN->MCR |= MCR_AWUM;
    }
    else
    {
      CAN->MCR &= ~MCR_AWUM;
    }

    /* Set the no automatic retransmission */
    if (CAN_InitStruct->CAN_NART == ENABLE)
    {
      CAN->MCR |= MCR_NART;
    }
    else
    {
      CAN->MCR &= ~MCR_NART;
    }

    /* Set the receive FIFO locked mode */
    if (CAN_InitStruct->CAN_RFLM == ENABLE)
    {
      CAN->MCR |= MCR_RFLM;
    }
    else
    {
      CAN->MCR &= ~MCR_RFLM;
    }

    /* Set the transmit FIFO priority */
    if (CAN_InitStruct->CAN_TXFP == ENABLE)
    {
      CAN->MCR |= MCR_TXFP;
    }
    else
    {
      CAN->MCR &= ~MCR_TXFP;
    }

    /* Set the bit timing register */
    CAN->BTR = (u32)((u32)CAN_InitStruct->CAN_Mode << 30) | ((u32)CAN_InitStruct->CAN_SJW << 24) |
               ((u32)CAN_InitStruct->CAN_BS1 << 16) | ((u32)CAN_InitStruct->CAN_BS2 << 20) |
               ((u32)CAN_InitStruct->CAN_Prescaler - 1);

    InitStatus = CANINITOK;

    /* Request leave initialisation */
    CAN->MCR &= ~MCR_INRQ;

    /* Wait the acknowledge */
    for(WaitAck = 0x400; WaitAck > 0x0; WaitAck--)
    {
    }
    
    /* ...and check acknowledged */
    if ((CAN->MSR & MSR_INAK) == MSR_INAK)
    {
      InitStatus = CANINITFAILED;
    }
  }

  /* At this step, return the status of initialization */
  return InitStatus;
}

/*******************************************************************************
* Function Name  : CAN_FilterInit
* Description    : Initializes the CAN peripheral according to the specified
*                  parameters in the CAN_FilterInitStruct.
* Input          : CAN_FilterInitStruct: pointer to a CAN_FilterInitTypeDef
*                  structure that contains the configuration information.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CAN_FilterInit(CAN_FilterInitTypeDef* CAN_FilterInitStruct)
{
  u16 FilterNumber_BitPos = 0;

  /* Check the parameters */
  assert_param(IS_CAN_FILTER_NUMBER(CAN_FilterInitStruct->CAN_FilterNumber));
  assert_param(IS_CAN_FILTER_MODE(CAN_FilterInitStruct->CAN_FilterMode));
  assert_param(IS_CAN_FILTER_SCALE(CAN_FilterInitStruct->CAN_FilterScale));
  assert_param(IS_CAN_FILTER_FIFO(CAN_FilterInitStruct->CAN_FilterFIFOAssignment));
  assert_param(IS_FUNCTIONAL_STATE(CAN_FilterInitStruct->CAN_FilterActivation));

  FilterNumber_BitPos = 
  (u16)(((u16)0x0001) << ((u16)CAN_FilterInitStruct->CAN_FilterNumber));

  /* Initialisation mode for the filter */
  CAN->FMR |= FMR_FINIT;

  /* Filter Deactivation */
  CAN->FA1R &= ~(u32)FilterNumber_BitPos;

  /* Filter Scale */
  if (CAN_FilterInitStruct->CAN_FilterScale == CAN_FilterScale_16bit)
  {
    /* 16-bit scale for the filter */
    CAN->FS1R &= ~(u32)FilterNumber_BitPos;

    /* First 16-bit identifier and First 16-bit mask */
    /* Or First 16-bit identifier and Second 16-bit identifier */
    CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR1 = 
    ((u32)((u32)0x0000FFFF & CAN_FilterInitStruct->CAN_FilterMaskIdLow) << 16) |
        ((u32)0x0000FFFF & CAN_FilterInitStruct->CAN_FilterIdLow);

    /* Second 16-bit identifier and Second 16-bit mask */
    /* Or Third 16-bit identifier and Fourth 16-bit identifier */
    CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR2 = 
    ((u32)((u32)0x0000FFFF & CAN_FilterInitStruct->CAN_FilterMaskIdHigh) << 16) |
        ((u32)0x0000FFFF & CAN_FilterInitStruct->CAN_FilterIdHigh);
  }
  if (CAN_FilterInitStruct->CAN_FilterScale == CAN_FilterScale_32bit)
  {
    /* 32-bit scale for the filter */
    CAN->FS1R |= FilterNumber_BitPos;

    /* 32-bit identifier or First 32-bit identifier */
    CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR1 = 
    ((u32)((u32)0x0000FFFF & CAN_FilterInitStruct->CAN_FilterIdHigh) << 16) |
        ((u32)0x0000FFFF & CAN_FilterInitStruct->CAN_FilterIdLow);

    /* 32-bit mask or Second 32-bit identifier */
    CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR2 = 
    ((u32)((u32)0x0000FFFF & CAN_FilterInitStruct->CAN_FilterMaskIdHigh) << 16) |
        ((u32)0x0000FFFF & CAN_FilterInitStruct->CAN_FilterMaskIdLow);

  }

  /* Filter Mode */
  if (CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdMask)
  {
    /*Id/Mask mode for the filter*/
    CAN->FM1R &= ~(u32)FilterNumber_BitPos;
  }
  else /* CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdList */
  {
    /*Identifier list mode for the filter*/
    CAN->FM1R |= (u32)FilterNumber_BitPos;
  }

  /* Filter FIFO assignment */
  if (CAN_FilterInitStruct->CAN_FilterFIFOAssignment == CAN_FilterFIFO0)
  {
    /* FIFO 0 assignation for the filter */
    CAN->FFA1R &= ~(u32)FilterNumber_BitPos;
  }
  if (CAN_FilterInitStruct->CAN_FilterFIFOAssignment == CAN_FilterFIFO1)
  {
    /* FIFO 1 assignation for the filter */
    CAN->FFA1R |= (u32)FilterNumber_BitPos;
  }
  
  /* Filter activation */
  if (CAN_FilterInitStruct->CAN_FilterActivation == ENABLE)
  {
    CAN->FA1R |= FilterNumber_BitPos;
  }

  /* Leave the initialisation mode for the filter */
  CAN->FMR &= ~FMR_FINIT;
}

/*******************************************************************************
* Function Name  : CAN_StructInit
* Description    : Fills each CAN_InitStruct member with its default value.
* Input          : CAN_InitStruct: pointer to a CAN_InitTypeDef structure which
*                  will be initialized.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CAN_StructInit(CAN_InitTypeDef* CAN_InitStruct)
{
  /* Reset CAN init structure parameters values */

  /* Initialize the time triggered communication mode */
  CAN_InitStruct->CAN_TTCM = DISABLE;

  /* Initialize the automatic bus-off management */
  CAN_InitStruct->CAN_ABOM = DISABLE;

  /* Initialize the automatic wake-up mode */
  CAN_InitStruct->CAN_AWUM = DISABLE;

  /* Initialize the no automatic retransmission */
  CAN_InitStruct->CAN_NART = DISABLE;

  /* Initialize the receive FIFO locked mode */
  CAN_InitStruct->CAN_RFLM = DISABLE;

  /* Initialize the transmit FIFO priority */
  CAN_InitStruct->CAN_TXFP = DISABLE;

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

/*******************************************************************************
* Function Name  : CAN_ITConfig
* Description    : Enables or disables the specified CAN interrupts.
* Input          : - CAN_IT: specifies the CAN interrupt sources to be enabled or
*                    disabled.
*                    This parameter can be: CAN_IT_TME, CAN_IT_FMP0, CAN_IT_FF0,
*                                           CAN_IT_FOV0, CAN_IT_FMP1, CAN_IT_FF1,
*                                           CAN_IT_FOV1, CAN_IT_EWG, CAN_IT_EPV,
*                                           CAN_IT_LEC, CAN_IT_ERR, CAN_IT_WKU or
*                                           CAN_IT_SLK.
*                  - NewState: new state of the CAN interrupts.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CAN_ITConfig(u32 CAN_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_CAN_ITConfig(CAN_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected CAN interrupt */
    CAN->IER |= CAN_IT;
  }
  else
  {
    /* Disable the selected CAN interrupt */
    CAN->IER &= ~CAN_IT;
  }
}

/*******************************************************************************
* Function Name  : CAN_Transmit
* Description    : Initiates the transmission of a message.
* Input          : TxMessage: pointer to a structure which contains CAN Id, CAN
*                  DLC and CAN datas.
* Output         : None.
* Return         : The number of the mailbox that is used for transmission
*                  or CAN_NO_MB if there is no empty mailbox.
*******************************************************************************/
u8 CAN_Transmit(CanTxMsg* TxMessage)
{
  u8 TransmitMailbox = 0;

  /* Check the parameters */
  assert_param(IS_CAN_STDID(TxMessage->StdId));
  assert_param(IS_CAN_EXTID(TxMessage->StdId));
  assert_param(IS_CAN_IDTYPE(TxMessage->IDE));
  assert_param(IS_CAN_RTR(TxMessage->RTR));
  assert_param(IS_CAN_DLC(TxMessage->DLC));

  /* Select one empty transmit mailbox */
  if ((CAN->TSR&TSR_TME0) == TSR_TME0)
  {
    TransmitMailbox = 0;
  }
  else if ((CAN->TSR&TSR_TME1) == TSR_TME1)
  {
    TransmitMailbox = 1;
  }
  else if ((CAN->TSR&TSR_TME2) == TSR_TME2)
  {
    TransmitMailbox = 2;
  }
  else
  {
    TransmitMailbox = CAN_NO_MB;
  }

  if (TransmitMailbox != CAN_NO_MB)
  {
    /* Set up the Id */
    CAN->sTxMailBox[TransmitMailbox].TIR &= TMIDxR_TXRQ;
    if (TxMessage->IDE == CAN_ID_STD)
    {
      TxMessage->StdId &= (u32)0x000007FF;
      TxMessage->StdId = TxMessage->StdId << 21;
      
      CAN->sTxMailBox[TransmitMailbox].TIR |= (TxMessage->StdId | TxMessage->IDE |
                                               TxMessage->RTR);
    }
    else
    {
      TxMessage->ExtId &= (u32)0x1FFFFFFF;
      TxMessage->ExtId <<= 3;

      CAN->sTxMailBox[TransmitMailbox].TIR |= (TxMessage->ExtId | TxMessage->IDE | 
                                               TxMessage->RTR);
    }
    
    /* Set up the DLC */
    TxMessage->DLC &= (u8)0x0000000F;
    CAN->sTxMailBox[TransmitMailbox].TDTR &= (u32)0xFFFFFFF0;
    CAN->sTxMailBox[TransmitMailbox].TDTR |= TxMessage->DLC;

    /* Set up the data field */
    CAN->sTxMailBox[TransmitMailbox].TDLR = (((u32)TxMessage->Data[3] << 24) | 
                                             ((u32)TxMessage->Data[2] << 16) |
                                             ((u32)TxMessage->Data[1] << 8) | 
                                             ((u32)TxMessage->Data[0]));
    CAN->sTxMailBox[TransmitMailbox].TDHR = (((u32)TxMessage->Data[7] << 24) | 
                                             ((u32)TxMessage->Data[6] << 16) |
                                             ((u32)TxMessage->Data[5] << 8) |
                                             ((u32)TxMessage->Data[4]));

    /* Request transmission */
    CAN->sTxMailBox[TransmitMailbox].TIR |= TMIDxR_TXRQ;
  }

  return TransmitMailbox;
}

/*******************************************************************************
* Function Name  : CAN_TransmitStatus
* Description    : Checks the transmission of a message.
* Input          : TransmitMailbox: the number of the mailbox that is used for
*                  transmission.
* Output         : None.
* Return         : CANTXOK if the CAN driver transmits the message, CANTXFAILED
*                  in an other case.
*******************************************************************************/
u8 CAN_TransmitStatus(u8 TransmitMailbox)
{
  /* RQCP, TXOK and TME bits */
  u8 State = 0;

  /* Check the parameters */
  assert_param(IS_CAN_TRANSMITMAILBOX(TransmitMailbox));

  switch (TransmitMailbox)
  {
    case (0): State |= (u8)((CAN->TSR & TSR_RQCP0) << 2);
      State |= (u8)((CAN->TSR & TSR_TXOK0) >> 0);
      State |= (u8)((CAN->TSR & TSR_TME0) >> 26);
      break;
    case (1): State |= (u8)((CAN->TSR & TSR_RQCP1) >> 6);
      State |= (u8)((CAN->TSR & TSR_TXOK1) >> 8);
      State |= (u8)((CAN->TSR & TSR_TME1) >> 27);
      break;
    case (2): State |= (u8)((CAN->TSR & TSR_RQCP2) >> 14);
      State |= (u8)((CAN->TSR & TSR_TXOK2) >> 16);
      State |= (u8)((CAN->TSR & TSR_TME2) >> 28);
      break;
    default:
      State = CANTXFAILED;
      break;
  }

  switch (State)
  {
      /* transmit pending  */
    case (0x0): State = CANTXPENDING;
      break;
      /* transmit failed  */
    case (0x5): State = CANTXFAILED;
      break;
      /* transmit succedeed  */
    case (0x7): State = CANTXOK;
      break;
    default:
      State = CANTXFAILED;
      break;
  }

  return State;
}

/*******************************************************************************
* Function Name  : CAN_CancelTransmit
* Description    : Cancels a transmit request.
* Input          : Mailbox number.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CAN_CancelTransmit(u8 Mailbox)
{
  /* Check the parameters */
  assert_param(IS_CAN_TRANSMITMAILBOX(Mailbox));

  /* abort transmission */
  switch (Mailbox)
  {
    case (0): CAN->TSR |= TSR_ABRQ0;
      break;
    case (1): CAN->TSR |= TSR_ABRQ1;
      break;
    case (2): CAN->TSR |= TSR_ABRQ2;
      break;
    default:
      break;
  }
}

/*******************************************************************************
* Function Name  : CAN_FIFORelease
* Description    : Releases a FIFO.
* Input          : FIFONumber: FIFO to release, CAN_FIFO0 or CAN_FIFO1.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CAN_FIFORelease(u8 FIFONumber)
{
  /* Check the parameters */
  assert_param(IS_CAN_FIFO(FIFONumber));

  /* Release FIFO0 */
  if (FIFONumber == CAN_FIFO0)
  {
    CAN->RF0R = RF0R_RFOM0;
  }
  /* Release FIFO1 */
  else /* FIFONumber == CAN_FIFO1 */
  {
    CAN->RF1R = RF1R_RFOM1;
  }
}

/*******************************************************************************
* Function Name  : CAN_MessagePending
* Description    : Returns the number of pending messages.
* Input          : FIFONumber: Receive FIFO number, CAN_FIFO0 or CAN_FIFO1.
* Output         : None.
* Return         : NbMessage which is the number of pending message.
*******************************************************************************/
u8 CAN_MessagePending(u8 FIFONumber)
{
  u8 MessagePending=0;

  /* Check the parameters */
  assert_param(IS_CAN_FIFO(FIFONumber));

  if (FIFONumber == CAN_FIFO0)
  {
    MessagePending = (u8)(CAN->RF0R&(u32)0x03);
  }
  else if (FIFONumber == CAN_FIFO1)
  {
    MessagePending = (u8)(CAN->RF1R&(u32)0x03);
  }
  else
  {
    MessagePending = 0;
  }
  return MessagePending;
}

/*******************************************************************************
* Function Name  : CAN_Receive
* Description    : Receives a message.
* Input          : FIFONumber: Receive FIFO number, CAN_FIFO0 or CAN_FIFO1.
* Output         : RxMessage: pointer to a structure which contains CAN Id,
*                  CAN DLC, CAN datas and FMI number.
* Return         : None.
*******************************************************************************/
void CAN_Receive(u8 FIFONumber, CanRxMsg* RxMessage)
{
  /* Check the parameters */
  assert_param(IS_CAN_FIFO(FIFONumber));

  /* Get the Id */
  RxMessage->IDE = (u8)0x04 & CAN->sFIFOMailBox[FIFONumber].RIR;
  if (RxMessage->IDE == CAN_ID_STD)
  {
    RxMessage->StdId = (u32)0x000007FF & (CAN->sFIFOMailBox[FIFONumber].RIR >> 21);
  }
  else
  {
    RxMessage->ExtId = (u32)0x1FFFFFFF & (CAN->sFIFOMailBox[FIFONumber].RIR >> 3);
  }
  
  RxMessage->RTR = (u8)0x02 & CAN->sFIFOMailBox[FIFONumber].RIR;

  /* Get the DLC */
  RxMessage->DLC = (u8)0x0F & CAN->sFIFOMailBox[FIFONumber].RDTR;

  /* Get the FMI */
  RxMessage->FMI = (u8)0xFF & (CAN->sFIFOMailBox[FIFONumber].RDTR >> 8);

  /* Get the data field */
  RxMessage->Data[0] = (u8)0xFF & CAN->sFIFOMailBox[FIFONumber].RDLR;
  RxMessage->Data[1] = (u8)0xFF & (CAN->sFIFOMailBox[FIFONumber].RDLR >> 8);
  RxMessage->Data[2] = (u8)0xFF & (CAN->sFIFOMailBox[FIFONumber].RDLR >> 16);
  RxMessage->Data[3] = (u8)0xFF & (CAN->sFIFOMailBox[FIFONumber].RDLR >> 24);

  RxMessage->Data[4] = (u8)0xFF & CAN->sFIFOMailBox[FIFONumber].RDHR;
  RxMessage->Data[5] = (u8)0xFF & (CAN->sFIFOMailBox[FIFONumber].RDHR >> 8);
  RxMessage->Data[6] = (u8)0xFF & (CAN->sFIFOMailBox[FIFONumber].RDHR >> 16);
  RxMessage->Data[7] = (u8)0xFF & (CAN->sFIFOMailBox[FIFONumber].RDHR >> 24);

  /* Release the FIFO */
  CAN_FIFORelease(FIFONumber);
}

/*******************************************************************************
* Function Name  : CAN_Sleep
* Description    : Enters the low power mode.
* Input          : None.
* Output         : None.
* Return         : CANSLEEPOK if sleep entered, CANSLEEPFAILED in an other case.
*******************************************************************************/
u8 CAN_Sleep(void)
{
  u8 SleepStatus = 0;

  /* Sleep mode entering request */
  CAN->MCR |= MCR_SLEEP;
  SleepStatus = CANSLEEPOK;

  /* Sleep mode status */
  if ((CAN->MCR&MCR_SLEEP) == 0)
  {
    /* Sleep mode not entered */
    SleepStatus = CANSLEEPFAILED;
  }

  /* At this step, sleep mode status */
  return SleepStatus;
}

/*******************************************************************************
* Function Name  : CAN_WakeUp
* Description    : Wakes the CAN up.
* Input          : None.
* Output         : None.
* Return         : CANWAKEUPOK if sleep mode left, CANWAKEUPFAILED in an other
*                  case.
*******************************************************************************/
u8 CAN_WakeUp(void)
{
  u8 WakeUpStatus = 0;

  /* Wake up request */
  CAN->MCR &= ~MCR_SLEEP;
  WakeUpStatus = CANWAKEUPFAILED;

  /* Sleep mode status */
  if ((CAN->MCR&MCR_SLEEP) == 0)
  {
    /* Sleep mode exited */
    WakeUpStatus = CANWAKEUPOK;
  }

  /* At this step, sleep mode status */
  return WakeUpStatus;
}

/*******************************************************************************
* Function Name  : CAN_GetFlagStatus
* Description    : Checks whether the specified CAN flag is set or not.
* Input          : CAN_FLAG: specifies the flag to check.
*                  This parameter can be: CAN_FLAG_EWG, CAN_FLAG_EPV or
*                                         CAN_FLAG_BOF.
* Output         : None.
* Return         : The new state of CAN_FLAG (SET or RESET).
*******************************************************************************/
FlagStatus CAN_GetFlagStatus(u32 CAN_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_CAN_FLAG(CAN_FLAG));

  /* Check the status of the specified CAN flag */
  if ((CAN->ESR & CAN_FLAG) != (u32)RESET)
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
  return  bitstatus;
}

/*******************************************************************************
* Function Name  : CAN_ClearFlag
* Description    : Clears the CAN's pending flags.
* Input          : CAN_FLAG: specifies the flag to clear.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CAN_ClearFlag(u32 CAN_FLAG)
{
  /* Check the parameters */
  assert_param(IS_CAN_FLAG(CAN_FLAG));

  /* Clear the selected CAN flags */
  CAN->ESR &= ~CAN_FLAG;
}

/*******************************************************************************
* Function Name  : CAN_GetITStatus
* Description    : Checks whether the specified CAN interrupt has occurred or 
*                  not.
* Input          : CAN_IT: specifies the CAN interrupt source to check.
*                  This parameter can be: CAN_IT_RQCP0, CAN_IT_RQCP1, CAN_IT_RQCP2,
*                                         CAN_IT_FF0, CAN_IT_FOV0, CAN_IT_FF1,
*                                         CAN_IT_FOV1, CAN_IT_EWG, CAN_IT_EPV, 
*                                         CAN_IT_BOF, CAN_IT_WKU or CAN_IT_SLK.
* Output         : None.
* Return         : The new state of CAN_IT (SET or RESET).
*******************************************************************************/
ITStatus CAN_GetITStatus(u32 CAN_IT)
{
  ITStatus pendingbitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_CAN_ITStatus(CAN_IT));

  switch (CAN_IT)
  {
    case CAN_IT_RQCP0:
      pendingbitstatus = CheckITStatus(CAN->TSR, TSR_RQCP0);
      break;
    case CAN_IT_RQCP1:
      pendingbitstatus = CheckITStatus(CAN->TSR, TSR_RQCP1);
      break;
    case CAN_IT_RQCP2:
      pendingbitstatus = CheckITStatus(CAN->TSR, TSR_RQCP2);
      break;
    case CAN_IT_FF0:
      pendingbitstatus = CheckITStatus(CAN->RF0R, RF0R_FULL0);
      break;
    case CAN_IT_FOV0:
      pendingbitstatus = CheckITStatus(CAN->RF0R, RF0R_FOVR0);
      break;
    case CAN_IT_FF1:
      pendingbitstatus = CheckITStatus(CAN->RF1R, RF1R_FULL1);
      break;
    case CAN_IT_FOV1:
      pendingbitstatus = CheckITStatus(CAN->RF1R, RF1R_FOVR1);
      break;
    case CAN_IT_EWG:
      pendingbitstatus = CheckITStatus(CAN->ESR, ESR_EWGF);
      break;
    case CAN_IT_EPV:
      pendingbitstatus = CheckITStatus(CAN->ESR, ESR_EPVF);
      break;
    case CAN_IT_BOF:
      pendingbitstatus = CheckITStatus(CAN->ESR, ESR_BOFF);
      break;
    case CAN_IT_SLK:
      pendingbitstatus = CheckITStatus(CAN->MSR, MSR_SLAKI);
      break;
    case CAN_IT_WKU:
      pendingbitstatus = CheckITStatus(CAN->MSR, MSR_WKUI);
      break;

    default :
      pendingbitstatus = RESET;
      break;
  }

  /* Return the CAN_IT status */
  return  pendingbitstatus;
}

/*******************************************************************************
* Function Name  : CAN_ClearITPendingBit
* Description    : Clears the CAN’s interrupt pending bits.
* Input          : CAN_IT: specifies the interrupt pending bit to clear.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CAN_ClearITPendingBit(u32 CAN_IT)
{
  /* Check the parameters */
  assert_param(IS_CAN_ITStatus(CAN_IT));

  switch (CAN_IT)
  {
    case CAN_IT_RQCP0:
      CAN->TSR = TSR_RQCP0; /* rc_w1*/
      break;
    case CAN_IT_RQCP1:
      CAN->TSR = TSR_RQCP1; /* rc_w1*/
      break;
    case CAN_IT_RQCP2:
      CAN->TSR = TSR_RQCP2; /* rc_w1*/
      break;
    case CAN_IT_FF0:
      CAN->RF0R = RF0R_FULL0; /* rc_w1*/
      break;
    case CAN_IT_FOV0:
      CAN->RF0R = RF0R_FOVR0; /* rc_w1*/
      break;
    case CAN_IT_FF1:
      CAN->RF1R = RF1R_FULL1; /* rc_w1*/
      break;
    case CAN_IT_FOV1:
      CAN->RF1R = RF1R_FOVR1; /* rc_w1*/
      break;
    case CAN_IT_EWG:
      CAN->ESR &= ~ ESR_EWGF; /* rw */
      break;
    case CAN_IT_EPV:
      CAN->ESR &= ~ ESR_EPVF; /* rw */
      break;
    case CAN_IT_BOF:
      CAN->ESR &= ~ ESR_BOFF; /* rw */
      break;
    case CAN_IT_WKU:
      CAN->MSR = MSR_WKUI;  /* rc_w1*/
      break;
    case CAN_IT_SLK:
      CAN->MSR = MSR_SLAKI;  /* rc_w1*/
      break;
    default :
      break;
  }
}

/*******************************************************************************
* Function Name  : CheckITStatus
* Description    : Checks whether the CAN interrupt has occurred or not.
* Input          : CAN_Reg: specifies the CAN interrupt register to check.
*                  It_Bit: specifies the interrupt source bit to check.
* Output         : None.
* Return         : The new state of the CAN Interrupt (SET or RESET).
*******************************************************************************/
static ITStatus CheckITStatus(u32 CAN_Reg, u32 It_Bit)
{
  ITStatus pendingbitstatus = RESET;

  if ((CAN_Reg & It_Bit) != (u32)RESET)
  {
    /* CAN_IT is set */
    pendingbitstatus = SET;
  }
  else
  {
    /* CAN_IT is reset */
    pendingbitstatus = RESET;
  }

  return pendingbitstatus;
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
