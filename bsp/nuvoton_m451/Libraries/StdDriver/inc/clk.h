/******************************************************************************
 * @file     CLK.h
 * @version  V3.0
 * $Revision  1 $
 * $Date: 15/08/11 10:26a $
 * @brief    M451 Series CLK Header File
 *
 * @note
 * Copyright (C) 2013~2015 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __CLK_H__
#define __CLK_H__

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


#define FREQ_25MHZ         25000000
#define FREQ_50MHZ         50000000
#define FREQ_72MHZ         72000000
#define FREQ_125MHZ        125000000
#define FREQ_200MHZ        200000000
#define FREQ_250MHZ        250000000
#define FREQ_500MHZ        500000000


/*---------------------------------------------------------------------------------------------------------*/
/*  CLKSEL0 constant definitions.  (Write-protection)                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKSEL0_HCLKSEL_HXT        (0x00UL<<CLK_CLKSEL0_HCLKSEL_Pos) /*!< Setting HCLK clock source as HXT */
#define CLK_CLKSEL0_HCLKSEL_LXT        (0x01UL<<CLK_CLKSEL0_HCLKSEL_Pos) /*!< Setting HCLK clock source as LXT */
#define CLK_CLKSEL0_HCLKSEL_PLL        (0x02UL<<CLK_CLKSEL0_HCLKSEL_Pos) /*!< Setting HCLK clock source as PLL */
#define CLK_CLKSEL0_HCLKSEL_LIRC       (0x03UL<<CLK_CLKSEL0_HCLKSEL_Pos) /*!< Setting HCLK clock source as LIRC */
#define CLK_CLKSEL0_HCLKSEL_HIRC       (0x07UL<<CLK_CLKSEL0_HCLKSEL_Pos) /*!< Setting HCLK clock source as HIRC */

#define CLK_CLKSEL0_STCLKSEL_HXT       (0x00UL<<CLK_CLKSEL0_STCLKSEL_Pos) /*!< Setting SysTick clock source as HXT */
#define CLK_CLKSEL0_STCLKSEL_LXT       (0x01UL<<CLK_CLKSEL0_STCLKSEL_Pos) /*!< Setting SysTick clock source as LXT */
#define CLK_CLKSEL0_STCLKSEL_HXT_DIV2  (0x02UL<<CLK_CLKSEL0_STCLKSEL_Pos) /*!< Setting SysTick clock source as HXT */
#define CLK_CLKSEL0_STCLKSEL_HCLK_DIV2 (0x03UL<<CLK_CLKSEL0_STCLKSEL_Pos) /*!< Setting SysTick clock source as HCLK/2 */
#define CLK_CLKSEL0_STCLKSEL_HIRC_DIV2 (0x07UL<<CLK_CLKSEL0_STCLKSEL_Pos) /*!< Setting SysTick clock source as HIRC/2 */
#define CLK_CLKSEL0_STCLKSEL_HCLK      (0x01UL<<SysTick_CTRL_CLKSOURCE_Pos) /*!< Setting SysTick clock source as HCLK */

#define CLK_CLKSEL0_PCLK0SEL_HCLK      (0x00UL<<CLK_CLKSEL0_PCLK0SEL_Pos) /*!< Setting PCLK0 clock source as HCLK */
#define CLK_CLKSEL0_PCLK0SEL_HCLK_DIV2 (0x01UL<<CLK_CLKSEL0_PCLK0SEL_Pos) /*!< Setting PCLK0 clock source as HCLK/2 */

#define CLK_CLKSEL0_PCLK1SEL_HCLK      (0x00UL<<CLK_CLKSEL0_PCLK1SEL_Pos) /*!< Setting PCLK1 clock source as HCLK */
#define CLK_CLKSEL0_PCLK1SEL_HCLK_DIV2 (0x01UL<<CLK_CLKSEL0_PCLK1SEL_Pos) /*!< Setting PCLK1 clock source as HCLK/2 */


/*---------------------------------------------------------------------------------------------------------*/
/*  CLKSEL1 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKSEL1_WDTSEL_LXT           (0x1UL<<CLK_CLKSEL1_WDTSEL_Pos)  /*!< Setting WDT clock source as LXT */
#define CLK_CLKSEL1_WDTSEL_PCLK0_DIV2048 (0x2UL<<CLK_CLKSEL1_WDTSEL_Pos)  /*!< Setting WDT clock source as PCLK0/2048 */
#define CLK_CLKSEL1_WDTSEL_LIRC          (0x3UL<<CLK_CLKSEL1_WDTSEL_Pos)  /*!< Setting WDT clock source as LIRC */

