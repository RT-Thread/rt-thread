/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
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

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* The following definitions are macros instead of enums because the values are used in preprocessor conditionals. */
/* Must match SCKCR.CKSEL values. */
#define BSP_CLOCKS_SOURCE_CLOCK_HOCO               (0) // The high speed on chip oscillator.
#define BSP_CLOCKS_SOURCE_CLOCK_MOCO               (1) // The middle speed on chip oscillator.
#define BSP_CLOCKS_SOURCE_CLOCK_LOCO               (2) // The low speed on chip oscillator.
#define BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC           (3) // The main oscillator.
#define BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK           (4) // The subclock oscillator.

#if !BSP_FEATURE_CGC_REGISTER_SET_B
 #if 0 < BSP_FEATURE_CGC_PLL1_NUM_OUTPUT_CLOCKS
  #define BSP_CLOCKS_SOURCE_CLOCK_PLL              (5) // The PLL oscillator.
 #endif
 #if 0 < BSP_FEATURE_CGC_PLL2_NUM_OUTPUT_CLOCKS
  #define BSP_CLOCKS_SOURCE_CLOCK_PLL2             (6) // The PLL2 oscillator.
 #endif
 #if (1 < BSP_FEATURE_CGC_PLL1_NUM_OUTPUT_CLOCKS && 1 < BSP_FEATURE_CGC_PLL2_NUM_OUTPUT_CLOCKS)
  #define BSP_CLOCKS_SOURCE_CLOCK_PLL1P            (BSP_CLOCKS_SOURCE_CLOCK_PLL)
  #define BSP_CLOCKS_SOURCE_CLOCK_PLL2P            (BSP_CLOCKS_SOURCE_CLOCK_PLL2)
  #define BSP_CLOCKS_SOURCE_CLOCK_PLL1Q            (7)  // The PLL1Q oscillator.
  #define BSP_CLOCKS_SOURCE_CLOCK_PLL1R            (8)  // The PLL1R oscillator.
  #define BSP_CLOCKS_SOURCE_CLOCK_PLL2Q            (9)  // The PLL2Q oscillator.
  #define BSP_CLOCKS_SOURCE_CLOCK_PLL2R            (10) // The PLL2R oscillator.
 #endif
#else
 #define BSP_CLOCKS_SOURCE_CLOCK_FSXP              (11) // Subsystem Clock (FSXP) source.

/* The following definitions are macros instead of enums because the values are used in preprocessor conditionals. */
/* Must match ICLKSCR.CKSEL, FMAINSCR.CKSEL, FOCOSCR.CKSEL, FSUBSCR.CKSEL, OSMC.WUTMMCK0 and CKS0.CSEL values. */
 #define BSP_CLOCKS_SOURCE_CLOCK_FMAIN             (0)  // Use Main System clock (FMAIN) as System clock (ICLK) source.
 #define BSP_CLOCKS_SOURCE_CLOCK_FSUB              (1)  // Use Sub System clock (FSUB) as System clock (ICLK) source.
 #define BSP_CLOCKS_FMAIN_SOURCE_CLOCK_FOCO        (0)  // Use Main on-chip oscillator clock (FOCO) as Main System clock (FMAIN) source.
 #define BSP_CLOCKS_FMAIN_SOURCE_CLOCK_MAIN_OSC    (1)  // Use Main clock oscillator (MOSC) as Main System clock (FMAIN) source.
 #define BSP_CLOCKS_FOCO_SOURCE_CLOCK_HOCO         (0)  // Use High-speed on-chip oscillator (HOCO) as Main on-chip oscillator clock (FOCO) source.
 #define BSP_CLOCKS_FOCO_SOURCE_CLOCK_MOCO         (1)  // Use Middle-speed on-chip oscillator (MOCO) as Main on-chip oscillator clock (FOCO) source.
 #define BSP_CLOCKS_FSUB_SOURCE_CLOCK_SUBCLOCK     (0)  // Use Sub-clock oscillator (SOSC) as Sub System clock (FSUB) source.
 #define BSP_CLOCKS_FSUB_SOURCE_CLOCK_LOCO         (1)  // Use Low-speed on-chip oscillator clock (LOCO) as Sub System clock (FSUB) source.
 #define BSP_CLOCKS_CLKOUT_SOURCE_CLOCK_FMAIN      (0)  // Use Main System clock (FMAIN) as Clock Out (CLKOUT) source.
 #define BSP_CLOCKS_CLKOUT_SOURCE_CLOCK_FSUB       (1)  // Use Subsystem Clock (FSUB) as Clock Out (CLKOUT) source.

/* Offset to convert OSTS setting to OSTC value (OSTC = ~(BSP_PRV_OSTC_OFFSET >> OSTS)) */
 #define BSP_PRV_OSTC_OFFSET                       (0x7FU)

#endif

/* PLLs are not supported in the following scenarios:
 *  - When using low voltage mode
 *  - When using an MCU that does not have a PLL
 *  - When the PLL only accepts the main oscillator as a source and XTAL is not used
 */
#if BSP_FEATURE_CGC_HAS_PLL && !BSP_CFG_USE_LOW_VOLTAGE_MODE && \
    !((1U != BSP_FEATURE_CGC_PLLCCR_TYPE) &&                    \
    (3U != BSP_FEATURE_CGC_PLLCCR_TYPE) &&                      \
    (4U != BSP_FEATURE_CGC_PLLCCR_TYPE) &&                      \
    (5U != BSP_FEATURE_CGC_PLLCCR_TYPE) &&                      \
    !BSP_CLOCK_CFG_MAIN_OSC_POPULATED)
 #define BSP_PRV_PLL_SUPPORTED      (1)
 #if BSP_FEATURE_CGC_HAS_PLL2
  #define BSP_PRV_PLL2_SUPPORTED    (1)
 #else
  #define BSP_PRV_PLL2_SUPPORTED    (0)
 #endif
#else
 #define BSP_PRV_PLL_SUPPORTED      (0)
 #define BSP_PRV_PLL2_SUPPORTED     (0)
#endif

/* The ICLK frequency at startup is used to determine the ideal operating mode to set after startup. The PLL frequency
 * calculated here is also used to initialize the g_clock_freq array. */
#if BSP_PRV_PLL_SUPPORTED
 #if ((1U == BSP_FEATURE_CGC_PLLCCR_TYPE) || (5U == BSP_FEATURE_CGC_PLLCCR_TYPE)) && \
    (BSP_CLOCKS_SOURCE_CLOCK_HOCO == BSP_CFG_PLL_SOURCE)
  #define BSP_PRV_PLL_SOURCE_FREQ_HZ     (BSP_HOCO_HZ)
 #else
  #define BSP_PRV_PLL_SOURCE_FREQ_HZ     (BSP_CFG_XTAL_HZ)
 #endif
#endif
#if BSP_PRV_PLL2_SUPPORTED
 #if BSP_CLOCKS_SOURCE_CLOCK_HOCO == BSP_CFG_PLL2_SOURCE
  #define BSP_PRV_PLL2_SOURCE_FREQ_HZ    (BSP_HOCO_HZ)
 #else
  #define BSP_PRV_PLL2_SOURCE_FREQ_HZ    (BSP_CFG_XTAL_HZ)
 #endif
#endif

#define BSP_MOCO_FREQ_HZ                 (BSP_MOCO_HZ)

/* Frequencies of clocks with fixed freqencies. */
#define BSP_LOCO_FREQ_HZ                 (32768U) // LOCO frequency is fixed at 32768 Hz
#define BSP_SUBCLOCK_FREQ_HZ             (32768U) // Subclock frequency is 32768 Hz

#if BSP_CLOCKS_SOURCE_CLOCK_HOCO == BSP_CFG_CLOCK_SOURCE
 #define BSP_STARTUP_SOURCE_CLOCK_HZ     (BSP_HOCO_HZ)
#elif BSP_CLOCKS_SOURCE_CLOCK_MOCO == BSP_CFG_CLOCK_SOURCE
 #define BSP_STARTUP_SOURCE_CLOCK_HZ     (BSP_MOCO_FREQ_HZ)
#elif BSP_CLOCKS_SOURCE_CLOCK_LOCO == BSP_CFG_CLOCK_SOURCE
 #define BSP_STARTUP_SOURCE_CLOCK_HZ     (BSP_LOCO_FREQ_HZ)
#elif BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK == BSP_CFG_CLOCK_SOURCE
 #define BSP_STARTUP_SOURCE_CLOCK_HZ     (BSP_SUBCLOCK_FREQ_HZ)
#elif BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC == BSP_CFG_CLOCK_SOURCE
 #define BSP_STARTUP_SOURCE_CLOCK_HZ     (BSP_CFG_XTAL_HZ)
#elif BSP_CLOCKS_SOURCE_CLOCK_PLL == BSP_CFG_CLOCK_SOURCE
 #if (1U == BSP_FEATURE_CGC_PLLCCR_TYPE) || (5U == BSP_FEATURE_CGC_PLLCCR_TYPE)
  #if BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC == BSP_CFG_PLL_SOURCE
   #define BSP_PRV_PLL_SOURCE_FREQ_HZ    (BSP_CFG_XTAL_HZ)
  #elif BSP_CLOCKS_SOURCE_CLOCK_HOCO == BSP_CFG_PLL_SOURCE
   #define BSP_PRV_PLL_SOURCE_FREQ_HZ    (BSP_HOCO_HZ)
  #endif
  #define BSP_STARTUP_SOURCE_CLOCK_HZ    (((BSP_PRV_PLL_SOURCE_FREQ_HZ * (BSP_CFG_PLL_MUL + 1U)) >> 1) / \
                                          (BSP_CFG_PLL_DIV + 1U))
 #elif (2U == BSP_FEATURE_CGC_PLLCCR_TYPE)
  #define BSP_PRV_PLL_SOURCE_FREQ_HZ     (BSP_CFG_XTAL_HZ)
  #define BSP_STARTUP_SOURCE_CLOCK_HZ    ((BSP_PRV_PLL_SOURCE_FREQ_HZ * ((BSP_CFG_PLL_MUL + 1U) >> 1)) >> \
                                          (BSP_CFG_PLL_DIV))
 #elif (3U == BSP_FEATURE_CGC_PLLCCR_TYPE) || (6U == BSP_FEATURE_CGC_PLLCCR_TYPE)
  #define BSP_STARTUP_SOURCE_CLOCK_HZ    (BSP_CFG_PLL1P_FREQUENCY_HZ)
 #endif
#endif

/* Convert divisor bitfield settings into divisor values to calculate startup clocks */
#define BSP_PRV_SCKDIVCR_DIV_VALUE(div)    (((div) & 8U) ? (3U << ((div) & ~8U)) : (1U << (div)))
#define BSP_PRV_CPUCLK_DIV_VALUE          BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_CPUCLK_DIV)

#if !BSP_FEATURE_CGC_REGISTER_SET_B
 #define BSP_PRV_ICLK_DIV_VALUE           BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_ICLK_DIV)
#else
 #define BSP_PRV_ICLK_DIV_VALUE           (1U << BSP_CFG_ICLK_DIV)
#endif

#define BSP_PRV_PCLKA_DIV_VALUE           BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_PCLKA_DIV)
#define BSP_PRV_PCLKB_DIV_VALUE           BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_PCLKB_DIV)
#define BSP_PRV_PCLKC_DIV_VALUE           BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_PCLKC_DIV)
#define BSP_PRV_PCLKD_DIV_VALUE           BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_PCLKD_DIV)
#define BSP_PRV_PCLKE_DIV_VALUE           BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_PCLKE_DIV)
#define BSP_PRV_BCLK_DIV_VALUE            BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_BCLK_DIV)
#define BSP_PRV_FCLK_DIV_VALUE            BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_FCLK_DIV)
#define BSP_PRV_EXTRACLK3_DIV_VALUE       BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_EXTRACLK3_DIV)

/* Startup clock frequency of each system clock. These macros are only helpful if the system clock and dividers have
 * not changed since startup. These macros are not used in FSP modules except for the clock startup code. */
#define BSP_STARTUP_CPUCLK_HZ             (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_CPUCLK_DIV_VALUE)
#define BSP_STARTUP_ICLK_HZ               (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_ICLK_DIV_VALUE)
#define BSP_STARTUP_PCLKA_HZ              (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_PCLKA_DIV_VALUE)
#define BSP_STARTUP_PCLKB_HZ              (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_PCLKB_DIV_VALUE)
#define BSP_STARTUP_PCLKC_HZ              (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_PCLKC_DIV_VALUE)
#define BSP_STARTUP_PCLKD_HZ              (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_PCLKD_DIV_VALUE)
#define BSP_STARTUP_PCLKE_HZ              (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_PCLKE_DIV_VALUE)
#define BSP_STARTUP_BCLK_HZ               (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_BCLK_DIV_VALUE)
#define BSP_STARTUP_FCLK_HZ               (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_FCLK_DIV_VALUE)
#define BSP_STARTUP_EXTRACLK3_HZ          (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_EXTRACLK3_DIV_VALUE)

/* System clock divider options. */
#define BSP_CLOCKS_SYS_CLOCK_DIV_1        (0)  // System clock divided by 1.
#define BSP_CLOCKS_SYS_CLOCK_DIV_2        (1)  // System clock divided by 2.
#define BSP_CLOCKS_SYS_CLOCK_DIV_4        (2)  // System clock divided by 4.
#define BSP_CLOCKS_SYS_CLOCK_DIV_8        (3)  // System clock divided by 8.
#define BSP_CLOCKS_SYS_CLOCK_DIV_16       (4)  // System clock divided by 16.
#define BSP_CLOCKS_SYS_CLOCK_DIV_32       (5)  // System clock divided by 32.
#define BSP_CLOCKS_SYS_CLOCK_DIV_64       (6)  // System clock divided by 64.
#define BSP_CLOCKS_SYS_CLOCK_DIV_128      (7)  // System clock divided by 128 (available for CLKOUT only).
#define BSP_CLOCKS_SYS_CLOCK_DIV_3        (8)  // System clock divided by 3.
#define BSP_CLOCKS_SYS_CLOCK_DIV_6        (9)  // System clock divided by 6.
#define BSP_CLOCKS_SYS_CLOCK_DIV_12       (10) // System clock divided by 12.
#define BSP_CLOCKS_SYS_CLOCK_DIV_24       (11) // System clock divided by 24.

/* USB clock divider options. */
#define BSP_CLOCKS_USB_CLOCK_DIV_1        (0)  // Divide USB source clock by 1
#define BSP_CLOCKS_USB_CLOCK_DIV_2        (1)  // Divide USB source clock by 2
#define BSP_CLOCKS_USB_CLOCK_DIV_3        (2)  // Divide USB source clock by 3
#define BSP_CLOCKS_USB_CLOCK_DIV_4        (3)  // Divide USB source clock by 4
#define BSP_CLOCKS_USB_CLOCK_DIV_5        (4)  // Divide USB source clock by 5
#define BSP_CLOCKS_USB_CLOCK_DIV_6        (5)  // Divide USB source clock by 6
#define BSP_CLOCKS_USB_CLOCK_DIV_8        (7)  // Divide USB source clock by 8
#define BSP_CLOCKS_USB_CLOCK_DIV_10       (9)  // Divide USB source clock by 10
#define BSP_CLOCKS_USB_CLOCK_DIV_16       (15) // Divide USB source clock by 16
#define BSP_CLOCKS_USB_CLOCK_DIV_32       (9)  // Divide USB source clock by 32

/* USB60 clock divider options. */
#define BSP_CLOCKS_USB60_CLOCK_DIV_1      (0)  // Divide USB60 source clock by 1
#define BSP_CLOCKS_USB60_CLOCK_DIV_2      (1)  // Divide USB60 source clock by 2
#define BSP_CLOCKS_USB60_CLOCK_DIV_3      (5)  // Divide USB60 source clock by 3
#define BSP_CLOCKS_USB60_CLOCK_DIV_4      (2)  // Divide USB60 source clock by 4
#define BSP_CLOCKS_USB60_CLOCK_DIV_5      (6)  // Divide USB60 source clock by 5
#define BSP_CLOCKS_USB60_CLOCK_DIV_6      (3)  // Divide USB66 source clock by 6
#define BSP_CLOCKS_USB60_CLOCK_DIV_8      (4)  // Divide USB60 source clock by 8
#define BSP_CLOCKS_USB60_CLOCK_DIV_10     (7)  // Divide USB60 source clock by 10
#define BSP_CLOCKS_USB60_CLOCK_DIV_16     (8)  // Divide USB60 source clock by 16
#define BSP_CLOCKS_USB60_CLOCK_DIV_32     (9)  // Divide USB60 source clock by 32

/* GLCD clock divider options. */
#define BSP_CLOCKS_LCD_CLOCK_DIV_1        (0)  // Divide LCD source clock by 1
#define BSP_CLOCKS_LCD_CLOCK_DIV_2        (1)  // Divide LCD source clock by 2
#define BSP_CLOCKS_LCD_CLOCK_DIV_3        (5)  // Divide LCD source clock by 3
#define BSP_CLOCKS_LCD_CLOCK_DIV_4        (2)  // Divide LCD source clock by 4
#define BSP_CLOCKS_LCD_CLOCK_DIV_5        (6)  // Divide LCD source clock by 5
#define BSP_CLOCKS_LCD_CLOCK_DIV_6        (3)  // Divide LCD source clock by 6
#define BSP_CLOCKS_LCD_CLOCK_DIV_8        (4)  // Divide LCD source clock by 8
#define BSP_CLOCKS_LCD_CLOCK_DIV_10       (7)  // Divide LCD source clock by 10
#define BSP_CLOCKS_LCD_CLOCK_DIV_16       (8)  // Divide LCD source clock by 16
#define BSP_CLOCKS_LCD_CLOCK_DIV_32       (9)  // Divide LCD source clock by 32

/* OCTA clock divider options. */
#define BSP_CLOCKS_OCTA_CLOCK_DIV_1       (0)  // Divide OCTA source clock by 1
#define BSP_CLOCKS_OCTA_CLOCK_DIV_2       (1)  // Divide OCTA source clock by 2
#define BSP_CLOCKS_OCTA_CLOCK_DIV_3       (5)  // Divide OCTA source clock by 3
#define BSP_CLOCKS_OCTA_CLOCK_DIV_4       (2)  // Divide OCTA source clock by 4
#define BSP_CLOCKS_OCTA_CLOCK_DIV_5       (6)  // Divide OCTA source clock by 5
#define BSP_CLOCKS_OCTA_CLOCK_DIV_6       (3)  // Divide OCTA source clock by 6
#define BSP_CLOCKS_OCTA_CLOCK_DIV_8       (4)  // Divide OCTA source clock by 8
#define BSP_CLOCKS_OCTA_CLOCK_DIV_10      (7)  // Divide OCTA source clock by 10
#define BSP_CLOCKS_OCTA_CLOCK_DIV_16      (8)  // Divide OCTA source clock by 16
#define BSP_CLOCKS_OCTA_CLOCK_DIV_32      (9)  // Divide OCTA source clock by 32

/* CANFD clock divider options. */
#define BSP_CLOCKS_CANFD_CLOCK_DIV_1      (0)  // Divide CANFD source clock by 1
#define BSP_CLOCKS_CANFD_CLOCK_DIV_2      (1)  // Divide CANFD source clock by 2
#define BSP_CLOCKS_CANFD_CLOCK_DIV_3      (5)  // Divide CANFD source clock by 3
#define BSP_CLOCKS_CANFD_CLOCK_DIV_4      (2)  // Divide CANFD source clock by 4
#define BSP_CLOCKS_CANFD_CLOCK_DIV_5      (6)  // Divide CANFD source clock by 5
#define BSP_CLOCKS_CANFD_CLOCK_DIV_6      (3)  // Divide CANFD source clock by 6
#define BSP_CLOCKS_CANFD_CLOCK_DIV_8      (4)  // Divide CANFD source clock by 8
#define BSP_CLOCKS_CANFD_CLOCK_DIV_10     (7)  // Divide CANFD source clock by 10
#define BSP_CLOCKS_CANFD_CLOCK_DIV_16     (8)  // Divide CANFD source clock by 16
#define BSP_CLOCKS_CANFD_CLOCK_DIV_32     (9)  // Divide CANFD source clock by 32

/* SCI clock divider options. */
#define BSP_CLOCKS_SCI_CLOCK_DIV_1        (0)  // Divide SCI source clock by 1
#define BSP_CLOCKS_SCI_CLOCK_DIV_2        (1)  // Divide SCI source clock by 2
#define BSP_CLOCKS_SCI_CLOCK_DIV_3        (5)  // Divide SCI source clock by 3
#define BSP_CLOCKS_SCI_CLOCK_DIV_4        (2)  // Divide SCI source clock by 4
#define BSP_CLOCKS_SCI_CLOCK_DIV_5        (6)  // Divide SCI source clock by 5
#define BSP_CLOCKS_SCI_CLOCK_DIV_6        (3)  // Divide SCI source clock by 6
#define BSP_CLOCKS_SCI_CLOCK_DIV_8        (4)  // Divide SCI source clock by 8
#define BSP_CLOCKS_SCI_CLOCK_DIV_10       (7)  // Divide SCI source clock by 10
#define BSP_CLOCKS_SCI_CLOCK_DIV_16       (8)  // Divide SCI source clock by 16
#define BSP_CLOCKS_SCI_CLOCK_DIV_32       (9)  // Divide SCI source clock by 32

/* SPI clock divider options. */
#define BSP_CLOCKS_SPI_CLOCK_DIV_1        (0)  // Divide SPI source clock by 1
#define BSP_CLOCKS_SPI_CLOCK_DIV_2        (1)  // Divide SPI source clock by 2
#define BSP_CLOCKS_SPI_CLOCK_DIV_3        (5)  // Divide SPI source clock by 3
#define BSP_CLOCKS_SPI_CLOCK_DIV_4        (2)  // Divide SPI source clock by 4
#define BSP_CLOCKS_SPI_CLOCK_DIV_5        (6)  // Divide SPI source clock by 5
#define BSP_CLOCKS_SPI_CLOCK_DIV_6        (3)  // Divide SPI source clock by 6
#define BSP_CLOCKS_SPI_CLOCK_DIV_8        (4)  // Divide SPI source clock by 8
#define BSP_CLOCKS_SPI_CLOCK_DIV_10       (7)  // Divide SPI source clock by 10
#define BSP_CLOCKS_SPI_CLOCK_DIV_16       (8)  // Divide SPI source clock by 16
#define BSP_CLOCKS_SPI_CLOCK_DIV_32       (9)  // Divide SPI source clock by 32

/* SCISPI clock divider options. */
#define BSP_CLOCKS_SCISPI_CLOCK_DIV_1     (0)  // Divide SCISPI source clock by 1
#define BSP_CLOCKS_SCISPI_CLOCK_DIV_2     (1)  // Divide SCISPI source clock by 2
#define BSP_CLOCKS_SCISPI_CLOCK_DIV_4     (2)  // Divide SCISPI source clock by 4
#define BSP_CLOCKS_SCISPI_CLOCK_DIV_6     (3)  // Divide SCISPI source clock by 6
#define BSP_CLOCKS_SCISPI_CLOCK_DIV_8     (4)  // Divide SCISPI source clock by 8

/* GPT clock divider options. */
#define BSP_CLOCKS_GPT_CLOCK_DIV_1        (0)  // Divide GPT source clock by 1
#define BSP_CLOCKS_GPT_CLOCK_DIV_2        (1)  // Divide GPT source clock by 2
#define BSP_CLOCKS_GPT_CLOCK_DIV_3        (5)  // Divide GPT source clock by 3
#define BSP_CLOCKS_GPT_CLOCK_DIV_4        (2)  // Divide GPT source clock by 4
#define BSP_CLOCKS_GPT_CLOCK_DIV_5        (6)  // Divide GPT source clock by 5
#define BSP_CLOCKS_GPT_CLOCK_DIV_6        (3)  // Divide GPT source clock by 6
#define BSP_CLOCKS_GPT_CLOCK_DIV_8        (4)  // Divide GPT source clock by 8
#define BSP_CLOCKS_GPT_CLOCK_DIV_10       (7)  // Divide GPT source clock by 10
#define BSP_CLOCKS_GPT_CLOCK_DIV_16       (8)  // Divide GPT source clock by 16
#define BSP_CLOCKS_GPT_CLOCK_DIV_32       (9)  // Divide GPT source clock by 32

/* IIC clock divider options. */
#define BSP_CLOCKS_IIC_CLOCK_DIV_1        (0)  // Divide IIC source clock by 1
#define BSP_CLOCKS_IIC_CLOCK_DIV_2        (1)  // Divide IIC source clock by 2
#define BSP_CLOCKS_IIC_CLOCK_DIV_4        (2)  // Divide IIC source clock by 4
#define BSP_CLOCKS_IIC_CLOCK_DIV_6        (3)  // Divide IIC source clock by 6
#define BSP_CLOCKS_IIC_CLOCK_DIV_8        (4)  // Divide IIC source clock by 8

/* CEC clock divider options. */
#define BSP_CLOCKS_CEC_CLOCK_DIV_1        (0)  // Divide CEC source clock by 1
#define BSP_CLOCKS_CEC_CLOCK_DIV_2        (1)  // Divide CEC source clock by 2

/* I3C clock divider options. */
#define BSP_CLOCKS_I3C_CLOCK_DIV_1        (0)  // Divide I3C source clock by 1
#define BSP_CLOCKS_I3C_CLOCK_DIV_2        (1)  // Divide I3C source clock by 2
#define BSP_CLOCKS_I3C_CLOCK_DIV_3        (5)  // Divide I3C source clock by 3
#define BSP_CLOCKS_I3C_CLOCK_DIV_4        (2)  // Divide I3C source clock by 4
#define BSP_CLOCKS_I3C_CLOCK_DIV_5        (6)  // Divide I3C source clock by 5
#define BSP_CLOCKS_I3C_CLOCK_DIV_6        (3)  // Divide I3C source clock by 6
#define BSP_CLOCKS_I3C_CLOCK_DIV_8        (4)  // Divide I3C source clock by 8
#define BSP_CLOCKS_I3C_CLOCK_DIV_10       (7)  // Divide I3C source clock by 10
#define BSP_CLOCKS_I3C_CLOCK_DIV_16       (8)  // Divide I3C source clock by 16
#define BSP_CLOCKS_I3C_CLOCK_DIV_32       (9)  // Divide I3C source clock by 32

