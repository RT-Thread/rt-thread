/*********************************************************************************************************//**
 * @file    ht32f5xxxx_spi.c
 * @version $Rev:: 7322         $
 * @date    $Date:: 2023-10-28 #$
 * @brief   This file provides all the SPI firmware functions.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f5xxxx_spi.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup SPI SPI
  * @brief SPI driver modules
  * @{
  */


#if (LIBCFG_MIDI)
#include "ht32f5xxxx_spi_midi.c"
#endif

/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup SPI_Private_Define SPI private definitions
  * @{
  */
/* SPI SPIEN Mask                                                                                           */
#define CR0_SPIEN_SET       (u32)0x00000001
#define CR0_SPIEN_RESET     (u32)0xFFFFFFFE

/* SPI SELOEN Mask                                                                                          */
#define CR0_SELOEN_SET      (u32)0x00000008
#define CR0_SELOEN_RESET    (u32)0xFFFFFFF7

/* SPI SPI DUALEN Mask                                                                                      */
#define CR0_DUALEN_SET      (u32)0x00000040
#define CR0_DUALEN_RESET    (u32)0xFFFFFFBF

#if (LIBCFG_QSPI)
/* QSPI QUADEN Mask                                                                                         */
#define CR0_QUADEN_SET      (u32)0x00020000
#define CR0_QUADEN_RESET    (u32)0xFFFDFFFF
/* QSPI QDIODIR Mask                                                                                        */
#define CR0_QDIODIR_OUT     (u32)0x00010000
#define CR0_QDIODIR_IN      (u32)0xFFFEFFFF
#endif

/* SPI SPI GUADTEN Mask                                                                                     */
#define CR0_GUADTEN_SET     (u32)0x00000080
#define CR0_GUADTEN_RESET   (u32)0xFFFFFF7F

/* SPI FIFOEN Mask                                                                                          */
#define FCR_FIFOEN_SET      (u32)0x00000400
#define FCR_FIFOEN_RESET    (u32)0xFFFFFBFF

/* SPI DFL Mask                                                                                             */
#if (LIBCFG_SPI_DATA_LENGTH_V01)
#define CR1_DFL_MASK        (u32)0x00000007
#else
#define CR1_DFL_MASK        (u32)0x0000000F
#endif

/* SPI FIFO Mask                                                                                            */
#if (LIBCFG_SPI_FIFO_DEPTH_V01)
#define FCR_FIFO_MASK        (u32)0x00000007
#else
#define FCR_FIFO_MASK        (u32)0x0000000F
#endif

/**
  * @}
  */


/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup SPI_Exported_Functions SPI exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the SPI peripheral registers to their default reset values.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @retval None
 ************************************************************************************************************/
void SPI_DeInit(HT_SPI_TypeDef* SPIx)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));

  if (SPIx == HT_SPI0)
  {
    RSTCUReset.Bit.SPI0 = 1;
  }
  #if (LIBCFG_SPI1)
  else if (SPIx == HT_SPI1)
  {
    RSTCUReset.Bit.SPI1 = 1;
  }
  #endif
  #if (LIBCFG_QSPI)
  else if (SPIx == HT_QSPI)
  {
    RSTCUReset.Bit.QSPI = 1;
  }
  #endif
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Initialize the SPIx peripheral according to the specified parameters in the SPI_InitStruct.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @param SPI_InitStruct: pointer to a SPI_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void SPI_Init(HT_SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
  u32 tmp;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));
  Assert_Param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
  Assert_Param(IS_SPI_FIFO_SET(SPI_InitStruct->SPI_FIFO));
  Assert_Param(IS_SPI_DATALENGTH(SPI_InitStruct->SPI_DataLength));
  Assert_Param(IS_SPI_SEL_MODE(SPI_InitStruct->SPI_SELMode));
  Assert_Param(IS_SPI_SEL_POLARITY(SPI_InitStruct->SPI_SELPolarity));
  Assert_Param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
  Assert_Param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
  Assert_Param(IS_SPI_FIRST_BIT(SPI_InitStruct->SPI_FirstBit));
  Assert_Param(IS_SPI_FIFO_LEVEL(SPI_InitStruct->SPI_RxFIFOTriggerLevel));
  Assert_Param(IS_SPI_FIFO_LEVEL(SPI_InitStruct->SPI_TxFIFOTriggerLevel));
  Assert_Param(IS_SPI_CLOCK_PRESCALER(SPI_InitStruct->SPI_ClockPrescaler));

  /*---------------------------- SPIx Control Register 2 Configuration -------------------------------------*/
  tmp =  SPI_InitStruct->SPI_CPOL;
  if (tmp == SPI_CPOL_LOW)
  {
    tmp |= (0x100 << SPI_InitStruct->SPI_CPHA);
  }
  else
  {
    tmp |= (0x200 >> SPI_InitStruct->SPI_CPHA);
  }

  SPIx->CR1 = SPI_InitStruct->SPI_Mode |  SPI_InitStruct->SPI_DataLength |
              SPI_InitStruct->SPI_SELMode | SPI_InitStruct->SPI_SELPolarity |
              SPI_InitStruct->SPI_FirstBit | tmp;

  /*---------------------------- SPIx FIFO Control Register Configuration ----------------------------------*/
  SPIx->FCR = SPI_InitStruct->SPI_FIFO | SPI_InitStruct->SPI_TxFIFOTriggerLevel |
             (SPI_InitStruct->SPI_RxFIFOTriggerLevel << 4);

  /*---------------------------- SPIx Clock Prescaler Register Configuration -------------------------------*/
  #if (LIBCFG_SPI_CLK_PRE_V01)
  SPIx->CPR = (SPI_InitStruct->SPI_ClockPrescaler - 1);
  #else
  SPIx->CPR = (SPI_InitStruct->SPI_ClockPrescaler / 2) - 1;
  #endif
}

