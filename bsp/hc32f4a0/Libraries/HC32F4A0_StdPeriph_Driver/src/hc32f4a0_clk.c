/**
 *******************************************************************************
 * @file  hc32f4a0_clk.c
 * @brief This file provides firmware functions to manage the Clock(CLK).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Zhangxl         First version
   2020-07-03       Zhangxl         1. Tpyo
                                    2. API CLK_SetSysClkSrc() refine
   2020-08-19       Zhangxl         1. Modify formula of PLL clock get API
                                    2. Zero structure for CLK_PLLxStrucInit()
   2020-08-25       Zhangxl         Modify for MISRAC2012-10.1, 10.3
   2020-10-13       Chengy          Add VBAT init at head of CLK_Xtal32Init()
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_clk.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_CLK CLK
 * @brief Clock Driver Library
 * @{
 */

#if (DDL_CLK_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CLK_Local_Macros CLK Local Macros
 * @brief Be able to modify TIMEOUT according to board condition.
 * @{
 */
#define CLK_XTAL_TIMEOUT                    ((uint32_t)0x1000UL)
#define CLK_XTAL32_TIMEOUT                  ((uint32_t)0x1000UL)
#define CLK_HRC_TIMEOUT                     ((uint32_t)0x1000UL)
#define CLK_MRC_TIMEOUT                     ((uint32_t)0x1000UL)
#define CLK_LRC_TIMEOUT                     ((uint32_t)0x1000UL)
#define CLK_PLLH_TIMEOUT                    ((uint32_t)0x1000UL)
#define CLK_PLLA_TIMEOUT                    ((uint32_t)0x1000UL)

/**
 * @defgroup CLK_Check_Parameters_Validity CLK Check Parameters Validity
 * @{
 */

/* Check CLK register lock status. */
#define IS_CLK_UNLOCKED()       ((M4_PWC->FPRC & PWC_FPRC_FPRCB0) == PWC_FPRC_FPRCB0)

/* Check CLK register lock status. */
#define IS_CLK_SEL_UNLOCKED()   ((M4_PWC->FPRC & PWC_FPRC_FPRCB1) == PWC_FPRC_FPRCB1)

/*! Parameter valid check for XTAL state */
#define IS_CLK_XTAL_STATE(sta)                                                  \
(   ((sta) == CLK_XTAL_OFF)                         ||                          \
    ((sta) == CLK_XTAL_ON))

/*! Parameter valid check for XTAL mode */
#define IS_CLK_XTAL_MODE(MODE)                                                  \
(   ((MODE) == CLK_XTALMODE_OSC)                    ||                          \
    ((MODE) == CLK_XTALMODE_EXCLK))

/*! Parameter valid check for XTAL driver ability mode */
#define IS_CLK_XTALDRV_MODE(drv)                                                \
(   ((drv) == CLK_XTALDRV_HIGH)                     ||                          \
    ((drv) == CLK_XTALDRV_MID)                      ||                          \
    ((drv) == CLK_XTALDRV_LOW)                      ||                          \
    ((drv) == CLK_XTALDRV_ULOW))

/*! Parameter valid check for XTAL stable time selection */
#define IS_CLK_XTALSTB_SEL(stb)                                                 \
(   ((stb) == CLK_XTALSTB_133US)                    ||                          \
    ((stb) == CLK_XTALSTB_255US)                    ||                          \
    ((stb) == CLK_XTALSTB_499US)                    ||                          \
    ((stb) == CLK_XTALSTB_988US)                    ||                          \
    ((stb) == CLK_XTALSTB_2MS)                      ||                          \
    ((stb) == CLK_XTALSTB_4MS)                      ||                          \
    ((stb) == CLK_XTALSTB_8MS)                      ||                          \
    ((stb) == CLK_XTALSTB_16MS)                     ||                          \
    ((stb) == CLK_XTALSTB_31MS))

/*! Parameter valid check for XTALSTD state */
#define IS_CLK_XTALSTD_STATE(sta)                                               \
(   ((sta) == CLK_XTALSTD_OFF)                      ||                          \
    ((sta) == CLK_XTALSTD_ON))

/*! Parameter valid check for XTALSTD mode */
#define IS_CLK_XTALSTD_MODE(mode)                                               \
(   ((mode) == CLK_XTALSTD_MODE_RST)                ||                          \
    ((mode) == CLK_XTALSTD_MODE_INT))

/*! Parameter valid check for XTALSTD interrupt state */
#define IS_CLK_XTALSTD_INT_STATE(sta)                                           \
(   ((sta) == CLK_XTALSTD_INT_OFF)                  ||                          \
    ((sta) == CLK_XTALSTD_INT_ON))

/*! Parameter valid check for XTALSTD reset state */
#define IS_CLK_XTALSTD_RST_STATE(sta)                                           \
(   ((sta) == CLK_XTALSTD_RST_OFF)                  ||                          \
    ((sta) == CLK_XTALSTD_RST_ON))

/*! Parameter valid check for PLLA state */
#define IS_CLK_PLLA_STATE(sta)                                                  \
(   ((sta) == CLK_PLLA_OFF)                         ||                          \
    ((sta) == CLK_PLLA_ON))

/*! Parameter valid check for PLLH state */
#define IS_CLK_PLLH_STATE(sta)                                                  \
(   ((sta) == CLK_PLLH_OFF)                         ||                          \
    ((sta) == CLK_PLLH_ON))

/*! Parameter valid check for XTAL32 state */
#define IS_CLK_XTAL32_STATE(sta)                                                \
(   ((sta) == CLK_XTAL32_OFF)                       ||                          \
    ((sta) == CLK_XTAL32_ON))

/*! Parameter valid check for XTAL32 driver ability mode */
#define IS_CLK_XTAL32DRV_MODE(mode)                                             \
(   ((mode) == CLK_XTAL32DRV_MID)                   ||                          \
    ((mode) == CLK_XTAL32DRV_HIGH))

/*! Parameter valid check for XTAL32 filtering selection */
#define IS_CLK_XTAL32_FILT_SEL(sel)                                             \
(   ((sel) == CLK_XTAL32NF_FULL)                    ||                          \
    ((sel) == CLK_XTAL32NF_PART)                    ||                          \
    ((sel) == CLK_XTAL32NF_NONE))

/*! Parameter valid check for system clock source */
#define IS_CLK_SYSCLK_SRC(src)                                                  \
(   ((src) == CLK_SYSCLKSOURCE_HRC)                 ||                          \
    ((src) == CLK_SYSCLKSOURCE_MRC)                 ||                          \
    ((src) == CLK_SYSCLKSOURCE_LRC)                 ||                          \
    ((src) == CLK_SYSCLKSOURCE_XTAL)                ||                          \
    ((src) == CLK_SYSCLKSOURCE_XTAL32)              ||                          \
    ((src) == CLK_SYSCLKSOURCE_PLLH))

/*! Parameter validity check for PLL input source */
#define IS_CLK_PLL_SRC(src)                                                     \
(   ((src) == CLK_PLLSRC_XTAL)                      ||                          \
    ((src) == CLK_PLLSRC_HRC))

/*! Parameter validity check for PLLH frequency range */
#define IS_CLK_PLLH_FREQ(freq)                                                  \
(   (CLK_PLLH_FREQ_MIN <= (freq))                   &&                          \
    (CLK_PLLH_FREQ_MAX >= (freq)))

/*! Parameter validity check for PLLH M divide */
#define IS_CLK_PLLHM_DIV(m)                                                     \
(   (CLK_PLLHM_DIV_MIN <= (m))                      &&                          \
    (CLK_PLLHM_DIV_MAX >= (m)))

/*! Parameter validity check for PLLH N multi- */
#define IS_CLK_PLLHN_MULTI(n)                                                   \
(   (CLK_PLLHN_MULTI_MIN <= (n))                    &&                          \
    (CLK_PLLHN_MULTI_MAX >= (n)))

/*! Parameter validity check for PLLH R divide */
#define IS_CLK_PLLHR_DIV(r)                                                     \
(   (CLK_PLLHR_DIV_MIN <= (r))                      &&                          \
    (CLK_PLLHR_DIV_MAX >= (r)))

/*! Parameter validity check for PLLH Q divede */
#define IS_CLK_PLLHQ_DIV(q)                                                     \
(   (CLK_PLLHQ_DIV_MIN <= (q))                      &&                          \
    (CLK_PLLHQ_DIV_MAX >= (q)))

/*! Parameter validity check for PLLH P divide */
#define IS_CLK_PLLHP_DIV(p)                                                     \
(   (CLK_PLLHP_DIV_MIN <= (p))                      &&                          \
    (CLK_PLLHP_DIV_MAX >= (p)))

/*! Parameter validity check for PLLH_input freq./PLLM(vco_in) */
#define IS_CLK_PLLH_VCO_IN(vco_in)                                              \
(   (CLK_PLLH_VCO_IN_MIN <= (vco_in))               &&                          \
    (CLK_PLLH_VCO_IN_MAX >= (vco_in)))

/*! Parameter validity check for PLLH vco_in*PLLN(vco_out) */
#define IS_CLK_PLLH_VCO_OUT(vco_out)                                            \
(   (CLK_PLLH_VCO_OUT_MIN <= (vco_out))             &&                          \
    (CLK_PLLH_VCO_OUT_MAX >= (vco_out)))

/*! Parameter validity check for PLLA frequency range */
#define IS_CLK_PLLA_FREQ(freq)                                                  \
(   (CLK_PLLA_FREQ_MIN <= (freq))                   &&                          \
    (CLK_PLLA_FREQ_MAX >= (freq)))

/*! Parameter validity check for PLLA M divide */
#define IS_CLK_PLLAM_DIV(m)                                                     \
(   (CLK_PLLAM_DIV_MIN <= (m))                      &&                          \
    (CLK_PLLAM_DIV_MAX >= (m)))

/*! Parameter validity check for PLLA N multi- */
#define IS_CLK_PLLAN_MULTI(n)                                                   \
(   (CLK_PLLAN_MULTI_MIN <= (n))                    &&                          \
    (CLK_PLLAN_MULTI_MAX >= (n)))

/*! Parameter validity check for PLLA R divide */
#define IS_CLK_PLLAR_DIV(r)                                                     \
(   (CLK_PLLAR_DIV_MIN <= (r))                      &&                          \
    (CLK_PLLAR_DIV_MAX >= (r)))

/*! Parameter validity check for PLLA Q divede */
#define IS_CLK_PLLAQ_DIV(q)                                                     \
(   (CLK_PLLAQ_DIV_MIN <= (q))                      &&                          \
    (CLK_PLLAQ_DIV_MAX >= (q)))

/*! Parameter validity check for PLLA P divide */
#define IS_CLK_PLLAP_DIV(p)                                                     \
(   (CLK_PLLAP_DIV_MIN <= (p))                      &&                          \
    (CLK_PLLAP_DIV_MAX >= (p)))

/*! Parameter validity check for PLLA_input freq./PLLM(vco_in) */
#define IS_CLK_PLLA_VCO_IN(vco_in)                                              \
(   (CLK_PLLA_VCO_IN_MIN <= (vco_in))               &&                          \
    (CLK_PLLA_VCO_IN_MAX >= (vco_in)))

/*! Parameter validity check for PLLA vco_in*PLLN(vco_out) */
#define IS_CLK_PLLA_VCO_OUT(vco_out)                                            \
(   (CLK_PLLA_VCO_OUT_MIN <= (vco_out))             &&                          \
    (CLK_PLLA_VCO_OUT_MAX >= (vco_out)))

/*! Parameter valid check for CLK stable flag. */
#define IS_CLK_STB_FLAG(flag)                                                   \
(   ((flag) != 0x00U)                               &&                          \
    (((flag) | CLK_STB_FLAG_MASK) == CLK_STB_FLAG_MASK))

/*! Parameter valid check for clock category */
#define IS_CLK_CATE(cate)       (((cate) & CLK_CATE_ALL) != (uint8_t)(0x00U))

/*! Parameter valid check for HCLK divider */
#define IS_CLK_HCLK_DIV(div)                                                    \
(   ((div) == CLK_HCLK_DIV1)                        ||                          \
    ((div) == CLK_HCLK_DIV2)                        ||                          \
    ((div) == CLK_HCLK_DIV4)                        ||                          \
    ((div) == CLK_HCLK_DIV8)                        ||                          \
    ((div) == CLK_HCLK_DIV16)                       ||                          \
    ((div) == CLK_HCLK_DIV32)                       ||                          \
    ((div) == CLK_HCLK_DIV64))

/*! Parameter valid check for EXCLK divider */
#define IS_CLK_EXCLK_DIV(div)                                                   \
(   ((div) == CLK_EXCLK_DIV1)                       ||                          \
    ((div) == CLK_EXCLK_DIV2)                       ||                          \
    ((div) == CLK_EXCLK_DIV4)                       ||                          \
    ((div) == CLK_EXCLK_DIV8)                       ||                          \
    ((div) == CLK_EXCLK_DIV16)                      ||                          \
    ((div) == CLK_EXCLK_DIV32)                      ||                          \
    ((div) == CLK_EXCLK_DIV64))

/*! Parameter valid check for PCLK0 divider */
#define IS_CLK_PCLK0_DIV(div)                                                   \
(   ((div) == CLK_PCLK0_DIV1)                       ||                          \
    ((div) == CLK_PCLK0_DIV2)                       ||                          \
    ((div) == CLK_PCLK0_DIV4)                       ||                          \
    ((div) == CLK_PCLK0_DIV8)                       ||                          \
    ((div) == CLK_PCLK0_DIV16)                      ||                          \
    ((div) == CLK_PCLK0_DIV32)                      ||                          \
    ((div) == CLK_PCLK0_DIV64))

/*! Parameter valid check for PCLK1 divider */
#define IS_CLK_PCLK1_DIV(div)                                                   \
(   ((div) == CLK_PCLK1_DIV1)                       ||                          \
    ((div) == CLK_PCLK1_DIV2)                       ||                          \
    ((div) == CLK_PCLK1_DIV4)                       ||                          \
    ((div) == CLK_PCLK1_DIV8)                       ||                          \
    ((div) == CLK_PCLK1_DIV16)                      ||                          \
    ((div) == CLK_PCLK1_DIV32)                      ||                          \
    ((div) == CLK_PCLK1_DIV64))

/*! Parameter valid check for PCLK2 divider */
#define IS_CLK_PCLK2_DIV(div)                                                   \
(   ((div) == CLK_PCLK2_DIV1)                       ||                          \
    ((div) == CLK_PCLK2_DIV2)                       ||                          \
    ((div) == CLK_PCLK2_DIV4)                       ||                          \
    ((div) == CLK_PCLK2_DIV8)                       ||                          \
    ((div) == CLK_PCLK2_DIV16)                      ||                          \
    ((div) == CLK_PCLK2_DIV32)                      ||                          \
    ((div) == CLK_PCLK2_DIV64))

/*! Parameter valid check for PCLK3 divider */
#define IS_CLK_PCLK3_DIV(div)                                                   \
(   ((div) == CLK_PCLK3_DIV1)                       ||                          \
    ((div) == CLK_PCLK3_DIV2)                       ||                          \
    ((div) == CLK_PCLK3_DIV4)                       ||                          \
    ((div) == CLK_PCLK3_DIV8)                       ||                          \
    ((div) == CLK_PCLK3_DIV16)                      ||                          \
    ((div) == CLK_PCLK3_DIV32)                      ||                          \
    ((div) == CLK_PCLK3_DIV64))

/*! Parameter valid check for PCLK4 divider */
#define IS_CLK_PCLK4_DIV(div)                                                   \
(   ((div) == CLK_PCLK4_DIV1)                       ||                          \
    ((div) == CLK_PCLK4_DIV2)                       ||                          \
    ((div) == CLK_PCLK4_DIV4)                       ||                          \
    ((div) == CLK_PCLK4_DIV8)                       ||                          \
    ((div) == CLK_PCLK4_DIV16)                      ||                          \
    ((div) == CLK_PCLK4_DIV32)                      ||                          \
    ((div) == CLK_PCLK4_DIV64))

/*! Parameter valid check for USB clock source */
#define IS_CLK_USB_CLK(src)                                                     \
(   ((src) == CLK_USB_CLK_MCLK_DIV2)                ||                          \
    ((src) == CLK_USB_CLK_MCLK_DIV3)                ||                          \
    ((src) == CLK_USB_CLK_MCLK_DIV4)                ||                          \
    ((src) == CLK_USB_CLK_MCLK_DIV5)                ||                          \
    ((src) == CLK_USB_CLK_MCLK_DIV6)                ||                          \
    ((src) == CLK_USB_CLK_MCLK_DIV7)                ||                          \
    ((src) == CLK_USB_CLK_MCLK_DIV8)                ||                          \
    ((src) == CLK_USB_CLK_PLLHQ)                    ||                          \
    ((src) == CLK_USB_CLK_PLLHR)                    ||                          \
    ((src) == CLK_USB_CLK_PLLAP)                    ||                          \
    ((src) == CLK_USB_CLK_PLLAQ)                    ||                          \
    ((src) == CLK_USB_CLK_PLLAR))

/*! Parameter valid check for CAN clock source */
#define IS_CLK_CAN_CLK(src)                                                     \
(   ((src) == CLK_CAN1_CLK_MCLK_DIV2)               ||                          \
    ((src) == CLK_CAN1_CLK_MCLK_DIV3)               ||                          \
    ((src) == CLK_CAN1_CLK_MCLK_DIV4)               ||                          \
    ((src) == CLK_CAN1_CLK_MCLK_DIV5)               ||                          \
    ((src) == CLK_CAN1_CLK_MCLK_DIV6)               ||                          \
    ((src) == CLK_CAN1_CLK_MCLK_DIV7)               ||                          \
    ((src) == CLK_CAN1_CLK_MCLK_DIV8)               ||                          \
    ((src) == CLK_CAN1_CLK_PLLHQ)                   ||                          \
    ((src) == CLK_CAN1_CLK_PLLHR)                   ||                          \
    ((src) == CLK_CAN1_CLK_PLLAP)                   ||                          \
    ((src) == CLK_CAN1_CLK_PLLAQ)                   ||                          \
    ((src) == CLK_CAN1_CLK_PLLAR)                   ||                          \
    ((src) == CLK_CAN1_CLK_XTAL)                    ||                          \
    ((src) == CLK_CAN2_CLK_MCLK_DIV2)               ||                          \
    ((src) == CLK_CAN2_CLK_MCLK_DIV3)               ||                          \
    ((src) == CLK_CAN2_CLK_MCLK_DIV4)               ||                          \
    ((src) == CLK_CAN2_CLK_MCLK_DIV5)               ||                          \
    ((src) == CLK_CAN2_CLK_MCLK_DIV6)               ||                          \
    ((src) == CLK_CAN2_CLK_MCLK_DIV7)               ||                          \
    ((src) == CLK_CAN2_CLK_MCLK_DIV8)               ||                          \
    ((src) == CLK_CAN2_CLK_PLLHQ)                   ||                          \
    ((src) == CLK_CAN2_CLK_PLLHR)                   ||                          \
    ((src) == CLK_CAN2_CLK_PLLAP)                   ||                          \
    ((src) == CLK_CAN2_CLK_PLLAQ)                   ||                          \
    ((src) == CLK_CAN2_CLK_PLLAR)                   ||                          \
    ((src) == CLK_CAN2_CLK_XTAL))

/*! Parameter valid check for CAN channel for clock source config */
#define IS_CLK_CAN_CH(ch)       (((ch) & CLK_CAN_CH_ALL) != (uint8_t)(0x00U))

/*! Parameter valid check for I2S clock source */
#define IS_CLK_I2S_CLK(src)                                                     \
(   ((src) == CLK_I2S1_CLK_PCLK)                    ||                          \
    ((src) == CLK_I2S1_CLK_PLLHQ)                   ||                          \
    ((src) == CLK_I2S1_CLK_PLLHR)                   ||                          \
    ((src) == CLK_I2S1_CLK_PLLAP)                   ||                          \
    ((src) == CLK_I2S1_CLK_PLLAQ)                   ||                          \
    ((src) == CLK_I2S1_CLK_PLLAR)                   ||                          \
    ((src) == CLK_I2S2_CLK_PCLK)                    ||                          \
    ((src) == CLK_I2S2_CLK_PLLHQ)                   ||                          \
    ((src) == CLK_I2S2_CLK_PLLHR)                   ||                          \
    ((src) == CLK_I2S2_CLK_PLLAP)                   ||                          \
    ((src) == CLK_I2S2_CLK_PLLAQ)                   ||                          \
    ((src) == CLK_I2S2_CLK_PLLAR)                   ||                          \
    ((src) == CLK_I2S3_CLK_PCLK)                    ||                          \
    ((src) == CLK_I2S3_CLK_PLLHQ)                   ||                          \
    ((src) == CLK_I2S3_CLK_PLLHR)                   ||                          \
    ((src) == CLK_I2S3_CLK_PLLAP)                   ||                          \
    ((src) == CLK_I2S3_CLK_PLLAQ)                   ||                          \
    ((src) == CLK_I2S3_CLK_PLLAR)                   ||                          \
    ((src) == CLK_I2S4_CLK_PCLK)                    ||                          \
    ((src) == CLK_I2S4_CLK_PLLHQ)                   ||                          \
    ((src) == CLK_I2S4_CLK_PLLHR)                   ||                          \
    ((src) == CLK_I2S4_CLK_PLLAP)                   ||                          \
    ((src) == CLK_I2S4_CLK_PLLAQ)                   ||                          \
    ((src) == CLK_I2S4_CLK_PLLAR))

/*! Parameter valid check for I2S channel for clock source config */
#define IS_CLK_I2S_CH(ch)       (((ch) & CLK_I2S_CH_ALL) != (uint8_t)(0x00U))

/*! Parameter valid check for PCLK2/PCLK4 source */
#define IS_CLK_PERI_CLK(src)                                                    \
(   ((src) == CLK_PERI_CLK_PCLK)                    ||                          \
    ((src) == CLK_PERI_CLK_PLLHQ)                   ||                          \
    ((src) == CLK_PERI_CLK_PLLHR)                   ||                          \
    ((src) == CLK_PERI_CLK_PLLAP)                   ||                          \
    ((src) == CLK_PERI_CLK_PLLAQ)                   ||                          \
    ((src) == CLK_PERI_CLK_PLLAR))

/*! Parameter valid check for TPIU clock divider */
#define IS_CLK_TPIU_CLK_DIV(div)                                                \
(   ((div) == CLK_TPIU_CLK_DIV1)                    ||                          \
    ((div) == CLK_TPIU_CLK_DIV2)                    ||                          \
    ((div) == CLK_TPIU_CLK_DIV4))

/*! Parameter valid check for CLK MCO clock source. */
#define IS_CLK_MCOSOURCE(src)                                                   \
(   ((src) == CLK_MCOSOURCCE_HRC)                   ||                          \
    ((src) == CLK_MCOSOURCCE_MRC)                   ||                          \
    ((src) == CLK_MCOSOURCCE_LRC)                   ||                          \
    ((src) == CLK_MCOSOURCCE_XTAL)                  ||                          \
    ((src) == CLK_MCOSOURCCE_XTAL32)                ||                          \
    ((src) == CLK_MCOSOURCCE_PLLHP)                 ||                          \
    ((src) == CLK_MCOSOURCCE_PLLHQ)                 ||                          \
    ((src) == CLK_MCOSOURCCE_PLLAP)                 ||                          \
    ((src) == CLK_MCOSOURCCE_PLLAQ)                 ||                          \
    ((src) == CLK_MCOSOURCCE_PLLAR)                 ||                          \
    ((src) == CLK_MCOSOURCCE_SYSCLK))

/*! Parameter valid check for CLK MCO clock divider. */
#define IS_CLK_MCODIV(div)                                                      \
(   ((div) == CLK_MCO_DIV1)                         ||                          \
    ((div) == CLK_MCO_DIV2)                         ||                          \
    ((div) == CLK_MCO_DIV4)                         ||                          \
    ((div) == CLK_MCO_DIV8)                         ||                          \
    ((div) == CLK_MCO_DIV16)                        ||                          \
    ((div) == CLK_MCO_DIV32)                        ||                          \
    ((div) == CLK_MCO_DIV64)                        ||                          \
    ((div) == CLK_MCO_DIV128))

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup CLK_Global_Functions CLK Global Functions
 * @{
 */
/**
 * @brief  Set PLLH/A source clock.
 * @param  [in] u32PllSrc PLLH/A source clock.
 *   @arg  CLK_PLLSRC_XTAL
 *   @arg  CLK_PLLSRC_HRC
 * @retval None
 */
void CLK_SetPLLSrc(uint32_t u32PllSrc)
{
    DDL_ASSERT(IS_CLK_PLL_SRC(u32PllSrc));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    WRITE_REG32(bM4_CMU->PLLHCFGR_b.PLLSRC, u32PllSrc);
}

/**
 * @brief  Init PLLA initial structure with default value.
 * @param  [in] pstcPLLAInit specifies the Parameter of PLLA.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: NULL pointer
 */
en_result_t CLK_PLLAStrucInit(stc_clk_plla_init_t* pstcPLLAInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcPLLAInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcPLLAInit->PLLCFGR        = 0UL;
        pstcPLLAInit->u8PLLState     = CLK_PLLA_OFF;
        pstcPLLAInit->PLLCFGR_f.PLLP = CLK_PLLAP_DFT;
        pstcPLLAInit->PLLCFGR_f.PLLQ = CLK_PLLAQ_DFT;
        pstcPLLAInit->PLLCFGR_f.PLLR = CLK_PLLAR_DFT;
        pstcPLLAInit->PLLCFGR_f.PLLN = CLK_PLLAN_DFT;
        pstcPLLAInit->PLLCFGR_f.PLLM = CLK_PLLAM_DFT;
    }
    return enRet;
}

/**
 * @brief  PLLA Initialize.
 * @param  [in] pstcPLLAInit specifies the structure of PLLA initial config.
 *   @arg  u8PLLState  : The new state of the PLLA.
 *   @arg  PLLCFGR     : PLLA config.
 * @retval en_result_t
 *         OK, PLLA initial successfully
 *         ErrorTimeout, PLLA initial timeout
 *         ErrorInvalidParameter, NULL pointer
 * @note   The pll_input/PLLM (VCOIN) must between 1 ~ 24MHz.
 *         The VCOIN*PLLN (VCOOUT) is between 240 ~ 480MHz.
 *         The PLLA frequency (VCOOUT/PLLAP_Q_R) is between 15 ~ 240MHz.
 */
en_result_t CLK_PLLAInit(const stc_clk_plla_init_t *pstcPLLAInit)
{
    en_result_t enRet;

#ifdef __DEBUG
    uint32_t vcoIn;
    uint32_t vcoOut;
#endif

    if (NULL == pstcPLLAInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
#ifdef __DEBUG
        DDL_ASSERT(IS_CLK_PLLAM_DIV(pstcPLLAInit->PLLCFGR_f.PLLM + 1UL));
        DDL_ASSERT(IS_CLK_PLLAN_MULTI(pstcPLLAInit->PLLCFGR_f.PLLN + 1UL));
        DDL_ASSERT(IS_CLK_PLLAR_DIV(pstcPLLAInit->PLLCFGR_f.PLLR + 1UL));
        DDL_ASSERT(IS_CLK_PLLAQ_DIV(pstcPLLAInit->PLLCFGR_f.PLLQ + 1UL));
        DDL_ASSERT(IS_CLK_PLLAP_DIV(pstcPLLAInit->PLLCFGR_f.PLLP + 1UL));

        vcoIn = ((CLK_PLLSRC_XTAL == bM4_CMU->PLLHCFGR_b.PLLSRC ?
                    XTAL_VALUE : HRC_VALUE) / (pstcPLLAInit->PLLCFGR_f.PLLM + 1UL));
        vcoOut = vcoIn * (pstcPLLAInit->PLLCFGR_f.PLLN + 1UL);

        DDL_ASSERT(IS_CLK_PLLA_VCO_IN(vcoIn));
        DDL_ASSERT(IS_CLK_PLLA_VCO_OUT(vcoOut));
        DDL_ASSERT(IS_CLK_PLLA_FREQ(vcoOut/(pstcPLLAInit->PLLCFGR_f.PLLR + 1UL)));
        DDL_ASSERT(IS_CLK_PLLA_FREQ(vcoOut/(pstcPLLAInit->PLLCFGR_f.PLLQ + 1UL)));
        DDL_ASSERT(IS_CLK_PLLA_FREQ(vcoOut/(pstcPLLAInit->PLLCFGR_f.PLLP + 1UL)));
#endif
        DDL_ASSERT(IS_CLK_PLLA_STATE(pstcPLLAInit->u8PLLState));
        DDL_ASSERT(IS_CLK_UNLOCKED());

        WRITE_REG32(M4_CMU->PLLACFGR, pstcPLLAInit->PLLCFGR);

        if (CLK_PLLA_ON == pstcPLLAInit->u8PLLState)
        {
            enRet = CLK_PLLACmd(Enable);
        }
        else
        {
            enRet = CLK_PLLACmd(Disable);
        }
    }
    return enRet;
}

/**
 * @brief  Init PLLH initial structure with default value.
 * @param  [in] pstcPLLHInit specifies the Parameter of PLLH.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: NULL pointer
 */
en_result_t CLK_PLLHStrucInit(stc_clk_pllh_init_t* pstcPLLHInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcPLLHInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcPLLHInit->PLLCFGR          = 0UL;
        pstcPLLHInit->u8PLLState       = CLK_PLLH_OFF;
        pstcPLLHInit->PLLCFGR_f.PLLP   = CLK_PLLHP_DFT;
        pstcPLLHInit->PLLCFGR_f.PLLQ   = CLK_PLLHQ_DFT;
        pstcPLLHInit->PLLCFGR_f.PLLR   = CLK_PLLHR_DFT;
        pstcPLLHInit->PLLCFGR_f.PLLN   = CLK_PLLHN_DFT;
        pstcPLLHInit->PLLCFGR_f.PLLM   = CLK_PLLHM_DFT;
        pstcPLLHInit->PLLCFGR_f.PLLSRC = CLK_PLLSRC_XTAL;
    }
    return enRet;
}

