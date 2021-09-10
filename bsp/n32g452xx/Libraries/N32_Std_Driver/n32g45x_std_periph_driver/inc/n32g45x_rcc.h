/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g45x_rcc.h
 * @author Nations
 * @version v1.0.1
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32G45X_RCC_H__
#define __N32G45X_RCC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g45x.h"

/** @addtogroup N32G45X_StdPeriph_Driver
 * @{
 */

/** @addtogroup RCC
 * @{
 */

/** @addtogroup RCC_Exported_Types
 * @{
 */

typedef struct
{
    uint32_t SysclkFreq;    /*!< returns SYSCLK clock frequency expressed in Hz */
    uint32_t HclkFreq;      /*!< returns HCLK clock frequency expressed in Hz */
    uint32_t Pclk1Freq;     /*!< returns PCLK1 clock frequency expressed in Hz */
    uint32_t Pclk2Freq;     /*!< returns PCLK2 clock frequency expressed in Hz */
    uint32_t AdcPllClkFreq; /*!< returns ADCPLLCLK clock frequency expressed in Hz */
    uint32_t AdcHclkFreq;   /*!< returns ADCHCLK clock frequency expressed in Hz */
} RCC_ClocksType;

/**
 * @}
 */

/** @addtogroup RCC_Exported_Constants
 * @{
 */

/** @addtogroup HSE_configuration
 * @{
 */

#define RC_HSE_DISABLE  ((uint32_t)0x00000000)
#define RCC_HSE_ENABLE  ((uint32_t)0x00010000)
#define RCC_HSE_BYPASS  ((uint32_t)0x00040000)
#define IS_RCC_HSE(HSE) (((HSE) == RC_HSE_DISABLE) || ((HSE) == RCC_HSE_ENABLE) || ((HSE) == RCC_HSE_BYPASS))

/**
 * @}
 */

/** @addtogroup PLL_entry_clock_source
 * @{
 */

#define RCC_PLL_SRC_HSI_DIV2 ((uint32_t)0x00000000)

#define RCC_PLL_SRC_HSE_DIV1 ((uint32_t)0x00010000)
#define RCC_PLL_SRC_HSE_DIV2 ((uint32_t)0x00030000)
#define IS_RCC_PLL_SRC(SOURCE)                                                                                         \
    (((SOURCE) == RCC_PLL_SRC_HSI_DIV2) || ((SOURCE) == RCC_PLL_SRC_HSE_DIV1) || ((SOURCE) == RCC_PLL_SRC_HSE_DIV2))

/**
 * @}
 */

/** @addtogroup PLL_multiplication_factor
 * @{
 */
#define RCC_PLL_MUL_2  ((uint32_t)0x00000000)
#define RCC_PLL_MUL_3  ((uint32_t)0x00040000)
#define RCC_PLL_MUL_4  ((uint32_t)0x00080000)
#define RCC_PLL_MUL_5  ((uint32_t)0x000C0000)
#define RCC_PLL_MUL_6  ((uint32_t)0x00100000)
#define RCC_PLL_MUL_7  ((uint32_t)0x00140000)
#define RCC_PLL_MUL_8  ((uint32_t)0x00180000)
#define RCC_PLL_MUL_9  ((uint32_t)0x001C0000)
#define RCC_PLL_MUL_10 ((uint32_t)0x00200000)
#define RCC_PLL_MUL_11 ((uint32_t)0x00240000)
#define RCC_PLL_MUL_12 ((uint32_t)0x00280000)
#define RCC_PLL_MUL_13 ((uint32_t)0x002C0000)
#define RCC_PLL_MUL_14 ((uint32_t)0x00300000)
#define RCC_PLL_MUL_15 ((uint32_t)0x00340000)
#define RCC_PLL_MUL_16 ((uint32_t)0x00380000)
#define RCC_PLL_MUL_17 ((uint32_t)0x08000000)
#define RCC_PLL_MUL_18 ((uint32_t)0x08040000)
#define RCC_PLL_MUL_19 ((uint32_t)0x08080000)
#define RCC_PLL_MUL_20 ((uint32_t)0x080C0000)
#define RCC_PLL_MUL_21 ((uint32_t)0x08100000)
#define RCC_PLL_MUL_22 ((uint32_t)0x08140000)
#define RCC_PLL_MUL_23 ((uint32_t)0x08180000)
#define RCC_PLL_MUL_24 ((uint32_t)0x081C0000)
#define RCC_PLL_MUL_25 ((uint32_t)0x08200000)
#define RCC_PLL_MUL_26 ((uint32_t)0x08240000)
#define RCC_PLL_MUL_27 ((uint32_t)0x08280000)
#define RCC_PLL_MUL_28 ((uint32_t)0x082C0000)
#define RCC_PLL_MUL_29 ((uint32_t)0x08300000)
#define RCC_PLL_MUL_30 ((uint32_t)0x08340000)
#define RCC_PLL_MUL_31 ((uint32_t)0x08380000)
#define RCC_PLL_MUL_32 ((uint32_t)0x083C0000)
#define IS_RCC_PLL_MUL(MUL)                                                                                            \
    (((MUL) == RCC_PLL_MUL_2) || ((MUL) == RCC_PLL_MUL_3) || ((MUL) == RCC_PLL_MUL_4) || ((MUL) == RCC_PLL_MUL_5)      \
     || ((MUL) == RCC_PLL_MUL_6) || ((MUL) == RCC_PLL_MUL_7) || ((MUL) == RCC_PLL_MUL_8) || ((MUL) == RCC_PLL_MUL_9)   \
     || ((MUL) == RCC_PLL_MUL_10) || ((MUL) == RCC_PLL_MUL_11) || ((MUL) == RCC_PLL_MUL_12)                            \
     || ((MUL) == RCC_PLL_MUL_13) || ((MUL) == RCC_PLL_MUL_14) || ((MUL) == RCC_PLL_MUL_15)                            \
     || ((MUL) == RCC_PLL_MUL_16) || ((MUL) == RCC_PLL_MUL_17) || ((MUL) == RCC_PLL_MUL_18)                            \
     || ((MUL) == RCC_PLL_MUL_19) || ((MUL) == RCC_PLL_MUL_20) || ((MUL) == RCC_PLL_MUL_21)                            \
     || ((MUL) == RCC_PLL_MUL_22) || ((MUL) == RCC_PLL_MUL_23) || ((MUL) == RCC_PLL_MUL_24)                            \
     || ((MUL) == RCC_PLL_MUL_25) || ((MUL) == RCC_PLL_MUL_26) || ((MUL) == RCC_PLL_MUL_27)                            \
     || ((MUL) == RCC_PLL_MUL_28) || ((MUL) == RCC_PLL_MUL_29) || ((MUL) == RCC_PLL_MUL_30)                            \
     || ((MUL) == RCC_PLL_MUL_31) || ((MUL) == RCC_PLL_MUL_32))