/*********************************************************************************************************//**
 * @brief Fill each SPI_InitStruct member with its default value.
 * @param SPI_InitStruct: pointer to an SPI_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
  /* Initialize the SPI_Mode member                                                                         */
  SPI_InitStruct->SPI_Mode = SPI_SLAVE;

  /* Initialize the SPI_FIFO member                                                                         */
  SPI_InitStruct->SPI_FIFO = SPI_FIFO_DISABLE;

  /* Initialize the SPI_DataLength member                                                                   */
  #if (LIBCFG_SPI_DATA_LENGTH_V01)
  SPI_InitStruct->SPI_DataLength = SPI_DATALENGTH_8;
  #else
  SPI_InitStruct->SPI_DataLength = SPI_DATALENGTH_16;
  #endif

  /* Initialize the SPI_SELMode member                                                                      */
  SPI_InitStruct->SPI_SELMode = SPI_SEL_SOFTWARE;

  /* Initialize the SPI_SELPolarity member                                                                  */
  SPI_InitStruct->SPI_SELPolarity = SPI_SELPOLARITY_LOW;

  /* Initialize the SPI_CPOL member                                                                         */
  SPI_InitStruct->SPI_CPOL = SPI_CPOL_LOW;

  /* Initialize the SPI_CPHA member                                                                         */
  SPI_InitStruct->SPI_CPHA = SPI_CPHA_FIRST;

  /* Initialize the SPI_FirstBit member                                                                     */
  SPI_InitStruct->SPI_FirstBit = SPI_FIRSTBIT_MSB;

  /* Initialize the SPI_RxFIFOTriggerLevel member                                                           */
  SPI_InitStruct->SPI_RxFIFOTriggerLevel = 0;

  /* Initialize the SPI_TxFIFOTriggerLevel member                                                           */
  SPI_InitStruct->SPI_TxFIFOTriggerLevel = 0;

  /* Initialize the SPI_ClockPrescaler member                                                               */
  SPI_InitStruct->SPI_ClockPrescaler = 2;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified SPI peripheral.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void SPI_Cmd(HT_SPI_TypeDef* SPIx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI peripheral                                                                   */
    SPIx->CR0 |= CR0_SPIEN_SET;
  }
  else
  {
    /* Disable the selected SPI peripheral                                                                  */
    SPIx->CR0 &= CR0_SPIEN_RESET;
  }
}

#if (!LIBCFG_SPI_NO_MULTI_MASTER)
/*********************************************************************************************************//**
 * @brief Enable or Disable the SEL output for the specified SPI peripheral.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void SPI_SELOutputCmd(HT_SPI_TypeDef* SPIx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    SPIx->CR0 |= CR0_SELOEN_SET;
  }
  else
  {
    SPIx->CR0 &= CR0_SELOEN_RESET;
  }
}
#endif

/*********************************************************************************************************//**
 * @brief Enable or Disable SPI FIFO.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void SPI_FIFOCmd(HT_SPI_TypeDef* SPIx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    SPIx->FCR |= FCR_FIFOEN_SET;
  }
  else
  {
    SPIx->FCR &= FCR_FIFOEN_RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Configure the data length for the selected SPI.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @param SPI_DataLength: specify data length of the SPI.
 * @retval None
 ************************************************************************************************************/
