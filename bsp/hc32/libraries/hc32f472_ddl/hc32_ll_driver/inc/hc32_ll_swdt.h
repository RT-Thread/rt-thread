/**
 *******************************************************************************
 * @file  hc32_ll_swdt.h
 * @brief This file contains all the functions prototypes of the SWDT driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-12-15       CDT             Modify macro define: SWDT_LPM_CNT_CONTINUE -> SWDT_LPM_CNT_CONT
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
#ifndef __HC32_LL_SWDT_H__
#define __HC32_LL_SWDT_H__

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
 * @addtogroup LL_SWDT
 * @{
 */

#if (LL_SWDT_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup SWDT_Global_Types SWDT Global Types
 * @{
 */

/**
 * @brief SWDT Init structure definition
 */
typedef struct {
    uint32_t u32CountPeriod;            /*!< Specifies the counting period of SWDT.
                                             This parameter can be a value of @ref SWDT_Count_Period */
    uint32_t u32ClockDiv;               /*!< Specifies the clock division factor of SWDT.
                                             This parameter can be a value of @ref SWDT_Clock_Division */
    uint32_t u32RefreshRange;           /*!< Specifies the allow refresh range of SWDT.
                                             This parameter can be a value of @ref SWDT_Refresh_Range */
    uint32_t u32LPMCount;               /*!< Specifies the count state in Low Power Mode (Sleep/Stop Mode).
                                             This parameter can be a value of @ref SWDT_LPM_Count */
    uint32_t u32ExceptionType;          /*!< Specifies the type of exception response for SWDT.
                                             This parameter can be a value of @ref SWDT_Exception_Type */
} stc_swdt_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SWDT_Global_Macros SWDT Global Macros
 * @{
 */

/**
 * @defgroup SWDT_Count_Period SWDT Count Period
 * @{
 */
#define SWDT_CNT_PERIOD256                      (0UL)               /*!< 256 clock cycle   */
#define SWDT_CNT_PERIOD4096                     (SWDT_CR_PERI_0)    /*!< 4096 clock cycle  */
#define SWDT_CNT_PERIOD16384                    (SWDT_CR_PERI_1)    /*!< 16384 clock cycle */
#define SWDT_CNT_PERIOD65536                    (SWDT_CR_PERI)      /*!< 65536 clock cycle */
/**
 * @}
 */

/**
 * @defgroup SWDT_Clock_Division SWDT Clock Division
 * @{
 */
#define SWDT_CLK_DIV1                           (0UL)                       /*!< SWDTCLK/1    */
#define SWDT_CLK_DIV16                          (0x04UL << SWDT_CR_CKS_POS) /*!< SWDTCLK/16   */
#define SWDT_CLK_DIV32                          (0x05UL << SWDT_CR_CKS_POS) /*!< SWDTCLK/32   */
#define SWDT_CLK_DIV64                          (0x06UL << SWDT_CR_CKS_POS) /*!< SWDTCLK/64   */
#define SWDT_CLK_DIV128                         (0x07UL << SWDT_CR_CKS_POS) /*!< SWDTCLK/128  */
#define SWDT_CLK_DIV256                         (0x08UL << SWDT_CR_CKS_POS) /*!< SWDTCLK/256  */
#define SWDT_CLK_DIV2048                        (0x0BUL << SWDT_CR_CKS_POS) /*!< SWDTCLK/2048 */
/**
 * @}
 */

/**
 * @defgroup SWDT_Refresh_Range SWDT Refresh Range
 * @{
 */
#define SWDT_RANGE_0TO25PCT                     (0x01UL << SWDT_CR_WDPT_POS)    /*!< 0%~25%             */
#define SWDT_RANGE_25TO50PCT                    (0x02UL << SWDT_CR_WDPT_POS)    /*!< 25%~50%            */
#define SWDT_RANGE_0TO50PCT                     (0x03UL << SWDT_CR_WDPT_POS)    /*!< 0%~50%             */
#define SWDT_RANGE_50TO75PCT                    (0x04UL << SWDT_CR_WDPT_POS)    /*!< 50%~75%            */
#define SWDT_RANGE_0TO25PCT_50TO75PCT           (0x05UL << SWDT_CR_WDPT_POS)    /*!< 0%~25% & 50%~75%   */
#define SWDT_RANGE_25TO75PCT                    (0x06UL << SWDT_CR_WDPT_POS)    /*!< 25%~75%            */
#define SWDT_RANGE_0TO75PCT                     (0x07UL << SWDT_CR_WDPT_POS)    /*!< 0%~75%             */
#define SWDT_RANGE_75TO100PCT                   (0x08UL << SWDT_CR_WDPT_POS)    /*!< 75%~100%           */
#define SWDT_RANGE_0TO25PCT_75TO100PCT          (0x09UL << SWDT_CR_WDPT_POS)    /*!< 0%~25% & 75%~100%  */
#define SWDT_RANGE_25TO50PCT_75TO100PCT         (0x0AUL << SWDT_CR_WDPT_POS)    /*!< 25%~50% & 75%~100% */
#define SWDT_RANGE_0TO50PCT_75TO100PCT          (0x0BUL << SWDT_CR_WDPT_POS)    /*!< 0%~50% & 75%~100%  */
#define SWDT_RANGE_50TO100PCT                   (0x0CUL << SWDT_CR_WDPT_POS)    /*!< 50%~100%           */
#define SWDT_RANGE_0TO25PCT_50TO100PCT          (0x0DUL << SWDT_CR_WDPT_POS)    /*!< 0%~25% & 50%~100%  */
#define SWDT_RANGE_25TO100PCT                   (0x0EUL << SWDT_CR_WDPT_POS)    /*!< 25%~100%           */
#define SWDT_RANGE_0TO100PCT                    (0x0FUL << SWDT_CR_WDPT_POS)    /*!< 0%~100%            */
/**
 * @}
 */

/**
 * @defgroup SWDT_LPM_Count SWDT Low Power Mode Count
 * @brief    Counting control of SWDT in sleep/stop mode.
 * @{
 */
#define SWDT_LPM_CNT_CONT                       (0UL)               /*!< Continue counting in sleep/stop mode */
#define SWDT_LPM_CNT_STOP                       (SWDT_CR_SLPOFF)    /*!< Stop counting in sleep/stop mode     */
/**
 * @}
 */

/**
 * @defgroup SWDT_Exception_Type SWDT Exception Type
 * @brief    Specifies the exception response when a refresh error or count overflow occurs.
 * @{
 */
#define SWDT_EXP_TYPE_INT                       (0UL)           /*!< SWDT trigger interrupt */
#define SWDT_EXP_TYPE_RST                       (SWDT_CR_ITS)   /*!< SWDT trigger reset     */
/**
 * @}
 */

/**
 * @defgroup SWDT_Flag SWDT Flag
 * @{
 */
#define SWDT_FLAG_UDF                           (SWDT_SR_UDF)   /*!< Count underflow flag */
#define SWDT_FLAG_REFRESH                       (SWDT_SR_REF)   /*!< Refresh error flag   */
#define SWDT_FLAG_ALL                           (SWDT_SR_UDF | SWDT_SR_REF)
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
 * @addtogroup SWDT_Global_Functions
 * @{
 */

/**
 * @brief  Get SWDT count value.
 * @param  None
 * @retval uint16_t                     Count value
 */
__STATIC_INLINE uint16_t SWDT_GetCountValue(void)
{
    return (uint16_t)(READ_REG32(CM_SWDT->SR) & SWDT_SR_CNT);
}

/* Initialization and configuration functions */
int32_t SWDT_Init(const stc_swdt_init_t *pstcSwdtInit);
void SWDT_FeedDog(void);
uint16_t SWDT_GetCountValue(void);

/* Flags management functions */
en_flag_status_t SWDT_GetStatus(uint32_t u32Flag);
int32_t SWDT_ClearStatus(uint32_t u32Flag);

/**
 * @}
 */

#endif /* LL_SWDT_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_SWDT_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
