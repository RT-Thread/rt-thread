/**
 *******************************************************************************
 * @file  hc32f4a0_clk.h
 * @brief This file contains all the functions prototypes of the CLK driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Zhangxl         First version
   2020-07-03       Zhangxl         _DIV64 definition for BUS clock division
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
#ifndef __HC32F4A0_CLK_H__
#define __HC32F4A0_CLK_H__

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
 * @addtogroup DDL_CLK
 * @{
 */

#if (DDL_CLK_ENABLE == DDL_ON)

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
typedef struct
{
    uint8_t u8XtalState;      /*!< The new state of the XTAL.
                                This parameter can be a value of @ref CLK_XTAL_Config   */

    uint8_t u8XtalDrv;        /*!< The XTAL drive ability.
                                This parameter can be a value of @ref CLK_XTAL_Config   */

    uint8_t u8XtalMode;       /*!< The XTAL mode selection osc or exclk.
                                This parameter can be a value of @ref CLK_XTAL_Config   */

    uint8_t u8XtalStb;        /*!< The XTAL stable time selection.
                                This parameter can be a value of @ref CLK_XTAL_Config   */
} stc_clk_xtal_init_t;

/**
 * @brief  CLK XTALSTD configuration structure definition
 */
typedef struct
{
    uint8_t u8XtalStdState;   /*!< Specifies the new state of XTALSTD.
                                This parameter can be a value of @ref CLK_XTALSTD_Config    */

    uint8_t u8XtalStdMode;    /*!< Specifies the XTALSTD mode.
                                This parameter can be a value of @ref CLK_XTALSTD_Config    */

    uint8_t u8XtalStdInt;     /*!< Specifies the XTALSTD interrupt on or off.
                                This parameter can be a value of @ref CLK_XTALSTD_Config    */

    uint8_t u8XtalStdRst;     /*!< Specifies the XTALSTD reset on or off.
                                This parameter can be a value of @ref CLK_XTALSTD_Config    */
} stc_clk_xtalstd_init_t;

/**
 * @brief  CLK XTAL32 configuration structure definition
 */
typedef struct
{
    uint8_t u8Xtal32State;      /*!< Xtal32 new state,
                                    @ref CLK_XTAL32_Config for details */

    uint8_t u8Xtal32Drv;        /*!< Xtal32 drive capacity setting,
                                    @ref CLK_XTAL32_Config for details */

    uint8_t u8Xtal32NF;         /*!< Xtal32 noise filter setting,
                                    @ref CLK_XTAL32_Config for details */
} stc_clk_xtal32_init_t;

/**
 * @brief  CLK PLLH configuration structure definition
 */
typedef struct
{
    uint8_t u8PLLState;         /*!< PLLH new state,
                                    @ref CLK_PLLH_Config for details */
    union
    {
        uint32_t PLLCFGR;       /* PLLH config register */
        struct
        {
            uint32_t PLLM   :2; /*! PLLH M divide */
            uint32_t resvd0 :5; /*! reserved */
            uint32_t PLLSRC :1; /*! PLLH/PLLA source clock select */
            uint32_t PLLN   :8; /*! PLLH N multi- */
            uint32_t resvd1 :4; /*! reserved */
            uint32_t PLLR   :4; /*! PLLH R divide */
            uint32_t PLLQ   :4; /*! PLLH Q divide */
            uint32_t PLLP   :4; /*! PLLH P divide */
        } PLLCFGR_f;
    };
} stc_clk_pllh_init_t;

/**
 * @brief  CLK PLLA configuration structure definition
 */
typedef struct
{
    uint8_t u8PLLState;         /*!< PLLA new state,
                                    @ref CLK_PLLA_Config for details */
    union
    {
        uint32_t PLLCFGR;       /* PLLA config register */
        struct
        {
            uint32_t PLLM   :5; /*!< PLLA M divide */
            uint32_t resvd0 :3; /*! reserved */
            uint32_t PLLN   :9; /*!< PLLA N multi- */
            uint32_t resvd1 :3; /*!< reserved */
            uint32_t PLLR   :4; /*!< PLLA R divide */
            uint32_t PLLQ   :4; /*!< PLLA Q divide */
            uint32_t PLLP   :4; /*!< PLLA P divide */
        } PLLCFGR_f;
    };
} stc_clk_plla_init_t;

/**
 * @brief  CLK bus frequency structure definition
 */
typedef struct
{
    uint32_t sysclkFreq;        /*!< System clock frequency. */
    uint32_t hclkFreq;          /*!< Hclk frequency. */
    uint32_t exckFreq;          /*!< Exclk frequency. */
    uint32_t pclk0Freq;         /*!< Pclk0 frequency. */
    uint32_t pclk1Freq;         /*!< Pclk1 frequency. */
    uint32_t pclk2Freq;         /*!< Pclk2 frequency. */
    uint32_t pclk3Freq;         /*!< Pclk3 frequency. */
    uint32_t pclk4Freq;         /*!< Pclk4 frequency. */
} stc_clk_freq_t;

/**
 * @brief  CLK PLL clock frequency structure definition
 */
