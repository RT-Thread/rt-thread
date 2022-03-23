/**
  ******************************************************************************
  * @file               ft32f0xx_usart.c
  * @author             FMD AE
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the Universal synchronous asynchronous receiver
  *                     transmitter (USART):
  *                 + Initialization and Configuration
  *                 + STOP Mode
  *                 + AutoBaudRate
  *                 + Data transfers
  *                 + Multi-Processor Communication
  *                 + LIN mode
  *                 + Half-duplex mode
  *                 + Smartcard mode
  *                 + IrDA mode
  *                 + RS485 mode
  *                 + DMA transfers management
  *                 + Interrupts and flags management
  * @version            V1.0.0
  * @data                   2021-07-01
    ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f0xx_usart.h"
#include "ft32f0xx_rcc.h"

/*!< USART CR1 register clear Mask ((~(uint32_t)0xFFFFE6F3)) */
#define CR1_CLEAR_MASK            ((uint32_t)(USART_CR1_M | USART_CR1_PCE | \
                                              USART_CR1_PS | USART_CR1_TE | \
                                              USART_CR1_RE))

/*!< USART CR2 register clock bits clear Mask ((~(uint32_t)0xFFFFF0FF)) */
#define CR2_CLOCK_CLEAR_MASK      ((uint32_t)(USART_CR2_CLKEN | USART_CR2_CPOL | \
                                              USART_CR2_CPHA | USART_CR2_LBCL))

/*!< USART CR3 register clear Mask ((~(uint32_t)0xFFFFFCFF)) */
#define CR3_CLEAR_MASK            ((uint32_t)(USART_CR3_RTSE | USART_CR3_CTSE))

/*!< USART Interrupts mask */
#define IT_MASK                   ((uint32_t)0x000000FF)


/**
  * @brief  Deinitializes the USARTx peripheral registers to their default reset values.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @retval None
  */
void USART_DeInit(USART_TypeDef* USARTx)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

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
}

/**
  * @brief  Initializes the USARTx peripheral according to the specified
  *         parameters in the USART_InitStruct .
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure that contains
  *         the configuration information for the specified USART peripheral.
  * @retval None
  */
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct)
{
  uint32_t divider = 0, apbclock = 0, tmpreg = 0;
  RCC_ClocksTypeDef RCC_ClocksStatus;

  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_BAUDRATE(USART_InitStruct->USART_BaudRate));
  assert_param(IS_USART_WORD_LENGTH(USART_InitStruct->USART_WordLength));
  assert_param(IS_USART_STOPBITS(USART_InitStruct->USART_StopBits));
  assert_param(IS_USART_PARITY(USART_InitStruct->USART_Parity));
  assert_param(IS_USART_MODE(USART_InitStruct->USART_Mode));
  assert_param(IS_USART_HARDWARE_FLOW_CONTROL(USART_InitStruct->USART_HardwareFlowControl));

  /* Disable USART */
  USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_UE);

  /*---------------------------- USART CR2 Configuration -----------------------*/
  tmpreg = USARTx->CR2;
  /* Clear STOP[13:12] bits */
  tmpreg &= (uint32_t)~((uint32_t)USART_CR2_STOP);

  /* Configure the USART Stop Bits, Clock, CPOL, CPHA and LastBit ------------*/
  /* Set STOP[13:12] bits according to USART_StopBits value */
  tmpreg |= (uint32_t)USART_InitStruct->USART_StopBits;

  /* Write to USART CR2 */
  USARTx->CR2 = tmpreg;

  /*---------------------------- USART CR1 Configuration -----------------------*/
  tmpreg = USARTx->CR1;
  /* Clear M, PCE, PS, TE and RE bits */
  tmpreg &= (uint32_t)~((uint32_t)CR1_CLEAR_MASK);

  /* Configure the USART Word Length, Parity and mode ----------------------- */
  /* Set the M bits according to USART_WordLength value */
  /* Set PCE and PS bits according to USART_Parity value */
  /* Set TE and RE bits according to USART_Mode value */
  tmpreg |= (uint32_t)USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity |
    USART_InitStruct->USART_Mode;

  /* Write to USART CR1 */
  USARTx->CR1 = tmpreg;

  /*---------------------------- USART CR3 Configuration -----------------------*/
  tmpreg = USARTx->CR3;
  /* Clear CTSE and RTSE bits */
  tmpreg &= (uint32_t)~((uint32_t)CR3_CLEAR_MASK);

  /* Configure the USART HFC -------------------------------------------------*/
  /* Set CTSE and RTSE bits according to USART_HardwareFlowControl value */
  tmpreg |= USART_InitStruct->USART_HardwareFlowControl;

  /* Write to USART CR3 */
  USARTx->CR3 = tmpreg;

  /*---------------------------- USART BRR Configuration -----------------------*/
  /* Configure the USART Baud Rate -------------------------------------------*/
  RCC_GetClocksFreq(&RCC_ClocksStatus);

  if (USARTx == USART1)
  {
    apbclock = RCC_ClocksStatus.USART1CLK_Frequency;
  }
  else if (USARTx == USART2)
  {
    apbclock = RCC_ClocksStatus.USART2CLK_Frequency;
  }

  /* Determine the integer part */
  if ((USARTx->CR1 & USART_CR1_OVER8) != 0)
  {
    /* (divider * 10) computing in case Oversampling mode is 8 Samples */
    divider = (uint32_t)((2 * apbclock) / (USART_InitStruct->USART_BaudRate));
    tmpreg  = (uint32_t)((2 * apbclock) % (USART_InitStruct->USART_BaudRate));
  }
  else /* if ((USARTx->CR1 & CR1_OVER8_Set) == 0) */
  {
    /* (divider * 10) computing in case Oversampling mode is 16 Samples */
    divider = (uint32_t)((apbclock) / (USART_InitStruct->USART_BaudRate));
    tmpreg  = (uint32_t)((apbclock) % (USART_InitStruct->USART_BaudRate));
  }

  /* round the divider : if fractional part i greater than 0.5 increment divider */
  if (tmpreg >=  (USART_InitStruct->USART_BaudRate) / 2)
  {
    divider++;
  }

  /* Implement the divider in case Oversampling mode is 8 Samples */
  if ((USARTx->CR1 & USART_CR1_OVER8) != 0)
  {
    /* get the LSB of divider and shift it to the right by 1 bit */
    tmpreg = (divider & (uint16_t)0x000F) >> 1;

    /* update the divider value */
    divider = (divider & (uint16_t)0xFFF0) | tmpreg;
  }

  /* Write to USART BRR */
  USARTx->BRR = (uint16_t)divider;
}

