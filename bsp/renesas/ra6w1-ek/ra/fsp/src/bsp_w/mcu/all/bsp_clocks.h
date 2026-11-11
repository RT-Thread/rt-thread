/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_CLOCKS_H
#define BSP_CLOCKS_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_clock_cfg.h"
#include "bsp_api.h"

#if BSP_MCU_GROUP_RA6W1
 #include "../ra6w1/bsp_clocks.h"
#endif

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* The following definitions are macros instead of enums because the values are used in preprocessor conditionals. */
#define BSP_CLOCKS_SOURCE_CLOCK_RCHS          (0)
#define BSP_CLOCKS_SOURCE_CLOCK_XTALM         (1)
#define BSP_CLOCKS_SOURCE_CLOCK_XTALM_DBLR    (2)
#define BSP_CLOCKS_SOURCE_CLOCK_PLL           (3)
#define BSP_CLOCKS_SOURCE_CLOCK_RCLP          (4)
#define BSP_CLOCKS_SOURCE_CLOCK_RCX           (5)
#define BSP_CLOCKS_SOURCE_CLOCK_XTALK         (6)
#define BSP_CLOCKS_SOURCE_CLOCK_DIGITAL       (7) // External square wave clock.

#if BSP_CLOCK_CFG_MAIN_OSC_POPULATED
 #define BSP_PRV_PLL_SUPPORTED                (1)
#else
 #define BSP_PRV_PLL_SUPPORTED                (0)
#endif

#if BSP_FEATURE_CGC_HAS_HCLK_DIV
 #define BSP_PRV_HCLK_DIV_MASK                (CRG_TOP_CLK_AMBA_REG_HCLK_DIV_Msk)
#else
 #define BSP_PRV_HCLK_DIV_MASK                (0)
#endif

#if BSP_FEATURE_CGC_HAS_PCLK_DIV
 #define BSP_PRV_PCLK_DIV_MASK                (CRG_TOP_CLK_AMBA_REG_PCLK_DIV_Msk)
#else
 #define BSP_PRV_PCLK_DIV_MASK                (0)
#endif

#if BSP_FEATURE_CGC_HAS_QCLK_DIV
 #define BSP_PRV_QCLK_DIV_MASK                (CRG_TOP_CLK_AMBA_REG_QSPI_SDR_DIV2_Msk)
#else
 #define BSP_PRV_QCLK_DIV_MASK                (0)
#endif

#define BSP_PRV_CLK_AMBA_REG_DIV              (BSP_PRV_HCLK_DIV_MASK | BSP_PRV_PCLK_DIV_MASK | BSP_PRV_QCLK_DIV_MASK)

#if BSP_PRV_PLL_SUPPORTED
 #define BSP_PRV_PLL_SOURCE_FREQ_HZ           (BSP_CFG_XTALM_HZ)
#endif
#if BSP_PRV_PLL2_SUPPORTED
 #define BSP_PRV_PLL2_SOURCE_FREQ_HZ          (BSP_CFG_XTALM_HZ)
#endif

/* Frequencies of clocks with fixed frequencies. */
#define BSP_DIVN_FREQ_HZ                      (32000000U) // DIVN frequency is 32 MHz
#if BSP_FEATURE_CGC_HAS_RCLP_SPEEDS
 #define BSP_RCLP_DEFAULT_SPEED_MODE          (0)
 #define BSP_RCLP_32K_SPEED_MODE              (1)
 #define BSP_RCLP_512K_SPEED_MODE             (2)

 #define BSP_RCLP_HIGH_SPEED_FREQ_HZ          (512000U)
 #define BSP_RCLP_LOW_SPEED_FREQ_HZ           (32000U)
#endif

#if BSP_PRV_PLL_SUPPORTED
 #if BSP_FPGA
  #define BSP_PLL_FREQ_HZ                     (32000000)
 #else
  #if BSP_MCU_GROUP_RA6B1 || BSP_MCU_GROUP_RA6U1
   #define BSP_PLL_FREQ_HZ                    (128000000)
  #elif BSP_MCU_GROUP_RA6W1
   #define BSP_PLL_FREQ_HZ                    (480000000)
  #endif
 #endif
