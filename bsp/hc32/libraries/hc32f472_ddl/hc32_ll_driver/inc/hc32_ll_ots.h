/**
 *******************************************************************************
 * @file  hc32_ll_ots.h
 * @brief This file contains all the functions prototypes of the OTS driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Modify typo
                                    Modify API OTS_DeInit()
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
#ifndef __HC32_LL_OTS_H__
#define __HC32_LL_OTS_H__

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
 * @addtogroup LL_OTS
 * @{
 */

#if (LL_OTS_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup OTS_Global_Types OTS Global Types
 * @{
 */

/**
 * @brief Conditions of default parameters(slope K and offset M).
 * @note Parameter 'u8T1' CANNOT equal to parameter 'u8T2'.
 */
typedef struct {
    uint16_t u16ClockFreq;                  /*!< Frequency(MHz) of clock sources that OTS is going to use. */
    uint8_t u8T1;                           /*!< Temperature value T1 for the default parameter.
                                                 This parameter can be a value of @ref OTS_Param_Temp_Cond */
    uint8_t u8T2;                           /*!< Temperature value T2 for the default parameter.
                                                 This parameter can be a value of @ref OTS_Param_Temp_Cond */
} stc_para_temp_cond_t;

/**
 * @brief OTS initialization structure.
 */
typedef struct {
    uint16_t u16ClockSrc;                   /*!< Specifies clock source for OTS.
                                                 This parameter can be a value of @ref OTS_Clock_Source */
    uint16_t u16AutoOffEn;                  /*!< Enable or disable OTS automatic-off(after sampled temperature).
                                                 This parameter can be a value of @ref OTS_Auto_Off_En */
    float32_t f32SlopeK;                    /*!< K: Temperature slope (calculated by calibration experiment).
                                                 If you want to use the default parameters(slope K and offset M),
                                                 specify both 'f32SlopeK' and 'f32OffsetM' as ZERO. */
    float32_t f32OffsetM;                   /*!< M: Temperature offset (calculated by calibration experiment).
                                                 If you want to use the default parameters(slope K and offset M),
                                                 specify both 'f32SlopeK' and 'f32OffsetM' as ZERO. */
    stc_para_temp_cond_t stcParaCond;       /*!< Specifies the temperature conditions of the default parameters(slope K and offset M) if you
                                                 want to use the default parameters. */
} stc_ots_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup OTS_Global_Macros OTS Global Macros
 * @{
 */

/**
 * @defgroup OTS_Clock_Source OTS Clock Source
 * @{
 */
#define OTS_CLK_XTAL                    (0x0U)              /*!< Select XTAL as OTS clock. */
#define OTS_CLK_HRC                     (OTS_CTL_OTSCK)     /*!< Select HRC as OTS clock */
/**
 * @}
 */

/**
 * @defgroup OTS_Auto_Off_En OTS Automatic Off Function Control
 * @{
 */
#define OTS_AUTO_OFF_DISABLE            (0x0U)              /*!< OTS automatically turned off when sampled done. */
#define OTS_AUTO_OFF_ENABLE             (OTS_CTL_TSSTP)     /*!< OTS is still on when sampled done. */
/**
 * @}
 */

/**
 * @defgroup OTS_Param_Temp_Cond OTS Parameter Temperature Condition
 * @{
 */
#define OTS_PARAM_TEMP_COND_TN40        (0U)                /*!< -40 degrees Celsius. */
#define OTS_PARAM_TEMP_COND_T25         (1U)                /*!< 25 degrees Celsius. */
#define OTS_PARAM_TEMP_COND_T125        (2U)                /*!< 125 degrees Celsius. */
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
 * @addtogroup OTS_Global_Functions
 * @{
 */

/**
 * @brief  Start OTS.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void OTS_Start(void)
{
    WRITE_REG32(bCM_OTS->CTL_b.OTSST, 1U);
}

/**
 * @brief  Stop OTS.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void OTS_Stop(void)
{
    WRITE_REG32(bCM_OTS->CTL_b.OTSST, 0U);
}

int32_t OTS_Init(const stc_ots_init_t *pstcOTSInit);
int32_t OTS_StructInit(stc_ots_init_t *pstcOTSInit);
int32_t OTS_DeInit(void);

int32_t OTS_Polling(float32_t *pf32Temp, uint32_t u32Timeout);

void OTS_IntCmd(en_functional_state_t enNewState);

int32_t OTS_ScalingExperiment(uint16_t *pu16Dr1, uint16_t *pu16Dr2,
                              uint16_t *pu16Ecr, float32_t *pf32A,
                              uint32_t u32Timeout);

float32_t OTS_CalculateTemp(void);

/**
 * @}
 */

#endif /* LL_OTS_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_OTS_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
