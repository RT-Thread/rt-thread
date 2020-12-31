/**
 *******************************************************************************
 * @file  hc32f4a0_ctc.h
 * @brief This file contains all the functions prototypes of the Clock Trimming
 *        Controller(CTC) driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-09-01       Hongjh          First version
   2020-10-30       Hongjh          Refine CTC initialization structure
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
#ifndef __HC32F4A0_CTC_H__
#define __HC32F4A0_CTC_H__

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
 * @addtogroup DDL_CTC
 * @{
 */

#if (DDL_CTC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup CTC_Global_Types CTC Global Types
 * @{
 */

/**
 * @brief CTC initialization structure definition
 */
typedef struct
{
    uint32_t  u32RefClockFreq;          /*!< Reference clock frequency
                                             This parameter should refer user manual recommended values */
    uint32_t  u32RefClockSrc;           /*!< Reference clock source selection
                                             This parameter can be a value of @ref CTC_Reference_Clock_Source */
    uint32_t  u32RefClockDiv;           /*!< Reference clock division
                                             This parameter can be a value of @ref CTC_Reference_Clock_Division */
    float32_t f32ToleranceDeviation;    /*!< CTC Tolerance bias.
                                             This parameter can be a value between Min_Data=0.0 and Max_Data=1.0(100%) */
    uint32_t  u32TrimValue;             /*!< CTC TRMVAL value
                                             This parameter can be a value between Min_Data=0 and Max_Data=0x3F */
} stc_ctc_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CTC_Global_Macros CTC Global Macros
 * @{
 */

/**
 * @defgroup CTC_Reference_Clock_Source CTC Reference Clock Source
 * @{
 */
#define CTC_REF_CLK_CTCREF                  (0UL)               /*!< Clock source: CTCREF */
#define CTC_REF_CLK_XTAL32                  (CTC_CR1_REFCKS_1)  /*!< Clock source: XTAL32 */
#define CTC_REF_CLK_XTAL                    (CTC_CR1_REFCKS)    /*!< Clock source: XTAL */
/**
 * @}
 */

/**
 * @defgroup CTC_Tolerance_Deviation_Max CTC Tolerance Deviation Max
 * @{
 */
#define CTC_TOLERANCE_DEVIATION_MAX         (1.0F)
/**
 * @}
 */

/**
 * @defgroup CTC_Flag CTC Flag
 * @{
 */
#define CTC_FLAG_TRIM_OK                    (CTC_STR_TRIMOK)    /*!< Trimming OK flag */
#define CTC_FLAG_TRIM_OVF                   (CTC_STR_TRMOVF)    /*!< Trimming overflow flag */
#define CTC_FLAG_TRIM_UDF                   (CTC_STR_TRMUDF)    /*!< Trimming underflow flag */
#define CTC_FLAG_BUSY                       (CTC_STR_CTCBSY)    /*!< CTC busy flag */
#define CTC_FLAG_ALL                        (CTC_FLAG_TRIM_OK  |               \
                                             CTC_FLAG_TRIM_OVF |               \
                                             CTC_FLAG_TRIM_UDF |               \
                                             CTC_FLAG_BUSY)
/**
 * @}
 */

/**
 * @defgroup CTC_Reference_Clock_Division CTC Reference Clock Division
 * @{
 */
#define CTC_REF_CLK_DIV8                    (0UL)   /*!< REFCLK/8 */
#define CTC_REF_CLK_DIV32                   (1UL)   /*!< REFCLK/32 */
#define CTC_REF_CLK_DIV128                  (2UL)   /*!< REFCLK/128 */
#define CTC_REF_CLK_DIV256                  (3UL)   /*!< REFCLK/256 */
#define CTC_REF_CLK_DIV512                  (4UL)   /*!< REFCLK/512 */
#define CTC_REF_CLK_DIV1024                 (5UL)   /*!< REFCLK/1024 */
#define CTC_REF_CLK_DIV2048                 (6UL)   /*!< REFCLK/2048 */
#define CTC_REF_CLK_DIV4096                 (7UL)   /*!< REFCLK/4096 */
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
 * @addtogroup CTC_Global_Functions
 * @{
 */

/**
 * @brief  Start CTC trimming.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void CTC_Start(void)
{
    WRITE_REG32(bM4_CTC->CR1_b.CTCEN, 1UL);
}

/**
 * @brief  Stop CTC trimming.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void CTC_Stop(void)
{
    WRITE_REG32(bM4_CTC->CR1_b.CTCEN, 0UL);
}

en_result_t CTC_Init(const stc_ctc_init_t *pstcCtcInit);
en_result_t CTC_StructInit(stc_ctc_init_t *pstcCtcInit);
en_result_t CTC_DeInit(void);
void CTC_SetRefClockDiv(uint32_t u32Div);
void CTC_SetRefClockSrc(uint32_t u32ClockSrc);
void CTC_IntCmd(en_functional_state_t enNewState);
en_flag_status_t CTC_GetStatus(uint32_t u32Flag);
void CTC_SetTrimValue(uint32_t u32TrimValue);
uint32_t CTC_GetTrimValue(void);
void CTC_SetReloadValue(uint32_t u32ReloadValue);
uint16_t CTC_GetReloadValue(void);
void CTC_SetOffsetValue(uint32_t u32OffsetValue);
uint32_t CTC_GetOffsetValue(void);

/**
 * @}
 */

#endif /* DDL_CTC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_CTC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
