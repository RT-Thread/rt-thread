/*********************************************************************************************************//**
 * @file    ht32f1xxxx_i2c.c
 * @version $Rev:: 2787         $
 * @date    $Date:: 2022-11-23 #$
 * @brief   This file provides all the I2C firmware functions.
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
#include "ht32f1xxxx_i2c.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @defgroup I2C I2C
  * @brief I2C driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup I2C_Private_Define I2C private definitions
  * @{
  */
/* I2C ENI2C mask                                                                                           */
#define CR_ENI2C_SET             ((u32)0x00000008)
#define CR_ENI2C_RESET           ((u32)0xFFFFFFF7)

/* I2C ENGC mask                                                                                            */
#define CR_ENGC_SET              ((u32)0x00000004)
#define CR_ENGC_RESET            ((u32)0xFFFFFFFB)

/* I2C AA mask                                                                                              */
#define CR_ACK_SET               ((u32)0x00000001)
#define CR_ACK_RESET             ((u32)0xFFFFFFFE)

/* I2C PDMANACK mask                                                                                        */
#define CR_PDMANACK_SET          ((u32)0x00000400)
#define CR_PDMANACK_RESET        ((u32)0xFFFFFBFF)

/* I2C ENTOUT mask                                                                                          */
#define CR_ENTOUT_SET            ((u32)0x00001000)
#define CR_ENTOUT_RESET          ((u32)0xFFFFEFFF)

/* I2C COMBFILT mask                                                                                        */
#define CR_COMBFILTER_SET        ((u32)0x00002000)
#define CR_COMBFILTER_RESET      ((u32)0xFFFFDFFF)
/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup I2C_Exported_Functions I2C exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the I2C peripheral registers to their default reset values.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @retval None
 ************************************************************************************************************/
void I2C_DeInit(HT_I2C_TypeDef* I2Cx)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));

  if (I2Cx == HT_I2C0)
  {
    RSTCUReset.Bit.I2C0 = 1;
  }
  else if (I2Cx == HT_I2C1)
  {
    RSTCUReset.Bit.I2C1 = 1;
  }

  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Initialize the I2Cx peripheral according to the specified parameters in the I2C_InitStruct.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param I2C_InitStruct: pointer to a I2C_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void I2C_Init(HT_I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct)
{
  u32 PCLK_Freq = 0;
  s32 sTmp = 0;
  s32 SHPGR = 0;
  s32 SLPGR = 0;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_GENERAL_CALL(I2C_InitStruct->I2C_GeneralCall));
  Assert_Param(IS_I2C_ACKNOWLEDGE_ADDRESS(I2C_InitStruct->I2C_AddressingMode));
  Assert_Param(IS_I2C_ACKNOWLEDGE(I2C_InitStruct->I2C_Acknowledge));
  Assert_Param(IS_I2C_ADDRESS(I2C_InitStruct->I2C_OwnAddress));
  Assert_Param(IS_I2C_SPEED(I2C_InitStruct->I2C_Speed));

  I2Cx->CR = (I2Cx->CR & 0xFFFFFF7A) | I2C_InitStruct->I2C_GeneralCall |
             I2C_InitStruct->I2C_AddressingMode | I2C_InitStruct->I2C_Acknowledge;

  I2Cx->ADDR = I2C_InitStruct->I2C_OwnAddress;

  if (I2Cx == HT_I2C0)
    PCLK_Freq = CKCU_GetPeripFrequency(CKCU_PCLK_I2C0);
  else if (I2Cx == HT_I2C1)
    PCLK_Freq = CKCU_GetPeripFrequency(CKCU_PCLK_I2C1);

  switch (I2Cx->CR & 0xC000)
  {
    case 0:
    {
      sTmp = 6;
      break;
    }
    case 0x4000:
    {
      sTmp = 8;
      break;
    }
    case 0x8000:
    {
      sTmp = 9;
      break;
    }
  }

  SHPGR = (PCLK_Freq * 9)/(I2C_InitStruct->I2C_Speed * 20) - sTmp - I2C_InitStruct->I2C_SpeedOffset;
  SLPGR = (PCLK_Freq * 11)/(I2C_InitStruct->I2C_Speed * 20) - sTmp - I2C_InitStruct->I2C_SpeedOffset;

  SHPGR = (SHPGR < 0) ? 0 : SHPGR;
  SLPGR = (SLPGR < 0) ? 0 : SLPGR;

  I2Cx->SHPGR = SHPGR;
  I2Cx->SLPGR = SLPGR;
}