#define CLK_CLKSEL1_TMR0SEL_HXT          (0x0UL<<CLK_CLKSEL1_TMR0SEL_Pos) /*!< Setting Timer 0 clock source as HXT */
#define CLK_CLKSEL1_TMR0SEL_LXT          (0x1UL<<CLK_CLKSEL1_TMR0SEL_Pos) /*!< Setting Timer 0 clock source as LXT */
#define CLK_CLKSEL1_TMR0SEL_PCLK0        (0x2UL<<CLK_CLKSEL1_TMR0SEL_Pos) /*!< Setting Timer 0 clock source as PCLK0 */
#define CLK_CLKSEL1_TMR0SEL_EXT_TRG      (0x3UL<<CLK_CLKSEL1_TMR0SEL_Pos) /*!< Setting Timer 0 clock source as external trigger */
#define CLK_CLKSEL1_TMR0SEL_LIRC         (0x5UL<<CLK_CLKSEL1_TMR0SEL_Pos) /*!< Setting Timer 0 clock source as LIRC */
#define CLK_CLKSEL1_TMR0SEL_HIRC         (0x7UL<<CLK_CLKSEL1_TMR0SEL_Pos) /*!< Setting Timer 0 clock source as HIRC */

#define CLK_CLKSEL1_TMR1SEL_HXT          (0x0UL<<CLK_CLKSEL1_TMR1SEL_Pos) /*!< Setting Timer 1 clock source as HXT */
#define CLK_CLKSEL1_TMR1SEL_LXT          (0x1UL<<CLK_CLKSEL1_TMR1SEL_Pos) /*!< Setting Timer 1 clock source as LXT */
#define CLK_CLKSEL1_TMR1SEL_PCLK0        (0x2UL<<CLK_CLKSEL1_TMR1SEL_Pos) /*!< Setting Timer 1 clock source as PCLK0 */
#define CLK_CLKSEL1_TMR1SEL_EXT_TRG      (0x3UL<<CLK_CLKSEL1_TMR1SEL_Pos) /*!< Setting Timer 1 clock source as external trigger */
#define CLK_CLKSEL1_TMR1SEL_LIRC         (0x5UL<<CLK_CLKSEL1_TMR1SEL_Pos) /*!< Setting Timer 1 clock source as LIRC */
#define CLK_CLKSEL1_TMR1SEL_HIRC         (0x7UL<<CLK_CLKSEL1_TMR1SEL_Pos) /*!< Setting Timer 1 clock source as HIRC */

#define CLK_CLKSEL1_TMR2SEL_HXT          (0x0UL<<CLK_CLKSEL1_TMR2SEL_Pos) /*!< Setting Timer 2 clock source as HXT */
#define CLK_CLKSEL1_TMR2SEL_LXT          (0x1UL<<CLK_CLKSEL1_TMR2SEL_Pos) /*!< Setting Timer 2 clock source as LXT */
#define CLK_CLKSEL1_TMR2SEL_PCLK1        (0x2UL<<CLK_CLKSEL1_TMR2SEL_Pos) /*!< Setting Timer 2 clock source as PCLK1 */
#define CLK_CLKSEL1_TMR2SEL_EXT_TRG      (0x3UL<<CLK_CLKSEL1_TMR2SEL_Pos) /*!< Setting Timer 2 clock source as external trigger */
#define CLK_CLKSEL1_TMR2SEL_LIRC         (0x5UL<<CLK_CLKSEL1_TMR2SEL_Pos) /*!< Setting Timer 2 clock source as LIRC */
#define CLK_CLKSEL1_TMR2SEL_HIRC         (0x7UL<<CLK_CLKSEL1_TMR2SEL_Pos) /*!< Setting Timer 2 clock source as HIRC */

