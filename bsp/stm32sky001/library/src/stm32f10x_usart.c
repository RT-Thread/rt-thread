/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_usart.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file provides all the USART firmware functions.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* USART UE Mask */
#define CR1_UE_Set                ((u16)0x2000)  /* USART Enable Mask */
#define CR1_UE_Reset              ((u16)0xDFFF)  /* USART Disable Mask */

/* USART WakeUp Method  */
#define CR1_WAKE_Mask             ((u16)0xF7FF)  /* USART WakeUp Method Mask */

/* USART RWU Mask */
#define CR1_RWU_Set               ((u16)0x0002)  /* USART mute mode Enable Mask */
#define CR1_RWU_Reset             ((u16)0xFFFD)  /* USART mute mode Enable Mask */

#define CR1_SBK_Set               ((u16)0x0001)  /* USART Break Character send Mask */

#define CR1_CLEAR_Mask            ((u16)0xE9F3)  /* USART CR1 Mask */

#define CR2_Address_Mask          ((u16)0xFFF0)  /* USART address Mask */

/* USART LIN Mask */
#define CR2_LINEN_Set              ((u16)0x4000)  /* USART LIN Enable Mask */
#define CR2_LINEN_Reset            ((u16)0xBFFF)  /* USART LIN Disable Mask */

/* USART LIN Break detection */
#define CR2_LBDL_Mask             ((u16)0xFFDF)  /* USART LIN Break detection Mask */

#define CR2_STOP_CLEAR_Mask       ((u16)0xCFFF)  /* USART CR2 STOP Bits Mask */
#define CR2_CLOCK_CLEAR_Mask      ((u16)0xF0FF)  /* USART CR2 Clock Mask */

/* USART SC Mask */
#define CR3_SCEN_Set              ((u16)0x0020)  /* USART SC Enable Mask */
#define CR3_SCEN_Reset            ((u16)0xFFDF)  /* USART SC Disable Mask */

/* USART SC NACK Mask */
#define CR3_NACK_Set              ((u16)0x0010)  /* USART SC NACK Enable Mask */
#define CR3_NACK_Reset            ((u16)0xFFEF)  /* USART SC NACK Disable Mask */

/* USART Half-Duplex Mask */
#define CR3_HDSEL_Set             ((u16)0x0008)  /* USART Half-Duplex Enable Mask */
#define CR3_HDSEL_Reset           ((u16)0xFFF7)  /* USART Half-Duplex Disable Mask */

/* USART IrDA Mask */
#define CR3_IRLP_Mask             ((u16)0xFFFB)  /* USART IrDA LowPower mode Mask */

#define CR3_CLEAR_Mask            ((u16)0xFCFF)  /* USART CR3 Mask */

/* USART IrDA Mask */
#define CR3_IREN_Set              ((u16)0x0002)  /* USART IrDA Enable Mask */
#define CR3_IREN_Reset            ((u16)0xFFFD)  /* USART IrDA Disable Mask */

#define GTPR_LSB_Mask             ((u16)0x00FF)  /* Guard Time Register LSB Mask */
#define GTPR_MSB_Mask             ((u16)0xFF00)  /* Guard Time Register MSB Mask */

#define IT_Mask                   ((u16)0x001F)  /* USART Interrupt Mask */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : USART_DeInit
* Description    : Deinitializes the USARTx peripheral registers to their
*                  default reset values.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_DeInit(USART_TypeDef* USARTx)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  switch (*(u32*)&USARTx)
  {
    case USART1_BASE:
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);
      break;

    case USART2_BASE:
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, ENABLE);
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, DISABLE);
      break;

    case USART3_BASE:
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, ENABLE);
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, DISABLE);
      break;
    
    case UART4_BASE:
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, ENABLE);
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, DISABLE);
      break;
    
    case UART5_BASE:
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, ENABLE);
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, DISABLE);
      break;            

    default:
      break;
  }
}

