/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
#define BSP_CLOCKS_SOURCE_CLOCK_HOCO        (0)  // The high speed on chip oscillator.
#define BSP_CLOCKS_SOURCE_CLOCK_MOCO        (1)  // The middle speed on chip oscillator.
#define BSP_CLOCKS_SOURCE_CLOCK_LOCO        (2)  // The low speed on chip oscillator.
#define BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC    (3)  // The main oscillator.
#define BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK    (4)  // The subclock oscillator.
#if 0 == BSP_FEATURE_NUM_PLL1_OUTPUT_CLOCKS && 0 == BSP_FEATURE_NUM_PLL2_OUTPUT_CLOCKS
 #define BSP_CLOCKS_SOURCE_CLOCK_PLL        (5)  // The PLL oscillator.
 #define BSP_CLOCKS_SOURCE_CLOCK_PLL2       (6)  // The PLL2 oscillator.
#elif (0 != BSP_FEATURE_NUM_PLL1_OUTPUT_CLOCKS && 0 != BSP_FEATURE_NUM_PLL2_OUTPUT_CLOCKS)
 #define BSP_CLOCKS_SOURCE_CLOCK_PLL        (5)  // The PLL oscillator. Treated as PLL1P.
 #define BSP_CLOCKS_SOURCE_CLOCK_PLL1P      (BSP_CLOCKS_SOURCE_CLOCK_PLL)
 #define BSP_CLOCKS_SOURCE_CLOCK_PLL2       (6)  // The PLL2 oscillator. Treated as PLL2P.
 #define BSP_CLOCKS_SOURCE_CLOCK_PLL2P      (BSP_CLOCKS_SOURCE_CLOCK_PLL2)
 #define BSP_CLOCKS_SOURCE_CLOCK_PLL1Q      (7)  // The PLL1Q oscillator.
 #define BSP_CLOCKS_SOURCE_CLOCK_PLL1R      (8)  // The PLL1R oscillator.
 #define BSP_CLOCKS_SOURCE_CLOCK_PLL2Q      (9)  // The PLL2Q oscillator.
 #define BSP_CLOCKS_SOURCE_CLOCK_PLL2R      (10) // The PLL2R oscillator.
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
    !BSP_CLOCK_CFG_MAIN_OSC_POPULATED)
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

/* Frequencies of clocks with fixed freqencies. */
#define BSP_LOCO_FREQ_HZ                 (32768U)   // LOCO frequency is fixed at 32768 Hz
#define BSP_SUBCLOCK_FREQ_HZ             (32768U)   // Subclock frequency is 32768 Hz
#define BSP_MOCO_FREQ_HZ                 (8000000U) // MOCO frequency is fixed at 8 MHz

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
 #if (1U == BSP_FEATURE_CGC_PLLCCR_TYPE)
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
 #elif (3U == BSP_FEATURE_CGC_PLLCCR_TYPE)
  #define BSP_STARTUP_SOURCE_CLOCK_HZ    (BSP_CFG_PLL1P_FREQUENCY_HZ)
 #endif
#endif

/* Convert divisor bitfield settings into divisor values to calculate startup clocks */
#define BSP_PRV_SCKDIVCR_DIV_VALUE(div)    (((div) & 8U) ? (3U << ((div) & ~8U)) : (1U << (div)))
#define BSP_PRV_CPUCLK_DIV_VALUE         BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_CPUCLK_DIV)
#define BSP_PRV_ICLK_DIV_VALUE           BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_ICLK_DIV)
#define BSP_PRV_PCLKA_DIV_VALUE          BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_PCLKA_DIV)
#define BSP_PRV_PCLKB_DIV_VALUE          BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_PCLKB_DIV)
#define BSP_PRV_PCLKC_DIV_VALUE          BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_PCLKC_DIV)
#define BSP_PRV_PCLKD_DIV_VALUE          BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_PCLKD_DIV)
#define BSP_PRV_PCLKE_DIV_VALUE          BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_PCLKE_DIV)
#define BSP_PRV_BCLK_DIV_VALUE           BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_BCLK_DIV)
#define BSP_PRV_FCLK_DIV_VALUE           BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_FCLK_DIV)

/* Startup clock frequency of each system clock. These macros are only helpful if the system clock and dividers have
 * not changed since startup. These macros are not used in FSP modules except for the clock startup code. */
