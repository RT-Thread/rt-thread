/**************************************************************************//**
 * @file     CLK.h
 * @version  V1.0
 * @brief    M480 Series CLK Driver Header File
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
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


#define FREQ_25MHZ         25000000UL   /*!< 25 MHz \hideinitializer */
#define FREQ_50MHZ         50000000UL   /*!< 50 MHz \hideinitializer */
#define FREQ_72MHZ         72000000UL   /*!< 72 MHz \hideinitializer */
#define FREQ_80MHZ         80000000UL   /*!< 80 MHz \hideinitializer */
#define FREQ_100MHZ        100000000UL  /*!< 100 MHz \hideinitializer */
#define FREQ_125MHZ        125000000UL  /*!< 125 MHz \hideinitializer */
#define FREQ_160MHZ        160000000UL  /*!< 160 MHz \hideinitializer */
#define FREQ_192MHZ        192000000UL  /*!< 192 MHz \hideinitializer */
#define FREQ_200MHZ        200000000UL  /*!< 200 MHz \hideinitializer */
#define FREQ_250MHZ        250000000UL  /*!< 250 MHz \hideinitializer */
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
#define CLK_CLKSEL0_STCLKSEL_HCLK        (0x01UL << SysTick_CTRL_CLKSOURCE_Pos)     /*!< Select SysTick clock source from HCLK \hideinitializer */

#define CLK_CLKSEL0_CCAPSEL_HXT         (0x0UL << CLK_CLKSEL0_CCAPSEL_Pos)          /*!< Select CCAP clock source from HXT \hideinitializer */
#define CLK_CLKSEL0_CCAPSEL_PLL         (0x1UL << CLK_CLKSEL0_CCAPSEL_Pos)          /*!< Select CCAP clock source from PLL \hideinitializer */
#define CLK_CLKSEL0_CCAPSEL_HCLK        (0x2UL << CLK_CLKSEL0_CCAPSEL_Pos)          /*!< Select CCAP clock source from HCLK \hideinitializer */
#define CLK_CLKSEL0_CCAPSEL_HIRC        (0x3UL << CLK_CLKSEL0_CCAPSEL_Pos)          /*!< Select CCAP clock source from HIRC \hideinitializer */


#if(0)
#define CLK_CLKSEL0_PCLK0DIV1            (0x0UL << CLK_CLKSEL0_PCLK0SEL_Pos)        /*!< Select PCLK0 clock source from HCLK \hideinitializer */
#define CLK_CLKSEL0_PCLK0DIV2            (0x1UL << CLK_CLKSEL0_PCLK0SEL_Pos)        /*!< Select PCLK0 clock source from 1/2 HCLK \hideinitializer */

#define CLK_CLKSEL0_PCLK1DIV1            (0x0UL << CLK_CLKSEL0_PCLK1SEL_Pos)        /*!< Select PCLK1 clock source from HCLK \hideinitializer */
#define CLK_CLKSEL0_PCLK1DIV2            (0x1UL << CLK_CLKSEL0_PCLK1SEL_Pos)        /*!< Select PCLK1 clock source from 1/2 HCLK \hideinitializer */
#endif

#define CLK_CLKSEL0_CCAPSEL_HXT          (0x0UL << CLK_CLKSEL0_CCAPSEL_Pos)         /*!< Select CCAP clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL0_CCAPSEL_PLL          (0x1UL << CLK_CLKSEL0_CCAPSEL_Pos)         /*!< Select CCAP clock source from PLL \hideinitializer */
#define CLK_CLKSEL0_CCAPSEL_HIRC         (0x3UL << CLK_CLKSEL0_CCAPSEL_Pos)         /*!< Select CCAP clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL0_CCAPSEL_HCLK         (0x2UL << CLK_CLKSEL0_CCAPSEL_Pos)         /*!< Select CCAP clock source from HCLK \hideinitializer */

#define CLK_CLKSEL0_SDH0SEL_HXT          (0x0UL << CLK_CLKSEL0_SDH0SEL_Pos)         /*!< Select SDH0 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL0_SDH0SEL_PLL          (0x1UL << CLK_CLKSEL0_SDH0SEL_Pos)         /*!< Select SDH0 clock source from PLL \hideinitializer */
#define CLK_CLKSEL0_SDH0SEL_HIRC         (0x3UL << CLK_CLKSEL0_SDH0SEL_Pos)         /*!< Select SDH0 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL0_SDH0SEL_HCLK         (0x2UL << CLK_CLKSEL0_SDH0SEL_Pos)         /*!< Select SDH0 clock source from HCLK \hideinitializer */

#define CLK_CLKSEL0_SDH1SEL_HXT          (0x0UL << CLK_CLKSEL0_SDH1SEL_Pos)         /*!< Select SDH1 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL0_SDH1SEL_PLL          (0x1UL << CLK_CLKSEL0_SDH1SEL_Pos)         /*!< Select SDH1 clock source from PLL \hideinitializer */
#define CLK_CLKSEL0_SDH1SEL_HIRC         (0x3UL << CLK_CLKSEL0_SDH1SEL_Pos)         /*!< Select SDH1 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL0_SDH1SEL_HCLK         (0x2UL << CLK_CLKSEL0_SDH1SEL_Pos)         /*!< Select SDH1 clock source from HCLK \hideinitializer */

#define CLK_CLKSEL0_USBSEL_RC48M         (0x0UL << CLK_CLKSEL0_USBSEL_Pos)          /*!< Select USB clock source from RC48M \hideinitializer */
#define CLK_CLKSEL0_USBSEL_PLL           (0x1UL << CLK_CLKSEL0_USBSEL_Pos)          /*!< Select USB clock source from PLL \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKSEL1 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKSEL1_WDTSEL_LXT           (0x1UL << CLK_CLKSEL1_WDTSEL_Pos)          /*!< Select WDT clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL1_WDTSEL_LIRC          (0x3UL << CLK_CLKSEL1_WDTSEL_Pos)          /*!< Select WDT clock source from low speed oscillator \hideinitializer */
#define CLK_CLKSEL1_WDTSEL_HCLK_DIV2048  (0x2UL << CLK_CLKSEL1_WDTSEL_Pos)          /*!< Select WDT clock source from HCLK/2048 \hideinitializer */

#define CLK_CLKSEL1_TMR0SEL_HXT          (0x0UL << CLK_CLKSEL1_TMR0SEL_Pos)         /*!< Select TMR0 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL1_TMR0SEL_LXT          (0x1UL << CLK_CLKSEL1_TMR0SEL_Pos)         /*!< Select TMR0 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL1_TMR0SEL_LIRC         (0x5UL << CLK_CLKSEL1_TMR0SEL_Pos)         /*!< Select TMR0 clock source from low speed oscillator \hideinitializer */
#define CLK_CLKSEL1_TMR0SEL_HIRC         (0x7UL << CLK_CLKSEL1_TMR0SEL_Pos)         /*!< Select TMR0 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL1_TMR0SEL_PCLK0        (0x2UL << CLK_CLKSEL1_TMR0SEL_Pos)         /*!< Select TMR0 clock source from PCLK0 \hideinitializer */
#define CLK_CLKSEL1_TMR0SEL_EXT          (0x3UL << CLK_CLKSEL1_TMR0SEL_Pos)         /*!< Select TMR0 clock source from external trigger \hideinitializer */

