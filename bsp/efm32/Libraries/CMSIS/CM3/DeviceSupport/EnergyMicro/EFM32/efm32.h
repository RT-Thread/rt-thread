/**************************************************************************//**
 * @file
 * @brief CMSIS Cortex-M0/M3 Peripheral Access Layer for EFM32 device series
 *
 * This is a convenience header file for defining the EFM32 part number on the
 * build command line, instead of specifying the part specific header file.
 * @verbatim
 * Example: Add "-DEFM32G890F128" to your build options, to define part
 *          Add "#include "efm32.h" to your source files
 * @endverbatim
 * @author Energy Micro AS
 * @version 2.3.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2011 Energy Micro AS, http://www.energymicro.com</b>
 ******************************************************************************
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
 *****************************************************************************/

#ifndef __EFM32_H
#define __EFM32_H


#if defined(EFM32G200F16)
#include "efm32g200f16.h"

#elif defined(EFM32G200F32)
#include "efm32g200f32.h"

#elif defined(EFM32G200F64)
#include "efm32g200f64.h"

#elif defined(EFM32G210F128)
#include "efm32g210f128.h"

#elif defined(EFM32G222F128)
#include "efm32g222f128.h"

#elif defined(EFM32G222F32)
#include "efm32g222f32.h"

#elif defined(EFM32G222F64)
#include "efm32g222f64.h"

#elif defined(EFM32G230F128)
#include "efm32g230f128.h"

#elif defined(EFM32G230F32)
#include "efm32g230f32.h"

#elif defined(EFM32G230F64)
#include "efm32g230f64.h"

#elif defined(EFM32G232F128)
#include "efm32g232f128.h"

#elif defined(EFM32G232F32)
#include "efm32g232f32.h"

#elif defined(EFM32G232F64)
#include "efm32g232f64.h"

#elif defined(EFM32G280F128)
#include "efm32g280f128.h"

#elif defined(EFM32G280F32)
#include "efm32g280f32.h"

#elif defined(EFM32G280F64)
#include "efm32g280f64.h"

#elif defined(EFM32G290F128)
#include "efm32g290f128.h"

#elif defined(EFM32G290F32)
#include "efm32g290f32.h"

#elif defined(EFM32G290F64)
#include "efm32g290f64.h"

#elif defined(EFM32G840F128)
#include "efm32g840f128.h"

#elif defined(EFM32G840F32)
#include "efm32g840f32.h"

#elif defined(EFM32G840F64)
#include "efm32g840f64.h"

#elif defined(EFM32G842F128)
#include "efm32g842f128.h"

#elif defined(EFM32G842F32)
#include "efm32g842f32.h"

#elif defined(EFM32G842F64)
#include "efm32g842f64.h"

#elif defined(EFM32G880F128)
#include "efm32g880f128.h"

#elif defined(EFM32G880F32)
#include "efm32g880f32.h"

#elif defined(EFM32G880F64)
#include "efm32g880f64.h"

#elif defined(EFM32G890F128)
#include "efm32g890f128.h"

#elif defined(EFM32G890F32)
#include "efm32g890f32.h"

#elif defined(EFM32G890F64)
#include "efm32g890f64.h"

#elif defined(EFM32GG230F1024)
#include "efm32gg230f1024.h"

#elif defined(EFM32GG230F512)
#include "efm32gg230f512.h"

#elif defined(EFM32GG232F1024)
#include "efm32gg232f1024.h"

#elif defined(EFM32GG232F512)
#include "efm32gg232f512.h"

#elif defined(EFM32GG280F1024)
#include "efm32gg280f1024.h"

#elif defined(EFM32GG280F512)
#include "efm32gg280f512.h"

#elif defined(EFM32GG290F1024)
#include "efm32gg290f1024.h"

#elif defined(EFM32GG290F512)
#include "efm32gg290f512.h"

#elif defined(EFM32GG295F1024)
#include "efm32gg295f1024.h"

#elif defined(EFM32GG295F512)
#include "efm32gg295f512.h"

#elif defined(EFM32GG330F1024)
#include "efm32gg330f1024.h"

#elif defined(EFM32GG330F512)
#include "efm32gg330f512.h"

#elif defined(EFM32GG332F1024)
#include "efm32gg332f1024.h"

#elif defined(EFM32GG332F512)
#include "efm32gg332f512.h"

#elif defined(EFM32GG380F1024)
#include "efm32gg380f1024.h"

#elif defined(EFM32GG380F512)
#include "efm32gg380f512.h"

#elif defined(EFM32GG390F1024)
#include "efm32gg390f1024.h"