/**
 * @brief  PLLH initialize.
 * @param  [in] pstcPLLHInit specifies the structure of PLLH initial config.
 *   @arg  u8PLLState  : The new state of the PLLH.
 *   @arg  PLLCFGR     : PLLH config.
 * @retval en_result_t
 *         OK, PLLH initial successfully
 *         ErrorTimeout, PLLH initial timeout
 *         ErrorNotReady, PLLH is the source clock, CANNOT stop it.
 *         ErrorInvalidParameter, NULL pointer
 * @note   The pll_input/PLLM (VCOIN) must between 8 ~ 24MHz.
 *         The VCOIN*PLLN (VCOOUT) is between 600 ~ 1200MHz.
 *         The PLLH frequency (VCOOUT/PLLHP_Q_R) is between 40 ~ 240MHz.
 */
en_result_t CLK_PLLHInit(const stc_clk_pllh_init_t *pstcPLLHInit)
{
    en_result_t enRet;

#ifdef __DEBUG
    uint32_t vcoIn;
    uint32_t vcoOut;
#endif

    if (NULL == pstcPLLHInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
#ifdef __DEBUG
        DDL_ASSERT(IS_CLK_PLLHM_DIV(pstcPLLHInit->PLLCFGR_f.PLLM + 1UL));
        DDL_ASSERT(IS_CLK_PLLHN_MULTI(pstcPLLHInit->PLLCFGR_f.PLLN + 1UL));
        DDL_ASSERT(IS_CLK_PLLHR_DIV(pstcPLLHInit->PLLCFGR_f.PLLR + 1UL));
        DDL_ASSERT(IS_CLK_PLLHQ_DIV(pstcPLLHInit->PLLCFGR_f.PLLQ + 1UL));
        DDL_ASSERT(IS_CLK_PLLHP_DIV(pstcPLLHInit->PLLCFGR_f.PLLP + 1UL));
        DDL_ASSERT(IS_CLK_PLL_SRC(pstcPLLHInit->PLLCFGR_f.PLLSRC));

        vcoIn = ((CLK_PLLSRC_XTAL == pstcPLLHInit->PLLCFGR_f.PLLSRC ?
                    XTAL_VALUE : HRC_VALUE) / (pstcPLLHInit->PLLCFGR_f.PLLM + 1UL));
        vcoOut = vcoIn * (pstcPLLHInit->PLLCFGR_f.PLLN + 1UL);

        DDL_ASSERT(IS_CLK_PLLH_VCO_IN(vcoIn));
        DDL_ASSERT(IS_CLK_PLLH_VCO_OUT(vcoOut));
        DDL_ASSERT(IS_CLK_PLLH_FREQ(vcoOut/(pstcPLLHInit->PLLCFGR_f.PLLR + 1UL)));
        DDL_ASSERT(IS_CLK_PLLH_FREQ(vcoOut/(pstcPLLHInit->PLLCFGR_f.PLLQ + 1UL)));
        DDL_ASSERT(IS_CLK_PLLH_FREQ(vcoOut/(pstcPLLHInit->PLLCFGR_f.PLLP + 1UL)));
#endif
        DDL_ASSERT(IS_CLK_PLLH_STATE(pstcPLLHInit->u8PLLState));
        DDL_ASSERT(IS_CLK_UNLOCKED());

        /* set PLL source in advance */
        WRITE_REG32(bM4_CMU->PLLHCFGR_b.PLLSRC, pstcPLLHInit->PLLCFGR_f.PLLSRC);
        WRITE_REG32(M4_CMU->PLLHCFGR, pstcPLLHInit->PLLCFGR);

        if (CLK_PLLH_ON == pstcPLLHInit->u8PLLState)
        {
            enRet = CLK_PLLHCmd(Enable);
        }
        else
        {
            enRet = CLK_PLLHCmd(Disable);
        }
    }

    return enRet;
}

