/**
 **************************************************************************
 * File Name    : at32f4xx_usart.c
 * Description  : at32f4xx USART source file
 * Date         : 2018-10-08
 * Version      : V1.0.5
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_usart.h"
#include "at32f4xx_rcc.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup USART
  * @brief USART driver modules
  * @{
  */

/** @defgroup USART_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup USART_Private_Defines
  * @{
  */

#define CTRL1_UEN_Set               ((uint16_t)0x2000)  /*!< USART Enable Mask */
#define CTRL1_UEN_Reset             ((uint16_t)0xDFFF)  /*!< USART Disable Mask */

#define CTRL1_WUMODE_Mask           ((uint16_t)0xF7FF)  /*!< USART WakeUp Method Mask */

#define CTRL1_RECMUTE_Set           ((uint16_t)0x0002)  /*!< USART mute mode Enable Mask */
#define CTRL1_RECMUTE_Reset         ((uint16_t)0xFFFD)  /*!< USART mute mode Enable Mask */
#define CTRL1_SBRK_Set              ((uint16_t)0x0001)  /*!< USART Break Character send Mask */
#define CTRL1_CLEAR_MASK            ((uint16_t)0xE9F3)  /*!< USART CTRL1 Mask */
#define CTRL2_ADDRESS_Mask          ((uint16_t)0xFFF0)  /*!< USART address Mask */

#define CTRL2_LINEN_Set             ((uint16_t)0x4000)  /*!< USART LIN Enable Mask */
#define CTRL2_LINEN_Reset           ((uint16_t)0xBFFF)  /*!< USART LIN Disable Mask */

#define CTRL2_LBDLEN_Mask           ((uint16_t)0xFFDF)  /*!< USART LIN Break detection Mask */
#define CTRL2_STOPB_CLEAR_Mask      ((uint16_t)0xCFFF)  /*!< USART CTRL2 STOP Bits Mask */
#define CTRL2_CLOCK_CLEAR_Mask      ((uint16_t)0xF0FF)  /*!< USART CTRL2 Clock Mask */

#define CTRL3_SCMEN_Set             ((uint16_t)0x0020)  /*!< USART SC Enable Mask */
#define CTRL3_SCMEN_Reset           ((uint16_t)0xFFDF)  /*!< USART SC Disable Mask */

#define CTRL3_NACKEN_Set            ((uint16_t)0x0010)  /*!< USART SC NACK Enable Mask */
#define CTRL3_NACKEN_Reset          ((uint16_t)0xFFEF)  /*!< USART SC NACK Disable Mask */

#define CTRL3_HALFSEL_Set           ((uint16_t)0x0008)  /*!< USART Half-Duplex Enable Mask */
#define CTRL3_HALFSEL_Reset         ((uint16_t)0xFFF7)  /*!< USART Half-Duplex Disable Mask */

#define CTRL3_IRDALP_Mask           ((uint16_t)0xFFFB)  /*!< USART IrDA LowPower mode Mask */
#define CTRL3_CLEAR_Mask            ((uint16_t)0xFCFF)  /*!< USART CR3 Mask */

#define CTRL3_IRDAEN_Set            ((uint16_t)0x0002)  /*!< USART IrDA Enable Mask */
#define CTRL3_IRDAEN_Reset          ((uint16_t)0xFFFD)  /*!< USART IrDA Disable Mask */
#define GTPR_LSB_Mask               ((uint16_t)0x00FF)  /*!< Guard Time Register LSB Mask */
#define GTPR_MSB_Mask               ((uint16_t)0xFF00)  /*!< Guard Time Register MSB Mask */
#define INT_Mask                    ((uint16_t)0x001F)  /*!< USART Interrupt Mask */

/* USART OverSampling-8 Mask */
#define CTRL1_OVER8_Set             ((u16)0x8000)  /* USART OVER8 mode Enable Mask */
#define CTRL1_OVER8_Reset           ((u16)0x7FFF)  /* USART OVER8 mode Disable Mask */

