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

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_clocks.h"

#if BSP_TZ_NONSECURE_BUILD
 #include "bsp_guard.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Key code for writing PRCR register. */
#define BSP_PRV_PRCR_KEY                        (0xA500U)
#define BSP_PRV_PRCR_UNLOCK                     ((BSP_PRV_PRCR_KEY) | 0x3U)
#define BSP_PRV_PRCR_LOCK                       ((BSP_PRV_PRCR_KEY) | 0x0U)

/* Wait state definitions for MEMWAIT. */
#define BSP_PRV_MEMWAIT_ZERO_WAIT_CYCLES        (0U)
#define BSP_PRV_MEMWAIT_TWO_WAIT_CYCLES         (1U)
#define BSP_PRV_MEMWAIT_MAX_ZERO_WAIT_FREQ      (32000000U)

/* Wait state definitions for FLDWAITR. */
#define BSP_PRV_FLDWAITR_ONE_WAIT_CYCLES        (0U)
#define BSP_PRV_FLDWAITR_TWO_WAIT_CYCLES        (1U)
#define BSP_PRV_FLDWAITR_MAX_ONE_WAIT_FREQ      (32000000U)

/* Temporary solution until R_FACI is added to renesas.h. */
#define BSP_PRV_FLDWAITR_REG_ACCESS             (*((volatile uint8_t *) (0x407EFFC4U)))

/* Wait state definitions for MCUS with SRAMWTSC and FLWT. */
#define BSP_PRV_SRAMWTSC_WAIT_CYCLES_DISABLE    (0U)
#define BSP_PRV_ROM_ZERO_WAIT_CYCLES            (0U)
#define BSP_PRV_ROM_ONE_WAIT_CYCLES             (1U)
#define BSP_PRV_ROM_TWO_WAIT_CYCLES             (2U)
#define BSP_PRV_ROM_THREE_WAIT_CYCLES           (3U)
#define BSP_PRV_ROM_FOUR_WAIT_CYCLES            (4U)
#define BSP_PRV_ROM_FIVE_WAIT_CYCLES            (5U)
#define BSP_PRV_SRAM_UNLOCK                     (((BSP_FEATURE_CGC_SRAMPRCR_KW_VALUE) << \
                                                  BSP_FEATURE_CGC_SRAMPRCR_KW_OFFSET) | 0x1U)
#define BSP_PRV_SRAM_LOCK                       (((BSP_FEATURE_CGC_SRAMPRCR_KW_VALUE) << \
                                                  BSP_FEATURE_CGC_SRAMPRCR_KW_OFFSET) | 0x0U)

/* Calculate value to write to MOMCR (MODRV controls main clock drive strength and MOSEL determines the source of the
 * main oscillator). */
#if BSP_FEATURE_CGC_MODRV_MASK
 #define BSP_PRV_MODRV                          ((CGC_MAINCLOCK_DRIVE << BSP_FEATURE_CGC_MODRV_SHIFT) & \
                                                 BSP_FEATURE_CGC_MODRV_MASK)
#else
 #define BSP_PRV_MODRV                          (0x1AU)
#endif
#define BSP_PRV_MOSEL                           (BSP_CLOCK_CFG_MAIN_OSC_CLOCK_SOURCE << R_SYSTEM_MOMCR_MOSEL_Pos)
#define BSP_PRV_MOMCR                           (BSP_PRV_MODRV | BSP_PRV_MOSEL)

/* Locations of bitfields used to configure CLKOUT. */
#define BSP_PRV_CKOCR_CKODIV_BIT                (4U)
#define BSP_PRV_CKOCR_CKOEN_BIT                 (7U)

/* Stop interval of at least 5 SOSC clock cycles between stop and restart of SOSC.
 * Calculated based on 8Mhz of MOCO clock. */
#define BSP_PRV_SUBCLOCK_STOP_INTERVAL_US       (200U)

/* Locations of bitfields used to configure Peripheral Clocks. */
#define BSP_PRV_PERIPHERAL_CLK_REQ_BIT_POS      (6U)
#define BSP_PRV_PERIPHERAL_CLK_REQ_BIT_MASK     (1U << BSP_PRV_PERIPHERAL_CLK_REQ_BIT_POS)
#define BSP_PRV_PERIPHERAL_CLK_RDY_BIT_POS      (7U)
#define BSP_PRV_PERIPHERAL_CLK_RDY_BIT_MASK     (1U << BSP_PRV_PERIPHERAL_CLK_RDY_BIT_POS)

#ifdef BSP_CFG_UCK_DIV

/* If the MCU has SCKDIVCR2 for USBCK configuration. */
 #if !BSP_FEATURE_BSP_HAS_USBCKDIVCR

/* Location of bitfield used to configure USB clock divider. */
  #define BSP_PRV_SCKDIVCR2_UCK_BIT    (4U)
  #define BSP_PRV_UCK_DIV              (BSP_CFG_UCK_DIV)

/* If the MCU has USBCKDIVCR. */
 #elif BSP_FEATURE_BSP_HAS_USBCKDIVCR
  #if BSP_CLOCKS_USB_CLOCK_DIV_1 == BSP_CFG_UCK_DIV
   #define BSP_PRV_UCK_DIV             (0U)
  #elif BSP_CLOCKS_USB_CLOCK_DIV_2 == BSP_CFG_UCK_DIV
   #define BSP_PRV_UCK_DIV             (1U)
  #elif BSP_CLOCKS_USB_CLOCK_DIV_3 == BSP_CFG_UCK_DIV
   #define BSP_PRV_UCK_DIV             (5U)
  #elif BSP_CLOCKS_USB_CLOCK_DIV_4 == BSP_CFG_UCK_DIV
   #define BSP_PRV_UCK_DIV             (2U)
  #elif BSP_CLOCKS_USB_CLOCK_DIV_5 == BSP_CFG_UCK_DIV
   #define BSP_PRV_UCK_DIV             (6U)
  #elif BSP_CLOCKS_USB_CLOCK_DIV_6 == BSP_CFG_UCK_DIV
   #define BSP_PRV_UCK_DIV             (3U)
  #elif BSP_CLOCKS_USB_CLOCK_DIV_8 == BSP_CFG_UCK_DIV
   #define BSP_PRV_UCK_DIV             (4U)
  #else

   #error "BSP_CFG_UCK_DIV not supported."

  #endif
 #endif
#endif
#if BSP_FEATURE_BSP_HAS_USB60_CLOCK_REQ
 #define BSP_CLOCKS_USB60_CLOCK_DIV_1            (0) // Divide USB source clock by 1
 #define BSP_CLOCKS_USB60_CLOCK_DIV_2            (1) // Divide USB source clock by 2
 #define BSP_CLOCKS_USB60_CLOCK_DIV_3            (5) // Divide USB source clock by 3
 #define BSP_CLOCKS_USB60_CLOCK_DIV_4            (2) // Divide USB source clock by 4
 #define BSP_CLOCKS_USB60_CLOCK_DIV_5            (6) // Divide USB source clock by 5
 #define BSP_CLOCKS_USB60_CLOCK_DIV_6            (3) // Divide USB source clock by 6
 #define BSP_CLOCKS_USB60_CLOCK_DIV_8            (4) // Divide USB source clock by 8
#endif /* BSP_FEATURE_BSP_HAS_USB60_CLOCK_REQ*/
/* Choose the value to write to FLLCR2 (if applicable). */
#if BSP_PRV_HOCO_USE_FLL
 #if 1U == BSP_CFG_HOCO_FREQUENCY
  #define BSP_PRV_FLL_FLLCR2                     (0x226U)
 #elif 2U == BSP_CFG_HOCO_FREQUENCY
  #define BSP_PRV_FLL_FLLCR2                     (0x263U)
 #elif 4U == BSP_CFG_HOCO_FREQUENCY
  #define BSP_PRV_FLL_FLLCR2                     (0x263U)
 #else

/* When BSP_CFG_HOCO_FREQUENCY is 0, 4, 7 */
  #define BSP_PRV_FLL_FLLCR2                     (0x1E9U)
 #endif
#endif

/* Calculate the value to write to SCKDIVCR. */
#define BSP_PRV_STARTUP_SCKDIVCR_ICLK_BITS       ((BSP_CFG_ICLK_DIV & 0xFU) << 24U)
#if BSP_FEATURE_CGC_HAS_PCLKE
 #define BSP_PRV_STARTUP_SCKDIVCR_PCLKE_BITS     ((BSP_CFG_PCLKE_DIV & 0xFU) << 20U)
#else
 #define BSP_PRV_STARTUP_SCKDIVCR_PCLKE_BITS     (0U)
#endif
#if BSP_FEATURE_CGC_HAS_PCLKD
 #define BSP_PRV_STARTUP_SCKDIVCR_PCLKD_BITS     (BSP_CFG_PCLKD_DIV & 0xFU)
#else
 #define BSP_PRV_STARTUP_SCKDIVCR_PCLKD_BITS     (0U)
#endif
#if BSP_FEATURE_CGC_HAS_PCLKC
 #define BSP_PRV_STARTUP_SCKDIVCR_PCLKC_BITS     ((BSP_CFG_PCLKC_DIV & 0xFU) << 4U)
#else
 #define BSP_PRV_STARTUP_SCKDIVCR_PCLKC_BITS     (0U)
#endif
#if BSP_FEATURE_CGC_HAS_PCLKB
 #define BSP_PRV_STARTUP_SCKDIVCR_PCLKB_BITS     ((BSP_CFG_PCLKB_DIV & 0xFU) << 8U)
#else
 #define BSP_PRV_STARTUP_SCKDIVCR_PCLKB_BITS     (0U)
#endif
#if BSP_FEATURE_CGC_HAS_PCLKA
 #define BSP_PRV_STARTUP_SCKDIVCR_PCLKA_BITS     ((BSP_CFG_PCLKA_DIV & 0xFU) << 12U)
#else
 #define BSP_PRV_STARTUP_SCKDIVCR_PCLKA_BITS     (0U)
#endif
#if BSP_FEATURE_CGC_HAS_BCLK
 #define BSP_PRV_STARTUP_SCKDIVCR_BCLK_BITS      ((BSP_CFG_BCLK_DIV & 0xFU) << 16U)
#elif BSP_FEATURE_CGC_SCKDIVCR_BCLK_MATCHES_PCLKB

/* Some MCUs have a requirement that bits 18-16 be set to the same value as the bits for configuring the PCLKB divisor. */
 #define BSP_PRV_STARTUP_SCKDIVCR_BCLK_BITS      ((BSP_CFG_PCLKB_DIV & 0xFU) << 16U)
#else
 #define BSP_PRV_STARTUP_SCKDIVCR_BCLK_BITS      (0U)
#endif
#if BSP_FEATURE_CGC_HAS_FCLK
 #define BSP_PRV_STARTUP_SCKDIVCR_FCLK_BITS      ((BSP_CFG_FCLK_DIV & 0xFU) << 28U)
#else
 #define BSP_PRV_STARTUP_SCKDIVCR_FCLK_BITS      (0U)
#endif
#define BSP_PRV_STARTUP_SCKDIVCR                 (BSP_PRV_STARTUP_SCKDIVCR_ICLK_BITS |  \
                                                  BSP_PRV_STARTUP_SCKDIVCR_PCLKE_BITS | \
                                                  BSP_PRV_STARTUP_SCKDIVCR_PCLKD_BITS | \
                                                  BSP_PRV_STARTUP_SCKDIVCR_PCLKC_BITS | \
                                                  BSP_PRV_STARTUP_SCKDIVCR_PCLKB_BITS | \
                                                  BSP_PRV_STARTUP_SCKDIVCR_PCLKA_BITS | \
                                                  BSP_PRV_STARTUP_SCKDIVCR_BCLK_BITS |  \
                                                  BSP_PRV_STARTUP_SCKDIVCR_FCLK_BITS)
#if BSP_FEATURE_CGC_HAS_CPUCLK
 #define BSP_PRV_STARTUP_SCKDIVCR2_CPUCK_BITS    (BSP_CFG_CPUCLK_DIV & 0xFU)
 #define BSP_PRV_STARTUP_SCKDIVCR2               (BSP_PRV_STARTUP_SCKDIVCR2_CPUCK_BITS)
#endif

/* The number of clocks is used to size the g_clock_freq array. */
#if BSP_PRV_PLL2_SUPPORTED
 #if 0 != BSP_FEATURE_NUM_PLL2_OUTPUT_CLOCKS
  #define BSP_PRV_NUM_CLOCKS    ((uint8_t) BSP_CLOCKS_SOURCE_CLOCK_PLL2 + (BSP_FEATURE_NUM_PLL1_OUTPUT_CLOCKS - 1) + \
                                 BSP_FEATURE_NUM_PLL2_OUTPUT_CLOCKS)
 #else
  #define BSP_PRV_NUM_CLOCKS    ((uint8_t) BSP_CLOCKS_SOURCE_CLOCK_PLL2 + 1U)
 #endif
#elif BSP_PRV_PLL_SUPPORTED
 #if 0 != BSP_FEATURE_NUM_PLL1_OUTPUT_CLOCKS

/* Removed offset of 1 since the BSP_CLOCKS_SOURCE_CLOCK_PLL will be reused for BSP_CLOCKS_SOURCE_CLOCK_PLL1P which is included in BSP_FEATURE_NUM_PLL1_OUTPUT_CLOCKS count. */
  #define BSP_PRV_NUM_CLOCKS    ((uint8_t) BSP_CLOCKS_SOURCE_CLOCK_PLL + BSP_FEATURE_NUM_PLL1_OUTPUT_CLOCKS)
 #else
  #define BSP_PRV_NUM_CLOCKS    ((uint8_t) BSP_CLOCKS_SOURCE_CLOCK_PLL + 1U)
 #endif
#else
 #define BSP_PRV_NUM_CLOCKS     ((uint8_t) BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK + 1U)
#endif

/* Calculate PLLCCR value. */
#if BSP_PRV_PLL_SUPPORTED
 #if (1U == BSP_FEATURE_CGC_PLLCCR_TYPE)
  #if BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC == BSP_CFG_PLL_SOURCE
   #define BSP_PRV_PLSRCSEL                        (0)
   #define BSP_PRV_PLL_USED                        (1)
  #elif BSP_CLOCKS_SOURCE_CLOCK_HOCO == BSP_CFG_PLL_SOURCE
   #define BSP_PRV_PLSRCSEL                        (1)
   #define BSP_PRV_PLL_USED                        (1)
  #else
   #define BSP_PRV_PLL_USED                        (0)
  #endif
  #define BSP_PRV_PLLCCR_PLLMUL_MASK               (0x3F) // PLLMUL in PLLCCR is 6 bits wide
  #define BSP_PRV_PLLCCR_PLLMUL_BIT                (8)    // PLLMUL in PLLCCR starts at bit 8
  #define BSP_PRV_PLLCCR_PLSRCSEL_BIT              (4)    // PLSRCSEL in PLLCCR starts at bit 4
  #define BSP_PRV_PLLCCR                           ((((BSP_CFG_PLL_MUL & BSP_PRV_PLLCCR_PLLMUL_MASK) <<   \
                                                      BSP_PRV_PLLCCR_PLLMUL_BIT) |                        \
                                                     (BSP_PRV_PLSRCSEL << BSP_PRV_PLLCCR_PLSRCSEL_BIT)) | \
                                                    BSP_CFG_PLL_DIV)
 #endif
 #if (2U == BSP_FEATURE_CGC_PLLCCR_TYPE)
  #if BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC == BSP_CFG_PLL_SOURCE
   #define BSP_PRV_PLSRCSEL                        (0)
   #define BSP_PRV_PLL_USED                        (1)
  #else
   #define BSP_PRV_PLL_USED                        (0)
  #endif
  #define BSP_PRV_PLLCCR2_PLLMUL_MASK              (0x1F) // PLLMUL in PLLCCR2 is 5 bits wide
  #define BSP_PRV_PLLCCR2_PLODIV_BIT               (6)    // PLODIV in PLLCCR2 starts at bit 6

  #define BSP_PRV_PLLCCR2_PLLMUL                   (BSP_CFG_PLL_MUL >> 1)
  #define BSP_PRV_PLLCCR                           ((BSP_PRV_PLLCCR2_PLLMUL & BSP_PRV_PLLCCR2_PLLMUL_MASK) | \
                                                    (BSP_CFG_PLL_DIV << BSP_PRV_PLLCCR2_PLODIV_BIT))
 #endif
 #if (3U == BSP_FEATURE_CGC_PLLCCR_TYPE)
  #if BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC == BSP_CFG_PLL_SOURCE
   #define BSP_PRV_PLSRCSEL                        (0)
   #define BSP_PRV_PLL_USED                        (1)
  #elif BSP_CLOCKS_SOURCE_CLOCK_HOCO == BSP_CFG_PLL_SOURCE
   #define BSP_PRV_PLSRCSEL                        (1)
   #define BSP_PRV_PLL_USED                        (1)
  #else
   #define BSP_PRV_PLL_USED                        (0)
  #endif

  #define BSP_PRV_PLL_MUL_CFG_MACRO_PLLMUL_MASK    (0x3FFU)
  #define BSP_PRV_PLLCCR_PLLMULNF_BIT              (6) // PLLMULNF in PLLCCR starts at bit 6
  #define BSP_PRV_PLLCCR_PLSRCSEL_BIT              (4) // PLSRCSEL in PLLCCR starts at bit 4
  #define BSP_PRV_PLLCCR                           ((((BSP_CFG_PLL_MUL & BSP_PRV_PLL_MUL_CFG_MACRO_PLLMUL_MASK) << \
                                                      BSP_PRV_PLLCCR_PLLMULNF_BIT) |                               \
                                                     (BSP_PRV_PLSRCSEL << BSP_PRV_PLLCCR_PLSRCSEL_BIT)) |          \
                                                    BSP_CFG_PLL_DIV)
  #define BSP_PRV_PLLCCR2_PLL_DIV_MASK             (0x0F) // PLL DIV in PLLCCR2/PLL2CCR2 is 4 bits wide
  #define BSP_PRV_PLLCCR2_PLL_DIV_Q_BIT            (4)    // PLL DIV Q in PLLCCR2/PLL2CCR2 starts at bit 4
  #define BSP_PRV_PLLCCR2_PLL_DIV_R_BIT            (8)    // PLL DIV R in PLLCCR2/PLL2CCR2 starts at bit 8
  #define BSP_PRV_PLLCCR2                          (((BSP_CFG_PLODIVR & BSP_PRV_PLLCCR2_PLL_DIV_MASK) << \
                                                     BSP_PRV_PLLCCR2_PLL_DIV_R_BIT) |                    \
                                                    ((BSP_CFG_PLODIVQ & BSP_PRV_PLLCCR2_PLL_DIV_MASK) << \
                                                     BSP_PRV_PLLCCR2_PLL_DIV_Q_BIT) |                    \
                                                    (BSP_CFG_PLODIVP & BSP_PRV_PLLCCR2_PLL_DIV_MASK))
 #endif
 #if (4U == BSP_FEATURE_CGC_PLLCCR_TYPE)
  #if BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK == BSP_CFG_PLL_SOURCE
   #define BSP_PRV_PLL_USED                        (1)
  #else
   #define BSP_PRV_PLL_USED                        (0)
  #endif

  #define BSP_PRV_PLLCCR_PLLMUL_MASK               (0xFFU)   // PLLMUL is 8 bits wide
  #define BSP_PRV_PLLCCR_PLLMUL_BIT                (8)       // PLLMUL starts at bit 8
  #define BSP_PRV_PLLCCR_RESET                     (0x0004U) // Bit 2 must be written as 1
  #define BSP_PRV_PLLCCR                           (((BSP_CFG_PLL_MUL & BSP_PRV_PLLCCR_PLLMUL_MASK) << \
                                                     BSP_PRV_PLLCCR_PLLMUL_BIT) |                      \
                                                    BSP_PRV_PLLCCR_RESET)
 #endif