void SPI_SetDataLength(HT_SPI_TypeDef* SPIx, u16 SPI_DataLength)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));
  Assert_Param(IS_SPI_DATALENGTH(SPI_DataLength));

  /* Clear DFL[x:0] in CR1.
     if Datalength is 16-bit mode, then x = 3
     if Datalength is 8-bit mode, then x = 2                                                                */
  SPIx->CR1 &= (u32)~CR1_DFL_MASK;

  /* Set new DFL[x:0] in CR1.
     if Datalength is 16-bit mode, then x = 3
     if Datalength is 8-bit mode, then x = 2                                                                */
  SPIx->CR1 |= SPI_DataLength;
}

/*********************************************************************************************************//**
 * @brief SEL pin is configured to be driven by hardware or software.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @param SPI_SEL: specify the SPI SEL pin mode.
 *   This parameter can be one of the following values:
 *     @arg SPI_SEL_HARDWARE : SEL is driven by hardware
 *     @arg SPI_SEL_SOFTWARE : SEL is driven by software
 * @retval None
 ************************************************************************************************************/
void SPI_SELModeConfig(HT_SPI_TypeDef* SPIx, u32 SPI_SEL)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));
  Assert_Param(IS_SPI_SEL_MODE(SPI_SEL));

  if (SPI_SEL != SPI_SEL_SOFTWARE)
  {
    SPIx->CR1 |= SPI_SEL_HARDWARE;
  }
  else
  {
    SPIx->CR1 &= ~SPI_SEL_HARDWARE;
  }
}

/*********************************************************************************************************//**
 * @brief Configure the SEL state by software.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @param SPI_SoftwareSEL: specify if the SPI SEL to be active or inactive.
 *   This parameter can be one of the following values:
 *     @arg SPI_SEL_ACTIVE   : activate SEL signal
 *     @arg SPI_SEL_INACTIVE : deactivate SEL signal
 * @retval None
 ************************************************************************************************************/
void SPI_SoftwareSELCmd(HT_SPI_TypeDef* SPIx, u32 SPI_SoftwareSEL)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));
  Assert_Param(IS_SPI_SOFTWARE_SEL(SPI_SoftwareSEL));

  if (SPI_SoftwareSEL != SPI_SEL_INACTIVE)
  {
    SPIx->CR0 |= SPI_SEL_ACTIVE;
  }
  else
  {
    SPIx->CR0 &= SPI_SEL_INACTIVE;
  }
}

/*********************************************************************************************************//**
 * @brief Send a data through the SPIx peripheral.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @param SPI_Data: the data to be transmitted.
 * @retval None
 ************************************************************************************************************/
void SPI_SendData(HT_SPI_TypeDef* SPIx, SPI_DataTypeDef SPI_Data)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));
  Assert_Param(IS_SPI_DATA(SPI_Data));

  SPIx->DR = SPI_Data;
}

/*********************************************************************************************************//**
 * @brief Return the received data through the SPIx peripheral
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @retval The value of the received data.
 ************************************************************************************************************/
SPI_DataTypeDef SPI_ReceiveData(HT_SPI_TypeDef* SPIx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));

  return (SPI_DataTypeDef)SPIx->DR;
}

/*********************************************************************************************************//**
 * @brief Set the value of SPI FIFO Time Out.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @param SPI_Timeout: specify the value of Time Out.
 * @retval None
 ************************************************************************************************************/
void SPI_SetTimeOutValue(HT_SPI_TypeDef* SPIx, SPI_TimeoutTypeDef SPI_Timeout)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));

  SPIx->FTOCR = SPI_Timeout;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified SPI interrupt.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @param SPI_Int: specify if the SPI interrupt source to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg SPI_INT_TXBE  : SPI Tx buffer empty interrupt
 *     @arg SPI_INT_TXE   : SPI Tx empty interrupt
 *     @arg SPI_INT_RXBNE : SPI Rx buffer not empty interrupt
 *     @arg SPI_INT_WC    : SPI write collision interrupt
 *     @arg SPI_INT_RO    : SPI read overrun interrupt
 *     @arg SPI_INT_MF    : SPI mode fault interrupt
 *     @arg SPI_INT_SA    : SPI slave abort interrupt
 *     @arg SPI_INT_TO    : SPI time out interrupt
 *     @arg SPI_INT_ALL   : All SPI interrupt
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void SPI_IntConfig(HT_SPI_TypeDef* SPIx, u32 SPI_Int, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));
  Assert_Param(IS_SPI_INT(SPI_Int));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    SPIx->IER |= SPI_Int;
  }
  else
  {
    SPIx->IER &= (u32)~SPI_Int;
  }
}

