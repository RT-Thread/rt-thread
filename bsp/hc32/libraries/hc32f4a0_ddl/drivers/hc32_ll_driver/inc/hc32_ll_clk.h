/**
 *******************************************************************************
 * @file  hc32_ll_clk.h
 * @brief This file contains all the functions prototypes of the CLK driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_CLK_H__
#define __HC32_LL_CLK_H__

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
 * @addtogroup LL_CLK
 * @{
 */

#if (LL_CLK_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup CLK_Global_Types CLK Global Types
 * @{
 */
/**
 * @brief  CLK XTAL configuration structure definition
 */
typedef struct {
    uint8_t u8State;        /*!< The new state of the XTAL.
                                This parameter can be a value of @ref CLK_XTAL_Config   */

    uint8_t u8Drv;          /*!< The XTAL drive ability.
                                This parameter can be a value of @ref CLK_XTAL_Config   */

    uint8_t u8Mode;         /*!< The XTAL mode selection osc or exclk.
                                This parameter can be a value of @ref CLK_XTAL_Config   */

    uint8_t u8StableTime;   /*!< The XTAL stable time selection.
                                This parameter can be a value of @ref CLK_XTAL_Config   */
} stc_clock_xtal_init_t;

/**
 * @brief  CLK XTAL fault detect configuration structure definition
 */
typedef struct {
    uint8_t u8State;   /*!< Specifies the new state of XTALSTD.
                                This parameter can be a value of @ref CLK_XTALSTD_Config    */

    uint8_t u8Mode;    /*!< Specifies the XTALSTD mode.
                                This parameter can be a value of @ref CLK_XTALSTD_Config    */

    uint8_t u8Int;     /*!< Specifies the XTALSTD interrupt on or off.
                                This parameter can be a value of @ref CLK_XTALSTD_Config    */

    uint8_t u8Reset;   /*!< Specifies the XTALSTD reset on or off.
                                This parameter can be a value of @ref CLK_XTALSTD_Config    */
} stc_clock_xtalstd_init_t;

/**
 * @brief  CLK XTAL32 configuration structure definition
 */
typedef struct {
    uint8_t u8State;        /*!< Xtal32 new state,
                                @ref CLK_XTAL32_Config for details */

    uint8_t u8Drv;          /*!< Xtal32 drive capacity setting,
                                @ref CLK_XTAL32_Config for details */

    uint8_t u8Filter;       /*!< Xtal32 noise filter setting,
                                @ref CLK_XTAL32_Config for details */
} stc_clock_xtal32_init_t;

/**
 * @brief  CLK clock frequency configuration structure definition
 */
typedef struct {
    union {
        uint32_t SCFGR;     /*!< clock frequency config register  */
        struct {
            uint32_t PCLK0S     : 3;    /*!< PCLK0      */
            uint32_t resvd0     : 1;    /*!< reserved   */
            uint32_t PCLK1S     : 3;    /*!< PCLK1      */
            uint32_t resvd1     : 1;    /*!< reserved   */
            uint32_t PCLK2S     : 3;    /*!< PCLK2      */
            uint32_t resvd2     : 1;    /*!< reserved   */
            uint32_t PCLK3S     : 3;    /*!< PCLK3      */
            uint32_t resvd3     : 1;    /*!< reserved   */
            uint32_t PCLK4S     : 3;    /*!< PCLK4      */
            uint32_t resvd4     : 1;    /*!< reserved   */
            uint32_t EXCKS      : 3;    /*!< EXCLK      */
            uint32_t resvd5     : 1;    /*!< reserved   */
            uint32_t HCLKS      : 3;    /*!< HCLK       */
            uint32_t resvd6     : 5;    /*!< reserved   */
        } SCFGR_f;
    };
} stc_clock_scale_t;

/**
 * @brief  CLK PLL configuration structure definition
 * @note   PLL for MPLL while HC32F460,HC32F451,HC32F452
 *         PLL for PLLH while HC32F4A0
 */
typedef struct {
    uint8_t u8PLLState;         /*!< PLL new state, @ref CLK_PLL_Config for details */
    union {
        uint32_t PLLCFGR;       /*!< PLL config register */
        struct {
            uint32_t PLLM   : 2; /*!< PLL M divide */
            uint32_t resvd0 : 5; /*!< reserved */
            uint32_t PLLSRC : 1; /*!< PLL/PLLA source clock select */
            uint32_t PLLN   : 8; /*! PLLH N multi- */
            uint32_t resvd1 : 4; /*! reserved */
            uint32_t PLLR   : 4; /*!< PLL R divide  */
            uint32_t PLLQ   : 4; /*!< PLL Q divide  */
            uint32_t PLLP   : 4; /*!< PLL P divide  */
        } PLLCFGR_f;
    };
} stc_clock_pll_init_t;

/**
 * @brief  CLK PLLx configuration structure definition
 * @note   PLLx for UPLL while HC32F460,HC32F451,HC32F452
 *         PLLx for PLLA while HC32F4A0
 */
typedef struct {
    uint8_t u8PLLState;          /*!< PLLx new state, @ref CLK_PLLx_State for details */
    union {
        uint32_t PLLCFGR;        /*!< PLLx config register */
        struct {
            uint32_t PLLM   : 5; /*!< PLLx M divide */
            uint32_t resvd0 : 3; /*!< reserved */
            uint32_t PLLN   : 9; /*!< PLLx N multi- */
            uint32_t resvd1 : 3; /*!< reserved */
            uint32_t PLLR   : 4; /*!< PLLx R divide */
            uint32_t PLLQ   : 4; /*!< PLLx Q divide */
            uint32_t PLLP   : 4; /*!< PLLx P divide */
        } PLLCFGR_f;
    };
}  stc_clock_pllx_init_t;

/**
 * @brief  CLK bus frequency structure definition
 */
typedef struct {
    uint32_t u32SysclkFreq;        /*!< System clock frequency. */
    uint32_t u32HclkFreq;          /*!< Hclk frequency.         */

    uint32_t u32Pclk1Freq;         /*!< Pclk1 frequency.        */
    uint32_t u32Pclk4Freq;         /*!< Pclk4 frequency.        */
    uint32_t u32Pclk3Freq;         /*!< Pclk3 frequency.        */
    uint32_t u32ExclkFreq;         /*!< Exclk frequency.        */
    uint32_t u32Pclk0Freq;         /*!< Pclk0 frequency.        */
    uint32_t u32Pclk2Freq;         /*!< Pclk2 frequency.        */
} stc_clock_freq_t;

/**
 * @brief  CLK PLL clock frequency structure definition
 */
typedef struct {
    uint32_t u32PllVcin;               /*!< PLL vcin clock frequency.      */
    uint32_t u32PllVco;                /*!< PLL vco clock frequency.       */
    uint32_t u32PllP;                  /*!< PLLp clock frequency.          */
    uint32_t u32PllQ;                  /*!< PLLq clock frequency.          */
    uint32_t u32PllR;                  /*!< PLLr clock frequency.          */
    uint32_t u32PllxVcin;              /*!< pllx vcin clock frequency.     */
    uint32_t u32PllxVco;               /*!< pllx vco clock frequency.      */
    uint32_t u32PllxP;                 /*!< pllxp clock frequency.         */
    uint32_t u32PllxQ;                 /*!< pllxq clock frequency.         */
    uint32_t u32PllxR;                 /*!< pllxr clock frequency.         */
} stc_pll_clock_freq_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CLK_Global_Macros CLK Global Macros
 * @{
 */
/**
 * @defgroup CLK_PLLx_State CLK PLLx State
 * @note   PLLx for UPLL while HC32F460,HC32F451,HC32F452
 *         PLLx for PLLA while HC32F4A0
 * @{
 */
#define CLK_PLLX_OFF                    (0x01U)
#define CLK_PLLX_ON                     (0x00U)
/**
 * @}
 */

/**
 * @defgroup CLK_PLL_Config PLL Config
 * @{
 */
/**
 * @brief PLL function config.
 */
#define CLK_PLL_OFF                     (0x01U)
#define CLK_PLL_ON                      (0x00U)

/**
 * @brief PLL/A source clock selection.
 */
#define CLK_PLL_SRC_XTAL                (0x00UL)
#define CLK_PLL_SRC_HRC                 (0x01UL)
/**
 * @}
 */

/**
 * @defgroup CLK_XTAL_Config XTAL Config
 * @{
 */
/**
 * @brief XTAL function config.
 */
#define CLK_XTAL_OFF                    (CMU_XTALCR_XTALSTP)
#define CLK_XTAL_ON                     (0x00U)

/**
 * @brief XTAL driver ability
 * @note    HC32F451/HC32F452  |                     |                               |
 * @note    HC32F4A0/HC32F460  |                     |                               |
 * @note    HC32F472           |  HC32M423/HC32M424  |  HC32M120/HC32F120/HC32F160   |
 *  High:       [20~25]        |       [20~24]       |           [20]                |
 *  Mid:        [16~20)        |       [16~20)       |         [10~20)               |
 *  Low:         (8~16)        |        (8~16)       |          (4~10)               |
 *  ULow:        [4~8]         |        [4~8]        |            [4]                |
 */
#define CLK_XTAL_DRV_HIGH               (0x00U << CMU_XTALCFGR_XTALDRV_POS)
#define CLK_XTAL_DRV_MID                (0x01U << CMU_XTALCFGR_XTALDRV_POS)
#define CLK_XTAL_DRV_LOW                (0x02U << CMU_XTALCFGR_XTALDRV_POS)
#define CLK_XTAL_DRV_ULOW               (0x03U << CMU_XTALCFGR_XTALDRV_POS)

/**
 * @brief XTAL mode selection osc or exclk
 */
#define CLK_XTAL_MD_OSC                 (0x00U)
#define CLK_XTAL_MD_EXCLK               (CMU_XTALCFGR_XTALMS)

/**
 * @brief XTAL stable time selection.
 * @note  a cycle of stable counter = a cycle of LRC divide by 8
 */
#define CLK_XTAL_STB_133US              (0x01U)       /*!< 35 stable count cycle, approx. 133us */
#define CLK_XTAL_STB_255US              (0x02U)       /*!< 67 stable count cycle, approx. 255us */
#define CLK_XTAL_STB_499US              (0x03U)       /*!< 131 stable count cycle, approx. 499us */
#define CLK_XTAL_STB_988US              (0x04U)       /*!< 259 stable count cycle, approx. 988us */
#define CLK_XTAL_STB_2MS                (0x05U)       /*!< 547 stable count cycle, approx. 2ms  */
#define CLK_XTAL_STB_4MS                (0x06U)       /*!< 1059 stable count cycle, approx. 4ms */
#define CLK_XTAL_STB_8MS                (0x07U)       /*!< 2147 stable count cycle, approx. 8ms */
#define CLK_XTAL_STB_16MS               (0x08U)       /*!< 4291 stable count cycle, approx. 16ms */
#define CLK_XTAL_STB_31MS               (0x09U)       /*!< 8163 stable count cycle, approx. 32ms */

/**
 * @}
 */

/**
 * @defgroup CLK_XTALSTD_Config XTALSTD Config
 * @{
 */

/**
 * @brief XTAL error detection on or off
 */
#define CLK_XTALSTD_OFF                 (0x00U)
#define CLK_XTALSTD_ON                  (CMU_XTALSTDCR_XTALSTDE)

/**
 * @brief XTALSTD mode selection
 */
#define CLK_XTALSTD_MD_RST              (CMU_XTALSTDCR_XTALSTDRIS)
#define CLK_XTALSTD_MD_INT              (0x00U)

/**
 * @brief XTALSTD reset on or off
 */
#define CLK_XTALSTD_RST_OFF             (0x00U)
#define CLK_XTALSTD_RST_ON              (CMU_XTALSTDCR_XTALSTDRE)

/**
 * @brief XTALSTD interrupt on or off
 */
#define CLK_XTALSTD_INT_OFF             (0x00U)
#define CLK_XTALSTD_INT_ON              (CMU_XTALSTDCR_XTALSTDIE)
/**
 * @}
 */

/**
 * @defgroup CLK_XTAL32_Config XTAL32 Config
 * @{
 */
/**
 * @brief XTAL32 function config.
 */
#define CLK_XTAL32_OFF                  (CMU_XTAL32CR_XTAL32STP)
#define CLK_XTAL32_ON                   (0x00U)

/**
 * @brief XTAL32 driver ability.
 */
#define CLK_XTAL32_DRV_MID              (0x00U)
#define CLK_XTAL32_DRV_HIGH             (0x01U)

/**
 * @brief XTAL32 filtering selection.
 */
#define CLK_XTAL32_FILTER_ALL_MD        (0x00U)   /*!< Valid in run,stop,power down mode.     */
#define CLK_XTAL32_FILTER_RUN_MD        (0x01U)   /*!< Valid in run mode.                     */
#define CLK_XTAL32_FILTER_OFF           (0x03U)   /*!< Invalid in run,stop,power down mode.   */
/**
 * @}
 */

/**
 * @defgroup CLK_HRC_Config HRC Config
 * @{
 */
#define CLK_HRC_OFF                     (CMU_HRCCR_HRCSTP)
#define CLK_HRC_ON                      (0x00U)
/**
 * @}
 */

/**
 * @defgroup CLK_HrcFreq_Sel Hrc Freqency Selection
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup CLK_STB_Flag CLK Stable Flags
 * @{
 */
#define CLK_STB_FLAG_HRC                (CMU_OSCSTBSR_HRCSTBF)
#define CLK_STB_FLAG_XTAL               (CMU_OSCSTBSR_XTALSTBF)
#define CLK_STB_FLAG_PLL                (CMU_OSCSTBSR_PLLHSTBF)
#define CLK_STB_FLAG_PLLX               (CMU_OSCSTBSR_PLLASTBF)
#define CLK_STB_FLAG_MASK               (CMU_OSCSTBSR_HRCSTBF | CMU_OSCSTBSR_XTALSTBF | \
                                        CMU_OSCSTBSR_PLLASTBF | CMU_OSCSTBSR_PLLHSTBF)

/**
 * @}
 */

/**
 * @defgroup CLK_System_Clock_Source System Clock Source
 * @{
 */
#define CLK_SYSCLK_SRC_HRC              (0x00U)
#define CLK_SYSCLK_SRC_MRC              (0x01U)
#define CLK_SYSCLK_SRC_LRC              (0x02U)
#define CLK_SYSCLK_SRC_XTAL             (0x03U)
#define CLK_SYSCLK_SRC_XTAL32           (0x04U)
#define CLK_SYSCLK_SRC_PLL              (0x05U)

/**
 * @}
 */

/**
 * @defgroup CLK_Bus_Clock_Sel Clock Bus Clock Category Selection
 * @{
 */
#define CLK_BUS_PCLK0                   (CMU_SCFGR_PCLK0S)
#define CLK_BUS_PCLK1                   (CMU_SCFGR_PCLK1S)
#define CLK_BUS_PCLK2                   (CMU_SCFGR_PCLK2S)
#define CLK_BUS_PCLK3                   (CMU_SCFGR_PCLK3S)
#define CLK_BUS_PCLK4                   (CMU_SCFGR_PCLK4S)
#define CLK_BUS_EXCLK                   (CMU_SCFGR_EXCKS)
#define CLK_BUS_HCLK                    (CMU_SCFGR_HCLKS)
#define CLK_BUS_CLK_ALL                 (CLK_BUS_PCLK0 | CLK_BUS_PCLK1 | CLK_BUS_PCLK2 | CLK_BUS_PCLK3 | \
                                         CLK_BUS_PCLK4 | CLK_BUS_EXCLK | CLK_BUS_HCLK)