#endif

#if BSP_FEATURE_CGC_HAS_PLL2
 #if BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC == BSP_CFG_PLL2_SOURCE
  #define BSP_PRV_PL2SRCSEL                           (0)
  #define BSP_PRV_PLL2_USED                           (1)
 #elif BSP_CLOCKS_SOURCE_CLOCK_HOCO == BSP_CFG_PLL2_SOURCE
  #define BSP_PRV_PL2SRCSEL                           (1)
  #define BSP_PRV_PLL2_USED                           (1)
 #else
  #define BSP_PRV_PLL2_USED                           (0)
 #endif

 #if (3U == BSP_FEATURE_CGC_PLLCCR_TYPE)
  #define BSP_PRV_PLL2_MUL_CFG_MACRO_PLLMUL_MASK      (0x3FF)
  #define BSP_PRV_PLL2_MUL_CFG_MACRO_PLLMULNF_MASK    (0x003U)
  #define BSP_PRV_PLL2CCR_PLLMULNF_BIT                (6) // PLLMULNF in PLLCCR starts at bit 6
  #define BSP_PRV_PLL2CCR_PLSRCSEL_BIT                (4) // PLSRCSEL in PLLCCR starts at bit 4
  #define BSP_PRV_PLL2CCR                             ((((BSP_CFG_PLL2_MUL & BSP_PRV_PLL2_MUL_CFG_MACRO_PLLMUL_MASK) << \
                                                         BSP_PRV_PLL2CCR_PLLMULNF_BIT) |                                \
                                                        (BSP_PRV_PL2SRCSEL << BSP_PRV_PLL2CCR_PLSRCSEL_BIT)) |          \
                                                       BSP_CFG_PLL2_DIV)
  #define BSP_PRV_PLL2CCR2_PLL_DIV_MASK               (0x0F) // PLL DIV in PLL2CCR2 is 4 bits wide
  #define BSP_PRV_PLL2CCR2_PLL_DIV_Q_BIT              (4)    // PLL DIV Q in PLL2CCR2 starts at bit 4
  #define BSP_PRV_PLL2CCR2_PLL_DIV_R_BIT              (8)    // PLL DIV R in PLL2CCR2 starts at bit 8
  #define BSP_PRV_PLL2CCR2                            (((BSP_CFG_PL2ODIVR & BSP_PRV_PLL2CCR2_PLL_DIV_MASK) << \
                                                        BSP_PRV_PLL2CCR2_PLL_DIV_R_BIT) |                     \
                                                       ((BSP_CFG_PL2ODIVQ & BSP_PRV_PLL2CCR2_PLL_DIV_MASK) << \
                                                        BSP_PRV_PLL2CCR2_PLL_DIV_Q_BIT) |                     \
                                                       (BSP_CFG_PL2ODIVP & BSP_PRV_PLL2CCR2_PLL_DIV_MASK))
 #else
  #define BSP_PRV_PLL2CCR                             ((BSP_CFG_PLL2_MUL << R_SYSTEM_PLL2CCR_PLL2MUL_Pos) | \
                                                       (BSP_CFG_PLL2_DIV << R_SYSTEM_PLL2CCR_PL2IDIV_Pos) | \
                                                       (BSP_PRV_PL2SRCSEL << R_SYSTEM_PLL2CCR_PL2SRCSEL_Pos))
 #endif
#endif

/* All clocks with configurable source except PLL and CLKOUT can use PLL. */
#if (BSP_CFG_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_PLL)
 #define BSP_PRV_STABILIZE_PLL                    (1)
#endif

/* All clocks with configurable source can use the main oscillator. */
#if (BSP_CFG_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)
 #define BSP_PRV_MAIN_OSC_USED                    (1)
 #define BSP_PRV_STABILIZE_MAIN_OSC               (1)
#elif defined(BSP_CFG_UCK_SOURCE) && BSP_FEATURE_BSP_HAS_USB_CLOCK_REQ && \
    (BSP_CFG_UCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)
 #define BSP_PRV_MAIN_OSC_USED                    (1)
#elif defined(BSP_CFG_CANFDCLK_SOURCE) && (BSP_CFG_CANFDCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)
 #define BSP_PRV_MAIN_OSC_USED                    (1)
#elif defined(BSP_CFG_PLL_SOURCE) && (BSP_CFG_PLL_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC) && BSP_PRV_PLL_USED
 #define BSP_PRV_MAIN_OSC_USED                    (1)
 #define BSP_PRV_STABILIZE_MAIN_OSC               (1)
#elif defined(BSP_CFG_PLL2_SOURCE) && (BSP_CFG_PLL2_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC) && BSP_PRV_PLL2_USED
 #define BSP_PRV_MAIN_OSC_USED                    (1)
 #define BSP_PRV_STABILIZE_MAIN_OSC               (1)
#elif defined(BSP_CFG_CLKOUT_SOURCE) && (BSP_CFG_CLKOUT_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)
 #define BSP_PRV_MAIN_OSC_USED                    (1)
#elif defined(BSP_CFG_SCISPICLK_SOURCE) && (BSP_CFG_SCISPICLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)
 #define BSP_PRV_MAIN_OSC_USED                    (1)
#elif defined(BSP_CFG_SPICLK_SOURCE) && (BSP_CFG_SPICLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)
 #define BSP_PRV_MAIN_OSC_USED                    (1)
#elif defined(BSP_CFG_SCICLK_SOURCE) && (BSP_CFG_SCICLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)
 #define BSP_PRV_MAIN_OSC_USED                    (1)
#elif defined(BSP_CFG_CANFDCLK_SOURCE) && (BSP_CFG_CANFDCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)
 #define BSP_PRV_MAIN_OSC_USED                    (1)
#elif defined(BSP_CFG_GPTCLK_SOURCE) && (BSP_CFG_GPTCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)
 #define BSP_PRV_MAIN_OSC_USED                    (1)
#elif defined(BSP_CFG_IICCLK_SOURCE) && (BSP_CFG_IICCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)
 #define BSP_PRV_MAIN_OSC_USED                    (1)
#elif defined(BSP_CFG_CECCLK_SOURCE) && (BSP_CFG_CECCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)
 #define BSP_PRV_MAIN_OSC_USED                    (1)
#elif defined(BSP_CFG_I3CCLK_SOURCE) && (BSP_CFG_I3CCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)
 #define BSP_PRV_MAIN_OSC_USED                    (1)
#elif defined(BSP_CFG_LCDCLK_SOURCE) && (BSP_CFG_LCDCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)
 #define BSP_PRV_MAIN_OSC_USED                    (1)
#elif defined(BSP_CFG_U60CLK_SOURCE) && (BSP_CFG_U60CLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)
 #define BSP_PRV_MAIN_OSC_USED                    (1)
#elif defined(BSP_CFG_OCTA_SOURCE) && (BSP_CFG_OCTA_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)
 #define BSP_PRV_MAIN_OSC_USED                    (1)
#elif defined(BSP_CFG_SDADC_CLOCK_SOURCE) && (BSP_CFG_SDADC_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)
 #define BSP_PRV_MAIN_OSC_USED                    (1)
#else
 #define BSP_PRV_MAIN_OSC_USED                    (0)
#endif

/* All clocks with configurable source can use HOCO except the CECCLK and I3CCLK. */
#if (BSP_CFG_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HOCO)
 #define BSP_PRV_HOCO_USED                        (1)
 #define BSP_PRV_STABILIZE_HOCO                   (1)
#elif defined(BSP_CFG_PLL_SOURCE) && (BSP_CFG_PLL_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HOCO) && BSP_PRV_PLL_USED
 #define BSP_PRV_HOCO_USED                        (1)
 #define BSP_PRV_STABILIZE_HOCO                   (1)
#elif defined(BSP_CFG_PLL2_SOURCE) && (BSP_CFG_PLL2_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HOCO) && BSP_PRV_PLL2_USED
 #define BSP_PRV_HOCO_USED                        (1)
 #define BSP_PRV_STABILIZE_HOCO                   (1)
#elif defined(BSP_CFG_UCK_SOURCE) && BSP_FEATURE_BSP_HAS_USB_CLOCK_REQ && \
    (BSP_CFG_UCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HOCO)
 #define BSP_PRV_HOCO_USED                        (1)
#elif defined(BSP_CFG_CLKOUT_SOURCE) && (BSP_CFG_CLKOUT_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HOCO)
 #define BSP_PRV_HOCO_USED                        (1)
#elif defined(BSP_CFG_SCISPICLK_SOURCE) && (BSP_CFG_SCISPICLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HOCO)
 #define BSP_PRV_HOCO_USED                        (1)
#elif defined(BSP_CFG_SPICLK_SOURCE) && (BSP_CFG_SPICLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HOCO)
 #define BSP_PRV_HOCO_USED                        (1)
#elif defined(BSP_CFG_SCICLK_SOURCE) && (BSP_CFG_SCICLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HOCO)
 #define BSP_PRV_HOCO_USED                        (1)
#elif defined(BSP_CFG_CANFDCLK_SOURCE) && (BSP_CFG_CANFDCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HOCO)
 #define BSP_PRV_HOCO_USED                        (1)
#elif defined(BSP_CFG_GPTCLK_SOURCE) && (BSP_CFG_GPTCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HOCO)
 #define BSP_PRV_HOCO_USED                        (1)
#elif defined(BSP_CFG_IICCLK_SOURCE) && (BSP_CFG_IICCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HOCO)
 #define BSP_PRV_HOCO_USED                        (1)
#elif defined(BSP_CFG_LCDCLK_SOURCE) && (BSP_CFG_LCDCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HOCO)
 #define BSP_PRV_HOCO_USED                        (1)
#elif defined(BSP_CFG_U60CLK_SOURCE) && (BSP_CFG_U60CLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HOCO)
 #define BSP_PRV_HOCO_USED                        (1)
#elif defined(BSP_CFG_OCTA_SOURCE) && (BSP_CFG_OCTA_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HOCO)
 #define BSP_PRV_HOCO_USED                        (1)
#elif defined(BSP_CFG_SDADC_CLOCK_SOURCE) && (BSP_CFG_SDADC_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_HOCO)
 #define BSP_PRV_HOCO_USED                        (1)
#else
 #define BSP_PRV_HOCO_USED                        (0)
#endif

/* All clocks with configurable source except PLL can use MOCO. */
#if (BSP_CFG_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MOCO)
 #define BSP_PRV_MOCO_USED                        (1)
 #define BSP_PRV_STABILIZE_MOCO                   (1)
#elif defined(BSP_CFG_CLKOUT_SOURCE) && (BSP_CFG_CLKOUT_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MOCO)
 #define BSP_PRV_MOCO_USED                        (1)
#elif defined(BSP_CFG_UCK_SOURCE) && BSP_FEATURE_BSP_HAS_USB_CLOCK_REQ && \
    (BSP_CFG_UCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MOCO)
 #define BSP_PRV_MOCO_USED                        (1)
#elif defined(BSP_CFG_SCISPICLK_SOURCE) && (BSP_CFG_SCISPICLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MOCO)
 #define BSP_PRV_MOCO_USED                        (1)
#elif defined(BSP_CFG_SPICLK_SOURCE) && (BSP_CFG_SPICLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MOCO)
 #define BSP_PRV_MOCO_USED                        (1)
#elif defined(BSP_CFG_SCICLK_SOURCE) && (BSP_CFG_SCICLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MOCO)
 #define BSP_PRV_MOCO_USED                        (1)
#elif defined(BSP_CFG_CANFDCLK_SOURCE) && (BSP_CFG_CANFDCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MOCO)
 #define BSP_PRV_MOCO_USED                        (1)
#elif defined(BSP_CFG_GPTCLK_SOURCE) && (BSP_CFG_GPTCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MOCO)
 #define BSP_PRV_MOCO_USED                        (1)
#elif defined(BSP_CFG_IICCLK_SOURCE) && (BSP_CFG_IICCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MOCO)
 #define BSP_PRV_MOCO_USED                        (1)
#elif defined(BSP_CFG_I3CCLK_SOURCE) && (BSP_CFG_I3CCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MOCO)
 #define BSP_PRV_MOCO_USED                        (1)
#elif defined(BSP_CFG_LCDCLK_SOURCE) && (BSP_CFG_LCDCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MOCO)
 #define BSP_PRV_MOCO_USED                        (1)
#elif defined(BSP_CFG_U60CLK_SOURCE) && (BSP_CFG_U60CLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MOCO)
 #define BSP_PRV_MOCO_USED                        (1)
#elif defined(BSP_CFG_OCTA_SOURCE) && (BSP_CFG_OCTA_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_MOCO)
 #define BSP_PRV_MOCO_USED                        (1)
#else
 #define BSP_PRV_MOCO_USED                        (0)
#endif

/* All clocks with configurable source except UCK, CANFD, LCDCLK, USBHSCLK, I3CCLK and PLL can use LOCO. */
#if (BSP_CFG_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_LOCO)
 #define BSP_PRV_LOCO_USED                        (1)
 #define BSP_PRV_STABILIZE_LOCO                   (1)
#elif defined(BSP_CFG_CLKOUT_SOURCE) && (BSP_CFG_CLKOUT_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_LOCO)
 #define BSP_PRV_LOCO_USED                        (1)
#elif defined(BSP_CFG_SCISPICLK_SOURCE) && (BSP_CFG_SCISPICLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_LOCO)
 #define BSP_PRV_LOCO_USED                        (1)
#elif defined(BSP_CFG_SPICLK_SOURCE) && (BSP_CFG_SPICLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_LOCO)
 #define BSP_PRV_LOCO_USED                        (1)
#elif defined(BSP_CFG_SCICLK_SOURCE) && (BSP_CFG_SCICLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_LOCO)
 #define BSP_PRV_LOCO_USED                        (1)
#elif defined(BSP_CFG_CANFDCLK_SOURCE) && (BSP_CFG_CANFDCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_LOCO)
 #define BSP_PRV_LOCO_USED                        (1)
#elif defined(BSP_CFG_GPTCLK_SOURCE) && (BSP_CFG_GPTCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_LOCO)
 #define BSP_PRV_LOCO_USED                        (1)