/*********************************************************************************************************//**
 * @brief Fill each I2C_InitStruct member with its default value.
 * @param I2C_InitStruct: pointer to an I2C_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)
{
  I2C_InitStruct->I2C_GeneralCall = I2C_GENERALCALL_DISABLE;
  I2C_InitStruct->I2C_AddressingMode = I2C_ADDRESSING_7BIT;
  I2C_InitStruct->I2C_Acknowledge = I2C_ACK_DISABLE;
  I2C_InitStruct->I2C_OwnAddress = 0;
  I2C_InitStruct->I2C_Speed = 1000000;
  I2C_InitStruct->I2C_SpeedOffset = 0;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified I2C peripheral.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void I2C_Cmd(HT_I2C_TypeDef* I2Cx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    I2Cx->CR |= CR_ENI2C_SET;
  }
  else
  {
    I2Cx->CR &= CR_ENI2C_RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Generate STOP condition of I2C communication.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @retval None
 ************************************************************************************************************/
void I2C_GenerateSTOP(HT_I2C_TypeDef* I2Cx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));

  I2Cx->CR |= 0x2;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable I2C interrupts.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param I2C_Int: specify if the I2C interrupt source to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg I2C_INT_STA
 *     @arg I2C_INT_STO
 *     @arg I2C_INT_ADRS
 *     @arg I2C_INT_GCS
 *     @arg I2C_INT_ARBLOS
 *     @arg I2C_INT_RXNACK
 *     @arg I2C_INT_BUSERR
 *     @arg I2C_INT_TOUT
 *     @arg I2C_INT_RXDNE
 *     @arg I2C_INT_TXDE
 *     @arg I2C_INT_RXBF
 *     @arg I2C_INT_ALL
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void I2C_IntConfig(HT_I2C_TypeDef* I2Cx, u32 I2C_Int, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_INT(I2C_Int));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    I2Cx->IER |= I2C_Int;
  }
   else
  {
    I2Cx->IER &= (u32)~I2C_Int;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable I2C General Call.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void I2C_GeneralCallCmd(HT_I2C_TypeDef* I2Cx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    I2Cx->CR |= CR_ENGC_SET;
  }
  else
  {
    I2Cx->CR &= CR_ENGC_RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable I2C sending acknowledgement.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void I2C_AckCmd(HT_I2C_TypeDef* I2Cx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    I2Cx->CR |= CR_ACK_SET;
  }
  else
  {
    I2Cx->CR &= CR_ACK_RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Configure own address of the specified I2C.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param I2C_Address: specify own address of I2C.
 * @retval None
 ************************************************************************************************************/
void I2C_SetOwnAddress(HT_I2C_TypeDef* I2Cx, I2C_AddressTypeDef I2C_Address)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_ADDRESS(I2C_Address));

  I2Cx->ADDR = I2C_Address;
}

/*********************************************************************************************************//**
 * @brief Start transmitting to target slave address.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param I2C_Address: specify the slave address which will be transmitted.
 * @param I2C_Direction: This parameter can be I2C_MASTER_READ or I2C_MASTER_WRITE.
 * @retval None
 ************************************************************************************************************/
void I2C_TargetAddressConfig(HT_I2C_TypeDef* I2Cx, I2C_AddressTypeDef I2C_Address, u32 I2C_Direction)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_ADDRESS(I2C_Address));
  Assert_Param(IS_I2C_DIRECTION(I2C_Direction));

  /* Make sure the prior stop command has been finished                                                     */
  while (I2Cx->CR & 0x2);

  if (I2C_Direction != I2C_MASTER_WRITE)
  {
    I2Cx->TAR = I2C_Address | I2C_MASTER_READ;
  }
   else
  {
    I2Cx->TAR = I2C_Address | I2C_MASTER_WRITE;
  }
}

/*********************************************************************************************************//**
 * @brief Send a data word through the I2Cx peripheral.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param I2C_Data: Byte to be transmitted.
 * @retval None
 ************************************************************************************************************/
void I2C_SendData(HT_I2C_TypeDef* I2Cx, u8 I2C_Data)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));

  I2Cx->DR = I2C_Data;
}

/*********************************************************************************************************//**
 * @brief Return the received data by the I2Cx peripheral.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @retval The value of the received data.
 ************************************************************************************************************/
u8 I2C_ReceiveData(HT_I2C_TypeDef* I2Cx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));

  return (u8)I2Cx->DR;
}