/**
 * @brief  Init Xtal initial structure with default value.
 * @param  [in] pstcXtalInit specifies the Parameter of XTAL.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: NULL pointer
 */
en_result_t CLK_XtalStrucInit(stc_clk_xtal_init_t* pstcXtalInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcXtalInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcXtalInit->u8XtalState   = CLK_XTAL_OFF;
        pstcXtalInit->u8XtalMode    = CLK_XTALMODE_OSC;
        pstcXtalInit->u8XtalDrv     = CLK_XTALDRV_HIGH;
        pstcXtalInit->u8XtalStb     = CLK_XTALSTB_2MS;
    }

    return enRet;
}

/**
 * @brief  XTAL initialize.
 * @param  [in] pstcXtalInit specifies the XTAL initial config.
 *   @arg  u8XtalState  : The new state of the XTAL.
 *   @arg  u8XtalDrv    : The XTAL drive ability.
 *   @arg  u8XtalMode   : The XTAL mode selection osc or exclk.
 *   @arg  u8XtalStb    : The XTAL stable time selection.
 * @retval en_result_t
 *         OK, XTAL intial successfully.
 *         ErrorTimeout, XTAL operate timeout.
 *         ErrorNotReady, XTAL is the system clock, CANNOT stop it.
 *         ErrorInvalidParameter, NULL pointer.
 * @note   DO NOT STOP XTAL while using it as system clock.
 */
