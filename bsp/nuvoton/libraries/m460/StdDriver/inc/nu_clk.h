/**************************************************************************//**
 * @file     CLK.h
 * @version  V3.00
 * @brief    M460 Series CLK Driver Header File
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __NU_CLK_H__
#define __NU_CLK_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup CLK_Driver CLK Driver
  @{
*/

/** @addtogroup CLK_EXPORTED_CONSTANTS CLK Exported Constants
  @{
*/


#define FREQ_1MHZ          1000000UL    /*!< 1 MHz \hideinitializer */
#define FREQ_4MHZ          4000000UL    /*!< 4 MHz \hideinitializer */
#define FREQ_8MHZ          8000000UL    /*!< 8 MHz \hideinitializer */
#define FREQ_25MHZ         25000000UL   /*!< 25 MHz \hideinitializer */
#define FREQ_50MHZ         50000000UL   /*!< 50 MHz \hideinitializer */
#define FREQ_75MHZ         75000000UL   /*!< 75 MHz \hideinitializer */
#define FREQ_100MHZ        100000000UL  /*!< 100 MHz \hideinitializer */
#define FREQ_125MHZ        125000000UL  /*!< 125 MHz \hideinitializer */
#define FREQ_150MHZ        150000000UL  /*!< 50 MHz \hideinitializer */
#define FREQ_175MHZ        175000000UL  /*!< 175 MHz \hideinitializer */
#define FREQ_180MHZ        180000000UL  /*!< 180 MHz \hideinitializer */
#define FREQ_192MHZ        192000000UL  /*!< 192 MHz \hideinitializer */
#define FREQ_200MHZ        200000000UL  /*!< 200 MHz \hideinitializer */
#define FREQ_500MHZ        500000000UL  /*!< 500 MHz \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKSEL0 constant definitions.  (Write-protection)                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKSEL0_HCLKSEL_HXT          (0x0UL << CLK_CLKSEL0_HCLKSEL_Pos)         /*!< Select HCLK clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL0_HCLKSEL_LXT          (0x1UL << CLK_CLKSEL0_HCLKSEL_Pos)         /*!< Select HCLK clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL0_HCLKSEL_PLL          (0x2UL << CLK_CLKSEL0_HCLKSEL_Pos)         /*!< Select HCLK clock source from PLL \hideinitializer */
#define CLK_CLKSEL0_HCLKSEL_LIRC         (0x3UL << CLK_CLKSEL0_HCLKSEL_Pos)         /*!< Select HCLK clock source from low speed oscillator \hideinitializer */
#define CLK_CLKSEL0_HCLKSEL_HIRC         (0x7UL << CLK_CLKSEL0_HCLKSEL_Pos)         /*!< Select HCLK clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL0_STCLKSEL_HXT         (0x0UL << CLK_CLKSEL0_STCLKSEL_Pos)        /*!< Select SysTick clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL0_STCLKSEL_LXT         (0x1UL << CLK_CLKSEL0_STCLKSEL_Pos)        /*!< Select SysTick clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL0_STCLKSEL_HXT_DIV2    (0x2UL << CLK_CLKSEL0_STCLKSEL_Pos)        /*!< Select SysTick clock source from HXT/2 \hideinitializer */
#define CLK_CLKSEL0_STCLKSEL_HCLK_DIV2   (0x3UL << CLK_CLKSEL0_STCLKSEL_Pos)        /*!< Select SysTick clock source from HCLK/2 \hideinitializer */
#define CLK_CLKSEL0_STCLKSEL_HIRC_DIV2   (0x7UL << CLK_CLKSEL0_STCLKSEL_Pos)        /*!< Select SysTick clock source from HIRC/2 \hideinitializer */
#define CLK_CLKSEL0_STCLKSEL_HCLK        (0x1UL << SysTick_CTRL_CLKSOURCE_Pos)      /*!< Select SysTick clock source from HCLK \hideinitializer */

#define CLK_CLKSEL0_USBSEL_HIRC48M       (0x0UL << CLK_CLKSEL0_USBSEL_Pos)          /*!< Select USB clock source from HIRC48M \hideinitializer */
#define CLK_CLKSEL0_USBSEL_PLL_DIV2      (0x1UL << CLK_CLKSEL0_USBSEL_Pos)          /*!< Select USB clock source from PLL/2 \hideinitializer */

#define CLK_CLKSEL0_EADC0SEL_PLLFN_DIV2  (0x0UL << CLK_CLKSEL0_EADC0SEL_Pos)        /*!< Select EADC0 clock source from PLLFN/2 \hideinitializer */
#define CLK_CLKSEL0_EADC0SEL_PLL_DIV2    (0x1UL << CLK_CLKSEL0_EADC0SEL_Pos)        /*!< Select EADC0 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL0_EADC0SEL_HCLK        (0x2UL << CLK_CLKSEL0_EADC0SEL_Pos)        /*!< Select EADC0 clock source from HCLK \hideinitializer */

#define CLK_CLKSEL0_EADC1SEL_PLLFN_DIV2  (0x0UL << CLK_CLKSEL0_EADC1SEL_Pos)        /*!< Select EADC1 clock source from PLLFN/2 \hideinitializer */
#define CLK_CLKSEL0_EADC1SEL_PLL_DIV2    (0x1UL << CLK_CLKSEL0_EADC1SEL_Pos)        /*!< Select EADC1 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL0_EADC1SEL_HCLK        (0x2UL << CLK_CLKSEL0_EADC1SEL_Pos)        /*!< Select EADC1 clock source from HCLK \hideinitializer */

#define CLK_CLKSEL0_EADC2SEL_PLLFN_DIV2  (0x0UL << CLK_CLKSEL0_EADC2SEL_Pos)        /*!< Select EADC2 clock source from PLLFN/2 \hideinitializer */
#define CLK_CLKSEL0_EADC2SEL_PLL_DIV2    (0x1UL << CLK_CLKSEL0_EADC2SEL_Pos)        /*!< Select EADC2 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL0_EADC2SEL_HCLK        (0x2UL << CLK_CLKSEL0_EADC2SEL_Pos)        /*!< Select EADC2 clock source from HCLK \hideinitializer */

#define CLK_CLKSEL0_CCAPSEL_HXT          (0x0UL << CLK_CLKSEL0_CCAPSEL_Pos)         /*!< Select CCAP sensor clock source from HXT \hideinitializer */
#define CLK_CLKSEL0_CCAPSEL_PLL_DIV2     (0x1UL << CLK_CLKSEL0_CCAPSEL_Pos)         /*!< Select CCAP sensor clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL0_CCAPSEL_HCLK         (0x2UL << CLK_CLKSEL0_CCAPSEL_Pos)         /*!< Select CCAP sensor clock source from HCLK \hideinitializer */
#define CLK_CLKSEL0_CCAPSEL_HIRC         (0x3UL << CLK_CLKSEL0_CCAPSEL_Pos)         /*!< Select CCAP sensor clock source from HIRC \hideinitializer */

#define CLK_CLKSEL0_SDH0SEL_HXT          (0x0UL << CLK_CLKSEL0_SDH0SEL_Pos)         /*!< Select SDH0 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL0_SDH0SEL_PLL_DIV2     (0x1UL << CLK_CLKSEL0_SDH0SEL_Pos)         /*!< Select SDH0 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL0_SDH0SEL_HCLK         (0x2UL << CLK_CLKSEL0_SDH0SEL_Pos)         /*!< Select SDH0 clock source from HCLK \hideinitializer */
#define CLK_CLKSEL0_SDH0SEL_HIRC         (0x3UL << CLK_CLKSEL0_SDH0SEL_Pos)         /*!< Select SDH0 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL0_SDH1SEL_HXT          (0x0UL << CLK_CLKSEL0_SDH1SEL_Pos)         /*!< Select SDH1 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL0_SDH1SEL_PLL_DIV2     (0x1UL << CLK_CLKSEL0_SDH1SEL_Pos)         /*!< Select SDH1 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL0_SDH1SEL_HCLK         (0x2UL << CLK_CLKSEL0_SDH1SEL_Pos)         /*!< Select SDH1 clock source from HCLK \hideinitializer */
#define CLK_CLKSEL0_SDH1SEL_HIRC         (0x3UL << CLK_CLKSEL0_SDH1SEL_Pos)         /*!< Select SDH1 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL0_CANFD0SEL_HXT        (0x0UL << CLK_CLKSEL0_CANFD0SEL_Pos)       /*!< Select CANFD0 clock source from HXT \hideinitializer */
#define CLK_CLKSEL0_CANFD0SEL_PLL_DIV2   (0x1UL << CLK_CLKSEL0_CANFD0SEL_Pos)       /*!< Select CANFD0 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL0_CANFD0SEL_HCLK       (0x2UL << CLK_CLKSEL0_CANFD0SEL_Pos)       /*!< Select CANFD0 clock source from HCLK \hideinitializer */
#define CLK_CLKSEL0_CANFD0SEL_HIRC       (0x3UL << CLK_CLKSEL0_CANFD0SEL_Pos)       /*!< Select CANFD0 clock source from HIRC \hideinitializer */

#define CLK_CLKSEL0_CANFD1SEL_HXT        (0x0UL << CLK_CLKSEL0_CANFD1SEL_Pos)       /*!< Select CANFD1 clock source from HXT \hideinitializer */
#define CLK_CLKSEL0_CANFD1SEL_PLL_DIV2   (0x1UL << CLK_CLKSEL0_CANFD1SEL_Pos)       /*!< Select CANFD1 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL0_CANFD1SEL_HCLK       (0x2UL << CLK_CLKSEL0_CANFD1SEL_Pos)       /*!< Select CANFD1 clock source from HCLK \hideinitializer */
#define CLK_CLKSEL0_CANFD1SEL_HIRC       (0x3UL << CLK_CLKSEL0_CANFD1SEL_Pos)       /*!< Select CANFD1 clock source from HIRC \hideinitializer */

#define CLK_CLKSEL0_CANFD2SEL_HXT        (0x0UL << CLK_CLKSEL0_CANFD2SEL_Pos)       /*!< Select CANFD2 clock source from HXT \hideinitializer */
#define CLK_CLKSEL0_CANFD2SEL_PLL_DIV2   (0x1UL << CLK_CLKSEL0_CANFD2SEL_Pos)       /*!< Select CANFD2 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL0_CANFD2SEL_HCLK       (0x2UL << CLK_CLKSEL0_CANFD2SEL_Pos)       /*!< Select CANFD2 clock source from HCLK \hideinitializer */
#define CLK_CLKSEL0_CANFD2SEL_HIRC       (0x3UL << CLK_CLKSEL0_CANFD2SEL_Pos)       /*!< Select CANFD2 clock source from HIRC \hideinitializer */

#define CLK_CLKSEL0_CANFD3SEL_HXT        (0x0UL << CLK_CLKSEL0_CANFD3SEL_Pos)       /*!< Select CANFD3 clock source from HXT \hideinitializer */
#define CLK_CLKSEL0_CANFD3SEL_PLL_DIV2   (0x1UL << CLK_CLKSEL0_CANFD3SEL_Pos)       /*!< Select CANFD3 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL0_CANFD3SEL_HCLK       (0x2UL << CLK_CLKSEL0_CANFD3SEL_Pos)       /*!< Select CANFD3 clock source from HCLK \hideinitializer */
#define CLK_CLKSEL0_CANFD3SEL_HIRC       (0x3UL << CLK_CLKSEL0_CANFD3SEL_Pos)       /*!< Select CANFD3 clock source from HIRC \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/*  CLKSEL1 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKSEL1_WDTSEL_LXT           (0x1UL << CLK_CLKSEL1_WDTSEL_Pos)          /*!< Select WDT clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL1_WDTSEL_HCLK_DIV2048  (0x2UL << CLK_CLKSEL1_WDTSEL_Pos)          /*!< Select WDT clock source from HCLK/2048 \hideinitializer */
#define CLK_CLKSEL1_WDTSEL_LIRC          (0x3UL << CLK_CLKSEL1_WDTSEL_Pos)          /*!< Select WDT clock source from low speed oscillator \hideinitializer */

#define CLK_CLKSEL1_CLKOSEL_HXT          (0x0UL << CLK_CLKSEL1_CLKOSEL_Pos)         /*!< Select CLKO clock source from HXT \hideinitializer */
#define CLK_CLKSEL1_CLKOSEL_LXT          (0x1UL << CLK_CLKSEL1_CLKOSEL_Pos)         /*!< Select CLKO clock source from LXT \hideinitializer */
#define CLK_CLKSEL1_CLKOSEL_HCLK         (0x2UL << CLK_CLKSEL1_CLKOSEL_Pos)         /*!< Select CLKO clock source from HCLK \hideinitializer */
#define CLK_CLKSEL1_CLKOSEL_HIRC         (0x3UL << CLK_CLKSEL1_CLKOSEL_Pos)         /*!< Select CLKO clock source from HIRC \hideinitializer */
#define CLK_CLKSEL1_CLKOSEL_LIRC         (0x4UL << CLK_CLKSEL1_CLKOSEL_Pos)         /*!< Select CLKO clock source from LIRC \hideinitializer */
#define CLK_CLKSEL1_CLKOSEL_PLLFN_DIV2   (0x5UL << CLK_CLKSEL1_CLKOSEL_Pos)         /*!< Select CLKO clock source from PLLFN/2 \hideinitializer */
#define CLK_CLKSEL1_CLKOSEL_PLL_DIV2     (0x6UL << CLK_CLKSEL1_CLKOSEL_Pos)         /*!< Select CLKO clock source from PLL/2 \hideinitializer */