/* USART One Bit Sampling Mask */
#define CTRL3_ONEBITE_Set           ((u16)0x0800)  /* USART ONEBITE mode Enable Mask */
#define CTRL3_ONEBITE_Reset         ((u16)0xF7FF)  /* USART ONEBITE mode Disable Mask */

/**
  * @}
  */

/** @defgroup USART_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup USART_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup USART_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup USART_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the USARTx peripheral registers to their default reset values.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *      USART1, USART2, USART3, UART4 or UART5.
  * @retval None
  */
void USART_Reset(USART_Type* USARTx)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  if (USARTx == USART1)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_USART1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_USART1, DISABLE);
  }
  else if (USARTx == USART2)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_USART2, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_USART2, DISABLE);
  }
  else if (USARTx == USART3)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_USART3, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_USART3, DISABLE);
  }
  else if (USARTx == UART4)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_UART4, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_UART4, DISABLE);
  }
  else if (USARTx == UART5)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_UART5, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_UART5, DISABLE);
  }
}

/**
  * @brief  Initializes the USARTx peripheral according to the specified
  *         parameters in the USART_InitStruct .
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  USART_InitStruct: pointer to a USART_InitType structure
  *         that contains the configuration information for the specified USART
  *         peripheral.
  * @retval None
  */
void USART_Init(USART_Type* USARTx, USART_InitType* USART_InitStruct)
{
  uint32_t tmpreg = 0x00, apbclock = 0x00;
  uint32_t integerdivider = 0x00;
  uint32_t fractionaldivider = 0x00;
  uint32_t usartxbase = 0;
  RCC_ClockType RCC_ClocksStatus;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_BAUDRATE(USART_InitStruct->USART_BaudRate));
  assert_param(IS_USART_WORD_LENGTH(USART_InitStruct->USART_WordLength));
  assert_param(IS_USART_STOPBITS(USART_InitStruct->USART_StopBits));
  assert_param(IS_USART_PARITY(USART_InitStruct->USART_Parity));
  assert_param(IS_USART_MODE(USART_InitStruct->USART_Mode));
  assert_param(IS_USART_HARDWARE_FLOW_CONTROL(USART_InitStruct->USART_HardwareFlowControl));

  /* The hardware flow control is available only for USART1, USART2 and USART3 */
  if (USART_InitStruct->USART_HardwareFlowControl != USART_HardwareFlowControl_None)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }

  usartxbase = (uint32_t)USARTx;

  /*---------------------------- USART CTRL2 Configuration -----------------------*/
  tmpreg = USARTx->CTRL2;
  /* Clear STOP[13:12] bits */
  tmpreg &= CTRL2_STOPB_CLEAR_Mask;
  /* Configure the USART Stop Bits, Clock, CPOL, CPHA and LastBit ------------*/
  /* Set STOP[13:12] bits according to USART_StopBits value */
  tmpreg |= (uint32_t)USART_InitStruct->USART_StopBits;

  /* Write to USART CTRL2 */
  USARTx->CTRL2 = (uint16_t)tmpreg;

  /*---------------------------- USART CTRL1 Configuration -----------------------*/
  tmpreg = USARTx->CTRL1;
  /* Clear M, PCE, PS, TE and RE bits */
  tmpreg &= CTRL1_CLEAR_MASK;
  /* Configure the USART Word Length, Parity and mode ----------------------- */
  /* Set the M bits according to USART_WordLength value */
  /* Set PCE and PS bits according to USART_Parity value */
  /* Set TE and RE bits according to USART_Mode value */
  tmpreg |= (uint32_t)USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity |
            USART_InitStruct->USART_Mode;
  /* Write to USART CTRL1 */
  USARTx->CTRL1 = (uint16_t)tmpreg;

  /*---------------------------- USART CR3 Configuration -----------------------*/
  tmpreg = USARTx->CTRL3;
  /* Clear CTSE and RTSE bits */
  tmpreg &= CTRL3_CLEAR_Mask;
  /* Configure the USART HFC -------------------------------------------------*/
  /* Set CTSE and RTSE bits according to USART_HardwareFlowControl value */
  tmpreg |= USART_InitStruct->USART_HardwareFlowControl;
  /* Write to USART CR3 */
  USARTx->CTRL3 = (uint16_t)tmpreg;

  /*---------------------------- USART BRR Configuration -----------------------*/
  /* Configure the USART Baud Rate -------------------------------------------*/
  RCC_GetClocksFreq(&RCC_ClocksStatus);

  if (usartxbase == USART1_BASE)
  {
    apbclock = RCC_ClocksStatus.APB2CLK_Freq;
  }
  else
  {
    apbclock = RCC_ClocksStatus.APB1CLK_Freq;
  }

  /* Determine the integer part */
  if ((USARTx->CTRL1 & CTRL1_OVER8_Set) != 0)
  {
    /* Integer part computing in case Oversampling mode is 8 Samples */
    integerdivider = ((25 * apbclock) / (2 * (USART_InitStruct->USART_BaudRate)));
  }
  else /* if ((USARTx->CTRL1 & CTRL1_OVER8_Set) == 0) */
  {
    /* Integer part computing in case Oversampling mode is 16 Samples */
    integerdivider = ((25 * apbclock) / (4 * (USART_InitStruct->USART_BaudRate)));
  }

  tmpreg = (integerdivider / 100) << 4;

  /* Determine the fractional part */
  fractionaldivider = integerdivider - (100 * (tmpreg >> 4));

  /* Implement the fractional part in the register */
  if ((USARTx->CTRL1 & CTRL1_OVER8_Set) != 0)
  {
    tmpreg |= ((((fractionaldivider * 8) + 50) / 100)) & ((uint8_t)0x07);
  }
  else /* if ((USARTx->CTRL1 & CTRL1_OVER8_Set) == 0) */
  {
    tmpreg |= ((((fractionaldivider * 16) + 50) / 100)) & ((uint8_t)0x0F);
  }

  /* Write to USART BRR */
  USARTx->BAUDR = (uint16_t)tmpreg;
}