#elif defined(EFM32GG390F512)
#include "efm32gg390f512.h"

#elif defined(EFM32GG395F1024)
#include "efm32gg395f1024.h"

#elif defined(EFM32GG395F512)
#include "efm32gg395f512.h"

#elif defined(EFM32GG840F1024)
#include "efm32gg840f1024.h"

#elif defined(EFM32GG840F512)
#include "efm32gg840f512.h"

#elif defined(EFM32GG842F1024)
#include "efm32gg842f1024.h"

#elif defined(EFM32GG842F512)
#include "efm32gg842f512.h"

#elif defined(EFM32GG880F1024)
#include "efm32gg880f1024.h"

#elif defined(EFM32GG880F512)
#include "efm32gg880f512.h"

#elif defined(EFM32GG890F1024)
#include "efm32gg890f1024.h"

#elif defined(EFM32GG890F512)
#include "efm32gg890f512.h"

#elif defined(EFM32GG895F1024)
#include "efm32gg895f1024.h"

#elif defined(EFM32GG895F512)
#include "efm32gg895f512.h"

#elif defined(EFM32GG940F1024)
#include "efm32gg940f1024.h"

#elif defined(EFM32GG940F512)
#include "efm32gg940f512.h"

#elif defined(EFM32GG942F1024)
#include "efm32gg942f1024.h"

#elif defined(EFM32GG942F512)
#include "efm32gg942f512.h"

#elif defined(EFM32GG980F1024)
#include "efm32gg980f1024.h"

#elif defined(EFM32GG980F512)
#include "efm32gg980f512.h"

#elif defined(EFM32GG990F1024)
#include "efm32gg990f1024.h"

#elif defined(EFM32GG990F512)
#include "efm32gg990f512.h"

#elif defined(EFM32GG995F1024)
#include "efm32gg995f1024.h"

#elif defined(EFM32GG995F512)
#include "efm32gg995f512.h"

#elif defined(EFM32LG230F128)
#include "efm32lg230f128.h"

#elif defined(EFM32LG230F256)
#include "efm32lg230f256.h"

#elif defined(EFM32LG230F64)
#include "efm32lg230f64.h"

#elif defined(EFM32LG232F128)
#include "efm32lg232f128.h"

#elif defined(EFM32LG232F256)
#include "efm32lg232f256.h"

#elif defined(EFM32LG232F64)
#include "efm32lg232f64.h"

#elif defined(EFM32LG280F128)
#include "efm32lg280f128.h"

#elif defined(EFM32LG280F256)
#include "efm32lg280f256.h"

#elif defined(EFM32LG280F64)
#include "efm32lg280f64.h"

#elif defined(EFM32LG290F128)
#include "efm32lg290f128.h"

#elif defined(EFM32LG290F256)
#include "efm32lg290f256.h"

#elif defined(EFM32LG290F64)
#include "efm32lg290f64.h"

#elif defined(EFM32LG295F128)
#include "efm32lg295f128.h"

#elif defined(EFM32LG295F256)
#include "efm32lg295f256.h"

#elif defined(EFM32LG295F64)
#include "efm32lg295f64.h"

#elif defined(EFM32LG330F128)
#include "efm32lg330f128.h"

#elif defined(EFM32LG330F256)
#include "efm32lg330f256.h"

#elif defined(EFM32LG330F64)
#include "efm32lg330f64.h"

#elif defined(EFM32LG332F128)
#include "efm32lg332f128.h"

#elif defined(EFM32LG332F256)
#include "efm32lg332f256.h"

#elif defined(EFM32LG332F64)
#include "efm32lg332f64.h"

#elif defined(EFM32LG380F128)
#include "efm32lg380f128.h"

#elif defined(EFM32LG380F256)
#include "efm32lg380f256.h"

#elif defined(EFM32LG380F64)
#include "efm32lg380f64.h"

#elif defined(EFM32LG390F128)
#include "efm32lg390f128.h"

#elif defined(EFM32LG390F256)
#include "efm32lg390f256.h"

#elif defined(EFM32LG390F64)
#include "efm32lg390f64.h"

#elif defined(EFM32LG395F128)
#include "efm32lg395f128.h"

#elif defined(EFM32LG395F256)
#include "efm32lg395f256.h"

#elif defined(EFM32LG395F64)
#include "efm32lg395f64.h"

#elif defined(EFM32LG840F128)
#include "efm32lg840f128.h"

#elif defined(EFM32LG840F256)
#include "efm32lg840f256.h"

#elif defined(EFM32LG840F64)
#include "efm32lg840f64.h"