#elif defined(BSP_CFG_IICCLK_SOURCE) && (BSP_CFG_IICCLK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_LOCO)
 #define BSP_PRV_LOCO_USED                        (1)
#elif defined(BSP_CFG_OCTA_SOURCE) && (BSP_CFG_OCTA_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_LOCO)
 #define BSP_PRV_LOCO_USED                        (1)
#else
 #define BSP_PRV_LOCO_USED                        (0)
#endif

/* Determine the optimal operating speed mode to apply after clock configuration based on the startup clock
 * frequency. */
#if BSP_STARTUP_ICLK_HZ <= BSP_FEATURE_CGC_LOW_SPEED_MAX_FREQ_HZ && \
    !BSP_PRV_PLL_USED && !BSP_PRV_PLL2_USED
 #define BSP_PRV_STARTUP_OPERATING_MODE           (BSP_PRV_OPERATING_MODE_LOW_SPEED)
#elif BSP_STARTUP_ICLK_HZ <= BSP_FEATURE_CGC_MIDDLE_SPEED_MAX_FREQ_HZ
 #define BSP_PRV_STARTUP_OPERATING_MODE           (BSP_PRV_OPERATING_MODE_MIDDLE_SPEED)
#else
 #define BSP_PRV_STARTUP_OPERATING_MODE           (BSP_PRV_OPERATING_MODE_HIGH_SPEED)
#endif

#if BSP_FEATURE_BSP_HAS_CLOCK_SUPPLY_TYPEB
 #define BSP_PRV_CLOCK_SUPPLY_TYPE_B              (0 == BSP_CFG_ROM_REG_OFS1_ICSATS)
#else
 #define BSP_PRV_CLOCK_SUPPLY_TYPE_B              (0)
#endif

#if (BSP_FEATURE_BSP_HAS_CANFD_CLOCK && (BSP_CFG_CANFDCLK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED) &&    \
    (BSP_CFG_CANFDCLK_SOURCE != BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)) ||                                \
    (BSP_FEATURE_BSP_HAS_SCISPI_CLOCK && (BSP_CFG_SCISPICLK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED)) || \
    (BSP_FEATURE_BSP_HAS_SCI_CLOCK && (BSP_CFG_SCICLK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED)) ||       \
    (BSP_FEATURE_BSP_HAS_SPI_CLOCK && (BSP_CFG_SPICLK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED)) ||       \
    (BSP_FEATURE_BSP_HAS_GPT_CLOCK && (BSP_CFG_GPTCLK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED)) ||       \
    (BSP_FEATURE_BSP_HAS_IIC_CLOCK && (BSP_CFG_IICCLK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED)) ||       \
    (BSP_FEATURE_BSP_HAS_CEC_CLOCK && (BSP_CFG_CECCLK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED)) ||       \
    (BSP_FEATURE_BSP_HAS_I3C_CLOCK && (BSP_CFG_I3CCLK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED)) ||       \
    (BSP_FEATURE_BSP_HAS_USB60_CLOCK_REQ && (BSP_CFG_U60CK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED)) ||  \
    (BSP_FEATURE_BSP_HAS_LCD_CLOCK && (BSP_CFG_LCDCLK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED))

 #define BSP_PRV_HAS_ENABLED_PERIPHERAL_CLOCKS    (1U)
#else
 #define BSP_PRV_HAS_ENABLED_PERIPHERAL_CLOCKS    (0U)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
static uint8_t bsp_clock_set_prechange(uint32_t requested_freq_hz);
static void    bsp_clock_set_postchange(uint32_t updated_freq_hz, uint8_t new_rom_wait_state);
static void    bsp_sosc_init(void);

#if BSP_CLOCK_CFG_SUBCLOCK_POPULATED
 #if defined(__ICCARM__)

void R_BSP_SubClockStabilizeWait(uint32_t delay_ms);
void R_BSP_SubClockStabilizeWaitAfterReset(uint32_t delay_ms);

  #pragma weak R_BSP_SubClockStabilizeWait
  #pragma weak R_BSP_SubClockStabilizeWaitAfterReset

 #elif defined(__GNUC__) || defined(__ARMCC_VERSION)

void R_BSP_SubClockStabilizeWait(uint32_t delay_ms) __attribute__((weak));
void R_BSP_SubClockStabilizeWaitAfterReset(uint32_t delay_ms) __attribute__((weak));

 #endif
#endif

#if (BSP_PRV_HAS_ENABLED_PERIPHERAL_CLOCKS == 1U)
static void bsp_peripheral_clock_set(volatile uint8_t * p_clk_ctrl_reg,
                                     volatile uint8_t * p_clk_div_reg,
                                     uint8_t            peripheral_clk_div,
                                     uint8_t            peripheral_clk_source);

#endif

#if !BSP_CFG_USE_LOW_VOLTAGE_MODE
static void bsp_prv_operating_mode_opccr_set(uint8_t operating_mode);

#endif

#if !BSP_CFG_STARTUP_CLOCK_REG_NOT_RESET
static void bsp_prv_clock_set_hard_reset(void);

#else
void bsp_soft_reset_prepare(void);

#endif

void prv_clock_dividers_set(uint32_t sckdivcr, uint8_t sckdivcr2);

/* This array stores the clock frequency of each system clock. This section of RAM should not be initialized by the C
 * runtime environment. This is initialized and used in bsp_clock_init, which is called before the C runtime
 * environment is initialized. */
static uint32_t g_clock_freq[BSP_PRV_NUM_CLOCKS]  BSP_PLACE_IN_SECTION(BSP_SECTION_NOINIT);

#if BSP_TZ_SECURE_BUILD

/* Callback used to notify the nonsecure project that the clock settings have changed. */
static bsp_clock_update_callback_t g_bsp_clock_update_callback = NULL;

/* Pointer to nonsecure memory to store the callback args. */
static bsp_clock_update_callback_args_t * gp_callback_memory = NULL;

/* Reentrant method of calling the clock_update_callback. */
static void r_bsp_clock_update_callback_call (bsp_clock_update_callback_t        p_callback,
                                              bsp_clock_update_callback_args_t * p_callback_args)
{
    /* Allocate memory for saving global callback args on the secure stack. */
    bsp_clock_update_callback_args_t callback_args;

    /* Save current info stored in callback memory. */
    callback_args = *gp_callback_memory;

    /* Write the callback args to the nonsecure callback memory. */
    *gp_callback_memory = *p_callback_args;

    /* Call the callback to notifiy ns project about clock changes. */
    p_callback(gp_callback_memory);

    /* Restore the info in callback memory. */
    *gp_callback_memory = callback_args;
}

/* Initialize the callback, callback memory and invoke the callback to ensure the nonsecure project has the correct clock settings. */
void r_bsp_clock_update_callback_set (bsp_clock_update_callback_t        p_callback,
                                      bsp_clock_update_callback_args_t * p_callback_memory)
{
    /* Store pointer to nonsecure callback memory. */
    gp_callback_memory = p_callback_memory;

    /* Store callback. */
    g_bsp_clock_update_callback = p_callback;

    /* Set callback args. */
    bsp_clock_update_callback_args_t callback_args =
    {
        .pll_freq = g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL]
    };

    /* Call the callback. */
    r_bsp_clock_update_callback_call(g_bsp_clock_update_callback, &callback_args);
}

#elif BSP_TZ_NONSECURE_BUILD && BSP_CFG_CLOCKS_SECURE == 1

bsp_clock_update_callback_args_t g_callback_memory;
 #if BSP_TZ_SECURE_BUILD || BSP_TZ_NONSECURE_BUILD
  #if defined(__ARMCC_VERSION) || defined(__ICCARM__)
static void BSP_CMSE_NONSECURE_CALL g_bsp_clock_update_callback (bsp_clock_update_callback_args_t * p_callback_args)
  #elif defined(__GNUC__)

static BSP_CMSE_NONSECURE_CALL void g_bsp_clock_update_callback (bsp_clock_update_callback_args_t * p_callback_args)
  #endif

{
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL] = p_callback_args->pll_freq;

    /* Update the SystemCoreClock value based on the new g_clock_freq settings. */
    SystemCoreClockUpdate();
}

 #endif
#endif

#if BSP_FEATURE_LPM_CHANGE_MSTP_REQUIRED

/* List of MSTP bits that must be set before entering low power modes or changing SCKDIVCR. */
static const uint8_t g_bsp_prv_power_change_mstp_data[][2] = BSP_FEATURE_LPM_CHANGE_MSTP_ARRAY;

static const uint8_t g_bsp_prv_power_change_mstp_length = sizeof(g_bsp_prv_power_change_mstp_data) /
                                                          sizeof(g_bsp_prv_power_change_mstp_data[0]);

static volatile uint32_t * const gp_bsp_prv_mstp = &R_MSTP->MSTPCRB;
#endif

/*******************************************************************************************************************//**
 * @internal
 * @addtogroup BSP_MCU_PRV Internal BSP Documentation
 * @ingroup RENESAS_INTERNAL
 * @{
 **********************************************************************************************************************/

#if !BSP_CFG_USE_LOW_VOLTAGE_MODE

/***********************************************************************************************************************
 * Changes the operating speed in OPCCR.  Assumes the LPM registers are unlocked in PRCR and cache is off.
 *
 * @param[in]  operating_mode  Desired operating mode, must be one of the BSP_PRV_OPERATING_MODE_* macros, cannot be
 *                             BSP_PRV_OPERATING_MODE_SUBOSC_SPEED
 **********************************************************************************************************************/
static void bsp_prv_operating_mode_opccr_set (uint8_t operating_mode)
{
 #if BSP_FEATURE_CGC_HOCOSF_BEFORE_OPCCR

    /* If the desired operating mode is already set, return. */
    if (operating_mode == R_SYSTEM->OPCCR)
    {
        return;
    }

    /* On some MCUs, the HOCO must be stable before updating OPCCR.OPCM. */
    if (0U == R_SYSTEM->HOCOCR)
    {
        /* Wait for HOCO to stabilize. */
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OSCSF_b.HOCOSF, 1U);
    }
 #endif

    /* Wait for transition to complete. */
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OPCCR_b.OPCMTSF, 0U);

    /* Apply requested operating speed mode. */
    R_SYSTEM->OPCCR = operating_mode;

    /* Wait for transition to complete. */
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OPCCR_b.OPCMTSF, 0U);
}

#endif

#if !BSP_CFG_USE_LOW_VOLTAGE_MODE

/***********************************************************************************************************************
 * Changes the operating speed mode.  Assumes the LPM registers are unlocked in PRCR and cache is off.
 *
 * @param[in]  operating_mode  Desired operating mode, must be one of the BSP_PRV_OPERATING_MODE_* macros
 **********************************************************************************************************************/
void bsp_prv_operating_mode_set (uint8_t operating_mode)
{
 #if BSP_PRV_POWER_USE_DCDC
    static bsp_power_mode_t power_mode = BSP_POWER_MODE_LDO;

    /* Disable DCDC if transitioning to an incompatible mode. */
    if ((operating_mode > BSP_PRV_OPERATING_MODE_MIDDLE_SPEED) && (R_SYSTEM->DCDCCTL & R_SYSTEM_DCDCCTL_DCDCON_Msk))
    {
        /* LDO boost must be used if entering subclock speed mode (see RA2L1 User's Manual (R01UH0853EJ0100) Section
         * 10.5.1 (5) Switching from High-speed/Middle-speed mode in DCDC power mode to Subosc-speed mode or Software
         * Standby mode). */
        power_mode = R_BSP_PowerModeSet((BSP_PRV_OPERATING_MODE_SUBOSC_SPEED == operating_mode) ?
                                        BSP_POWER_MODE_LDO_BOOST : BSP_POWER_MODE_LDO);
    }
 #endif

 #if BSP_FEATURE_CGC_HAS_SOPCCR
    if (BSP_PRV_OPERATING_MODE_SUBOSC_SPEED == operating_mode)
    {
        /* Wait for transition to complete. */
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->SOPCCR_b.SOPCMTSF, 0U);

        /* Set subosc speed mode. */
        R_SYSTEM->SOPCCR = 0x1U;

        /* Wait for transition to complete. */
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->SOPCCR_b.SOPCMTSF, 0U);
    }
    else
 #endif
    {
 #if BSP_FEATURE_CGC_HAS_SOPCCR

        /* Wait for transition to complete. */
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->SOPCCR_b.SOPCMTSF, 0U);

        /* Exit subosc speed mode first. */
        R_SYSTEM->SOPCCR = 0U;

        /* Wait for transition to complete. Check the entire register here since it should be set to 0 at this point.
         * Checking the entire register is slightly more efficient. This will also hang the program if the LPM
         * registers are not unlocked, which can help catch programming errors. */
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->SOPCCR, 0U);
 #endif

        bsp_prv_operating_mode_opccr_set(operating_mode);
    }

 #if BSP_PRV_POWER_USE_DCDC

    /* Enable DCDC if it was previously enabled. */
    if ((operating_mode <= BSP_PRV_OPERATING_MODE_MIDDLE_SPEED) && (power_mode < BSP_POWER_MODE_LDO))
    {
        R_BSP_PowerModeSet(power_mode);
        power_mode = BSP_POWER_MODE_LDO;
    }
 #endif
}

#endif

#if BSP_PRV_PLL_SUPPORTED

/***********************************************************************************************************************
 * Updates the operating frequency of the PLL.
 *
 * @param[in] pll_freq_hz              New frequency of the PLL after the PLL is configured
 **********************************************************************************************************************/
void bsp_prv_prepare_pll (uint32_t pll_freq_hz)
{
    /* Store the PLL frequency, which is required to update SystemCoreClock after switching to PLL. */
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL] = pll_freq_hz;
}

#endif

/*******************************************************************************************************************//**
 * Update SystemCoreClock variable based on current clock settings.
 **********************************************************************************************************************/
void SystemCoreClockUpdate (void)
{
#if BSP_FEATURE_TZ_HAS_TRUSTZONE && (BSP_TZ_SECURE_BUILD || BSP_TZ_NONSECURE_BUILD) && BSP_FEATURE_TZ_VERSION == 2
    bool secure = !R_SYSTEM->CGFSAR_b.NONSEC00;
#endif

    uint32_t clock_index = FSP_STYPE3_REG8_READ(R_SYSTEM->SCKSCR, secure);

#if !BSP_FEATURE_CGC_HAS_CPUCLK
    uint32_t ick =
        (FSP_STYPE3_REG32_READ(R_SYSTEM->SCKDIVCR, secure) & R_SYSTEM_SCKDIVCR_ICK_Msk) >> R_SYSTEM_SCKDIVCR_ICK_Pos;
    SystemCoreClock = g_clock_freq[clock_index] >> ick;
#else
    uint8_t cpuck = (FSP_STYPE3_REG8_READ(R_SYSTEM->SCKDIVCR2, secure) & R_SYSTEM_SCKDIVCR2_CPUCK_Msk) >>
                    R_SYSTEM_SCKDIVCR2_CPUCK_Pos;
    uint8_t cpuclk_div = cpuck;

    if (8U == cpuclk_div)
    {
        SystemCoreClock = g_clock_freq[clock_index] / 3U;
    }
    else if (9U == cpuclk_div)
    {
        SystemCoreClock = g_clock_freq[clock_index] / 6U;
    }
    else if (10U == cpuclk_div)
    {
        SystemCoreClock = g_clock_freq[clock_index] / 12U;
    }
    else
    {
        SystemCoreClock = g_clock_freq[clock_index] >> cpuclk_div;
    }
#endif
}

#if BSP_FEATURE_LPM_CHANGE_MSTP_REQUIRED

/*******************************************************************************************************************//**
 * Sets MSTP bits as required by the hardware manual for the MCU (reference Figure 9.2 "Example flow for changing the
 * value of SCKDIVCR" in the RA6M3 manual R01UH0886EJ0100).
 *
 * This function must be called before entering standby or changing SCKDIVCR.
 *
 * @return bitmask of bits set, where each bit corresponds to an index in g_bsp_prv_power_change_mstp_data
 **********************************************************************************************************************/
uint32_t bsp_prv_power_change_mstp_set (void)
{
    uint32_t mstp_set_bitmask = 0U;
    for (uint32_t i = 0U; i < g_bsp_prv_power_change_mstp_length; i++)
    {
        /* Get the MSTP register index and the bit to test from the MCU specific array. */
        uint32_t mstp_index = g_bsp_prv_power_change_mstp_data[i][0];
        uint32_t mstp_bit   = 1U << g_bsp_prv_power_change_mstp_data[i][1];

        /* Only set the bit if it's currently cleared. */
        if (!(gp_bsp_prv_mstp[mstp_index] & mstp_bit))
        {
            gp_bsp_prv_mstp[mstp_index] |= mstp_bit;
            mstp_set_bitmask            |= 1U << i;
        }

        /* This loop takes over 250 ns (30 cycles at 120 MHz) between 2 consecutive bits being set. It was measured
         * at 58 cycles for default IAR build configurations and 59 cycles for default GCC build configurations. */
    }

    /* The time between setting last MSTP bit and setting SCKDIVCR takes over 750 ns (90 cycles at 120 MHz). It was
     * measured at 96 cycles for default IAR build configurations and 102 cycles for default GCC build
     * configurations. */

    return mstp_set_bitmask;
}

