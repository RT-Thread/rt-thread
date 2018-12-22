/**************************************************************************//**
 * @file     CLK.h
 * @version  V1.0
 * $Revision  1 $
 * $Date: 15/11/19 10:06a $
 * @brief    NUC472/NUC442 CLK Header File
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __CLK_H__
#define __CLK_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_CLK_Driver CLK Driver
  @{
*/


/** @addtogroup NUC472_442_CLK_EXPORTED_CONSTANTS CLK Exported Constants
@{
*/

#define FREQ_500MHZ        500000000
#define FREQ_250MHZ        250000000
#define FREQ_200MHZ        200000000
#define FREQ_125MHZ        125000000
#define FREQ_72MHZ         72000000
#define FREQ_50MHZ         50000000
#define FREQ_25MHZ         25000000
#define FREQ_24MHZ         24000000
#define FREQ_22MHZ         22000000
#define FREQ_32KHZ         32000
#define FREQ_10KHZ         10000

/*---------------------------------------------------------------------------------------------------------*/
/*  PLLCTL constant definitions. PLL = FIN * NF / NR / NO                                                  */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_PLLCTL_PLLSRC_HIRC (0x1UL<<CLK_PLLCTL_PLLSRC_Pos)        /*!< For PLL clock source is internal RC clock. 4MHz < FIN < 24MHz  \hideinitializer */
#define CLK_PLLCTL_PLLSRC_HXT  (0x0UL<<CLK_PLLCTL_PLLSRC_Pos)        /*!< For PLL clock source is external crystal.  4MHz < FIN < 24MHz  \hideinitializer */

#define CLK_PLLCTL_NR(x)        (((x)-2)<<9)        /*!< x must be constant and 2 <= x <= 33.  1.6MHz < FIN/NR < 15MHz  \hideinitializer */
#define CLK_PLLCTL_NF(x)         ((x)-2)            /*!< x must be constant and 2 <= x <= 513. 100MHz < FIN*NF/NR < 200MHz. (120MHz < FIN*NF/NR < 200MHz is preferred.)  \hideinitializer */

#define CLK_PLLCTL_NO_1         (0x0UL<<CLK_PLLCTL_OUTDV_Pos)             /*!< For output divider is 1  \hideinitializer */
#define CLK_PLLCTL_NO_2         (0x1UL<<CLK_PLLCTL_OUTDV_Pos)             /*!< For output divider is 2  \hideinitializer */
#define CLK_PLLCTL_NO_4         (0x3UL<<CLK_PLLCTL_OUTDV_Pos)             /*!< For output divider is 4  \hideinitializer */

#if (__HXT == 12000000)
#define CLK_PLLCTL_FOR_I2S      (0xA54)                                                                                     /*!< Predefined PLLCTL setting for 147428571.428571Hz PLL output with 12MHz XTAL  \hideinitializer */
#define CLK_PLLCTL_84MHz_HXT   (CLK_PLLCTL_PLLSRC_HXT | CLK_PLLCTL_NR(2) | CLK_PLLCTL_NF( 28) | CLK_PLLCTL_NO_2) /*!< Predefined PLLCTL setting for 84MHz PLL output with 12MHz XTAL  \hideinitializer */
#define CLK_PLLCTL_50MHz_HXT   (CLK_PLLCTL_PLLSRC_HXT | CLK_PLLCTL_NR(3) | CLK_PLLCTL_NF( 25) | CLK_PLLCTL_NO_2) /*!< Predefined PLLCTL setting for 50MHz PLL output with 12MHz XTAL  \hideinitializer */
#define CLK_PLLCTL_48MHz_HXT   (CLK_PLLCTL_PLLSRC_HXT | CLK_PLLCTL_NR(7) | CLK_PLLCTL_NF(112) | CLK_PLLCTL_NO_4) /*!< Predefined PLLCTL setting for 48MHz PLL output with 12MHz XTAL  \hideinitializer */
#define CLK_PLLCTL_36MHz_HXT   (CLK_PLLCTL_PLLSRC_HXT | CLK_PLLCTL_NR(7) | CLK_PLLCTL_NF( 84) | CLK_PLLCTL_NO_4) /*!< Predefined PLLCTL setting for 36MHz PLL output with 12MHz XTAL  \hideinitializer */
#define CLK_PLLCTL_32MHz_HXT   (CLK_PLLCTL_PLLSRC_HXT | CLK_PLLCTL_NR(6) | CLK_PLLCTL_NF( 64) | CLK_PLLCTL_NO_4) /*!< Predefined PLLCTL setting for 32MHz PLL output with 12MHz XTAL  \hideinitializer */
#define CLK_PLLCTL_24MHz_HXT   (CLK_PLLCTL_PLLSRC_HXT | CLK_PLLCTL_NR(2) | CLK_PLLCTL_NF( 16) | CLK_PLLCTL_NO_4) /*!< Predefined PLLCTL setting for 24MHz PLL output with 12MHz XTAL  \hideinitializer */
#else
# error "The PLL pre-definitions are only valid when external crystal is 12MHz"
#endif

#define CLK_PLLCTL_50MHz_HIRC (CLK_PLLCTL_PLLSRC_HIRC | CLK_PLLCTL_NR(13) | CLK_PLLCTL_NF( 59) | CLK_PLLCTL_NO_2) /*!< Predefined PLLCTL setting for 50.1918MHz PLL output with 22.1184MHz IRC  \hideinitializer */
#define CLK_PLLCTL_48MHz_HIRC (CLK_PLLCTL_PLLSRC_HIRC | CLK_PLLCTL_NR(13) | CLK_PLLCTL_NF(113) | CLK_PLLCTL_NO_4) /*!< Predefined PLLCTL setting for 48.064985MHz PLL output with 22.1184MHz IRC \hideinitializer */
#define CLK_PLLCTL_36MHz_HIRC (CLK_PLLCTL_PLLSRC_HIRC | CLK_PLLCTL_NR(12) | CLK_PLLCTL_NF( 78) | CLK_PLLCTL_NO_4) /*!< Predefined PLLCTL setting for 35.9424MHz PLL output with 22.1184MHz IRC  \hideinitializer */
#define CLK_PLLCTL_32MHz_HIRC (CLK_PLLCTL_PLLSRC_HIRC | CLK_PLLCTL_NR( 9) | CLK_PLLCTL_NF( 52) | CLK_PLLCTL_NO_4) /*!< Predefined PLLCTL setting for 31.9488MHz PLL output with 22.1184MHz IRC \hideinitializer */
#define CLK_PLLCTL_24MHz_HIRC (CLK_PLLCTL_PLLSRC_HIRC | CLK_PLLCTL_NR( 3) | CLK_PLLCTL_NF( 13) | CLK_PLLCTL_NO_4) /*!< Predefined PLLCTL setting for 23.9616MHz PLL output with 22.1184MHz IRC \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  PLL2CTL constant definitions.                                                                */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_PLL2CTL_PLL2DIV(x)       (((x)-1) << CLK_PLL2CTL_PLL2DIV_Pos) /*!< USBPLL clock frequency = (480 MHz) / 2 / (USB_N + 1). It could be 1~256,  Max. PLL frequency :480MHz / 2 when XTL12M.  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKSEL0 constant definitions.  (Write-protection)                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKSEL0_HCLKSEL_HXT         (0x00UL<<CLK_CLKSEL0_HCLKSEL_Pos) /*!< Setting clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL0_HCLKSEL_LXT         (0x01UL<<CLK_CLKSEL0_HCLKSEL_Pos) /*!< Setting clock source as external XTAL 32.768KHz \hideinitializer */
#define CLK_CLKSEL0_HCLKSEL_PLL         (0x02UL<<CLK_CLKSEL0_HCLKSEL_Pos) /*!< Setting clock source as PLL output  \hideinitializer */
#define CLK_CLKSEL0_HCLKSEL_LIRC        (0x03UL<<CLK_CLKSEL0_HCLKSEL_Pos) /*!< Setting clock source as internal 10KHz RC clock  \hideinitializer */
#define CLK_CLKSEL0_HCLKSEL_PLL2        (0x04UL<<CLK_CLKSEL0_HCLKSEL_Pos) /*!< Setting clock source as USBPLL clock  \hideinitializer */
#define CLK_CLKSEL0_HCLKSEL_HIRC        (0x07UL<<CLK_CLKSEL0_HCLKSEL_Pos) /*!< Setting clock source as internal 22.1184MHz RC clock  \hideinitializer */

