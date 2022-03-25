/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#ifndef BSP_CLOCKS_H
#define BSP_CLOCKS_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_clock_cfg.h"
#include "bsp_api.h"

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* The following definitions are macros instead of enums because the values are used in preprocessor conditionals. */
/* Must match SCKCR.CKSEL values. */
#define BSP_CLOCKS_SOURCE_CLOCK_HOCO        (0) // The high speed on chip oscillator.
#define BSP_CLOCKS_SOURCE_CLOCK_MOCO        (1) // The middle speed on chip oscillator.
#define BSP_CLOCKS_SOURCE_CLOCK_LOCO        (2) // The low speed on chip oscillator.
#define BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC    (3) // The main oscillator.
#define BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK    (4) // The subclock oscillator.
#define BSP_CLOCKS_SOURCE_CLOCK_PLL         (5) // The PLL oscillator.
#define BSP_CLOCKS_SOURCE_CLOCK_PLL2        (6) // The PLL2 oscillator.

/* PLLs are not supported in the following scenarios:
 *  - When using low voltage mode
 *  - When using an MCU that does not have a PLL
 *  - When the PLL only accepts the main oscillator as a source and XTAL is not used
 */
#if BSP_FEATURE_CGC_HAS_PLL && !BSP_CFG_USE_LOW_VOLTAGE_MODE && \
    !((1U != BSP_FEATURE_CGC_PLLCCR_TYPE) && !BSP_CLOCK_CFG_MAIN_OSC_POPULATED)
 #define BSP_PRV_PLL_SUPPORTED              (1)
 #if BSP_FEATURE_CGC_HAS_PLL2
  #define BSP_PRV_PLL2_SUPPORTED            (1)
 #else
  #define BSP_PRV_PLL2_SUPPORTED            (0)
 #endif
#else
 #define BSP_PRV_PLL_SUPPORTED              (0)
 #define BSP_PRV_PLL2_SUPPORTED             (0)
#endif

/* The ICLK frequency at startup is used to determine the ideal operating mode to set after startup. The PLL frequency
 * calculated here is also used to initialize the g_clock_freq array. */
#if BSP_PRV_PLL_SUPPORTED
 #if (1U == BSP_FEATURE_CGC_PLLCCR_TYPE) && (BSP_CLOCKS_SOURCE_CLOCK_HOCO == BSP_CFG_PLL_SOURCE)
  #define BSP_PRV_PLL_SOURCE_FREQ_HZ           (BSP_HOCO_HZ)
 #else
  #define BSP_PRV_PLL_SOURCE_FREQ_HZ           (BSP_CFG_XTAL_HZ)
 #endif
#endif
#if BSP_PRV_PLL2_SUPPORTED
 #if BSP_CLOCKS_SOURCE_CLOCK_HOCO == BSP_CFG_PLL2_SOURCE
  #define BSP_PRV_PLL2_SOURCE_FREQ_HZ          (BSP_HOCO_HZ)
 #else
  #define BSP_PRV_PLL2_SOURCE_FREQ_HZ          (BSP_CFG_XTAL_HZ)
 #endif
#endif

/* Frequencies of clocks with fixed freqencies. */
#define BSP_LOCO_FREQ_HZ                       (32768U)   // LOCO frequency is fixed at 32768 Hz
#define BSP_SUBCLOCK_FREQ_HZ                   (32768U)   // Subclock frequency is 32768 Hz
#define BSP_MOCO_FREQ_HZ                       (8000000U) // MOCO frequency is fixed at 8 MHz

#if BSP_CLOCKS_SOURCE_CLOCK_HOCO == BSP_CFG_CLOCK_SOURCE
 #define BSP_STARTUP_SOURCE_CLOCK_HZ           (BSP_HOCO_HZ)
#elif BSP_CLOCKS_SOURCE_CLOCK_MOCO == BSP_CFG_CLOCK_SOURCE
 #define BSP_STARTUP_SOURCE_CLOCK_HZ           (BSP_MOCO_FREQ_HZ)
#elif BSP_CLOCKS_SOURCE_CLOCK_LOCO == BSP_CFG_CLOCK_SOURCE
 #define BSP_STARTUP_SOURCE_CLOCK_HZ           (BSP_LOCO_FREQ_HZ)