en_result_t CLK_XtalInit(const stc_clk_xtal_init_t *pstcXtalInit)
{
    en_result_t enRet;

    if (NULL == pstcXtalInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_CLK_XTAL_STATE(pstcXtalInit->u8XtalState));
        DDL_ASSERT(IS_CLK_XTALDRV_MODE(pstcXtalInit->u8XtalDrv));
        DDL_ASSERT(IS_CLK_XTAL_MODE(pstcXtalInit->u8XtalMode));
        DDL_ASSERT(IS_CLK_XTALSTB_SEL(pstcXtalInit->u8XtalStb));
        DDL_ASSERT(IS_CLK_UNLOCKED());

        WRITE_REG8(M4_CMU->XTALSTBCR, pstcXtalInit->u8XtalStb);
        WRITE_REG8(M4_CMU->XTALCFGR, (0x80U | pstcXtalInit->u8XtalDrv | pstcXtalInit->u8XtalMode));

        if (CLK_XTAL_ON == pstcXtalInit->u8XtalState)
        {
            enRet = CLK_XtalCmd(Enable);
        }
        else
        {
            enRet = CLK_XtalCmd(Disable);
        }
    }

    return enRet;
}

/**
 * @brief  Init Xtal32 initial structure with default value.
 * @param  [in] pstcXtal32Init specifies the Parameter of XTAL32.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: NULL pointer
 */
en_result_t CLK_Xtal32StrucInit(stc_clk_xtal32_init_t* pstcXtal32Init)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcXtal32Init)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcXtal32Init->u8Xtal32State   = CLK_XTAL32_OFF;
        pstcXtal32Init->u8Xtal32Drv     = CLK_XTAL32DRV_MID;
        pstcXtal32Init->u8Xtal32NF      = CLK_XTAL32NF_FULL;
    }

    return enRet;
}

/**
 * @brief  XTAL32 initialize.
 * @param  [in] pstcXtal32Init specifies the XTAL32 initial config.
 *   @arg  u8Xtal32State  : The new state of the XTAL32.
 *   @arg  u8Xtal32Drv    : The XTAL32 drive capacity.
 *   @arg  u8Xtal32NF     : The XTAL32 nosie filter on or off.
 * @retval en_result_t
 *         OK, XTAL32 intial successfully.
 *         ErrorNotReady, XTAL32 is the system clock, CANNOT stop it.
 *         ErrorInvalidParameter, NULL pointer.
 * @note   DO NOT STOP XTAL32 while using it as system clock.
 */
en_result_t CLK_Xtal32Init(const stc_clk_xtal32_init_t *pstcXtal32Init)
{
    en_result_t enRet;

    if (NULL == pstcXtal32Init)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Parameters check */
        DDL_ASSERT(IS_CLK_XTAL32DRV_MODE(pstcXtal32Init->u8Xtal32Drv));
        DDL_ASSERT(IS_CLK_XTAL32_FILT_SEL(pstcXtal32Init->u8Xtal32NF));
        DDL_ASSERT(IS_CLK_UNLOCKED());
        DDL_ASSERT(IS_CLK_SEL_UNLOCKED());

        WRITE_REG8(M4_PWC->VBATRSTR, 0xA5U);
        WRITE_REG8(M4_CMU->XTAL32CFGR, pstcXtal32Init->u8Xtal32Drv);
        WRITE_REG8(M4_CMU->XTAL32NFR, pstcXtal32Init->u8Xtal32NF);

        if (CLK_XTAL32_ON == pstcXtal32Init->u8Xtal32State)
        {
            enRet = CLK_Xtal32Cmd(Enable);
        }
        else
        {
            enRet = CLK_Xtal32Cmd(Disable);
        }
    }

    return enRet;
}

/**
 * @brief  XTAL function enable/disbale.
 * @param  [in] enNewState specifies the new state of XTAL.
 *   @arg  Enable
 *   @arg  Disable
 * @retval en_result_t
 *         OK, XTAL operate successfully
 *         ErrorNotReady, XTAL is the system clock or as the PLL source clock,
 *                        CANNOT stop it.
 *         ErrorTimeout, XTAL operate timeout.
 * @note   DO NOT STOP XTAL while using it as system clock or as the PLL source clock.
 */
en_result_t CLK_XtalCmd(en_functional_state_t enNewState)
{

    en_result_t enRet = Ok;
    __IO uint32_t timeout = 0UL;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (Disable == enNewState)
    {
        if (CLK_SYSCLKSOURCE_XTAL == READ_REG8_BIT(M4_CMU->CKSWR, CMU_CKSWR_CKSW))
        {
            enRet = ErrorNotReady;
        }
        /* XTAL as PLL clock source and PLL is working */
        else if (0UL == bM4_CMU->PLLHCFGR_b.PLLSRC)
        {
           if (0UL == bM4_CMU->PLLHCR_b.PLLHOFF)
           {
                enRet = ErrorNotReady;
           }
           else
           {
                WRITE_REG32(bM4_CMU->XTALCR_b.XTALSTP, CLK_XTAL_OFF);
           }
        }
        else
        {
            WRITE_REG32(bM4_CMU->XTALCR_b.XTALSTP, CLK_XTAL_OFF);
        }
    }
    else
    {
        WRITE_REG32(bM4_CMU->XTALCR_b.XTALSTP, CLK_XTAL_ON);

        enRet = ErrorTimeout;
        while (timeout <= CLK_XTAL_TIMEOUT)
        {
            if (Set == CLK_GetStableStatus(CMU_OSCSTBSR_XTALSTBF))
            {
                enRet = Ok;
                break;
            }
            timeout++;
        }
    }

    return enRet;
}

/**
 * @brief  XTAL32 function enable/disbale.
 * @param  [in] enNewState specifies the new state of XTAL32.
 *   @arg  Enable
 *   @arg  Disable
 * @retval en_result_t
 *         OK, XTAL32 operate successfully
 *         ErrorNotReady, XTAL32 is the system clock, CANNOT stop it.
 * @note   DO NOT STOP XTAL32 while using it as system clock.
 */
en_result_t CLK_Xtal32Cmd(en_functional_state_t enNewState)
{
    en_result_t enRet = Ok;
    __IO uint32_t timeout = 0UL;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (Disable == enNewState)
    {
        if (CLK_SYSCLKSOURCE_XTAL32 == READ_REG8_BIT(M4_CMU->CKSWR, CMU_CKSWR_CKSW))
        {
            enRet = ErrorNotReady;
        }
        else
        {
            WRITE_REG32(bM4_CMU->XTAL32CR_b.XTAL32STP, CLK_XTAL32_OFF);
        }
    }
    else
    {
        WRITE_REG32(bM4_CMU->XTAL32CR_b.XTAL32STP, CLK_XTAL32_ON);

        while (timeout <= CLK_XTAL32_TIMEOUT)
        {
            timeout++;
        }
    }

    return enRet;
}

/**
 * @brief  HRC function enable/disbale.
 * @param  [in] enNewState specifies the new state of HRC.
 *   @arg  Enable
 *   @arg  Disable
 * @retval en_result_t
 *         OK, HRC operate successfully
 *         ErrorNotReady, HRC is the system clock or as the PLL source clock,
 *                        CANNOT stop it.
 *         ErrorTimeout, HRC operate timeout
 * @note   DO NOT STOP HRC while using it as system clock or as the PLL source clock.
 */
en_result_t CLK_HrcCmd(en_functional_state_t enNewState)
{
    en_result_t enRet = Ok;
    __IO uint32_t timeout = 0UL;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (Disable == enNewState)
    {
        if (CLK_SYSCLKSOURCE_HRC == READ_REG8_BIT(M4_CMU->CKSWR, CMU_CKSWR_CKSW))
        {
            enRet = ErrorNotReady;
        }
        /* HRC as PLL clock source and PLL is working */
        else if (1UL == bM4_CMU->PLLHCFGR_b.PLLSRC)
        {
            if (0UL == bM4_CMU->PLLHCR_b.PLLHOFF)
            {
                enRet = ErrorNotReady;
            }
            else
            {
                WRITE_REG32(bM4_CMU->HRCCR_b.HRCSTP, CLK_HRC_OFF);
            }
        }
        else
        {
            WRITE_REG32(bM4_CMU->HRCCR_b.HRCSTP, CLK_HRC_OFF);
        }
    }
    else
    {
        WRITE_REG32(bM4_CMU->HRCCR_b.HRCSTP, CLK_HRC_ON);

        enRet = ErrorTimeout;
        while (timeout <= CLK_HRC_TIMEOUT)
        {
            if (Set == CLK_GetStableStatus(CMU_OSCSTBSR_HRCSTBF))
            {
                enRet = Ok;
                break;
            }
            timeout++;
        }
    }

    return enRet;
}

/**
 * @brief  MRC function enable/disbale.
 * @param  [in] enNewState specifies the new state of MRC.
 *   @arg  Enable
 *   @arg  Disable
 * @retval en_result_t
 *         OK, MRC operate successfully
 *         ErrorNotReady, MRC is the system clock, CANNOT stop it.
 * @note   DO NOT STOP MRC while using it as system clock.
 */
en_result_t CLK_MrcCmd(en_functional_state_t enNewState)
{
    en_result_t enRet = Ok;
    __IO uint32_t timeout = 0UL;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (Disable == enNewState)
    {
        if (CLK_SYSCLKSOURCE_MRC == READ_REG8_BIT(M4_CMU->CKSWR, CMU_CKSWR_CKSW))
        {
            enRet = ErrorNotReady;
        }
        else
        {
            WRITE_REG32(bM4_CMU->MRCCR_b.MRCSTP, CLK_MRC_OFF);
        }
    }
    else
    {
        WRITE_REG32(bM4_CMU->MRCCR_b.MRCSTP, CLK_MRC_ON);

        while (timeout <= CLK_MRC_TIMEOUT)
        {
            timeout++;
        }
    }

    return enRet;
}