#define CLK_CLKSEL1_TMR1SEL_HXT          (0x0UL << CLK_CLKSEL1_TMR1SEL_Pos)         /*!< Select TMR1 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL1_TMR1SEL_LXT          (0x1UL << CLK_CLKSEL1_TMR1SEL_Pos)         /*!< Select TMR1 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL1_TMR1SEL_LIRC         (0x5UL << CLK_CLKSEL1_TMR1SEL_Pos)         /*!< Select TMR1 clock source from low speed oscillator \hideinitializer */
#define CLK_CLKSEL1_TMR1SEL_HIRC         (0x7UL << CLK_CLKSEL1_TMR1SEL_Pos)         /*!< Select TMR1 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL1_TMR1SEL_PCLK0        (0x2UL << CLK_CLKSEL1_TMR1SEL_Pos)         /*!< Select TMR1 clock source from PCLK0 \hideinitializer */
#define CLK_CLKSEL1_TMR1SEL_EXT          (0x3UL << CLK_CLKSEL1_TMR1SEL_Pos)         /*!< Select TMR1 clock source from external trigger \hideinitializer */

#define CLK_CLKSEL1_TMR2SEL_HXT          (0x0UL << CLK_CLKSEL1_TMR2SEL_Pos)         /*!< Select TMR2 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL1_TMR2SEL_LXT          (0x1UL << CLK_CLKSEL1_TMR2SEL_Pos)         /*!< Select TMR2 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL1_TMR2SEL_LIRC         (0x5UL << CLK_CLKSEL1_TMR2SEL_Pos)         /*!< Select TMR2 clock source from low speed oscillator \hideinitializer */
#define CLK_CLKSEL1_TMR2SEL_HIRC         (0x7UL << CLK_CLKSEL1_TMR2SEL_Pos)         /*!< Select TMR2 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL1_TMR2SEL_PCLK1        (0x2UL << CLK_CLKSEL1_TMR2SEL_Pos)         /*!< Select TMR2 clock source from PCLK1 \hideinitializer */
#define CLK_CLKSEL1_TMR2SEL_EXT          (0x3UL << CLK_CLKSEL1_TMR2SEL_Pos)         /*!< Select TMR2 clock source from external trigger \hideinitializer */

#define CLK_CLKSEL1_TMR3SEL_HXT          (0x0UL << CLK_CLKSEL1_TMR3SEL_Pos)         /*!< Select TMR3 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL1_TMR3SEL_LXT          (0x1UL << CLK_CLKSEL1_TMR3SEL_Pos)         /*!< Select TMR3 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL1_TMR3SEL_LIRC         (0x5UL << CLK_CLKSEL1_TMR3SEL_Pos)         /*!< Select TMR3 clock source from low speed oscillator \hideinitializer */
#define CLK_CLKSEL1_TMR3SEL_HIRC         (0x7UL << CLK_CLKSEL1_TMR3SEL_Pos)         /*!< Select TMR3 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL1_TMR3SEL_PCLK1        (0x2UL << CLK_CLKSEL1_TMR3SEL_Pos)         /*!< Select TMR3 clock source from PCLK1 \hideinitializer */
#define CLK_CLKSEL1_TMR3SEL_EXT          (0x3UL << CLK_CLKSEL1_TMR3SEL_Pos)         /*!< Select TMR3 clock source from external trigger \hideinitializer */

#define CLK_CLKSEL1_UART0SEL_HXT         (0x0UL << CLK_CLKSEL1_UART0SEL_Pos)        /*!< Select UART0 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL1_UART0SEL_LXT         (0x2UL << CLK_CLKSEL1_UART0SEL_Pos)        /*!< Select UART0 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL1_UART0SEL_PLL         (0x1UL << CLK_CLKSEL1_UART0SEL_Pos)        /*!< Select UART0 clock source from PLL \hideinitializer */
#define CLK_CLKSEL1_UART0SEL_HIRC        (0x3UL << CLK_CLKSEL1_UART0SEL_Pos)        /*!< Select UART0 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL1_UART1SEL_HXT         (0x0UL << CLK_CLKSEL1_UART1SEL_Pos)        /*!< Select UART1 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL1_UART1SEL_LXT         (0x2UL << CLK_CLKSEL1_UART1SEL_Pos)        /*!< Select UART1 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL1_UART1SEL_PLL         (0x1UL << CLK_CLKSEL1_UART1SEL_Pos)        /*!< Select UART1 clock source from PLL \hideinitializer */
#define CLK_CLKSEL1_UART1SEL_HIRC        (0x3UL << CLK_CLKSEL1_UART1SEL_Pos)        /*!< Select UART1 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL1_CLKOSEL_HXT          (0x0UL << CLK_CLKSEL1_CLKOSEL_Pos)         /*!< Select CLKO clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL1_CLKOSEL_LXT          (0x1UL << CLK_CLKSEL1_CLKOSEL_Pos)         /*!< Select CLKO clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL1_CLKOSEL_HIRC         (0x3UL << CLK_CLKSEL1_CLKOSEL_Pos)         /*!< Select CLKO clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL1_CLKOSEL_HCLK         (0x2UL << CLK_CLKSEL1_CLKOSEL_Pos)         /*!< Select CLKO clock source from HCLK \hideinitializer */

#define CLK_CLKSEL1_WWDTSEL_LIRC         (0x3UL << CLK_CLKSEL1_WWDTSEL_Pos)         /*!< Select WWDT clock source from low speed oscillator \hideinitializer */
#define CLK_CLKSEL1_WWDTSEL_HCLK_DIV2048 (0x2UL << CLK_CLKSEL1_WWDTSEL_Pos)         /*!< Select WWDT clock source from HCLK/2048 \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/*  CLKSEL2 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKSEL2_QSPI0SEL_HXT         (0x0UL << CLK_CLKSEL2_QSPI0SEL_Pos)        /*!< Select QSPI0 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL2_QSPI0SEL_PLL         (0x1UL << CLK_CLKSEL2_QSPI0SEL_Pos)        /*!< Select QSPI0 clock source from PLL \hideinitializer */
#define CLK_CLKSEL2_QSPI0SEL_HIRC        (0x3UL << CLK_CLKSEL2_QSPI0SEL_Pos)        /*!< Select QSPI0 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL2_QSPI0SEL_PCLK0       (0x2UL << CLK_CLKSEL2_QSPI0SEL_Pos)        /*!< Select QSPI0 clock source from PCLK0 \hideinitializer */

#define CLK_CLKSEL2_SPI0SEL_HXT          (0x0UL << CLK_CLKSEL2_SPI0SEL_Pos)         /*!< Select SPI0 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL2_SPI0SEL_PLL          (0x1UL << CLK_CLKSEL2_SPI0SEL_Pos)         /*!< Select SPI0 clock source from PLL \hideinitializer */
#define CLK_CLKSEL2_SPI0SEL_HIRC         (0x3UL << CLK_CLKSEL2_SPI0SEL_Pos)         /*!< Select SPI0 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL2_SPI0SEL_PCLK1        (0x2UL << CLK_CLKSEL2_SPI0SEL_Pos)         /*!< Select SPI0 clock source from PCLK1 \hideinitializer */