#define CLK_CLKSEL0_STCLKSEL_HXT         (0x00UL<<CLK_CLKSEL0_STCLKSEL_Pos)  /*!< Setting clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL0_STCLKSEL_LXT      (0x01UL<<CLK_CLKSEL0_STCLKSEL_Pos)  /*!< Setting clock source as external XTAL 32.768KHz \hideinitializer */
#define CLK_CLKSEL0_STCLKSEL_HXT_DIV2    (0x02UL<<CLK_CLKSEL0_STCLKSEL_Pos)  /*!< Setting clock source as external XTAL/2  \hideinitializer */
#define CLK_CLKSEL0_STCLKSEL_HCLK_DIV2    (0x03UL<<CLK_CLKSEL0_STCLKSEL_Pos)  /*!< Setting clock source as HCLK/2  \hideinitializer */
#define CLK_CLKSEL0_STCLKSEL_HIRC_DIV2  (0x07UL<<CLK_CLKSEL0_STCLKSEL_Pos)  /*!< Setting clock source as internal 22.1184MHz RC clock/2  \hideinitializer */
#define CLK_CLKSEL0_STCLKSEL_HCLK      (0x01UL<<SysTick_CTRL_CLKSOURCE_Pos) /*!< Setting SysTick clock source as HCLK */

#define CLK_CLKSEL0_PCLKSEL_HCLK   (0x00UL<<CLK_CLKSEL0_PCLKSEL_Pos)    /*!< Setting clock source as HCLK  \hideinitializer */
#define CLK_CLKSEL0_PCLKSEL_HCLK_DIV2  (0x01UL<<CLK_CLKSEL0_PCLKSEL_Pos)    /*!< Setting clock source as HCLK/2  \hideinitializer */

#define CLK_CLKSEL0_USBHSEL_PLL   (0x01UL<<CLK_CLKSEL0_USBHSEL_Pos)    /*!< Setting clock source as PLL   \hideinitializer */
#define CLK_CLKSEL0_USBHSEL_PLL2    (0x00UL<<CLK_CLKSEL0_USBHSEL_Pos)    /*!< Setting clock source as PLL2  \hideinitializer */

#define CLK_CLKSEL0_CAPSEL_HXT     (0x00UL<<CLK_CLKSEL0_CAPSEL_Pos)    /*!< Setting clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL0_CAPSEL_PLL     (0x01UL<<CLK_CLKSEL0_CAPSEL_Pos)    /*!< Setting clock source as PLL   \hideinitializer */
#define CLK_CLKSEL0_CAPSEL_HCLK    (0x02UL<<CLK_CLKSEL0_CAPSEL_Pos)    /*!< Setting clock source as HCLK  \hideinitializer */
#define CLK_CLKSEL0_CAPSEL_HIRC    (0x03UL<<CLK_CLKSEL0_CAPSEL_Pos)    /*!< Setting clock source as internal 22.1184MHz RC clock  \hideinitializer */

#define CLK_CLKSEL0_ICAPSEL_HXT    (0x00UL<<CLK_CLKSEL0_CAPSEL_Pos)    /*!< Setting clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL0_ICAPSEL_PLL    (0x01UL<<CLK_CLKSEL0_CAPSEL_Pos)    /*!< Setting clock source as PLL   \hideinitializer */
#define CLK_CLKSEL0_ICAPSEL_HCLK   (0x02UL<<CLK_CLKSEL0_CAPSEL_Pos)    /*!< Setting clock source as HCLK  \hideinitializer */
#define CLK_CLKSEL0_ICAPSEL_HIRC   (0x03UL<<CLK_CLKSEL0_CAPSEL_Pos)    /*!< Setting clock source as internal 22.1184MHz RC clock  \hideinitializer */

#define CLK_CLKSEL0_SDHSEL_HXT    (0x00UL<<CLK_CLKSEL0_SDHSEL_Pos)    /*!< Setting clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL0_SDHSEL_PLL    (0x01UL<<CLK_CLKSEL0_SDHSEL_Pos)    /*!< Setting clock source as PLL2  \hideinitializer */
#define CLK_CLKSEL0_SDHSEL_HCLK   (0x02UL<<CLK_CLKSEL0_SDHSEL_Pos)    /*!< Setting clock source as HCLK  \hideinitializer */
#define CLK_CLKSEL0_SDHSEL_HIRC   (0x03UL<<CLK_CLKSEL0_SDHSEL_Pos)    /*!< Setting clock source as internal 22.1184MHz RC clock  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKSEL1 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKSEL1_WDTSEL_HXT       (0x0UL<<CLK_CLKSEL1_WDTSEL_Pos)       /*!< Setting WDT clock source as external XTAL \hideinitializer */
#define CLK_CLKSEL1_WDTSEL_LXT       (0x1UL<<CLK_CLKSEL1_WDTSEL_Pos)       /*!< Setting WDT clock source as external XTAL 32.768KHz \hideinitializer */
#define CLK_CLKSEL1_WDTSEL_HCLK_DIV2048  (0x2UL<<CLK_CLKSEL1_WDTSEL_Pos)       /*!< Setting WDT clock source as HCLK/2048  \hideinitializer */
#define CLK_CLKSEL1_WDTSEL_LIRC        (0x3UL<<CLK_CLKSEL1_WDTSEL_Pos)       /*!< Setting WDT clock source as internal 10KHz RC clock  \hideinitializer */

#define CLK_CLKSEL1_ADCSEL_HXT          (0x0UL<<CLK_CLKSEL1_ADCSEL_Pos)       /*!< Setting ADC clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL1_ADCSEL_PLL           (0x1UL<<CLK_CLKSEL1_ADCSEL_Pos)       /*!< Setting ADC clock source as PLL  \hideinitializer */
#define CLK_CLKSEL1_ADCSEL_PCLK          (0x2UL<<CLK_CLKSEL1_ADCSEL_Pos)       /*!< Setting ADC clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL1_ADCSEL_HIRC        (0x3UL<<CLK_CLKSEL1_ADCSEL_Pos)       /*!< Setting ADC clock source as internal 22.1184MHz RC clock  \hideinitializer */

