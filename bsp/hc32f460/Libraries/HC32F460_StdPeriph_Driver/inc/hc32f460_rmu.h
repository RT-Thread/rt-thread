/*****************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_rmu.h
 **
 ** A detailed description is available at
 ** @link RmuGroup RMU description @endlink
 **
 **   - 2018-10-28  CDT  First version for Device Driver Library of RMU
 **
 ******************************************************************************/
#ifndef __HC32F460_RMU_H__
#define __HC32F460_RMU_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

#if (DDL_RMU_ENABLE == DDL_ON)

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup RmuGroup Reset Management Unit(RMU)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief system reset cause flag
 **
 ******************************************************************************/
typedef struct stc_rmu_rstcause
{
    en_flag_status_t   enMultiRst;              ///< Multiply reset cause
    en_flag_status_t   enXtalErr;               ///< Xtal error reset
    en_flag_status_t   enClkFreqErr;            ///< Clk freqence error reset
    en_flag_status_t   enRamEcc;                ///< Ram ECC reset
    en_flag_status_t   enRamParityErr;          ///< Ram parity error reset
    en_flag_status_t   enMpuErr;                ///< Mpu error reset
    en_flag_status_t   enSoftware;              ///< Software reset
    en_flag_status_t   enPowerDown;             ///< Power down reset
    en_flag_status_t   enSwdt;                  ///< Special watchdog timer reset
    en_flag_status_t   enWdt;                   ///< Watchdog timer reset
    en_flag_status_t   enPvd2;                  ///< Program voltage Dectection 2 reset
    en_flag_status_t   enPvd1;                  ///< Program voltage Dectection 1 reset
    en_flag_status_t   enBrownOut;              ///< Brown out reset
    en_flag_status_t   enRstPin;                ///< Reset pin reset
    en_flag_status_t   enPowerOn;               ///< Power on reset
}stc_rmu_rstcause_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
en_result_t RMU_GetResetCause(stc_rmu_rstcause_t *pstcData);
en_result_t RMU_ClrResetFlag(void);

//@} // RmuGroup

#ifdef __cplusplus
}
#endif

#endif /* DDL_RMU_ENABLE */

#endif /* __HC32F460_RMU_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