/**
  * @brief  Fills each USART_InitStruct member with its default value.
  * @param  USART_InitStruct: pointer to a USART_InitType structure
  *         which will be initialized.
  * @retval None
  */
void USART_StructInit(USART_InitType* USART_InitStruct)
{
  /* USART_InitStruct members default value */
  USART_InitStruct->USART_BaudRate = 9600;
  USART_InitStruct->USART_WordLength = USART_WordLength_8b;
  USART_InitStruct->USART_StopBits = USART_StopBits_1;
  USART_InitStruct->USART_Parity = USART_Parity_No ;
  USART_InitStruct->USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct->USART_HardwareFlowControl = USART_HardwareFlowControl_None;
}

/**
  * @brief  Initializes the USARTx peripheral Clock according to the
  *          specified parameters in the USART_ClockInitStruct .
  * @param  USARTx: where x can be 1, 2, 3 to select the USART peripheral.
  * @param  USART_ClockInitStruct: pointer to a USART_ClockInitType
  *         structure that contains the configuration information for the specified
  *         USART peripheral.
  * @note The Smart Card and Synchronous modes are not available for UART4 and UART5.
  * @retval None
  */
void USART_ClockInit(USART_Type* USARTx, USART_ClockInitType* USART_ClockInitStruct)
{
  uint32_t tmpreg = 0x00;
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_USART_CLOCK(USART_ClockInitStruct->USART_Clock));
  assert_param(IS_USART_CPOL(USART_ClockInitStruct->USART_CPOL));
  assert_param(IS_USART_CPHA(USART_ClockInitStruct->USART_CPHA));
  assert_param(IS_USART_LASTBIT(USART_ClockInitStruct->USART_LastBit));

  /*---------------------------- USART CTRL2 Configuration -----------------------*/
  tmpreg = USARTx->CTRL2;
  /* Clear CLKEN, CPOL, CPHA and LBCL bits */
  tmpreg &= CTRL2_CLOCK_CLEAR_Mask;
  /* Configure the USART Clock, CPOL, CPHA and LastBit ------------*/
  /* Set CLKEN bit according to USART_Clock value */
  /* Set CPOL bit according to USART_CPOL value */
  /* Set CPHA bit according to USART_CPHA value */
  /* Set LBCL bit according to USART_LastBit value */
  tmpreg |= (uint32_t)USART_ClockInitStruct->USART_Clock | USART_ClockInitStruct->USART_CPOL |
            USART_ClockInitStruct->USART_CPHA | USART_ClockInitStruct->USART_LastBit;
  /* Write to USART CTRL2 */
  USARTx->CTRL2 = (uint16_t)tmpreg;
}

