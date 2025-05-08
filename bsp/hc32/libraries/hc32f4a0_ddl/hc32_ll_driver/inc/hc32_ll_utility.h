/**
 *******************************************************************************
 * @file  hc32_ll_utility.h
 * @brief This file contains all the functions prototypes of the DDL utility.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_UTILITY_H__
#define __HC32_LL_UTILITY_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_UTILITY
 * @{
 */

#if (LL_UTILITY_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup UTILITY_Global_Functions
 * @{
 */

/* Imprecise delay */
void DDL_DelayMS(uint32_t u32Count);
void DDL_DelayUS(uint32_t u32Count);

/* Systick functions */
int32_t SysTick_Init(uint32_t u32Freq);
void SysTick_Delay(uint32_t u32Delay);
void SysTick_IncTick(void);
uint32_t SysTick_GetTick(void);
void SysTick_Suspend(void);
void SysTick_Resume(void);

#if (LL_PRINT_ENABLE == DDL_ON)
int32_t LL_PrintfInit(void *vpDevice, uint32_t u32Param, int32_t (*pfnPreinit)(void *vpDevice, uint32_t u32Param));
#endif

/* You can add your own assert functions by implement the function DDL_AssertHandler
   definition follow the function DDL_AssertHandler declaration */
#ifdef __DEBUG
#define DDL_ASSERT(x)                                                          \
do {                                                                           \
    ((x) ? (void)0 : DDL_AssertHandler(__FILE__, __LINE__));                   \
} while (0)
/* Exported function */
void DDL_AssertHandler(const char *file, int line);
#else
#define DDL_ASSERT(x)                   ((void)0U)
#endif /* __DEBUG */

#if (LL_PRINT_ENABLE == DDL_ON)
#include <stdio.h>
__WEAKDEF int32_t DDL_ConsoleOutputChar(char cData);

#define DDL_PrintfInit                  (void)LL_PrintfInit
#define DDL_Printf                      (void)printf
#else
#define DDL_PrintfInit(vpDevice, u32Param, pfnPreinit)
#define DDL_Printf(...)
#endif

/**
 * @}
 */

#endif /* LL_UTILITY_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_UTILITY_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