/* ADC clock divider options. */
#define BSP_CLOCKS_ADC_CLOCK_DIV_1        (0)  // Divide ADC source clock by 1
#define BSP_CLOCKS_ADC_CLOCK_DIV_2        (1)  // Divide ADC source clock by 2
#define BSP_CLOCKS_ADC_CLOCK_DIV_3        (5)  // Divide ADC source clock by 3
#define BSP_CLOCKS_ADC_CLOCK_DIV_4        (2)  // Divide ADC source clock by 4
#define BSP_CLOCKS_ADC_CLOCK_DIV_5        (6)  // Divide ADC source clock by 5
#define BSP_CLOCKS_ADC_CLOCK_DIV_6        (3)  // Divide ADC source clock by 6
#define BSP_CLOCKS_ADC_CLOCK_DIV_8        (4)  // Divide ADC source clock by 8
#define BSP_CLOCKS_ADC_CLOCK_DIV_10       (7)  // Divide ADC source clock by 10
#define BSP_CLOCKS_ADC_CLOCK_DIV_16       (8)  // Divide ADC source clock by 16
#define BSP_CLOCKS_ADC_CLOCK_DIV_32       (9)  // Divide ADC source clock by 32

/* SAU clock divider options. */
#define BSP_CLOCKS_SAU_CLOCK_DIV_1        (0)  // Divide SAU source clock by 1
#define BSP_CLOCKS_SAU_CLOCK_DIV_2        (1)  // Divide SAU source clock by 2
#define BSP_CLOCKS_SAU_CLOCK_DIV_4        (2)  // Divide SAU source clock by 4
#define BSP_CLOCKS_SAU_CLOCK_DIV_8        (3)  // Divide SAU source clock by 8
#define BSP_CLOCKS_SAU_CLOCK_DIV_16       (4)  // Divide SAU source clock by 16
#define BSP_CLOCKS_SAU_CLOCK_DIV_32       (5)  // Divide SAU source clock by 32
#define BSP_CLOCKS_SAU_CLOCK_DIV_64       (6)  // Divide SAU source clock by 64
#define BSP_CLOCKS_SAU_CLOCK_DIV_128      (7)  // Divide SAU source clock by 128
#define BSP_CLOCKS_SAU_CLOCK_DIV_256      (8)  // Divide SAU source clock by 256
#define BSP_CLOCKS_SAU_CLOCK_DIV_512      (9)  // Divide SAU source clock by 512
#define BSP_CLOCKS_SAU_CLOCK_DIV_1024     (10) // Divide SAU source clock by 1024
#define BSP_CLOCKS_SAU_CLOCK_DIV_2048     (11) // Divide SAU source clock by 2048
#define BSP_CLOCKS_SAU_CLOCK_DIV_4096     (12) // Divide SAU source clock by 4096
#define BSP_CLOCKS_SAU_CLOCK_DIV_8192     (13) // Divide SAU source clock by 8192
#define BSP_CLOCKS_SAU_CLOCK_DIV_16384    (14) // Divide SAU source clock by 16384
#define BSP_CLOCKS_SAU_CLOCK_DIV_32768    (15) // Divide SAU source clock by 32768

/* PLL divider options. */
#define BSP_CLOCKS_PLL_DIV_1              (0)
#define BSP_CLOCKS_PLL_DIV_2              (1)
#define BSP_CLOCKS_PLL_DIV_3              (2)
#define BSP_CLOCKS_PLL_DIV_4              (3)
#define BSP_CLOCKS_PLL_DIV_5              (4)
#define BSP_CLOCKS_PLL_DIV_6              (5)
#define BSP_CLOCKS_PLL_DIV_8              (7)
#define BSP_CLOCKS_PLL_DIV_9              (8)
#define BSP_CLOCKS_PLL_DIV_1_5            (9)
#define BSP_CLOCKS_PLL_DIV_16             (15)

/* PLL multiplier options. */
#if (4U == BSP_FEATURE_CGC_PLLCCR_TYPE)

/* Offset from decimal multiplier to register value for PLLCCR type 4. */
 #define BSP_PRV_CLOCKS_PLL_MUL_INT_OFFSET    (574)

/**
 * X=Integer portion of the multiplier.
 * Y=Fractional portion of the multiplier. (not used for this PLLCCR type)
 */
 #define BSP_CLOCKS_PLL_MUL(X, Y)    (X - BSP_PRV_CLOCKS_PLL_MUL_INT_OFFSET)

#elif (3U != BSP_FEATURE_CGC_PLLCCR_TYPE) && (6U != BSP_FEATURE_CGC_PLLCCR_TYPE)

/**
 * X=Integer portion of the multiplier.
 * Y=Fractional portion of the multiplier.
 */
 #define BSP_CLOCKS_PLL_MUL(X, Y)    (((X) << 1 | ((Y) >= 50U ? 1 : 0)) - 1U)

#else

 #define BSP_PRV_CLOCKS_PLL_MUL_INT_SHIFT     (2U)
 #define BSP_PRV_CLOCKS_PLL_MUL_FRAC_MASK     (0x3U)
 #define BSP_PRV_CLOCKS_PLL_MUL_FRAC_SHIFT    (0U)

/**
 * X=Integer portion of the multiplier.
 * Y=Fractional portion of the multiplier.
 */
 #define BSP_CLOCKS_PLL_MUL(X, Y)    ((((X) -1U) << 2U) | ((Y) == 50U ? 3U : ((Y) / 33U)))

#endif

/* Configuration option used to disable clock output. */
#define BSP_CLOCKS_CLOCK_DISABLED               (0xFFU)

/* HOCO cycles per microsecond. */
#define BSP_PRV_HOCO_CYCLES_PER_US              (BSP_HOCO_HZ / 1000000U)

/* Maximum number of delay cycles required to ensure 1 us passes between setting PLLCCR and clearing PLLCR. */
#if BSP_HOCO_HZ < 48000000U
 #define BSP_PRV_MAX_HOCO_CYCLES_PER_US         (BSP_PRV_HOCO_CYCLES_PER_US)
#else
 #define BSP_PRV_MAX_HOCO_CYCLES_PER_US         (48U)
#endif

/* Create a mask of valid bits in SCKDIVCR. */
#define BSP_PRV_SCKDIVCR_ICLK_MASK              (FSP_PRV_SCKDIVCR_DIV_MASK << 24)
#if BSP_FEATURE_CGC_HAS_PCLKD
 #define BSP_PRV_SCKDIVCR_PCLKD_MASK            (FSP_PRV_SCKDIVCR_DIV_MASK << 0)
#else
 #define BSP_PRV_SCKDIVCR_PCLKD_MASK            (0U)
#endif
#if BSP_FEATURE_CGC_HAS_PCLKC
 #define BSP_PRV_SCKDIVCR_PCLKC_MASK            (FSP_PRV_SCKDIVCR_DIV_MASK << 4)
#else
 #define BSP_PRV_SCKDIVCR_PCLKC_MASK            (0U)
#endif
#if BSP_FEATURE_CGC_HAS_PCLKB
 #define BSP_PRV_SCKDIVCR_PCLKB_MASK            (FSP_PRV_SCKDIVCR_DIV_MASK << 8)
#else
 #define BSP_PRV_SCKDIVCR_PCLKB_MASK            (0U)
#endif
#if BSP_FEATURE_CGC_HAS_PCLKA
 #define BSP_PRV_SCKDIVCR_PCLKA_MASK            (FSP_PRV_SCKDIVCR_DIV_MASK << 12)
#else
 #define BSP_PRV_SCKDIVCR_PCLKA_MASK            (0U)
#endif
#if BSP_FEATURE_CGC_HAS_BCLK || BSP_FEATURE_CGC_SCKDIVCR_BCLK_MATCHES_PCLKB
 #define BSP_PRV_SCKDIVCR_BCLK_MASK             (FSP_PRV_SCKDIVCR_DIV_MASK << 16)
#else
 #define BSP_PRV_SCKDIVCR_BCLK_MASK             (0U)
#endif
#if BSP_FEATURE_CGC_HAS_PCLKE
 #define BSP_PRV_SCKDIVCR_PCLKE_MASK            (FSP_PRV_SCKDIVCR_DIV_MASK << 24)
#else
 #define BSP_PRV_SCKDIVCR_PCLKE_MASK            (0U)
#endif
#if BSP_FEATURE_CGC_HAS_FCLK
 #define BSP_PRV_SCKDIVCR_FCLK_MASK             (FSP_PRV_SCKDIVCR_DIV_MASK << 28)
#else
 #define BSP_PRV_SCKDIVCR_FCLK_MASK             (0U)
#endif
#define BSP_PRV_SCKDIVCR_MASK                   (BSP_PRV_SCKDIVCR_ICLK_MASK | BSP_PRV_SCKDIVCR_PCLKD_MASK |  \
                                                 BSP_PRV_SCKDIVCR_PCLKC_MASK | BSP_PRV_SCKDIVCR_PCLKB_MASK | \
                                                 BSP_PRV_SCKDIVCR_PCLKA_MASK | BSP_PRV_SCKDIVCR_BCLK_MASK |  \
                                                 BSP_PRV_SCKDIVCR_PCLKE_MASK | BSP_PRV_SCKDIVCR_FCLK_MASK)

/* FLL is only used when enabled, present and the subclock is populated. */
#if BSP_FEATURE_CGC_HAS_FLL && BSP_CFG_FLL_ENABLE && BSP_CLOCK_CFG_SUBCLOCK_POPULATED
 #define BSP_PRV_HOCO_USE_FLL                   (1)
 #ifndef BSP_PRV_FLL_STABILIZATION_TIME_US
  #define BSP_PRV_FLL_STABILIZATION_TIME_US     (1800)
 #endif
#else
 #define BSP_PRV_HOCO_USE_FLL                   (0)
 #define BSP_PRV_FLL_STABILIZATION_TIME_US      (0)
#endif

#if BSP_FEATURE_RTC_IS_AVAILABLE || BSP_FEATURE_RTC_HAS_TCEN || BSP_FEATURE_SYSC_HAS_VBTICTLR
 #define BSP_PRV_RTC_RESET_DELAY_US             (200)
#endif

/* Operating power control modes. */
#if BSP_FEATURE_CGC_REGISTER_SET_B
 #define BSP_PRV_OPERATING_MODE_LOW_SPEED       (1U) // Should match FLMODE low speed
 #define BSP_PRV_OPERATING_MODE_MIDDLE_SPEED    (2U) // Should match FLMODE middle speed
 #define BSP_PRV_OPERATING_MODE_HIGH_SPEED      (3U) // Should match FLMODE high speed
#else
 #define BSP_PRV_OPERATING_MODE_HIGH_SPEED      (0U) // Should match OPCCR OPCM high speed
 #define BSP_PRV_OPERATING_MODE_MIDDLE_SPEED    (1U) // Should match OPCCR OPCM middle speed
 #define BSP_PRV_OPERATING_MODE_LOW_VOLTAGE     (2U) // Should match OPCCR OPCM low voltage
 #define BSP_PRV_OPERATING_MODE_LOW_SPEED       (3U) // Should match OPCCR OPCM low speed
#endif
#define BSP_PRV_OPERATING_MODE_SUBOSC_SPEED     (4U) // Can be any value not otherwise used

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