#define CLK_CLKSEL2_SPI1SEL_HXT          (0x0UL << CLK_CLKSEL2_SPI1SEL_Pos)         /*!< Select SPI1 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL2_SPI1SEL_PLL          (0x1UL << CLK_CLKSEL2_SPI1SEL_Pos)         /*!< Select SPI1 clock source from PLL \hideinitializer */
#define CLK_CLKSEL2_SPI1SEL_HIRC         (0x3UL << CLK_CLKSEL2_SPI1SEL_Pos)         /*!< Select SPI1 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL2_SPI1SEL_PCLK0        (0x2UL << CLK_CLKSEL2_SPI1SEL_Pos)         /*!< Select SPI1 clock source from PCLK0 \hideinitializer */

#define CLK_CLKSEL2_EPWM0SEL_PLL         (0x0UL << CLK_CLKSEL2_EPWM0SEL_Pos)        /*!< Select EPWM0 clock source from PLL \hideinitializer */
#define CLK_CLKSEL2_EPWM0SEL_PCLK0       (0x1UL << CLK_CLKSEL2_EPWM0SEL_Pos)        /*!< Select EPWM0 clock source from PCLK0 \hideinitializer */

#define CLK_CLKSEL2_EPWM1SEL_PLL         (0x0UL << CLK_CLKSEL2_EPWM1SEL_Pos)        /*!< Select EPWM1 clock source from PLL \hideinitializer */
#define CLK_CLKSEL2_EPWM1SEL_PCLK1       (0x1UL << CLK_CLKSEL2_EPWM1SEL_Pos)        /*!< Select EPWM1 clock source from PCLK1 \hideinitializer */

#define CLK_CLKSEL2_BPWM0SEL_PLL         (0x0UL << CLK_CLKSEL2_BPWM0SEL_Pos)        /*!< Select BPWM0 clock source from PLL \hideinitializer */
#define CLK_CLKSEL2_BPWM0SEL_PCLK0       (0x1UL << CLK_CLKSEL2_BPWM0SEL_Pos)        /*!< Select BPWM0 clock source from PCLK0 \hideinitializer */

#define CLK_CLKSEL2_BPWM1SEL_PLL         (0x0UL << CLK_CLKSEL2_BPWM1SEL_Pos)        /*!< Select BPWM1 clock source from PLL \hideinitializer */
#define CLK_CLKSEL2_BPWM1SEL_PCLK1       (0x1UL << CLK_CLKSEL2_BPWM1SEL_Pos)        /*!< Select BPWM1 clock source from PCLK1 \hideinitializer */

#define CLK_CLKSEL2_SPI2SEL_HXT          (0x0UL << CLK_CLKSEL2_SPI2SEL_Pos)         /*!< Select SPI2 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL2_SPI2SEL_PLL          (0x1UL << CLK_CLKSEL2_SPI2SEL_Pos)         /*!< Select SPI2 clock source from PLL \hideinitializer */
#define CLK_CLKSEL2_SPI2SEL_HIRC         (0x3UL << CLK_CLKSEL2_SPI2SEL_Pos)         /*!< Select SPI2 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL2_SPI2SEL_PCLK1        (0x2UL << CLK_CLKSEL2_SPI2SEL_Pos)         /*!< Select SPI2 clock source from PCLK1 \hideinitializer */

#define CLK_CLKSEL2_SPI3SEL_HXT          (0x0UL << CLK_CLKSEL2_SPI3SEL_Pos)         /*!< Select SPI3 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL2_SPI3SEL_PLL          (0x1UL << CLK_CLKSEL2_SPI3SEL_Pos)         /*!< Select SPI3 clock source from PLL \hideinitializer */
#define CLK_CLKSEL2_SPI3SEL_HIRC         (0x3UL << CLK_CLKSEL2_SPI3SEL_Pos)         /*!< Select SPI3 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL2_SPI3SEL_PCLK0        (0x2UL << CLK_CLKSEL2_SPI3SEL_Pos)         /*!< Select SPI3 clock source from PCLK0 \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/*  CLKSEL3 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKSEL3_SC0SEL_HXT           (0x0UL << CLK_CLKSEL3_SC0SEL_Pos)          /*!< Select SC0 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_SC0SEL_PLL           (0x1UL << CLK_CLKSEL3_SC0SEL_Pos)          /*!< Select SC0 clock source from PLL \hideinitializer */
#define CLK_CLKSEL3_SC0SEL_HIRC          (0x3UL << CLK_CLKSEL3_SC0SEL_Pos)          /*!< Select SC0 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL3_SC0SEL_PCLK0         (0x2UL << CLK_CLKSEL3_SC0SEL_Pos)          /*!< Select SC0 clock source from PCLK0 \hideinitializer */

#define CLK_CLKSEL3_SC1SEL_HXT           (0x0UL << CLK_CLKSEL3_SC1SEL_Pos)          /*!< Select SC1 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_SC1SEL_PLL           (0x1UL << CLK_CLKSEL3_SC1SEL_Pos)          /*!< Select SC1 clock source from PLL \hideinitializer */
#define CLK_CLKSEL3_SC1SEL_HIRC          (0x3UL << CLK_CLKSEL3_SC1SEL_Pos)          /*!< Select SC1 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL3_SC1SEL_PCLK1         (0x2UL << CLK_CLKSEL3_SC1SEL_Pos)          /*!< Select SC1 clock source from PCLK1 \hideinitializer */

#define CLK_CLKSEL3_SC2SEL_HXT           (0x0UL << CLK_CLKSEL3_SC2SEL_Pos)          /*!< Select SC2 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_SC2SEL_PLL           (0x1UL << CLK_CLKSEL3_SC2SEL_Pos)          /*!< Select SC2 clock source from PLL \hideinitializer */
#define CLK_CLKSEL3_SC2SEL_HIRC          (0x3UL << CLK_CLKSEL3_SC2SEL_Pos)          /*!< Select SC2 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL3_SC2SEL_PCLK0         (0x2UL << CLK_CLKSEL3_SC2SEL_Pos)          /*!< Select SC2 clock source from PCLK0 \hideinitializer */

#define CLK_CLKSEL3_RTCSEL_LXT           (0x0UL << CLK_CLKSEL3_RTCSEL_Pos)          /*!< Select RTC clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL3_RTCSEL_LIRC          (0x1UL << CLK_CLKSEL3_RTCSEL_Pos)          /*!< Select RTC clock source from low speed oscillator \hideinitializer */

#define CLK_CLKSEL3_QSPI1SEL_HXT         (0x0UL << CLK_CLKSEL3_QSPI1SEL_Pos)        /*!< Select QSPI1 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_QSPI1SEL_PLL         (0x1UL << CLK_CLKSEL3_QSPI1SEL_Pos)        /*!< Select QSPI1 clock source from PLL \hideinitializer */
#define CLK_CLKSEL3_QSPI1SEL_HIRC        (0x3UL << CLK_CLKSEL3_QSPI1SEL_Pos)        /*!< Select QSPI1 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL3_QSPI1SEL_PCLK1       (0x2UL << CLK_CLKSEL3_QSPI1SEL_Pos)        /*!< Select QSPI1 clock source from PCLK1 \hideinitializer */