/**
 * @}
 */

/** @addtogroup System_clock_source
 * @{
 */

#define RCC_SYSCLK_SRC_HSI    ((uint32_t)0x00000000)
#define RCC_SYSCLK_SRC_HSE    ((uint32_t)0x00000001)
#define RCC_SYSCLK_SRC_PLLCLK ((uint32_t)0x00000002)
#define IS_RCC_SYSCLK_SRC(SOURCE)                                                                                      \
    (((SOURCE) == RCC_SYSCLK_SRC_HSI) || ((SOURCE) == RCC_SYSCLK_SRC_HSE) || ((SOURCE) == RCC_SYSCLK_SRC_PLLCLK))
/**
 * @}
 */

/** @addtogroup AHB_clock_source
 * @{
 */

#define RCC_SYSCLK_DIV1   ((uint32_t)0x00000000)
#define RCC_SYSCLK_DIV2   ((uint32_t)0x00000080)
#define RCC_SYSCLK_DIV4   ((uint32_t)0x00000090)
#define RCC_SYSCLK_DIV8   ((uint32_t)0x000000A0)
#define RCC_SYSCLK_DIV16  ((uint32_t)0x000000B0)
#define RCC_SYSCLK_DIV64  ((uint32_t)0x000000C0)
#define RCC_SYSCLK_DIV128 ((uint32_t)0x000000D0)
#define RCC_SYSCLK_DIV256 ((uint32_t)0x000000E0)
#define RCC_SYSCLK_DIV512 ((uint32_t)0x000000F0)
#define IS_RCC_SYSCLK_DIV(HCLK)                                                                                        \
    (((HCLK) == RCC_SYSCLK_DIV1) || ((HCLK) == RCC_SYSCLK_DIV2) || ((HCLK) == RCC_SYSCLK_DIV4)                         \
     || ((HCLK) == RCC_SYSCLK_DIV8) || ((HCLK) == RCC_SYSCLK_DIV16) || ((HCLK) == RCC_SYSCLK_DIV64)                    \
     || ((HCLK) == RCC_SYSCLK_DIV128) || ((HCLK) == RCC_SYSCLK_DIV256) || ((HCLK) == RCC_SYSCLK_DIV512))
/**
 * @}
 */

/** @addtogroup APB1_APB2_clock_source
 * @{
 */

#define RCC_HCLK_DIV1  ((uint32_t)0x00000000)
#define RCC_HCLK_DIV2  ((uint32_t)0x00000400)
#define RCC_HCLK_DIV4  ((uint32_t)0x00000500)
#define RCC_HCLK_DIV8  ((uint32_t)0x00000600)
#define RCC_HCLK_DIV16 ((uint32_t)0x00000700)
#define IS_RCC_HCLK_DIV(PCLK)                                                                                          \
    (((PCLK) == RCC_HCLK_DIV1) || ((PCLK) == RCC_HCLK_DIV2) || ((PCLK) == RCC_HCLK_DIV4) || ((PCLK) == RCC_HCLK_DIV8)  \
     || ((PCLK) == RCC_HCLK_DIV16))
/**
 * @}
 */

/** @addtogroup RCC_Interrupt_source
 * @{
 */

#define RCC_INT_LSIRDIF ((uint8_t)0x01)
#define RCC_INT_LSERDIF ((uint8_t)0x02)
#define RCC_INT_HSIRDIF ((uint8_t)0x04)
#define RCC_INT_HSERDIF ((uint8_t)0x08)
#define RCC_INT_PLLRDIF ((uint8_t)0x10)
#define RCC_INT_CLKSSIF ((uint8_t)0x80)

#define IS_RCC_INT(IT) ((((IT) & (uint8_t)0xE0) == 0x00) && ((IT) != 0x00))
#define IS_RCC_GET_INT(IT)                                                                                             \
    (((IT) == RCC_INT_LSIRDIF) || ((IT) == RCC_INT_LSERDIF) || ((IT) == RCC_INT_HSIRDIF) || ((IT) == RCC_INT_HSERDIF)  \
     || ((IT) == RCC_INT_PLLRDIF) || ((IT) == RCC_INT_CLKSSIF))
#define IS_RCC_CLR_INT(IT) ((((IT) & (uint8_t)0x60) == 0x00) && ((IT) != 0x00))

/**
 * @}
 */

/** @addtogroup USB_Device_clock_source
 * @{
 */

#define RCC_USBCLK_SRC_PLLCLK_DIV1_5 ((uint8_t)0x00)
#define RCC_USBCLK_SRC_PLLCLK_DIV1   ((uint8_t)0x01)
#define RCC_USBCLK_SRC_PLLCLK_DIV2   ((uint8_t)0x02)
#define RCC_USBCLK_SRC_PLLCLK_DIV3   ((uint8_t)0x03)

#define IS_RCC_USBCLK_SRC(SOURCE)                                                                                      \
    (((SOURCE) == RCC_USBCLK_SRC_PLLCLK_DIV1_5) || ((SOURCE) == RCC_USBCLK_SRC_PLLCLK_DIV1)                            \
     || ((SOURCE) == RCC_USBCLK_SRC_PLLCLK_DIV2) || ((SOURCE) == RCC_USBCLK_SRC_PLLCLK_DIV3))