/** PLL multiplier values */
typedef enum e_cgc_pll_mul
{
    CGC_PLL_MUL_4_0    = BSP_CLOCKS_PLL_MUL(4U, 0U),    ///< PLL multiplier of 4.00
    CGC_PLL_MUL_4_5    = BSP_CLOCKS_PLL_MUL(4U, 50U),   ///< PLL multiplier of 4.50
    CGC_PLL_MUL_5_0    = BSP_CLOCKS_PLL_MUL(5U, 0U),    ///< PLL multiplier of 5.00
    CGC_PLL_MUL_5_5    = BSP_CLOCKS_PLL_MUL(5U, 50U),   ///< PLL multiplier of 5.50
    CGC_PLL_MUL_6_0    = BSP_CLOCKS_PLL_MUL(6U, 0U),    ///< PLL multiplier of 6.00
    CGC_PLL_MUL_6_5    = BSP_CLOCKS_PLL_MUL(6U, 50U),   ///< PLL multiplier of 6.50
    CGC_PLL_MUL_7_0    = BSP_CLOCKS_PLL_MUL(7U, 0U),    ///< PLL multiplier of 7.00
    CGC_PLL_MUL_7_5    = BSP_CLOCKS_PLL_MUL(7U, 50U),   ///< PLL multiplier of 7.50
    CGC_PLL_MUL_8_0    = BSP_CLOCKS_PLL_MUL(8U, 0U),    ///< PLL multiplier of 8.00
    CGC_PLL_MUL_8_5    = BSP_CLOCKS_PLL_MUL(8U, 50U),   ///< PLL multiplier of 8.50
    CGC_PLL_MUL_9_0    = BSP_CLOCKS_PLL_MUL(9U, 0U),    ///< PLL multiplier of 9.00
    CGC_PLL_MUL_9_5    = BSP_CLOCKS_PLL_MUL(9U, 50U),   ///< PLL multiplier of 9.50
    CGC_PLL_MUL_10_0   = BSP_CLOCKS_PLL_MUL(10U, 0U),   ///< PLL multiplier of 10.00
    CGC_PLL_MUL_10_5   = BSP_CLOCKS_PLL_MUL(10U, 50U),  ///< PLL multiplier of 10.50
    CGC_PLL_MUL_11_0   = BSP_CLOCKS_PLL_MUL(11U, 0U),   ///< PLL multiplier of 11.00
    CGC_PLL_MUL_11_5   = BSP_CLOCKS_PLL_MUL(11U, 50U),  ///< PLL multiplier of 11.50
    CGC_PLL_MUL_12_0   = BSP_CLOCKS_PLL_MUL(12U, 0U),   ///< PLL multiplier of 12.00
    CGC_PLL_MUL_12_5   = BSP_CLOCKS_PLL_MUL(12U, 50U),  ///< PLL multiplier of 12.50
    CGC_PLL_MUL_13_0   = BSP_CLOCKS_PLL_MUL(13U, 0U),   ///< PLL multiplier of 13.00
    CGC_PLL_MUL_13_5   = BSP_CLOCKS_PLL_MUL(13U, 50U),  ///< PLL multiplier of 13.50
    CGC_PLL_MUL_14_0   = BSP_CLOCKS_PLL_MUL(14U, 0U),   ///< PLL multiplier of 14.00
    CGC_PLL_MUL_14_5   = BSP_CLOCKS_PLL_MUL(14U, 50U),  ///< PLL multiplier of 14.50
    CGC_PLL_MUL_15_0   = BSP_CLOCKS_PLL_MUL(15U, 0U),   ///< PLL multiplier of 15.00
    CGC_PLL_MUL_15_5   = BSP_CLOCKS_PLL_MUL(15U, 50U),  ///< PLL multiplier of 15.50
    CGC_PLL_MUL_16_0   = BSP_CLOCKS_PLL_MUL(16U, 0U),   ///< PLL multiplier of 16.00
    CGC_PLL_MUL_16_5   = BSP_CLOCKS_PLL_MUL(16U, 50U),  ///< PLL multiplier of 16.50
    CGC_PLL_MUL_17_0   = BSP_CLOCKS_PLL_MUL(17U, 0U),   ///< PLL multiplier of 17.00
    CGC_PLL_MUL_17_5   = BSP_CLOCKS_PLL_MUL(17U, 50U),  ///< PLL multiplier of 17.50
    CGC_PLL_MUL_18_0   = BSP_CLOCKS_PLL_MUL(18U, 0U),   ///< PLL multiplier of 18.00
    CGC_PLL_MUL_18_5   = BSP_CLOCKS_PLL_MUL(18U, 50U),  ///< PLL multiplier of 18.50
    CGC_PLL_MUL_19_0   = BSP_CLOCKS_PLL_MUL(19U, 0U),   ///< PLL multiplier of 19.00
    CGC_PLL_MUL_19_5   = BSP_CLOCKS_PLL_MUL(19U, 50U),  ///< PLL multiplier of 19.50
    CGC_PLL_MUL_20_0   = BSP_CLOCKS_PLL_MUL(20U, 0U),   ///< PLL multiplier of 20.00
    CGC_PLL_MUL_20_5   = BSP_CLOCKS_PLL_MUL(20U, 50U),  ///< PLL multiplier of 20.50
    CGC_PLL_MUL_21_0   = BSP_CLOCKS_PLL_MUL(21U, 0U),   ///< PLL multiplier of 21.00
    CGC_PLL_MUL_21_5   = BSP_CLOCKS_PLL_MUL(21U, 50U),  ///< PLL multiplier of 21.50
    CGC_PLL_MUL_22_0   = BSP_CLOCKS_PLL_MUL(22U, 0U),   ///< PLL multiplier of 22.00
    CGC_PLL_MUL_22_5   = BSP_CLOCKS_PLL_MUL(22U, 50U),  ///< PLL multiplier of 22.50
    CGC_PLL_MUL_23_0   = BSP_CLOCKS_PLL_MUL(23U, 0U),   ///< PLL multiplier of 23.00
    CGC_PLL_MUL_23_5   = BSP_CLOCKS_PLL_MUL(23U, 50U),  ///< PLL multiplier of 23.50
    CGC_PLL_MUL_24_0   = BSP_CLOCKS_PLL_MUL(24U, 0U),   ///< PLL multiplier of 24.00
    CGC_PLL_MUL_24_5   = BSP_CLOCKS_PLL_MUL(24U, 50U),  ///< PLL multiplier of 24.50
    CGC_PLL_MUL_25_0   = BSP_CLOCKS_PLL_MUL(25U, 0U),   ///< PLL multiplier of 25.00
    CGC_PLL_MUL_25_5   = BSP_CLOCKS_PLL_MUL(25U, 50U),  ///< PLL multiplier of 25.50
    CGC_PLL_MUL_26_0   = BSP_CLOCKS_PLL_MUL(26U, 0U),   ///< PLL multiplier of 26.00
    CGC_PLL_MUL_26_33  = BSP_CLOCKS_PLL_MUL(26U, 33U),  ///< PLL multiplier of 26.33
    CGC_PLL_MUL_26_5   = BSP_CLOCKS_PLL_MUL(26U, 50U),  ///< PLL multiplier of 26.50
    CGC_PLL_MUL_26_66  = BSP_CLOCKS_PLL_MUL(26U, 66U),  ///< PLL multiplier of 26.66
    CGC_PLL_MUL_27_0   = BSP_CLOCKS_PLL_MUL(27U, 0U),   ///< PLL multiplier of 27.00
    CGC_PLL_MUL_27_33  = BSP_CLOCKS_PLL_MUL(27U, 33U),  ///< PLL multiplier of 27.33
    CGC_PLL_MUL_27_5   = BSP_CLOCKS_PLL_MUL(27U, 50U),  ///< PLL multiplier of 27.50
    CGC_PLL_MUL_27_66  = BSP_CLOCKS_PLL_MUL(27U, 66U),  ///< PLL multiplier of 27.66
    CGC_PLL_MUL_28_0   = BSP_CLOCKS_PLL_MUL(28U, 0U),   ///< PLL multiplier of 28.00
    CGC_PLL_MUL_28_33  = BSP_CLOCKS_PLL_MUL(28U, 33U),  ///< PLL multiplier of 28.33
    CGC_PLL_MUL_28_5   = BSP_CLOCKS_PLL_MUL(28U, 50U),  ///< PLL multiplier of 28.50
    CGC_PLL_MUL_28_66  = BSP_CLOCKS_PLL_MUL(28U, 66U),  ///< PLL multiplier of 28.66
    CGC_PLL_MUL_29_0   = BSP_CLOCKS_PLL_MUL(29U, 0U),   ///< PLL multiplier of 29.00
    CGC_PLL_MUL_29_33  = BSP_CLOCKS_PLL_MUL(29U, 33U),  ///< PLL multiplier of 29.33
    CGC_PLL_MUL_29_5   = BSP_CLOCKS_PLL_MUL(29U, 50U),  ///< PLL multiplier of 29.50
    CGC_PLL_MUL_29_66  = BSP_CLOCKS_PLL_MUL(29U, 66U),  ///< PLL multiplier of 29.66
    CGC_PLL_MUL_30_0   = BSP_CLOCKS_PLL_MUL(30U, 0U),   ///< PLL multiplier of 30.00
    CGC_PLL_MUL_30_33  = BSP_CLOCKS_PLL_MUL(30U, 33U),  ///< PLL multiplier of 30.33
    CGC_PLL_MUL_30_5   = BSP_CLOCKS_PLL_MUL(30U, 50U),  ///< PLL multiplier of 30.50
    CGC_PLL_MUL_30_66  = BSP_CLOCKS_PLL_MUL(30U, 66U),  ///< PLL multiplier of 30.66
    CGC_PLL_MUL_31_0   = BSP_CLOCKS_PLL_MUL(31U, 0U),   ///< PLL multiplier of 31.00
    CGC_PLL_MUL_31_33  = BSP_CLOCKS_PLL_MUL(31U, 33U),  ///< PLL multiplier of 31.33
    CGC_PLL_MUL_31_5   = BSP_CLOCKS_PLL_MUL(31U, 50U),  ///< PLL multiplier of 31.50
    CGC_PLL_MUL_31_66  = BSP_CLOCKS_PLL_MUL(31U, 66U),  ///< PLL multiplier of 31.66
    CGC_PLL_MUL_32_0   = BSP_CLOCKS_PLL_MUL(32U, 0U),   ///< PLL multiplier of 32.00
    CGC_PLL_MUL_32_33  = BSP_CLOCKS_PLL_MUL(32U, 33U),  ///< PLL multiplier of 32.33
    CGC_PLL_MUL_32_5   = BSP_CLOCKS_PLL_MUL(32U, 50U),  ///< PLL multiplier of 32.50
    CGC_PLL_MUL_32_66  = BSP_CLOCKS_PLL_MUL(32U, 66U),  ///< PLL multiplier of 32.66
    CGC_PLL_MUL_33_0   = BSP_CLOCKS_PLL_MUL(33U, 0U),   ///< PLL multiplier of 33.00
    CGC_PLL_MUL_33_33  = BSP_CLOCKS_PLL_MUL(33U, 33U),  ///< PLL multiplier of 33.33
    CGC_PLL_MUL_33_5   = BSP_CLOCKS_PLL_MUL(33U, 50U),  ///< PLL multiplier of 33.50
    CGC_PLL_MUL_33_66  = BSP_CLOCKS_PLL_MUL(33U, 66U),  ///< PLL multiplier of 33.66
    CGC_PLL_MUL_34_0   = BSP_CLOCKS_PLL_MUL(34U, 0U),   ///< PLL multiplier of 34.00
    CGC_PLL_MUL_34_33  = BSP_CLOCKS_PLL_MUL(34U, 33U),  ///< PLL multiplier of 34.33
    CGC_PLL_MUL_34_5   = BSP_CLOCKS_PLL_MUL(34U, 50U),  ///< PLL multiplier of 34.50
    CGC_PLL_MUL_34_66  = BSP_CLOCKS_PLL_MUL(34U, 66U),  ///< PLL multiplier of 34.66
    CGC_PLL_MUL_35_0   = BSP_CLOCKS_PLL_MUL(35U, 0U),   ///< PLL multiplier of 35.00
    CGC_PLL_MUL_35_33  = BSP_CLOCKS_PLL_MUL(35U, 33U),  ///< PLL multiplier of 35.33
    CGC_PLL_MUL_35_5   = BSP_CLOCKS_PLL_MUL(35U, 50U),  ///< PLL multiplier of 35.50
    CGC_PLL_MUL_35_66  = BSP_CLOCKS_PLL_MUL(35U, 66U),  ///< PLL multiplier of 35.66
    CGC_PLL_MUL_36_0   = BSP_CLOCKS_PLL_MUL(36U, 0U),   ///< PLL multiplier of 36.00
    CGC_PLL_MUL_36_33  = BSP_CLOCKS_PLL_MUL(36U, 33U),  ///< PLL multiplier of 36.33
    CGC_PLL_MUL_36_5   = BSP_CLOCKS_PLL_MUL(36U, 50U),  ///< PLL multiplier of 36.50
    CGC_PLL_MUL_36_66  = BSP_CLOCKS_PLL_MUL(36U, 66U),  ///< PLL multiplier of 36.66
    CGC_PLL_MUL_37_0   = BSP_CLOCKS_PLL_MUL(37U, 0U),   ///< PLL multiplier of 37.00
    CGC_PLL_MUL_37_33  = BSP_CLOCKS_PLL_MUL(37U, 33U),  ///< PLL multiplier of 37.33
    CGC_PLL_MUL_37_5   = BSP_CLOCKS_PLL_MUL(37U, 50U),  ///< PLL multiplier of 37.50
    CGC_PLL_MUL_37_66  = BSP_CLOCKS_PLL_MUL(37U, 66U),  ///< PLL multiplier of 37.66
    CGC_PLL_MUL_38_0   = BSP_CLOCKS_PLL_MUL(38U, 0U),   ///< PLL multiplier of 38.00
    CGC_PLL_MUL_38_33  = BSP_CLOCKS_PLL_MUL(38U, 33U),  ///< PLL multiplier of 38.33
    CGC_PLL_MUL_38_5   = BSP_CLOCKS_PLL_MUL(38U, 50U),  ///< PLL multiplier of 38.50
    CGC_PLL_MUL_38_66  = BSP_CLOCKS_PLL_MUL(38U, 66U),  ///< PLL multiplier of 38.66
    CGC_PLL_MUL_39_0   = BSP_CLOCKS_PLL_MUL(39U, 0U),   ///< PLL multiplier of 39.00
    CGC_PLL_MUL_39_33  = BSP_CLOCKS_PLL_MUL(39U, 33U),  ///< PLL multiplier of 39.33
    CGC_PLL_MUL_39_5   = BSP_CLOCKS_PLL_MUL(39U, 50U),  ///< PLL multiplier of 39.50
    CGC_PLL_MUL_39_66  = BSP_CLOCKS_PLL_MUL(39U, 66U),  ///< PLL multiplier of 39.66
    CGC_PLL_MUL_40_0   = BSP_CLOCKS_PLL_MUL(40U, 0U),   ///< PLL multiplier of 40.00
    CGC_PLL_MUL_40_33  = BSP_CLOCKS_PLL_MUL(40U, 33U),  ///< PLL multiplier of 40.33
    CGC_PLL_MUL_40_5   = BSP_CLOCKS_PLL_MUL(40U, 50U),  ///< PLL multiplier of 40.50
    CGC_PLL_MUL_40_66  = BSP_CLOCKS_PLL_MUL(40U, 66U),  ///< PLL multiplier of 40.66
    CGC_PLL_MUL_41_0   = BSP_CLOCKS_PLL_MUL(41U, 0U),   ///< PLL multiplier of 41.00
    CGC_PLL_MUL_41_33  = BSP_CLOCKS_PLL_MUL(41U, 33U),  ///< PLL multiplier of 41.33
    CGC_PLL_MUL_41_5   = BSP_CLOCKS_PLL_MUL(41U, 50U),  ///< PLL multiplier of 41.50
    CGC_PLL_MUL_41_66  = BSP_CLOCKS_PLL_MUL(41U, 66U),  ///< PLL multiplier of 41.66
    CGC_PLL_MUL_42_0   = BSP_CLOCKS_PLL_MUL(42U, 0U),   ///< PLL multiplier of 42.00
    CGC_PLL_MUL_42_33  = BSP_CLOCKS_PLL_MUL(42U, 33U),  ///< PLL multiplier of 42.33
    CGC_PLL_MUL_42_5   = BSP_CLOCKS_PLL_MUL(42U, 50U),  ///< PLL multiplier of 42.50
    CGC_PLL_MUL_42_66  = BSP_CLOCKS_PLL_MUL(42U, 66U),  ///< PLL multiplier of 42.66
    CGC_PLL_MUL_43_0   = BSP_CLOCKS_PLL_MUL(43U, 0U),   ///< PLL multiplier of 43.00
    CGC_PLL_MUL_43_33  = BSP_CLOCKS_PLL_MUL(43U, 33U),  ///< PLL multiplier of 43.33
    CGC_PLL_MUL_43_5   = BSP_CLOCKS_PLL_MUL(43U, 50U),  ///< PLL multiplier of 43.50
    CGC_PLL_MUL_43_66  = BSP_CLOCKS_PLL_MUL(43U, 66U),  ///< PLL multiplier of 43.66
    CGC_PLL_MUL_44_0   = BSP_CLOCKS_PLL_MUL(44U, 0U),   ///< PLL multiplier of 44.00
    CGC_PLL_MUL_44_33  = BSP_CLOCKS_PLL_MUL(44U, 33U),  ///< PLL multiplier of 44.33
    CGC_PLL_MUL_44_5   = BSP_CLOCKS_PLL_MUL(44U, 50U),  ///< PLL multiplier of 44.50
    CGC_PLL_MUL_44_66  = BSP_CLOCKS_PLL_MUL(44U, 66U),  ///< PLL multiplier of 44.66
    CGC_PLL_MUL_45_0   = BSP_CLOCKS_PLL_MUL(45U, 0U),   ///< PLL multiplier of 45.00
    CGC_PLL_MUL_45_33  = BSP_CLOCKS_PLL_MUL(45U, 33U),  ///< PLL multiplier of 45.33
    CGC_PLL_MUL_45_5   = BSP_CLOCKS_PLL_MUL(45U, 50U),  ///< PLL multiplier of 45.50
    CGC_PLL_MUL_45_66  = BSP_CLOCKS_PLL_MUL(45U, 66U),  ///< PLL multiplier of 45.66
    CGC_PLL_MUL_46_0   = BSP_CLOCKS_PLL_MUL(46U, 0U),   ///< PLL multiplier of 46.00
    CGC_PLL_MUL_46_33  = BSP_CLOCKS_PLL_MUL(46U, 33U),  ///< PLL multiplier of 46.33
    CGC_PLL_MUL_46_5   = BSP_CLOCKS_PLL_MUL(46U, 50U),  ///< PLL multiplier of 46.50
    CGC_PLL_MUL_46_66  = BSP_CLOCKS_PLL_MUL(46U, 66U),  ///< PLL multiplier of 46.66
    CGC_PLL_MUL_47_0   = BSP_CLOCKS_PLL_MUL(47U, 0U),   ///< PLL multiplier of 47.00
    CGC_PLL_MUL_47_33  = BSP_CLOCKS_PLL_MUL(47U, 33U),  ///< PLL multiplier of 47.33
    CGC_PLL_MUL_47_5   = BSP_CLOCKS_PLL_MUL(47U, 50U),  ///< PLL multiplier of 47.50
    CGC_PLL_MUL_47_66  = BSP_CLOCKS_PLL_MUL(47U, 66U),  ///< PLL multiplier of 47.66
    CGC_PLL_MUL_48_0   = BSP_CLOCKS_PLL_MUL(48U, 0U),   ///< PLL multiplier of 48.00
    CGC_PLL_MUL_48_33  = BSP_CLOCKS_PLL_MUL(48U, 33U),  ///< PLL multiplier of 48.33
    CGC_PLL_MUL_48_5   = BSP_CLOCKS_PLL_MUL(48U, 50U),  ///< PLL multiplier of 48.50
    CGC_PLL_MUL_48_66  = BSP_CLOCKS_PLL_MUL(48U, 66U),  ///< PLL multiplier of 48.66
    CGC_PLL_MUL_49_0   = BSP_CLOCKS_PLL_MUL(49U, 0U),   ///< PLL multiplier of 49.00
    CGC_PLL_MUL_49_33  = BSP_CLOCKS_PLL_MUL(49U, 33U),  ///< PLL multiplier of 49.33
    CGC_PLL_MUL_49_5   = BSP_CLOCKS_PLL_MUL(49U, 50U),  ///< PLL multiplier of 49.50
    CGC_PLL_MUL_49_66  = BSP_CLOCKS_PLL_MUL(49U, 66U),  ///< PLL multiplier of 49.66
    CGC_PLL_MUL_50_0   = BSP_CLOCKS_PLL_MUL(50U, 0U),   ///< PLL multiplier of 50.00
    CGC_PLL_MUL_50_33  = BSP_CLOCKS_PLL_MUL(50U, 33U),  ///< PLL multiplier of 50.33
    CGC_PLL_MUL_50_5   = BSP_CLOCKS_PLL_MUL(50U, 50U),  ///< PLL multiplier of 50.50
    CGC_PLL_MUL_50_66  = BSP_CLOCKS_PLL_MUL(50U, 66U),  ///< PLL multiplier of 50.66
    CGC_PLL_MUL_51_0   = BSP_CLOCKS_PLL_MUL(51U, 0U),   ///< PLL multiplier of 51.00
    CGC_PLL_MUL_51_33  = BSP_CLOCKS_PLL_MUL(51U, 33U),  ///< PLL multiplier of 51.33
    CGC_PLL_MUL_51_5   = BSP_CLOCKS_PLL_MUL(51U, 50U),  ///< PLL multiplier of 51.50
    CGC_PLL_MUL_51_66  = BSP_CLOCKS_PLL_MUL(51U, 66U),  ///< PLL multiplier of 51.66
    CGC_PLL_MUL_52_0   = BSP_CLOCKS_PLL_MUL(52U, 0U),   ///< PLL multiplier of 52.00
    CGC_PLL_MUL_52_33  = BSP_CLOCKS_PLL_MUL(52U, 33U),  ///< PLL multiplier of 52.33
    CGC_PLL_MUL_52_5   = BSP_CLOCKS_PLL_MUL(52U, 50U),  ///< PLL multiplier of 52.50
    CGC_PLL_MUL_52_66  = BSP_CLOCKS_PLL_MUL(52U, 66U),  ///< PLL multiplier of 52.66
    CGC_PLL_MUL_53_0   = BSP_CLOCKS_PLL_MUL(53U, 0U),   ///< PLL multiplier of 53.00
    CGC_PLL_MUL_53_33  = BSP_CLOCKS_PLL_MUL(53U, 33U),  ///< PLL multiplier of 53.33
    CGC_PLL_MUL_53_5   = BSP_CLOCKS_PLL_MUL(53U, 50U),  ///< PLL multiplier of 53.50
    CGC_PLL_MUL_53_66  = BSP_CLOCKS_PLL_MUL(53U, 66U),  ///< PLL multiplier of 53.66
    CGC_PLL_MUL_54_0   = BSP_CLOCKS_PLL_MUL(54U, 0U),   ///< PLL multiplier of 54.00
    CGC_PLL_MUL_54_33  = BSP_CLOCKS_PLL_MUL(54U, 33U),  ///< PLL multiplier of 54.33
    CGC_PLL_MUL_54_5   = BSP_CLOCKS_PLL_MUL(54U, 50U),  ///< PLL multiplier of 54.50
    CGC_PLL_MUL_54_66  = BSP_CLOCKS_PLL_MUL(54U, 66U),  ///< PLL multiplier of 54.66
    CGC_PLL_MUL_55_0   = BSP_CLOCKS_PLL_MUL(55U, 0U),   ///< PLL multiplier of 55.00
    CGC_PLL_MUL_55_33  = BSP_CLOCKS_PLL_MUL(55U, 33U),  ///< PLL multiplier of 55.33
    CGC_PLL_MUL_55_5   = BSP_CLOCKS_PLL_MUL(55U, 50U),  ///< PLL multiplier of 55.50
    CGC_PLL_MUL_55_66  = BSP_CLOCKS_PLL_MUL(55U, 66U),  ///< PLL multiplier of 55.66
    CGC_PLL_MUL_56_0   = BSP_CLOCKS_PLL_MUL(56U, 0U),   ///< PLL multiplier of 56.00
    CGC_PLL_MUL_56_33  = BSP_CLOCKS_PLL_MUL(56U, 33U),  ///< PLL multiplier of 56.33
    CGC_PLL_MUL_56_5   = BSP_CLOCKS_PLL_MUL(56U, 50U),  ///< PLL multiplier of 56.50
    CGC_PLL_MUL_56_66  = BSP_CLOCKS_PLL_MUL(56U, 66U),  ///< PLL multiplier of 56.66
    CGC_PLL_MUL_57_0   = BSP_CLOCKS_PLL_MUL(57U, 0U),   ///< PLL multiplier of 57.00
    CGC_PLL_MUL_57_33  = BSP_CLOCKS_PLL_MUL(57U, 33U),  ///< PLL multiplier of 57.33
    CGC_PLL_MUL_57_5   = BSP_CLOCKS_PLL_MUL(57U, 50U),  ///< PLL multiplier of 57.50
    CGC_PLL_MUL_57_66  = BSP_CLOCKS_PLL_MUL(57U, 66U),  ///< PLL multiplier of 57.66
    CGC_PLL_MUL_58_0   = BSP_CLOCKS_PLL_MUL(58U, 0U),   ///< PLL multiplier of 58.00
    CGC_PLL_MUL_58_33  = BSP_CLOCKS_PLL_MUL(58U, 33U),  ///< PLL multiplier of 58.33
    CGC_PLL_MUL_58_5   = BSP_CLOCKS_PLL_MUL(58U, 50U),  ///< PLL multiplier of 58.50
    CGC_PLL_MUL_58_66  = BSP_CLOCKS_PLL_MUL(58U, 66U),  ///< PLL multiplier of 58.66
    CGC_PLL_MUL_59_0   = BSP_CLOCKS_PLL_MUL(59U, 0U),   ///< PLL multiplier of 59.00
    CGC_PLL_MUL_59_33  = BSP_CLOCKS_PLL_MUL(59U, 33U),  ///< PLL multiplier of 59.33
    CGC_PLL_MUL_59_5   = BSP_CLOCKS_PLL_MUL(59U, 50U),  ///< PLL multiplier of 59.50
    CGC_PLL_MUL_59_66  = BSP_CLOCKS_PLL_MUL(59U, 66U),  ///< PLL multiplier of 59.66
    CGC_PLL_MUL_60_0   = BSP_CLOCKS_PLL_MUL(60U, 0U),   ///< PLL multiplier of 60.00
    CGC_PLL_MUL_60_33  = BSP_CLOCKS_PLL_MUL(60U, 33U),  ///< PLL multiplier of 60.33
    CGC_PLL_MUL_60_5   = BSP_CLOCKS_PLL_MUL(60U, 50U),  ///< PLL multiplier of 60.50
    CGC_PLL_MUL_60_66  = BSP_CLOCKS_PLL_MUL(60U, 66U),  ///< PLL multiplier of 60.66
    CGC_PLL_MUL_61_0   = BSP_CLOCKS_PLL_MUL(61U, 0U),   ///< PLL multiplier of 61.00
    CGC_PLL_MUL_61_33  = BSP_CLOCKS_PLL_MUL(61U, 33U),  ///< PLL multiplier of 61.33
    CGC_PLL_MUL_61_5   = BSP_CLOCKS_PLL_MUL(61U, 50U),  ///< PLL multiplier of 61.50
    CGC_PLL_MUL_61_66  = BSP_CLOCKS_PLL_MUL(61U, 66U),  ///< PLL multiplier of 61.66
    CGC_PLL_MUL_62_0   = BSP_CLOCKS_PLL_MUL(62U, 0U),   ///< PLL multiplier of 62.00
    CGC_PLL_MUL_62_33  = BSP_CLOCKS_PLL_MUL(62U, 33U),  ///< PLL multiplier of 62.33
    CGC_PLL_MUL_62_5   = BSP_CLOCKS_PLL_MUL(62U, 50U),  ///< PLL multiplier of 62.50
    CGC_PLL_MUL_62_66  = BSP_CLOCKS_PLL_MUL(62U, 66U),  ///< PLL multiplier of 62.66
    CGC_PLL_MUL_63_0   = BSP_CLOCKS_PLL_MUL(63U, 0U),   ///< PLL multiplier of 63.00
    CGC_PLL_MUL_63_33  = BSP_CLOCKS_PLL_MUL(63U, 33U),  ///< PLL multiplier of 63.33
    CGC_PLL_MUL_63_5   = BSP_CLOCKS_PLL_MUL(63U, 50U),  ///< PLL multiplier of 63.50
    CGC_PLL_MUL_63_66  = BSP_CLOCKS_PLL_MUL(63U, 66U),  ///< PLL multiplier of 63.66
    CGC_PLL_MUL_64_0   = BSP_CLOCKS_PLL_MUL(64U, 0U),   ///< PLL multiplier of 64.00
    CGC_PLL_MUL_64_33  = BSP_CLOCKS_PLL_MUL(64U, 33U),  ///< PLL multiplier of 64.33
    CGC_PLL_MUL_64_5   = BSP_CLOCKS_PLL_MUL(64U, 50U),  ///< PLL multiplier of 64.50
    CGC_PLL_MUL_64_66  = BSP_CLOCKS_PLL_MUL(64U, 66U),  ///< PLL multiplier of 64.66
    CGC_PLL_MUL_65_0   = BSP_CLOCKS_PLL_MUL(65U, 0U),   ///< PLL multiplier of 65.00
    CGC_PLL_MUL_65_33  = BSP_CLOCKS_PLL_MUL(65U, 33U),  ///< PLL multiplier of 65.33
    CGC_PLL_MUL_65_5   = BSP_CLOCKS_PLL_MUL(65U, 50U),  ///< PLL multiplier of 65.50
    CGC_PLL_MUL_65_66  = BSP_CLOCKS_PLL_MUL(65U, 66U),  ///< PLL multiplier of 65.66
    CGC_PLL_MUL_66_0   = BSP_CLOCKS_PLL_MUL(66U, 0U),   ///< PLL multiplier of 66.00
    CGC_PLL_MUL_66_33  = BSP_CLOCKS_PLL_MUL(66U, 33U),  ///< PLL multiplier of 66.33
    CGC_PLL_MUL_66_5   = BSP_CLOCKS_PLL_MUL(66U, 50U),  ///< PLL multiplier of 66.50
    CGC_PLL_MUL_66_66  = BSP_CLOCKS_PLL_MUL(66U, 66U),  ///< PLL multiplier of 66.66
    CGC_PLL_MUL_67_0   = BSP_CLOCKS_PLL_MUL(67U, 0U),   ///< PLL multiplier of 67.00
    CGC_PLL_MUL_67_33  = BSP_CLOCKS_PLL_MUL(67U, 33U),  ///< PLL multiplier of 67.33
    CGC_PLL_MUL_67_5   = BSP_CLOCKS_PLL_MUL(67U, 50U),  ///< PLL multiplier of 67.50
    CGC_PLL_MUL_67_66  = BSP_CLOCKS_PLL_MUL(67U, 66U),  ///< PLL multiplier of 67.66
    CGC_PLL_MUL_68_0   = BSP_CLOCKS_PLL_MUL(68U, 0U),   ///< PLL multiplier of 68.00
    CGC_PLL_MUL_68_33  = BSP_CLOCKS_PLL_MUL(68U, 33U),  ///< PLL multiplier of 68.33
    CGC_PLL_MUL_68_5   = BSP_CLOCKS_PLL_MUL(68U, 50U),  ///< PLL multiplier of 68.50
    CGC_PLL_MUL_68_66  = BSP_CLOCKS_PLL_MUL(68U, 66U),  ///< PLL multiplier of 68.66
    CGC_PLL_MUL_69_0   = BSP_CLOCKS_PLL_MUL(69U, 0U),   ///< PLL multiplier of 69.00
    CGC_PLL_MUL_69_33  = BSP_CLOCKS_PLL_MUL(69U, 33U),  ///< PLL multiplier of 69.33
    CGC_PLL_MUL_69_5   = BSP_CLOCKS_PLL_MUL(69U, 50U),  ///< PLL multiplier of 69.50
    CGC_PLL_MUL_69_66  = BSP_CLOCKS_PLL_MUL(69U, 66U),  ///< PLL multiplier of 69.66
    CGC_PLL_MUL_70_0   = BSP_CLOCKS_PLL_MUL(70U, 0U),   ///< PLL multiplier of 70.00
    CGC_PLL_MUL_70_33  = BSP_CLOCKS_PLL_MUL(70U, 33U),  ///< PLL multiplier of 70.33
    CGC_PLL_MUL_70_5   = BSP_CLOCKS_PLL_MUL(70U, 50U),  ///< PLL multiplier of 70.50
    CGC_PLL_MUL_70_66  = BSP_CLOCKS_PLL_MUL(70U, 66U),  ///< PLL multiplier of 70.66
    CGC_PLL_MUL_71_0   = BSP_CLOCKS_PLL_MUL(71U, 0U),   ///< PLL multiplier of 71.00
    CGC_PLL_MUL_71_33  = BSP_CLOCKS_PLL_MUL(71U, 33U),  ///< PLL multiplier of 71.33
    CGC_PLL_MUL_71_5   = BSP_CLOCKS_PLL_MUL(71U, 50U),  ///< PLL multiplier of 71.50
    CGC_PLL_MUL_71_66  = BSP_CLOCKS_PLL_MUL(71U, 66U),  ///< PLL multiplier of 71.66
    CGC_PLL_MUL_72_0   = BSP_CLOCKS_PLL_MUL(72U, 0U),   ///< PLL multiplier of 72.00
    CGC_PLL_MUL_72_33  = BSP_CLOCKS_PLL_MUL(72U, 33U),  ///< PLL multiplier of 72.33
    CGC_PLL_MUL_72_5   = BSP_CLOCKS_PLL_MUL(72U, 50U),  ///< PLL multiplier of 72.50
    CGC_PLL_MUL_72_66  = BSP_CLOCKS_PLL_MUL(72U, 66U),  ///< PLL multiplier of 72.66
    CGC_PLL_MUL_73_0   = BSP_CLOCKS_PLL_MUL(73U, 0U),   ///< PLL multiplier of 73.00
    CGC_PLL_MUL_73_33  = BSP_CLOCKS_PLL_MUL(73U, 33U),  ///< PLL multiplier of 73.33
    CGC_PLL_MUL_73_5   = BSP_CLOCKS_PLL_MUL(73U, 50U),  ///< PLL multiplier of 73.50
    CGC_PLL_MUL_73_66  = BSP_CLOCKS_PLL_MUL(73U, 66U),  ///< PLL multiplier of 73.66
    CGC_PLL_MUL_74_0   = BSP_CLOCKS_PLL_MUL(74U, 0U),   ///< PLL multiplier of 74.00
    CGC_PLL_MUL_74_33  = BSP_CLOCKS_PLL_MUL(74U, 33U),  ///< PLL multiplier of 74.33
    CGC_PLL_MUL_74_5   = BSP_CLOCKS_PLL_MUL(74U, 50U),  ///< PLL multiplier of 74.50
    CGC_PLL_MUL_74_66  = BSP_CLOCKS_PLL_MUL(74U, 66U),  ///< PLL multiplier of 74.66
    CGC_PLL_MUL_75_0   = BSP_CLOCKS_PLL_MUL(75U, 0U),   ///< PLL multiplier of 75.00
    CGC_PLL_MUL_75_33  = BSP_CLOCKS_PLL_MUL(75U, 33U),  ///< PLL multiplier of 75.33
    CGC_PLL_MUL_75_5   = BSP_CLOCKS_PLL_MUL(75U, 50U),  ///< PLL multiplier of 75.50
    CGC_PLL_MUL_75_66  = BSP_CLOCKS_PLL_MUL(75U, 66U),  ///< PLL multiplier of 75.66
    CGC_PLL_MUL_76_0   = BSP_CLOCKS_PLL_MUL(76U, 0U),   ///< PLL multiplier of 76.00
    CGC_PLL_MUL_76_33  = BSP_CLOCKS_PLL_MUL(76U, 33U),  ///< PLL multiplier of 76.33
    CGC_PLL_MUL_76_5   = BSP_CLOCKS_PLL_MUL(76U, 50U),  ///< PLL multiplier of 76.50
    CGC_PLL_MUL_76_66  = BSP_CLOCKS_PLL_MUL(76U, 66U),  ///< PLL multiplier of 76.66
    CGC_PLL_MUL_77_0   = BSP_CLOCKS_PLL_MUL(77U, 0U),   ///< PLL multiplier of 77.00
    CGC_PLL_MUL_77_33  = BSP_CLOCKS_PLL_MUL(77U, 33U),  ///< PLL multiplier of 77.33
    CGC_PLL_MUL_77_5   = BSP_CLOCKS_PLL_MUL(77U, 50U),  ///< PLL multiplier of 77.50
    CGC_PLL_MUL_77_66  = BSP_CLOCKS_PLL_MUL(77U, 66U),  ///< PLL multiplier of 77.66
    CGC_PLL_MUL_78_0   = BSP_CLOCKS_PLL_MUL(78U, 0U),   ///< PLL multiplier of 78.00
    CGC_PLL_MUL_78_33  = BSP_CLOCKS_PLL_MUL(78U, 33U),  ///< PLL multiplier of 78.33
    CGC_PLL_MUL_78_5   = BSP_CLOCKS_PLL_MUL(78U, 50U),  ///< PLL multiplier of 78.50
    CGC_PLL_MUL_78_66  = BSP_CLOCKS_PLL_MUL(78U, 66U),  ///< PLL multiplier of 78.66
    CGC_PLL_MUL_79_0   = BSP_CLOCKS_PLL_MUL(79U, 0U),   ///< PLL multiplier of 79.00
    CGC_PLL_MUL_79_33  = BSP_CLOCKS_PLL_MUL(79U, 33U),  ///< PLL multiplier of 79.33
    CGC_PLL_MUL_79_5   = BSP_CLOCKS_PLL_MUL(79U, 50U),  ///< PLL multiplier of 79.50
    CGC_PLL_MUL_79_66  = BSP_CLOCKS_PLL_MUL(79U, 66U),  ///< PLL multiplier of 79.66
    CGC_PLL_MUL_80_0   = BSP_CLOCKS_PLL_MUL(80U, 0U),   ///< PLL multiplier of 80.00
    CGC_PLL_MUL_80_33  = BSP_CLOCKS_PLL_MUL(80U, 33U),  ///< PLL multiplier of 80.33
    CGC_PLL_MUL_80_5   = BSP_CLOCKS_PLL_MUL(80U, 50U),  ///< PLL multiplier of 80.50
    CGC_PLL_MUL_80_66  = BSP_CLOCKS_PLL_MUL(80U, 66U),  ///< PLL multiplier of 80.66
    CGC_PLL_MUL_81_0   = BSP_CLOCKS_PLL_MUL(81U, 0U),   ///< PLL multiplier of 81.00
    CGC_PLL_MUL_81_33  = BSP_CLOCKS_PLL_MUL(81U, 33U),  ///< PLL multiplier of 81.33
    CGC_PLL_MUL_81_5   = BSP_CLOCKS_PLL_MUL(81U, 50U),  ///< PLL multiplier of 81.50
    CGC_PLL_MUL_81_66  = BSP_CLOCKS_PLL_MUL(81U, 66U),  ///< PLL multiplier of 81.66
    CGC_PLL_MUL_82_0   = BSP_CLOCKS_PLL_MUL(82U, 0U),   ///< PLL multiplier of 82.00
    CGC_PLL_MUL_82_33  = BSP_CLOCKS_PLL_MUL(82U, 33U),  ///< PLL multiplier of 82.33
    CGC_PLL_MUL_82_5   = BSP_CLOCKS_PLL_MUL(82U, 50U),  ///< PLL multiplier of 82.50
    CGC_PLL_MUL_82_66  = BSP_CLOCKS_PLL_MUL(82U, 66U),  ///< PLL multiplier of 82.66
    CGC_PLL_MUL_83_0   = BSP_CLOCKS_PLL_MUL(83U, 0U),   ///< PLL multiplier of 83.00
    CGC_PLL_MUL_83_33  = BSP_CLOCKS_PLL_MUL(83U, 33U),  ///< PLL multiplier of 83.33
    CGC_PLL_MUL_83_5   = BSP_CLOCKS_PLL_MUL(83U, 50U),  ///< PLL multiplier of 83.50
    CGC_PLL_MUL_83_66  = BSP_CLOCKS_PLL_MUL(83U, 66U),  ///< PLL multiplier of 83.66
    CGC_PLL_MUL_84_0   = BSP_CLOCKS_PLL_MUL(84U, 0U),   ///< PLL multiplier of 84.00
    CGC_PLL_MUL_84_33  = BSP_CLOCKS_PLL_MUL(84U, 33U),  ///< PLL multiplier of 84.33
    CGC_PLL_MUL_84_5   = BSP_CLOCKS_PLL_MUL(84U, 50U),  ///< PLL multiplier of 84.50
    CGC_PLL_MUL_84_66  = BSP_CLOCKS_PLL_MUL(84U, 66U),  ///< PLL multiplier of 84.66
    CGC_PLL_MUL_85_0   = BSP_CLOCKS_PLL_MUL(85U, 0U),   ///< PLL multiplier of 85.00
    CGC_PLL_MUL_85_33  = BSP_CLOCKS_PLL_MUL(85U, 33U),  ///< PLL multiplier of 85.33
    CGC_PLL_MUL_85_5   = BSP_CLOCKS_PLL_MUL(85U, 50U),  ///< PLL multiplier of 85.50
    CGC_PLL_MUL_85_66  = BSP_CLOCKS_PLL_MUL(85U, 66U),  ///< PLL multiplier of 85.66
    CGC_PLL_MUL_86_0   = BSP_CLOCKS_PLL_MUL(86U, 0U),   ///< PLL multiplier of 86.00
    CGC_PLL_MUL_86_33  = BSP_CLOCKS_PLL_MUL(86U, 33U),  ///< PLL multiplier of 86.33
    CGC_PLL_MUL_86_5   = BSP_CLOCKS_PLL_MUL(86U, 50U),  ///< PLL multiplier of 86.50
    CGC_PLL_MUL_86_66  = BSP_CLOCKS_PLL_MUL(86U, 66U),  ///< PLL multiplier of 86.66
    CGC_PLL_MUL_87_0   = BSP_CLOCKS_PLL_MUL(87U, 0U),   ///< PLL multiplier of 87.00
    CGC_PLL_MUL_87_33  = BSP_CLOCKS_PLL_MUL(87U, 33U),  ///< PLL multiplier of 87.33
    CGC_PLL_MUL_87_5   = BSP_CLOCKS_PLL_MUL(87U, 50U),  ///< PLL multiplier of 87.50
    CGC_PLL_MUL_87_66  = BSP_CLOCKS_PLL_MUL(87U, 66U),  ///< PLL multiplier of 87.66
    CGC_PLL_MUL_88_0   = BSP_CLOCKS_PLL_MUL(88U, 0U),   ///< PLL multiplier of 88.00
    CGC_PLL_MUL_88_33  = BSP_CLOCKS_PLL_MUL(88U, 33U),  ///< PLL multiplier of 88.33
    CGC_PLL_MUL_88_5   = BSP_CLOCKS_PLL_MUL(88U, 50U),  ///< PLL multiplier of 88.50
    CGC_PLL_MUL_88_66  = BSP_CLOCKS_PLL_MUL(88U, 66U),  ///< PLL multiplier of 88.66
    CGC_PLL_MUL_89_0   = BSP_CLOCKS_PLL_MUL(89U, 0U),   ///< PLL multiplier of 89.00
    CGC_PLL_MUL_89_33  = BSP_CLOCKS_PLL_MUL(89U, 33U),  ///< PLL multiplier of 89.33
    CGC_PLL_MUL_89_5   = BSP_CLOCKS_PLL_MUL(89U, 50U),  ///< PLL multiplier of 89.50
    CGC_PLL_MUL_89_66  = BSP_CLOCKS_PLL_MUL(89U, 66U),  ///< PLL multiplier of 89.66
    CGC_PLL_MUL_90_0   = BSP_CLOCKS_PLL_MUL(90U, 0U),   ///< PLL multiplier of 90.00
    CGC_PLL_MUL_90_33  = BSP_CLOCKS_PLL_MUL(90U, 33U),  ///< PLL multiplier of 90.33
    CGC_PLL_MUL_90_5   = BSP_CLOCKS_PLL_MUL(90U, 50U),  ///< PLL multiplier of 90.50
    CGC_PLL_MUL_90_66  = BSP_CLOCKS_PLL_MUL(90U, 66U),  ///< PLL multiplier of 90.66
    CGC_PLL_MUL_91_0   = BSP_CLOCKS_PLL_MUL(91U, 0U),   ///< PLL multiplier of 91.00
    CGC_PLL_MUL_91_33  = BSP_CLOCKS_PLL_MUL(91U, 33U),  ///< PLL multiplier of 91.33
    CGC_PLL_MUL_91_5   = BSP_CLOCKS_PLL_MUL(91U, 50U),  ///< PLL multiplier of 91.50
    CGC_PLL_MUL_91_66  = BSP_CLOCKS_PLL_MUL(91U, 66U),  ///< PLL multiplier of 91.66
    CGC_PLL_MUL_92_0   = BSP_CLOCKS_PLL_MUL(92U, 0U),   ///< PLL multiplier of 92.00
    CGC_PLL_MUL_92_33  = BSP_CLOCKS_PLL_MUL(92U, 33U),  ///< PLL multiplier of 92.33
    CGC_PLL_MUL_92_5   = BSP_CLOCKS_PLL_MUL(92U, 50U),  ///< PLL multiplier of 92.50
    CGC_PLL_MUL_92_66  = BSP_CLOCKS_PLL_MUL(92U, 66U),  ///< PLL multiplier of 92.66
    CGC_PLL_MUL_93_0   = BSP_CLOCKS_PLL_MUL(93U, 0U),   ///< PLL multiplier of 93.00
    CGC_PLL_MUL_93_33  = BSP_CLOCKS_PLL_MUL(93U, 33U),  ///< PLL multiplier of 93.33
    CGC_PLL_MUL_93_5   = BSP_CLOCKS_PLL_MUL(93U, 50U),  ///< PLL multiplier of 93.50
    CGC_PLL_MUL_93_66  = BSP_CLOCKS_PLL_MUL(93U, 66U),  ///< PLL multiplier of 93.66
    CGC_PLL_MUL_94_0   = BSP_CLOCKS_PLL_MUL(94U, 0U),   ///< PLL multiplier of 94.00
    CGC_PLL_MUL_94_33  = BSP_CLOCKS_PLL_MUL(94U, 33U),  ///< PLL multiplier of 94.33
    CGC_PLL_MUL_94_5   = BSP_CLOCKS_PLL_MUL(94U, 50U),  ///< PLL multiplier of 94.50
    CGC_PLL_MUL_94_66  = BSP_CLOCKS_PLL_MUL(94U, 66U),  ///< PLL multiplier of 94.66
    CGC_PLL_MUL_95_0   = BSP_CLOCKS_PLL_MUL(95U, 0U),   ///< PLL multiplier of 95.00
    CGC_PLL_MUL_95_33  = BSP_CLOCKS_PLL_MUL(95U, 33U),  ///< PLL multiplier of 95.33
    CGC_PLL_MUL_95_5   = BSP_CLOCKS_PLL_MUL(95U, 50U),  ///< PLL multiplier of 95.50
    CGC_PLL_MUL_95_66  = BSP_CLOCKS_PLL_MUL(95U, 66U),  ///< PLL multiplier of 95.66
    CGC_PLL_MUL_96_0   = BSP_CLOCKS_PLL_MUL(96U, 0U),   ///< PLL multiplier of 96.00
    CGC_PLL_MUL_96_33  = BSP_CLOCKS_PLL_MUL(96U, 33U),  ///< PLL multiplier of 96.33
    CGC_PLL_MUL_96_5   = BSP_CLOCKS_PLL_MUL(96U, 50U),  ///< PLL multiplier of 96.50
    CGC_PLL_MUL_96_66  = BSP_CLOCKS_PLL_MUL(96U, 66U),  ///< PLL multiplier of 96.66
    CGC_PLL_MUL_97_0   = BSP_CLOCKS_PLL_MUL(97U, 0U),   ///< PLL multiplier of 97.00
    CGC_PLL_MUL_97_33  = BSP_CLOCKS_PLL_MUL(97U, 33U),  ///< PLL multiplier of 97.33
    CGC_PLL_MUL_97_5   = BSP_CLOCKS_PLL_MUL(97U, 50U),  ///< PLL multiplier of 97.50
    CGC_PLL_MUL_97_66  = BSP_CLOCKS_PLL_MUL(97U, 66U),  ///< PLL multiplier of 97.66
    CGC_PLL_MUL_98_0   = BSP_CLOCKS_PLL_MUL(98U, 0U),   ///< PLL multiplier of 98.00
    CGC_PLL_MUL_98_33  = BSP_CLOCKS_PLL_MUL(98U, 33U),  ///< PLL multiplier of 98.33
    CGC_PLL_MUL_98_5   = BSP_CLOCKS_PLL_MUL(98U, 50U),  ///< PLL multiplier of 98.50
    CGC_PLL_MUL_98_66  = BSP_CLOCKS_PLL_MUL(98U, 66U),  ///< PLL multiplier of 98.66
    CGC_PLL_MUL_99_0   = BSP_CLOCKS_PLL_MUL(99U, 0U),   ///< PLL multiplier of 99.00
    CGC_PLL_MUL_99_33  = BSP_CLOCKS_PLL_MUL(99U, 33U),  ///< PLL multiplier of 99.33
    CGC_PLL_MUL_99_5   = BSP_CLOCKS_PLL_MUL(99U, 50U),  ///< PLL multiplier of 99.50
    CGC_PLL_MUL_99_66  = BSP_CLOCKS_PLL_MUL(99U, 66U),  ///< PLL multiplier of 99.66
    CGC_PLL_MUL_100_0  = BSP_CLOCKS_PLL_MUL(100U, 0U),  ///< PLL multiplier of 100.00
    CGC_PLL_MUL_100_33 = BSP_CLOCKS_PLL_MUL(100U, 33U), ///< PLL multiplier of 100.33
    CGC_PLL_MUL_100_5  = BSP_CLOCKS_PLL_MUL(100U, 50U), ///< PLL multiplier of 100.50
    CGC_PLL_MUL_100_66 = BSP_CLOCKS_PLL_MUL(100U, 66U), ///< PLL multiplier of 100.66
    CGC_PLL_MUL_101_0  = BSP_CLOCKS_PLL_MUL(101U, 0U),  ///< PLL multiplier of 101.00
    CGC_PLL_MUL_101_33 = BSP_CLOCKS_PLL_MUL(101U, 33U), ///< PLL multiplier of 101.33
    CGC_PLL_MUL_101_5  = BSP_CLOCKS_PLL_MUL(101U, 50U), ///< PLL multiplier of 101.50
    CGC_PLL_MUL_101_66 = BSP_CLOCKS_PLL_MUL(101U, 66U), ///< PLL multiplier of 101.66
    CGC_PLL_MUL_102_0  = BSP_CLOCKS_PLL_MUL(102U, 0U),  ///< PLL multiplier of 102.00
    CGC_PLL_MUL_102_33 = BSP_CLOCKS_PLL_MUL(102U, 33U), ///< PLL multiplier of 102.33
    CGC_PLL_MUL_102_5  = BSP_CLOCKS_PLL_MUL(102U, 50U), ///< PLL multiplier of 102.50
    CGC_PLL_MUL_102_66 = BSP_CLOCKS_PLL_MUL(102U, 66U), ///< PLL multiplier of 102.66
    CGC_PLL_MUL_103_0  = BSP_CLOCKS_PLL_MUL(103U, 0U),  ///< PLL multiplier of 103.00
    CGC_PLL_MUL_103_33 = BSP_CLOCKS_PLL_MUL(103U, 33U), ///< PLL multiplier of 103.33
    CGC_PLL_MUL_103_5  = BSP_CLOCKS_PLL_MUL(103U, 50U), ///< PLL multiplier of 103.50
    CGC_PLL_MUL_103_66 = BSP_CLOCKS_PLL_MUL(103U, 66U), ///< PLL multiplier of 103.66
    CGC_PLL_MUL_104_0  = BSP_CLOCKS_PLL_MUL(104U, 0U),  ///< PLL multiplier of 104.00
    CGC_PLL_MUL_104_33 = BSP_CLOCKS_PLL_MUL(104U, 33U), ///< PLL multiplier of 104.33
    CGC_PLL_MUL_104_5  = BSP_CLOCKS_PLL_MUL(104U, 50U), ///< PLL multiplier of 104.50
    CGC_PLL_MUL_104_66 = BSP_CLOCKS_PLL_MUL(104U, 66U), ///< PLL multiplier of 104.66
    CGC_PLL_MUL_105_0  = BSP_CLOCKS_PLL_MUL(105U, 0U),  ///< PLL multiplier of 105.00
    CGC_PLL_MUL_105_33 = BSP_CLOCKS_PLL_MUL(105U, 33U), ///< PLL multiplier of 105.33
    CGC_PLL_MUL_105_5  = BSP_CLOCKS_PLL_MUL(105U, 50U), ///< PLL multiplier of 105.50
    CGC_PLL_MUL_105_66 = BSP_CLOCKS_PLL_MUL(105U, 66U), ///< PLL multiplier of 105.66
    CGC_PLL_MUL_106_0  = BSP_CLOCKS_PLL_MUL(106U, 0U),  ///< PLL multiplier of 106.00
    CGC_PLL_MUL_106_33 = BSP_CLOCKS_PLL_MUL(106U, 33U), ///< PLL multiplier of 106.33
    CGC_PLL_MUL_106_5  = BSP_CLOCKS_PLL_MUL(106U, 50U), ///< PLL multiplier of 106.50
    CGC_PLL_MUL_106_66 = BSP_CLOCKS_PLL_MUL(106U, 66U), ///< PLL multiplier of 106.66
    CGC_PLL_MUL_107_0  = BSP_CLOCKS_PLL_MUL(107U, 0U),  ///< PLL multiplier of 107.00
    CGC_PLL_MUL_107_33 = BSP_CLOCKS_PLL_MUL(107U, 33U), ///< PLL multiplier of 107.33
    CGC_PLL_MUL_107_5  = BSP_CLOCKS_PLL_MUL(107U, 50U), ///< PLL multiplier of 107.50
    CGC_PLL_MUL_107_66 = BSP_CLOCKS_PLL_MUL(107U, 66U), ///< PLL multiplier of 107.66
    CGC_PLL_MUL_108_0  = BSP_CLOCKS_PLL_MUL(108U, 0U),  ///< PLL multiplier of 108.00
    CGC_PLL_MUL_108_33 = BSP_CLOCKS_PLL_MUL(108U, 33U), ///< PLL multiplier of 108.33
    CGC_PLL_MUL_108_5  = BSP_CLOCKS_PLL_MUL(108U, 50U), ///< PLL multiplier of 108.50
    CGC_PLL_MUL_108_66 = BSP_CLOCKS_PLL_MUL(108U, 66U), ///< PLL multiplier of 108.66
    CGC_PLL_MUL_109_0  = BSP_CLOCKS_PLL_MUL(109U, 0U),  ///< PLL multiplier of 109.00
    CGC_PLL_MUL_109_33 = BSP_CLOCKS_PLL_MUL(109U, 33U), ///< PLL multiplier of 109.33
    CGC_PLL_MUL_109_5  = BSP_CLOCKS_PLL_MUL(109U, 50U), ///< PLL multiplier of 109.50
    CGC_PLL_MUL_109_66 = BSP_CLOCKS_PLL_MUL(109U, 66U), ///< PLL multiplier of 109.66
    CGC_PLL_MUL_110_0  = BSP_CLOCKS_PLL_MUL(110U, 0U),  ///< PLL multiplier of 110.00
    CGC_PLL_MUL_110_33 = BSP_CLOCKS_PLL_MUL(110U, 33U), ///< PLL multiplier of 110.33
    CGC_PLL_MUL_110_5  = BSP_CLOCKS_PLL_MUL(110U, 50U), ///< PLL multiplier of 110.50
    CGC_PLL_MUL_110_66 = BSP_CLOCKS_PLL_MUL(110U, 66U), ///< PLL multiplier of 110.66
    CGC_PLL_MUL_111_0  = BSP_CLOCKS_PLL_MUL(111U, 0U),  ///< PLL multiplier of 111.00
    CGC_PLL_MUL_111_33 = BSP_CLOCKS_PLL_MUL(111U, 33U), ///< PLL multiplier of 111.33
    CGC_PLL_MUL_111_5  = BSP_CLOCKS_PLL_MUL(111U, 50U), ///< PLL multiplier of 111.50
    CGC_PLL_MUL_111_66 = BSP_CLOCKS_PLL_MUL(111U, 66U), ///< PLL multiplier of 111.66
    CGC_PLL_MUL_112_0  = BSP_CLOCKS_PLL_MUL(112U, 0U),  ///< PLL multiplier of 112.00
    CGC_PLL_MUL_112_33 = BSP_CLOCKS_PLL_MUL(112U, 33U), ///< PLL multiplier of 112.33
    CGC_PLL_MUL_112_5  = BSP_CLOCKS_PLL_MUL(112U, 50U), ///< PLL multiplier of 112.50
    CGC_PLL_MUL_112_66 = BSP_CLOCKS_PLL_MUL(112U, 66U), ///< PLL multiplier of 112.66
    CGC_PLL_MUL_113_0  = BSP_CLOCKS_PLL_MUL(113U, 0U),  ///< PLL multiplier of 113.00
    CGC_PLL_MUL_113_33 = BSP_CLOCKS_PLL_MUL(113U, 33U), ///< PLL multiplier of 113.33
    CGC_PLL_MUL_113_5  = BSP_CLOCKS_PLL_MUL(113U, 50U), ///< PLL multiplier of 113.50
    CGC_PLL_MUL_113_66 = BSP_CLOCKS_PLL_MUL(113U, 66U), ///< PLL multiplier of 113.66
    CGC_PLL_MUL_114_0  = BSP_CLOCKS_PLL_MUL(114U, 0U),  ///< PLL multiplier of 114.00
    CGC_PLL_MUL_114_33 = BSP_CLOCKS_PLL_MUL(114U, 33U), ///< PLL multiplier of 114.33
    CGC_PLL_MUL_114_5  = BSP_CLOCKS_PLL_MUL(114U, 50U), ///< PLL multiplier of 114.50
    CGC_PLL_MUL_114_66 = BSP_CLOCKS_PLL_MUL(114U, 66U), ///< PLL multiplier of 114.66
    CGC_PLL_MUL_115_0  = BSP_CLOCKS_PLL_MUL(115U, 0U),  ///< PLL multiplier of 115.00
    CGC_PLL_MUL_115_33 = BSP_CLOCKS_PLL_MUL(115U, 33U), ///< PLL multiplier of 115.33
    CGC_PLL_MUL_115_5  = BSP_CLOCKS_PLL_MUL(115U, 50U), ///< PLL multiplier of 115.50
    CGC_PLL_MUL_115_66 = BSP_CLOCKS_PLL_MUL(115U, 66U), ///< PLL multiplier of 115.66
    CGC_PLL_MUL_116_0  = BSP_CLOCKS_PLL_MUL(116U, 0U),  ///< PLL multiplier of 116.00
    CGC_PLL_MUL_116_33 = BSP_CLOCKS_PLL_MUL(116U, 33U), ///< PLL multiplier of 116.33
    CGC_PLL_MUL_116_5  = BSP_CLOCKS_PLL_MUL(116U, 50U), ///< PLL multiplier of 116.50
    CGC_PLL_MUL_116_66 = BSP_CLOCKS_PLL_MUL(116U, 66U), ///< PLL multiplier of 116.66
    CGC_PLL_MUL_117_0  = BSP_CLOCKS_PLL_MUL(117U, 0U),  ///< PLL multiplier of 117.00
    CGC_PLL_MUL_117_33 = BSP_CLOCKS_PLL_MUL(117U, 33U), ///< PLL multiplier of 117.33
    CGC_PLL_MUL_117_5  = BSP_CLOCKS_PLL_MUL(117U, 50U), ///< PLL multiplier of 117.50
    CGC_PLL_MUL_117_66 = BSP_CLOCKS_PLL_MUL(117U, 66U), ///< PLL multiplier of 117.66
    CGC_PLL_MUL_118_0  = BSP_CLOCKS_PLL_MUL(118U, 0U),  ///< PLL multiplier of 118.00
    CGC_PLL_MUL_118_33 = BSP_CLOCKS_PLL_MUL(118U, 33U), ///< PLL multiplier of 118.33
    CGC_PLL_MUL_118_5  = BSP_CLOCKS_PLL_MUL(118U, 50U), ///< PLL multiplier of 118.50
    CGC_PLL_MUL_118_66 = BSP_CLOCKS_PLL_MUL(118U, 66U), ///< PLL multiplier of 118.66
    CGC_PLL_MUL_119_0  = BSP_CLOCKS_PLL_MUL(119U, 0U),  ///< PLL multiplier of 119.00
    CGC_PLL_MUL_119_33 = BSP_CLOCKS_PLL_MUL(119U, 33U), ///< PLL multiplier of 119.33
    CGC_PLL_MUL_119_5  = BSP_CLOCKS_PLL_MUL(119U, 50U), ///< PLL multiplier of 119.50
    CGC_PLL_MUL_119_66 = BSP_CLOCKS_PLL_MUL(119U, 66U), ///< PLL multiplier of 119.66
    CGC_PLL_MUL_120_0  = BSP_CLOCKS_PLL_MUL(120U, 0U),  ///< PLL multiplier of 120.00
    CGC_PLL_MUL_120_33 = BSP_CLOCKS_PLL_MUL(120U, 33U), ///< PLL multiplier of 120.33
    CGC_PLL_MUL_120_5  = BSP_CLOCKS_PLL_MUL(120U, 50U), ///< PLL multiplier of 120.50
    CGC_PLL_MUL_120_66 = BSP_CLOCKS_PLL_MUL(120U, 66U), ///< PLL multiplier of 120.66
    CGC_PLL_MUL_121_0  = BSP_CLOCKS_PLL_MUL(121U, 0U),  ///< PLL multiplier of 121.00
    CGC_PLL_MUL_121_33 = BSP_CLOCKS_PLL_MUL(121U, 33U), ///< PLL multiplier of 121.33
    CGC_PLL_MUL_121_5  = BSP_CLOCKS_PLL_MUL(121U, 50U), ///< PLL multiplier of 121.50
    CGC_PLL_MUL_121_66 = BSP_CLOCKS_PLL_MUL(121U, 66U), ///< PLL multiplier of 121.66
    CGC_PLL_MUL_122_0  = BSP_CLOCKS_PLL_MUL(122U, 0U),  ///< PLL multiplier of 122.00
    CGC_PLL_MUL_122_33 = BSP_CLOCKS_PLL_MUL(122U, 33U), ///< PLL multiplier of 122.33
    CGC_PLL_MUL_122_5  = BSP_CLOCKS_PLL_MUL(122U, 50U), ///< PLL multiplier of 122.50
    CGC_PLL_MUL_122_66 = BSP_CLOCKS_PLL_MUL(122U, 66U), ///< PLL multiplier of 122.66
    CGC_PLL_MUL_123_0  = BSP_CLOCKS_PLL_MUL(123U, 0U),  ///< PLL multiplier of 123.00
    CGC_PLL_MUL_123_33 = BSP_CLOCKS_PLL_MUL(123U, 33U), ///< PLL multiplier of 123.33
    CGC_PLL_MUL_123_5  = BSP_CLOCKS_PLL_MUL(123U, 50U), ///< PLL multiplier of 123.50
    CGC_PLL_MUL_123_66 = BSP_CLOCKS_PLL_MUL(123U, 66U), ///< PLL multiplier of 123.66
    CGC_PLL_MUL_124_0  = BSP_CLOCKS_PLL_MUL(124U, 0U),  ///< PLL multiplier of 124.00
    CGC_PLL_MUL_124_33 = BSP_CLOCKS_PLL_MUL(124U, 33U), ///< PLL multiplier of 124.33
    CGC_PLL_MUL_124_5  = BSP_CLOCKS_PLL_MUL(124U, 50U), ///< PLL multiplier of 124.50
    CGC_PLL_MUL_124_66 = BSP_CLOCKS_PLL_MUL(124U, 66U), ///< PLL multiplier of 124.66
    CGC_PLL_MUL_125_0  = BSP_CLOCKS_PLL_MUL(125U, 0U),  ///< PLL multiplier of 125.00
    CGC_PLL_MUL_125_33 = BSP_CLOCKS_PLL_MUL(125U, 33U), ///< PLL multiplier of 125.33
    CGC_PLL_MUL_125_5  = BSP_CLOCKS_PLL_MUL(125U, 50U), ///< PLL multiplier of 125.50
    CGC_PLL_MUL_125_66 = BSP_CLOCKS_PLL_MUL(125U, 66U), ///< PLL multiplier of 125.66
    CGC_PLL_MUL_126_0  = BSP_CLOCKS_PLL_MUL(126U, 0U),  ///< PLL multiplier of 126.00
    CGC_PLL_MUL_126_33 = BSP_CLOCKS_PLL_MUL(126U, 33U), ///< PLL multiplier of 126.33
    CGC_PLL_MUL_126_5  = BSP_CLOCKS_PLL_MUL(126U, 50U), ///< PLL multiplier of 126.50
    CGC_PLL_MUL_126_66 = BSP_CLOCKS_PLL_MUL(126U, 66U), ///< PLL multiplier of 126.66
    CGC_PLL_MUL_127_0  = BSP_CLOCKS_PLL_MUL(127U, 0U),  ///< PLL multiplier of 127.00
    CGC_PLL_MUL_127_33 = BSP_CLOCKS_PLL_MUL(127U, 33U), ///< PLL multiplier of 127.33
    CGC_PLL_MUL_127_5  = BSP_CLOCKS_PLL_MUL(127U, 50U), ///< PLL multiplier of 127.50
    CGC_PLL_MUL_127_66 = BSP_CLOCKS_PLL_MUL(127U, 66U), ///< PLL multiplier of 127.66
    CGC_PLL_MUL_128_0  = BSP_CLOCKS_PLL_MUL(128U, 0U),  ///< PLL multiplier of 128.00
    CGC_PLL_MUL_128_33 = BSP_CLOCKS_PLL_MUL(128U, 33U), ///< PLL multiplier of 128.33
    CGC_PLL_MUL_128_5  = BSP_CLOCKS_PLL_MUL(128U, 50U), ///< PLL multiplier of 128.50
    CGC_PLL_MUL_128_66 = BSP_CLOCKS_PLL_MUL(128U, 66U), ///< PLL multiplier of 128.66
    CGC_PLL_MUL_129_0  = BSP_CLOCKS_PLL_MUL(129U, 0U),  ///< PLL multiplier of 129.00
    CGC_PLL_MUL_129_33 = BSP_CLOCKS_PLL_MUL(129U, 33U), ///< PLL multiplier of 129.33
    CGC_PLL_MUL_129_5  = BSP_CLOCKS_PLL_MUL(129U, 50U), ///< PLL multiplier of 129.50
    CGC_PLL_MUL_129_66 = BSP_CLOCKS_PLL_MUL(129U, 66U), ///< PLL multiplier of 129.66
    CGC_PLL_MUL_130_0  = BSP_CLOCKS_PLL_MUL(130U, 0U),  ///< PLL multiplier of 130.00
    CGC_PLL_MUL_130_33 = BSP_CLOCKS_PLL_MUL(130U, 33U), ///< PLL multiplier of 130.33
    CGC_PLL_MUL_130_5  = BSP_CLOCKS_PLL_MUL(130U, 50U), ///< PLL multiplier of 130.50
    CGC_PLL_MUL_130_66 = BSP_CLOCKS_PLL_MUL(130U, 66U), ///< PLL multiplier of 130.66
    CGC_PLL_MUL_131_0  = BSP_CLOCKS_PLL_MUL(131U, 0U),  ///< PLL multiplier of 131.00
    CGC_PLL_MUL_131_33 = BSP_CLOCKS_PLL_MUL(131U, 33U), ///< PLL multiplier of 131.33
    CGC_PLL_MUL_131_5  = BSP_CLOCKS_PLL_MUL(131U, 50U), ///< PLL multiplier of 131.50
    CGC_PLL_MUL_131_66 = BSP_CLOCKS_PLL_MUL(131U, 66U), ///< PLL multiplier of 131.66
    CGC_PLL_MUL_132_0  = BSP_CLOCKS_PLL_MUL(132U, 0U),  ///< PLL multiplier of 132.00
    CGC_PLL_MUL_132_33 = BSP_CLOCKS_PLL_MUL(132U, 33U), ///< PLL multiplier of 132.33
    CGC_PLL_MUL_132_5  = BSP_CLOCKS_PLL_MUL(132U, 50U), ///< PLL multiplier of 132.50
    CGC_PLL_MUL_132_66 = BSP_CLOCKS_PLL_MUL(132U, 66U), ///< PLL multiplier of 132.66
    CGC_PLL_MUL_133_0  = BSP_CLOCKS_PLL_MUL(133U, 0U),  ///< PLL multiplier of 133.00
    CGC_PLL_MUL_133_33 = BSP_CLOCKS_PLL_MUL(133U, 33U), ///< PLL multiplier of 133.33
    CGC_PLL_MUL_133_5  = BSP_CLOCKS_PLL_MUL(133U, 50U), ///< PLL multiplier of 133.50
    CGC_PLL_MUL_133_66 = BSP_CLOCKS_PLL_MUL(133U, 66U), ///< PLL multiplier of 133.66
    CGC_PLL_MUL_134_0  = BSP_CLOCKS_PLL_MUL(134U, 0U),  ///< PLL multiplier of 134.00
    CGC_PLL_MUL_134_33 = BSP_CLOCKS_PLL_MUL(134U, 33U), ///< PLL multiplier of 134.33
    CGC_PLL_MUL_134_5  = BSP_CLOCKS_PLL_MUL(134U, 50U), ///< PLL multiplier of 134.50
    CGC_PLL_MUL_134_66 = BSP_CLOCKS_PLL_MUL(134U, 66U), ///< PLL multiplier of 134.66
    CGC_PLL_MUL_135_0  = BSP_CLOCKS_PLL_MUL(135U, 0U),  ///< PLL multiplier of 135.00
    CGC_PLL_MUL_135_33 = BSP_CLOCKS_PLL_MUL(135U, 33U), ///< PLL multiplier of 135.33
    CGC_PLL_MUL_135_5  = BSP_CLOCKS_PLL_MUL(135U, 50U), ///< PLL multiplier of 135.50
    CGC_PLL_MUL_135_66 = BSP_CLOCKS_PLL_MUL(135U, 66U), ///< PLL multiplier of 135.66
    CGC_PLL_MUL_136_0  = BSP_CLOCKS_PLL_MUL(136U, 0U),  ///< PLL multiplier of 136.00
    CGC_PLL_MUL_136_33 = BSP_CLOCKS_PLL_MUL(136U, 33U), ///< PLL multiplier of 136.33
    CGC_PLL_MUL_136_5  = BSP_CLOCKS_PLL_MUL(136U, 50U), ///< PLL multiplier of 136.50
    CGC_PLL_MUL_136_66 = BSP_CLOCKS_PLL_MUL(136U, 66U), ///< PLL multiplier of 136.66
    CGC_PLL_MUL_137_0  = BSP_CLOCKS_PLL_MUL(137U, 0U),  ///< PLL multiplier of 137.00
    CGC_PLL_MUL_137_33 = BSP_CLOCKS_PLL_MUL(137U, 33U), ///< PLL multiplier of 137.33
    CGC_PLL_MUL_137_5  = BSP_CLOCKS_PLL_MUL(137U, 50U), ///< PLL multiplier of 137.50
    CGC_PLL_MUL_137_66 = BSP_CLOCKS_PLL_MUL(137U, 66U), ///< PLL multiplier of 137.66
    CGC_PLL_MUL_138_0  = BSP_CLOCKS_PLL_MUL(138U, 0U),  ///< PLL multiplier of 138.00
    CGC_PLL_MUL_138_33 = BSP_CLOCKS_PLL_MUL(138U, 33U), ///< PLL multiplier of 138.33
    CGC_PLL_MUL_138_5  = BSP_CLOCKS_PLL_MUL(138U, 50U), ///< PLL multiplier of 138.50
    CGC_PLL_MUL_138_66 = BSP_CLOCKS_PLL_MUL(138U, 66U), ///< PLL multiplier of 138.66
    CGC_PLL_MUL_139_0  = BSP_CLOCKS_PLL_MUL(139U, 0U),  ///< PLL multiplier of 139.00
    CGC_PLL_MUL_139_33 = BSP_CLOCKS_PLL_MUL(139U, 33U), ///< PLL multiplier of 139.33
    CGC_PLL_MUL_139_5  = BSP_CLOCKS_PLL_MUL(139U, 50U), ///< PLL multiplier of 139.50
    CGC_PLL_MUL_139_66 = BSP_CLOCKS_PLL_MUL(139U, 66U), ///< PLL multiplier of 139.66
    CGC_PLL_MUL_140_0  = BSP_CLOCKS_PLL_MUL(140U, 0U),  ///< PLL multiplier of 140.00
    CGC_PLL_MUL_140_33 = BSP_CLOCKS_PLL_MUL(140U, 33U), ///< PLL multiplier of 140.33
    CGC_PLL_MUL_140_5  = BSP_CLOCKS_PLL_MUL(140U, 50U), ///< PLL multiplier of 140.50
    CGC_PLL_MUL_140_66 = BSP_CLOCKS_PLL_MUL(140U, 66U), ///< PLL multiplier of 140.66
    CGC_PLL_MUL_141_0  = BSP_CLOCKS_PLL_MUL(141U, 0U),  ///< PLL multiplier of 141.00
    CGC_PLL_MUL_141_33 = BSP_CLOCKS_PLL_MUL(141U, 33U), ///< PLL multiplier of 141.33
    CGC_PLL_MUL_141_5  = BSP_CLOCKS_PLL_MUL(141U, 50U), ///< PLL multiplier of 141.50
    CGC_PLL_MUL_141_66 = BSP_CLOCKS_PLL_MUL(141U, 66U), ///< PLL multiplier of 141.66
    CGC_PLL_MUL_142_0  = BSP_CLOCKS_PLL_MUL(142U, 0U),  ///< PLL multiplier of 142.00
    CGC_PLL_MUL_142_33 = BSP_CLOCKS_PLL_MUL(142U, 33U), ///< PLL multiplier of 142.33
    CGC_PLL_MUL_142_5  = BSP_CLOCKS_PLL_MUL(142U, 50U), ///< PLL multiplier of 142.50
    CGC_PLL_MUL_142_66 = BSP_CLOCKS_PLL_MUL(142U, 66U), ///< PLL multiplier of 142.66
    CGC_PLL_MUL_143_0  = BSP_CLOCKS_PLL_MUL(143U, 0U),  ///< PLL multiplier of 143.00
    CGC_PLL_MUL_143_33 = BSP_CLOCKS_PLL_MUL(143U, 33U), ///< PLL multiplier of 143.33
    CGC_PLL_MUL_143_5  = BSP_CLOCKS_PLL_MUL(143U, 50U), ///< PLL multiplier of 143.50
    CGC_PLL_MUL_143_66 = BSP_CLOCKS_PLL_MUL(143U, 66U), ///< PLL multiplier of 143.66
    CGC_PLL_MUL_144_0  = BSP_CLOCKS_PLL_MUL(144U, 0U),  ///< PLL multiplier of 144.00
    CGC_PLL_MUL_144_33 = BSP_CLOCKS_PLL_MUL(144U, 33U), ///< PLL multiplier of 144.33
    CGC_PLL_MUL_144_5  = BSP_CLOCKS_PLL_MUL(144U, 50U), ///< PLL multiplier of 144.50
    CGC_PLL_MUL_144_66 = BSP_CLOCKS_PLL_MUL(144U, 66U), ///< PLL multiplier of 144.66
    CGC_PLL_MUL_145_0  = BSP_CLOCKS_PLL_MUL(145U, 0U),  ///< PLL multiplier of 145.00
    CGC_PLL_MUL_145_33 = BSP_CLOCKS_PLL_MUL(145U, 33U), ///< PLL multiplier of 145.33
    CGC_PLL_MUL_145_5  = BSP_CLOCKS_PLL_MUL(145U, 50U), ///< PLL multiplier of 145.50
    CGC_PLL_MUL_145_66 = BSP_CLOCKS_PLL_MUL(145U, 66U), ///< PLL multiplier of 145.66
    CGC_PLL_MUL_146_0  = BSP_CLOCKS_PLL_MUL(146U, 0U),  ///< PLL multiplier of 146.00
    CGC_PLL_MUL_146_33 = BSP_CLOCKS_PLL_MUL(146U, 33U), ///< PLL multiplier of 146.33
    CGC_PLL_MUL_146_5  = BSP_CLOCKS_PLL_MUL(146U, 50U), ///< PLL multiplier of 146.50
    CGC_PLL_MUL_146_66 = BSP_CLOCKS_PLL_MUL(146U, 66U), ///< PLL multiplier of 146.66
    CGC_PLL_MUL_147_0  = BSP_CLOCKS_PLL_MUL(147U, 0U),  ///< PLL multiplier of 147.00
    CGC_PLL_MUL_147_33 = BSP_CLOCKS_PLL_MUL(147U, 33U), ///< PLL multiplier of 147.33
    CGC_PLL_MUL_147_5  = BSP_CLOCKS_PLL_MUL(147U, 50U), ///< PLL multiplier of 147.50
    CGC_PLL_MUL_147_66 = BSP_CLOCKS_PLL_MUL(147U, 66U), ///< PLL multiplier of 147.66
    CGC_PLL_MUL_148_0  = BSP_CLOCKS_PLL_MUL(148U, 0U),  ///< PLL multiplier of 148.00
    CGC_PLL_MUL_148_33 = BSP_CLOCKS_PLL_MUL(148U, 33U), ///< PLL multiplier of 148.33
    CGC_PLL_MUL_148_5  = BSP_CLOCKS_PLL_MUL(148U, 50U), ///< PLL multiplier of 148.50
    CGC_PLL_MUL_148_66 = BSP_CLOCKS_PLL_MUL(148U, 66U), ///< PLL multiplier of 148.66
    CGC_PLL_MUL_149_0  = BSP_CLOCKS_PLL_MUL(149U, 0U),  ///< PLL multiplier of 149.00
    CGC_PLL_MUL_149_33 = BSP_CLOCKS_PLL_MUL(149U, 33U), ///< PLL multiplier of 149.33
    CGC_PLL_MUL_149_5  = BSP_CLOCKS_PLL_MUL(149U, 50U), ///< PLL multiplier of 149.50
    CGC_PLL_MUL_149_66 = BSP_CLOCKS_PLL_MUL(149U, 66U), ///< PLL multiplier of 149.66
    CGC_PLL_MUL_150_0  = BSP_CLOCKS_PLL_MUL(150U, 0U),  ///< PLL multiplier of 150.00
    CGC_PLL_MUL_150_33 = BSP_CLOCKS_PLL_MUL(150U, 33U), ///< PLL multiplier of 150.33
    CGC_PLL_MUL_150_5  = BSP_CLOCKS_PLL_MUL(150U, 50U), ///< PLL multiplier of 150.50
    CGC_PLL_MUL_150_66 = BSP_CLOCKS_PLL_MUL(150U, 66U), ///< PLL multiplier of 150.66
    CGC_PLL_MUL_151_0  = BSP_CLOCKS_PLL_MUL(151U, 0U),  ///< PLL multiplier of 151.00
    CGC_PLL_MUL_151_33 = BSP_CLOCKS_PLL_MUL(151U, 33U), ///< PLL multiplier of 151.33
    CGC_PLL_MUL_151_5  = BSP_CLOCKS_PLL_MUL(151U, 50U), ///< PLL multiplier of 151.50
    CGC_PLL_MUL_151_66 = BSP_CLOCKS_PLL_MUL(151U, 66U), ///< PLL multiplier of 151.66
    CGC_PLL_MUL_152_0  = BSP_CLOCKS_PLL_MUL(152U, 0U),  ///< PLL multiplier of 152.00
    CGC_PLL_MUL_152_33 = BSP_CLOCKS_PLL_MUL(152U, 33U), ///< PLL multiplier of 152.33
    CGC_PLL_MUL_152_5  = BSP_CLOCKS_PLL_MUL(152U, 50U), ///< PLL multiplier of 152.50
    CGC_PLL_MUL_152_66 = BSP_CLOCKS_PLL_MUL(152U, 66U), ///< PLL multiplier of 152.66
    CGC_PLL_MUL_153_0  = BSP_CLOCKS_PLL_MUL(153U, 0U),  ///< PLL multiplier of 153.00
    CGC_PLL_MUL_153_33 = BSP_CLOCKS_PLL_MUL(153U, 33U), ///< PLL multiplier of 153.33
    CGC_PLL_MUL_153_5  = BSP_CLOCKS_PLL_MUL(153U, 50U), ///< PLL multiplier of 153.50
    CGC_PLL_MUL_153_66 = BSP_CLOCKS_PLL_MUL(153U, 66U), ///< PLL multiplier of 153.66
    CGC_PLL_MUL_154_0  = BSP_CLOCKS_PLL_MUL(154U, 0U),  ///< PLL multiplier of 154.00
    CGC_PLL_MUL_154_33 = BSP_CLOCKS_PLL_MUL(154U, 33U), ///< PLL multiplier of 154.33
    CGC_PLL_MUL_154_5  = BSP_CLOCKS_PLL_MUL(154U, 50U), ///< PLL multiplier of 154.50
    CGC_PLL_MUL_154_66 = BSP_CLOCKS_PLL_MUL(154U, 66U), ///< PLL multiplier of 154.66
    CGC_PLL_MUL_155_0  = BSP_CLOCKS_PLL_MUL(155U, 0U),  ///< PLL multiplier of 155.00
    CGC_PLL_MUL_155_33 = BSP_CLOCKS_PLL_MUL(155U, 33U), ///< PLL multiplier of 155.33
    CGC_PLL_MUL_155_5  = BSP_CLOCKS_PLL_MUL(155U, 50U), ///< PLL multiplier of 155.50
    CGC_PLL_MUL_155_66 = BSP_CLOCKS_PLL_MUL(155U, 66U), ///< PLL multiplier of 155.66
    CGC_PLL_MUL_156_0  = BSP_CLOCKS_PLL_MUL(156U, 0U),  ///< PLL multiplier of 156.00
    CGC_PLL_MUL_156_33 = BSP_CLOCKS_PLL_MUL(156U, 33U), ///< PLL multiplier of 156.33
    CGC_PLL_MUL_156_5  = BSP_CLOCKS_PLL_MUL(156U, 50U), ///< PLL multiplier of 156.50
    CGC_PLL_MUL_156_66 = BSP_CLOCKS_PLL_MUL(156U, 66U), ///< PLL multiplier of 156.66
    CGC_PLL_MUL_157_0  = BSP_CLOCKS_PLL_MUL(157U, 0U),  ///< PLL multiplier of 157.00
    CGC_PLL_MUL_157_33 = BSP_CLOCKS_PLL_MUL(157U, 33U), ///< PLL multiplier of 157.33
    CGC_PLL_MUL_157_5  = BSP_CLOCKS_PLL_MUL(157U, 50U), ///< PLL multiplier of 157.50
    CGC_PLL_MUL_157_66 = BSP_CLOCKS_PLL_MUL(157U, 66U), ///< PLL multiplier of 157.66
    CGC_PLL_MUL_158_0  = BSP_CLOCKS_PLL_MUL(158U, 0U),  ///< PLL multiplier of 158.00
    CGC_PLL_MUL_158_33 = BSP_CLOCKS_PLL_MUL(158U, 33U), ///< PLL multiplier of 158.33
    CGC_PLL_MUL_158_5  = BSP_CLOCKS_PLL_MUL(158U, 50U), ///< PLL multiplier of 158.50
    CGC_PLL_MUL_158_66 = BSP_CLOCKS_PLL_MUL(158U, 66U), ///< PLL multiplier of 158.66
    CGC_PLL_MUL_159_0  = BSP_CLOCKS_PLL_MUL(159U, 0U),  ///< PLL multiplier of 159.00
    CGC_PLL_MUL_159_33 = BSP_CLOCKS_PLL_MUL(159U, 33U), ///< PLL multiplier of 159.33
    CGC_PLL_MUL_159_5  = BSP_CLOCKS_PLL_MUL(159U, 50U), ///< PLL multiplier of 159.50
    CGC_PLL_MUL_159_66 = BSP_CLOCKS_PLL_MUL(159U, 66U), ///< PLL multiplier of 159.66
    CGC_PLL_MUL_160_0  = BSP_CLOCKS_PLL_MUL(160U, 0U),  ///< PLL multiplier of 160.00
    CGC_PLL_MUL_160_33 = BSP_CLOCKS_PLL_MUL(160U, 33U), ///< PLL multiplier of 160.33
    CGC_PLL_MUL_160_5  = BSP_CLOCKS_PLL_MUL(160U, 50U), ///< PLL multiplier of 160.50
    CGC_PLL_MUL_160_66 = BSP_CLOCKS_PLL_MUL(160U, 66U), ///< PLL multiplier of 160.66
    CGC_PLL_MUL_161_0  = BSP_CLOCKS_PLL_MUL(161U, 0U),  ///< PLL multiplier of 161.00
    CGC_PLL_MUL_161_33 = BSP_CLOCKS_PLL_MUL(161U, 33U), ///< PLL multiplier of 161.33
    CGC_PLL_MUL_161_5  = BSP_CLOCKS_PLL_MUL(161U, 50U), ///< PLL multiplier of 161.50
    CGC_PLL_MUL_161_66 = BSP_CLOCKS_PLL_MUL(161U, 66U), ///< PLL multiplier of 161.66
    CGC_PLL_MUL_162_0  = BSP_CLOCKS_PLL_MUL(162U, 0U),  ///< PLL multiplier of 162.00
    CGC_PLL_MUL_162_33 = BSP_CLOCKS_PLL_MUL(162U, 33U), ///< PLL multiplier of 162.33
    CGC_PLL_MUL_162_5  = BSP_CLOCKS_PLL_MUL(162U, 50U), ///< PLL multiplier of 162.50
    CGC_PLL_MUL_162_66 = BSP_CLOCKS_PLL_MUL(162U, 66U), ///< PLL multiplier of 162.66
    CGC_PLL_MUL_163_0  = BSP_CLOCKS_PLL_MUL(163U, 0U),  ///< PLL multiplier of 163.00
    CGC_PLL_MUL_163_33 = BSP_CLOCKS_PLL_MUL(163U, 33U), ///< PLL multiplier of 163.33
    CGC_PLL_MUL_163_5  = BSP_CLOCKS_PLL_MUL(163U, 50U), ///< PLL multiplier of 163.50
    CGC_PLL_MUL_163_66 = BSP_CLOCKS_PLL_MUL(163U, 66U), ///< PLL multiplier of 163.66
    CGC_PLL_MUL_164_0  = BSP_CLOCKS_PLL_MUL(164U, 0U),  ///< PLL multiplier of 164.00
    CGC_PLL_MUL_164_33 = BSP_CLOCKS_PLL_MUL(164U, 33U), ///< PLL multiplier of 164.33
    CGC_PLL_MUL_164_5  = BSP_CLOCKS_PLL_MUL(164U, 50U), ///< PLL multiplier of 164.50
    CGC_PLL_MUL_164_66 = BSP_CLOCKS_PLL_MUL(164U, 66U), ///< PLL multiplier of 164.66
    CGC_PLL_MUL_165_0  = BSP_CLOCKS_PLL_MUL(165U, 0U),  ///< PLL multiplier of 165.00
    CGC_PLL_MUL_165_33 = BSP_CLOCKS_PLL_MUL(165U, 33U), ///< PLL multiplier of 165.33
    CGC_PLL_MUL_165_5  = BSP_CLOCKS_PLL_MUL(165U, 50U), ///< PLL multiplier of 165.50
    CGC_PLL_MUL_165_66 = BSP_CLOCKS_PLL_MUL(165U, 66U), ///< PLL multiplier of 165.66
    CGC_PLL_MUL_166_0  = BSP_CLOCKS_PLL_MUL(166U, 0U),  ///< PLL multiplier of 166.00
    CGC_PLL_MUL_166_33 = BSP_CLOCKS_PLL_MUL(166U, 33U), ///< PLL multiplier of 166.33
    CGC_PLL_MUL_166_5  = BSP_CLOCKS_PLL_MUL(166U, 50U), ///< PLL multiplier of 166.50
    CGC_PLL_MUL_166_66 = BSP_CLOCKS_PLL_MUL(166U, 66U), ///< PLL multiplier of 166.66
    CGC_PLL_MUL_167_0  = BSP_CLOCKS_PLL_MUL(167U, 0U),  ///< PLL multiplier of 167.00
    CGC_PLL_MUL_167_33 = BSP_CLOCKS_PLL_MUL(167U, 33U), ///< PLL multiplier of 167.33
    CGC_PLL_MUL_167_5  = BSP_CLOCKS_PLL_MUL(167U, 50U), ///< PLL multiplier of 167.50
    CGC_PLL_MUL_167_66 = BSP_CLOCKS_PLL_MUL(167U, 66U), ///< PLL multiplier of 167.66
    CGC_PLL_MUL_168_0  = BSP_CLOCKS_PLL_MUL(168U, 0U),  ///< PLL multiplier of 168.00
    CGC_PLL_MUL_168_33 = BSP_CLOCKS_PLL_MUL(168U, 33U), ///< PLL multiplier of 168.33
    CGC_PLL_MUL_168_5  = BSP_CLOCKS_PLL_MUL(168U, 50U), ///< PLL multiplier of 168.50
    CGC_PLL_MUL_168_66 = BSP_CLOCKS_PLL_MUL(168U, 66U), ///< PLL multiplier of 168.66
    CGC_PLL_MUL_169_0  = BSP_CLOCKS_PLL_MUL(169U, 0U),  ///< PLL multiplier of 169.00
    CGC_PLL_MUL_169_33 = BSP_CLOCKS_PLL_MUL(169U, 33U), ///< PLL multiplier of 169.33
    CGC_PLL_MUL_169_5  = BSP_CLOCKS_PLL_MUL(169U, 50U), ///< PLL multiplier of 169.50
    CGC_PLL_MUL_169_66 = BSP_CLOCKS_PLL_MUL(169U, 66U), ///< PLL multiplier of 169.66
    CGC_PLL_MUL_170_0  = BSP_CLOCKS_PLL_MUL(170U, 0U),  ///< PLL multiplier of 170.00
    CGC_PLL_MUL_170_33 = BSP_CLOCKS_PLL_MUL(170U, 33U), ///< PLL multiplier of 170.33
    CGC_PLL_MUL_170_5  = BSP_CLOCKS_PLL_MUL(170U, 50U), ///< PLL multiplier of 170.50
    CGC_PLL_MUL_170_66 = BSP_CLOCKS_PLL_MUL(170U, 66U), ///< PLL multiplier of 170.66
    CGC_PLL_MUL_171_0  = BSP_CLOCKS_PLL_MUL(171U, 0U),  ///< PLL multiplier of 171.00
    CGC_PLL_MUL_171_33 = BSP_CLOCKS_PLL_MUL(171U, 33U), ///< PLL multiplier of 171.33
    CGC_PLL_MUL_171_5  = BSP_CLOCKS_PLL_MUL(171U, 50U), ///< PLL multiplier of 171.50
    CGC_PLL_MUL_171_66 = BSP_CLOCKS_PLL_MUL(171U, 66U), ///< PLL multiplier of 171.66
    CGC_PLL_MUL_172_0  = BSP_CLOCKS_PLL_MUL(172U, 0U),  ///< PLL multiplier of 172.00
    CGC_PLL_MUL_172_33 = BSP_CLOCKS_PLL_MUL(172U, 33U), ///< PLL multiplier of 172.33
    CGC_PLL_MUL_172_5  = BSP_CLOCKS_PLL_MUL(172U, 50U), ///< PLL multiplier of 172.50
    CGC_PLL_MUL_172_66 = BSP_CLOCKS_PLL_MUL(172U, 66U), ///< PLL multiplier of 172.66
    CGC_PLL_MUL_173_0  = BSP_CLOCKS_PLL_MUL(173U, 0U),  ///< PLL multiplier of 173.00
    CGC_PLL_MUL_173_33 = BSP_CLOCKS_PLL_MUL(173U, 33U), ///< PLL multiplier of 173.33
    CGC_PLL_MUL_173_5  = BSP_CLOCKS_PLL_MUL(173U, 50U), ///< PLL multiplier of 173.50
    CGC_PLL_MUL_173_66 = BSP_CLOCKS_PLL_MUL(173U, 66U), ///< PLL multiplier of 173.66
    CGC_PLL_MUL_174_0  = BSP_CLOCKS_PLL_MUL(174U, 0U),  ///< PLL multiplier of 174.00
    CGC_PLL_MUL_174_33 = BSP_CLOCKS_PLL_MUL(174U, 33U), ///< PLL multiplier of 174.33
    CGC_PLL_MUL_174_5  = BSP_CLOCKS_PLL_MUL(174U, 50U), ///< PLL multiplier of 174.50
    CGC_PLL_MUL_174_66 = BSP_CLOCKS_PLL_MUL(174U, 66U), ///< PLL multiplier of 174.66
    CGC_PLL_MUL_175_0  = BSP_CLOCKS_PLL_MUL(175U, 0U),  ///< PLL multiplier of 175.00
    CGC_PLL_MUL_175_33 = BSP_CLOCKS_PLL_MUL(175U, 33U), ///< PLL multiplier of 175.33
    CGC_PLL_MUL_175_5  = BSP_CLOCKS_PLL_MUL(175U, 50U), ///< PLL multiplier of 175.50
    CGC_PLL_MUL_175_66 = BSP_CLOCKS_PLL_MUL(175U, 66U), ///< PLL multiplier of 175.66
    CGC_PLL_MUL_176_0  = BSP_CLOCKS_PLL_MUL(176U, 0U),  ///< PLL multiplier of 176.00
    CGC_PLL_MUL_176_33 = BSP_CLOCKS_PLL_MUL(176U, 33U), ///< PLL multiplier of 176.33
    CGC_PLL_MUL_176_5  = BSP_CLOCKS_PLL_MUL(176U, 50U), ///< PLL multiplier of 176.50
    CGC_PLL_MUL_176_66 = BSP_CLOCKS_PLL_MUL(176U, 66U), ///< PLL multiplier of 176.66
    CGC_PLL_MUL_177_0  = BSP_CLOCKS_PLL_MUL(177U, 0U),  ///< PLL multiplier of 177.00
    CGC_PLL_MUL_177_33 = BSP_CLOCKS_PLL_MUL(177U, 33U), ///< PLL multiplier of 177.33
    CGC_PLL_MUL_177_5  = BSP_CLOCKS_PLL_MUL(177U, 50U), ///< PLL multiplier of 177.50
    CGC_PLL_MUL_177_66 = BSP_CLOCKS_PLL_MUL(177U, 66U), ///< PLL multiplier of 177.66
    CGC_PLL_MUL_178_0  = BSP_CLOCKS_PLL_MUL(178U, 0U),  ///< PLL multiplier of 178.00
    CGC_PLL_MUL_178_33 = BSP_CLOCKS_PLL_MUL(178U, 33U), ///< PLL multiplier of 178.33
    CGC_PLL_MUL_178_5  = BSP_CLOCKS_PLL_MUL(178U, 50U), ///< PLL multiplier of 178.50
    CGC_PLL_MUL_178_66 = BSP_CLOCKS_PLL_MUL(178U, 66U), ///< PLL multiplier of 178.66
    CGC_PLL_MUL_179_0  = BSP_CLOCKS_PLL_MUL(179U, 0U),  ///< PLL multiplier of 179.00
    CGC_PLL_MUL_179_33 = BSP_CLOCKS_PLL_MUL(179U, 33U), ///< PLL multiplier of 179.33
    CGC_PLL_MUL_179_5  = BSP_CLOCKS_PLL_MUL(179U, 50U), ///< PLL multiplier of 179.50
    CGC_PLL_MUL_179_66 = BSP_CLOCKS_PLL_MUL(179U, 66U), ///< PLL multiplier of 179.66
    CGC_PLL_MUL_180_0  = BSP_CLOCKS_PLL_MUL(180U, 0U),  ///< PLL multiplier of 180.00
    CGC_PLL_MUL_180_33 = BSP_CLOCKS_PLL_MUL(180U, 33U), ///< PLL multiplier of 180.33
    CGC_PLL_MUL_180_5  = BSP_CLOCKS_PLL_MUL(180U, 50U), ///< PLL multiplier of 180.50
    CGC_PLL_MUL_180_66 = BSP_CLOCKS_PLL_MUL(180U, 66U), ///< PLL multiplier of 180.66
    CGC_PLL_MUL_181_0  = BSP_CLOCKS_PLL_MUL(181U, 0U),  ///< PLL multiplier of 181.00
    CGC_PLL_MUL_181_33 = BSP_CLOCKS_PLL_MUL(181U, 33U), ///< PLL multiplier of 181.33
    CGC_PLL_MUL_181_5  = BSP_CLOCKS_PLL_MUL(181U, 50U), ///< PLL multiplier of 181.50
    CGC_PLL_MUL_181_66 = BSP_CLOCKS_PLL_MUL(181U, 66U), ///< PLL multiplier of 181.66
    CGC_PLL_MUL_182_0  = BSP_CLOCKS_PLL_MUL(182U, 0U),  ///< PLL multiplier of 182.00
    CGC_PLL_MUL_182_33 = BSP_CLOCKS_PLL_MUL(182U, 33U), ///< PLL multiplier of 182.33
    CGC_PLL_MUL_182_5  = BSP_CLOCKS_PLL_MUL(182U, 50U), ///< PLL multiplier of 182.50
    CGC_PLL_MUL_182_66 = BSP_CLOCKS_PLL_MUL(182U, 66U), ///< PLL multiplier of 182.66
    CGC_PLL_MUL_183_0  = BSP_CLOCKS_PLL_MUL(183U, 0U),  ///< PLL multiplier of 183.00
    CGC_PLL_MUL_183_33 = BSP_CLOCKS_PLL_MUL(183U, 33U), ///< PLL multiplier of 183.33
    CGC_PLL_MUL_183_5  = BSP_CLOCKS_PLL_MUL(183U, 50U), ///< PLL multiplier of 183.50
    CGC_PLL_MUL_183_66 = BSP_CLOCKS_PLL_MUL(183U, 66U), ///< PLL multiplier of 183.66
    CGC_PLL_MUL_184_0  = BSP_CLOCKS_PLL_MUL(184U, 0U),  ///< PLL multiplier of 184.00
    CGC_PLL_MUL_184_33 = BSP_CLOCKS_PLL_MUL(184U, 33U), ///< PLL multiplier of 184.33
    CGC_PLL_MUL_184_5  = BSP_CLOCKS_PLL_MUL(184U, 50U), ///< PLL multiplier of 184.50
    CGC_PLL_MUL_184_66 = BSP_CLOCKS_PLL_MUL(184U, 66U), ///< PLL multiplier of 184.66
    CGC_PLL_MUL_185_0  = BSP_CLOCKS_PLL_MUL(185U, 0U),  ///< PLL multiplier of 185.00
    CGC_PLL_MUL_185_33 = BSP_CLOCKS_PLL_MUL(185U, 33U), ///< PLL multiplier of 185.33
    CGC_PLL_MUL_185_5  = BSP_CLOCKS_PLL_MUL(185U, 50U), ///< PLL multiplier of 185.50
    CGC_PLL_MUL_185_66 = BSP_CLOCKS_PLL_MUL(185U, 66U), ///< PLL multiplier of 185.66
    CGC_PLL_MUL_186_0  = BSP_CLOCKS_PLL_MUL(186U, 0U),  ///< PLL multiplier of 186.00
    CGC_PLL_MUL_186_33 = BSP_CLOCKS_PLL_MUL(186U, 33U), ///< PLL multiplier of 186.33
    CGC_PLL_MUL_186_5  = BSP_CLOCKS_PLL_MUL(186U, 50U), ///< PLL multiplier of 186.50
    CGC_PLL_MUL_186_66 = BSP_CLOCKS_PLL_MUL(186U, 66U), ///< PLL multiplier of 186.66
    CGC_PLL_MUL_187_0  = BSP_CLOCKS_PLL_MUL(187U, 0U),  ///< PLL multiplier of 187.00
    CGC_PLL_MUL_187_33 = BSP_CLOCKS_PLL_MUL(187U, 33U), ///< PLL multiplier of 187.33
    CGC_PLL_MUL_187_5  = BSP_CLOCKS_PLL_MUL(187U, 50U), ///< PLL multiplier of 187.50
    CGC_PLL_MUL_187_66 = BSP_CLOCKS_PLL_MUL(187U, 66U), ///< PLL multiplier of 187.66
    CGC_PLL_MUL_188_0  = BSP_CLOCKS_PLL_MUL(188U, 0U),  ///< PLL multiplier of 188.00
    CGC_PLL_MUL_188_33 = BSP_CLOCKS_PLL_MUL(188U, 33U), ///< PLL multiplier of 188.33
    CGC_PLL_MUL_188_5  = BSP_CLOCKS_PLL_MUL(188U, 50U), ///< PLL multiplier of 188.50
    CGC_PLL_MUL_188_66 = BSP_CLOCKS_PLL_MUL(188U, 66U), ///< PLL multiplier of 188.66
    CGC_PLL_MUL_189_0  = BSP_CLOCKS_PLL_MUL(189U, 0U),  ///< PLL multiplier of 189.00
    CGC_PLL_MUL_189_33 = BSP_CLOCKS_PLL_MUL(189U, 33U), ///< PLL multiplier of 189.33
    CGC_PLL_MUL_189_5  = BSP_CLOCKS_PLL_MUL(189U, 50U), ///< PLL multiplier of 189.50
    CGC_PLL_MUL_189_66 = BSP_CLOCKS_PLL_MUL(189U, 66U), ///< PLL multiplier of 189.66
    CGC_PLL_MUL_190_0  = BSP_CLOCKS_PLL_MUL(190U, 0U),  ///< PLL multiplier of 190.00
    CGC_PLL_MUL_190_33 = BSP_CLOCKS_PLL_MUL(190U, 33U), ///< PLL multiplier of 190.33
    CGC_PLL_MUL_190_5  = BSP_CLOCKS_PLL_MUL(190U, 50U), ///< PLL multiplier of 190.50
    CGC_PLL_MUL_190_66 = BSP_CLOCKS_PLL_MUL(190U, 66U), ///< PLL multiplier of 190.66
    CGC_PLL_MUL_191_0  = BSP_CLOCKS_PLL_MUL(191U, 0U),  ///< PLL multiplier of 191.00
    CGC_PLL_MUL_191_33 = BSP_CLOCKS_PLL_MUL(191U, 33U), ///< PLL multiplier of 191.33
    CGC_PLL_MUL_191_5  = BSP_CLOCKS_PLL_MUL(191U, 50U), ///< PLL multiplier of 191.50
    CGC_PLL_MUL_191_66 = BSP_CLOCKS_PLL_MUL(191U, 66U), ///< PLL multiplier of 191.66
    CGC_PLL_MUL_192_0  = BSP_CLOCKS_PLL_MUL(192U, 0U),  ///< PLL multiplier of 192.00
    CGC_PLL_MUL_192_33 = BSP_CLOCKS_PLL_MUL(192U, 33U), ///< PLL multiplier of 192.33
    CGC_PLL_MUL_192_5  = BSP_CLOCKS_PLL_MUL(192U, 50U), ///< PLL multiplier of 192.50
    CGC_PLL_MUL_192_66 = BSP_CLOCKS_PLL_MUL(192U, 66U), ///< PLL multiplier of 192.66
    CGC_PLL_MUL_193_0  = BSP_CLOCKS_PLL_MUL(193U, 0U),  ///< PLL multiplier of 193.00
    CGC_PLL_MUL_193_33 = BSP_CLOCKS_PLL_MUL(193U, 33U), ///< PLL multiplier of 193.33
    CGC_PLL_MUL_193_5  = BSP_CLOCKS_PLL_MUL(193U, 50U), ///< PLL multiplier of 193.50
    CGC_PLL_MUL_193_66 = BSP_CLOCKS_PLL_MUL(193U, 66U), ///< PLL multiplier of 193.66
    CGC_PLL_MUL_194_0  = BSP_CLOCKS_PLL_MUL(194U, 0U),  ///< PLL multiplier of 194.00
    CGC_PLL_MUL_194_33 = BSP_CLOCKS_PLL_MUL(194U, 33U), ///< PLL multiplier of 194.33
    CGC_PLL_MUL_194_5  = BSP_CLOCKS_PLL_MUL(194U, 50U), ///< PLL multiplier of 194.50
    CGC_PLL_MUL_194_66 = BSP_CLOCKS_PLL_MUL(194U, 66U), ///< PLL multiplier of 194.66
    CGC_PLL_MUL_195_0  = BSP_CLOCKS_PLL_MUL(195U, 0U),  ///< PLL multiplier of 195.00
    CGC_PLL_MUL_195_33 = BSP_CLOCKS_PLL_MUL(195U, 33U), ///< PLL multiplier of 195.33
    CGC_PLL_MUL_195_5  = BSP_CLOCKS_PLL_MUL(195U, 50U), ///< PLL multiplier of 195.50
    CGC_PLL_MUL_195_66 = BSP_CLOCKS_PLL_MUL(195U, 66U), ///< PLL multiplier of 195.66
    CGC_PLL_MUL_196_0  = BSP_CLOCKS_PLL_MUL(196U, 0U),  ///< PLL multiplier of 196.00
    CGC_PLL_MUL_196_33 = BSP_CLOCKS_PLL_MUL(196U, 33U), ///< PLL multiplier of 196.33
    CGC_PLL_MUL_196_5  = BSP_CLOCKS_PLL_MUL(196U, 50U), ///< PLL multiplier of 196.50
    CGC_PLL_MUL_196_66 = BSP_CLOCKS_PLL_MUL(196U, 66U), ///< PLL multiplier of 196.66
    CGC_PLL_MUL_197_0  = BSP_CLOCKS_PLL_MUL(197U, 0U),  ///< PLL multiplier of 197.00
    CGC_PLL_MUL_197_33 = BSP_CLOCKS_PLL_MUL(197U, 33U), ///< PLL multiplier of 197.33
    CGC_PLL_MUL_197_5  = BSP_CLOCKS_PLL_MUL(197U, 50U), ///< PLL multiplier of 197.50
    CGC_PLL_MUL_197_66 = BSP_CLOCKS_PLL_MUL(197U, 66U), ///< PLL multiplier of 197.66
    CGC_PLL_MUL_198_0  = BSP_CLOCKS_PLL_MUL(198U, 0U),  ///< PLL multiplier of 198.00
    CGC_PLL_MUL_198_33 = BSP_CLOCKS_PLL_MUL(198U, 33U), ///< PLL multiplier of 198.33
    CGC_PLL_MUL_198_5  = BSP_CLOCKS_PLL_MUL(198U, 50U), ///< PLL multiplier of 198.50
    CGC_PLL_MUL_198_66 = BSP_CLOCKS_PLL_MUL(198U, 66U), ///< PLL multiplier of 198.66
    CGC_PLL_MUL_199_0  = BSP_CLOCKS_PLL_MUL(199U, 0U),  ///< PLL multiplier of 199.00
    CGC_PLL_MUL_199_33 = BSP_CLOCKS_PLL_MUL(199U, 33U), ///< PLL multiplier of 199.33
    CGC_PLL_MUL_199_5  = BSP_CLOCKS_PLL_MUL(199U, 50U), ///< PLL multiplier of 199.50
    CGC_PLL_MUL_199_66 = BSP_CLOCKS_PLL_MUL(199U, 66U), ///< PLL multiplier of 199.66
    CGC_PLL_MUL_200_0  = BSP_CLOCKS_PLL_MUL(200U, 0U),  ///< PLL multiplier of 200.00
    CGC_PLL_MUL_200_33 = BSP_CLOCKS_PLL_MUL(200U, 33U), ///< PLL multiplier of 200.33
    CGC_PLL_MUL_200_5  = BSP_CLOCKS_PLL_MUL(200U, 50U), ///< PLL multiplier of 200.50
    CGC_PLL_MUL_200_66 = BSP_CLOCKS_PLL_MUL(200U, 66U), ///< PLL multiplier of 200.66
    CGC_PLL_MUL_201_0  = BSP_CLOCKS_PLL_MUL(201U, 0U),  ///< PLL multiplier of 201.00
    CGC_PLL_MUL_201_33 = BSP_CLOCKS_PLL_MUL(201U, 33U), ///< PLL multiplier of 201.33
    CGC_PLL_MUL_201_5  = BSP_CLOCKS_PLL_MUL(201U, 50U), ///< PLL multiplier of 201.50
    CGC_PLL_MUL_201_66 = BSP_CLOCKS_PLL_MUL(201U, 66U), ///< PLL multiplier of 201.66
    CGC_PLL_MUL_202_0  = BSP_CLOCKS_PLL_MUL(202U, 0U),  ///< PLL multiplier of 202.00
    CGC_PLL_MUL_202_33 = BSP_CLOCKS_PLL_MUL(202U, 33U), ///< PLL multiplier of 202.33
    CGC_PLL_MUL_202_5  = BSP_CLOCKS_PLL_MUL(202U, 50U), ///< PLL multiplier of 202.50
    CGC_PLL_MUL_202_66 = BSP_CLOCKS_PLL_MUL(202U, 66U), ///< PLL multiplier of 202.66
    CGC_PLL_MUL_203_0  = BSP_CLOCKS_PLL_MUL(203U, 0U),  ///< PLL multiplier of 203.00
    CGC_PLL_MUL_203_33 = BSP_CLOCKS_PLL_MUL(203U, 33U), ///< PLL multiplier of 203.33
    CGC_PLL_MUL_203_5  = BSP_CLOCKS_PLL_MUL(203U, 50U), ///< PLL multiplier of 203.50
    CGC_PLL_MUL_203_66 = BSP_CLOCKS_PLL_MUL(203U, 66U), ///< PLL multiplier of 203.66
    CGC_PLL_MUL_204_0  = BSP_CLOCKS_PLL_MUL(204U, 0U),  ///< PLL multiplier of 204.00
    CGC_PLL_MUL_204_33 = BSP_CLOCKS_PLL_MUL(204U, 33U), ///< PLL multiplier of 204.33
    CGC_PLL_MUL_204_5  = BSP_CLOCKS_PLL_MUL(204U, 50U), ///< PLL multiplier of 204.50
    CGC_PLL_MUL_204_66 = BSP_CLOCKS_PLL_MUL(204U, 66U), ///< PLL multiplier of 204.66
    CGC_PLL_MUL_205_0  = BSP_CLOCKS_PLL_MUL(205U, 0U),  ///< PLL multiplier of 205.00
    CGC_PLL_MUL_205_33 = BSP_CLOCKS_PLL_MUL(205U, 33U), ///< PLL multiplier of 205.33
    CGC_PLL_MUL_205_5  = BSP_CLOCKS_PLL_MUL(205U, 50U), ///< PLL multiplier of 205.50
    CGC_PLL_MUL_205_66 = BSP_CLOCKS_PLL_MUL(205U, 66U), ///< PLL multiplier of 205.66
    CGC_PLL_MUL_206_0  = BSP_CLOCKS_PLL_MUL(206U, 0U),  ///< PLL multiplier of 206.00
    CGC_PLL_MUL_206_33 = BSP_CLOCKS_PLL_MUL(206U, 33U), ///< PLL multiplier of 206.33
    CGC_PLL_MUL_206_5  = BSP_CLOCKS_PLL_MUL(206U, 50U), ///< PLL multiplier of 206.50
    CGC_PLL_MUL_206_66 = BSP_CLOCKS_PLL_MUL(206U, 66U), ///< PLL multiplier of 206.66
    CGC_PLL_MUL_207_0  = BSP_CLOCKS_PLL_MUL(207U, 0U),  ///< PLL multiplier of 207.00
    CGC_PLL_MUL_207_33 = BSP_CLOCKS_PLL_MUL(207U, 33U), ///< PLL multiplier of 207.33
    CGC_PLL_MUL_207_5  = BSP_CLOCKS_PLL_MUL(207U, 50U), ///< PLL multiplier of 207.50
    CGC_PLL_MUL_207_66 = BSP_CLOCKS_PLL_MUL(207U, 66U), ///< PLL multiplier of 207.66
    CGC_PLL_MUL_208_0  = BSP_CLOCKS_PLL_MUL(208U, 0U),  ///< PLL multiplier of 208.00
    CGC_PLL_MUL_208_33 = BSP_CLOCKS_PLL_MUL(208U, 33U), ///< PLL multiplier of 208.33
    CGC_PLL_MUL_208_5  = BSP_CLOCKS_PLL_MUL(208U, 50U), ///< PLL multiplier of 208.50
    CGC_PLL_MUL_208_66 = BSP_CLOCKS_PLL_MUL(208U, 66U), ///< PLL multiplier of 208.66
    CGC_PLL_MUL_209_0  = BSP_CLOCKS_PLL_MUL(209U, 0U),  ///< PLL multiplier of 209.00
    CGC_PLL_MUL_209_33 = BSP_CLOCKS_PLL_MUL(209U, 33U), ///< PLL multiplier of 209.33
    CGC_PLL_MUL_209_5  = BSP_CLOCKS_PLL_MUL(209U, 50U), ///< PLL multiplier of 209.50
    CGC_PLL_MUL_209_66 = BSP_CLOCKS_PLL_MUL(209U, 66U), ///< PLL multiplier of 209.66
    CGC_PLL_MUL_210_0  = BSP_CLOCKS_PLL_MUL(210U, 0U),  ///< PLL multiplier of 210.00
    CGC_PLL_MUL_210_33 = BSP_CLOCKS_PLL_MUL(210U, 33U), ///< PLL multiplier of 210.33
    CGC_PLL_MUL_210_5  = BSP_CLOCKS_PLL_MUL(210U, 50U), ///< PLL multiplier of 210.50
    CGC_PLL_MUL_210_66 = BSP_CLOCKS_PLL_MUL(210U, 66U), ///< PLL multiplier of 210.66
    CGC_PLL_MUL_211_0  = BSP_CLOCKS_PLL_MUL(211U, 0U),  ///< PLL multiplier of 211.00
    CGC_PLL_MUL_211_33 = BSP_CLOCKS_PLL_MUL(211U, 33U), ///< PLL multiplier of 211.33
    CGC_PLL_MUL_211_5  = BSP_CLOCKS_PLL_MUL(211U, 50U), ///< PLL multiplier of 211.50
    CGC_PLL_MUL_211_66 = BSP_CLOCKS_PLL_MUL(211U, 66U), ///< PLL multiplier of 211.66
    CGC_PLL_MUL_212_0  = BSP_CLOCKS_PLL_MUL(212U, 0U),  ///< PLL multiplier of 212.00
    CGC_PLL_MUL_212_33 = BSP_CLOCKS_PLL_MUL(212U, 33U), ///< PLL multiplier of 212.33
    CGC_PLL_MUL_212_5  = BSP_CLOCKS_PLL_MUL(212U, 50U), ///< PLL multiplier of 212.50
    CGC_PLL_MUL_212_66 = BSP_CLOCKS_PLL_MUL(212U, 66U), ///< PLL multiplier of 212.66
    CGC_PLL_MUL_213_0  = BSP_CLOCKS_PLL_MUL(213U, 0U),  ///< PLL multiplier of 213.00
    CGC_PLL_MUL_213_33 = BSP_CLOCKS_PLL_MUL(213U, 33U), ///< PLL multiplier of 213.33
    CGC_PLL_MUL_213_5  = BSP_CLOCKS_PLL_MUL(213U, 50U), ///< PLL multiplier of 213.50
    CGC_PLL_MUL_213_66 = BSP_CLOCKS_PLL_MUL(213U, 66U), ///< PLL multiplier of 213.66
    CGC_PLL_MUL_214_0  = BSP_CLOCKS_PLL_MUL(214U, 0U),  ///< PLL multiplier of 214.00
    CGC_PLL_MUL_214_33 = BSP_CLOCKS_PLL_MUL(214U, 33U), ///< PLL multiplier of 214.33
    CGC_PLL_MUL_214_5  = BSP_CLOCKS_PLL_MUL(214U, 50U), ///< PLL multiplier of 214.50
    CGC_PLL_MUL_214_66 = BSP_CLOCKS_PLL_MUL(214U, 66U), ///< PLL multiplier of 214.66
    CGC_PLL_MUL_215_0  = BSP_CLOCKS_PLL_MUL(215U, 0U),  ///< PLL multiplier of 215.00
    CGC_PLL_MUL_215_33 = BSP_CLOCKS_PLL_MUL(215U, 33U), ///< PLL multiplier of 215.33
    CGC_PLL_MUL_215_5  = BSP_CLOCKS_PLL_MUL(215U, 50U), ///< PLL multiplier of 215.50
    CGC_PLL_MUL_215_66 = BSP_CLOCKS_PLL_MUL(215U, 66U), ///< PLL multiplier of 215.66
    CGC_PLL_MUL_216_0  = BSP_CLOCKS_PLL_MUL(216U, 0U),  ///< PLL multiplier of 216.00
    CGC_PLL_MUL_216_33 = BSP_CLOCKS_PLL_MUL(216U, 33U), ///< PLL multiplier of 216.33
    CGC_PLL_MUL_216_5  = BSP_CLOCKS_PLL_MUL(216U, 50U), ///< PLL multiplier of 216.50
    CGC_PLL_MUL_216_66 = BSP_CLOCKS_PLL_MUL(216U, 66U), ///< PLL multiplier of 216.66
    CGC_PLL_MUL_217_0  = BSP_CLOCKS_PLL_MUL(217U, 0U),  ///< PLL multiplier of 217.00
    CGC_PLL_MUL_217_33 = BSP_CLOCKS_PLL_MUL(217U, 33U), ///< PLL multiplier of 217.33
    CGC_PLL_MUL_217_5  = BSP_CLOCKS_PLL_MUL(217U, 50U), ///< PLL multiplier of 217.50
    CGC_PLL_MUL_217_66 = BSP_CLOCKS_PLL_MUL(217U, 66U), ///< PLL multiplier of 217.66
    CGC_PLL_MUL_218_0  = BSP_CLOCKS_PLL_MUL(218U, 0U),  ///< PLL multiplier of 218.00
    CGC_PLL_MUL_218_33 = BSP_CLOCKS_PLL_MUL(218U, 33U), ///< PLL multiplier of 218.33
    CGC_PLL_MUL_218_5  = BSP_CLOCKS_PLL_MUL(218U, 50U), ///< PLL multiplier of 218.50
    CGC_PLL_MUL_218_66 = BSP_CLOCKS_PLL_MUL(218U, 66U), ///< PLL multiplier of 218.66
    CGC_PLL_MUL_219_0  = BSP_CLOCKS_PLL_MUL(219U, 0U),  ///< PLL multiplier of 219.00
    CGC_PLL_MUL_219_33 = BSP_CLOCKS_PLL_MUL(219U, 33U), ///< PLL multiplier of 219.33
    CGC_PLL_MUL_219_5  = BSP_CLOCKS_PLL_MUL(219U, 50U), ///< PLL multiplier of 219.50
    CGC_PLL_MUL_219_66 = BSP_CLOCKS_PLL_MUL(219U, 66U), ///< PLL multiplier of 219.66
    CGC_PLL_MUL_220_0  = BSP_CLOCKS_PLL_MUL(220U, 0U),  ///< PLL multiplier of 220.00
    CGC_PLL_MUL_220_33 = BSP_CLOCKS_PLL_MUL(220U, 33U), ///< PLL multiplier of 220.33
    CGC_PLL_MUL_220_5  = BSP_CLOCKS_PLL_MUL(220U, 50U), ///< PLL multiplier of 220.50
    CGC_PLL_MUL_220_66 = BSP_CLOCKS_PLL_MUL(220U, 66U), ///< PLL multiplier of 220.66
    CGC_PLL_MUL_221_0  = BSP_CLOCKS_PLL_MUL(221U, 0U),  ///< PLL multiplier of 221.00
    CGC_PLL_MUL_221_33 = BSP_CLOCKS_PLL_MUL(221U, 33U), ///< PLL multiplier of 221.33
    CGC_PLL_MUL_221_5  = BSP_CLOCKS_PLL_MUL(221U, 50U), ///< PLL multiplier of 221.50
    CGC_PLL_MUL_221_66 = BSP_CLOCKS_PLL_MUL(221U, 66U), ///< PLL multiplier of 221.66
    CGC_PLL_MUL_222_0  = BSP_CLOCKS_PLL_MUL(222U, 0U),  ///< PLL multiplier of 222.00
    CGC_PLL_MUL_222_33 = BSP_CLOCKS_PLL_MUL(222U, 33U), ///< PLL multiplier of 222.33
    CGC_PLL_MUL_222_5  = BSP_CLOCKS_PLL_MUL(222U, 50U), ///< PLL multiplier of 222.50
    CGC_PLL_MUL_222_66 = BSP_CLOCKS_PLL_MUL(222U, 66U), ///< PLL multiplier of 222.66
    CGC_PLL_MUL_223_0  = BSP_CLOCKS_PLL_MUL(223U, 0U),  ///< PLL multiplier of 223.00
    CGC_PLL_MUL_223_33 = BSP_CLOCKS_PLL_MUL(223U, 33U), ///< PLL multiplier of 223.33
    CGC_PLL_MUL_223_5  = BSP_CLOCKS_PLL_MUL(223U, 50U), ///< PLL multiplier of 223.50
    CGC_PLL_MUL_223_66 = BSP_CLOCKS_PLL_MUL(223U, 66U), ///< PLL multiplier of 223.66
    CGC_PLL_MUL_224_0  = BSP_CLOCKS_PLL_MUL(224U, 0U),  ///< PLL multiplier of 224.00
    CGC_PLL_MUL_224_33 = BSP_CLOCKS_PLL_MUL(224U, 33U), ///< PLL multiplier of 224.33
    CGC_PLL_MUL_224_5  = BSP_CLOCKS_PLL_MUL(224U, 50U), ///< PLL multiplier of 224.50
    CGC_PLL_MUL_224_66 = BSP_CLOCKS_PLL_MUL(224U, 66U), ///< PLL multiplier of 224.66
    CGC_PLL_MUL_225_0  = BSP_CLOCKS_PLL_MUL(225U, 0U),  ///< PLL multiplier of 225.00
    CGC_PLL_MUL_225_33 = BSP_CLOCKS_PLL_MUL(225U, 33U), ///< PLL multiplier of 225.33
    CGC_PLL_MUL_225_5  = BSP_CLOCKS_PLL_MUL(225U, 50U), ///< PLL multiplier of 225.50
    CGC_PLL_MUL_225_66 = BSP_CLOCKS_PLL_MUL(225U, 66U), ///< PLL multiplier of 225.66
    CGC_PLL_MUL_226_0  = BSP_CLOCKS_PLL_MUL(226U, 0U),  ///< PLL multiplier of 226.00
    CGC_PLL_MUL_226_33 = BSP_CLOCKS_PLL_MUL(226U, 33U), ///< PLL multiplier of 226.33
    CGC_PLL_MUL_226_5  = BSP_CLOCKS_PLL_MUL(226U, 50U), ///< PLL multiplier of 226.50
    CGC_PLL_MUL_226_66 = BSP_CLOCKS_PLL_MUL(226U, 66U), ///< PLL multiplier of 226.66
    CGC_PLL_MUL_227_0  = BSP_CLOCKS_PLL_MUL(227U, 0U),  ///< PLL multiplier of 227.00
    CGC_PLL_MUL_227_33 = BSP_CLOCKS_PLL_MUL(227U, 33U), ///< PLL multiplier of 227.33
    CGC_PLL_MUL_227_5  = BSP_CLOCKS_PLL_MUL(227U, 50U), ///< PLL multiplier of 227.50
    CGC_PLL_MUL_227_66 = BSP_CLOCKS_PLL_MUL(227U, 66U), ///< PLL multiplier of 227.66
    CGC_PLL_MUL_228_0  = BSP_CLOCKS_PLL_MUL(228U, 0U),  ///< PLL multiplier of 228.00
    CGC_PLL_MUL_228_33 = BSP_CLOCKS_PLL_MUL(228U, 33U), ///< PLL multiplier of 228.33
    CGC_PLL_MUL_228_5  = BSP_CLOCKS_PLL_MUL(228U, 50U), ///< PLL multiplier of 228.50
    CGC_PLL_MUL_228_66 = BSP_CLOCKS_PLL_MUL(228U, 66U), ///< PLL multiplier of 228.66
    CGC_PLL_MUL_229_0  = BSP_CLOCKS_PLL_MUL(229U, 0U),  ///< PLL multiplier of 229.00
    CGC_PLL_MUL_229_33 = BSP_CLOCKS_PLL_MUL(229U, 33U), ///< PLL multiplier of 229.33
    CGC_PLL_MUL_229_5  = BSP_CLOCKS_PLL_MUL(229U, 50U), ///< PLL multiplier of 229.50
    CGC_PLL_MUL_229_66 = BSP_CLOCKS_PLL_MUL(229U, 66U), ///< PLL multiplier of 229.66
    CGC_PLL_MUL_230_0  = BSP_CLOCKS_PLL_MUL(230U, 0U),  ///< PLL multiplier of 230.00
    CGC_PLL_MUL_230_33 = BSP_CLOCKS_PLL_MUL(230U, 33U), ///< PLL multiplier of 230.33
    CGC_PLL_MUL_230_5  = BSP_CLOCKS_PLL_MUL(230U, 50U), ///< PLL multiplier of 230.50
    CGC_PLL_MUL_230_66 = BSP_CLOCKS_PLL_MUL(230U, 66U), ///< PLL multiplier of 230.66
    CGC_PLL_MUL_231_0  = BSP_CLOCKS_PLL_MUL(231U, 0U),  ///< PLL multiplier of 231.00
    CGC_PLL_MUL_231_33 = BSP_CLOCKS_PLL_MUL(231U, 33U), ///< PLL multiplier of 231.33
    CGC_PLL_MUL_231_5  = BSP_CLOCKS_PLL_MUL(231U, 50U), ///< PLL multiplier of 231.50
    CGC_PLL_MUL_231_66 = BSP_CLOCKS_PLL_MUL(231U, 66U), ///< PLL multiplier of 231.66
    CGC_PLL_MUL_232_0  = BSP_CLOCKS_PLL_MUL(232U, 0U),  ///< PLL multiplier of 232.00
    CGC_PLL_MUL_232_33 = BSP_CLOCKS_PLL_MUL(232U, 33U), ///< PLL multiplier of 232.33
    CGC_PLL_MUL_232_5  = BSP_CLOCKS_PLL_MUL(232U, 50U), ///< PLL multiplier of 232.50
    CGC_PLL_MUL_232_66 = BSP_CLOCKS_PLL_MUL(232U, 66U), ///< PLL multiplier of 232.66
    CGC_PLL_MUL_233_0  = BSP_CLOCKS_PLL_MUL(233U, 0U),  ///< PLL multiplier of 233.00
    CGC_PLL_MUL_233_33 = BSP_CLOCKS_PLL_MUL(233U, 33U), ///< PLL multiplier of 233.33
    CGC_PLL_MUL_233_5  = BSP_CLOCKS_PLL_MUL(233U, 50U), ///< PLL multiplier of 233.50
    CGC_PLL_MUL_233_66 = BSP_CLOCKS_PLL_MUL(233U, 66U), ///< PLL multiplier of 233.66
    CGC_PLL_MUL_234_0  = BSP_CLOCKS_PLL_MUL(234U, 0U),  ///< PLL multiplier of 234.00
    CGC_PLL_MUL_234_33 = BSP_CLOCKS_PLL_MUL(234U, 33U), ///< PLL multiplier of 234.33
    CGC_PLL_MUL_234_5  = BSP_CLOCKS_PLL_MUL(234U, 50U), ///< PLL multiplier of 234.50
    CGC_PLL_MUL_234_66 = BSP_CLOCKS_PLL_MUL(234U, 66U), ///< PLL multiplier of 234.66
    CGC_PLL_MUL_235_0  = BSP_CLOCKS_PLL_MUL(235U, 0U),  ///< PLL multiplier of 235.00
    CGC_PLL_MUL_235_33 = BSP_CLOCKS_PLL_MUL(235U, 33U), ///< PLL multiplier of 235.33
    CGC_PLL_MUL_235_5  = BSP_CLOCKS_PLL_MUL(235U, 50U), ///< PLL multiplier of 235.50
    CGC_PLL_MUL_235_66 = BSP_CLOCKS_PLL_MUL(235U, 66U), ///< PLL multiplier of 235.66
    CGC_PLL_MUL_236_0  = BSP_CLOCKS_PLL_MUL(236U, 0U),  ///< PLL multiplier of 236.00
    CGC_PLL_MUL_236_33 = BSP_CLOCKS_PLL_MUL(236U, 33U), ///< PLL multiplier of 236.33
    CGC_PLL_MUL_236_5  = BSP_CLOCKS_PLL_MUL(236U, 50U), ///< PLL multiplier of 236.50
    CGC_PLL_MUL_236_66 = BSP_CLOCKS_PLL_MUL(236U, 66U), ///< PLL multiplier of 236.66
    CGC_PLL_MUL_237_0  = BSP_CLOCKS_PLL_MUL(237U, 0U),  ///< PLL multiplier of 237.00
    CGC_PLL_MUL_237_33 = BSP_CLOCKS_PLL_MUL(237U, 33U), ///< PLL multiplier of 237.33
    CGC_PLL_MUL_237_5  = BSP_CLOCKS_PLL_MUL(237U, 50U), ///< PLL multiplier of 237.50
    CGC_PLL_MUL_237_66 = BSP_CLOCKS_PLL_MUL(237U, 66U), ///< PLL multiplier of 237.66
    CGC_PLL_MUL_238_0  = BSP_CLOCKS_PLL_MUL(238U, 0U),  ///< PLL multiplier of 238.00
    CGC_PLL_MUL_238_33 = BSP_CLOCKS_PLL_MUL(238U, 33U), ///< PLL multiplier of 238.33
    CGC_PLL_MUL_238_5  = BSP_CLOCKS_PLL_MUL(238U, 50U), ///< PLL multiplier of 238.50
    CGC_PLL_MUL_238_66 = BSP_CLOCKS_PLL_MUL(238U, 66U), ///< PLL multiplier of 238.66
    CGC_PLL_MUL_239_0  = BSP_CLOCKS_PLL_MUL(239U, 0U),  ///< PLL multiplier of 239.00
    CGC_PLL_MUL_239_33 = BSP_CLOCKS_PLL_MUL(239U, 33U), ///< PLL multiplier of 239.33
    CGC_PLL_MUL_239_5  = BSP_CLOCKS_PLL_MUL(239U, 50U), ///< PLL multiplier of 239.50
    CGC_PLL_MUL_239_66 = BSP_CLOCKS_PLL_MUL(239U, 66U), ///< PLL multiplier of 239.66
    CGC_PLL_MUL_240_0  = BSP_CLOCKS_PLL_MUL(240U, 0U),  ///< PLL multiplier of 240.00
    CGC_PLL_MUL_240_33 = BSP_CLOCKS_PLL_MUL(240U, 33U), ///< PLL multiplier of 240.33
    CGC_PLL_MUL_240_5  = BSP_CLOCKS_PLL_MUL(240U, 50U), ///< PLL multiplier of 240.50
    CGC_PLL_MUL_240_66 = BSP_CLOCKS_PLL_MUL(240U, 66U), ///< PLL multiplier of 240.66
    CGC_PLL_MUL_241_0  = BSP_CLOCKS_PLL_MUL(241U, 0U),  ///< PLL multiplier of 241.00
    CGC_PLL_MUL_241_33 = BSP_CLOCKS_PLL_MUL(241U, 33U), ///< PLL multiplier of 241.33
    CGC_PLL_MUL_241_5  = BSP_CLOCKS_PLL_MUL(241U, 50U), ///< PLL multiplier of 241.50
    CGC_PLL_MUL_241_66 = BSP_CLOCKS_PLL_MUL(241U, 66U), ///< PLL multiplier of 241.66
    CGC_PLL_MUL_242_0  = BSP_CLOCKS_PLL_MUL(242U, 0U),  ///< PLL multiplier of 242.00
    CGC_PLL_MUL_242_33 = BSP_CLOCKS_PLL_MUL(242U, 33U), ///< PLL multiplier of 242.33
    CGC_PLL_MUL_242_5  = BSP_CLOCKS_PLL_MUL(242U, 50U), ///< PLL multiplier of 242.50
    CGC_PLL_MUL_242_66 = BSP_CLOCKS_PLL_MUL(242U, 66U), ///< PLL multiplier of 242.66
    CGC_PLL_MUL_243_0  = BSP_CLOCKS_PLL_MUL(243U, 0U),  ///< PLL multiplier of 243.00
    CGC_PLL_MUL_243_33 = BSP_CLOCKS_PLL_MUL(243U, 33U), ///< PLL multiplier of 243.33
    CGC_PLL_MUL_243_5  = BSP_CLOCKS_PLL_MUL(243U, 50U), ///< PLL multiplier of 243.50
    CGC_PLL_MUL_243_66 = BSP_CLOCKS_PLL_MUL(243U, 66U), ///< PLL multiplier of 243.66
    CGC_PLL_MUL_244_0  = BSP_CLOCKS_PLL_MUL(244U, 0U),  ///< PLL multiplier of 244.00
    CGC_PLL_MUL_244_33 = BSP_CLOCKS_PLL_MUL(244U, 33U), ///< PLL multiplier of 244.33
    CGC_PLL_MUL_244_5  = BSP_CLOCKS_PLL_MUL(244U, 50U), ///< PLL multiplier of 244.50
    CGC_PLL_MUL_244_66 = BSP_CLOCKS_PLL_MUL(244U, 66U), ///< PLL multiplier of 244.66
    CGC_PLL_MUL_245_0  = BSP_CLOCKS_PLL_MUL(245U, 0U),  ///< PLL multiplier of 245.00
    CGC_PLL_MUL_245_33 = BSP_CLOCKS_PLL_MUL(245U, 33U), ///< PLL multiplier of 245.33
    CGC_PLL_MUL_245_5  = BSP_CLOCKS_PLL_MUL(245U, 50U), ///< PLL multiplier of 245.50
    CGC_PLL_MUL_245_66 = BSP_CLOCKS_PLL_MUL(245U, 66U), ///< PLL multiplier of 245.66
    CGC_PLL_MUL_246_0  = BSP_CLOCKS_PLL_MUL(246U, 0U),  ///< PLL multiplier of 246.00
    CGC_PLL_MUL_246_33 = BSP_CLOCKS_PLL_MUL(246U, 33U), ///< PLL multiplier of 246.33
    CGC_PLL_MUL_246_5  = BSP_CLOCKS_PLL_MUL(246U, 50U), ///< PLL multiplier of 246.50
    CGC_PLL_MUL_246_66 = BSP_CLOCKS_PLL_MUL(246U, 66U), ///< PLL multiplier of 246.66
    CGC_PLL_MUL_247_0  = BSP_CLOCKS_PLL_MUL(247U, 0U),  ///< PLL multiplier of 247.00
    CGC_PLL_MUL_247_33 = BSP_CLOCKS_PLL_MUL(247U, 33U), ///< PLL multiplier of 247.33
    CGC_PLL_MUL_247_5  = BSP_CLOCKS_PLL_MUL(247U, 50U), ///< PLL multiplier of 247.50
    CGC_PLL_MUL_247_66 = BSP_CLOCKS_PLL_MUL(247U, 66U), ///< PLL multiplier of 247.66
    CGC_PLL_MUL_248_0  = BSP_CLOCKS_PLL_MUL(248U, 0U),  ///< PLL multiplier of 248.00
    CGC_PLL_MUL_248_33 = BSP_CLOCKS_PLL_MUL(248U, 33U), ///< PLL multiplier of 248.33
    CGC_PLL_MUL_248_5  = BSP_CLOCKS_PLL_MUL(248U, 50U), ///< PLL multiplier of 248.50
    CGC_PLL_MUL_248_66 = BSP_CLOCKS_PLL_MUL(248U, 66U), ///< PLL multiplier of 248.66
    CGC_PLL_MUL_249_0  = BSP_CLOCKS_PLL_MUL(249U, 0U),  ///< PLL multiplier of 249.00
    CGC_PLL_MUL_249_33 = BSP_CLOCKS_PLL_MUL(249U, 33U), ///< PLL multiplier of 249.33
    CGC_PLL_MUL_249_5  = BSP_CLOCKS_PLL_MUL(249U, 50U), ///< PLL multiplier of 249.50
    CGC_PLL_MUL_249_66 = BSP_CLOCKS_PLL_MUL(249U, 66U), ///< PLL multiplier of 249.66
    CGC_PLL_MUL_250_0  = BSP_CLOCKS_PLL_MUL(250U, 0U),  ///< PLL multiplier of 250.00
    CGC_PLL_MUL_250_33 = BSP_CLOCKS_PLL_MUL(250U, 33U), ///< PLL multiplier of 250.33
    CGC_PLL_MUL_250_5  = BSP_CLOCKS_PLL_MUL(250U, 50U), ///< PLL multiplier of 250.50
    CGC_PLL_MUL_250_66 = BSP_CLOCKS_PLL_MUL(250U, 66U), ///< PLL multiplier of 250.66
    CGC_PLL_MUL_251_0  = BSP_CLOCKS_PLL_MUL(251U, 0U),  ///< PLL multiplier of 251.00
    CGC_PLL_MUL_251_33 = BSP_CLOCKS_PLL_MUL(251U, 33U), ///< PLL multiplier of 251.33
    CGC_PLL_MUL_251_5  = BSP_CLOCKS_PLL_MUL(251U, 50U), ///< PLL multiplier of 251.50
    CGC_PLL_MUL_251_66 = BSP_CLOCKS_PLL_MUL(251U, 66U), ///< PLL multiplier of 251.66
    CGC_PLL_MUL_252_0  = BSP_CLOCKS_PLL_MUL(252U, 0U),  ///< PLL multiplier of 252.00
    CGC_PLL_MUL_252_33 = BSP_CLOCKS_PLL_MUL(252U, 33U), ///< PLL multiplier of 252.33
    CGC_PLL_MUL_252_5  = BSP_CLOCKS_PLL_MUL(252U, 50U), ///< PLL multiplier of 252.50
    CGC_PLL_MUL_252_66 = BSP_CLOCKS_PLL_MUL(252U, 66U), ///< PLL multiplier of 252.66
    CGC_PLL_MUL_253_0  = BSP_CLOCKS_PLL_MUL(253U, 0U),  ///< PLL multiplier of 253.00
    CGC_PLL_MUL_253_33 = BSP_CLOCKS_PLL_MUL(253U, 33U), ///< PLL multiplier of 253.33
    CGC_PLL_MUL_253_5  = BSP_CLOCKS_PLL_MUL(253U, 50U), ///< PLL multiplier of 253.50
    CGC_PLL_MUL_253_66 = BSP_CLOCKS_PLL_MUL(253U, 66U), ///< PLL multiplier of 253.66
    CGC_PLL_MUL_254_0  = BSP_CLOCKS_PLL_MUL(254U, 0U),  ///< PLL multiplier of 254.00
    CGC_PLL_MUL_254_33 = BSP_CLOCKS_PLL_MUL(254U, 33U), ///< PLL multiplier of 254.33
    CGC_PLL_MUL_254_5  = BSP_CLOCKS_PLL_MUL(254U, 50U), ///< PLL multiplier of 254.50
    CGC_PLL_MUL_254_66 = BSP_CLOCKS_PLL_MUL(254U, 66U), ///< PLL multiplier of 254.66
    CGC_PLL_MUL_255_0  = BSP_CLOCKS_PLL_MUL(255U, 0U),  ///< PLL multiplier of 255.00
    CGC_PLL_MUL_255_33 = BSP_CLOCKS_PLL_MUL(255U, 33U), ///< PLL multiplier of 255.33
    CGC_PLL_MUL_255_5  = BSP_CLOCKS_PLL_MUL(255U, 50U), ///< PLL multiplier of 255.50
    CGC_PLL_MUL_255_66 = BSP_CLOCKS_PLL_MUL(255U, 66U), ///< PLL multiplier of 255.66
    CGC_PLL_MUL_256_0  = BSP_CLOCKS_PLL_MUL(256U, 0U),  ///< PLL multiplier of 256.00
    CGC_PLL_MUL_256_33 = BSP_CLOCKS_PLL_MUL(256U, 33U), ///< PLL multiplier of 256.33
    CGC_PLL_MUL_256_5  = BSP_CLOCKS_PLL_MUL(256U, 50U), ///< PLL multiplier of 256.50
    CGC_PLL_MUL_256_66 = BSP_CLOCKS_PLL_MUL(256U, 66U), ///< PLL multiplier of 256.66
    CGC_PLL_MUL_257_0  = BSP_CLOCKS_PLL_MUL(257U, 0U),  ///< PLL multiplier of 257.00
    CGC_PLL_MUL_257_33 = BSP_CLOCKS_PLL_MUL(257U, 33U), ///< PLL multiplier of 257.33
    CGC_PLL_MUL_257_5  = BSP_CLOCKS_PLL_MUL(257U, 50U), ///< PLL multiplier of 257.50
    CGC_PLL_MUL_257_66 = BSP_CLOCKS_PLL_MUL(257U, 66U), ///< PLL multiplier of 257.66
    CGC_PLL_MUL_258_0  = BSP_CLOCKS_PLL_MUL(258U, 0U),  ///< PLL multiplier of 258.00
    CGC_PLL_MUL_258_33 = BSP_CLOCKS_PLL_MUL(258U, 33U), ///< PLL multiplier of 258.33
    CGC_PLL_MUL_258_5  = BSP_CLOCKS_PLL_MUL(258U, 50U), ///< PLL multiplier of 258.50
    CGC_PLL_MUL_258_66 = BSP_CLOCKS_PLL_MUL(258U, 66U), ///< PLL multiplier of 258.66
    CGC_PLL_MUL_259_0  = BSP_CLOCKS_PLL_MUL(259U, 0U),  ///< PLL multiplier of 259.00
    CGC_PLL_MUL_259_33 = BSP_CLOCKS_PLL_MUL(259U, 33U), ///< PLL multiplier of 259.33
    CGC_PLL_MUL_259_5  = BSP_CLOCKS_PLL_MUL(259U, 50U), ///< PLL multiplier of 259.50
    CGC_PLL_MUL_259_66 = BSP_CLOCKS_PLL_MUL(259U, 66U), ///< PLL multiplier of 259.66
    CGC_PLL_MUL_260_0  = BSP_CLOCKS_PLL_MUL(260U, 0U),  ///< PLL multiplier of 260.00
    CGC_PLL_MUL_260_33 = BSP_CLOCKS_PLL_MUL(260U, 33U), ///< PLL multiplier of 260.33
    CGC_PLL_MUL_260_5  = BSP_CLOCKS_PLL_MUL(260U, 50U), ///< PLL multiplier of 260.50
    CGC_PLL_MUL_260_66 = BSP_CLOCKS_PLL_MUL(260U, 66U), ///< PLL multiplier of 260.66
    CGC_PLL_MUL_261_0  = BSP_CLOCKS_PLL_MUL(261U, 0U),  ///< PLL multiplier of 261.00
    CGC_PLL_MUL_261_33 = BSP_CLOCKS_PLL_MUL(261U, 33U), ///< PLL multiplier of 261.33
    CGC_PLL_MUL_261_5  = BSP_CLOCKS_PLL_MUL(261U, 50U), ///< PLL multiplier of 261.50
    CGC_PLL_MUL_261_66 = BSP_CLOCKS_PLL_MUL(261U, 66U), ///< PLL multiplier of 261.66
    CGC_PLL_MUL_262_0  = BSP_CLOCKS_PLL_MUL(262U, 0U),  ///< PLL multiplier of 262.00
    CGC_PLL_MUL_262_33 = BSP_CLOCKS_PLL_MUL(262U, 33U), ///< PLL multiplier of 262.33
    CGC_PLL_MUL_262_5  = BSP_CLOCKS_PLL_MUL(262U, 50U), ///< PLL multiplier of 262.50
    CGC_PLL_MUL_262_66 = BSP_CLOCKS_PLL_MUL(262U, 66U), ///< PLL multiplier of 262.66
    CGC_PLL_MUL_263_0  = BSP_CLOCKS_PLL_MUL(263U, 0U),  ///< PLL multiplier of 263.00
    CGC_PLL_MUL_263_33 = BSP_CLOCKS_PLL_MUL(263U, 33U), ///< PLL multiplier of 263.33
    CGC_PLL_MUL_263_5  = BSP_CLOCKS_PLL_MUL(263U, 50U), ///< PLL multiplier of 263.50
    CGC_PLL_MUL_263_66 = BSP_CLOCKS_PLL_MUL(263U, 66U), ///< PLL multiplier of 263.66
    CGC_PLL_MUL_264_0  = BSP_CLOCKS_PLL_MUL(264U, 0U),  ///< PLL multiplier of 264.00
    CGC_PLL_MUL_264_33 = BSP_CLOCKS_PLL_MUL(264U, 33U), ///< PLL multiplier of 264.33
    CGC_PLL_MUL_264_5  = BSP_CLOCKS_PLL_MUL(264U, 50U), ///< PLL multiplier of 264.50
    CGC_PLL_MUL_264_66 = BSP_CLOCKS_PLL_MUL(264U, 66U), ///< PLL multiplier of 264.66
    CGC_PLL_MUL_265_0  = BSP_CLOCKS_PLL_MUL(265U, 0U),  ///< PLL multiplier of 265.00
    CGC_PLL_MUL_265_33 = BSP_CLOCKS_PLL_MUL(265U, 33U), ///< PLL multiplier of 265.33
    CGC_PLL_MUL_265_5  = BSP_CLOCKS_PLL_MUL(265U, 50U), ///< PLL multiplier of 265.50
    CGC_PLL_MUL_265_66 = BSP_CLOCKS_PLL_MUL(265U, 66U), ///< PLL multiplier of 265.66
    CGC_PLL_MUL_266_0  = BSP_CLOCKS_PLL_MUL(266U, 0U),  ///< PLL multiplier of 266.00
    CGC_PLL_MUL_266_33 = BSP_CLOCKS_PLL_MUL(266U, 33U), ///< PLL multiplier of 266.33
    CGC_PLL_MUL_266_5  = BSP_CLOCKS_PLL_MUL(266U, 50U), ///< PLL multiplier of 266.50
    CGC_PLL_MUL_266_66 = BSP_CLOCKS_PLL_MUL(266U, 66U), ///< PLL multiplier of 266.66
    CGC_PLL_MUL_267_0  = BSP_CLOCKS_PLL_MUL(267U, 0U),  ///< PLL multiplier of 267.00
    CGC_PLL_MUL_267_33 = BSP_CLOCKS_PLL_MUL(267U, 33U), ///< PLL multiplier of 267.33
    CGC_PLL_MUL_267_5  = BSP_CLOCKS_PLL_MUL(267U, 50U), ///< PLL multiplier of 267.50
    CGC_PLL_MUL_267_66 = BSP_CLOCKS_PLL_MUL(267U, 66U), ///< PLL multiplier of 267.66
    CGC_PLL_MUL_268_0  = BSP_CLOCKS_PLL_MUL(268U, 0U),  ///< PLL multiplier of 268.00
    CGC_PLL_MUL_268_33 = BSP_CLOCKS_PLL_MUL(268U, 33U), ///< PLL multiplier of 268.33
    CGC_PLL_MUL_268_5  = BSP_CLOCKS_PLL_MUL(268U, 50U), ///< PLL multiplier of 268.50
    CGC_PLL_MUL_268_66 = BSP_CLOCKS_PLL_MUL(268U, 66U), ///< PLL multiplier of 268.66
    CGC_PLL_MUL_269_0  = BSP_CLOCKS_PLL_MUL(269U, 0U),  ///< PLL multiplier of 269.00
    CGC_PLL_MUL_269_33 = BSP_CLOCKS_PLL_MUL(269U, 33U), ///< PLL multiplier of 269.33
    CGC_PLL_MUL_269_5  = BSP_CLOCKS_PLL_MUL(269U, 50U), ///< PLL multiplier of 269.50
    CGC_PLL_MUL_269_66 = BSP_CLOCKS_PLL_MUL(269U, 66U), ///< PLL multiplier of 269.66
    CGC_PLL_MUL_270_0  = BSP_CLOCKS_PLL_MUL(270U, 0U),  ///< PLL multiplier of 270.00
    CGC_PLL_MUL_270_33 = BSP_CLOCKS_PLL_MUL(270U, 33U), ///< PLL multiplier of 270.33
    CGC_PLL_MUL_270_5  = BSP_CLOCKS_PLL_MUL(270U, 50U), ///< PLL multiplier of 270.50
    CGC_PLL_MUL_270_66 = BSP_CLOCKS_PLL_MUL(270U, 66U), ///< PLL multiplier of 270.66
    CGC_PLL_MUL_271_0  = BSP_CLOCKS_PLL_MUL(271U, 0U),  ///< PLL multiplier of 271.00
    CGC_PLL_MUL_271_33 = BSP_CLOCKS_PLL_MUL(271U, 33U), ///< PLL multiplier of 271.33
    CGC_PLL_MUL_271_5  = BSP_CLOCKS_PLL_MUL(271U, 50U), ///< PLL multiplier of 271.50
    CGC_PLL_MUL_271_66 = BSP_CLOCKS_PLL_MUL(271U, 66U), ///< PLL multiplier of 271.66
    CGC_PLL_MUL_272_0  = BSP_CLOCKS_PLL_MUL(272U, 0U),  ///< PLL multiplier of 272.00
    CGC_PLL_MUL_272_33 = BSP_CLOCKS_PLL_MUL(272U, 33U), ///< PLL multiplier of 272.33
    CGC_PLL_MUL_272_5  = BSP_CLOCKS_PLL_MUL(272U, 50U), ///< PLL multiplier of 272.50
    CGC_PLL_MUL_272_66 = BSP_CLOCKS_PLL_MUL(272U, 66U), ///< PLL multiplier of 272.66
    CGC_PLL_MUL_273_0  = BSP_CLOCKS_PLL_MUL(273U, 0U),  ///< PLL multiplier of 273.00
    CGC_PLL_MUL_273_33 = BSP_CLOCKS_PLL_MUL(273U, 33U), ///< PLL multiplier of 273.33
    CGC_PLL_MUL_273_5  = BSP_CLOCKS_PLL_MUL(273U, 50U), ///< PLL multiplier of 273.50
    CGC_PLL_MUL_273_66 = BSP_CLOCKS_PLL_MUL(273U, 66U), ///< PLL multiplier of 273.66
    CGC_PLL_MUL_274_0  = BSP_CLOCKS_PLL_MUL(274U, 0U),  ///< PLL multiplier of 274.00
    CGC_PLL_MUL_274_33 = BSP_CLOCKS_PLL_MUL(274U, 33U), ///< PLL multiplier of 274.33
    CGC_PLL_MUL_274_5  = BSP_CLOCKS_PLL_MUL(274U, 50U), ///< PLL multiplier of 274.50
    CGC_PLL_MUL_274_66 = BSP_CLOCKS_PLL_MUL(274U, 66U), ///< PLL multiplier of 274.66
    CGC_PLL_MUL_275_0  = BSP_CLOCKS_PLL_MUL(275U, 0U),  ///< PLL multiplier of 275.00
    CGC_PLL_MUL_275_33 = BSP_CLOCKS_PLL_MUL(275U, 33U), ///< PLL multiplier of 275.33
    CGC_PLL_MUL_275_5  = BSP_CLOCKS_PLL_MUL(275U, 50U), ///< PLL multiplier of 275.50
    CGC_PLL_MUL_275_66 = BSP_CLOCKS_PLL_MUL(275U, 66U), ///< PLL multiplier of 275.66
    CGC_PLL_MUL_276_0  = BSP_CLOCKS_PLL_MUL(276U, 0U),  ///< PLL multiplier of 276.00
    CGC_PLL_MUL_276_33 = BSP_CLOCKS_PLL_MUL(276U, 33U), ///< PLL multiplier of 276.33
    CGC_PLL_MUL_276_5  = BSP_CLOCKS_PLL_MUL(276U, 50U), ///< PLL multiplier of 276.50
    CGC_PLL_MUL_276_66 = BSP_CLOCKS_PLL_MUL(276U, 66U), ///< PLL multiplier of 276.66
    CGC_PLL_MUL_277_0  = BSP_CLOCKS_PLL_MUL(277U, 0U),  ///< PLL multiplier of 277.00
    CGC_PLL_MUL_277_33 = BSP_CLOCKS_PLL_MUL(277U, 33U), ///< PLL multiplier of 277.33
    CGC_PLL_MUL_277_5  = BSP_CLOCKS_PLL_MUL(277U, 50U), ///< PLL multiplier of 277.50
    CGC_PLL_MUL_277_66 = BSP_CLOCKS_PLL_MUL(277U, 66U), ///< PLL multiplier of 277.66
    CGC_PLL_MUL_278_0  = BSP_CLOCKS_PLL_MUL(278U, 0U),  ///< PLL multiplier of 278.00
    CGC_PLL_MUL_278_33 = BSP_CLOCKS_PLL_MUL(278U, 33U), ///< PLL multiplier of 278.33
    CGC_PLL_MUL_278_5  = BSP_CLOCKS_PLL_MUL(278U, 50U), ///< PLL multiplier of 278.50
    CGC_PLL_MUL_278_66 = BSP_CLOCKS_PLL_MUL(278U, 66U), ///< PLL multiplier of 278.66
    CGC_PLL_MUL_279_0  = BSP_CLOCKS_PLL_MUL(279U, 0U),  ///< PLL multiplier of 279.00
    CGC_PLL_MUL_279_33 = BSP_CLOCKS_PLL_MUL(279U, 33U), ///< PLL multiplier of 279.33
    CGC_PLL_MUL_279_5  = BSP_CLOCKS_PLL_MUL(279U, 50U), ///< PLL multiplier of 279.50
    CGC_PLL_MUL_279_66 = BSP_CLOCKS_PLL_MUL(279U, 66U), ///< PLL multiplier of 279.66
    CGC_PLL_MUL_280_0  = BSP_CLOCKS_PLL_MUL(280U, 0U),  ///< PLL multiplier of 280.00
    CGC_PLL_MUL_280_33 = BSP_CLOCKS_PLL_MUL(280U, 33U), ///< PLL multiplier of 280.33
    CGC_PLL_MUL_280_5  = BSP_CLOCKS_PLL_MUL(280U, 50U), ///< PLL multiplier of 280.50
    CGC_PLL_MUL_280_66 = BSP_CLOCKS_PLL_MUL(280U, 66U), ///< PLL multiplier of 280.66
    CGC_PLL_MUL_281_0  = BSP_CLOCKS_PLL_MUL(281U, 0U),  ///< PLL multiplier of 281.00
    CGC_PLL_MUL_281_33 = BSP_CLOCKS_PLL_MUL(281U, 33U), ///< PLL multiplier of 281.33
    CGC_PLL_MUL_281_5  = BSP_CLOCKS_PLL_MUL(281U, 50U), ///< PLL multiplier of 281.50
    CGC_PLL_MUL_281_66 = BSP_CLOCKS_PLL_MUL(281U, 66U), ///< PLL multiplier of 281.66
    CGC_PLL_MUL_282_0  = BSP_CLOCKS_PLL_MUL(282U, 0U),  ///< PLL multiplier of 282.00
    CGC_PLL_MUL_282_33 = BSP_CLOCKS_PLL_MUL(282U, 33U), ///< PLL multiplier of 282.33
    CGC_PLL_MUL_282_5  = BSP_CLOCKS_PLL_MUL(282U, 50U), ///< PLL multiplier of 282.50
    CGC_PLL_MUL_282_66 = BSP_CLOCKS_PLL_MUL(282U, 66U), ///< PLL multiplier of 282.66
    CGC_PLL_MUL_283_0  = BSP_CLOCKS_PLL_MUL(283U, 0U),  ///< PLL multiplier of 283.00
    CGC_PLL_MUL_283_33 = BSP_CLOCKS_PLL_MUL(283U, 33U), ///< PLL multiplier of 283.33
    CGC_PLL_MUL_283_5  = BSP_CLOCKS_PLL_MUL(283U, 50U), ///< PLL multiplier of 283.50
    CGC_PLL_MUL_283_66 = BSP_CLOCKS_PLL_MUL(283U, 66U), ///< PLL multiplier of 283.66
    CGC_PLL_MUL_284_0  = BSP_CLOCKS_PLL_MUL(284U, 0U),  ///< PLL multiplier of 284.00
    CGC_PLL_MUL_284_33 = BSP_CLOCKS_PLL_MUL(284U, 33U), ///< PLL multiplier of 284.33
    CGC_PLL_MUL_284_5  = BSP_CLOCKS_PLL_MUL(284U, 50U), ///< PLL multiplier of 284.50
    CGC_PLL_MUL_284_66 = BSP_CLOCKS_PLL_MUL(284U, 66U), ///< PLL multiplier of 284.66
    CGC_PLL_MUL_285_0  = BSP_CLOCKS_PLL_MUL(285U, 0U),  ///< PLL multiplier of 285.00
    CGC_PLL_MUL_285_33 = BSP_CLOCKS_PLL_MUL(285U, 33U), ///< PLL multiplier of 285.33
    CGC_PLL_MUL_285_5  = BSP_CLOCKS_PLL_MUL(285U, 50U), ///< PLL multiplier of 285.50
    CGC_PLL_MUL_285_66 = BSP_CLOCKS_PLL_MUL(285U, 66U), ///< PLL multiplier of 285.66
    CGC_PLL_MUL_286_0  = BSP_CLOCKS_PLL_MUL(286U, 0U),  ///< PLL multiplier of 286.00
    CGC_PLL_MUL_286_33 = BSP_CLOCKS_PLL_MUL(286U, 33U), ///< PLL multiplier of 286.33
    CGC_PLL_MUL_286_5  = BSP_CLOCKS_PLL_MUL(286U, 50U), ///< PLL multiplier of 286.50
    CGC_PLL_MUL_286_66 = BSP_CLOCKS_PLL_MUL(286U, 66U), ///< PLL multiplier of 286.66
    CGC_PLL_MUL_287_0  = BSP_CLOCKS_PLL_MUL(287U, 0U),  ///< PLL multiplier of 287.00
    CGC_PLL_MUL_287_33 = BSP_CLOCKS_PLL_MUL(287U, 33U), ///< PLL multiplier of 287.33
    CGC_PLL_MUL_287_5  = BSP_CLOCKS_PLL_MUL(287U, 50U), ///< PLL multiplier of 287.50
    CGC_PLL_MUL_287_66 = BSP_CLOCKS_PLL_MUL(287U, 66U), ///< PLL multiplier of 287.66
    CGC_PLL_MUL_288_0  = BSP_CLOCKS_PLL_MUL(288U, 0U),  ///< PLL multiplier of 288.00
    CGC_PLL_MUL_288_33 = BSP_CLOCKS_PLL_MUL(288U, 33U), ///< PLL multiplier of 288.33
    CGC_PLL_MUL_288_5  = BSP_CLOCKS_PLL_MUL(288U, 50U), ///< PLL multiplier of 288.50
    CGC_PLL_MUL_288_66 = BSP_CLOCKS_PLL_MUL(288U, 66U), ///< PLL multiplier of 288.66
    CGC_PLL_MUL_289_0  = BSP_CLOCKS_PLL_MUL(289U, 0U),  ///< PLL multiplier of 289.00
    CGC_PLL_MUL_289_33 = BSP_CLOCKS_PLL_MUL(289U, 33U), ///< PLL multiplier of 289.33
    CGC_PLL_MUL_289_5  = BSP_CLOCKS_PLL_MUL(289U, 50U), ///< PLL multiplier of 289.50
    CGC_PLL_MUL_289_66 = BSP_CLOCKS_PLL_MUL(289U, 66U), ///< PLL multiplier of 289.66
    CGC_PLL_MUL_290_0  = BSP_CLOCKS_PLL_MUL(290U, 0U),  ///< PLL multiplier of 290.00
    CGC_PLL_MUL_290_33 = BSP_CLOCKS_PLL_MUL(290U, 33U), ///< PLL multiplier of 290.33
    CGC_PLL_MUL_290_5  = BSP_CLOCKS_PLL_MUL(290U, 50U), ///< PLL multiplier of 290.50
    CGC_PLL_MUL_290_66 = BSP_CLOCKS_PLL_MUL(290U, 66U), ///< PLL multiplier of 290.66
    CGC_PLL_MUL_291_0  = BSP_CLOCKS_PLL_MUL(291U, 0U),  ///< PLL multiplier of 291.00
    CGC_PLL_MUL_291_33 = BSP_CLOCKS_PLL_MUL(291U, 33U), ///< PLL multiplier of 291.33
    CGC_PLL_MUL_291_5  = BSP_CLOCKS_PLL_MUL(291U, 50U), ///< PLL multiplier of 291.50
    CGC_PLL_MUL_291_66 = BSP_CLOCKS_PLL_MUL(291U, 66U), ///< PLL multiplier of 291.66
    CGC_PLL_MUL_292_0  = BSP_CLOCKS_PLL_MUL(292U, 0U),  ///< PLL multiplier of 292.00
    CGC_PLL_MUL_292_33 = BSP_CLOCKS_PLL_MUL(292U, 33U), ///< PLL multiplier of 292.33
    CGC_PLL_MUL_292_5  = BSP_CLOCKS_PLL_MUL(292U, 50U), ///< PLL multiplier of 292.50
    CGC_PLL_MUL_292_66 = BSP_CLOCKS_PLL_MUL(292U, 66U), ///< PLL multiplier of 292.66
    CGC_PLL_MUL_293_0  = BSP_CLOCKS_PLL_MUL(293U, 0U),  ///< PLL multiplier of 293.00
    CGC_PLL_MUL_293_33 = BSP_CLOCKS_PLL_MUL(293U, 33U), ///< PLL multiplier of 293.33
    CGC_PLL_MUL_293_5  = BSP_CLOCKS_PLL_MUL(293U, 50U), ///< PLL multiplier of 293.50
    CGC_PLL_MUL_293_66 = BSP_CLOCKS_PLL_MUL(293U, 66U), ///< PLL multiplier of 293.66
    CGC_PLL_MUL_294_0  = BSP_CLOCKS_PLL_MUL(294U, 0U),  ///< PLL multiplier of 294.00
    CGC_PLL_MUL_294_33 = BSP_CLOCKS_PLL_MUL(294U, 33U), ///< PLL multiplier of 294.33
    CGC_PLL_MUL_294_5  = BSP_CLOCKS_PLL_MUL(294U, 50U), ///< PLL multiplier of 294.50
    CGC_PLL_MUL_294_66 = BSP_CLOCKS_PLL_MUL(294U, 66U), ///< PLL multiplier of 294.66
    CGC_PLL_MUL_295_0  = BSP_CLOCKS_PLL_MUL(295U, 0U),  ///< PLL multiplier of 295.00
    CGC_PLL_MUL_295_33 = BSP_CLOCKS_PLL_MUL(295U, 33U), ///< PLL multiplier of 295.33
    CGC_PLL_MUL_295_5  = BSP_CLOCKS_PLL_MUL(295U, 50U), ///< PLL multiplier of 295.50
    CGC_PLL_MUL_295_66 = BSP_CLOCKS_PLL_MUL(295U, 66U), ///< PLL multiplier of 295.66
    CGC_PLL_MUL_296_0  = BSP_CLOCKS_PLL_MUL(296U, 0U),  ///< PLL multiplier of 296.00
    CGC_PLL_MUL_296_33 = BSP_CLOCKS_PLL_MUL(296U, 33U), ///< PLL multiplier of 296.33
    CGC_PLL_MUL_296_5  = BSP_CLOCKS_PLL_MUL(296U, 50U), ///< PLL multiplier of 296.50
    CGC_PLL_MUL_296_66 = BSP_CLOCKS_PLL_MUL(296U, 66U), ///< PLL multiplier of 296.66
    CGC_PLL_MUL_297_0  = BSP_CLOCKS_PLL_MUL(297U, 0U),  ///< PLL multiplier of 297.00
    CGC_PLL_MUL_297_33 = BSP_CLOCKS_PLL_MUL(297U, 33U), ///< PLL multiplier of 297.33
    CGC_PLL_MUL_297_5  = BSP_CLOCKS_PLL_MUL(297U, 50U), ///< PLL multiplier of 297.50
    CGC_PLL_MUL_297_66 = BSP_CLOCKS_PLL_MUL(297U, 66U), ///< PLL multiplier of 297.66
    CGC_PLL_MUL_298_0  = BSP_CLOCKS_PLL_MUL(298U, 0U),  ///< PLL multiplier of 298.00
    CGC_PLL_MUL_298_33 = BSP_CLOCKS_PLL_MUL(298U, 33U), ///< PLL multiplier of 298.33
    CGC_PLL_MUL_298_5  = BSP_CLOCKS_PLL_MUL(298U, 50U), ///< PLL multiplier of 298.50
    CGC_PLL_MUL_298_66 = BSP_CLOCKS_PLL_MUL(298U, 66U), ///< PLL multiplier of 298.66
    CGC_PLL_MUL_299_0  = BSP_CLOCKS_PLL_MUL(299U, 0U),  ///< PLL multiplier of 299.00
    CGC_PLL_MUL_299_33 = BSP_CLOCKS_PLL_MUL(299U, 33U), ///< PLL multiplier of 299.33
    CGC_PLL_MUL_299_5  = BSP_CLOCKS_PLL_MUL(299U, 50U), ///< PLL multiplier of 299.50
    CGC_PLL_MUL_299_66 = BSP_CLOCKS_PLL_MUL(299U, 66U), ///< PLL multiplier of 299.66
    CGC_PLL_MUL_300_0  = BSP_CLOCKS_PLL_MUL(300U, 0U),  ///< PLL multiplier of 300.00
    CGC_PLL_MUL_300_33 = BSP_CLOCKS_PLL_MUL(300U, 33U), ///< PLL multiplier of 300.33
    CGC_PLL_MUL_300_5  = BSP_CLOCKS_PLL_MUL(300U, 50U), ///< PLL multiplier of 300.50
    CGC_PLL_MUL_300_66 = BSP_CLOCKS_PLL_MUL(300U, 66U), ///< PLL multiplier of 300.66
    CGC_PLL_MUL_732_0  = BSP_CLOCKS_PLL_MUL(732U, 0U),  ///< PLL multiplier of 732.00
    CGC_PLL_MUL_781_0  = BSP_CLOCKS_PLL_MUL(781U, 0U),  ///< PLL multiplier of 781.00
} cgc_pll_mul_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/* Public functions defined in bsp.h */
void bsp_clock_init(void);             // Used internally by BSP