/*******************************************************************************
* Function Name  : USART_Init
* Description    : Initializes the USARTx peripheral according to the specified
*                  parameters in the USART_InitStruct .
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
*                  - USART_InitStruct: pointer to a USART_InitTypeDef structure
*                    that contains the configuration information for the
*                    specified USART peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct)
{
  u32 tmpreg = 0x00, apbclock = 0x00;
  u32 integerdivider = 0x00;
  u32 fractionaldivider = 0x00;
  u32 usartxbase = 0;
  RCC_ClocksTypeDef RCC_ClocksStatus;

  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_BAUDRATE(USART_InitStruct->USART_BaudRate));  
  assert_param(IS_USART_WORD_LENGTH(USART_InitStruct->USART_WordLength));
  assert_param(IS_USART_STOPBITS(USART_InitStruct->USART_StopBits));
  assert_param(IS_USART_PARITY(USART_InitStruct->USART_Parity));
  assert_param(IS_USART_MODE(USART_InitStruct->USART_Mode));
  assert_param(IS_USART_HARDWARE_FLOW_CONTROL(USART_InitStruct->USART_HardwareFlowControl));
  /* The hardware flow control is available only for USART1, USART2 and USART3 */          
  assert_param(IS_USART_PERIPH_HFC(USARTx, USART_InitStruct->USART_HardwareFlowControl));
  
  usartxbase = (*(u32*)&USARTx);

/*---------------------------- USART CR2 Configuration -----------------------*/
  tmpreg = USARTx->CR2;
  /* Clear STOP[13:12] bits */
  tmpreg &= CR2_STOP_CLEAR_Mask;

  /* Configure the USART Stop Bits, Clock, CPOL, CPHA and LastBit ------------*/
  /* Set STOP[13:12] bits according to USART_StopBits value */
  tmpreg |= (u32)USART_InitStruct->USART_StopBits;
  
  /* Write to USART CR2 */
  USARTx->CR2 = (u16)tmpreg;

/*---------------------------- USART CR1 Configuration -----------------------*/
  tmpreg = USARTx->CR1;
  /* Clear M, PCE, PS, TE and RE bits */
  tmpreg &= CR1_CLEAR_Mask;

  /* Configure the USART Word Length, Parity and mode ----------------------- */
  /* Set the M bits according to USART_WordLength value */
  /* Set PCE and PS bits according to USART_Parity value */
  /* Set TE and RE bits according to USART_Mode value */
  tmpreg |= (u32)USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity |
            USART_InitStruct->USART_Mode;

  /* Write to USART CR1 */
  USARTx->CR1 = (u16)tmpreg;

/*---------------------------- USART CR3 Configuration -----------------------*/  
  tmpreg = USARTx->CR3;
  /* Clear CTSE and RTSE bits */
  tmpreg &= CR3_CLEAR_Mask;

  /* Configure the USART HFC -------------------------------------------------*/
  /* Set CTSE and RTSE bits according to USART_HardwareFlowControl value */
  tmpreg |= USART_InitStruct->USART_HardwareFlowControl;

  /* Write to USART CR3 */
  USARTx->CR3 = (u16)tmpreg;

/*---------------------------- USART BRR Configuration -----------------------*/
  /* Configure the USART Baud Rate -------------------------------------------*/
  RCC_GetClocksFreq(&RCC_ClocksStatus);
  if (usartxbase == USART1_BASE)
  {
    apbclock = RCC_ClocksStatus.PCLK2_Frequency;
  }
  else
  {
    apbclock = RCC_ClocksStatus.PCLK1_Frequency;
  }

  /* Determine the integer part */
  integerdivider = ((0x19 * apbclock) / (0x04 * (USART_InitStruct->USART_BaudRate)));
  tmpreg = (integerdivider / 0x64) << 0x04;

  /* Determine the fractional part */
  fractionaldivider = integerdivider - (0x64 * (tmpreg >> 0x04));
  tmpreg |= ((((fractionaldivider * 0x10) + 0x32) / 0x64)) & ((u8)0x0F);

  /* Write to USART BRR */
  USARTx->BRR = (u16)tmpreg;
}

/*******************************************************************************
* Function Name  : USART_StructInit
* Description    : Fills each USART_InitStruct member with its default value.
* Input          : - USART_InitStruct: pointer to a USART_InitTypeDef structure
*                    which will be initialized.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_StructInit(USART_InitTypeDef* USART_InitStruct)
{
  /* USART_InitStruct members default value */
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
*                  specified parameters in the USART_ClockInitStruct .
* Input          : - USARTx: where x can be 1, 2, 3 to select the USART peripheral.
*                    Note: The Smart Card mode is not available for UART4 and UART5.
*                  - USART_ClockInitStruct: pointer to a USART_ClockInitTypeDef
*                    structure that contains the configuration information for 
*                    the specified USART peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  u32 tmpreg = 0x00;

  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_USART_CLOCK(USART_ClockInitStruct->USART_Clock));
  assert_param(IS_USART_CPOL(USART_ClockInitStruct->USART_CPOL));
  assert_param(IS_USART_CPHA(USART_ClockInitStruct->USART_CPHA));
  assert_param(IS_USART_LASTBIT(USART_ClockInitStruct->USART_LastBit));              
  
