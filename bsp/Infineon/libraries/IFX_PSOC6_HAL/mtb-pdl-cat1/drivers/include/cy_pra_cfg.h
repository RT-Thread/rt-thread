/***************************************************************************//**
* \file cy_pra_cfg.h
* \version 2.40
*
* \brief The header file of the PRA driver. The API is not intended to
* be used directly by the user application.
*
********************************************************************************
* \copyright
* Copyright 2020 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#if !defined(CY_PRA_CFG_H)
#define CY_PRA_CFG_H

#include "cy_device.h"

#if defined (CY_IP_MXS40SRSS)

#include <stdint.h>
#include <stdbool.h>
#include "cy_pra.h"
#include "cy_sysclk.h"
#include "cy_systick.h"
#include "cy_ble_clk.h"
#include "cy_device_headers.h"

#if defined (CY_DEVICE_SECURE) || defined (CY_DOXYGEN)

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
*                            Type Definitions
*******************************************************************************/

/** \cond INTERNAL */

#define CY_PRA_FREQUENCY_HZ_CONVERSION   1000000UL
#define CY_PRA_150MHZ_FREQUENCY          150UL
#define CY_PRA_FLL_ENABLE_TIMEOUT        200000UL
#define CY_PRA_ECO_ENABLE_TIMEOUT        3000UL
#define CY_PRA_WCO_ENABLE_TIMEOUT        1000000UL
#define CY_PRA_IMO_SRC_FREQUENCY         8000000UL
#define CY_PRA_ILO_SRC_FREQUENCY         32000UL
#define CY_PRA_WCO_SRC_FREQUENCY         32768UL
#define CY_PRA_PILO_SRC_FREQUENCY        32768UL
#define CY_PRA_DEFAULT_SRC_FREQUENCY     0xFFFFFFFEUL
#define CY_PRA_ULP_MODE_MAX_FREQUENCY    50000000UL
#define CY_PRA_LP_MODE_MAX_FREQUENCY     100000000UL
#define CY_PRA_ALTHF_MIN_FREQUENCY       2000000UL
#define CY_PRA_ALTHF_MAX_FREQUENCY       32000000UL
#define CY_PRA_ALTHF_FREQ_16MHZ          16000000UL
#define CY_PRA_ALTHF_FREQ_32MHZ          32000000UL
#define CY_PRA_ALTHF_MIN_STARTUP_TIME    400UL
#define CY_PRA_ALTHF_MAX_STARTUP_TIME    4704UL
#define CY_PRA_ALTHF_MIN_LOAD            0
#define CY_PRA_ALTHF_MAX_LOAD            251

#define CY_PRA_ECO_FREQ_MIN              (16000000UL) /* 16 MHz   */
#define CY_PRA_ECO_FREQ_MAX              (35000000UL) /* 35 MHz   */
#define CY_PRA_ECO_CSM_MIN               (1UL)        /* 1  pF    */
#define CY_PRA_ECO_CSM_MAX               (100UL)      /* 100 pF   */
#define CY_PRA_ECO_ESR_MIN               (1UL)        /* 1  Ohm   */
#define CY_PRA_ECO_ESR_MAX               (1000UL)     /* 1000 Ohm */
#define CY_PRA_ECO_DRV_MIN               (1UL)        /* 1 kW     */
#define CY_PRA_ECO_DRV_MAX               (1000UL)     /* 1 mW     */

#define CY_PRA_FLL_SRC_MIN_FREQUENCY     (1000UL)       /* 1 KHz */
#define CY_PRA_FLL_SRC_MAX_FREQUENCY     (100000000UL)  /* 100 MHz */
#define CY_PRA_FLL_OUT_MIN_FREQUENCY     (24000000UL)   /* 24 MHz */
#define CY_PRA_FLL_ULP_OUT_MAX_FREQUENCY (50000000UL)   /* 50 MHz */
#define CY_PRA_FLL_OUT_MAX_FREQUENCY     ((CY_HF_CLK_MAX_FREQ > 100000000UL) ? (100000000UL) : (CY_HF_CLK_MAX_FREQ))
#define CY_PRA_FLL_MIN_MULTIPLIER        1UL
#define CY_PRA_FLL_MAX_MULTIPLIER        262143UL
#define CY_PRA_FLL_MIN_REFDIV            1UL
#define CY_PRA_FLL_MAX_REFDIV            8191UL
#define CY_PRA_FLL_MAX_LOCK_TOLERENCE    511UL

