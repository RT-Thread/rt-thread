/**
 *******************************************************************************
 * @file  stl_common.h
 * @brief This file contains STL common definitions: enumeration, macros and
 *        structures definitions.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#ifndef __STL_COMMON_H__
#define __STL_COMMON_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup IEC60730_STL
 * @{
 */

/**
 * @addtogroup IEC60730_STL_Common
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
*******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup STL_Common_Global_Macros STL Common Global Macros
 * @{
 */

/**
 * @defgroup STL_Generic_Error_Codes STL Generic Error Codes
 * @{
 */
#define STL_OK                          (0UL)   /*!< No error occurs */
#define STL_ERR                         (1UL)   /*!< Error occurs */
/**
 * @}
 */

/**
 * @defgroup STL_Module_Switch STL Module Switch
 * @{
 */
#define STL_ON                          (1U)
#define STL_OFF                         (0U)
/**
 * @}
 */

/**
 * @defgroup Compiler_Macros Compiler Macros
 * @{
 */
#ifdef __CC_ARM                         /*!< ARM Compiler */
/* CPU will start executing at the program entry label __main when the CPU is reset */
extern void __main(void);

/* CC */
#define STL_SECTION(x)              __attribute__((section(x)))
#define STL_UNUSED                  __attribute__((unused))
#define STL_USED                    __attribute__((used))
#define STL_ALIGN(n)                __attribute__((aligned(n)))
#define STL_WEAK                    __WEAKDEF
#define STL_INLINE                  static __inline

#define CallApplicationStartUp( )   __main()

#elif defined (__ICCARM__)              /*!< IAR Compiler */
/* CPU will start executing at the program entry label __iar_program_start when the CPU is reset */
extern void __iar_program_start(void);

/* CC */
#define STL_SECTION(x)              @ x
#define STL_UNUSED
#define STL_USED                    __root
#define STL_PRAGMA(x)               _Pragma(#x)
#define STL_ALIGN(n)                STL_PRAGMA(data_alignment=n)
#define STL_WEAK                    __WEAKDEF
#define STL_INLINE                  static inline

#define CallApplicationStartUp( )   __iar_program_start()
#else
#error Unsupported tool chain
#endif
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __STL_COMMON_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
