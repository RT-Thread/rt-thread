/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_utility.h
 **
 ** A detailed description is available at
 ** @link DdlUtilityGroup Ddl Utility description @endlink
 **
 **   - 2018-11-02 CDT First version for Device Driver Library Utility.
 **
 ******************************************************************************/
#ifndef __HC32F460_UTILITY_H__
#define __HC32F460_UTILITY_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

#if (DDL_UTILITY_ENABLE == DDL_ON)

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup DdlUtilityGroup Device Driver Library Utility(DDLUTILITY)
 **
 ******************************************************************************/
//@{

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
/* A approximate delay */
void Ddl_Delay1ms(uint32_t u32Cnt);
void Ddl_Delay1us(uint32_t u32Cnt);

/* Systick functions */
en_result_t SysTick_Init(uint32_t u32Freq);
void SysTick_Delay(uint32_t u32Delay);
void SysTick_IncTick(void);
uint32_t SysTick_GetTick(void);
void SysTick_Suspend(void);
void SysTick_Resume(void);

/*! Ddl assert, you can add your own assert functions by implement the function
Ddl_AssertHook definition follow the function Ddl_AssertHook declaration */
#ifdef __DEBUG
#define DDL_ASSERT(x)                                                          \
do{                                                                            \
    ((x) ? (void)0 : Ddl_AssertHandler((uint8_t *)__FILE__, __LINE__));        \
}while(0)
/* Exported function */
void Ddl_AssertHandler(uint8_t *file, int16_t line);
#else
#define DDL_ASSERT(x)                               (void)(0)
#endif /* __DEBUG */

#if (DDL_PRINT_ENABLE == DDL_ON)
#include <stdio.h>

en_result_t UART_PrintfInit(M4_USART_TypeDef *UARTx,
                            uint32_t u32Baudrate,
                            void (*PortInit)(void));

#define DDL_PrintfInit      (void)UART_PrintfInit
#define DDL_Printf          (void)printf
#else
#define DDL_PrintfInit(x, y, z)
#define DDL_Printf(fmt, ...)
#endif

//@} // DdlUtilityGroup

#ifdef __cplusplus
}
#endif

#endif /* DDL_UTILITY_ENABLE */

#endif /* __HC32F460_UTILITY_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