typedef struct
{
    uint32_t pllhvcin;              /*!< pllh vcin clock frequency. */
    uint32_t pllhvco;               /*!< pllh vco clock frequency. */
    uint32_t pllhp;                 /*!< pllhp clock frequency. */
    uint32_t pllhq;                 /*!< pllhq clock frequency. */
    uint32_t pllhr;                 /*!< pllhr clock frequency. */
    uint32_t pllavcin;              /*!< plla vcin clock frequency. */
    uint32_t pllavco;               /*!< plla vco clock frequency. */
    uint32_t pllap;                 /*!< pllap clock frequency. */
    uint32_t pllaq;                 /*!< pllaq clock frequency. */
    uint32_t pllar;                 /*!< pllar clock frequency. */
} stc_pll_clk_freq_t;

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
 * @defgroup CLK_PLLH_FREQ PLLH P/Q/R frequency range definition
 * @{
 */
#define CLK_PLLH_FREQ_MIN           (40UL*1000UL*1000UL)
#define CLK_PLLH_FREQ_MAX           (240UL*1000UL*1000UL)
/**
 * @}
 */

/**
 * @defgroup CLK_PLLH_VCO_IN PLLH VCO in frequency range definition
 * @{
 */
#define CLK_PLLH_VCO_IN_MIN         (8UL*1000UL*1000UL)
#define CLK_PLLH_VCO_IN_MAX         (24UL*1000UL*1000UL)
/**
 * @}
 */

/**
 * @defgroup CLK_PLLH_VCO_OUT PLLH VCO out frequency range definition
 * @{
 */
#define CLK_PLLH_VCO_OUT_MIN        (600UL*1000UL*1000UL)
#define CLK_PLLH_VCO_OUT_MAX        (1200UL*1000UL*1000UL)
/**
 * @}
 */

/**
 * @defgroup CLK_PLLHM_Div_Sel PLLH M divide range definition
 * @{
 */
#define CLK_PLLHM_DIV_MIN           (1UL)
#define CLK_PLLHM_DIV_MAX           (4UL)
/**
 * @}
 */

/**
 * @defgroup CLK_PLLHN_Div_Sel PLLH N multi- range definition
 * @{
 */
#define CLK_PLLHN_MULTI_MIN         (25UL)
#define CLK_PLLHN_MULTI_MAX         (150UL)
/**
 * @}
 */

/**
 * @defgroup CLK_PLLHR_Div_Sel PLLH R divide range definition
 * @{
 */
#define CLK_PLLHR_DIV_MIN           (2UL)
#define CLK_PLLHR_DIV_MAX           (16UL)
/**
 * @}
 */

/**
 * @defgroup CLK_PLLHQ_Div_Sel PLLH Q divide range definition
 * @{
 */
#define CLK_PLLHQ_DIV_MIN           (2UL)
#define CLK_PLLHQ_DIV_MAX           (16UL)
/**
 * @}
 */

/**
 * @defgroup CLK_PLLHP_Div_Sel PLLH P divide range definition
 * @{
 */
#define CLK_PLLHP_DIV_MIN           (2UL)
#define CLK_PLLHP_DIV_MAX           (16UL)
/**
 * @}
 */

/**
 * @defgroup CLK_PLLA_FREQ PLLA P/Q/R frequency range definition
 * @{
 */
#define CLK_PLLA_FREQ_MIN           (15UL*1000UL*1000UL)
#define CLK_PLLA_FREQ_MAX           (240UL*1000UL*1000UL)
/**
 * @}
 */

/**
 * @defgroup CLK_PLLA_VCO_IN PLLA VCO in frequency range definition
 * @{
 */
#define CLK_PLLA_VCO_IN_MIN         (1UL*1000UL*1000UL)
#define CLK_PLLA_VCO_IN_MAX         (24UL*1000UL*1000UL)
/**
 * @}
 */

/**
 * @defgroup CLK_PLLA_VCO_OUT PLLA VCO out frequency range definition
 * @{
 */
#define CLK_PLLA_VCO_OUT_MIN        (240UL*1000UL*1000UL)
#define CLK_PLLA_VCO_OUT_MAX        (480UL*1000UL*1000UL)
/**
 * @}
 */

/**
 * @defgroup CLK_PLLAM_Div_Sel PLLA M divide range definition
 * @{
 */
#define CLK_PLLAM_DIV_MIN           (1UL)
#define CLK_PLLAM_DIV_MAX           (24UL)
/**
 * @}
 */

/**
 * @defgroup CLK_PLLAN_Div_Sel PLLA N multi- range definition
 * @{
 */
#define CLK_PLLAN_MULTI_MIN         (20UL)
#define CLK_PLLAN_MULTI_MAX         (480UL)
/**
 * @}
 */

/**
 * @defgroup CLK_PLLAR_Div_Sel PLLA R divide range definition
 * @{
 */
#define CLK_PLLAR_DIV_MIN           (2UL)
#define CLK_PLLAR_DIV_MAX           (16UL)
/**
 * @}
 */

/**
 * @defgroup CLK_PLLAQ_Div_Sel PLLA Q divide range definition
 * @{
 */
#define CLK_PLLAQ_DIV_MIN           (2UL)
#define CLK_PLLAQ_DIV_MAX           (16UL)
/**
 * @}
 */

/**
 * @defgroup CLK_PLLAP_Div_Sel PLLA P divide range definition
 * @{
 */
#define CLK_PLLAP_DIV_MIN           (2UL)
#define CLK_PLLAP_DIV_MAX           (16UL)
/**
 * @}
 */

/**
 * @defgroup CLK_Switch_Config Congigureation for system clock switching
 * @{
 */
/**
 * @brief Stable waiting time while switching system clock.
 * @note Approx. 1us based on 168M frequency.
 */
#define CLK_SYSCLK_SW_STABLE        (0xB0UL)

/**
 * @brief FCGx default value.
 */
#define CLK_FCG0_DEFAULT            (0xFFFFFA0EUL)
#define CLK_FCG1_DEFAULT            (0xFFFFFFFFUL)
#define CLK_FCG2_DEFAULT            (0xFFFFFFFFUL)
#define CLK_FCG3_DEFAULT            (0xFFFFFFFFUL)
/**
 * @}
 */

/**
 * @defgroup CLK_PLLA_Config PLLA Config
 * @{
 */
/**
 * @brief PLLH function config.
 */
#define CLK_PLLA_OFF                (CMU_PLLACR_PLLAOFF)
#define CLK_PLLA_ON                 (0x00U)

/**
 * @brief PLLH default config.
 */
#define CLK_PLLAP_DFT               (0x01UL)
#define CLK_PLLAQ_DFT               (0x01UL)
#define CLK_PLLAR_DFT               (0x01UL)
#define CLK_PLLAN_DFT               (0x13UL)
#define CLK_PLLAM_DFT               (0x01UL)
/**
 * @}
 */

/**
 * @defgroup CLK_PLLH_Config PLLH Config
 * @{
 */
/**
 * @brief PLLH function config.
 */
#define CLK_PLLH_OFF                (CMU_PLLHCR_PLLHOFF)
#define CLK_PLLH_ON                 (0x00U)

/**
 * @brief PLLH default config.
 */
#define CLK_PLLHP_DFT               (0x01UL)
#define CLK_PLLHQ_DFT               (0x01UL)
#define CLK_PLLHR_DFT               (0x01UL)
#define CLK_PLLHN_DFT               (0x13UL)
#define CLK_PLLHM_DFT               (0x01UL)

/**
 * @brief PLLH/A source clock selction.
 */
#define CLK_PLLSRC_XTAL             (0x00UL)
#define CLK_PLLSRC_HRC              (0x01UL)
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
#define CLK_XTAL_OFF                (CMU_XTALCR_XTALSTP)
#define CLK_XTAL_ON                 (0x00U)

/**
 * @brief XTAL driver ability
 * @note  High: 20 ~ 24MHz, Mid: 16~20MHz, Low: 8~16MHz, ULow 4 ~ 8MHz.
 */
#define CLK_XTALDRV_HIGH            (0x00U)
#define CLK_XTALDRV_MID             (0x01U)
#define CLK_XTALDRV_LOW             (0x02U)
#define CLK_XTALDRV_ULOW            (0x03U)

/**
 * @brief XTAL mode selection osc or exclk
 */
#define CLK_XTALMODE_OSC            (0x00U)
#define CLK_XTALMODE_EXCLK          (0x01U)

/**
 * @brief XTAL stable time selection.
 * @note  a cycle of stable counter = a cycle of LRC divide by 8
 */
#define CLK_XTALSTB_133US           (0x01U)       /*!< 35 stable count cycle, approx. 133us */
#define CLK_XTALSTB_255US           (0x02U)       /*!< 67 stable count cycle, approx. 255us */
#define CLK_XTALSTB_499US           (0x03U)       /*!< 131 stable count cycle, approx. 499us */
#define CLK_XTALSTB_988US           (0x04U)       /*!< 259 stable count cycle, approx. 988us */
#define CLK_XTALSTB_2MS             (0x05U)       /*!< 547 stable count cycle, approx. 2ms  */
#define CLK_XTALSTB_4MS             (0x06U)       /*!< 1059 stable count cycle, approx. 4ms */
#define CLK_XTALSTB_8MS             (0x07U)       /*!< 2147 stable count cycle, approx. 8ms */
#define CLK_XTALSTB_16MS            (0x08U)       /*!< 4291 stable count cycle, approx. 16ms */
#define CLK_XTALSTB_31MS            (0x09U)       /*!< 8163 stable count cycle, approx. 32ms */
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
#define CLK_XTALSTD_OFF             (0x00U)
#define CLK_XTALSTD_ON              (CMU_XTALSTDCR_XTALSTDE)

/**
 * @brief XTALSTD mode selection
 */
#define CLK_XTALSTD_MODE_RST        (CMU_XTALSTDCR_XTALSTDRIS)
#define CLK_XTALSTD_MODE_INT        (0x00U)

/**
 * @brief XTALSTD reset on or off
 */
#define CLK_XTALSTD_RST_OFF         (0x00U)
#define CLK_XTALSTD_RST_ON          (CMU_XTALSTDCR_XTALSTDRE)

/**
 * @brief XTALSTD interrupt on or off
 */
#define CLK_XTALSTD_INT_OFF         (0x00U)
#define CLK_XTALSTD_INT_ON          (CMU_XTALSTDCR_XTALSTDIE)
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
#define CLK_XTAL32_OFF              (CMU_XTAL32CR_XTAL32STP)
#define CLK_XTAL32_ON               (0x00U)

/**
 * @brief XTAL32 driver ability.
 */
#define CLK_XTAL32DRV_MID           (0x00U)
#define CLK_XTAL32DRV_HIGH          (0x01U)

/**
 * @brief XTAL32 filtering seletion.
 */
#define CLK_XTAL32NF_FULL           (0x00U)   /*!< Valid in run,stop,power down mode.     */
#define CLK_XTAL32NF_PART           (0x02U)   /*!< Valid in run mode.                     */
#define CLK_XTAL32NF_NONE           (0x03U)   /*!< Invalid in run,stop,power down mode.   */
/**
 * @}
 */

/**
 * @defgroup CLK_HRC_Config HRC Config
 * @{
 */
#define CLK_HRC_OFF                 (CMU_HRCCR_HRCSTP)
#define CLK_HRC_ON                  (0x00U)
/**
 * @}
 */

/**
 * @defgroup CLK_MRC_Config HRC Config
 * @{
 */
#define CLK_MRC_OFF                 (CMU_MRCCR_MRCSTP)
#define CLK_MRC_ON                  (0x00U)
/**
 * @}
 */

/**
 * @defgroup CLK_LRC_Config LRC Config
 * @{
 */
#define CLK_LRC_OFF                 (CMU_LRCCR_LRCSTP)
#define CLK_LRC_ON                  (0x00U)
/**
 * @}
 */

/**
 * @defgroup CLK_RTCLRC_Config LRC Config
 * @{
 */
#define CLK_RTCLRC_OFF              (CMU_RTCLRCCR_RTCLRCSTP)
#define CLK_RTCLRC_ON               (0x00U)
/**
 * @}
 */

/**
 * @defgroup CLK_STB_Flag CLK stable Flags
 * @{
 */
#define CLK_STB_FLAG_HRCSTB         (CMU_OSCSTBSR_HRCSTBF)
#define CLK_STB_FLAG_XTALSTB        (CMU_OSCSTBSR_XTALSTBF)
#define CLK_STB_FLAG_PLLASTB        (CMU_OSCSTBSR_PLLASTBF)
#define CLK_STB_FLAG_PLLHSTB        (CMU_OSCSTBSR_PLLHSTBF)
#define CLK_STB_FLAG_MASK           ((CMU_OSCSTBSR_HRCSTBF) |   \
                                     (CMU_OSCSTBSR_XTALSTBF)|   \
                                     (CMU_OSCSTBSR_PLLASTBF)|   \
                                     (CMU_OSCSTBSR_PLLHSTBF))