#define CLK_CLKSEL1_TMR0SEL_HXT          (0x0UL << CLK_CLKSEL1_TMR0SEL_Pos)         /*!< Select TMR0 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL1_TMR0SEL_LXT          (0x1UL << CLK_CLKSEL1_TMR0SEL_Pos)         /*!< Select TMR0 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL1_TMR0SEL_PCLK0        (0x2UL << CLK_CLKSEL1_TMR0SEL_Pos)         /*!< Select TMR0 clock source from PCLK0 \hideinitializer */
#define CLK_CLKSEL1_TMR0SEL_EXT          (0x3UL << CLK_CLKSEL1_TMR0SEL_Pos)         /*!< Select TMR0 clock source from external trigger \hideinitializer */
#define CLK_CLKSEL1_TMR0SEL_LIRC         (0x5UL << CLK_CLKSEL1_TMR0SEL_Pos)         /*!< Select TMR0 clock source from low speed oscillator \hideinitializer */
#define CLK_CLKSEL1_TMR0SEL_HIRC         (0x7UL << CLK_CLKSEL1_TMR0SEL_Pos)         /*!< Select TMR0 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL1_TMR1SEL_HXT          (0x0UL << CLK_CLKSEL1_TMR1SEL_Pos)         /*!< Select TMR1 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL1_TMR1SEL_LXT          (0x1UL << CLK_CLKSEL1_TMR1SEL_Pos)         /*!< Select TMR1 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL1_TMR1SEL_PCLK0        (0x2UL << CLK_CLKSEL1_TMR1SEL_Pos)         /*!< Select TMR1 clock source from PCLK0 \hideinitializer */
#define CLK_CLKSEL1_TMR1SEL_EXT          (0x3UL << CLK_CLKSEL1_TMR1SEL_Pos)         /*!< Select TMR1 clock source from external trigger \hideinitializer */
#define CLK_CLKSEL1_TMR1SEL_LIRC         (0x5UL << CLK_CLKSEL1_TMR1SEL_Pos)         /*!< Select TMR1 clock source from low speed oscillator \hideinitializer */
#define CLK_CLKSEL1_TMR1SEL_HIRC         (0x7UL << CLK_CLKSEL1_TMR1SEL_Pos)         /*!< Select TMR1 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL1_TMR2SEL_HXT          (0x0UL << CLK_CLKSEL1_TMR2SEL_Pos)         /*!< Select TMR2 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL1_TMR2SEL_LXT          (0x1UL << CLK_CLKSEL1_TMR2SEL_Pos)         /*!< Select TMR2 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL1_TMR2SEL_PCLK1        (0x2UL << CLK_CLKSEL1_TMR2SEL_Pos)         /*!< Select TMR2 clock source from PCLK1 \hideinitializer */
#define CLK_CLKSEL1_TMR2SEL_EXT          (0x3UL << CLK_CLKSEL1_TMR2SEL_Pos)         /*!< Select TMR2 clock source from external trigger \hideinitializer */
#define CLK_CLKSEL1_TMR2SEL_LIRC         (0x5UL << CLK_CLKSEL1_TMR2SEL_Pos)         /*!< Select TMR2 clock source from low speed oscillator \hideinitializer */
#define CLK_CLKSEL1_TMR2SEL_HIRC         (0x7UL << CLK_CLKSEL1_TMR2SEL_Pos)         /*!< Select TMR2 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL1_TMR3SEL_HXT          (0x0UL << CLK_CLKSEL1_TMR3SEL_Pos)         /*!< Select TMR3 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL1_TMR3SEL_LXT          (0x1UL << CLK_CLKSEL1_TMR3SEL_Pos)         /*!< Select TMR3 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL1_TMR3SEL_PCLK1        (0x2UL << CLK_CLKSEL1_TMR3SEL_Pos)         /*!< Select TMR3 clock source from PCLK1 \hideinitializer */
#define CLK_CLKSEL1_TMR3SEL_EXT          (0x3UL << CLK_CLKSEL1_TMR3SEL_Pos)         /*!< Select TMR3 clock source from external trigger \hideinitializer */
#define CLK_CLKSEL1_TMR3SEL_LIRC         (0x5UL << CLK_CLKSEL1_TMR3SEL_Pos)         /*!< Select TMR3 clock source from low speed oscillator \hideinitializer */
#define CLK_CLKSEL1_TMR3SEL_HIRC         (0x7UL << CLK_CLKSEL1_TMR3SEL_Pos)         /*!< Select TMR3 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL1_UART0SEL_HXT         (0x0UL << CLK_CLKSEL1_UART0SEL_Pos)        /*!< Select UART0 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL1_UART0SEL_PLL_DIV2    (0x1UL << CLK_CLKSEL1_UART0SEL_Pos)        /*!< Select UART0 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL1_UART0SEL_LXT         (0x2UL << CLK_CLKSEL1_UART0SEL_Pos)        /*!< Select UART0 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL1_UART0SEL_HIRC        (0x3UL << CLK_CLKSEL1_UART0SEL_Pos)        /*!< Select UART0 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL1_UART1SEL_HXT         (0x0UL << CLK_CLKSEL1_UART1SEL_Pos)        /*!< Select UART1 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL1_UART1SEL_PLL_DIV2    (0x1UL << CLK_CLKSEL1_UART1SEL_Pos)        /*!< Select UART1 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL1_UART1SEL_LXT         (0x2UL << CLK_CLKSEL1_UART1SEL_Pos)        /*!< Select UART1 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL1_UART1SEL_HIRC        (0x3UL << CLK_CLKSEL1_UART1SEL_Pos)        /*!< Select UART1 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL1_WWDTSEL_HCLK_DIV2048 (0x2UL << CLK_CLKSEL1_WWDTSEL_Pos)         /*!< Select WWDT clock source from HCLK/2048 \hideinitializer */
#define CLK_CLKSEL1_WWDTSEL_LIRC         (0x3UL << CLK_CLKSEL1_WWDTSEL_Pos)         /*!< Select WWDT clock source from low speed oscillator \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/*  CLKSEL2 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKSEL2_EPWM0SEL_HCLK        (0x0UL << CLK_CLKSEL2_EPWM0SEL_Pos)        /*!< Select EPWM0 clock source from HCLK \hideinitializer */
#define CLK_CLKSEL2_EPWM0SEL_PCLK0       (0x1UL << CLK_CLKSEL2_EPWM0SEL_Pos)        /*!< Select EPWM0 clock source from PCLK0 \hideinitializer */

#define CLK_CLKSEL2_EPWM1SEL_HCLK        (0x0UL << CLK_CLKSEL2_EPWM1SEL_Pos)        /*!< Select EPWM1 clock source from HCLK \hideinitializer */
#define CLK_CLKSEL2_EPWM1SEL_PCLK1       (0x1UL << CLK_CLKSEL2_EPWM1SEL_Pos)        /*!< Select EPWM1 clock source from PCLK1 \hideinitializer */

#define CLK_CLKSEL2_QSPI0SEL_HXT         (0x0UL << CLK_CLKSEL2_QSPI0SEL_Pos)        /*!< Select QSPI0 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL2_QSPI0SEL_PLL_DIV2    (0x1UL << CLK_CLKSEL2_QSPI0SEL_Pos)        /*!< Select QSPI0 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL2_QSPI0SEL_PCLK0       (0x2UL << CLK_CLKSEL2_QSPI0SEL_Pos)        /*!< Select QSPI0 clock source from PCLK0 \hideinitializer */
#define CLK_CLKSEL2_QSPI0SEL_HIRC        (0x3UL << CLK_CLKSEL2_QSPI0SEL_Pos)        /*!< Select QSPI0 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL2_SPI0SEL_HXT          (0x0UL << CLK_CLKSEL2_SPI0SEL_Pos)         /*!< Select SPI0 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL2_SPI0SEL_PLL_DIV2     (0x1UL << CLK_CLKSEL2_SPI0SEL_Pos)         /*!< Select SPI0 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL2_SPI0SEL_PCLK1        (0x2UL << CLK_CLKSEL2_SPI0SEL_Pos)         /*!< Select SPI0 clock source from PCLK1 \hideinitializer */
#define CLK_CLKSEL2_SPI0SEL_HIRC         (0x3UL << CLK_CLKSEL2_SPI0SEL_Pos)         /*!< Select SPI0 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL2_SPI0SEL_HIRC48M      (0x4UL << CLK_CLKSEL2_SPI0SEL_Pos)         /*!< Select SPI0 clock source from HIRC48M \hideinitializer */
#define CLK_CLKSEL2_SPI0SEL_PLLFN_DIV2   (0x5UL << CLK_CLKSEL2_SPI0SEL_Pos)         /*!< Select SPI0 clock source from PLLFN/2 \hideinitializer */

#define CLK_CLKSEL2_BPWM0SEL_HCLK        (0x0UL << CLK_CLKSEL2_BPWM0SEL_Pos)        /*!< Select BPWM0 clock source from HCLK \hideinitializer */
#define CLK_CLKSEL2_BPWM0SEL_PCLK0       (0x1UL << CLK_CLKSEL2_BPWM0SEL_Pos)        /*!< Select BPWM0 clock source from PCLK0 \hideinitializer */

#define CLK_CLKSEL2_BPWM1SEL_HCLK        (0x0UL << CLK_CLKSEL2_BPWM1SEL_Pos)        /*!< Select BPWM1 clock source from HCLK \hideinitializer */
#define CLK_CLKSEL2_BPWM1SEL_PCLK1       (0x1UL << CLK_CLKSEL2_BPWM1SEL_Pos)        /*!< Select BPWM1 clock source from PCLK1 \hideinitializer */

#define CLK_CLKSEL2_QSPI1SEL_HXT         (0x0UL << CLK_CLKSEL2_QSPI1SEL_Pos)        /*!< Select QSPI1 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL2_QSPI1SEL_PLL_DIV2    (0x1UL << CLK_CLKSEL2_QSPI1SEL_Pos)        /*!< Select QSPI1 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL2_QSPI1SEL_PCLK1       (0x2UL << CLK_CLKSEL2_QSPI1SEL_Pos)        /*!< Select QSPI1 clock source from PCLK1 \hideinitializer */
#define CLK_CLKSEL2_QSPI1SEL_HIRC        (0x3UL << CLK_CLKSEL2_QSPI1SEL_Pos)        /*!< Select QSPI1 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL2_SPI1SEL_HXT          (0x0UL << CLK_CLKSEL2_SPI1SEL_Pos)         /*!< Select SPI1 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL2_SPI1SEL_PLL_DIV2     (0x1UL << CLK_CLKSEL2_SPI1SEL_Pos)         /*!< Select SPI1 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL2_SPI1SEL_PCLK0        (0x2UL << CLK_CLKSEL2_SPI1SEL_Pos)         /*!< Select SPI1 clock source from PCLK0 \hideinitializer */
#define CLK_CLKSEL2_SPI1SEL_HIRC         (0x3UL << CLK_CLKSEL2_SPI1SEL_Pos)         /*!< Select SPI1 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL2_SPI1SEL_HIRC48M      (0x4UL << CLK_CLKSEL2_SPI1SEL_Pos)         /*!< Select SPI1 clock source from HIRC48M \hideinitializer */
#define CLK_CLKSEL2_SPI1SEL_PLLFN_DIV2   (0x5UL << CLK_CLKSEL2_SPI1SEL_Pos)         /*!< Select SPI1 clock source from PLLFN/2 \hideinitializer */

#define CLK_CLKSEL2_I2S1SEL_HXT          (0x0UL << CLK_CLKSEL2_I2S1SEL_Pos)         /*!< Select I2S1 clock source from HXT \hideinitializer */
#define CLK_CLKSEL2_I2S1SEL_PLL_DIV2     (0x1UL << CLK_CLKSEL2_I2S1SEL_Pos)         /*!< Select I2S1 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL2_I2S1SEL_PCLK1        (0x2UL << CLK_CLKSEL2_I2S1SEL_Pos)         /*!< Select I2S1 clock source from PCLK1 \hideinitializer */
#define CLK_CLKSEL2_I2S1SEL_HIRC         (0x3UL << CLK_CLKSEL2_I2S1SEL_Pos)         /*!< Select I2S1 clock source from HIRC \hideinitializer */
#define CLK_CLKSEL2_I2S1SEL_HIRC48M      (0x4UL << CLK_CLKSEL2_I2S1SEL_Pos)         /*!< Select I2S1 clock source from HIRC48M \hideinitializer */
#define CLK_CLKSEL2_I2S1SEL_PLLFN_DIV2   (0x5UL << CLK_CLKSEL2_I2S1SEL_Pos)         /*!< Select I2S1 clock source from PLLFN/2 \hideinitializer */

#define CLK_CLKSEL2_UART8SEL_HXT         (0x0UL << CLK_CLKSEL2_UART8SEL_Pos)        /*!< Select UART8 clock source from HXT \hideinitializer */
#define CLK_CLKSEL2_UART8SEL_PLL_DIV2    (0x1UL << CLK_CLKSEL2_UART8SEL_Pos)        /*!< Select UART8 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL2_UART8SEL_LXT         (0x2UL << CLK_CLKSEL2_UART8SEL_Pos)        /*!< Select UART8 clock source from LXT \hideinitializer */
#define CLK_CLKSEL2_UART8SEL_HIRC        (0x3UL << CLK_CLKSEL2_UART8SEL_Pos)        /*!< Select UART8 clock source from HIRC \hideinitializer */

#define CLK_CLKSEL2_UART9SEL_HXT         (0x0UL << CLK_CLKSEL2_UART9SEL_Pos)        /*!< Select UART9 clock source from HXT \hideinitializer */
#define CLK_CLKSEL2_UART9SEL_PLL_DIV2    (0x1UL << CLK_CLKSEL2_UART9SEL_Pos)        /*!< Select UART9 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL2_UART9SEL_LXT         (0x2UL << CLK_CLKSEL2_UART9SEL_Pos)        /*!< Select UART9 clock source from LXT \hideinitializer */
#define CLK_CLKSEL2_UART9SEL_HIRC        (0x3UL << CLK_CLKSEL2_UART9SEL_Pos)        /*!< Select UART9 clock source from HIRC \hideinitializer */

#define CLK_CLKSEL2_TRNGSEL_LXT          (0x0UL << CLK_CLKSEL2_TRNGSEL_Pos)         /*!< Select TRNG clock source from LXT \hideinitializer */
#define CLK_CLKSEL2_TRNGSEL_LIRC         (0x1UL << CLK_CLKSEL2_TRNGSEL_Pos)         /*!< Select TRNG clock source from LIRC \hideinitializer */