/**
  * @brief  Fills each USART_ClockInitStruct member with its default value.
  * @param  USART_ClockInitStruct: pointer to a USART_ClockInitType
  *         structure which will be initialized.
  * @retval None
  */
void USART_ClockStructInit(USART_ClockInitType* USART_ClockInitStruct)
{
  /* USART_ClockInitStruct members default value */
  USART_ClockInitStruct->USART_Clock = USART_Clock_Disable;
  USART_ClockInitStruct->USART_CPOL = USART_CPOL_Low;
  USART_ClockInitStruct->USART_CPHA = USART_CPHA_1Edge;
  USART_ClockInitStruct->USART_LastBit = USART_LastBit_Disable;
}

/**
  * @brief  Enables or disables the specified USART peripheral.
  * @param  USARTx: Select the USART or the UART peripheral.
  *         This parameter can be one of the following values:
  *           USART1, USART2, USART3, UART4 or UART5.
  * @param  NewState: new state of the USARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_Cmd(USART_Type* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected USART by setting the UE bit in the CTRL1 register */
    USARTx->CTRL1 |= CTRL1_UEN_Set;
  }
  else
  {
    /* Disable the selected USART by clearing the UE bit in the CTRL1 register */
    USARTx->CTRL1 &= CTRL1_UEN_Reset;
  }
}

/**
  * @brief  Enables or disables the specified USART interrupts.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  USART_INT: specifies the USART interrupt sources to be enabled or disabled.
  *   This parameter can be one of the following values:
  *     @arg USART_INT_CTSF:  CTS change interrupt (not available for UART4 and UART5)
  *     @arg USART_INT_LBDF:  LIN Break detection interrupt
  *     @arg USART_INT_TDE:  Transmit Data Register empty interrupt
  *     @arg USART_INT_TRAC:   Transmission complete interrupt
  *     @arg USART_INT_RDNE: Receive Data register not empty interrupt
  *     @arg USART_INT_IDLEF: Idle line detection interrupt
  *     @arg USART_INT_PERR:   Parity Error interrupt
  *     @arg USART_INT_ERR:  Error interrupt(Frame error, noise error, overrun error)
  * @param  NewState: new state of the specified USARTx interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_INTConfig(USART_Type* USARTx, uint16_t USART_INT, FunctionalState NewState)
{
  uint32_t usartreg = 0x00, itpos = 0x00, itmask = 0x00;
  uint32_t usartxbase = 0x00;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CONFIG_INT(USART_INT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* The CTS interrupt is not available for UART4 and UART5 */
  if (USART_INT == USART_INT_CTSF)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }

  usartxbase = (uint32_t)USARTx;

  /* Get the USART register index */
  usartreg = (((uint8_t)USART_INT) >> 0x05);

  /* Get the interrupt position */
  itpos = USART_INT & INT_Mask;
  itmask = (((uint32_t)0x01) << itpos);

  if (usartreg == 0x01) /* The INT is in CTRL1 register */
  {
    usartxbase += 0x0C;
  }
  else if (usartreg == 0x02) /* The INT is in CTRL2 register */
  {
    usartxbase += 0x10;
  }
  else /* The INT is in CR3 register */
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