/**
 * @brief  LRC function enable/disbale.
 * @param  [in] enNewState specifies the new state of LRC.
 *   @arg  Enable
 *   @arg  Disable
 * @retval en_result_t
 *         OK, LRC operate successfully
 *         ErrorNotReady, LRC is the system clock, CANNOT stop it.
 * @note   DO NOT STOP LRC while using it as system clock.
 */
en_result_t CLK_LrcCmd(en_functional_state_t enNewState)
{
    en_result_t enRet = Ok;
    __IO uint32_t timeout = 0UL;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (Disable == enNewState)
    {
        if (CLK_SYSCLKSOURCE_LRC == READ_REG8_BIT(M4_CMU->CKSWR, CMU_CKSWR_CKSW))
        {
            enRet = ErrorNotReady;
        }
        else
        {
            WRITE_REG32(bM4_CMU->LRCCR_b.LRCSTP, CLK_LRC_OFF);
        }
    }
    else
    {
        WRITE_REG32(bM4_CMU->LRCCR_b.LRCSTP, CLK_LRC_ON);

        while (timeout <= CLK_LRC_TIMEOUT)
        {
            timeout++;
        }
    }

    return enRet;
}

/**
 * @brief  PLLA function enable/disbale.
 * @param  [in] enNewState specifies the new state of PLLA.
 *   @arg  Enable
 *   @arg  Disable
 * @retval en_result_t
 *         OK, PLLA operate successfully
 *         ErrorTimeout, PLLA operate timeout
 * @note
 */
en_result_t CLK_PLLACmd(en_functional_state_t enNewState)
{
    en_result_t enRet = Ok;
    __IO uint32_t timeout = 0UL;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (Disable == enNewState)
    {
        WRITE_REG32(bM4_CMU->PLLACR_b.PLLAOFF, CLK_PLLA_OFF);
    }
    else
    {
        WRITE_REG32(bM4_CMU->PLLACR_b.PLLAOFF, CLK_PLLA_ON);

        enRet = ErrorTimeout;
        while (timeout <= CLK_PLLA_TIMEOUT)
        {
            if (Set == CLK_GetStableStatus(CMU_OSCSTBSR_PLLASTBF))
            {
                enRet = Ok;
                break;
            }
            timeout++;
        }
    }

    return enRet;
}

/**
 * @brief  PLLH function enable/disbale.
 * @param  [in] enNewState specifies the new state of PLLH.
 *   @arg  Enable
 *   @arg  Disable
 * @retval en_result_t
 *         OK, PLLH operate successfully
 *         ErrorNotReady, PLLH is the system clock, CANNOT stop it.
 *         ErrorTimeout, PLLH operate timeout
 * @note   DO NOT STOP PLLH while using it as system clock.
 */
en_result_t CLK_PLLHCmd(en_functional_state_t enNewState)
{
    en_result_t enRet = Ok;
    __IO uint32_t timeout = 0UL;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (Disable == enNewState)
    {
        if (CLK_SYSCLKSOURCE_PLLH == READ_REG8_BIT(M4_CMU->CKSWR, CMU_CKSWR_CKSW))
        {
            enRet = ErrorNotReady;
        }
        else
        {
            WRITE_REG32(bM4_CMU->PLLHCR_b.PLLHOFF, CLK_PLLH_OFF);
        }
    }
    else
    {
        WRITE_REG32(bM4_CMU->PLLHCR_b.PLLHOFF, CLK_PLLH_ON);

        enRet = ErrorTimeout;
        while (timeout <= CLK_PLLH_TIMEOUT)
        {
            if (Set == CLK_GetStableStatus(CMU_OSCSTBSR_PLLHSTBF))
            {
                enRet = Ok;
                break;
            }
            timeout++;
        }
    }

    return enRet;
}

/**
 * @brief  Init XtalStd initial structure with default value.
 * @param  [in] pstcXtalStdInit specifies the Parameter of XTALSTD.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t CLK_XtalStdStrucInit(stc_clk_xtalstd_init_t* pstcXtalStdInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcXtalStdInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcXtalStdInit->u8XtalStdState = CLK_XTALSTD_OFF;
        pstcXtalStdInit->u8XtalStdMode  = CLK_XTALSTD_MODE_INT;
        pstcXtalStdInit->u8XtalStdInt   = CLK_XTALSTD_RST_OFF;
        pstcXtalStdInit->u8XtalStdRst   = CLK_XTALSTD_INT_OFF;
    }

    return enRet;
}

/**
 * @brief  Initialise the XTAL status detection.
 * @param  [in] pstcXtalStdInit specifies the Parameter of XTALSTD.
 *   @arg  u8XtalStdState: The new state of the XTALSTD.
 *   @arg  u8XtalStdMode:  The XTAL status detection occur interrupt or reset.
 *   @arg  u8XtalStdInt:   The XTAL status detection interrupt on or off.
 *   @arg  u8XtalStdRst:   The XTAL status detection reset on or off.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t CLK_XtalStdInit(const stc_clk_xtalstd_init_t* pstcXtalStdInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcXtalStdInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Parameter valid check */
        DDL_ASSERT(IS_CLK_XTALSTD_STATE(pstcXtalStdInit->u8XtalStdState));
        DDL_ASSERT(IS_CLK_UNLOCKED());

        if(CLK_XTALSTD_OFF == pstcXtalStdInit->u8XtalStdState)
        {
            /* Disbale XTAL status detection */
            WRITE_REG32(bM4_CMU->XTALSTDCR_b.XTALSTDE, (uint32_t)CLK_XTALSTD_OFF);
        }
        else
        {
            /* Parameter valid check */
            DDL_ASSERT(IS_CLK_XTALSTD_MODE(pstcXtalStdInit->u8XtalStdMode));
            DDL_ASSERT(IS_CLK_XTALSTD_INT_STATE(pstcXtalStdInit->u8XtalStdInt));
            DDL_ASSERT(IS_CLK_XTALSTD_RST_STATE(pstcXtalStdInit->u8XtalStdRst));

            /* Configure and enable XTALSTD */
            WRITE_REG8(M4_CMU->XTALSTDCR, (pstcXtalStdInit->u8XtalStdState |   \
                                           pstcXtalStdInit->u8XtalStdMode  |   \
                                           pstcXtalStdInit->u8XtalStdInt   |   \
                                           pstcXtalStdInit->u8XtalStdRst));
        }
    }

    return enRet;
}

/**
 * @brief  Clear the XTAL error flag.
 * @param  None
 * @retval None
 * @note   The system clock should not be XTAL before call this function.
 */
void CLK_ClearXtalStdStatus(void)
{
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if(1UL == READ_REG32(bM4_CMU->XTALSTDSR_b.XTALSTDF))
    {
        /* Clear the XTAL STD flag */
        WRITE_REG32(bM4_CMU->XTALSTDSR_b.XTALSTDF, 0UL);
    }
}

/**
 * @brief  Get the XTAL error flag.
 * @param  None
 * @retval en_flag_status_t
 */
en_flag_status_t CLK_GetXtalStdStatus(void)
{
    return ((0UL != READ_REG32(bM4_CMU->XTALSTDSR_b.XTALSTDF)) ? Set : Reset);
}

/**
 * @brief  Set HRC trimming value.
 * @param  [in] i8TrimVal specifies the trimming value for HRC.
 * @retval None
 */
void CLK_HrcTrim(int8_t i8TrimVal)
{
    DDL_ASSERT(IS_CLK_UNLOCKED());

    WRITE_REG8(M4_CMU->HRCTRM, i8TrimVal);
}

/**
 * @brief  Set MRC trimming value.
 * @param  [in] i8TrimVal specifies the trimming value for MRC.
 * @retval None
 */
void CLK_MrcTrim(int8_t i8TrimVal)
{
    DDL_ASSERT(IS_CLK_UNLOCKED());

    WRITE_REG8(M4_CMU->MRCTRM, i8TrimVal);
}

/**
 * @brief  Set LRC trimming value.
 * @param  [in] i8TrimVal specifies the trimming value for LRC.
 * @retval None
 */
void CLK_LrcTrim(int8_t i8TrimVal)
{
    DDL_ASSERT(IS_CLK_UNLOCKED());

    WRITE_REG8(M4_CMU->LRCTRM, i8TrimVal);
}

/**
 * @brief  Set RTC LRC trimming value.
 * @param  [in] i8TrimVal specifies the trimming value for RTC LRC.
 * @retval None
 */
void CLK_RtcLrcTrim(int8_t i8TrimVal)
{
    DDL_ASSERT(IS_CLK_UNLOCKED());

    WRITE_REG8(M4_CMU->RTCLRCTRM, i8TrimVal);
}

/**
 * @brief  PLL/XTAL/HRC stable flag read.
 * @param  [in] u8StableFlag specifies the stable flag to be read.
 *   @arg  CLK_STB_FLAG_HRCSTB
 *   @arg  CLK_STB_FLAG_XTALSTB
 *   @arg  CLK_STB_FLAG_PLLASTB
 *   @arg  CLK_STB_FLAG_PLLHSTB
 * @retval en_flag_status_t
 */
en_flag_status_t CLK_GetStableStatus(uint8_t u8StableFlag)
{
    DDL_ASSERT(IS_CLK_STB_FLAG(u8StableFlag));

    return ((READ_REG8_BIT(M4_CMU->OSCSTBSR, u8StableFlag))? Set : Reset);
}

/**
 * @brief  Set the system clock source.
 * @param  [in] u8Src specifies the source of system clock.
 *          This parameter can be one of the following values:
 *            @arg    CLK_SYSCLKSOURCE_HRC    : select HRC as system clock source
 *            @arg    CLK_SYSCLKSOURCE_MRC    : select MHRC as system clock source
 *            @arg    CLK_SYSCLKSOURCE_LRC    : select LRC as system clock source
 *            @arg    CLK_SYSCLKSOURCE_XTAL   : select XTAL as system clock source
 *            @arg    CLK_SYSCLKSOURCE_XTAL32 : select XTAL32 as system clock source
 *            @arg    CLK_SYSCLKSOURCE_PLLH   : select PLLH as system clock source
 * @retval None
 */
void CLK_SetSysClkSrc(uint8_t u8Src)
{
    __IO uint32_t timeout = 0UL;
    /* backup FCGx setting */
    __IO uint32_t fcg0 = M4_PWC->FCG0;
    __IO uint32_t fcg1 = M4_PWC->FCG1;
    __IO uint32_t fcg2 = M4_PWC->FCG2;
    __IO uint32_t fcg3 = M4_PWC->FCG3;
    uint8_t u8TmpFlag = 0U;

    DDL_ASSERT(IS_CLK_SYSCLK_SRC(u8Src));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    /* Only current system clock source or target system clock source is PLLH
    need to close fcg0~fcg3 and open fcg0~fcg3 during switch system clock source.
    We need to backup fcg0~fcg3 before close them. */
    if (CLK_SYSCLKSOURCE_PLLH == READ_REG8_BIT(M4_CMU->CKSWR, CMU_CKSWR_CKSW) ||    \
        (CLK_SYSCLKSOURCE_PLLH == u8Src))
    {
        u8TmpFlag = 1U;
        /* FCG0 protect judgment */
        DDL_ASSERT((M4_PWC->FCG0PC & PWC_FCG0PC_PRT0) == PWC_FCG0PC_PRT0);
        /* Close FCGx. */
        M4_PWC->FCG0 = CLK_FCG0_DEFAULT;
        M4_PWC->FCG1 = CLK_FCG1_DEFAULT;
        M4_PWC->FCG2 = CLK_FCG2_DEFAULT;
        M4_PWC->FCG3 = CLK_FCG3_DEFAULT;

        /* Wait stable after close FCGx. */
        do
        {
            timeout++;
        } while(timeout < CLK_SYSCLK_SW_STABLE);
    }

    /* Set system clock source */
    WRITE_REG8(M4_CMU->CKSWR, u8Src);

    if (1U == u8TmpFlag)
    {
        M4_PWC->FCG0 = fcg0;
        M4_PWC->FCG1 = fcg1;
        M4_PWC->FCG2 = fcg2;
        M4_PWC->FCG3 = fcg3;
        /* Wait stable after open fcg. */
        timeout = 0UL;
        do
        {
            timeout++;
        } while(timeout < CLK_SYSCLK_SW_STABLE);
    }

    /* Update system clock */
    SystemCoreClockUpdate();
}