#define CLK_CLKSEL3_I2S0SEL_HXT          (0x0UL << CLK_CLKSEL3_I2S0SEL_Pos)         /*!< Select I2S0 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_I2S0SEL_PLL          (0x1UL << CLK_CLKSEL3_I2S0SEL_Pos)         /*!< Select I2S0 clock source from PLL \hideinitializer */
#define CLK_CLKSEL3_I2S0SEL_HIRC         (0x3UL << CLK_CLKSEL3_I2S0SEL_Pos)         /*!< Select I2S0 clock source from high speed oscillator \hideinitializer */
#define CLK_CLKSEL3_I2S0SEL_PCLK0        (0x2UL << CLK_CLKSEL3_I2S0SEL_Pos)         /*!< Select I2S0 clock source from PCLK0 \hideinitializer */

#define CLK_CLKSEL3_UART2SEL_HXT         (0x0UL << CLK_CLKSEL3_UART2SEL_Pos)        /*!< Select UART2 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART2SEL_LXT         (0x2UL << CLK_CLKSEL3_UART2SEL_Pos)        /*!< Select UART2 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART2SEL_PLL         (0x1UL << CLK_CLKSEL3_UART2SEL_Pos)        /*!< Select UART2 clock source from PLL \hideinitializer */
#define CLK_CLKSEL3_UART2SEL_HIRC        (0x3UL << CLK_CLKSEL3_UART2SEL_Pos)        /*!< Select UART2 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL3_UART3SEL_HXT         (0x0UL << CLK_CLKSEL3_UART3SEL_Pos)        /*!< Select UART3 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART3SEL_LXT         (0x2UL << CLK_CLKSEL3_UART3SEL_Pos)        /*!< Select UART3 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART3SEL_PLL         (0x1UL << CLK_CLKSEL3_UART3SEL_Pos)        /*!< Select UART3 clock source from PLL \hideinitializer */
#define CLK_CLKSEL3_UART3SEL_HIRC        (0x3UL << CLK_CLKSEL3_UART3SEL_Pos)        /*!< Select UART3 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL3_UART4SEL_HXT         (0x0UL << CLK_CLKSEL3_UART4SEL_Pos)        /*!< Select UART4 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART4SEL_LXT         (0x2UL << CLK_CLKSEL3_UART4SEL_Pos)        /*!< Select UART4 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART4SEL_PLL         (0x1UL << CLK_CLKSEL3_UART4SEL_Pos)        /*!< Select UART4 clock source from PLL \hideinitializer */
#define CLK_CLKSEL3_UART4SEL_HIRC        (0x3UL << CLK_CLKSEL3_UART4SEL_Pos)        /*!< Select UART4 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL3_UART5SEL_HXT         (0x0UL << CLK_CLKSEL3_UART5SEL_Pos)        /*!< Select UART5 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART5SEL_LXT         (0x2UL << CLK_CLKSEL3_UART5SEL_Pos)        /*!< Select UART5 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART5SEL_PLL         (0x1UL << CLK_CLKSEL3_UART5SEL_Pos)        /*!< Select UART5 clock source from PLL \hideinitializer */
#define CLK_CLKSEL3_UART5SEL_HIRC        (0x3UL << CLK_CLKSEL3_UART5SEL_Pos)        /*!< Select UART5 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL3_UART6SEL_HXT         (0x0UL << CLK_CLKSEL3_UART6SEL_Pos)        /*!< Select UART6 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART6SEL_LXT         (0x2UL << CLK_CLKSEL3_UART6SEL_Pos)        /*!< Select UART6 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART6SEL_PLL         (0x1UL << CLK_CLKSEL3_UART6SEL_Pos)        /*!< Select UART6 clock source from PLL \hideinitializer */
#define CLK_CLKSEL3_UART6SEL_HIRC        (0x3UL << CLK_CLKSEL3_UART6SEL_Pos)        /*!< Select UART6 clock source from high speed oscillator \hideinitializer */

#define CLK_CLKSEL3_UART7SEL_HXT         (0x0UL << CLK_CLKSEL3_UART7SEL_Pos)        /*!< Select UART7 clock source from high speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART7SEL_LXT         (0x2UL << CLK_CLKSEL3_UART7SEL_Pos)        /*!< Select UART7 clock source from low speed crystal \hideinitializer */
#define CLK_CLKSEL3_UART7SEL_PLL         (0x1UL << CLK_CLKSEL3_UART7SEL_Pos)        /*!< Select UART7 clock source from PLL \hideinitializer */
#define CLK_CLKSEL3_UART7SEL_HIRC        (0x3UL << CLK_CLKSEL3_UART7SEL_Pos)        /*!< Select UART7 clock source from high speed oscillator \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV0 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV0_HCLK(x)              (((x) - 1UL) << CLK_CLKDIV0_HCLKDIV_Pos)   /*!< CLKDIV0 Setting for HCLK clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV0_USB(x)               (((x) - 1UL) << CLK_CLKDIV0_USBDIV_Pos)    /*!< CLKDIV0 Setting for USB clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV0_SDH0(x)              (((x) - 1UL) << CLK_CLKDIV0_SDH0DIV_Pos)   /*!< CLKDIV0 Setting for SDH0 clock divider. It could be 1~256 \hideinitializer */
#define CLK_CLKDIV0_UART0(x)             (((x) - 1UL) << CLK_CLKDIV0_UART0DIV_Pos)  /*!< CLKDIV0 Setting for UART0 clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV0_UART1(x)             (((x) - 1UL) << CLK_CLKDIV0_UART1DIV_Pos)  /*!< CLKDIV0 Setting for UART1 clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV0_EADC(x)              (((x) - 1UL) << CLK_CLKDIV0_EADCDIV_Pos)   /*!< CLKDIV0 Setting for EADC clock divider. It could be 1~256 \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV1 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV1_SC0(x)               (((x) - 1UL) << CLK_CLKDIV1_SC0DIV_Pos)    /*!< CLKDIV1 Setting for SC0 clock divider. It could be 1~256 \hideinitializer */
#define CLK_CLKDIV1_SC1(x)               (((x) - 1UL) << CLK_CLKDIV1_SC1DIV_Pos)    /*!< CLKDIV1 Setting for SC1 clock divider. It could be 1~256 \hideinitializer */
#define CLK_CLKDIV1_SC2(x)               (((x) - 1UL) << CLK_CLKDIV1_SC2DIV_Pos)    /*!< CLKDIV1 Setting for SC2 clock divider. It could be 1~256 \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV2 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV2_I2S0(x)              (((x) - 1UL) << CLK_CLKDIV2_I2SDIV_Pos)    /*!< CLKDIV2 Setting for I2S0 clock divider. It could be 1~16 */
#define CLK_CLKDIV2_EADC1(x)             (((x) - 1UL) << CLK_CLKDIV2_EADC1DIV_Pos)  /*!< CLKDIV2 Setting for EADC1 clock divider. It could be 1~256 */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV3 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV3_CCAP(x)              (((x) - 1UL) << CLK_CLKDIV3_CCAPDIV_Pos)   /*!< CLKDIV3 Setting for CCAP clock divider. It could be 1~256 */
#define CLK_CLKDIV3_VSENSE(x)            (((x) - 1UL) << CLK_CLKDIV3_VSENSEDIV_Pos) /*!< CLKDIV3 Setting for VSENSE clock divider. It could be 1~256 */
#define CLK_CLKDIV3_EMAC(x)              (((x) - 1UL) << CLK_CLKDIV3_EMACDIV_Pos)   /*!< CLKDIV3 Setting for EMAC clock divider. It could be 1~256 \hideinitializer */
#define CLK_CLKDIV3_SDH1(x)              (((x) - 1UL) << CLK_CLKDIV3_SDH1DIV_Pos)   /*!< CLKDIV3 Setting for SDH1 clock divider. It could be 1~256 \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV4 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV4_UART2(x)             (((x) - 1UL) << CLK_CLKDIV4_UART2DIV_Pos)  /*!< CLKDIV4 Setting for UART2 clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV4_UART3(x)             (((x) - 1UL) << CLK_CLKDIV4_UART3DIV_Pos)  /*!< CLKDIV4 Setting for UART3 clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV4_UART4(x)             (((x) - 1UL) << CLK_CLKDIV4_UART4DIV_Pos)  /*!< CLKDIV4 Setting for UART4 clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV4_UART5(x)             (((x) - 1UL) << CLK_CLKDIV4_UART5DIV_Pos)  /*!< CLKDIV4 Setting for UART5 clock divider. It could be 1~16 \hideinitializer */
#define CLK_CLKDIV4_UART6(x)             (((x) - 1UL) << CLK_CLKDIV4_UART6DIV_Pos)  /*!< CLKDIV4 Setting for UART6 clock divider. It could be 1~16 */
#define CLK_CLKDIV4_UART7(x)             (((x) - 1UL) << CLK_CLKDIV4_UART7DIV_Pos)  /*!< CLKDIV4 Setting for UART7 clock divider. It could be 1~16 */

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
// 
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
#define CLK_PLLCTL_192MHz_HXT   (CLK_PLLCTL_PLLSRC_HXT  | CLK_PLLCTL_NR(2UL) | CLK_PLLCTL_NF( 32UL) | CLK_PLLCTL_NO_2) /*!< Predefined PLLCTL setting for 192MHz PLL output with HXT(12MHz X'tal) \hideinitializer */