#endif

#if BSP_FEATURE_LPM_CHANGE_MSTP_REQUIRED

/*******************************************************************************************************************//**
 * Clears MSTP bits set by bsp_prv_power_change_mstp_set as required by the hardware manual for the MCU (reference
 * Figure 9.2 "Example flow for changing the value of SCKDIVCR" in the RA6M3 manual R01UH0886EJ0100).
 *
 * This function must be called after exiting standby or changing SCKDIVCR.
 *
 * @param[in] mstp_clear_bitmask       bitmask of bits to clear, where each bit corresponds to an index in
 *                                     g_bsp_prv_power_change_mstp_data
 **********************************************************************************************************************/
void bsp_prv_power_change_mstp_clear (uint32_t mstp_clear_bitmask)
{
    /* The time between setting SCKDIVCR and clearing the first MSTP bit takes over 250 ns (30 cycles at 120 MHz). It
     * was measured at 38 cycles for default IAR build configurations and 68 cycles for default GCC build
     * configurations. */

    for (uint32_t i = 0U; i < g_bsp_prv_power_change_mstp_length; i++)
    {
        /* Only clear the bit if it was set in bsp_prv_power_change_mstp_set. */
        if ((1U << i) & mstp_clear_bitmask)
        {
            /* Get the MSTP register index and the bit to test from the MCU specific array. */
            uint32_t mstp_index = g_bsp_prv_power_change_mstp_data[i][0];
            uint32_t mstp_bit   = 1U << g_bsp_prv_power_change_mstp_data[i][1];

            gp_bsp_prv_mstp[mstp_index] &= ~mstp_bit;
        }

        /* This loop takes over 250 ns (30 cycles at 120 MHz) between 2 consecutive bits being cleared. It was measured
         * at 44 cycles for default IAR build configurations and 53 cycles for default GCC build configurations. */
    }
}

#endif

/*******************************************************************************************************************//**
 * Write SCKDIVCR and SCKDIVCR2 in the correct order to ensure that CPUCLK frequency is greater than ICLK frequency.
 *
 * @param[in] sckdivcr                 The new SCKDIVCR setting.
 * @param[in] sckdivcr2                The new SCKDIVCR2 setting.
 **********************************************************************************************************************/
void prv_clock_dividers_set (uint32_t sckdivcr, uint8_t sckdivcr2)
{
#if BSP_FEATURE_CGC_HAS_CPUCLK
    uint32_t requested_iclk_div = BSP_PRV_SCKDIVCR_DIV_VALUE(
        (sckdivcr >> FSP_PRIV_CLOCK_ICLK) & FSP_PRV_SCKDIVCR_DIV_MASK);
    uint32_t current_iclk_div = BSP_PRV_SCKDIVCR_DIV_VALUE(R_SYSTEM->SCKDIVCR_b.ICK);

    if (requested_iclk_div >= current_iclk_div)
    {
        /* If the requested ICLK divider is greater than or equal to the current ICLK divider, then writing to
         * SCKDIVCR first will always satisfy the constraint: CPUCLK frequency >= ICLK frequency. */
        R_SYSTEM->SCKDIVCR  = sckdivcr;
        R_SYSTEM->SCKDIVCR2 = sckdivcr2;
    }
    else
    {
        /* If the requested ICLK divider is less than the current ICLK divider, then writing to SCKDIVCR2 first
         * will always satisfy the constraint: CPUCLK frequency >= ICLK frequency. */
        R_SYSTEM->SCKDIVCR2 = sckdivcr2;
        R_SYSTEM->SCKDIVCR  = sckdivcr;
    }

#else
    FSP_PARAMETER_NOT_USED(sckdivcr2);

    R_SYSTEM->SCKDIVCR = sckdivcr;
#endif
}

/*******************************************************************************************************************//**
 * Applies system core clock source and divider changes.  The MCU is expected to be in high speed mode during this
 * configuration and the CGC registers are expected to be unlocked in PRCR.
 *
 * @param[in] clock                    Desired system clock
 * @param[in] sckdivcr                 Value to set in SCKDIVCR register
 * @param[in] sckdivcr2                Value to set in SCKDIVCR2 register
 **********************************************************************************************************************/
void bsp_prv_clock_set (uint32_t clock, uint32_t sckdivcr, uint8_t sckdivcr2)
{
#if BSP_FEATURE_LPM_CHANGE_MSTP_REQUIRED

    /* Set MSTP bits as required by the hardware manual. This is done first to ensure the 750 ns delay required after
     * increasing any division ratio in SCKDIVCR is met. */
    uint32_t mstp_set_bitmask = bsp_prv_power_change_mstp_set();
#endif

    uint32_t iclk_div = (sckdivcr >> FSP_PRIV_CLOCK_ICLK) & FSP_PRV_SCKDIVCR_DIV_MASK;

    /* Adjust the MCU specific wait state right before the system clock is set, if the system clock frequency to be
     * set is higher than before. */
    uint32_t clock_freq_hz_post_change = g_clock_freq[clock] / BSP_PRV_SCKDIVCR_DIV_VALUE(iclk_div);
    uint8_t  new_rom_wait_state        = bsp_clock_set_prechange(clock_freq_hz_post_change);

    /* Switching to a faster source clock. */
    if (g_clock_freq[clock] >= g_clock_freq[R_SYSTEM->SCKSCR])
    {
#if BSP_CFG_CLOCK_SETTLING_DELAY_ENABLE
        bool post_div_set_delay = false;

        if ((clock_freq_hz_post_change > SystemCoreClock) &&
            ((clock_freq_hz_post_change - SystemCoreClock) > BSP_MAX_CLOCK_CHANGE_THRESHOLD))
        {
            /* If the requested ICLK divider is greater than or equal to the current ICLK divider, then writing to
             * SCKDIVCR first will always satisfy the constraint: CPUCLK frequency >= ICLK frequency. */
            if (iclk_div == sckdivcr2)
            {
                /* If dividers are equal, bump both down 1 notch.
                 * /1 and /2 are the only possible options. */
                uint32_t new_div = BSP_CLOCKS_SYS_CLOCK_DIV_2;
                if (BSP_CFG_CPUCLK_DIV == BSP_CLOCKS_SYS_CLOCK_DIV_1)
                {
                    new_div = BSP_CLOCKS_SYS_CLOCK_DIV_4;
                }

                R_SYSTEM->SCKDIVCR = (BSP_PRV_STARTUP_SCKDIVCR & ~(R_SYSTEM_SCKDIVCR_ICK_Msk)) |
                                     (new_div << R_SYSTEM_SCKDIVCR_ICK_Pos);
                R_SYSTEM->SCKDIVCR2 = (uint8_t) new_div;
            }
            else
            {
                R_SYSTEM->SCKDIVCR = BSP_PRV_STARTUP_SCKDIVCR;
                if (BSP_CFG_CPUCLK_DIV == BSP_CLOCKS_SYS_CLOCK_DIV_1)
                {
                    /* Determine what the other dividers are using and stay aligned with that. */
                    R_SYSTEM->SCKDIVCR2 =
                        (BSP_CFG_ICLK_DIV & 0x8) ? BSP_CLOCKS_SYS_CLOCK_DIV_3 : BSP_CLOCKS_SYS_CLOCK_DIV_2;
                }
                else
                {
                    /* If not /1, can just add 1 to it. */
                    R_SYSTEM->SCKDIVCR2 = BSP_PRV_STARTUP_SCKDIVCR2 + 1;
                }
            }

            /* Set the system source clock */
            R_SYSTEM->SCKSCR = BSP_CFG_CLOCK_SOURCE;

            /* Wait for settling delay. */
            SystemCoreClockUpdate();
            R_BSP_SoftwareDelay(BSP_CFG_CLOCK_SETTLING_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);

            /* Trigger delay after setting dividers */
            post_div_set_delay = true;
        }
        /* Continue and set clock to actual target speed. */
#endif

        /* Set the clock dividers before switching to the new clock source. */
        prv_clock_dividers_set(sckdivcr, sckdivcr2);

#if BSP_CFG_CLOCK_SETTLING_DELAY_ENABLE
        if (post_div_set_delay)
        {
            /* Update the CMSIS core clock variable so that it reflects the new ICLK frequency. */
            SystemCoreClock = clock_freq_hz_post_change;

            /* Wait for settling delay. */
            R_BSP_SoftwareDelay(BSP_CFG_CLOCK_SETTLING_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);
        }
        else
#endif
        {
            /* Switch to the new clock source. */
            R_SYSTEM->SCKSCR = (uint8_t) clock;
        }
    }
    /* Switching to a slower source clock. */
    else
    {
#if BSP_CFG_CLOCK_SETTLING_DELAY_ENABLE
        if ((SystemCoreClock > clock_freq_hz_post_change) &&
            ((SystemCoreClock - clock_freq_hz_post_change) > BSP_MAX_CLOCK_CHANGE_THRESHOLD))
        {
            uint32_t current_sckdivcr = R_SYSTEM->SCKDIVCR;

            /* Must first step CPUCLK down by factor of 2 or 3 if it is currently above threshold. */
            if (R_SYSTEM->SCKDIVCR2 == ((current_sckdivcr >> R_SYSTEM_SCKDIVCR_ICK_Pos) & 0xF))
            {
                /* If ICLK and CPUCLK have same divider currently, move ICLK down 1 notch first. */
                uint32_t current_iclk_div = (current_sckdivcr >> R_SYSTEM_SCKDIVCR_ICK_Pos) & 0xF;
                uint32_t new_div          = current_iclk_div + 1;
                if (current_iclk_div == 0)
                {
                    /* Align with already selected divider for PCLKA because it must have one > 1 already. */
                    new_div =
                        (current_sckdivcr &
                         (0x8 << R_SYSTEM_SCKDIVCR_PCKA_Pos)) ? BSP_CLOCKS_SYS_CLOCK_DIV_3 : BSP_CLOCKS_SYS_CLOCK_DIV_2;
                }

                R_BSP_SoftwareDelay(BSP_CFG_CLOCK_SETTLING_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);
                R_SYSTEM->SCKDIVCR = (current_sckdivcr & ~(R_SYSTEM_SCKDIVCR_ICK_Msk)) |
                                     (new_div << R_SYSTEM_SCKDIVCR_ICK_Pos);
                R_SYSTEM->SCKDIVCR2 = (uint8_t) new_div;

                SystemCoreClockUpdate();
            }
        }
        R_BSP_SoftwareDelay(BSP_CFG_CLOCK_SETTLING_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);
#endif
        R_SYSTEM->SCKSCR = (uint8_t) clock;

        /* Set the clock dividers after switching to the new clock source. */
        prv_clock_dividers_set(sckdivcr, sckdivcr2);
    }

    /* Clock is now at requested frequency. */

    /* Update the CMSIS core clock variable so that it reflects the new ICLK frequency. */
    SystemCoreClock = clock_freq_hz_post_change;

#if BSP_TZ_SECURE_BUILD
    if (NULL != g_bsp_clock_update_callback)
    {
        /* Set callback args. */
        bsp_clock_update_callback_args_t callback_args =
        {
            .pll_freq = g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL]
        };

        /* Call the callback. */
        r_bsp_clock_update_callback_call(g_bsp_clock_update_callback, &callback_args);
    }
#endif

    /* Adjust the MCU specific wait state soon after the system clock is set, if the system clock frequency to be
     * set is lower than previous. */
    bsp_clock_set_postchange(SystemCoreClock, new_rom_wait_state);

#if BSP_FEATURE_LPM_CHANGE_MSTP_REQUIRED

    /* Clear MSTP bits as required by the hardware manual. This is done last to ensure the 250 ns delay required after
     * decreasing any division ratio in SCKDIVCR is met. */
    bsp_prv_power_change_mstp_clear(mstp_set_bitmask);
#endif
}

#if BSP_CFG_SLEEP_MODE_DELAY_ENABLE || BSP_CFG_RTOS_SLEEP_MODE_DELAY_ENABLE

bool bsp_prv_clock_prepare_pre_sleep (void)
{
    /* Must wait before entering or exiting sleep modes.
     * See Section 10.7.10 in RA8M1 manual R01UH0994EJ0100 */
    R_BSP_SoftwareDelay(BSP_CFG_CLOCK_SETTLING_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);

    /* Need to slow CPUCLK down before sleeping if it is above 240MHz. */
    bool cpuclk_slowed = false;
    if (SystemCoreClock > BSP_MAX_CLOCK_CHANGE_THRESHOLD)
    {
        /* Reduce speed of CPUCLK to /2 or /3 of current, select which ones based on what ICLK divider is. */
        R_SYSTEM->SCKDIVCR2 =
            (R_SYSTEM->SCKDIVCR &
             (0x8 << R_SYSTEM_SCKDIVCR_ICK_Pos)) ? BSP_CLOCKS_SYS_CLOCK_DIV_3 : BSP_CLOCKS_SYS_CLOCK_DIV_2;
        cpuclk_slowed = true;
        SystemCoreClockUpdate();
        R_BSP_SoftwareDelay(BSP_CFG_CLOCK_SETTLING_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);
    }

    return cpuclk_slowed;
}

void bsp_prv_clock_prepare_post_sleep (bool cpuclk_slowed)
{
    /* Set CPUCLK back to original speed here if it was slowed down before sleeping (dropped to below 240MHz)
     * Add delays as described in Section 10.7.10 of RA8M1 manual R01UH0994EJ0100 */
    R_BSP_SoftwareDelay(BSP_CFG_CLOCK_SETTLING_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);
    if (cpuclk_slowed)
    {
        /* Set divider of CPUCLK back to /1. This is the only possible value for it to have been over 240MHz before sleeping. */
        R_SYSTEM->SCKDIVCR2 = BSP_CLOCKS_SYS_CLOCK_DIV_1;
        SystemCoreClockUpdate();
        R_BSP_SoftwareDelay(BSP_CFG_CLOCK_SETTLING_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);
    }
}

#endif

#if !BSP_CFG_STARTUP_CLOCK_REG_NOT_RESET