#elif BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK == BSP_CFG_CLOCK_SOURCE
 #define BSP_STARTUP_SOURCE_CLOCK_HZ           (BSP_SUBCLOCK_FREQ_HZ)
#elif BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC == BSP_CFG_CLOCK_SOURCE
 #define BSP_STARTUP_SOURCE_CLOCK_HZ           (BSP_CFG_XTAL_HZ)
#elif BSP_CLOCKS_SOURCE_CLOCK_PLL == BSP_CFG_CLOCK_SOURCE
 #if (1U == BSP_FEATURE_CGC_PLLCCR_TYPE)
  #if BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC == BSP_CFG_PLL_SOURCE
   #define BSP_PRV_PLL_SOURCE_FREQ_HZ          (BSP_CFG_XTAL_HZ)
  #elif BSP_CLOCKS_SOURCE_CLOCK_HOCO == BSP_CFG_PLL_SOURCE
   #define BSP_PRV_PLL_SOURCE_FREQ_HZ          (BSP_HOCO_HZ)
  #endif
  #define BSP_STARTUP_SOURCE_CLOCK_HZ          (((BSP_PRV_PLL_SOURCE_FREQ_HZ * (BSP_CFG_PLL_MUL + 1U)) >> 1) / \
                                                (BSP_CFG_PLL_DIV + 1U))
 #elif (2U == BSP_FEATURE_CGC_PLLCCR_TYPE)
  #define BSP_PRV_PLL_SOURCE_FREQ_HZ           (BSP_CFG_XTAL_HZ)
  #define BSP_STARTUP_SOURCE_CLOCK_HZ          ((BSP_PRV_PLL_SOURCE_FREQ_HZ * ((BSP_CFG_PLL_MUL + 1U) >> 1)) >> \
                                                (BSP_CFG_PLL_DIV))
 #endif
#endif

/* Startup clock frequency of each system clock. These macros are only helpful if the system clock and dividers have
 * not changed since startup. These macros are not used in FSP modules except for the clock startup code. */
#define BSP_STARTUP_ICLK_HZ                    (BSP_STARTUP_SOURCE_CLOCK_HZ >> BSP_CFG_ICLK_DIV)
#define BSP_STARTUP_PCLKA_HZ                   (BSP_STARTUP_SOURCE_CLOCK_HZ >> BSP_CFG_PCLKA_DIV)
#define BSP_STARTUP_PCLKB_HZ                   (BSP_STARTUP_SOURCE_CLOCK_HZ >> BSP_CFG_PCLKB_DIV)
#define BSP_STARTUP_PCLKC_HZ                   (BSP_STARTUP_SOURCE_CLOCK_HZ >> BSP_CFG_PCLKC_DIV)
#define BSP_STARTUP_PCLKD_HZ                   (BSP_STARTUP_SOURCE_CLOCK_HZ >> BSP_CFG_PCLKD_DIV)
#define BSP_STARTUP_BCLK_HZ                    (BSP_STARTUP_SOURCE_CLOCK_HZ >> BSP_CFG_BCLK_DIV)
#define BSP_STARTUP_FCLK_HZ                    (BSP_STARTUP_SOURCE_CLOCK_HZ >> BSP_CFG_FCLK_DIV)

/* System clock divider options. */
#define BSP_CLOCKS_SYS_CLOCK_DIV_1             (0) // System clock divided by 1.
#define BSP_CLOCKS_SYS_CLOCK_DIV_2             (1) // System clock divided by 2.
#define BSP_CLOCKS_SYS_CLOCK_DIV_4             (2) // System clock divided by 4.
#define BSP_CLOCKS_SYS_CLOCK_DIV_8             (3) // System clock divided by 8.
#define BSP_CLOCKS_SYS_CLOCK_DIV_16            (4) // System clock divided by 16.
#define BSP_CLOCKS_SYS_CLOCK_DIV_32            (5) // System clock divided by 32.
#define BSP_CLOCKS_SYS_CLOCK_DIV_64            (6) // System clock divided by 64.
#define BSP_CLOCKS_SYS_CLOCK_DIV_128           (7) // System clock divided by 128 (available for CLKOUT only).