/*********************************************************************************************************//**
 * @brief Read the specified I2C register and returns its value.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param I2C_Register: specify the register to read.
 *   This parameter can be one of the following values:
 *     @arg I2C_REGISTER_CR    : Control Register
 *     @arg I2C_REGISTER_IER   : Interrupt Enable Register
 *     @arg I2C_REGISTER_ADDR  : Address Register
 *     @arg I2C_REGISTER_SR    : Status Register
 *     @arg I2C_REGISTER_SHPGR : SCL High Period Generation Register
 *     @arg I2C_REGISTER_SLPGR : SCL Low Period Generation Register
 *     @arg I2C_REGISTER_DR    : Data Register
 *     @arg I2C_REGISTER_TAR   : Target Register
 * @retval None
 ************************************************************************************************************/
u32 I2C_ReadRegister(HT_I2C_TypeDef* I2Cx, u8 I2C_Register)
{
  vu32 tmp = 0;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_REGISTER(I2C_Register));

  tmp = (u32)I2Cx;
  tmp += I2C_Register;
  return (*(u32 *)tmp);
}

/*********************************************************************************************************//**
 * @brief Check whether the specified I2C flag has been set.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param I2C_Flag: specify the flag to be check.
 *   This parameter can be one of the following values:
 *     @arg I2C_FLAG_STA     : I2C start condition transmitted flag (Master mode)
 *     @arg I2C_FLAG_STO     : I2C stop condition detected flag (Slave flag)
 *     @arg I2C_FLAG_ADRS    : I2C address flag
 *     @arg I2C_FLAG_GCS     : I2C general call flag (Slave mode)
 *     @arg I2C_FLAG_ARBLOS  : I2C arbitration loss flag (Master mode)
 *     @arg I2C_FLAG_RXNACK  : I2C received not acknowledge flag
 *     @arg I2C_FLAG_BUSERR  : I2C bus error flag
 *     @arg I2C_FLAG_RXDNE   : I2C Rx data not empty flag
 *     @arg I2C_FLAG_TXDE    : I2C Tx data empty flag
 *     @arg I2C_FLAG_RXBF    : I2C RX buffer full flag
 *     @arg I2C_FLAG_BUSBUSY : I2C bus busy flag
 *     @arg I2C_FLAG_MASTER  : I2C master mode flag (Master flag)
 *     @arg I2C_FLAG_TXNRX   : I2C transmitter mode flag
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus I2C_GetFlagStatus(HT_I2C_TypeDef* I2Cx, u32 I2C_Flag)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_FLAG(I2C_Flag));

  if ((I2Cx->SR & I2C_Flag) != (u32)RESET)
  {
    return (SET);
  }
  else
  {
    return (RESET);
  }
}

/*********************************************************************************************************//**
 * @brief Check whether the specified I2C status has been active.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param I2C_Status: specify the flag that is to be check.
 *   This parameter can be one of the following values:
 *     @arg I2C_MASTER_SEND_START
 *     @arg I2C_MASTER_RECEIVER_MODE
 *     @arg I2C_MASTER_TRANSMITTER_MODE
 *     @arg I2C_MASTER_RX_NOT_EMPTY
 *     @arg I2C_MASTER_RX_NOT_EMPTY_NOBUSY
 *     @arg I2C_MASTER_TX_EMPTY
 *     @arg I2C_MASTER_RX_BUFFER_FULL
 *     @arg I2C_SLAVE_ACK_TRANSMITTER_ADDRESS
 *     @arg I2C_SLAVE_ACK_RECEIVER_ADDRESS
 *     @arg I2C_SLAVE_ACK_GCALL_ADDRESS
 *     @arg I2C_SLAVE_RX_NOT_EMPTY
 *     @arg I2C_SLAVE_RX_NOT_EMPTY_STOP
 *     @arg I2C_SLAVE_TX_EMPTY
 *     @arg I2C_SLAVE_RX_BUFFER_FULL
 *     @arg I2C_SLAVE_RECEIVED_NACK
 *     @arg I2C_SLAVE_RECEIVED_NACK_STOP
 *     @arg I2C_SLAVE_STOP_DETECTED
 * @retval SUCCESS or ERROR
 ************************************************************************************************************/
ErrStatus I2C_CheckStatus(HT_I2C_TypeDef* I2Cx, u32 I2C_Status)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_STATUS(I2C_Status));

  if (I2Cx->SR == I2C_Status)
  {
    return (SUCCESS);
  }
  else
  {
    return (ERROR);
  }
}