#define CLK_CLKSEL1_EADCSEL_HXT          (0x0UL<<CLK_CLKSEL1_ADCSEL_Pos)       /*!< Setting EADC clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL1_EADCSEL_PLL           (0x1UL<<CLK_CLKSEL1_ADCSEL_Pos)       /*!< Setting EADC clock source as PLL  \hideinitializer */
#define CLK_CLKSEL1_EADCSEL_PCLK          (0x2UL<<CLK_CLKSEL1_ADCSEL_Pos)       /*!< Setting EADC clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL1_EADCSEL_HIRC        (0x3UL<<CLK_CLKSEL1_ADCSEL_Pos)       /*!< Setting EADC clock source as internal 22.1184MHz RC clock  \hideinitializer */

#define CLK_CLKSEL1_SPI0SEL_PLL          (0x0UL<<CLK_CLKSEL1_SPI0SEL_Pos)       /*!< Setting SPI0 clock source as PLL  \hideinitializer */
#define CLK_CLKSEL1_SPI0SEL_PCLK         (0x1UL<<CLK_CLKSEL1_SPI0SEL_Pos)       /*!< Setting SPI0 clock source as PCLK  \hideinitializer */

#define CLK_CLKSEL1_SPI1SEL_PLL          (0x0UL<<CLK_CLKSEL1_SPI1SEL_Pos)       /*!< Setting SPI1 clock source as PLL  \hideinitializer */
#define CLK_CLKSEL1_SPI1SEL_PCLK         (0x1UL<<CLK_CLKSEL1_SPI1SEL_Pos)       /*!< Setting SPI1 clock source as PCLK  \hideinitializer */

#define CLK_CLKSEL1_SPI2SEL_PLL          (0x0UL<<CLK_CLKSEL1_SPI2SEL_Pos)       /*!< Setting SPI2 clock source as PLL  \hideinitializer */
#define CLK_CLKSEL1_SPI2SEL_PCLK         (0x1UL<<CLK_CLKSEL1_SPI2SEL_Pos)       /*!< Setting SPI2 clock source as PCLK  \hideinitializer */

#define CLK_CLKSEL1_SPI3SEL_PLL          (0x0UL<<CLK_CLKSEL1_SPI3SEL_Pos)       /*!< Setting SPI3 clock source as PLL  \hideinitializer */
#define CLK_CLKSEL1_SPI3SEL_PCLK         (0x1UL<<CLK_CLKSEL1_SPI3SEL_Pos)       /*!< Setting SPI3 clock source as PCLK  \hideinitializer */

#define CLK_CLKSEL1_TMR0SEL_HXT         (0x0UL<<CLK_CLKSEL1_TMR0SEL_Pos)       /*!< Setting Timer 0 clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL1_TMR0SEL_LXT      (0x1UL<<CLK_CLKSEL1_TMR0SEL_Pos)       /*!< Setting Timer 0 clock source as external XTAL 32.768KHz  \hideinitializer */
#define CLK_CLKSEL1_TMR0SEL_PCLK         (0x2UL<<CLK_CLKSEL1_TMR0SEL_Pos)       /*!< Setting Timer 0 clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL1_TMR0SEL_EXT      (0x3UL<<CLK_CLKSEL1_TMR0SEL_Pos)       /*!< Setting Timer 0 clock source as external trigger  \hideinitializer */
#define CLK_CLKSEL1_TMR0SEL_LIRC       (0x5UL<<CLK_CLKSEL1_TMR0SEL_Pos)       /*!< Setting Timer 0 clock source as internal 10KHz RC clock  \hideinitializer */
#define CLK_CLKSEL1_TMR0SEL_HIRC       (0x7UL<<CLK_CLKSEL1_TMR0SEL_Pos)       /*!< Setting Timer 0 clock source as internal 22.1184MHz RC clock  \hideinitializer */

#define CLK_CLKSEL1_TMR1SEL_HXT         (0x0UL<<CLK_CLKSEL1_TMR1SEL_Pos)      /*!< Setting Timer 1 clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL1_TMR1SEL_LXT      (0x1UL<<CLK_CLKSEL1_TMR1SEL_Pos)      /*!< Setting Timer 1 clock source as external XTAL 32.768KHz  \hideinitializer */
#define CLK_CLKSEL1_TMR1SEL_PCLK         (0x2UL<<CLK_CLKSEL1_TMR1SEL_Pos)      /*!< Setting Timer 1 clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL1_TMR1SEL_EXT     (0x3UL<<CLK_CLKSEL1_TMR1SEL_Pos)      /*!< Setting Timer 1 clock source as external trigger  \hideinitializer */
#define CLK_CLKSEL1_TMR1SEL_LIRC       (0x5UL<<CLK_CLKSEL1_TMR1SEL_Pos)      /*!< Setting Timer 1 clock source as internal 10KHz RC clock  \hideinitializer */
#define CLK_CLKSEL1_TMR1SEL_HIRC       (0x7UL<<CLK_CLKSEL1_TMR1SEL_Pos)      /*!< Setting Timer 1 clock source as internal 22.1184MHz RC clock  \hideinitializer */

#define CLK_CLKSEL1_TMR2SEL_HXT         (0x0UL<<CLK_CLKSEL1_TMR2SEL_Pos)      /*!< Setting Timer 2 clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL1_TMR2SEL_LXT      (0x1UL<<CLK_CLKSEL1_TMR2SEL_Pos)      /*!< Setting Timer 2 clock source as external XTAL 32.768KHz  \hideinitializer */
#define CLK_CLKSEL1_TMR2SEL_PCLK         (0x2UL<<CLK_CLKSEL1_TMR2SEL_Pos)      /*!< Setting Timer 2 clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL1_TMR2SEL_EXT      (0x3UL<<CLK_CLKSEL1_TMR2SEL_Pos)      /*!< Setting Timer 2 clock source as external trigger  \hideinitializer */
#define CLK_CLKSEL1_TMR2SEL_LIRC       (0x5UL<<CLK_CLKSEL1_TMR2SEL_Pos)      /*!< Setting Timer 2 clock source as internal 10KHz RC clock  \hideinitializer */
#define CLK_CLKSEL1_TMR2SEL_HIRC       (0x7UL<<CLK_CLKSEL1_TMR2SEL_Pos)      /*!< Setting Timer 2 clock source as internal 22.1184MHz RC clock  \hideinitializer */

#define CLK_CLKSEL1_TMR3SEL_HXT         (0x0UL<<CLK_CLKSEL1_TMR3SEL_Pos)      /*!< Setting Timer 3 clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL1_TMR3SEL_LXT      (0x1UL<<CLK_CLKSEL1_TMR3SEL_Pos)      /*!< Setting Timer 3 clock source as external XTAL 32.768KHz  \hideinitializer */
#define CLK_CLKSEL1_TMR3SEL_PCLK         (0x2UL<<CLK_CLKSEL1_TMR3SEL_Pos)      /*!< Setting Timer 3 clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL1_TMR3SEL_EXT     (0x3UL<<CLK_CLKSEL1_TMR3SEL_Pos)      /*!< Setting Timer 3 clock source as external trigger  \hideinitializer */
#define CLK_CLKSEL1_TMR3SEL_LIRC       (0x5UL<<CLK_CLKSEL1_TMR3SEL_Pos)      /*!< Setting Timer 3 clock source as internal 10KHz RC clock  \hideinitializer */
#define CLK_CLKSEL1_TMR3SEL_HIRC       (0x7UL<<CLK_CLKSEL1_TMR3SEL_Pos)      /*!< Setting Timer 3 clock source as internal 22.1184MHz RC clock  \hideinitializer */