#define CLK_CLKSEL2_PSIOSEL_HXT          (0x0UL << CLK_CLKSEL2_PSIOSEL_Pos)         /*!< Select PSIO clock source from LXT \hideinitializer */
#define CLK_CLKSEL2_PSIOSEL_LXT          (0x1UL << CLK_CLKSEL2_PSIOSEL_Pos)         /*!< Select PSIO clock source from LIRC \hideinitializer */
#define CLK_CLKSEL2_PSIOSEL_PCLK1        (0x2UL << CLK_CLKSEL2_PSIOSEL_Pos)         /*!< Select PSIO clock source from PCLK1 \hideinitializer */
#define CLK_CLKSEL2_PSIOSEL_PLL_DIV2     (0x3UL << CLK_CLKSEL2_PSIOSEL_Pos)         /*!< Select PSIO clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL2_PSIOSEL_LIRC         (0x4UL << CLK_CLKSEL2_PSIOSEL_Pos)         /*!< Select PSIO clock source from LIRC \hideinitializer */
#define CLK_CLKSEL2_PSIOSEL_HIRC         (0x5UL << CLK_CLKSEL2_PSIOSEL_Pos)         /*!< Select PSIO clock source from HIRC \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKSEL3 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKSEL3_SC0SEL_HXT           (0x0UL << CLK_CLKSEL3_SC0SEL_Pos)          /*!< Select SC0 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_SC0SEL_PLL_DIV2      (0x1UL << CLK_CLKSEL3_SC0SEL_Pos)          /*!< Select SC0 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL3_SC0SEL_PCLK0         (0x2UL << CLK_CLKSEL3_SC0SEL_Pos)          /*!< Select SC0 clock source from PCLK0 \hideinitializer */
#define CLK_CLKSEL3_SC0SEL_HIRC          (0x3UL << CLK_CLKSEL3_SC0SEL_Pos)          /*!< Select SC0 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL3_SC1SEL_HXT           (0x0UL << CLK_CLKSEL3_SC1SEL_Pos)          /*!< Select SC1 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_SC1SEL_PLL_DIV2      (0x1UL << CLK_CLKSEL3_SC1SEL_Pos)          /*!< Select SC1 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL3_SC1SEL_PCLK1         (0x2UL << CLK_CLKSEL3_SC1SEL_Pos)          /*!< Select SC1 clock source from PCLK1 \hideinitializer */
#define CLK_CLKSEL3_SC1SEL_HIRC          (0x3UL << CLK_CLKSEL3_SC1SEL_Pos)          /*!< Select SC1 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL3_SC2SEL_HXT           (0x0UL << CLK_CLKSEL3_SC2SEL_Pos)          /*!< Select SC2 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_SC2SEL_PLL_DIV2      (0x1UL << CLK_CLKSEL3_SC2SEL_Pos)          /*!< Select SC2 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL3_SC2SEL_PCLK0         (0x2UL << CLK_CLKSEL3_SC2SEL_Pos)          /*!< Select SC2 clock source from PCLK0 \hideinitializer */
#define CLK_CLKSEL3_SC2SEL_HIRC          (0x3UL << CLK_CLKSEL3_SC2SEL_Pos)          /*!< Select SC2 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL3_KPISEL_HXT           (0x0UL << CLK_CLKSEL3_KPISEL_Pos)          /*!< Select KPI clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_KPISEL_LIRC          (0x1UL << CLK_CLKSEL3_KPISEL_Pos)          /*!< Select KPI clock source from low speed oscillator \hideinitializer */
#define CLK_CLKSEL3_KPISEL_HIRC          (0x2UL << CLK_CLKSEL3_KPISEL_Pos)          /*!< Select KPI clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL3_SPI2SEL_HXT          (0x0UL << CLK_CLKSEL3_SPI2SEL_Pos)         /*!< Select SPI2 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_SPI2SEL_PLL_DIV2     (0x1UL << CLK_CLKSEL3_SPI2SEL_Pos)         /*!< Select SPI2 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL3_SPI2SEL_PCLK1        (0x2UL << CLK_CLKSEL3_SPI2SEL_Pos)         /*!< Select SPI2 clock source from PCLK1 \hideinitializer */
#define CLK_CLKSEL3_SPI2SEL_HIRC         (0x3UL << CLK_CLKSEL3_SPI2SEL_Pos)         /*!< Select SPI2 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL3_SPI2SEL_HIRC48M      (0x4UL << CLK_CLKSEL3_SPI2SEL_Pos)         /*!< Select SPI2 clock source from HIRC48M \hideinitializer */
#define CLK_CLKSEL3_SPI2SEL_PLLFN_DIV2   (0x5UL << CLK_CLKSEL3_SPI2SEL_Pos)         /*!< Select SPI2 clock source from PLLFN/2 \hideinitializer */

#define CLK_CLKSEL3_SPI3SEL_HXT          (0x0UL << CLK_CLKSEL3_SPI3SEL_Pos)         /*!< Select SPI3 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_SPI3SEL_PLL_DIV2     (0x1UL << CLK_CLKSEL3_SPI3SEL_Pos)         /*!< Select SPI3 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL3_SPI3SEL_PCLK0        (0x2UL << CLK_CLKSEL3_SPI3SEL_Pos)         /*!< Select SPI3 clock source from PCLK0 \hideinitializer */
#define CLK_CLKSEL3_SPI3SEL_HIRC         (0x3UL << CLK_CLKSEL3_SPI3SEL_Pos)         /*!< Select SPI3 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL3_SPI3SEL_HIRC48M      (0x4UL << CLK_CLKSEL3_SPI3SEL_Pos)         /*!< Select SPI3 clock source from HIRC48M \hideinitializer */
#define CLK_CLKSEL3_SPI3SEL_PLLFN_DIV2   (0x5UL << CLK_CLKSEL3_SPI3SEL_Pos)         /*!< Select SPI3 clock source from PLLFN/2 \hideinitializer */

#define CLK_CLKSEL3_I2S0SEL_HXT          (0x0UL << CLK_CLKSEL3_I2S0SEL_Pos)         /*!< Select I2S0 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_I2S0SEL_PLL_DIV2     (0x1UL << CLK_CLKSEL3_I2S0SEL_Pos)         /*!< Select I2S0 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL3_I2S0SEL_PCLK0        (0x2UL << CLK_CLKSEL3_I2S0SEL_Pos)         /*!< Select I2S0 clock source from PCLK0 \hideinitializer */
#define CLK_CLKSEL3_I2S0SEL_HIRC         (0x3UL << CLK_CLKSEL3_I2S0SEL_Pos)         /*!< Select I2S0 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL3_I2S0SEL_HIRC48M      (0x4UL << CLK_CLKSEL3_I2S0SEL_Pos)         /*!< Select I2S0 clock source from HIRC48M \hideinitializer */
#define CLK_CLKSEL3_I2S0SEL_PLLFN_DIV2   (0x5UL << CLK_CLKSEL3_I2S0SEL_Pos)         /*!< Select I2S0 clock source from PLLFN/2 \hideinitializer */

#define CLK_CLKSEL3_UART6SEL_HXT         (0x0UL << CLK_CLKSEL3_UART6SEL_Pos)        /*!< Select UART6 clock source from HXT \hideinitializer */
#define CLK_CLKSEL3_UART6SEL_PLL_DIV2    (0x1UL << CLK_CLKSEL3_UART6SEL_Pos)        /*!< Select UART6 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL3_UART6SEL_LXT         (0x2UL << CLK_CLKSEL3_UART6SEL_Pos)        /*!< Select UART6 clock source from LXT \hideinitializer */
#define CLK_CLKSEL3_UART6SEL_HIRC        (0x3UL << CLK_CLKSEL3_UART6SEL_Pos)        /*!< Select UART6 clock source from HIRC \hideinitializer */

#define CLK_CLKSEL3_UART7SEL_HXT         (0x0UL << CLK_CLKSEL3_UART7SEL_Pos)        /*!< Select UART7 clock source from HXT \hideinitializer */
#define CLK_CLKSEL3_UART7SEL_PLL_DIV2    (0x1UL << CLK_CLKSEL3_UART7SEL_Pos)        /*!< Select UART7 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL3_UART7SEL_LXT         (0x2UL << CLK_CLKSEL3_UART7SEL_Pos)        /*!< Select UART7 clock source from LXT \hideinitializer */
#define CLK_CLKSEL3_UART7SEL_HIRC        (0x3UL << CLK_CLKSEL3_UART7SEL_Pos)        /*!< Select UART7 clock source from HIRC \hideinitializer */

