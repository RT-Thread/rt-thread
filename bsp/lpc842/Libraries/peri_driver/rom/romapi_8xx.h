/*
 * @brief LPC8xx ROM API declarations and functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
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

#ifndef __ROMAPI_8XX_H_
#define __ROMAPI_8XX_H_

#include "../iap/iap.h"
#include "../../common/chip/error_8xx.h"
#include "rom_i2c_8xx.h"
#include "rom_pwr_8xx.h"
#include "rom_uart_8xx.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup ROMAPI_8XX CHIP: LPC8xx ROM API declarations and functions
 * @ingroup CHIP_8XX_Drivers
 * @{
 */

/**
 * @brief LPC8XX High level ROM API structure
 */
typedef struct ROM_API {
	const uint32_t    unused[3];
	const PWRD_API_T  *pPWRD;	/*!< Power profiles API function table */
	const uint32_t    p_dev1;
	const I2CD_API_T  *pI2CD;	/*!< I2C driver routines functions table */
	const uint32_t    p_dev3;
	const uint32_t    p_dev4;
	const uint32_t    p_dev5;
	const UARTD_API_T *pUARTD;	/*!< UART driver routines function table */
} LPC_ROM_API_T;

/* Pointer to ROM API function address */
#define LPC_ROM_API_BASE_LOC	0x1FFF1FF8UL
#define LPC_ROM_API		(*(LPC_ROM_API_T * *) LPC_ROM_API_BASE_LOC)

/* Pointer to @ref PWRD_API_T functions in ROM */
#define LPC_PWRD_API    ((LPC_ROM_API)->pPWRD)

/* Pointer to @ref I2CD_API_T functions in ROM */
#define LPC_I2CD_API    ((LPC_ROM_API)->pI2CD)

/* Pointer to @ref UARTD_API_T functions in ROM */
#define LPC_UARTD_API   ((LPC_ROM_API)->pUARTD)

/* Pointer to ROM IAP entry functions */
#define IAP_ENTRY_LOCATION        0X1FFF1FF1UL

/**
 * @brief LPC8XX IAP_ENTRY API function type
 */
static INLINE void iap_entry(unsigned int cmd_param[], unsigned int status_result[])
{
	((IAP_ENTRY_T) IAP_ENTRY_LOCATION)(cmd_param, status_result);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ROMAPI_8XX_H_ */