#define CLK_CLKSEL1_UARTSEL_HXT         (0x0UL<<CLK_CLKSEL1_UARTSEL_Pos)      /*!< Setting UR clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL1_UARTSEL_PLL          (0x1UL<<CLK_CLKSEL1_UARTSEL_Pos)      /*!< Setting UR clock source as external PLL  \hideinitializer */
#define CLK_CLKSEL1_UARTSEL_HIRC       (0x3UL<<CLK_CLKSEL1_UARTSEL_Pos)      /*!< Setting UR clock source as external internal 22.1184MHz RC clock  \hideinitializer */

#define CLK_CLKSEL1_CLKOSEL_HXT       (0x0UL<<CLK_CLKSEL1_CLKOSEL_Pos)      /*!< Setting CLKO clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL1_CLKOSEL_LXT    (0x1UL<<CLK_CLKSEL1_CLKOSEL_Pos)      /*!< Setting CLKO clock source as external XTAL 32.768KHz   \hideinitializer */
#define CLK_CLKSEL1_CLKOSEL_HCLK       (0x2UL<<CLK_CLKSEL1_CLKOSEL_Pos)      /*!< Setting CLKO clock source as HCLK  \hideinitializer */
#define CLK_CLKSEL1_CLKOSEL_HIRC     (0x3UL<<CLK_CLKSEL1_CLKOSEL_Pos)      /*!< Setting CLKO clock source as external internal 22.1184MHz RC clock  \hideinitializer */

#define CLK_CLKSEL1_WWDTSEL_HCLK_DIV2048  (0x2UL<<CLK_CLKSEL1_WWDTSEL_Pos)       /*!< Setting CLKO clock source as  HCLK/2048  \hideinitializer */
#define CLK_CLKSEL1_WWDTSEL_LIRC        (0x3UL<<CLK_CLKSEL1_WWDTSEL_Pos)       /*!< Setting CLKO clock source as internal 10KHz RC clock   \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/*  CLKSEL2 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKSEL2_PWM0CH01SEL_HXT      (0x0UL<<CLK_CLKSEL2_PWM0CH01SEL_Pos)   /*!< Setting PWM0 and PWM1 clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL2_PWM0CH01SEL_LXT    (0x1UL<<CLK_CLKSEL2_PWM0CH01SEL_Pos)   /*!< Setting PWM0 and PWM1 clock source as external XTAL 32.768KHz  \hideinitializer */
#define CLK_CLKSEL2_PWM0CH01SEL_PCLK     (0x2UL<<CLK_CLKSEL2_PWM0CH01SEL_Pos)   /*!< Setting PWM0 and PWM1 clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL2_PWM0CH01SEL_HIRC   (0x3UL<<CLK_CLKSEL2_PWM0CH01SEL_Pos)     /*!< Setting PWM0 and PWM1 clock source as internal 22.1184MHz RC clock  \hideinitializer */
#define CLK_CLKSEL2_PWM0CH01SEL_LIRC   (0x7UL<<CLK_CLKSEL2_PWM0CH01SEL_Pos)   /*!< Setting PWM0 and PWM1 clock source as internal 10KHz RC clock  \hideinitializer */

#define CLK_CLKSEL2_PWM0CH23SEL_HXT      (0x0UL<<CLK_CLKSEL2_PWM0CH23SEL_Pos)   /*!< Setting PWM2 and PWM3 clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL2_PWM0CH23SEL_LXT    (0x1UL<<CLK_CLKSEL2_PWM0CH23SEL_Pos)   /*!< Setting PWM2 and PWM3 clock source as external XTAL 32.768KHz  \hideinitializer */
#define CLK_CLKSEL2_PWM0CH23SEL_PCLK     (0x2UL<<CLK_CLKSEL2_PWM0CH23SEL_Pos)   /*!< Setting PWM2 and PWM3 clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL2_PWM0CH23SEL_HIRC   (0x3UL<<CLK_CLKSEL2_PWM0CH23SEL_Pos)     /*!< Setting PWM2 and PWM3 clock source as internal 22.1184MHz RC clock  \hideinitializer */
#define CLK_CLKSEL2_PWM0CH23SEL_LIRC   (0x7UL<<CLK_CLKSEL2_PWM0CH23SEL_Pos)   /*!< Setting PWM2 and PWM3 clock source as internal 10KHz RC clock  \hideinitializer */

#define CLK_CLKSEL2_PWM0CH45SEL_HXT      (0x0UL<<CLK_CLKSEL2_PWM0CH45SEL_Pos)   /*!< Setting PWM4 and PWM5 clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL2_PWM0CH45SEL_LXT    (0x1UL<<CLK_CLKSEL2_PWM0CH45SEL_Pos)   /*!< Setting PWM4 and PWM5 clock source as external XTAL 32.768KHz  \hideinitializer */
#define CLK_CLKSEL2_PWM0CH45SEL_PCLK     (0x2UL<<CLK_CLKSEL2_PWM0CH45SEL_Pos)   /*!< Setting PWM4 and PWM5 clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL2_PWM0CH45SEL_HIRC   (0x3UL<<CLK_CLKSEL2_PWM0CH45SEL_Pos)     /*!< Setting PWM4 and PWM5 clock source as internal 22.1184MHz RC clock  \hideinitializer */
#define CLK_CLKSEL2_PWM0CH45SEL_LIRC   (0x7UL<<CLK_CLKSEL2_PWM0CH45SEL_Pos)   /*!< Setting PWM4 and PWM5 clock source as internal 10KHz RC clock  \hideinitializer */

#define CLK_CLKSEL2_PWM1CH01SEL_HXT      (0x0UL<<CLK_CLKSEL2_PWM1CH01SEL_Pos)   /*!< Setting PWM0 and PWM1 clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL2_PWM1CH01SEL_LXT    (0x1UL<<CLK_CLKSEL2_PWM1CH01SEL_Pos)   /*!< Setting PWM0 and PWM1 clock source as external XTAL 32.768KHz  \hideinitializer */
#define CLK_CLKSEL2_PWM1CH01SEL_PCLK     (0x2UL<<CLK_CLKSEL2_PWM1CH01SEL_Pos)   /*!< Setting PWM0 and PWM1 clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL2_PWM1CH01SEL_HIRC   (0x3UL<<CLK_CLKSEL2_PWM1CH01SEL_Pos)     /*!< Setting PWM0 and PWM1 clock source as internal 22.1184MHz RC clock  \hideinitializer */
#define CLK_CLKSEL2_PWM1CH01SEL_LIRC   (0x7UL<<CLK_CLKSEL2_PWM1CH01SEL_Pos)   /*!< Setting PWM0 and PWM1 clock source as internal 10KHz RC clock  \hideinitializer */