#endif

#if BSP_FEATURE_CGC_HAS_RCHS_SPEEDS
 #define BSP_RCHS_32M_SPEED_MODE             (0)
 #define BSP_RCHS_64M_SPEED_MODE             (1)
#endif

#if BSP_CLOCKS_SOURCE_CLOCK_RCHS == BSP_CFG_CLOCK_SOURCE
 #define BSP_STARTUP_SOURCE_CLOCK_HZ         (BSP_RCHS_HZ)
#elif BSP_CLOCKS_SOURCE_CLOCK_XTALM == BSP_CFG_CLOCK_SOURCE
 #define BSP_STARTUP_SOURCE_CLOCK_HZ         (BSP_CFG_XTALM_HZ)
#elif BSP_CLOCKS_SOURCE_CLOCK_XTALM_DBLR == BSP_CFG_CLOCK_SOURCE
 #define BSP_STARTUP_SOURCE_CLOCK_HZ         (2 * BSP_CFG_XTALM_HZ)
#elif BSP_CLOCKS_SOURCE_CLOCK_PLL == BSP_CFG_CLOCK_SOURCE
 #define BSP_STARTUP_SOURCE_CLOCK_HZ         (BSP_CFG_PLL_FREQUENCY_HZ)
#elif BSP_CLOCKS_SOURCE_CLOCK_RCLP == BSP_CFG_CLOCK_SOURCE
 #define BSP_STARTUP_SOURCE_CLOCK_HZ         (BSP_RCLP_HZ)
#endif

#if BSP_FEATURE_CGC_HAS_LP_CLOCK
 #if BSP_CLOCKS_SOURCE_CLOCK_RCLP == BSP_CFG_LP_CLOCK_SOURCE
  #define BSP_STARTUP_LP_CLOCK_HZ            (BSP_RCLP_HZ)
 #elif BSP_CLOCKS_SOURCE_CLOCK_RCX == BSP_CFG_LP_CLOCK_SOURCE
  #define BSP_STARTUP_LP_CLOCK_HZ            (BSP_RCX_HZ)
 #elif BSP_CLOCKS_SOURCE_CLOCK_XTALK == BSP_CFG_LP_CLOCK_SOURCE
  #define BSP_STARTUP_LP_CLOCK_HZ            (BSP_CFG_XTALK_HZ)
 #endif
#endif

#define BSP_CLOCKS_SYS_CLOCK_DIV_1           (0U) // System clock divided by 1.
#define BSP_CLOCKS_SYS_CLOCK_DIV_2           (1U) // System clock divided by 2.
#define BSP_CLOCKS_SYS_CLOCK_DIV_4           (2U) // System clock divided by 4.
#define BSP_CLOCKS_SYS_CLOCK_DIV_8           (3U) // System clock divided by 8.
#define BSP_CLOCKS_SYS_CLOCK_DIV_16          (4U) // HCLK divided by 16.

/* SPI clock output divider options. */
#define BSP_CLOCKS_SPI_CLK_DIV_8             (0U) // SPI clock divided by 8.
#define BSP_CLOCKS_SPI_CLK_DIV_4             (1U) // SPI clock divided by 4.
#define BSP_CLOCKS_SPI_CLK_DIV_2             (2U) // SPI clock divided by 2.
#define BSP_CLOCKS_SPI_CLK_DIV_14            (3U) // SPI clock divided by 14.

/* QSPI clock output divider options. */
#define BSP_CLOCKS_QSPI_CLK_DIV_1            (0U) // QSPI clock divided by 1.
#define BSP_CLOCKS_QSPI_CLK_DIV_2            (1U) // QSPI clock divided by 2.
#define BSP_CLOCKS_QSPI_CLK_DIV_4            (2U) // QSPI clock divided by 4.
#define BSP_CLOCKS_QSPI_CLK_DIV_8            (3U) // QSPI clock divided by 8.

/* WDOG clock output divider options. */
#define BSP_CLOCKS_WDOG_DIV_320              (1U) // WDOG clock is LP CLK divided by 320.