#define CLK_CLKSEL1_TMR3SEL_HXT          (0x0UL<<CLK_CLKSEL1_TMR3SEL_Pos) /*!< Setting Timer 3 clock source as HXT */
#define CLK_CLKSEL1_TMR3SEL_LXT          (0x1UL<<CLK_CLKSEL1_TMR3SEL_Pos) /*!< Setting Timer 3 clock source as LXT */
#define CLK_CLKSEL1_TMR3SEL_PCLK1        (0x2UL<<CLK_CLKSEL1_TMR3SEL_Pos) /*!< Setting Timer 3 clock source as PCLK1 */
#define CLK_CLKSEL1_TMR3SEL_EXT_TRG      (0x3UL<<CLK_CLKSEL1_TMR3SEL_Pos) /*!< Setting Timer 3 clock source as external trigger */
#define CLK_CLKSEL1_TMR3SEL_LIRC         (0x5UL<<CLK_CLKSEL1_TMR3SEL_Pos) /*!< Setting Timer 3 clock source as LIRC */
#define CLK_CLKSEL1_TMR3SEL_HIRC         (0x7UL<<CLK_CLKSEL1_TMR3SEL_Pos) /*!< Setting Timer 3 clock source as HIRC */

#define CLK_CLKSEL1_UARTSEL_HXT          (0x0UL<<CLK_CLKSEL1_UARTSEL_Pos) /*!< Setting UART clock source as HXT */
#define CLK_CLKSEL1_UARTSEL_PLL          (0x1UL<<CLK_CLKSEL1_UARTSEL_Pos) /*!< Setting UART clock source as PLL */
#define CLK_CLKSEL1_UARTSEL_LXT          (0x2UL<<CLK_CLKSEL1_UARTSEL_Pos) /*!< Setting UART clock source as LXT */
#define CLK_CLKSEL1_UARTSEL_HIRC         (0x3UL<<CLK_CLKSEL1_UARTSEL_Pos) /*!< Setting UART clock source as HIRC */

#define CLK_CLKSEL1_CLKOSEL_HXT          (0x0UL<<CLK_CLKSEL1_CLKOSEL_Pos) /*!< Setting CLKO clock source as HXT */
#define CLK_CLKSEL1_CLKOSEL_LXT          (0x1UL<<CLK_CLKSEL1_CLKOSEL_Pos) /*!< Setting CLKO clock source as LXT */
#define CLK_CLKSEL1_CLKOSEL_HCLK         (0x2UL<<CLK_CLKSEL1_CLKOSEL_Pos) /*!< Setting CLKO clock source as HCLK */
#define CLK_CLKSEL1_CLKOSEL_HIRC         (0x3UL<<CLK_CLKSEL1_CLKOSEL_Pos) /*!< Setting CLKO clock source as HIRC */

#define CLK_CLKSEL1_WWDTSEL_PCLK0_DIV2048 (0x2UL<<CLK_CLKSEL1_WWDTSEL_Pos) /*!< Setting WWDT clock source as PCLK0/2048 */
#define CLK_CLKSEL1_WWDTSEL_LIRC          (0x3UL<<CLK_CLKSEL1_WWDTSEL_Pos) /*!< Setting WWDT clock source as LIRC */


/*---------------------------------------------------------------------------------------------------------*/
/*  CLKSEL2 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKSEL2_PWM0SEL_PLL            (0x0UL<<CLK_CLKSEL2_PWM0SEL_Pos) /*!< Setting PWM0 clock source as PLL */
#define CLK_CLKSEL2_PWM0SEL_PCLK0          (0x1UL<<CLK_CLKSEL2_PWM0SEL_Pos) /*!< Setting PWM0 clock source as PCLK0 */

#define CLK_CLKSEL2_PWM1SEL_PLL            (0x0UL<<CLK_CLKSEL2_PWM1SEL_Pos) /*!< Setting PWM1 clock source as PLL */
#define CLK_CLKSEL2_PWM1SEL_PCLK1          (0x1UL<<CLK_CLKSEL2_PWM1SEL_Pos) /*!< Setting PWM1 clock source as PCLK1 */

#define CLK_CLKSEL2_SPI0SEL_HXT            (0x0UL<<CLK_CLKSEL2_SPI0SEL_Pos) /*!< Setting SPI0 clock source as HXT */
#define CLK_CLKSEL2_SPI0SEL_PLL            (0x1UL<<CLK_CLKSEL2_SPI0SEL_Pos) /*!< Setting SPI0 clock source as PLL */
#define CLK_CLKSEL2_SPI0SEL_PCLK0          (0x2UL<<CLK_CLKSEL2_SPI0SEL_Pos) /*!< Setting SPI0 clock source as PCLK0 */
#define CLK_CLKSEL2_SPI0SEL_HIRC           (0x3UL<<CLK_CLKSEL2_SPI0SEL_Pos) /*!< Setting SPI0 clock source as HIRC */