#define CLK_CLKSEL3_UART2SEL_HXT         (0x0UL << CLK_CLKSEL3_UART2SEL_Pos)        /*!< Select UART2 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART2SEL_PLL_DIV2    (0x1UL << CLK_CLKSEL3_UART2SEL_Pos)        /*!< Select UART2 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL3_UART2SEL_LXT         (0x2UL << CLK_CLKSEL3_UART2SEL_Pos)        /*!< Select UART2 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART2SEL_HIRC        (0x3UL << CLK_CLKSEL3_UART2SEL_Pos)        /*!< Select UART2 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL3_UART3SEL_HXT         (0x0UL << CLK_CLKSEL3_UART3SEL_Pos)        /*!< Select UART3 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART3SEL_PLL_DIV2    (0x1UL << CLK_CLKSEL3_UART3SEL_Pos)        /*!< Select UART3 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL3_UART3SEL_LXT         (0x2UL << CLK_CLKSEL3_UART3SEL_Pos)        /*!< Select UART3 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART3SEL_HIRC        (0x3UL << CLK_CLKSEL3_UART3SEL_Pos)        /*!< Select UART3 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL3_UART4SEL_HXT         (0x0UL << CLK_CLKSEL3_UART4SEL_Pos)        /*!< Select UART4 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART4SEL_PLL_DIV2    (0x1UL << CLK_CLKSEL3_UART4SEL_Pos)        /*!< Select UART4 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL3_UART4SEL_LXT         (0x2UL << CLK_CLKSEL3_UART4SEL_Pos)        /*!< Select UART4 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART4SEL_HIRC        (0x3UL << CLK_CLKSEL3_UART4SEL_Pos)        /*!< Select UART4 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL3_UART5SEL_HXT         (0x0UL << CLK_CLKSEL3_UART5SEL_Pos)        /*!< Select UART5 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART5SEL_PLL_DIV2    (0x1UL << CLK_CLKSEL3_UART5SEL_Pos)        /*!< Select UART5 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL3_UART5SEL_LXT         (0x2UL << CLK_CLKSEL3_UART5SEL_Pos)        /*!< Select UART5 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART5SEL_HIRC        (0x3UL << CLK_CLKSEL3_UART5SEL_Pos)        /*!< Select UART5 clock source from high speed oscillator \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKSEL4 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKSEL4_SPI4SEL_HXT          (0x0UL << CLK_CLKSEL4_SPI4SEL_Pos)         /*!< Select SPI4 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL4_SPI4SEL_PLL_DIV2     (0x1UL << CLK_CLKSEL4_SPI4SEL_Pos)         /*!< Select SPI4 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL4_SPI4SEL_PCLK1        (0x2UL << CLK_CLKSEL4_SPI4SEL_Pos)         /*!< Select SPI4 clock source from PCLK1 \hideinitializer */
#define CLK_CLKSEL4_SPI4SEL_HIRC         (0x3UL << CLK_CLKSEL4_SPI4SEL_Pos)         /*!< Select SPI4 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL4_SPI5SEL_HXT          (0x0UL << CLK_CLKSEL4_SPI5SEL_Pos)         /*!< Select SPI5 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL4_SPI5SEL_PLL_DIV2     (0x1UL << CLK_CLKSEL4_SPI5SEL_Pos)         /*!< Select SPI5 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL4_SPI5SEL_PCLK0        (0x2UL << CLK_CLKSEL4_SPI5SEL_Pos)         /*!< Select SPI5 clock source from PCLK0 \hideinitializer */
#define CLK_CLKSEL4_SPI5SEL_HIRC         (0x3UL << CLK_CLKSEL4_SPI5SEL_Pos)         /*!< Select SPI5 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL4_SPI6SEL_HXT          (0x0UL << CLK_CLKSEL4_SPI6SEL_Pos)         /*!< Select SPI6 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL4_SPI6SEL_PLL_DIV2     (0x1UL << CLK_CLKSEL4_SPI6SEL_Pos)         /*!< Select SPI6 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL4_SPI6SEL_PCLK1        (0x2UL << CLK_CLKSEL4_SPI6SEL_Pos)         /*!< Select SPI6 clock source from PCLK1 \hideinitializer */
#define CLK_CLKSEL4_SPI6SEL_HIRC         (0x3UL << CLK_CLKSEL4_SPI6SEL_Pos)         /*!< Select SPI6 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL4_SPI7SEL_HXT          (0x0UL << CLK_CLKSEL4_SPI7SEL_Pos)         /*!< Select SPI7 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL4_SPI7SEL_PLL_DIV2     (0x1UL << CLK_CLKSEL4_SPI7SEL_Pos)         /*!< Select SPI7 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL4_SPI7SEL_PCLK0        (0x2UL << CLK_CLKSEL4_SPI7SEL_Pos)         /*!< Select SPI7 clock source from PCLK0 \hideinitializer */
#define CLK_CLKSEL4_SPI7SEL_HIRC         (0x3UL << CLK_CLKSEL4_SPI7SEL_Pos)         /*!< Select SPI7 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL4_SPI8SEL_HXT          (0x0UL << CLK_CLKSEL4_SPI8SEL_Pos)         /*!< Select SPI8 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL4_SPI8SEL_PLL_DIV2     (0x1UL << CLK_CLKSEL4_SPI8SEL_Pos)         /*!< Select SPI8 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL4_SPI8SEL_PCLK1        (0x2UL << CLK_CLKSEL4_SPI8SEL_Pos)         /*!< Select SPI8 clock source from PCLK1 \hideinitializer */
#define CLK_CLKSEL4_SPI8SEL_HIRC         (0x3UL << CLK_CLKSEL4_SPI8SEL_Pos)         /*!< Select SPI8 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL4_SPI9SEL_HXT          (0x0UL << CLK_CLKSEL4_SPI9SEL_Pos)         /*!< Select SPI9 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL4_SPI9SEL_PLL_DIV2     (0x1UL << CLK_CLKSEL4_SPI9SEL_Pos)         /*!< Select SPI9 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL4_SPI9SEL_PCLK0        (0x2UL << CLK_CLKSEL4_SPI9SEL_Pos)         /*!< Select SPI9 clock source from PCLK0 \hideinitializer */
#define CLK_CLKSEL4_SPI9SEL_HIRC         (0x3UL << CLK_CLKSEL4_SPI9SEL_Pos)         /*!< Select SPI9 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL4_SPI10SEL_HXT         (0x0UL << CLK_CLKSEL4_SPI10SEL_Pos)        /*!< Select SPI10 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL4_SPI10SEL_PLL_DIV2    (0x1UL << CLK_CLKSEL4_SPI10SEL_Pos)        /*!< Select SPI10 clock source from PLL/2 \hideinitializer */
#define CLK_CLKSEL4_SPI10SEL_PCLK1       (0x2UL << CLK_CLKSEL4_SPI10SEL_Pos)        /*!< Select SPI10 clock source from PCLK1 \hideinitializer */
#define CLK_CLKSEL4_SPI10SEL_HIRC        (0x3UL << CLK_CLKSEL4_SPI10SEL_Pos)        /*!< Select SPI10 clock source from high speed oscillator \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  RTC clock source constant definitions.                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
#define RTC_LXTCTL_RTCCKSEL_LXT          (0x0UL<<RTC_LXTCTL_RTCCKSEL_Pos)           /*!< Setting RTC clock source as LXT \hideinitializer */
#define RTC_LXTCTL_RTCCKSEL_LIRC         (0x1UL<<RTC_LXTCTL_RTCCKSEL_Pos)           /*!< Setting RTC clock source as LIRC \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV0 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV0_HCLK(x)              (((x) - 1UL) << CLK_CLKDIV0_HCLKDIV_Pos)   /*!< CLKDIV0 Setting for HCLK clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV0_USB(x)               (((x) - 1UL) << CLK_CLKDIV0_USBDIV_Pos)    /*!< CLKDIV0 Setting for USB clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV0_SDH0(x)              (((x) - 1UL) << CLK_CLKDIV0_SDH0DIV_Pos)   /*!< CLKDIV0 Setting for SDH0 clock divider. It could be 1~256 \hideinitializer */
#define CLK_CLKDIV0_UART0(x)             (((x) - 1UL) << CLK_CLKDIV0_UART0DIV_Pos)  /*!< CLKDIV0 Setting for UART0 clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV0_UART1(x)             (((x) - 1UL) << CLK_CLKDIV0_UART1DIV_Pos)  /*!< CLKDIV0 Setting for UART1 clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV0_EADC0(x)             (((x) - 1UL) << CLK_CLKDIV0_EADC0DIV_Pos)  /*!< CLKDIV0 Setting for EADC0 clock divider. It could be 1~256 \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV1 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV1_SC0(x)               (((x) - 1UL) << CLK_CLKDIV1_SC0DIV_Pos)    /*!< CLKDIV1 Setting for SC0 clock divider. It could be 1~256 \hideinitializer */
#define CLK_CLKDIV1_SC1(x)               (((x) - 1UL) << CLK_CLKDIV1_SC1DIV_Pos)    /*!< CLKDIV1 Setting for SC1 clock divider. It could be 1~256 \hideinitializer */
#define CLK_CLKDIV1_SC2(x)               (((x) - 1UL) << CLK_CLKDIV1_SC2DIV_Pos)    /*!< CLKDIV1 Setting for SC2 clock divider. It could be 1~256 \hideinitializer */
#define CLK_CLKDIV1_PSIO(x)              (((x) - 1UL) << CLK_CLKDIV1_PSIODIV_Pos)   /*!< CLKDIV1 Setting for PSIO clock divider. It could be 1~256 \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV2 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV2_I2S0(x)              (((x) - 1UL) << CLK_CLKDIV2_I2S0DIV_Pos)   /*!< CLKDIV2 Setting for I2S0 clock divider. It could be 1~16 */
#define CLK_CLKDIV2_I2S1(x)              (((x) - 1UL) << CLK_CLKDIV2_I2S1DIV_Pos)   /*!< CLKDIV2 Setting for I2S1 clock divider. It could be 1~16 */
#define CLK_CLKDIV2_KPI(x)               (((x) - 1UL) << CLK_CLKDIV2_KPIDIV_Pos)    /*!< CLKDIV2 Setting for KPI clock divider. It could be 1~256 */
#define CLK_CLKDIV2_EADC1(x)             (((x) - 1UL) << CLK_CLKDIV2_EADC1DIV_Pos)  /*!< CLKDIV2 Setting for EADC1 clock divider. It could be 1~256 */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV3 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV3_VSENSE(x)            (((x) - 1UL) << CLK_CLKDIV3_VSENSEDIV_Pos) /*!< CLKDIV3 Setting for VSENSE clock divider. It could be 1~256 \hideinitializer */
#define CLK_CLKDIV3_EMAC0(x)             (((x) - 1UL) << CLK_CLKDIV3_EMAC0DIV_Pos)  /*!< CLKDIV3 Setting for EMAC0 clock divider. It could be 1~256 \hideinitializer */
#define CLK_CLKDIV3_SDH1(x)              (((x) - 1UL) << CLK_CLKDIV3_SDH1DIV_Pos)   /*!< CLKDIV3 Setting for SDH1 clock divider. It could be 1~256 \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV4 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV4_UART2(x)             (((x) - 1UL) << CLK_CLKDIV4_UART2DIV_Pos)  /*!< CLKDIV4 Setting for UART2 clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV4_UART3(x)             (((x) - 1UL) << CLK_CLKDIV4_UART3DIV_Pos)  /*!< CLKDIV4 Setting for UART3 clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV4_UART4(x)             (((x) - 1UL) << CLK_CLKDIV4_UART4DIV_Pos)  /*!< CLKDIV4 Setting for UART4 clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV4_UART5(x)             (((x) - 1UL) << CLK_CLKDIV4_UART5DIV_Pos)  /*!< CLKDIV4 Setting for UART5 clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV4_UART6(x)             (((x) - 1UL) << CLK_CLKDIV4_UART6DIV_Pos)  /*!< CLKDIV4 Setting for UART6 clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV4_UART7(x)             (((x) - 1UL) << CLK_CLKDIV4_UART7DIV_Pos)  /*!< CLKDIV4 Setting for UART7 clock divider. It could be 1~16 \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV5 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV5_CANFD0(x)            (((x) - 1UL) << CLK_CLKDIV5_CANFD0DIV_Pos) /*!< CLKDIV5 Setting for CANFD0 clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV5_CANFD1(x)            (((x) - 1UL) << CLK_CLKDIV5_CANFD1DIV_Pos) /*!< CLKDIV5 Setting for CANFD1 clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV5_CANFD2(x)            (((x) - 1UL) << CLK_CLKDIV5_CANFD2DIV_Pos) /*!< CLKDIV5 Setting for CANFD2 clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV5_CANFD3(x)            (((x) - 1UL) << CLK_CLKDIV5_CANFD3DIV_Pos) /*!< CLKDIV5 Setting for CANFD3 clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV5_UART8(x)             (((x) - 1UL) << CLK_CLKDIV5_UART8DIV_Pos)  /*!< CLKDIV5 Setting for UART8 clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV5_UART9(x)             (((x) - 1UL) << CLK_CLKDIV5_UART9DIV_Pos)  /*!< CLKDIV5 Setting for UART9 clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV5_EADC2(x)             (((x) - 1UL) << CLK_CLKDIV5_EADC2DIV_Pos)  /*!< CLKDIV5 Setting for EADC2 clock divider. It could be 1~256 \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  PCLKDIV constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_PCLKDIV_PCLK0DIV1            (0x0UL << CLK_PCLKDIV_APB0DIV_Pos)  /*!< PCLKDIV Setting for PCLK0 = HCLK \hideinitializer */
#define CLK_PCLKDIV_PCLK0DIV2            (0x1UL << CLK_PCLKDIV_APB0DIV_Pos)  /*!< PCLKDIV Setting for PCLK0 = 1/2 HCLK \hideinitializer */
#define CLK_PCLKDIV_PCLK0DIV4            (0x2UL << CLK_PCLKDIV_APB0DIV_Pos)  /*!< PCLKDIV Setting for PCLK0 = 1/4 HCLK \hideinitializer */
#define CLK_PCLKDIV_PCLK0DIV8            (0x3UL << CLK_PCLKDIV_APB0DIV_Pos)  /*!< PCLKDIV Setting for PCLK0 = 1/8 HCLK \hideinitializer */
#define CLK_PCLKDIV_PCLK0DIV16           (0x4UL << CLK_PCLKDIV_APB0DIV_Pos)  /*!< PCLKDIV Setting for PCLK0 = 1/16 HCLK \hideinitializer */
#define CLK_PCLKDIV_PCLK1DIV1            (0x0UL << CLK_PCLKDIV_APB1DIV_Pos)  /*!< PCLKDIV Setting for PCLK1 = HCLK \hideinitializer */
#define CLK_PCLKDIV_PCLK1DIV2            (0x1UL << CLK_PCLKDIV_APB1DIV_Pos)  /*!< PCLKDIV Setting for PCLK1 = 1/2 HCLK \hideinitializer */
#define CLK_PCLKDIV_PCLK1DIV4            (0x2UL << CLK_PCLKDIV_APB1DIV_Pos)  /*!< PCLKDIV Setting for PCLK1 = 1/4 HCLK \hideinitializer */
#define CLK_PCLKDIV_PCLK1DIV8            (0x3UL << CLK_PCLKDIV_APB1DIV_Pos)  /*!< PCLKDIV Setting for PCLK1 = 1/8 HCLK \hideinitializer */
#define CLK_PCLKDIV_PCLK1DIV16           (0x4UL << CLK_PCLKDIV_APB1DIV_Pos)  /*!< PCLKDIV Setting for PCLK1 = 1/16 HCLK \hideinitializer */

#define CLK_PCLKDIV_APB0DIV_DIV1         (0x0UL << CLK_PCLKDIV_APB0DIV_Pos)  /*!< PCLKDIV Setting for PCLK0 = HCLK \hideinitializer */
#define CLK_PCLKDIV_APB0DIV_DIV2         (0x1UL << CLK_PCLKDIV_APB0DIV_Pos)  /*!< PCLKDIV Setting for PCLK0 = 1/2 HCLK \hideinitializer */
#define CLK_PCLKDIV_APB0DIV_DIV4         (0x2UL << CLK_PCLKDIV_APB0DIV_Pos)  /*!< PCLKDIV Setting for PCLK0 = 1/4 HCLK \hideinitializer */
#define CLK_PCLKDIV_APB0DIV_DIV8         (0x3UL << CLK_PCLKDIV_APB0DIV_Pos)  /*!< PCLKDIV Setting for PCLK0 = 1/8 HCLK \hideinitializer */
#define CLK_PCLKDIV_APB0DIV_DIV16        (0x4UL << CLK_PCLKDIV_APB0DIV_Pos)  /*!< PCLKDIV Setting for PCLK0 = 1/16 HCLK \hideinitializer */
#define CLK_PCLKDIV_APB1DIV_DIV1         (0x0UL << CLK_PCLKDIV_APB1DIV_Pos)  /*!< PCLKDIV Setting for PCLK1 = HCLK \hideinitializer */
#define CLK_PCLKDIV_APB1DIV_DIV2         (0x1UL << CLK_PCLKDIV_APB1DIV_Pos)  /*!< PCLKDIV Setting for PCLK1 = 1/2 HCLK \hideinitializer */
#define CLK_PCLKDIV_APB1DIV_DIV4         (0x2UL << CLK_PCLKDIV_APB1DIV_Pos)  /*!< PCLKDIV Setting for PCLK1 = 1/4 HCLK \hideinitializer */
#define CLK_PCLKDIV_APB1DIV_DIV8         (0x3UL << CLK_PCLKDIV_APB1DIV_Pos)  /*!< PCLKDIV Setting for PCLK1 = 1/8 HCLK \hideinitializer */
#define CLK_PCLKDIV_APB1DIV_DIV16        (0x4UL << CLK_PCLKDIV_APB1DIV_Pos)  /*!< PCLKDIV Setting for PCLK1 = 1/16 HCLK \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  PLLCTL constant definitions. PLL = FIN * 2 * NF / NR / NO                                              */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_PLLCTL_PLLSRC_HXT   0x00000000UL    /*!< For PLL clock source is HXT.  4MHz < FIN/NR < 8MHz \hideinitializer */
#define CLK_PLLCTL_PLLSRC_HIRC  0x00080000UL    /*!< For PLL clock source is HIRC. 4MHz < FIN/NR < 8MHz \hideinitializer */

#define CLK_PLLCTL_NF(x)        (((x)-2UL))       /*!< x must be constant and 2 <= x <= 513. 200MHz < FIN*2*NF/NR < 500MHz. \hideinitializer */
#define CLK_PLLCTL_NR(x)        (((x)-1UL)<<9)    /*!< x must be constant and 1 <= x <= 32.  4MHz < FIN/NR < 8MHz \hideinitializer */

#define CLK_PLLCTL_NO_1         0x0000UL        /*!< For output divider is 1 \hideinitializer */
#define CLK_PLLCTL_NO_2         0x4000UL        /*!< For output divider is 2 \hideinitializer */
#define CLK_PLLCTL_NO_4         0xC000UL        /*!< For output divider is 4 \hideinitializer */