/**
  * @brief  Fills each USART_InitStruct member with its default value.
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
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

/**
  * @brief  Initializes the USARTx peripheral Clock according to the
  *         specified parameters in the USART_ClockInitStruct.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  USART_ClockInitStruct: pointer to a USART_ClockInitTypeDef
  *         structure that contains the configuration information for the specified
  *         USART peripheral.
  * @retval None
  */
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLOCK(USART_ClockInitStruct->USART_Clock));
  assert_param(IS_USART_CPOL(USART_ClockInitStruct->USART_CPOL));
  assert_param(IS_USART_CPHA(USART_ClockInitStruct->USART_CPHA));
  assert_param(IS_USART_LASTBIT(USART_ClockInitStruct->USART_LastBit));
/*---------------------------- USART CR2 Configuration -----------------------*/
  tmpreg = USARTx->CR2;
  /* Clear CLKEN, CPOL, CPHA, LBCL and SSM bits */
  tmpreg &= (uint32_t)~((uint32_t)CR2_CLOCK_CLEAR_MASK);
  /* Configure the USART Clock, CPOL, CPHA, LastBit and SSM ------------*/
  /* Set CLKEN bit according to USART_Clock value */
  /* Set CPOL bit according to USART_CPOL value */
  /* Set CPHA bit according to USART_CPHA value */
  /* Set LBCL bit according to USART_LastBit value */
  tmpreg |= (uint32_t)(USART_ClockInitStruct->USART_Clock | USART_ClockInitStruct->USART_CPOL |
                       USART_ClockInitStruct->USART_CPHA | USART_ClockInitStruct->USART_LastBit);
  /* Write to USART CR2 */
  USARTx->CR2 = tmpreg;
}

/**
  * @brief  Fills each USART_ClockInitStruct member with its default value.
  * @param  USART_ClockInitStruct: pointer to a USART_ClockInitTypeDef
  *         structure which will be initialized.
  * @retval None
  */
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  /* USART_ClockInitStruct members default value */
  USART_ClockInitStruct->USART_Clock = USART_Clock_Disable;
  USART_ClockInitStruct->USART_CPOL = USART_CPOL_Low;
  USART_ClockInitStruct->USART_CPHA = USART_CPHA_1Edge;
  USART_ClockInitStruct->USART_LastBit = USART_LastBit_Disable;
}