/**
  * @brief  Enables or disables the USART's DMA interface.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  USART_DMAReq: specifies the DMA request.
  *   This parameter can be any combination of the following values:
  *     @arg USART_DMAReq_Tx: USART DMA transmit request
  *     @arg USART_DMAReq_Rx: USART DMA receive request
  * @param  NewState: new state of the DMA Request sources.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_DMACmd(USART_Type* USARTx, uint16_t USART_DMAReq, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DMAREQ(USART_DMAReq));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the DMA transfer for selected requests by setting the DMAT and/or
       DMAR bits in the USART CR3 register */
    USARTx->CTRL3 |= USART_DMAReq;
  }
  else
  {
    /* Disable the DMA transfer for selected requests by clearing the DMAT and/or
       DMAR bits in the USART CR3 register */
    USARTx->CTRL3 &= (uint16_t)~USART_DMAReq;
  }
}

/**
  * @brief  Sets the address of the USART node.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  USART_Address: Indicates the address of the USART node.
  * @retval None
  */
void USART_SetAddress(USART_Type* USARTx, uint8_t USART_Address)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_ADDRESS(USART_Address));

  /* Clear the USART address */
  USARTx->CTRL2 &= CTRL2_ADDRESS_Mask;
  /* Set the USART address node */
  USARTx->CTRL2 |= USART_Address;
}

/**
  * @brief  Selects the USART WakeUp method.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  USART_WakeUp: specifies the USART wakeup method.
  *   This parameter can be one of the following values:
  *     @arg USART_WakeUp_IdleLine: WakeUp by an idle line detection
  *     @arg USART_WakeUp_AddressMark: WakeUp by an address mark
  * @retval None
  */
void USART_WakeUpConfig(USART_Type* USARTx, uint16_t USART_WakeUp)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_WAKEUP(USART_WakeUp));

  USARTx->CTRL1 &= CTRL1_WUMODE_Mask;
  USARTx->CTRL1 |= USART_WakeUp;
}

/**
  * @brief  Determines if the USART is in mute mode or not.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  NewState: new state of the USART mute mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_ReceiverWakeUpCmd(USART_Type* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the USART mute mode  by setting the RWU bit in the CTRL1 register */
    USARTx->CTRL1 |= CTRL1_RECMUTE_Set;
  }
  else
  {
    /* Disable the USART mute mode by clearing the RWU bit in the CTRL1 register */
    USARTx->CTRL1 &= CTRL1_RECMUTE_Reset;
  }
}

/**
  * @brief  Sets the USART LIN Break detection length.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  USART_LINBreakDetectLength: specifies the LIN break detection length.
  *   This parameter can be one of the following values:
  *     @arg USART_LINBreakDetectLength_10b: 10-bit break detection
  *     @arg USART_LINBreakDetectLength_11b: 11-bit break detection
  * @retval None
  */
void USART_LINBreakDetectLengthConfig(USART_Type* USARTx, uint16_t USART_LINBreakDetectLength)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_LIN_BREAK_DETECT_LENGTH(USART_LINBreakDetectLength));

  USARTx->CTRL2 &= CTRL2_LBDLEN_Mask;
  USARTx->CTRL2 |= USART_LINBreakDetectLength;
}

/**
  * @brief  Enables or disables the USART’s LIN mode.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  NewState: new state of the USART LIN mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_LINCmd(USART_Type* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the LIN mode by setting the LINEN bit in the CTRL2 register */
    USARTx->CTRL2 |= CTRL2_LINEN_Set;
  }
  else
  {
    /* Disable the LIN mode by clearing the LINEN bit in the CTRL2 register */
    USARTx->CTRL2 &= CTRL2_LINEN_Reset;
  }
}

/**
  * @brief  Transmits single data through the USARTx peripheral.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  Data: the data to transmit.
  * @retval None
  */
void USART_SendData(USART_Type* USARTx, uint16_t Data)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DATA(Data));

  /* Transmit Data */
  USARTx->DT = (Data & (uint16_t)0x01FF);
}

/**
  * @brief  Returns the most recent received data by the USARTx peripheral.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @retval The received data.
  */
uint16_t USART_ReceiveData(USART_Type* USARTx)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  /* Receive Data */
  return (uint16_t)(USARTx->DT & (uint16_t)0x01FF);
}

/**
  * @brief  Transmits break characters.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @retval None
  */
void USART_SendBreak(USART_Type* USARTx)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  /* Send break characters */
  USARTx->CTRL1 |= CTRL1_SBRK_Set;
}