/* USB clock divider options. */
#define BSP_CLOCKS_USB_CLOCK_DIV_3             (2) // Divide USB source clock by 3
#define BSP_CLOCKS_USB_CLOCK_DIV_4             (3) // Divide USB source clock by 4
#define BSP_CLOCKS_USB_CLOCK_DIV_5             (4) // Divide USB source clock by 5

/* OCTA clock divider options. */
#define BSP_CLOCKS_OCTA_CLOCK_DIV_1            (0) // Divide OCTA source clock by 1
#define BSP_CLOCKS_OCTA_CLOCK_DIV_2            (1) // Divide OCTA source clock by 2
#define BSP_CLOCKS_OCTA_CLOCK_DIV_4            (2) // Divide OCTA source clock by 4
#define BSP_CLOCKS_OCTA_CLOCK_DIV_6            (3) // Divide OCTA source clock by 6
#define BSP_CLOCKS_OCTA_CLOCK_DIV_8            (4) // Divide OCTA source clock by 8

/* CANFD clock divider options. */
#define BSP_CLOCKS_CANFD_CLOCK_DIV_1           (0) // Divide CANFD source clock by 1
#define BSP_CLOCKS_CANFD_CLOCK_DIV_2           (1) // Divide CANFD source clock by 2
#define BSP_CLOCKS_CANFD_CLOCK_DIV_4           (2) // Divide CANFD source clock by 4
#define BSP_CLOCKS_CANFD_CLOCK_DIV_6           (3) // Divide CANFD source clock by 6
#define BSP_CLOCKS_CANFD_CLOCK_DIV_8           (4) // Divide CANFD source clock by 8

/* SCISPI clock divider options. */
#define BSP_CLOCKS_SCISPI_CLOCK_DIV_1          (0) // Divide SCISPI source clock by 1
#define BSP_CLOCKS_SCISPI_CLOCK_DIV_2          (1) // Divide SCISPI source clock by 2
#define BSP_CLOCKS_SCISPI_CLOCK_DIV_4          (2) // Divide SCISPI source clock by 4
#define BSP_CLOCKS_SCISPI_CLOCK_DIV_6          (3) // Divide SCISPI source clock by 6
#define BSP_CLOCKS_SCISPI_CLOCK_DIV_8          (4) // Divide SCISPI source clock by 8

/* GPT clock divider options. */
#define BSP_CLOCKS_GPT_CLOCK_DIV_1             (0) // Divide GPT source clock by 1
#define BSP_CLOCKS_GPT_CLOCK_DIV_2             (1) // Divide GPT source clock by 2
#define BSP_CLOCKS_GPT_CLOCK_DIV_4             (2) // Divide GPT source clock by 4
#define BSP_CLOCKS_GPT_CLOCK_DIV_6             (3) // Divide GPT source clock by 6
#define BSP_CLOCKS_GPT_CLOCK_DIV_8             (4) // Divide GPT source clock by 8

/* IIC clock divider options. */
#define BSP_CLOCKS_IIC_CLOCK_DIV_1             (0) // Divide IIC source clock by 1
#define BSP_CLOCKS_IIC_CLOCK_DIV_2             (1) // Divide IIC source clock by 2
#define BSP_CLOCKS_IIC_CLOCK_DIV_4             (2) // Divide IIC source clock by 4
#define BSP_CLOCKS_IIC_CLOCK_DIV_6             (3) // Divide IIC source clock by 6
#define BSP_CLOCKS_IIC_CLOCK_DIV_8             (4) // Divide IIC source clock by 8

/* PLL divider options. */
#define BSP_CLOCKS_PLL_DIV_1                   (0)
#define BSP_CLOCKS_PLL_DIV_2                   (1)
#define BSP_CLOCKS_PLL_DIV_3                   (2)
#define BSP_CLOCKS_PLL_DIV_4                   (2)