/**
  * @brief  Enables or disables the specified USART peripheral.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  NewState: new state of the USARTx peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected USART by setting the UE bit in the CR1 register */
    USARTx->CR1 |= USART_CR1_UE;
  }
  else
  {
    /* Disable the selected USART by clearing the UE bit in the CR1 register */
    USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_UE);
  }
}

/**
  * @brief  Enables or disables the USART's transmitter or receiver.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  USART_Direction: specifies the USART direction.
  *          This parameter can be any combination of the following values:
  *            @arg USART_Mode_Tx: USART Transmitter
  *            @arg USART_Mode_Rx: USART Receiver
  * @param  NewState: new state of the USART transfer direction.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_DirectionModeCmd(USART_TypeDef* USARTx, uint32_t USART_DirectionMode, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_MODE(USART_DirectionMode));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the USART's transfer interface by setting the TE and/or RE bits
       in the USART CR1 register */
    USARTx->CR1 |= USART_DirectionMode;
  }
  else
  {
    /* Disable the USART's transfer interface by clearing the TE and/or RE bits
       in the USART CR3 register */
    USARTx->CR1 &= (uint32_t)~USART_DirectionMode;
  }
}

/**
  * @brief  Enables or disables the USART's 8x oversampling mode.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  NewState: new state of the USART 8x oversampling mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   This function has to be called before calling USART_Init() function
  *         in order to have correct baudrate Divider value.
  * @retval None
  */
void USART_OverSampling8Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the 8x Oversampling mode by setting the OVER8 bit in the CR1 register */
    USARTx->CR1 |= USART_CR1_OVER8;
  }
  else
  {
    /* Disable the 8x Oversampling mode by clearing the OVER8 bit in the CR1 register */
    USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_OVER8);
  }
}

/**
  * @brief  Enables or disables the USART's one bit sampling method.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  NewState: new state of the USART one bit sampling method.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   This function has to be called before calling USART_Cmd() function.
  * @retval None
  */
void USART_OneBitMethodCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the one bit method by setting the ONEBITE bit in the CR3 register */
    USARTx->CR3 |= USART_CR3_ONEBIT;
  }
  else
  {
    /* Disable the one bit method by clearing the ONEBITE bit in the CR3 register */
    USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_ONEBIT);
  }
}

/**
  * @brief  Enables or disables the USART's most significant bit first
  *         transmitted/received following the start bit.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  NewState: new state of the USART most significant bit first
  *         transmitted/received following the start bit.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   This function has to be called before calling USART_Cmd() function.
  * @retval None
  */
void USART_MSBFirstCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the most significant bit first transmitted/received following the
       start bit by setting the MSBFIRST bit in the CR2 register */
    USARTx->CR2 |= USART_CR2_MSBFIRST;
  }
  else
  {
    /* Disable the most significant bit first transmitted/received following the
       start bit by clearing the MSBFIRST bit in the CR2 register */
    USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_MSBFIRST);
  }
}

/**
  * @brief  Enables or disables the binary data inversion.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  NewState: new defined levels for the USART data.
  *          This parameter can be:
  *            @arg ENABLE: Logical data from the data register are send/received in negative
  *                          logic (1=L, 0=H). The parity bit is also inverted.
  *            @arg DISABLE: Logical data from the data register are send/received in positive
  *                          logic (1=H, 0=L)
  * @note   This function has to be called before calling USART_Cmd() function.
  * @retval None
  */
void USART_DataInvCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the binary data inversion feature by setting the DATAINV bit in
       the CR2 register */
    USARTx->CR2 |= USART_CR2_DATAINV;
  }
  else
  {
    /* Disable the binary data inversion feature by clearing the DATAINV bit in
       the CR2 register */
    USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_DATAINV);
  }
}

/**
  * @brief  Enables or disables the Pin(s) active level inversion.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  USART_InvPin: specifies the USART pin(s) to invert.
  *          This parameter can be any combination of the following values:
  *            @arg USART_InvPin_Tx: USART Tx pin active level inversion.
  *            @arg USART_InvPin_Rx: USART Rx pin active level inversion.
  * @param  NewState: new active level status for the USART pin(s).
  *          This parameter can be:
  *            @arg ENABLE: pin(s) signal values are inverted (Vdd =0, Gnd =1).
  *            @arg DISABLE: pin(s) signal works using the standard logic levels (Vdd =1, Gnd =0).
  * @note   This function has to be called before calling USART_Cmd() function.
  * @retval None
  */
