/**
 *******************************************************************************
 * @file  hc32_ll_dbgc.h
 * @brief This file contains all the functions prototypes of the DBGC driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
   2023-09-30       CDT             Remove API DBGC_GetChipID()
                                    Add macro definition DBGC_Trace_Mode
                                    Add declaration of API DBGC_TraceIoCmd,DBGC_TraceModeConfig
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
#ifndef __HC32_LL_DBGC_H__
#define __HC32_LL_DBGC_H__

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
 * @addtogroup LL_DBGC
 * @{
 */

#if (LL_DBGC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup DBGC_Global_Macros DBGC Global Macros
 * @{
 */

/**
 * @defgroup DBGC_Periph_Sel DBGC Periph Selection
 * @{
 */
#define DBGC_PERIPH_SWDT                    (DBGC_MCUSTPCTL_SWDTSTP)
#define DBGC_PERIPH_WDT                     (DBGC_MCUSTPCTL_WDTSTP )
#define DBGC_PERIPH_RTC                     (DBGC_MCUSTPCTL_RTCSTP )
#define DBGC_PERIPH_TMR0_1                  (DBGC_MCUSTPCTL_M06STP)
#define DBGC_PERIPH_TMR0_2                  (DBGC_MCUSTPCTL_M07STP)
#define DBGC_PERIPH_TMR4_1                  (DBGC_MCUSTPCTL_M12STP)
#define DBGC_PERIPH_TMR4_2                  (DBGC_MCUSTPCTL_M13STP)
#define DBGC_PERIPH_TMR4_3                  (DBGC_MCUSTPCTL_M14STP)
#define DBGC_PERIPH_TMR6_1                  (DBGC_MCUSTPCTL_M15STP)
#define DBGC_PERIPH_TMR6_2                  (DBGC_MCUSTPCTL_M16STP)
/**
 * @}
 */

/**
 * @defgroup DBGC_Periph2_Sel DBGC Periph2 Selection
 * @{
 */
#define DBGC_PERIPH_TMRA_1                  (DBGC_MCUSTPCTL2_M32STP)
#define DBGC_PERIPH_TMRA_2                  (DBGC_MCUSTPCTL2_M33STP)
#define DBGC_PERIPH_TMRA_3                  (DBGC_MCUSTPCTL2_M34STP)
#define DBGC_PERIPH_TMRA_4                  (DBGC_MCUSTPCTL2_M35STP)
#define DBGC_PERIPH_TMRA_5                  (DBGC_MCUSTPCTL2_M36STP)
/**
 * @}
 */

/**
 * @defgroup DBGC_Trace_Mode DBGC trace mode
 * @{
 */
#define DBGC_TRACE_ASYNC                    (0UL)
#define DBGC_TRACE_SYNC_1BIT                (DBGC_MCUTRACECTL_TRACEMODE_0)
#define DBGC_TRACE_SYNC_2BIT                (DBGC_MCUTRACECTL_TRACEMODE_1)
#define DBGC_TRACE_SYNC_4BIT                (DBGC_MCUTRACECTL_TRACEMODE)
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
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup DBGC_Global_Functions
 * @{
 */
void DBGC_PeriphCmd(uint32_t u32Periph, en_functional_state_t enNewState);
void DBGC_Periph2Cmd(uint32_t u32Periph, en_functional_state_t enNewState);
void DBGC_TraceIoCmd(en_functional_state_t enNewState);
void DBGC_TraceModeConfig(uint32_t u32TraceMode);
/**
 * @}
 */

#endif /* LL_DBGC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_DBGC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
