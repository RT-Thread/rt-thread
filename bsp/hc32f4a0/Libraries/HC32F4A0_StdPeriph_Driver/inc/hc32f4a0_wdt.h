/**
 *******************************************************************************
 * @file  hc32f4a0_wdt.h
 * @brief This file contains all the functions prototypes of the WDT driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Yangjp          First version
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
#ifndef __HC32F4A0_WDT_H__
#define __HC32F4A0_WDT_H__

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
 * @addtogroup DDL_WDT
 * @{
 */

#if (DDL_WDT_ENABLE == DDL_ON)

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
typedef struct
{
    uint32_t u32CountCycle;         /*!< Specifies the WDT Count Cycle.
                                         This parameter can be a value of @ref WDT_Counter_Cycle */

    uint32_t u32ClockDivision;      /*!< Specifies the WDT Clock Division.
                                         This parameter can be a value of @ref WDT_Clock_Division */

    uint32_t u32RefreshRange;       /*!< Specifies the WDT Allow Refresh Range.
                                         This parameter can be a value of @ref WDT_Refresh_Percent_Range */

    uint32_t u32LPModeCountEn;      /*!< Specifies the WDT Count Enable/Disable In Low Power Mode(Sleep Mode).
                                         This parameter can be a value of @ref WDT_LPW_Mode_Count */

    uint32_t u32TrigType;           /*!< Specifies the WDT Refresh Error or Count Underflow trigger event Type.
                                         This parameter can be a value of @ref WDT_Trigger_Event_Type */
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
 * @defgroup WDT_Counter_Cycle WDT Counter Cycle
 * @{
 */
#define WDT_COUNTER_CYCLE_256                   (0UL)             /*!< 256 clock cycle   */
#define WDT_COUNTER_CYCLE_4096                  (WDT_CR_PERI_0)   /*!< 4096 clock cycle  */
#define WDT_COUNTER_CYCLE_16384                 (WDT_CR_PERI_1)   /*!< 16384 clock cycle */
#define WDT_COUNTER_CYCLE_65536                 (WDT_CR_PERI)     /*!< 65536 clock cycle */
/**
 * @}
 */

/**
 * @defgroup WDT_Clock_Division WDT Clock Division
 * @{
 */
#define WDT_CLOCK_DIV4                          (WDT_CR_CKS_1)                                /*!< PLCK3/4    */
#define WDT_CLOCK_DIV64                         (WDT_CR_CKS_2 | WDT_CR_CKS_1)                 /*!< PLCK3/64   */
#define WDT_CLOCK_DIV128                        (WDT_CR_CKS_2 | WDT_CR_CKS_1 | WDT_CR_CKS_0)  /*!< PLCK3/128  */
#define WDT_CLOCK_DIV256                        (WDT_CR_CKS_3)                                /*!< PLCK3/256  */
#define WDT_CLOCK_DIV512                        (WDT_CR_CKS_3 | WDT_CR_CKS_0)                 /*!< PLCK3/512  */
#define WDT_CLOCK_DIV1024                       (WDT_CR_CKS_3 | WDT_CR_CKS_1)                 /*!< PLCK3/1024 */
#define WDT_CLOCK_DIV2048                       (WDT_CR_CKS_3 | WDT_CR_CKS_1 | WDT_CR_CKS_0)  /*!< PLCK3/2048 */
#define WDT_CLOCK_DIV8192                       (WDT_CR_CKS_3 | WDT_CR_CKS_2 | WDT_CR_CKS_0)  /*!< PLCK3/8192 */
/**
 * @}
 */

/**
 * @defgroup WDT_Refresh_Percent_Range WDT Refresh Percent Range
 * @{
 */
#define WDT_RANGE_0TO100PCT                     (0UL)                                             /*!< 0%~100%            */
#define WDT_RANGE_0TO25PCT                      (WDT_CR_WDPT_0)                                   /*!< 0%~25%             */
#define WDT_RANGE_25TO50PCT                     (WDT_CR_WDPT_1)                                   /*!< 25%~50%            */
#define WDT_RANGE_0TO50PCT                      (WDT_CR_WDPT_1 | WDT_CR_WDPT_0)                   /*!< 0%~50%             */
#define WDT_RANGE_50TO75PCT                     (WDT_CR_WDPT_2)                                   /*!< 50%~75%            */
#define WDT_RANGE_0TO25PCT_50TO75PCT            (WDT_CR_WDPT_2 | WDT_CR_WDPT_0)                   /*!< 0%~25% & 50%~75%   */
#define WDT_RANGE_25TO75PCT                     (WDT_CR_WDPT_2 | WDT_CR_WDPT_1)                   /*!< 25%~75%            */
#define WDT_RANGE_0TO75PCT                      (WDT_CR_WDPT_2 | WDT_CR_WDPT_1 | WDT_CR_WDPT_0)   /*!< 0%~75%             */
#define WDT_RANGE_75TO100PCT                    (WDT_CR_WDPT_3)                                   /*!< 75%~100%           */
#define WDT_RANGE_0TO25PCT_75TO100PCT           (WDT_CR_WDPT_3 | WDT_CR_WDPT_0)                   /*!< 0%~25% & 75%~100%  */
#define WDT_RANGE_25TO50PCT_75TO100PCT          (WDT_CR_WDPT_3 | WDT_CR_WDPT_1)                   /*!< 25%~50% & 75%~100% */
#define WDT_RANGE_0TO50PCT_75TO100PCT           (WDT_CR_WDPT_3 | WDT_CR_WDPT_1 | WDT_CR_WDPT_0)   /*!< 0%~50% & 75%~100%  */
#define WDT_RANGE_50TO100PCT                    (WDT_CR_WDPT_3 | WDT_CR_WDPT_2)                   /*!< 50%~100%           */
#define WDT_RANGE_0TO25PCT_50TO100PCT           (WDT_CR_WDPT_3 | WDT_CR_WDPT_2 | WDT_CR_WDPT_0)   /*!< 0%~25% & 50%~100%  */
#define WDT_RANGE_25TO100PCT                    (WDT_CR_WDPT_3 | WDT_CR_WDPT_2 | WDT_CR_WDPT_1)   /*!< 25%~100%           */
/**
 * @}
 */

/**
 * @defgroup WDT_LPW_Mode_Count WDT Low Power Mode Count
 * @brief WDT count control in the sleep mode
 * @{
 */
#define WDT_LPM_COUNT_CONTINUE                  (0UL)             /*!< WDT count continue in the sleep mode */
#define WDT_LPM_COUNT_STOP                      (WDT_CR_SLPOFF)   /*!< WDT count stop in the sleep mode     */
/**
 * @}
 */

/**
* @defgroup WDT_Trigger_Event_Type WDT Trigger Event Type
* @{
*/
#define WDT_TRIG_EVENT_INT                      (0UL)           /*!< WDT trigger interrupt */
#define WDT_TRIG_EVENT_RESET                    (WDT_CR_ITS)    /*!< WDT trigger reset     */
/**
 * @}
 */

/**
 * @defgroup WDT_Flag WDT Flag
 * @{
 */
#define WDT_FLAG_UDF                            (WDT_SR_UDF)    /*!< Count underflow flag */
#define WDT_FLAG_REF                            (WDT_SR_REF)    /*!< Refresh error flag   */
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
 * @retval Count value
 */
__STATIC_INLINE uint16_t WDT_GetCountValue(void)
{
    return (uint16_t)(READ_REG32(M4_WDT->SR) & WDT_SR_CNT);
}

/* Initialization and configuration functions */
en_result_t WDT_Init(const stc_wdt_init_t *pstcWdtInit);
void WDT_Feed(void);
uint16_t WDT_GetCountValue(void);

/* Flags management functions */
en_flag_status_t WDT_GetStatus(uint32_t u32Flag);
en_result_t WDT_ClearStatus(uint32_t u32Flag);

/**
 * @}
 */

#endif /* DDL_WDT_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_WDT_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
