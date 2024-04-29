/**
 *******************************************************************************
 * @file  hc32_ll_pla.h
 * @brief This file contains all the functions prototypes of the PLA driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-09-30       CDT             Modify API for Reference Manual Rev1.0
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
#ifndef __HC32_LL_PLA_H__
#define __HC32_LL_PLA_H__

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
 * @addtogroup LL_PLA
 * @{
 */

#if (LL_PLA_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup PLA_Global_Types PLA Global Types
 * @{
 */

/**
 * @brief PLA Init structure definition
 */
typedef struct {
    uint32_t u32Mux0Src;                /*!< Specifies the input signal source of MUX0.
                                             This parameter can be a value of @ref PLA_MUX_Source */
    uint32_t u32Mux1Src;                /*!< Specifies the input signal source of MUX1.
                                             This parameter can be a value of @ref PLA_MUX_Source */
    uint32_t u32CombLogic;              /*!< Specifies the combinatorial logic for input signals.
                                             This parameter can be a number between 0UL and 0xFFUL */
    uint32_t u32OutputSrc;              /*!< Specifies the output signal source of PLA.
                                             This parameter can be a value of @ref PLA_Output_Source */
} stc_pla_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup PLA_Global_Macros PLA Global Macros
 * @{
 */

/**
 * @defgroup PLA_Unit PLA Unit
 * @{
 */
#define PLA_UNIT0                       (0x0001UL)
#define PLA_UNIT1                       (0x0002UL)
#define PLA_UNIT2                       (0x0004UL)
#define PLA_UNIT3                       (0x0008UL)
#define PLA_UNIT4                       (0x0010UL)
#define PLA_UNIT5                       (0x0020UL)
#define PLA_UNIT6                       (0x0040UL)
#define PLA_UNIT7                       (0x0080UL)
#define PLA_UNIT8                       (0x0100UL)
#define PLA_UNIT9                       (0x0200UL)
#define PLA_UNIT10                      (0x0400UL)
#define PLA_UNIT11                      (0x0800UL)
#define PLA_UNIT12                      (0x1000UL)
#define PLA_UNIT13                      (0x2000UL)
#define PLA_UNIT14                      (0x4000UL)
#define PLA_UNIT15                      (0x8000UL)
#define PLA_UNIT_ALL                    (0xFFFFUL)
/**
 * @}
 */

/**
 * @defgroup PLA_MUX_Channel PLA MUX Channel
 * @{
 */
#define PLA_MUX_CH0                     (1UL)
#define PLA_MUX_CH1                     (0UL)
/**
 * @}
 */

/**
 * @defgroup PLA_MUX_Source PLA MUX Source
 * @{
 */
#define PLA_MUX_SRC_SIGNAL0             (0U)
#define PLA_MUX_SRC_SIGNAL1             (1U)
#define PLA_MUX_SRC_SIGNAL2             (2U)
#define PLA_MUX_SRC_SIGNAL3             (3U)
#define PLA_MUX_SRC_SIGNAL4             (4U)
#define PLA_MUX_SRC_SIGNAL5             (5U)
#define PLA_MUX_SRC_SIGNAL6             (6U)
#define PLA_MUX_SRC_SIGNAL7             (7U)
#define PLA_MUX_SRC_SIGNAL8             (8U)
#define PLA_MUX_SRC_SIGNAL9             (9U)
#define PLA_MUX_SRC_SIGNAL10            (10U)
#define PLA_MUX_SRC_SIGNAL11            (11U)
#define PLA_MUX_SRC_SIGNAL12            (12U)
#define PLA_MUX_SRC_SIGNAL13            (13U)
#define PLA_MUX_SRC_SIGNAL14            (14U)
#define PLA_MUX_SRC_SIGNAL15            (15U)
#define PLA_MUX_SRC_SIGNAL16            (16U)
#define PLA_MUX_SRC_SIGNAL17            (17U)
#define PLA_MUX_SRC_SIGNAL18            (18U)
#define PLA_MUX_SRC_SIGNAL19            (19U)
#define PLA_MUX_SRC_SIGNAL20            (20U)
#define PLA_MUX_SRC_SIGNAL21            (21U)
#define PLA_MUX_SRC_SIGNAL22            (22U)
#define PLA_MUX_SRC_SIGNAL23            (23U)
#define PLA_MUX_SRC_SIGNAL24            (24U)
#define PLA_MUX_SRC_SIGNAL25            (25U)
#define PLA_MUX_SRC_SIGNAL26            (26U)
#define PLA_MUX_SRC_SIGNAL27            (27U)
/**
 * @}
 */

/**
 * @defgroup PLA_Output_Source PLA Output Source
 * @{
 */
#define PLA_OUTPUT_SRC_NONE             (0UL)           /*!< The LUT result isn't the output of PLA */
#define PLA_OUTPUT_SRC_LUT              (PLA_CTL_OSEL)  /*!< The LUT result is the output of PLA    */
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
 * @addtogroup PLA_Global_Functions
 * @{
 */

/* Initialization and configuration functions */
int32_t PLA_DeInit(CM_PLA_TypeDef *PLAx);
int32_t PLA_Init(CM_PLA_TypeDef *PLAx, uint32_t u32Unit, const stc_pla_init_t *pstcPlaInit);
int32_t PLA_StructInit(stc_pla_init_t *pstcPlaInit);
en_functional_state_t PLA_GetOutputLevel(CM_PLA_TypeDef *PLAx, uint32_t u32Unit);
void PLA_SetMuxSrc(CM_PLA_TypeDef *PLAx, uint32_t u32Unit, uint32_t u32Ch, uint32_t u32Src);
void PLA_SetCombLogic(CM_PLA_TypeDef *PLAx, uint32_t u32Unit, uint32_t u32Value);
void PLA_OutputCmd(CM_PLA_TypeDef *PLAx, uint32_t u32Unit, en_functional_state_t enNewState);
void PLA_Cmd(CM_PLA_TypeDef *PLAx, uint32_t u32Unit, en_functional_state_t enNewState);

/**
 * @}
 */

#endif /* LL_PLA_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_PLA_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