#define CLK_PLLCTL_72MHz_HXT    (CLK_PLLCTL_PLLSRC_HXT  | CLK_PLLCTL_NR(3UL) | CLK_PLLCTL_NF( 36UL) | CLK_PLLCTL_NO_4) /*!< Predefined PLLCTL setting for 72MHz PLL output with HXT(12MHz X'tal) \hideinitializer */
#define CLK_PLLCTL_80MHz_HXT    (CLK_PLLCTL_PLLSRC_HXT  | CLK_PLLCTL_NR(3UL) | CLK_PLLCTL_NF( 40UL) | CLK_PLLCTL_NO_4) /*!< Predefined PLLCTL setting for 80MHz PLL output with HXT(12MHz X'tal) \hideinitializer */
#define CLK_PLLCTL_144MHz_HXT   (CLK_PLLCTL_PLLSRC_HXT  | CLK_PLLCTL_NR(2UL) | CLK_PLLCTL_NF( 24UL) | CLK_PLLCTL_NO_2) /*!< Predefined PLLCTL setting for 144MHz PLL output with HXT(12MHz X'tal) \hideinitializer */
#define CLK_PLLCTL_160MHz_HXT   (CLK_PLLCTL_PLLSRC_HXT  | CLK_PLLCTL_NR(3UL) | CLK_PLLCTL_NF( 40UL) | CLK_PLLCTL_NO_2) /*!< Predefined PLLCTL setting for 160MHz PLL output with HXT(12MHz X'tal) \hideinitializer */
#define CLK_PLLCTL_180MHz_HXT   (CLK_PLLCTL_PLLSRC_HXT  | CLK_PLLCTL_NR(3UL) | CLK_PLLCTL_NF( 45UL) | CLK_PLLCTL_NO_2) /*!< Predefined PLLCTL setting for 180MHz PLL output with HXT(12MHz X'tal) \hideinitializer */
#define CLK_PLLCTL_192MHz_HXT   (CLK_PLLCTL_PLLSRC_HXT  | CLK_PLLCTL_NR(2UL) | CLK_PLLCTL_NF( 32UL) | CLK_PLLCTL_NO_2) /*!< Predefined PLLCTL setting for 192MHz PLL output with HXT(12MHz X'tal) \hideinitializer */
#define CLK_PLLCTL_200MHz_HXT   (CLK_PLLCTL_PLLSRC_HXT  | CLK_PLLCTL_NR(3UL) | CLK_PLLCTL_NF( 25UL) | CLK_PLLCTL_NO_1) /*!< Predefined PLLCTL setting for 200MHz PLL output with HXT(12MHz X'tal) \hideinitializer */

#define CLK_PLLCTL_72MHz_HIRC   (CLK_PLLCTL_PLLSRC_HIRC | CLK_PLLCTL_NR(3UL) | CLK_PLLCTL_NF( 36UL) | CLK_PLLCTL_NO_4) /*!< Predefined PLLCTL setting for 72MHz PLL output with HIRC(12MHz IRC) \hideinitializer */
#define CLK_PLLCTL_80MHz_HIRC   (CLK_PLLCTL_PLLSRC_HIRC | CLK_PLLCTL_NR(3UL) | CLK_PLLCTL_NF( 40UL) | CLK_PLLCTL_NO_4) /*!< Predefined PLLCTL setting for 80MHz PLL output with HIRC(12MHz IRC) \hideinitializer */
#define CLK_PLLCTL_144MHz_HIRC  (CLK_PLLCTL_PLLSRC_HIRC | CLK_PLLCTL_NR(2UL) | CLK_PLLCTL_NF( 24UL) | CLK_PLLCTL_NO_2) /*!< Predefined PLLCTL setting for 144MHz PLL output with HIRC(12MHz IRC) \hideinitializer */
#define CLK_PLLCTL_160MHz_HIRC  (CLK_PLLCTL_PLLSRC_HIRC | CLK_PLLCTL_NR(3UL) | CLK_PLLCTL_NF( 40UL) | CLK_PLLCTL_NO_2) /*!< Predefined PLLCTL setting for 160MHz PLL output with HIRC(12MHz IRC) \hideinitializer */
#define CLK_PLLCTL_180MHz_HIRC  (CLK_PLLCTL_PLLSRC_HIRC | CLK_PLLCTL_NR(3UL) | CLK_PLLCTL_NF( 45UL) | CLK_PLLCTL_NO_2) /*!< Predefined PLLCTL setting for 180MHz PLL output with HIRC(12MHz IRC) \hideinitializer */
#define CLK_PLLCTL_192MHz_HIRC  (CLK_PLLCTL_PLLSRC_HIRC | CLK_PLLCTL_NR(2UL) | CLK_PLLCTL_NF( 32UL) | CLK_PLLCTL_NO_2) /*!< Predefined PLLCTL setting for 192MHz PLL output with HIRC(12MHz IRC) \hideinitializer */
#define CLK_PLLCTL_200MHz_HIRC  (CLK_PLLCTL_PLLSRC_HIRC | CLK_PLLCTL_NR(3UL) | CLK_PLLCTL_NF( 25UL) | CLK_PLLCTL_NO_1) /*!< Predefined PLLCTL setting for 200MHz PLL output with HIRC(12MHz IRC) \hideinitializer */
#define CLK_PLLCTL_384MHz_HIRC  (CLK_PLLCTL_PLLSRC_HIRC | CLK_PLLCTL_NR(2UL) | CLK_PLLCTL_NF( 48UL) | CLK_PLLCTL_NO_1) /*!< Predefined PLLCTL setting for 384MHz PLL output with HIRC(12MHz IRC) \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  PLLFNCTL constant definitions.                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_PLLFNCTL1_PLLSRC_HXT   0x00000000UL
#define CLK_PLLFNCTL1_PLLSRC_HIRC  CLK_PLLFNCTL1_PLLSRC_Msk

/*---------------------------------------------------------------------------------------------------------*/
/*  MODULE constant definitions.                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
/* APBCLK(31:29)|CLKSEL(28:26)|CLKSEL_Msk(25:22)|CLKSEL_Pos(21:17)|CLKDIV(16:14)|CLKDIV_Msk(13:10)|CLKDIV_Pos(9:5)|IP_EN_Pos(4:0) */

#define MODULE_APBCLK(x)        (((x) >>29) & 0x07UL)   /*!< Calculate AHBCLK/APBCLK offset on MODULE index, 0x0:AHBCLK0, 0x1:APBCLK0, 0x2:APBCLK1, 0x3:APBCLK2, 0x4:AHBCLK1 \hideinitializer */
#define MODULE_CLKSEL(x)        (((x) >>26) & 0x07UL)   /*!< Calculate CLKSEL offset on MODULE index, 0x0:CLKSEL0, 0x1:CLKSEL1, 0x2:CLKSEL2, 0x3:CLKSEL3, 0x4:CLKSEL4 \hideinitializer */
#define MODULE_CLKSEL_Msk(x)    (((x) >>22) & 0x0fUL)   /*!< Calculate CLKSEL mask offset on MODULE index \hideinitializer */
#define MODULE_CLKSEL_Pos(x)    (((x) >>17) & 0x1fUL)   /*!< Calculate CLKSEL position offset on MODULE index \hideinitializer */
#define MODULE_CLKDIV(x)        (((x) >>14) & 0x07UL)   /*!< Calculate APBCLK CLKDIV on MODULE index, 0x0:CLKDIV0, 0x1:CLKDIV1, 0x2:CLKDIV2, 0x3:CLKDIV3, 0x4:CLKDIV4, 0x5:CLKDIV5 \hideinitializer */
#define MODULE_CLKDIV_Msk(x)    (((x) >>10) & 0x0fUL)   /*!< Calculate CLKDIV mask offset on MODULE index \hideinitializer */
#define MODULE_CLKDIV_Pos(x)    (((x) >>5 ) & 0x1fUL)   /*!< Calculate CLKDIV position offset on MODULE index \hideinitializer */
#define MODULE_IP_EN_Pos(x)     (((x) >>0 ) & 0x1fUL)   /*!< Calculate APBCLK offset on MODULE index \hideinitializer */
#define MODULE_NoMsk            0x0UL                   /*!< Not mask on MODULE index \hideinitializer */
#define NA                      MODULE_NoMsk            /*!< Not Available \hideinitializer */

#define MODULE_APBCLK_ENC(x)        (((x) & 0x07UL) << 29)   /*!< MODULE index, 0x0:AHBCLK0, 0x1:APBCLK0, 0x2:APBCLK1, 0x3:APBCLK2 0x4:AHBCLK1 \hideinitializer */
#define MODULE_CLKSEL_ENC(x)        (((x) & 0x07UL) << 26)   /*!< CLKSEL offset on MODULE index, 0x0:CLKSEL0, 0x1:CLKSEL1, 0x2:CLKSEL2, 0x3:CLKSEL3, 0x4:CLKSEL4, 0x5:CLKSEL5 \hideinitializer */
#define MODULE_CLKSEL_Msk_ENC(x)    (((x) & 0x0fUL) << 22)   /*!< CLKSEL mask offset on MODULE index \hideinitializer */
#define MODULE_CLKSEL_Pos_ENC(x)    (((x) & 0x1fUL) << 17)   /*!< CLKSEL position offset on MODULE index \hideinitializer */
#define MODULE_CLKDIV_ENC(x)        (((x) & 0x07UL) << 14)   /*!< APBCLK CLKDIV on MODULE index, 0x0:CLKDIV0, 0x1:CLKDIV1, 0x2:CLKDIV2, 0x3:CLKDIV3, 0x4:CLKDIV4, 0x4:CLKDIV5 \hideinitializer */
#define MODULE_CLKDIV_Msk_ENC(x)    (((x) & 0x0fUL) << 10)   /*!< CLKDIV mask offset on MODULE index \hideinitializer */
#define MODULE_CLKDIV_Pos_ENC(x)    (((x) & 0x1fUL) <<  5)   /*!< CLKDIV position offset on MODULE index \hideinitializer */
#define MODULE_IP_EN_Pos_ENC(x)     (((x) & 0x1fUL) <<  0)   /*!< AHBCLK/APBCLK offset on MODULE index \hideinitializer */

/* AHBCLK0 */
#define PDMA0_MODULE   (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_PDMA0CKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< PDMA0 Module */

#define ISP_MODULE     (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_ISPCKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< ISP Module */

#define EBI_MODULE     (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_EBICKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< EBI Module */

#define ST_MODULE      (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_STCKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< ST Module */

#define EMAC0_MODULE   (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_EMAC0CKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(    NA)|MODULE_CLKSEL_Pos_ENC(  NA)|\
                        MODULE_CLKDIV_ENC( 3UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC(16UL))  /*!< EMAC0 Module */

#define SDH0_MODULE    (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_SDH0CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 0UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC(20UL)|\
                        MODULE_CLKDIV_ENC( 0UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC(24UL))  /*!< SDH0 Module */

#define CRC_MODULE     (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_CRCCKEN_Pos)|\
                        MODULE_CLKSEL_ENC( NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC( NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))         /*!< CRC Module */

#define CCAP_MODULE    (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_CCAPCKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 0UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC(16UL)|\
                        MODULE_CLKDIV_ENC( NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))         /*!< CCAP Module */

#define SEN_MODULE     (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_SENCKEN_Pos)|\
                        MODULE_CLKSEL_ENC( NA)|MODULE_CLKSEL_Msk_ENC(   NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC( 3UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC( 8UL))  /*!< SEN Module */

#define HSUSBD_MODULE  (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_HSUSBDCKEN_Pos)|\
                        MODULE_CLKSEL_ENC( NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC( NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))         /*!< HSUSBD Module */

#define HBI_MODULE     (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_HBICKEN_Pos)|\
                        MODULE_CLKSEL_ENC( NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC( NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))         /*!< HBI Module */

#define CRPT_MODULE    (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_CRPTCKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< CRPT Module */

#define KS_MODULE      (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_KSCKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< KS Module */

#define SPIM_MODULE    (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_SPIMCKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< SPIM Module */

#define FMCIDLE_MODULE (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_FMCIDLE_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< FMCIDLE Module */

#define USBH_MODULE    (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_USBHCKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 0UL)|MODULE_CLKSEL_Msk_ENC(  1UL)|MODULE_CLKSEL_Pos_ENC( 8UL)|\
                        MODULE_CLKDIV_ENC( 0UL)|MODULE_CLKDIV_Msk_ENC(0xFUL)|MODULE_CLKDIV_Pos_ENC( 4UL))   /*!< USBH Module */

#define SDH1_MODULE    (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_SDH1CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 0UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC(22UL)|\
                        MODULE_CLKDIV_ENC( 3UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC(24UL))  /*!< SDH1 Module */

#define PDMA1_MODULE   (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_PDMA1CKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< PDMA1 Module */

#define TRACE_MODULE   (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_TRACECKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< TRACE Module */

#define GPA_MODULE     (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_GPACKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< GPA Module */

#define GPB_MODULE     (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_GPBCKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< GPB Module */

#define GPC_MODULE     (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_GPCCKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< GPC Module */

#define GPD_MODULE     (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_GPDCKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< GPD Module */

#define GPE_MODULE     (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_GPECKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< GPE Module */

#define GPF_MODULE     (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_GPFCKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< GPF Module */

#define GPG_MODULE     (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_GPGCKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< GPG Module */

#define GPH_MODULE     (MODULE_APBCLK_ENC( 0UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK0_GPHCKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< GPH Module */

/* AHBCLK1 */
#define CANFD0_MODULE  (MODULE_APBCLK_ENC( 4UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK1_CANFD0CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 0UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC(24UL)|\
                        MODULE_CLKDIV_ENC( 5UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC( 0UL))  /*!< CANFD0 Module */

#define CANFD1_MODULE  (MODULE_APBCLK_ENC( 4UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK1_CANFD1CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 0UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC(26UL)|\
                        MODULE_CLKDIV_ENC( 5UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC( 4UL))  /*!< CANFD1 Module */

#define CANFD2_MODULE  (MODULE_APBCLK_ENC( 4UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK1_CANFD2CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 0UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC(28UL)|\
                        MODULE_CLKDIV_ENC( 5UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC( 8UL))  /*!< CANFD2 Module */

#define CANFD3_MODULE  (MODULE_APBCLK_ENC( 4UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK1_CANFD3CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 0UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC(30UL)|\
                        MODULE_CLKDIV_ENC( 5UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC(12UL))  /*!< CANFD3 Module */

#define GPI_MODULE     (MODULE_APBCLK_ENC( 4UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK1_GPICKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< GPI Module */

#define GPJ_MODULE     (MODULE_APBCLK_ENC( 4UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK1_GPJCKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< GPJ Module */

#define BMC_MODULE     (MODULE_APBCLK_ENC( 4UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_AHBCLK1_BMCCKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< BMC Module */