/*---------------------------- USART CR2 Configuration -----------------------*/
  tmpreg = USARTx->CR2;
  /* Clear CLKEN, CPOL, CPHA and LBCL bits */
  tmpreg &= CR2_CLOCK_CLEAR_Mask;

  /* Configure the USART Clock, CPOL, CPHA and LastBit ------------*/
  /* Set CLKEN bit according to USART_Clock value */
  /* Set CPOL bit according to USART_CPOL value */
  /* Set CPHA bit according to USART_CPHA value */
  /* Set LBCL bit according to USART_LastBit value */
  tmpreg |= (u32)USART_ClockInitStruct->USART_Clock | USART_ClockInitStruct->USART_CPOL | 
                 USART_ClockInitStruct->USART_CPHA | USART_ClockInitStruct->USART_LastBit;

  /* Write to USART CR2 */
  USARTx->CR2 = (u16)tmpreg;
}

/*******************************************************************************
* Function Name  : USART_ClockStructInit
* Description    : Fills each USART_ClockInitStruct member with its default value.
* Input          : - USART_ClockInitStruct: pointer to a USART_ClockInitTypeDef
*                    structure which will be initialized.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  /* USART_ClockInitStruct members default value */
  USART_ClockInitStruct->USART_Clock = USART_Clock_Disable;
  USART_ClockInitStruct->USART_CPOL = USART_CPOL_Low;
  USART_ClockInitStruct->USART_CPHA = USART_CPHA_1Edge;
  USART_ClockInitStruct->USART_LastBit = USART_LastBit_Disable;
}

/*******************************************************************************
* Function Name  : USART_Cmd
* Description    : Enables or disables the specified USART peripheral.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
*                : - NewState: new state of the USARTx peripheral.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected USART by setting the UE bit in the CR1 register */
    USARTx->CR1 |= CR1_UE_Set;
  }
  else
  {
    /* Disable the selected USART by clearing the UE bit in the CR1 register */
    USARTx->CR1 &= CR1_UE_Reset;
  }
}

/*******************************************************************************
* Function Name  : USART_ITConfig
* Description    : Enables or disables the specified USART interrupts.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
*                  - USART_IT: specifies the USART interrupt sources to be
*                    enabled or disabled.
*                    This parameter can be one of the following values:
*                       - USART_IT_CTS:  CTS change interrupt (not available for
*                                        UART4 and UART5)
*                       - USART_IT_LBD:  LIN Break detection interrupt
*                       - USART_IT_TXE:  Tansmit Data Register empty interrupt
*                       - USART_IT_TC:   Transmission complete interrupt
*                       - USART_IT_RXNE: Receive Data register not empty 
*                                        interrupt
*                       - USART_IT_IDLE: Idle line detection interrupt
*                       - USART_IT_PE:   Parity Error interrupt
*                       - USART_IT_ERR:  Error interrupt(Frame error, noise
*                                        error, overrun error)
*                  - NewState: new state of the specified USARTx interrupts.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_ITConfig(USART_TypeDef* USARTx, u16 USART_IT, FunctionalState NewState)
{
  u32 usartreg = 0x00, itpos = 0x00, itmask = 0x00;
  u32 usartxbase = 0x00;

  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CONFIG_IT(USART_IT));
  assert_param(IS_USART_PERIPH_IT(USARTx, USART_IT)); /* The CTS interrupt is not available for UART4 and UART5 */     
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  usartxbase = (*(u32*)&(USARTx));

  /* Get the USART register index */
  usartreg = (((u8)USART_IT) >> 0x05);

  /* Get the interrupt position */
  itpos = USART_IT & IT_Mask;

  itmask = (((u32)0x01) << itpos);
    
  if (usartreg == 0x01) /* The IT is in CR1 register */
  {
    usartxbase += 0x0C;
  }
  else if (usartreg == 0x02) /* The IT is in CR2 register */
  {
    usartxbase += 0x10;
  }
  else /* The IT is in CR3 register */
  {
    usartxbase += 0x14; 
  }
  if (NewState != DISABLE)
  {
    *(vu32*)usartxbase  |= itmask;
  }
  else
  {
    *(vu32*)usartxbase &= ~itmask;
  }
}