/**
  * @brief  Sets the specified USART guard time.
  * @param  USARTx: where x can be 1, 2 or 3 to select the USART peripheral.
  * @param  USART_GuardTime: specifies the guard time.
  * @note The guard time bits are not available for UART4 and UART5.
  * @retval None
  */
void USART_SetGuardTime(USART_Type* USARTx, uint8_t USART_GuardTime)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));

  /* Clear the USART Guard time */
  USARTx->GTP &= GTPR_LSB_Mask;
  /* Set the USART guard time */
  USARTx->GTP |= (uint16_t)((uint16_t)USART_GuardTime << 0x08);
}

/**
  * @brief  Sets the system clock prescaler.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  USART_Prescaler: specifies the prescaler clock.
  * @note   The function is used for IrDA mode with UART4 and UART5.
  * @retval None
  */
void USART_SetPrescaler(USART_Type* USARTx, uint8_t USART_Prescaler)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  /* Clear the USART prescaler */
  USARTx->GTP &= GTPR_MSB_Mask;
  /* Set the USART prescaler */
  USARTx->GTP |= USART_Prescaler;
}

/**
  * @brief  Enables or disables the USART’s Smart Card mode.
  * @param  USARTx: where x can be 1, 2 or 3 to select the USART peripheral.
  * @param  NewState: new state of the Smart Card mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @note The Smart Card mode is not available for UART4 and UART5.
  * @retval None
  */
void USART_SmartCardCmd(USART_Type* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the SC mode by setting the SCEN bit in the CR3 register */
    USARTx->CTRL3 |= CTRL3_SCMEN_Set;
  }
  else
  {
    /* Disable the SC mode by clearing the SCEN bit in the CR3 register */
    USARTx->CTRL3 &= CTRL3_SCMEN_Reset;
  }
}

/**
  * @brief  Enables or disables NACK transmission.
  * @param  USARTx: where x can be 1, 2 or 3 to select the USART peripheral.
  * @param  NewState: new state of the NACK transmission.
  *   This parameter can be: ENABLE or DISABLE.
  * @note The Smart Card mode is not available for UART4 and UART5.
  * @retval None
  */
void USART_SmartCardNACKCmd(USART_Type* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the NACK transmission by setting the NACK bit in the CR3 register */
    USARTx->CTRL3 |= CTRL3_NACKEN_Set;
  }
  else
  {
    /* Disable the NACK transmission by clearing the NACK bit in the CR3 register */
    USARTx->CTRL3 &= CTRL3_NACKEN_Reset;
  }
}

/**
  * @brief  Enables or disables the USART’s Half Duplex communication.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  NewState: new state of the USART Communication.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_HalfDuplexCmd(USART_Type* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Half-Duplex mode by setting the HDSEL bit in the CR3 register */
    USARTx->CTRL3 |= CTRL3_HALFSEL_Set;
  }
  else
  {
    /* Disable the Half-Duplex mode by clearing the HDSEL bit in the CR3 register */
    USARTx->CTRL3 &= CTRL3_HALFSEL_Reset;
  }
}


/**
  * @brief  Enables or disables the USART's 8x oversampling mode.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  NewState: new state of the USART one bit sampling method.
  *   This parameter can be: ENABLE or DISABLE.
  * @note
  *     This function has to be called before calling USART_Init()
  *     function in order to have correct baudrate Divider value.
  * @retval None
  */
void USART_OverSampling8Cmd(USART_Type* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the 8x Oversampling mode by setting the OVER8 bit in the CTRL1 register */
    USARTx->CTRL1 |= CTRL1_OVER8_Set;
  }
  else
  {
    /* Disable the 8x Oversampling mode by clearing the OVER8 bit in the CTRL1 register */
    USARTx->CTRL1 &= CTRL1_OVER8_Reset;
  }
}