/**
 * @brief  Get bus clock frequency.
 * @param  [out] pstcClkFreq specifies the pointer to get bus frequency.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: NULL pointer
 */
en_result_t CLK_GetClockFreq(stc_clk_freq_t *pstcClkFreq)
{
    en_result_t enRet = Ok;
    uint32_t plln;
    uint32_t pllp;
    uint32_t pllm;

    if (NULL == pstcClkFreq)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        switch (READ_REG8_BIT(M4_CMU->CKSWR, CMU_CKSWR_CKSW))
        {
            case CLK_SYSCLKSOURCE_HRC:
                /* HRC is used to system clock */
                pstcClkFreq->sysclkFreq = HRC_VALUE;
                break;
            case CLK_SYSCLKSOURCE_MRC:
                /* MRC is used to system clock */
                pstcClkFreq->sysclkFreq = MRC_VALUE;
                break;
            case CLK_SYSCLKSOURCE_LRC:
                /* LRC is used to system clock */
                pstcClkFreq->sysclkFreq = LRC_VALUE;
                break;
            case CLK_SYSCLKSOURCE_XTAL:
                /* XTAL is used to system clock */
                pstcClkFreq->sysclkFreq = XTAL_VALUE;
                break;
            case CLK_SYSCLKSOURCE_XTAL32:
                /* XTAL32 is used to system clock */
                pstcClkFreq->sysclkFreq = HRC_VALUE;
                break;
            case CLK_SYSCLKSOURCE_PLLH:
                /* PLLHP is used as system clock. */
                pllp = (uint32_t)((M4_CMU->PLLHCFGR >> CMU_PLLHCFGR_PLLHP_POS) & 0x0FUL);
                plln = (uint32_t)((M4_CMU->PLLHCFGR >> CMU_PLLHCFGR_PLLHN_POS) & 0xFFUL);
                pllm = (uint32_t)((M4_CMU->PLLHCFGR >> CMU_PLLHCFGR_PLLHM_POS) & 0x03UL);

                /* fpll = ((pllin / pllm) * plln) / pllp */
                if (CLK_PLLSRC_XTAL == READ_REG32_BIT(M4_CMU->PLLHCFGR, CMU_PLLHCFGR_PLLSRC))
                {
                    pstcClkFreq->sysclkFreq = ((XTAL_VALUE/(pllm + 1UL))*(plln + 1UL))/(pllp + 1UL);
                }
                else
                {
                    pstcClkFreq->sysclkFreq = ((HRC_VALUE/(pllm + 1UL))*(plln + 1UL))/(pllp + 1UL);
                }
                break;
            default:
                break;
        }

        /* Get hclk. */
        pstcClkFreq->hclkFreq = pstcClkFreq->sysclkFreq >> \
                    (READ_REG32_BIT(M4_CMU->SCFGR, CMU_SCFGR_HCLKS) >> CMU_SCFGR_HCLKS_POS);

        /* Get exck. */
        pstcClkFreq->exckFreq = pstcClkFreq->sysclkFreq >> \
                    (READ_REG32_BIT(M4_CMU->SCFGR, CMU_SCFGR_EXCKS) >> CMU_SCFGR_EXCKS_POS);

        /* Get pclk0. */
        pstcClkFreq->pclk0Freq = pstcClkFreq->sysclkFreq >> \
                    (READ_REG32_BIT(M4_CMU->SCFGR, CMU_SCFGR_PCLK0S) >> CMU_SCFGR_PCLK0S_POS);

        /* Get pclk1. */
        pstcClkFreq->pclk1Freq = pstcClkFreq->sysclkFreq >> \
                    (READ_REG32_BIT(M4_CMU->SCFGR, CMU_SCFGR_PCLK1S) >> CMU_SCFGR_PCLK1S_POS);

        /* Get pclk2. */
        pstcClkFreq->pclk2Freq = pstcClkFreq->sysclkFreq >> \
                    (READ_REG32_BIT(M4_CMU->SCFGR, CMU_SCFGR_PCLK2S) >> CMU_SCFGR_PCLK2S_POS);

        /* Get pclk3. */
        pstcClkFreq->pclk3Freq = pstcClkFreq->sysclkFreq >> \
                    (READ_REG32_BIT(M4_CMU->SCFGR, CMU_SCFGR_PCLK3S) >> CMU_SCFGR_PCLK3S_POS);

        /* Get pclk4. */
        pstcClkFreq->pclk4Freq = pstcClkFreq->sysclkFreq >> \
                    (READ_REG32_BIT(M4_CMU->SCFGR, CMU_SCFGR_PCLK4S) >> CMU_SCFGR_PCLK4S_POS);
    }
    return enRet;
}

/**
 * @brief  Get PLLH/PLLA P/Q/R clock frequency.
 * @param  [out] pstcPllClkFreq specifies the pointer to get PLLH/PLLA frequency.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: NULL pointer
 */
en_result_t CLK_GetPllClockFreq(stc_pll_clk_freq_t *pstcPllClkFreq)
{
    en_result_t enRet = Ok;
    uint32_t pllhn;
    uint32_t pllhm;
    uint32_t pllhp;
    uint32_t pllhq;
    uint32_t pllhr;
    uint32_t pllan;
    uint32_t pllam;
    uint32_t pllap;
    uint32_t pllaq;
    uint32_t pllar;
    uint32_t pllin;

    if (NULL == pstcPllClkFreq)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pllhp = (uint32_t)((M4_CMU->PLLHCFGR >> CMU_PLLHCFGR_PLLHP_POS) & 0x0FUL);
        pllhq = (uint32_t)((M4_CMU->PLLHCFGR >> CMU_PLLHCFGR_PLLHQ_POS) & 0x0FUL);
        pllhr = (uint32_t)((M4_CMU->PLLHCFGR >> CMU_PLLHCFGR_PLLHR_POS) & 0x0FUL);
        pllhn = (uint32_t)((M4_CMU->PLLHCFGR >> CMU_PLLHCFGR_PLLHN_POS) & 0xFFUL);
        pllhm = (uint32_t)((M4_CMU->PLLHCFGR >> CMU_PLLHCFGR_PLLHM_POS) & 0x03UL);

        pllap = (uint32_t)((M4_CMU->PLLACFGR >> CMU_PLLHCFGR_PLLHP_POS) & 0x0FUL);
        pllaq = (uint32_t)((M4_CMU->PLLACFGR >> CMU_PLLHCFGR_PLLHQ_POS) & 0x0FUL);
        pllar = (uint32_t)((M4_CMU->PLLACFGR >> CMU_PLLHCFGR_PLLHR_POS) & 0x0FUL);
        pllan = (uint32_t)((M4_CMU->PLLACFGR >> CMU_PLLHCFGR_PLLHN_POS) & 0x1FFUL);
        pllam = (uint32_t)((M4_CMU->PLLACFGR >> CMU_PLLHCFGR_PLLHM_POS) & 0x1FUL);

        /* PLLHP is used as system clock. */
        if (CLK_PLLSRC_XTAL == READ_REG32_BIT(M4_CMU->PLLHCFGR, CMU_PLLHCFGR_PLLSRC))
        {
            pllin = XTAL_VALUE;
        }
        else
        {
            pllin = HRC_VALUE;
        }
        pstcPllClkFreq->pllhvcin = (pllin/(pllhm + 1UL));
        pstcPllClkFreq->pllhvco = ((pllin/(pllhm + 1UL))*(pllhn + 1UL));
        pstcPllClkFreq->pllhp = ((pllin/(pllhm + 1UL))*(pllhn + 1UL))/(pllhp + 1UL);
        pstcPllClkFreq->pllhq = ((pllin/(pllhm + 1UL))*(pllhn + 1UL))/(pllhq + 1UL);
        pstcPllClkFreq->pllhr = ((pllin/(pllhm + 1UL))*(pllhn + 1UL))/(pllhr + 1UL);

        pstcPllClkFreq->pllavcin = (pllin/(pllam + 1UL));
        pstcPllClkFreq->pllavco = ((pllin/(pllam + 1UL))*(pllan + 1UL));
        pstcPllClkFreq->pllap = ((pllin/(pllam + 1UL))*(pllan + 1UL))/(pllap + 1UL);
        pstcPllClkFreq->pllaq = ((pllin/(pllam + 1UL))*(pllan + 1UL))/(pllaq + 1UL);
        pstcPllClkFreq->pllar = ((pllin/(pllam + 1UL))*(pllan + 1UL))/(pllar + 1UL);
    }
    return enRet;
}

/**
 * @brief  HCLK/PCLK divide setting.
 * @param  [in] u8ClkCate specifies the clock to be divided.
 *   @arg  CLK_CATE_PCLK0: Select PCLK0 to be divided
 *   @arg  CLK_CATE_PCLK1: Select PCLK1 to be divided
 *   @arg  CLK_CATE_PCLK2: Select PCLK2 to be divided
 *   @arg  CLK_CATE_PCLK3: Select PCLK3 to be divided
 *   @arg  CLK_CATE_PCLK4: Select PCLK4 to be divided
 *   @arg  CLK_CATE_EXCLK: Select EXCLK to be divided
 *   @arg  CLK_CATE_HCLK : Select HCLK  to be divided
 *   @arg  CLK_CATE_ALL : Select all to be divided
 * @param  [in] u32Div specifies the clock divide factor.
 *   @arg  CLK_HCLK_DIV1 : HCLK no divide
 *   @arg  CLK_HCLK_DIV2 : HCLK divided by 2
 *   @arg  CLK_HCLK_DIV4 : HCLK divided by 4
 *   @arg  CLK_HCLK_DIV8 : HCLK divided by 8
 *   @arg  CLK_HCLK_DIV16: HCLK divided by 16
 *   @arg  CLK_HCLK_DIV32: HCLK divided by 32
 *   @arg  CLK_HCLK_DIV64: HCLK divided by 64
 *   @arg  CLK_EXCLK_DIV1 : EXCLK no divide
 *   @arg  CLK_EXCLK_DIV2 : EXCLK divided by 2
 *   @arg  CLK_EXCLK_DIV4 : EXCLK divided by 4
 *   @arg  CLK_EXCLK_DIV8 : EXCLK divided by 8
 *   @arg  CLK_EXCLK_DIV16: EXCLK divided by 16
 *   @arg  CLK_EXCLK_DIV32: EXCLK divided by 32
 *   @arg  CLK_EXCLK_DIV64: EXCLK divided by 64
 *   @arg  CLK_PCLKx_DIV1 : PCLKx no divide
 *   @arg  CLK_PCLKx_DIV2 : PCLKx divided by 2
 *   @arg  CLK_PCLKx_DIV4 : PCLKx divided by 4
 *   @arg  CLK_PCLKx_DIV8 : PCLKx divided by 8
 *   @arg  CLK_PCLKx_DIV16: PCLKx divided by 16
 *   @arg  CLK_PCLKx_DIV32: PCLKx divided by 32
 *   @arg  CLK_PCLKx_DIV64: PCLKx divided by 64
 * @retval None
 * @note   'x' is 0~4 in CLK_PCLKx_DIVy
 */
