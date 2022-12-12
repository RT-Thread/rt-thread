/**
 *******************************************************************************
 * @file  hc32_ll_fmac.h
 * @brief This file contains all the functions prototypes of the FMAC driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author        Notes
   2022-03-31       CDT           First version
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
#ifndef __HC32_LL_FMAC_H__
#define __HC32_LL_FMAC_H__

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
 * @addtogroup LL_FMAC
 * @{
 */

#if (LL_FMAC_ENABLE == DDL_ON)

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
typedef struct {
    uint32_t u32Stage;                  /*!< FMAC filter stage number config.
                                             This parameter can be a value of @ref FMAC_Filter_Stage.*/
    uint32_t u32Shift;                  /*!< FMAC filter result right shift bits.
                                             This parameter can be a value of @ref FMAC_Filter_Shift.*/
    int16_t *pi16Factor;                /*!< FMAC filter factor config. FIR factor array */
    uint32_t u32IntCmd;                 /*!< Enable or disable FMAC interrupt.
                                             This parameter can be a value of @ref FMAC_Interrupt_Selection.*/
} stc_fmac_init_t;

/**
 * @brief FMAC result definition
 */
typedef struct {
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
 * @defgroup FMAC_Interrupt_Selection FMAC Interrupt Selection
 * @{
 */
#define FMAC_INT_ENABLE                 (FMAC_IER_INTEN)
#define FMAC_INT_DISABLE                (0x0UL)
/**
 * @}
 */

/**
 * @defgroup FMAC_Filter_Shift FMAC Filter Shift
 * @{
 */
#define FMAC_FIR_SHIFT_0BIT             (0U)
#define FMAC_FIR_SHIFT_1BIT             (1U)
#define FMAC_FIR_SHIFT_2BIT             (2U)
#define FMAC_FIR_SHIFT_3BIT             (3U)
#define FMAC_FIR_SHIFT_4BIT             (4U)
#define FMAC_FIR_SHIFT_5BIT             (5U)
#define FMAC_FIR_SHIFT_6BIT             (6U)
#define FMAC_FIR_SHIFT_7BIT             (7U)
#define FMAC_FIR_SHIFT_8BIT             (8U)
#define FMAC_FIR_SHIFT_9BIT             (9U)
#define FMAC_FIR_SHIFT_10BIT            (10U)
#define FMAC_FIR_SHIFT_11BIT            (11U)
#define FMAC_FIR_SHIFT_12BIT            (12U)
#define FMAC_FIR_SHIFT_13BIT            (13U)
#define FMAC_FIR_SHIFT_14BIT            (14U)
#define FMAC_FIR_SHIFT_15BIT            (15U)
#define FMAC_FIR_SHIFT_16BIT            (16U)
#define FMAC_FIR_SHIFT_17BIT            (17U)
#define FMAC_FIR_SHIFT_18BIT            (18U)
#define FMAC_FIR_SHIFT_19BIT            (19U)
#define FMAC_FIR_SHIFT_20BIT            (20U)
#define FMAC_FIR_SHIFT_21BIT            (21U)
/**
 * @}
 */

/**
 * @defgroup FMAC_Filter_Stage FMAC Filter Stage
 * @{
 */
#define FMAC_FIR_STAGE_0                (0U)
#define FMAC_FIR_STAGE_1                (1U)
#define FMAC_FIR_STAGE_2                (2U)
#define FMAC_FIR_STAGE_3                (3U)
#define FMAC_FIR_STAGE_4                (4U)
#define FMAC_FIR_STAGE_5                (5U)
#define FMAC_FIR_STAGE_6                (6U)
#define FMAC_FIR_STAGE_7                (7U)
#define FMAC_FIR_STAGE_8                (8U)
#define FMAC_FIR_STAGE_9                (9U)
#define FMAC_FIR_STAGE_10               (10U)
#define FMAC_FIR_STAGE_11               (11U)
#define FMAC_FIR_STAGE_12               (12U)
#define FMAC_FIR_STAGE_13               (13U)
#define FMAC_FIR_STAGE_14               (14U)
#define FMAC_FIR_STAGE_15               (15U)
#define FMAC_FIR_STAGE_16               (16U)
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
int32_t FMAC_StructInit(stc_fmac_init_t *pstcFmacInit);
void FMAC_DeInit(CM_FMAC_TypeDef *FMACx);
int32_t FMAC_Init(CM_FMAC_TypeDef *FMACx, const stc_fmac_init_t *pstcFmacInit);
void FMAC_Cmd(CM_FMAC_TypeDef *FMACx, en_functional_state_t enNewState);
void FMAC_SetResultShift(CM_FMAC_TypeDef *FMACx, uint32_t u32ShiftNum);
void FMAC_SetStageFactor(CM_FMAC_TypeDef *FMACx, uint32_t u32FilterStage, int16_t *pi16Factor);
void FMAC_IntCmd(CM_FMAC_TypeDef *FMACx, en_functional_state_t enNewState);
void FMAC_FIRInput(CM_FMAC_TypeDef *FMACx, int16_t i16Factor);
en_flag_status_t FMAC_GetStatus(const CM_FMAC_TypeDef *FMACx);
int32_t FMAC_GetResult(const CM_FMAC_TypeDef *FMACx, stc_fmac_result_t *pstcResult);
/**
 * @}
 */

#endif /* LL_FMAC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_FMAC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