#define CLK_PLLCTL_72MHz_HIRC   (CLK_PLLCTL_PLLSRC_HIRC | CLK_PLLCTL_NR(3UL) | CLK_PLLCTL_NF( 36UL) | CLK_PLLCTL_NO_4) /*!< Predefined PLLCTL setting for 72MHz PLL output with HIRC(12MHz IRC) \hideinitializer */
#define CLK_PLLCTL_80MHz_HIRC   (CLK_PLLCTL_PLLSRC_HIRC | CLK_PLLCTL_NR(3UL) | CLK_PLLCTL_NF( 40UL) | CLK_PLLCTL_NO_4) /*!< Predefined PLLCTL setting for 80MHz PLL output with HIRC(12MHz IRC) \hideinitializer */
#define CLK_PLLCTL_144MHz_HIRC  (CLK_PLLCTL_PLLSRC_HIRC | CLK_PLLCTL_NR(2UL) | CLK_PLLCTL_NF( 24UL) | CLK_PLLCTL_NO_2) /*!< Predefined PLLCTL setting for 144MHz PLL output with HIRC(12MHz IRC) \hideinitializer */
#define CLK_PLLCTL_160MHz_HIRC  (CLK_PLLCTL_PLLSRC_HIRC | CLK_PLLCTL_NR(3UL) | CLK_PLLCTL_NF( 40UL) | CLK_PLLCTL_NO_2) /*!< Predefined PLLCTL setting for 160MHz PLL output with HIRC(12MHz IRC) \hideinitializer */
#define CLK_PLLCTL_192MHz_HIRC  (CLK_PLLCTL_PLLSRC_HIRC | CLK_PLLCTL_NR(2UL) | CLK_PLLCTL_NF( 32UL) | CLK_PLLCTL_NO_2) /*!< Predefined PLLCTL setting for 192MHz PLL output with HIRC(12MHz IRC) \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  MODULE constant definitions.                                                                           */
/*---------------------------------------------------------------------------------------------------------*/

/* APBCLK(31:30)|CLKSEL(29:28)|CLKSEL_Msk(27:25) |CLKSEL_Pos(24:20)|CLKDIV(19:18)|CLKDIV_Msk(17:10)|CLKDIV_Pos(9:5)|IP_EN_Pos(4:0) */

#define MODULE_APBCLK(x)        (((x) >>30) & 0x3UL)    /*!< Calculate AHBCLK/APBCLK offset on MODULE index, 0x0:AHBCLK, 0x1:APBCLK0, 0x2:APBCLK1 \hideinitializer */
#define MODULE_CLKSEL(x)        (((x) >>28) & 0x3UL)    /*!< Calculate CLKSEL offset on MODULE index, 0x0:CLKSEL0, 0x1:CLKSEL1, 0x2:CLKSEL2, 0x3:CLKSEL3 \hideinitializer */
#define MODULE_CLKSEL_Msk(x)    (((x) >>25) & 0x7UL)    /*!< Calculate CLKSEL mask offset on MODULE index \hideinitializer */
#define MODULE_CLKSEL_Pos(x)    (((x) >>20) & 0x1fUL)   /*!< Calculate CLKSEL position offset on MODULE index \hideinitializer */
#define MODULE_CLKDIV(x)        (((x) >>18) & 0x3UL)    /*!< Calculate APBCLK CLKDIV on MODULE index, 0x0:CLKDIV0, 0x1:CLKDIV1, 0x2:CLKDIV3, 0x3:CLKDIV4 \hideinitializer */
#define MODULE_CLKDIV_Msk(x)    (((x) >>10) & 0xffUL)   /*!< Calculate CLKDIV mask offset on MODULE index \hideinitializer */
#define MODULE_CLKDIV_Pos(x)    (((x) >>5 ) & 0x1fUL)   /*!< Calculate CLKDIV position offset on MODULE index \hideinitializer */
#define MODULE_IP_EN_Pos(x)     (((x) >>0 ) & 0x1fUL)   /*!< Calculate APBCLK offset on MODULE index \hideinitializer */
#define MODULE_NoMsk            0x0UL                   /*!< Not mask on MODULE index \hideinitializer */
#define NA                      MODULE_NoMsk            /*!< Not Available \hideinitializer */