void USART_InvPinCmd(USART_TypeDef* USARTx, uint32_t USART_InvPin, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_INVERSTION_PIN(USART_InvPin));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the active level inversion for selected pins by setting the TXINV
       and/or RXINV bits in the USART CR2 register */
    USARTx->CR2 |= USART_InvPin;
  }
  else
  {
    /* Disable the active level inversion for selected requests by clearing the
       TXINV and/or RXINV bits in the USART CR2 register */
    USARTx->CR2 &= (uint32_t)~USART_InvPin;
  }
}

/**
  * @brief  Enables or disables the swap Tx/Rx pins.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  NewState: new state of the USARTx TX/RX pins pinout.
  *          This parameter can be:
  *            @arg ENABLE: The TX and RX pins functions are swapped.
  *            @arg DISABLE: TX/RX pins are used as defined in standard pinout
  * @note   This function has to be called before calling USART_Cmd() function.
  * @retval None
  */
void USART_SWAPPinCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the SWAP feature by setting the SWAP bit in the CR2 register */
    USARTx->CR2 |= USART_CR2_SWAP;
  }
  else
  {
    /* Disable the SWAP feature by clearing the SWAP bit in the CR2 register */
    USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_SWAP);
  }
}

/**
  * @brief  Enables or disables the receiver Time Out feature.
  * @param  USARTx: where x can be 1, 2 to select the USART peripheral.
  * @param  NewState: new state of the USARTx receiver Time Out.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_ReceiverTimeOutCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the receiver time out feature by setting the RTOEN bit in the CR2
       register */
    USARTx->CR2 |= USART_CR2_RTOEN;
  }
  else
  {
    /* Disable the receiver time out feature by clearing the RTOEN bit in the CR2
       register */
    USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_RTOEN);
  }
}

/**
  * @brief  Sets the receiver Time Out value.
  * @param  USARTx: where x can be 1, 2 to select the USART peripheral.
  * @param  USART_ReceiverTimeOut: specifies the Receiver Time Out value.
  * @retval None
  */
void USART_SetReceiverTimeOut(USART_TypeDef* USARTx, uint32_t USART_ReceiverTimeOut)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_USART_TIMEOUT(USART_ReceiverTimeOut));

  /* Clear the receiver Time Out value by clearing the RTO[23:0] bits in the RTOR
     register  */
  USARTx->RTOR &= (uint32_t)~((uint32_t)USART_RTOR_RTO);
  /* Set the receiver Time Out value by setting the RTO[23:0] bits in the RTOR
     register  */
  USARTx->RTOR |= USART_ReceiverTimeOut;
}
/**
  * @}
  */
/**
  * @brief  Enables or disables the Auto Baud Rate.
  * @param  USARTx: where x can be 1or 2  to select the USART peripheral.
  * @param  NewState: new state of the USARTx auto baud rate.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_AutoBaudRateCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the auto baud rate feature by setting the ABREN bit in the CR2
       register */
    USARTx->CR2 |= USART_CR2_ABREN;
  }
  else
  {
    /* Disable the auto baud rate feature by clearing the ABREN bit in the CR2
       register */
    USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_ABREN);
  }
}

/**
  * @brief  Selects the USART auto baud rate method.
  * @param  USARTx: where x can be 1or 2  to select the USART peripheral.
  * @param  USART_AutoBaudRate: specifies the selected USART auto baud rate method.
  *          This parameter can be one of the following values:
  *            @arg USART_AutoBaudRate_StartBit: Start Bit duration measurement.
  *            @arg USART_AutoBaudRate_FallingEdge: Falling edge to falling edge measurement.
  * @note   This function has to be called before calling USART_Cmd() function.
  * @retval None
  */
void USART_AutoBaudRateConfig(USART_TypeDef* USARTx, uint32_t USART_AutoBaudRate)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_USART_AUTOBAUDRATE_MODE(USART_AutoBaudRate));

  USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_ABRMODE);
  USARTx->CR2 |= USART_AutoBaudRate;
}

/**
  * @}
  */
/**
  * @brief  Transmits single data through the USARTx peripheral.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  Data: the data to transmit.
  * @retval None
  */
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DATA(Data));

  /* Transmit Data */
  USARTx->TDR = (Data & (uint16_t)0x01FF);
}