/**
 * @}
 */

/**
 * @defgroup CLK_Clock_Divider Clock Divider
 * @{
 */

/**
 * @defgroup CLK_System_Clock_Divider System Clock Divider
 * @{
 */
#define CLK_SYSCLK_DIV1                 (0x00U)
#define CLK_SYSCLK_DIV2                 (0x01U)
#define CLK_SYSCLK_DIV4                 (0x02U)
#define CLK_SYSCLK_DIV8                 (0x03U)
#define CLK_SYSCLK_DIV16                (0x04U)
#define CLK_SYSCLK_DIV32                (0x05U)
#define CLK_SYSCLK_DIV64                (0x06U)
/**
 * @}
 */

/**
 * @defgroup CLK_HCLK_Divider CLK HCLK Divider
 * @{
 */
#define CLK_HCLK_DIV1                   (CLK_SYSCLK_DIV1  << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV2                   (CLK_SYSCLK_DIV2  << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV4                   (CLK_SYSCLK_DIV4  << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV8                   (CLK_SYSCLK_DIV8  << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV16                  (CLK_SYSCLK_DIV16 << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV32                  (CLK_SYSCLK_DIV32 << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV64                  (CLK_SYSCLK_DIV64 << CMU_SCFGR_HCLKS_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_PCLK1_Divider CLK PCLK1 Divider
 * @{
 */
#define CLK_PCLK1_DIV1                  (CLK_SYSCLK_DIV1  << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV2                  (CLK_SYSCLK_DIV2  << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV4                  (CLK_SYSCLK_DIV4  << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV8                  (CLK_SYSCLK_DIV8  << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV16                 (CLK_SYSCLK_DIV16 << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV32                 (CLK_SYSCLK_DIV32 << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV64                 (CLK_SYSCLK_DIV64 << CMU_SCFGR_PCLK1S_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_PCLK4_Divider CLK PCLK4 Divider
 * @{
 */
#define CLK_PCLK4_DIV1                  (CLK_SYSCLK_DIV1  << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV2                  (CLK_SYSCLK_DIV2  << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV4                  (CLK_SYSCLK_DIV4  << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV8                  (CLK_SYSCLK_DIV8  << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV16                 (CLK_SYSCLK_DIV16 << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV32                 (CLK_SYSCLK_DIV32 << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV64                 (CLK_SYSCLK_DIV64 << CMU_SCFGR_PCLK4S_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_PCLK3_Divider CLK PCLK3 Divider
 * @{
 */
#define CLK_PCLK3_DIV1                  (CLK_SYSCLK_DIV1  << CMU_SCFGR_PCLK3S_POS)
#define CLK_PCLK3_DIV2                  (CLK_SYSCLK_DIV2  << CMU_SCFGR_PCLK3S_POS)
#define CLK_PCLK3_DIV4                  (CLK_SYSCLK_DIV4  << CMU_SCFGR_PCLK3S_POS)
#define CLK_PCLK3_DIV8                  (CLK_SYSCLK_DIV8  << CMU_SCFGR_PCLK3S_POS)
#define CLK_PCLK3_DIV16                 (CLK_SYSCLK_DIV16 << CMU_SCFGR_PCLK3S_POS)
#define CLK_PCLK3_DIV32                 (CLK_SYSCLK_DIV32 << CMU_SCFGR_PCLK3S_POS)
#define CLK_PCLK3_DIV64                 (CLK_SYSCLK_DIV64 << CMU_SCFGR_PCLK3S_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_EXCLK_Divider CLK EXCLK Divider
 * @{
 */
#define CLK_EXCLK_DIV1                  (CLK_SYSCLK_DIV1  << CMU_SCFGR_EXCKS_POS)
#define CLK_EXCLK_DIV2                  (CLK_SYSCLK_DIV2  << CMU_SCFGR_EXCKS_POS)
#define CLK_EXCLK_DIV4                  (CLK_SYSCLK_DIV4  << CMU_SCFGR_EXCKS_POS)
#define CLK_EXCLK_DIV8                  (CLK_SYSCLK_DIV8  << CMU_SCFGR_EXCKS_POS)
#define CLK_EXCLK_DIV16                 (CLK_SYSCLK_DIV16 << CMU_SCFGR_EXCKS_POS)
#define CLK_EXCLK_DIV32                 (CLK_SYSCLK_DIV32 << CMU_SCFGR_EXCKS_POS)
#define CLK_EXCLK_DIV64                 (CLK_SYSCLK_DIV64 << CMU_SCFGR_EXCKS_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_PCLK2_Divider CLK PCLK2 Divider
 * @{
 */
#define CLK_PCLK2_DIV1                  (CLK_SYSCLK_DIV1  << CMU_SCFGR_PCLK2S_POS)
#define CLK_PCLK2_DIV2                  (CLK_SYSCLK_DIV2  << CMU_SCFGR_PCLK2S_POS)
#define CLK_PCLK2_DIV4                  (CLK_SYSCLK_DIV4  << CMU_SCFGR_PCLK2S_POS)
#define CLK_PCLK2_DIV8                  (CLK_SYSCLK_DIV8  << CMU_SCFGR_PCLK2S_POS)
#define CLK_PCLK2_DIV16                 (CLK_SYSCLK_DIV16 << CMU_SCFGR_PCLK2S_POS)
#define CLK_PCLK2_DIV32                 (CLK_SYSCLK_DIV32 << CMU_SCFGR_PCLK2S_POS)
#define CLK_PCLK2_DIV64                 (CLK_SYSCLK_DIV64 << CMU_SCFGR_PCLK2S_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_PCLK0_Divider CLK PCLK0 Divider
 * @{
 */
#define CLK_PCLK0_DIV1                  (CLK_SYSCLK_DIV1  << CMU_SCFGR_PCLK0S_POS)
#define CLK_PCLK0_DIV2                  (CLK_SYSCLK_DIV2  << CMU_SCFGR_PCLK0S_POS)
#define CLK_PCLK0_DIV4                  (CLK_SYSCLK_DIV4  << CMU_SCFGR_PCLK0S_POS)
#define CLK_PCLK0_DIV8                  (CLK_SYSCLK_DIV8  << CMU_SCFGR_PCLK0S_POS)
#define CLK_PCLK0_DIV16                 (CLK_SYSCLK_DIV16 << CMU_SCFGR_PCLK0S_POS)
#define CLK_PCLK0_DIV32                 (CLK_SYSCLK_DIV32 << CMU_SCFGR_PCLK0S_POS)
#define CLK_PCLK0_DIV64                 (CLK_SYSCLK_DIV64 << CMU_SCFGR_PCLK0S_POS)
/**
 * @}
 */
/**
 * @}
 */

/**
 * @defgroup CLK_USBCLK_Sel CLK USB Clock Selection
 * @{
 */
#define CLK_USBCLK_SYSCLK_DIV2         (0x01U << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USBCLK_SYSCLK_DIV3         (0x02U << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USBCLK_SYSCLK_DIV4         (0x03U << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USBCLK_SYSCLK_DIV5         (0x04U << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USBCLK_SYSCLK_DIV6         (0x05U << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USBCLK_SYSCLK_DIV7         (0x06U << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USBCLK_SYSCLK_DIV8         (0x07U << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USBCLK_PLLQ                (0x08U << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USBCLK_PLLR                (0x09U << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USBCLK_PLLXP               (0x0AU << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USBCLK_PLLXQ               (0x0BU << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USBCLK_PLLXR               (0x0CU << CMU_USBCKCFGR_USBCKS_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_CANCLK_Sel CLK CAN Clock Selection
 * @{
 */
#define CLK_CANCLK_SYSCLK_DIV2         (0x01U)
#define CLK_CANCLK_SYSCLK_DIV3         (0x02U)
#define CLK_CANCLK_SYSCLK_DIV4         (0x03U)
#define CLK_CANCLK_SYSCLK_DIV5         (0x04U)
#define CLK_CANCLK_SYSCLK_DIV6         (0x05U)
#define CLK_CANCLK_SYSCLK_DIV7         (0x06U)
#define CLK_CANCLK_SYSCLK_DIV8         (0x07U)
#define CLK_CANCLK_PLLQ                (0x08U)
#define CLK_CANCLK_PLLR                (0x09U)
#define CLK_CANCLK_PLLXP               (0x0AU)
#define CLK_CANCLK_PLLXQ               (0x0BU)
#define CLK_CANCLK_PLLXR               (0x0CU)
#define CLK_CANCLK_XTAL                (0x0DU)
/**
 * @}
 */

/**
 * @defgroup CLK_CAN_Sel CLK CAN Channel Selection
 * @{
 */
#define CLK_CAN1                        (0x01U)
#define CLK_CAN2                        (0x02U)
/**
 * @}
 */

/**
 * @defgroup CLK_PERIPH_Sel CLK Peripheral Clock Selection
 * @note    ADC,I2S,DAC,TRANG
 * @{
 */
#define CLK_PERIPHCLK_PCLK               (0x0000U)   /*  PCLK2 is used for ADC clock, \
                                                    PCLK1 is used for I2S clock, \
                                                    PCLK4 is used for DAC/TRANG clock */
#define CLK_PERIPHCLK_PLLQ               (0x0008U)
#define CLK_PERIPHCLK_PLLR               (0x0009U)
#define CLK_PERIPHCLK_PLLXP              (0x000AU)
#define CLK_PERIPHCLK_PLLXQ              (0x000BU)
#define CLK_PERIPHCLK_PLLXR              (0x000CU)

/**
 * @}
 */

/**
 * @defgroup CLK_I2S_Sel CLK I2S Channel Selection
 * @{
 */
#define CLK_I2S1                        (0x00U)
#define CLK_I2S2                        (0x01U)
#define CLK_I2S3                        (0x02U)
#define CLK_I2S4                        (0x03U)
/**
 * @}
 */

/**
 * @defgroup CLK_TPIU_Divider TPIU clock divider
 * @{
 */
#define CLK_TPIUCLK_DIV1               (0x00U)
#define CLK_TPIUCLK_DIV2               (0x01U)
#define CLK_TPIUCLK_DIV4               (0x02U)
/**
 * @}
 */

/**
 * @defgroup CLK_MCO_Channel_Sel CLK MCO Channel Select
 * @{
 */
#define CLK_MCO1                        (0x00U)
#define CLK_MCO2                        (0x01U)
/**
 * @}
 */

/**
 * @defgroup CLK_MCO_Clock_Source CLK MCO Clock Source
 * @{
 */
#define CLK_MCO_SRC_HRC                 (0x00U)
#define CLK_MCO_SRC_MRC                 (0x01U)
#define CLK_MCO_SRC_LRC                 (0x02U)
#define CLK_MCO_SRC_XTAL                (0x03U)
#define CLK_MCO_SRC_XTAL32              (0x04U)
#define CLK_MCO_SRC_PLLP                (0x06U)
#define CLK_MCO_SRC_PLLXP               (0x07U)
#define CLK_MCO_SRC_PLLQ                (0x08U)
#define CLK_MCO_SRC_PLLXQ               (0x09U)
#define CLK_MCO_SRC_PLLXR               (0x0AU)
#define CLK_MCO_SRC_HCLK                (0x0BU)

/**
 * @}
 */

/**
 * @defgroup CLK_MCO_Clock_Prescaler CLK MCO Clock Prescaler
 * @{
 */
#define CLK_MCO_DIV1                    (0x00U << CMU_MCOCFGR_MCODIV_POS)
#define CLK_MCO_DIV2                    (0x01U << CMU_MCOCFGR_MCODIV_POS)
#define CLK_MCO_DIV4                    (0x02U << CMU_MCOCFGR_MCODIV_POS)
#define CLK_MCO_DIV8                    (0x03U << CMU_MCOCFGR_MCODIV_POS)
#define CLK_MCO_DIV16                   (0x04U << CMU_MCOCFGR_MCODIV_POS)
#define CLK_MCO_DIV32                   (0x05U << CMU_MCOCFGR_MCODIV_POS)
#define CLK_MCO_DIV64                   (0x06U << CMU_MCOCFGR_MCODIV_POS)
#define CLK_MCO_DIV128                  (0x07U << CMU_MCOCFGR_MCODIV_POS)
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
 * @addtogroup CLK_Global_Functions
 * @{
 */

int32_t CLK_HrcCmd(en_functional_state_t enNewState);

int32_t CLK_MrcCmd(en_functional_state_t enNewState);

int32_t CLK_LrcCmd(en_functional_state_t enNewState);

void CLK_HrcTrim(int8_t i8TrimVal);
void CLK_MrcTrim(int8_t i8TrimVal);
void CLK_LrcTrim(int8_t i8TrimVal);
void CLK_RtcLrcTrim(int8_t i8TrimVal);

int32_t CLK_XtalStructInit(stc_clock_xtal_init_t *pstcXtalInit);
int32_t CLK_XtalInit(const stc_clock_xtal_init_t *pstcXtalInit);
int32_t CLK_XtalCmd(en_functional_state_t enNewState);

int32_t CLK_XtalStdStructInit(stc_clock_xtalstd_init_t *pstcXtalStdInit);
int32_t CLK_XtalStdInit(const stc_clock_xtalstd_init_t *pstcXtalStdInit);
void CLK_ClearXtalStdStatus(void);
en_flag_status_t CLK_GetXtalStdStatus(void);

int32_t CLK_Xtal32StructInit(stc_clock_xtal32_init_t *pstcXtal32Init);
int32_t CLK_Xtal32Init(const stc_clock_xtal32_init_t *pstcXtal32Init);
int32_t CLK_Xtal32Cmd(en_functional_state_t enNewState);

void CLK_Xtal32InputCmd(en_functional_state_t enNewState);

void CLK_SetPLLSrc(uint32_t u32PllSrc);
int32_t CLK_PLLStructInit(stc_clock_pll_init_t *pstcPLLInit);
int32_t CLK_PLLInit(const stc_clock_pll_init_t *pstcPLLInit);
int32_t CLK_PLLCmd(en_functional_state_t enNewState);
int32_t CLK_GetPLLClockFreq(stc_pll_clock_freq_t *pstcPllClkFreq);

int32_t CLK_PLLxStructInit(stc_clock_pllx_init_t *pstcPLLxInit);
int32_t CLK_PLLxInit(const stc_clock_pllx_init_t *pstcPLLxInit);
int32_t CLK_PLLxCmd(en_functional_state_t enNewState);

void CLK_MCOConfig(uint8_t u8Ch, uint8_t u8Src, uint8_t u8Div);
void CLK_MCOCmd(uint8_t u8Ch, en_functional_state_t enNewState);

en_flag_status_t CLK_GetStableStatus(uint8_t u8Flag);

void CLK_SetSysClockSrc(uint8_t u8Src);
void CLK_SetClockDiv(uint32_t u32Clock, uint32_t u32Div);
int32_t CLK_GetClockFreq(stc_clock_freq_t *pstcClockFreq);
uint32_t CLK_GetBusClockFreq(uint32_t u32Clock);

void CLK_SetPeriClockSrc(uint16_t u16Src);

void CLK_SetUSBClockSrc(uint8_t u8Src);
void CLK_SetI2SClockSrc(uint8_t u8Unit, uint8_t u8Src);

void CLK_SetCANClockSrc(uint8_t u8Unit, uint8_t u8Src);

void CLK_TpiuClockCmd(en_functional_state_t enNewState);
void CLK_SetTpiuClockDiv(uint8_t u8Div);

/**
 * @}
 */

#endif /* LL_CLK_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_CLK_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
