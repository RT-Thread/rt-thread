/**
 *******************************************************************************
 * @file    hc32_ll_icg.h
 * @brief   This file contains all the Macro Definitions of the ICG driver
 *          library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
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
#ifndef __HC32_LL_ICG_H__
#define __HC32_LL_ICG_H__

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
 * @addtogroup LL_ICG
 * @{
 */

#if (LL_ICG_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ICG_Global_Macros ICG Global Macros
 * @{
 */

/**
 * @defgroup ICG_SWDT_Reset_State ICG SWDT Reset State
 * @{
 */
#define ICG_SWDT_RST_START                      (0UL)                   /*!< SWDT auto start after reset */
#define ICG_SWDT_RST_STOP                       (ICG_ICG0_SWDTAUTS)     /*!< SWDT stop after reset       */
/**
 * @}
 */

/**
 * @defgroup ICG_SWDT_Exception_Type ICG SWDT Exception Type
 * @{
 */
#define ICG_SWDT_EXP_TYPE_INT                   (0UL)               /*!< SWDT trigger interrupt */
#define ICG_SWDT_EXP_TYPE_RST                   (ICG_ICG0_SWDTITS)  /*!< SWDT trigger reset     */
/**
 * @}
 */

/**
 * @defgroup ICG_SWDT_Count_Period ICG SWDT Count Period
 * @{
 */
#define ICG_SWDT_CNT_PERIOD256                  (0UL)                   /*!< 256 clock cycle   */
#define ICG_SWDT_CNT_PERIOD4096                 (ICG_ICG0_SWDTPERI_0)   /*!< 4096 clock cycle  */
#define ICG_SWDT_CNT_PERIOD16384                (ICG_ICG0_SWDTPERI_1)   /*!< 16384 clock cycle */
#define ICG_SWDT_CNT_PERIOD65536                (ICG_ICG0_SWDTPERI)     /*!< 65536 clock cycle */
/**
 * @}
 */

/**
 * @defgroup ICG_SWDT_Clock_Division ICG SWDT Clock Division
 * @{
 */
#define ICG_SWDT_CLK_DIV1                       (0UL)                               /*!< CLK      */
#define ICG_SWDT_CLK_DIV16                      (0x04UL << ICG_ICG0_SWDTCKS_POS)    /*!< CLK/16   */
#define ICG_SWDT_CLK_DIV32                      (0x05UL << ICG_ICG0_SWDTCKS_POS)    /*!< CLK/32   */
#define ICG_SWDT_CLK_DIV64                      (0x06UL << ICG_ICG0_SWDTCKS_POS)    /*!< CLK/64   */
#define ICG_SWDT_CLK_DIV128                     (0x07UL << ICG_ICG0_SWDTCKS_POS)    /*!< CLK/128  */
#define ICG_SWDT_CLK_DIV256                     (0x08UL << ICG_ICG0_SWDTCKS_POS)    /*!< CLK/256  */
#define ICG_SWDT_CLK_DIV2048                    (0x0BUL << ICG_ICG0_SWDTCKS_POS)    /*!< CLK/2048 */
/**
 * @}
 */

/**
 * @defgroup ICG_SWDT_Refresh_Range ICG SWDT Refresh Range
 * @{
 */
#define ICG_SWDT_RANGE_0TO25PCT                 (0x01UL << ICG_ICG0_SWDTWDPT_POS)   /*!< 0%~25%             */
#define ICG_SWDT_RANGE_25TO50PCT                (0x02UL << ICG_ICG0_SWDTWDPT_POS)   /*!< 25%~50%            */
#define ICG_SWDT_RANGE_0TO50PCT                 (0x03UL << ICG_ICG0_SWDTWDPT_POS)   /*!< 0%~50%             */
#define ICG_SWDT_RANGE_50TO75PCT                (0x04UL << ICG_ICG0_SWDTWDPT_POS)   /*!< 50%~75%            */
#define ICG_SWDT_RANGE_0TO25PCT_50TO75PCT       (0x05UL << ICG_ICG0_SWDTWDPT_POS)   /*!< 0%~25% & 50%~75%   */
#define ICG_SWDT_RANGE_25TO75PCT                (0x06UL << ICG_ICG0_SWDTWDPT_POS)   /*!< 25%~75%            */
#define ICG_SWDT_RANGE_0TO75PCT                 (0x07UL << ICG_ICG0_SWDTWDPT_POS)   /*!< 0%~75%             */
#define ICG_SWDT_RANGE_75TO100PCT               (0x08UL << ICG_ICG0_SWDTWDPT_POS)   /*!< 75%~100%           */
#define ICG_SWDT_RANGE_0TO25PCT_75TO100PCT      (0x09UL << ICG_ICG0_SWDTWDPT_POS)   /*!< 0%~25% & 75%~100%  */
#define ICG_SWDT_RANGE_25TO50PCT_75TO100PCT     (0x0AUL << ICG_ICG0_SWDTWDPT_POS)   /*!< 25%~50% & 75%~100% */
#define ICG_SWDT_RANGE_0TO50PCT_75TO100PCT      (0x0BUL << ICG_ICG0_SWDTWDPT_POS)   /*!< 0%~50% & 75%~100%  */
#define ICG_SWDT_RANGE_50TO100PCT               (0x0CUL << ICG_ICG0_SWDTWDPT_POS)   /*!< 50%~100%           */
#define ICG_SWDT_RANGE_0TO25PCT_50TO100PCT      (0x0DUL << ICG_ICG0_SWDTWDPT_POS)   /*!< 0%~25% & 50%~100%  */
#define ICG_SWDT_RANGE_25TO100PCT               (0x0EUL << ICG_ICG0_SWDTWDPT_POS)   /*!< 25%~100%           */
#define ICG_SWDT_RANGE_0TO100PCT                (0x0FUL << ICG_ICG0_SWDTWDPT_POS)   /*!< 0%~100%            */
/**
 * @}
 */

/**
 * @defgroup ICG_SWDT_LPM_Count ICG SWDT Low Power Mode Count
 * @brief    Counting control of SWDT in sleep/stop mode
 * @{
 */
#define ICG_SWDT_LPM_CNT_CONTINUE               (0UL)                   /*!< Continue counting in sleep/stop mode */
#define ICG_SWDT_LPM_CNT_STOP                   (ICG_ICG0_SWDTSLPOFF)   /*!< Stop counting in sleep/stop mode     */
/**
 * @}
 */

/**
 * @defgroup ICG_WDT_Reset_State ICG WDT Reset State
 * @{
 */
#define ICG_WDT_RST_START                       (0UL)               /*!< WDT auto start after reset */
#define ICG_WDT_RST_STOP                        (ICG_ICG0_WDTAUTS)  /*!< WDT stop after reset       */
/**
 * @}
 */

/**
 * @defgroup ICG_WDT_Exception_Type ICG WDT Exception Type
 * @{
 */
#define ICG_WDT_EXP_TYPE_INT                    (0UL)               /*!< WDT trigger interrupt */
#define ICG_WDT_EXP_TYPE_RST                    (ICG_ICG0_WDTITS)   /*!< WDT trigger reset     */
/**
 * @}
 */

/**
 * @defgroup ICG_WDT_Count_Period ICG WDT Count Period
 * @{
 */
#define REDEF_ICG_WDTPERI_POS                   ICG_ICG0_WDTPERI_POS

#define ICG_WDT_CNT_PERIOD256                   (0UL)                               /*!< 256 clock cycle   */
#define ICG_WDT_CNT_PERIOD4096                  (0x01UL << REDEF_ICG_WDTPERI_POS)   /*!< 4096 clock cycle  */
#define ICG_WDT_CNT_PERIOD16384                 (0x02UL << REDEF_ICG_WDTPERI_POS)   /*!< 16384 clock cycle */
#define ICG_WDT_CNT_PERIOD65536                 (0x03UL << REDEF_ICG_WDTPERI_POS)   /*!< 65536 clock cycle */
/**
 * @}
 */

/**
 * @defgroup ICG_WDT_Clock_Division ICG WDT Clock Division
 * @{
 */
#define REDEF_ICG_WDTCKS_POS                    ICG_ICG0_WDTCKS_POS

#define ICG_WDT_CLK_DIV4                        (0x02UL << REDEF_ICG_WDTCKS_POS)    /*!< CLK/4    */
#define ICG_WDT_CLK_DIV64                       (0x06UL << REDEF_ICG_WDTCKS_POS)    /*!< CLK/64   */
#define ICG_WDT_CLK_DIV128                      (0x07UL << REDEF_ICG_WDTCKS_POS)    /*!< CLK/128  */
#define ICG_WDT_CLK_DIV256                      (0x08UL << REDEF_ICG_WDTCKS_POS)    /*!< CLK/256  */
#define ICG_WDT_CLK_DIV512                      (0x09UL << REDEF_ICG_WDTCKS_POS)    /*!< CLK/512  */
#define ICG_WDT_CLK_DIV1024                     (0x0AUL << REDEF_ICG_WDTCKS_POS)    /*!< CLK/1024 */
#define ICG_WDT_CLK_DIV2048                     (0x0BUL << REDEF_ICG_WDTCKS_POS)    /*!< CLK/2048 */
#define ICG_WDT_CLK_DIV8192                     (0x0DUL << REDEF_ICG_WDTCKS_POS)    /*!< CLK/8192 */
/**
 * @}
 */

/**
 * @defgroup ICG_WDT_Refresh_Range ICG WDT Refresh Range
 * @{
 */
#define REDEF_ICG_WDTWDPT_POS                   ICG_ICG0_WDTWDPT_POS

#define ICG_WDT_RANGE_0TO25PCT                  (0x01UL << REDEF_ICG_WDTWDPT_POS)   /*!< 0%~25%             */
#define ICG_WDT_RANGE_25TO50PCT                 (0x02UL << REDEF_ICG_WDTWDPT_POS)   /*!< 25%~50%            */
#define ICG_WDT_RANGE_0TO50PCT                  (0x03UL << REDEF_ICG_WDTWDPT_POS)   /*!< 0%~50%             */
#define ICG_WDT_RANGE_50TO75PCT                 (0x04UL << REDEF_ICG_WDTWDPT_POS)   /*!< 50%~75%            */
#define ICG_WDT_RANGE_0TO25PCT_50TO75PCT        (0x05UL << REDEF_ICG_WDTWDPT_POS)   /*!< 0%~25% & 50%~75%   */
#define ICG_WDT_RANGE_25TO75PCT                 (0x06UL << REDEF_ICG_WDTWDPT_POS)   /*!< 25%~75%            */
#define ICG_WDT_RANGE_0TO75PCT                  (0x07UL << REDEF_ICG_WDTWDPT_POS)   /*!< 0%~75%             */
#define ICG_WDT_RANGE_75TO100PCT                (0x08UL << REDEF_ICG_WDTWDPT_POS)   /*!< 75%~100%           */
#define ICG_WDT_RANGE_0TO25PCT_75TO100PCT       (0x09UL << REDEF_ICG_WDTWDPT_POS)   /*!< 0%~25% & 75%~100%  */
#define ICG_WDT_RANGE_25TO50PCT_75TO100PCT      (0x0AUL << REDEF_ICG_WDTWDPT_POS)   /*!< 25%~50% & 75%~100% */
#define ICG_WDT_RANGE_0TO50PCT_75TO100PCT       (0x0BUL << REDEF_ICG_WDTWDPT_POS)   /*!< 0%~50% & 75%~100%  */
#define ICG_WDT_RANGE_50TO100PCT                (0x0CUL << REDEF_ICG_WDTWDPT_POS)   /*!< 50%~100%           */
#define ICG_WDT_RANGE_0TO25PCT_50TO100PCT       (0x0DUL << REDEF_ICG_WDTWDPT_POS)   /*!< 0%~25% & 50%~100%  */
#define ICG_WDT_RANGE_25TO100PCT                (0x0EUL << REDEF_ICG_WDTWDPT_POS)   /*!< 25%~100%           */
#define ICG_WDT_RANGE_0TO100PCT                 (0x0FUL << REDEF_ICG_WDTWDPT_POS)   /*!< 0%~100%            */
/**
 * @}
 */

/**
 * @defgroup ICG_WDT_LPM_Count ICG WDT Low Power Mode Count
 * @brief    Counting control of WDT in sleep mode
 * @{
 */
#define ICG_WDT_LPM_CNT_CONTINUE                (0UL)                   /*!< Continue counting in sleep mode */
#define ICG_WDT_LPM_CNT_STOP                    (ICG_ICG0_WDTSLPOFF)    /*!< Stop counting in sleep mode     */
/**
 * @}
 */

/**
 * @defgroup ICG_NMI_Pin_Filter_Clock_Division ICG NMI Pin Filter Clock Division
 * @{
 */
#define REDEF_ICG_NMIFCLK_POS                   ICG_ICG1_SMPCLK_POS

#define ICG_NMI_PIN_FILTER_CLK_DIV1             (0UL)                               /*!< CLK    */
#define ICG_NMI_PIN_FILTER_CLK_DIV8             (0x01UL << REDEF_ICG_NMIFCLK_POS)   /*!< CLK/8  */
#define ICG_NMI_PIN_FILTER_CLK_DIV32            (0x02UL << REDEF_ICG_NMIFCLK_POS)   /*!< CLK/32 */
#define ICG_NMI_PIN_FILTER_CLK_DIV64            (0x03UL << REDEF_ICG_NMIFCLK_POS)   /*!< CLK/64 */
/**
 * @}
 */

/**
 * @defgroup ICG_NMI_Pin_Filter ICG NMI Pin Filter
 * @{
 */
#define ICG_NMI_PIN_FILTER_DISABLE              (0UL)               /*!< Disable NMI Pin filter */
#define ICG_NMI_PIN_FILTER_ENABLE               (ICG_ICG1_NFEN)     /*!< Enable NMI Pin filter  */
/**
 * @}
 */

/**
 * @defgroup ICG_NMI_Pin_Trigger_Edge ICG NMI Pin Trigger Edge
 * @{
 */
#define ICG_NMI_PIN_TRIG_EDGE_FALLING           (0UL)               /*!< Falling edge trigger */
#define ICG_NMI_PIN_TRIG_EDGE_RISING            (ICG_ICG1_NMITRG)   /*!< Rising edge trigger  */
/**
 * @}
 */

/**
 * @defgroup ICG_NMI_Pin_Interrupt ICG NMI Pin Interrupt
 * @{
 */
#define ICG_NMI_PIN_INT_DISABLE                 (0UL)               /*!< Disable NMI pin interrupt */
#define ICG_NMI_PIN_INT_ENABLE                  (ICG_ICG1_NMIEN)    /*!< Enable NMI pin interrupt  */
/**
 * @}
 */

/**
 * @defgroup ICG_NMI_Pin_Reset_State ICG NMI Pin Reset State
 * @{
 */
#define ICG_NMI_PIN_RST_ENABLE                  (0UL)                   /*!< Enable NMI pin after reset  */
#define ICG_NMI_PIN_RST_DISABLE                 (ICG_ICG1_NMIICGEN)     /*!< Disable NMI pin after reset */
/**
 * @}
 */

/**
 * @defgroup ICG_BOR_Voltage_Threshold ICG BOR Voltage Threshold
 * @{
 */
#define ICG_BOR_VOL_THRESHOLD_LVL0              (0UL)                   /*!< BOR voltage threshold 1.9V */
#define ICG_BOR_VOL_THRESHOLD_LVL1              (ICG_ICG1_BOR_LEV_0)    /*!< BOR voltage threshold 2.0V */
#define ICG_BOR_VOL_THRESHOLD_LVL2              (ICG_ICG1_BOR_LEV_1)    /*!< BOR voltage threshold 2.1V */
#define ICG_BOR_VOL_THRESHOLD_LVL3              (ICG_ICG1_BOR_LEV)      /*!< BOR voltage threshold 2.3V */
/**
 * @}
 */

/**
 * @defgroup ICG_BOR_Reset_State ICG BOR Reset State
 * @{
 */
#define ICG_BOR_RST_ENABLE                      (0UL)               /*!< Enable BOR voltage detection after reset  */
#define ICG_BOR_RST_DISABLE                     (ICG_ICG1_BORDIS)   /*!< Disable BOR voltage detection after reset */
/**
 * @}
 */

/**
 * @defgroup ICG_HRC_Frequency_Select ICG HRC Frequency Select
 * @{
 */

#define ICG_HRC_20M                             (0UL)                   /*!< HRC = 20MHZ */
#define ICG_HRC_16M                             (ICG_ICG1_HRCFREQSEL)   /*!< HRC = 16MHZ */
/**
 * @}
 */

/**
 * @defgroup ICG_HRC_Reset_State ICG HRC Reset State
 * @{
 */
#define ICG_HRC_RST_OSCILLATION                 (0UL)               /*!< HRC Oscillation after reset */
#define ICG_HRC_RST_STOP                        (ICG_ICG1_HRCSTOP)  /*!< HRC stop after reset        */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup ICG_Register_Configuration ICG Register Configuration
 * @{
 */

/**
 * @defgroup ICG_SWDT_Preload_Configuration ICG SWDT Preload Configuration
 * @{
 */
/* SWDT register config */
#define ICG_RB_SWDT_AUTS                        (ICG_SWDT_RST_STOP)
#define ICG_RB_SWDT_ITS                         (ICG_SWDT_EXP_TYPE_RST)
#define ICG_RB_SWDT_PERI                        (ICG_SWDT_CNT_PERIOD65536)
#define ICG_RB_SWDT_CKS                         (ICG_SWDT_CLK_DIV2048)
#define ICG_RB_SWDT_WDPT                        (ICG_SWDT_RANGE_0TO100PCT)
#define ICG_RB_SWDT_SLTPOFF                     (ICG_SWDT_LPM_CNT_STOP)

/* SWDT register value */
#define ICG_REG_SWDT_CONFIG                     (ICG_RB_SWDT_AUTS | ICG_RB_SWDT_ITS  | ICG_RB_SWDT_PERI | \
                                                 ICG_RB_SWDT_CKS  | ICG_RB_SWDT_WDPT | ICG_RB_SWDT_SLTPOFF)
/**
 * @}
 */

/**
 * @defgroup ICG_WDT_Preload_Configuration ICG WDT Preload Configuration
 * @{
 */
/* WDT register config */
#define ICG_RB_WDT_AUTS                         (ICG_WDT_RST_STOP)
#define ICG_RB_WDT_ITS                          (ICG_WDT_EXP_TYPE_RST)
#define ICG_RB_WDT_PERI                         (ICG_WDT_CNT_PERIOD65536)
#define ICG_RB_WDT_CKS                          (ICG_WDT_CLK_DIV8192)
#define ICG_RB_WDT_WDPT                         (ICG_WDT_RANGE_0TO100PCT)
#define ICG_RB_WDT_SLTPOFF                      (ICG_WDT_LPM_CNT_STOP)

/* WDT register value */
#define ICG_REG_WDT_CONFIG                      (ICG_RB_WDT_AUTS | ICG_RB_WDT_ITS  | ICG_RB_WDT_PERI | \
                                                 ICG_RB_WDT_CKS  | ICG_RB_WDT_WDPT | ICG_RB_WDT_SLTPOFF)