#elif defined(EFM32LG842F128)
#include "efm32lg842f128.h"

#elif defined(EFM32LG842F256)
#include "efm32lg842f256.h"

#elif defined(EFM32LG842F64)
#include "efm32lg842f64.h"

#elif defined(EFM32LG880F128)
#include "efm32lg880f128.h"

#elif defined(EFM32LG880F256)
#include "efm32lg880f256.h"

#elif defined(EFM32LG880F64)
#include "efm32lg880f64.h"

#elif defined(EFM32LG890F128)
#include "efm32lg890f128.h"

#elif defined(EFM32LG890F256)
#include "efm32lg890f256.h"

#elif defined(EFM32LG890F64)
#include "efm32lg890f64.h"

#elif defined(EFM32LG895F128)
#include "efm32lg895f128.h"

#elif defined(EFM32LG895F256)
#include "efm32lg895f256.h"

#elif defined(EFM32LG895F64)
#include "efm32lg895f64.h"

#elif defined(EFM32LG940F128)
#include "efm32lg940f128.h"

#elif defined(EFM32LG940F256)
#include "efm32lg940f256.h"

#elif defined(EFM32LG940F64)
#include "efm32lg940f64.h"

#elif defined(EFM32LG942F128)
#include "efm32lg942f128.h"

#elif defined(EFM32LG942F256)
#include "efm32lg942f256.h"

#elif defined(EFM32LG942F64)
#include "efm32lg942f64.h"

#elif defined(EFM32LG980F128)
#include "efm32lg980f128.h"

#elif defined(EFM32LG980F256)
#include "efm32lg980f256.h"

#elif defined(EFM32LG980F64)
#include "efm32lg980f64.h"

#elif defined(EFM32LG990F128)
#include "efm32lg990f128.h"

#elif defined(EFM32LG990F256)
#include "efm32lg990f256.h"

#elif defined(EFM32LG990F64)
#include "efm32lg990f64.h"

#elif defined(EFM32LG995F128)
#include "efm32lg995f128.h"

#elif defined(EFM32LG995F256)
#include "efm32lg995f256.h"

#elif defined(EFM32LG995F64)
#include "efm32lg995f64.h"

#elif defined(EFM32TG108F16)
#include "efm32tg108f16.h"

#elif defined(EFM32TG108F32)
#include "efm32tg108f32.h"

#elif defined(EFM32TG108F4)
#include "efm32tg108f4.h"

#elif defined(EFM32TG108F8)
#include "efm32tg108f8.h"

#elif defined(EFM32TG110F16)
#include "efm32tg110f16.h"

#elif defined(EFM32TG110F32)
#include "efm32tg110f32.h"

#elif defined(EFM32TG110F4)
#include "efm32tg110f4.h"

#elif defined(EFM32TG110F8)
#include "efm32tg110f8.h"

#elif defined(EFM32TG210F16)
#include "efm32tg210f16.h"

#elif defined(EFM32TG210F32)
#include "efm32tg210f32.h"

#elif defined(EFM32TG210F8)
#include "efm32tg210f8.h"

#elif defined(EFM32TG222F16)
#include "efm32tg222f16.h"

#elif defined(EFM32TG222F32)
#include "efm32tg222f32.h"

#elif defined(EFM32TG222F8)
#include "efm32tg222f8.h"

#elif defined(EFM32TG230F16)
#include "efm32tg230f16.h"

#elif defined(EFM32TG230F32)
#include "efm32tg230f32.h"

#elif defined(EFM32TG230F8)
#include "efm32tg230f8.h"

#elif defined(EFM32TG232F16)
#include "efm32tg232f16.h"

#elif defined(EFM32TG232F32)
#include "efm32tg232f32.h"

#elif defined(EFM32TG232F8)
#include "efm32tg232f8.h"

#elif defined(EFM32TG822F16)
#include "efm32tg822f16.h"

#elif defined(EFM32TG822F32)
#include "efm32tg822f32.h"

#elif defined(EFM32TG822F8)
#include "efm32tg822f8.h"

#elif defined(EFM32TG840F16)
#include "efm32tg840f16.h"

#elif defined(EFM32TG840F32)
#include "efm32tg840f32.h"

#elif defined(EFM32TG840F8)
#include "efm32tg840f8.h"

#elif defined(EFM32TG842F16)
#include "efm32tg842f16.h"

#elif defined(EFM32TG842F32)
#include "efm32tg842f32.h"

#elif defined(EFM32TG842F8)
#include "efm32tg842f8.h"


#else
#error "efm32.h: PART NUMBER undefined"
#endif

#endif