/**
 * @}
 */

/** @addtogroup ADC_clock_source
 * @{
 */

#define RCC_PCLK2_DIV2 ((uint32_t)0x00000000)
#define RCC_PCLK2_DIV4 ((uint32_t)0x00004000)
#define RCC_PCLK2_DIV6 ((uint32_t)0x00008000)
#define RCC_PCLK2_DIV8 ((uint32_t)0x0000C000)
#define IS_RCC_PCLK2_DIV(ADCCLK)                                                                                       \
    (((ADCCLK) == RCC_PCLK2_DIV2) || ((ADCCLK) == RCC_PCLK2_DIV4) || ((ADCCLK) == RCC_PCLK2_DIV6)                      \
     || ((ADCCLK) == RCC_PCLK2_DIV8))

/**
 * @}
 */

/** @addtogroup RCC_CFGR2_Config
 * @{
 */
#define RCC_TIM18CLK_SRC_TIM18CLK ((uint32_t)0x00000000)
#define RCC_TIM18CLK_SRC_SYSCLK   ((uint32_t)0x20000000)
#define IS_RCC_TIM18CLKSRC(TIM18CLK)                                                                                   \
    (((TIM18CLK) == RCC_TIM18CLK_SRC_TIM18CLK) || ((TIM18CLK) == RCC_TIM18CLK_SRC_SYSCLK))

#define RCC_RNGCCLK_SYSCLK_DIV1  ((uint32_t)0x00000000)
#define RCC_RNGCCLK_SYSCLK_DIV2  ((uint32_t)0x01000000)
#define RCC_RNGCCLK_SYSCLK_DIV3  ((uint32_t)0x02000000)
#define RCC_RNGCCLK_SYSCLK_DIV4  ((uint32_t)0x03000000)
#define RCC_RNGCCLK_SYSCLK_DIV5  ((uint32_t)0x04000000)
#define RCC_RNGCCLK_SYSCLK_DIV6  ((uint32_t)0x05000000)
#define RCC_RNGCCLK_SYSCLK_DIV7  ((uint32_t)0x06000000)
#define RCC_RNGCCLK_SYSCLK_DIV8  ((uint32_t)0x07000000)
#define RCC_RNGCCLK_SYSCLK_DIV9  ((uint32_t)0x08000000)
#define RCC_RNGCCLK_SYSCLK_DIV10 ((uint32_t)0x09000000)
#define RCC_RNGCCLK_SYSCLK_DIV11 ((uint32_t)0x0A000000)
#define RCC_RNGCCLK_SYSCLK_DIV12 ((uint32_t)0x0B000000)
#define RCC_RNGCCLK_SYSCLK_DIV13 ((uint32_t)0x0C000000)
#define RCC_RNGCCLK_SYSCLK_DIV14 ((uint32_t)0x0D000000)
#define RCC_RNGCCLK_SYSCLK_DIV15 ((uint32_t)0x0E000000)
#define RCC_RNGCCLK_SYSCLK_DIV16 ((uint32_t)0x0F000000)
#define RCC_RNGCCLK_SYSCLK_DIV17 ((uint32_t)0x10000000)
#define RCC_RNGCCLK_SYSCLK_DIV18 ((uint32_t)0x11000000)
#define RCC_RNGCCLK_SYSCLK_DIV19 ((uint32_t)0x12000000)
#define RCC_RNGCCLK_SYSCLK_DIV20 ((uint32_t)0x13000000)
#define RCC_RNGCCLK_SYSCLK_DIV21 ((uint32_t)0x14000000)
#define RCC_RNGCCLK_SYSCLK_DIV22 ((uint32_t)0x15000000)
#define RCC_RNGCCLK_SYSCLK_DIV23 ((uint32_t)0x16000000)
#define RCC_RNGCCLK_SYSCLK_DIV24 ((uint32_t)0x17000000)
#define RCC_RNGCCLK_SYSCLK_DIV25 ((uint32_t)0x18000000)
#define RCC_RNGCCLK_SYSCLK_DIV26 ((uint32_t)0x19000000)
#define RCC_RNGCCLK_SYSCLK_DIV27 ((uint32_t)0x1A000000)
#define RCC_RNGCCLK_SYSCLK_DIV28 ((uint32_t)0x1B000000)
#define RCC_RNGCCLK_SYSCLK_DIV29 ((uint32_t)0x1C000000)
#define RCC_RNGCCLK_SYSCLK_DIV30 ((uint32_t)0x1D000000)
#define RCC_RNGCCLK_SYSCLK_DIV31 ((uint32_t)0x1E000000)
#define RCC_RNGCCLK_SYSCLK_DIV32 ((uint32_t)0x1F000000)
#define IS_RCC_RNGCCLKPRE(DIV)                                                                                         \
    (((DIV) == RCC_RNGCCLK_SYSCLK_DIV1) || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV2) || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV3)    \
     || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV4) || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV5) || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV6) \
     || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV7) || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV8) || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV9) \
     || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV10) || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV11)                                     \
     || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV12) || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV13)                                     \
     || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV14) || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV15)                                     \
     || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV16) || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV17)                                     \
     || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV18) || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV19)                                     \
     || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV20) || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV21)                                     \
     || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV22) || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV23)                                     \
     || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV24) || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV25)                                     \
     || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV26) || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV27)                                     \
     || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV28) || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV29)                                     \
     || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV30) || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV31)                                     \
     || ((DIV) == RCC_RNGCCLK_SYSCLK_DIV32))

#define RCC_ETHCLK_SRC_IOINPUTCLK  ((uint32_t)0x00000000)
#define RCC_ETHCLK_SRC_INTERNALCLK ((uint32_t)0x00100000)
#define IS_RCC_ETHCLK_SRC(ETHCLK)  (((ETHCLK) == RCC_ETHCLK_SRC_IOINPUTCLK) || ((ETHCLK) == RCC_ETHCLK_SRC_INTERNALCLK))

