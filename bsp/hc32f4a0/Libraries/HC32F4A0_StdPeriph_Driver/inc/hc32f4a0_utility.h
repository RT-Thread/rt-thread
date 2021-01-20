/**
 *******************************************************************************
 * @file  hc32f4a0_utility.h
 * @brief This file contains all the functions prototypes of the DDL utility.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Yangjp          First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32F4A0_UTILITY_H__
#define __HC32F4A0_UTILITY_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_UTILITY
 * @{
 */

#if (DDL_UTILITY_ENABLE == DDL_ON)

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
void DDL_DelayMS(uint32_t u32Cnt);
void DDL_DelayUS(uint32_t u32Cnt);

/* Systick functions */
en_result_t SysTick_Init(uint32_t u32Freq);
void SysTick_Delay(uint32_t u32Delay);
void SysTick_IncTick(void);
uint32_t SysTick_GetTick(void);
void SysTick_Suspend(void);
void SysTick_Resume(void);

/* You can add your own assert functions by implement the function DDL_AssertHandler
   definition follow the function DDL_AssertHandler declaration */
#ifdef __DEBUG
    #define DDL_ASSERT(x)                                                      \
    do{                                                                        \
        ((x) ? (void)0 : DDL_AssertHandler(__FILE__, __LINE__));    \
    }while(0)
    /* Exported function */
    void DDL_AssertHandler(const char *file, int line);
#else
    #define DDL_ASSERT(x)               ((void)0U)
#endif /* __DEBUG */

#if (DDL_PRINT_ENABLE == DDL_ON)
#include <stdio.h>

en_result_t DDL_PrintfInit(void);
#endif

/**
 * @}
 */

#endif /* DDL_UTILITY_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_UTILITY_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
