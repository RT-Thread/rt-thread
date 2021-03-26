/**
 *******************************************************************************
 * @file  hc32f4a0_fmac.h
 * @brief This file contains all the functions prototypes of the FMAC driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Heqb         First version
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
#ifndef __HC32F4A0_FMAC_H__
#define __HC32F4A0_FMAC_H__

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
 * @addtogroup DDL_FMAC
 * @{
 */

#if (DDL_FMAC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup FMAC_Global_Types FMAC Global Types
 * @{
 */

/**
 * @brief FMAC configuration structure
 */
typedef struct
{
    uint32_t u32FiltStage;                /*!< FMAC filter stage number config.
                                               This parameter can be a value of @ref FMAC_Filter_stage.*/
    uint32_t u32FiltShift;                /*!< FMAC filter result right shift bits.
                                               This parameter can be a value of @ref FMAC_Filter_shift.*/
    int16_t i16FiltFactor;                /*!< FMAC filter factor config.
                                               This parameter can be set -32768~32767 */
    uint32_t u32IntCmd;                   /*!< Enable or disable FMAC interrupt.
                                               This parameter can be a value of @ref FMAC_Interrupt_Definition.*/
}stc_fmac_init_t;

/**
 * @brief FMAC result definition
 */
typedef struct
{
    uint32_t u32ResultHigh;             /*!< The high value of the result.    */
    uint32_t u32ResultLow;              /*!< The low value of the result.     */

} stc_fmac_result_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup FMAC_Global_Macros FMAC Global Macros
 * @{
 */

/**
 * @defgroup FMAC_ENABLE FMAC Enable or Disable
 * @{
 */
#define FMAC_FUNC_ENABLE              (FMAC_ENR_FMACEN)
#define FMAC_FUNC_DISABLE             (0x0UL)
/**
 * @}
 */

/**
 * @defgroup FMAC_Interrupt_Definition  FMAC interrupt definition
 * @{
 */
#define FMAC_INT_ENABLE               (FMAC_IER_INTEN)
#define FMAC_INT_DISABLE              (0x0UL)
/**
 * @}
 */

/** @defgroup FMAC_Filter_shift FMAC filter shift times
  * @{
  */
#define FMAC_FILTER_SHIFT_0BIT        (0U)
#define FMAC_FILTER_SHIFT_1BIT        (1U)
#define FMAC_FILTER_SHIFT_2BIT        (2U)
#define FMAC_FILTER_SHIFT_3BIT        (3U)
#define FMAC_FILTER_SHIFT_4BIT        (4U)
#define FMAC_FILTER_SHIFT_5BIT        (5U)
#define FMAC_FILTER_SHIFT_6BIT        (6U)
#define FMAC_FILTER_SHIFT_7BIT        (7U)
#define FMAC_FILTER_SHIFT_8BIT        (8U)
#define FMAC_FILTER_SHIFT_9BIT        (9U)
#define FMAC_FILTER_SHIFT_10BIT       (10U)
#define FMAC_FILTER_SHIFT_11BIT       (11U)
#define FMAC_FILTER_SHIFT_12BIT       (12U)
#define FMAC_FILTER_SHIFT_13BIT       (13U)
#define FMAC_FILTER_SHIFT_14BIT       (14U)
#define FMAC_FILTER_SHIFT_15BIT       (15U)
#define FMAC_FILTER_SHIFT_16BIT       (16U)
#define FMAC_FILTER_SHIFT_17BIT       (17U)
#define FMAC_FILTER_SHIFT_18BIT       (18U)
#define FMAC_FILTER_SHIFT_19BIT       (19U)
#define FMAC_FILTER_SHIFT_20BIT       (20U)
#define FMAC_FILTER_SHIFT_21BIT       (21U)
/**
 * @}
 */

/** @defgroup FMAC_Filter_stage FMAC filter stage number
  * @{
  */
#define FMAC_FILTER_STAGE_0          (0U)
#define FMAC_FILTER_STAGE_1          (1U)
#define FMAC_FILTER_STAGE_2          (2U)
#define FMAC_FILTER_STAGE_3          (3U)
#define FMAC_FILTER_STAGE_4          (4U)
#define FMAC_FILTER_STAGE_5          (5U)
#define FMAC_FILTER_STAGE_6          (6U)
#define FMAC_FILTER_STAGE_7          (7U)
#define FMAC_FILTER_STAGE_8          (8U)
#define FMAC_FILTER_STAGE_9          (9U)
#define FMAC_FILTER_STAGE_10         (10U)
#define FMAC_FILTER_STAGE_11         (11U)
#define FMAC_FILTER_STAGE_12         (12U)
#define FMAC_FILTER_STAGE_13         (13U)
#define FMAC_FILTER_STAGE_14         (14U)
#define FMAC_FILTER_STAGE_15         (15U)
#define FMAC_FILTER_STAGE_16         (16U)
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
 * @addtogroup FMAC_Global_Functions
 * @{
 */
en_result_t FMAC_StructInit(stc_fmac_init_t* pstcInitStruct);
void FMAC_DeInit(M4_FMAC_TypeDef* FMACx);
en_result_t FMAC_Init(M4_FMAC_TypeDef* FMACx, const stc_fmac_init_t *pstcFmacInit);
void FMAC_Cmd(M4_FMAC_TypeDef* FMACx, en_functional_state_t enNewState);
void FMAC_SetResultShift(M4_FMAC_TypeDef* FMACx, uint32_t u32ShiftNum);
void FMAC_SetStageFactor(M4_FMAC_TypeDef* FMACx, uint32_t u32FilterStage, int16_t i16Factor);
void FMAC_IntCmd(M4_FMAC_TypeDef* FMACx, en_functional_state_t enNewState);
void FMAC_FIRInput(M4_FMAC_TypeDef* FMACx, int16_t i16Factor);
en_flag_status_t FMAC_GetStatus(const M4_FMAC_TypeDef* FMACx);
en_result_t FMAC_GetResult(const M4_FMAC_TypeDef* FMACx, stc_fmac_result_t *stcResult);
/**
 * @}
 */

#endif /* DDL_FMAC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_FMAC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