static void bsp_prv_clock_set_hard_reset (void)
{
    /* Wait states in SRAMWTSC are set after hard reset. No change required here. */

    /* Calculate the wait states for ROM */
 #if BSP_FEATURE_CGC_HAS_FLWT
  #if BSP_STARTUP_ICLK_HZ <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_ONE_ROM_WAITS

    /* Do nothing. Default setting in FLWT is correct. */
  #elif BSP_STARTUP_ICLK_HZ <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_TWO_ROM_WAITS || \
    BSP_FEATURE_BSP_SYS_CLOCK_FREQ_TWO_ROM_WAITS == 0
    R_FCACHE->FLWT = BSP_PRV_ROM_ONE_WAIT_CYCLES;
  #elif 0 == BSP_FEATURE_BSP_SYS_CLOCK_FREQ_THREE_ROM_WAITS || \
    (BSP_STARTUP_ICLK_HZ <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_THREE_ROM_WAITS)
    R_FCACHE->FLWT = BSP_PRV_ROM_TWO_WAIT_CYCLES;
  #elif 0 == BSP_FEATURE_BSP_SYS_CLOCK_FREQ_FOUR_ROM_WAITS || \
    (BSP_STARTUP_ICLK_HZ <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_FOUR_ROM_WAITS)
    R_FCACHE->FLWT = BSP_PRV_ROM_THREE_WAIT_CYCLES;
  #elif 0 == BSP_FEATURE_BSP_SYS_CLOCK_FREQ_FIVE_ROM_WAITS || \
    (BSP_STARTUP_ICLK_HZ <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_FIVE_ROM_WAITS)
    R_FCACHE->FLWT = BSP_PRV_ROM_FOUR_WAIT_CYCLES;
  #else
    R_FCACHE->FLWT = BSP_PRV_ROM_FIVE_WAIT_CYCLES;
  #endif
 #endif

 #if BSP_FEATURE_CGC_HAS_MEMWAIT && !BSP_PRV_CLOCK_SUPPLY_TYPE_B
  #if BSP_STARTUP_ICLK_HZ > BSP_PRV_MEMWAIT_MAX_ZERO_WAIT_FREQ

    /* The MCU must be in high speed mode to set wait states to 2. High speed mode is the default out of reset. */
    R_SYSTEM->MEMWAIT = BSP_PRV_MEMWAIT_TWO_WAIT_CYCLES;
  #endif
 #endif

 #if BSP_FEATURE_CGC_HAS_FLDWAITR && !BSP_PRV_CLOCK_SUPPLY_TYPE_B
  #if BSP_STARTUP_ICLK_HZ > BSP_PRV_FLDWAITR_MAX_ONE_WAIT_FREQ

    /* The MCU must be in high speed mode to set wait states to 2. High speed mode is the default out of reset. */
    BSP_PRV_FLDWAITR_REG_ACCESS = BSP_PRV_FLDWAITR_TWO_WAIT_CYCLES;
  #endif
 #endif

    /* In order to avoid a system clock (momentarily) higher than expected, the order of switching the clock and
     * dividers must be so that the frequency of the clock goes lower, instead of higher, before being correct. */

    /* MOCO is the source clock after reset. If the new source clock is faster than the current source clock,
     * then set the clock dividers before switching to the new source clock. */
 #if BSP_MOCO_FREQ_HZ <= BSP_STARTUP_SOURCE_CLOCK_HZ
  #if BSP_FEATURE_CGC_HAS_CPUCLK
   #if BSP_CFG_CLOCK_SETTLING_DELAY_ENABLE && (BSP_STARTUP_CPUCLK_HZ >= BSP_MAX_CLOCK_CHANGE_THRESHOLD)

    /* If the requested ICLK divider is greater than or equal to the current ICLK divider, then writing to
     * SCKDIVCR first will always satisfy the constraint: CPUCLK frequency >= ICLK frequency. */
    #if BSP_CFG_ICLK_DIV == BSP_CFG_CPUCLK_DIV

    /* If dividers are equal, bump both down 1 notch.
     * /1 and /2 are the only possible options. */
     #if BSP_CFG_CPUCLK_DIV == BSP_CLOCKS_SYS_CLOCK_DIV_1
    R_SYSTEM->SCKDIVCR = (BSP_PRV_STARTUP_SCKDIVCR & ~(R_SYSTEM_SCKDIVCR_ICK_Msk)) |
                         (BSP_CLOCKS_SYS_CLOCK_DIV_2 << R_SYSTEM_SCKDIVCR_ICK_Pos);
    R_SYSTEM->SCKDIVCR2 = BSP_CLOCKS_SYS_CLOCK_DIV_2;
     #else
    R_SYSTEM->SCKDIVCR = (BSP_PRV_STARTUP_SCKDIVCR & ~(R_SYSTEM_SCKDIVCR_ICK_Msk)) |
                         (BSP_CLOCKS_SYS_CLOCK_DIV_4 << R_SYSTEM_SCKDIVCR_ICK_Pos);
    R_SYSTEM->SCKDIVCR2 = BSP_CLOCKS_SYS_CLOCK_DIV_4;
     #endif
    #else
    R_SYSTEM->SCKDIVCR = BSP_PRV_STARTUP_SCKDIVCR;
     #if BSP_CFG_CPUCLK_DIV == BSP_CLOCKS_SYS_CLOCK_DIV_1

    /* Determine what the other dividers are using and stay aligned with that. */
    R_SYSTEM->SCKDIVCR2 = (BSP_CFG_ICLK_DIV & 0x8) ? BSP_CLOCKS_SYS_CLOCK_DIV_3 : BSP_CLOCKS_SYS_CLOCK_DIV_2;
     #else

    /* If not /1, can just add 1 to it. */
    R_SYSTEM->SCKDIVCR2 = BSP_PRV_STARTUP_SCKDIVCR2 + 1;
     #endif
    #endif

    /* Set the system source clock */
    R_SYSTEM->SCKSCR = BSP_CFG_CLOCK_SOURCE;

    /* Wait for settling delay. */
    SystemCoreClockUpdate();
    R_BSP_SoftwareDelay(BSP_CFG_CLOCK_SETTLING_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);

    /* Continue and set clock to actual target speed. */
    R_SYSTEM->SCKDIVCR2 = BSP_PRV_STARTUP_SCKDIVCR2;
    R_SYSTEM->SCKDIVCR  = BSP_PRV_STARTUP_SCKDIVCR;

    /* Wait for settling delay. */
    SystemCoreClockUpdate();
    R_BSP_SoftwareDelay(BSP_CFG_CLOCK_SETTLING_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);
   #else
    #if BSP_PRV_ICLK_DIV_VALUE >= BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_FEATURE_CGC_ICLK_DIV_RESET)

    /* If the requested ICLK divider is greater than or equal to the current ICLK divider, then writing to
     * SCKDIVCR first will always satisfy the constraint: CPUCLK frequency >= ICLK frequency. */
    R_SYSTEM->SCKDIVCR  = BSP_PRV_STARTUP_SCKDIVCR;
    R_SYSTEM->SCKDIVCR2 = BSP_PRV_STARTUP_SCKDIVCR2;
    #else

    /* If the requested ICLK divider is less than the current ICLK divider, then writing to SCKDIVCR2 first
     * will always satisfy the constraint: CPUCLK frequency >= ICLK frequency. */
    R_SYSTEM->SCKDIVCR2 = BSP_PRV_STARTUP_SCKDIVCR2;
    R_SYSTEM->SCKDIVCR  = BSP_PRV_STARTUP_SCKDIVCR;
    #endif
   #endif
  #else
    R_SYSTEM->SCKDIVCR = BSP_PRV_STARTUP_SCKDIVCR;
  #endif
 #endif

    /* Set the system source clock */
    R_SYSTEM->SCKSCR = BSP_CFG_CLOCK_SOURCE;

    /* MOCO is the source clock after reset. If the new source clock is slower than the current source clock,
     * then set the clock dividers after switching to the new source clock. */
 #if BSP_MOCO_FREQ_HZ > BSP_STARTUP_SOURCE_CLOCK_HZ
  #if BSP_FEATURE_CGC_HAS_CPUCLK
   #if BSP_PRV_ICLK_DIV_VALUE >= BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_FEATURE_CGC_ICLK_DIV_RESET)

    /* If the requested ICLK divider is greater than or equal to the current ICLK divider, then writing to
     * SCKDIVCR first will always satisfy the constraint: CPUCLK frequency >= ICLK frequency. */
    R_SYSTEM->SCKDIVCR  = BSP_PRV_STARTUP_SCKDIVCR;
    R_SYSTEM->SCKDIVCR2 = BSP_PRV_STARTUP_SCKDIVCR2;
   #else

    /* If the requested ICLK divider is less than the current ICLK divider, then writing to SCKDIVCR2 first
     * will always satisfy the constraint: CPUCLK frequency >= ICLK frequency. */
    R_SYSTEM->SCKDIVCR2 = BSP_PRV_STARTUP_SCKDIVCR2;
    R_SYSTEM->SCKDIVCR  = BSP_PRV_STARTUP_SCKDIVCR;
   #endif
  #else
    R_SYSTEM->SCKDIVCR = BSP_PRV_STARTUP_SCKDIVCR;
  #endif
 #endif

    /* Update the CMSIS core clock variable so that it reflects the new ICLK frequency. */
    SystemCoreClockUpdate();

    /* Clocks are now at requested frequencies. */

    /* Adjust the MCU specific wait state soon after the system clock is set, if the system clock frequency to be
     * set is lower than previous. */
 #if BSP_FEATURE_CGC_HAS_SRAMWTSC
  #if BSP_STARTUP_ICLK_HZ <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_NO_RAM_WAITS
   #if BSP_FEATURE_CGC_HAS_SRAMPRCR2 == 1
    R_SRAM->SRAMPRCR2 = BSP_PRV_SRAM_UNLOCK;
    R_SRAM->SRAMWTSC  = BSP_PRV_SRAMWTSC_WAIT_CYCLES_DISABLE;
    R_SRAM->SRAMPRCR2 = BSP_PRV_SRAM_LOCK;
   #else
    R_SRAM->SRAMPRCR = BSP_PRV_SRAM_UNLOCK;

    /* Execute data memory barrier before and after setting the wait states, See Section 50.4.2 in the RA8M1
     * manual R01UH0994EJ0100 */
    __DMB();
    R_SRAM->SRAMWTSC = BSP_PRV_SRAMWTSC_WAIT_CYCLES_DISABLE;
    __DMB();

    R_SRAM->SRAMPRCR = BSP_PRV_SRAM_LOCK;
   #endif
  #endif
 #endif

    /* ROM wait states are 0 by default.  No change required here. */
}

#endif

/*******************************************************************************************************************//**
 * Initializes variable to store system clock frequencies.
 **********************************************************************************************************************/
#if BSP_TZ_NONSECURE_BUILD
void bsp_clock_freq_var_init (void)
#else
static void bsp_clock_freq_var_init (void)
#endif
{
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_HOCO] = BSP_HOCO_HZ;
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_MOCO] = BSP_MOCO_FREQ_HZ;
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_LOCO] = BSP_LOCO_FREQ_HZ;
#if BSP_CLOCK_CFG_MAIN_OSC_POPULATED
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC] = BSP_CFG_XTAL_HZ;
#else
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC] = 0U;
#endif
#if BSP_CLOCK_CFG_SUBCLOCK_POPULATED
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK] = BSP_SUBCLOCK_FREQ_HZ;
#else
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK] = 0U;
#endif
#if BSP_PRV_PLL_SUPPORTED
 #if BSP_CLOCKS_SOURCE_CLOCK_PLL == BSP_CFG_CLOCK_SOURCE
  #if (3U != BSP_FEATURE_CGC_PLLCCR_TYPE)

    /* The PLL Is the startup clock. */
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL] = BSP_STARTUP_SOURCE_CLOCK_HZ;
  #else
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL]   = BSP_CFG_PLL1P_FREQUENCY_HZ;
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL1Q] = BSP_CFG_PLL1Q_FREQUENCY_HZ;
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL1R] = BSP_CFG_PLL1R_FREQUENCY_HZ;
  #endif
 #else

    /* The PLL value will be calculated at initialization. */
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL] = BSP_CFG_XTAL_HZ;
 #endif
#endif

#if BSP_TZ_NONSECURE_BUILD && BSP_CFG_CLOCKS_SECURE == 1

    /* If the CGC is secure and this is a non secure project, register a callback for getting clock settings. */
    R_BSP_ClockUpdateCallbackSet(g_bsp_clock_update_callback, &g_callback_memory);
#endif

    /* Update PLL Clock Frequency based on BSP Configuration. */
#if BSP_PRV_PLL_SUPPORTED && BSP_CLOCKS_SOURCE_CLOCK_PLL != BSP_CFG_CLOCK_SOURCE && BSP_PRV_PLL_USED
 #if (1U == BSP_FEATURE_CGC_PLLCCR_TYPE)
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL] = ((g_clock_freq[BSP_CFG_PLL_SOURCE] * (BSP_CFG_PLL_MUL + 1U)) >> 1U) /
                                                (BSP_CFG_PLL_DIV + 1U);
 #elif (3U == BSP_FEATURE_CGC_PLLCCR_TYPE)
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL]   = BSP_CFG_PLL1P_FREQUENCY_HZ;
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL1Q] = BSP_CFG_PLL1Q_FREQUENCY_HZ;
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL1R] = BSP_CFG_PLL1R_FREQUENCY_HZ;
 #elif (4U == BSP_FEATURE_CGC_PLLCCR_TYPE)
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL] = (g_clock_freq[BSP_CFG_PLL_SOURCE] * (BSP_CFG_PLL_MUL + 1U)) >> 1U;
 #else
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL] = ((g_clock_freq[BSP_CFG_PLL_SOURCE] * (BSP_CFG_PLL_MUL + 1U)) >> 1U) >>
                                                BSP_CFG_PLL_DIV;
 #endif
#endif

    /* Update PLL2 Clock Frequency based on BSP Configuration. */
#if BSP_PRV_PLL2_SUPPORTED && BSP_PRV_PLL2_USED
 #if (1U == BSP_FEATURE_CGC_PLLCCR_TYPE)
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL2] = ((g_clock_freq[BSP_CFG_PLL2_SOURCE] * (BSP_CFG_PLL2_MUL + 1U)) >> 1U) /
                                                 (BSP_CFG_PLL2_DIV + 1U);
 #elif (3U == BSP_FEATURE_CGC_PLLCCR_TYPE)
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL2]  = BSP_CFG_PLL2P_FREQUENCY_HZ;
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL2Q] = BSP_CFG_PLL2Q_FREQUENCY_HZ;
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL2R] = BSP_CFG_PLL2R_FREQUENCY_HZ;
 #else
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL2] =
        ((g_clock_freq[BSP_CFG_PLL2_SOURCE] * (BSP_CFG_PLL2_MUL + 1U)) >> 1U) >> BSP_CFG_PLL2_DIV;
 #endif
#endif

    /* The SystemCoreClock needs to be updated before calling R_BSP_SoftwareDelay. */
    SystemCoreClockUpdate();
}

#if BSP_CFG_STARTUP_CLOCK_REG_NOT_RESET

/*
 * If the clock registers are not guaranteed to be set to their value after reset (Ie. the application is executing after a bootloader),
 * then the current state of the registers must be taken into consideration before writing the clock configuration.
 *
 * The HOCO must be stopped in the following situations:
 *  - The application configures the HOCO to be stopped.
 *  - The application enables the FLL, but the HOCO is already running. In order to enable the FLL, the HOCO must be stopped.
 * The PLL must be stopped in the following situations:
 *  - The application configures the PLL to be stopped.
 *  - The application configures settings that are different than the current settings, but the PLL is already running. In order to
 *    write new PLL settings, the PLL must be stopped.
 *  - The HOCO is the PLL source clock and the HOCO is being stopped.
 * The PLL2 must be stopped in the following situations:
 *  - The application configures the PLL2 to be stopped.
 *  - The application configures settings that are different than the current settings, but the PLL2 is already running. In order to
 *    write new PLL2 settings, the PLL2 must be stopped.
 *  - The HOCO is the PLL2 source clock and the HOCO is being stopped.
 *
 * If the HOCO or PLL are being used as the system clock source and they need to be stopped, then the system clock source needs to be switched
 * to the default system clock source before the current system clock source is disabled.
 */
void bsp_soft_reset_prepare (void)
{
    bool stop_hoco = false;
 #if BSP_PRV_PLL_SUPPORTED
    bool stop_pll = false;
 #endif
 #if BSP_PRV_PLL2_SUPPORTED
    bool stop_pll2 = false;
 #endif

 #if BSP_PRV_HOCO_USE_FLL || !BSP_PRV_HOCO_USED
  #if BSP_PRV_HOCO_USE_FLL

    /* Determine if the FLL needs to be enabled. */
    bool enable_fll = (0 == R_SYSTEM->FLLCR1 && BSP_PRV_HOCO_USE_FLL);
  #else
    bool enable_fll = false;
  #endif

    /* If the HOCO is already enabled and either the FLL needs to be enabled or the HOCO is not used, then stop the HOCO. */
    if ((0 == R_SYSTEM->HOCOCR) && (enable_fll || !BSP_PRV_HOCO_USED))
    {
        stop_hoco = true;
    }
 #endif

 #if BSP_PRV_PLL_SUPPORTED
    if (0 == R_SYSTEM->PLLCR)
    {
        /*
         * If any of the following conditions are true, then the PLL needs to be stopped:
         * - The PLL is not used
         * - The PLL settings need to be changed
         * - The HOCO is selected as the PLL clock source and the HOCO needs to be stopped
         *   - Note that PLL type 2 does not support running off of the HOCO
         */
  #if BSP_PRV_PLL_USED
   #if 3 == BSP_FEATURE_CGC_PLLCCR_TYPE
        if ((BSP_PRV_PLLCCR != R_SYSTEM->PLLCCR) || (BSP_PRV_PLLCCR2 != R_SYSTEM->PLLCCR2) ||
            (stop_hoco && (1 == R_SYSTEM->PLLCCR_b.PLSRCSEL)))
   #elif 2 == BSP_FEATURE_CGC_PLLCCR_TYPE
        if (BSP_PRV_PLLCCR != R_SYSTEM->PLLCCR2)
   #else
        if ((BSP_PRV_PLLCCR != R_SYSTEM->PLLCCR) || (stop_hoco && (1 == R_SYSTEM->PLLCCR_b.PLSRCSEL)))
   #endif
  #endif
        {
            stop_pll = true;
        }
    }
 #endif

 #if BSP_PRV_PLL2_SUPPORTED
    if (0 == R_SYSTEM->PLL2CR)
    {
        /*
         * If any of the following conditions are true, then the PLL2 needs to be stopped:
         * - The PLL2 is not used
         * - The PLL2 settings need to be changed
         * - The HOCO is selected as the PLL2 clock source and the HOCO needs to be stopped
         *   - Note that PLL type 2 does not support running off of the HOCO
         */
  #if BSP_PRV_PLL2_USED
   #if 3 == BSP_FEATURE_CGC_PLLCCR_TYPE
        if ((BSP_PRV_PLL2CCR != R_SYSTEM->PLL2CCR) || (BSP_PRV_PLL2CCR2 != R_SYSTEM->PLL2CCR2) ||
            (stop_hoco && (1 == R_SYSTEM->PLL2CCR_b.PL2SRCSEL)))
   #else
        if ((BSP_PRV_PLL2CCR != R_SYSTEM->PLL2CCR) || (stop_hoco && (1 == R_SYSTEM->PLL2CCR_b.PL2SRCSEL)))
   #endif
  #endif
        {
            stop_pll2 = true;
        }
    }
 #endif

    uint8_t sckscr = R_SYSTEM->SCKSCR;

    /* If the System Clock source needs to be stopped, then switch to the MOCO. */
 #if BSP_PRV_PLL_SUPPORTED
    if ((stop_hoco && (BSP_CLOCKS_SOURCE_CLOCK_HOCO == sckscr)) ||
        (stop_pll && (BSP_CLOCKS_SOURCE_CLOCK_PLL == sckscr)))
 #else
    if (stop_hoco && (BSP_CLOCKS_SOURCE_CLOCK_HOCO == sckscr))
 #endif
    {
        bsp_prv_clock_set(BSP_FEATURE_CGC_STARTUP_SCKSCR,
                          BSP_FEATURE_CGC_STARTUP_SCKDIVCR,
                          BSP_FEATURE_CGC_STARTUP_SCKDIVCR2);
    }

    /* Disable the oscillators so that the application can write the new clock configuration. */

 #if BSP_PRV_PLL_SUPPORTED
    if (stop_pll)
    {
        R_SYSTEM->PLLCR = 1;
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OSCSF_b.PLLSF, 0);
    }
 #endif

 #if BSP_PRV_PLL2_SUPPORTED
    if (stop_pll2)
    {
        R_SYSTEM->PLL2CR = 1;
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OSCSF_b.PLL2SF, 0);
    }
 #endif

    if (stop_hoco)
    {
        R_SYSTEM->HOCOCR = 1;
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OSCSF_b.HOCOSF, 0);
    }
}

