/***************************************************************************//**
 * @file
 * @brief Verify that part specific main header files are supported and included
 * @author Energy Micro AS
 * @version 3.0.0
 *******************************************************************************
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
#ifndef __EM_PART_H
#define __EM_PART_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup Part
 * @brief Lists all Energy Micro parts that are supported by emlib
 * @{
 ******************************************************************************/

/* Gecko parts */
#if defined(EFM32G200F16)
#include "efm32.h"
#elif defined(EFM32G200F32)
#include "efm32.h"
#elif defined(EFM32G200F64)
#include "efm32.h"
#elif defined(EFM32G210F128)
#include "efm32.h"
#elif defined(EFM32G222F128)
#include "efm32.h"
#elif defined(EFM32G222F32)
#include "efm32.h"
#elif defined(EFM32G222F64)
#include "efm32.h"
#elif defined(EFM32G230F128)
#include "efm32.h"
#elif defined(EFM32G230F32)
#include "efm32.h"
#elif defined(EFM32G230F64)
#include "efm32.h"
#elif defined(EFM32G232F128)
#include "efm32.h"
#elif defined(EFM32G232F32)
#include "efm32.h"
#elif defined(EFM32G232F64)
#include "efm32.h"
#elif defined(EFM32G280F128)
#include "efm32.h"
#elif defined(EFM32G280F32)
#include "efm32.h"
#elif defined(EFM32G280F64)
#include "efm32.h"
#elif defined(EFM32G290F128)
#include "efm32.h"
#elif defined(EFM32G290F32)
#include "efm32.h"
#elif defined(EFM32G290F64)
#include "efm32.h"
#elif defined(EFM32G840F128)
#include "efm32.h"
#elif defined(EFM32G840F32)
#include "efm32.h"
#elif defined(EFM32G840F64)
#include "efm32.h"
#elif defined(EFM32G842F128)
#include "efm32.h"
#elif defined(EFM32G842F32)
#include "efm32.h"
#elif defined(EFM32G842F64)
#include "efm32.h"
#elif defined(EFM32G880F128)
#include "efm32.h"
#elif defined(EFM32G880F32)
#include "efm32.h"
#elif defined(EFM32G880F64)
#include "efm32.h"
#elif defined(EFM32G890F128)
#include "efm32.h"
#elif defined(EFM32G890F32)
#include "efm32.h"
#elif defined(EFM32G890F64)
#include "efm32.h"
/* Tiny Gecko parts */
#elif defined(EFM32TG108F16)
#include "efm32.h"
#elif defined(EFM32TG108F32)
#include "efm32.h"
#elif defined(EFM32TG108F4)
#include "efm32.h"
#elif defined(EFM32TG108F8)
#include "efm32.h"
#elif defined(EFM32TG110F16)
#include "efm32.h"
#elif defined(EFM32TG110F32)
#include "efm32.h"
#elif defined(EFM32TG110F4)
#include "efm32.h"
#elif defined(EFM32TG110F8)
#include "efm32.h"
#elif defined(EFM32TG210F16)
#include "efm32.h"
#elif defined(EFM32TG210F32)
#include "efm32.h"
#elif defined(EFM32TG210F8)
#include "efm32.h"
#elif defined(EFM32TG222F16)
#include "efm32.h"
#elif defined(EFM32TG222F32)
#include "efm32.h"
#elif defined(EFM32TG222F8)
#include "efm32.h"
#elif defined(EFM32TG230F16)
#include "efm32.h"
#elif defined(EFM32TG230F32)
#include "efm32.h"
#elif defined(EFM32TG230F8)
#include "efm32.h"
#elif defined(EFM32TG232F16)
#include "efm32.h"
#elif defined(EFM32TG232F32)
#include "efm32.h"
#elif defined(EFM32TG232F8)
#include "efm32.h"
#elif defined(EFM32TG822F16)
#include "efm32.h"
#elif defined(EFM32TG822F32)
#include "efm32.h"
#elif defined(EFM32TG822F8)
#include "efm32.h"
#elif defined(EFM32TG840F16)
#include "efm32.h"
#elif defined(EFM32TG840F32)
#include "efm32.h"
#elif defined(EFM32TG840F8)
#include "efm32.h"
#elif defined(EFM32TG842F16)
#include "efm32.h"
#elif defined(EFM32TG842F32)
#include "efm32.h"
#elif defined(EFM32TG842F8)
#include "efm32.h"
/* Giant Gecko parts */
#elif defined(EFM32GG230F1024)
#include "efm32.h"
#elif defined(EFM32GG230F512)
#include "efm32.h"
#elif defined(EFM32GG232F1024)
#include "efm32.h"
#elif defined(EFM32GG232F512)
#include "efm32.h"
#elif defined(EFM32GG280F1024)
#include "efm32.h"
#elif defined(EFM32GG280F512)
#include "efm32.h"
#elif defined(EFM32GG290F1024)
#include "efm32.h"
#elif defined(EFM32GG290F512)
#include "efm32.h"
#elif defined(EFM32GG295F1024)
#include "efm32.h"
#elif defined(EFM32GG295F512)
#include "efm32.h"
#elif defined(EFM32GG330F1024)
#include "efm32.h"
#elif defined(EFM32GG330F512)
#include "efm32.h"
#elif defined(EFM32GG332F1024)
#include "efm32.h"
#elif defined(EFM32GG332F512)
#include "efm32.h"
#elif defined(EFM32GG380F1024)
#include "efm32.h"
#elif defined(EFM32GG380F512)
#include "efm32.h"
#elif defined(EFM32GG390F1024)
#include "efm32.h"
#elif defined(EFM32GG390F512)
#include "efm32.h"
#elif defined(EFM32GG395F1024)
#include "efm32.h"
#elif defined(EFM32GG395F512)
#include "efm32.h"
#elif defined(EFM32GG840F1024)
#include "efm32.h"
#elif defined(EFM32GG840F512)
#include "efm32.h"
#elif defined(EFM32GG842F1024)
#include "efm32.h"
#elif defined(EFM32GG842F512)
#include "efm32.h"
#elif defined(EFM32GG880F1024)
#include "efm32.h"
#elif defined(EFM32GG880F512)
#include "efm32.h"
#elif defined(EFM32GG890F1024)
#include "efm32.h"
#elif defined(EFM32GG890F512)
#include "efm32.h"
#elif defined(EFM32GG895F1024)
#include "efm32.h"
#elif defined(EFM32GG895F512)
#include "efm32.h"
#elif defined(EFM32GG940F1024)
#include "efm32.h"
#elif defined(EFM32GG940F512)
#include "efm32.h"
#elif defined(EFM32GG942F1024)
#include "efm32.h"
#elif defined(EFM32GG942F512)
#include "efm32.h"
#elif defined(EFM32GG980F1024)
#include "efm32.h"
#elif defined(EFM32GG980F512)
#include "efm32.h"
#elif defined(EFM32GG990F1024)
#include "efm32.h"
#elif defined(EFM32GG990F512)
#include "efm32.h"
#elif defined(EFM32GG995F1024)
#include "efm32.h"
#elif defined(EFM32GG995F512)
#include "efm32.h"
/* Leopard Gecko parts */
#elif defined(EFM32LG230F128)
#include "efm32.h"
#elif defined(EFM32LG230F256)
#include "efm32.h"
#elif defined(EFM32LG230F64)
#include "efm32.h"
#elif defined(EFM32LG232F128)
#include "efm32.h"
#elif defined(EFM32LG232F256)
#include "efm32.h"
#elif defined(EFM32LG232F64)
#include "efm32.h"
#elif defined(EFM32LG280F128)
#include "efm32.h"
#elif defined(EFM32LG280F256)
#include "efm32.h"
#elif defined(EFM32LG280F64)
#include "efm32.h"
#elif defined(EFM32LG290F128)
#include "efm32.h"
#elif defined(EFM32LG290F256)
#include "efm32.h"
#elif defined(EFM32LG290F64)
#include "efm32.h"
#elif defined(EFM32LG295F128)
#include "efm32.h"
#elif defined(EFM32LG295F256)
#include "efm32.h"
#elif defined(EFM32LG295F64)
#include "efm32.h"
#elif defined(EFM32LG330F128)
#include "efm32.h"
#elif defined(EFM32LG330F256)
#include "efm32.h"
#elif defined(EFM32LG330F64)
#include "efm32.h"
#elif defined(EFM32LG332F128)
#include "efm32.h"
#elif defined(EFM32LG332F256)
#include "efm32.h"
#elif defined(EFM32LG332F64)
#include "efm32.h"
#elif defined(EFM32LG380F128)
#include "efm32.h"
#elif defined(EFM32LG380F256)
#include "efm32.h"
#elif defined(EFM32LG380F64)
#include "efm32.h"
#elif defined(EFM32LG390F128)
#include "efm32.h"
#elif defined(EFM32LG390F256)
#include "efm32.h"
#elif defined(EFM32LG390F64)
#include "efm32.h"
#elif defined(EFM32LG395F128)
#include "efm32.h"
#elif defined(EFM32LG395F256)
#include "efm32.h"
#elif defined(EFM32LG395F64)
#include "efm32.h"
#elif defined(EFM32LG840F128)
#include "efm32.h"
#elif defined(EFM32LG840F256)
#include "efm32.h"
#elif defined(EFM32LG840F64)
#include "efm32.h"
#elif defined(EFM32LG842F128)
#include "efm32.h"
#elif defined(EFM32LG842F256)
#include "efm32.h"
#elif defined(EFM32LG842F64)
#include "efm32.h"
#elif defined(EFM32LG880F128)
#include "efm32.h"
#elif defined(EFM32LG880F256)
#include "efm32.h"
#elif defined(EFM32LG880F64)
#include "efm32.h"
#elif defined(EFM32LG890F128)
#include "efm32.h"
#elif defined(EFM32LG890F256)
#include "efm32.h"
#elif defined(EFM32LG890F64)
#include "efm32.h"
#elif defined(EFM32LG895F128)
#include "efm32.h"
#elif defined(EFM32LG895F256)
#include "efm32.h"
#elif defined(EFM32LG895F64)
#include "efm32.h"
#elif defined(EFM32LG940F128)
#include "efm32.h"
#elif defined(EFM32LG940F256)
#include "efm32.h"
#elif defined(EFM32LG940F64)
#include "efm32.h"
#elif defined(EFM32LG942F128)
#include "efm32.h"
#elif defined(EFM32LG942F256)
#include "efm32.h"
#elif defined(EFM32LG942F64)
#include "efm32.h"
#elif defined(EFM32LG980F128)
#include "efm32.h"
#elif defined(EFM32LG980F256)
#include "efm32.h"
#elif defined(EFM32LG980F64)
#include "efm32.h"
#elif defined(EFM32LG990F128)
#include "efm32.h"
#elif defined(EFM32LG990F256)
#include "efm32.h"
#elif defined(EFM32LG990F64)
#include "efm32.h"
#elif defined(EFM32LG995F128)
#include "efm32.h"
#elif defined(EFM32LG995F256)
#include "efm32.h"
/* EFR4 parts */
#elif defined(EFR4D1080F256)
#include "efr4.h"
#elif defined(EFR4D1090F256)
#include "efr4.h"
#elif defined(EFR4D1092F256)
#include "efr4.h"
#elif defined(EFR4D2080F256)
#include "efr4.h"
#elif defined(EFR4D2090F256)
#include "efr4.h"
#elif defined(EFR4D2092F256)
#include "efr4.h"
#elif defined(EFR4D2280F256)
#include "efr4.h"
#elif defined(EFR4D2290F256)
#include "efr4.h"
#elif defined(EFR4D2292F256)
#include "efr4.h"

#else
#error "em_part.h: PART NUMBER undefined"
#endif

#if defined(_EFM32_GIANT_FAMILY)
/* Add EFM32 Giant and Leopard Gecko specifics here */
#define _EFM_DEVICE /**< Energy Micro EFM-type microcontroller */
#elif defined(_EFM32_TINY_FAMILY)
/* Add EFM32 Tiny Gecko specifics here */
#define _EFM_DEVICE /**< Energy Micro EFM-type microcontroller */
#elif defined(_EFM32_GECKO_FAMILY)
/* Add EFM32 Gecko specifics here */
#define _EFM_DEVICE /**< Energy Micro EFM-type microcontroller */
#elif defined(_EFR4_DRACO_FAMILY)
/* Add EFR4 Draco specifics here */
#define _EFR_DEVICE /**< Energy Micro EFR-type RF SoC or transceiver */
#else
#error "em_part.h: Unknown device type"
#endif

/** @} (end addtogroup Part) */
/** @} (end addtogroup EM_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EM_PART_H */
