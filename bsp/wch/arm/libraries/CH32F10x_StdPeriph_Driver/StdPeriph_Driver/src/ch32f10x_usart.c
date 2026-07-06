/***************COPYRIGHT(C)  2019 WCH. A11 rights reserved*********************
* File Name          : ch32f10x_usart.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2019/10/15
* Description        : This file provides all the USART firmware functions.
*******************************************************************************/ 
#include "ch32f10x_usart.h"
#include "ch32f10x_rcc.h"

/* USART_Private_Defines */
#define CTLR1_UE_Set                ((uint16_t)0x2000)  /*!< USART Enable Mask */
#define CTLR1_UE_Reset              ((uint16_t)0xDFFF)  /*!< USART Disable Mask */

#define CTLR1_WAKE_Mask             ((uint16_t)0xF7FF)  /*!< USART WakeUp Method Mask */

#define CTLR1_RWU_Set               ((uint16_t)0x0002)  /*!< USART mute mode Enable Mask */
#define CTLR1_RWU_Reset             ((uint16_t)0xFFFD)  /*!< USART mute mode Enable Mask */
#define CTLR1_SBK_Set               ((uint16_t)0x0001)  /*!< USART Break Character send Mask */
#define CTLR1_CLEAR_Mask            ((uint16_t)0xE9F3)  /*!< USART CR1 Mask */
#define CTLR2_Address_Mask          ((uint16_t)0xFFF0)  /*!< USART address Mask */

#define CTLR2_LINEN_Set             ((uint16_t)0x4000)  /*!< USART LIN Enable Mask */
#define CTLR2_LINEN_Reset           ((uint16_t)0xBFFF)  /*!< USART LIN Disable Mask */

#define CTLR2_LBDL_Mask             ((uint16_t)0xFFDF)  /*!< USART LIN Break detection Mask */
#define CTLR2_STOP_CLEAR_Mask       ((uint16_t)0xCFFF)  /*!< USART CR2 STOP Bits Mask */
#define CTLR2_CLOCK_CLEAR_Mask      ((uint16_t)0xF0FF)  /*!< USART CR2 Clock Mask */

#define CTLR3_SCEN_Set              ((uint16_t)0x0020)  /*!< USART SC Enable Mask */
#define CTLR3_SCEN_Reset            ((uint16_t)0xFFDF)  /*!< USART SC Disable Mask */

#define CTLR3_NACK_Set              ((uint16_t)0x0010)  /*!< USART SC NACK Enable Mask */
#define CTLR3_NACK_Reset            ((uint16_t)0xFFEF)  /*!< USART SC NACK Disable Mask */

#define CTLR3_HDSEL_Set             ((uint16_t)0x0008)  /*!< USART Half-Duplex Enable Mask */
#define CTLR3_HDSEL_Reset           ((uint16_t)0xFFF7)  /*!< USART Half-Duplex Disable Mask */

#define CTLR3_IRLP_Mask             ((uint16_t)0xFFFB)  /*!< USART IrDA LowPower mode Mask */
#define CTLR3_CLEAR_Mask            ((uint16_t)0xFCFF)  /*!< USART CR3 Mask */

#define CTLR3_IREN_Set              ((uint16_t)0x0002)  /*!< USART IrDA Enable Mask */
#define CTLR3_IREN_Reset            ((uint16_t)0xFFFD)  /*!< USART IrDA Disable Mask */
#define GPR_LSB_Mask                ((uint16_t)0x00FF)  /*!< Guard Time Register LSB Mask */
#define GPR_MSB_Mask                ((uint16_t)0xFF00)  /*!< Guard Time Register MSB Mask */
#define IT_Mask                     ((uint16_t)0x001F)  /*!< USART Interrupt Mask */

/* USART OverSampling-8 Mask */
#define CTLR1_OVER8_Set             ((uint16_t)0x8000)  /* USART OVER8 mode Enable Mask */
#define CTLR1_OVER8_Reset           ((uint16_t)0x7FFF)  /* USART OVER8 mode Disable Mask */