#endif

/*******************************************************************************************************************//**
 * Initializes system clocks.  Makes no assumptions about current register settings.
 **********************************************************************************************************************/
void bsp_clock_init (void)
{
    /* Unlock CGC and LPM protection registers. */
#if BSP_FEATURE_TZ_VERSION == 2 && BSP_TZ_NONSECURE_BUILD == 1
    R_SYSTEM->PRCR_NS = (uint16_t) BSP_PRV_PRCR_UNLOCK;
#else
    R_SYSTEM->PRCR = (uint16_t) BSP_PRV_PRCR_UNLOCK;
#endif

#if BSP_FEATURE_BSP_FLASH_CACHE
 #if !BSP_CFG_USE_LOW_VOLTAGE_MODE && BSP_FEATURE_BSP_FLASH_CACHE_DISABLE_OPM

    /* Disable flash cache before modifying MEMWAIT, SOPCCR, or OPCCR. */
    R_BSP_FlashCacheDisable();
 #else

    /* Enable the flash cache and don't disable it while running from flash. On these MCUs, the flash cache does not
     * need to be disabled when adjusting the operating power mode. */
    R_BSP_FlashCacheEnable();
 #endif
#endif

#if BSP_FEATURE_BSP_FLASH_PREFETCH_BUFFER

    /* Disable the flash prefetch buffer. */
    R_FACI_LP->PFBER = 0;
#endif

    bsp_clock_freq_var_init();

#if BSP_CFG_STARTUP_CLOCK_REG_NOT_RESET

    /* Transition to an intermediate clock configuration in order to prepare for writing the new clock configuraiton. */
    bsp_soft_reset_prepare();
#endif

#if BSP_CLOCK_CFG_MAIN_OSC_POPULATED
 #if BSP_CFG_STARTUP_CLOCK_REG_NOT_RESET

    /* Update the main oscillator drive, source, and wait states if the main oscillator is stopped.  If the main
     * oscillator is running, the drive, source, and wait states are assumed to be already set appropriately. */
    if (R_SYSTEM->MOSCCR)
    {
        /* Don't write to MOSCWTCR unless MOSTP is 1 and MOSCSF = 0. */
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OSCSF_b.MOSCSF, 0U);

        /* Configure main oscillator drive. */
        R_SYSTEM->MOMCR = BSP_PRV_MOMCR;

        /* Set the main oscillator wait time. */
        R_SYSTEM->MOSCWTCR = (uint8_t) BSP_CLOCK_CFG_MAIN_OSC_WAIT;
    }

 #else

    /* Configure main oscillator drive. */
    R_SYSTEM->MOMCR = BSP_PRV_MOMCR;

    /* Set the main oscillator wait time. */
    R_SYSTEM->MOSCWTCR = (uint8_t) BSP_CLOCK_CFG_MAIN_OSC_WAIT;
 #endif
#endif

    /* Initialize the sub-clock according to the BSP configuration. */
    bsp_sosc_init();

#if BSP_FEATURE_CGC_HAS_HOCOWTCR
 #if BSP_FEATURE_CGC_HOCOWTCR_64MHZ_ONLY

    /* These MCUs only require writes to HOCOWTCR if HOCO is set to 64 MHz. */
  #if 64000000 == BSP_HOCO_HZ
   #if BSP_CFG_USE_LOW_VOLTAGE_MODE

    /* Wait for HOCO to stabilize before writing to HOCOWTCR. */
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OSCSF_b.HOCOSF, 1U);
   #else

    /* HOCO is assumed to be stable because these MCUs also require the HOCO to be stable before changing the operating
     * power control mode. */
   #endif
    R_SYSTEM->HOCOWTCR = BSP_FEATURE_CGC_HOCOWTCR_VALUE;
  #endif
 #else

    /* These MCUs require HOCOWTCR to be set to the maximum value except in snooze mode.  There is no restriction to
     * writing this register. */
    R_SYSTEM->HOCOWTCR = BSP_FEATURE_CGC_HOCOWTCR_VALUE;
 #endif
#endif

#if !BSP_CFG_USE_LOW_VOLTAGE_MODE
 #if BSP_CFG_STARTUP_CLOCK_REG_NOT_RESET

    /* Switch to high-speed to prevent any issues with the subsequent clock configurations. */
    bsp_prv_operating_mode_set(BSP_PRV_OPERATING_MODE_HIGH_SPEED);
 #elif BSP_FEATURE_CGC_LOW_VOLTAGE_MAX_FREQ_HZ > 0U

    /* MCUs that support low voltage mode start up in low voltage mode. */
    bsp_prv_operating_mode_opccr_set(BSP_PRV_OPERATING_MODE_HIGH_SPEED);

  #if !BSP_PRV_HOCO_USED

    /* HOCO must be running during startup in low voltage mode. If HOCO is not used, turn it off after exiting low
     * voltage mode. */
    R_SYSTEM->HOCOCR = 1U;
  #endif
 #elif BSP_FEATURE_CGC_STARTUP_OPCCR_MODE != BSP_PRV_OPERATING_MODE_HIGH_SPEED

    /* Some MCUs do not start in high speed mode. */
    bsp_prv_operating_mode_opccr_set(BSP_PRV_OPERATING_MODE_HIGH_SPEED);
 #endif
#endif

    /* The FLL function can only be used when the subclock is running. */
#if BSP_PRV_HOCO_USE_FLL

    /* If FLL is to be used configure FLLCR1 and FLLCR2 before starting HOCO. */
    R_SYSTEM->FLLCR2 = BSP_PRV_FLL_FLLCR2;
    R_SYSTEM->FLLCR1 = 1U;
#endif

    /* Start all clocks used by other clocks first. */
#if BSP_PRV_HOCO_USED
    R_SYSTEM->HOCOCR = 0U;

 #if BSP_PRV_HOCO_USE_FLL && (BSP_CLOCKS_SOURCE_CLOCK_HOCO != BSP_CFG_PLL_SOURCE)

    /* If FLL is enabled, wait for the FLL stabilization delay (1.8 ms) */
    R_BSP_SoftwareDelay(BSP_PRV_FLL_STABILIZATION_TIME_US, BSP_DELAY_UNITS_MICROSECONDS);
 #endif

 #if BSP_PRV_STABILIZE_HOCO

    /* Wait for HOCO to stabilize. */
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OSCSF_b.HOCOSF, 1U);
 #endif
#endif
#if BSP_PRV_MOCO_USED
 #if BSP_CFG_STARTUP_CLOCK_REG_NOT_RESET

    /* If the MOCO is not running, start it and wait for it to stabilize using a software delay. */
    if (0U != R_SYSTEM->MOCOCR)
    {
        R_SYSTEM->MOCOCR = 0U;
  #if BSP_PRV_STABILIZE_MOCO
        R_BSP_SoftwareDelay(BSP_FEATURE_CGC_MOCO_STABILIZATION_MAX_US, BSP_DELAY_UNITS_MICROSECONDS);
  #endif
    }
 #endif
#endif
#if BSP_PRV_LOCO_USED
 #if BSP_CFG_STARTUP_CLOCK_REG_NOT_RESET

    /* If the LOCO is not running, start it and wait for it to stabilize using a software delay. */
    if (0U != R_SYSTEM->LOCOCR)
    {
        R_SYSTEM->LOCOCR = 0U;
  #if BSP_PRV_STABILIZE_LOCO
        R_BSP_SoftwareDelay(BSP_FEATURE_CGC_LOCO_STABILIZATION_MAX_US, BSP_DELAY_UNITS_MICROSECONDS);
  #endif
    }

 #else
    R_SYSTEM->LOCOCR = 0U;
  #if BSP_PRV_STABILIZE_LOCO
    R_BSP_SoftwareDelay(BSP_FEATURE_CGC_LOCO_STABILIZATION_MAX_US, BSP_DELAY_UNITS_MICROSECONDS);
  #endif
 #endif
#endif
#if BSP_PRV_MAIN_OSC_USED
 #if BSP_CFG_STARTUP_CLOCK_REG_NOT_RESET
    if (R_SYSTEM->MOSCCR)
 #endif
    {
        R_SYSTEM->MOSCCR = 0U;

 #if BSP_PRV_STABILIZE_MAIN_OSC

        /* Wait for main oscillator to stabilize. */
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OSCSF_b.MOSCSF, 1U);
 #endif
    }
#endif

    /* Start clocks that require other clocks. At this point, all dependent clocks are running and stable if needed. */

#if BSP_PRV_STARTUP_OPERATING_MODE != BSP_PRV_OPERATING_MODE_LOW_SPEED
 #if BSP_FEATURE_CGC_HAS_PLL2 && BSP_CFG_PLL2_SOURCE != BSP_CLOCKS_CLOCK_DISABLED
  #if BSP_CFG_STARTUP_CLOCK_REG_NOT_RESET
    if (R_SYSTEM->PLL2CR)
  #endif
    {
        R_SYSTEM->PLL2CCR = BSP_PRV_PLL2CCR;
  #if (3U == BSP_FEATURE_CGC_PLLCCR_TYPE)
        R_SYSTEM->PLL2CCR2 = BSP_PRV_PLL2CCR2;
  #endif

        /* Start PLL2. */
        R_SYSTEM->PLL2CR = 0U;
    }
 #endif                                /* BSP_FEATURE_CGC_HAS_PLL2 && BSP_CFG_PLL2_ENABLE */
#endif

#if BSP_PRV_PLL_SUPPORTED && BSP_PRV_PLL_USED
 #if BSP_CFG_STARTUP_CLOCK_REG_NOT_RESET
    if (R_SYSTEM->PLLCR)
 #endif
    {
 #if (1U == BSP_FEATURE_CGC_PLLCCR_TYPE) || (4U == BSP_FEATURE_CGC_PLLCCR_TYPE)
        R_SYSTEM->PLLCCR = (uint16_t) BSP_PRV_PLLCCR;
 #elif 2U == BSP_FEATURE_CGC_PLLCCR_TYPE
        R_SYSTEM->PLLCCR2 = (uint8_t) BSP_PRV_PLLCCR;
 #elif 3U == BSP_FEATURE_CGC_PLLCCR_TYPE
        R_SYSTEM->PLLCCR  = (uint16_t) BSP_PRV_PLLCCR;
        R_SYSTEM->PLLCCR2 = (uint16_t) BSP_PRV_PLLCCR2;
 #endif

 #if BSP_FEATURE_CGC_PLLCCR_WAIT_US > 0

        /* This loop is provided to ensure at least 1 us passes between setting PLLMUL and clearing PLLSTP on some
         * MCUs (see PLLSTP notes in Section 8.2.4 "PLL Control Register (PLLCR)" of the RA4M1 manual R01UH0887EJ0100).
         * Five loops are needed here to ensure the most efficient path takes at least 1 us from the setting of
         * PLLMUL to the clearing of PLLSTP. HOCO is the fastest clock we can be using here since PLL cannot be running
         * while setting PLLCCR. */
        bsp_prv_software_delay_loop(BSP_DELAY_LOOPS_CALCULATE(BSP_PRV_MAX_HOCO_CYCLES_PER_US));
 #endif

        R_SYSTEM->PLLCR = 0U;

 #if BSP_PRV_STABILIZE_PLL

        /* Wait for PLL to stabilize. */
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OSCSF_b.PLLSF, 1U);
 #endif
    }
#endif

    /* Set source clock and dividers. */
#if BSP_CFG_STARTUP_CLOCK_REG_NOT_RESET
 #if BSP_TZ_SECURE_BUILD

    /* In case of soft reset, make sure callback pointer is NULL initially. */
    g_bsp_clock_update_callback = NULL;
 #endif

 #if BSP_FEATURE_CGC_HAS_CPUCLK
    bsp_prv_clock_set(BSP_CFG_CLOCK_SOURCE, BSP_PRV_STARTUP_SCKDIVCR, BSP_PRV_STARTUP_SCKDIVCR2);
 #else
    bsp_prv_clock_set(BSP_CFG_CLOCK_SOURCE, BSP_PRV_STARTUP_SCKDIVCR, 0);
 #endif
#else
    bsp_prv_clock_set_hard_reset();
#endif

    /* If the MCU can run in a lower power mode, apply the optimal operating speed mode. */
#if !BSP_CFG_USE_LOW_VOLTAGE_MODE
 #if BSP_PRV_STARTUP_OPERATING_MODE != BSP_PRV_OPERATING_MODE_HIGH_SPEED
    bsp_prv_operating_mode_set(BSP_PRV_STARTUP_OPERATING_MODE);
 #endif
#endif

#if defined(BSP_PRV_POWER_USE_DCDC) && (BSP_PRV_POWER_USE_DCDC == BSP_PRV_POWER_DCDC_STARTUP) && \
    (BSP_PRV_STARTUP_OPERATING_MODE <= BSP_PRV_OPERATING_MODE_MIDDLE_SPEED)

    /* Start DCDC as part of BSP startup when configured (BSP_CFG_DCDC_ENABLE == 2). */
    R_BSP_PowerModeSet(BSP_CFG_DCDC_VOLTAGE_RANGE);
#endif

    /* Configure BCLK if it exists on the MCU. */
#ifdef BSP_CFG_BCLK_OUTPUT
 #if BSP_CFG_BCLK_OUTPUT > 0U
    R_SYSTEM->BCKCR   = BSP_CFG_BCLK_OUTPUT - 1U;
    R_SYSTEM->EBCKOCR = 1U;
 #else
  #if BSP_CFG_STARTUP_CLOCK_REG_NOT_RESET
    R_SYSTEM->EBCKOCR = 0U;
  #endif
 #endif
#endif

    /* Configure SDRAM clock if it exists on the MCU. */
#ifdef BSP_CFG_SDCLK_OUTPUT
    R_SYSTEM->SDCKOCR = BSP_CFG_SDCLK_OUTPUT;
#endif

    /* Configure CLKOUT. */
#if BSP_CFG_CLKOUT_SOURCE == BSP_CLOCKS_CLOCK_DISABLED
 #if BSP_CFG_STARTUP_CLOCK_REG_NOT_RESET
    R_SYSTEM->CKOCR = 0U;
 #endif
#else
    uint8_t ckocr = BSP_CFG_CLKOUT_SOURCE | (BSP_CFG_CLKOUT_DIV << BSP_PRV_CKOCR_CKODIV_BIT);
    R_SYSTEM->CKOCR = ckocr;
    ckocr          |= (1U << BSP_PRV_CKOCR_CKOEN_BIT);
    R_SYSTEM->CKOCR = ckocr;
#endif

