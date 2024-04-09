/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal_def.h
  * @author  MCD Application Team
  * @brief   This file contains HAL common defines, enumeration, macros and
  *          structures definitions.
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7RSxx_HAL_DEF_H
#define STM32H7RSxx_HAL_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx.h"
#include "Legacy/stm32_hal_legacy.h"  /* Aliases file for old names compatibility */
#include <math.h>
#include <stddef.h>

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  HAL Status structures definition
  */
typedef enum
{
  HAL_OK       = 0x00,
  HAL_ERROR    = 0x01,
  HAL_BUSY     = 0x02,
  HAL_TIMEOUT  = 0x03
} HAL_StatusTypeDef;

/**
  * @brief  HAL Lock structures definition
  */
typedef enum
{
  HAL_UNLOCKED = 0x00,
  HAL_LOCKED   = 0x01
} HAL_LockTypeDef;

/* Exported macros -----------------------------------------------------------*/

#if !defined(UNUSED)
#define UNUSED(X) (void)X      /* To avoid gcc/g++ warnings */
#endif /* UNUSED */

#define HAL_MAX_DELAY      0xFFFFFFFFU

#define HAL_IS_BIT_SET(REG, BIT)         (((REG) & (BIT)) == (BIT))
#define HAL_IS_BIT_CLR(REG, BIT)         (((REG) & (BIT)) == 0U)

#define __HAL_LINKDMA(__HANDLE__, __PPP_DMA_FIELD__, __DMA_HANDLE__) \
  do{                                                    \
    (__HANDLE__)->__PPP_DMA_FIELD__ = &(__DMA_HANDLE__); \
    (__DMA_HANDLE__).Parent = (__HANDLE__);              \
  } while(0)

/** @brief Reset the Handle's State field.
  * @param __HANDLE__ specifies the Peripheral Handle.
  * @note  This macro can be used for the following purpose:
  *          - When the Handle is declared as local variable; before passing it as parameter
  *            to HAL_PPP_Init() for the first time, it is mandatory to use this macro
  *            to set to 0 the Handle's "State" field.
  *            Otherwise, "State" field may have any random value and the first time the function
  *            HAL_PPP_Init() is called, the low level hardware initialization will be missed
  *            (i.e. HAL_PPP_MspInit() will not be executed).
  *          - When there is a need to reconfigure the low level hardware: instead of calling
  *            HAL_PPP_DeInit() then HAL_PPP_Init(), user can make a call to this macro then HAL_PPP_Init().
  *            In this later function, when the Handle's "State" field is set to 0, it will execute the function
  *            HAL_PPP_MspInit() which will reconfigure the low level hardware.
  * @retval None
  */
#define __HAL_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = 0)

#if (USE_RTOS == 1)
/* Reserved for future use */
#error " USE_RTOS should be 0 in the current HAL release "
#else
#define __HAL_LOCK(__HANDLE__)            \
  do{                                     \
    if((__HANDLE__)->Lock == HAL_LOCKED)  \
    {                                     \
      return HAL_BUSY;                    \
    }                                     \
    else                                  \
    {                                     \
      (__HANDLE__)->Lock = HAL_LOCKED;    \
    }                                     \
  }while (0)

#define __HAL_UNLOCK(__HANDLE__)          \
  do{                                     \
    (__HANDLE__)->Lock = HAL_UNLOCKED;    \
  }while (0)
#endif /* USE_RTOS */


#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
#ifndef __weak
#define __weak  __attribute__((weak))
#endif /* __weak */
#ifndef __packed
#define __packed  __attribute__((packed))
#endif /* packed */
#elif defined (__GNUC__) /* GNU Compiler */
#ifndef __weak
#define __weak  __attribute__((weak))
#endif /* __weak */
#ifndef __packed
#define __packed  __attribute__((__packed__))
#endif /* __packed */
#endif /* __GNUC__ */

/* Macro to get buffer 32-bytes aligned (aligned to cache line width) */
#define ALIGN_32BYTES(buf)  buf __attribute__((aligned(32)))

/* Macro to get buffer 8-bytes aligned (aligned to double-word width) */
/* This alignment is required for double-word DMA transfers */
#define ALIGN_8BYTES(buf)  buf __attribute__((aligned(8)))

/* Legacy macros to get variable 4-bytes aligned */
#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN
#endif /* __ALIGN_BEGIN */
#ifndef __ALIGN_END
#define __ALIGN_END  __attribute__((aligned(4)))
#endif /* __ALIGN_END */

/**
  * @brief  __RAM_FUNC definition
  */
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
/* ARM Compiler V6
   ---------------
   RAM functions are defined using the toolchain options.
   Functions that are executed in RAM should reside in a separate source module.
   Using the 'Options for File' dialog you can simply change the 'Code / Const'
   area of a module to a memory space in physical RAM.
   Available memory areas are declared in the 'Target' tab of the 'Options for Target'
   dialog.
*/
#define __RAM_FUNC

#elif defined (__ICCARM__)
/* ICCARM Compiler
   ---------------
   RAM functions are defined using a specific toolchain keyword "__ramfunc".
*/
#define __RAM_FUNC  __ramfunc

#elif defined (__GNUC__)
/* GNU Compiler
   ------------
  RAM functions are defined using a specific toolchain attribute
   "__attribute__((section(".RamFunc")))".
*/
#define __RAM_FUNC  __attribute__((section(".RamFunc")))

#endif /* __ARMCC_VERSION */

/**
  * @brief  __NOINLINE definition
  */
#if (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) || defined (__GNUC__)
/* ARM V6 & GNU Compiler
   ---------------------
*/
#define __NOINLINE __attribute__((noinline))

#elif defined (__ICCARM__)
/* ICCARM Compiler
   ---------------
*/
#define __NOINLINE _Pragma("optimize = no_inline")

#endif /* __ARMCC_VERSION || __GNUC__ */


#ifdef __cplusplus
}
#endif

#endif /* STM32H7RSxx_HAL_DEF_H */