#define RCC_ADC1MCLK_SRC_HSI         ((uint32_t)0x00000000)
#define RCC_ADC1MCLK_SRC_HSE         ((uint32_t)0x00020000)
#define IS_RCC_ADC1MCLKSRC(ADC1MCLK) (((ADC1MCLK) == RCC_ADC1MCLK_SRC_HSI) || ((ADC1MCLK) == RCC_ADC1MCLK_SRC_HSE))

#define RCC_ADC1MCLK_DIV1  ((uint32_t)0x00000000)
#define RCC_ADC1MCLK_DIV2  ((uint32_t)0x00000800)
#define RCC_ADC1MCLK_DIV3  ((uint32_t)0x00001000)
#define RCC_ADC1MCLK_DIV4  ((uint32_t)0x00001800)
#define RCC_ADC1MCLK_DIV5  ((uint32_t)0x00002000)
#define RCC_ADC1MCLK_DIV6  ((uint32_t)0x00002800)
#define RCC_ADC1MCLK_DIV7  ((uint32_t)0x00003000)
#define RCC_ADC1MCLK_DIV8  ((uint32_t)0x00003800)
#define RCC_ADC1MCLK_DIV9  ((uint32_t)0x00004000)
#define RCC_ADC1MCLK_DIV10 ((uint32_t)0x00004800)
#define RCC_ADC1MCLK_DIV11 ((uint32_t)0x00005000)
#define RCC_ADC1MCLK_DIV12 ((uint32_t)0x00005800)
#define RCC_ADC1MCLK_DIV13 ((uint32_t)0x00006000)
#define RCC_ADC1MCLK_DIV14 ((uint32_t)0x00006800)
#define RCC_ADC1MCLK_DIV15 ((uint32_t)0x00007000)
#define RCC_ADC1MCLK_DIV16 ((uint32_t)0x00007800)
#define RCC_ADC1MCLK_DIV17 ((uint32_t)0x00008000)
#define RCC_ADC1MCLK_DIV18 ((uint32_t)0x00008800)
#define RCC_ADC1MCLK_DIV19 ((uint32_t)0x00009000)
#define RCC_ADC1MCLK_DIV20 ((uint32_t)0x00009800)
#define RCC_ADC1MCLK_DIV21 ((uint32_t)0x0000A000)
#define RCC_ADC1MCLK_DIV22 ((uint32_t)0x0000A800)
#define RCC_ADC1MCLK_DIV23 ((uint32_t)0x0000B000)
#define RCC_ADC1MCLK_DIV24 ((uint32_t)0x0000B800)
#define RCC_ADC1MCLK_DIV25 ((uint32_t)0x0000C000)
#define RCC_ADC1MCLK_DIV26 ((uint32_t)0x0000C800)
#define RCC_ADC1MCLK_DIV27 ((uint32_t)0x0000D000)
#define RCC_ADC1MCLK_DIV28 ((uint32_t)0x0000D800)
#define RCC_ADC1MCLK_DIV29 ((uint32_t)0x0000E000)
#define RCC_ADC1MCLK_DIV30 ((uint32_t)0x0000E800)
#define RCC_ADC1MCLK_DIV31 ((uint32_t)0x0000F000)
#define RCC_ADC1MCLK_DIV32 ((uint32_t)0x0000F800)
#define IS_RCC_ADC1MCLKPRE(DIV)                                                                                        \
    (((DIV) == RCC_ADC1MCLK_DIV1) || ((DIV) == RCC_ADC1MCLK_DIV2) || ((DIV) == RCC_ADC1MCLK_DIV3)                      \
     || ((DIV) == RCC_ADC1MCLK_DIV4) || ((DIV) == RCC_ADC1MCLK_DIV5) || ((DIV) == RCC_ADC1MCLK_DIV6)                   \
     || ((DIV) == RCC_ADC1MCLK_DIV7) || ((DIV) == RCC_ADC1MCLK_DIV8) || ((DIV) == RCC_ADC1MCLK_DIV9)                   \
     || ((DIV) == RCC_ADC1MCLK_DIV10) || ((DIV) == RCC_ADC1MCLK_DIV11) || ((DIV) == RCC_ADC1MCLK_DIV12)                \
     || ((DIV) == RCC_ADC1MCLK_DIV13) || ((DIV) == RCC_ADC1MCLK_DIV14) || ((DIV) == RCC_ADC1MCLK_DIV15)                \
     || ((DIV) == RCC_ADC1MCLK_DIV16) || ((DIV) == RCC_ADC1MCLK_DIV17) || ((DIV) == RCC_ADC1MCLK_DIV18)                \
     || ((DIV) == RCC_ADC1MCLK_DIV19) || ((DIV) == RCC_ADC1MCLK_DIV20) || ((DIV) == RCC_ADC1MCLK_DIV21)                \
     || ((DIV) == RCC_ADC1MCLK_DIV22) || ((DIV) == RCC_ADC1MCLK_DIV23) || ((DIV) == RCC_ADC1MCLK_DIV24)                \
     || ((DIV) == RCC_ADC1MCLK_DIV25) || ((DIV) == RCC_ADC1MCLK_DIV26) || ((DIV) == RCC_ADC1MCLK_DIV27)                \
     || ((DIV) == RCC_ADC1MCLK_DIV28) || ((DIV) == RCC_ADC1MCLK_DIV29) || ((DIV) == RCC_ADC1MCLK_DIV30)                \
     || ((DIV) == RCC_ADC1MCLK_DIV31) || ((DIV) == RCC_ADC1MCLK_DIV32))