/* PLL multiplier options. */
#define BSP_CLOCKS_PLL_MUL_8_0                 (0xF)
#define BSP_CLOCKS_PLL_MUL_9_0                 (0x11)
#define BSP_CLOCKS_PLL_MUL_10_0                (0x13)
#define BSP_CLOCKS_PLL_MUL_10_5                (0x14)
#define BSP_CLOCKS_PLL_MUL_11_0                (0x15)
#define BSP_CLOCKS_PLL_MUL_11_5                (0x16)
#define BSP_CLOCKS_PLL_MUL_12_0                (0x17)
#define BSP_CLOCKS_PLL_MUL_12_5                (0x18)
#define BSP_CLOCKS_PLL_MUL_13_0                (0x19)
#define BSP_CLOCKS_PLL_MUL_13_5                (0x1A)
#define BSP_CLOCKS_PLL_MUL_14_0                (0x1B)
#define BSP_CLOCKS_PLL_MUL_14_5                (0x1c)
#define BSP_CLOCKS_PLL_MUL_15_0                (0x1d)
#define BSP_CLOCKS_PLL_MUL_15_5                (0x1e)
#define BSP_CLOCKS_PLL_MUL_16_0                (0x1f)
#define BSP_CLOCKS_PLL_MUL_16_5                (0x20)
#define BSP_CLOCKS_PLL_MUL_17_0                (0x21)
#define BSP_CLOCKS_PLL_MUL_17_5                (0x22)
#define BSP_CLOCKS_PLL_MUL_18_0                (0x23)
#define BSP_CLOCKS_PLL_MUL_18_5                (0x24)
#define BSP_CLOCKS_PLL_MUL_19_0                (0x25)
#define BSP_CLOCKS_PLL_MUL_19_5                (0x26)
#define BSP_CLOCKS_PLL_MUL_20_0                (0x27)
#define BSP_CLOCKS_PLL_MUL_20_5                (0x28)
#define BSP_CLOCKS_PLL_MUL_21_0                (0x29)
#define BSP_CLOCKS_PLL_MUL_21_5                (0x2A)
#define BSP_CLOCKS_PLL_MUL_22_0                (0x2B)
#define BSP_CLOCKS_PLL_MUL_22_5                (0x2c)
#define BSP_CLOCKS_PLL_MUL_23_0                (0x2d)
#define BSP_CLOCKS_PLL_MUL_23_5                (0x2e)
#define BSP_CLOCKS_PLL_MUL_24_0                (0x2f)
#define BSP_CLOCKS_PLL_MUL_24_5                (0x30)
#define BSP_CLOCKS_PLL_MUL_25_0                (0x31)
#define BSP_CLOCKS_PLL_MUL_25_5                (0x32)
#define BSP_CLOCKS_PLL_MUL_26_0                (0x33)
#define BSP_CLOCKS_PLL_MUL_26_5                (0x34)
#define BSP_CLOCKS_PLL_MUL_27_0                (0x35)
#define BSP_CLOCKS_PLL_MUL_27_5                (0x36)
#define BSP_CLOCKS_PLL_MUL_28_0                (0x37)
#define BSP_CLOCKS_PLL_MUL_28_5                (0x38)
#define BSP_CLOCKS_PLL_MUL_29_0                (0x39)
#define BSP_CLOCKS_PLL_MUL_29_5                (0x3A)
#define BSP_CLOCKS_PLL_MUL_30_0                (0x3B)
#define BSP_CLOCKS_PLL_MUL_31_0                (0x3D)

/* Configuration option used to disable clock output. */
#define BSP_CLOCKS_CLOCK_DISABLED              (0xFFU)

/* HOCO cycles per microsecond. */
#define BSP_PRV_HOCO_CYCLES_PER_US             (BSP_HOCO_HZ / 1000000U)

/* Maximum number of delay cycles required to ensure 1 us passes between setting PLLCCR and clearing PLLCR. */
#if BSP_HOCO_HZ < 48000000U
 #define BSP_PRV_MAX_HOCO_CYCLES_PER_US        (BSP_PRV_HOCO_CYCLES_PER_US)
#else
 #define BSP_PRV_MAX_HOCO_CYCLES_PER_US        (48U)
#endif

/* Create a mask of valid bits in SCKDIVCR. */
#define BSP_PRV_SCKDIVCR_ICLK_MASK             (7U << 24)
#if BSP_FEATURE_CGC_HAS_PCLKD
 #define BSP_PRV_SCKDIVCR_PCLKD_MASK           (7U << 0)
#else
 #define BSP_PRV_SCKDIVCR_PCLKD_MASK           (0U)
#endif
#if BSP_FEATURE_CGC_HAS_PCLKC
 #define BSP_PRV_SCKDIVCR_PCLKC_MASK           (7U << 4)
