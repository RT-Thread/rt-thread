/**
 *******************************************************************************
 * @file  hc32_ll_vref.h
 * @brief This file contains all the functions prototypes of the VREF driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Add API VREF_DeInit()
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
#ifndef __HC32_LL_VREF_H__
#define __HC32_LL_VREF_H__

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
 * @addtogroup LL_VREF
 * @{
 */

#if (LL_VREF_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup VREF_Global_Macros VREF Global Macros
 * @{
 */

/**
 * @defgroup VREF_Intern_Vref_Mode VREF Operating Mode
 * @{
 */
#define VREF_EXT_REF_MD         (0x0UL)                 /*!< External reference voltage mode, use external VREFH as
                                                             reference voltage. Internal reference voltage is OFF. */
#define VREF_SHORT_MD           (VREF_CR_HIZ)           /*!< External VREFH is short to VSS.
                                                             Internal reference voltage is OFF. */
#define VREF_INTERN_REF_MD      (VREF_CR_IVREFEN)       /*!< Use internal reference voltage.
                                                             External VREFH is short to VREF circuit. */
/**
 * @}
 */

/**
 * @defgroup VREF_Avcc_Div_Config VREF AVCC Divider configure
 * @{
 */
#define VREF_AVCC_DIV_QUARTER       (0x0UL)                                     /*!< AVCC*1/4 */
#define VREF_AVCC_DIV_ONE_THIRD     (VREF_CR_AVCCMONS_0)                        /*!< AVCC*1/3 */
#define VREF_AVCC_DIV_TWO_FIFTHS    (VREF_CR_AVCCMONS_1)                        /*!< AVCC*2/5 */
#define VREF_AVCC_DIV_HALF          (VREF_CR_AVCCMONS_1 | VREF_CR_AVCCMONS_0)   /*!< AVCC*1/2 */
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
 * @addtogroup VREF_Global_Functions
 * @{
 */
void VREF_BandGapRefCmd(en_functional_state_t enNewState);
void VREF_CurrentSrcCmd(en_functional_state_t enNewState);

void VREF_AvccDivCmd(en_functional_state_t enNewState);
void VREF_AvccDivConfig(uint32_t u32Div);

void VREF_VrefintCmd(en_functional_state_t enNewState);

void VREF_IvrefCmd(en_functional_state_t enNewState);
void VREF_SetIvrefMode(uint32_t u32Mode);

int32_t VREF_DeInit(void);
/**
 * @}
 */

#endif /* LL_VREF_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_VREF_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