/* USART One Bit Sampling Mask */
#define CTLR3_ONEBITE_Set           ((uint16_t)0x0800)  /* USART ONEBITE mode Enable Mask */
#define CTLR3_ONEBITE_Reset         ((uint16_t)0xF7FF)  /* USART ONEBITE mode Disable Mask */


/*******************************************************************************
* Function Name  : USART_DeInit
* Description    : Deinitializes the USARTx peripheral registers to their default
*      reset values.
* Input          : USARTx: where x can be 1, 2 or 3 to select the UART peripheral.
* Return         : None
*******************************************************************************/
void USART_DeInit(USART_TypeDef* USARTx)
{
  if (USARTx == USART1)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);
  }
  else if (USARTx == USART2)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, DISABLE);
  }
  else if (USARTx == USART3)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, DISABLE);
  }    
  else if (USARTx == UART4)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, DISABLE);
  }    
  else
  {
    if (USARTx == UART5)
    { 
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, ENABLE);
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, DISABLE);
    }
  }
}

/*******************************************************************************
* Function Name  : USART_Init
* Description    : Initializes the USARTx peripheral according to the specified
*      parameters in the USART_InitStruct.
* Input          : USARTx: where x can be 1, 2 or 3 to select the UART peripheral.
*                  USART_InitStruct: pointer to a USART_InitTypeDef structure
*      that contains the configuration information for the specified USART peripheral. 
* Return         : None
*******************************************************************************/
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct)
{
  uint32_t tmpreg = 0x00, apbclock = 0x00;
  uint32_t integerdivider = 0x00;
  uint32_t fractionaldivider = 0x00;
  uint32_t usartxbase = 0;
  RCC_ClocksTypeDef RCC_ClocksStatus;

  if (USART_InitStruct->USART_HardwareFlowControl != USART_HardwareFlowControl_None)
  {
  }

  usartxbase = (uint32_t)USARTx;
  tmpreg = USARTx->CTLR2;
  tmpreg &= CTLR2_STOP_CLEAR_Mask;
  tmpreg |= (uint32_t)USART_InitStruct->USART_StopBits;  
	
  USARTx->CTLR2 = (uint16_t)tmpreg;
  tmpreg = USARTx->CTLR1;
  tmpreg &= CTLR1_CLEAR_Mask;
  tmpreg |= (uint32_t)USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity |
            USART_InitStruct->USART_Mode;
  USARTx->CTLR1 = (uint16_t)tmpreg;
 
  tmpreg = USARTx->CTLR3;
  tmpreg &= CTLR3_CLEAR_Mask;
  tmpreg |= USART_InitStruct->USART_HardwareFlowControl;
  USARTx->CTLR3 = (uint16_t)tmpreg;

  RCC_GetClocksFreq(&RCC_ClocksStatus);
	
  if (usartxbase == USART1_BASE)
  {
    apbclock = RCC_ClocksStatus.PCLK2_Frequency;
  }
  else
  {
    apbclock = RCC_ClocksStatus.PCLK1_Frequency;
  }
  
  if ((USARTx->CTLR1 & CTLR1_OVER8_Set) != 0)
  {
    integerdivider = ((25 * apbclock) / (2 * (USART_InitStruct->USART_BaudRate)));    
  }
  else 
  {
    integerdivider = ((25 * apbclock) / (4 * (USART_InitStruct->USART_BaudRate)));    
  }
  tmpreg = (integerdivider / 100) << 4;

  fractionaldivider = integerdivider - (100 * (tmpreg >> 4));

  if ((USARTx->CTLR1 & CTLR1_OVER8_Set) != 0)
  {
    tmpreg |= ((((fractionaldivider * 8) + 50) / 100)) & ((uint8_t)0x07);
  }
  else 
  {
    tmpreg |= ((((fractionaldivider * 16) + 50) / 100)) & ((uint8_t)0x0F);
  }
  
  USARTx->BRR = (uint16_t)tmpreg;
}