/*********************************************************************************************************//**
 * @brief Check whether the specified SPI flag has been set or not.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @param SPI_Flag: specify the flag that is to be check.
 *   This parameter can be one of the following values:
 *     @arg SPI_FLAG_TXBE  : SPI Tx buffer empty flag
 *     @arg SPI_FLAG_TXE   : SPI Tx empty flag
 *     @arg SPI_FLAG_RXBNE : SPI Rx buffer not empty flag
 *     @arg SPI_FLAG_WC    : SPI write collision flag
 *     @arg SPI_FLAG_RO    : SPI read overrun flag
 *     @arg SPI_FLAG_MF    : SPI mode fault flag
 *     @arg SPI_FLAG_SA    : SPI slave abort flag
 *     @arg SPI_FLAG_TOUT  : SPI time out flag
 *     @arg SPI_FLAG_BUSY  : SPI busy flag
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus SPI_GetFlagStatus(HT_SPI_TypeDef* SPIx, u32 SPI_Flag)
{
  FlagStatus bitstatus = RESET;
  u32 statusreg = 0;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));
  Assert_Param(IS_SPI_FLAG(SPI_Flag));

  statusreg = SPIx->SR;

  if ((statusreg & SPI_Flag) != (u32)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return bitstatus;
}

/*********************************************************************************************************//**
 * @brief Return the status of specified SPI FIFO.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @param SPI_FIFODirection: specify the FIFO that is to be checked.
 *   This parameter can be one of the following values:
 *     @arg SPI_FIFO_TX :
 *     @arg SPI_FIFO_RX :
 * @retval The number of data in Tx FIFO or Rx FIFO.
 ************************************************************************************************************/
u8 SPI_GetFIFOStatus(HT_SPI_TypeDef* SPIx, u32 SPI_FIFODirection)
{
  u32 tmpreg;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));
  Assert_Param(IS_SPI_FIFO_DIRECTION(SPI_FIFODirection));

  if (SPI_FIFODirection == SPI_FIFO_TX)
  {
    tmpreg = SPIx->FSR & FCR_FIFO_MASK;
  }
  else
  {
    tmpreg = (SPIx->FSR & (FCR_FIFO_MASK << 4)) >> 4;
  }

  return (u8)tmpreg;
}

/*********************************************************************************************************//**
 * @brief Clear the specified SPI flag.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @param SPI_Flag: specify the flag that is to be cleared.
 *   This parameter can be one of the following values:
 *     @arg SPI_FLAG_WC   : SPI write collision flag
 *     @arg SPI_FLAG_RO   : SPI read overrun flag
 *     @arg SPI_FLAG_MF   : SPI mode fault flag
 *     @arg SPI_FLAG_SA   : SPI slave abort flag
 *     @arg SPI_FLAG_TOUT : SPI time out flag
 * @retval None
 ************************************************************************************************************/
void SPI_ClearFlag(HT_SPI_TypeDef* SPIx, u32 SPI_Flag)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));
  Assert_Param(IS_SPI_FLAG_CLEAR(SPI_Flag));

  SPIx->SR = SPI_Flag;
}

/*********************************************************************************************************//**
 * @brief Set the trigger level of SPI FIFO.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @param SPI_FIFODirection: specify the FIFO that is to be set.
 *   This parameter can be one of the following values:
 *     @arg SPI_FIFO_TX :
 *     @arg SPI_FIFO_RX :
 * @param SPI_FIFOLevel: Specify the FIFO trigger level.
 * @retval None
 ************************************************************************************************************/
void SPI_FIFOTriggerLevelConfig(HT_SPI_TypeDef* SPIx, u32 SPI_FIFODirection, u8 SPI_FIFOLevel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));
  Assert_Param(IS_SPI_FIFO_DIRECTION(SPI_FIFODirection));
  Assert_Param(IS_SPI_FIFO_LEVEL(SPI_FIFOLevel));

  if (SPI_FIFODirection == SPI_FIFO_TX)
  {
    SPIx->FCR = ((SPIx->FCR & (0x00000400 | (FCR_FIFO_MASK << 4))) | SPI_FIFOLevel);
  }
  else
  {
    SPIx->FCR = ((SPIx->FCR & (0x00000400 | FCR_FIFO_MASK)) | (SPI_FIFOLevel << 4));
  }
}