/*******************************************************************************
* Function Name  : USART_DMACmd
* Description    : Enables or disables the USART’s DMA interface.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3 or UART4.
*                    Note: The DMA mode is not available for UART5.
*                  - USART_DMAReq: specifies the DMA request.
*                    This parameter can be any combination of the following values:
*                       - USART_DMAReq_Tx: USART DMA transmit request
*                       - USART_DMAReq_Rx: USART DMA receive request
*                  - NewState: new state of the DMA Request sources.
*                   This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_DMACmd(USART_TypeDef* USARTx, u16 USART_DMAReq, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_1234_PERIPH(USARTx));
  assert_param(IS_USART_DMAREQ(USART_DMAReq));  
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 

  if (NewState != DISABLE)
  {
    /* Enable the DMA transfer for selected requests by setting the DMAT and/or
       DMAR bits in the USART CR3 register */
    USARTx->CR3 |= USART_DMAReq;
  }
  else
  {
    /* Disable the DMA transfer for selected requests by clearing the DMAT and/or
       DMAR bits in the USART CR3 register */
    USARTx->CR3 &= (u16)~USART_DMAReq;
  }
}

/*******************************************************************************
* Function Name  : USART_SetAddress
* Description    : Sets the address of the USART node.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
*                  - USART_Address: Indicates the address of the USART node.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_SetAddress(USART_TypeDef* USARTx, u8 USART_Address)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_ADDRESS(USART_Address)); 
    
  /* Clear the USART address */
  USARTx->CR2 &= CR2_Address_Mask;
  /* Set the USART address node */
  USARTx->CR2 |= USART_Address;
}

/*******************************************************************************
* Function Name  : USART_WakeUpConfig
* Description    : Selects the USART WakeUp method.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
*                  - USART_WakeUp: specifies the USART wakeup method.
*                    This parameter can be one of the following values:
*                        - USART_WakeUp_IdleLine: WakeUp by an idle line detection
*                        - USART_WakeUp_AddressMark: WakeUp by an address mark
* Output         : None
* Return         : None
*******************************************************************************/
void USART_WakeUpConfig(USART_TypeDef* USARTx, u16 USART_WakeUp)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_WAKEUP(USART_WakeUp));
  
  USARTx->CR1 &= CR1_WAKE_Mask;
  USARTx->CR1 |= USART_WakeUp;
}

/*******************************************************************************
* Function Name  : USART_ReceiverWakeUpCmd
* Description    : Determines if the USART is in mute mode or not.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
*                  - NewState: new state of the USART mute mode.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_ReceiverWakeUpCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 
  
  if (NewState != DISABLE)
  {
    /* Enable the USART mute mode  by setting the RWU bit in the CR1 register */
    USARTx->CR1 |= CR1_RWU_Set;
  }
  else
  {
    /* Disable the USART mute mode by clearing the RWU bit in the CR1 register */
    USARTx->CR1 &= CR1_RWU_Reset;
  }
}

/*******************************************************************************
* Function Name  : USART_LINBreakDetectLengthConfig
* Description    : Sets the USART LIN Break detection length.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
*                  - USART_LINBreakDetectLength: specifies the LIN break
*                    detection length.
*                    This parameter can be one of the following values:
*                       - USART_LINBreakDetectLength_10b: 10-bit break detection
*                       - USART_LINBreakDetectLength_11b: 11-bit break detection
* Output         : None
* Return         : None
*******************************************************************************/
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, u16 USART_LINBreakDetectLength)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_LIN_BREAK_DETECT_LENGTH(USART_LINBreakDetectLength));
  
  USARTx->CR2 &= CR2_LBDL_Mask;
  USARTx->CR2 |= USART_LINBreakDetectLength;  
}