#if BSP_PRV_STARTUP_OPERATING_MODE != BSP_PRV_OPERATING_MODE_LOW_SPEED
 #if BSP_CFG_UCK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED

    /* If the USB clock has a divider setting in SCKDIVCR2. */
  #if BSP_FEATURE_BSP_HAS_USB_CLOCK_DIV && !BSP_FEATURE_BSP_HAS_USBCKDIVCR
    R_SYSTEM->SCKDIVCR2 = BSP_PRV_UCK_DIV << BSP_PRV_SCKDIVCR2_UCK_BIT;
  #endif                               /* BSP_FEATURE_BSP_HAS_USB_CLOCK_DIV && !BSP_FEATURE_BSP_HAS_USBCKDIVCR */

    /* If there is a REQ bit in USBCKCR, then follow sequence from section 8.2.29 in RA6M4 hardware manual R01UH0890EJ0050. */
  #if BSP_FEATURE_BSP_HAS_USB_CLOCK_REQ

    /* Request to change the USB Clock. */
    R_SYSTEM->USBCKCR_b.USBCKSREQ = 1;

    /* Wait for the clock to be stopped. */
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->USBCKCR_b.USBCKSRDY, 1U);

    /* Write the settings. */
    R_SYSTEM->USBCKDIVCR = BSP_PRV_UCK_DIV;

    /* Select the USB Clock without enabling it. */
    R_SYSTEM->USBCKCR = BSP_CFG_UCK_SOURCE | R_SYSTEM_USBCKCR_USBCKSREQ_Msk;
  #endif                               /* BSP_FEATURE_BSP_HAS_USB_CLOCK_REQ */

  #if BSP_FEATURE_BSP_HAS_USB_CLOCK_SEL

    /* Some MCUs use an alternate register for selecting the USB clock source. */
   #if BSP_FEATURE_BSP_HAS_USB_CLOCK_SEL_ALT
    #if BSP_CLOCKS_SOURCE_CLOCK_PLL == BSP_CFG_UCK_SOURCE

    /* Write to USBCKCR to select the PLL. */
    R_SYSTEM->USBCKCR_ALT = 0;
    #elif BSP_CLOCKS_SOURCE_CLOCK_HOCO == BSP_CFG_UCK_SOURCE

    /* Write to USBCKCR to select the HOCO. */
    R_SYSTEM->USBCKCR_ALT = 1;
    #endif
   #else

    /* Select the USB Clock. */
    R_SYSTEM->USBCKCR = BSP_CFG_UCK_SOURCE;
   #endif
  #endif                               /* BSP_FEATURE_BSP_HAS_USB_CLOCK_REQ */

  #if BSP_FEATURE_BSP_HAS_USB_CLOCK_REQ

    /* Wait for the USB Clock to be started. */
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->USBCKCR_b.USBCKSRDY, 0U);
  #endif                               /* BSP_FEATURE_BSP_HAS_USB_CLOCK_REQ */
 #endif                                /* BSP_CFG_USB_ENABLE */
#endif                                 /* BSP_PRV_STARTUP_OPERATING_MODE != BSP_PRV_OPERATING_MODE_LOW_SPEED */

    /* Set the OCTASPI clock if it exists on the MCU (See section 8.2.30 of the RA6M4 hardware manual R01UH0890EJ0050). */
#if BSP_FEATURE_BSP_HAS_OCTASPI_CLOCK && BSP_CFG_OCTA_SOURCE != BSP_CLOCKS_CLOCK_DISABLED
    bsp_octaclk_settings_t octaclk_settings =
    {
        .source_clock = (bsp_clocks_source_t) BSP_CFG_OCTA_SOURCE,
        .divider      = (bsp_clocks_octaclk_div_t) BSP_CFG_OCTA_DIV
    };
    R_BSP_OctaclkUpdate(&octaclk_settings);
#endif                                 /* BSP_FEATURE_BSP_HAS_OCTASPI_CLOCK && BSP_CFG_OCTASPI_CLOCK_ENABLE */

    /* Set the CANFD clock if it exists on the MCU */
#if BSP_FEATURE_BSP_HAS_CANFD_CLOCK && (BSP_CFG_CANFDCLK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED) && \
    (BSP_CFG_CANFDCLK_SOURCE != BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC)

    bsp_peripheral_clock_set(&R_SYSTEM->CANFDCKCR,
                             &R_SYSTEM->CANFDCKDIVCR,
                             BSP_CFG_CANFDCLK_DIV,
                             BSP_CFG_CANFDCLK_SOURCE);
#endif

    /* Set the SCISPI clock if it exists on the MCU */
#if BSP_FEATURE_BSP_HAS_SCISPI_CLOCK && (BSP_CFG_SCISPICLK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED)
    bsp_peripheral_clock_set(&R_SYSTEM->SCISPICKCR,
                             &R_SYSTEM->SCISPICKDIVCR,
                             BSP_CFG_SCISPICLK_DIV,
                             BSP_CFG_SCISPICLK_SOURCE);
#endif

    /* Set the SCI clock if it exists on the MCU */
#if BSP_FEATURE_BSP_HAS_SCI_CLOCK && (BSP_CFG_SCICLK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED)
    bsp_peripheral_clock_set(&R_SYSTEM->SCICKCR, &R_SYSTEM->SCICKDIVCR, BSP_CFG_SCICLK_DIV, BSP_CFG_SCICLK_SOURCE);
#endif

    /* Set the SPI clock if it exists on the MCU */
#if BSP_FEATURE_BSP_HAS_SPI_CLOCK && (BSP_CFG_SPICLK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED)
    bsp_peripheral_clock_set(&R_SYSTEM->SPICKCR, &R_SYSTEM->SPICKDIVCR, BSP_CFG_SPICLK_DIV, BSP_CFG_SPICLK_SOURCE);
#endif

    /* Set the GPT clock if it exists on the MCU */
#if BSP_FEATURE_BSP_HAS_GPT_CLOCK && (BSP_CFG_GPTCLK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED)
    bsp_peripheral_clock_set(&R_SYSTEM->GPTCKCR, &R_SYSTEM->GPTCKDIVCR, BSP_CFG_GPTCLK_DIV, BSP_CFG_GPTCLK_SOURCE);
#endif

    /* Set the IIC clock if it exists on the MCU */
#if BSP_FEATURE_BSP_HAS_IIC_CLOCK && (BSP_CFG_IICCLK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED)
    bsp_peripheral_clock_set(&R_SYSTEM->IICCKCR, &R_SYSTEM->IICCKDIVCR, BSP_CFG_IICCLK_DIV, BSP_CFG_IICCLK_SOURCE);
#endif

    /* Set the CEC clock if it exists on the MCU */
#if BSP_FEATURE_BSP_HAS_CEC_CLOCK && (BSP_CFG_CECCLK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED)
    bsp_peripheral_clock_set(&R_SYSTEM->CECCKCR, &R_SYSTEM->CECCKDIVCR, BSP_CFG_CECCLK_DIV, BSP_CFG_CECCLK_SOURCE);
#endif

    /* Set the I3C clock if it exists on the MCU */
#if BSP_FEATURE_BSP_HAS_I3C_CLOCK && (BSP_CFG_I3CCLK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED)
    bsp_peripheral_clock_set(&R_SYSTEM->I3CCKCR, &R_SYSTEM->I3CCKDIVCR, BSP_CFG_I3CCLK_DIV, BSP_CFG_I3CCLK_SOURCE);
#endif

    /* Set the LCD clock if it exists on the MCU */
#if BSP_FEATURE_BSP_HAS_LCD_CLOCK && (BSP_CFG_LCDCLK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED)
    bsp_peripheral_clock_set(&R_SYSTEM->LCDCKCR, &R_SYSTEM->LCDCKDIVCR, BSP_CFG_LCDCLK_DIV, BSP_CFG_LCDCLK_SOURCE);
#endif

    /* Set the USB-HS clock if it exists on the MCU */
#if BSP_FEATURE_BSP_HAS_USB60_CLOCK_REQ && (BSP_CFG_U60CK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED)
    bsp_peripheral_clock_set(&R_SYSTEM->USB60CKCR, &R_SYSTEM->USB60CKDIVCR, BSP_CFG_U60CK_DIV, BSP_CFG_U60CK_SOURCE);
#endif

    /* Set the SDADC clock if it exists on the MCU. */
#if BSP_FEATURE_BSP_HAS_SDADC_CLOCK && (BSP_CFG_SDADC_CLOCK_SOURCE != BSP_CLOCKS_CLOCK_DISABLED)
 #if BSP_CFG_SDADC_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HOCO
    uint8_t sdadcckcr = 1U;
 #elif BSP_CFG_SDADC_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_PLL
    uint8_t sdadcckcr = 2U;
 #else                                 /* BSP_CLOCK_SOURCE_CLOCK_MOSC */
    uint8_t sdadcckcr = 0U;
 #endif

    /* SDADC isn't controlled like the other peripheral clocks so we cannot use the generic setter. */
    R_SYSTEM->SDADCCKCR = sdadcckcr & R_SYSTEM_SDADCCKCR_SDADCCKSEL_Msk;
#endif

    /* Lock CGC and LPM protection registers. */
#if BSP_FEATURE_TZ_VERSION == 2 && BSP_TZ_NONSECURE_BUILD == 1
    R_SYSTEM->PRCR_NS = (uint16_t) BSP_PRV_PRCR_LOCK;
#else
    R_SYSTEM->PRCR = (uint16_t) BSP_PRV_PRCR_LOCK;
#endif

#if BSP_FEATURE_BSP_FLASH_CACHE && BSP_FEATURE_BSP_FLASH_CACHE_DISABLE_OPM
    R_BSP_FlashCacheEnable();
#endif

#if BSP_FEATURE_BSP_FLASH_PREFETCH_BUFFER
    R_FACI_LP->PFBER = 1;
#endif
}

#if BSP_CLOCK_CFG_SUBCLOCK_POPULATED

/*******************************************************************************************************************//**
 * This function is called during SOSC stabilization when Sub-Clock oscillator is populated.
 * This function is declared as a weak symbol higher up in this file because it is meant to be overridden by a user
 * implemented version. One of the main uses for this function is to update the IWDT/WDT Refresh Register if an
 * application starts IWDT/WDT automatically after reset. To use this function just copy this function into your own
 * code and modify it to meet your needs.
 *
 * @param[in]  delay_ms    Stabilization Time for the clock.
 **********************************************************************************************************************/
void R_BSP_SubClockStabilizeWait (uint32_t delay_ms)
{
    /* Wait for clock to stabilize. */
    R_BSP_SoftwareDelay(delay_ms, BSP_DELAY_UNITS_MILLISECONDS);
}

/*******************************************************************************************************************//**
 * This function is called during SOSC registers initialization when Sub-Clock oscillator is populated.
 * This function is declared as a weak symbol higher up in this file because it is meant to be overridden by a user
 * implemented version. One of the main uses for this function is to skip waiting for stabilization time after reset.
 * To use this function just copy this function into your own code and modify it to meet your needs.
 *
 * @param[in]  delay_ms    Stabilization Time for the clock.
 **********************************************************************************************************************/
void R_BSP_SubClockStabilizeWaitAfterReset (uint32_t delay_ms)
{
 #if (BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK == BSP_CFG_CLOCK_SOURCE) || (BSP_PRV_HOCO_USE_FLL)

    /* Wait for clock to stabilize after reset. */
    R_BSP_SoftwareDelay(delay_ms, BSP_DELAY_UNITS_MILLISECONDS);
 #else
    FSP_PARAMETER_NOT_USED(delay_ms);
 #endif
}

#endif

#if (BSP_PRV_HAS_ENABLED_PERIPHERAL_CLOCKS == 1U)

/*******************************************************************************************************************//**
 * Set the peripheral clock on the MCU
 *
 * @param[in] p_clk_ctrl_reg            Pointer to peripheral clock control register
 * @param[in] p_clk_div_reg             Pointer to peripheral clock division control register
 * @param[in] peripheral_clk_div        Peripheral clock division
 * @param[in] peripheral_clk_source     Peripheral clock source
 *
 * @return The wait states for FLWT required after the clock change (or 0 if FLWT does not exist).
 **********************************************************************************************************************/
static void bsp_peripheral_clock_set (volatile uint8_t * p_clk_ctrl_reg,
                                      volatile uint8_t * p_clk_div_reg,
                                      uint8_t            peripheral_clk_div,
                                      uint8_t            peripheral_clk_source)
{
    /* Request to stop the peripheral clock. */
    *p_clk_ctrl_reg |= (uint8_t) BSP_PRV_PERIPHERAL_CLK_REQ_BIT_MASK;

    /* Wait for the peripheral clock to stop. */
    FSP_HARDWARE_REGISTER_WAIT((uint8_t) ((*p_clk_ctrl_reg & BSP_PRV_PERIPHERAL_CLK_RDY_BIT_MASK) >>
                                          BSP_PRV_PERIPHERAL_CLK_RDY_BIT_POS),
                               1U);

    /* Select the peripheral clock divisor and source. */
    *p_clk_div_reg  = peripheral_clk_div;
    *p_clk_ctrl_reg = peripheral_clk_source | BSP_PRV_PERIPHERAL_CLK_REQ_BIT_MASK |
                      BSP_PRV_PERIPHERAL_CLK_RDY_BIT_MASK;

    /* Request to start the peripheral clock. */
    *p_clk_ctrl_reg &= (uint8_t) ~BSP_PRV_PERIPHERAL_CLK_REQ_BIT_MASK;

    /* Wait for the peripheral clock to start. */
    FSP_HARDWARE_REGISTER_WAIT((uint8_t) ((*p_clk_ctrl_reg & BSP_PRV_PERIPHERAL_CLK_RDY_BIT_MASK) >>
                                          BSP_PRV_PERIPHERAL_CLK_RDY_BIT_POS),
                               0U);
}

#endif

/*******************************************************************************************************************//**
 * Increases the ROM and RAM wait state settings to the minimum required based on the requested clock change.
 *
 * @param[in] requested_freq_hz        New core clock frequency after the clock change.
 *
 * @return The wait states for FLWT required after the clock change (or 0 if FLWT does not exist).
 **********************************************************************************************************************/
static uint8_t bsp_clock_set_prechange (uint32_t requested_freq_hz)
{
    uint8_t new_rom_wait_state = 0U;

    FSP_PARAMETER_NOT_USED(requested_freq_hz);

#if BSP_FEATURE_CGC_HAS_SRAMWTSC

    /* Wait states for SRAM (SRAM0, SRAM1 and SRAM0 (DED)). */
    if (requested_freq_hz > BSP_FEATURE_BSP_SYS_CLOCK_FREQ_NO_RAM_WAITS)
    {
 #if BSP_FEATURE_CGC_HAS_SRAMPRCR2 == 1
        R_SRAM->SRAMPRCR2 = BSP_PRV_SRAM_UNLOCK;
        R_SRAM->SRAMWTSC  = BSP_FEATURE_SRAM_SRAMWTSC_WAIT_CYCLE_ENABLE;
        R_SRAM->SRAMPRCR2 = BSP_PRV_SRAM_LOCK;
 #else
        R_SRAM->SRAMPRCR = BSP_PRV_SRAM_UNLOCK;

        /* Execute data memory barrier before and after setting the wait states, See Section 50.4.2 in the RA8M1
         * manual R01UH0994EJ0100 */
        __DMB();
        R_SRAM->SRAMWTSC = BSP_FEATURE_SRAM_SRAMWTSC_WAIT_CYCLE_ENABLE;
        __DMB();

        R_SRAM->SRAMPRCR = BSP_PRV_SRAM_LOCK;
 #endif
    }
#endif

#if BSP_FEATURE_CGC_HAS_FLWT

    /* Calculate the wait states for ROM */
 #if BSP_FEATURE_BSP_SYS_CLOCK_FREQ_TWO_ROM_WAITS == 0
    if (requested_freq_hz <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_ONE_ROM_WAITS)
    {
        new_rom_wait_state = BSP_PRV_ROM_ZERO_WAIT_CYCLES;
    }
    else
    {
        new_rom_wait_state = BSP_PRV_ROM_ONE_WAIT_CYCLES;
    }

 #elif BSP_FEATURE_BSP_SYS_CLOCK_FREQ_THREE_ROM_WAITS == 0
    if (requested_freq_hz <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_ONE_ROM_WAITS)
    {
        new_rom_wait_state = BSP_PRV_ROM_ZERO_WAIT_CYCLES;
    }
    else if (requested_freq_hz <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_TWO_ROM_WAITS)
    {
        new_rom_wait_state = BSP_PRV_ROM_ONE_WAIT_CYCLES;
    }
    else
    {
        new_rom_wait_state = BSP_PRV_ROM_TWO_WAIT_CYCLES;
    }

 #elif BSP_FEATURE_BSP_SYS_CLOCK_FREQ_FOUR_ROM_WAITS == 0
    if (requested_freq_hz <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_ONE_ROM_WAITS)
    {
        new_rom_wait_state = BSP_PRV_ROM_ZERO_WAIT_CYCLES;
    }
    else if (requested_freq_hz <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_TWO_ROM_WAITS)
    {
        new_rom_wait_state = BSP_PRV_ROM_ONE_WAIT_CYCLES;
    }
    else if (requested_freq_hz <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_THREE_ROM_WAITS)
    {
        new_rom_wait_state = BSP_PRV_ROM_TWO_WAIT_CYCLES;
    }
    else
    {
        new_rom_wait_state = BSP_PRV_ROM_THREE_WAIT_CYCLES;
    }

 #elif BSP_FEATURE_BSP_SYS_CLOCK_FREQ_FIVE_ROM_WAITS == 0
    if (requested_freq_hz <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_ONE_ROM_WAITS)
    {
        new_rom_wait_state = BSP_PRV_ROM_ZERO_WAIT_CYCLES;
    }
    else if (requested_freq_hz <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_TWO_ROM_WAITS)
    {
        new_rom_wait_state = BSP_PRV_ROM_ONE_WAIT_CYCLES;
    }
    else if (requested_freq_hz <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_THREE_ROM_WAITS)
    {
        new_rom_wait_state = BSP_PRV_ROM_TWO_WAIT_CYCLES;
    }
    else if (requested_freq_hz <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_FOUR_ROM_WAITS)
    {
        new_rom_wait_state = BSP_PRV_ROM_THREE_WAIT_CYCLES;
    }
    else
    {
        new_rom_wait_state = BSP_PRV_ROM_FOUR_WAIT_CYCLES;
    }

 #else
    if (requested_freq_hz <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_ONE_ROM_WAITS)
    {
        new_rom_wait_state = BSP_PRV_ROM_ZERO_WAIT_CYCLES;
    }
    else if (requested_freq_hz <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_TWO_ROM_WAITS)
    {
        new_rom_wait_state = BSP_PRV_ROM_ONE_WAIT_CYCLES;
    }
    else if (requested_freq_hz <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_THREE_ROM_WAITS)
    {
        new_rom_wait_state = BSP_PRV_ROM_TWO_WAIT_CYCLES;
    }
    else if (requested_freq_hz <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_FOUR_ROM_WAITS)
    {
        new_rom_wait_state = BSP_PRV_ROM_THREE_WAIT_CYCLES;
    }
    else if (requested_freq_hz <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_FIVE_ROM_WAITS)
    {
        new_rom_wait_state = BSP_PRV_ROM_FOUR_WAIT_CYCLES;
    }
    else
    {
        new_rom_wait_state = BSP_PRV_ROM_FIVE_WAIT_CYCLES;
    }
 #endif

    /* If more wait states are required after the change, then set the wait states before changing the clock. */
    if (new_rom_wait_state > R_FCACHE->FLWT)
    {
        R_FCACHE->FLWT = new_rom_wait_state;
    }
#endif

#if BSP_FEATURE_CGC_HAS_MEMWAIT && !BSP_PRV_CLOCK_SUPPLY_TYPE_B
    if (requested_freq_hz > BSP_PRV_MEMWAIT_MAX_ZERO_WAIT_FREQ)
    {
        /* The MCU must be in high speed mode to set wait states to 2. The MCU should already be in high speed mode as
         * a precondition to bsp_prv_clock_set. */
        R_SYSTEM->MEMWAIT = BSP_PRV_MEMWAIT_TWO_WAIT_CYCLES;
    }
#endif

#if BSP_FEATURE_CGC_HAS_FLDWAITR && !BSP_PRV_CLOCK_SUPPLY_TYPE_B
    if (requested_freq_hz > BSP_PRV_FLDWAITR_MAX_ONE_WAIT_FREQ)
    {
        /* The MCU must be in high speed mode to set wait states to 2. The MCU should already be in high speed mode as
         * a precondition to bsp_prv_clock_set. */
        BSP_PRV_FLDWAITR_REG_ACCESS = BSP_PRV_FLDWAITR_TWO_WAIT_CYCLES;
    }
#endif

    return new_rom_wait_state;
}

