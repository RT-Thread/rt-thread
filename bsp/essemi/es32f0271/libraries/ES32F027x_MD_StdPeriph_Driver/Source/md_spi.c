/**
  ******************************************************************************
  * @file    md_spi.c
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
#include "md_spi.h"
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
  * @brief  Initialize the SPI registers according to the specified parameters in SPI_initStruct.
  * @note   The parameters in md_spi_init should be expected values. Otherwise, ERROR result will be returned.
  * @param  SPIx SPI Instance
  * @param  SPI_initStruct pointer to a @ref SPI_initStruct structure
  * @retval An ErrorStatus enumeration value. (Return always SUCCESS)
  */
void md_spi_struct_init(md_spi_inittypedef *SPI_initStruct)
{
  SPI_initStruct->Mode               = MD_SPI_MODE_MASTER;
  SPI_initStruct->ClockPhase         = MD_SPI_PHASE_1EDGE;
  SPI_initStruct->ClockPolarity      = MD_SPI_POLARITY_LOW;
  SPI_initStruct->BaudRate           = MD_SPI_BAUDRATEPRESCALER_DIV256;
  SPI_initStruct->BitOrder           = MD_SPI_MSB_FIRST;
  SPI_initStruct->TransferDirection  = MD_SPI_FULL_DUPLEX;
  SPI_initStruct->DataWidth          = MD_SPI_FRAME_FORMAT_8BIT;
  SPI_initStruct->CRCCalculation     = MD_SPI_CRCCALCULATION_DISABLE;
  SPI_initStruct->CRCPoly            = 0x7;
  SPI_initStruct->NSS                = MD_SPI_NSS_HARD;
}

/**
  * @brief  Initialize the SPI registers according to the specified parameters in SPI_initStruct.
  * @note   The parameters in md_i2c_init should be expected values. Otherwise, ERROR result will be returned.
  * @param  SPIx SPI Instance
  * @param  SPI_initStruct pointer to a @ref SPI_initStruct structure
  * @retval An ErrorStatus enumeration value. (Return always SUCCESS)
  */
ErrorStatus md_spi_init(SPI_TypeDef *SPIx, md_spi_inittypedef *SPI_InitStruct)
{
  ErrorStatus status = ERROR;

  md_spi_disable_con1_spien(SPIx);

  md_spi_set_con1_mstren(SPIx, SPI_InitStruct->Mode);
  md_spi_set_con1_cpha(SPIx, SPI_InitStruct->ClockPhase);
  md_spi_set_con1_cpol(SPIx, SPI_InitStruct->ClockPolarity);
  md_spi_set_con1_baud(SPIx, SPI_InitStruct->BaudRate);
  md_spi_set_con1_lsbfirst(SPIx, SPI_InitStruct->BitOrder);
  md_spi_set_con1_bidimode(SPIx, SPI_InitStruct->TransferDirection);
  md_spi_set_con1_ssout(SPIx, SPI_InitStruct->NSS);
  md_spi_enable_con2_ssoe(SPIx);

  md_spi_enable_con1_spien(SPIx);

  status = SUCCESS;

  return status;
}

/**
  * @brief  use to receive single one byte data.
  * @note   SPI Slave receive data
  * @param  SPIx SPI Instance
  */
uint8_t SPISSingleRd(SPI_TypeDef *SPIx)
{
  while (md_spi_is_active_flag_stat_rxe(SPIx));

  return (md_spi_recv_data8(SPIx));
}


/**
  * @brief  use to send single one byte data.
  * @note   SPI receive data
  * @param  SPIx SPI Instance
  * @param  data SPI send one byte data.
  */
void SPISingleWr(SPI_TypeDef *SPIx, uint8_t data)
{
  while (md_spi_is_active_flag_stat_txf(SPIx));

  md_spi_send_data8(SPIx, data);
}

/**
  * @} Micro_Driver
  */