/**
 * @}
 */

/**
 * @defgroup ICG_NMI_Pin_Preload_Configuration ICG NMI Pin Preload Configuration
 * @{
 */
/* NMI register config */
#define ICG_RB_NMI_FCLK                         (ICG_NMI_PIN_FILTER_CLK_DIV64)
#define ICG_RB_NMI_FEN                          (ICG_NMI_PIN_FILTER_ENABLE)
#define ICG_RB_NMI_TRG                          (ICG_NMI_PIN_TRIG_EDGE_RISING)
#define ICG_RB_NMI_EN                           (ICG_NMI_PIN_INT_ENABLE)
#define ICG_RB_NMI_ICGEN                        (ICG_NMI_PIN_RST_DISABLE)

/* NMI register value */
#define ICG_REG_NMI_CONFIG                      (ICG_RB_NMI_FCLK | ICG_RB_NMI_FEN | ICG_RB_NMI_TRG | \
                                                 ICG_RB_NMI_EN   | ICG_RB_NMI_ICGEN)
/**
 * @}
 */

/**
 * @defgroup ICG_BOR_Preload_Configuration ICG BOR Preload Configuration
 * @{
 */
/* BOR register config */
#define ICG_RB_BOR_LEV                          (ICG_BOR_VOL_THRESHOLD_LVL3)
#define ICG_RB_BOR_DIS                          (ICG_BOR_RST_DISABLE)

