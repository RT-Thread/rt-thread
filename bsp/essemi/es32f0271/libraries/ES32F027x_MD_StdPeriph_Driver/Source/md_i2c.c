/**
  ******************************************************************************
  * @file    md_i2c.c
  * @brief   ES32F0271 I2C Source File.
  *
  * @version V1.00.01
  * @date    4/12/2018
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */

/* Includes -------------------------------------------------------------------*/
#include "md_i2c.h"
#include "md_rcu.h"
#include <stdio.h>
#include "stdint.h"
/** @addtogroup Micro_Driver
  * @{
  */

/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/

/**
  * @brief  Initialize the I2C registers according to the specified parameters in I2C_InitStruct.
  * @note   The parameters in md_i2c_init should be expected values. Otherwise, ERROR result will be returned.
  * @param  I2Cx I2C Instance
  * @param  I2C_InitStruct pointer to a @ref md_i2c_inittypedef structure
  * @retval An ErrorStatus enumeration value. (Return always SUCCESS)
  */
ErrorStatus md_i2c_init(I2C_TypeDef *I2Cx, md_i2c_inittypedef *I2C_InitStruct)
{
  ErrorStatus status = ERROR;
  uint8_t pllmulnow;

  /* Check the I2C Instance I2Cx */
  assert_param(IS_MD_I2C_ALL_INSTANCE(I2Cx));

  /* Check the I2C parameters from I2C_InitStruct */
  assert_param(IS_MD_I2C_TIMING(I2C_InitStruct->Timing));
  assert_param(IS_MD_I2C_ADDRSIZE(I2C_InitStruct->AddrSize));
  assert_param(IS_MD_I2C_ADDRESS1(I2C_InitStruct->Address1));
  assert_param(IS_MD_I2C_DUALADDRESSMODE(I2C_InitStruct->DualAddressMode));
  assert_param(IS_MD_I2C_ADDRESS2(I2C_InitStruct->Address2));
  assert_param(IS_MD_I2C_ADDRESS2MASKS(I2C_InitStruct->Address2Masks));
  /* Check the PLL clock, if not corrt, modify it */
  pllmulnow = md_rcu_get_cfg_pllmul(RCU);

  if (pllmulnow != (uint8_t)((I2C_InitStruct->Timing) >> 28))
  {
    md_rcu_pllreinit((uint8_t)((I2C_InitStruct->Timing) >> 28));
  }

  md_i2c_disable_con1_pe(I2Cx);
  md_i2c_set_timingr_presc(I2Cx, ((I2C_InitStruct->Timing) >> 24) & 0xF);
  md_i2c_set_timingr_scll(I2Cx, ((I2C_InitStruct->Timing) >> 16) & 0xFF);
  md_i2c_set_timingr_sclh(I2Cx, ((I2C_InitStruct->Timing) >> 8) & 0xFF);
  md_i2c_set_timingr_sdadel(I2Cx, ((I2C_InitStruct->Timing) >> 4) & 0xF);
  md_i2c_set_timingr_scldel(I2Cx, (I2C_InitStruct->Timing) & 0xF);
  md_i2c_enable_con1_pe(I2Cx);

  md_i2c_disable_addr1_oa1en(I2Cx);
  md_i2c_set_addr1_oa1(I2Cx, I2C_InitStruct->Address1);

  if (I2C_InitStruct->AddrSize == MD_I2C_OA1_10BIT)
    md_i2c_set_addr1_oa1mode(I2Cx, MD_I2C_OA1_10BIT);
  else
    md_i2c_set_addr1_oa1mode(I2Cx, MD_I2C_OA1_7BIT);

  md_i2c_enable_addr1_oa1en(I2Cx);

  if (I2C_InitStruct->DualAddressMode == MD_I2C_DUALADDRESS_ENABLE)
  {
    md_i2c_disable_addr2_oa2en(I2Cx);
    md_i2c_set_addr2_oa2mask(I2Cx, I2C_InitStruct->Address2Masks);
    md_i2c_set_addr2_oa2(I2Cx, I2C_InitStruct->Address2);
    md_i2c_enable_addr2_oa2en(I2Cx);
  }

  status = SUCCESS;

  return status;
}

/**
  * @brief  Set each @ref md_i2c_inittypedef field to default value.
  * @param  UART_InitStruct pointer to a @ref md_i2c_inittypedef structure
  *         whose fields will be set to default values.
  * @retval None
  */
void md_i2c_struct_init(md_i2c_inittypedef *I2C_InitStruct)
{
  /* Set UART_InitStruct fields to default values */
  I2C_InitStruct->Timing          = CLK100kHz48M;
  I2C_InitStruct->AddrSize        = MD_I2C_ADDRESSINGMODE_7BIT;
  I2C_InitStruct->Address1        = 0x50 << 1;
  I2C_InitStruct->DualAddressMode = MD_I2C_DUALADDRESS_DISABLE;
  I2C_InitStruct->Address2        = 0x70 << 1;
  I2C_InitStruct->Address2Masks   = MD_I2C_ADDR2_NOMASK;
}

/**
  * @brief  Transmits in master mode an amount of data in blocking mode.
  * @param  I2Cx I2C Instance
  * @param  The number of bytes to be transmitted
  * @param  Enable/Disable 10-bit addressing mode
  * @param  Device(slave) address
  * @param  The pointer to a data buffer
  * @retval None
  */