/*******************************************************************************************************************//**
 * Decreases the ROM and RAM wait state settings to the minimum supported based on the applied clock change.
 *
 * @param[in] updated_freq_hz          New clock frequency after clock change
 * @param[in] new_rom_wait_state       Optimal value for FLWT if it exists, 0 if FLWT does not exist on the MCU
 **********************************************************************************************************************/
static void bsp_clock_set_postchange (uint32_t updated_freq_hz, uint8_t new_rom_wait_state)
{
    /* These variables are unused for some MCUs. */
    FSP_PARAMETER_NOT_USED(new_rom_wait_state);
    FSP_PARAMETER_NOT_USED(updated_freq_hz);

#if BSP_FEATURE_CGC_HAS_SRAMWTSC

    /* Wait states for SRAM (SRAM0, SRAM1 and SRAM0 (DED)). */
    if (updated_freq_hz <= BSP_FEATURE_BSP_SYS_CLOCK_FREQ_NO_RAM_WAITS)
    {
 #if BSP_FEATURE_CGC_HAS_SRAMPRCR2 == 1
        R_SRAM->SRAMPRCR2 = BSP_PRV_SRAM_UNLOCK;
        R_SRAM->SRAMWTSC  = BSP_PRV_SRAMWTSC_WAIT_CYCLES_DISABLE;
        R_SRAM->SRAMPRCR2 = BSP_PRV_SRAM_LOCK;
 #else
        R_SRAM->SRAMPRCR = BSP_PRV_SRAM_UNLOCK;

        /* Execute data memory barrier before and after setting the wait states,See Section 50.4.2 in the RA8M1
         * manual R01UH0994EJ0100*/
        __DMB();
        R_SRAM->SRAMWTSC = BSP_PRV_SRAMWTSC_WAIT_CYCLES_DISABLE;
        __DMB();

        R_SRAM->SRAMPRCR = BSP_PRV_SRAM_LOCK;
 #endif
    }
#endif

#if BSP_FEATURE_CGC_HAS_FLWT
    if (new_rom_wait_state != R_FCACHE->FLWT)
    {
        R_FCACHE->FLWT = new_rom_wait_state;
    }
#endif

#if BSP_FEATURE_CGC_HAS_MEMWAIT && !BSP_PRV_CLOCK_SUPPLY_TYPE_B
    if (updated_freq_hz <= BSP_PRV_MEMWAIT_MAX_ZERO_WAIT_FREQ)
    {
        R_SYSTEM->MEMWAIT = BSP_PRV_MEMWAIT_ZERO_WAIT_CYCLES;
    }
#endif

#if BSP_FEATURE_CGC_HAS_FLDWAITR && !BSP_PRV_CLOCK_SUPPLY_TYPE_B
    if (updated_freq_hz <= BSP_PRV_FLDWAITR_MAX_ONE_WAIT_FREQ)
    {
        BSP_PRV_FLDWAITR_REG_ACCESS = BSP_PRV_FLDWAITR_ONE_WAIT_CYCLES;
    }
#endif
}

/*******************************************************************************************************************//**
 * Initializes sub-clock according to the BSP configuration.
 **********************************************************************************************************************/
static void bsp_sosc_init (void)
{
#if BSP_FEATURE_CGC_HAS_SOSC
 #if BSP_CLOCK_CFG_SUBCLOCK_POPULATED
  #if BSP_FEATURE_RTC_IS_IRTC
   #if ((BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK == BSP_CFG_CLOCK_SOURCE) || (BSP_PRV_HOCO_USE_FLL))

    /* If sub-clock is used as system clock source or HOCO FLL source, wait for VRTC-domain become valid */
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->VRTSR_b.VRTVLD, 1);
   #else

    /* Check if VRTC-domain area is valid. */
    if (1U == R_SYSTEM->VRTSR_b.VRTVLD)
   #endif
  #endif
    {
        if (R_SYSTEM->SOSCCR || (BSP_CLOCK_CFG_SUBCLOCK_DRIVE != R_SYSTEM->SOMCR_b.SODRV))
        {
            /* If Sub-Clock Oscillator is started at reset, stop it before configuring the subclock drive. */
            if (0U == R_SYSTEM->SOSCCR)
            {
                /* Stop the Sub-Clock Oscillator to update the SOMCR register. */
                R_SYSTEM->SOSCCR = 1U;

                /* Allow a stop interval of at least 5 SOSC clock cycles before configuring the drive capacity
                 * and restarting Sub-Clock Oscillator. */
                R_BSP_SoftwareDelay(BSP_PRV_SUBCLOCK_STOP_INTERVAL_US, BSP_DELAY_UNITS_MICROSECONDS);

                /*
                 * r01uh0893ej0120-ra4m3 8.2.9 SOSCCR : Sub-Clock Oscillator Control Register:
                 * When changing the value of the SOSTP bit, execute subsequent instructions
                 * only after reading the bit to check that the value is updated.
                 */
                FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->SOSCCR, 1U);
            }

            /* Configure the subclock drive as subclock is not running. */
            R_SYSTEM->SOMCR =
                ((BSP_CLOCK_CFG_SUBCLOCK_DRIVE << BSP_FEATURE_CGC_SODRV_SHIFT) & BSP_FEATURE_CGC_SODRV_MASK);

            R_SYSTEM->SOSCCR = 0U;

            /* r01uh0893ej0120-ra4m3 8.2.9 SOSCCR : Sub-Clock Oscillator Control Register:
             * After setting the SOSTP bit to 0, use the sub-clock only after the sub-clock
             * oscillation stabilization time has elapsed.
             */
  #if (BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK == BSP_CFG_CLOCK_SOURCE) || (BSP_PRV_HOCO_USE_FLL)
            R_BSP_SubClockStabilizeWait(BSP_CLOCK_CFG_SUBCLOCK_STABILIZATION_MS);
  #endif
        }
        else
        {
            /*
             * RA MCUs like RA6M5 requires to use sub-clock after oscillation stabilization time
             * has elapsed on Power-On-Reset. But, POR is not well supported on EK boards, so BSP
             * has to wait on any reset. Please override this function in application if waiting
             * for stabilization is not required.
             */
            R_BSP_SubClockStabilizeWaitAfterReset(BSP_CLOCK_CFG_SUBCLOCK_STABILIZATION_MS);
        }
    }

 #else
    R_SYSTEM->SOSCCR = 1U;
 #endif
#endif
}

/*******************************************************************************************************************//**
 * Octa-SPI clock update.
 * @param[in]   p_octaclk_setting   Pointer to Octaclk setting structure which provides information regarding
 *                                  Octaclk source and divider settings to be applied.
 * @note The requested Octaclk source must be started before calling this function.
 **********************************************************************************************************************/
void R_BSP_OctaclkUpdate (bsp_octaclk_settings_t * p_octaclk_setting)
{
#if BSP_FEATURE_BSP_HAS_OCTASPI_CLOCK

    /* Store initial value of CGC and LPM protection registers. */
 #if BSP_FEATURE_TZ_VERSION == 2 && BSP_TZ_NONSECURE_BUILD == 1
    uint16_t bsp_prv_prcr_orig = R_SYSTEM->PRCR_NS;
 #else
    uint16_t bsp_prv_prcr_orig = R_SYSTEM->PRCR;
 #endif

    /* Unlock CGC and LPM protection registers. */
 #if BSP_FEATURE_TZ_VERSION == 2 && BSP_TZ_NONSECURE_BUILD == 1
    R_SYSTEM->PRCR_NS = (uint16_t) BSP_PRV_PRCR_UNLOCK;
 #else
    R_SYSTEM->PRCR = (uint16_t) BSP_PRV_PRCR_UNLOCK;
 #endif

    /* Request to change the OCTASPI Clock. */
    R_SYSTEM->OCTACKCR_b.OCTACKSREQ = 1;

    /* Wait for the clock to be stopped. */
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OCTACKCR_b.OCTACKSRDY, 1U);

    /* Write the settings. */
    R_SYSTEM->OCTACKDIVCR = (uint8_t) p_octaclk_setting->divider;
    R_SYSTEM->OCTACKCR    = (uint8_t) (p_octaclk_setting->source_clock | R_SYSTEM_OCTACKCR_OCTACKSREQ_Msk);

    /* Start the OCTASPI Clock by setting OCTACKSREQ to zero. */
    R_SYSTEM->OCTACKCR = (uint8_t) p_octaclk_setting->source_clock;

    /* Wait for the OCTASPI Clock to be started. */
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OCTACKCR_b.OCTACKSRDY, 0U);

    /* Restore CGC and LPM protection registers. */
 #if BSP_FEATURE_TZ_VERSION == 2 && BSP_TZ_NONSECURE_BUILD == 1
    R_SYSTEM->PRCR_NS = bsp_prv_prcr_orig;
 #else
    R_SYSTEM->PRCR = bsp_prv_prcr_orig;
 #endif
#else
    FSP_PARAMETER_NOT_USED(p_octaclk_setting);
#endif
}

/*******************************************************************************************************************//**
 * Gets the frequency of a source clock.
 * @param[in]   clock   Pointer to Octaclk setting structure which provides information regarding
 *                                  Octaclk source and divider settings to be applied.
 * @return     Frequency of requested clock in Hertz.
 **********************************************************************************************************************/
uint32_t R_BSP_SourceClockHzGet (fsp_priv_source_clock_t clock)
{
    uint32_t source_clock = g_clock_freq[clock];

    return source_clock;
}

#if BSP_FEATURE_RTC_IS_AVAILABLE || BSP_FEATURE_RTC_HAS_TCEN || BSP_FEATURE_SYSC_HAS_VBTICTLR

/*******************************************************************************************************************//**
 * RTC Initialization
 *
 * Some RTC registers must be initialized after reset to ensure correct operation.
 * This reset is not performed automatically if the RTC is used in a project as it will
 * be handled by the RTC driver if needed.
 **********************************************************************************************************************/
void R_BSP_Init_RTC (void)
{
    /* RA4M3 UM r01uh0893ej0120: Figure 23.14 Initialization procedure */

    /* RCKSEL bit is not initialized after reset. Use LOCO as the default
     * clock source if it is available. Note RCR4.ROPSEL is also cleared.
     */

 #if BSP_FEATURE_RTC_IS_IRTC
    if (0U == R_SYSTEM->VRTSR_b.VRTVLD) // Return if VRTC-domain is invalid
    {
        return;
    }
 #endif

 #if BSP_PRV_LOCO_USED && !BSP_FEATURE_RTC_IS_IRTC
    R_RTC->RCR4 = 1 << R_RTC_RCR4_RCKSEL_Pos;
 #else

    /* Sses SOSC as clock source, or there is no clock source. */
    R_RTC->RCR4 = 0;
 #endif

 #if !BSP_CFG_RTC_USED
  #if BSP_PRV_LOCO_USED || (BSP_FEATURE_CGC_HAS_SOSC && BSP_CLOCK_CFG_SUBCLOCK_POPULATED)

    /*Wait for 6 clocks: 200 > (6*1000000) / 32K */
    R_BSP_SoftwareDelay(BSP_PRV_RTC_RESET_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);

    R_RTC->RCR2 = 0;
    FSP_HARDWARE_REGISTER_WAIT(R_RTC->RCR2, 0);

    R_RTC->RCR2_b.RESET = 1;
    FSP_HARDWARE_REGISTER_WAIT(R_RTC->RCR2_b.RESET, 0);

    /* Disable RTC interrupts */
    R_RTC->RCR1 = 0;

    /* When the RCR1 register is modified, check that all the bits are updated before proceeding
     * (see section 26.2.17 "RTC Control Register 1 (RCR1)" of the RA6M3 manual R01UH0886EJ0100)*/
    FSP_HARDWARE_REGISTER_WAIT(R_RTC->RCR1, 0);

   #if BSP_FEATURE_RTC_HAS_TCEN
    for (uint8_t index = 0U; index < BSP_FEATURE_RTC_RTCCR_CHANNELS; index++)
    {
        /* RTCCRn.TCEN must be cleared after reset. */
        R_RTC->RTCCR[index].RTCCR_b.TCEN = 0U;
        FSP_HARDWARE_REGISTER_WAIT(R_RTC->RTCCR[index].RTCCR_b.TCEN, 0);
    }
   #endif
  #endif
 #endif

 #if BSP_FEATURE_SYSC_HAS_VBTICTLR

    /* VBTICTLR.VCHnINEN must be cleared after reset. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_OM_LPC_BATT);
    R_SYSTEM->VBTICTLR = 0U;
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_OM_LPC_BATT);
 #endif
}

#endif

#if BSP_FEATURE_RTC_IS_IRTC

/*******************************************************************************************************************//**
 * To check sub-clock status.
 *
 * @retval FSP_SUCCESS                  Sub-clock is ready to use.
 * @retval FSP_ERR_INVALID_HW_CONDITION VRTC-domain area is invalid.
 * @retval FSP_ERR_NOT_INITIALIZED      Sub-clock has not been inititalized yet.
 **********************************************************************************************************************/
fsp_err_t R_BSP_SubclockStatusGet ()
{
 #if BSP_CLOCK_CFG_SUBCLOCK_POPULATED

    /* Check if VRTC-domain area is invalid */
    FSP_ERROR_RETURN(1U == R_SYSTEM->VRTSR_b.VRTVLD, FSP_ERR_INVALID_HW_CONDITION);

    /* Check if SOSC has been configured */
    if ((0U == R_SYSTEM->SOSCCR) && (BSP_CLOCK_CFG_SUBCLOCK_DRIVE == R_SYSTEM->SOMCR_b.SODRV))
    {
        return FSP_SUCCESS;
    }
 #endif

    return FSP_ERR_NOT_INITIALIZED;
}

/*******************************************************************************************************************//**
 * To initialize the sub-clock.
 *
 * @retval FSP_SUCCESS                  Sub-clock successfully initialized.
 * @retval FSP_ERR_INVALID_HW_CONDITION Sub-clock cannot be initialized.
 **********************************************************************************************************************/
fsp_err_t R_BSP_SubclockInitialize ()
{
 #if BSP_CLOCK_CFG_SUBCLOCK_POPULATED

    /* Check if VRTC-domain area is valid */
    FSP_ERROR_RETURN(1U == R_SYSTEM->VRTSR_b.VRTVLD, FSP_ERR_INVALID_HW_CONDITION);

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);
    bsp_sosc_init();
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_CGC);

    return FSP_SUCCESS;
 #else

    return FSP_ERR_INVALID_HW_CONDITION;
 #endif
}

#endif

/** @} (end addtogroup BSP_MCU_PRV) */
