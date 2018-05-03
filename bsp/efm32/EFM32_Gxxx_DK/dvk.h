/**************************************************************************//**
 * @file
 * @brief DVK Board Support, master header file
 * @author Energy Micro AS
 * @version 2.0.1
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 * 4. The source and compiled code may only be used on Energy Micro "EFM32"
 *    microcontrollers and "EFR4" radios.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 *****************************************************************************/

#ifndef __DVK_H
#define __DVK_H

/***************************************************************************//**
 * @addtogroup BSP
 * @{
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "dvk_boardcontrol.h"
#include "dvk_bcregisters.h"

/* onelife: Add missing define */
#define NULL ((void *)0)

/* IF not user overrides default, try to decide DVK access interface based on
 * part number */
#ifndef DVK_SPI_CONTROL
#ifndef DVK_EBI_CONTROL

#if defined(EFM32G200F16)
#define DVK_SPI_CONTROL
#elif defined(EFM32G200F32)
#define DVK_SPI_CONTROL
#elif defined(EFM32G200F64)
#define DVK_SPI_CONTROL
#elif defined(EFM32G210F128)
#define DVK_SPI_CONTROL
#elif defined(EFM32G230F128)
#define DVK_SPI_CONTROL
#elif defined(EFM32G230F32)
#define DVK_SPI_CONTROL
#elif defined(EFM32G230F64)
#define DVK_SPI_CONTROL
#elif defined(EFM32G280F128)
#define DVK_EBI_CONTROL
#elif defined(EFM32G280F32)
#define DVK_EBI_CONTROL
#elif defined(EFM32G280F64)
#define DVK_EBI_CONTROL
#elif defined(EFM32G290F128)
#define DVK_EBI_CONTROL
#elif defined(EFM32G290F32)
#define DVK_EBI_CONTROL
#elif defined(EFM32G290F64)
#define DVK_EBI_CONTROL
#elif defined(EFM32G840F128)
#define DVK_SPI_CONTROL
#elif defined(EFM32G840F32)
#define DVK_SPI_CONTROL
#elif defined(EFM32G840F64)
#define DVK_SPI_CONTROL
#elif defined(EFM32G880F128)
#define DVK_SPI_CONTROL
#elif defined(EFM32G880F32)
#define DVK_SPI_CONTROL
#elif defined(EFM32G880F64)
#define DVK_SPI_CONTROL
#elif defined(EFM32G890F128)
#define DVK_SPI_CONTROL
#elif defined(EFM32G890F32)
#define DVK_SPI_CONTROL
#elif defined(EFM32G890F64)
#define DVK_SPI_CONTROL
#else
#define DVK_SPI_CONTROL
#endif

#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* EBI access */
bool DVK_EBI_init(void);
void DVK_EBI_disable(void);
void DVK_EBI_configure(void);
void DVK_EBI_writeRegister(volatile uint16_t *addr, uint16_t data);
uint16_t DVK_EBI_readRegister(volatile uint16_t *addr);

/* SPI access */
bool DVK_SPI_init(void);
void DVK_SPI_disable(void);

void DVK_SPI_writeRegister(volatile uint16_t *addr, uint16_t data);
uint16_t DVK_SPI_readRegister(volatile uint16_t *addr);


/* Accodring to configuration, use either SPI or EBI */
#ifdef DVK_EBI_CONTROL
#define DVK_writeRegister(A, B)    DVK_EBI_writeRegister(A, B)
#define DVK_readRegister(A)        DVK_EBI_readRegister(A)
#endif

#ifdef DVK_SPI_CONTROL
#define DVK_writeRegister(A, B)    DVK_SPI_writeRegister(A, B)
#define DVK_readRegister(A)        DVK_SPI_readRegister(A)
#endif

/* General initialization routines */
bool DVK_init(void);
void DVK_disable(void);

#ifdef __cplusplus
}
#endif

/** @} (end group BSP) */

#endif