#define CLK_CLKSEL2_SPI1SEL_HXT            (0x0UL<<CLK_CLKSEL2_SPI1SEL_Pos) /*!< Setting SPI1 clock source as HXT */
#define CLK_CLKSEL2_SPI1SEL_PLL            (0x1UL<<CLK_CLKSEL2_SPI1SEL_Pos) /*!< Setting SPI1 clock source as PLL */
#define CLK_CLKSEL2_SPI1SEL_PCLK1          (0x2UL<<CLK_CLKSEL2_SPI1SEL_Pos) /*!< Setting SPI1 clock source as PCLK1 */
#define CLK_CLKSEL2_SPI1SEL_HIRC           (0x3UL<<CLK_CLKSEL2_SPI1SEL_Pos) /*!< Setting SPI1 clock source as HIRC */

#define CLK_CLKSEL2_SPI2SEL_HXT            (0x0UL<<CLK_CLKSEL2_SPI2SEL_Pos) /*!< Setting SPI2 clock source as HXT */
#define CLK_CLKSEL2_SPI2SEL_PLL            (0x1UL<<CLK_CLKSEL2_SPI2SEL_Pos) /*!< Setting SPI2 clock source as PLL */
#define CLK_CLKSEL2_SPI2SEL_PCLK0          (0x2UL<<CLK_CLKSEL2_SPI2SEL_Pos) /*!< Setting SPI2 clock source as PCLK0 */
#define CLK_CLKSEL2_SPI2SEL_HIRC           (0x3UL<<CLK_CLKSEL2_SPI2SEL_Pos) /*!< Setting SPI2 clock source as HIRC */


/*---------------------------------------------------------------------------------------------------------*/
/*  CLKSEL3 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKSEL3_SC0SEL_HXT             (0x0UL<<CLK_CLKSEL3_SC0SEL_Pos) /*!< Setting SC0 clock source as HXT */
#define CLK_CLKSEL3_SC0SEL_PLL             (0x1UL<<CLK_CLKSEL3_SC0SEL_Pos) /*!< Setting SC0 clock source as PLL */
#define CLK_CLKSEL3_SC0SEL_PCLK0           (0x2UL<<CLK_CLKSEL3_SC0SEL_Pos) /*!< Setting SC0 clock source as PCLK0 */
#define CLK_CLKSEL3_SC0SEL_HIRC            (0x3UL<<CLK_CLKSEL3_SC0SEL_Pos) /*!< Setting SC0 clock source as HIRC */

#define CLK_CLKSEL3_RTCSEL_LXT             (0x0UL<<CLK_CLKSEL3_RTCSEL_Pos) /*!< Setting RTC clock source as LXT */
#define CLK_CLKSEL3_RTCSEL_LIRC            (0x1UL<<CLK_CLKSEL3_RTCSEL_Pos) /*!< Setting RTC clock source as LIRC */


/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV0 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV0_HCLK(x)     (((x)-1) << CLK_CLKDIV0_HCLKDIV_Pos) /*!< CLKDIV0 Setting for HCLK clock divider. It could be 1~16 */
#define CLK_CLKDIV0_USB(x)      (((x)-1) << CLK_CLKDIV0_USBDIV_Pos)  /*!< CLKDIV0 Setting for USB clock divider. It could be 1~16 */
#define CLK_CLKDIV0_UART(x)     (((x)-1) << CLK_CLKDIV0_UARTDIV_Pos) /*!< CLKDIV0 Setting for UART clock divider. It could be 1~16 */
#define CLK_CLKDIV0_EADC(x)     (((x)-1) << CLK_CLKDIV0_EADCDIV_Pos) /*!< CLKDIV0 Setting for EADC clock divider. It could be 1~256 */


/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV1 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV1_SC0(x)      (((x)-1) << CLK_CLKDIV1_SC0DIV_Pos) /*!< CLKDIV1 Setting for SC0 clock divider. It could be 1~256 */


/*---------------------------------------------------------------------------------------------------------*/
/*  PLLCTL constant definitions. PLL = FIN * NF / NR / NO                                                  */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_PLLCTL_PLLSRC_HXT   0x00000000UL    /*!< For PLL clock source is HXT.  3.2MHz < FIN < 150MHz */
#define CLK_PLLCTL_PLLSRC_HIRC  0x00080000UL    /*!< For PLL clock source is HIRC. 3.2MHz < FIN < 150MHz */