#define BSP_STARTUP_CPUCLK_HZ            (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_CPUCLK_DIV_VALUE)
#define BSP_STARTUP_ICLK_HZ              (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_ICLK_DIV_VALUE)
#define BSP_STARTUP_PCLKA_HZ             (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_PCLKA_DIV_VALUE)
#define BSP_STARTUP_PCLKB_HZ             (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_PCLKB_DIV_VALUE)
#define BSP_STARTUP_PCLKC_HZ             (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_PCLKC_DIV_VALUE)
#define BSP_STARTUP_PCLKD_HZ             (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_PCLKD_DIV_VALUE)
#define BSP_STARTUP_PCLKE_HZ             (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_PCLKE_DIV_VALUE)
#define BSP_STARTUP_BCLK_HZ              (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_BCLK_DIV_VALUE)
#define BSP_STARTUP_FCLK_HZ              (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_FCLK_DIV_VALUE)

/* System clock divider options. */
#define BSP_CLOCKS_SYS_CLOCK_DIV_1       (0)  // System clock divided by 1.
#define BSP_CLOCKS_SYS_CLOCK_DIV_2       (1)  // System clock divided by 2.
#define BSP_CLOCKS_SYS_CLOCK_DIV_4       (2)  // System clock divided by 4.
#define BSP_CLOCKS_SYS_CLOCK_DIV_8       (3)  // System clock divided by 8.
#define BSP_CLOCKS_SYS_CLOCK_DIV_16      (4)  // System clock divided by 16.
#define BSP_CLOCKS_SYS_CLOCK_DIV_32      (5)  // System clock divided by 32.
#define BSP_CLOCKS_SYS_CLOCK_DIV_64      (6)  // System clock divided by 64.
#define BSP_CLOCKS_SYS_CLOCK_DIV_128     (7)  // System clock divided by 128 (available for CLKOUT only).
#define BSP_CLOCKS_SYS_CLOCK_DIV_3       (8)  // System clock divided by 3.
#define BSP_CLOCKS_SYS_CLOCK_DIV_6       (9)  // System clock divided by 6.
#define BSP_CLOCKS_SYS_CLOCK_DIV_12      (10) // System clock divided by 12.

/* USB clock divider options. */
#define BSP_CLOCKS_USB_CLOCK_DIV_1       (0)  // Divide USB source clock by 1
#define BSP_CLOCKS_USB_CLOCK_DIV_2       (1)  // Divide USB source clock by 2
#define BSP_CLOCKS_USB_CLOCK_DIV_3       (5)  // Divide USB source clock by 3
#define BSP_CLOCKS_USB_CLOCK_DIV_4       (2)  // Divide USB source clock by 4
#define BSP_CLOCKS_USB_CLOCK_DIV_5       (6)  // Divide USB source clock by 5
#define BSP_CLOCKS_USB_CLOCK_DIV_6       (3)  // Divide USB source clock by 6
#define BSP_CLOCKS_USB_CLOCK_DIV_8       (4)  // Divide USB source clock by 8

/* USB60 clock divider options. */
#define BSP_CLOCKS_USB60_CLOCK_DIV_1     (0)  // Divide USB60 source clock by 1
#define BSP_CLOCKS_USB60_CLOCK_DIV_2     (1)  // Divide USB60 source clock by 2
#define BSP_CLOCKS_USB60_CLOCK_DIV_3     (5)  // Divide USB60 source clock by 3
#define BSP_CLOCKS_USB60_CLOCK_DIV_4     (2)  // Divide USB60 source clock by 4
#define BSP_CLOCKS_USB60_CLOCK_DIV_5     (6)  // Divide USB60 source clock by 5
#define BSP_CLOCKS_USB60_CLOCK_DIV_6     (3)  // Divide USB66 source clock by 6
#define BSP_CLOCKS_USB60_CLOCK_DIV_8     (4)  // Divide USB60 source clock by 8

/* GLCD clock divider options. */
#define BSP_CLOCKS_LCD_CLOCK_DIV_1       (0)  // Divide LCD source clock by 1
#define BSP_CLOCKS_LCD_CLOCK_DIV_2       (1)  // Divide LCD source clock by 2
#define BSP_CLOCKS_LCD_CLOCK_DIV_3       (5)  // Divide LCD source clock by 3
#define BSP_CLOCKS_LCD_CLOCK_DIV_4       (2)  // Divide LCD source clock by 4
#define BSP_CLOCKS_LCD_CLOCK_DIV_5       (6)  // Divide LCD source clock by 5
#define BSP_CLOCKS_LCD_CLOCK_DIV_6       (3)  // Divide LCD source clock by 6
#define BSP_CLOCKS_LCD_CLOCK_DIV_8       (4)  // Divide LCD source clock by 8