/* BOR register value */
#define ICG_REG_BOR_CONFIG                      (ICG_RB_BOR_LEV | ICG_RB_BOR_DIS)
/**
 * @}
 */

/**
 * @defgroup ICG_HRC_Preload_Configuration ICG HRC Preload Configuration
 * @{
 */
/* HRC register config */
#define ICG_RB_HRC_FREQSEL                      (ICG_HRC_16M)
#define ICG_RB_HRC_STOP                         (ICG_HRC_RST_OSCILLATION)

/* HRC register value */
#define ICG_REG_HRC_CONFIG                      (ICG_RB_HRC_FREQSEL | ICG_RB_HRC_STOP)
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup ICG_Register_Value ICG Register Value
 * @{
 */
/* ICG register value */
#ifndef ICG_REG_CFG0_CONST
#define ICG_REG_CFG0_CONST                      (ICG_REG_WDT_CONFIG | ICG_REG_SWDT_CONFIG | 0xE000E000UL)
#endif
#ifndef ICG_REG_CFG1_CONST
#define ICG_REG_CFG1_CONST                      (ICG_REG_NMI_CONFIG | ICG_REG_BOR_CONFIG  | ICG_REG_HRC_CONFIG | 0x03F8FEFEUL)
#endif
/* ICG reserved value */
#define ICG_REG_RESV_CONST                      (0xFFFFFFFFUL)

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/

#endif /* LL_ICG_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_ICG_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