#define CY_PRA_PLL_SRC_MIN_FREQUENCY     (4000000UL)    /* 4 MHz */
#define CY_PRA_PLL_SRC_MAX_FREQUENCY     (64000000UL)   /* 64 MHz */
#define CY_PRA_PLL_LOW_OUT_MIN_FREQUENCY (10625000UL)   /* 10.625 MHz */
#define CY_PRA_PLL_OUT_MIN_FREQUENCY     (12500000UL)   /* 12.5 MHz */
#define CY_PRA_PLL_ULP_OUT_MAX_FREQUENCY (50000000UL)   /* 50 MHz */
#define CY_PRA_PLL_OUT_MAX_FREQUENCY     (CY_HF_CLK_MAX_FREQ)

#define CY_PRA_HF0_MIN_FREQUENCY         200000UL
#define CY_PRA_PUMP_OUT_MAX_FREQUENCY    400000000UL
#define CY_PRA_BAK_OUT_MAX_FREQUENCY     100000UL
#define CY_PRA_FAST_OUT_MAX_FREQUENCY    400000000UL
#define CY_PRA_TIMER_OUT_MAX_FREQUENCY   400000000UL
#define CY_PRA_SLOW_OUT_MAX_FREQUENCY    100000000UL
#define CY_PRA_SYSTICK_OUT_MAX_FREQUENCY   400000000UL
#define CY_PRA_ULP_MODE_HF0_MAX_FREQUENCY  25000000UL

#define CY_PRA_DEFAULT_ZERO              0U
#define CY_PRA_DATA_ENABLE               1UL
#define CY_PRA_DATA_DISABLE              0UL
#define CY_PRA_CLKHF_0                   0UL
#define CY_PRA_CLKHF_1                   1UL
#define CY_PRA_CLKHF_2                   2UL
#define CY_PRA_CLKHF_3                   3UL
#define CY_PRA_CLKHF_4                   4UL
#define CY_PRA_CLKHF_5                   5UL
#define CY_PRA_CLKPATH_0                 0U
#define CY_PRA_CLKPATH_1                 1U
#define CY_PRA_CLKPATH_2                 2U
#define CY_PRA_CLKPATH_3                 3U
#define CY_PRA_CLKPATH_4                 4U
#define CY_PRA_CLKPATH_5                 5U
#define CY_PRA_CLKPLL_1                  1U
#define CY_PRA_CLKPLL_2                  2U
#define CY_PRA_DIVIDER_0                 0U
#define CY_PRA_DIVIDER_1                 1U
#define CY_PRA_DIVIDER_2                 2U
#define CY_PRA_DIVIDER_4                 4U
#define CY_PRA_DIVIDER_8                 8U

/** \endcond */


/**
* \addtogroup group_pra_stc
* \{
*/