/* APBCLK0 */
#define WDT_MODULE     (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_WDTCKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 1UL)|MODULE_CLKSEL_Msk_ENC( 3UL)|MODULE_CLKSEL_Pos_ENC( 0UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(  NA)|MODULE_CLKDIV_Pos_ENC( NA))     /*!< WDT Module */

#define WWDT_MODULE    (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_WDTCKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 1UL)|MODULE_CLKSEL_Msk_ENC( 3UL)|MODULE_CLKSEL_Pos_ENC(30UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(  NA)|MODULE_CLKDIV_Pos_ENC(  NA))    /*!< WWDT Module */

#define RTC_MODULE     (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_RTCCKEN_Pos)|\
                        MODULE_CLKSEL_ENC( NA)|MODULE_CLKSEL_Msk_ENC( NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC( NA)|MODULE_CLKDIV_Msk_ENC( NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< RTC Module */

#define TMR0_MODULE    (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_TMR0CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 1UL)|MODULE_CLKSEL_Msk_ENC( 7UL)|MODULE_CLKSEL_Pos_ENC( 8UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(  NA)|MODULE_CLKDIV_Pos_ENC(  NA))    /*!< TMR0 Module */

#define TMR1_MODULE    (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_TMR1CKEN_Pos) |\
                        MODULE_CLKSEL_ENC( 1UL)|MODULE_CLKSEL_Msk_ENC( 7UL)|MODULE_CLKSEL_Pos_ENC(12UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(   NA))     /*!< TMR1 Module */

#define TMR2_MODULE    (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_TMR2CKEN_Pos) |\
                        MODULE_CLKSEL_ENC( 1UL)|MODULE_CLKSEL_Msk_ENC( 7UL)|MODULE_CLKSEL_Pos_ENC(16UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(    NA))    /*!< TMR2 Module */

#define TMR3_MODULE    (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_TMR3CKEN_Pos) |\
                        MODULE_CLKSEL_ENC( 1UL)|MODULE_CLKSEL_Msk_ENC( 7UL)|MODULE_CLKSEL_Pos_ENC(20UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(   NA))     /*!< TMR3 Module */

#define CLKO_MODULE    (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_CLKOCKEN_Pos) |\
                        MODULE_CLKSEL_ENC( 1UL)|MODULE_CLKSEL_Msk_ENC( 7UL)|MODULE_CLKSEL_Pos_ENC( 4UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(   NA))     /*!< CLKO Module */

#define ACMP01_MODULE  (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_ACMP01CKEN_Pos) |\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< ACMP01 Module */

#define I2C0_MODULE    (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_I2C0CKEN_Pos) |\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< I2C0 Module */

#define I2C1_MODULE    (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_I2C1CKEN_Pos) |\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< I2C1 Module */

#define I2C2_MODULE    (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_I2C2CKEN_Pos) |\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< I2C2 Module */

#define I2C3_MODULE    (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_I2C3CKEN_Pos) |\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< I2C3 Module */

#define QSPI0_MODULE   (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_QSPI0CKEN_Pos) |\
                        MODULE_CLKSEL_ENC( 2UL)|MODULE_CLKSEL_Msk_ENC( 3UL)|MODULE_CLKSEL_Pos_ENC( 2UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(  NA)|MODULE_CLKDIV_Pos_ENC(  NA))    /*!< QSPI0 Module */

#define SPI0_MODULE    (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_SPI0CKEN_Pos) |\
                        MODULE_CLKSEL_ENC( 2UL)|MODULE_CLKSEL_Msk_ENC( 7UL)|MODULE_CLKSEL_Pos_ENC( 4UL)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(   NA)|MODULE_CLKDIV_Pos_ENC(  NA))     /*!< SPI0 Module */

#define SPI1_MODULE    (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_SPI1CKEN_Pos) |\
                        MODULE_CLKSEL_ENC( 2UL)|MODULE_CLKSEL_Msk_ENC( 7UL)|MODULE_CLKSEL_Pos_ENC(12UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(  NA)|MODULE_CLKDIV_Pos_ENC(  NA))    /*!< SPI1 Module */

#define SPI2_MODULE    (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_SPI2CKEN_Pos) |\
                        MODULE_CLKSEL_ENC( 3UL)|MODULE_CLKSEL_Msk_ENC( 7UL)|MODULE_CLKSEL_Pos_ENC( 9UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(  NA)|MODULE_CLKDIV_Pos_ENC(  NA))    /*!< SPI2 Module */

#define UART0_MODULE   (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_UART0CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 1UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC(24UL)|\
                        MODULE_CLKDIV_ENC( 0UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC( 8UL))  /*!< UART0 Module */

#define UART1_MODULE   (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_UART1CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 1UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC(26UL)|\
                        MODULE_CLKDIV_ENC( 0UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC(12UL))  /*!< UART1 Module */

#define UART2_MODULE   (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_UART2CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 3UL)|MODULE_CLKSEL_Msk_ENC( 3UL)|MODULE_CLKSEL_Pos_ENC(24UL)|\
                        MODULE_CLKDIV_ENC( 4UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC( 0UL))  /*!< UART2 Module */

#define UART3_MODULE   (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_UART3CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 3UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC(26UL)|\
                        MODULE_CLKDIV_ENC( 4UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC( 4UL))  /*!< UART3 Module */

#define UART4_MODULE   (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_UART4CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 3UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC(28UL)|\
                        MODULE_CLKDIV_ENC( 4UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC( 8UL))  /*!< UART4 Module */

#define UART5_MODULE   (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_UART5CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 3UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC(30UL)|\
                        MODULE_CLKDIV_ENC( 4UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC(12UL))  /*!< UART5 Module */

#define UART6_MODULE   (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_UART6CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 3UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC(20UL)|\
                        MODULE_CLKDIV_ENC( 4UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC(16UL))  /*!< UART6 Module */

#define UART7_MODULE   (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_UART7CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 3UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC(22UL)|\
                        MODULE_CLKDIV_ENC( 4UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC(20UL))  /*!< UART7 Module */

#define OTG_MODULE     (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_OTGCKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 0UL)|MODULE_CLKSEL_Msk_ENC(  1UL)|MODULE_CLKSEL_Pos_ENC( 8UL)|\
                        MODULE_CLKDIV_ENC( 0UL)|MODULE_CLKDIV_Msk_ENC(0xFUL)|MODULE_CLKDIV_Pos_ENC( 4UL))   /*!< OTG Module */

#define USBD_MODULE    (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_USBDCKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 0UL)|MODULE_CLKSEL_Msk_ENC(  1UL)|MODULE_CLKSEL_Pos_ENC( 8UL)|\
                        MODULE_CLKDIV_ENC( 0UL)|MODULE_CLKDIV_Msk_ENC(0xFUL)|MODULE_CLKDIV_Pos_ENC( 4UL))   /*!< USBD Module */

#define EADC0_MODULE   (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_EADC0CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 0UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC(10UL)|\
                        MODULE_CLKDIV_ENC( 0UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC(16UL))  /*!< EADC0 Module */

#define I2S0_MODULE    (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_I2S0CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 3UL)|MODULE_CLKSEL_Msk_ENC(   7UL)|MODULE_CLKSEL_Pos_ENC(16UL)|\
                        MODULE_CLKDIV_ENC( 2UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC( 0UL))  /*!< I2S0 Module */

#define HSOTG_MODULE   (MODULE_APBCLK_ENC( 1UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK0_HSOTGCKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< HSOTG Module */