void CLK_ClkDiv(uint8_t u8ClkCate, uint32_t u32Div)
{
    __IO uint32_t timeout = 0UL;
    /* backup FCGx setting */
    __IO uint32_t fcg0 = M4_PWC->FCG0;
    __IO uint32_t fcg1 = M4_PWC->FCG1;
    __IO uint32_t fcg2 = M4_PWC->FCG2;
    __IO uint32_t fcg3 = M4_PWC->FCG3;
    uint8_t u8TmpFlag = 0U;

    DDL_ASSERT(IS_CLK_HCLK_DIV(u32Div & CMU_SCFGR_HCLKS));
    DDL_ASSERT(IS_CLK_EXCLK_DIV(u32Div & CMU_SCFGR_EXCKS));
    DDL_ASSERT(IS_CLK_PCLK0_DIV(u32Div & CMU_SCFGR_PCLK0S));
    DDL_ASSERT(IS_CLK_PCLK1_DIV(u32Div & CMU_SCFGR_PCLK1S));
    DDL_ASSERT(IS_CLK_PCLK2_DIV(u32Div & CMU_SCFGR_PCLK2S));
    DDL_ASSERT(IS_CLK_PCLK3_DIV(u32Div & CMU_SCFGR_PCLK3S));
    DDL_ASSERT(IS_CLK_PCLK4_DIV(u32Div & CMU_SCFGR_PCLK4S));
    DDL_ASSERT(IS_CLK_CATE(u8ClkCate));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    /* Only current system clock source or target system clock source is PLLH
    need to close fcg0~fcg3 and open fcg0~fcg3 during switch system clock source.
    We need to backup fcg0~fcg3 before close them. */
    if (CLK_SYSCLKSOURCE_PLLH == READ_REG8_BIT(M4_CMU->CKSWR, CMU_CKSWR_CKSW))
    {
        DDL_ASSERT((M4_PWC->FCG0PC & PWC_FCG0PC_PRT0) == PWC_FCG0PC_PRT0);

        u8TmpFlag = 1U;

        /* Close FCGx. */
        M4_PWC->FCG0 = CLK_FCG0_DEFAULT;
        M4_PWC->FCG1 = CLK_FCG1_DEFAULT;
        M4_PWC->FCG2 = CLK_FCG2_DEFAULT;
        M4_PWC->FCG3 = CLK_FCG3_DEFAULT;

        /* Wait stable after close FCGx. */
        do
        {
            timeout++;
        } while(timeout < CLK_SYSCLK_SW_STABLE);
    }

    /* PCLK0 div */
    if (0U != (CLK_CATE_PCLK0 & u8ClkCate))
    {
        MODIFY_REG32(M4_CMU->SCFGR, CMU_SCFGR_PCLK0S, u32Div);
    }
    /* PCLK1 div */
    if (0U != (CLK_CATE_PCLK1 & u8ClkCate))
    {
        MODIFY_REG32(M4_CMU->SCFGR, CMU_SCFGR_PCLK1S, u32Div);
    }
    /* PCLK2 div */
    if (0U != (CLK_CATE_PCLK2 & u8ClkCate))
    {
        MODIFY_REG32(M4_CMU->SCFGR, CMU_SCFGR_PCLK2S, u32Div);
    }
    /* PCLK3 div */
    if (0U != (CLK_CATE_PCLK3 & u8ClkCate))
    {
        MODIFY_REG32(M4_CMU->SCFGR, CMU_SCFGR_PCLK3S, u32Div);
    }
    /* PCLK4 div */
    if (0U != (CLK_CATE_PCLK4 & u8ClkCate))
    {
        MODIFY_REG32(M4_CMU->SCFGR, CMU_SCFGR_PCLK4S, u32Div);
    }
    /* Ext. bus clock div */
    if (0U != (CLK_CATE_EXCLK & u8ClkCate))
    {
        MODIFY_REG32(M4_CMU->SCFGR, CMU_SCFGR_EXCKS, u32Div);
    }
    /* HCLK div */
    if (0U != (CLK_CATE_HCLK & u8ClkCate))
    {
        MODIFY_REG32(M4_CMU->SCFGR, CMU_SCFGR_HCLKS, u32Div);
    }
    if (1U == u8TmpFlag)
    {
        M4_PWC->FCG0 = fcg0;
        M4_PWC->FCG1 = fcg1;
        M4_PWC->FCG2 = fcg2;
        M4_PWC->FCG3 = fcg3;

        /* Wait stable after open fcg. */
        timeout = 0UL;
        do
        {
            timeout++;
        } while(timeout < CLK_SYSCLK_SW_STABLE);
    }
}

/**
 * @brief  USB clock source config.
 * @param  [in] u8UsbClk specifies the USB clock source.
 *   @arg  CLK_USB_CLK_MCLK_DIV2:  Select PCLK1 divide by 2 as USB clock
 *   @arg  CLK_USB_CLK_MCLK_DIV3:  Select PCLK1 divide by 3 as USB clock
 *   @arg  CLK_USB_CLK_MCLK_DIV4:  Select PCLK1 divide by 4 as USB clock
 *   @arg  CLK_USB_CLK_MCLK_DIV5:  Select PCLK1 divide by 5 as USB clock
 *   @arg  CLK_USB_CLK_MCLK_DIV6:  Select PCLK1 divide by 6 as USB clock
 *   @arg  CLK_USB_CLK_MCLK_DIV7:  Select PCLK1 divide by 7 as USB clock
 *   @arg  CLK_USB_CLK_MCLK_DIV8:  Select PCLK1 divide by 8 as USB clock
 *   @arg  CLK_USB_CLK_PLLHQ: Select PLLHQ as USB clock
 *   @arg  CLK_USB_CLK_PLLHR: Select PLLHR as USB clock
 *   @arg  CLK_USB_CLK_PLLAP: Select PLLAP as USB clock
 *   @arg  CLK_USB_CLK_PLLAQ: Select PLLAQ as USB clock
 *   @arg  CLK_USB_CLK_PLLAR: Select PLLAR as USB clock
 * @retval None
 */
void CLK_USB_ClkConfig(uint8_t u8UsbClk)
{
    DDL_ASSERT(IS_CLK_USB_CLK(u8UsbClk));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    WRITE_REG8(M4_CMU->USBCKCFGR, u8UsbClk);
}

/**
 * @brief  CAN clock source config.
 * @param  [in] u8CanCh specifies the CAN channel for clock source.
 *   @arg  CLK_CAN_CH1:  CAN Channel 1
 *   @arg  CLK_CAN_CH2:  CAN Channel 2
 * @param  [in] u8CanClk specifies the CAN clock source.
 *   @arg  CLK_CAN1_CLK_MCLK_DIV2:  Select system clock divide by 2 as CAN clock
 *   @arg  CLK_CAN1_CLK_MCLK_DIV3:  Select system clock divide by 3 as CAN clock
 *   @arg  CLK_CAN1_CLK_MCLK_DIV4:  Select system clock divide by 4 as CAN clock
 *   @arg  CLK_CAN1_CLK_MCLK_DIV5:  Select system clock divide by 5 as CAN clock
 *   @arg  CLK_CAN1_CLK_MCLK_DIV6:  Select system clock divide by 6 as CAN clock
 *   @arg  CLK_CAN1_CLK_MCLK_DIV7:  Select system clock divide by 7 as CAN clock
 *   @arg  CLK_CAN1_CLK_MCLK_DIV8:  Select system clock divide by 8 as CAN clock
 *   @arg  CLK_CAN1_CLK_PLLHQ: Select PLLHQ as CAN clock
 *   @arg  CLK_CAN1_CLK_PLLHR: Select PLLHR as CAN clock
 *   @arg  CLK_CAN1_CLK_PLLAP: Select PLLAP as CAN clock
 *   @arg  CLK_CAN1_CLK_PLLAQ: Select PLLAQ as CAN clock
 *   @arg  CLK_CAN1_CLK_PLLAR: Select PLLAR as CAN clock
 *   @arg  CLK_CAN_CLK_XTAL: Select PLLAR as CAN clock
 *   @arg  CLK_CAN2_CLK_MCLK_DIV2:  Select system clock divide by 2 as CAN clock
 *   @arg  CLK_CAN2_CLK_MCLK_DIV3:  Select system clock divide by 3 as CAN clock
 *   @arg  CLK_CAN2_CLK_MCLK_DIV4:  Select system clock divide by 4 as CAN clock
 *   @arg  CLK_CAN2_CLK_MCLK_DIV5:  Select system clock divide by 5 as CAN clock
 *   @arg  CLK_CAN2_CLK_MCLK_DIV6:  Select system clock divide by 6 as CAN clock
 *   @arg  CLK_CAN2_CLK_MCLK_DIV7:  Select system clock divide by 7 as CAN clock
 *   @arg  CLK_CAN2_CLK_MCLK_DIV8:  Select system clock divide by 8 as CAN clock
 *   @arg  CLK_CAN2_CLK_PLLHQ: Select PLLHQ as CAN clock
 *   @arg  CLK_CAN2_CLK_PLLHR: Select PLLHR as CAN clock
 *   @arg  CLK_CAN2_CLK_PLLAP: Select PLLAP as CAN clock
 *   @arg  CLK_CAN2_CLK_PLLAQ: Select PLLAQ as CAN clock
 *   @arg  CLK_CAN2_CLK_PLLAR: Select PLLAR as CAN clock
 *   @arg  CLK_CAN2_CLK_XTAL: Select PLLAR as CAN clock
 * @retval None
 */
void CLK_CAN_ClkConfig(uint8_t u8CanCh, uint8_t u8CanClk)
{
    DDL_ASSERT(IS_CLK_CAN_CH(u8CanCh));
    DDL_ASSERT(IS_CLK_CAN_CLK(u8CanClk));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    if (0U != (CLK_CAN_CH1 & u8CanCh))
    {
        MODIFY_REG8(M4_CMU->CANCKCFGR, CMU_CANCKCFGR_CAN1CKS, u8CanClk);
    }
    if (0U != (CLK_CAN_CH2 & u8CanCh))
    {
        MODIFY_REG8(M4_CMU->CANCKCFGR, CMU_CANCKCFGR_CAN2CKS, u8CanClk);
    }
}