/** System configuration structure */
typedef struct
{
    bool powerEnable;                                   /**< Power is enabled or disabled */
    bool ldoEnable;                                     /**< Core Regulator */
    bool pmicEnable;                                    /**< Power using external PMIC output */
    bool vBackupVDDDEnable;                             /**< vBackup source using VDD or Direct supply */
    bool ulpEnable;                                     /**< System Active Power mode is ULP */
    bool ecoEnable;                                     /**< ECO Enable */
    bool extClkEnable;                                  /**< EXTCLK Enable */
    bool iloEnable;                                     /**< ILO Enable */
    bool wcoEnable;                                     /**< WCO Enable */
    bool fllEnable;                                     /**< FLL Enable */
    bool pll0Enable;                                    /**< PLL0 Enable */
    bool pll1Enable;                                    /**< PLL1 Enable */
    bool path0Enable;                                   /**< PATH_MUX0 Enable */
    bool path1Enable;                                   /**< PATH_MUX1 Enable */
    bool path2Enable;                                   /**< PATH_MUX2 Enable */
    bool path3Enable;                                   /**< PATH_MUX3 Enable */
    bool path4Enable;                                   /**< PATH_MUX4 Enable */
    bool path5Enable;                                   /**< PATH_MUX5 Enable */
    bool clkFastEnable;                                 /**< CLKFAST Enable */
    bool clkPeriEnable;                                 /**< CLKPERI Enable */
    bool clkSlowEnable;                                 /**< CLKSLOW Enable */
    bool clkHF0Enable;                                  /**< CLKHF0 Enable */
    bool clkHF1Enable;                                  /**< CLKHF1 Enable */
    bool clkHF2Enable;                                  /**< CLKHF2 Enable */
    bool clkHF3Enable;                                  /**< CLKHF3 Enable */
    bool clkHF4Enable;                                  /**< CLKHF4 Enable */
    bool clkHF5Enable;                                  /**< CLKHF5 Enable */
    bool clkPumpEnable;                                 /**< CLKPUMP Enable */
    bool clkLFEnable;                                   /**< CLKLF Enable */
    bool clkBakEnable;                                  /**< CLKBAK Enable */
    bool clkTimerEnable;                                /**< CLKTIMER Enable */
    bool clkAltSysTickEnable;                           /**< CLKALTSYSTICK Enable */
    bool piloEnable;                                    /**< PILO Enable */
    bool clkAltHfEnable;                                /**< BLE ECO Clock Enable */

    /* Power */
    cy_en_syspm_ldo_voltage_t ldoVoltage;               /**< LDO Voltage (LP or ULP) */
    cy_en_syspm_buck_voltage1_t buckVoltage;            /**< Buck Voltage */
    bool pwrCurrentModeMin;                             /**< Minimum core regulator current mode */

    /* System clocks */
    /* IMO is always enabled */
    /* ECO Configuration */
    uint32_t ecoFreqHz;                                 /**< ECO Frequency in Hz */
    uint32_t ecoLoad;                                   /**< Parallel Load Capacitance (pF) */
    uint32_t ecoEsr;                                    /**< Equivalent series resistance (ohm) */
    uint32_t ecoDriveLevel;                             /**< Drive Level (uW) */
    GPIO_PRT_Type *ecoInPort;                           /**< ECO input port */
    GPIO_PRT_Type *ecoOutPort;                          /**< ECO output port */
    uint32_t ecoInPinNum;                               /**< ECO input pin number */
    uint32_t ecoOutPinNum;                              /**< ECO output pin number */

    /* EXTCLK Configuration */
    uint32_t extClkFreqHz;                              /**< External clock frequency in Hz */
    GPIO_PRT_Type *extClkPort;                          /**< External connection port */
    uint32_t extClkPinNum;                              /**< External connection pin */
    en_hsiom_sel_t extClkHsiom;                         /**< IO mux value */

    /* ILO Configuration */
    bool iloHibernateON;                                /**< Run in Hibernate Mode */

    /* WCO Configuration */
    bool bypassEnable;                                  /**< Clock port bypass to External sine wave or to normal crystal */
    GPIO_PRT_Type *wcoInPort;                           /**< WCO Input port */
    GPIO_PRT_Type *wcoOutPort;                          /**< WCO Output port */
    uint32_t wcoInPinNum;                               /**< WCO Input pin */
    uint32_t wcoOutPinNum;                              /**< WCO Output pin */

    /* FLL Configuration */
    uint32_t fllOutFreqHz;                              /**< FLL Output Frequency in Hz */
    uint32_t                    fllMult;                /**< CLK_FLL_CONFIG  register, FLL_MULT bits */
    uint16_t                    fllRefDiv;              /**< CLK_FLL_CONFIG2 register, FLL_REF_DIV bits */
    cy_en_fll_cco_ranges_t      fllCcoRange;            /**< CLK_FLL_CONFIG4 register, CCO_RANGE bits */
    bool                        enableOutputDiv;        /**< CLK_FLL_CONFIG  register, FLL_OUTPUT_DIV bit */
    uint16_t                    lockTolerance;          /**< CLK_FLL_CONFIG2 register, LOCK_TOL bits */
    uint8_t                     igain;                  /**< CLK_FLL_CONFIG3 register, FLL_LF_IGAIN bits */
    uint8_t                     pgain;                  /**< CLK_FLL_CONFIG3 register, FLL_LF_PGAIN bits */
    uint16_t                    settlingCount;          /**< CLK_FLL_CONFIG3 register, SETTLING_COUNT bits */
    cy_en_fll_pll_output_mode_t outputMode;             /**< CLK_FLL_CONFIG3 register, BYPASS_SEL bits */
    uint16_t                    ccoFreq;                /**< CLK_FLL_CONFIG4 register, CCO_FREQ bits */

    /* Number of PLL available for the device is defined in CY_SRSS_NUM_PLL
     * Max 2 instances of PLLs are defined */

    /* PLL0 Configuration */
    uint32_t pll0OutFreqHz;                             /**< PLL0 output frequency in Hz */
    uint8_t                     pll0FeedbackDiv;        /**< PLL0 CLK_PLL_CONFIG register, FEEDBACK_DIV (P) bits */
    uint8_t                     pll0ReferenceDiv;       /**< PLL0 CLK_PLL_CONFIG register, REFERENCE_DIV (Q) bits */
    uint8_t                     pll0OutputDiv;          /**< PLL0 CLK_PLL_CONFIG register, OUTPUT_DIV bits */
    bool                        pll0LfMode;             /**< PLL0 CLK_PLL_CONFIG register, PLL_LF_MODE bit */
    cy_en_fll_pll_output_mode_t pll0OutputMode;         /**< PLL0 CLK_PLL_CONFIG register, BYPASS_SEL bits */

    /* PLL1 Configuration */
    uint32_t pll1OutFreqHz;                             /**< PLL1 output frequency in Hz */
    uint8_t                     pll1FeedbackDiv;        /**< PLL1 CLK_PLL_CONFIG register, FEEDBACK_DIV (P) bits */
    uint8_t                     pll1ReferenceDiv;       /**< PLL1 CLK_PLL_CONFIG register, REFERENCE_DIV (Q) bits */
    uint8_t                     pll1OutputDiv;          /**< PLL1 CLK_PLL_CONFIG register, OUTPUT_DIV bits */
    bool                        pll1LfMode;             /**< PLL1 CLK_PLL_CONFIG register, PLL_LF_MODE bit */
    cy_en_fll_pll_output_mode_t pll1OutputMode;         /**< PLL1 CLK_PLL_CONFIG register, BYPASS_SEL bits */

    /* The number of clock paths available for the device is defined in CY_SRSS_NUM_CLKPATH.
     * Max 6 clock paths are defined */

    /* Clock Paths Configuration */
    cy_en_clkpath_in_sources_t path0Src;                /**< Input multiplexer0 clock source */
    cy_en_clkpath_in_sources_t path1Src;                /**< Input multiplexer1 clock source */
    cy_en_clkpath_in_sources_t path2Src;                /**< Input multiplexer2 clock source */
    cy_en_clkpath_in_sources_t path3Src;                /**< Input multiplexer3 clock source */
    cy_en_clkpath_in_sources_t path4Src;                /**< Input multiplexer4 clock source */
    cy_en_clkpath_in_sources_t path5Src;                /**< Input multiplexer5 clock source */

    /* Clock Dividers */
    uint8_t clkFastDiv;                                 /**< Fast clock divider. User has to pass actual divider-1 */
    uint8_t clkPeriDiv;                                 /**< Peri clock divider. User has to pass actual divider-1 */
    uint8_t clkSlowDiv;                                 /**< Slow clock divider. User has to pass actual divider-1 */

    /* The number of HF clocks is defined in the device specific header CY_SRSS_NUM_HFROOT
     * Max 6 HFs are defined */
     /* HF Configurations */
    cy_en_clkhf_in_sources_t hf0Source;                 /**< HF0 Source Clock Path */
    cy_en_clkhf_dividers_t hf0Divider;                  /**< HF0 Divider */
    uint32_t hf0OutFreqMHz;                             /**< HF0 Output Frequency in MHz */
    cy_en_clkhf_in_sources_t hf1Source;                 /**< HF1 Source Clock Path */
    cy_en_clkhf_dividers_t hf1Divider;                  /**< HF1 Divider */
    uint32_t hf1OutFreqMHz;                             /**< HF1 Output Frequency in MHz */
    cy_en_clkhf_in_sources_t hf2Source;                 /**< HF2 Source Clock Path */
    cy_en_clkhf_dividers_t hf2Divider;                  /**< HF2 Divider */
    uint32_t hf2OutFreqMHz;                             /**< HF2 Output Frequency in MHz */
    cy_en_clkhf_in_sources_t hf3Source;                 /**< HF3 Source Clock Path */
    cy_en_clkhf_dividers_t hf3Divider;                  /**< HF3 Divider */
    uint32_t hf3OutFreqMHz;                             /**< HF3 Output Frequency in MHz */
    cy_en_clkhf_in_sources_t hf4Source;                 /**< HF4 Source Clock Path */
    cy_en_clkhf_dividers_t hf4Divider;                  /**< HF4 Divider */
    uint32_t hf4OutFreqMHz;                             /**< HF4 Output Frequency in MHz */
    cy_en_clkhf_in_sources_t hf5Source;                 /**< HF5 Source Clock Path */
    cy_en_clkhf_dividers_t hf5Divider;                  /**< HF5 Divider */
    uint32_t hf5OutFreqMHz;                             /**< HF5 Output Frequency in MHz */
    cy_en_clkpump_in_sources_t pumpSource;              /**< PUMP Source Clock Path */
    cy_en_clkpump_divide_t pumpDivider;                 /**< PUMP Divider */

    /* Misc clock configurations */
    cy_en_clklf_in_sources_t clkLfSource;               /**< Clock LF Source */
    cy_en_clkbak_in_sources_t clkBakSource;             /**< Clock Backup domain Source */
    cy_en_clktimer_in_sources_t clkTimerSource;         /**< Clock Timer Source */
    uint8_t clkTimerDivider;                            /**< Clock Timer Divider */
    cy_en_systick_clock_source_t clkSrcAltSysTick;      /**< SysTick Source */

    /* BLE ECO */
    uint32_t altHFcLoad;                                /**< Load Cap (pF) */
    uint32_t altHFxtalStartUpTime;                      /**< Startup Time (us) */
    uint32_t altHFclkFreq;                              /**< Clock Frequency. 0 -> 16MHz and 1 -> 32MHz. Any other value except 0 and 1 is invalid */
    uint32_t altHFsysClkDiv;                            /**< Clock Divider */
    uint32_t altHFvoltageReg;                           /**< BLE Voltage Regulator */
} cy_stc_pra_system_config_t;
/** \} group_pra_stc */