/**
  * @brief  Enables or disables the USART's one bit sampling method.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  NewState: new state of the USART one bit sampling method.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_OneBitMethodCmd(USART_Type* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the one bit method by setting the ONEBITE bit in the CR3 register */
    USARTx->CTRL3 |= CTRL3_ONEBITE_Set;
  }
  else
  {
    /* Disable tthe one bit method by clearing the ONEBITE bit in the CR3 register */
    USARTx->CTRL3 &= CTRL3_ONEBITE_Reset;
  }
}

/**
  * @brief  Configures the USART's IrDA interface.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  USART_IrDAMode: specifies the IrDA mode.
  *   This parameter can be one of the following values:
  *     @arg USART_IrDAMode_LowPower
  *     @arg USART_IrDAMode_Normal
  * @retval None
  */
void USART_IrDAConfig(USART_Type* USARTx, uint16_t USART_IrDAMode)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_IRDA_MODE(USART_IrDAMode));

  USARTx->CTRL3 &= CTRL3_IRDALP_Mask;
  USARTx->CTRL3 |= USART_IrDAMode;
}

/**
  * @brief  Enables or disables the USART's IrDA interface.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  NewState: new state of the IrDA mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_IrDACmd(USART_Type* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the IrDA mode by setting the IREN bit in the CR3 register */
    USARTx->CTRL3 |= CTRL3_IRDAEN_Set;
  }
  else
  {
    /* Disable the IrDA mode by clearing the IREN bit in the CR3 register */
    USARTx->CTRL3 &= CTRL3_IRDAEN_Reset;
  }
}

/**
  * @brief  Checks whether the specified USART flag is set or not.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  USART_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg USART_FLAG_CTSF:  CTS Change flag (not available for UART4 and UART5)
  *     @arg USART_FLAG_LBDF:  LIN Break detection flag
  *     @arg USART_FLAG_TDE:  Transmit data register empty flag
  *     @arg USART_FLAG_TRAC:   Transmission Complete flag
  *     @arg USART_FLAG_RDNE: Receive data register not empty flag
  *     @arg USART_FLAG_IDLEF: Idle Line detection flag
  *     @arg USART_FLAG_ORERR:  OverRun Error flag
  *     @arg USART_FLAG_NERR:   Noise Error flag
  *     @arg USART_FLAG_FERR:   Framing Error flag
  *     @arg USART_FLAG_PERR:   Parity Error flag
  * @retval The new state of USART_FLAG (SET or RESET).
  */
FlagStatus USART_GetFlagStatus(USART_Type* USARTx, uint16_t USART_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_FLAG(USART_FLAG));

  /* The CTS flag is not available for UART4 and UART5 */
  if (USART_FLAG == USART_FLAG_CTSF)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }

  if ((USARTx->STS & USART_FLAG) != (uint16_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return bitstatus;
}

/**
  * @brief  Clears the USARTx's pending flags.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  USART_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg USART_FLAG_CTSF:  CTS Change flag (not available for UART4 and UART5).
  *     @arg USART_FLAG_LBDF:  LIN Break detection flag.
  *     @arg USART_FLAG_TRAC:   Transmission Complete flag.
  *     @arg USART_FLAG_RDNE: Receive data register not empty flag.
  *
  * @note
  *   - PE (Parity error), FE (Framing error), NE (Noise error), ORE (OverRun
  *     error) and IDLE (Idle line detected) flags are cleared by software
  *     sequence: a read operation to USART_SR register (USART_GetFlagStatus())
  *     followed by a read operation to USART_DR register (USART_ReceiveData()).
  *   - RXNE flag can be also cleared by a read to the USART_DR register
  *     (USART_ReceiveData()).
  *   - TC flag can be also cleared by software sequence: a read operation to
  *     USART_SR register (USART_GetFlagStatus()) followed by a write operation
  *     to USART_DR register (USART_SendData()).
  *   - TXE flag is cleared only by a write to the USART_DR register
  *     (USART_SendData()).
  * @retval None
  */
void USART_ClearFlag(USART_Type* USARTx, uint16_t USART_FLAG)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLEAR_FLAG(USART_FLAG));

  /* The CTS flag is not available for UART4 and UART5 */
  if ((USART_FLAG & USART_FLAG_CTSF) == USART_FLAG_CTSF)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }

  USARTx->STS = (uint16_t)~USART_FLAG;
}

