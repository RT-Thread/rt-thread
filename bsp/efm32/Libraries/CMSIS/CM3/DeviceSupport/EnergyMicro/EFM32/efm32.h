/**************************************************************************//**
 * @file
 * @brief CMSIS Cortex-M3 Peripheral Access Layer for EFM32 Gxxx Device series
 *
 * This is a convenience header file for defining the EFM32 part number on the
 * build command line, instead of specifying the part specific header file.
 * @verbatim
 * Example: Add "-DEFM32G890F128" to your build options, to define part
 *          Add "#include "efm32.h" to your source files
 * @endverbatim
 * @author Energy Micro AS
 * @version 1.3.0
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2010 Energy Micro AS, http://www.energymicro.com</b>
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

/* Gecko Parts */

#if defined(EFM32G200F16)
#include "efm32g200f16.h"

#elif defined(EFM32G200F32)
#include "efm32g200f32.h"

#elif defined(EFM32G200F64)
#include "efm32g200f64.h"

#elif defined(EFM32G210F128)
#include "efm32g210f128.h"

#elif defined(EFM32G230F128)
#include "efm32g230f128.h"

#elif defined(EFM32G230F32)
#include "efm32g230f32.h"

#elif defined(EFM32G230F64)
#include "efm32g230f64.h"

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