/* Configuration option used to disable a clock, or to select DIV1/DIVN as source. */
#define BSP_CLOCKS_SOURCE_CLOCK_DISABLED     (0xFFU)
#define BSP_CLOCKS_SOURCE_CLOCK_DIV1         (0U)
#define BSP_CLOCKS_SOURCE_CLOCK_DIV2         (1U)
#define BSP_CLOCKS_SOURCE_CLOCK_DIVN         (2U)
#define BSP_CLOCKS_SOURCE_CLOCK_DIVN_DIV2    (2U) // Only for GPADC.

// NOLINTEND(modernize-macro-to-enum)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if BSP_TZ_SECURE_BUILD || BSP_TZ_NONSECURE_BUILD
typedef struct
{
    uint32_t pll_freq;
} bsp_clock_update_callback_args_t;

 #if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * bsp_clock_update_callback_t)(bsp_clock_update_callback_args_t *
                                                                     p_callback_args);
 #elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile bsp_clock_update_callback_t)(bsp_clock_update_callback_args_t *
                                                                             p_callback_args);
 #endif

#endif

#if BSP_FEATURE_CGC_HAS_RCLP_SPEEDS

/**
 * @brief RCLP mode selection
 */
typedef enum e_bsp_clock_rclp_speed
{
    BSP_CLOCK_RCLP_SPEED_DEFAULT = BSP_RCLP_DEFAULT_SPEED_MODE, ///< Default RCLP speed mode (automatically switches to 32
    /// kHz during sleep and to 512 kHz during active)
    BSP_CLOCK_RCLP_SPEED_32K  = BSP_RCLP_32K_SPEED_MODE,        ///< Low  speed RCLP mode (32  kHz)
    BSP_CLOCK_RCLP_SPEED_512K = BSP_RCLP_512K_SPEED_MODE,       ///< High speed RCLP mode (512 kHz)
} bsp_clock_rclp_speed_t;
#endif /* BSP_FEATURE_CGC_HAS_RCLP_SPEEDS */

#if BSP_FEATURE_CGC_HAS_RCHS_SPEEDS

/**
 * @brief RCHS mode selection
 */
typedef enum e_bsp_clock_rchs_speed
{
    BSP_CLOCK_RCHS_SPEED_32M = BSP_RCHS_32M_SPEED_MODE, ///< High speed RCHS speed (32 MHz)
    BSP_CLOCK_RCHS_SPEED_64M = BSP_RCHS_64M_SPEED_MODE, ///< Low  speed RCHS speed (64 MHz)
} bsp_clock_rchs_speed_t;
#endif /* BSP_FEATURE_CGC_HAS_RCHS_SPEEDS */

/**
 * @brief The type of clock to be measured
 */
typedef enum e_bsp_clock_msr_sel
{
    BSP_CLOCK_MSR_SEL_RCLP     = 0,
    BSP_CLOCK_MSR_SEL_RCHS     = 1,
    BSP_CLOCK_MSR_SEL_RCX      = 2,
    BSP_CLOCK_MSR_SEL_XTAL32K  = 3,
    BSP_CLOCK_MSR_SEL_XTAL32M  = 4,
    BSP_CLOCK_MSR_SEL_XTAL64M  = 5,
    BSP_CLOCK_MSR_SEL_EXTERNAL = 6,
    BSP_CLOCK_MSR_SEL_DIVN     = 7,
} bsp_clock_msr_sel_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
#if BSP_FEATURE_CGC_HAS_LP_CLOCK
extern uint32_t g_bsp_lp_clock;        /** System Clock Frequency (Low Power Clock) */
extern uint32_t g_clock_freq[];
#endif

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

void bsp_clock_rchs_enable(bool enable);
bool bsp_clock_rchs_is_enabled(void);

#if BSP_FEATURE_CGC_HAS_RCHS_SPEEDS
fsp_err_t bsp_clock_rchs_high_speed_preconditions_check(void);
void      bsp_clock_rchs_speed_set(bsp_clock_rchs_speed_t speed);

#endif