#define CLK_CLKSEL2_PWM1CH23SEL_HXT      (0x0UL<<CLK_CLKSEL2_PWM1CH23SEL_Pos)   /*!< Setting PWM2 and PWM3 clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL2_PWM1CH23SEL_LXT    (0x1UL<<CLK_CLKSEL2_PWM1CH23SEL_Pos)   /*!< Setting PWM2 and PWM3 clock source as external XTAL 32.768KHz  \hideinitializer */
#define CLK_CLKSEL2_PWM1CH23SEL_PCLK     (0x2UL<<CLK_CLKSEL2_PWM1CH23SEL_Pos)   /*!< Setting PWM2 and PWM3 clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL2_PWM1CH23SEL_HIRC   (0x3UL<<CLK_CLKSEL2_PWM1CH23SEL_Pos)     /*!< Setting PWM2 and PWM3 clock source as internal 22.1184MHz RC clock  \hideinitializer */
#define CLK_CLKSEL2_PWM1CH23SEL_LIRC   (0x7UL<<CLK_CLKSEL2_PWM1CH23SEL_Pos)   /*!< Setting PWM2 and PWM3 clock source as internal 10KHz RC clock  \hideinitializer */

#define CLK_CLKSEL2_PWM1CH45SEL_HXT      (0x0UL<<CLK_CLKSEL2_PWM1CH45SEL_Pos)   /*!< Setting PWM4 and PWM5 clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL2_PWM1CH45SEL_LXT    (0x1UL<<CLK_CLKSEL2_PWM1CH45SEL_Pos)   /*!< Setting PWM4 and PWM5 clock source as external XTAL 32.768KHz  \hideinitializer */
#define CLK_CLKSEL2_PWM1CH45SEL_PCLK     (0x2UL<<CLK_CLKSEL2_PWM1CH45SEL_Pos)   /*!< Setting PWM4 and PWM5 clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL2_PWM1CH45SEL_HIRC   (0x3UL<<CLK_CLKSEL2_PWM1CH45SEL_Pos)     /*!< Setting PWM4 and PWM5 clock source as internal 22.1184MHz RC clock  \hideinitializer */
#define CLK_CLKSEL2_PWM1CH45SEL_LIRC   (0x7UL<<CLK_CLKSEL2_PWM1CH45SEL_Pos)   /*!< Setting PWM4 and PWM5 clock source as internal 10KHz RC clock  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKSEL3 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKSEL3_SC0SEL_HXT           (0x0UL<<CLK_CLKSEL3_SC0SEL_Pos)      /*!< Setting SC0 clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL3_SC0SEL_PLL            (0x1UL<<CLK_CLKSEL3_SC0SEL_Pos)      /*!< Setting SC0 clock source as PLL  \hideinitializer */
#define CLK_CLKSEL3_SC0SEL_PCLK           (0x2UL<<CLK_CLKSEL3_SC0SEL_Pos)      /*!< Setting SC0 clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL3_SC0SEL_HIRC         (0x3UL<<CLK_CLKSEL3_SC0SEL_Pos)      /*!< Setting SC0 clock source as internal 22.1184MHz RC clock  \hideinitializer */

#define CLK_CLKSEL3_SC1SEL_HXT           (0x0UL<<CLK_CLKSEL3_SC1SEL_Pos)      /*!< Setting SC1 clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL3_SC1SEL_PLL            (0x1UL<<CLK_CLKSEL3_SC1SEL_Pos)      /*!< Setting SC1 clock source as PLL  \hideinitializer */
#define CLK_CLKSEL3_SC1SEL_PCLK           (0x2UL<<CLK_CLKSEL3_SC1SEL_Pos)      /*!< Setting SC1 clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL3_SC1SEL_HIRC         (0x3UL<<CLK_CLKSEL3_SC1SEL_Pos)      /*!< Setting SC1 clock source as internal 22.1184MHz RC clock  \hideinitializer */

#define CLK_CLKSEL3_SC2SEL_HXT           (0x0UL<<CLK_CLKSEL3_SC2SEL_Pos)    /*!< Setting SC2 clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL3_SC2SEL_PLL            (0x1UL<<CLK_CLKSEL3_SC2SEL_Pos)      /*!< Setting SC2 clock source as PLL  \hideinitializer */
#define CLK_CLKSEL3_SC2SEL_PCLK           (0x2UL<<CLK_CLKSEL3_SC2SEL_Pos)      /*!< Setting SC2 clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL3_SC2SEL_HIRC         (0x3UL<<CLK_CLKSEL3_SC2SEL_Pos)      /*!< Setting SC2 clock source as internal 22.1184MHz RC clock  \hideinitializer */

#define CLK_CLKSEL3_SC3SEL_HXT           (0x0UL<<CLK_CLKSEL3_SC3SEL_Pos)      /*!< Setting SC3 clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL3_SC3SEL_PLL            (0x1UL<<CLK_CLKSEL3_SC3SEL_Pos)      /*!< Setting SC3 clock source as PLL  \hideinitializer */
#define CLK_CLKSEL3_SC3SEL_PCLK           (0x2UL<<CLK_CLKSEL3_SC3SEL_Pos)      /*!< Setting SC3 clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL3_SC3SEL_HIRC         (0x3UL<<CLK_CLKSEL3_SC3SEL_Pos)      /*!< Setting SC3 clock source as internal 22.1184MHz RC clock  \hideinitializer */

#define CLK_CLKSEL3_SC4SEL_HXT           (0x0UL<<CLK_CLKSEL3_SC4SEL_Pos)      /*!< Setting SC4 clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL3_SC4SEL_PLL            (0x1UL<<CLK_CLKSEL3_SC4SEL_Pos)      /*!< Setting SC4 clock source as PLL  \hideinitializer */
#define CLK_CLKSEL3_SC4SEL_PCLK           (0x2UL<<CLK_CLKSEL3_SC4SEL_Pos)      /*!< Setting SC4 clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL3_SC4SEL_HIRC         (0x3UL<<CLK_CLKSEL3_SC4SEL_Pos)      /*!< Setting SC4 clock source as internal 22.1184MHz RC clock  \hideinitializer */

#define CLK_CLKSEL3_SC5SEL_HXT           (0x0UL<<CLK_CLKSEL3_SC5SEL_Pos)    /*!< Setting SC5 clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL3_SC5SEL_PLL            (0x1UL<<CLK_CLKSEL3_SC5SEL_Pos)      /*!< Setting SC5 clock source as PLL  \hideinitializer */
#define CLK_CLKSEL3_SC5SEL_PCLK           (0x2UL<<CLK_CLKSEL3_SC5SEL_Pos)      /*!< Setting SC5 clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL3_SC5SEL_HIRC         (0x3UL<<CLK_CLKSEL3_SC5SEL_Pos)      /*!< Setting SC5 clock source as internal 22.1184MHz RC clock  \hideinitializer */