#define CLK_PLLCTL_NF(x)        ((x)-2)         /*!< x must be constant and 2 <= x <= 513. 200MHz < FIN*NF/NR < 500MHz. (FIN*NF/NR > 250MHz is preferred.) */
#define CLK_PLLCTL_NR(x)        (((x)-2)<<9)    /*!< x must be constant and 2 <= x <= 33.  1.6MHz < FIN/NR < 16MHz */

#define CLK_PLLCTL_NO_1         0x0000UL        /*!< For output divider is 1 */
#define CLK_PLLCTL_NO_2         0x4000UL        /*!< For output divider is 2 */
#define CLK_PLLCTL_NO_4         0xC000UL        /*!< For output divider is 4 */

#define CLK_PLLCTL_72MHz_HXT    (CLK_PLLCTL_PLLSRC_HXT  | CLK_PLLCTL_NR(2) | CLK_PLLCTL_NF( 48) | CLK_PLLCTL_NO_4) /*!< Predefined PLLCTL setting for 72MHz PLL output with HXT(12MHz X'tal) */
#define CLK_PLLCTL_144MHz_HXT   (CLK_PLLCTL_PLLSRC_HXT  | CLK_PLLCTL_NR(2) | CLK_PLLCTL_NF( 48) | CLK_PLLCTL_NO_2) /*!< Predefined PLLCTL setting for 144MHz PLL output with HXT(12MHz X'tal) */
#define CLK_PLLCTL_72MHz_HIRC   (CLK_PLLCTL_PLLSRC_HIRC | CLK_PLLCTL_NR(4) | CLK_PLLCTL_NF( 52) | CLK_PLLCTL_NO_4) /*!< Predefined PLLCTL setting for 71.8848MHz PLL output with HIRC(22.1184MHz IRC) */


/*---------------------------------------------------------------------------------------------------------*/
/*  MODULE constant definitions.                                                                           */
/*---------------------------------------------------------------------------------------------------------*/

/* APBCLK(31:30)|CLKSEL(29:28)|CLKSEL_Msk(27:25) |CLKSEL_Pos(24:20)|CLKDIV(19:18)|CLKDIV_Msk(17:10)|CLKDIV_Pos(9:5)|IP_EN_Pos(4:0) */

#define MODULE_APBCLK(x)        (((x) >>30) & 0x3)    /*!< Calculate AHBCLK/APBCLK offset on MODULE index, 0x0:AHBCLK, 0x1:APBCLK0, 0x2:APBCLK1 */
#define MODULE_CLKSEL(x)        (((x) >>28) & 0x3)    /*!< Calculate CLKSEL offset on MODULE index, 0x0:CLKSEL0, 0x1:CLKSEL1, 0x2:CLKSEL2, 0x3:CLKSEL3 */
#define MODULE_CLKSEL_Msk(x)    (((x) >>25) & 0x7)    /*!< Calculate CLKSEL mask offset on MODULE index */
#define MODULE_CLKSEL_Pos(x)    (((x) >>20) & 0x1f)   /*!< Calculate CLKSEL position offset on MODULE index */
#define MODULE_CLKDIV(x)        (((x) >>18) & 0x3)    /*!< Calculate APBCLK CLKDIV on MODULE index, 0x0:CLKDIV, 0x1:CLKDIV1 */
#define MODULE_CLKDIV_Msk(x)    (((x) >>10) & 0xff)   /*!< Calculate CLKDIV mask offset on MODULE index */
#define MODULE_CLKDIV_Pos(x)    (((x) >>5 ) & 0x1f)   /*!< Calculate CLKDIV position offset on MODULE index */
#define MODULE_IP_EN_Pos(x)     (((x) >>0 ) & 0x1f)   /*!< Calculate APBCLK offset on MODULE index */
#define MODULE_NoMsk            0x0                 /*!< Not mask on MODULE index */
#define NA                      MODULE_NoMsk        /*!< Not Available */