/**
  * @brief  Returns the most recent received data by the USARTx peripheral.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @retval The received data.
  */
uint16_t USART_ReceiveData(USART_TypeDef* USARTx)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  /* Receive Data */
  return (uint16_t)(USARTx->RDR & (uint16_t)0x01FF);
}

/**
  * @}
  */
/**
  * @brief  Sets the address of the USART node.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  USART_Address: Indicates the address of the USART node.
  * @retval None
  */
void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  /* Clear the USART address */
  USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_ADD);
  /* Set the USART address node */
  USARTx->CR2 |=((uint32_t)USART_Address << (uint32_t)0x18);
}

/**
  * @brief  Enables or disables the USART's mute mode.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  NewState: new state of the USART mute mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_MuteModeCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the USART mute mode by setting the MME bit in the CR1 register */
    USARTx->CR1 |= USART_CR1_MME;
  }
  else
  {
    /* Disable the USART mute mode by clearing the MME bit in the CR1 register */
    USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_MME);
  }
}

/**
  * @brief  Selects the USART WakeUp method from mute mode.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  USART_WakeUp: specifies the USART wakeup method.
  *          This parameter can be one of the following values:
  *            @arg USART_WakeUp_IdleLine: WakeUp by an idle line detection
  *            @arg USART_WakeUp_AddressMark: WakeUp by an address mark
  * @retval None
  */
void USART_MuteModeWakeUpConfig(USART_TypeDef* USARTx, uint32_t USART_WakeUp)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_MUTEMODE_WAKEUP(USART_WakeUp));

  USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_WAKE);
  USARTx->CR1 |= USART_WakeUp;
}

/**
  * @brief  Configure the the USART Address detection length.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  USART_AddressLength: specifies the USART address length detection.
  *          This parameter can be one of the following values:
  *            @arg USART_AddressLength_4b: 4-bit address length detection
  *            @arg USART_AddressLength_7b: 7-bit address length detection
  * @retval None
  */
void USART_AddressDetectionConfig(USART_TypeDef* USARTx, uint32_t USART_AddressLength)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_ADDRESS_DETECTION(USART_AddressLength));

  USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_ADDM7);
  USARTx->CR2 |= USART_AddressLength;
}

/**
  * @}
  */
/**
  * @brief  Enables or disables the USART's Half Duplex communication.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  NewState: new state of the USART Communication.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Half-Duplex mode by setting the HDSEL bit in the CR3 register */
    USARTx->CR3 |= USART_CR3_HDSEL;
  }
  else
  {
    /* Disable the Half-Duplex mode by clearing the HDSEL bit in the CR3 register */
    USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_HDSEL);
  }
}

/**
  * @}
  */
/**
  * @brief  Enables or disables the USART's DE functionality.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @param  NewState: new state of the driver enable mode.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_DECmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the DE functionality by setting the DEM bit in the CR3 register */
    USARTx->CR3 |= USART_CR3_DEM;
  }
  else
  {
    /* Disable the DE functionality by clearing the DEM bit in the CR3 register */
    USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_DEM);
  }
}

/**
  * @brief  Configures the USART's DE polarity
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @param  USART_DEPolarity: specifies the DE polarity.
  *          This parameter can be one of the following values:
  *            @arg USART_DEPolarity_Low
  *            @arg USART_DEPolarity_High
  * @retval None
  */
void USART_DEPolarityConfig(USART_TypeDef* USARTx, uint32_t USART_DEPolarity)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DE_POLARITY(USART_DEPolarity));

  USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_DEP);
  USARTx->CR3 |= USART_DEPolarity;
}

/**
  * @brief  Sets the specified RS485 DE assertion time
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @param  USART_DEAssertionTime: specifies the time between the activation of
  *         the DE signal and the beginning of the start bit
  * @retval None
  */
void USART_SetDEAssertionTime(USART_TypeDef* USARTx, uint32_t USART_DEAssertionTime)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DE_ASSERTION_DEASSERTION_TIME(USART_DEAssertionTime));

  /* Clear the DE assertion time */
  USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_DEAT);
  /* Set the new value for the DE assertion time */
  USARTx->CR1 |=((uint32_t)USART_DEAssertionTime << (uint32_t)0x15);
}

/**
  * @brief  Sets the specified RS485 DE deassertion time
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @param  USART_DeassertionTime: specifies the time between the middle of the last
  *         stop bit in a transmitted message and the de-activation of the DE signal
  * @retval None
  */