#define CLK_CLKSEL3_I2S0SEL_HXT           (0x0UL<<CLK_CLKSEL3_I2S0SEL_Pos)       /*!< Setting I2S0 clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL3_I2S0SEL_PLL            (0x1UL<<CLK_CLKSEL3_I2S0SEL_Pos)      /*!< Setting I2S0 clock source as PLL  \hideinitializer */
#define CLK_CLKSEL3_I2S0SEL_PCLK           (0x2UL<<CLK_CLKSEL3_I2S0SEL_Pos)      /*!< Setting I2S0 clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL3_I2S0SEL_HIRC         (0x3UL<<CLK_CLKSEL3_I2S0SEL_Pos)      /*!< Setting I2S0 clock source as internal 22.1184MHz RC clock  \hideinitializer */

#define CLK_CLKSEL3_I2S1SEL_HXT           (0x0UL<<CLK_CLKSEL3_I2S1SEL_Pos)    /*!< Setting I2S1 clock source as external XTAL  \hideinitializer */
#define CLK_CLKSEL3_I2S1SEL_PLL            (0x1UL<<CLK_CLKSEL3_I2S1SEL_Pos)      /*!< Setting I2S1 clock source as PLL  \hideinitializer */
#define CLK_CLKSEL3_I2S1SEL_PCLK           (0x2UL<<CLK_CLKSEL3_I2S1SEL_Pos)      /*!< Setting I2S1 clock source as PCLK  \hideinitializer */
#define CLK_CLKSEL3_I2S1SEL_HIRC         (0x3UL<<CLK_CLKSEL3_I2S1SEL_Pos)      /*!< Setting I2S1 clock source as internal 22.1184MHz RC clock  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV0 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV0_HCLK(x)    (((x)-1) << CLK_CLKDIV0_HCLKDIV_Pos)    /*!< CLKDIV Setting for HCLK clock divider. It could be 1~16  \hideinitializer */
#define CLK_CLKDIV0_USB(x)     (((x)-1) << CLK_CLKDIV0_USBHDIV_Pos)    /*!< CLKDIV Setting for USB clock divider. It could be 1~16   \hideinitializer */
#define CLK_CLKDIV0_UART(x)    (((x)-1) << CLK_CLKDIV0_UARTDIV_Pos)      /*!< CLKDIV Setting for UR clock divider. It could be 1~16  \hideinitializer */
#define CLK_CLKDIV0_ADC(x)     (((x)-1) << CLK_CLKDIV0_ADCDIV_Pos)     /*!< CLKDIV Setting for ADC clock divider. It could be 1~256  \hideinitializer */
#define CLK_CLKDIV0_SDH(x)     (((x)-1) << CLK_CLKDIV0_SDHDIV_Pos)     /*!< CLKDIV Setting for SDIO clock divider. It could be 1~256  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV1 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV1_SC0(x)  (((x)-1) << CLK_CLKDIV1_SC0DIV_Pos) /*!< CLKDIV Setting for SC0 clock divider. It could be 1~256  \hideinitializer */
#define CLK_CLKDIV1_SC1(x)  (((x)-1) << CLK_CLKDIV1_SC1DIV_Pos) /*!< CLKDIV Setting for SC1 clock divider. It could be 1~256  \hideinitializer */
#define CLK_CLKDIV1_SC2(x)  (((x)-1) << CLK_CLKDIV1_SC2DIV_Pos) /*!< CLKDIV Setting for SC2 clock divider. It could be 1~256  \hideinitializer */
#define CLK_CLKDIV1_SC3(x)  (((x)-1) << CLK_CLKDIV1_SC3DIV_Pos) /*!< CLKDIV Setting for SC3 clock divider. It could be 1~256  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV2 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV2_SC4(x)  (((x)-1) << CLK_CLKDIV2_SC4DIV_Pos) /*!< CLKDIV Setting for SC4 clock divider. It could be 1~256  \hideinitializer */
#define CLK_CLKDIV2_SC5(x)  (((x)-1) << CLK_CLKDIV2_SC5DIV_Pos) /*!< CLKDIV Setting for SC5 clock divider. It could be 1~256  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV3 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV3_CAP(x)      (((x)-1) << CLK_CLKDIV3_CAPDIV_Pos) /*!< CLKDIV Setting for CAP Engine clock divider. It could be 1~256  \hideinitializer */
#define CLK_CLKDIV3_VSENSE(x)   (((x)-1) << CLK_CLKDIV3_VSENSEDIV_Pos) /*!< CLKDIV Setting for Video Pixel clock divider. It could be 1~256  \hideinitializer */
#define CLK_CLKDIV3_EMAC(x)  (((x)-1) << CLK_CLKDIV3_EMACDIV_Pos) /*!< CLKDIV Setting for EMAC_MDCLK clock divider. It could be 1~256  \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/*  MODULE constant definitions.                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define MODULE_APBCLK(x)                   ((x >>30) & 0x3)    /*!< Calculate AHBCLK/APBCLK offset on MODULE index  \hideinitializer */
#define MODULE_CLKSEL(x)                   ((x >>28) & 0x3)    /*!< Calculate CLKSEL offset on MODULE index  \hideinitializer */
#define MODULE_CLKSEL_Msk(x)               ((x >>25) & 0x7)    /*!< Calculate CLKSEL mask offset on MODULE index  \hideinitializer */
#define MODULE_CLKSEL_Pos(x)               ((x >>20) & 0x1f)   /*!< Calculate CLKSEL position offset on MODULE index  \hideinitializer */
#define MODULE_CLKDIV(x)                   ((x >>18) & 0x3)    /*!< Calculate APBCLK CLKDIV on MODULE index  \hideinitializer */
#define MODULE_CLKDIV_Msk(x)               ((x >>10) & 0xff)   /*!< Calculate CLKDIV mask offset on MODULE index  \hideinitializer */
#define MODULE_CLKDIV_Pos(x)               ((x >>5 ) & 0x1f)   /*!< Calculate CLKDIV position offset on MODULE index  \hideinitializer */
#define MODULE_IP_EN_Pos(x)                ((x >>0 ) & 0x1f)   /*!< Calculate APBCLK offset on MODULE index  \hideinitializer */
#define MODULE_NoMsk                       0x0                 /*!< Not mask on MODULE index  \hideinitializer */
#define NA                                 MODULE_NoMsk        /*!< Not Available  \hideinitializer */

