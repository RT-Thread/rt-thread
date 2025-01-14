/**
 *******************************************************************************
 * @file  hc32_ll_dac.h
 * @brief This file contains all the functions prototypes of the DAC driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-06-30       CDT             Modify function: DAC_AMPCmd
   2023-06-30       CDT             Refine definition of dac resolution
   2023-09-30       CDT             Modify API DAC_DeInit
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
#ifndef __HC32_LL_DAC_H__
#define __HC32_LL_DAC_H__

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
 * @addtogroup LL_DAC
 * @{
 */

#if (LL_DAC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup DAC_Global_Types DAC Global Types
 * @{
 */

/**
 * @brief Structure definition of DAC initialization.
 */
typedef struct {
    uint16_t u16Src;                 /*!< Data source to be converted
                                     This parameter can be a value of @ref DAC_DATA_SRC */
    en_functional_state_t enOutput;  /*!< Enable or disable analog output
                                     This parameter can be a value of @ref en_functional_state_t */
} stc_dac_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup DAC_Global_Macros DAC Global Macros
 * @{
 */

/**
 * @defgroup DAC_CH DAC channel
 * @{
 */
#define DAC_CH1                           (0U)
#define DAC_CH2                           (1U)
/**
 * @}
 */

/**
 * @defgroup DAC_DATA_SRC DAC data source
 * @{
 */
#define DAC_DATA_SRC_DATAREG               (0U)
#define DAC_DATA_SRC_DCU                   (DAC_DACR_EXTDSL1)
/**
 * @}
 */

/**
 * @defgroup DAC_DATAREG_ALIGN_PATTERN DAC data register alignment pattern
 * @{
 */
#define DAC_DATA_ALIGN_LEFT                (DAC_DACR_DPSEL)
#define DAC_DATA_ALIGN_RIGHT               (0U)
/**
 * @}
 */

/**
 * @defgroup DAC_RESOLUTION DAC resolution
 * @{
 */
#define DAC_RESOLUTION_12BIT                 (12U)
/**
 * @}
 */

/**
 * @defgroup DAC_ADP_SELECT DAC ADCx priority select
 * @{
 */
#define DAC_ADP_SEL_ADC1                   (DAC_DAADPCR_ADCSL1)
#define DAC_ADP_SEL_ADC2                   (DAC_DAADPCR_ADCSL2)
#define DAC_ADP_SEL_ADC3                   (DAC_DAADPCR_ADCSL3)
#define DAC_ADP_SEL_ALL   (DAC_DAADPCR_ADCSL1 | DAC_DAADPCR_ADCSL2 | DAC_DAADPCR_ADCSL3)
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
 * @addtogroup DAC_Global_Functions
 * @{
 */

int32_t DAC_StructInit(stc_dac_init_t *pstcDacInit);
int32_t DAC_Init(CM_DAC_TypeDef *DACx, uint16_t u16Ch, const stc_dac_init_t *pstcDacInit);
int32_t DAC_DeInit(CM_DAC_TypeDef *DACx);

void DAC_SetDataSrc(CM_DAC_TypeDef *DACx, uint16_t u16Ch, uint16_t u16Src);
void DAC_DataRegAlignConfig(CM_DAC_TypeDef *DACx, uint16_t u16Align);
void DAC_OutputCmd(CM_DAC_TypeDef *DACx, uint16_t u16Ch, en_functional_state_t enNewState);
void DAC_AMPCmd(CM_DAC_TypeDef *DACx, uint16_t u16Ch, en_functional_state_t enNewState);
void DAC_ADCPrioCmd(CM_DAC_TypeDef *DACx, en_functional_state_t enNewState);
void DAC_ADCPrioConfig(CM_DAC_TypeDef *DACx, uint16_t u16ADCxPrio, en_functional_state_t enNewState);

int32_t DAC_Start(CM_DAC_TypeDef *DACx, uint16_t u16Ch);
int32_t DAC_Stop(CM_DAC_TypeDef *DACx, uint16_t u16Ch);
void DAC_StartDualCh(CM_DAC_TypeDef *DACx);
void DAC_StopDualCh(CM_DAC_TypeDef *DACx);

void DAC_SetChData(CM_DAC_TypeDef *DACx, uint16_t u16Ch, uint16_t u16Data);
void DAC_SetDualChData(CM_DAC_TypeDef *DACx, uint16_t u16Data1, uint16_t u16Data2);
int32_t DAC_GetChConvertState(const CM_DAC_TypeDef *DACx, uint16_t u16Ch);

/**
 * @}
 */

#endif /* LL_DAC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_DAC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