#if BSP_TZ_NONSECURE_BUILD || BSP_ALT_BUILD
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

void bsp_prv_prepare_pll(uint32_t clock, uint32_t const * const p_pll_hz);

#if !BSP_FEATURE_CGC_REGISTER_SET_B
void bsp_prv_clock_set(uint32_t clock, uint32_t sckdivcr, uint16_t sckdivcr2);

#else
void     bsp_prv_clock_set(uint32_t clock, uint8_t hocodiv, uint8_t mocodiv, uint8_t moscdiv);
uint32_t bsp_prv_clock_source_get(void);

#endif

/* RTC Initialization */
#if BSP_FEATURE_RTC_IS_AVAILABLE || BSP_FEATURE_RTC_HAS_TCEN || BSP_FEATURE_SYSC_HAS_VBTICTLR
void R_BSP_Init_RTC(void);

#endif

#if BSP_FEATURE_LPM_RTC_REGISTER_CLOCK_DISABLE
bool bsp_prv_rtc_register_clock_set(bool enable);

#endif

#if BSP_CFG_SLEEP_MODE_DELAY_ENABLE || BSP_CFG_RTOS_SLEEP_MODE_DELAY_ENABLE
bool bsp_prv_clock_prepare_pre_sleep(void);
void bsp_prv_clock_prepare_post_sleep(bool cpuclk_slowed);

#endif

/* The public function is used to get state or initialize the sub-clock. */
#if BSP_FEATURE_RTC_IS_IRTC
fsp_err_t R_BSP_SubclockStatusGet();
fsp_err_t R_BSP_SubclockInitialize();

#endif

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