void md_i2c_master_send(I2C_TypeDef *I2Cx, uint8_t Nbyte, uint32_t addr10, uint16_t DevAddr, uint8_t *txbuf)
{
  uint8_t index;

  /* Config Device(slave) address */
  if (addr10 == MD_I2C_ADDRESSINGMODE_10BIT)
    md_i2c_set_con2_add10(I2Cx, MD_I2C_ADDRESSINGMODE_10BIT);
  else
    md_i2c_set_con2_add10(I2Cx, MD_I2C_ADDRESSINGMODE_7BIT);

  md_i2c_set_con2_sadd(I2Cx, DevAddr);
  md_i2c_set_con2_nbytes(I2Cx, Nbyte);
  md_i2c_set_fcon_txfrst(I2Cx, MD_I2C_TXFIFO_RESET);
  md_i2c_set_con2_rd_wrn(I2Cx, MD_I2C_MASTER_WRITE);
  md_i2c_set_con2_reload(I2Cx, MD_I2C_NORELOAD_MODE);
  /* When NBYTES is matched, the communication will be automatically stop */
  md_i2c_set_con2_autoend(I2Cx, MD_I2C_AUTOEND_MODE);

  if (Nbyte <= 8)
  {
    for (index = 0; index < Nbyte; index++)
      md_i2c_send(I2Cx, *txbuf++);

    Nbyte = 0;
  }
  else
  {
    for (index = 0; index < 8; index++)
      md_i2c_send(I2Cx, *txbuf++);

    Nbyte -= 8;
  }

  /* Start the I2C communication */
  md_i2c_set_con2_start(I2Cx, MD_I2C_START_GENERATION);

  while (Nbyte > 0)
  {
    while (md_i2c_is_active_stat_txf(I2Cx));

    md_i2c_send(I2Cx, *txbuf++);
    Nbyte--;
  }
}

/**
  * @brief  Receives in master mode an amount of data in blocking mode.
  * @param  I2Cx I2C Instance
  * @param  The number of bytes to be received
  * @param  Enable/Disable 10-bit addressing mode
  * @param  Device(slave) address
  * @param  The pointer to a data buffer
  * @retval None
  */
void md_i2c_master_rece(I2C_TypeDef *I2Cx, uint8_t Nbyte, uint32_t addr10, uint16_t DevAddr, uint8_t *rxbuf)
{
  /* Config Device(slave) address */
  if (addr10 == MD_I2C_ADDRESSINGMODE_10BIT)
    md_i2c_set_con2_add10(I2Cx, MD_I2C_ADDRESSINGMODE_10BIT);
  else
    md_i2c_set_con2_add10(I2Cx, MD_I2C_ADDRESSINGMODE_7BIT);

  md_i2c_set_con2_sadd(I2Cx, DevAddr);
  md_i2c_set_con2_nbytes(I2Cx, Nbyte);
  md_i2c_set_fcon_rxfrst(I2Cx, MD_I2C_RXFIFO_RESET);
  md_i2c_set_con2_rd_wrn(I2Cx, MD_I2C_MASTER_READ);
  md_i2c_set_con2_reload(I2Cx, MD_I2C_NORELOAD_MODE);
  /* When NBYTES is matched, the communication will be automatically stop */
  md_i2c_set_con2_autoend(I2Cx, MD_I2C_AUTOEND_MODE);
  /* Start the I2C communication */
  md_i2c_set_con2_start(I2Cx, MD_I2C_START_GENERATION);

  while (Nbyte > 0)
  {
    /* Wait Rx FIFO non-empty */
    while (md_i2c_is_active_stat_rxe(I2Cx));

    *rxbuf++ = md_i2c_recv(I2Cx);
    Nbyte--;
  }
}

/**
  * @brief  Transmits in slave mode an amount of data in blocking mode.
  * @param  I2Cx I2C Instance
  * @param  The number of bytes to be transmitted, not for NBYTES
  * @param  The pointer to a data buffer
  * @retval None
  */
void md_i2c_slave_send(I2C_TypeDef *I2Cx, uint8_t Num, uint8_t *txbuf)
{
  md_i2c_set_fcon_txfrst(I2Cx, MD_I2C_TXFIFO_RESET);

  while (!(md_i2c_is_active_stat_busy(I2Cx)));

  while (Num > 0)
  {
    while (md_i2c_is_active_stat_txf(I2Cx));

    md_i2c_send(I2Cx, *txbuf++);
    Num--;
  }
}

/**
  * @brief  Receives in slave mode an amount of data in blocking mode.
  * @param  I2Cx I2C Instance
  * @param  The number of bytes to be transmitted, not for NBYTES
  * @param  The pointer to a data buffer
  * @retval None
  */
void md_i2c_slave_rece(I2C_TypeDef *I2Cx, uint8_t Num, uint8_t *rxbuf)
{
  md_i2c_set_fcon_rxfrst(I2Cx, MD_I2C_RXFIFO_RESET);

  while (!(md_i2c_is_active_stat_busy(I2Cx)));

  while (Num > 0)
  {
    while (md_i2c_is_active_stat_rxe(I2Cx));

    *rxbuf++ = md_i2c_recv(I2Cx);
    Num--;
  }
}

/**
  * @} Micro_Driver
  */
