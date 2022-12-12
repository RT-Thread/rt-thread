/**
 *******************************************************************************
 * @file  hc32_ll_hrpwm.h
 * @brief Head file for HRPWM module.
 *
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
#ifndef __HC32_LL_HRPWM_H__
#define __HC32_LL_HRPWM_H__

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
 * @addtogroup LL_HRPWM
 * @{
 */

#if (LL_HRPWM_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup HRPWM_Global_Macros HRPWM Global Macros
 * @{
 */

#define   HRPWM_CH_MIN                (1UL)
#define   HRPWM_CH_MAX                (16UL)

#define   HRPWM_CH_DELAY_NUM_MIN      (1U)
#define   HRPWM_CH_DELAY_NUM_MAX      (256U)

/**
 * @defgroup HRPWM_Calibrate_Unit_Define HRPWM Calibrate Unit Define
 * @{
 */
#define   HRPWM_CAL_UNIT0             (0x00UL)
#define   HRPWM_CAL_UNIT1             (0x01UL)
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
 * @addtogroup HRPWM_Global_Functions
 * @{
 */
/* HRPWM Judge the condition of calibration function */
en_functional_state_t HRPWM_CondConfirm(void);

/* Process for getting HRPWM Calibrate function code */
int32_t HRPWM_CalibrateProcess(uint32_t u32Unit, uint8_t *pu8Code);

/* HRPWM Calibrate function enable or disable for specified unit */
void HRPWM_CalibrateCmd(uint32_t u32Unit, en_functional_state_t enNewState);
/* HRPWM Calibrate function status get for specified unit */
en_functional_state_t HRPWM_GetCalibrateState(uint32_t u32Unit);
/* HRPWM Calibrate code get for specified unit */
uint8_t HRPWM_GetCalibrateCode(uint32_t u32Unit);

/* HRPWM function enable or disable for specified channel */
void HRPWM_ChCmd(uint32_t u32Ch, en_functional_state_t enNewState);
/* HRPWM positive edge adjust enable or disable for specified channel */
void HRPWM_ChPositiveAdjustCmd(uint32_t u32Ch, en_functional_state_t enNewState);
/* HRPWM negative edge adjust enable or disable for specified channel */
void HRPWM_ChNegativeAdjustCmd(uint32_t u32Ch, en_functional_state_t enNewState);
/* HRPWM positive edge adjust delay counts configration for specified channel */
void HRPWM_ChPositiveAdjustConfig(uint32_t u32Ch, uint8_t u8DelayNum);
/* HRPWM negative edge adjust delay counts configration for specified channel */
void HRPWM_ChNegativeAdjustConfig(uint32_t u32Ch, uint8_t u8DelayNum);

/**
 * @}
 */

#endif /* LL_HRPWM_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_HRPWM_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
