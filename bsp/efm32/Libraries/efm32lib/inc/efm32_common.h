/***************************************************************************//**
 * @file
 * @brief EFM32 general purpose utilities.
 * @author Energy Micro AS
 * @version 2.0.0
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2011 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * This source code is the property of Energy Micro AS. The source and compiled
 * code may only be used on Energy Micro "EFM32" microcontrollers.
 *
 * This copyright notice may not be removed from the source code nor changed.
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
 ******************************************************************************/
#ifndef __EFM32_COMMON_H
#define __EFM32_COMMON_H

#include <stdint.h>
#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup EFM32_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup COMMON
 * @brief EFM32 general purpose utilities.
 * @{
 ******************************************************************************/

#if !defined(__GNUC__)

/** Macro for getting minimum value. */
#define EFM32_MIN(a, b)    ((a) < (b) ? (a) : (b))
/** Macro for getting maximum value. */
#define EFM32_MAX(a, b)    ((a) > (b) ? (a) : (b))

#else

/** Macro for getting minimum value. No sideeffects, a and b are evaluated once only. */
#define EFM32_MIN(a, b)    ({ typeof(a)_a = (a); typeof(b)_b = (b); _a < _b ? _a : _b; })
/** Macro for getting maximum value. No sideeffects, a and b are evaluated once only. */
#define EFM32_MAX(a, b)    ({ typeof(a)_a = (a); typeof(b)_b = (b); _a > _b ? _a : _b; })

#endif

/** @} (end addtogroup COMMON) */
/** @} (end addtogroup EFM32_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EFM32_COMMON_H */