/*******************************************************************************
* Function Name  : USART_LINCmd
* Description    : Enables or disables the USART’s LIN mode.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
*                  - NewState: new state of the USART LIN mode.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the LIN mode by setting the LINEN bit in the CR2 register */
    USARTx->CR2 |= CR2_LINEN_Set;
  }
  else
  {
    /* Disable the LIN mode by clearing the LINEN bit in the CR2 register */
    USARTx->CR2 &= CR2_LINEN_Reset;
  }
}

/*******************************************************************************
* Function Name  : USART_SendData
* Description    : Transmits single data through the USARTx peripheral.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
*                  - Data: the data to transmit.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_SendData(USART_TypeDef* USARTx, u16 Data)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DATA(Data)); 
    
  /* Transmit Data */
  USARTx->DR = (Data & (u16)0x01FF);
}

/*******************************************************************************
* Function Name  : USART_ReceiveData
* Description    : Returns the most recent received data by the USARTx peripheral.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
* Output         : None
* Return         : The received data.
*******************************************************************************/
u16 USART_ReceiveData(USART_TypeDef* USARTx)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  
  /* Receive Data */
  return (u16)(USARTx->DR & (u16)0x01FF);
}

/*******************************************************************************
* Function Name  : USART_SendBreak
* Description    : Transmits break characters.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_SendBreak(USART_TypeDef* USARTx)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  
  /* Send break characters */
  USARTx->CR1 |= CR1_SBK_Set;
}

/*******************************************************************************
* Function Name  : USART_SetGuardTime
* Description    : Sets the specified USART guard time.
* Input          : - USARTx: where x can be 1, 2 or 3 to select the USART
*                    peripheral.
*                  Note: The guard time bits are not available for UART4 and UART5.
*                  - USART_GuardTime: specifies the guard time.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_SetGuardTime(USART_TypeDef* USARTx, u8 USART_GuardTime)
{    
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  
  /* Clear the USART Guard time */
  USARTx->GTPR &= GTPR_LSB_Mask;
  /* Set the USART guard time */
  USARTx->GTPR |= (u16)((u16)USART_GuardTime << 0x08);
}

/*******************************************************************************
* Function Name  : USART_SetPrescaler
* Description    : Sets the system clock prescaler.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
*                  Note: The function is used for IrDA mode with UART4 and UART5.
*                  - USART_Prescaler: specifies the prescaler clock.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_SetPrescaler(USART_TypeDef* USARTx, u8 USART_Prescaler)
{ 
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  
  /* Clear the USART prescaler */
  USARTx->GTPR &= GTPR_MSB_Mask;
  /* Set the USART prescaler */
  USARTx->GTPR |= USART_Prescaler;
}

/*******************************************************************************
* Function Name  : USART_SmartCardCmd
* Description    : Enables or disables the USART’s Smart Card mode.
* Input          : - USARTx: where x can be 1, 2 or 3 to select the USART
*                    peripheral. 
*                    Note: The Smart Card mode is not available for UART4 and UART5.
*                  - NewState: new state of the Smart Card mode.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the SC mode by setting the SCEN bit in the CR3 register */
    USARTx->CR3 |= CR3_SCEN_Set;
  }
  else
  {
    /* Disable the SC mode by clearing the SCEN bit in the CR3 register */
    USARTx->CR3 &= CR3_SCEN_Reset;
  }
}

/*******************************************************************************
* Function Name  : USART_SmartCardNACKCmd
* Description    : Enables or disables NACK transmission.
* Input          : - USARTx: where x can be 1, 2 or 3 to select the USART
*                    peripheral. 
*                    Note: The Smart Card mode is not available for UART4 and UART5.
*                  - NewState: new state of the NACK transmission.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));  
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the NACK transmission by setting the NACK bit in the CR3 register */
    USARTx->CR3 |= CR3_NACK_Set;
  }
  else
  {
    /* Disable the NACK transmission by clearing the NACK bit in the CR3 register */
    USARTx->CR3 &= CR3_NACK_Reset;
  }
}

/*******************************************************************************
* Function Name  : USART_HalfDuplexCmd
* Description    : Enables or disables the USART’s Half Duplex communication.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
*                  - NewState: new state of the USART Communication.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the Half-Duplex mode by setting the HDSEL bit in the CR3 register */
    USARTx->CR3 |= CR3_HDSEL_Set;
  }
  else
  {
    /* Disable the Half-Duplex mode by clearing the HDSEL bit in the CR3 register */
    USARTx->CR3 &= CR3_HDSEL_Reset;
  }
}

