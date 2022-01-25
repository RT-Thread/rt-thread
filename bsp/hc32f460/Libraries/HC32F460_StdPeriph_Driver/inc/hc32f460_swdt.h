/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_swdt.h
 **
 ** A detailed description is available at
 ** @link SwdtGroup Special Watchdog Counter description @endlink
 **
 **   - 2018-10-16  CDT  First version for Device Driver Library of SWDT.
 **
 ******************************************************************************/
#ifndef __HC32F460_SWDT_H__
#define __HC32F460_SWDT_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

#if (DDL_SWDT_ENABLE == DDL_ON)

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup SwdtGroup Special Watchdog Counter(SWDT)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief SWDT flag type enumeration
 ******************************************************************************/
typedef enum en_swdt_flag_type
{
    SwdtFlagCountUnderflow = 0u,            ///< Count underflow flag
    SwdtFlagRefreshError   = 1u,            ///< Refresh error flag
} en_swdt_flag_type_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/* Base functions */
en_result_t SWDT_RefreshCounter(void);
uint16_t SWDT_GetCountValue(void);

/* Flags functions */
en_flag_status_t SWDT_GetFlag(en_swdt_flag_type_t enFlag);
en_result_t SWDT_ClearFlag(en_swdt_flag_type_t enFlag);

//@} // SwdtGroup

#ifdef __cplusplus
}
#endif

#endif /* DDL_SWDT_ENABLE */

#endif /* __HC32F460_SWDT_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