#define RCC_ADCPLLCLK_DISABLE    ((uint32_t)0xFFFFFEFF)
#define RCC_ADCPLLCLK_DIV1       ((uint32_t)0x00000100)
#define RCC_ADCPLLCLK_DIV2       ((uint32_t)0x00000110)
#define RCC_ADCPLLCLK_DIV4       ((uint32_t)0x00000120)
#define RCC_ADCPLLCLK_DIV6       ((uint32_t)0x00000130)
#define RCC_ADCPLLCLK_DIV8       ((uint32_t)0x00000140)
#define RCC_ADCPLLCLK_DIV10      ((uint32_t)0x00000150)
#define RCC_ADCPLLCLK_DIV12      ((uint32_t)0x00000160)
#define RCC_ADCPLLCLK_DIV16      ((uint32_t)0x00000170)
#define RCC_ADCPLLCLK_DIV32      ((uint32_t)0x00000180)
#define RCC_ADCPLLCLK_DIV64      ((uint32_t)0x00000190)
#define RCC_ADCPLLCLK_DIV128     ((uint32_t)0x000001A0)
#define RCC_ADCPLLCLK_DIV256     ((uint32_t)0x000001B0)
#define RCC_ADCPLLCLK_DIV_OTHERS ((uint32_t)0x000001C0)
#define IS_RCC_ADCPLLCLKPRE(DIV)                                                                                       \
    (((DIV) == RCC_ADCPLLCLK_DIV1) || ((DIV) == RCC_ADCPLLCLK_DIV2) || ((DIV) == RCC_ADCPLLCLK_DIV4)                   \
     || ((DIV) == RCC_ADCPLLCLK_DIV6) || ((DIV) == RCC_ADCPLLCLK_DIV8) || ((DIV) == RCC_ADCPLLCLK_DIV10)               \
     || ((DIV) == RCC_ADCPLLCLK_DIV12) || ((DIV) == RCC_ADCPLLCLK_DIV16) || ((DIV) == RCC_ADCPLLCLK_DIV32)             \
     || ((DIV) == RCC_ADCPLLCLK_DIV64) || ((DIV) == RCC_ADCPLLCLK_DIV128) || ((DIV) == RCC_ADCPLLCLK_DIV256)           \
     || ((DIV) == RCC_ADC1MCLK_DIV15) || ((DIV) == RCC_ADCPLLCLK_DIV16)                                                \
     || (((DIV)&RCC_ADCPLLCLK_DIV_OTHERS) == 0x000001C0))

#define RCC_ADCHCLK_DIV1       ((uint32_t)0x00000000)
#define RCC_ADCHCLK_DIV2       ((uint32_t)0x00000001)
#define RCC_ADCHCLK_DIV4       ((uint32_t)0x00000002)
#define RCC_ADCHCLK_DIV6       ((uint32_t)0x00000003)
#define RCC_ADCHCLK_DIV8       ((uint32_t)0x00000004)
#define RCC_ADCHCLK_DIV10      ((uint32_t)0x00000005)
#define RCC_ADCHCLK_DIV12      ((uint32_t)0x00000006)
#define RCC_ADCHCLK_DIV16      ((uint32_t)0x00000007)
#define RCC_ADCHCLK_DIV32      ((uint32_t)0x00000008)
#define RCC_ADCHCLK_DIV_OTHERS ((uint32_t)0x00000008)
#define IS_RCC_ADCHCLKPRE(DIV)                                                                                         \
    (((DIV) == RCC_ADCHCLK_DIV1) || ((DIV) == RCC_ADCHCLK_DIV2) || ((DIV) == RCC_ADCHCLK_DIV4)                         \
     || ((DIV) == RCC_ADCHCLK_DIV6) || ((DIV) == RCC_ADCHCLK_DIV8) || ((DIV) == RCC_ADCHCLK_DIV10)                     \
     || ((DIV) == RCC_ADCHCLK_DIV12) || ((DIV) == RCC_ADCHCLK_DIV16) || ((DIV) == RCC_ADCHCLK_DIV32)                   \
     || (((DIV)&RCC_ADCHCLK_DIV_OTHERS) != 0x00))
/**
 * @}
 */

/** @addtogroup RCC_CFGR3_Config
 * @{
 */
#define RCC_BOR_RST_ENABLE ((uint32_t)0x00000040)

#define RCC_TRNG1MCLK_ENABLE  ((uint32_t)0x00040000)
#define RCC_TRNG1MCLK_DISABLE ((uint32_t)0xFFFBFFFF)

#define RCC_TRNG1MCLK_SRC_HSI ((uint32_t)0x00000000)
#define RCC_TRNG1MCLK_SRC_HSE ((uint32_t)0x00020000)
#define IS_RCC_TRNG1MCLK_SRC(TRNG1MCLK)                                                                                \
    (((TRNG1MCLK) == RCC_TRNG1MCLK_SRC_HSI) || ((TRNG1MCLK) == RCC_TRNG1MCLK_SRC_HSE))