/** \cond INTERNAL */
/* External clock provisioned configuration */
typedef struct
{
    bool extClkEnable;                                  /* EXTCLK Enable */
    bool ecoEnable;                                     /* ECO Enable */
    bool wcoEnable;                                     /* WCO Enable */
    bool bypassEnable;                                  /* WCO Clock port bypass to External sine wave or to normal crystal */

    /* EXTCLK Configuration */
    uint32_t extClkFreqHz;                              /* External clock frequency in Hz */
    GPIO_PRT_Type *extClkPort;                          /* External connection port */
    uint32_t extClkPinNum;                              /* External connection pin */

    /* ECO Configuration */
    uint32_t ecoFreqHz;                                 /* ECO Frequency in Hz */
    uint32_t ecoLoad;                                   /* Parallel Load Capacitance (pF) */
    uint32_t ecoEsr;                                    /* Equivalent series resistance (ohm) */
    uint32_t ecoDriveLevel;                             /* Drive Level (uW) */
    GPIO_PRT_Type *ecoInPort;                           /* ECO input port */
    GPIO_PRT_Type *ecoOutPort;                          /* ECO output port */
    uint32_t ecoInPinNum;                               /* ECO input pin number */
    uint32_t ecoOutPinNum;                              /* ECO output pin number */

    /* WCO Configuration */
    GPIO_PRT_Type *wcoInPort;                           /* WCO Input port */
    GPIO_PRT_Type *wcoOutPort;                          /* WCO Output port */
    uint32_t wcoInPinNum;                               /* WCO Input pin */
    uint32_t wcoOutPinNum;                              /* WCO Output pin */

} cy_stc_pra_extclk_policy_t;
/** \endcond */

/*******************************************************************************
*        Global variables
*******************************************************************************/
/** \cond INTERNAL */
/* External clock provisioned configuration */
extern cy_stc_pra_extclk_policy_t *extClkPolicyPtr;
/** \endcond */

/*******************************************************************************
*        Function Prototypes
*******************************************************************************/

/**
* \addtogroup group_pra_functions
* \{
*/

cy_en_pra_status_t Cy_PRA_SystemConfig(const cy_stc_pra_system_config_t *devConfig);

/** \} group_pra_functions */

#if (CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN)
uint32_t Cy_PRA_CalculateFLLOutFreq(const cy_stc_pra_system_config_t *devConfig);
uint32_t Cy_PRA_CalculatePLLOutFreq(uint8_t pll, const cy_stc_pra_system_config_t *devConfig);
#endif /* (CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN) */

#ifdef __cplusplus
}
#endif

#endif /* (CY_DEVICE_SECURE) */

#endif /* defined (CY_IP_MXS40SRSS) */

#endif /* #if !defined(CY_PRA_CFG_H) */

/* [] END OF FILE */