void USART_SetDEDeassertionTime(USART_TypeDef* USARTx, uint32_t USART_DEDeassertionTime)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DE_ASSERTION_DEASSERTION_TIME(USART_DEDeassertionTime));

  /* Clear the DE deassertion time */
  USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_DEDT);
  /* Set the new value for the DE deassertion time */
  USARTx->CR1 |=((uint32_t)USART_DEDeassertionTime << (uint32_t)0x10);
}

/**
  * @}
  */

/**
  * @brief  Enables or disables the USART's DMA interface.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @param  USART_DMAReq: specifies the DMA request.
  *          This parameter can be any combination of the following values:
  *            @arg USART_DMAReq_Tx: USART DMA transmit request
  *            @arg USART_DMAReq_Rx: USART DMA receive request
  * @param  NewState: new state of the DMA Request sources.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_DMACmd(USART_TypeDef* USARTx, uint32_t USART_DMAReq, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
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
    USARTx->CR3 &= (uint32_t)~USART_DMAReq;
  }
}

/**
  * @brief  Enables or disables the USART's DMA interface when reception error occurs.
  * @param  USARTx: where x can be from 1 to 8 to select the USART peripheral.
  * @param  USART_DMAOnError: specifies the DMA status in case of reception error.
  *          This parameter can be any combination of the following values:
  *            @arg USART_DMAOnError_Enable: DMA receive request enabled when the USART DMA
  *                                          reception error is asserted.
  *            @arg USART_DMAOnError_Disable: DMA receive request disabled when the USART DMA
  *                                           reception error is asserted.
  * @retval None
  */
void USART_DMAReceptionErrorConfig(USART_TypeDef* USARTx, uint32_t USART_DMAOnError)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DMAONERROR(USART_DMAOnError));

  /* Clear the DMA Reception error detection bit */
  USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_DDRE);
  /* Set the new value for the DMA Reception error detection bit */
  USARTx->CR3 |= USART_DMAOnError;
}

/**
  * @}
  */
/**
  * @brief  Enables or disables the specified USART interrupts.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  USART_IT: specifies the USART interrupt sources to be enabled or disabled.
  *          This parameter can be one of the following values:
  *            @arg USART_IT_WU:  Wake up interrupt
  *            @arg USART_IT_CM:  Character match interrupt.
  *            @arg USART_IT_EOB:  End of block interrupt
  *            @arg USART_IT_RTO:  Receive time out interrupt.
  *            @arg USART_IT_CTS:  CTS change interrupt.
  *            @arg USART_IT_LBD:  LIN Break detection interrupt
  *            @arg USART_IT_TXE:  Tansmit Data Register empty interrupt.
  *            @arg USART_IT_TC:  Transmission complete interrupt.
  *            @arg USART_IT_RXNE:  Receive Data register not empty interrupt.
  *            @arg USART_IT_IDLE:  Idle line detection interrupt.
  *            @arg USART_IT_PE:  Parity Error interrupt.
  *            @arg USART_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
  * @param  NewState: new state of the specified USARTx interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_ITConfig(USART_TypeDef* USARTx, uint32_t USART_IT, FunctionalState NewState)
{
  uint32_t usartreg = 0, itpos = 0, itmask = 0;
  uint32_t usartxbase = 0;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CONFIG_IT(USART_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  usartxbase = (uint32_t)USARTx;

  /* Get the USART register index */
  usartreg = (((uint16_t)USART_IT) >> 0x08);

  /* Get the interrupt position */
  itpos = USART_IT & IT_MASK;
  itmask = (((uint32_t)0x01) << itpos);

  if (usartreg == 0x02) /* The IT is in CR2 register */
  {
    usartxbase += 0x04;
  }
  else if (usartreg == 0x03) /* The IT is in CR3 register */
  {
    usartxbase += 0x08;
  }
  else /* The IT is in CR1 register */
  {
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
  * @brief  Enables the specified USART's Request.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  USART_Request: specifies the USART request.
  *          This parameter can be any combination of the following values:
  *            @arg USART_Request_TXFRQ: Transmit data flush ReQuest
  *            @arg USART_Request_RXFRQ: Receive data flush ReQuest
  *            @arg USART_Request_MMRQ: Mute Mode ReQuest
  *            @arg USART_Request_SBKRQ: Send Break ReQuest
  *            @arg USART_Request_ABRRQ: Auto Baud Rate ReQuest
  * @param  NewState: new state of the DMA interface when reception error occurs.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_RequestCmd(USART_TypeDef* USARTx, uint32_t USART_Request, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_REQUEST(USART_Request));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the USART ReQuest by setting the dedicated request bit in the RQR
       register.*/
      USARTx->RQR |= USART_Request;
  }
  else
  {
    /* Disable the USART ReQuest by clearing the dedicated request bit in the RQR
       register.*/
    USARTx->RQR &= (uint32_t)~USART_Request;
  }
}