#define RCC_TRNG1MCLK_DIV2  ((uint32_t)0x00000800)
#define RCC_TRNG1MCLK_DIV4  ((uint32_t)0x00001800)
#define RCC_TRNG1MCLK_DIV6  ((uint32_t)0x00002800)
#define RCC_TRNG1MCLK_DIV8  ((uint32_t)0x00003800)
#define RCC_TRNG1MCLK_DIV10 ((uint32_t)0x00004800)
#define RCC_TRNG1MCLK_DIV12 ((uint32_t)0x00005800)
#define RCC_TRNG1MCLK_DIV14 ((uint32_t)0x00006800)
#define RCC_TRNG1MCLK_DIV16 ((uint32_t)0x00007800)
#define RCC_TRNG1MCLK_DIV18 ((uint32_t)0x00008800)
#define RCC_TRNG1MCLK_DIV20 ((uint32_t)0x00009800)
#define RCC_TRNG1MCLK_DIV22 ((uint32_t)0x0000A800)
#define RCC_TRNG1MCLK_DIV24 ((uint32_t)0x0000B800)
#define RCC_TRNG1MCLK_DIV26 ((uint32_t)0x0000C800)
#define RCC_TRNG1MCLK_DIV28 ((uint32_t)0x0000D800)
#define RCC_TRNG1MCLK_DIV30 ((uint32_t)0x0000E800)
#define RCC_TRNG1MCLK_DIV32 ((uint32_t)0x0000F800)
#define IS_RCC_TRNG1MCLKPRE(VAL)                                                                                       \
    (((VAL) == RCC_TRNG1MCLK_DIV2) || ((VAL) == RCC_TRNG1MCLK_DIV4) || ((VAL) == RCC_TRNG1MCLK_DIV6)                   \
     || ((VAL) == RCC_TRNG1MCLK_DIV8) || ((VAL) == RCC_TRNG1MCLK_DIV10) || ((VAL) == RCC_TRNG1MCLK_DIV12)              \
     || ((VAL) == RCC_TRNG1MCLK_DIV14) || ((VAL) == RCC_TRNG1MCLK_DIV16) || ((VAL) == RCC_TRNG1MCLK_DIV18)             \
     || ((VAL) == RCC_TRNG1MCLK_DIV20) || ((VAL) == RCC_TRNG1MCLK_DIV22) || ((VAL) == RCC_TRNG1MCLK_DIV24)             \
     || ((VAL) == RCC_TRNG1MCLK_DIV26) || ((VAL) == RCC_TRNG1MCLK_DIV28) || ((VAL) == RCC_TRNG1MCLK_DIV30)             \
     || ((VAL) == RCC_TRNG1MCLK_DIV32))

/**
 * @}
 */

/** @addtogroup LSE_configuration
 * @{
 */

#define RCC_LSE_DISABLE ((uint8_t)0x00)
#define RCC_LSE_ENABLE  ((uint8_t)0x01)
#define RCC_LSE_BYPASS  ((uint8_t)0x04)
#define IS_RCC_LSE(LSE) (((LSE) == RCC_LSE_DISABLE) || ((LSE) == RCC_LSE_ENABLE) || ((LSE) == RCC_LSE_BYPASS))
/**
 * @}
 */

/** @addtogroup RTC_clock_source
 * @{
 */

#define RCC_RTCCLK_SRC_LSE        ((uint32_t)0x00000100)
#define RCC_RTCCLK_SRC_LSI        ((uint32_t)0x00000200)
#define RCC_RTCCLK_SRC_HSE_DIV128 ((uint32_t)0x00000300)
#define IS_RCC_RTCCLK_SRC(SOURCE)                                                                                      \
    (((SOURCE) == RCC_RTCCLK_SRC_LSE) || ((SOURCE) == RCC_RTCCLK_SRC_LSI) || ((SOURCE) == RCC_RTCCLK_SRC_HSE_DIV128))
/**
 * @}
 */

/** @addtogroup AHB_peripheral
 * @{
 */

#define RCC_AHB_PERIPH_DMA1   ((uint32_t)0x00000001)
#define RCC_AHB_PERIPH_DMA2   ((uint32_t)0x00000002)
#define RCC_AHB_PERIPH_SRAM   ((uint32_t)0x00000004)
#define RCC_AHB_PERIPH_FLITF  ((uint32_t)0x00000010)
#define RCC_AHB_PERIPH_CRC    ((uint32_t)0x00000040)
#define RCC_AHB_PERIPH_XFMC   ((uint32_t)0x00000100)
#define RCC_AHB_PERIPH_RNGC   ((uint32_t)0x00000200)
#define RCC_AHB_PERIPH_SDIO   ((uint32_t)0x00000400)
#define RCC_AHB_PERIPH_SAC    ((uint32_t)0x00000800)
#define RCC_AHB_PERIPH_ADC1   ((uint32_t)0x00001000)
#define RCC_AHB_PERIPH_ADC2   ((uint32_t)0x00002000)
#define RCC_AHB_PERIPH_ADC3   ((uint32_t)0x00004000)
#define RCC_AHB_PERIPH_ADC4   ((uint32_t)0x00008000)
#define RCC_AHB_PERIPH_ETHMAC ((uint32_t)0x00010000)
#define RCC_AHB_PERIPH_QSPI   ((uint32_t)0x00020000)

#define IS_RCC_AHB_PERIPH(PERIPH) ((((PERIPH)&0xFFFC02A8) == 0x00) && ((PERIPH) != 0x00))

/**
 * @}
 */

/** @addtogroup APB2_peripheral
 * @{
 */

#define RCC_APB2_PERIPH_AFIO   ((uint32_t)0x00000001)
#define RCC_APB2_PERIPH_GPIOA  ((uint32_t)0x00000004)
#define RCC_APB2_PERIPH_GPIOB  ((uint32_t)0x00000008)
#define RCC_APB2_PERIPH_GPIOC  ((uint32_t)0x00000010)
#define RCC_APB2_PERIPH_GPIOD  ((uint32_t)0x00000020)
#define RCC_APB2_PERIPH_GPIOE  ((uint32_t)0x00000040)
#define RCC_APB2_PERIPH_GPIOF  ((uint32_t)0x00000080)
#define RCC_APB2_PERIPH_GPIOG  ((uint32_t)0x00000100)
#define RCC_APB2_PERIPH_TIM1   ((uint32_t)0x00000800)
#define RCC_APB2_PERIPH_SPI1   ((uint32_t)0x00001000)
#define RCC_APB2_PERIPH_TIM8   ((uint32_t)0x00002000)
#define RCC_APB2_PERIPH_USART1 ((uint32_t)0x00004000)
#define RCC_APB2_PERIPH_DVP    ((uint32_t)0x00010000)
#define RCC_APB2_PERIPH_UART6  ((uint32_t)0x00020000)
#define RCC_APB2_PERIPH_UART7  ((uint32_t)0x00040000)
#define RCC_APB2_PERIPH_I2C3   ((uint32_t)0x00080000)
#define RCC_APB2_PERIPH_I2C4   ((uint32_t)0x00100000)

