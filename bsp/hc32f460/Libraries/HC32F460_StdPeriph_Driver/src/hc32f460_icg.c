/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_icg.c
 **
 ** A detailed description is available at
 ** @link IcgGroup Initialize Configure description @endlink
 **
 **   - 2018-10-15  CDT  First version for Device Driver Library of ICG.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f460_icg.h"

#if (DDL_ICG_ENABLE == DDL_ON)

/**
 *******************************************************************************
 ** \addtogroup IcgGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
#if defined ( __GNUC__ ) && !defined (__CC_ARM) /* GNU Compiler */
const uint32_t u32ICG[] __attribute__((section(".icg_sec"))) =
#elif defined (__CC_ARM)
const uint32_t u32ICG[] __attribute__((at(0x400))) =
#elif defined (__ICCARM__)
__root const uint32_t u32ICG[] @ 0x400 =
#else
#error "unsupported compiler!!"
#endif
{
    /* ICG 0~ 3 */
    ICG0_REGISTER_CONSTANT,
    ICG1_REGISTER_CONSTANT,
    ICG2_REGISTER_CONSTANT,
    ICG3_REGISTER_CONSTANT,
    /* ICG 4~ 7 */
    ICG4_REGISTER_CONSTANT,
    ICG5_REGISTER_CONSTANT,
    ICG6_REGISTER_CONSTANT,
    ICG7_REGISTER_CONSTANT,
};

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

//@} // IcgGroup

#endif /* DDL_ICG_ENABLE */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