/**
  * @brief  Enables or disables the USART's Overrun detection.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  USART_OVRDetection: specifies the OVR detection status in case of OVR error.
  *          This parameter can be any combination of the following values:
  *            @arg USART_OVRDetection_Enable: OVR error detection enabled when
  *                                            the USART OVR error is asserted.
  *            @arg USART_OVRDetection_Disable: OVR error detection disabled when
  *                                             the USART OVR error is asserted.
  * @retval None
  */
void USART_OverrunDetectionConfig(USART_TypeDef* USARTx, uint32_t USART_OVRDetection)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_OVRDETECTION(USART_OVRDetection));

  /* Clear the OVR detection bit */
  USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_OVRDIS);
  /* Set the new value for the OVR detection bit */
  USARTx->CR3 |= USART_OVRDetection;
}

/**
  * @brief  Checks whether the specified USART flag is set or not.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral..
  * @param  USART_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg USART_FLAG_REACK:  Receive Enable acknowledge flag.
  *            @arg USART_FLAG_TEACK:  Transmit Enable acknowledge flag.
  *            @arg USART_FLAG_WU:  Wake up flag
  *            @arg USART_FLAG_RWU:  Receive Wake up flag
  *            @arg USART_FLAG_SBK:  Send Break flag.
  *            @arg USART_FLAG_CM:  Character match flag.
  *            @arg USART_FLAG_BUSY:  Busy flag.
  *            @arg USART_FLAG_ABRF:  Auto baud rate flag.
  *            @arg USART_FLAG_ABRE:  Auto baud rate error flag.
  *            @arg USART_FLAG_EOB:  End of block flag
  *            @arg USART_FLAG_RTO:  Receive time out flag.
  *            @arg USART_FLAG_nCTSS:  Inverted nCTS input bit status.
  *            @arg USART_FLAG_CTS:  CTS Change flag.
  *            @arg USART_FLAG_LBD:  LIN Break detection flag
  *            @arg USART_FLAG_TXE:  Transmit data register empty flag.
  *            @arg USART_FLAG_TC:  Transmission Complete flag.
  *            @arg USART_FLAG_RXNE:  Receive data register not empty flag.
  *            @arg USART_FLAG_IDLE:  Idle Line detection flag.
  *            @arg USART_FLAG_ORE:  OverRun Error flag.
  *            @arg USART_FLAG_NE:  Noise Error flag.
  *            @arg USART_FLAG_FE:  Framing Error flag.
  *            @arg USART_FLAG_PE:  Parity Error flag.
  * @retval The new state of USART_FLAG (SET or RESET).
  */
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint32_t USART_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_FLAG(USART_FLAG));

  if ((USARTx->ISR & USART_FLAG) != (uint16_t)RESET)
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
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  USART_FLAG: specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg USART_FLAG_WU:  Wake up flag
  *            @arg USART_FLAG_CM:  Character match flag.
  *            @arg USART_FLAG_EOB:  End of block flag
  *            @arg USART_FLAG_RTO:  Receive time out flag.
  *            @arg USART_FLAG_CTS:  CTS Change flag.
  *            @arg USART_FLAG_LBD:  LIN Break detection flag
  *            @arg USART_FLAG_TC:  Transmission Complete flag.
  *            @arg USART_FLAG_IDLE:  IDLE line detected flag.
  *            @arg USART_FLAG_ORE:  OverRun Error flag.
  *            @arg USART_FLAG_NE: Noise Error flag.
  *            @arg USART_FLAG_FE: Framing Error flag.
  *            @arg USART_FLAG_PE:   Parity Errorflag.
  *
  * @note     RXNE pending bit is cleared by a read to the USART_RDR register
  *           (USART_ReceiveData()) or by writing 1 to the RXFRQ in the register
  *           USART_RQR (USART_RequestCmd()).
  * @note     TC flag can be also cleared by software sequence: a read operation
  *           to USART_SR register (USART_GetFlagStatus()) followed by a write
  *           operation to USART_TDR register (USART_SendData()).
  * @note     TXE flag is cleared by a write to the USART_TDR register (USART_SendData())
  *           or by writing 1 to the TXFRQ in the register USART_RQR (USART_RequestCmd()).
  * @note     SBKF flag is cleared by 1 to the SBKRQ in the register USART_RQR
  *           (USART_RequestCmd()).
  * @retval None
  */