/*******************************************************************************
* Function Name  : USART_IrDAConfig
* Description    : Configures the USART’s IrDA interface.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
*                  - USART_IrDAMode: specifies the IrDA mode.
*                    This parameter can be one of the following values:
*                       - USART_IrDAMode_LowPower
*                       - USART_IrDAMode_Normal
* Output         : None
* Return         : None
*******************************************************************************/
void USART_IrDAConfig(USART_TypeDef* USARTx, u16 USART_IrDAMode)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_IRDA_MODE(USART_IrDAMode));
    
  USARTx->CR3 &= CR3_IRLP_Mask;
  USARTx->CR3 |= USART_IrDAMode;
}

/*******************************************************************************
* Function Name  : USART_IrDACmd
* Description    : Enables or disables the USART’s IrDA interface.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
*                  - NewState: new state of the IrDA mode.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
    
  if (NewState != DISABLE)
  {
    /* Enable the IrDA mode by setting the IREN bit in the CR3 register */
    USARTx->CR3 |= CR3_IREN_Set;
  }
  else
  {
    /* Disable the IrDA mode by clearing the IREN bit in the CR3 register */
    USARTx->CR3 &= CR3_IREN_Reset;
  }
}

/*******************************************************************************
* Function Name  : USART_GetFlagStatus
* Description    : Checks whether the specified USART flag is set or not.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
*                  - USART_FLAG: specifies the flag to check.
*                    This parameter can be one of the following values:
*                       - USART_FLAG_CTS:  CTS Change flag (not available for 
*                                          UART4 and UART5)
*                       - USART_FLAG_LBD:  LIN Break detection flag
*                       - USART_FLAG_TXE:  Transmit data register empty flag
*                       - USART_FLAG_TC:   Transmission Complete flag
*                       - USART_FLAG_RXNE: Receive data register not empty flag
*                       - USART_FLAG_IDLE: Idle Line detection flag
*                       - USART_FLAG_ORE:  OverRun Error flag
*                       - USART_FLAG_NE:   Noise Error flag
*                       - USART_FLAG_FE:   Framing Error flag
*                       - USART_FLAG_PE:   Parity Error flag
* Output         : None
* Return         : The new state of USART_FLAG (SET or RESET).
*******************************************************************************/
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, u16 USART_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_FLAG(USART_FLAG));
  assert_param(IS_USART_PERIPH_FLAG(USARTx, USART_FLAG)); /* The CTS flag is not available for UART4 and UART5 */   

  if ((USARTx->SR & USART_FLAG) != (u16)RESET)
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
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
*                  - USART_FLAG: specifies the flag to clear.
*                    This parameter can be any combination of the following values:
*                       - USART_FLAG_CTS:  CTS Change flag (not available for
*                                          UART4 and UART5).
*                       - USART_FLAG_LBD:  LIN Break detection flag.
*                       - USART_FLAG_TC:   Transmission Complete flag.
*                       - USART_FLAG_RXNE: Receive data register not empty flag.
*
*                  Notes:
*                        - PE (Parity error), FE (Framing error), NE (Noise error),
*                          ORE (OverRun error) and IDLE (Idle line detected) 
*                          flags are cleared by software sequence: a read 
*                          operation to USART_SR register (USART_GetFlagStatus()) 
*                          followed by a read operation to USART_DR register 
*                          (USART_ReceiveData()).
*                        - RXNE flag can be also cleared by a read to the 
*                          USART_DR register (USART_ReceiveData()).
*                        - TC flag can be also cleared by software sequence: a 
*                          read operation to USART_SR register 
*                          (USART_GetFlagStatus()) followed by a write operation
*                          to USART_DR register (USART_SendData()).                                                      
*                        - TXE flag is cleared only by a write to the USART_DR 
*                          register (USART_SendData()).                        
* Output         : None
* Return         : None
*******************************************************************************/
void USART_ClearFlag(USART_TypeDef* USARTx, u16 USART_FLAG)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLEAR_FLAG(USART_FLAG));
  assert_param(IS_USART_PERIPH_FLAG(USARTx, USART_FLAG)); /* The CTS flag is not available for UART4 and UART5 */   
   
  USARTx->SR = (u16)~USART_FLAG;
}