/* OCTA clock divider options. */
#define BSP_CLOCKS_OCTA_CLOCK_DIV_1      (0)  // Divide OCTA source clock by 1
#define BSP_CLOCKS_OCTA_CLOCK_DIV_2      (1)  // Divide OCTA source clock by 2
#define BSP_CLOCKS_OCTA_CLOCK_DIV_4      (2)  // Divide OCTA source clock by 4
#define BSP_CLOCKS_OCTA_CLOCK_DIV_6      (3)  // Divide OCTA source clock by 6
#define BSP_CLOCKS_OCTA_CLOCK_DIV_8      (4)  // Divide OCTA source clock by 8

/* CANFD clock divider options. */
#define BSP_CLOCKS_CANFD_CLOCK_DIV_1     (0)  // Divide CANFD source clock by 1
#define BSP_CLOCKS_CANFD_CLOCK_DIV_2     (1)  // Divide CANFD source clock by 2
#define BSP_CLOCKS_CANFD_CLOCK_DIV_3     (5)  // Divide CANFD source clock by 3
#define BSP_CLOCKS_CANFD_CLOCK_DIV_4     (2)  // Divide CANFD source clock by 4
#define BSP_CLOCKS_CANFD_CLOCK_DIV_5     (6)  // Divide CANFD source clock by 5
#define BSP_CLOCKS_CANFD_CLOCK_DIV_6     (3)  // Divide CANFD source clock by 6
#define BSP_CLOCKS_CANFD_CLOCK_DIV_8     (4)  // Divide CANFD source clock by 8

/* SCI clock divider options. */
#define BSP_CLOCKS_SCI_CLOCK_DIV_1       (0)  // Divide SCI source clock by 1
#define BSP_CLOCKS_SCI_CLOCK_DIV_2       (1)  // Divide SCI source clock by 2
#define BSP_CLOCKS_SCI_CLOCK_DIV_3       (5)  // Divide SCI source clock by 3
#define BSP_CLOCKS_SCI_CLOCK_DIV_4       (2)  // Divide SCI source clock by 4
#define BSP_CLOCKS_SCI_CLOCK_DIV_5       (6)  // Divide SCI source clock by 5
#define BSP_CLOCKS_SCI_CLOCK_DIV_6       (3)  // Divide SCI source clock by 6
#define BSP_CLOCKS_SCI_CLOCK_DIV_8       (4)  // Divide SCI source clock by 8

/* SPI clock divider options. */
#define BSP_CLOCKS_SPI_CLOCK_DIV_1       (0)  // Divide SPI source clock by 1
#define BSP_CLOCKS_SPI_CLOCK_DIV_2       (1)  // Divide SPI source clock by 2
#define BSP_CLOCKS_SPI_CLOCK_DIV_3       (5)  // Divide SPI source clock by 3
#define BSP_CLOCKS_SPI_CLOCK_DIV_4       (2)  // Divide SPI source clock by 4
#define BSP_CLOCKS_SPI_CLOCK_DIV_5       (6)  // Divide SPI source clock by 5
#define BSP_CLOCKS_SPI_CLOCK_DIV_6       (3)  // Divide SPI source clock by 6
#define BSP_CLOCKS_SPI_CLOCK_DIV_8       (4)  // Divide SPI source clock by 8

/* SCISPI clock divider options. */
#define BSP_CLOCKS_SCISPI_CLOCK_DIV_1    (0)  // Divide SCISPI source clock by 1
#define BSP_CLOCKS_SCISPI_CLOCK_DIV_2    (1)  // Divide SCISPI source clock by 2
#define BSP_CLOCKS_SCISPI_CLOCK_DIV_4    (2)  // Divide SCISPI source clock by 4
#define BSP_CLOCKS_SCISPI_CLOCK_DIV_6    (3)  // Divide SCISPI source clock by 6
#define BSP_CLOCKS_SCISPI_CLOCK_DIV_8    (4)  // Divide SCISPI source clock by 8