/**
  * @brief  Checks whether the specified USART interrupt has occurred or not.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  USART_INT: specifies the USART interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg USART_INT_CTSF:  CTS change interrupt (not available for UART4 and UART5)
  *     @arg USART_INT_LBDF:  LIN Break detection interrupt
  *     @arg USART_INT_TDE:  Tansmit Data Register empty interrupt
  *     @arg USART_INT_TRAC:   Transmission complete interrupt
  *     @arg USART_INT_RDNE: Receive Data register not empty interrupt
  *     @arg USART_INT_IDLEF: Idle line detection interrupt
  *     @arg USART_INT_ORERR:  OverRun Error interrupt
  *     @arg USART_INT_NERR:   Noise Error interrupt
  *     @arg USART_INT_FERR:   Framing Error interrupt
  *     @arg USART_INT_PERR:   Parity Error interrupt
  * @retval The new state of USART_INT (SET or RESET).
  */
ITStatus USART_GetITStatus(USART_Type* USARTx, uint16_t USART_INT)
{
  uint32_t bitpos = 0x00, itmask = 0x00, usartreg = 0x00;
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_GET_INT(USART_INT));

  /* The CTS interrupt is not available for UART4 and UART5 */
  if (USART_INT == USART_INT_CTSF)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }

  /* Get the USART register index */
  usartreg = (((uint8_t)USART_INT) >> 0x05);
  /* Get the interrupt position */
  itmask = USART_INT & INT_Mask;
  itmask = (uint32_t)0x01 << itmask;

  if (usartreg == 0x01) /* The INT  is in CTRL1 register */
  {
    itmask &= USARTx->CTRL1;
  }
  else if (usartreg == 0x02) /* The INT  is in CTRL2 register */
  {
    itmask &= USARTx->CTRL2;
  }
  else /* The INT  is in CR3 register */
  {
    itmask &= USARTx->CTRL3;
  }

  bitpos = USART_INT >> 0x08;
  bitpos = (uint32_t)0x01 << bitpos;
  bitpos &= USARTx->STS;

  if ((itmask != (uint16_t)RESET) && (bitpos != (uint16_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return bitstatus;
}

/**
  * @brief  Clears the USARTx's interrupt pending bits.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  USART_INT: specifies the interrupt pending bit to clear.
  *   This parameter can be one of the following values:
  *     @arg USART_INT_CTSF:  CTS change interrupt (not available for UART4 and UART5)
  *     @arg USART_INT_LBDF:  LIN Break detection interrupt
  *     @arg USART_INT_TRAC:   Transmission complete interrupt.
  *     @arg USART_INT_RDNE: Receive Data register not empty interrupt.
  *
  * @note
  *   - PE (Parity error), FE (Framing error), NE (Noise error), ORE (OverRun
  *     error) and IDLE (Idle line detected) pending bits are cleared by
  *     software sequence: a read operation to USART_SR register
  *     (USART_GetITStatus()) followed by a read operation to USART_DR register
  *     (USART_ReceiveData()).
  *   - RXNE pending bit can be also cleared by a read to the USART_DR register
  *     (USART_ReceiveData()).
  *   - TC pending bit can be also cleared by software sequence: a read
  *     operation to USART_SR register (USART_GetITStatus()) followed by a write
  *     operation to USART_DR register (USART_SendData()).
  *   - TXE pending bit is cleared only by a write to the USART_DR register
  *     (USART_SendData()).
  * @retval None
  */
void USART_ClearITPendingBit(USART_Type* USARTx, uint16_t USART_INT)
{
  uint16_t bitpos = 0x00, itmask = 0x00;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLEAR_INT(USART_INT));

  /* The CTS interrupt is not available for UART4 and UART5 */
  if (USART_INT == USART_INT_CTSF)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }

  bitpos = USART_INT >> 0x08;
  itmask = ((uint16_t)0x01 << (uint16_t)bitpos);
  USARTx->STS = (uint16_t)~itmask;
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