/*******************************************************************************
* Function Name  : USART_GetITStatus
* Description    : Checks whether the specified USART interrupt has occurred or not.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
*                  - USART_IT: specifies the USART interrupt source to check.
*                    This parameter can be one of the following values:
*                       - USART_IT_CTS:  CTS change interrupt (not available for 
*                                        UART4 and UART5)
*                       - USART_IT_LBD:  LIN Break detection interrupt
*                       - USART_IT_TXE:  Tansmit Data Register empty interrupt
*                       - USART_IT_TC:   Transmission complete interrupt
*                       - USART_IT_RXNE: Receive Data register not empty 
*                                        interrupt
*                       - USART_IT_IDLE: Idle line detection interrupt
*                       - USART_IT_ORE:  OverRun Error interrupt
*                       - USART_IT_NE:   Noise Error interrupt
*                       - USART_IT_FE:   Framing Error interrupt
*                       - USART_IT_PE:   Parity Error interrupt
* Output         : None
* Return         : The new state of USART_IT (SET or RESET).
*******************************************************************************/
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, u16 USART_IT)
{
  u32 bitpos = 0x00, itmask = 0x00, usartreg = 0x00;
  ITStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_GET_IT(USART_IT));
  assert_param(IS_USART_PERIPH_IT(USARTx, USART_IT)); /* The CTS interrupt is not available for UART4 and UART5 */  
  
  /* Get the USART register index */
  usartreg = (((u8)USART_IT) >> 0x05);

  /* Get the interrupt position */
  itmask = USART_IT & IT_Mask;

  itmask = (u32)0x01 << itmask;
  
  if (usartreg == 0x01) /* The IT  is in CR1 register */
  {
    itmask &= USARTx->CR1;
  }
  else if (usartreg == 0x02) /* The IT  is in CR2 register */
  {
    itmask &= USARTx->CR2;
  }
  else /* The IT  is in CR3 register */
  {
    itmask &= USARTx->CR3;
  }
  
  bitpos = USART_IT >> 0x08;

  bitpos = (u32)0x01 << bitpos;
  bitpos &= USARTx->SR;

  if ((itmask != (u16)RESET)&&(bitpos != (u16)RESET))
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
* Description    : Clears the USARTx’s interrupt pending bits.
* Input          : - USARTx: Select the USART or the UART peripheral. 
*                    This parameter can be one of the following values:
*                     - USART1, USART2, USART3, UART4 or UART5.
*                  - USART_IT: specifies the interrupt pending bit to clear.
*                    This parameter can be one of the following values:
*                       - USART_IT_CTS:  CTS change interrupt (not available for 
*                                        UART4 and UART5)
*                       - USART_IT_LBD:  LIN Break detection interrupt
*                       - USART_IT_TC:   Transmission complete interrupt. 
*                       - USART_IT_RXNE: Receive Data register not empty interrupt.
*                    
*                  Notes:
*                        - PE (Parity error), FE (Framing error), NE (Noise error),
*                          ORE (OverRun error) and IDLE (Idle line detected) 
*                          pending bits are cleared by software sequence: a read 
*                          operation to USART_SR register (USART_GetITStatus()) 
*                          followed by a read operation to USART_DR register 
*                          (USART_ReceiveData()).
*                        - RXNE pending bit can be also cleared by a read to the 
*                          USART_DR register (USART_ReceiveData()).
*                        - TC pending bit can be also cleared by software 
*                          sequence: a read operation to USART_SR register 
*                          (USART_GetITStatus()) followed by a write operation
*                          to USART_DR register (USART_SendData()).                                                      
*                        - TXE pending bit is cleared only by a write to the 
*                          USART_DR register (USART_SendData()).  
* Output         : None
* Return         : None
*******************************************************************************/
void USART_ClearITPendingBit(USART_TypeDef* USARTx, u16 USART_IT)
{
  u16 bitpos = 0x00, itmask = 0x00;

  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLEAR_IT(USART_IT));
  assert_param(IS_USART_PERIPH_IT(USARTx, USART_IT)); /* The CTS interrupt is not available for UART4 and UART5 */
  
  bitpos = USART_IT >> 0x08;

  itmask = (u16)((u16)0x01 << bitpos);
  USARTx->SR = (u16)~itmask;
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