#define MODULE_APBCLK_ENC(x)               (((x) & 0x03) << 30)   /*!< MODULE index, 0x0:AHBCLK, 0x1:APBCLK0, 0x2:APBCLK1 */
#define MODULE_CLKSEL_ENC(x)               (((x) & 0x03) << 28)   /*!< CLKSEL offset on MODULE index, 0x0:CLKSEL0, 0x1:CLKSEL1, 0x2:CLKSEL2, 0x3:CLKSEL3 */
#define MODULE_CLKSEL_Msk_ENC(x)           (((x) & 0x07) << 25)   /*!< CLKSEL mask offset on MODULE index */
#define MODULE_CLKSEL_Pos_ENC(x)           (((x) & 0x1f) << 20)   /*!< CLKSEL position offset on MODULE index */
#define MODULE_CLKDIV_ENC(x)               (((x) & 0x03) << 18)   /*!< APBCLK CLKDIV on MODULE index, 0x0:CLKDIV, 0x1:CLKDIV1 */
#define MODULE_CLKDIV_Msk_ENC(x)           (((x) & 0xff) << 10)   /*!< CLKDIV mask offset on MODULE index */
#define MODULE_CLKDIV_Pos_ENC(x)           (((x) & 0x1f) <<  5)   /*!< CLKDIV position offset on MODULE index */
#define MODULE_IP_EN_Pos_ENC(x)            (((x) & 0x1f) <<  0)   /*!< AHBCLK/APBCLK offset on MODULE index */
/*--------------------------------------------------------------------------------------------------------------------------------------*/
/*   AHBCLK/APBCLK(2) | CLKSEL(2) | CLKSEL_Msk(3) |    CLKSEL_Pos(5)    | CLKDIV(2) | CLKDIV_Msk(8) |     CLKDIV_Pos(5)  |  IP_EN_Pos(5)*/
/*--------------------------------------------------------------------------------------------------------------------------------------*/
#define PDMA_MODULE      ((0UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_AHBCLK_PDMACKEN_Pos)    /*!< PDMA Module  \hideinitializer */
#define ISP_MODULE       ((0UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_AHBCLK_ISPCKEN_Pos)     /*!< ISP Module  \hideinitializer */
#define EBI_MODULE       ((0UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_AHBCLK_EBICKEN_Pos)     /*!< EBI Module  \hideinitializer */
#define USBH_MODULE      ((0UL<<30)|(0<<28)|(1<<25)           |( 8<<20)|(0<<18)|(0xF<<10)         |( 4<<5)|CLK_AHBCLK_USBHCKEN_Pos)    /*!< USBH Module  \hideinitializer */
#define EMAC_MODULE      ((0UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|(10<<20)|(3<<18)|(0xFF<<10)        |(16<<5)|CLK_AHBCLK_EMACCKEN_Pos)    /*!< EMAC Module  \hideinitializer */
#define SDH_MODULE       ((0UL<<30)|(0<<28)|(3<<25)           |(20<<20)|(0<<18)|(0xFF<<10)        |(24<<5)|CLK_AHBCLK_SDHCKEN_Pos)     /*!< SDH Module  \hideinitializer */
#define CRC_MODULE       ((0UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_AHBCLK_CRCCKEN_Pos)     /*!< CRC Module  \hideinitializer */
#define CAP_MODULE       ((0UL<<30)|(0<<28)|(3<<25)           |(16<<20)|(3<<18)|(0xFF<<10)        |( 0<<5)|CLK_AHBCLK_CAPCKEN_Pos)     /*!< CAP Module  \hideinitializer */
#define SEN_MODULE       ((0UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(3<<18)|(0xFF<<10)        |( 8<<5)|CLK_AHBCLK_SENCKEN_Pos)     /*!< Sensor Clock Module  \hideinitializer */
#define USBD_MODULE      ((0UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_AHBCLK_USBDCKEN_Pos)    /*!< USBD Module  \hideinitializer */
#define CRPT_MODULE      ((0UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_AHBCLK_CRPTCKEN_Pos)    /*!< CRYPTO Module  \hideinitializer */

#define WDT_MODULE       ((1UL<<30)|(1<<28)|(3<<25)           |( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_WDTCKEN_Pos)    /*!< Watchdog Timer Module  \hideinitializer */
#define WWDT_MODULE      ((1UL<<30)|(1<<28)|(3<<25)           |(30<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_WDTCKEN_Pos)    /*!< Window Watchdog Timer Module  \hideinitializer */
#define RTC_MODULE       ((1UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_RTCCKEN_Pos)    /*!< RTC Module  \hideinitializer */
#define TMR0_MODULE      ((1UL<<30)|(1<<28)|(7<<25)           |( 8<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_TMR0CKEN_Pos)   /*!< Timer0 Module  \hideinitializer */
#define TMR1_MODULE      ((1UL<<30)|(1<<28)|(7<<25)           |(12<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_TMR1CKEN_Pos)   /*!< Timer1 Module  \hideinitializer */
#define TMR2_MODULE      ((1UL<<30)|(1<<28)|(7<<25)           |(16<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_TMR2CKEN_Pos)   /*!< Timer2 Module  \hideinitializer */
#define TMR3_MODULE      ((1UL<<30)|(1<<28)|(7<<25)           |(20<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_TMR3CKEN_Pos)   /*!< Timer3 Module  \hideinitializer */
#define CLKO_MODULE      ((1UL<<30)|(1<<28)|(3<<25)           |(28<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_CLKOCKEN_Pos)   /*!< CLKO Module  \hideinitializer */
#define ACMP_MODULE      ((1UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_ACMPCKEN_Pos)   /*!< ACMP Module  \hideinitializer */
#define I2C0_MODULE      ((1UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_I2C0CKEN_Pos)   /*!< I2C0 Module  \hideinitializer */
#define I2C1_MODULE      ((1UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_I2C1CKEN_Pos)   /*!< I2C1 Module  \hideinitializer */
#define I2C2_MODULE      ((1UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_I2C2CKEN_Pos)   /*!< I2C2 Module  \hideinitializer */
#define I2C3_MODULE      ((1UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_I2C3CKEN_Pos)   /*!< I2C3 Module  \hideinitializer */
#define SPI0_MODULE      ((1UL<<30)|(1<<28)|(1<<25)           |( 4<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_SPI0CKEN_Pos)   /*!< SPI0 Module  \hideinitializer */
#define SPI1_MODULE      ((1UL<<30)|(1<<28)|(1<<25)           |( 5<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_SPI1CKEN_Pos)   /*!< SPI1 Module  \hideinitializer */
#define SPI2_MODULE      ((1UL<<30)|(1<<28)|(1<<25)           |( 6<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_SPI2CKEN_Pos)   /*!< SPI2 Module  \hideinitializer */
#define SPI3_MODULE      ((1UL<<30)|(1<<28)|(1<<25)           |( 7<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_SPI3CKEN_Pos)   /*!< SPI3 Module  \hideinitializer */
#define UART0_MODULE     ((1UL<<30)|(1<<28)|(3<<25)           |(24<<20)|(0<<18)|(0xF<<10)         |( 8<<5)|CLK_APBCLK0_UART0CKEN_Pos)  /*!< UART0 Module  \hideinitializer */
#define UART1_MODULE     ((1UL<<30)|(1<<28)|(3<<25)           |(24<<20)|(0<<18)|(0xF<<10)         |( 8<<5)|CLK_APBCLK0_UART1CKEN_Pos)  /*!< UART1 Module  \hideinitializer */
#define UART2_MODULE     ((1UL<<30)|(1<<28)|(3<<25)           |(24<<20)|(0<<18)|(0xF<<10)         |( 8<<5)|CLK_APBCLK0_UART2CKEN_Pos)  /*!< UART2 Module  \hideinitializer */
#define UART3_MODULE     ((1UL<<30)|(1<<28)|(3<<25)           |(24<<20)|(0<<18)|(0xF<<10)         |( 8<<5)|CLK_APBCLK0_UART3CKEN_Pos)  /*!< UART3 Module  \hideinitializer */
#define UART4_MODULE     ((1UL<<30)|(1<<28)|(3<<25)           |(24<<20)|(0<<18)|(0xF<<10)         |( 8<<5)|CLK_APBCLK0_UART4CKEN_Pos)  /*!< UART4 Module  \hideinitializer */
#define UART5_MODULE     ((1UL<<30)|(1<<28)|(3<<25)           |(24<<20)|(0<<18)|(0xF<<10)         |( 8<<5)|CLK_APBCLK0_UART5CKEN_Pos)  /*!< UART5 Module  \hideinitializer */
#define CAN0_MODULE      ((1UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_CAN0CKEN_Pos)   /*!< CAN0 Module  \hideinitializer */
#define CAN1_MODULE      ((1UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_CAN1CKEN_Pos)   /*!< CAN1 Module  \hideinitializer */
#define OTG_MODULE       ((1UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_OTGCKEN_Pos)    /*!< OTG Module  \hideinitializer */
#define ADC_MODULE       ((1UL<<30)|(1<<28)|(3<<25)           |( 2<<20)|(0<<18)|(0xFF<<10)        |(16<<5)|CLK_APBCLK0_ADCCKEN_Pos)    /*!< ADC Module  \hideinitializer */
#define I2S0_MODULE      ((1UL<<30)|(3<<28)|(3<<25)           |(16<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_I2S0CKEN_Pos)   /*!< I2S0 Module  \hideinitializer */
#define I2S1_MODULE      ((1UL<<30)|(3<<28)|(3<<25)           |(18<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_I2S1CKEN_Pos)   /*!< I2S1 Module  \hideinitializer */
#define PS2_MODULE       ((1UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK0_PS2CKEN_Pos)    /*!< PS2 Module  \hideinitializer */