#define MODULE_APBCLK_ENC(x)        (((x) & 0x03UL) << 30)   /*!< MODULE index, 0x0:AHBCLK, 0x1:APBCLK0, 0x2:APBCLK1 \hideinitializer */
#define MODULE_CLKSEL_ENC(x)        (((x) & 0x03UL) << 28)   /*!< CLKSEL offset on MODULE index, 0x0:CLKSEL0, 0x1:CLKSEL1, 0x2:CLKSEL2, 0x3:CLKSEL3 \hideinitializer */
#define MODULE_CLKSEL_Msk_ENC(x)    (((x) & 0x07UL) << 25)   /*!< CLKSEL mask offset on MODULE index \hideinitializer */
#define MODULE_CLKSEL_Pos_ENC(x)    (((x) & 0x1fUL) << 20)   /*!< CLKSEL position offset on MODULE index \hideinitializer */
#define MODULE_CLKDIV_ENC(x)        (((x) & 0x03UL) << 18)   /*!< APBCLK CLKDIV on MODULE index, 0x0:CLKDIV0, 0x1:CLKDIV1, 0x2:CLKDIV3, 0x3:CLKDIV4 \hideinitializer */
#define MODULE_CLKDIV_Msk_ENC(x)    (((x) & 0xffUL) << 10)   /*!< CLKDIV mask offset on MODULE index \hideinitializer */
#define MODULE_CLKDIV_Pos_ENC(x)    (((x) & 0x1fUL) <<  5)   /*!< CLKDIV position offset on MODULE index \hideinitializer */
#define MODULE_IP_EN_Pos_ENC(x)     (((x) & 0x1fUL) <<  0)   /*!< AHBCLK/APBCLK offset on MODULE index \hideinitializer */