/*******************************************************************************
* Function Name  : USART_StructInit
* Description    : Fills each USART_InitStruct member with its default value.
* Input          : USART_InitStruct: pointer to a USART_InitTypeDef structure 
*      which will be initialized.
* Return         : None
*******************************************************************************/
void USART_StructInit(USART_InitTypeDef* USART_InitStruct)
{
  USART_InitStruct->USART_BaudRate = 9600;
  USART_InitStruct->USART_WordLength = USART_WordLength_8b;
  USART_InitStruct->USART_StopBits = USART_StopBits_1;
  USART_InitStruct->USART_Parity = USART_Parity_No ;
  USART_InitStruct->USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct->USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
}

/*******************************************************************************
* Function Name  : USART_ClockInit
* Description    : Initializes the USARTx peripheral Clock according to the 
*      specified parameters in the USART_ClockInitStruct .
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  USART_ClockInitStruct: pointer to a USART_ClockInitTypeDef
*      structure that contains the configuration information for the specified 
*      USART peripheral.
* Return         : None
*******************************************************************************/
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  uint32_t tmpreg = 0x00;
	
  tmpreg = USARTx->CTLR2;
  tmpreg &= CTLR2_CLOCK_CLEAR_Mask;
  tmpreg |= (uint32_t)USART_ClockInitStruct->USART_Clock | USART_ClockInitStruct->USART_CPOL | 
                 USART_ClockInitStruct->USART_CPHA | USART_ClockInitStruct->USART_LastBit;
  USARTx->CTLR2 = (uint16_t)tmpreg;
}

/*******************************************************************************
* Function Name  : USART_ClockStructInit
* Description    : Fills each USART_InitStruct member with its default value.
* Input          : USART_ClockInitStruct: pointer to a USART_ClockInitTypeDef
*      structure which will be initialized.
* Return         : None
*******************************************************************************/
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  USART_ClockInitStruct->USART_Clock = USART_Clock_Disable;
  USART_ClockInitStruct->USART_CPOL = USART_CPOL_Low;
  USART_ClockInitStruct->USART_CPHA = USART_CPHA_1Edge;
  USART_ClockInitStruct->USART_LastBit = USART_LastBit_Disable;
}

/*******************************************************************************
* Function Name  : USART_Cmd
* Description    : Enables or disables the specified USART peripheral.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    USARTx->CTLR1 |= CTLR1_UE_Set;
  }
  else
  {
    USARTx->CTLR1 &= CTLR1_UE_Reset;
  }
}

/*******************************************************************************
* Function Name  : USART_ITConfig
* Description    : Enables or disables the specified USART interrupts.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  USART_IT: specifies the USART interrupt sources to be enabled or disabled.
*                    USART_IT_CTS:  CTS change interrupt.
*                    USART_IT_LBD:  LIN Break detection interrupt.
*                    USART_IT_TXE:  Transmit Data Register empty interrupt.
*                    USART_IT_TC:   Transmission complete interrupt.
*                    USART_IT_RXNE: Receive Data register not empty interrupt.
*                    USART_IT_IDLE: Idle line detection interrupt.
*                    USART_IT_PE:   Parity Error interrupt.
*                    USART_IT_ERR:  Error interrupt.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState)
{
  uint32_t usartreg = 0x00, itpos = 0x00, itmask = 0x00;
  uint32_t usartxbase = 0x00;

  if (USART_IT == USART_IT_CTS)
  {
  }   
  
  usartxbase = (uint32_t)USARTx;
  usartreg = (((uint8_t)USART_IT) >> 0x05);
  itpos = USART_IT & IT_Mask;
  itmask = (((uint32_t)0x01) << itpos);
    
  if (usartreg == 0x01) 
  {
    usartxbase += 0x0C;
  }
  else if (usartreg == 0x02) 
  {
    usartxbase += 0x10;
  }
  else 
  {
    usartxbase += 0x14; 
  }
	
  if (NewState != DISABLE)
  {
    *(__IO uint32_t*)usartxbase  |= itmask;
  }
  else
  {
    *(__IO uint32_t*)usartxbase &= ~itmask;
  }
}

/*******************************************************************************
* Function Name  : USART_DMACmd
* Description    : Enables or disables the USART DMA interface.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  USART_DMAReq: specifies the DMA request.
*                    USART_DMAReq_Tx: USART DMA transmit request.
*                    USART_DMAReq_Rx: USART DMA receive request.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void USART_DMACmd(USART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    USARTx->CTLR3 |= USART_DMAReq;
  }
  else
  {
    USARTx->CTLR3 &= (uint16_t)~USART_DMAReq;
  }
}

/*******************************************************************************
* Function Name  : USART_SetAddress
* Description    : Sets the address of the USART node.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  USART_Address: Indicates the address of the USART node.
* Return         : None
*******************************************************************************/
void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address)
{
  USARTx->CTLR2 &= CTLR2_Address_Mask;
  USARTx->CTLR2 |= USART_Address;
}

