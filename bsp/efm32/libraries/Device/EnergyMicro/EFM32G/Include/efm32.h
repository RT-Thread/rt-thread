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
 * @version 3.0.0
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 ******************************************************************************
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


#else
#error "efm32.h: PART NUMBER undefined"
#endif

#endif

