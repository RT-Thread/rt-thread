/**
 *******************************************************************************
 * @file  hc32f4a0_hrpwm.h
 * @brief Head file for HRPWM module.
 *
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Wangmin         First version
   2020-09-07       Wangmin         Modify channel delay configure function 
                                    parameter type.
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
#ifndef __HC32F4A0_HRPWM_H__
#define __HC32F4A0_HRPWM_H__

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
 * @addtogroup DDL_HRPWM
 * @{
 */

#if (DDL_HRPWM_ENABLE == DDL_ON)

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

/** @defgroup HRPWM_Calibrate_Unit_Define HRPWM Calibrate unit define
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
en_functional_state_t HRPWM_ConditionConfirm(void);

/* Process for getting HRPWM Calibrate function code */
en_result_t HRPWM_CalibrateProcess(uint32_t u32Unit, uint8_t* pu8Code);

/* HRPWM Calibrate function enable or disable for specified unit */
void HRPWM_CalibrateCmd(uint32_t u32Unit, en_functional_state_t enNewState);
/* HRPWM Calibrate function status get for specified unit */
en_functional_state_t HRPWM_GetCalibrateStd(uint32_t u32Unit);
/* HRPWM Calibrate code get for specified unit */
uint8_t HRPWM_GetCalCode(uint32_t u32Unit);

/* HRPWM function enable or disable for specified channel */
void HRPWM_CHCmd(uint32_t u32Ch, en_functional_state_t enNewState);
/* HRPWM positive edge adjust enable or disable for specified channel */
void HRPWM_CHPositAdjCmd(uint32_t u32Ch, en_functional_state_t enNewState);
/* HRPWM negative edge adjust enable or disable for specified channel */
void HRPWM_CHNegatAdjCmd(uint32_t u32Ch, en_functional_state_t enNewState);
/* HRPWM positive edge adjust delay counts configration for specified channel */
void HRPWM_CHPositCfg(uint32_t u32Ch, uint8_t u8DelayNum);
/* HRPWM negative edge adjust delay counts configration for specified channel */
void HRPWM_CHNegatCfg(uint32_t u32Ch, uint8_t u8DelayNum);

/**
 * @}
 */

#endif /* DDL_HRPWM_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_HRPWM_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