#define MODULE_APBCLK_ENC(x)        (((x) & 0x03) << 30)   /*!< MODULE index, 0x0:AHBCLK, 0x1:APBCLK0, 0x2:APBCLK1 */
#define MODULE_CLKSEL_ENC(x)        (((x) & 0x03) << 28)   /*!< CLKSEL offset on MODULE index, 0x0:CLKSEL0, 0x1:CLKSEL1, 0x2:CLKSEL2, 0x3:CLKSEL3 */
#define MODULE_CLKSEL_Msk_ENC(x)    (((x) & 0x07) << 25)   /*!< CLKSEL mask offset on MODULE index */
#define MODULE_CLKSEL_Pos_ENC(x)    (((x) & 0x1f) << 20)   /*!< CLKSEL position offset on MODULE index */
#define MODULE_CLKDIV_ENC(x)        (((x) & 0x03) << 18)   /*!< APBCLK CLKDIV on MODULE index, 0x0:CLKDIV, 0x1:CLKDIV1 */
#define MODULE_CLKDIV_Msk_ENC(x)    (((x) & 0xff) << 10)   /*!< CLKDIV mask offset on MODULE index */
#define MODULE_CLKDIV_Pos_ENC(x)    (((x) & 0x1f) <<  5)   /*!< CLKDIV position offset on MODULE index */
#define MODULE_IP_EN_Pos_ENC(x)     (((x) & 0x1f) <<  0)   /*!< AHBCLK/APBCLK offset on MODULE index */