/**
 * @}
 */

/**
 * @defgroup CLK_System_Clock_Source System Clock Source
 * @{
 */
#define CLK_SYSCLKSOURCE_HRC        (0x00U)
#define CLK_SYSCLKSOURCE_MRC        (0x01U)
#define CLK_SYSCLKSOURCE_LRC        (0x02U)
#define CLK_SYSCLKSOURCE_XTAL       (0x03U)
#define CLK_SYSCLKSOURCE_XTAL32     (0x04U)
#define CLK_SYSCLKSOURCE_PLLH       (0x05U)
/**
 * @}
 */

/**
 * @defgroup CLK_CATE_Sel Clock category selection
 * @{
 */
#define CLK_CATE_PCLK0              (0x01U)
#define CLK_CATE_PCLK1              (0x02U)
#define CLK_CATE_PCLK2              (0x04U)
#define CLK_CATE_PCLK3              (0x08U)
#define CLK_CATE_PCLK4              (0x10U)
#define CLK_CATE_EXCLK              (0x20U)
#define CLK_CATE_HCLK               (0x40U)
#define CLK_CATE_ALL                (CLK_CATE_PCLK0 | CLK_CATE_PCLK1 |  \
                                     CLK_CATE_PCLK2 | CLK_CATE_PCLK3 |  \
                                     CLK_CATE_PCLK4 | CLK_CATE_EXCLK |  \
                                     CLK_CATE_HCLK)