/*********************************************************************************************************//**
 * @brief Clear the specified I2C flag.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param I2C_Flag: specify the flag that is to be cleared.
 *   This parameter can be one of the following values:
 *     @arg I2C_FLAG_ARBLOS : I2C arbitration flag
 *     @arg I2C_FLAG_RXNACK : I2C receive not acknowledge flag
 *     @arg I2C_FLAG_BUSERR : I2C Bus error flag
 * @retval None
 ************************************************************************************************************/
void I2C_ClearFlag(HT_I2C_TypeDef* I2Cx, u32 I2C_Flag)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_CLEAR_FLAG(I2C_Flag));

  I2Cx->SR = I2C_Flag;
}

/*********************************************************************************************************//**
 * @brief Set the interval timing of the high period of the I2C clock.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param I2C_HighPeriod: specify the high period that is to be set.
 *   This parameter must be a number between 0 and 0xFFFF.
 * @retval None
 ************************************************************************************************************/
void I2C_SetSCLHighPeriod(HT_I2C_TypeDef* I2Cx, u32 I2C_HighPeriod)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_SCL_HIGH(I2C_HighPeriod));

  I2Cx->SHPGR = I2C_HighPeriod;
}

/*********************************************************************************************************//**
 * @brief Set the interval timing of low period of the I2C clock.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param I2C_LowPeriod: specify the low period that is to be set.
 *   This parameter must be a number between 0 and 0xFFFF.
 * @retval None
 ************************************************************************************************************/
void I2C_SetSCLLowPeriod(HT_I2C_TypeDef* I2Cx, u32 I2C_LowPeriod)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_SCL_LOW(I2C_LowPeriod));

  I2Cx->SLPGR = I2C_LowPeriod;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the I2Cx PDMA interface.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param I2C_PDMAREQ: specify the I2C PDMA transfer request to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg I2C_PDMAREQ_TX: Tx PDMA transfer request
 *     @arg I2C_PDMAREQ_RX: Rx PDMA transfer request
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void I2C_PDMACmd(HT_I2C_TypeDef* I2Cx, u32 I2C_PDMAREQ, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_PDMA_REQ(I2C_PDMAREQ));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    I2Cx->CR |= I2C_PDMAREQ;
  }
  else
  {
    I2Cx->CR &= ~I2C_PDMAREQ;
  }
}

/*********************************************************************************************************//**
 * @brief Specify that the next PDMA transfer is the last one.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void I2C_PDMANACKCmd(HT_I2C_TypeDef* I2Cx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    I2Cx->CR |= CR_PDMANACK_SET;
  }
  else
  {
    I2Cx->CR &= CR_PDMANACK_RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified I2C time out function.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void I2C_TimeOutCmd(HT_I2C_TypeDef* I2Cx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    I2Cx->CR |= CR_ENTOUT_SET;
  }
  else
  {
    I2Cx->CR &= CR_ENTOUT_RESET;
  }
}

/*********************************************************************************************************//**
 * @brief This function is used to set the I2C timeout value.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param I2C_Timeout: specify the timeout value.
 * @retval None
 ************************************************************************************************************/
void I2C_SetTimeOutValue(HT_I2C_TypeDef* I2Cx, u32 I2C_Timeout)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_TIMEOUT(I2C_Timeout));

  I2Cx->TOUT = (I2C_Timeout | (I2Cx->TOUT & 0xFFFF0000));
}

/*********************************************************************************************************//**
 * @brief This function is used to set the prescaler of I2C timeout value.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param I2C_Prescaler: specify the I2C time out prescaler value.
 *   This parameter can be one of the following values:
 *     @arg I2C_PRESCALER_1   : I2C prescaler set to 1
 *     @arg I2C_PRESCALER_2   : I2C prescaler set to 2
 *     @arg I2C_PRESCALER_4   : I2C prescaler set to 4
 *     @arg I2C_PRESCALER_16  : I2C prescaler set to 16
 *     @arg I2C_PRESCALER_32  : I2C prescaler set to 32
 *     @arg I2C_PRESCALER_64  : I2C prescaler set to 64
 *     @arg I2C_PRESCALER_128 : I2C prescaler set to 128
 * @retval None
 ************************************************************************************************************/
void I2C_SetTimeOutPrescaler(HT_I2C_TypeDef* I2Cx, u32 I2C_Prescaler)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_PRESCALER(I2C_Prescaler));

  I2Cx->TOUT = (I2C_Prescaler | (I2Cx->TOUT & 0x0000FFFF));
}

