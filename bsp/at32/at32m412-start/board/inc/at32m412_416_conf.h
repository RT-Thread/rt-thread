/**
  **************************************************************************
  * @file     at32m412_416_conf.h
  * @brief    at32m412_416 config header file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32M412_416_CONF_H
#define __AT32M412_416_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief in the following line adjust the value of high speed external crystal (hext)
  * used in your application
  *
  * tip: to avoid modifying this file each time you need to use different hext, you
  *      can define the hext value in your toolchain compiler preprocessor.
  *
  */
#if !defined  HEXT_VALUE
#define HEXT_VALUE                       ((uint32_t)8000000) /*!< value of the high speed external crystal in hz */
#endif

/**
  * @brief in the following line adjust the high speed external crystal (hext) startup
  * timeout value
  */
#define HEXT_STARTUP_TIMEOUT             ((uint16_t)0x3000)  /*!< time out for hext start up */
#define HICK_VALUE                       ((uint32_t)8000000) /*!< value of the high speed internal clock in hz */
#define LEXT_VALUE                       ((uint32_t)32768)   /*!< value of the low speed external clock in hz */

/* module define -------------------------------------------------------------*/
#define ADC_MODULE_ENABLED
#define CAN_MODULE_ENABLED
#define CMP_MODULE_ENABLED
#define CRC_MODULE_ENABLED
#define CRM_MODULE_ENABLED
#define DAC_MODULE_ENABLED
#define DEBUG_MODULE_ENABLED
#define DMA_MODULE_ENABLED
#define ERTC_MODULE_ENABLED
#define EXINT_MODULE_ENABLED
#define FLASH_MODULE_ENABLED
#define GPIO_MODULE_ENABLED
#define I2C_MODULE_ENABLED
#define MISC_MODULE_ENABLED
#define OP_MODULE_ENABLED
#define PWC_MODULE_ENABLED
#define SCFG_MODULE_ENABLED
#define SPI_MODULE_ENABLED
#define TMR_MODULE_ENABLED
#define USART_MODULE_ENABLED
#define WWDT_MODULE_ENABLED
#define WDT_MODULE_ENABLED

/* includes ------------------------------------------------------------------*/
#ifdef ADC_MODULE_ENABLED
#include "at32m412_416_adc.h"
#endif
#ifdef CAN_MODULE_ENABLED
#include "at32m412_416_can.h"
#endif
#ifdef CMP_MODULE_ENABLED
#include "at32m412_416_cmp.h"
#endif
#ifdef CRC_MODULE_ENABLED
#include "at32m412_416_crc.h"
#endif
#ifdef CRM_MODULE_ENABLED
#include "at32m412_416_crm.h"
#endif
#ifdef DAC_MODULE_ENABLED
#include "at32m412_416_dac.h"
#endif
#ifdef DEBUG_MODULE_ENABLED
#include "at32m412_416_debug.h"
#endif
#ifdef DMA_MODULE_ENABLED
#include "at32m412_416_dma.h"
#endif
#ifdef ERTC_MODULE_ENABLED
#include "at32m412_416_ertc.h"
#endif
#ifdef EXINT_MODULE_ENABLED
#include "at32m412_416_exint.h"
#endif
#ifdef FLASH_MODULE_ENABLED
#include "at32m412_416_flash.h"
#endif
#ifdef GPIO_MODULE_ENABLED
#include "at32m412_416_gpio.h"
#endif
#ifdef I2C_MODULE_ENABLED
#include "at32m412_416_i2c.h"
#endif
#ifdef MISC_MODULE_ENABLED
#include "at32m412_416_misc.h"
#endif
#ifdef OP_MODULE_ENABLED
#include "at32m412_416_op.h"
#endif
#ifdef PWC_MODULE_ENABLED
#include "at32m412_416_pwc.h"
#endif
#ifdef SCFG_MODULE_ENABLED
#include "at32m412_416_scfg.h"
#endif
#ifdef SPI_MODULE_ENABLED
#include "at32m412_416_spi.h"
#endif
#ifdef TMR_MODULE_ENABLED
#include "at32m412_416_tmr.h"
#endif
#ifdef USART_MODULE_ENABLED
#include "at32m412_416_usart.h"
#endif
#ifdef WWDT_MODULE_ENABLED
#include "at32m412_416_wwdt.h"
#endif
#ifdef WDT_MODULE_ENABLED
#include "at32m412_416_wdt.h"
#endif

#ifdef __cplusplus
}
#endif

#endif