/*******************************************************************************
* Function Name  : USART_WakeUpConfig
* Description    : Selects the USART WakeUp method.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  USART_WakeUp: specifies the USART wakeup method.
*                    USART_WakeUp_IdleLine: WakeUp by an idle line detection.
*                    USART_WakeUp_AddressMark: WakeUp by an address mark.
* Return         : None
*******************************************************************************/
void USART_WakeUpConfig(USART_TypeDef* USARTx, uint16_t USART_WakeUp)
{
  USARTx->CTLR1 &= CTLR1_WAKE_Mask;
  USARTx->CTLR1 |= USART_WakeUp;
}

/*******************************************************************************
* Function Name  : USART_ReceiverWakeUpCmd
* Description    : Determines if the USART is in mute mode or not.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void USART_ReceiverWakeUpCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    USARTx->CTLR1 |= CTLR1_RWU_Set;
  }
  else
  {
    USARTx->CTLR1 &= CTLR1_RWU_Reset;
  }
}

/*******************************************************************************
* Function Name  : USART_LINBreakDetectLengthConfig
* Description    : Sets the USART LIN Break detection length.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  USART_LINBreakDetectLength: specifies the LIN break detection length.
*                    USART_LINBreakDetectLength_10b: 10-bit break detection.
*                    USART_LINBreakDetectLength_11b: 11-bit break detection.
* Return         : None
*******************************************************************************/
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint16_t USART_LINBreakDetectLength)
{
  USARTx->CTLR2 &= CTLR2_LBDL_Mask;
  USARTx->CTLR2 |= USART_LINBreakDetectLength;  
}

/*******************************************************************************
* Function Name  : USART_LINCmd
* Description    : Enables or disables the USART LIN mode.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    USARTx->CTLR2 |= CTLR2_LINEN_Set;
  }
  else
  {
    USARTx->CTLR2 &= CTLR2_LINEN_Reset;
  }
}

/*******************************************************************************
* Function Name  : USART_SendData
* Description    : Transmits single data through the USARTx peripheral.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  Data: the data to transmit..
* Return         : None
*******************************************************************************/
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data)
{
  USARTx->DATAR = (Data & (uint16_t)0x01FF);
}

/*******************************************************************************
* Function Name  : USART_ReceiveData
* Description    : Returns the most recent received data by the USARTx peripheral.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
* Return         : The received data.
*******************************************************************************/
uint16_t USART_ReceiveData(USART_TypeDef* USARTx)
{
  return (uint16_t)(USARTx->DATAR & (uint16_t)0x01FF);
}

/*******************************************************************************
* Function Name  : USART_SendBreak
* Description    : Transmits break characters.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
* Return         : None
*******************************************************************************/
void USART_SendBreak(USART_TypeDef* USARTx)
{
  USARTx->CTLR1 |= CTLR1_SBK_Set;
}

/*******************************************************************************
* Function Name  : USART_SetGuardTime
* Description    : Sets the specified USART guard time.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  USART_GuardTime: specifies the guard time.
* Return         : None
*******************************************************************************/
void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime)
{    
  USARTx->GPR &= GPR_LSB_Mask;
  USARTx->GPR |= (uint16_t)((uint16_t)USART_GuardTime << 0x08);
}