void USART_ClearFlag(USART_TypeDef* USARTx, uint32_t USART_FLAG)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLEAR_FLAG(USART_FLAG));

  USARTx->ICR = USART_FLAG;
}

/**
  * @brief  Checks whether the specified USART interrupt has occurred or not.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  USART_IT: specifies the USART interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg USART_IT_WU:  Wake up interrupt
  *            @arg USART_IT_CM:  Character match interrupt.
  *            @arg USART_IT_EOB:  End of block interrupt
  *            @arg USART_IT_RTO:  Receive time out interrupt.
  *            @arg USART_IT_CTS:  CTS change interrupt.
  *            @arg USART_IT_LBD:  LIN Break detection interrupt
  *            @arg USART_IT_TXE:  Tansmit Data Register empty interrupt.
  *            @arg USART_IT_TC:  Transmission complete interrupt.
  *            @arg USART_IT_RXNE:  Receive Data register not empty interrupt.
  *            @arg USART_IT_IDLE:  Idle line detection interrupt.
  *            @arg USART_IT_ORE:  OverRun Error interrupt.
  *            @arg USART_IT_NE:  Noise Error interrupt.
  *            @arg USART_IT_FE:  Framing Error interrupt.
  *            @arg USART_IT_PE:  Parity Error interrupt.
  * @retval The new state of USART_IT (SET or RESET).
  */
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint32_t USART_IT)
{
  uint32_t bitpos = 0, itmask = 0, usartreg = 0;
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_GET_IT(USART_IT));

  /* Get the USART register index */
  usartreg = (((uint16_t)USART_IT) >> 0x08);
  /* Get the interrupt position */
  itmask = USART_IT & IT_MASK;
  itmask = (uint32_t)0x01 << itmask;

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

  bitpos = USART_IT >> 0x10;
  bitpos = (uint32_t)0x01 << bitpos;
  bitpos &= USARTx->ISR;
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

/**
  * @brief  Clears the USARTx's interrupt pending bits.
  * @param  USARTx: where x can be from 1 to 2 to select the USART peripheral.
  * @param  USART_IT: specifies the interrupt pending bit to clear.
  *          This parameter can be one of the following values:
  *            @arg USART_IT_WU:  Wake up interrupt
  *            @arg USART_IT_CM:  Character match interrupt.
  *            @arg USART_IT_EOB:  End of block interrupt
  *            @arg USART_IT_RTO:  Receive time out interrupt.
  *            @arg USART_IT_CTS:  CTS change interrupt.
  *            @arg USART_IT_LBD:  LIN Break detection interrupt
  *            @arg USART_IT_TC:  Transmission complete interrupt.
  *            @arg USART_IT_IDLE:  IDLE line detected interrupt.
  *            @arg USART_IT_ORE:  OverRun Error interrupt.
  *            @arg USART_IT_NE:  Noise Error interrupt.
  *            @arg USART_IT_FE:  Framing Error interrupt.
  *            @arg USART_IT_PE:  Parity Error interrupt.
  *
  * @note     RXNE pending bit is cleared by a read to the USART_RDR register
  *           (USART_ReceiveData()) or by writing 1 to the RXFRQ in the register
  *           USART_RQR (USART_RequestCmd()).
  * @note     TC pending bit can be also cleared by software sequence: a read
  *           operation to USART_SR register (USART_GetITStatus()) followed by
  *           a write operation to USART_TDR register (USART_SendData()).
  * @note     TXE pending bit is cleared by a write to the USART_TDR register
  *           (USART_SendData()) or by writing 1 to the TXFRQ in the register
  *           USART_RQR (USART_RequestCmd()).
  * @retval None
  */
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint32_t USART_IT)
{
  uint32_t bitpos = 0, itmask = 0;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLEAR_IT(USART_IT));

  bitpos = USART_IT >> 0x10;
  itmask = ((uint32_t)0x01 << (uint32_t)bitpos);
  USARTx->ICR = (uint32_t)itmask;
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

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