#if (LIBCFG_PDMA)
/*********************************************************************************************************//**
 * @brief Enable or Disable the SPIx PDMA interface.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @param SPI_PDMAREQ: specify the SPI PDMA transfer request to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg SPI_PDMAREQ_TX : Tx PDMA transfer request
 *     @arg SPI_PDMAREQ_RX : Rx PDMA transfer request
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void SPI_PDMACmd(HT_SPI_TypeDef* SPIx, u32 SPI_PDMAREQ, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));
  Assert_Param(IS_SPI_PDMA_REQ(SPI_PDMAREQ));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    SPIx->CR0 |= SPI_PDMAREQ;
  }
  else
  {
    SPIx->CR0 &= ~SPI_PDMAREQ;
  }
}
#endif

#if (!LIBCFG_SPI_NO_DUAL)
/*********************************************************************************************************//**
 * @brief Enable or Disable the SPIx dual port read interface.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void SPI_DUALCmd(HT_SPI_TypeDef* SPIx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  (NewState == ENABLE)?(SPIx->CR0 |= CR0_DUALEN_SET):(SPIx->CR0 &= CR0_DUALEN_RESET);
}
#endif

#if (LIBCFG_QSPI)
/*********************************************************************************************************//**
 * @brief Enable or Disable the QSPI quad port interface.
 * @param SPIx: where SPIx is the selected QSPI from the QSPI peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void QSPI_QuadCmd(HT_SPI_TypeDef* SPIx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_QSPI(SPIx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState == DISABLE)
  {
    QSPI_DirectionConfig(SPIx, SIO_DIR_IN);
    SPIx->CR0 &= CR0_QUADEN_RESET;
  }
  else
  {
    SPIx->CR0 |= CR0_QUADEN_SET;
  }
}

/*********************************************************************************************************//**
 * @brief Configure the direction of SIO pins in dual or quad mode.
 * @param SPIx: where SPIx is the selected QSPI from the QSPI peripherals.
 * @param SIO_DIR_INorOUT:
 *   This parameter can be one of below:
 *     @arg SIO_DIR_IN  : The SIO pins are input mode
 *     @arg SIO_DIR_OUT : The SIO pins are output mode
 * @retval None
 ************************************************************************************************************/
void QSPI_DirectionConfig(HT_SPI_TypeDef* SPIx, SIO_DIR_Enum SIO_DIR_INorOUT)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_QSPI(SPIx));
  Assert_Param(IS_SIO_DIR(SIO_DIR_INorOUT));

  if (SIO_DIR_INorOUT != SIO_DIR_IN)
    SPIx->CR0 |= CR0_QDIODIR_OUT;
  else
    SPIx->CR0 &= CR0_QDIODIR_IN;
}
#endif

/*********************************************************************************************************//**
 * @brief Enable or Disable the SPIx guard time selection function.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void SPI_GUARDTCmd(HT_SPI_TypeDef* SPIx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  (NewState == ENABLE) ? (SPIx->CR0 |= CR0_GUADTEN_SET) : (SPIx->CR0 &= CR0_GUADTEN_RESET);
}

/*********************************************************************************************************//**
 * @brief Set the SPIx guard time length.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @param Guard_Time: number of SCK to be the guard time length.
 *   This parameter can be: SPI_GUADTIME_1_SCK to SPI_GUADTIME_16_SCK.
 * @retval None
 ************************************************************************************************************/
void SPI_GUARDTConfig(HT_SPI_TypeDef* SPIx, u32 Guard_Time)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));
  Assert_Param(IS_SPI_GUADTIME(Guard_Time));

  SPIx->CR0 = (SPIx->CR0 & 0xF0FF) | (Guard_Time << 8);
}

/*********************************************************************************************************//**
 * @brief Set the SPIx chip select hold time.
 * @param SPIx: where SPIx is the selected SPI from the SPI peripherals.
 * @param CS_Hold_Time: number of SCK to be the hold time length.
 *   This parameter can be: 0 ~ 15
 * @retval None
 ************************************************************************************************************/
void SPI_SELHTConfig(HT_SPI_TypeDef* SPIx, u32 CS_Hold_Time)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SPI(SPIx));
  Assert_Param(IS_SPI_SELHOLDTIME(CS_Hold_Time));

  SPIx->CR0 = (SPIx->CR0 & 0x0FFF) | (CS_Hold_Time << 12);
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