#else
 #define BSP_PRV_SCKDIVCR_PCLKC_MASK           (0U)
#endif
#if BSP_FEATURE_CGC_HAS_PCLKB
 #define BSP_PRV_SCKDIVCR_PCLKB_MASK           (7U << 8)
#else
 #define BSP_PRV_SCKDIVCR_PCLKB_MASK           (0U)
#endif
#if BSP_FEATURE_CGC_HAS_PCLKA
 #define BSP_PRV_SCKDIVCR_PCLKA_MASK           (7U << 12)
#else
 #define BSP_PRV_SCKDIVCR_PCLKA_MASK           (0U)
#endif
#if BSP_FEATURE_CGC_HAS_BCLK || BSP_FEATURE_CGC_SCKDIVCR_BCLK_MATCHES_PCLKB
 #define BSP_PRV_SCKDIVCR_BCLK_MASK            (7U << 16)
#else
 #define BSP_PRV_SCKDIVCR_BCLK_MASK            (0U)
#endif
#if BSP_FEATURE_CGC_HAS_FCLK
 #define BSP_PRV_SCKDIVCR_FCLK_MASK            (7U << 28)
#else
 #define BSP_PRV_SCKDIVCR_FCLK_MASK            (0U)
#endif
#define BSP_PRV_SCKDIVCR_MASK                  ((((((BSP_PRV_SCKDIVCR_ICLK_MASK | BSP_PRV_SCKDIVCR_PCLKD_MASK) |  \
                                                    BSP_PRV_SCKDIVCR_PCLKC_MASK) | BSP_PRV_SCKDIVCR_PCLKB_MASK) | \
                                                  BSP_PRV_SCKDIVCR_PCLKA_MASK) |                                  \
                                                 BSP_PRV_SCKDIVCR_BCLK_MASK) | BSP_PRV_SCKDIVCR_FCLK_MASK)

/* FLL is only used when enabled, present and the subclock is populated. */
#if BSP_FEATURE_CGC_HAS_FLL && BSP_CFG_FLL_ENABLE && BSP_CLOCK_CFG_SUBCLOCK_POPULATED
 #define BSP_PRV_HOCO_USE_FLL                  (1)
 #ifndef BSP_PRV_FLL_STABILIZATION_TIME_US
  #define BSP_PRV_FLL_STABILIZATION_TIME_US    (1800)
 #endif
#else
 #define BSP_PRV_HOCO_USE_FLL                  (0)
 #define BSP_PRV_FLL_STABILIZATION_TIME_US     (0)
#endif

/* Operating power control modes. */
#define BSP_PRV_OPERATING_MODE_HIGH_SPEED      (0U) // Should match OPCCR OPCM high speed
#define BSP_PRV_OPERATING_MODE_MIDDLE_SPEED    (1U) // Should match OPCCR OPCM middle speed
#define BSP_PRV_OPERATING_MODE_LOW_VOLTAGE     (2U) // Should match OPCCR OPCM low voltage
#define BSP_PRV_OPERATING_MODE_LOW_SPEED       (3U) // Should match OPCCR OPCM low speed
#define BSP_PRV_OPERATING_MODE_SUBOSC_SPEED    (4U) // Can be any value not otherwise used

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

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/* Public functions defined in bsp.h */
void bsp_clock_init(void);             // Used internally by BSP

#if BSP_TZ_NONSECURE_BUILD
void bsp_clock_freq_var_init(void);    // Used internally by BSP

#endif

#if BSP_TZ_SECURE_BUILD
void r_bsp_clock_update_callback_set(bsp_clock_update_callback_t        p_callback,
                                     bsp_clock_update_callback_args_t * p_callback_memory);

#endif

/* Used internally by CGC */

#if !BSP_CFG_USE_LOW_VOLTAGE_MODE
void bsp_prv_operating_mode_set(uint8_t operating_mode);

#endif

#if BSP_FEATURE_LPM_CHANGE_MSTP_REQUIRED
uint32_t bsp_prv_power_change_mstp_set(void);
void     bsp_prv_power_change_mstp_clear(uint32_t mstp_clear_bitmask);

#endif

void bsp_prv_prepare_pll(uint32_t pll_freq_hz);
void bsp_prv_clock_set(uint32_t clock, uint32_t sckdivcr);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