void bsp_clock_rclp_enable(bool enable);
bool bsp_clock_rclp_is_enabled(void);

#if BSP_FEATURE_CGC_HAS_RCLP_SPEEDS
void bsp_clock_rclp_speed_set(bsp_clock_rclp_speed_t speed);

#endif

#if BSP_FEATURE_CGC_HAS_RCX_CONTROL
void bsp_clock_rcx_enable(bool enable);

#endif

bool bsp_clock_rcx_is_enabled(void);

#if BSP_CLOCK_CFG_MAIN_OSC_POPULATED
fsp_err_t bsp_clock_xtalm_preconditions_check(void);
void      bsp_clock_xtalm_configure(void);
void      bsp_clock_xtalm_enable(bool enable);
bool      bsp_clock_xtalm_is_enabled(void);
bool      bsp_clock_xtalm_is_settled(void);

 #if BSP_FEATURE_CGC_HAS_XTALM_READY_COUNTER
int16_t bsp_clock_xtalm_ready_counter_update(void);

 #endif
 #if BSP_FEATURE_CGC_HAS_XTALM_DBLR
void bsp_clock_xtalm_64m_output_enable(bool enable);
bool bsp_clock_xtalm_64m_output_is_enabled(void);

 #endif
#endif

#if BSP_FEATURE_CGC_HAS_SOSC
void bsp_clock_xtalk_enable(bool enable);

 #if BSP_CLOCK_CFG_SUBCLOCK_POPULATED
void bsp_clock_xtalk_configure(void);
bool bsp_clock_xtalk_is_enabled(void);

 #endif
#endif

#if BSP_PRV_PLL_SUPPORTED
fsp_err_t bsp_clock_pll_preconditions_check(void);
void      bsp_clock_check_core_voltage_before_switch_sysclk_to_pll(void);
void      bsp_clock_pll_enable(bool enable);
bool      bsp_clock_pll_is_enabled(void);
bool      bsp_clock_pll_is_locked(void);

 #if BSP_MCU_GROUP_RA6B1 || BSP_MCU_GROUP_RA6U1
void bsp_clock_usbpll_enable(bool enable);
bool bsp_clock_usbpll_is_locked(void);

 #endif

#endif

#if BSP_FEATURE_CGC_HAS_LP_CLOCK
void bsp_clock_lpclk_set(fsp_priv_source_clock_t clock);

#endif

void bsp_clock_sysclk_set(fsp_priv_source_clock_t clock);
void bsp_clock_set(fsp_priv_source_clock_t clock, uint32_t clk_amba_reg_div);
void bsp_clock_hclk_set(uint8_t sys_clock_sel, uint8_t hclk_div);

#if !BSP_MCU_GROUP_RA6W1 && !BSP_MCU_GROUP_RA6W3

uint32_t bsp_clock_measurement(bsp_clock_msr_sel_t target, bsp_clock_msr_sel_t ref, uint32_t cycles);
void     bsp_clock_measurement_configure(bsp_clock_msr_sel_t target, bsp_clock_msr_sel_t ref, uint32_t cycles);

__STATIC_FORCEINLINE void bsp_clock_measurement_start (void)
{
    ANAMISC->CLK_REF_SEL_REG_b.REF_CAL_START = 1;
}

__STATIC_FORCEINLINE uint32_t bsp_clock_measurement_read (void)
{
    return ANAMISC->CLK_REF_VAL_REG;
}

#endif

#if BSP_FEATURE_CGC_HAS_LP_CLOCK
uint32_t R_BSP_LPClockHzGet(void);
void     R_BSP_LPClockUpdate(void);

#endif

void bsp_clock_init(void);

#if BSP_TZ_NONSECURE_BUILD
void bsp_clock_freq_var_init(void);

#endif

#if BSP_TZ_SECURE_BUILD
void r_bsp_clock_update_callback_set(bsp_clock_update_callback_t        p_callback,
                                     bsp_clock_update_callback_args_t * p_callback_memory);

#endif

/* RTC Initialization */
#if BSP_FEATURE_RTC_IS_AVAILABLE
void R_BSP_Init_RTC(void);

#endif

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
