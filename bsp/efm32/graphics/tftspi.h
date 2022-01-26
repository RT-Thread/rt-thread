/***************************************************************************//**
 * @file    tftspi.h
 * @brief   Stub functions of EFM32 LCD driver
 *  COPYRIGHT (C) 2012, RT-Thread Development Team
 * @author  onelife
 * @version 1.0
 *******************************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file
 *  LICENSE in this distribution or at http://www.rt-thread.org/license/LICENSE
 *******************************************************************************
 * @section Change Logs
 * Date         Author      Notes
 * 2011-12-20   onelife     Initial creation for EFM32
 ******************************************************************************/
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