#define PDMA_MODULE      ((0UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(1UL<<0))  /*!< PDMA Module \hideinitializer */
#define ISP_MODULE       ((0UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(2UL<<0))  /*!< ISP Module \hideinitializer */
#define EBI_MODULE       ((0UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(3UL<<0))  /*!< EBI Module \hideinitializer */
#define USBH_MODULE      ((0UL<<30)|(0UL<<28)         |(0x1UL<<25)       |(8UL<<20)         |(0UL<<18)         |(0xFUL<<10)       |(4UL<<5)         |(16UL<<0)) /*!< USBH Module \hideinitializer */
#define EMAC_MODULE      ((0UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(2UL<<18)         |(0xFFUL<<10)      |(16UL<<5)        |(5UL<<0))  /*!< EMAC Module \hideinitializer */
#define SDH0_MODULE      ((0UL<<30)|(0UL<<28)         |(0x3UL<<25)       |(20UL<<20)        |(0UL<<18)         |(0xFFUL<<10)      |(24UL<<5)        |(6UL<<0))  /*!< SDH0 Module \hideinitializer */
#define CRC_MODULE       ((0UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(7UL<<0))  /*!< CRC Module \hideinitializer */
#define CCAP_MODULE      ((0UL<<30)|(0UL<<28)         |(0x3UL<<25)       |(16UL<<20)        |(2UL<<18)         |(0xFFUL<<10)      |(0UL<<5)         |(8UL<<0))  /*!< CCAP Module \hideinitializer */
#define SEN_MODULE       ((0UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(9UL<<0))  /*!< SEN Module \hideinitializer */
#define HSUSBD_MODULE    ((0UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(10UL<<0)) /*!< HSUSBD Module \hideinitializer */
#define CRPT_MODULE      ((0UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(12UL<<0)) /*!< CRPT Module \hideinitializer */
#define SPIM_MODULE      ((0UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(14UL<<0)) /*!< SPIM Module \hideinitializer */
#define FMCIDLE_MODULE   ((0UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(15UL<<0)) /*!< FMCIDLE Module \hideinitializer */
#define SDH1_MODULE      ((0UL<<30)|(0UL<<28)         |(0x3UL<<25)       |(22UL<<20)        |(2UL<<18)         |(0xFFUL<<10)      |(24UL<<5)        |(17UL<<0)) /*!< SDH1 Module \hideinitializer */
#define WDT_MODULE       ((1UL<<30)|(1UL<<28)         |(0x3UL<<25)       |(0UL<<20)         |(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(0UL<<0))  /*!< WDT Module \hideinitializer */
#define RTC_MODULE       ((1UL<<30)|(3UL<<28)         |(0x1UL<<25)       |(8UL<<20)         |(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(1UL<<0))  /*!< RTC Module \hideinitializer */
#define TMR0_MODULE      ((1UL<<30)|(1UL<<28)         |(0x7UL<<25)       |(8UL<<20)         |(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(2UL<<0))  /*!< TMR0 Module \hideinitializer */
#define TMR1_MODULE      ((1UL<<30)|(1UL<<28)         |(0x7UL<<25)       |(12UL<<20)        |(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(3UL<<0))  /*!< TMR1 Module \hideinitializer */
#define TMR2_MODULE      ((1UL<<30)|(1UL<<28)         |(0x7UL<<25)       |(16UL<<20)        |(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(4UL<<0))  /*!< TMR2 Module \hideinitializer */
#define TMR3_MODULE      ((1UL<<30)|(1UL<<28)         |(0x7UL<<25)       |(20UL<<20)        |(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(5UL<<0))  /*!< TMR3 Module \hideinitializer */
#define CLKO_MODULE      ((1UL<<30)|(1UL<<28)         |(0x3UL<<25)       |(28UL<<20)        |(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(6UL<<0))  /*!< CLKO Module \hideinitializer */
#define WWDT_MODULE      ((1UL<<30)|(1UL<<28)         |(0x3UL<<25)       |(30UL<<20)        |(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(0UL<<0))  /*!< WWDT Module \hideinitializer */
#define ACMP01_MODULE    ((1UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(7UL<<0))  /*!< ACMP01 Module \hideinitializer */
#define I2C0_MODULE      ((1UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(8UL<<0))  /*!< I2C0 Module \hideinitializer */
#define I2C1_MODULE      ((1UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(9UL<<0))  /*!< I2C1 Module \hideinitializer */
#define I2C2_MODULE      ((1UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(10UL<<0)) /*!< I2C2 Module \hideinitializer */
#define QSPI0_MODULE     ((1UL<<30)|(2UL<<28)         |(0x3UL<<25)       |(2UL<<20)         |(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(12UL<<0)) /*!< QSPI0 Module \hideinitializer */
#define SPI0_MODULE      ((1UL<<30)|(2UL<<28)         |(0x3UL<<25)       |(4UL<<20)         |(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(13UL<<0)) /*!< SPI0 Module \hideinitializer */
#define SPI1_MODULE      ((1UL<<30)|(2UL<<28)         |(0x3UL<<25)       |(6UL<<20)         |(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(14UL<<0)) /*!< SPI1 Module \hideinitializer */
#define SPI2_MODULE      ((1UL<<30)|(2UL<<28)         |(0x3UL<<25)       |(10UL<<20)        |(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(15UL<<0)) /*!< SPI2 Module \hideinitializer */
#define UART0_MODULE     ((1UL<<30)|(1UL<<28)         |(0x3UL<<25)       |(24UL<<20)        |(0UL<<18)         |(0xFUL<<10)       |(8UL<<5)         |(16UL<<0)) /*!< UART0 Module \hideinitializer */
#define UART1_MODULE     ((1UL<<30)|(1UL<<28)         |(0x3UL<<25)       |(26UL<<20)        |(0UL<<18)         |(0xFUL<<10)       |(12UL<<5)        |(17UL<<0)) /*!< UART1 Module \hideinitializer */
#define UART2_MODULE     ((1UL<<30)|(3UL<<28)         |(0x3UL<<25)       |(24UL<<20)        |(3UL<<18)         |(0xFUL<<10)       |(0UL<<5)         |(18UL<<0)) /*!< UART2 Module \hideinitializer */
#define UART3_MODULE     ((1UL<<30)|(3UL<<28)         |(0x3UL<<25)       |(26UL<<20)        |(3UL<<18)         |(0xFUL<<10)       |(4UL<<5)         |(19UL<<0)) /*!< UART3 Module \hideinitializer */
#define UART4_MODULE     ((1UL<<30)|(3UL<<28)         |(0x3UL<<25)       |(28UL<<20)        |(3UL<<18)         |(0xFUL<<10)       |(8UL<<5)         |(20UL<<0)) /*!< UART4 Module \hideinitializer */
#define UART5_MODULE     ((1UL<<30)|(3UL<<28)         |(0x3UL<<25)       |(30UL<<20)        |(3UL<<18)         |(0xFUL<<10)       |(12UL<<5)        |(21UL<<0)) /*!< UART5 Module \hideinitializer */
#define UART6_MODULE     ((1UL<<30)|(3UL<<28)         |(0x3UL<<25)       |(20UL<<20)        |(3UL<<18)         |(0xFUL<<10)       |(16UL<<5)        |(22UL<<0)) /*!< UART6 Module \hideinitializer */
#define UART7_MODULE     ((1UL<<30)|(3UL<<28)         |(0x3UL<<25)       |(22UL<<20)        |(3UL<<18)         |(0xFUL<<10)       |(20UL<<5)        |(23UL<<0)) /*!< UART7 Module \hideinitializer */
#define CAN0_MODULE      ((1UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(24UL<<0)) /*!< CAN0 Module \hideinitializer */
#define CAN1_MODULE      ((1UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(25UL<<0)) /*!< CAN1 Module \hideinitializer */
#define OTG_MODULE       ((1UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(26UL<<0)) /*!< OTG Module \hideinitializer */
#define USBD_MODULE      ((1UL<<30)|(MODULE_NoMsk<<28)|(1UL<<25)         |(8UL<<20)         |(MODULE_NoMsk<<18)|(0xFUL<<10)       |(4UL<<5)         |(27UL<<0)) /*!< USBD Module \hideinitializer */
#define EADC_MODULE      ((1UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(0UL<<18)         |(0xFFUL<<10)      |(16UL<<5)        |(28UL<<0)) /*!< EADC Module \hideinitializer */
#define I2S0_MODULE      ((1UL<<30)|(3UL<<28)         |(0x3UL<<25)       |(16UL<<20)        |(2UL<<18)         |(0xFUL<<10)       |(0UL<<5)         |(29UL<<0)) /*!< I2S0 Module \hideinitializer */
#define HSOTG_MODULE     ((1UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(30UL<<0)) /*!< HSOTG Module \hideinitializer */
#define SC0_MODULE       ((2UL<<30)|(3UL<<28)         |(0x3UL<<25)       |(0UL<<20)         |(1UL<<18)         |(0xFFUL<<10)      |(0UL<<5)         |(0UL<<0))  /*!< SC0 Module \hideinitializer */
#define SC1_MODULE       ((2UL<<30)|(3UL<<28)         |(0x3UL<<25)       |(2UL<<20)         |(1UL<<18)         |(0xFFUL<<10)      |(8UL<<5)         |(1UL<<0))  /*!< SC1 Module \hideinitializer */
#define SC2_MODULE       ((2UL<<30)|(3UL<<28)         |(0x3UL<<25)       |(4UL<<20)         |(1UL<<18)         |(0xFFUL<<10)      |(16UL<<5)        |(2UL<<0))  /*!< SC2 Module \hideinitializer */
#define QSPI1_MODULE     ((2UL<<30)|(3UL<<28)         |(0x3UL<<25)       |(12UL<<20)        |(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(4UL<<0))  /*!< QSPI1 Module \hideinitializer */
#define SPI3_MODULE      ((2UL<<30)|(2UL<<28)         |(0x3UL<<25)       |(12UL<<20)        |(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(6UL<<0))  /*!< SPI3 Module \hideinitializer */
#define USCI0_MODULE     ((2UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(8UL<<0))  /*!< USCI0 Module \hideinitializer */
#define USCI1_MODULE     ((2UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(9UL<<0))  /*!< USCI1 Module \hideinitializer */
#define DAC_MODULE       ((2UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(12UL<<0)) /*!< DAC Module \hideinitializer */
#define CAN2_MODULE      ((2UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(28UL<<0)) /*!< CAN2 Module \hideinitializer */
#define EPWM0_MODULE     ((2UL<<30)|(2UL<<28)         |(0x1UL<<25)       |(0UL<<20)         |(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(16UL<<0)) /*!< EPWM0 Module \hideinitializer */
#define EPWM1_MODULE     ((2UL<<30)|(2UL<<28)         |(0x1UL<<25)       |(1UL<<20)         |(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(17UL<<0)) /*!< EPWM1 Module \hideinitializer */
#define BPWM0_MODULE     ((2UL<<30)|(2UL<<28)         |(0x1UL<<25)       |(8UL<<20)         |(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(18UL<<0)) /*!< BPWM0 Module \hideinitializer */
#define BPWM1_MODULE     ((2UL<<30)|(2UL<<28)         |(0x1UL<<25)       |(9UL<<20)         |(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(19UL<<0)) /*!< BPWM1 Module \hideinitializer */
#define QEI0_MODULE      ((2UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(22UL<<0)) /*!< QEI0 Module \hideinitializer */
#define QEI1_MODULE      ((2UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(23UL<<0)) /*!< QEI1 Module \hideinitializer */
#define TRNG_MODULE      ((2UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(25UL<<0)) /*!< TRNG Module \hideinitializer */
#define ECAP0_MODULE     ((2UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(26UL<<0)) /*!< ECAP0 Module \hideinitializer */
#define ECAP1_MODULE     ((2UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(27UL<<0)) /*!< ECAP1 Module \hideinitializer */
#define OPA_MODULE       ((2UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(MODULE_NoMsk<<18)|(MODULE_NoMsk<<10)|(MODULE_NoMsk<<5)|(30UL<<0)) /*!< OPA Module \hideinitializer */
#define EADC1_MODULE     ((2UL<<30)|(MODULE_NoMsk<<28)|(MODULE_NoMsk<<25)|(MODULE_NoMsk<<20)|(2UL<<18)         |(0xFFUL<<10)      |(24UL<<5)        |(31UL<<0)) /*!< EADC1 Module \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  PDMSEL constant definitions.                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_PMUCTL_PDMSEL_PD          (0x0UL << CLK_PMUCTL_PDMSEL_Pos)        /*!< Select power down mode is Power-down mode \hideinitializer */
#define CLK_PMUCTL_PDMSEL_LLPD        (0x1UL << CLK_PMUCTL_PDMSEL_Pos)        /*!< Select power down mode is Low leakage Power-down mode \hideinitializer */
#define CLK_PMUCTL_PDMSEL_FWPD        (0x2UL << CLK_PMUCTL_PDMSEL_Pos)        /*!< Select power down mode is Fast wake-up Power-down mode \hideinitializer */
#define CLK_PMUCTL_PDMSEL_SPD0        (0x4UL << CLK_PMUCTL_PDMSEL_Pos)        /*!< Select power down mode is Standby Power-down mode 0 \hideinitializer */
#define CLK_PMUCTL_PDMSEL_SPD1        (0x5UL << CLK_PMUCTL_PDMSEL_Pos)        /*!< Select power down mode is Standby Power-down mode 1 \hideinitializer */
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
#define CLK_DPDWKPIN_DISABLE     (0x0UL << CLK_PMUCTL_WKPINEN_Pos)     /*!< Disable Wake-up pin at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN_RISING      (0x1UL << CLK_PMUCTL_WKPINEN_Pos)     /*!< Enable Wake-up pin rising edge at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN_FALLING     (0x2UL << CLK_PMUCTL_WKPINEN_Pos)     /*!< Enable Wake-up pin falling edge at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN_BOTHEDGE    (0x3UL << CLK_PMUCTL_WKPINEN_Pos)     /*!< Enable Wake-up pin both edge at Deep Power-down mode \hideinitializer */