/*******************************************************************************
* Function Name  : USART_SetPrescaler
* Description    : Sets the system clock prescaler.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  USART_Prescaler: specifies the prescaler clock.
* Return         : None
*******************************************************************************/
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler)
{ 
  USARTx->GPR &= GPR_MSB_Mask;
  USARTx->GPR |= USART_Prescaler;
}

/*******************************************************************************
* Function Name  : USART_SmartCardCmd
* Description    : Enables or disables the USART Smart Card mode.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  NewState: ENABLE or DISABLE.    
* Return         : None
*******************************************************************************/
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    USARTx->CTLR3 |= CTLR3_SCEN_Set;
  }
  else
  {
    USARTx->CTLR3 &= CTLR3_SCEN_Reset;
  }
}

/*******************************************************************************
* Function Name  : USART_SmartCardNACKCmd
* Description    : Enables or disables NACK transmission.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  NewState: ENABLE or DISABLE.    
* Return         : None
*******************************************************************************/
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    USARTx->CTLR3 |= CTLR3_NACK_Set;
  }
  else
  {
    USARTx->CTLR3 &= CTLR3_NACK_Reset;
  }
}

/*******************************************************************************
* Function Name  : USART_HalfDuplexCmd
* Description    : Enables or disables the USART Half Duplex communication.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  NewState: ENABLE or DISABLE.    
* Return         : None
*******************************************************************************/
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    USARTx->CTLR3 |= CTLR3_HDSEL_Set;
  }
  else
  {
    USARTx->CTLR3 &= CTLR3_HDSEL_Reset;
  }
}

/*******************************************************************************
* Function Name  : USART_OverSampling8Cmd
* Description    : Enables or disables the USART's 8x oversampling mode.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  NewState: ENABLE or DISABLE.    
* Return         : None
*******************************************************************************/
void USART_OverSampling8Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    USARTx->CTLR1 |= CTLR1_OVER8_Set;
  }
  else
  {
    USARTx->CTLR1 &= CTLR1_OVER8_Reset;
  }
}

/*******************************************************************************
* Function Name  : USART_OneBitMethodCmd
* Description    : Enables or disables the USART's one bit sampling method.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  NewState: ENABLE or DISABLE.    
* Return         : None
*******************************************************************************/
void USART_OneBitMethodCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    USARTx->CTLR3 |= CTLR3_ONEBITE_Set;
  }
  else
  {
    USARTx->CTLR3 &= CTLR3_ONEBITE_Reset;
  }
}

/*******************************************************************************
* Function Name  : USART_IrDAConfig
* Description    : Configures the USART's IrDA interface.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  USART_IrDAMode: specifies the IrDA mode.
*                    USART_IrDAMode_LowPower.
*                    USART_IrDAMode_Normal.
* Return         : None
*******************************************************************************/
void USART_IrDAConfig(USART_TypeDef* USARTx, uint16_t USART_IrDAMode)
{ 
  USARTx->CTLR3 &= CTLR3_IRLP_Mask;
  USARTx->CTLR3 |= USART_IrDAMode;
}

/*******************************************************************************
* Function Name  : USART_IrDACmd
* Description    : Enables or disables the USART's IrDA interface.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  NewState: ENABLE or DISABLE.   
* Return         : None
*******************************************************************************/
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState)
{ 
  if (NewState != DISABLE)
  {
    USARTx->CTLR3 |= CTLR3_IREN_Set;
  }
  else
  {
    USARTx->CTLR3 &= CTLR3_IREN_Reset;
  }
}