/*********************************************************************************************************//**
 * @brief This function is used to determine the prescaler of I2C timeout value.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param I2C_Mask: specify the bit position of I2C slave address to be masked.
 *   This parameter can be any combination of the following values:
 *     @arg I2C_MASKBIT_0 : Bit 0 of I2C slave address is masked
 *     @arg I2C_MASKBIT_1 : Bit 1 of I2C slave address is masked
 *     @arg I2C_MASKBIT_2 : Bit 2 of I2C slave address is masked
 *     @arg I2C_MASKBIT_3 : Bit 3 of I2C slave address is masked
 *     @arg I2C_MASKBIT_4 : Bit 4 of I2C slave address is masked
 *     @arg I2C_MASKBIT_5 : Bit 5 of I2C slave address is masked
 *     @arg I2C_MASKBIT_6 : Bit 6 of I2C slave address is masked
 *     @arg I2C_MASKBIT_7 : Bit 7 of I2C slave address is masked
 *     @arg I2C_MASKBIT_8 : Bit 8 of I2C slave address is masked
 *     @arg I2C_MASKBIT_9 : Bit 9 of I2C slave address is masked
 * @retval None
 ************************************************************************************************************/
void I2C_AddressMaskConfig(HT_I2C_TypeDef* I2Cx, u32 I2C_Mask)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_ADDRESS_MASK(I2C_Mask));

  I2Cx->ADDMR = I2C_Mask;
}

/*********************************************************************************************************//**
 * @brief Return the received address by the I2Cx peripheral.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @retval The value of the received address.
 ************************************************************************************************************/
u16 I2C_GetAddressBuffer(HT_I2C_TypeDef* I2Cx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));

  return ((u16)I2Cx->ADDSR);
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the combinational filter.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void I2C_CombFilterCmd(HT_I2C_TypeDef* I2Cx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    I2Cx->CR |= CR_COMBFILTER_SET;
  }
  else
  {
    I2Cx->CR &= CR_COMBFILTER_RESET;
  }
}

/*********************************************************************************************************//**
 * @brief This function is used to determine the filter glitch width of 0~2 PCLK.
 * @param I2Cx: where I2Cx is the selected I2C from the I2C peripherals.
 * @param Seq_Filter_Select: specify the glitch width of 0~2 PCLK.
 *   This parameter can be any combination of the following values:
 *     @arg SEQ_FILTER_DISABLE : sequential filter is disabled
 *     @arg SEQ_FILTER_1_PCLK  : filter glitch width of 1 PCLK
 *     @arg SEQ_FILTER_2_PCLK  : filter glitch width of 2 PCLK
 * @retval None
 ************************************************************************************************************/
void I2C_SequentialFilterConfig(HT_I2C_TypeDef* I2Cx, u32 Seq_Filter_Select)
{
  u32 SHPGR = I2Cx->SHPGR;
  u32 SLPGR = I2Cx->SLPGR;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2C(I2Cx));
  Assert_Param(IS_I2C_SEQ_FILTER_MASK(Seq_Filter_Select));

  switch (I2Cx->CR & 0xC000)
  {
    case 0:
      if (Seq_Filter_Select == SEQ_FILTER_1_PCLK)
      {
        if (SHPGR >= 2)
        {
          SHPGR -= 2;
          SLPGR -= 2;
        }
      }
      else if (Seq_Filter_Select == SEQ_FILTER_2_PCLK)
      {
        if (SHPGR >= 2)
        {
          SHPGR -= 3;
          SLPGR -= 3;
        }
      }
      break;

    case 0x4000:
      if (Seq_Filter_Select == SEQ_FILTER_DISABLE)
      {
        SHPGR += 2;
        SLPGR += 2;
      }
      else if (Seq_Filter_Select == SEQ_FILTER_2_PCLK)
      {
        if (SHPGR >= 1)
        {
          SHPGR -= 1;
          SLPGR -= 1;
        }
      }
      break;

    case 0x8000:
      if (Seq_Filter_Select == SEQ_FILTER_DISABLE)
      {
        SHPGR += 3;
        SLPGR += 3;
      }
      else if (Seq_Filter_Select == SEQ_FILTER_1_PCLK)
      {
        SHPGR += 1;
        SLPGR += 1;
      }
      break;

    default:
      break;
  }

  I2Cx->SHPGR = SHPGR;
  I2Cx->SLPGR = SLPGR;
  I2Cx->CR = (I2Cx->CR & 0x3FFF) | Seq_Filter_Select;
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
