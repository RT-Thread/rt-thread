/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2011-12-20   onelife     Initial creation for EFM32
 */

#ifndef __TFTSPI_H__
#define __TFTSPI_H__

#include <rtthread.h>

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define SPI_TFT_Init()
#define SPI_TFT_WriteRegister(reg, data)    efm32_spiLcd_writeRegister(reg, data)

/* Exported functions ------------------------------------------------------- */
extern rt_err_t efm32_spiLcd_writeRegister(rt_uint8_t reg, rt_uint16_t data);

#endif /* __TFTSPI_H__ */