#define SC0_MODULE       ((2UL<<30)|(3<<28)|(3<<25)           |( 0<<20)|(1<<18)|(0xFF<<10)        |( 0<<5)|CLK_APBCLK1_SC0CKEN_Pos)    /*!< SmartCard0 Module  \hideinitializer */
#define SC1_MODULE       ((2UL<<30)|(3<<28)|(3<<25)           |( 2<<20)|(1<<18)|(0xFF<<10)        |( 8<<5)|CLK_APBCLK1_SC1CKEN_Pos)    /*!< SmartCard1 Module  \hideinitializer */
#define SC2_MODULE       ((2UL<<30)|(3<<28)|(3<<25)           |( 4<<20)|(1<<18)|(0xFF<<10)        |(16<<5)|CLK_APBCLK1_SC2CKEN_Pos)    /*!< SmartCard2 Module  \hideinitializer */
#define SC3_MODULE       ((2UL<<30)|(3<<28)|(3<<25)           |( 6<<20)|(1<<18)|(0xFF<<10)        |(24<<5)|CLK_APBCLK1_SC3CKEN_Pos)    /*!< SmartCard3 Module  \hideinitializer */
#define SC4_MODULE       ((2UL<<30)|(3<<28)|(3<<25)           |( 8<<20)|(2<<18)|(0xFF<<10)        |( 0<<5)|CLK_APBCLK1_SC4CKEN_Pos)    /*!< SmartCard4 Module  \hideinitializer */
#define SC5_MODULE       ((2UL<<30)|(3<<28)|(3<<25)           |(10<<20)|(2<<18)|(0xFF<<10)        |( 8<<5)|CLK_APBCLK1_SC5CKEN_Pos)    /*!< SmartCard5 Module  \hideinitializer */
#define I2C4_MODULE      ((2UL<<30)|(0<<28)|(0<<25)           |( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK1_I2C4CKEN_Pos)   /*!< I2C4 Module */
#define PWM0CH01_MODULE  ((2UL<<30)|(2<<28)|(7<<25)           |( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK1_PWM0CH01CKEN_Pos) /*!< PWM0CH01 Module  \hideinitializer */
#define PWM0CH23_MODULE  ((2UL<<30)|(2<<28)|(7<<25)           |( 4<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK1_PWM0CH23CKEN_Pos) /*!< PWM0CH23 Module  \hideinitializer */
#define PWM0CH45_MODULE  ((2UL<<30)|(2<<28)|(7<<25)           |( 8<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK1_PWM0CH45CKEN_Pos) /*!< PWM0CH45 Module  \hideinitializer */
#define PWM1CH01_MODULE  ((2UL<<30)|(2<<28)|(7<<25)           |(12<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK1_PWM1CH01CKEN_Pos) /*!< PWM1CH01 Module  \hideinitializer */
#define PWM1CH23_MODULE  ((2UL<<30)|(2<<28)|(7<<25)           |(16<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK1_PWM1CH2345CKEN_Pos) /*!< PWM1CH23 Module  \hideinitializer */
#define PWM1CH45_MODULE  ((2UL<<30)|(2<<28)|(7<<25)           |(20<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK1_PWM1CH2345CKEN_Pos) /*!< PWM1CH45 Module  \hideinitializer */
#define QEI0_MODULE      ((2UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK1_QEI0CKEN_Pos)   /*!< QEI0 Module  \hideinitializer */
#define QEI1_MODULE      ((2UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK1_QEI1CKEN_Pos)   /*!< QEI1 Module  \hideinitializer */
#define ECAP0_MODULE     ((2UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK1_ECAP0CKEN_Pos)  /*!< ECAP0 Module  \hideinitializer */
#define ECAP1_MODULE     ((2UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK1_ECAP1CKEN_Pos)  /*!< ECAP1 Module  \hideinitializer */
#define EPWM0_MODULE     ((2UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK1_EPWM0CKEN_Pos)  /*!< EPWM0 Module  \hideinitializer */
#define EPWM1_MODULE     ((2UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK1_EPWM1CKEN_Pos)  /*!< EPWM1 Module  \hideinitializer */
#define OPA_MODULE       ((2UL<<30)|(0<<28)|(MODULE_NoMsk<<25)|( 0<<20)|(0<<18)|(MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK1_OPACKEN_Pos)    /*!< OPA Module  \hideinitializer */
#define EADC_MODULE      ((2UL<<30)|(1<<28)|(3<<25)           |( 2<<20)|(0<<18)|(0xFF<<10)        |(16<<5)|CLK_APBCLK1_EADCCKEN_Pos)   /*!< EADC Module  \hideinitializer */

/*@}*/ /* end of group NUC472_442_CLK_EXPORTED_CONSTANTS */


/** @addtogroup NUC472_442_CLK_EXPORTED_FUNCTIONS CLK Exported Functions
  @{
*/

void CLK_DisableCKO(void);
void CLK_EnableCKO(uint32_t u32ClkSrc, uint32_t u32ClkDiv, uint32_t u32ClkDivBy1En);
void CLK_PowerDown(void);
void CLK_Idle(void);
uint32_t CLK_GetHXTFreq(void);
uint32_t CLK_GetLXTFreq(void);
uint32_t CLK_GetHCLKFreq(void);
uint32_t CLK_GetPCLKFreq(void);
uint32_t CLK_GetCPUFreq(void);
uint32_t CLK_GetPLLClockFreq(void);
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
void CLK_SysTickDelay(uint32_t us);
uint32_t CLK_WaitClockReady(uint32_t u32ClkMask);
void CLK_EnableSysTick(uint32_t u32ClkSrc, uint32_t u32Count);
void CLK_DisableSysTick(void);

/*@}*/ /* end of group NUC472_442_CLK_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_CLK_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__CLK_H__

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
