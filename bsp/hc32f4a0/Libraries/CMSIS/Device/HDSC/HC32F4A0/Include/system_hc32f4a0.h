/**
 *******************************************************************************
 * @file  system_hc32f4a0.h
 * @brief This file contains all the functions prototypes of the HC32 System.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Zhangxl         First version
   2020-07-03       Zhangxl         Modify for 16MHz & 20MHz HRC
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
#ifndef __SYSTEM_HC32F4A0_H__
#define __SYSTEM_HC32F4A0_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <stdint.h>

/**
 * @addtogroup CMSIS
 * @{
 */

/**
 * @addtogroup HC32F4A0_System
 * @{
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('define')
 ******************************************************************************/
/**
 * @addtogroup HC32F4A0_System_Global_Macros
 * @{
 */

/**
 * @brief Clock setup macro definition
 */
#define CLOCK_SETTING_NONE              0U  /*!< User provides own clock setting in application */
#define CLOCK_SETTING_CMSIS             1U

#define HRC_FREQ_MON()                  (*((volatile unsigned int*)(0x40010684UL)))

/**
 * @addtogroup HC32F4A0_System_Clock_Source
 * @{
 */
#if !defined (HRC_16MHz_VALUE)
    #define HRC_16MHz_VALUE             ((uint32_t)16000000UL)  /*!< Internal high speed RC freq.(16MHz) */
#endif

#if !defined (HRC_20MHz_VALUE)
    #define HRC_20MHz_VALUE             ((uint32_t)20000000UL)  /*!< Internal high speed RC freq.(20MHz) */
#endif

#if !defined (MRC_VALUE)
#define MRC_VALUE                       ((uint32_t)8000000UL)   /*!< Internal middle speed RC freq.(8MHz) */
#endif

#if !defined (LRC_VALUE)
    #define LRC_VALUE                   ((uint32_t)32768UL)     /*!< Internal low speed RC freq.(32.768KHz) */
#endif

#if !defined (RTCLRC_VALUE)
    #define RTCLRC_VALUE                ((uint32_t)32768UL)     /*!< Internal RTC low speed RC freq.(32.768KHz) */
#endif

#if !defined (SWDTLRC_VALUE)
    #define SWDTLRC_VALUE               ((uint32_t)10000UL)     /*!< External low speed OSC freq.(10KHz) */
#endif

#if !defined (XTAL_VALUE)
    #define XTAL_VALUE                  ((uint32_t)8000000UL)   /*!< External high speed OSC freq.(8MHz) */
#endif

#if !defined (XTAL32_VALUE)
    #define XTAL32_VALUE                ((uint32_t)32768UL)     /*!< External low speed OSC freq.(32.768KHz) */
#endif

#if !defined (HCLK_VALUE)
#define HCLK_VALUE      (SystemCoreClock >> ((M4_CMU->SCFGR & CMU_SCFGR_HCLKS) >> CMU_SCFGR_HCLKS_POS))
#endif


/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
/**
 * @addtogroup HC32F4A0_System_Exported_Variable
 * @{
 */
extern uint32_t SystemCoreClock;        /*!< System clock frequency (Core clock) */
extern uint32_t HRC_VALUE;              /*!< HRC frequency */

/**
 * @}
 */

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup HC32F4A0_System_Global_Functions
 * @{
 */
extern void SystemInit(void);             /*!< Initialize the system */
extern void SystemCoreClockUpdate(void);  /*!< Update SystemCoreClock variable */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_HC32F4A0_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