/* APBCLK1 */
#define SC0_MODULE     (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_SC0CKEN_Pos)  |\
                        MODULE_CLKSEL_ENC( 3UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC( 0UL)|\
                        MODULE_CLKDIV_ENC( 1UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC( 0UL))  /*!< SC0 Module */

#define SC1_MODULE     (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_SC1CKEN_Pos)  |\
                        MODULE_CLKSEL_ENC( 3UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC( 2UL)|\
                        MODULE_CLKDIV_ENC( 1UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC( 8UL))  /*!< SC1 Module */

#define SC2_MODULE     (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_SC2CKEN_Pos)  |\
                        MODULE_CLKSEL_ENC( 3UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC( 4UL)|\
                        MODULE_CLKDIV_ENC( 1UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC(16UL))  /*!< SC2 Module */

#define I2C4_MODULE    (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_I2C4CKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< I2C4 Module */

#define QSPI1_MODULE   (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_QSPI1CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 2UL)|MODULE_CLKSEL_Msk_ENC( 3UL)|MODULE_CLKSEL_Pos_ENC(10UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< QSPI1 Module */

#define SPI3_MODULE    (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_SPI3CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 3UL)|MODULE_CLKSEL_Msk_ENC( 7UL)|MODULE_CLKSEL_Pos_ENC(12UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< SPI3 Module */

#define SPI4_MODULE    (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_SPI4CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 4UL)|MODULE_CLKSEL_Msk_ENC( 7UL)|MODULE_CLKSEL_Pos_ENC( 0UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< SPI4 Module */

#define USCI0_MODULE   (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_USCI0CKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< USCI0 Module */

#define PSIO_MODULE    (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_PSIOCKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 2UL)|MODULE_CLKSEL_Msk_ENC(   7UL)|MODULE_CLKSEL_Pos_ENC(28UL)|\
                        MODULE_CLKDIV_ENC( 1UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC(24UL))  /*!< PSIO Module */

#define DAC_MODULE     (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_DACCKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< DAC Module */

#define ECAP2_MODULE   (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_ECAP2CKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< ECAP2 Module */

#define ECAP3_MODULE   (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_ECAP3CKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< ECAP3 Module */

#define EPWM0_MODULE   (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_EPWM0CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 2UL)|MODULE_CLKSEL_Msk_ENC( 1UL)|MODULE_CLKSEL_Pos_ENC( 0UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< EPWM0 Module */

#define EPWM1_MODULE   (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_EPWM1CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 2UL)|MODULE_CLKSEL_Msk_ENC( 1UL)|MODULE_CLKSEL_Pos_ENC( 1UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< EPWM1 Module */

#define BPWM0_MODULE   (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_BPWM0CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 2UL)|MODULE_CLKSEL_Msk_ENC( 1UL)|MODULE_CLKSEL_Pos_ENC( 8UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< BPWM0 Module */

#define BPWM1_MODULE   (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_BPWM1CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 2UL)|MODULE_CLKSEL_Msk_ENC( 1UL)|MODULE_CLKSEL_Pos_ENC( 9UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< BPWM1 Module */

#define EQEI0_MODULE   (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_EQEI0CKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< EQEI0 Module */

#define EQEI1_MODULE   (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_EQEI1CKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< EQEI1 Module */

#define EQEI2_MODULE   (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_EQEI2CKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< EQEI2 Module */

#define EQEI3_MODULE   (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_EQEI3CKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< EQEI3 Module */

#define TRNG_MODULE    (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_TRNGCKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 2UL)|MODULE_CLKSEL_Msk_ENC( 1UL)|MODULE_CLKSEL_Pos_ENC(27UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< TRNG Module */

#define ECAP0_MODULE   (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_ECAP0CKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< ECAP0 Module */

#define ECAP1_MODULE   (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_ECAP1CKEN_Pos)|\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< ECAP1 Module */

#define I2S1_MODULE    (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_I2S1CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 2UL)|MODULE_CLKSEL_Msk_ENC(   7UL)|MODULE_CLKSEL_Pos_ENC(16UL)|\
                        MODULE_CLKDIV_ENC( 2UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC( 4UL))  /*!< I2S1 Module */

#define EADC1_MODULE   (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK1_EADC1CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 0UL)|MODULE_CLKSEL_Msk_ENC( 3UL)|MODULE_CLKSEL_Pos_ENC(12UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< EADC1 Module */

/* APBCLK2 */
#define KPI_MODULE     (MODULE_APBCLK_ENC( 3UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK2_KPICKEN_Pos)  |\
                        MODULE_CLKSEL_ENC( 3UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC( 6UL)|\
                        MODULE_CLKDIV_ENC( 2UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC( 8UL))  /*!< KPI Module */

#define EADC2_MODULE   (MODULE_APBCLK_ENC( 3UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK2_EADC2CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 0UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC(14UL)|\
                        MODULE_CLKDIV_ENC( 2UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC(24UL))  /*!< EADC2 Module */

#define ACMP23_MODULE  (MODULE_APBCLK_ENC( 3UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK2_ACMP23CKEN_Pos)  |\
                        MODULE_CLKSEL_ENC(  NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< ACMP23 Module */

#define SPI5_MODULE    (MODULE_APBCLK_ENC( 3UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK2_SPI5CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 4UL)|MODULE_CLKSEL_Msk_ENC( 7UL)|MODULE_CLKSEL_Pos_ENC( 4UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< SPI5 Module */

#define SPI6_MODULE    (MODULE_APBCLK_ENC( 3UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK2_SPI6CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 4UL)|MODULE_CLKSEL_Msk_ENC( 7UL)|MODULE_CLKSEL_Pos_ENC( 8UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< SPI6 Module */

#define SPI7_MODULE    (MODULE_APBCLK_ENC( 3UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK2_SPI7CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 4UL)|MODULE_CLKSEL_Msk_ENC( 7UL)|MODULE_CLKSEL_Pos_ENC(12UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< SPI7 Module */

#define SPI8_MODULE    (MODULE_APBCLK_ENC( 3UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK2_SPI8CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 4UL)|MODULE_CLKSEL_Msk_ENC( 7UL)|MODULE_CLKSEL_Pos_ENC(16UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< SPI8 Module */

#define SPI9_MODULE    (MODULE_APBCLK_ENC( 3UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK2_SPI9CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 4UL)|MODULE_CLKSEL_Msk_ENC( 7UL)|MODULE_CLKSEL_Pos_ENC(20UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< SPI9 Module */

#define SPI10_MODULE   (MODULE_APBCLK_ENC( 3UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK2_SPI10CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 4UL)|MODULE_CLKSEL_Msk_ENC( 7UL)|MODULE_CLKSEL_Pos_ENC(24UL)|\
                        MODULE_CLKDIV_ENC(  NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))        /*!< SPI10 Module */

#define UART8_MODULE   (MODULE_APBCLK_ENC( 3UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK2_UART8CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 2UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC(20UL)|\
                        MODULE_CLKDIV_ENC( 5UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC(16UL))  /*!< UART8 Module */

#define UART9_MODULE   (MODULE_APBCLK_ENC( 3UL)|MODULE_IP_EN_Pos_ENC((uint32_t)CLK_APBCLK2_UART9CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 2UL)|MODULE_CLKSEL_Msk_ENC(   3UL)|MODULE_CLKSEL_Pos_ENC(22UL)|\
                        MODULE_CLKDIV_ENC( 5UL)|MODULE_CLKDIV_Msk_ENC(0x0FUL)|MODULE_CLKDIV_Pos_ENC(20UL))  /*!< UART9 Module */


/*---------------------------------------------------------------------------------------------------------*/
/*  PDMSEL constant definitions.                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_PMUCTL_PDMSEL_PD          (0x0UL << CLK_PMUCTL_PDMSEL_Pos)        /*!< Select power down mode is Power-down mode \hideinitializer */
#define CLK_PMUCTL_PDMSEL_LLPD        (0x1UL << CLK_PMUCTL_PDMSEL_Pos)        /*!< Select power down mode is Low leakage Power-down mode \hideinitializer */
#define CLK_PMUCTL_PDMSEL_FWPD        (0x2UL << CLK_PMUCTL_PDMSEL_Pos)        /*!< Select power down mode is Fast wake-up Power-down mode \hideinitializer */
#define CLK_PMUCTL_PDMSEL_SPD         (0x4UL << CLK_PMUCTL_PDMSEL_Pos)        /*!< Select power down mode is Standby Power-down mode \hideinitializer */
#define CLK_PMUCTL_PDMSEL_DPD         (0x6UL << CLK_PMUCTL_PDMSEL_Pos)        /*!< Select power down mode is Deep Power-down mode \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  WKTMRIS constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_PMUCTL_WKTMRIS_128          (0x0UL << CLK_PMUCTL_WKTMRIS_Pos)     /*!< Select Wake-up Timer Time-out Interval is 128 OSC10K clocks (12.8 ms) \hideinitializer */
#define CLK_PMUCTL_WKTMRIS_256          (0x1UL << CLK_PMUCTL_WKTMRIS_Pos)     /*!< Select Wake-up Timer Time-out Interval is 256 OSC10K clocks (25.6 ms) \hideinitializer */
#define CLK_PMUCTL_WKTMRIS_512          (0x2UL << CLK_PMUCTL_WKTMRIS_Pos)     /*!< Select Wake-up Timer Time-out Interval is 512 OSC10K clocks (51.2 ms) \hideinitializer */
#define CLK_PMUCTL_WKTMRIS_1024         (0x3UL << CLK_PMUCTL_WKTMRIS_Pos)     /*!< Select Wake-up Timer Time-out Interval is 1024 OSC10K clocks (102.4ms) \hideinitializer */
#define CLK_PMUCTL_WKTMRIS_4096         (0x4UL << CLK_PMUCTL_WKTMRIS_Pos)     /*!< Select Wake-up Timer Time-out Interval is 4096 OSC10K clocks (409.6ms) \hideinitializer */
#define CLK_PMUCTL_WKTMRIS_8192         (0x5UL << CLK_PMUCTL_WKTMRIS_Pos)     /*!< Select Wake-up Timer Time-out Interval is 8192 OSC10K clocks (819.2ms) \hideinitializer */
#define CLK_PMUCTL_WKTMRIS_16384        (0x6UL << CLK_PMUCTL_WKTMRIS_Pos)     /*!< Select Wake-up Timer Time-out Interval is 16384 OSC10K clocks (1638.4ms) \hideinitializer */
#define CLK_PMUCTL_WKTMRIS_65536        (0x7UL << CLK_PMUCTL_WKTMRIS_Pos)     /*!< Select Wake-up Timer Time-out Interval is 65536 OSC10K clocks (6553.6ms) \hideinitializer */
#define CLK_PMUCTL_WKTMRIS_131072       (0x8UL << CLK_PMUCTL_WKTMRIS_Pos)     /*!< Select Wake-up Timer Time-out Interval is 131072 OSC10K clocks (13107.2 ms) \hideinitializer */
#define CLK_PMUCTL_WKTMRIS_262144       (0x9UL << CLK_PMUCTL_WKTMRIS_Pos)     /*!< Select Wake-up Timer Time-out Interval is 262144 OSC10K clocks (26214.4 ms) \hideinitializer */
#define CLK_PMUCTL_WKTMRIS_524288       (0xaUL << CLK_PMUCTL_WKTMRIS_Pos)     /*!< Select Wake-up Timer Time-out Interval is 524288 OSC10K clocks (52428.8ms) \hideinitializer */
#define CLK_PMUCTL_WKTMRIS_1048576      (0xbUL << CLK_PMUCTL_WKTMRIS_Pos)     /*!< Select Wake-up Timer Time-out Interval is 1048576 OSC10K clocks (104857.6ms) \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  SWKDBCLKSEL constant definitions.                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_SWKDBCTL_SWKDBCLKSEL_1          (0x0UL << CLK_SWKDBCTL_SWKDBCLKSEL_Pos)     /*!< Select Standby Power-down Pin De-bounce Sampling Cycle is 1 clocks \hideinitializer */
#define CLK_SWKDBCTL_SWKDBCLKSEL_2          (0x1UL << CLK_SWKDBCTL_SWKDBCLKSEL_Pos)     /*!< Select Standby Power-down Pin De-bounce Sampling Cycle is 2 clocks \hideinitializer */
#define CLK_SWKDBCTL_SWKDBCLKSEL_4          (0x2UL << CLK_SWKDBCTL_SWKDBCLKSEL_Pos)     /*!< Select Standby Power-down Pin De-bounce Sampling Cycle is 4 clocks \hideinitializer */
#define CLK_SWKDBCTL_SWKDBCLKSEL_8          (0x3UL << CLK_SWKDBCTL_SWKDBCLKSEL_Pos)     /*!< Select Standby Power-down Pin De-bounce Sampling Cycle is 8 clocks \hideinitializer */
#define CLK_SWKDBCTL_SWKDBCLKSEL_16         (0x4UL << CLK_SWKDBCTL_SWKDBCLKSEL_Pos)     /*!< Select Standby Power-down Pin De-bounce Sampling Cycle is 16 clocks \hideinitializer */
#define CLK_SWKDBCTL_SWKDBCLKSEL_32         (0x5UL << CLK_SWKDBCTL_SWKDBCLKSEL_Pos)     /*!< Select Standby Power-down Pin De-bounce Sampling Cycle is 32 clocks \hideinitializer */
#define CLK_SWKDBCTL_SWKDBCLKSEL_64         (0x6UL << CLK_SWKDBCTL_SWKDBCLKSEL_Pos)     /*!< Select Standby Power-down Pin De-bounce Sampling Cycle is 64 clocks \hideinitializer */
#define CLK_SWKDBCTL_SWKDBCLKSEL_128        (0x7UL << CLK_SWKDBCTL_SWKDBCLKSEL_Pos)     /*!< Select Standby Power-down Pin De-bounce Sampling Cycle is 128 clocks \hideinitializer */
#define CLK_SWKDBCTL_SWKDBCLKSEL_256        (0x8UL << CLK_SWKDBCTL_SWKDBCLKSEL_Pos)     /*!< Select Standby Power-down Pin De-bounce Sampling Cycle is 256 clocks \hideinitializer */
#define CLK_SWKDBCTL_SWKDBCLKSEL_2x256      (0x9UL << CLK_SWKDBCTL_SWKDBCLKSEL_Pos)     /*!< Select Standby Power-down Pin De-bounce Sampling Cycle is 2x256 clocks \hideinitializer */
#define CLK_SWKDBCTL_SWKDBCLKSEL_4x256      (0xaUL << CLK_SWKDBCTL_SWKDBCLKSEL_Pos)     /*!< Select Standby Power-down Pin De-bounce Sampling Cycle is 4x256 clocks \hideinitializer */
#define CLK_SWKDBCTL_SWKDBCLKSEL_8x256      (0xbUL << CLK_SWKDBCTL_SWKDBCLKSEL_Pos)     /*!< Select Standby Power-down Pin De-bounce Sampling Cycle is 8x256 clocks \hideinitializer */
#define CLK_SWKDBCTL_SWKDBCLKSEL_16x256     (0xcUL << CLK_SWKDBCTL_SWKDBCLKSEL_Pos)     /*!< Select Standby Power-down Pin De-bounce Sampling Cycle is 16x256 clocks \hideinitializer */
#define CLK_SWKDBCTL_SWKDBCLKSEL_32x256     (0xdUL << CLK_SWKDBCTL_SWKDBCLKSEL_Pos)     /*!< Select Standby Power-down Pin De-bounce Sampling Cycle is 32x256 clocks \hideinitializer */
#define CLK_SWKDBCTL_SWKDBCLKSEL_64x256     (0xeUL << CLK_SWKDBCTL_SWKDBCLKSEL_Pos)     /*!< Select Standby Power-down Pin De-bounce Sampling Cycle is 64x256 clocks \hideinitializer */
#define CLK_SWKDBCTL_SWKDBCLKSEL_128x256    (0xfUL << CLK_SWKDBCTL_SWKDBCLKSEL_Pos)     /*!< Select Standby Power-down Pin De-bounce Sampling Cycle is 128x256 clocks \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  DPD Pin Rising/Falling Edge Wake-up Enable constant definitions.                                       */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_DPDWKPIN0_DISABLE    (0x0UL << CLK_PMUCTL_WKPINEN0_Pos)    /*!< Disable Wake-up pin0 (GPC.0) at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN0_RISING     (0x1UL << CLK_PMUCTL_WKPINEN0_Pos)    /*!< Enable Wake-up pin0 (GPC.0) rising edge at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN0_FALLING    (0x2UL << CLK_PMUCTL_WKPINEN0_Pos)    /*!< Enable Wake-up pin0 (GPC.0) falling edge at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN0_BOTHEDGE   (0x3UL << CLK_PMUCTL_WKPINEN0_Pos)    /*!< Enable Wake-up pin0 (GPC.0) both edge at Deep Power-down mode \hideinitializer */

#define CLK_DPDWKPIN1_DISABLE    (0x0UL << CLK_PMUCTL_WKPINEN1_Pos)    /*!< Disable Wake-up pin1 (GPB.0) at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN1_RISING     (0x1UL << CLK_PMUCTL_WKPINEN1_Pos)    /*!< Enable Wake-up pin1 (GPB.0) rising edge at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN1_FALLING    (0x2UL << CLK_PMUCTL_WKPINEN1_Pos)    /*!< Enable Wake-up pin1 (GPB.0) falling edge at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN1_BOTHEDGE   (0x3UL << CLK_PMUCTL_WKPINEN1_Pos)    /*!< Enable Wake-up pin1 (GPB.0) both edge at Deep Power-down mode \hideinitializer */

#define CLK_DPDWKPIN2_DISABLE    (0x0UL << CLK_PMUCTL_WKPINEN2_Pos)    /*!< Disable Wake-up pin2 (GPB.2) at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN2_RISING     (0x1UL << CLK_PMUCTL_WKPINEN2_Pos)    /*!< Enable Wake-up pin2 (GPB.2) rising edge at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN2_FALLING    (0x2UL << CLK_PMUCTL_WKPINEN2_Pos)    /*!< Enable Wake-up pin2 (GPB.2) falling edge at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN2_BOTHEDGE   (0x3UL << CLK_PMUCTL_WKPINEN2_Pos)    /*!< Enable Wake-up pin2 (GPB.2) both edge at Deep Power-down mode \hideinitializer */

#define CLK_DPDWKPIN3_DISABLE    (0x0UL << CLK_PMUCTL_WKPINEN3_Pos)    /*!< Disable Wake-up pin3 (GPB.12) at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN3_RISING     (0x1UL << CLK_PMUCTL_WKPINEN3_Pos)    /*!< Enable Wake-up pin3 (GPB.12) rising edge at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN3_FALLING    (0x2UL << CLK_PMUCTL_WKPINEN3_Pos)    /*!< Enable Wake-up pin3 (GPB.12) falling edge at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN3_BOTHEDGE   (0x3UL << CLK_PMUCTL_WKPINEN3_Pos)    /*!< Enable Wake-up pin3 (GPB.12) both edge at Deep Power-down mode \hideinitializer */

#define CLK_DPDWKPIN4_DISABLE    (0x0UL << CLK_PMUCTL_WKPINEN4_Pos)    /*!< Disable Wake-up pin4 (GPF.6) at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN4_RISING     (0x1UL << CLK_PMUCTL_WKPINEN4_Pos)    /*!< Enable Wake-up pin4 (GPF.6) rising edge at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN4_FALLING    (0x2UL << CLK_PMUCTL_WKPINEN4_Pos)    /*!< Enable Wake-up pin4 (GPF.6) falling edge at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN4_BOTHEDGE   (0x3UL << CLK_PMUCTL_WKPINEN4_Pos)    /*!< Enable Wake-up pin4 (GPF.6) both edge at Deep Power-down mode \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  SPD Pin Rising/Falling Edge Wake-up Enable constant definitions.                                       */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_SPDWKPIN_ENABLE         (0x1UL << 0)     /*!< Enable Standby Power-down Pin Wake-up \hideinitializer */
#define CLK_SPDWKPIN_RISING         (0x1UL << 1)     /*!< Standby Power-down Wake-up on Standby Power-down Pin rising edge \hideinitializer */
#define CLK_SPDWKPIN_FALLING        (0x1UL << 2)     /*!< Standby Power-down Wake-up on Standby Power-down Pin falling edge \hideinitializer */
#define CLK_SPDWKPIN_DEBOUNCEEN     (0x1UL << 8)     /*!< Enable Standby power-down pin De-bounce function \hideinitializer */
#define CLK_SPDWKPIN_DEBOUNCEDIS    (0x0UL << 8)     /*!< Disable Standby power-down pin De-bounce function \hideinitializer */

#define CLK_SPDSRETSEL_NO           (0x0UL << CLK_PMUCTL_SRETSEL_Pos)     /*!< No SRAM retention when chip enter SPD mode \hideinitializer */
#define CLK_SPDSRETSEL_16K          (0x1UL << CLK_PMUCTL_SRETSEL_Pos)     /*!< 16K SRAM retention when chip enter SPD mode \hideinitializer */
#define CLK_SPDSRETSEL_32K          (0x2UL << CLK_PMUCTL_SRETSEL_Pos)     /*!< 32K SRAM retention when chip enter SPD mode \hideinitializer */
#define CLK_SPDSRETSEL_64K          (0x3UL << CLK_PMUCTL_SRETSEL_Pos)     /*!< 64K SRAM retention when chip enter SPD mode \hideinitializer */
#define CLK_SPDSRETSEL_128K         (0x4UL << CLK_PMUCTL_SRETSEL_Pos)     /*!< 128K SRAM retention when chip enter SPD mode \hideinitializer */
#define CLK_SPDSRETSEL_256K         (0x5UL << CLK_PMUCTL_SRETSEL_Pos)     /*!< 256K SRAM retention when chip enter SPD mode \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* CLK Time-out Handler Constant Definitions                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_TIMEOUT_ERR             (-1)     /*!< Clock timeout error value \hideinitializer */

/*@}*/ /* end of group CLK_EXPORTED_CONSTANTS */

extern int32_t g_CLK_i32ErrCode;

/** @addtogroup CLK_EXPORTED_FUNCTIONS CLK Exported Functions
  @{
*/

/**
  * @brief      Disable Wake-up Timer
  * @param      None
  * @return     None
  * @details    This macro disables Wake-up timer at Standby or Deep Power-down mode.
  */
#define CLK_DISABLE_WKTMR()       (CLK->PMUCTL &= ~CLK_PMUCTL_WKTMREN_Msk)

/**
  * @brief      Enable Wake-up Timer
  * @param      None
  * @return     None
  * @details    This macro enables Wake-up timer at Standby or Deep Power-down mode.
  */
#define CLK_ENABLE_WKTMR()        (CLK->PMUCTL |= CLK_PMUCTL_WKTMREN_Msk)

/**
  * @brief      Disable DPD Mode Wake-up Pin 0
  * @param      None
  * @return     None
  * @details    This macro disables Wake-up pin 0 (GPC.0) at Deep Power-down mode.
  */
#define CLK_DISABLE_DPDWKPIN0()   (CLK->PMUCTL &= ~CLK_PMUCTL_WKPINEN0_Msk)

/**
  * @brief      Disable DPD Mode Wake-up Pin 1
  * @param      None
  * @return     None
  * @details    This macro disables Wake-up pin 1 (GPB.0) at Deep Power-down mode.
  */
#define CLK_DISABLE_DPDWKPIN1()   (CLK->PMUCTL &= ~CLK_PMUCTL_WKPINEN1_Msk)

/**
  * @brief      Disable DPD Mode Wake-up Pin 2
  * @param      None
  * @return     None
  * @details    This macro disables Wake-up pin 2 (GPB.2) at Deep Power-down mode.
  */
#define CLK_DISABLE_DPDWKPIN2()   (CLK->PMUCTL &= ~CLK_PMUCTL_WKPINEN2_Msk)

/**
  * @brief      Disable DPD Mode Wake-up Pin 3
  * @param      None
  * @return     None
  * @details    This macro disables Wake-up pin 3 (GPB.12) at Deep Power-down mode.
  */
#define CLK_DISABLE_DPDWKPIN3()   (CLK->PMUCTL &= ~CLK_PMUCTL_WKPINEN3_Msk)

/**
  * @brief      Disable DPD Mode Wake-up Pin 4
  * @param      None
  * @return     None
  * @details    This macro disables Wake-up pin 4 (GPF.6) at Deep Power-down mode.
  */
#define CLK_DISABLE_DPDWKPIN4()   (CLK->PMUCTL &= ~CLK_PMUCTL_WKPINEN4_Msk)

/**
  * @brief      Disable SPD Mode ACMP Wake-up
  * @param      None
  * @return     None
  * @details    This macro disables ACMP wake-up at Standby Power-down mode.
  */
#define CLK_DISABLE_SPDACMP()     (CLK->PMUCTL &= ~CLK_PMUCTL_ACMPSPWK_Msk)

/**
  * @brief      Enable SPD Mode ACMP Wake-up
  * @param      None
  * @return     None
  * @details    This macro enables ACMP wake-up at Standby Power-down mode.
  */
#define CLK_ENABLE_SPDACMP()      (CLK->PMUCTL |= CLK_PMUCTL_ACMPSPWK_Msk)

/**
  * @brief      Disable SPD and DPD Mode RTC Wake-up
  * @param      None
  * @return     None
  * @details    This macro disables RTC Wake-up at Standby or Deep Power-down mode.
  */
#define CLK_DISABLE_RTCWK()       (CLK->PMUCTL &= ~CLK_PMUCTL_RTCWKEN_Msk)

/**
  * @brief      Enable SPD and DPD Mode RTC Wake-up
  * @param      None
  * @return     None
  * @details    This macro enables RTC Wake-up at Standby or Deep Power-down mode.
  */
#define CLK_ENABLE_RTCWK()        (CLK->PMUCTL |= CLK_PMUCTL_RTCWKEN_Msk)

/**
 * @brief       Set Wake-up Timer Time-out Interval
 *
 * @param[in]   u32Interval   The Wake-up Timer Time-out Interval selection. It could be
 *                             - \ref CLK_PMUCTL_WKTMRIS_128
 *                             - \ref CLK_PMUCTL_WKTMRIS_256
 *                             - \ref CLK_PMUCTL_WKTMRIS_512
 *                             - \ref CLK_PMUCTL_WKTMRIS_1024
 *                             - \ref CLK_PMUCTL_WKTMRIS_4096
 *                             - \ref CLK_PMUCTL_WKTMRIS_8192
 *                             - \ref CLK_PMUCTL_WKTMRIS_16384
 *                             - \ref CLK_PMUCTL_WKTMRIS_65536
 *                             - \ref CLK_PMUCTL_WKTMRIS_131072
 *                             - \ref CLK_PMUCTL_WKTMRIS_262144
 *                             - \ref CLK_PMUCTL_WKTMRIS_524288
 *                             - \ref CLK_PMUCTL_WKTMRIS_1048576
 *
 * @return      None
 *
 * @details     This function set Wake-up Timer Time-out Interval.
 *
 * \hideinitializer
 */
#define CLK_SET_WKTMR_INTERVAL(u32Interval)   CLK->PMUCTL = (CLK->PMUCTL & (~CLK_PMUCTL_WKTMRIS_Msk)) | (u32Interval)

/**
 * @brief       Set De-bounce Sampling Cycle Time
 *
 * @param[in]   u32CycleSel   The de-bounce sampling cycle selection. It could be
 *                             - \ref CLK_SWKDBCTL_SWKDBCLKSEL_1
 *                             - \ref CLK_SWKDBCTL_SWKDBCLKSEL_2
 *                             - \ref CLK_SWKDBCTL_SWKDBCLKSEL_4
 *                             - \ref CLK_SWKDBCTL_SWKDBCLKSEL_8
 *                             - \ref CLK_SWKDBCTL_SWKDBCLKSEL_16
 *                             - \ref CLK_SWKDBCTL_SWKDBCLKSEL_32
 *                             - \ref CLK_SWKDBCTL_SWKDBCLKSEL_64
 *                             - \ref CLK_SWKDBCTL_SWKDBCLKSEL_128
 *                             - \ref CLK_SWKDBCTL_SWKDBCLKSEL_256
 *                             - \ref CLK_SWKDBCTL_SWKDBCLKSEL_2x256
 *                             - \ref CLK_SWKDBCTL_SWKDBCLKSEL_4x256
 *                             - \ref CLK_SWKDBCTL_SWKDBCLKSEL_8x256
 *                             - \ref CLK_SWKDBCTL_SWKDBCLKSEL_16x256
 *                             - \ref CLK_SWKDBCTL_SWKDBCLKSEL_32x256
 *                             - \ref CLK_SWKDBCTL_SWKDBCLKSEL_64x256
 *                             - \ref CLK_SWKDBCTL_SWKDBCLKSEL_128x256
 *
 * @return      None
 *
 * @details     This function set De-bounce Sampling Cycle Time for Standby Power-down pin wake-up.
 *
 * \hideinitializer
 */
#define CLK_SET_SPDDEBOUNCETIME(u32CycleSel)    (CLK->SWKDBCTL = (u32CycleSel))

/*---------------------------------------------------------------------------------------------------------*/
/* static inline functions                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
/* Declare these inline functions here to avoid MISRA C 2004 rule 8.1 error */
__STATIC_INLINE int32_t CLK_SysTickDelay(uint32_t us);
__STATIC_INLINE int32_t CLK_SysTickLongDelay(uint32_t us);

/**
  * @brief      This function execute delay function.
  * @param[in]  us  Delay time. The Max value is 2^24 / CPU Clock(MHz). Ex:
  *                             200MHz => 83886us, 180MHz => 93206us ...
  * @retval     0 Delay success. Target delay time reached.
  * @retval     CLK_TIMEOUT_ERR Delay function execute failed due to SysTick stop working.
  * @details    Use the SysTick to generate the delay time and the unit is in us.
  *             The SysTick clock source is from HCLK, i.e the same as system core clock.
  *             User can use SystemCoreClockUpdate() to calculate CyclesPerUs automatically before using this function.
  */
__STATIC_INLINE int32_t CLK_SysTickDelay(uint32_t us)
{
    /* The u32TimeOutCnt value must be greater than the max delay time of 1398ms if HCLK=12MHz */
    uint32_t u32TimeOutCnt = SystemCoreClock << 1; /* 2 second time-out */

    SysTick->LOAD = us * CyclesPerUs;
    SysTick->VAL  = (0x00);
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

    /* Waiting for down-count to zero */
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0)
    {
        if (--u32TimeOutCnt == 0)
        {
            break;
        }
    }

    /* Disable SysTick counter */
    SysTick->CTRL = 0;

    if (u32TimeOutCnt == 0)
        return CLK_TIMEOUT_ERR;
    else
        return 0;
}

/**
  * @brief      This function execute long delay function.
  * @param[in]  us  Delay time.
  * @retval     0 Delay success. Target delay time reached.
  * @retval     CLK_TIMEOUT_ERR Delay function execute failed due to SysTick stop working.
  * @details    Use the SysTick to generate the long delay time and the UNIT is in us.
  *             The SysTick clock source is from HCLK, i.e the same as system core clock.
  *             User can use SystemCoreClockUpdate() to calculate CyclesPerUs automatically before using this function.
  */
__STATIC_INLINE int32_t CLK_SysTickLongDelay(uint32_t us)
{
    /* The u32TimeOutCnt value must be greater than the max delay time of 1398ms if HCLK=12MHz */
    uint32_t u32Delay, u32TimeOutCnt;

    /* It should <= 65536us for each delay loop */
    u32Delay = 65536UL;

    do
    {
        if (us > u32Delay)
        {
            us -= u32Delay;
        }
        else
        {
            u32Delay = us;
            us = 0UL;
        }

        SysTick->LOAD = u32Delay * CyclesPerUs;
        SysTick->VAL  = (0x0UL);
        SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

        /* Waiting for down-count to zero */
        u32TimeOutCnt = SystemCoreClock << 1; /* 2 second time-out */
        while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0UL)
            if (--u32TimeOutCnt == 0) break;

        /* Disable SysTick counter */
        SysTick->CTRL = 0UL;
    }
    while ((us > 0UL) && (u32TimeOutCnt != 0));

    if (u32TimeOutCnt == 0)
        return CLK_TIMEOUT_ERR;
    else
        return 0;
}


void CLK_DisableCKO(void);
void CLK_EnableCKO(uint32_t u32ClkSrc, uint32_t u32ClkDiv, uint32_t u32ClkDivBy1En);
void CLK_PowerDown(void);
void CLK_Idle(void);
uint32_t CLK_GetHXTFreq(void);
uint32_t CLK_GetLXTFreq(void);
uint32_t CLK_GetHCLKFreq(void);
uint32_t CLK_GetPCLK0Freq(void);
uint32_t CLK_GetPCLK1Freq(void);
uint32_t CLK_GetCPUFreq(void);
uint32_t CLK_SetCoreClock(uint32_t u32Hclk);
void CLK_SetHCLK(uint32_t u32ClkSrc, uint32_t u32ClkDiv);
void CLK_SetModuleClock(uint32_t u32ModuleIdx, uint32_t u32ClkSrc, uint32_t u32ClkDiv);
void CLK_SetSysTickClockSrc(uint32_t u32ClkSrc);
void CLK_EnableXtalRC(uint32_t u32ClkMask);
void CLK_DisableXtalRC(uint32_t u32ClkMask);
void CLK_EnableModuleClock(uint32_t u32ModuleIdx);
void CLK_DisableModuleClock(uint32_t u32ModuleIdx);
uint32_t CLK_EnablePLL(uint32_t u32PllClkSrc, uint32_t u32PllFreq);
void CLK_DisablePLL(void);
uint32_t CLK_WaitClockReady(uint32_t u32ClkMask);
void CLK_EnableSysTick(uint32_t u32ClkSrc, uint32_t u32Count);
void CLK_DisableSysTick(void);
void CLK_SetPowerDownMode(uint32_t u32PDMode);
void CLK_EnableDPDWKPin(uint32_t u32TriggerType);
uint32_t CLK_GetPMUWKSrc(void);
void CLK_EnableSPDWKPin(uint32_t u32Port, uint32_t u32Pin, uint32_t u32TriggerType, uint32_t u32DebounceEn);
uint32_t CLK_GetPLLClockFreq(void);
uint32_t CLK_GetModuleClockSource(uint32_t u32ModuleIdx);
uint32_t CLK_GetModuleClockDivider(uint32_t u32ModuleIdx);
void CLK_DisablePLLFN(void);
uint32_t CLK_EnablePLLFN(uint32_t u32PllClkSrc, uint32_t u32PllFreq);
uint32_t CLK_GetPLLFNClockFreq(void);

/*@}*/ /* end of group CLK_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CLK_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif  /* __NU_CLK_H__ */
