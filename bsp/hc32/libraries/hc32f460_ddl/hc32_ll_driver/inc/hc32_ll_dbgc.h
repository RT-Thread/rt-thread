/**
 *******************************************************************************
 * @file  hc32_ll_dbgc.h
 * @brief This file contains all the functions prototypes of the DBGC driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-09-30       CDT             First version
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
/**
 * @defgroup DBGC_Global_Types DBGC Global Types
 * @{
 */
/**
 * @brief DBGC authenticate ID definition
 */
typedef struct {
    uint32_t            u32AuthID0;     /*!< auth ID 0.       */
    uint32_t            u32AuthID1;     /*!< auth ID 1.       */
    uint32_t            u32AuthID2;     /*!< auth ID 2.       */
} stc_dbgc_auth_id_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup DBGC_Global_Macros DBGC Global Macros
 * @{
 */

/**
 * @defgroup DBGC_MCU_Security_Flag DBGC MCU Security Status flag
 * @{
 */
#define DBGC_SECURITY_AUTH_SUCCESS          (DBGC_MCUSTAT_AUTHFG)       /*!< AUTHID register equal security password */
#define DBGC_SECURITY_LOCK_LVL1             (DBGC_MCUSTAT_PRTLV1)       /*!< Security lock level 1 */
#define DBGC_SECURITY_LOCK_LVL2             (DBGC_MCUSTAT_PRTLV2)       /*!< Security lock level 2 */
#define DBGC_SECURITY_ALL                   (DBGC_MCUSTAT_AUTHFG | DBGC_MCUSTAT_PRTLV1 | DBGC_MCUSTAT_PRTLV2)
/**
 * @}
 */

/**
 * @defgroup DBGC_Periph_Sel DBGC Periph Selection
 * @{
 */
#define DBGC_PERIPH_SWDT                    (DBGC_MCUSTPCTL_SWDTSTP)
#define DBGC_PERIPH_WDT                     (DBGC_MCUSTPCTL_WDTSTP)
#define DBGC_PERIPH_RTC                     (DBGC_MCUSTPCTL_RTCSTP)
#define DBGC_PERIPH_TMR0_1                  (DBGC_MCUSTPCTL_TMR01STP)
#define DBGC_PERIPH_TMR0_2                  (DBGC_MCUSTPCTL_TMR02STP)
#define DBGC_PERIPH_TMR4_1                  (DBGC_MCUSTPCTL_TMR41STP)
#define DBGC_PERIPH_TMR4_2                  (DBGC_MCUSTPCTL_TMR42STP)
#define DBGC_PERIPH_TMR4_3                  (DBGC_MCUSTPCTL_TMR43STP)
#define DBGC_PERIPH_TMR6_1                  (DBGC_MCUSTPCTL_TM61STP)
#define DBGC_PERIPH_TMR6_2                  (DBGC_MCUSTPCTL_TM62STP)
#define DBGC_PERIPH_TMR6_3                  (DBGC_MCUSTPCTL_TMR63STP)
#define DBGC_PERIPH_TMRA_1                  (DBGC_MCUSTPCTL_TMRA1STP)
#define DBGC_PERIPH_TMRA_2                  (DBGC_MCUSTPCTL_TMRA2STP)
#define DBGC_PERIPH_TMRA_3                  (DBGC_MCUSTPCTL_TMRA3STP)
#define DBGC_PERIPH_TMRA_4                  (DBGC_MCUSTPCTL_TMRA4STP)
#define DBGC_PERIPH_TMRA_5                  (DBGC_MCUSTPCTL_TMRA5STP)
#define DBGC_PERIPH_TMRA_6                  (DBGC_MCUSTPCTL_TMRA6STP)
/**
 * @}
 */

/**
 * @defgroup DBGC_Periph2_Sel DBGC Periph2 Selection
 * @{
 */
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
en_flag_status_t DBGC_GetSecurityStatus(uint32_t u32Flag);
int32_t DBGC_FlashErase(uint32_t u32Timeout);
void DBGC_GetAuthID(stc_dbgc_auth_id_t *pstcAuthID);
void DBGC_PeriphCmd(uint32_t u32Periph, en_functional_state_t enNewState);
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