/* GPT clock divider options. */
#define BSP_CLOCKS_GPT_CLOCK_DIV_1       (0)  // Divide GPT source clock by 1
#define BSP_CLOCKS_GPT_CLOCK_DIV_2       (1)  // Divide GPT source clock by 2
#define BSP_CLOCKS_GPT_CLOCK_DIV_3       (5)  // Divide GPT source clock by 3
#define BSP_CLOCKS_GPT_CLOCK_DIV_4       (2)  // Divide GPT source clock by 4
#define BSP_CLOCKS_GPT_CLOCK_DIV_5       (6)  // Divide GPT source clock by 5
#define BSP_CLOCKS_GPT_CLOCK_DIV_6       (3)  // Divide GPT source clock by 6
#define BSP_CLOCKS_GPT_CLOCK_DIV_8       (4)  // Divide GPT source clock by 8

/* IIC clock divider options. */
#define BSP_CLOCKS_IIC_CLOCK_DIV_1       (0)  // Divide IIC source clock by 1
#define BSP_CLOCKS_IIC_CLOCK_DIV_2       (1)  // Divide IIC source clock by 2
#define BSP_CLOCKS_IIC_CLOCK_DIV_4       (2)  // Divide IIC source clock by 4
#define BSP_CLOCKS_IIC_CLOCK_DIV_6       (3)  // Divide IIC source clock by 6
#define BSP_CLOCKS_IIC_CLOCK_DIV_8       (4)  // Divide IIC source clock by 8

/* CEC clock divider options. */
#define BSP_CLOCKS_CEC_CLOCK_DIV_1       (0)  // Divide CEC source clock by 1
#define BSP_CLOCKS_CEC_CLOCK_DIV_2       (1)  // Divide CEC source clock by 2

/* I3C clock divider options. */
#define BSP_CLOCKS_I3C_CLOCK_DIV_1       (0)  // Divide I3C source clock by 1
#define BSP_CLOCKS_I3C_CLOCK_DIV_2       (1)  // Divide I3C source clock by 2
#define BSP_CLOCKS_I3C_CLOCK_DIV_3       (5)  // Divide I3C source clock by 3
#define BSP_CLOCKS_I3C_CLOCK_DIV_4       (2)  // Divide I3C source clock by 4
#define BSP_CLOCKS_I3C_CLOCK_DIV_5       (6)  // Divide I3C source clock by 5
#define BSP_CLOCKS_I3C_CLOCK_DIV_6       (3)  // Divide I3C source clock by 6
#define BSP_CLOCKS_I3C_CLOCK_DIV_8       (4)  // Divide I3C source clock by 8

/* ADC clock divider options. */
#define BSP_CLOCKS_ADC_CLOCK_DIV_1       (0)  // Divide ADC source clock by 1
#define BSP_CLOCKS_ADC_CLOCK_DIV_2       (1)  // Divide ADC source clock by 2
#define BSP_CLOCKS_ADC_CLOCK_DIV_3       (5)  // Divide ADC source clock by 3
#define BSP_CLOCKS_ADC_CLOCK_DIV_4       (2)  // Divide ADC source clock by 4
#define BSP_CLOCKS_ADC_CLOCK_DIV_5       (6)  // Divide ADC source clock by 5
#define BSP_CLOCKS_ADC_CLOCK_DIV_6       (3)  // Divide ADC source clock by 6
#define BSP_CLOCKS_ADC_CLOCK_DIV_8       (4)  // Divide ADC source clock by 8

/* PLL divider options. */
#define BSP_CLOCKS_PLL_DIV_1             (0)
#define BSP_CLOCKS_PLL_DIV_2             (1)
#define BSP_CLOCKS_PLL_DIV_3             (2)
#define BSP_CLOCKS_PLL_DIV_4             (3)
#define BSP_CLOCKS_PLL_DIV_5             (4)
#define BSP_CLOCKS_PLL_DIV_6             (5)
#define BSP_CLOCKS_PLL_DIV_8             (7)
#define BSP_CLOCKS_PLL_DIV_9             (8)
#define BSP_CLOCKS_PLL_DIV_16            (15)

/* PLL multiplier options. */
#if (4U == BSP_FEATURE_CGC_PLLCCR_TYPE)

/* Offset from decimal multiplier to register value for PLLCCR type 4. */
 #define BSP_PRV_CLOCKS_PLL_MUL_INT_OFFSET    (574)

/**
 * X=Integer portion of the multiplier.
 * Y=Fractional portion of the multiplier. (not used for this PLLCCR type)
 */
 #define BSP_CLOCKS_PLL_MUL(X, Y)    ((X) -BSP_PRV_CLOCKS_PLL_MUL_INT_OFFSET)