#define IS_RCC_APB2_PERIPH(PERIPH) ((((PERIPH)&0xFFE08602) == 0x00) && ((PERIPH) != 0x00))
/**
 * @}
 */

/** @addtogroup APB1_peripheral
 * @{
 */

#define RCC_APB1_PERIPH_TIM2      ((uint32_t)0x00000001)
#define RCC_APB1_PERIPH_TIM3      ((uint32_t)0x00000002)
#define RCC_APB1_PERIPH_TIM4      ((uint32_t)0x00000004)
#define RCC_APB1_PERIPH_TIM5      ((uint32_t)0x00000008)
#define RCC_APB1_PERIPH_TIM6      ((uint32_t)0x00000010)
#define RCC_APB1_PERIPH_TIM7      ((uint32_t)0x00000020)
#define RCC_APB1_PERIPH_COMP      ((uint32_t)0x00000040)
#define RCC_APB1_PERIPH_COMP_FILT ((uint32_t)0x00000080)
#define RCC_APB1_PERIPH_TSC       ((uint32_t)0x00000400)
#define RCC_APB1_PERIPH_WWDG      ((uint32_t)0x00000800)
#define RCC_APB1_PERIPH_SPI2      ((uint32_t)0x00004000)
#define RCC_APB1_PERIPH_SPI3      ((uint32_t)0x00008000)
#define RCC_APB1_PERIPH_USART2    ((uint32_t)0x00020000)
#define RCC_APB1_PERIPH_USART3    ((uint32_t)0x00040000)
#define RCC_APB1_PERIPH_UART4     ((uint32_t)0x00080000)
#define RCC_APB1_PERIPH_UART5     ((uint32_t)0x00100000)
#define RCC_APB1_PERIPH_I2C1      ((uint32_t)0x00200000)
#define RCC_APB1_PERIPH_I2C2      ((uint32_t)0x00400000)
#define RCC_APB1_PERIPH_USB       ((uint32_t)0x00800000)
#define RCC_APB1_PERIPH_CAN1      ((uint32_t)0x02000000)
#define RCC_APB1_PERIPH_CAN2      ((uint32_t)0x04000000)
#define RCC_APB1_PERIPH_BKP       ((uint32_t)0x08000000)
#define RCC_APB1_PERIPH_PWR       ((uint32_t)0x10000000)
#define RCC_APB1_PERIPH_DAC       ((uint32_t)0x20000000)
#define RCC_APB1_PERIPH_OPAMP     ((uint32_t)0x80000000)

#define IS_RCC_APB1_PERIPH(PERIPH) ((((PERIPH)&0x41013300) == 0x00) && ((PERIPH) != 0x00))

/**
 * @}
 */

#define RCC_MCO_PLLCLK_DIV2  ((uint32_t)0x20000000)
#define RCC_MCO_PLLCLK_DIV3  ((uint32_t)0x30000000)
#define RCC_MCO_PLLCLK_DIV4  ((uint32_t)0x40000000)
#define RCC_MCO_PLLCLK_DIV5  ((uint32_t)0x50000000)
#define RCC_MCO_PLLCLK_DIV6  ((uint32_t)0x60000000)
#define RCC_MCO_PLLCLK_DIV7  ((uint32_t)0x70000000)
#define RCC_MCO_PLLCLK_DIV8  ((uint32_t)0x80000000)
#define RCC_MCO_PLLCLK_DIV9  ((uint32_t)0x90000000)
#define RCC_MCO_PLLCLK_DIV10 ((uint32_t)0xA0000000)
#define RCC_MCO_PLLCLK_DIV11 ((uint32_t)0xB0000000)
#define RCC_MCO_PLLCLK_DIV12 ((uint32_t)0xC0000000)
#define RCC_MCO_PLLCLK_DIV13 ((uint32_t)0xD0000000)
#define RCC_MCO_PLLCLK_DIV14 ((uint32_t)0xE0000000)
#define RCC_MCO_PLLCLK_DIV15 ((uint32_t)0xF0000000)
#define IS_RCC_MCOPLLCLKPRE(DIV)                                                                                       \
    (((DIV) == RCC_MCO_PLLCLK_DIV2) || ((DIV) == RCC_MCO_PLLCLK_DIV3) || ((DIV) == RCC_MCO_PLLCLK_DIV4)                \
     || ((DIV) == RCC_MCO_PLLCLK_DIV5) || ((DIV) == RCC_MCO_PLLCLK_DIV6) || ((DIV) == RCC_MCO_PLLCLK_DIV7)             \
     || ((DIV) == RCC_MCO_PLLCLK_DIV8) || ((DIV) == RCC_MCO_PLLCLK_DIV9) || ((DIV) == RCC_MCO_PLLCLK_DIV10)            \
     || ((DIV) == RCC_MCO_PLLCLK_DIV11) || ((DIV) == RCC_MCO_PLLCLK_DIV12) || ((DIV) == RCC_MCO_PLLCLK_DIV13)          \
     || ((DIV) == RCC_MCO_PLLCLK_DIV14) || ((DIV) == RCC_MCO_PLLCLK_DIV15))

/** @addtogroup Clock_source_to_output_on_MCO_pin
 * @{
 */

#define RCC_MCO_NOCLK  ((uint8_t)0x00)
#define RCC_MCO_SYSCLK ((uint8_t)0x04)
#define RCC_MCO_HSI    ((uint8_t)0x05)
#define RCC_MCO_HSE    ((uint8_t)0x06)
#define RCC_MCO_PLLCLK ((uint8_t)0x07)

#define IS_RCC_MCO(MCO)                                                                                                \
    (((MCO) == RCC_MCO_NOCLK) || ((MCO) == RCC_MCO_HSI) || ((MCO) == RCC_MCO_SYSCLK) || ((MCO) == RCC_MCO_HSE)         \
     || ((MCO) == RCC_MCO_PLLCLK))

/**
 * @}
 */

/** @addtogroup RCC_Flag
 * @{
 */