/**
 * @}
 */

/**
 * @defgroup CLK_HCLK_Divider HCLK divider
 * @{
 */
#define CLK_HCLK_DIV1               (0x00U << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV2               (0x01U << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV4               (0x02U << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV8               (0x03U << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV16              (0x04U << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV32              (0x05U << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV64              (0x06U << CMU_SCFGR_HCLKS_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_EXCLK_Divider EXCLK divider
 * @{
 */
#define CLK_EXCLK_DIV1              (0x00U << CMU_SCFGR_EXCKS_POS)
#define CLK_EXCLK_DIV2              (0x01U << CMU_SCFGR_EXCKS_POS)
#define CLK_EXCLK_DIV4              (0x02U << CMU_SCFGR_EXCKS_POS)
#define CLK_EXCLK_DIV8              (0x03U << CMU_SCFGR_EXCKS_POS)
#define CLK_EXCLK_DIV16             (0x04U << CMU_SCFGR_EXCKS_POS)
#define CLK_EXCLK_DIV32             (0x05U << CMU_SCFGR_EXCKS_POS)
#define CLK_EXCLK_DIV64             (0x06U << CMU_SCFGR_EXCKS_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_PCLK4_Divider PCLK4 divider
 * @{
 */
#define CLK_PCLK4_DIV1              (0x00U << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV2              (0x01U << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV4              (0x02U << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV8              (0x03U << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV16             (0x04U << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV32             (0x05U << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV64             (0x06U << CMU_SCFGR_PCLK4S_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_PCLK3_Divider PCLK3 divider
 * @{
 */
#define CLK_PCLK3_DIV1              (0x00U << CMU_SCFGR_PCLK3S_POS)
#define CLK_PCLK3_DIV2              (0x01U << CMU_SCFGR_PCLK3S_POS)
#define CLK_PCLK3_DIV4              (0x02U << CMU_SCFGR_PCLK3S_POS)
#define CLK_PCLK3_DIV8              (0x03U << CMU_SCFGR_PCLK3S_POS)
#define CLK_PCLK3_DIV16             (0x04U << CMU_SCFGR_PCLK3S_POS)
#define CLK_PCLK3_DIV32             (0x05U << CMU_SCFGR_PCLK3S_POS)
#define CLK_PCLK3_DIV64             (0x06U << CMU_SCFGR_PCLK3S_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_PCLK2_Divider PCLK2 divider
 * @{
 */
#define CLK_PCLK2_DIV1              (0x00U << CMU_SCFGR_PCLK2S_POS)
#define CLK_PCLK2_DIV2              (0x01U << CMU_SCFGR_PCLK2S_POS)
#define CLK_PCLK2_DIV4              (0x02U << CMU_SCFGR_PCLK2S_POS)
#define CLK_PCLK2_DIV8              (0x03U << CMU_SCFGR_PCLK2S_POS)
#define CLK_PCLK2_DIV16             (0x04U << CMU_SCFGR_PCLK2S_POS)
#define CLK_PCLK2_DIV32             (0x05U << CMU_SCFGR_PCLK2S_POS)
#define CLK_PCLK2_DIV64             (0x06U << CMU_SCFGR_PCLK2S_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_PCLK1_Divider PCLK1 divider
 * @{
 */
#define CLK_PCLK1_DIV1              (0x00U << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV2              (0x01U << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV4              (0x02U << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV8              (0x03U << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV16             (0x04U << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV32             (0x05U << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV64             (0x06U << CMU_SCFGR_PCLK1S_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_PCLK0_Divider PCLK0 divider
 * @{
 */
#define CLK_PCLK0_DIV1              (0x00U << CMU_SCFGR_PCLK0S_POS)
#define CLK_PCLK0_DIV2              (0x01U << CMU_SCFGR_PCLK0S_POS)
#define CLK_PCLK0_DIV4              (0x02U << CMU_SCFGR_PCLK0S_POS)
#define CLK_PCLK0_DIV8              (0x03U << CMU_SCFGR_PCLK0S_POS)
#define CLK_PCLK0_DIV16             (0x04U << CMU_SCFGR_PCLK0S_POS)
#define CLK_PCLK0_DIV32             (0x05U << CMU_SCFGR_PCLK0S_POS)
#define CLK_PCLK0_DIV64             (0x06U << CMU_SCFGR_PCLK0S_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_USB_CLK_Sel USB clock selection
 * @{
 */
#define CLK_USB_CLK_MCLK_DIV2       (0x01U << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USB_CLK_MCLK_DIV3       (0x02U << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USB_CLK_MCLK_DIV4       (0x03U << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USB_CLK_MCLK_DIV5       (0x04U << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USB_CLK_MCLK_DIV6       (0x05U << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USB_CLK_MCLK_DIV7       (0x06U << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USB_CLK_MCLK_DIV8       (0x07U << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USB_CLK_PLLHQ           (0x08U << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USB_CLK_PLLHR           (0x09U << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USB_CLK_PLLAP           (0x0AU << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USB_CLK_PLLAQ           (0x0BU << CMU_USBCKCFGR_USBCKS_POS)
#define CLK_USB_CLK_PLLAR           (0x0CU << CMU_USBCKCFGR_USBCKS_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_CAN_CLK_Sel CAN clock selection
 * @{
 */
#define CLK_CAN_CLK_MCLK_DIV2       (0x01U)
#define CLK_CAN_CLK_MCLK_DIV3       (0x02U)
#define CLK_CAN_CLK_MCLK_DIV4       (0x03U)
#define CLK_CAN_CLK_MCLK_DIV5       (0x04U)
#define CLK_CAN_CLK_MCLK_DIV6       (0x05U)
#define CLK_CAN_CLK_MCLK_DIV7       (0x06U)
#define CLK_CAN_CLK_MCLK_DIV8       (0x07U)
#define CLK_CAN_CLK_PLLHQ           (0x08U)
#define CLK_CAN_CLK_PLLHR           (0x09U)
#define CLK_CAN_CLK_PLLAP           (0x0AU)
#define CLK_CAN_CLK_PLLAQ           (0x0BU)
#define CLK_CAN_CLK_PLLAR           (0x0CU)
#define CLK_CAN_CLK_XTAL            (0x0DU)
#define CLK_CAN1_CLK_MCLK_DIV2      (CLK_CAN_CLK_MCLK_DIV2)
#define CLK_CAN1_CLK_MCLK_DIV3      (CLK_CAN_CLK_MCLK_DIV3)
#define CLK_CAN1_CLK_MCLK_DIV4      (CLK_CAN_CLK_MCLK_DIV4)
#define CLK_CAN1_CLK_MCLK_DIV5      (CLK_CAN_CLK_MCLK_DIV5)
#define CLK_CAN1_CLK_MCLK_DIV6      (CLK_CAN_CLK_MCLK_DIV6)
#define CLK_CAN1_CLK_MCLK_DIV7      (CLK_CAN_CLK_MCLK_DIV7)
#define CLK_CAN1_CLK_MCLK_DIV8      (CLK_CAN_CLK_MCLK_DIV8)
#define CLK_CAN1_CLK_PLLHQ          (CLK_CAN_CLK_PLLHQ)
#define CLK_CAN1_CLK_PLLHR          (CLK_CAN_CLK_PLLHR)
#define CLK_CAN1_CLK_PLLAP          (CLK_CAN_CLK_PLLAP)
#define CLK_CAN1_CLK_PLLAQ          (CLK_CAN_CLK_PLLAQ)
#define CLK_CAN1_CLK_PLLAR          (CLK_CAN_CLK_PLLAR)
#define CLK_CAN1_CLK_XTAL           (CLK_CAN_CLK_XTAL)
#define CLK_CAN2_CLK_MCLK_DIV2      (CLK_CAN_CLK_MCLK_DIV2 << CMU_CANCKCFGR_CAN2CKS_POS)
#define CLK_CAN2_CLK_MCLK_DIV3      (CLK_CAN_CLK_MCLK_DIV3 << CMU_CANCKCFGR_CAN2CKS_POS)
#define CLK_CAN2_CLK_MCLK_DIV4      (CLK_CAN_CLK_MCLK_DIV4 << CMU_CANCKCFGR_CAN2CKS_POS)
#define CLK_CAN2_CLK_MCLK_DIV5      (CLK_CAN_CLK_MCLK_DIV5 << CMU_CANCKCFGR_CAN2CKS_POS)
#define CLK_CAN2_CLK_MCLK_DIV6      (CLK_CAN_CLK_MCLK_DIV6 << CMU_CANCKCFGR_CAN2CKS_POS)
#define CLK_CAN2_CLK_MCLK_DIV7      (CLK_CAN_CLK_MCLK_DIV7 << CMU_CANCKCFGR_CAN2CKS_POS)
#define CLK_CAN2_CLK_MCLK_DIV8      (CLK_CAN_CLK_MCLK_DIV8 << CMU_CANCKCFGR_CAN2CKS_POS)
#define CLK_CAN2_CLK_PLLHQ          (CLK_CAN_CLK_PLLHQ << CMU_CANCKCFGR_CAN2CKS_POS)
#define CLK_CAN2_CLK_PLLHR          (CLK_CAN_CLK_PLLHR << CMU_CANCKCFGR_CAN2CKS_POS)
#define CLK_CAN2_CLK_PLLAP          (CLK_CAN_CLK_PLLAP << CMU_CANCKCFGR_CAN2CKS_POS)
#define CLK_CAN2_CLK_PLLAQ          (CLK_CAN_CLK_PLLAQ << CMU_CANCKCFGR_CAN2CKS_POS)
#define CLK_CAN2_CLK_PLLAR          (CLK_CAN_CLK_PLLAR << CMU_CANCKCFGR_CAN2CKS_POS)
#define CLK_CAN2_CLK_XTAL           (CLK_CAN_CLK_XTAL  << CMU_CANCKCFGR_CAN2CKS_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_CAN_CH_Sel CAN channel for clock selection
 * @{
 */
#define CLK_CAN_CH1                 (0x01U)
#define CLK_CAN_CH2                 (0x02U)
#define CLK_CAN_CH_ALL              (CLK_CAN_CH1 | CLK_CAN_CH2)
/**
 * @}
 */

/**
 * @defgroup CLK_I2S_CLK_Sel I2S clock selection
 * @{
 */
#define CLK_I2S_CLK_PCLK            (0x0000U)
#define CLK_I2S_CLK_PLLHQ           (0x0008U)
#define CLK_I2S_CLK_PLLHR           (0x0009U)
#define CLK_I2S_CLK_PLLAP           (0x000AU)
#define CLK_I2S_CLK_PLLAQ           (0x000BU)
#define CLK_I2S_CLK_PLLAR           (0x000CU)
#define CLK_I2S1_CLK_PCLK           (CLK_I2S_CLK_PCLK)
#define CLK_I2S1_CLK_PLLHQ          (CLK_I2S_CLK_PLLHQ)
#define CLK_I2S1_CLK_PLLHR          (CLK_I2S_CLK_PLLHR)
#define CLK_I2S1_CLK_PLLAP          (CLK_I2S_CLK_PLLAP)
#define CLK_I2S1_CLK_PLLAQ          (CLK_I2S_CLK_PLLAQ)
#define CLK_I2S1_CLK_PLLAR          (CLK_I2S_CLK_PLLAR)
#define CLK_I2S2_CLK_PCLK           (CLK_I2S_CLK_PCLK  << CMU_I2SCKSEL_I2S2CKSEL_POS)
#define CLK_I2S2_CLK_PLLHQ          (CLK_I2S_CLK_PLLHQ << CMU_I2SCKSEL_I2S2CKSEL_POS)
#define CLK_I2S2_CLK_PLLHR          (CLK_I2S_CLK_PLLHR << CMU_I2SCKSEL_I2S2CKSEL_POS)
#define CLK_I2S2_CLK_PLLAP          (CLK_I2S_CLK_PLLAP << CMU_I2SCKSEL_I2S2CKSEL_POS)
#define CLK_I2S2_CLK_PLLAQ          (CLK_I2S_CLK_PLLAQ << CMU_I2SCKSEL_I2S2CKSEL_POS)
#define CLK_I2S2_CLK_PLLAR          (CLK_I2S_CLK_PLLAR << CMU_I2SCKSEL_I2S2CKSEL_POS)
#define CLK_I2S3_CLK_PCLK           (CLK_I2S_CLK_PCLK  << CMU_I2SCKSEL_I2S3CKSEL_POS)
#define CLK_I2S3_CLK_PLLHQ          (CLK_I2S_CLK_PLLHQ << CMU_I2SCKSEL_I2S3CKSEL_POS)
#define CLK_I2S3_CLK_PLLHR          (CLK_I2S_CLK_PLLHR << CMU_I2SCKSEL_I2S3CKSEL_POS)
#define CLK_I2S3_CLK_PLLAP          (CLK_I2S_CLK_PLLAP << CMU_I2SCKSEL_I2S3CKSEL_POS)
#define CLK_I2S3_CLK_PLLAQ          (CLK_I2S_CLK_PLLAQ << CMU_I2SCKSEL_I2S3CKSEL_POS)
#define CLK_I2S3_CLK_PLLAR          (CLK_I2S_CLK_PLLAR << CMU_I2SCKSEL_I2S3CKSEL_POS)
#define CLK_I2S4_CLK_PCLK           (CLK_I2S_CLK_PCLK  << CMU_I2SCKSEL_I2S4CKSEL_POS)
#define CLK_I2S4_CLK_PLLHQ          (CLK_I2S_CLK_PLLHQ << CMU_I2SCKSEL_I2S4CKSEL_POS)
#define CLK_I2S4_CLK_PLLHR          (CLK_I2S_CLK_PLLHR << CMU_I2SCKSEL_I2S4CKSEL_POS)
#define CLK_I2S4_CLK_PLLAP          (CLK_I2S_CLK_PLLAP << CMU_I2SCKSEL_I2S4CKSEL_POS)
#define CLK_I2S4_CLK_PLLAQ          (CLK_I2S_CLK_PLLAQ << CMU_I2SCKSEL_I2S4CKSEL_POS)
#define CLK_I2S4_CLK_PLLAR          (CLK_I2S_CLK_PLLAR << CMU_I2SCKSEL_I2S4CKSEL_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_I2S_CH_Sel I2S channel for clock selection
 * @{
 */
#define CLK_I2S_CH1                 (0x01U)
#define CLK_I2S_CH2                 (0x02U)
#define CLK_I2S_CH3                 (0x04U)
#define CLK_I2S_CH4                 (0x08U)
#define CLK_I2S_CH_ALL              (CLK_I2S_CH1 | CLK_I2S_CH2 | CLK_I2S_CH3 | CLK_I2S_CH4)
/**
 * @}
 */

/**
 * @defgroup CLK_PCLK24_Sel PCLK2/4 selection
 * @{
 */
#define CLK_PERI_CLK_PCLK           (0x0000U)
#define CLK_PERI_CLK_PLLHQ          (0x0008U)
#define CLK_PERI_CLK_PLLHR          (0x0009U)
#define CLK_PERI_CLK_PLLAP          (0x000AU)
#define CLK_PERI_CLK_PLLAQ          (0x000BU)
#define CLK_PERI_CLK_PLLAR          (0x000CU)
/**
 * @}
 */

/**
 * @defgroup CLK_TPIU_Divider TPIU clock divider
 * @{
 */
#define CLK_TPIU_CLK_DIV1           (0x00U)
#define CLK_TPIU_CLK_DIV2           (0x01U)
#define CLK_TPIU_CLK_DIV4           (0x02U)
/**
 * @}
 */

/**
 * @defgroup CLK_MCO_Clock_Source CLK MCO Clock Source
 * @{
 */
#define CLK_MCOSOURCCE_HRC          (0x00U)
#define CLK_MCOSOURCCE_MRC          (0x01U)
#define CLK_MCOSOURCCE_LRC          (0x02U)
#define CLK_MCOSOURCCE_XTAL         (0x03U)
#define CLK_MCOSOURCCE_XTAL32       (0x04U)
#define CLK_MCOSOURCCE_PLLHP        (0x06U)
#define CLK_MCOSOURCCE_PLLAP        (0x07U)
#define CLK_MCOSOURCCE_PLLHQ        (0x08U)
#define CLK_MCOSOURCCE_PLLAQ        (0x09U)
#define CLK_MCOSOURCCE_PLLAR        (0x0AU)
#define CLK_MCOSOURCCE_SYSCLK       (0x0BU)
/**
 * @}
 */

/**
 * @defgroup CLK_MCO_Clock_Prescaler CLK MCO Clock Prescaler
 * @{
 */
#define CLK_MCO_DIV1                (0x00U << CMU_MCO2CFGR_MCO2DIV_POS)
#define CLK_MCO_DIV2                (0x01U << CMU_MCO2CFGR_MCO2DIV_POS)
#define CLK_MCO_DIV4                (0x02U << CMU_MCO2CFGR_MCO2DIV_POS)
#define CLK_MCO_DIV8                (0x03U << CMU_MCO2CFGR_MCO2DIV_POS)
#define CLK_MCO_DIV16               (0x04U << CMU_MCO2CFGR_MCO2DIV_POS)
#define CLK_MCO_DIV32               (0x05U << CMU_MCO2CFGR_MCO2DIV_POS)
#define CLK_MCO_DIV64               (0x06U << CMU_MCO2CFGR_MCO2DIV_POS)
#define CLK_MCO_DIV128              (0x07U << CMU_MCO2CFGR_MCO2DIV_POS)
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
en_result_t CLK_XtalStdStrucInit(stc_clk_xtalstd_init_t* pstcXtalStdInit);
en_result_t CLK_XtalStdInit(const stc_clk_xtalstd_init_t* pstcXtalStdInit);
void CLK_ClearXtalStdStatus(void);
en_flag_status_t CLK_GetXtalStdStatus(void);

void CLK_HrcTrim(int8_t i8TrimVal);
void CLK_MrcTrim(int8_t i8TrimVal);
void CLK_LrcTrim(int8_t i8TrimVal);
void CLK_RtcLrcTrim(int8_t i8TrimVal);

en_result_t CLK_XtalCmd(en_functional_state_t enNewState);
en_result_t CLK_Xtal32Cmd(en_functional_state_t enNewState);
en_result_t CLK_HrcCmd(en_functional_state_t enNewState);
en_result_t CLK_MrcCmd(en_functional_state_t enNewState);
en_result_t CLK_LrcCmd(en_functional_state_t enNewState);
en_result_t CLK_PLLACmd(en_functional_state_t enNewState);
en_result_t CLK_PLLHCmd(en_functional_state_t enNewState);

en_result_t CLK_PLLAStrucInit(stc_clk_plla_init_t* pstcPLLAInit);
en_result_t CLK_PLLAInit(const stc_clk_plla_init_t *pstcPLLAInit);

en_result_t CLK_PLLHStrucInit(stc_clk_pllh_init_t* pstcPLLHInit);
en_result_t CLK_PLLHInit(const stc_clk_pllh_init_t *pstcPLLHInit);

en_result_t CLK_XtalStrucInit(stc_clk_xtal_init_t* pstcXtalInit);
en_result_t CLK_XtalInit(const stc_clk_xtal_init_t *pstcXtalInit);

en_result_t CLK_Xtal32StrucInit(stc_clk_xtal32_init_t* pstcXtal32Init);
en_result_t CLK_Xtal32Init(const stc_clk_xtal32_init_t *pstcXtal32Init);

en_flag_status_t CLK_GetStableStatus(uint8_t u8StableFlag);

void CLK_SetSysClkSrc(uint8_t u8Src);
void CLK_ClkDiv(uint8_t u8ClkCate, uint32_t u32Div);

void CLK_USB_ClkConfig(uint8_t u8UsbClk);
void CLK_CAN_ClkConfig(uint8_t u8CanCh, uint8_t u8CanClk);
void CLK_I2S_ClkConfig(uint8_t u8I2sCh, uint16_t u16I2sClk);
void CLK_PERI_ClkConfig(uint16_t u16Periclk);

void CLK_TpiuClkCmd(en_functional_state_t enNewState);
void CLK_TpiuClkConfig(uint8_t u8TpiuDiv);

void CLK_MCO1Config(uint8_t CLK_MCOSource, uint8_t CLK_MCODiv);
void CLK_MCO1Cmd(en_functional_state_t enNewState);
void CLK_MCO2Config(uint8_t CLK_MCOSource, uint8_t CLK_MCODiv);
void CLK_MCO2Cmd(en_functional_state_t enNewState);

en_result_t CLK_GetClockFreq(stc_clk_freq_t *pstcClkFreq);
en_result_t CLK_GetPllClockFreq(stc_pll_clk_freq_t *pstcPllClkFreq);
void CLK_SetPLLSrc(uint32_t u32PllSrc);


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

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_CLK_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