#elif (3U != BSP_FEATURE_CGC_PLLCCR_TYPE)

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
#define BSP_PRV_SCKDIVCR_ICLK_MASK             (FSP_PRV_SCKDIVCR_DIV_MASK << 24)
#if BSP_FEATURE_CGC_HAS_PCLKD
 #define BSP_PRV_SCKDIVCR_PCLKD_MASK           (FSP_PRV_SCKDIVCR_DIV_MASK << 0)
#else
 #define BSP_PRV_SCKDIVCR_PCLKD_MASK           (0U)
#endif
#if BSP_FEATURE_CGC_HAS_PCLKC
 #define BSP_PRV_SCKDIVCR_PCLKC_MASK           (FSP_PRV_SCKDIVCR_DIV_MASK << 4)
#else
 #define BSP_PRV_SCKDIVCR_PCLKC_MASK           (0U)
#endif
#if BSP_FEATURE_CGC_HAS_PCLKB
 #define BSP_PRV_SCKDIVCR_PCLKB_MASK           (FSP_PRV_SCKDIVCR_DIV_MASK << 8)
#else
 #define BSP_PRV_SCKDIVCR_PCLKB_MASK           (0U)
#endif
#if BSP_FEATURE_CGC_HAS_PCLKA
 #define BSP_PRV_SCKDIVCR_PCLKA_MASK           (FSP_PRV_SCKDIVCR_DIV_MASK << 12)
#else
 #define BSP_PRV_SCKDIVCR_PCLKA_MASK           (0U)
#endif
#if BSP_FEATURE_CGC_HAS_BCLK || BSP_FEATURE_CGC_SCKDIVCR_BCLK_MATCHES_PCLKB
 #define BSP_PRV_SCKDIVCR_BCLK_MASK            (FSP_PRV_SCKDIVCR_DIV_MASK << 16)
#else
 #define BSP_PRV_SCKDIVCR_BCLK_MASK            (0U)
#endif
#if BSP_FEATURE_CGC_HAS_PCLKE
 #define BSP_PRV_SCKDIVCR_PCLKE_MASK           (FSP_PRV_SCKDIVCR_DIV_MASK << 24)
#else
 #define BSP_PRV_SCKDIVCR_PCLKE_MASK           (0U)
#endif
#if BSP_FEATURE_CGC_HAS_FCLK
 #define BSP_PRV_SCKDIVCR_FCLK_MASK            (FSP_PRV_SCKDIVCR_DIV_MASK << 28)
#else
 #define BSP_PRV_SCKDIVCR_FCLK_MASK            (0U)
#endif
#define BSP_PRV_SCKDIVCR_MASK                  (BSP_PRV_SCKDIVCR_ICLK_MASK | BSP_PRV_SCKDIVCR_PCLKD_MASK |  \
                                                BSP_PRV_SCKDIVCR_PCLKC_MASK | BSP_PRV_SCKDIVCR_PCLKB_MASK | \
                                                BSP_PRV_SCKDIVCR_PCLKA_MASK | BSP_PRV_SCKDIVCR_BCLK_MASK |  \
                                                BSP_PRV_SCKDIVCR_PCLKE_MASK | BSP_PRV_SCKDIVCR_FCLK_MASK)

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

#if BSP_FEATURE_RTC_IS_AVAILABLE || BSP_FEATURE_RTC_HAS_TCEN || BSP_FEATURE_SYSC_HAS_VBTICTLR
 #define BSP_PRV_RTC_RESET_DELAY_US            (200)
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

/** PLL multiplier values */
typedef enum e_cgc_pll_mul
{
    CGC_PLL_MUL_8_0    = BSP_CLOCKS_PLL_MUL(8U, 0U),    ///< PLL multiplier of 8.0
    CGC_PLL_MUL_9_0    = BSP_CLOCKS_PLL_MUL(9U, 0U),    ///< PLL multiplier of 9.0
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
void bsp_prv_clock_set(uint32_t clock, uint32_t sckdivcr, uint8_t sckdivcr2);

/* RTC Initialization */
#if BSP_FEATURE_RTC_IS_AVAILABLE || BSP_FEATURE_RTC_HAS_TCEN || BSP_FEATURE_SYSC_HAS_VBTICTLR
void R_BSP_Init_RTC(void);

#endif

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