/*******************************************************************************
* Function Name  : USART_GetFlagStatus
* Description    : Checks whether the specified USART flag is set or not.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  USART_FLAG: specifies the flag to check.
*                    USART_FLAG_CTS: CTS Change flag.
*                    USART_FLAG_LBD: LIN Break detection flag.
*                    USART_FLAG_TXE: Transmit data register empty flag.
*                    USART_FLAG_TC: Transmission Complete flag.
*                    USART_FLAG_RXNE: Receive data register not empty flag.
*                    USART_FLAG_IDLE: Idle Line detection flag.
*                    USART_FLAG_ORE: OverRun Error flag.
*                    USART_FLAG_NE: Noise Error flag.
*                    USART_FLAG_FE: Framing Error flag.
*                    USART_FLAG_PE: Parity Error flag.
* Return         : bitstatus: SET or RESET.
*******************************************************************************/
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG)
{
  FlagStatus bitstatus = RESET;

  if (USART_FLAG == USART_FLAG_CTS)
  {
  }  
  
  if ((USARTx->STATR & USART_FLAG) != (uint16_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/*******************************************************************************
* Function Name  : USART_ClearFlag
* Description    : Clears the USARTx's pending flags.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  USART_FLAG: specifies the flag to clear.
*                    USART_FLAG_CTS: CTS Change flag.
*                    USART_FLAG_LBD: LIN Break detection flag.
*                    USART_FLAG_TC: Transmission Complete flag.
*                    USART_FLAG_RXNE: Receive data register not empty flag.
* Return         : None
*******************************************************************************/
void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG)
{
  if ((USART_FLAG & USART_FLAG_CTS) == USART_FLAG_CTS)
  {
  } 
   
  USARTx->STATR = (uint16_t)~USART_FLAG;
}

/*******************************************************************************
* Function Name  : USART_GetITStatus
* Description    : Checks whether the specified USART interrupt has occurred or not.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  USART_IT: specifies the USART interrupt source to check.
*                    USART_IT_CTS: CTS change interrupt.
*                    USART_IT_LBD: LIN Break detection interrupt.
*                    USART_IT_TXE: Tansmit Data Register empty interrupt.
*                    USART_IT_TC: Transmission complete interrupt.
*                    USART_IT_RXNE: Receive Data register not empty interrupt.
*                    USART_IT_IDLE: Idle line detection interrupt.
*                    USART_IT_ORE: OverRun Error interrupt.
*                    USART_IT_NE: Noise Error interrupt.
*                    USART_IT_FE: Framing Error interrupt.
*                    USART_IT_PE: Parity Error interrupt.
* Return         : bitstatus: SET or RESET.
*******************************************************************************/
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT)
{
  uint32_t bitpos = 0x00, itmask = 0x00, usartreg = 0x00;
  ITStatus bitstatus = RESET;

  if (USART_IT == USART_IT_CTS)
  {
  }   
  
  usartreg = (((uint8_t)USART_IT) >> 0x05);
  itmask = USART_IT & IT_Mask;
  itmask = (uint32_t)0x01 << itmask;
  
  if (usartreg == 0x01) 
  {
    itmask &= USARTx->CTLR1;
  }
  else if (usartreg == 0x02) 
  {
    itmask &= USARTx->CTLR2;
  }
  else 
  {
    itmask &= USARTx->CTLR3;
  }
  
  bitpos = USART_IT >> 0x08;
  bitpos = (uint32_t)0x01 << bitpos;
  bitpos &= USARTx->STATR;
	
  if ((itmask != (uint16_t)RESET)&&(bitpos != (uint16_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  
  return bitstatus;  
}

/*******************************************************************************
* Function Name  : USART_ClearITPendingBit
* Description    : Clears the USARTx's interrupt pending bits.
* Input          : USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                  USART_IT: specifies the interrupt pending bit to clear.
*                    USART_IT_CTS:  CTS change interrupt. 
*                    USART_IT_LBD:  LIN Break detection interrupt.
*                    USART_IT_TC:   Transmission complete interrupt.
*                    USART_IT_RXNE: Receive Data register not empty interrupt.
* Return         : None
*******************************************************************************/
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT)
{
  uint16_t bitpos = 0x00, itmask = 0x00;

  if (USART_IT == USART_IT_CTS)
  {
		
  }   
  
  bitpos = USART_IT >> 0x08;
  itmask = ((uint16_t)0x01 << (uint16_t)bitpos);
  USARTx->STATR = (uint16_t)~itmask;
}








