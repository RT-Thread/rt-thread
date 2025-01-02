/**
 *******************************************************************************
 * @file  hc32_ll_wdt.h
 * @brief This file contains all the functions prototypes of the WDT driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
   2023-12-15       CDT             Modify macro define: WDT_LPM_CNT_CONTINUE -> WDT_LPM_CNT_CONT
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
#ifndef __HC32_LL_WDT_H__
#define __HC32_LL_WDT_H__

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
 * @addtogroup LL_WDT
 * @{
 */

#if (LL_WDT_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup WDT_Global_Types WDT Global Types
 * @{
 */

/**
 * @brief WDT Init structure definition
 */
typedef struct {
    uint32_t u32CountPeriod;            /*!< Specifies the counting period of WDT.
                                             This parameter can be a value of @ref WDT_Count_Period */
    uint32_t u32ClockDiv;               /*!< Specifies the clock division factor of WDT.
                                             This parameter can be a value of @ref WDT_Clock_Division */
    uint32_t u32RefreshRange;           /*!< Specifies the allow refresh range of WDT.
                                             This parameter can be a value of @ref WDT_Refresh_Range */
    uint32_t u32LPMCount;               /*!< Specifies the count state in Low Power Mode (Sleep Mode).
                                             This parameter can be a value of @ref WDT_LPM_Count */
    uint32_t u32ExceptionType;          /*!< Specifies the type of exception response for WDT.
                                             This parameter can be a value of @ref WDT_Exception_Type */
} stc_wdt_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup WDT_Global_Macros WDT Global Macros
 * @{
 */

/**
 * @defgroup WDT_Count_Period WDT Count Period
 * @{
 */
#define WDT_CNT_PERIOD256                       (0UL)               /*!< 256 clock cycle   */
#define WDT_CNT_PERIOD4096                      (WDT_CR_PERI_0)     /*!< 4096 clock cycle  */
#define WDT_CNT_PERIOD16384                     (WDT_CR_PERI_1)     /*!< 16384 clock cycle */
#define WDT_CNT_PERIOD65536                     (WDT_CR_PERI)       /*!< 65536 clock cycle */
/**
 * @}
 */

/**
 * @defgroup WDT_Clock_Division WDT Clock Division
 * @{
 */
#define WDT_CLK_DIV4                            (0x02UL << WDT_CR_CKS_POS)  /*!< PLCKx/4    */
#define WDT_CLK_DIV64                           (0x06UL << WDT_CR_CKS_POS)  /*!< PLCKx/64   */
#define WDT_CLK_DIV128                          (0x07UL << WDT_CR_CKS_POS)  /*!< PLCKx/128  */
#define WDT_CLK_DIV256                          (0x08UL << WDT_CR_CKS_POS)  /*!< PLCKx/256  */
#define WDT_CLK_DIV512                          (0x09UL << WDT_CR_CKS_POS)  /*!< PLCKx/512  */
#define WDT_CLK_DIV1024                         (0x0AUL << WDT_CR_CKS_POS)  /*!< PLCKx/1024 */
#define WDT_CLK_DIV2048                         (0x0BUL << WDT_CR_CKS_POS)  /*!< PLCKx/2048 */
#define WDT_CLK_DIV8192                         (0x0DUL << WDT_CR_CKS_POS)  /*!< PLCKx/8192 */
/**
 * @}
 */

/**
 * @defgroup WDT_Refresh_Range WDT Refresh Range
 * @{
 */
#define WDT_RANGE_0TO25PCT                      (0x01UL << WDT_CR_WDPT_POS)     /*!< 0%~25%             */
#define WDT_RANGE_25TO50PCT                     (0x02UL << WDT_CR_WDPT_POS)     /*!< 25%~50%            */
#define WDT_RANGE_0TO50PCT                      (0x03UL << WDT_CR_WDPT_POS)     /*!< 0%~50%             */
#define WDT_RANGE_50TO75PCT                     (0x04UL << WDT_CR_WDPT_POS)     /*!< 50%~75%            */
#define WDT_RANGE_0TO25PCT_50TO75PCT            (0x05UL << WDT_CR_WDPT_POS)     /*!< 0%~25% & 50%~75%   */
#define WDT_RANGE_25TO75PCT                     (0x06UL << WDT_CR_WDPT_POS)     /*!< 25%~75%            */
#define WDT_RANGE_0TO75PCT                      (0x07UL << WDT_CR_WDPT_POS)     /*!< 0%~75%             */
#define WDT_RANGE_75TO100PCT                    (0x08UL << WDT_CR_WDPT_POS)     /*!< 75%~100%           */
#define WDT_RANGE_0TO25PCT_75TO100PCT           (0x09UL << WDT_CR_WDPT_POS)     /*!< 0%~25% & 75%~100%  */
#define WDT_RANGE_25TO50PCT_75TO100PCT          (0x0AUL << WDT_CR_WDPT_POS)     /*!< 25%~50% & 75%~100% */
#define WDT_RANGE_0TO50PCT_75TO100PCT           (0x0BUL << WDT_CR_WDPT_POS)     /*!< 0%~50% & 75%~100%  */
#define WDT_RANGE_50TO100PCT                    (0x0CUL << WDT_CR_WDPT_POS)     /*!< 50%~100%           */
#define WDT_RANGE_0TO25PCT_50TO100PCT           (0x0DUL << WDT_CR_WDPT_POS)     /*!< 0%~25% & 50%~100%  */
#define WDT_RANGE_25TO100PCT                    (0x0EUL << WDT_CR_WDPT_POS)     /*!< 25%~100%           */
#define WDT_RANGE_0TO100PCT                     (0x0FUL << WDT_CR_WDPT_POS)     /*!< 0%~100%            */
/**
 * @}
 */

/**
 * @defgroup WDT_LPM_Count WDT Low Power Mode Count
 * @brief    Counting control of WDT in sleep mode.
 * @{
 */
#define WDT_LPM_CNT_CONT                        (0UL)               /*!< Continue counting in sleep mode */
#define WDT_LPM_CNT_STOP                        (WDT_CR_SLPOFF)     /*!< Stop counting in sleep mode     */
/**
 * @}
 */

/**
 * @defgroup WDT_Exception_Type WDT Exception Type
 * @brief    Specifies the exception response when a refresh error or count overflow occurs.
 * @{
 */
#define WDT_EXP_TYPE_INT                        (0UL)           /*!< WDT trigger interrupt */
#define WDT_EXP_TYPE_RST                        (WDT_CR_ITS)    /*!< WDT trigger reset     */
/**
 * @}
 */

/**
 * @defgroup WDT_Flag WDT Flag
 * @{
 */
#define WDT_FLAG_UDF                            (WDT_SR_UDF)    /*!< Count underflow flag */
#define WDT_FLAG_REFRESH                        (WDT_SR_REF)    /*!< Refresh error flag   */
#define WDT_FLAG_ALL                            (WDT_SR_UDF | WDT_SR_REF)
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
 * @addtogroup WDT_Global_Functions
 * @{
 */

/**
 * @brief  Get WDT count value.
 * @param  None
 * @retval uint16_t                     Count value
 */
__STATIC_INLINE uint16_t WDT_GetCountValue(void)
{
    return (uint16_t)(READ_REG32(CM_WDT->SR) & WDT_SR_CNT);
}

/* Initialization and configuration functions */
int32_t WDT_Init(const stc_wdt_init_t *pstcWdtInit);
void WDT_FeedDog(void);
uint16_t WDT_GetCountValue(void);

/* Flags management functions */
en_flag_status_t WDT_GetStatus(uint32_t u32Flag);
int32_t WDT_ClearStatus(uint32_t u32Flag);

/**
 * @}
 */

#endif /* LL_WDT_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_WDT_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
