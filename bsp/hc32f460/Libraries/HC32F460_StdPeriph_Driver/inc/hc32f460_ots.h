/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_ots.h
 **
 ** A detailed description is available at
 ** @link OtsGroup Ots description @endlink
 **
 **   - 2018-10-26  CDT First version for Device Driver Library of Ots.
 **
 ******************************************************************************/
#ifndef __HC32F460_OTS_H__
#define __HC32F460_OTS_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

#if (DDL_OTS_ENABLE == DDL_ON)

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup OtsGroup On-chip Temperature Sensor(OTS)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/* Automatically turn off the analog temperature sensor after the temperature
   measurement is over. */
typedef enum en_ots_auto_off
{
    OtsAutoOff_Disable = 0x0,           ///< Disable automatically turn off OTS.
    OtsAutoOff_Enable  = 0x1,           ///< Enable automatically turn off OTS.
} en_ots_auto_off_t;

/* Temperature measurement end interrupt request. */
typedef enum en_ots_ie
{
    OtsInt_Disable = 0x0,               ///< Disable OTS interrupt.
    OtsInt_Enable  = 0x1,               ///< Enable OTS interrupt.
} en_ots_ie_t;

/* OTS clock selection. */
typedef enum en_ots_clk_sel
{
    OtsClkSel_Xtal = 0x0,               ///< Select XTAL as OTS clock.
    OtsClkSel_Hrc  = 0x1,               ///< Select HRC as OTS clock.
} en_ots_clk_sel_t;

/* OTS OTS initialization structure definition. */
typedef struct stc_ots_init
{
    en_ots_auto_off_t enAutoOff;        ///< @ref en_ots_auto_off_t.
    en_ots_clk_sel_t  enClkSel;         ///< @ref en_ots_clk_sel_t.
    float32_t f32SlopeK;                ///< K: Temperature slope (calculated by calibration experiment). */
    float32_t f32OffsetM;               ///< M: Temperature offset (calculated by calibration experiment). */
} stc_ots_init_t;

/* OTS common trigger source select */
typedef enum en_ots_com_trigger
{
    OtsComTrigger_1   = 0x1,            ///< Select common trigger 1.
    OtsComTrigger_2   = 0x2,            ///< Select common trigger 2.
    OtsComTrigger_1_2 = 0x3,            ///< Select common trigger 1 and 2.
} en_ots_com_trigger_t;

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/

/**
 * @brief  Start OTS.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void OTS_Start(void)
{
    bM4_OTS_CTL_OTSST = (uint32_t)1u;
}

/**
 * @brief  Stop OTS.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void OTS_Stop(void)
{
    bM4_OTS_CTL_OTSST = (uint32_t)0u;
}

en_result_t OTS_Init(const stc_ots_init_t *pstcInit);
void OTS_DeInit(void);

en_result_t OTS_Polling(float32_t *pf32Temp, uint32_t u32Timeout);

void OTS_IntCmd(en_functional_state_t enNewState);
void OTS_SetTriggerSrc(en_event_src_t enEvent);
void OTS_ComTriggerCmd(en_ots_com_trigger_t enComTrigger, en_functional_state_t enState);

en_result_t OTS_ScalingExperiment(uint16_t *pu16Dr1, uint16_t *pu16Dr2, \
                                  uint16_t *pu16Ecr, float32_t *pf32A,  \
                                  uint32_t u32Timeout);

float OTS_CalculateTemp(void);

//@} // OtsGroup

#ifdef __cplusplus
}
#endif

#endif /* DDL_OTS_ENABLE */

#endif /* __HC32F460_OTS_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