#define RCC_FLAG_HSIRD   ((uint8_t)0x21)
#define RCC_FLAG_HSERD   ((uint8_t)0x31)
#define RCC_FLAG_PLLRD   ((uint8_t)0x39)
#define RCC_FLAG_LSERD   ((uint8_t)0x41)
#define RCC_FLAG_LSIRD   ((uint8_t)0x61)
#define RCC_FLAG_BORRST  ((uint8_t)0x73)
#define RCC_FLAG_RETEMC  ((uint8_t)0x74)
#define RCC_FLAG_BKPEMC  ((uint8_t)0x75)
#define RCC_FLAG_RAMRST  ((uint8_t)0x77)
#define RCC_FLAG_MMURST  ((uint8_t)0x79)
#define RCC_FLAG_PINRST  ((uint8_t)0x7A)
#define RCC_FLAG_PORRST  ((uint8_t)0x7B)
#define RCC_FLAG_SFTRST  ((uint8_t)0x7C)
#define RCC_FLAG_IWDGRST ((uint8_t)0x7D)
#define RCC_FLAG_WWDGRST ((uint8_t)0x7E)
#define RCC_FLAG_LPWRRST ((uint8_t)0x7F)

#define IS_RCC_FLAG(FLAG)                                                                                              \
    (((FLAG) == RCC_FLAG_HSIRD) || ((FLAG) == RCC_FLAG_HSERD) || ((FLAG) == RCC_FLAG_PLLRD)                            \
     || ((FLAG) == RCC_FLAG_LSERD) || ((FLAG) == RCC_FLAG_LSIRD) || ((FLAG) == RCC_FLAG_BORRST)                        \
     || ((FLAG) == RCC_FLAG_RETEMC) || ((FLAG) == RCC_FLAG_BKPEMC) || ((FLAG) == RCC_FLAG_RAMRST)                      \
     || ((FLAG) == RCC_FLAG_MMURST) || ((FLAG) == RCC_FLAG_PINRST) || ((FLAG) == RCC_FLAG_PORRST)                      \
     || ((FLAG) == RCC_FLAG_SFTRST) || ((FLAG) == RCC_FLAG_IWDGRST) || ((FLAG) == RCC_FLAG_WWDGRST)                    \
     || ((FLAG) == RCC_FLAG_LPWRRST))

#define IS_RCC_CALIB_VALUE(VALUE) ((VALUE) <= 0x1F)
/**
 * @}
 */

/**
 * @}
 */

/** @addtogroup RCC_Exported_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup RCC_Exported_Functions
 * @{
 */

void RCC_DeInit(void);
void RCC_ConfigHse(uint32_t RCC_HSE);
ErrorStatus RCC_WaitHseStable(void);
void RCC_SetHsiCalibValue(uint8_t HSICalibrationValue);
void RCC_EnableHsi(FunctionalState Cmd);
void RCC_ConfigPll(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul);
void RCC_EnablePll(FunctionalState Cmd);

void RCC_ConfigSysclk(uint32_t RCC_SYSCLKSource);
uint8_t RCC_GetSysclkSrc(void);
void RCC_ConfigHclk(uint32_t RCC_SYSCLK);
void RCC_ConfigPclk1(uint32_t RCC_HCLK);
void RCC_ConfigPclk2(uint32_t RCC_HCLK);
void RCC_ConfigInt(uint8_t RccInt, FunctionalState Cmd);

void RCC_ConfigUsbClk(uint32_t RCC_USBCLKSource);

void RCC_ConfigTim18Clk(uint32_t RCC_TIM18CLKSource);
void RCC_ConfigRngcClk(uint32_t RCC_RNGCCLKPrescaler);
void RCC_ConfigEthClk(uint32_t RCC_ETHCLKSource);

void RCC_ConfigAdc1mClk(uint32_t RCC_ADC1MCLKSource, uint32_t RCC_ADC1MPrescaler);
void RCC_ConfigAdcPllClk(uint32_t RCC_ADCPLLCLKPrescaler, FunctionalState Cmd);
void RCC_ConfigAdcHclk(uint32_t RCC_ADCHCLKPrescaler);

void RCC_ConfigTrng1mClk(uint32_t RCC_TRNG1MCLKSource, uint32_t RCC_TRNG1MPrescaler);
void RCC_EnableTrng1mClk(FunctionalState Cmd);

void RCC_ConfigLse(uint8_t RCC_LSE);
void RCC_EnableLsi(FunctionalState Cmd);
void RCC_ConfigRtcClk(uint32_t RCC_RTCCLKSource);
void RCC_EnableRtcClk(FunctionalState Cmd);
void RCC_GetClocksFreqValue(RCC_ClocksType* RCC_Clocks);
void RCC_EnableAHBPeriphClk(uint32_t RCC_AHBPeriph, FunctionalState Cmd);
void RCC_EnableAPB2PeriphClk(uint32_t RCC_APB2Periph, FunctionalState Cmd);
void RCC_EnableAPB1PeriphClk(uint32_t RCC_APB1Periph, FunctionalState Cmd);

void RCC_EnableAHBPeriphReset(uint32_t RCC_AHBPeriph, FunctionalState Cmd);
void RCC_EnableAPB2PeriphReset(uint32_t RCC_APB2Periph, FunctionalState Cmd);
void RCC_EnableAPB1PeriphReset(uint32_t RCC_APB1Periph, FunctionalState Cmd);
void RCC_EnableBORReset(FunctionalState Cmd);
void RCC_EnableBackupReset(FunctionalState Cmd);
void RCC_EnableClockSecuritySystem(FunctionalState Cmd);
void RCC_ConfigMcoPllClk(uint32_t RCC_MCOPLLCLKPrescaler);
void RCC_ConfigMco(uint8_t RCC_MCO);
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG);
void RCC_ClrFlag(void);
INTStatus RCC_GetIntStatus(uint8_t RccInt);
void RCC_ClrIntPendingBit(uint8_t RccInt);

#ifdef __cplusplus
}
#endif

#endif /* __N32G45X_RCC_H__ */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