//AHBCLK
#define PDMA_MODULE    (MODULE_APBCLK_ENC( 0)|MODULE_IP_EN_Pos_ENC(CLK_AHBCLK_PDMACKEN_Pos)  |\
                        MODULE_CLKSEL_ENC(NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< PDMA Module */

#define ISP_MODULE     (MODULE_APBCLK_ENC( 0)|MODULE_IP_EN_Pos_ENC(CLK_AHBCLK_ISPCKEN_Pos)  |\
                        MODULE_CLKSEL_ENC(NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< ISP Module */

#define EBI_MODULE     (MODULE_APBCLK_ENC( 0)|MODULE_IP_EN_Pos_ENC(CLK_AHBCLK_EBICKEN_Pos)  |\
                        MODULE_CLKSEL_ENC(NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< EBI Module */

#define USBH_MODULE    (MODULE_APBCLK_ENC( 0)|MODULE_IP_EN_Pos_ENC(CLK_AHBCLK_USBHCKEN_Pos)  |\
                        MODULE_CLKSEL_ENC(NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC( 0)|MODULE_CLKDIV_Msk_ENC(0x0F)|MODULE_CLKDIV_Pos_ENC(4))     /*!< USBH Module */

#define CRC_MODULE     (MODULE_APBCLK_ENC( 0)|MODULE_IP_EN_Pos_ENC(CLK_AHBCLK_CRCCKEN_Pos)  |\
                        MODULE_CLKSEL_ENC(NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< CRC Module */


//APBCLK0
#define WDT_MODULE     (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_WDTCKEN_Pos)  |\
                        MODULE_CLKSEL_ENC( 1)|MODULE_CLKSEL_Msk_ENC( 3)|MODULE_CLKSEL_Pos_ENC( 0)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< WDT Module */

#define WWDT_MODULE    (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_WDTCKEN_Pos)  |\
                        MODULE_CLKSEL_ENC( 1)|MODULE_CLKSEL_Msk_ENC( 3)|MODULE_CLKSEL_Pos_ENC(30)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< WWDT Module */

#define RTC_MODULE     (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_RTCCKEN_Pos)  |\
                        MODULE_CLKSEL_ENC( 3)|MODULE_CLKSEL_Msk_ENC( 1)|MODULE_CLKSEL_Pos_ENC( 8)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< RTC Module */

#define TMR0_MODULE    (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_TMR0CKEN_Pos) |\
                        MODULE_CLKSEL_ENC( 1)|MODULE_CLKSEL_Msk_ENC( 7)|MODULE_CLKSEL_Pos_ENC( 8)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< TMR0 Module */

#define TMR1_MODULE    (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_TMR1CKEN_Pos) |\
                        MODULE_CLKSEL_ENC( 1)|MODULE_CLKSEL_Msk_ENC( 7)|MODULE_CLKSEL_Pos_ENC(12)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< TMR1 Module */

#define TMR2_MODULE    (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_TMR2CKEN_Pos) |\
                        MODULE_CLKSEL_ENC( 1)|MODULE_CLKSEL_Msk_ENC( 7)|MODULE_CLKSEL_Pos_ENC(16)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< TMR2 Module */

#define TMR3_MODULE    (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_TMR3CKEN_Pos) |\
                        MODULE_CLKSEL_ENC( 1)|MODULE_CLKSEL_Msk_ENC( 7)|MODULE_CLKSEL_Pos_ENC(20)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< TMR3 Module */

#define CLKO_MODULE    (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_CLKOCKEN_Pos) |\
                        MODULE_CLKSEL_ENC( 1)|MODULE_CLKSEL_Msk_ENC( 3)|MODULE_CLKSEL_Pos_ENC(28)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< CLKO Module */

#define ACMP01_MODULE  (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_ACMP01CKEN_Pos) |\
                        MODULE_CLKSEL_ENC(NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< ACMP01 Module */

#define I2C0_MODULE    (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_I2C0CKEN_Pos) |\
                        MODULE_CLKSEL_ENC(NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< I2C0 Module */

#define I2C1_MODULE    (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_I2C1CKEN_Pos) |\
                        MODULE_CLKSEL_ENC(NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< I2C1 Module */

#define SPI0_MODULE    (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_SPI0CKEN_Pos) |\
                        MODULE_CLKSEL_ENC( 2)|MODULE_CLKSEL_Msk_ENC( 3)|MODULE_CLKSEL_Pos_ENC( 2)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< SPI0 Module */

#define SPI1_MODULE    (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_SPI1CKEN_Pos) |\
                        MODULE_CLKSEL_ENC( 2)|MODULE_CLKSEL_Msk_ENC( 3)|MODULE_CLKSEL_Pos_ENC( 4)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< SPI1 Module */

#define SPI2_MODULE    (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_SPI2CKEN_Pos) |\
                        MODULE_CLKSEL_ENC( 2)|MODULE_CLKSEL_Msk_ENC( 3)|MODULE_CLKSEL_Pos_ENC( 6)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< SPI2 Module */

#define UART0_MODULE   (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_UART0CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 1)|MODULE_CLKSEL_Msk_ENC( 3)|MODULE_CLKSEL_Pos_ENC(24)|\
                        MODULE_CLKDIV_ENC( 0)|MODULE_CLKDIV_Msk_ENC(0x0F)|MODULE_CLKDIV_Pos_ENC( 8))    /*!< UART0 Module */

#define UART1_MODULE   (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_UART1CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 1)|MODULE_CLKSEL_Msk_ENC( 3)|MODULE_CLKSEL_Pos_ENC(24)|\
                        MODULE_CLKDIV_ENC( 0)|MODULE_CLKDIV_Msk_ENC(0x0F)|MODULE_CLKDIV_Pos_ENC( 8))    /*!< UART1 Module */

#define UART2_MODULE   (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_UART2CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 1)|MODULE_CLKSEL_Msk_ENC( 3)|MODULE_CLKSEL_Pos_ENC(24)|\
                        MODULE_CLKDIV_ENC( 0)|MODULE_CLKDIV_Msk_ENC(0x0F)|MODULE_CLKDIV_Pos_ENC( 8))    /*!< UART2 Module */

#define UART3_MODULE   (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_UART3CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 1)|MODULE_CLKSEL_Msk_ENC( 3)|MODULE_CLKSEL_Pos_ENC(24)|\
                        MODULE_CLKDIV_ENC( 0)|MODULE_CLKDIV_Msk_ENC(0x0F)|MODULE_CLKDIV_Pos_ENC( 8))    /*!< UART3 Module */

#define CAN0_MODULE    (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_CAN0CKEN_Pos) |\
                        MODULE_CLKSEL_ENC(NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< CAN0 Module */

#define OTG_MODULE     (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_OTGCKEN_Pos) |\
                        MODULE_CLKSEL_ENC(NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC( 0)|MODULE_CLKDIV_Msk_ENC(0x0F)|MODULE_CLKDIV_Pos_ENC(4))     /*!< OTG Module */

#define USBD_MODULE    (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_USBDCKEN_Pos) |\
                        MODULE_CLKSEL_ENC(NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC( 0)|MODULE_CLKDIV_Msk_ENC(0x0F)|MODULE_CLKDIV_Pos_ENC(4))     /*!< USBD Module */

#define EADC_MODULE    (MODULE_APBCLK_ENC( 1)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK0_EADCCKEN_Pos)  |\
                        MODULE_CLKSEL_ENC(NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC( 0)|MODULE_CLKDIV_Msk_ENC(0xFF)|MODULE_CLKDIV_Pos_ENC(16))    /*!< EADC Module */


//APBCLK1
#define SC0_MODULE     (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK1_SC0CKEN_Pos)  |\
                        MODULE_CLKSEL_ENC( 3)|MODULE_CLKSEL_Msk_ENC( 3)|MODULE_CLKSEL_Pos_ENC( 0)|\
                        MODULE_CLKDIV_ENC( 1)|MODULE_CLKDIV_Msk_ENC(0xFF)|MODULE_CLKDIV_Pos_ENC( 0))    /*!< SC0 Module */

#define DAC_MODULE     (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK1_DACCKEN_Pos)  |\
                        MODULE_CLKSEL_ENC(NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< DAC Module */

#define PWM0_MODULE    (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK1_PWM0CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 2)|MODULE_CLKSEL_Msk_ENC( 1)|MODULE_CLKSEL_Pos_ENC( 0)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< PWM0 Module */

#define PWM1_MODULE    (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK1_PWM1CKEN_Pos)|\
                        MODULE_CLKSEL_ENC( 2)|MODULE_CLKSEL_Msk_ENC( 1)|MODULE_CLKSEL_Pos_ENC( 1)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< PWM1 Module */

#define TK_MODULE      (MODULE_APBCLK_ENC( 2UL)|MODULE_IP_EN_Pos_ENC(CLK_APBCLK1_TKCKEN_Pos)|\
                        MODULE_CLKSEL_ENC(NA)|MODULE_CLKSEL_Msk_ENC(NA)|MODULE_CLKSEL_Pos_ENC(NA)|\
                        MODULE_CLKDIV_ENC(NA)|MODULE_CLKDIV_Msk_ENC(NA)|MODULE_CLKDIV_Pos_ENC(NA))      /*!< TK Module */


/*@}*/ /* end of group CLK_EXPORTED_CONSTANTS */


/** @addtogroup CLK_EXPORTED_FUNCTIONS CLK Exported Functions
  @{
*/


/**
  * @brief      Get PLL clock frequency
  * @param      None
  * @return     PLL frequency
  * @details    This function get PLL frequency. The frequency unit is Hz.
  */
__STATIC_INLINE uint32_t CLK_GetPLLClockFreq(void)
{
    uint32_t u32PllFreq = 0, u32PllReg;
    uint32_t u32FIN, u32NF, u32NR, u32NO;
    uint8_t au8NoTbl[4] = {1, 2, 2, 4};

    u32PllReg = CLK->PLLCTL;

    if(u32PllReg & (CLK_PLLCTL_PD_Msk | CLK_PLLCTL_OE_Msk))
        return 0;           /* PLL is in power down mode or fix low */

    if(u32PllReg & CLK_PLLCTL_PLLSRC_HIRC)
        u32FIN = __HIRC;    /* PLL source clock from HIRC */
    else
        u32FIN = __HXT;     /* PLL source clock from HXT */

    if(u32PllReg & CLK_PLLCTL_BP_Msk)
        return u32FIN;      /* PLL is in bypass mode */

    /* PLL is output enabled in normal work mode */
    u32NO = au8NoTbl[((u32PllReg & CLK_PLLCTL_OUTDIV_Msk) >> CLK_PLLCTL_OUTDIV_Pos)];
    u32NF = ((u32PllReg & CLK_PLLCTL_FBDIV_Msk) >> CLK_PLLCTL_FBDIV_Pos) + 2;
    u32NR = ((u32PllReg & CLK_PLLCTL_INDIV_Msk) >> CLK_PLLCTL_INDIV_Pos) + 2;

    /* u32FIN is shifted 2 bits to avoid overflow */
    u32PllFreq = (((u32FIN >> 2) * u32NF) / (u32NR * u32NO) << 2);

    return u32PllFreq;
}

/**
  * @brief      This function execute delay function.
  * @param      us  Delay time. The Max value is 2^24 / CPU Clock(MHz). Ex:
  *                             72MHz => 233016us, 50MHz => 335544us,
                                48MHz => 349525us, 28MHz => 699050us ...
  * @return     None
  * @details    Use the SysTick to generate the delay time and the unit is in us.
  *             The SysTick clock source is from HCLK, i.e the same as system core clock.
  */
__STATIC_INLINE void CLK_SysTickDelay(uint32_t us)
{
    SysTick->LOAD = us * CyclesPerUs;
    SysTick->VAL  = (0x00);
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

    /* Waiting for down-count to zero */
    while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
    
    /* Disable SysTick counter */
    SysTick->CTRL = 0;
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



/*@}*/ /* end of group CLK_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CLK_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif  //__CLK_H__