#define CLK_DPDWKPIN0_DISABLE    (0x0UL << CLK_PMUCTL_WKPINEN_Pos)     /*!< Disable Wake-up pin0 (GPC.0) at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN0_RISING     (0x1UL << CLK_PMUCTL_WKPINEN_Pos)     /*!< Enable Wake-up pin0 (GPC.0) rising edge at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN0_FALLING    (0x2UL << CLK_PMUCTL_WKPINEN_Pos)     /*!< Enable Wake-up pin0 (GPC.0) falling edge at Deep Power-down mode \hideinitializer */
#define CLK_DPDWKPIN0_BOTHEDGE   (0x3UL << CLK_PMUCTL_WKPINEN_Pos)     /*!< Enable Wake-up pin0 (GPC.0) both edge at Deep Power-down mode \hideinitializer */

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

#define CLK_DISABLE_WKTMR(void)       (CLK->PMUCTL &= ~CLK_PMUCTL_WKTMREN_Msk)    /*!< Disable Wake-up timer at Standby or Deep Power-down mode \hideinitializer */
#define CLK_ENABLE_WKTMR(void)        (CLK->PMUCTL |= CLK_PMUCTL_WKTMREN_Msk)     /*!< Enable Wake-up timer at Standby or Deep Power-down mode \hideinitializer */
#define CLK_DISABLE_DPDWKPIN(void)    (CLK->PMUCTL &= ~CLK_PMUCTL_WKPINEN_Msk)    /*!< Disable Wake-up pin at Deep Power-down mode \hideinitializer */
#define CLK_DISABLE_DPDWKPIN0(void)   (CLK->PMUCTL &= ~CLK_PMUCTL_WKPINEN_Msk)    /*!< Disable Wake-up pin0 (GPC.0) at Deep Power-down mode \hideinitializer */
#define CLK_DISABLE_DPDWKPIN1(void)   (CLK->PMUCTL &= ~CLK_PMUCTL_WKPINEN1_Msk)   /*!< Disable Wake-up pin1 (GPB.0) at Deep Power-down mode \hideinitializer */
#define CLK_DISABLE_DPDWKPIN2(void)   (CLK->PMUCTL &= ~CLK_PMUCTL_WKPINEN2_Msk)   /*!< Disable Wake-up pin2 (GPB.2) at Deep Power-down mode \hideinitializer */
#define CLK_DISABLE_DPDWKPIN3(void)   (CLK->PMUCTL &= ~CLK_PMUCTL_WKPINEN3_Msk)   /*!< Disable Wake-up pin3 (GPB.12) at Deep Power-down mode \hideinitializer */
#define CLK_DISABLE_DPDWKPIN4(void)   (CLK->PMUCTL &= ~CLK_PMUCTL_WKPINEN4_Msk)   /*!< Disable Wake-up pin4 (GPF.6) at Deep Power-down mode \hideinitializer */
#define CLK_DISABLE_SPDACMP(void)     (CLK->PMUCTL &= ~CLK_PMUCTL_ACMPSPWK_Msk)   /*!< Disable ACMP wake-up at Standby Power-down mode \hideinitializer */
#define CLK_ENABLE_SPDACMP(void)      (CLK->PMUCTL |= CLK_PMUCTL_ACMPSPWK_Msk)    /*!< Enable ACMP wake-up at Standby Power-down mode \hideinitializer */
#define CLK_DISABLE_RTCWK(void)       (CLK->PMUCTL &= ~CLK_PMUCTL_RTCWKEN_Msk)    /*!< Disable RTC Wake-up at Standby or Deep Power-down mode \hideinitializer */
#define CLK_ENABLE_RTCWK(void)        (CLK->PMUCTL |= CLK_PMUCTL_RTCWKEN_Msk)     /*!< Enable RTC Wake-up at Standby or Deep Power-down mode \hideinitializer */

/*@}*/ /* end of group CLK_EXPORTED_CONSTANTS */

/** @addtogroup CLK_EXPORTED_FUNCTIONS CLK Exported Functions
  @{
*/

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
#define CLK_SET_WKTMR_INTERVAL(u32Interval)   (CLK->PMUCTL |= (u32Interval))

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
 * @details     This function set Set De-bounce Sampling Cycle Time.
 *
 * \hideinitializer
 */
#define CLK_SET_SPDDEBOUNCETIME(u32CycleSel)    (CLK->SWKDBCTL = (u32CycleSel))

/*---------------------------------------------------------------------------------------------------------*/
/* static inline functions                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
/* Declare these inline functions here to avoid MISRA C 2004 rule 8.1 error */
__STATIC_INLINE void CLK_SysTickDelay(uint32_t us);
__STATIC_INLINE void CLK_SysTickLongDelay(uint32_t us);

/**
  * @brief      This function execute delay function.
  * @param[in]  us  Delay time. The Max value is 2^24 / CPU Clock(MHz). Ex:
  *                             72MHz => 233016us, 50MHz => 335544us,
  *                             48MHz => 349525us, 28MHz => 699050us ...
  * @return     None
  * @details    Use the SysTick to generate the delay time and the unit is in us.
  *             The SysTick clock source is from HCLK, i.e the same as system core clock.
  */
__STATIC_INLINE void CLK_SysTickDelay(uint32_t us)
{
    SysTick->LOAD = us * CyclesPerUs;
    SysTick->VAL  = 0x0UL;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

    /* Waiting for down-count to zero */
    while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0UL)
    {
    }

    /* Disable SysTick counter */
    SysTick->CTRL = 0UL;
}

/**
  * @brief      This function execute long delay function.
  * @param[in]  us  Delay time.
  * @return     None
  * @details    Use the SysTick to generate the long delay time and the UNIT is in us.
  *             The SysTick clock source is from HCLK, i.e the same as system core clock.
  *             User can use SystemCoreClockUpdate() to calculate CyclesPerUs automatically before using this function.
  */
__STATIC_INLINE void CLK_SysTickLongDelay(uint32_t us)
{
    uint32_t delay;

    /* It should <= 349525us for each delay loop */
    delay = 349525UL;

    do
    {
        if(us > delay)
        {
            us -= delay;
        }
        else
        {
            delay = us;
            us = 0UL;
        }

        SysTick->LOAD = delay * CyclesPerUs;
        SysTick->VAL  = (0x0UL);
        SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

        /* Waiting for down-count to zero */
        while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0UL);

        /* Disable SysTick counter */
        SysTick->CTRL = 0UL;

    }
    while(us > 0UL);

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

/*@}*/ /* end of group CLK_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CLK_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif  /* __NU_CLK_H__ */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
