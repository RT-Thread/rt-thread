/*
 * @brief LPC5410X ROM API declarations and functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __ROMAPI_5410X_H_
#define __ROMAPI_5410X_H_

#include <stdint.h>
#include "iap.h"
#include "error.h"
#include "cmsis.h"

/* v1 ROM driver APIs */
#include "rom_pwr_5410x.h"

/* v2 ROM driver APIs */
#include "romapi_adc.h"
#include "romapi_dma.h"
#include "romapi_i2cm.h"
#include "romapi_i2cmon.h"
#include "romapi_i2cs.h"
#include "romapi_spim.h"
#include "romapi_spis.h"
#include "romapi_uart.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup ROMAPI_5410X CHIP: LPC5410X ROM API declarations and functions
 * @ingroup CHIP_5410X_DRIVERS
 * @{
 */

/**
 * @brief High level ROM API structure
 */
typedef struct {
    const uint32_t reserved_usb;                /*!< Reserved */
    const uint32_t reserved_clib;               /*!< Reserved */
    const uint32_t reserved_can;                /*!< Reserved */
    const PWRD_API_T *pPWRD;                    /*!< Power API function table base address */
    const uint32_t reserved_div;                /*!< Reserved */
    const uint32_t reserved_i2cd;               /*!< Reserved */
    const uint32_t reserved_dmad;               /*!< Reserved */
    const uint32_t reserved_spid;               /*!< Reserved */
    const uint32_t reserved_adcd;               /*!< Reserved */
    const uint32_t reserved_uartd;              /*!< Reserved */
    const uint32_t reserved_vfifo;              /*!< Reserved */
    const uint32_t reserved_usart;              /*!< Reserved */
    /* v2 drivers - only present in some LPC5410x devices */
    const ROM_I2CMD_API_T *pI2CMD;              /*!< v2 I2C master only driver API function table base address */
    const ROM_I2CSD_API_T *pI2CSD;              /*!< v2 I2C slave only driver API function table base address */
    const ROM_I2CMOND_API_T *pI2CMOND;          /*!< v2 I2C bus monitor driver API function table base address */
    const ROM_SPIMD_API_T *pSPIMD;              /*!< v2 SPI master only driver API function table base address */
    const ROM_SPISD_API_T *pSPISD;              /*!< v2 SPI slave only driver API function table base address */
    const ROM_DMAALTD_API_T *pDMAALT;           /*!< v2 abstract DMA driver API function table base address */
    const ROM_ADC_API_T *pADCALT;               /*!< v2 ADC driver API function table base address */
    const ROM_UART_API_T *pUARTALT;             /*!< v2 UART driver API function table base address */
} LPC_ROM_API_T;

/* Pointer to ROM API function address */
#define LPC_ROM_API_BASE_LOC    0x03000200UL
#define LPC_ROM_API     (*(LPC_ROM_API_T * *) LPC_ROM_API_BASE_LOC)

/* Pointer to @ref PWRD_API_T functions in ROM */
#define LPC_PWRD_API    ((LPC_ROM_API)->pPWRD)

/* Pointer to v2 I2C master peripheral driver functions in ROM */
#define ROMAPI_I2CM_API ((LPC_ROM_API)->pI2CMD)

/* Pointer to v2 I2C master peripheral driver functions in ROM */
#define ROMAPI_I2CMON_API   ((LPC_ROM_API)->pI2CMOND)

/* Pointer to v2 I2C slave peripheral driver functions in ROM */
#define ROMAPI_I2CS_API ((LPC_ROM_API)->pI2CSD)

/* Pointer to v2 SPI master peripheral driver functions in ROM */
#define ROMAPI_SPIM_API ((LPC_ROM_API)->pSPIMD)

/* Pointer to v2 SPI slave peripheral driver functions in ROM */
#define ROMAPI_SPIS_API ((LPC_ROM_API)->pSPISD)

/* Pointer to v2 DMA controller driver functions in ROM */
#define ROMAPI_DMAALT_API   ((LPC_ROM_API)->pDMAALT)

/* Pointer to v2 ADC driver functions in ROM */
#define ROMAPI_ADC_API      ((LPC_ROM_API)->pADCALT)

/* Pointer to v2 UART controller driver functions in ROM */
#define ROMAPI_UART_API ((LPC_ROM_API)->pUARTALT)

/* Pointer to ROM IAP entry functions */
#define IAP_ENTRY_LOCATION        0x03000205

/**
 * @brief LPC5410x IAP_ENTRY API function type
 */
static INLINE void iap_entry(uint32_t cmd_param[5], uint32_t status_result[4])
{
    ((IAP_ENTRY_T) IAP_ENTRY_LOCATION)(cmd_param, status_result);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ROMAPI_5410X_H_ */