/**
 * @brief  I2S clock source config.
 * @param  [in] u8I2sCh specifies the I2S channel for clock source.
 *   @arg  CLK_I2S_CH1:  I2S Channel 1
 *   @arg  CLK_I2S_CH2:  I2S Channel 2
 *   @arg  CLK_I2S_CH3:  I2S Channel 3
 *   @arg  CLK_I2S_CH4:  I2S Channel 4
 * @param  [in] u16I2sClk specifies the I2S clock source.
 *   @arg  CLK_I2S1_CLK_PCLK:  Select PCLK3 as I2S clock
 *   @arg  CLK_I2S1_CLK_PLLHQ: Select PLLHQ as I2S clock
 *   @arg  CLK_I2S1_CLK_PLLHR: Select PLLHR as I2S clock
 *   @arg  CLK_I2S1_CLK_PLLAP: Select PLLAP as I2S clock
 *   @arg  CLK_I2S1_CLK_PLLAQ: Select PLLAQ as I2S clock
 *   @arg  CLK_I2S1_CLK_PLLAR: Select PLLAR as I2S clock
 *   @arg  CLK_I2S2_CLK_PCLK:  Select PCLK3 as I2S clock
 *   @arg  CLK_I2S2_CLK_PLLHQ: Select PLLHQ as I2S clock
 *   @arg  CLK_I2S2_CLK_PLLHR: Select PLLHR as I2S clock
 *   @arg  CLK_I2S2_CLK_PLLAP: Select PLLAP as I2S clock
 *   @arg  CLK_I2S2_CLK_PLLAQ: Select PLLAQ as I2S clock
 *   @arg  CLK_I2S2_CLK_PLLAR: Select PLLAR as I2S clock
 *   @arg  CLK_I2S3_CLK_PCLK:  Select PCLK3 as I2S clock
 *   @arg  CLK_I2S3_CLK_PLLHQ: Select PLLHQ as I2S clock
 *   @arg  CLK_I2S3_CLK_PLLHR: Select PLLHR as I2S clock
 *   @arg  CLK_I2S3_CLK_PLLAP: Select PLLAP as I2S clock
 *   @arg  CLK_I2S3_CLK_PLLAQ: Select PLLAQ as I2S clock
 *   @arg  CLK_I2S3_CLK_PLLAR: Select PLLAR as I2S clock
 *   @arg  CLK_I2S4_CLK_PCLK:  Select PCLK3 as I2S clock
 *   @arg  CLK_I2S4_CLK_PLLHQ: Select PLLHQ as I2S clock
 *   @arg  CLK_I2S4_CLK_PLLHR: Select PLLHR as I2S clock
 *   @arg  CLK_I2S4_CLK_PLLAP: Select PLLAP as I2S clock
 *   @arg  CLK_I2S4_CLK_PLLAQ: Select PLLAQ as I2S clock
 *   @arg  CLK_I2S4_CLK_PLLAR: Select PLLAR as I2S clock
 * @retval None
 */
void CLK_I2S_ClkConfig(uint8_t u8I2sCh, uint16_t u16I2sClk)
{
    DDL_ASSERT(IS_CLK_I2S_CH(u8I2sCh));
    DDL_ASSERT(IS_CLK_I2S_CLK(u16I2sClk));
    DDL_ASSERT(IS_CLK_SEL_UNLOCKED());

    if (0U != (CLK_I2S_CH1 & u8I2sCh))
    {
        MODIFY_REG16(M4_CMU->I2SCKSEL, CMU_I2SCKSEL_I2S1CKSEL, u16I2sClk);
    }
    if (0U != (CLK_I2S_CH2 & u8I2sCh))
    {
        MODIFY_REG16(M4_CMU->I2SCKSEL, CMU_I2SCKSEL_I2S2CKSEL, u16I2sClk);
    }
    if (0U != (CLK_I2S_CH3 & u8I2sCh))
    {
        MODIFY_REG16(M4_CMU->I2SCKSEL, CMU_I2SCKSEL_I2S3CKSEL, u16I2sClk);
    }
    if (0U != (CLK_I2S_CH4 & u8I2sCh))
    {
        MODIFY_REG16(M4_CMU->I2SCKSEL, CMU_I2SCKSEL_I2S4CKSEL, u16I2sClk);
    }
}

/**
 * @brief  ADC/DAC/TRNG clock source config.
 * @param  [in] u16Periclk specifies the ADC/DAC/TRNG clock source.
 *   @arg  CLK_PERI_CLK_PCLK:  Select default setting for PCLK2/PCLK4 clock
 *   @arg  CLK_PERI_CLK_PLLHQ: Select PLLHQ as PCLK2/PCLK4 clock
 *   @arg  CLK_PERI_CLK_PLLHR: Select PLLHR as PCLK2/PCLK4 clock
 *   @arg  CLK_PERI_CLK_PLLAP: Select PLLAP as PCLK2/PCLK4 clock
 *   @arg  CLK_PERI_CLK_PLLAQ: Select PLLAQ as PCLK2/PCLK4 clock
 *   @arg  CLK_PERI_CLK_PLLAR: Select PLLAR as PCLK2/PCLK4 clock
 * @retval None
 * @note   PCLK2 is used for ADC clock, PCLK4 is used for DAC/TRANG clock
 */
void CLK_PERI_ClkConfig(uint16_t u16Periclk)
{
    DDL_ASSERT(IS_CLK_PERI_CLK(u16Periclk));
    DDL_ASSERT(IS_CLK_SEL_UNLOCKED());

    WRITE_REG16(M4_CMU->PERICKSEL, u16Periclk);
}

/**
 * @brief  Enable or disable the TPIU clock.
 * @param  [in] enNewState specifies the new state of the TPIU clock.
 *   @arg Enable:   Enable clock output.
 *   @arg Disable:  Disable clock output.
 * @retval None
 */
void CLK_TpiuClkCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    WRITE_REG32(bM4_CMU->TPIUCKCFGR_b.TPIUCKOE, enNewState);
}

/**
 * @brief  TPIU clock divider config.
 * @param  [in] u8TpiuDiv specifies the TPIU clock divide factor.
 *   @arg  CLK_TPIU_CLK_DIV1: TPIU clock no divide
 *   @arg  CLK_TPIU_CLK_DIV2: TPIU clock divide by 2
 *   @arg  CLK_TPIU_CLK_DIV4: TPIU clock divide by 4
 * @retval None
 */
void CLK_TpiuClkConfig(uint8_t u8TpiuDiv)
{
    DDL_ASSERT(IS_CLK_TPIU_CLK_DIV(u8TpiuDiv));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    MODIFY_REG8(M4_CMU->TPIUCKCFGR, CMU_TPIUCKCFGR_TPIUCKS, u8TpiuDiv);
}

/**
 * @brief  Selects the clock source to output on MCO1 pin.
 * @param  [in] CLK_MCOSource specifies the clock source to output.
 *   @arg CLK_MCOSOURCCE_HRC       HRC clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_MRC       MRC clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_LRC       LRC clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_XTAL      XTAL clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_XTAL32    XTAL32 clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_PLLHP     PLLHP clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_PLLAP     PLLAP clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_PLLHQ     PLLHQ clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_PLLAQ     PLLAQ clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_PLLAR     PLLAR clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_SYSCLK    System clock selected as MCOx source
 * @param  [in] CLK_MCODiv specifies the MCOx prescaler.
 *   @arg CLK_MCO_DIV1:   no division applied to MCOx clock
 *   @arg CLK_MCO_DIV2:   division by 2 applied to MCOx clock
 *   @arg CLK_MCO_DIV4:   division by 4 applied to MCOx clock
 *   @arg CLK_MCO_DIV8:   division by 8 applied to MCOx clock
 *   @arg CLK_MCO_DIV16:  division by 16 applied to MCOx clock
 *   @arg CLK_MCO_DIV32:  division by 32 applied to MCOx clock
 *   @arg CLK_MCO_DIV64:  division by 64 applied to MCOx clock
 *   @arg CLK_MCO_DIV128: division by 128 applied to MCOx clock
 * @retval None
 * @note   MCO pin should be configured in alternate function 1 mode.
 */
void CLK_MCO1Config(uint8_t CLK_MCOSource, uint8_t CLK_MCODiv)
{
    /* Check the parameters. */
    DDL_ASSERT(IS_CLK_MCOSOURCE(CLK_MCOSource));
    DDL_ASSERT(IS_CLK_MCODIV(CLK_MCODiv));

    /* Enable register write. */
    DDL_ASSERT(IS_CLK_UNLOCKED());

    /* Config the MCO1 */
    MODIFY_REG8(M4_CMU->MCO1CFGR, (CMU_MCO1CFGR_MCO1SEL | CMU_MCO1CFGR_MCO1DIV), (CLK_MCODiv | CLK_MCOSource));
}

/**
 * @brief  Enable or disable the MCO1 output.
 * @param  [in] enNewState specifies the new state of the clock output.
 *   @arg Enable:   Enable clock output.
 *   @arg Disable:  Disable clock output.
 * @retval None
 */
void CLK_MCO1Cmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    /* Enable or disable clock output. */
    WRITE_REG32(bM4_CMU->MCO1CFGR_b.MCO1EN, enNewState);
}

/**
 * @brief  Selects the clock source to output on MCO2 pin.
 * @param  [in] CLK_MCOSource specifies the clock source to output.
 *   @arg CLK_MCOSOURCCE_HRC       HRC clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_MRC       MRC clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_LRC       LRC clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_XTAL      XTAL clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_XTAL32    XTAL32 clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_PLLHP     PLLHP clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_PLLAP     PLLAP clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_PLLHQ     PLLHQ clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_PLLAQ     PLLAQ clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_PLLAR     PLLAR clock selected as MCOx source
 *   @arg CLK_MCOSOURCCE_SYSCLK    System clock selected as MCOx source
 * @param  [in] CLK_MCODiv specifies the MCOx prescaler.
 *   @arg CLK_MCO_DIV1:   no division applied to MCOx clock
 *   @arg CLK_MCO_DIV2:   division by 2 applied to MCOx clock
 *   @arg CLK_MCO_DIV4:   division by 4 applied to MCOx clock
 *   @arg CLK_MCO_DIV8:   division by 8 applied to MCOx clock
 *   @arg CLK_MCO_DIV16:  division by 16 applied to MCOx clock
 *   @arg CLK_MCO_DIV32:  division by 32 applied to MCOx clock
 *   @arg CLK_MCO_DIV64:  division by 64 applied to MCOx clock
 *   @arg CLK_MCO_DIV128: division by 128 applied to MCOx clock
 * @retval None
 * @note   MCO2 pin should be configured in alternate function 1 mode.
 */
void CLK_MCO2Config(uint8_t CLK_MCOSource, uint8_t CLK_MCODiv)
{
    /* Check the parameters. */
    DDL_ASSERT(IS_CLK_MCOSOURCE(CLK_MCOSource));
    DDL_ASSERT(IS_CLK_MCODIV(CLK_MCODiv));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    /* Config the MCO */
    MODIFY_REG8(M4_CMU->MCO2CFGR, (CMU_MCO2CFGR_MCO2SEL | CMU_MCO2CFGR_MCO2DIV), (CLK_MCODiv | CLK_MCOSource));
}

/**
 * @brief  Enable or disable the MCO2 output.
 * @param  [in] enNewState specifies the new state of the clock output.
 *   @arg Enable:   Enable clock output.
 *   @arg Disable:  Disable clock output.
 * @retval None
 */
void CLK_MCO2Cmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_CLK_UNLOCKED());

    /* Enable or disable clock output. */
    WRITE_REG32(bM4_CMU->MCO2CFGR_b.MCO2EN, enNewState);
}

/**
 * @}
 */

#endif /* DDL_CLK_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
