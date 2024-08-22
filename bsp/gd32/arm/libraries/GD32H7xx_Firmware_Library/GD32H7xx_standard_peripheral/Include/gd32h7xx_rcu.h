/*!
    \file    gd32h7xx_rcu.h
    \brief   definitions for the RCU

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef GD32H7XX_RCU_H
#define GD32H7XX_RCU_H

#include "gd32h7xx.h"

/* RCU definitions */
#define RCU                             RCU_BASE

/* registers definitions */
#define RCU_CTL                         REG32(RCU + 0x00000000U)                    /*!< control register */
#define RCU_PLL0                        REG32(RCU + 0x00000004U)                    /*!< PLL0 register */
#define RCU_CFG0                        REG32(RCU + 0x00000008U)                    /*!< clock configuration register 0 */
#define RCU_INT                         REG32(RCU + 0x0000000CU)                    /*!< clock interrupt register */
#define RCU_AHB1RST                     REG32(RCU + 0x00000010U)                    /*!< AHB1 reset register */
#define RCU_AHB2RST                     REG32(RCU + 0x00000014U)                    /*!< AHB2 reset register */
#define RCU_AHB3RST                     REG32(RCU + 0x00000018U)                    /*!< AHB3 reset register */
#define RCU_AHB4RST                     REG32(RCU + 0x0000001CU)                    /*!< AHB4 reset register */
#define RCU_APB1RST                     REG32(RCU + 0x00000020U)                    /*!< APB1 reset register */
#define RCU_APB2RST                     REG32(RCU + 0x00000024U)                    /*!< APB2 reset register */
#define RCU_APB3RST                     REG32(RCU + 0x00000028U)                    /*!< APB3 reset register */
#define RCU_APB4RST                     REG32(RCU + 0x0000002CU)                    /*!< APB4 reset register */
#define RCU_AHB1EN                      REG32(RCU + 0x00000030U)                    /*!< AHB1 enable register */
#define RCU_AHB2EN                      REG32(RCU + 0x00000034U)                    /*!< AHB2 enable register */
#define RCU_AHB3EN                      REG32(RCU + 0x00000038U)                    /*!< AHB3 enable register */
#define RCU_AHB4EN                      REG32(RCU + 0x0000003CU)                    /*!< AHB4 enable register */
#define RCU_APB1EN                      REG32(RCU + 0x00000040U)                    /*!< APB1 enable register */
#define RCU_APB2EN                      REG32(RCU + 0x00000044U)                    /*!< APB2 enable register */
#define RCU_APB3EN                      REG32(RCU + 0x00000048U)                    /*!< APB3 enable register */
#define RCU_APB4EN                      REG32(RCU + 0x0000004CU)                    /*!< APB4 enable register */
#define RCU_AHB1SPEN                    REG32(RCU + 0x00000050U)                    /*!< AHB1 sleep mode enable register */
#define RCU_AHB2SPEN                    REG32(RCU + 0x00000054U)                    /*!< AHB2 sleep mode enable register */
#define RCU_AHB3SPEN                    REG32(RCU + 0x00000058U)                    /*!< AHB3 sleep mode enable register */
#define RCU_AHB4SPEN                    REG32(RCU + 0x0000005CU)                    /*!< AHB4 sleep mode enable register */
#define RCU_APB1SPEN                    REG32(RCU + 0x00000060U)                    /*!< APB1 sleep mode enable register */
#define RCU_APB2SPEN                    REG32(RCU + 0x00000064U)                    /*!< APB2 sleep mode enable register */
#define RCU_APB3SPEN                    REG32(RCU + 0x00000068U)                    /*!< APB3 sleep mode enable register */
#define RCU_APB4SPEN                    REG32(RCU + 0x0000006CU)                    /*!< APB4 sleep mode enable register */
#define RCU_BDCTL                       REG32(RCU + 0x00000070U)                    /*!< backup domain control register */
#define RCU_RSTSCK                      REG32(RCU + 0x00000074U)                    /*!< reset source / clock register */
#define RCU_PLLADDCTL                   REG32(RCU + 0x00000080U)                    /*!< PLL clock additional control register */
#define RCU_PLL1                        REG32(RCU + 0x00000084U)                    /*!< PLL1 register */
#define RCU_PLL2                        REG32(RCU + 0x00000088U)                    /*!< PLL2 register */
#define RCU_CFG1                        REG32(RCU + 0x0000008CU)                    /*!< clock configuration register 1 */
#define RCU_CFG2                        REG32(RCU + 0x00000090U)                    /*!< clock configuration register 2 */
#define RCU_CFG3                        REG32(RCU + 0x00000094U)                    /*!< clock configuration register 3 */
#define RCU_PLLALL                      REG32(RCU + 0x00000098U)                    /*!< PLL configuration register */
#define RCU_PLL0FRA                     REG32(RCU + 0x0000009CU)                    /*!< PLL0 fraction configuration register */
#define RCU_PLL1FRA                     REG32(RCU + 0x000000A0U)                    /*!< PLL1 fraction configuration register */
#define RCU_PLL2FRA                     REG32(RCU + 0x000000A4U)                    /*!< PLL2 fraction configuration register */
#define RCU_ADDCTL0                     REG32(RCU + 0x000000C0U)                    /*!< additional clock control register 0 */
#define RCU_ADDCTL1                     REG32(RCU + 0x000000C4U)                    /*!< additional clock control register 1 */
#define RCU_ADDINT                      REG32(RCU + 0x000000CCU)                    /*!< additional clock interrupt register */
#define RCU_CFG4                        REG32(RCU + 0x000000D0U)                    /*!< clock configuration register 4  */
#define RCU_USBCLKCTL                   REG32(RCU + 0x000000D4U)                    /*!< USB clock control register */
#define RCU_PLLUSBCFG                   REG32(RCU + 0x000000D8U)                    /*!< PLLUSB configuration register */
#define RCU_ADDAPB2RST                  REG32(RCU + 0x000000E0U)                    /*!< APB2 additional reset register */
#define RCU_ADDAPB2EN                   REG32(RCU + 0x000000E4U)                    /*!< APB2 additional enable register */
#define RCU_ADDAPB2SPEN                 REG32(RCU + 0x000000E8U)                    /*!< APB2 additional sleep mode enable register */
#define RCU_CFG5                        REG32(RCU + 0x000000F0U)                    /*!< clock configuration register 5  */

/* bits definitions */
/* RCU_CTL */
#define RCU_CTL_IRC64MADJ               BITS(0,6)                                   /*!< high speed internal oscillator clock trim adjust value */
#define RCU_CTL_IRC64MCALIB             BITS(7,15)                                  /*!< high speed internal oscillator calibration value register */
#define RCU_CTL_HXTALEN                 BIT(16)                                     /*!< external high speed oscillator enable */
#define RCU_CTL_HXTALSTB                BIT(17)                                     /*!< external crystal oscillator clock stabilization flag */
#define RCU_CTL_HXTALBPS                BIT(18)                                     /*!< external crystal oscillator clock bypass mode enable */
#define RCU_CTL_CKMEN                   BIT(19)                                     /*!< HXTAL clock monitor enable */
#define RCU_CTL_PLL0EN                  BIT(24)                                     /*!< PLL0 enable */
#define RCU_CTL_PLL0STB                 BIT(25)                                     /*!< PLL0 clock stabilization flag */
#define RCU_CTL_PLL1EN                  BIT(26)                                     /*!< PLL1 enable */
#define RCU_CTL_PLL1STB                 BIT(27)                                     /*!< PLL1 clock stabilization flag */
#define RCU_CTL_PLL2EN                  BIT(28)                                     /*!< PLL2 enable */
#define RCU_CTL_PLL2STB                 BIT(29)                                     /*!< PLL2 clock stabilization flag */
#define RCU_CTL_IRC64MEN                BIT(30)                                     /*!< IRC64M high speed oscillator enable */
#define RCU_CTL_IRC64MSTB               BIT(31)                                     /*!< IRC64M high speed internal oscillator stabilization flag */

/* RCU_PLL0 */
#define RCU_PLL0_PLL0PSC                BITS(0,5)                                   /*!< The PLL0 VCO source clock prescaler */
#define RCU_PLL0_PLL0N                  BITS(6,14)                                  /*!< The PLL0 VCO clock multi factor */
#define RCU_PLL0_PLL0P                  BITS(16,22)                                 /*!< The PLL0P output frequency division factor from PLL0 VCO clock */
#define RCU_PLL0_PLL0R                  BITS(24,30)                                 /*!< the PLL0R output frequency division factor from PLL0 VCO clock */
#define RCU_PLL0_PLLSTBSRC              BIT(31)                                     /*!< PLLs stabilization signal sources */

/* RCU_CFG0 */
#define RCU_CFG0_SCS                    BITS(0,1)                                   /*!< system clock switch */
#define RCU_CFG0_SCSS                   BITS(2,3)                                   /*!< system clock switch status */
#define RCU_CFG0_AHBPSC                 BITS(4,7)                                   /*!< AHB prescaler selection */
#define RCU_CFG0_APB1PSC                BITS(10,12)                                 /*!< APB1 prescaler selection */
#define RCU_CFG0_APB2PSC                BITS(13,15)                                 /*!< APB2 prescaler selection */
#define RCU_CFG0_RTCDIV                 BITS(16,21)                                 /*!< RTC clock divider factor */
#define RCU_CFG0_APB4PSC                BITS(24,26)                                 /*!< APB4 prescaler selection */
#define RCU_CFG0_APB3PSC                BITS(27,29)                                 /*!< APB3 prescaler selection */
#define RCU_CFG0_I2C0SEL                BITS(30,31)                                 /*!< I2C0 clock source selection */

/* RCU_INT */
#define RCU_INT_IRC32KSTBIF             BIT(0)                                      /*!< IRC32K stabilization interrupt flag */
#define RCU_INT_LXTALSTBIF              BIT(1)                                      /*!< LXTAL stabilization interrupt flag */
#define RCU_INT_IRC64MSTBIF             BIT(2)                                      /*!< IRC64M stabilization interrupt flag */
#define RCU_INT_HXTALSTBIF              BIT(3)                                      /*!< HXTAL stabilization interrupt flag */
#define RCU_INT_PLL0STBIF               BIT(4)                                      /*!< PLL0 stabilization interrupt flag */
#define RCU_INT_PLL1STBIF               BIT(5)                                      /*!< PLL1 stabilization interrupt flag */
#define RCU_INT_PLL2STBIF               BIT(6)                                      /*!< PLL2 stabilization interrupt flag */
#define RCU_INT_CKMIF                   BIT(7)                                      /*!< HXTAL clock stuck interrupt flag */
#define RCU_INT_IRC32KSTBIE             BIT(8)                                      /*!< IRC32K stabilization interrupt enable */
#define RCU_INT_LXTALSTBIE              BIT(9)                                      /*!< LXTAL stabilization interrupt enable */
#define RCU_INT_IRC64MSTBIE             BIT(10)                                     /*!< IRC64M stabilization interrupt enable */
#define RCU_INT_HXTALSTBIE              BIT(11)                                     /*!< HXTAL stabilization interrupt enable */
#define RCU_INT_PLL0STBIE               BIT(12)                                     /*!< PLL0 stabilization interrupt enable */
#define RCU_INT_PLL1STBIE               BIT(13)                                     /*!< PLL1 stabilization interrupt enable */
#define RCU_INT_PLL2STBIE               BIT(14)                                     /*!< PLL2 stabilization interrupt enable */
#define RCU_INT_IRC32KSTBIC             BIT(16)                                     /*!< IRC32K stabilization interrupt clear */
#define RCU_INT_LXTALSTBIC              BIT(17)                                     /*!< LXTAL stabilization interrupt clear */
#define RCU_INT_IRC64MSTBIC             BIT(18)                                     /*!< IRC64M stabilization interrupt clear */
#define RCU_INT_HXTALSTBIC              BIT(19)                                     /*!< HXTAL stabilization interrupt clear */
#define RCU_INT_PLL0STBIC               BIT(20)                                     /*!< PLL0 stabilization interrupt clear */
#define RCU_INT_PLL1STBIC               BIT(21)                                     /*!< PLL1 stabilization interrupt clear */
#define RCU_INT_PLL2STBIC               BIT(22)                                     /*!< PLL2 stabilization interrupt clear */
#define RCU_INT_CKMIC                   BIT(23)                                     /*!< HXTAL clock stuck interrupt clear */
#define RCU_INT_LPIRC4MSTBIF            BIT(24)                                     /*!< LPIRC4M stabilization interrupt flag */
#define RCU_INT_LPIRC4MSTBIE            BIT(25)                                     /*!< LPIRC4M stabilization interrupt enable */
#define RCU_INT_LPIRC4MSTBIC            BIT(26)                                     /*!< LPIRC4M stabilization interrupt clear */
#define RCU_INT_LCKMIF                  BIT(27)                                     /*!< LXTAL clock stuck interrupt flag */
#define RCU_INT_LCKMIC                  BIT(28)                                     /*!< LXTAL clock stuck interrupt clear */

/* RCU_AHB1RST */
#define RCU_AHB1RST_ENET1RST            BIT(0)                                      /*!< ENET1 reset */
#define RCU_AHB1RST_USBHS0RST           BIT(14)                                     /*!< USBHS0 reset */
#define RCU_AHB1RST_DMA0RST             BIT(21)                                     /*!< DMA0 reset */
#define RCU_AHB1RST_DMA1RST             BIT(22)                                     /*!< DMA1 reset */
#define RCU_AHB1RST_DMAMUXRST           BIT(23)                                     /*!< DMAMUX reset */
#define RCU_AHB1RST_ENET0RST            BIT(25)                                     /*!< ENET0 reset */
#define RCU_AHB1RST_USBHS1RST           BIT(29)                                     /*!< USBHS1 reset */

/* RCU_AHB2RST */
#define RCU_AHB2RST_DCIRST              BIT(0)                                      /*!< DCI reset */
#define RCU_AHB2RST_FACRST              BIT(1)                                      /*!< FAC reset */
#define RCU_AHB2RST_SDIO1RST            BIT(2)                                      /*!< SDIO1 reset */
#define RCU_AHB2RST_CAURST              BIT(3)                                      /*!< CAU reset */
#define RCU_AHB2RST_HAURST              BIT(4)                                      /*!< HAU reset */
#define RCU_AHB2RST_TRNGRST             BIT(6)                                      /*!< TRNG reset */
#define RCU_AHB2RST_TMURST              BIT(7)                                      /*!< TMU reset */

/* RCU_AHB3RST */
#define RCU_AHB3RST_EXMCRST             BIT(0)                                      /*!< EXMC reset */
#define RCU_AHB3RST_IPARST              BIT(1)                                      /*!< IPA reset */
#define RCU_AHB3RST_SDIO0RST            BIT(2)                                      /*!< SDIO0 reset */
#define RCU_AHB3RST_MDMARST             BIT(3)                                      /*!< MDMA reset */
#define RCU_AHB3RST_OSPIMRST            BIT(4)                                      /*!< OSPIM reset */
#define RCU_AHB3RST_OSPI0RST            BIT(5)                                      /*!< OSPI0 reset */
#define RCU_AHB3RST_OSPI1RST            BIT(6)                                      /*!< OSPI1 reset */
#define RCU_AHB3RST_RTDEC0RST           BIT(8)                                      /*!< RTDEC0 reset */
#define RCU_AHB3RST_RTDEC1RST           BIT(9)                                      /*!< RTDEC1 reset */

/* RCU_AHB4RST */
#define RCU_AHB4RST_PARST               BIT(0)                                      /*!< GPIO port A reset */
#define RCU_AHB4RST_PBRST               BIT(1)                                      /*!< GPIO port B reset */
#define RCU_AHB4RST_PCRST               BIT(2)                                      /*!< GPIO port C reset */
#define RCU_AHB4RST_PDRST               BIT(3)                                      /*!< GPIO port D reset */
#define RCU_AHB4RST_PERST               BIT(4)                                      /*!< GPIO port E reset */
#define RCU_AHB4RST_PFRST               BIT(5)                                      /*!< GPIO port F reset */
#define RCU_AHB4RST_PGRST               BIT(6)                                      /*!< GPIO port G reset */
#define RCU_AHB4RST_PHRST               BIT(7)                                      /*!< GPIO port H reset */
#define RCU_AHB4RST_PJRST               BIT(8)                                      /*!< GPIO port J reset */
#define RCU_AHB4RST_PKRST               BIT(9)                                      /*!< GPIO port K reset */
#define RCU_AHB4RST_CRCRST              BIT(14)                                     /*!< CRC reset */
#define RCU_AHB4RST_HWSEMRST            BIT(15)                                     /*!< HWSEM reset */

/* RCU_APB1RST */
#define RCU_APB1RST_TIMER1RST           BIT(0)                                      /*!< TIMER1 reset */
#define RCU_APB1RST_TIMER2RST           BIT(1)                                      /*!< TIMER2 reset */
#define RCU_APB1RST_TIMER3RST           BIT(2)                                      /*!< TIMER3 reset */
#define RCU_APB1RST_TIMER4RST           BIT(3)                                      /*!< TIMER4 reset */
#define RCU_APB1RST_TIMER5RST           BIT(4)                                      /*!< TIMER5 reset */
#define RCU_APB1RST_TIMER6RST           BIT(5)                                      /*!< TIMER6 reset */
#define RCU_APB1RST_TIMER22RST          BIT(6)                                      /*!< TIMER22 reset */
#define RCU_APB1RST_TIMER23RST          BIT(7)                                      /*!< TIMER23 reset */
#define RCU_APB1RST_TIMER30RST          BIT(8)                                      /*!< TIMER30 reset */
#define RCU_APB1RST_TIMER31RST          BIT(9)                                      /*!< TIMER31 reset */
#define RCU_APB1RST_TIMER50RST          BIT(10)                                     /*!< TIMER50 reset */
#define RCU_APB1RST_TIMER51RST          BIT(11)                                     /*!< TIMER51 reset */
#define RCU_APB1RST_RSPDIFRST           BIT(13)                                     /*!< RSPDIF reset */
#define RCU_APB1RST_SPI1RST             BIT(14)                                     /*!< SPI1 reset */
#define RCU_APB1RST_SPI2RST             BIT(15)                                     /*!< SPI2 reset */
#define RCU_APB1RST_MDIORST             BIT(16)                                     /*!< MDIO reset */
#define RCU_APB1RST_USART1RST           BIT(17)                                     /*!< USART1 reset */
#define RCU_APB1RST_USART2RST           BIT(18)                                     /*!< USART2 reset */
#define RCU_APB1RST_UART3RST            BIT(19)                                     /*!< UART3 reset */
#define RCU_APB1RST_UART4RST            BIT(20)                                     /*!< UART4 reset */
#define RCU_APB1RST_I2C0RST             BIT(21)                                     /*!< I2C0 reset */
#define RCU_APB1RST_I2C1RST             BIT(22)                                     /*!< I2C1 reset */
#define RCU_APB1RST_I2C2RST             BIT(23)                                     /*!< I2C2 reset */
#define RCU_APB1RST_I2C3RST             BIT(24)                                     /*!< I2C3 reset */
#define RCU_APB1RST_CTCRST              BIT(27)                                     /*!< CTC reset */
#define RCU_APB1RST_DACHOLDRST          BIT(28)                                     /*!< DAC hold clock reset */
#define RCU_APB1RST_DACRST              BIT(29)                                     /*!< DAC reset */
#define RCU_APB1RST_UART6RST            BIT(30)                                     /*!< UART6 reset */
#define RCU_APB1RST_UART7RST            BIT(31)                                     /*!< UART7 reset */

/* RCU_APB2RST */
#define RCU_APB2RST_TIMER0RST           BIT(0)                                      /*!< TIMER0 reset */
#define RCU_APB2RST_TIMER7RST           BIT(1)                                      /*!< TIMER7 reset */
#define RCU_APB2RST_USART0RST           BIT(4)                                      /*!< USART0 reset */
#define RCU_APB2RST_USART5RST           BIT(5)                                      /*!< USART5 reset */
#define RCU_APB2RST_ADC0RST             BIT(8)                                      /*!< ADC0 reset */
#define RCU_APB2RST_ADC1RST             BIT(9)                                      /*!< ADC1 reset */
#define RCU_APB2RST_ADC2RST             BIT(10)                                     /*!< ADC2 reset */
#define RCU_APB2RST_SPI0RST             BIT(12)                                     /*!< SPI0 reset */
#define RCU_APB2RST_SPI3RST             BIT(13)                                     /*!< SPI3 reset */
#define RCU_APB2RST_TIMER14RST          BIT(16)                                     /*!< TIMER14 reset */
#define RCU_APB2RST_TIMER15RST          BIT(17)                                     /*!< TIMER15 reset */
#define RCU_APB2RST_TIMER16RST          BIT(18)                                     /*!< TIMER15 reset */
#define RCU_APB2RST_HPDFRST             BIT(19)                                     /*!< HPDF reset */
#define RCU_APB2RST_SPI4RST             BIT(20)                                     /*!< SPI4 reset */
#define RCU_APB2RST_SPI5RST             BIT(21)                                     /*!< SPI5 reset */
#define RCU_APB2RST_SAI0RST             BIT(22)                                     /*!< SAI0 reset */
#define RCU_APB2RST_SAI1RST             BIT(23)                                     /*!< SAI1 reset */
#define RCU_APB2RST_SAI2RST             BIT(24)                                     /*!< SAI2 reset */
#define RCU_APB2RST_TIMER40RST          BIT(25)                                     /*!< TIMER40 reset */
#define RCU_APB2RST_TIMER41RST          BIT(26)                                     /*!< TIMER41 reset */
#define RCU_APB2RST_TIMER42RST          BIT(27)                                     /*!< TIMER42 reset */
#define RCU_APB2RST_TIMER43RST          BIT(28)                                     /*!< TIMER43 reset */
#define RCU_APB2RST_TIMER44RST          BIT(29)                                     /*!< TIMER44 reset */
#define RCU_APB2RST_EDOUTRST            BIT(30)                                     /*!< EDOUT reset */
#define RCU_APB2RST_TRIGSELRST          BIT(31)                                     /*!< TRIGSEL reset */

/* RCU_APB3RST */
#define RCU_APB3RST_TLIRST              BIT(0)                                      /*!< TLI reset */
#define RCU_APB3RST_WWDGTRST            BIT(1)                                      /*!< WWDGT reset */

/* RCU_APB4RST */
#define RCU_APB4RST_SYSCFGRST           BIT(0)                                      /*!< SYSCFG reset */
#define RCU_APB4RST_CMPRST              BIT(1)                                      /*!< CMP reset */
#define RCU_APB4RST_VREFRST             BIT(2)                                      /*!< VREF reset */
#define RCU_APB4RST_LPDTSRST            BIT(3)                                      /*!< LPDTS reset */
#define RCU_APB4RST_PMURST              BIT(4)                                      /*!< PMU reset */

/* RCU_AHB1EN */
#define RCU_AHB1EN_ENET1EN              BIT(0)                                      /*!< ENET1 clock enable */
#define RCU_AHB1EN_ENET1TXEN            BIT(1)                                      /*!< ENET1 TX clock enable */
#define RCU_AHB1EN_ENET1RXEN            BIT(2)                                      /*!< ENET1 RX clock enable */
#define RCU_AHB1EN_ENET1PTPEN           BIT(3)                                      /*!< ENET1 PTP clock enable */
#define RCU_AHB1EN_USBHS0EN             BIT(14)                                     /*!< USBHS0 clock enable */
#define RCU_AHB1EN_USBHS0ULPIEN         BIT(15)                                     /*!< USBHS0 ULPI clock enable */
#define RCU_AHB1EN_DMA0EN               BIT(21)                                     /*!< DMA0 clock enable */
#define RCU_AHB1EN_DMA1EN               BIT(22)                                     /*!< DMA1 clock enable */
#define RCU_AHB1EN_DMAMUXEN             BIT(23)                                     /*!< DMAMUX clock enable */
#define RCU_AHB1EN_ENET0EN              BIT(25)                                     /*!< ENET0 clock enable */
#define RCU_AHB1EN_ENET0TXEN            BIT(26)                                     /*!< ENET0 TX clock enable */
#define RCU_AHB1EN_ENET0RXEN            BIT(27)                                     /*!< ENET0 RX clock enable */
#define RCU_AHB1EN_ENET0PTPEN           BIT(28)                                     /*!< ENET0 PTP clock enable */
#define RCU_AHB1EN_USBHS1EN             BIT(29)                                     /*!< USBHS1 clock enable */
#define RCU_AHB1EN_USBHS1ULPIEN         BIT(30)                                     /*!< USBHS1 ULPI clock enable */

/* RCU_AHB2EN */
#define RCU_AHB2EN_DCIEN                BIT(0)                                      /*!< DCI clock enable */
#define RCU_AHB2EN_FACEN                BIT(1)                                      /*!< FAC clock enable */
#define RCU_AHB2EN_SDIO1EN              BIT(2)                                      /*!< SDIO1 clock enable */
#define RCU_AHB2EN_CAUEN                BIT(3)                                      /*!< CAU clock enable */
#define RCU_AHB2EN_HAUEN                BIT(4)                                      /*!< HAU clock enable */
#define RCU_AHB2EN_TRNGEN               BIT(6)                                      /*!< TRNG clock enable */
#define RCU_AHB2EN_TMUEN                BIT(7)                                      /*!< TMU clock enable */
#define RCU_AHB2EN_RAMECCMU1EN          BIT(8)                                      /*!< RAMECCMU1 clock enable */

/* RCU_AHB3EN */
#define RCU_AHB3EN_EXMCEN               BIT(0)                                      /*!< EXMC clock enable */
#define RCU_AHB3EN_IPAEN                BIT(1)                                      /*!< IPA clock enable */
#define RCU_AHB3EN_SDIO0EN              BIT(2)                                      /*!< SDIO0 clock enable */
#define RCU_AHB3EN_MDMAEN               BIT(3)                                      /*!< MDMA clock enable */
#define RCU_AHB3EN_OSPIMEN              BIT(4)                                      /*!< OSPIM clock enable */
#define RCU_AHB3EN_OSPI0EN              BIT(5)                                      /*!< OSPI0 clock enable */
#define RCU_AHB3EN_OSPI1EN              BIT(6)                                      /*!< OSPI1 clock enable */
#define RCU_AHB3EN_RTDEC0EN             BIT(8)                                      /*!< RTDEC0 clock enable */
#define RCU_AHB3EN_RTDEC1EN             BIT(9)                                      /*!< RTDEC1 clock enable */
#define RCU_AHB3EN_RAMECCMU0EN          BIT(10)                                     /*!< RAMECCMU0 clock enable */
#define RCU_AHB3EN_CPUEN                BIT(15)                                     /*!< CPU clock enable */

/* RCU_AHB4EN */
#define RCU_AHB4EN_PAEN                 BIT(0)                                      /*!< GPIO port A enable */
#define RCU_AHB4EN_PBEN                 BIT(1)                                      /*!< GPIO port B enable */
#define RCU_AHB4EN_PCEN                 BIT(2)                                      /*!< GPIO port C enable */
#define RCU_AHB4EN_PDEN                 BIT(3)                                      /*!< GPIO port D enable */
#define RCU_AHB4EN_PEEN                 BIT(4)                                      /*!< GPIO port E enable */
#define RCU_AHB4EN_PFEN                 BIT(5)                                      /*!< GPIO port F enable */
#define RCU_AHB4EN_PGEN                 BIT(6)                                      /*!< GPIO port G enable */
#define RCU_AHB4EN_PHEN                 BIT(7)                                      /*!< GPIO port H enable */
#define RCU_AHB4EN_PJEN                 BIT(8)                                      /*!< GPIO port J enable */
#define RCU_AHB4EN_PKEN                 BIT(9)                                      /*!< GPIO port K enable */
#define RCU_AHB4EN_BKPSRAMEN            BIT(13)                                     /*!< Backup SRAM enable */
#define RCU_AHB4EN_CRCEN                BIT(14)                                     /*!< CRC enable */
#define RCU_AHB4EN_HWSEMEN              BIT(15)                                     /*!< HWSEM enable */

/* RCU_APB1EN */
#define RCU_APB1EN_TIMER1EN             BIT(0)                                      /*!< TIMER1 enable */
#define RCU_APB1EN_TIMER2EN             BIT(1)                                      /*!< TIMER2 enable */
#define RCU_APB1EN_TIMER3EN             BIT(2)                                      /*!< TIMER3 enable */
#define RCU_APB1EN_TIMER4EN             BIT(3)                                      /*!< TIMER4 enable */
#define RCU_APB1EN_TIMER5EN             BIT(4)                                      /*!< TIMER5 enable */
#define RCU_APB1EN_TIMER6EN             BIT(5)                                      /*!< TIMER6 enable */
#define RCU_APB1EN_TIMER22EN            BIT(6)                                      /*!< TIMER22 enable */
#define RCU_APB1EN_TIMER23EN            BIT(7)                                      /*!< TIMER23 enable */
#define RCU_APB1EN_TIMER30EN            BIT(8)                                      /*!< TIMER30 enable */
#define RCU_APB1EN_TIMER31EN            BIT(9)                                      /*!< TIMER31 enable */
#define RCU_APB1EN_TIMER50EN            BIT(10)                                     /*!< TIMER50 enable */
#define RCU_APB1EN_TIMER51EN            BIT(11)                                     /*!< TIMER51 enable */
#define RCU_APB1EN_RSPDIFEN             BIT(13)                                     /*!< RSPDIF enable */
#define RCU_APB1EN_SPI1EN               BIT(14)                                     /*!< SPI1 enable */
#define RCU_APB1EN_SPI2EN               BIT(15)                                     /*!< SPI2 enable */
#define RCU_APB1EN_MDIOEN               BIT(16)                                     /*!< MDIO enable */
#define RCU_APB1EN_USART1EN             BIT(17)                                     /*!< USART1 enable */
#define RCU_APB1EN_USART2EN             BIT(18)                                     /*!< USART2 enable */
#define RCU_APB1EN_UART3EN              BIT(19)                                     /*!< UART3 enable */
#define RCU_APB1EN_UART4EN              BIT(20)                                     /*!< UART4 enable */
#define RCU_APB1EN_I2C0EN               BIT(21)                                     /*!< I2C0 enable */
#define RCU_APB1EN_I2C1EN               BIT(22)                                     /*!< I2C1 enable */
#define RCU_APB1EN_I2C2EN               BIT(23)                                     /*!< I2C2 enable */
#define RCU_APB1EN_I2C3EN               BIT(24)                                     /*!< I2C3 enable */
#define RCU_APB1EN_CTCEN                BIT(27)                                     /*!< CTC enable */
#define RCU_APB1EN_DACHOLDEN            BIT(28)                                     /*!< DAC hold clock enable */
#define RCU_APB1EN_DACEN                BIT(29)                                     /*!< DAC enable */
#define RCU_APB1EN_UART6EN              BIT(30)                                     /*!< UART6 enable */
#define RCU_APB1EN_UART7EN              BIT(31)                                     /*!< UART7 enable */

/* RCU_APB2EN */
#define RCU_APB2EN_TIMER0EN             BIT(0)                                      /*!< TIMER0 enable */
#define RCU_APB2EN_TIMER7EN             BIT(1)                                      /*!< TIMER7 enable */
#define RCU_APB2EN_USART0EN             BIT(4)                                      /*!< USART0 enable */
#define RCU_APB2EN_USART5EN             BIT(5)                                      /*!< USART5 enable */
#define RCU_APB2EN_ADC0EN               BIT(8)                                      /*!< ADC0 enable */
#define RCU_APB2EN_ADC1EN               BIT(9)                                      /*!< ADC1 enable */
#define RCU_APB2EN_ADC2EN               BIT(10)                                     /*!< ADC2 enable */
#define RCU_APB2EN_SPI0EN               BIT(12)                                     /*!< SPI0 enable */
#define RCU_APB2EN_SPI3EN               BIT(13)                                     /*!< SPI3 enable */
#define RCU_APB2EN_TIMER14EN            BIT(16)                                     /*!< TIMER14 enable */
#define RCU_APB2EN_TIMER15EN            BIT(17)                                     /*!< TIMER15 enable */
#define RCU_APB2EN_TIMER16EN            BIT(18)                                     /*!< TIMER15 enable */
#define RCU_APB2EN_HPDFEN               BIT(19)                                     /*!< HPDF enable */
#define RCU_APB2EN_SPI4EN               BIT(20)                                     /*!< SPI4 enable */
#define RCU_APB2EN_SPI5EN               BIT(21)                                     /*!< SPI5 enable */
#define RCU_APB2EN_SAI0EN               BIT(22)                                     /*!< SAI0 enable */
#define RCU_APB2EN_SAI1EN               BIT(23)                                     /*!< SAI1 enable */
#define RCU_APB2EN_SAI2EN               BIT(24)                                     /*!< SAI2 enable */
#define RCU_APB2EN_TIMER40EN            BIT(25)                                     /*!< TIMER40 enable */
#define RCU_APB2EN_TIMER41EN            BIT(26)                                     /*!< TIMER41 enable */
#define RCU_APB2EN_TIMER42EN            BIT(27)                                     /*!< TIMER42 enable */
#define RCU_APB2EN_TIMER43EN            BIT(28)                                     /*!< TIMER43 enable */
#define RCU_APB2EN_TIMER44EN            BIT(29)                                     /*!< TIMER44 enable */
#define RCU_APB2EN_EDOUTEN              BIT(30)                                     /*!< EDOUT enable */
#define RCU_APB2EN_TRGSELEN             BIT(31)                                     /*!< TRGSEL enable */

/* RCU_APB3EN */
#define RCU_APB3EN_TLIEN                BIT(0)                                      /*!< TLI enable */
#define RCU_APB3EN_WWDGTEN              BIT(1)                                      /*!< WWDGT enable */

/* RCU_APB4EN */
#define RCU_APB4EN_SYSCFGEN             BIT(0)                                      /*!< SYSCFG enable */
#define RCU_APB4EN_CMPEN                BIT(1)                                      /*!< CMP enable */
#define RCU_APB4EN_VREFEN               BIT(2)                                      /*!< VREF enable */
#define RCU_APB4EN_LPDTSEN              BIT(3)                                      /*!< LPDTS enable */
#define RCU_APB4EN_PMUEN                BIT(4)                                      /*!< PMU enable */

/* RCU_AHB1SPEN */
#define RCU_AHB1SPEN_ENET1SPEN          BIT(0)                                      /*!< ENET1 clock enable when sleep mode*/
#define RCU_AHB1SPEN_ENET1TXSPEN        BIT(1)                                      /*!< ENET1 TX clock enable when sleep mode*/
#define RCU_AHB1SPEN_ENET1RXSPEN        BIT(2)                                      /*!< ENET1 RX clock enable when sleep mode*/
#define RCU_AHB1SPEN_ENET1PTPSPEN       BIT(3)                                      /*!< ENET1 PTP clock enable when sleep mode */
#define RCU_AHB1SPEN_USBHS0SPEN         BIT(14)                                     /*!< USBHS0 clock enable when sleep mode */
#define RCU_AHB1SPEN_USBHS0ULPISPEN     BIT(15)                                     /*!< USBHS0ULPI clock enable when sleep mode */
#define RCU_AHB1SPEN_SRAM0SPEN          BIT(16)                                     /*!< SRAM0 clock enable when sleep mode */
#define RCU_AHB1SPEN_SRAM1SPEN          BIT(17)                                     /*!< SRAM1 clock enable when sleep mode */
#define RCU_AHB1SPEN_DMA0SPEN           BIT(21)                                     /*!< DMA0 clock enable when sleep mode*/
#define RCU_AHB1SPEN_DMA1SPEN           BIT(22)                                     /*!< DMA1 clock enable when sleep mode*/
#define RCU_AHB1SPEN_DMAMUXSPEN         BIT(23)                                     /*!< DMAMUX clock enable when sleep mode*/
#define RCU_AHB1SPEN_ENET0SPEN          BIT(25)                                     /*!< ENET0 clock enable when sleep mode*/
#define RCU_AHB1SPEN_ENET0TXSPEN        BIT(26)                                     /*!< ENET0 TX clock enable when sleep mode*/
#define RCU_AHB1SPEN_ENET0RXSPEN        BIT(27)                                     /*!< ENET0 RX clock enable when sleep mode*/
#define RCU_AHB1SPEN_ENET0PTPSPEN       BIT(28)                                     /*!< ENET0 PTP clock enable when sleep mode*/
#define RCU_AHB1SPEN_USBHS1SPEN         BIT(29)                                     /*!< USBHS1 clock enable when sleep mode*/
#define RCU_AHB1SPEN_USBHS1ULPISPEN     BIT(30)                                     /*!< USBHS1 ULPI clock enable when sleep mode*/

/* RCU_AHB2SPEN */
#define RCU_AHB2SPEN_DCISPEN            BIT(0)                                      /*!< DCI clock enable when sleep mode*/
#define RCU_AHB2SPEN_FACSPEN            BIT(1)                                      /*!< FAC clock enable when sleep mode*/
#define RCU_AHB2SPEN_SDIO1SPEN          BIT(2)                                      /*!< SDIO1 clock enable when sleep mode*/
#define RCU_AHB2SPEN_CAUSPEN            BIT(3)                                      /*!< CAU clock enable when sleep mode*/
#define RCU_AHB2SPEN_HAUSPEN            BIT(4)                                      /*!< HAU clock enable when sleep mode*/
#define RCU_AHB2SPEN_TRNGSPEN           BIT(6)                                      /*!< TRNG clock enable when sleep mode*/
#define RCU_AHB2SPEN_TMUSPEN            BIT(7)                                      /*!< TMU clock enable when sleep mode*/
#define RCU_AHB2SPEN_RAMECCMU1SPEN      BIT(8)                                      /*!< RAMECCMU1 clock enable when sleep mode*/

/* RCU_AHB3SPEN */
#define RCU_AHB3SPEN_EXMCSPEN           BIT(0)                                      /*!< EXMC clock enable when sleep mode*/
#define RCU_AHB3SPEN_IPASPEN            BIT(1)                                      /*!< IPA clock enable when sleep mode*/
#define RCU_AHB3SPEN_SDIO0SPEN          BIT(2)                                      /*!< SDIO0 clock enable when sleep mode*/
#define RCU_AHB3SPEN_MDMASPEN           BIT(3)                                      /*!< MDMA clock enable when sleep mode*/
#define RCU_AHB3SPEN_OSPIMSPEN          BIT(4)                                      /*!< OSPIM clock enable when sleep mode*/
#define RCU_AHB3SPEN_OSPI0SPEN          BIT(5)                                      /*!< OSPI0 clock enable when sleep mode*/
#define RCU_AHB3SPEN_OSPI1SPEN          BIT(6)                                      /*!< OSPI1 clock enable when sleep mode*/
#define RCU_AHB3SPEN_RTDEC0SPEN         BIT(8)                                      /*!< RTDEC0 clock enable when sleep mode*/
#define RCU_AHB3SPEN_RTDEC1SPEN         BIT(9)                                      /*!< RTDEC1 clock enable when sleep mode*/
#define RCU_AHB2SPEN_RAMECCMU0SPEN      BIT(10)                                     /*!< RAMECCMU0 clock enable when sleep mode*/
#define RCU_AHB3SPEN_AXISRAMSPEN        BIT(14)                                     /*!< AXISRAM clock enable when sleep mode*/
#define RCU_AHB3SPEN_FMCSPEN            BIT(15)                                     /*!< FMC clock enable when sleep mode*/

/* RCU_AHB4SPEN */
#define RCU_AHB4SPEN_PASPEN             BIT(0)                                      /*!< GPIO port A clock enable when sleep mode*/
#define RCU_AHB4SPEN_PBSPEN             BIT(1)                                      /*!< GPIO port B clock enable when sleep mode*/
#define RCU_AHB4SPEN_PCSPEN             BIT(2)                                      /*!< GPIO port C clock enable when sleep mode*/
#define RCU_AHB4SPEN_PDSPEN             BIT(3)                                      /*!< GPIO port D clock enable when sleep mode*/
#define RCU_AHB4SPEN_PESPEN             BIT(4)                                      /*!< GPIO port E clock enable when sleep mode*/
#define RCU_AHB4SPEN_PFSPEN             BIT(5)                                      /*!< GPIO port F clock enable when sleep mode*/
#define RCU_AHB4SPEN_PGSPEN             BIT(6)                                      /*!< GPIO port G clock enable when sleep mode*/
#define RCU_AHB4SPEN_PHSPEN             BIT(7)                                      /*!< GPIO port H clock enable when sleep mode*/
#define RCU_AHB4SPEN_PJSPEN             BIT(8)                                      /*!< GPIO port J clock enable when sleep mode*/
#define RCU_AHB4SPEN_PKSPEN             BIT(9)                                      /*!< GPIO port K clock enable when sleep mode*/
#define RCU_AHB4SPEN_BKPSRAMSPEN        BIT(13)                                     /*!< BKPSRAMEN clock enable when sleep mode*/
#define RCU_AHB4SPEN_CRCSPEN            BIT(14)                                     /*!< CRC clock enable when sleep mode*/

/* RCU_APB1SPEN */
#define RCU_APB1SPEN_TIMER1SPEN         BIT(0)                                      /*!< TIMER1 clock enable when sleep mode*/
#define RCU_APB1SPEN_TIMER2SPEN         BIT(1)                                      /*!< TIMER2 clock enable when sleep mode*/
#define RCU_APB1SPEN_TIMER3SPEN         BIT(2)                                      /*!< TIMER3 clock enable when sleep mode*/
#define RCU_APB1SPEN_TIMER4SPEN         BIT(3)                                      /*!< TIMER4 clock enable when sleep mode*/
#define RCU_APB1SPEN_TIMER5SPEN         BIT(4)                                      /*!< TIMER5 clock enable when sleep mode*/
#define RCU_APB1SPEN_TIMER6SPEN         BIT(5)                                      /*!< TIMER6 clock enable when sleep mode*/
#define RCU_APB1SPEN_TIMER22SPEN        BIT(6)                                      /*!< TIMER22 clock enable when sleep mode*/
#define RCU_APB1SPEN_TIMER23SPEN        BIT(7)                                      /*!< TIMER23 clock enable when sleep mode*/
#define RCU_APB1SPEN_TIMER30SPEN        BIT(8)                                      /*!< TIMER30 clock enable when sleep mode*/
#define RCU_APB1SPEN_TIMER31SPEN        BIT(9)                                      /*!< TIMER31 clock enable when sleep mode*/
#define RCU_APB1SPEN_TIMER50SPEN        BIT(10)                                     /*!< TIMER50 clock enable when sleep mode*/
#define RCU_APB1SPEN_TIMER51SPEN        BIT(11)                                     /*!< TIMER51 clock enable when sleep mode*/
#define RCU_APB1SPEN_RSPDIFSPEN         BIT(13)                                     /*!< RSPDIF clock enable when sleep mode*/
#define RCU_APB1SPEN_SPI1SPEN           BIT(14)                                     /*!< SPI1 clock enable when sleep mode*/
#define RCU_APB1SPEN_SPI2SPEN           BIT(15)                                     /*!< SPI2 clock enable when sleep mode*/
#define RCU_APB1SPEN_MDIOSPEN           BIT(16)                                     /*!< MDIO clock enable when sleep mode*/
#define RCU_APB1SPEN_USART1SPEN         BIT(17)                                     /*!< USART1 clock enable when sleep mode*/
#define RCU_APB1SPEN_USART2SPEN         BIT(18)                                     /*!< USART2 clock enable when sleep mode*/
#define RCU_APB1SPEN_UART3SPEN          BIT(19)                                     /*!< UART3 clock enable when sleep mode*/
#define RCU_APB1SPEN_UART4SPEN          BIT(20)                                     /*!< UART4 clock enable when sleep mode*/
#define RCU_APB1SPEN_I2C0SPEN           BIT(21)                                     /*!< I2C0 clock enable when sleep mode*/
#define RCU_APB1SPEN_I2C1SPEN           BIT(22)                                     /*!< I2C1 clock enable when sleep mode*/
#define RCU_APB1SPEN_I2C2SPEN           BIT(23)                                     /*!< I2C2 clock enable when sleep mode*/
#define RCU_APB1SPEN_I2C3SPEN           BIT(24)                                     /*!< I2C3 clock enable when sleep mode*/
#define RCU_APB1SPEN_CTCSPEN            BIT(27)                                     /*!< CTC clock enable when sleep mode*/
#define RCU_APB1SPEN_DACHOLDSPEN        BIT(28)                                     /*!< DAC hold clock enable when sleep mode*/
#define RCU_APB1SPEN_DACSPEN            BIT(29)                                     /*!< DAC clock enable when sleep mode*/
#define RCU_APB1SPEN_UART6SPEN          BIT(30)                                     /*!< UART6 clock enable when sleep mode*/
#define RCU_APB1SPEN_UART7SPEN          BIT(31)                                     /*!< UART7 clock enable when sleep mode*/

/* RCU_APB2SPEN */
#define RCU_APB2SPEN_TIMER0SPEN         BIT(0)                                      /*!< TIMER0 clock enable when sleep mode*/
#define RCU_APB2SPEN_TIMER7SPEN         BIT(1)                                      /*!< TIMER7 clock enable when sleep mode*/
#define RCU_APB2SPEN_USART0SPEN         BIT(4)                                      /*!< USART0 clock enable when sleep mode*/
#define RCU_APB2SPEN_USART5SPEN         BIT(5)                                      /*!< USART5 clock enable when sleep mode*/
#define RCU_APB2SPEN_ADC0SPEN           BIT(8)                                      /*!< ADC0 clock enable when sleep mode*/
#define RCU_APB2SPEN_ADC1SPEN           BIT(9)                                      /*!< ADC1 clock enable when sleep mode*/
#define RCU_APB2SPEN_ADC2SPEN           BIT(10)                                     /*!< ADC2 clock enable when sleep mode*/
#define RCU_APB2SPEN_SPI0SPEN           BIT(12)                                     /*!< SPI0 clock enable when sleep mode*/
#define RCU_APB2SPEN_SPI3SPEN           BIT(13)                                     /*!< SPI3 clock enable when sleep mode*/
#define RCU_APB2SPEN_TIMER14SPEN        BIT(16)                                     /*!< TIMER14 clock enable when sleep mode*/
#define RCU_APB2SPEN_TIMER15SPEN        BIT(17)                                     /*!< TIMER15 clock enable when sleep mode*/
#define RCU_APB2SPEN_TIMER16SPEN        BIT(18)                                     /*!< TIMER16 clock enable when sleep mode*/
#define RCU_APB2SPEN_HPDFSPEN           BIT(19)                                     /*!< HPDF clock enable when sleep mode*/
#define RCU_APB2SPEN_SPI4SPEN           BIT(20)                                     /*!< SPI4 clock enable when sleep mode*/
#define RCU_APB2SPEN_SPI5SPEN           BIT(21)                                     /*!< SPI5 clock enable when sleep mode*/
#define RCU_APB2SPEN_SAI0SPEN           BIT(22)                                     /*!< SAI0 clock enable when sleep mode*/
#define RCU_APB2SPEN_SAI1SPEN           BIT(23)                                     /*!< SAI1 clock enable when sleep mode*/
#define RCU_APB2SPEN_SAI2SPEN           BIT(24)                                     /*!< SAI2 clock enable when sleep mode*/
#define RCU_APB2SPEN_TIMER40SPEN        BIT(25)                                     /*!< TIMER40 clock enable when sleep mode*/
#define RCU_APB2SPEN_TIMER41SPEN        BIT(26)                                     /*!< TIMER41 clock enable when sleep mode*/
#define RCU_APB2SPEN_TIMER42SPEN        BIT(27)                                     /*!< TIMER42 clock enable when sleep mode*/
#define RCU_APB2SPEN_TIMER43SPEN        BIT(28)                                     /*!< TIMER43 clock enable when sleep mode*/
#define RCU_APB2SPEN_TIMER44SPEN        BIT(29)                                     /*!< TIMER44 clock enable when sleep mode*/
#define RCU_APB2SPEN_EDOUTSPEN          BIT(30)                                     /*!< EDOUT clock enable when sleep mode*/
#define RCU_APB2SPEN_TRIGSELSPEN        BIT(31)                                     /*!< TRIGSEL clock enable when sleep mode*/

/* RCU_APB3SPEN */
#define RCU_APB3SPEN_TLISPEN            BIT(0)                                      /*!< TLI clock enable when sleep mode*/
#define RCU_APB3SPEN_WWDGTSPEN          BIT(1)                                      /*!< WWDGT clock enable when sleep mode*/

/* RCU_APB4SPEN */
#define RCU_APB4SPEN_SYSCFGSPEN         BIT(0)                                      /*!< SYSCFG clock enable when sleep mode*/
#define RCU_APB4SPEN_CMPSPEN            BIT(1)                                      /*!< CMP clock enable when sleep mode*/
#define RCU_APB4SPEN_VREFSPEN           BIT(2)                                      /*!< VREF clock enable when sleep mode*/
#define RCU_APB4SPEN_LPDTSSPEN          BIT(3)                                      /*!< LPDTS clock enable when sleep mode*/
#define RCU_APB4SPEN_PMUSPEN            BIT(4)                                      /*!< PMU clock enable when sleep mode*/

/* RCU_BDCTL */
#define RCU_BDCTL_LXTALEN               BIT(0)                                      /*!< LXTAL enable */
#define RCU_BDCTL_LXTALSTB              BIT(1)                                      /*!< low speed crystal oscillator stabilization flag */
#define RCU_BDCTL_LXTALBPS              BIT(2)                                      /*!< LXTAL bypass mode enable */
#define RCU_BDCTL_LXTALDRI              BITS(3,4)                                   /*!< LXTAL drive capability */
#define RCU_BDCTL_LCKMEN                BIT(5)                                      /*!< LXTAL clock monitor enable */
#define RCU_BDCTL_LCKMD                 BIT(6)                                      /*!< LXTAL clock failure detection flag */
#define RCU_BDCTL_RTCSRC                BITS(8,9)                                   /*!< RTC clock entry selection */
#define RCU_BDCTL_RTCEN                 BIT(15)                                     /*!< RTC clock enable */
#define RCU_BDCTL_BKPRST                BIT(16)                                     /*!< backup domain reset */

/* RCU_RSTSCK */
#define RCU_RSTSCK_IRC32KEN             BIT(0)                                      /*!< IRC32K enable */
#define RCU_RSTSCK_IRC32KSTB            BIT(1)                                      /*!< IRC32K stabilization flag */
#define RCU_RSTSCK_RSTFC                BIT(24)                                     /*!< reset flag clear */
#define RCU_RSTSCK_BORRSTF              BIT(25)                                     /*!< BOR reset flag */
#define RCU_RSTSCK_EPRSTF               BIT(26)                                     /*!< external pin reset flag */
#define RCU_RSTSCK_PORRSTF              BIT(27)                                     /*!< power reset flag */
#define RCU_RSTSCK_SWRSTF               BIT(28)                                     /*!< software reset flag */
#define RCU_RSTSCK_FWDGTRSTF            BIT(29)                                     /*!< free watchdog timer reset flag */
#define RCU_RSTSCK_WWDGTRSTF            BIT(30)                                     /*!< window watchdog timer reset flag */
#define RCU_RSTSCK_LPRSTF               BIT(31)                                     /*!< low-power reset flag */

/* RCU_PLLADDCTL */
#define RCU_PLLADDCTL_PLL0Q             BITS(0,6)                                   /*!< the PLL0Q output frequency division factor from PLL0 VCO clock */
#define RCU_PLLADDCTL_PLL1Q             BITS(8,14)                                  /*!< the PLL1Q output frequency division factor from PLL1 VCO clock */
#define RCU_PLLADDCTL_PLL2Q             BITS(16,22)                                 /*!< the PLL2Q output frequency division factor from PLL2 VCO clock */
#define RCU_PLLADDCTL_PLL0QEN           BIT(23)                                     /*!< PLL0Q divider output enable */
#define RCU_PLLADDCTL_PLL0REN           BIT(24)                                     /*!< PLL0R divider output enable */
#define RCU_PLLADDCTL_PLL0PEN           BIT(25)                                     /*!< PLL0P divider output enable */
#define RCU_PLLADDCTL_PLL1QEN           BIT(26)                                     /*!< PLL1Q divider output enable */
#define RCU_PLLADDCTL_PLL1REN           BIT(27)                                     /*!< PLL1R divider output enable */
#define RCU_PLLADDCTL_PLL1PEN           BIT(28)                                     /*!< PLL1P divider output enable */
#define RCU_PLLADDCTL_PLL2QEN           BIT(29)                                     /*!< PLL2Q divider output enable */
#define RCU_PLLADDCTL_PLL2REN           BIT(30)                                     /*!< PLL2R divider output enable */
#define RCU_PLLADDCTL_PLL2PEN           BIT(31)                                     /*!< PLL2P divider output enable */

/* RCU_PLL1 */
#define RCU_PLL1_PLL1PSC                BITS(0,5)                                   /*!< the PLL1 VCO source clock prescaler */
#define RCU_PLL1_PLL1N                  BITS(6,14)                                  /*!< the PLL1 VCO clock multi factor */
#define RCU_PLL1_PLL1P                  BITS(16,22)                                 /*!< the PLL1P output frequency division factor from PLL1 VCO clock */
#define RCU_PLL1_PLL1R                  BITS(24,30)                                 /*!< the PLL1R output frequency division factor from PLL1 VCO clock */

/* RCU_PLL2 */
#define RCU_PLL2_PLL2PSC                BITS(0,5)                                   /*!< the PLL2 VCO source clock prescaler */
#define RCU_PLL2_PLL2N                  BITS(6,14)                                  /*!< the PLL2 VCO clock multi factor */
#define RCU_PLL2_PLL2P                  BITS(16,22)                                 /*!< the PLL2P output frequency division factor from PLL2 VCO clock */
#define RCU_PLL2_PLL2R                  BITS(24,30)                                 /*!< the PLL2R output frequency division factor from PLL2 VCO clock */

/* RCU_CFG1 */
#define RCU_CFG1_USART0SEL              BITS(0,1)                                   /*!< USART0 clock source selection */
#define RCU_CFG1_RSPDIFSEL              BITS(4,5)                                   /*!< RSPDIF clock source selection */
#define RCU_CFG1_CAN0SEL                BITS(8,9)                                   /*!< CAN0 clock source selection */
#define RCU_CFG1_CAN1SEL                BITS(10,11)                                 /*!< CAN1 clock source selection */
#define RCU_CFG1_CAN2SEL                BITS(12,13)                                 /*!< CAN2 clock source selection */
#define RCU_CFG1_PERSEL                 BITS(14,15)                                 /*!< CK_PER clock source selection */
#define RCU_CFG1_PLL2RDIV               BITS(16,17)                                 /*!< the divider factor from PLL2R clock */
#define RCU_CFG1_USART1SEL              BITS(18,19)                                 /*!< USART1 clock source selection */
#define RCU_CFG1_USART2SEL              BITS(20,21)                                 /*!< USART2 clock source selection */
#define RCU_CFG1_USART5SEL              BITS(22,23)                                 /*!< USART5 clock source selection */
#define RCU_CFG1_TIMERSEL               BIT(24)                                     /*!< TIMER clock selection */
#define RCU_CFG1_HPDFSEL                BIT(31)                                     /*!< HPDF clock source selection */

/* RCU_CFG2 */
#define RCU_CFG2_CKOUT0DIV              BITS(0,3)                                   /*!< The CK_OUT0 divider which the CK_OUT0 frequency can be reduced */
#define RCU_CFG2_CKOUT0SEL              BITS(4,6)                                   /*!< CKOUT0 clock source selection */
#define RCU_CFG2_CKOUT1DIV              BITS(8,11)                                  /*!< The CK_OUT1 divider which the CK_OUT1 frequency can be reduced */
#define RCU_CFG2_CKOUT1SEL              BITS(12,14)                                 /*!< CKOUT1 clock source selection */
#define RCU_CFG2_SAI0SEL                BITS(16,18)                                 /*!< SAI0 clock source selection */
#define RCU_CFG2_SAI1SEL                BITS(20,22)                                 /*!< SAI1 clock source selection */
#define RCU_CFG2_SAI2B0SEL              BITS(24,26)                                 /*!< SAI2 Block 0 clock source selection */
#define RCU_CFG2_SAI2B1SEL              BITS(28,30)                                 /*!< SAI2 Block 1 clock source selection */

/* RCU_CFG3 */
#define RCU_CFG3_I2C1SEL                BITS(0,1)                                   /*!< I2C1 clock source selection */
#define RCU_CFG3_I2C2SEL                BITS(2,3)                                   /*!< I2C2 clock source selection */
#define RCU_CFG3_I2C3SEL                BITS(4,5)                                   /*!< I2C3 clock source selection */
#define RCU_CFG3_SDIO1SEL               BIT(12)                                     /*!< SDIO1 function clock source selection */
#define RCU_CFG3_DSPWUSSEL              BIT(24)                                     /*!< deep-sleep wakeup system clock source selection */
#define RCU_CFG3_ADC01SEL               BITS(26,27)                                 /*!< ADC0 and ADC1 clock source selection */
#define RCU_CFG3_ADC2SEL                BITS(28,29)                                 /*!< ADC2 clock source selection */

/* RCU_PLLALL */
#define RCU_PLLALL_PLL0RNG              BITS(0,1)                                   /*!< PLL0 input clock range */
#define RCU_PLLALL_PLL0VCOSEL           BIT(2)                                      /*!< PLL0 VCO selection */
#define RCU_PLLALL_PLL1RNG              BITS(4,5)                                   /*!< PLL1 input clock range */
#define RCU_PLLALL_PLL1VCOSEL           BIT(6)                                      /*!< PLL1 VCO selection */
#define RCU_PLLALL_PLL2RNG              BITS(8,9)                                   /*!< PLL2 input clock range */
#define RCU_PLLALL_PLL2VCOSEL           BIT(10)                                     /*!< PLL2 VCO selection */
#define RCU_PLLALL_PLLSEL               BITS(16,17)                                 /*!< PLLs clock source selection */

/* RCU_PLL0FRA */
#define RCU_PLL0FRA_PLL0FRAN            BITS(0,12)                                  /*!< fractional part of the multiplication factor for PLL0 VCO */
#define RCU_PLL0FRA_PLL0FRAEN           BIT(15)                                     /*!< PLL0 fractional latch enable */

/* RCU_PLL1FRA */
#define RCU_PLL1FRA_PLL1FRAN            BITS(0,12)                                  /*!< fractional part of the multiplication factor for PLL1 VCO */
#define RCU_PLL1FRA_PLL1FRAEN           BIT(15)                                     /*!< PLL1 fractional latch enable */

/* RCU_PLL2FRA */
#define RCU_PLL2FRA_PLL2FRAN            BITS(0,12)                                  /*!< fractional part of the multiplication factor for PLL2 VCO */
#define RCU_PLL2FRA_PLL2FRAEN           BIT(15)                                     /*!< PLL2 fractional latch enable */

/* RCU_ADDCTL0 */
#define RCU_ADDCTL0_CK48MSEL            BIT(0)                                      /*!< 48MHz clock selection */
#define RCU_ADDCTL0_PLL48MSEL           BIT(1)                                      /*!< PLL48M clock selection */
#define RCU_ADDCTL0_IRC48MEN            BIT(16)                                     /*!< internal 48MHz RC oscillator enable */
#define RCU_ADDCTL0_IRC48MSTB           BIT(17)                                     /*!< internal 48MHz RC oscillator clock stabilization flag */
#define RCU_ADDCTL0_IRC48MCALB          BITS(24,31)                                 /*!< internal 48MHz RC oscillator calibration value register */

/* RCU_ADDCTL1 */
#define RCU_ADDCTL1_LPIRC4MEN           BIT(0)                                      /*!< LPIRC4M clock enable */
#define RCU_ADDCTL1_LPIRC4MSTB          BIT(1)                                      /*!< LPIRC4M clock stabilization flag */
#define RCU_ADDCTL1_LPIRC4MTRIM         BITS(2,7)                                   /*!< LPIRC4M clock trim adjust value */
#define RCU_ADDCTL1_LPIRC4MCAL          BITS(8,15)                                  /*!< LPIRC4M clock calibration value */
#define RCU_ADDCTL1_IRC64MDIV           BITS(16,17)                                 /*!< IRC64M clock divider */
#define RCU_ADDCTL1_LPIRC4MDSPEN        BIT(20)                                     /*!< LPIRC4M clock enable in deepsleep mode */
#define RCU_ADDCTL1_PLLUSBHS0EN         BIT(28)                                     /*!< PLLUSBHS0 clock enable */
#define RCU_ADDCTL1_PLLUSBHS0STB        BIT(29)                                     /*!< PLLUSBHS0 clock stabilization flag */
#define RCU_ADDCTL1_PLLUSBHS1EN         BIT(30)                                     /*!< PLLUSBHS1 clock enable */
#define RCU_ADDCTL1_PLLUSBHS1STB        BIT(31)                                     /*!< PLLUSBHS1 clock stabilization flag */

/* RCU_ADDINT */
#define RCU_ADDINT_PLLUSBHS0STBIF       BIT(4)                                      /*!< Internal PLL of USBHS0 stabilization interrupt flag */
#define RCU_ADDINT_PLLUSBHS1STBIF       BIT(5)                                      /*!< Internal PLL of USBHS1 stabilization interrupt flag */
#define RCU_ADDINT_IRC48MSTBIF          BIT(6)                                      /*!< IRC48M stabilization interrupt flag */
#define RCU_ADDINT_PLLUSBHS0STBIE       BIT(12)                                     /*!< Internal PLL of USBHS0 stabilization interrupt enable */
#define RCU_ADDINT_PLLUSBHS1STBIE       BIT(13)                                     /*!< Internal PLL of USBHS1 stabilization interrupt enable */
#define RCU_ADDINT_IRC48MSTBIE          BIT(14)                                     /*!< Internal 48 MHz RC oscillator stabilization interrupt enable */
#define RCU_ADDINT_PLLUSBHS0STBIC       BIT(20)                                     /*!< Internal PLL of USBHS0 stabilization interrupt clear */
#define RCU_ADDINT_PLLUSBHS1STBIC       BIT(21)                                     /*!< Internal PLL of USBHS1 stabilization interrupt clear */
#define RCU_ADDINT_IRC48MSTBIC          BIT(22)                                     /*!< Internal 48 MHz RC oscillator stabilization interrupt clear */

/* RCU_CFG4 */
#define RCU_CFG4_SDIO0SEL               BIT(0)                                      /*!< SDIO0 clock source selection */
#define RCU_CFG4_EXMCSEL                BITS(8,9)                                   /*!< EXMC clock surce selection */

/* RCU_USBCLKCTL*/
#define RCU_USBCLKCTL_USBHS0SEL         BIT(1)                                      /*!< USBHS0 clock selection */
#define RCU_USBCLKCTL_PLLUSBHS0PRESEL   BIT(3)                                      /*!< PLLUSBHS0 clock source selection */
#define RCU_USBCLKCTL_USBHS0SWEN        BIT(4)                                      /*!< USBHS0 clock source selection enable */
#define RCU_USBCLKCTL_USBHS048MSEL      BITS(5,6)                                   /*!< USBHS0 48M clock source selection */
#define RCU_USBCLKCTL_USBHS1SEL         BIT(9)                                      /*!< USBHS1 clock selection */
#define RCU_USBCLKCTL_PLLUSBHS1PRESEL   BIT(11)                                     /*!< PLLUSBHS1 clock source selection */
#define RCU_USBCLKCTL_USBHS1SWEN        BIT(12)                                     /*!< USBHS1 clock source selection enable */
#define RCU_USBCLKCTL_USBHS148MSEL      BITS(13,14)                                 /*!< USBHS1 48M clock source selection */
#define RCU_USBCLKCTL_USBHS0PSC         BITS(16,18)                                 /*!< USBHS0 clock prescaler selection */
#define RCU_USBCLKCTL_USBHS1PSC         BITS(19,21)                                 /*!< USBHS1 clock prescaler selection */

/* RCU_PLLUSBCFG*/
#define RCU_PLLUSBCFG_PLLUSBHS0PREDV    BITS(0,3)                                   /*!< the PLLUSBHS0PREDV clock prescaler */
#define RCU_PLLUSBCFG_USBHS0DV          BITS(4,6)                                   /*!< USBHS0 clock divider */
#define RCU_PLLUSBCFG_PLLUSBHS0MF       BITS(8,14)                                  /*!< the PLLUSBHS0 clock multiplication factor */
#define RCU_PLLUSBCFG_PLLUSBHS1PREDV    BITS(16,19)                                 /*!< the PLLUSBHS1PREDV clock prescaler */
#define RCU_PLLUSBCFG_USBHS1DV          BITS(20,22)                                 /*!< USBHS1 clock divider */
#define RCU_PLLUSBCFG_PLLUSBHS1MF       BITS(24,30)                                 /*!< the PLLUSBHS1 clock multiplication factor */

/* RCU_ADDAPB2RST */
#define RCU_ADDAPB2RST_CAN0RST          BIT(0)                                      /*!< CAN0 reset */
#define RCU_ADDAPB2RST_CAN1RST          BIT(1)                                      /*!< CAN1 reset */
#define RCU_ADDAPB2RST_CAN2RST          BIT(2)                                      /*!< CAN2 reset */

/* RCU_ADDAPB2EN */
#define RCU_ADDAPB2EN_CAN0EN            BIT(0)                                      /*!< CAN0 clock enable */
#define RCU_ADDAPB2EN_CAN1EN            BIT(1)                                      /*!< CAN1 clock enable */
#define RCU_ADDAPB2EN_CAN2EN            BIT(2)                                      /*!< CAN2 clock enable */

/* RCU_ADDAPB2SPEN */
#define RCU_ADDAPB2SPEN_CAN0SPEN        BIT(0)                                      /*!< CAN0 clock enable when sleep mode*/
#define RCU_ADDAPB2SPEN_CAN1SPEN        BIT(1)                                      /*!< CAN1 clock enable when sleep mode*/
#define RCU_ADDAPB2SPEN_CAN2SPEN        BIT(2)                                      /*!< CAN2 clock enable when sleep mode*/

/* RCU_CFG5 */
#define RCU_CFG5_SPI0SEL                BITS(0,2)                                   /*!< SPI0 and I2S0 clock source selection */
#define RCU_CFG5_SPI1SEL                BITS(4,6)                                   /*!< SPI1 and I2S1 clock source selection */
#define RCU_CFG5_SPI2SEL                BITS(8,10)                                  /*!< SPI2 and I2S2 clock source selection */
#define RCU_CFG5_SPI3SEL                BITS(12,14)                                 /*!< SPI3 clock source selection */
#define RCU_CFG5_SPI4SEL                BITS(16,18)                                 /*!< SPI4 clock source selection */
#define RCU_CFG5_SPI5SEL                BITS(20,22)                                 /*!< SPI5 and I2S5 clock source selection */

/* constants definitions */
/* define the peripheral clock enable bit position and its register index offset */
#define RCU_REGIDX_BIT(regidx, bitpos)  (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define RCU_REG_VAL(periph)             (REG32(RCU + ((uint32_t)(periph) >> 6)))
#define RCU_BIT_POS(val)                ((uint32_t)(val) & 0x0000001FU)

/* register offset */
/* peripherals enable */
#define AHB1EN_REG_OFFSET               ((uint32_t)0x00000030U)                     /*!< AHB1 enable register offset */
#define AHB2EN_REG_OFFSET               ((uint32_t)0x00000034U)                     /*!< AHB2 enable register offset */
#define AHB3EN_REG_OFFSET               ((uint32_t)0x00000038U)                     /*!< AHB3 enable register offset */
#define AHB4EN_REG_OFFSET               ((uint32_t)0x0000003CU)                     /*!< AHB4 enable register offset */
#define APB1EN_REG_OFFSET               ((uint32_t)0x00000040U)                     /*!< APB1 enable register offset */
#define APB2EN_REG_OFFSET               ((uint32_t)0x00000044U)                     /*!< APB2 enable register offset */
#define APB3EN_REG_OFFSET               ((uint32_t)0x00000048U)                     /*!< APB3 enable register offset */
#define APB4EN_REG_OFFSET               ((uint32_t)0x0000004CU)                     /*!< APB4 enable register offset */
#define AHB1SPEN_REG_OFFSET             ((uint32_t)0x00000050U)                     /*!< AHB1 sleep mode enable register offset */
#define AHB2SPEN_REG_OFFSET             ((uint32_t)0x00000054U)                     /*!< AHB2 sleep mode enable register offset */
#define AHB3SPEN_REG_OFFSET             ((uint32_t)0x00000058U)                     /*!< AHB3 sleep mode enable register offset */
#define AHB4SPEN_REG_OFFSET             ((uint32_t)0x0000005CU)                     /*!< AHB4 sleep mode enable register offset */
#define APB1SPEN_REG_OFFSET             ((uint32_t)0x00000060U)                     /*!< APB1 sleep mode enable register offset */
#define APB2SPEN_REG_OFFSET             ((uint32_t)0x00000064U)                     /*!< APB2 sleep mode enable register offset */
#define APB3SPEN_REG_OFFSET             ((uint32_t)0x00000068U)                     /*!< APB3 sleep mode enable register offset */
#define APB4SPEN_REG_OFFSET             ((uint32_t)0x0000006CU)                     /*!< APB4 sleep mode enable register offset */
#define ADD_APB2EN_REG_OFFSET           ((uint32_t)0x000000E4U)                     /*!< APB2 additional enable register offset */
#define ADD_APB2SPEN_REG_OFFSET         ((uint32_t)0x000000E8U)                     /*!< APB2 additional sleep mode enable register offset */

/* peripherals reset */
#define AHB1RST_REG_OFFSET              ((uint32_t)0x00000010U)                     /*!< AHB1 reset register offset */
#define AHB2RST_REG_OFFSET              ((uint32_t)0x00000014U)                     /*!< AHB2 reset register offset */
#define AHB3RST_REG_OFFSET              ((uint32_t)0x00000018U)                     /*!< AHB3 reset register offset */
#define AHB4RST_REG_OFFSET              ((uint32_t)0x0000001CU)                     /*!< AHB4 reset register offset */
#define APB1RST_REG_OFFSET              ((uint32_t)0x00000020U)                     /*!< APB1 reset register offset */
#define APB2RST_REG_OFFSET              ((uint32_t)0x00000024U)                     /*!< APB2 reset register offset */
#define APB3RST_REG_OFFSET              ((uint32_t)0x00000028U)                     /*!< APB3 reset register offset */
#define APB4RST_REG_OFFSET              ((uint32_t)0x0000002CU)                     /*!< APB4 reset register offset */
#define ADD_APB2RST_REG_OFFSET          ((uint32_t)0x000000E0U)                     /*!< APB2 additional reset register offset */
#define RSTSCK_REG_OFFSET               ((uint32_t)0x00000074U)                     /*!< reset source/clock register offset */

/* clock control */
#define CTL_REG_OFFSET                  ((uint32_t)0x00000000U)                     /*!< control register offset */
#define BDCTL_REG_OFFSET                ((uint32_t)0x00000070U)                     /*!< backup domain control register offset */
#define ADDCTL0_REG_OFFSET              ((uint32_t)0x000000C0U)                     /*!< additional clock control register 0 offset */
#define ADDCTL1_REG_OFFSET              ((uint32_t)0x000000C4U)                     /*!< additional clock control register 1 offset */

/* clock stabilization and stuck interrupt */
#define INT_REG_OFFSET                  ((uint32_t)0x0000000CU)                     /*!< clock interrupt register offset */
#define ADDINT_REG_OFFSET               ((uint32_t)0x000000CCU)                     /*!< additional clock interrupt register offset */

/* configuration register */
#define PLL0_REG_OFFSET                 ((uint32_t)0x00000004U)                     /*!< PLL0 register offset */
#define CFG0_REG_OFFSET                 ((uint32_t)0x00000008U)                     /*!< clock configuration register 0 offset */
#define PLL1_REG_OFFSET                 ((uint32_t)0x00000084U)                     /*!< PLL1 register offset */
#define PLL2_REG_OFFSET                 ((uint32_t)0x00000088U)                     /*!< PLL2 register offset */
#define CFG1_REG_OFFSET                 ((uint32_t)0x0000008CU)                     /*!< clock configuration register 1 offset */
#define CFG2_REG_OFFSET                 ((uint32_t)0x00000090U)                     /*!< clock configuration register 2 offset */
#define CFG3_REG_OFFSET                 ((uint32_t)0x00000094U)                     /*!< clock configuration register 3 offset */
#define PLLALL_REG_OFFSET               ((uint32_t)0x00000098U)                     /*!< PLL configuration register */
#define PLL0FRA_REG_OFFSET              ((uint32_t)0x0000009CU)                     /*!< PLL0 fraction configuration register */
#define PLL1FRA_REG_OFFSET              ((uint32_t)0x000000A0U)                     /*!< PLL1 fraction configuration register */
#define PLL2FRA_REG_OFFSET              ((uint32_t)0x000000A4U)                     /*!< PLL2 fraction configuration register */

/* peripheral clock enable */
typedef enum {
    /* AHB1 peripherals */
    RCU_ENET1      = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 0U),                         /*!< ENET1 clock */
    RCU_ENET1TX    = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 1U),                         /*!< ENET1 TX clock */
    RCU_ENET1RX    = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 2U),                         /*!< ENET1 RX clock */
    RCU_ENET1PTP   = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 3U),                         /*!< ENET1 PTP clock */
    RCU_USBHS0     = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 14U),                        /*!< USBHS0 clock */
    RCU_USBHS0ULPI = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 15U),                        /*!< USBHS0 ULPI clock */
    RCU_DMA0       = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 21U),                        /*!< DMA0 clock */
    RCU_DMA1       = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 22U),                        /*!< DMA1 clock */
    RCU_DMAMUX     = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 23U),                        /*!< IPA clock */
    RCU_ENET0      = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 25U),                        /*!< ENET0 clock */
    RCU_ENET0TX    = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 26U),                        /*!< ENET0 TX clock */
    RCU_ENET0RX    = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 27U),                        /*!< ENET0 RX clock */
    RCU_ENET0PTP   = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 28U),                        /*!< ENET0 PTP clock */
    RCU_USBHS1     = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 29U),                        /*!< USBHS1 clock */
    RCU_USBHS1ULPI = RCU_REGIDX_BIT(AHB1EN_REG_OFFSET, 30U),                        /*!< USBHS1 ULPI clock */
    /* AHB2 peripherals */
    RCU_DCI        = RCU_REGIDX_BIT(AHB2EN_REG_OFFSET, 0U),                         /*!< DCI clock */
    RCU_FAC        = RCU_REGIDX_BIT(AHB2EN_REG_OFFSET, 1U),                         /*!< FAC clock */
    RCU_SDIO1      = RCU_REGIDX_BIT(AHB2EN_REG_OFFSET, 2U),                         /*!< SDIO1 clock */
    RCU_CAU        = RCU_REGIDX_BIT(AHB2EN_REG_OFFSET, 3U),                         /*!< CAU clock */
    RCU_HAU        = RCU_REGIDX_BIT(AHB2EN_REG_OFFSET, 4U),                         /*!< HAU clock */
    RCU_TRNG       = RCU_REGIDX_BIT(AHB2EN_REG_OFFSET, 6U),                         /*!< TRNG clock */
    RCU_TMU        = RCU_REGIDX_BIT(AHB2EN_REG_OFFSET, 7U),                         /*!< TMU clock */
    RCU_RAMECCMU1  = RCU_REGIDX_BIT(AHB2EN_REG_OFFSET, 8U),                         /*!< RAMECCMU1 clock */
    /* AHB3 peripherals */
    RCU_EXMC       = RCU_REGIDX_BIT(AHB3EN_REG_OFFSET, 0U),                         /*!< EXMC clock */
    RCU_IPA        = RCU_REGIDX_BIT(AHB3EN_REG_OFFSET, 1U),                         /*!< IPA clock */
    RCU_SDIO0      = RCU_REGIDX_BIT(AHB3EN_REG_OFFSET, 2U),                         /*!< SDIO0 clock */
    RCU_MDMA       = RCU_REGIDX_BIT(AHB3EN_REG_OFFSET, 3U),                         /*!< MDMMA clock */
    RCU_OSPIM      = RCU_REGIDX_BIT(AHB3EN_REG_OFFSET, 4U),                         /*!< OSPIM clock */
    RCU_OSPI0      = RCU_REGIDX_BIT(AHB3EN_REG_OFFSET, 5U),                         /*!< OSPI0 clock */
    RCU_OSPI1      = RCU_REGIDX_BIT(AHB3EN_REG_OFFSET, 6U),                         /*!< OSPI1 clock */
    RCU_RTDEC0     = RCU_REGIDX_BIT(AHB3EN_REG_OFFSET, 8U),                         /*!< RTDEC0 clock */
    RCU_RTDEC1     = RCU_REGIDX_BIT(AHB3EN_REG_OFFSET, 9U),                         /*!< RTDEC1 clock */
    RCU_RAMECCMU0  = RCU_REGIDX_BIT(AHB3EN_REG_OFFSET, 10U),                        /*!< RAMECCMU0 clock */
    RCU_CPU        = RCU_REGIDX_BIT(AHB3EN_REG_OFFSET, 15U),                        /*!< CPU clock */
    /* AHB4 peripherals */
    RCU_GPIOA      = RCU_REGIDX_BIT(AHB4EN_REG_OFFSET, 0U),                         /*!< GPIOA clock */
    RCU_GPIOB      = RCU_REGIDX_BIT(AHB4EN_REG_OFFSET, 1U),                         /*!< GPIOB clock */
    RCU_GPIOC      = RCU_REGIDX_BIT(AHB4EN_REG_OFFSET, 2U),                         /*!< GPIOC clock */
    RCU_GPIOD      = RCU_REGIDX_BIT(AHB4EN_REG_OFFSET, 3U),                         /*!< GPIOD clock */
    RCU_GPIOE      = RCU_REGIDX_BIT(AHB4EN_REG_OFFSET, 4U),                         /*!< GPIOE clock */
    RCU_GPIOF      = RCU_REGIDX_BIT(AHB4EN_REG_OFFSET, 5U),                         /*!< GPIOF clock */
    RCU_GPIOG      = RCU_REGIDX_BIT(AHB4EN_REG_OFFSET, 6U),                         /*!< GPIOG clock */
    RCU_GPIOH      = RCU_REGIDX_BIT(AHB4EN_REG_OFFSET, 7U),                         /*!< GPIOH clock */
    RCU_GPIOJ      = RCU_REGIDX_BIT(AHB4EN_REG_OFFSET, 8U),                         /*!< GPIOJ clock */
    RCU_GPIOK      = RCU_REGIDX_BIT(AHB4EN_REG_OFFSET, 9U),                         /*!< GPIOK clock */
    RCU_BKPSRAM    = RCU_REGIDX_BIT(AHB4EN_REG_OFFSET, 13U),                        /*!< BKPSRAM clock */
    RCU_CRC        = RCU_REGIDX_BIT(AHB4EN_REG_OFFSET, 14U),                        /*!< CRC clock */
    RCU_HWSEM      = RCU_REGIDX_BIT(AHB4EN_REG_OFFSET, 15U),                        /*!< HWSEM  clock */
    /* APB1 peripherals */
    RCU_TIMER1     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 0U),                         /*!< TIMER1 clock */
    RCU_TIMER2     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 1U),                         /*!< TIMER2 clock */
    RCU_TIMER3     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 2U),                         /*!< TIMER3 clock */
    RCU_TIMER4     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 3U),                         /*!< TIMER4 clock */
    RCU_TIMER5     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 4U),                         /*!< TIMER5 clock */
    RCU_TIMER6     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 5U),                         /*!< TIMER6 clock */
    RCU_TIMER22    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 6U),                         /*!< TIMER22 clock */
    RCU_TIMER23    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 7U),                         /*!< TIMER23 clock */
    RCU_TIMER30    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 8U),                         /*!< TIMER30 clock */
    RCU_TIMER31    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 9U),                         /*!< TIMER31 clock */
    RCU_TIMER50    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 10U),                        /*!< TIMER50 clock */
    RCU_TIMER51    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 11U),                        /*!< TIMER51 clock */
    RCU_RSPDIF     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 13U),                        /*!< RSPDIF clock */
    RCU_SPI1       = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 14U),                        /*!< SPI1 clock */
    RCU_SPI2       = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 15U),                        /*!< SPI2 clock */
    RCU_MDIO       = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 16U),                        /*!< MDIO clock */
    RCU_USART1     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 17U),                        /*!< USART1 clock */
    RCU_USART2     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 18U),                        /*!< USART2 clock */
    RCU_UART3      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 19U),                        /*!< UART3 clock */
    RCU_UART4      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 20U),                        /*!< UART4 clock */
    RCU_I2C0       = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 21U),                        /*!< I2C0 clock */
    RCU_I2C1       = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 22U),                        /*!< I2C1 clock */
    RCU_I2C2       = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 23U),                        /*!< I2C2 clock */
    RCU_I2C3       = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 24U),                        /*!< I2C3 clock */
    RCU_CTC        = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 27U),                        /*!< CTC clock */
    RCU_DACHOLD    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 28U),                        /*!< DACHOLD clock */
    RCU_DAC        = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 29U),                        /*!< DAC clock */
    RCU_UART6      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 30U),                        /*!< UART6 clock */
    RCU_UART7      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 31U),                        /*!< UART7 clock */
    /* APB2 peripherals */
    RCU_TIMER0     = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 0U),                         /*!< TIMER0 clock */
    RCU_TIMER7     = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 1U),                         /*!< TIMER7 clock */
    RCU_USART0     = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 4U),                         /*!< USART0 clock */
    RCU_USART5     = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 5U),                         /*!< USART5 clock */
    RCU_ADC0       = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 8U),                         /*!< ADC0 clock */
    RCU_ADC1       = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 9U),                         /*!< ADC1 clock */
    RCU_ADC2       = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 10U),                        /*!< ADC2 clock */
    RCU_SPI0       = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 12U),                        /*!< SPI0 clock */
    RCU_SPI3       = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 13U),                        /*!< SPI3 clock */
    RCU_TIMER14    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 16U),                        /*!< TIMER14 clock */
    RCU_TIMER15    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 17U),                        /*!< TIMER15 clock */
    RCU_TIMER16    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 18U),                        /*!< TIMER16 clock */
    RCU_HPDF       = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 19U),                        /*!< HPDF clock */
    RCU_SPI4       = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 20U),                        /*!< SPI4 clock */
    RCU_SPI5       = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 21U),                        /*!< SPI5 clock */
    RCU_SAI0       = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 22U),                        /*!< SAI0 clock */
    RCU_SAI1       = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 23U),                        /*!< SAI1 clock */
    RCU_SAI2       = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 24U),                        /*!< SAI2 clock */
    RCU_TIMER40    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 25U),                        /*!< TIMER40 clock */
    RCU_TIMER41    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 26U),                        /*!< TIMER41 clock */
    RCU_TIMER42    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 27U),                        /*!< TIMER42 clock */
    RCU_TIMER43    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 28U),                        /*!< TIMER43 clock */
    RCU_TIMER44    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 29U),                        /*!< TIMER44 clock */
    RCU_EDOUT      = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 30U),                        /*!< EDOUT clock */
    RCU_TRIGSEL    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 31U),                        /*!< TRIGSEL clock */
    /* APB3 peripherals */
    RCU_TLI        = RCU_REGIDX_BIT(APB3EN_REG_OFFSET, 0U),                         /*!< TLI clock */
    RCU_WWDGT      = RCU_REGIDX_BIT(APB3EN_REG_OFFSET, 1U),                         /*!< WWDGT clock */
    /* APB4 peripherals */
    RCU_SYSCFG     = RCU_REGIDX_BIT(APB4EN_REG_OFFSET, 0U),                         /*!< SYSCFG  clock */
    RCU_CMP        = RCU_REGIDX_BIT(APB4EN_REG_OFFSET, 1U),                         /*!< CMP clock */
    RCU_VREF       = RCU_REGIDX_BIT(APB4EN_REG_OFFSET, 2U),                         /*!< VREF clock */
    RCU_LPDTS      = RCU_REGIDX_BIT(APB4EN_REG_OFFSET, 3U),                         /*!< LPDTS clock */
    RCU_PMU        = RCU_REGIDX_BIT(APB4EN_REG_OFFSET, 4U),                         /*!< PMU clock */
    RCU_RTC        = RCU_REGIDX_BIT(BDCTL_REG_OFFSET, 15U),                         /*!< RTC clock */
    /* APB2 additional peripherals */
    RCU_CAN0       = RCU_REGIDX_BIT(ADD_APB2EN_REG_OFFSET, 0U),                     /*!< CAN0 clock */
    RCU_CAN1       = RCU_REGIDX_BIT(ADD_APB2EN_REG_OFFSET, 1U),                     /*!< CAN1 clock */
    RCU_CAN2       = RCU_REGIDX_BIT(ADD_APB2EN_REG_OFFSET, 2U)                      /*!< CAN2 clock */
} rcu_periph_enum;

/* peripheral clock enable when sleep mode*/
typedef enum {
    /* AHB1 peripherals */
    RCU_ENET1_SLP       = RCU_REGIDX_BIT(AHB1SPEN_REG_OFFSET, 0U),                  /*!< ENET1 clock when sleep mode */
    RCU_ENET1TX_SLP     = RCU_REGIDX_BIT(AHB1SPEN_REG_OFFSET, 1U),                  /*!< ENET1 TX clock when sleep mode */
    RCU_ENET1RX_SLP     = RCU_REGIDX_BIT(AHB1SPEN_REG_OFFSET, 2U),                  /*!< ENET1 RX clock when sleep mode */
    RCU_ENET1PTP_SLP    = RCU_REGIDX_BIT(AHB1SPEN_REG_OFFSET, 3U),                  /*!< ENET1 PTP clock when sleep mode */
    RCU_USBHS0_SLP      = RCU_REGIDX_BIT(AHB1SPEN_REG_OFFSET, 14U),                 /*!< USBHS0 clock when sleep mode */
    RCU_USBHS0ULPI_SLP  = RCU_REGIDX_BIT(AHB1SPEN_REG_OFFSET, 15U),                 /*!< USBHS0ULPI clock when sleep mode */
    RCU_SRAM0_SLP       = RCU_REGIDX_BIT(AHB1SPEN_REG_OFFSET, 16U),                 /*!< SRAM0 clock when sleep mode */
    RCU_SRAM1_SLP       = RCU_REGIDX_BIT(AHB1SPEN_REG_OFFSET, 17U),                 /*!< SRAM1 clock when sleep mode */
    RCU_DMA0_SLP        = RCU_REGIDX_BIT(AHB1SPEN_REG_OFFSET, 21U),                 /*!< DMA0 clock when sleep mode */
    RCU_DMA1_SLP        = RCU_REGIDX_BIT(AHB1SPEN_REG_OFFSET, 22U),                 /*!< DMA1 clock when sleep mode */
    RCU_DMAMUX_SLP      = RCU_REGIDX_BIT(AHB1SPEN_REG_OFFSET, 23U),                 /*!< DMAMUX clock when sleep mode */
    RCU_ENET0_SLP       = RCU_REGIDX_BIT(AHB1SPEN_REG_OFFSET, 25U),                 /*!< ENET0 clock when sleep mode */
    RCU_ENET0TX_SLP     = RCU_REGIDX_BIT(AHB1SPEN_REG_OFFSET, 26U),                 /*!< ENET0 TX clock when sleep mode */
    RCU_ENET0RX_SLP     = RCU_REGIDX_BIT(AHB1SPEN_REG_OFFSET, 27U),                 /*!< ENET0 RX clock when sleep mode */
    RCU_ENET0PTP_SLP    = RCU_REGIDX_BIT(AHB1SPEN_REG_OFFSET, 28U),                 /*!< ENET0 PTP clock when sleep mode */
    RCU_USBHS1_SLP      = RCU_REGIDX_BIT(AHB1SPEN_REG_OFFSET, 29U),                 /*!< USBHS1 clock when sleep mode */
    RCU_USBHS1ULPI_SLP  = RCU_REGIDX_BIT(AHB1SPEN_REG_OFFSET, 30U),                 /*!< USBHS1ULPI clock when sleep mode */
    /* AHB2 peripherals */
    RCU_DCI_SLP         = RCU_REGIDX_BIT(AHB2SPEN_REG_OFFSET, 0U),                  /*!< DCI clock when sleep mode */
    RCU_FAC_SLP         = RCU_REGIDX_BIT(AHB2SPEN_REG_OFFSET, 1U),                  /*!< FAC clock when sleep mode */
    RCU_SDIO1_SLP       = RCU_REGIDX_BIT(AHB2SPEN_REG_OFFSET, 2U),                  /*!< SDIO1 clock when sleep mode */
    RCU_CAU_SLP         = RCU_REGIDX_BIT(AHB2SPEN_REG_OFFSET, 3U),                  /*!< CAU clock when sleep mode */
    RCU_HAU_SLP         = RCU_REGIDX_BIT(AHB2SPEN_REG_OFFSET, 4U),                  /*!< HAU clock when sleep mode */
    RCU_TRNG_SLP        = RCU_REGIDX_BIT(AHB2SPEN_REG_OFFSET, 6U),                  /*!< TRNG clock when sleep mode */
    RCU_TMU_SLP         = RCU_REGIDX_BIT(AHB2SPEN_REG_OFFSET, 7U),                  /*!< TMU clock when sleep mode */
    RCU_RAMECCMU1_SLP   = RCU_REGIDX_BIT(AHB2SPEN_REG_OFFSET, 8U),                  /*!< RAMECCMU1 clock when sleep mode */
    /* AHB3 peripherals */
    RCU_EXMC_SLP        = RCU_REGIDX_BIT(AHB3SPEN_REG_OFFSET, 0U),                  /*!< EXMC clock when sleep mode */
    RCU_IPA_SLP         = RCU_REGIDX_BIT(AHB3SPEN_REG_OFFSET, 1U),                  /*!< IPA clock when sleep mode */
    RCU_SDIO0_SLP       = RCU_REGIDX_BIT(AHB3SPEN_REG_OFFSET, 2U),                  /*!< SDIO0 clock when sleep mode */
    RCU_MDMA_SLP        = RCU_REGIDX_BIT(AHB3SPEN_REG_OFFSET, 3U),                  /*!< MDMMA clock when sleep mode */
    RCU_OSPIM_SLP       = RCU_REGIDX_BIT(AHB3SPEN_REG_OFFSET, 4U),                  /*!< OSPIM clock when sleep mode */
    RCU_OSPI0_SLP       = RCU_REGIDX_BIT(AHB3SPEN_REG_OFFSET, 5U),                  /*!< OSPI0 clock when sleep mode */
    RCU_OSPI1_SLP       = RCU_REGIDX_BIT(AHB3SPEN_REG_OFFSET, 6U),                  /*!< OSPI1 clock when sleep mode */
    RCU_RTDEC0_SLP      = RCU_REGIDX_BIT(AHB3SPEN_REG_OFFSET, 8U),                  /*!< RTDEC0 clock when sleep mode */
    RCU_RTDEC1_SLP      = RCU_REGIDX_BIT(AHB3SPEN_REG_OFFSET, 9U),                  /*!< RTDEC1 clock when sleep mode */
    RCU_RAMECCMU0_SLP   = RCU_REGIDX_BIT(AHB3SPEN_REG_OFFSET, 10U),                 /*!< RAMECCMU0 clock when sleep mode */
    RCU_AXISRAM_SLP     = RCU_REGIDX_BIT(AHB3SPEN_REG_OFFSET, 14U),                 /*!< AXISRAM clock when sleep mode */
    RCU_FMC_SLP         = RCU_REGIDX_BIT(AHB3SPEN_REG_OFFSET, 15U),                 /*!< FMC clock when sleep mode */
    /* AHB4 peripherals */
    RCU_GPIOA_SLP       = RCU_REGIDX_BIT(AHB4SPEN_REG_OFFSET, 0U),                  /*!< GPIOA clock when sleep mode */
    RCU_GPIOB_SLP       = RCU_REGIDX_BIT(AHB4SPEN_REG_OFFSET, 1U),                  /*!< GPIOB clock when sleep mode */
    RCU_GPIOC_SLP       = RCU_REGIDX_BIT(AHB4SPEN_REG_OFFSET, 2U),                  /*!< GPIOC clock when sleep mode */
    RCU_GPIOD_SLP       = RCU_REGIDX_BIT(AHB4SPEN_REG_OFFSET, 3U),                  /*!< GPIOD clock when sleep mode */
    RCU_GPIOE_SLP       = RCU_REGIDX_BIT(AHB4SPEN_REG_OFFSET, 4U),                  /*!< GPIOE clock when sleep mode */
    RCU_GPIOF_SLP       = RCU_REGIDX_BIT(AHB4SPEN_REG_OFFSET, 5U),                  /*!< GPIOF clock when sleep mode */
    RCU_GPIOG_SLP       = RCU_REGIDX_BIT(AHB4SPEN_REG_OFFSET, 6U),                  /*!< GPIOG clock when sleep mode */
    RCU_GPIOH_SLP       = RCU_REGIDX_BIT(AHB4SPEN_REG_OFFSET, 7U),                  /*!< GPIOH clock when sleep mode */
    RCU_GPIOJ_SLP       = RCU_REGIDX_BIT(AHB4SPEN_REG_OFFSET, 8U),                  /*!< GPIOJ clock when sleep mode */
    RCU_GPIOK_SLP       = RCU_REGIDX_BIT(AHB4SPEN_REG_OFFSET, 9U),                  /*!< GPIOK clock when sleep mode */
    RCU_BKPSRAM_SLP     = RCU_REGIDX_BIT(AHB4SPEN_REG_OFFSET, 13U),                 /*!< BKPSRAM clock when sleep mode */
    RCU_CRC_SLP         = RCU_REGIDX_BIT(AHB4SPEN_REG_OFFSET, 14U),                 /*!< CRC clock when sleep mode */
    /* APB1 peripherals */
    RCU_TIMER1_SLP      = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 0U),                  /*!< TIMER1 clock when sleep mode */
    RCU_TIMER2_SLP      = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 1U),                  /*!< TIMER2 clock when sleep mode */
    RCU_TIMER3_SLP      = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 2U),                  /*!< TIMER3 clock when sleep mode */
    RCU_TIMER4_SLP      = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 3U),                  /*!< TIMER4 clock when sleep mode */
    RCU_TIMER5_SLP      = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 4U),                  /*!< TIMER5 clock when sleep mode */
    RCU_TIMER6_SLP      = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 5U),                  /*!< TIMER6 clock when sleep mode */
    RCU_TIMER22_SLP     = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 6U),                  /*!< TIMER22 clock when sleep mode */
    RCU_TIMER23_SLP     = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 7U),                  /*!< TIMER23 clock when sleep mode */
    RCU_TIMER30_SLP     = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 8U),                  /*!< TIMER30 clock when sleep mode */
    RCU_TIMER31_SLP     = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 9U),                  /*!< TIMER31 clock when sleep mode */
    RCU_TIMER50_SLP     = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 10U),                 /*!< TIMER50 clock when sleep mode */
    RCU_TIMER51_SLP     = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 11U),                 /*!< TIMER51 clock when sleep mode */
    RCU_RSPDIF_SLP      = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 13U),                 /*!< RSPDIF clock when sleep mode */
    RCU_SPI1_SLP        = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 14U),                 /*!< SPI1 clock when sleep mode */
    RCU_SPI2_SLP        = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 15U),                 /*!< SPI2 clock when sleep mode */
    RCU_MDIO_SLP        = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 16U),                 /*!< MDIO clock when sleep mode */
    RCU_USART1_SLP      = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 17U),                 /*!< USART1 clock when sleep mode */
    RCU_USART2_SLP      = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 18U),                 /*!< USART2 clock when sleep mode */
    RCU_UART3_SLP       = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 19U),                 /*!< UART3 clock when sleep mode */
    RCU_UART4_SLP       = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 20U),                 /*!< UART4 clock when sleep mode */
    RCU_I2C0_SLP        = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 21U),                 /*!< I2C0 clock when sleep mode */
    RCU_I2C1_SLP        = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 22U),                 /*!< I2C1 clock when sleep mode */
    RCU_I2C2_SLP        = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 23U),                 /*!< I2C2 clock when sleep mode */
    RCU_I2C3_SLP        = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 24U),                 /*!< I2C3 clock when sleep mode */
    RCU_CTC_SLP         = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 27U),                 /*!< CTC clock when sleep mode */
    RCU_DACHOLD_SLP     = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 28U),                 /*!< DACHOLD clock when sleep mode */
    RCU_DAC_SLP         = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 29U),                 /*!< DAC clock when sleep mode */
    RCU_UART6_SLP       = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 30U),                 /*!< UART6 clock when sleep mode */
    RCU_UART7_SLP       = RCU_REGIDX_BIT(APB1SPEN_REG_OFFSET, 31U),                 /*!< UART7 clock when sleep mode */
    /* APB2 peripherals */
    RCU_TIMER0_SLP      = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 0U),                  /*!< TIMER0 clock when sleep mode */
    RCU_TIMER7_SLP      = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 1U),                  /*!< TIMER7 clock when sleep mode */
    RCU_USART0_SLP      = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 4U),                  /*!< USART0 clock when sleep mode */
    RCU_USART5_SLP      = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 5U),                  /*!< USART5 clock when sleep mode */
    RCU_ADC0_SLP        = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 8U),                  /*!< ADC0 clock when sleep mode */
    RCU_ADC1_SLP        = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 9U),                  /*!< ADC1 clock when sleep mode */
    RCU_ADC2_SLP        = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 10U),                 /*!< ADC2 clock when sleep mode */
    RCU_SPI0_SLP        = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 12U),                 /*!< SPI0 clock when sleep mode */
    RCU_SPI3_SLP        = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 13U),                 /*!< SPI3 clock when sleep mode */
    RCU_TIMER14_SLP     = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 16U),                 /*!< TIMER14 clock when sleep mode */
    RCU_TIMER15_SLP     = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 17U),                 /*!< TIMER15 clock when sleep mode */
    RCU_TIMER16_SLP     = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 18U),                 /*!< TIMER16 clock when sleep mode */
    RCU_HPDF_SLP        = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 19U),                 /*!< HPDF clock when sleep mode */
    RCU_SPI4_SLP        = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 20U),                 /*!< SPI4 clock when sleep mode */
    RCU_SPI5_SLP        = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 21U),                 /*!< SPI5 clock when sleep mode */
    RCU_SAI0_SLP        = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 22U),                 /*!< SAI0 clock when sleep mode */
    RCU_SAI1_SLP        = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 23U),                 /*!< SAI1 clock when sleep mode */
    RCU_SAI2_SLP        = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 24U),                 /*!< SAI2 clock when sleep mode */
    RCU_TIMER40_SLP     = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 25U),                 /*!< TIMER40 clock when sleep mode */
    RCU_TIMER41_SLP     = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 26U),                 /*!< TIMER41 clock when sleep mode */
    RCU_TIMER42_SLP     = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 27U),                 /*!< TIMER42 clock when sleep mode */
    RCU_TIMER43_SLP     = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 28U),                 /*!< TIMER43 clock when sleep mode */
    RCU_TIMER44_SLP     = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 29U),                 /*!< TIMER44 clock when sleep mode */
    RCU_EDOUT_SLP       = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 30U),                 /*!< EDOUT clock when sleep mode */
    RCU_TRIGSEL_SLP     = RCU_REGIDX_BIT(APB2SPEN_REG_OFFSET, 31U),                 /*!< TRIGSEL clock when sleep mode */
    /* APB3 peripherals */
    RCU_TLI_SLP         = RCU_REGIDX_BIT(APB3SPEN_REG_OFFSET, 0U),                  /*!< TLI clock when sleep mode */
    RCU_WWDGT_SLP       = RCU_REGIDX_BIT(APB3SPEN_REG_OFFSET, 1U),                  /*!< WWDGT clock when sleep mode */
    /* APB4 peripherals */
    RCU_SYSCFG_SLP      = RCU_REGIDX_BIT(APB4SPEN_REG_OFFSET, 0U),                  /*!< SYSCFG clock when sleep mode */
    RCU_CMP_SLP         = RCU_REGIDX_BIT(APB4SPEN_REG_OFFSET, 1U),                  /*!< CMP clock when sleep mode */
    RCU_VREF_SLP        = RCU_REGIDX_BIT(APB4SPEN_REG_OFFSET, 2U),                  /*!< VREF clock when sleep mode */
    RCU_LPDTS_SLP       = RCU_REGIDX_BIT(APB4SPEN_REG_OFFSET, 3U),                  /*!< LPDTS clock when sleep mode */
    RCU_PMU_SLP         = RCU_REGIDX_BIT(APB4SPEN_REG_OFFSET, 4U),                  /*!< PMU clock when sleep mode */
    /* APB2 additional peripherals */
    RCU_CAN0_SLP        = RCU_REGIDX_BIT(ADD_APB2SPEN_REG_OFFSET, 0U),              /*!< CAN0 clock when sleep mode */
    RCU_CAN1_SLP        = RCU_REGIDX_BIT(ADD_APB2SPEN_REG_OFFSET, 1U),              /*!< CAN1 clock when sleep mode */
    RCU_CAN2_SLP        = RCU_REGIDX_BIT(ADD_APB2SPEN_REG_OFFSET, 2U)               /*!< CAN2 clock when sleep mode */
} rcu_periph_sleep_enum;

/* peripherals reset */
typedef enum {
    /* AHB1 peripherals */
    RCU_ENET1RST     = RCU_REGIDX_BIT(AHB1RST_REG_OFFSET, 0U),                      /*!< ENET1 clock reset */
    RCU_USBHS0RST    = RCU_REGIDX_BIT(AHB1RST_REG_OFFSET, 14U),                     /*!< USBHS0 clock reset */
    RCU_DMA0RST      = RCU_REGIDX_BIT(AHB1RST_REG_OFFSET, 21U),                     /*!< DMA0 clock reset */
    RCU_DMA1RST      = RCU_REGIDX_BIT(AHB1RST_REG_OFFSET, 22U),                     /*!< DMA1 clock reset */
    RCU_DMAMUXRST    = RCU_REGIDX_BIT(AHB1RST_REG_OFFSET, 23U),                     /*!< DMAMUX clock reset */
    RCU_ENET0RST     = RCU_REGIDX_BIT(AHB1RST_REG_OFFSET, 25U),                     /*!< ENET clock reset */
    RCU_USBHS1RST    = RCU_REGIDX_BIT(AHB1RST_REG_OFFSET, 29U),                     /*!< USBHS1HS clock reset */
    /* AHB2 peripherals */
    RCU_DCIRST       = RCU_REGIDX_BIT(AHB2RST_REG_OFFSET, 0U),                      /*!< DCI clock reset */
    RCU_FACRST       = RCU_REGIDX_BIT(AHB2RST_REG_OFFSET, 1U),                      /*!< FAC clock reset */
    RCU_SDIO1RST     = RCU_REGIDX_BIT(AHB2RST_REG_OFFSET, 2U),                      /*!< SDIO1 clock reset */
    RCU_CAURST       = RCU_REGIDX_BIT(AHB2RST_REG_OFFSET, 3U),                      /*!< CAU clock reset */
    RCU_HAURST       = RCU_REGIDX_BIT(AHB2RST_REG_OFFSET, 4U),                      /*!< HAU clock reset */
    RCU_TRNGRST      = RCU_REGIDX_BIT(AHB2RST_REG_OFFSET, 6U),                      /*!< TRNG clock reset */
    RCU_TMURST       = RCU_REGIDX_BIT(AHB2RST_REG_OFFSET, 7U),                      /*!< TMU clock reset */
    /* AHB3 peripherals */
    RCU_EXMCRST      = RCU_REGIDX_BIT(AHB3RST_REG_OFFSET, 0U),                      /*!< EXMC clock reset */
    RCU_IPARST       = RCU_REGIDX_BIT(AHB3RST_REG_OFFSET, 1U),                      /*!< IPA clock reset */
    RCU_SDIO0RST     = RCU_REGIDX_BIT(AHB3RST_REG_OFFSET, 2U),                      /*!< SDIO0 clock reset */
    RCU_MDMARST      = RCU_REGIDX_BIT(AHB3RST_REG_OFFSET, 3U),                      /*!< MDMMA clock reset */
    RCU_OSPIMRST     = RCU_REGIDX_BIT(AHB3RST_REG_OFFSET, 4U),                      /*!< OSPIM clock reset */
    RCU_OSPI0RST     = RCU_REGIDX_BIT(AHB3RST_REG_OFFSET, 5U),                      /*!< OSPI0 clock reset */
    RCU_OSPI1RST     = RCU_REGIDX_BIT(AHB3RST_REG_OFFSET, 6U),                      /*!< OSPI1 clock reset */
    RCU_RTDEC0RST    = RCU_REGIDX_BIT(AHB3RST_REG_OFFSET, 8U),                      /*!< RTDEC0 clock reset */
    RCU_RTDEC1RST    = RCU_REGIDX_BIT(AHB3RST_REG_OFFSET, 9U),                      /*!< RTDEC1 clock reset */
    /* AHB4 peripherals */
    RCU_GPIOARST     = RCU_REGIDX_BIT(AHB4RST_REG_OFFSET, 0U),                      /*!< GPIOA clock reset */
    RCU_GPIOBRST     = RCU_REGIDX_BIT(AHB4RST_REG_OFFSET, 1U),                      /*!< GPIOB clock reset */
    RCU_GPIOCRST     = RCU_REGIDX_BIT(AHB4RST_REG_OFFSET, 2U),                      /*!< GPIOC clock reset */
    RCU_GPIODRST     = RCU_REGIDX_BIT(AHB4RST_REG_OFFSET, 3U),                      /*!< GPIOD clock reset */
    RCU_GPIOERST     = RCU_REGIDX_BIT(AHB4RST_REG_OFFSET, 4U),                      /*!< GPIOE clock reset */
    RCU_GPIOFRST     = RCU_REGIDX_BIT(AHB4RST_REG_OFFSET, 5U),                      /*!< GPIOF clock reset */
    RCU_GPIOGRST     = RCU_REGIDX_BIT(AHB4RST_REG_OFFSET, 6U),                      /*!< GPIOG clock reset */
    RCU_GPIOHRST     = RCU_REGIDX_BIT(AHB4RST_REG_OFFSET, 7U),                      /*!< GPIOH clock reset */
    RCU_GPIOJRST     = RCU_REGIDX_BIT(AHB4RST_REG_OFFSET, 8U),                      /*!< GPIOJ clock reset */
    RCU_GPIOKRST     = RCU_REGIDX_BIT(AHB4RST_REG_OFFSET, 9U),                      /*!< GPIOK clock reset */
    RCU_CRCRST       = RCU_REGIDX_BIT(AHB4RST_REG_OFFSET, 14U),                     /*!< CRC clock reset */
    RCU_HWSEMRST     = RCU_REGIDX_BIT(AHB4RST_REG_OFFSET, 15U),                     /*!< HWSEM clock reset */
    /* APB1 peripherals */
    RCU_TIMER1RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 0U),                      /*!< TIMER1 clock reset */
    RCU_TIMER2RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 1U),                      /*!< TIMER2 clock reset */
    RCU_TIMER3RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 2U),                      /*!< TIMER3 clock reset */
    RCU_TIMER4RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 3U),                      /*!< TIMER4 clock reset */
    RCU_TIMER5RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 4U),                      /*!< TIMER5 clock reset */
    RCU_TIMER6RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 5U),                      /*!< TIMER6 clock reset */
    RCU_TIMER22RST   = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 6U),                      /*!< TIMER22 clock reset */
    RCU_TIMER23RST   = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 7U),                      /*!< TIMER23 clock reset */
    RCU_TIMER30RST   = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 8U),                      /*!< TIMER30 clock reset */
    RCU_TIMER31RST   = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 9U),                      /*!< TIMER31 clock reset */
    RCU_TIMER50RST   = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 10U),                     /*!< TIMER50 clock reset */
    RCU_TIMER51RST   = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 11U),                     /*!< TIMER51 clock reset */
    RCU_RSPDIFRST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 13U),                     /*!< RSPDIF clock reset */
    RCU_SPI1RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 14U),                     /*!< SPI1 clock reset */
    RCU_SPI2RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 15U),                     /*!< SPI2 clock reset */
    RCU_MDIORST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 16U),                     /*!< MDIO clock reset */
    RCU_USART1RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 17U),                     /*!< USART1 clock reset */
    RCU_USART2RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 18U),                     /*!< USART2 clock reset */
    RCU_UART3RST     = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 19U),                     /*!< UART3 clock reset */
    RCU_UART4RST     = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 20U),                     /*!< UART4 clock reset */
    RCU_I2C0RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 21U),                     /*!< I2C0 clock reset */
    RCU_I2C1RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 22U),                     /*!< I2C1 clock reset */
    RCU_I2C2RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 23U),                     /*!< I2C2 clock reset */
    RCU_I2C3RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 24U),                     /*!< I2C3 clock reset */
    RCU_CTCRST       = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 27U),                     /*!< CTC clock reset */
    RCU_DACHOLDRST   = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 28U),                     /*!< DACHOLD clock reset */
    RCU_DACRST       = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 29U),                     /*!< DAC clock reset */
    RCU_UART6RST     = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 30U),                     /*!< UART6 clock reset */
    RCU_UART7RST     = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 31U),                     /*!< UART7 clock reset */
    /* APB2 peripherals */
    RCU_TIMER0RST    = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 0U),                      /*!< TIMER0 clock reset */
    RCU_TIMER7RST    = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 1U),                      /*!< TIMER7 clock reset */
    RCU_USART0RST    = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 4U),                      /*!< USART0 clock reset */
    RCU_USART5RST    = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 5U),                      /*!< USART5 clock reset */
    RCU_ADC0RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 8U),                      /*!< ADC0 clock reset */
    RCU_ADC1RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 9U),                      /*!< ADC1 clock reset */
    RCU_ADC2RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 10U),                     /*!< ADC2 clock reset */
    RCU_SPI0RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 12U),                     /*!< SPI0 clock reset */
    RCU_SPI3RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 13U),                     /*!< SPI3 clock reset */
    RCU_TIMER14RST   = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 16U),                     /*!< TIMER14 clock reset */
    RCU_TIMER15RST   = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 17U),                     /*!< TIMER15 clock reset */
    RCU_TIMER16RST   = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 18U),                     /*!< TIMER16 clock reset */
    RCU_HPDFRST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 19U),                     /*!< HPDF clock reset */
    RCU_SPI4RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 20U),                     /*!< SPI4 clock reset */
    RCU_SPI5RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 21U),                     /*!< SPI5 clock reset */
    RCU_SAI0RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 22U),                     /*!< SAI0 clock reset */
    RCU_SAI1RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 23U),                     /*!< SAI1 clock reset */
    RCU_SAI2RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 24U),                     /*!< SAI2 clock reset */
    RCU_TIMER40RST   = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 25U),                     /*!< TIMER40 clock reset */
    RCU_TIMER41RST   = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 26U),                     /*!< TIMER41 clock reset */
    RCU_TIMER42RST   = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 27U),                     /*!< TIMER42 clock reset */
    RCU_TIMER43RST   = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 28U),                     /*!< TIMER43 clock reset */
    RCU_TIMER44RST   = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 29U),                     /*!< TIMER44 clock reset */
    RCU_EDOUTRST     = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 30U),                     /*!< EDOUT clock reset */
    RCU_TRIGSELRST   = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 31U),                     /*!< TRIGSEL clock reset */
    /* APB3 peripherals */
    RCU_TLIRST       = RCU_REGIDX_BIT(APB3RST_REG_OFFSET, 0U),                      /*!< TLI clock reset */
    RCU_WWDGTRST     = RCU_REGIDX_BIT(APB3RST_REG_OFFSET, 1U),                      /*!< WWDGT clock reset */
    /* APB4 peripherals */
    RCU_SYSCFGRST    = RCU_REGIDX_BIT(APB4RST_REG_OFFSET, 0U),                      /*!< SYSCFG clock reset */
    RCU_CMPRST       = RCU_REGIDX_BIT(APB4RST_REG_OFFSET, 1U),                      /*!< CMP clock reset */
    RCU_VREFRST      = RCU_REGIDX_BIT(APB4RST_REG_OFFSET, 2U),                      /*!< VREF clock reset */
    RCU_LPDTSRST     = RCU_REGIDX_BIT(APB4RST_REG_OFFSET, 3U),                      /*!< LPDTS clock reset */
    RCU_PMURST       = RCU_REGIDX_BIT(APB4RST_REG_OFFSET, 4U),                      /*!< PMU clock reset */
    /* APB2 additional peripherals */
    RCU_CAN0RST      = RCU_REGIDX_BIT(ADD_APB2RST_REG_OFFSET, 0U),                  /*!< CAN0 clock reset */
    RCU_CAN1RST      = RCU_REGIDX_BIT(ADD_APB2RST_REG_OFFSET, 1U),                  /*!< CAN1 clock reset */
    RCU_CAN2RST      = RCU_REGIDX_BIT(ADD_APB2RST_REG_OFFSET, 2U)                   /*!< CAN2 clock reset */
} rcu_periph_reset_enum;

/* clock stabilization and failure and peripheral reset flags */
typedef enum {
    /* clock stabilization flags */
    RCU_FLAG_IRC64MSTB     = RCU_REGIDX_BIT(CTL_REG_OFFSET, 31U),                   /*!< IRC64M stabilization flags */
    RCU_FLAG_HXTALSTB      = RCU_REGIDX_BIT(CTL_REG_OFFSET, 17U),                   /*!< HXTAL stabilization flags */
    RCU_FLAG_PLL0STB       = RCU_REGIDX_BIT(CTL_REG_OFFSET, 25U),                   /*!< PLL0 stabilization flags */
    RCU_FLAG_PLL1STB       = RCU_REGIDX_BIT(CTL_REG_OFFSET, 27U),                   /*!< PLL1 stabilization flags */
    RCU_FLAG_PLL2STB       = RCU_REGIDX_BIT(CTL_REG_OFFSET, 29U),                   /*!< PLL2 stabilization flags */
    RCU_FLAG_LXTALSTB      = RCU_REGIDX_BIT(BDCTL_REG_OFFSET, 1U),                  /*!< LXTAL stabilization flags */
    RCU_FLAG_IRC32KSTB     = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 1U),                 /*!< IRC32K stabilization flags */
    RCU_FLAG_IRC48MSTB     = RCU_REGIDX_BIT(ADDCTL0_REG_OFFSET, 17U),               /*!< IRC48M stabilization flags */
    RCU_FLAG_LPIRC4MSTB    = RCU_REGIDX_BIT(ADDCTL1_REG_OFFSET, 1U),                /*!< LPIRC4M stabilization flags */
    RCU_FLAG_PLLUSBHS0STB  = RCU_REGIDX_BIT(ADDCTL1_REG_OFFSET, 29U),               /*!< PLLUSBHS0 stabilization flags */
    RCU_FLAG_PLLUSBHS1STB  = RCU_REGIDX_BIT(ADDCTL1_REG_OFFSET, 31U),               /*!< PLLUSBHS1 stabilization flags */
    /* clock failure flag */
    RCU_FLAG_LCKMD         = RCU_REGIDX_BIT(BDCTL_REG_OFFSET, 6U),                  /*!< LXTAL clock failure detection flags */
    /* reset source flags */
    RCU_FLAG_BORRST        = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 25U),                /*!< BOR reset flags */
    RCU_FLAG_EPRST         = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 26U),                /*!< External PIN reset flags */
    RCU_FLAG_PORRST        = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 27U),                /*!< power reset flags */
    RCU_FLAG_SWRST         = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 28U),                /*!< Software reset flags */
    RCU_FLAG_FWDGTRST      = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 29U),                /*!< FWDGT reset flags */
    RCU_FLAG_WWDGTRST      = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 30U),                /*!< WWDGT reset flags */
    RCU_FLAG_LPRST         = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 31U)                 /*!< low-power reset flags */
} rcu_flag_enum;

/* clock stabilization and stuck interrupt flags */
typedef enum {
    RCU_INT_FLAG_IRC32KSTB      = RCU_REGIDX_BIT(INT_REG_OFFSET, 0U),               /*!< IRC32K stabilization interrupt flag */
    RCU_INT_FLAG_LXTALSTB       = RCU_REGIDX_BIT(INT_REG_OFFSET, 1U),               /*!< LXTAL stabilization interrupt flag */
    RCU_INT_FLAG_IRC64MSTB      = RCU_REGIDX_BIT(INT_REG_OFFSET, 2U),               /*!< IRC64M stabilization interrupt flag */
    RCU_INT_FLAG_HXTALSTB       = RCU_REGIDX_BIT(INT_REG_OFFSET, 3U),               /*!< HXTAL stabilization interrupt flag */
    RCU_INT_FLAG_PLL0STB        = RCU_REGIDX_BIT(INT_REG_OFFSET, 4U),               /*!< PLL0 stabilization interrupt flag */
    RCU_INT_FLAG_PLL1STB        = RCU_REGIDX_BIT(INT_REG_OFFSET, 5U),               /*!< PLL1 stabilization interrupt flag */
    RCU_INT_FLAG_PLL2STB        = RCU_REGIDX_BIT(INT_REG_OFFSET, 6U),               /*!< PLL2 stabilization interrupt flag */
    RCU_INT_FLAG_CKM            = RCU_REGIDX_BIT(INT_REG_OFFSET, 7U),               /*!< HXTAL clock stuck interrupt flag */
    RCU_INT_FLAG_LCKM           = RCU_REGIDX_BIT(INT_REG_OFFSET, 27U),              /*!< LXTAL clock stuck interrupt flag */
    RCU_INT_FLAG_LPIRC4MSTB     = RCU_REGIDX_BIT(INT_REG_OFFSET, 24U),              /*!< LPIRC4M stabilization interrupt flag */
    RCU_INT_FLAG_IRC48MSTB      = RCU_REGIDX_BIT(ADDINT_REG_OFFSET, 6U),            /*!< IRC48M stabilization interrupt flag */
    RCU_INT_FLAG_PLLUSBHS0STB   = RCU_REGIDX_BIT(ADDINT_REG_OFFSET, 4U),            /*!< PLLUSBHS0 stabilization interrupt flag */
    RCU_INT_FLAG_PLLUSBHS1STB   = RCU_REGIDX_BIT(ADDINT_REG_OFFSET, 5U)             /*!< PLLUSBHS1 stabilization interrupt flag */
} rcu_int_flag_enum;

/* clock stabilization and stuck interrupt flags clear */
typedef enum {
    RCU_INT_FLAG_IRC32KSTB_CLR      = RCU_REGIDX_BIT(INT_REG_OFFSET, 16U),          /*!< IRC32K stabilization interrupt flags clear */
    RCU_INT_FLAG_LXTALSTB_CLR       = RCU_REGIDX_BIT(INT_REG_OFFSET, 17U),          /*!< LXTAL stabilization interrupt flags clear */
    RCU_INT_FLAG_IRC64MSTB_CLR      = RCU_REGIDX_BIT(INT_REG_OFFSET, 18U),          /*!< IRC64M stabilization interrupt flags clear */
    RCU_INT_FLAG_HXTALSTB_CLR       = RCU_REGIDX_BIT(INT_REG_OFFSET, 19U),          /*!< HXTAL stabilization interrupt flags clear */
    RCU_INT_FLAG_PLL0STB_CLR        = RCU_REGIDX_BIT(INT_REG_OFFSET, 20U),          /*!< PLL0 stabilization interrupt flags clear */
    RCU_INT_FLAG_PLL1STB_CLR        = RCU_REGIDX_BIT(INT_REG_OFFSET, 21U),          /*!< PLL1 stabilization interrupt flags clear */
    RCU_INT_FLAG_PLL2STB_CLR        = RCU_REGIDX_BIT(INT_REG_OFFSET, 22U),          /*!< PLL2 stabilization interrupt flags clear */
    RCU_INT_FLAG_CKM_CLR            = RCU_REGIDX_BIT(INT_REG_OFFSET, 23U),          /*!< HXTAL clock stuck interrupt flags clear */
    RCU_INT_FLAG_LCKM_CLR           = RCU_REGIDX_BIT(INT_REG_OFFSET, 28U),          /*!< LXTAL clock stuck interrupt flags clear */
    RCU_INT_FLAG_LPIRC4MSTB_CLR     = RCU_REGIDX_BIT(INT_REG_OFFSET, 26U),          /*!< LPIRC4M  stabilization interrupt flag clear */
    RCU_INT_FLAG_IRC48MSTB_CLR      = RCU_REGIDX_BIT(ADDINT_REG_OFFSET, 22U),       /*!< IRC48M stabilization interrupt flag clear */
    RCU_INT_FLAG_PLLUSBHS0STB_CLR   = RCU_REGIDX_BIT(ADDINT_REG_OFFSET, 20U),       /*!< PLLUSBHS0 stabilization interrupt flag clear */
    RCU_INT_FLAG_PLLUSBHS1STB_CLR   = RCU_REGIDX_BIT(ADDINT_REG_OFFSET, 21U)        /*!< PLLUSBHS1 stabilization interrupt flag clear */
} rcu_int_flag_clear_enum;

/* clock stabilization interrupt enable or disable */
typedef enum {
    RCU_INT_IRC32KSTB               = RCU_REGIDX_BIT(INT_REG_OFFSET, 8U),           /*!< IRC32K stabilization interrupt */
    RCU_INT_LXTALSTB                = RCU_REGIDX_BIT(INT_REG_OFFSET, 9U),           /*!< LXTAL stabilization interrupt */
    RCU_INT_IRC64MSTB               = RCU_REGIDX_BIT(INT_REG_OFFSET, 10U),          /*!< IRC64M stabilization interrupt */
    RCU_INT_HXTALSTB                = RCU_REGIDX_BIT(INT_REG_OFFSET, 11U),          /*!< HXTAL stabilization interrupt */
    RCU_INT_PLL0STB                 = RCU_REGIDX_BIT(INT_REG_OFFSET, 12U),          /*!< PLL0 stabilization interrupt */
    RCU_INT_PLL1STB                 = RCU_REGIDX_BIT(INT_REG_OFFSET, 13U),          /*!< PLL1 stabilization interrupt */
    RCU_INT_PLL2STB                 = RCU_REGIDX_BIT(INT_REG_OFFSET, 14U),          /*!< PLL2 stabilization interrupt */
    RCU_INT_IRC48MSTB               = RCU_REGIDX_BIT(ADDINT_REG_OFFSET, 14U),       /*!< internal 48 MHz RC oscillator stabilization interrupt */
    RCU_INT_LPIRC4MSTB              = RCU_REGIDX_BIT(INT_REG_OFFSET, 25U),          /*!< LPIRC4M stabilization interrupt */
    RCU_INT_PLLUSBHS0STB            = RCU_REGIDX_BIT(ADDINT_REG_OFFSET, 12U),       /*!< PLLUSBHS0 stabilization interrupt */
    RCU_INT_PLLUSBHS1STB            = RCU_REGIDX_BIT(ADDINT_REG_OFFSET, 13U)        /*!< PLLUSBHS1 stabilization interrupt */
} rcu_int_enum;

/* oscillator types */
typedef enum {
    RCU_HXTAL                       = RCU_REGIDX_BIT(CTL_REG_OFFSET, 16U),          /*!< HXTAL */
    RCU_LXTAL                       = RCU_REGIDX_BIT(BDCTL_REG_OFFSET, 0U),         /*!< LXTAL */
    RCU_IRC64M                      = RCU_REGIDX_BIT(CTL_REG_OFFSET, 30U),          /*!< IRC64M */
    RCU_IRC48M                      = RCU_REGIDX_BIT(ADDCTL0_REG_OFFSET, 16U),      /*!< IRC48M */
    RCU_IRC32K                      = RCU_REGIDX_BIT(RSTSCK_REG_OFFSET, 0U),        /*!< IRC32K */
    RCU_LPIRC4M                     = RCU_REGIDX_BIT(ADDCTL1_REG_OFFSET, 0U),       /*!< LPIRC4M */
    RCU_PLL0_CK                     = RCU_REGIDX_BIT(CTL_REG_OFFSET, 24U),          /*!< PLL0 */
    RCU_PLL1_CK                     = RCU_REGIDX_BIT(CTL_REG_OFFSET, 26U),          /*!< PLL1 */
    RCU_PLL2_CK                     = RCU_REGIDX_BIT(CTL_REG_OFFSET, 28U),          /*!< PLL2 */
    RCU_PLLUSBHS0_CK                = RCU_REGIDX_BIT(ADDCTL1_REG_OFFSET, 28U),      /*!< PLLUSBHS0 */
    RCU_PLLUSBHS1_CK                = RCU_REGIDX_BIT(ADDCTL1_REG_OFFSET, 30U)       /*!< PLLUSBHS1 */
} rcu_osci_type_enum;

/* rcu clock frequency */
typedef enum {
    CK_SYS = 0U,                                                                    /*!< system clock */
    CK_AHB,                                                                         /*!< AHB clock */
    CK_APB1,                                                                        /*!< APB1 clock */
    CK_APB2,                                                                        /*!< APB2 clock */
    CK_APB3,                                                                        /*!< APB3 clock */
    CK_APB4,                                                                        /*!< APB4 clock */
    CK_PLL0P,                                                                       /*!< PLL0P clock */
    CK_PLL0Q,                                                                       /*!< PLL0Q clock */
    CK_PLL0R,                                                                       /*!< PLL0R clock */
    CK_PLL1P,                                                                       /*!< PLL1P clock */
    CK_PLL1Q,                                                                       /*!< PLL1Q clock */
    CK_PLL1R,                                                                       /*!< PLL1R clock */
    CK_PLL2P,                                                                       /*!< PLL2P clock */
    CK_PLL2Q,                                                                       /*!< PLL2Q clock */
    CK_PLL2R,                                                                       /*!< PLL2R clock */
    CK_PER,                                                                         /*!< PER clock */
    CK_USART0,                                                                      /*!< USART0 clock */
    CK_USART1,                                                                      /*!< USART1 clock */
    CK_USART2,                                                                      /*!< USART2 clock */
    CK_USART5,                                                                      /*!< USART5 clock */
    CK_IRC64MDIV,                                                                   /*!< IRC64MDIV clock */
    CK_HXTAL,                                                                       /*!< HXTAL clock */
    CK_LPIRC4M                                                                      /*!< LPIRC4M clock */
} rcu_clock_freq_enum;

typedef enum {
    IDX_USART0 = 0U,                                                                /*!< idnex of USART0 */
    IDX_USART1,                                                                     /*!< idnex of USART1 */
    IDX_USART2,                                                                     /*!< idnex of USART2 */
    IDX_USART5                                                                      /*!< idnex of USART5 */
} usart_idx_enum;

typedef enum {
    IDX_I2C0 = 0U,                                                                  /*!< idnex of I2C0 */
    IDX_I2C1,                                                                       /*!< idnex of I2C1 */
    IDX_I2C2,                                                                       /*!< idnex of I2C2 */
    IDX_I2C3,                                                                       /*!< idnex of I2C2 */
} i2c_idx_enum;

typedef enum {
    IDX_CAN0 = 0U,                                                                  /*!< idnex of CAN0 */
    IDX_CAN1,                                                                       /*!< idnex of CAN1 */
    IDX_CAN2,                                                                       /*!< idnex of CAN2 */
} can_idx_enum;

typedef enum {
    IDX_SAI0 = 0U,                                                                  /*!< idnex of SAI0 */
    IDX_SAI1                                                                        /*!< idnex of SAI1 */
} sai_idx_enum;

typedef enum {
    IDX_SAI2B0 = 0U,                                                                /*!< idnex of SAI2B0 */
    IDX_SAI2B1                                                                      /*!< idnex of SAI2B1 */
} sai2b_idx_enum;

typedef enum {
    IDX_ADC0 = 0U,                                                                  /*!< idnex of ADC0 */
    IDX_ADC1,                                                                       /*!< idnex of ADC1 */
    IDX_ADC2                                                                        /*!< idnex of ADC2 */
} adc_idx_enum;

typedef enum {
    IDX_USBHS0 = 0U,                                                                /*!< idnex of USBHS0 */
    IDX_USBHS1                                                                      /*!< idnex of USBHS1 */
} usbhs_idx_enum;

typedef enum {
    IDX_PLL0 = 0U,                                                                  /*!< idnex of PLL0 */
    IDX_PLL1,                                                                       /*!< idnex of PLL1 */
    IDX_PLL2                                                                        /*!< idnex of PLL2 */
} pll_idx_enum;

typedef enum {
    IDX_SDIO0 = 0U,                                                                 /*!< idnex of SDIO0 */
    IDX_SDIO1                                                                       /*!< idnex of SDIO1 */
} sdio_idx_enum;

typedef enum {
    IDX_SPI0 = 0U,                                                                  /*!< idnex of SPI0 */
    IDX_SPI1,                                                                       /*!< idnex of SPI1 */
    IDX_SPI2,                                                                       /*!< idnex of SPI2 */
    IDX_SPI3,                                                                       /*!< idnex of SPI3 */
    IDX_SPI4,                                                                       /*!< idnex of SPI4 */
    IDX_SPI5                                                                        /*!< idnex of SPI5 */
} spi_idx_enum;

/* RCU_PLLADDCTL register bit define */
/* PLLs P/Q/R divider output enable */
#define RCU_PLL0P                 RCU_PLLADDCTL_PLL0PEN                             /*!< PLL0P divider output enable */
#define RCU_PLL0Q                 RCU_PLLADDCTL_PLL0QEN                             /*!< PLL0Q divider output enable */
#define RCU_PLL0R                 RCU_PLLADDCTL_PLL0REN                             /*!< PLL0R divider output enable */
#define RCU_PLL1P                 RCU_PLLADDCTL_PLL1PEN                             /*!< PLL1P divider output enable */
#define RCU_PLL1Q                 RCU_PLLADDCTL_PLL1QEN                             /*!< PLL1Q divider output enable */
#define RCU_PLL1R                 RCU_PLLADDCTL_PLL1REN                             /*!< PLL1R divider output enable */
#define RCU_PLL2P                 RCU_PLLADDCTL_PLL2PEN                             /*!< PLL2P divider output enable */
#define RCU_PLL2Q                 RCU_PLLADDCTL_PLL2QEN                             /*!< PLL2Q divider output enable */
#define RCU_PLL2R                 RCU_PLLADDCTL_PLL2REN                             /*!< PLL2R divider output enable */

/* RCU_CFG0 register bit define */
/* USARTx(x=0,1,2,5) clock source selection */
#define CFG1_USART0SEL(regval)       (BITS(0,1) & ((uint32_t)(regval) << 0U))
#define RCU_USARTSRC_APB             CFG1_USART0SEL(0)                              /*!< CK_USART select CK_APB */
#define RCU_USARTSRC_AHB             CFG1_USART0SEL(1)                              /*!< CK_USART select CK_AHB */
#define RCU_USARTSRC_LXTAL           CFG1_USART0SEL(2)                              /*!< CK_USART select CK_LXTAL */
#define RCU_USARTSRC_IRC64MDIV       CFG1_USART0SEL(3)                              /*!< CK_USART select CK_IRC16MDIV */

/* I2Cx(x=0,1,2,3) clock source selection */
#define CFG3_I2C1SEL(regval)         (BITS(0,1) & ((uint32_t)(regval) << 0U))
#define RCU_I2CSRC_APB1              CFG3_I2C1SEL(0)                                /*!< CK_I2C select CK_APB1 */
#define RCU_I2CSRC_PLL2R             CFG3_I2C1SEL(1)                                /*!< CK_I2C select CK_PLL2R */
#define RCU_I2CSRC_IRC64MDIV         CFG3_I2C1SEL(2)                                /*!< CK_I2C select CK_IRC64MDIV */
#define RCU_I2CSRC_LPIRC4M           CFG3_I2C1SEL(3)                                /*!< CK_I2C select CK_LPIRC4M */

/* CANx(x=0,1,2) clock source selection */
#define CFG1_CAN0SEL(regval)         (BITS(8,9) & ((uint32_t)(regval) << 8U))
#define RCU_CANSRC_HXTAL             CFG1_CAN0SEL(0)                                /*!< CK_CAN select CK_HXTAL */
#define RCU_CANSRC_APB2              CFG1_CAN0SEL(1)                                /*!< CK_CAN select CK_APB2 */
#define RCU_CANSRC_APB2_DIV2         CFG1_CAN0SEL(2)                                /*!< CK_CAN select CK_APB2/2 */
#define RCU_CANSRC_IRC64MDIV         CFG1_CAN0SEL(3)                                /*!< CK_CAN select CK_IRC64MDIV */

/* RSPDIF clock selection */
#define CFG1_RSPDIFSEL(regval)       (BITS(4,5) & ((uint32_t)(regval) << 4U))
#define RCU_RSPDIFSRC_PLL0Q          CFG1_RSPDIFSEL(0)                              /*!< CK_RSPDIF select CK_PLL0Q */
#define RCU_RSPDIFSRC_PLL1R          CFG1_RSPDIFSEL(1)                              /*!< CK_RSPDIF select CK_PLL1R */
#define RCU_RSPDIFSRC_PLL2R          CFG1_RSPDIFSEL(2)                              /*!< CK_RSPDIF select CK_PLL2R */
#define RCU_RSPDIFSRC_IRC64MDIV      CFG1_RSPDIFSEL(3)                              /*!< CK_RSPDIF select CK_IRC64MDIV */

/* EXMC clock selection */
#define CFG4_EXMCSEL(regval)         (BITS(8,9) & ((uint32_t)(regval) << 8U))
#define RCU_EXMCSRC_AHB              CFG4_EXMCSEL(0)                                /*!< CK_EXMC select CK_AHB */
#define RCU_EXMCSRC_PLL0Q            CFG4_EXMCSEL(1)                                /*!< CK_EXMC select CK_PLL0Q */
#define RCU_EXMCSRC_PLL1R            CFG4_EXMCSEL(2)                                /*!< CK_EXMC select CK_PLL1R */
#define RCU_EXMCSRC_PER              CFG4_EXMCSEL(3)                                /*!< CK_EXMC select CK_PER */

/* SPIx(x=0,1,2) clock source selecion */
#define CFG5_SPI0SEL(regval)         (BITS(0,2) & ((uint32_t)(regval) << 0U))
#define RCU_SPISRC_PLL0Q             CFG5_SPI0SEL(0)                                /*!< CK_SPI select CK_PLL0Q */
#define RCU_SPISRC_PLL1P             CFG5_SPI0SEL(1)                                /*!< CK_SPI select CK_PLL1P */
#define RCU_SPISRC_PLL2P             CFG5_SPI0SEL(2)                                /*!< CK_SPI select CK_PLL2P */
#define RCU_SPISRC_I2S_CKIN          CFG5_SPI0SEL(3)                                /*!< CK_SPI select I2S_CKIN */
#define RCU_SPISRC_PER               CFG5_SPI0SEL(4)                                /*!< CK_SPI select CK_PER */

/* SPIx(x=3,4,5) clock source selection */
#define CFG5_SPI3SEL(regval)         (BITS(12,14) & ((uint32_t)(regval) << 12U))
#define RCU_SPISRC_APB2              CFG5_SPI3SEL(0)                                /*!< CK_SPI select CK_APB2 */
#define RCU_SPISRC_PLL1Q             CFG5_SPI3SEL(1)                                /*!< CK_SPI select CK_PLL1Q */
#define RCU_SPISRC_PLL2Q             CFG5_SPI3SEL(2)                                /*!< CK_SPI select CK_PLL2Q */
#define RCU_SPISRC_IRC64MDIV         CFG5_SPI3SEL(3)                                /*!< CK_SPI select CK_IRC64MDIV */
#define RCU_SPISRC_LPIRC4M           CFG5_SPI3SEL(4)                                /*!< CK_SPI select CK_LPIRC4M */
#define RCU_SPISRC_HXTAL             CFG5_SPI3SEL(5)                                /*!< CK_SPI select CK_HXTAL */
#define RCU_SPI5SRC_I2S_CKIN         CFG5_SPI3SEL(6)                                /*!< CK_SPI select I2S_CKIN */

/* SDIOx(x=0,1) clock source selection */
#define RCU_SDIO0SRC_PLL0Q           (uint32_t)(0X00000000U)                        /*!< CK_SDIO0 select CK_PLL0Q */
#define RCU_SDIO0SRC_PLL1R           RCU_CFG4_SDIO0SEL                              /*!< CK_SDIO0 select CK_PLL1R */
#define RCU_SDIO1SRC_PLL0Q           (uint32_t)(0X00000000U)                        /*!< CK_SDIO1 select CK_PLL0Q */
#define RCU_SDIO1SRC_PLL1R           RCU_CFG3_SDIO1SEL                              /*!< CK_SDIO1 select CK_PLL1R */

/* Deep-sleep wakeup system clock source selection */
#define RCU_DSPWUSSEL_IRC64MDIV      (uint32_t)(0X00000000U)                        /*!< CK_IRC64MDIV is selected as wake up system clock from deep-sleep mode */
#define RCU_DSPWUSSEL_LPIRC4M        RCU_CFG3_DSPWUSSEL                             /*!< CK_LPIRC4M is selected as wake up system clock from deep-sleep mode */

/* ADCx(x=0,1,2) clock source selection */
#define CFG3_ADC0SEL(regval)         (BITS(26,27) & ((uint32_t)(regval) << 26U))
#define RCU_ADCSRC_PLL1P             CFG3_ADC0SEL(0)                                /*!< CK_ADC select CK_PLL1P */
#define RCU_ADCSRC_PLL2R             CFG3_ADC0SEL(1)                                /*!< CK_ADC select CK_PLL2R */
#define RCU_ADCSRC_PER               CFG3_ADC0SEL(2)                                /*!< CK_ADC select CK_PER */

/* SAIx(x=0,1) clock source selection */
#define CFG2_SAI0SEL(regval)         (BITS(16,18) & ((uint32_t)(regval) << 16U))
#define RCU_SAISRC_PLL0Q             CFG2_SAI0SEL(0)                                /*!< CK_SAI0/1 select CK_PLL0Q */
#define RCU_SAISRC_PLL1P             CFG2_SAI0SEL(1)                                /*!< CK_SAI0/1 select CK_PLL1P */
#define RCU_SAISRC_PLL2P             CFG2_SAI0SEL(2)                                /*!< CK_SAI0/1 select CK_PLL2P */
#define RCU_SAISRC_I2S_CKIN          CFG2_SAI0SEL(3)                                /*!< CK_SAI0/1 select I2S_CKIN */
#define RCU_SAISRC_PER               CFG2_SAI0SEL(4)                                /*!< CK_SAI0/1 select CK_PER */

/* SAI2Bx(x=0,1) clock source selection */
#define CFG2_SAI2B0SEL(regval)       (BITS(24,26) & ((uint32_t)(regval) << 24U))
#define RCU_SAI2BSRC_PLL0Q           CFG2_SAI2B0SEL(0)                              /*!< SAI2 block0/1 select CK_PLL0Q */
#define RCU_SAI2BSRC_PLL1P           CFG2_SAI2B0SEL(1)                              /*!< SAI2 block0/1 select CK_PLL1P */
#define RCU_SAI2BSRC_PLL2P           CFG2_SAI2B0SEL(2)                              /*!< SAI2 block0/1 select CK_PLL2P */
#define RCU_SAI2BSRC_I2S_CKIN        CFG2_SAI2B0SEL(3)                              /*!< SAI2 block0/1 select I2S_CKIN */
#define RCU_SAI2BSRC_PER             CFG2_SAI2B0SEL(4)                              /*!< SAI2 block0/1 select CK_PER */
#define RCU_SAI2BSRC_RSPDIF_SYMB     CFG2_SAI2B0SEL(5)                              /*!< SAI2 block0/1 select CK_RSPDIF_SYMB */

/* HPDF clock source selection */
#define RCU_HPDFSRC_APB2             (uint32_t)(0X00000000U)                        /*!< CK_HPDF select CK_APB2 */
#define RCU_HPDFSRC_AHB              RCU_CFG1_HPDFSEL                               /*!< CK_HPDF select CK_AHB */

/* PER clock selection */
#define CFG1_PERSEL(regval)          (BITS(14,15) & ((uint32_t)(regval) << 14U))
#define RCU_PERSRC_IRC64MDIV         CFG1_PERSEL(0)                                 /*!< CK_PER select CK_IRC64MDIV */
#define RCU_PERSRC_LPIRC4M           CFG1_PERSEL(1)                                 /*!< CK_PER select CK_LPIRC4M */
#define RCU_PERSRC_HXTAL             CFG1_PERSEL(2)                                 /*!< CK_PER select CK_HXTAL */

/* system clock source select */
#define CFG0_SCS(regval)             (BITS(0,1) & ((uint32_t)(regval) << 0U))
#define RCU_CKSYSSRC_IRC64MDIV       CFG0_SCS(0)                                    /*!< system clock source select IRC64MDIV */
#define RCU_CKSYSSRC_HXTAL           CFG0_SCS(1)                                    /*!< system clock source select HXTAL */
#define RCU_CKSYSSRC_LPIRC4M         CFG0_SCS(2)                                    /*!< system clock source select LPIRC4M */
#define RCU_CKSYSSRC_PLL0P           CFG0_SCS(3)                                    /*!< system clock source select PLL0P */

/* system clock source select status */
#define CFG0_SCSS(regval)            (BITS(2,3) & ((uint32_t)(regval) << 2U))
#define RCU_SCSS_IRC64MDIV           CFG0_SCSS(0)                                   /*!< system clock source select CK_IRC64MDIV */
#define RCU_SCSS_HXTAL               CFG0_SCSS(1)                                   /*!< system clock source select CK_HXTAL */
#define RCU_SCSS_LPIRC4M             CFG0_SCSS(2)                                   /*!< system clock source select CK_LPIRC4M */
#define RCU_SCSS_PLL0P               CFG0_SCSS(3)                                   /*!< system clock source select CK_PLL0P */

/* IRC64M clock divider */
#define ADDCTL1_IRC64MDIV(regval)    (BITS(16,17) & ((uint32_t)(regval) << 16U))
#define RCU_IRC64M_DIV1              ADDCTL1_IRC64MDIV(0)                           /*!< CK_IRC64MDIV is CK_IRC64M / 1 */
#define RCU_IRC64M_DIV2              ADDCTL1_IRC64MDIV(1)                           /*!< CK_IRC64MDIV is CK_IRC64M / 2 */
#define RCU_IRC64M_DIV4              ADDCTL1_IRC64MDIV(2)                           /*!< CK_IRC64MDIV is CK_IRC64M / 4 */
#define RCU_IRC64M_DIV8              ADDCTL1_IRC64MDIV(3)                           /*!< CK_IRC64MDIV is CK_IRC64M / 8 */

/* AHB prescaler selection */
#define CFG0_AHBPSC(regval)          (BITS(4,7) & ((uint32_t)(regval) << 4U))
#define RCU_AHB_CKSYS_DIV1           CFG0_AHBPSC(0)                                 /*!< AHB prescaler select CK_SYS */
#define RCU_AHB_CKSYS_DIV2           CFG0_AHBPSC(8)                                 /*!< AHB prescaler select CK_SYS / 2 */
#define RCU_AHB_CKSYS_DIV4           CFG0_AHBPSC(9)                                 /*!< AHB prescaler select CK_SYS / 4 */
#define RCU_AHB_CKSYS_DIV8           CFG0_AHBPSC(10)                                /*!< AHB prescaler select CK_SYS / 8 */
#define RCU_AHB_CKSYS_DIV16          CFG0_AHBPSC(11)                                /*!< AHB prescaler select CK_SYS / 16 */
#define RCU_AHB_CKSYS_DIV64          CFG0_AHBPSC(12)                                /*!< AHB prescaler select CK_SYS / 64 */
#define RCU_AHB_CKSYS_DIV128         CFG0_AHBPSC(13)                                /*!< AHB prescaler select CK_SYS / 128 */
#define RCU_AHB_CKSYS_DIV256         CFG0_AHBPSC(14)                                /*!< AHB prescaler select CK_SYS / 256 */
#define RCU_AHB_CKSYS_DIV512         CFG0_AHBPSC(15)                                /*!< AHB prescaler select CK_SYS / 512 */

/* APB1 prescaler selection */
#define CFG0_APB1PSC(regval)         (BITS(10,12) & ((uint32_t)(regval) << 10U))
#define RCU_APB1_CKAHB_DIV1          CFG0_APB1PSC(0)                                /*!< APB1 prescaler select CK_AHB */
#define RCU_APB1_CKAHB_DIV2          CFG0_APB1PSC(4)                                /*!< APB1 prescaler select CK_AHB / 2 */
#define RCU_APB1_CKAHB_DIV4          CFG0_APB1PSC(5)                                /*!< APB1 prescaler select CK_AHB / 4 */
#define RCU_APB1_CKAHB_DIV8          CFG0_APB1PSC(6)                                /*!< APB1 prescaler select CK_AHB / 8 */
#define RCU_APB1_CKAHB_DIV16         CFG0_APB1PSC(7)                                /*!< APB1 prescaler select CK_AHB / 16 */

/* APB2 prescaler selection */
#define CFG0_APB2PSC(regval)         (BITS(13,15) & ((uint32_t)(regval) << 13U))
#define RCU_APB2_CKAHB_DIV1          CFG0_APB2PSC(0)                                /*!< APB2 prescaler select CK_AHB */
#define RCU_APB2_CKAHB_DIV2          CFG0_APB2PSC(4)                                /*!< APB2 prescaler select CK_AHB / 2 */
#define RCU_APB2_CKAHB_DIV4          CFG0_APB2PSC(5)                                /*!< APB2 prescaler select CK_AHB / 4 */
#define RCU_APB2_CKAHB_DIV8          CFG0_APB2PSC(6)                                /*!< APB2 prescaler select CK_AHB / 8 */
#define RCU_APB2_CKAHB_DIV16         CFG0_APB2PSC(7)                                /*!< APB2 prescaler select CK_AHB / 16 */

/* APB3 prescaler selection */
#define CFG0_APB3PSC(regval)         (BITS(27,29) & ((uint32_t)(regval) << 27U))
#define RCU_APB3_CKAHB_DIV1          CFG0_APB3PSC(0)                                /*!< APB3 prescaler select CK_AHB */
#define RCU_APB3_CKAHB_DIV2          CFG0_APB3PSC(4)                                /*!< APB3 prescaler select CK_AHB / 2 */
#define RCU_APB3_CKAHB_DIV4          CFG0_APB3PSC(5)                                /*!< APB3 prescaler select CK_AHB / 4 */
#define RCU_APB3_CKAHB_DIV8          CFG0_APB3PSC(6)                                /*!< APB3 prescaler select CK_AHB / 8 */
#define RCU_APB3_CKAHB_DIV16         CFG0_APB3PSC(7)                                /*!< APB3 prescaler select CK_AHB / 16 */

/* APB4 prescaler selection */
#define CFG0_APB4PSC(regval)         (BITS(24,26) & ((uint32_t)(regval) << 24U))
#define RCU_APB4_CKAHB_DIV1          CFG0_APB4PSC(0)                                /*!< APB4 prescaler select CK_AHB */
#define RCU_APB4_CKAHB_DIV2          CFG0_APB4PSC(4)                                /*!< APB4 prescaler select CK_AHB / 2 */
#define RCU_APB4_CKAHB_DIV4          CFG0_APB4PSC(5)                                /*!< APB4 prescaler select CK_AHB / 4 */
#define RCU_APB4_CKAHB_DIV8          CFG0_APB4PSC(6)                                /*!< APB4 prescaler select CK_AHB / 8 */
#define RCU_APB4_CKAHB_DIV16         CFG0_APB4PSC(7)                                /*!< APB4 prescaler select CK_AHB / 16 */

/* RTC clock divider factor from HXTAL clock */
#define CFG0_RTCDIV(regval)          (BITS(16,21) & ((uint32_t)(regval) << 16U))
#define RCU_RTC_HXTAL_NONE           CFG0_RTCDIV(0)                                 /*!< no clock for RTC */
#define RCU_RTC_HXTAL_DIV2           CFG0_RTCDIV(2)                                 /*!< RTCDIV clock select CK_HXTAL / 2 */
#define RCU_RTC_HXTAL_DIV3           CFG0_RTCDIV(3)                                 /*!< RTCDIV clock select CK_HXTAL / 3 */
#define RCU_RTC_HXTAL_DIV4           CFG0_RTCDIV(4)                                 /*!< RTCDIV clock select CK_HXTAL / 4 */
#define RCU_RTC_HXTAL_DIV5           CFG0_RTCDIV(5)                                 /*!< RTCDIV clock select CK_HXTAL / 5 */
#define RCU_RTC_HXTAL_DIV6           CFG0_RTCDIV(6)                                 /*!< RTCDIV clock select CK_HXTAL / 6 */
#define RCU_RTC_HXTAL_DIV7           CFG0_RTCDIV(7)                                 /*!< RTCDIV clock select CK_HXTAL / 7 */
#define RCU_RTC_HXTAL_DIV8           CFG0_RTCDIV(8)                                 /*!< RTCDIV clock select CK_HXTAL / 8 */
#define RCU_RTC_HXTAL_DIV9           CFG0_RTCDIV(9)                                 /*!< RTCDIV clock select CK_HXTAL / 9 */
#define RCU_RTC_HXTAL_DIV10          CFG0_RTCDIV(10)                                /*!< RTCDIV clock select CK_HXTAL / 10 */
#define RCU_RTC_HXTAL_DIV11          CFG0_RTCDIV(11)                                /*!< RTCDIV clock select CK_HXTAL / 11 */
#define RCU_RTC_HXTAL_DIV12          CFG0_RTCDIV(12)                                /*!< RTCDIV clock select CK_HXTAL / 12 */
#define RCU_RTC_HXTAL_DIV13          CFG0_RTCDIV(13)                                /*!< RTCDIV clock select CK_HXTAL / 13 */
#define RCU_RTC_HXTAL_DIV14          CFG0_RTCDIV(14)                                /*!< RTCDIV clock select CK_HXTAL / 14 */
#define RCU_RTC_HXTAL_DIV15          CFG0_RTCDIV(15)                                /*!< RTCDIV clock select CK_HXTAL / 15 */
#define RCU_RTC_HXTAL_DIV16          CFG0_RTCDIV(16)                                /*!< RTCDIV clock select CK_HXTAL / 16 */
#define RCU_RTC_HXTAL_DIV17          CFG0_RTCDIV(17)                                /*!< RTCDIV clock select CK_HXTAL / 17 */
#define RCU_RTC_HXTAL_DIV18          CFG0_RTCDIV(18)                                /*!< RTCDIV clock select CK_HXTAL / 18 */
#define RCU_RTC_HXTAL_DIV19          CFG0_RTCDIV(19)                                /*!< RTCDIV clock select CK_HXTAL / 19 */
#define RCU_RTC_HXTAL_DIV20          CFG0_RTCDIV(20)                                /*!< RTCDIV clock select CK_HXTAL / 20 */
#define RCU_RTC_HXTAL_DIV21          CFG0_RTCDIV(21)                                /*!< RTCDIV clock select CK_HXTAL / 21 */
#define RCU_RTC_HXTAL_DIV22          CFG0_RTCDIV(22)                                /*!< RTCDIV clock select CK_HXTAL / 22 */
#define RCU_RTC_HXTAL_DIV23          CFG0_RTCDIV(23)                                /*!< RTCDIV clock select CK_HXTAL / 23 */
#define RCU_RTC_HXTAL_DIV24          CFG0_RTCDIV(24)                                /*!< RTCDIV clock select CK_HXTAL / 24 */
#define RCU_RTC_HXTAL_DIV25          CFG0_RTCDIV(25)                                /*!< RTCDIV clock select CK_HXTAL / 25 */
#define RCU_RTC_HXTAL_DIV26          CFG0_RTCDIV(26)                                /*!< RTCDIV clock select CK_HXTAL / 26 */
#define RCU_RTC_HXTAL_DIV27          CFG0_RTCDIV(27)                                /*!< RTCDIV clock select CK_HXTAL / 27 */
#define RCU_RTC_HXTAL_DIV28          CFG0_RTCDIV(28)                                /*!< RTCDIV clock select CK_HXTAL / 28 */
#define RCU_RTC_HXTAL_DIV29          CFG0_RTCDIV(29)                                /*!< RTCDIV clock select CK_HXTAL / 29 */
#define RCU_RTC_HXTAL_DIV30          CFG0_RTCDIV(30)                                /*!< RTCDIV clock select CK_HXTAL / 30 */
#define RCU_RTC_HXTAL_DIV31          CFG0_RTCDIV(31)                                /*!< RTCDIV clock select CK_HXTAL / 31 */
#define RCU_RTC_HXTAL_DIV32          CFG0_RTCDIV(32)                                /*!< RTCDIV clock select CK_HXTAL / 32 */
#define RCU_RTC_HXTAL_DIV33          CFG0_RTCDIV(33)                                /*!< RTCDIV clock select CK_HXTAL / 33 */
#define RCU_RTC_HXTAL_DIV34          CFG0_RTCDIV(34)                                /*!< RTCDIV clock select CK_HXTAL / 34 */
#define RCU_RTC_HXTAL_DIV35          CFG0_RTCDIV(35)                                /*!< RTCDIV clock select CK_HXTAL / 35 */
#define RCU_RTC_HXTAL_DIV36          CFG0_RTCDIV(36)                                /*!< RTCDIV clock select CK_HXTAL / 36 */
#define RCU_RTC_HXTAL_DIV37          CFG0_RTCDIV(37)                                /*!< RTCDIV clock select CK_HXTAL / 37 */
#define RCU_RTC_HXTAL_DIV38          CFG0_RTCDIV(38)                                /*!< RTCDIV clock select CK_HXTAL / 38 */
#define RCU_RTC_HXTAL_DIV39          CFG0_RTCDIV(39)                                /*!< RTCDIV clock select CK_HXTAL / 39 */
#define RCU_RTC_HXTAL_DIV40          CFG0_RTCDIV(40)                                /*!< RTCDIV clock select CK_HXTAL / 40 */
#define RCU_RTC_HXTAL_DIV41          CFG0_RTCDIV(41)                                /*!< RTCDIV clock select CK_HXTAL / 41 */
#define RCU_RTC_HXTAL_DIV42          CFG0_RTCDIV(42)                                /*!< RTCDIV clock select CK_HXTAL / 42 */
#define RCU_RTC_HXTAL_DIV43          CFG0_RTCDIV(43)                                /*!< RTCDIV clock select CK_HXTAL / 43 */
#define RCU_RTC_HXTAL_DIV44          CFG0_RTCDIV(44)                                /*!< RTCDIV clock select CK_HXTAL / 44 */
#define RCU_RTC_HXTAL_DIV45          CFG0_RTCDIV(45)                                /*!< RTCDIV clock select CK_HXTAL / 45 */
#define RCU_RTC_HXTAL_DIV46          CFG0_RTCDIV(46)                                /*!< RTCDIV clock select CK_HXTAL / 46 */
#define RCU_RTC_HXTAL_DIV47          CFG0_RTCDIV(47)                                /*!< RTCDIV clock select CK_HXTAL / 47 */
#define RCU_RTC_HXTAL_DIV48          CFG0_RTCDIV(48)                                /*!< RTCDIV clock select CK_HXTAL / 48 */
#define RCU_RTC_HXTAL_DIV49          CFG0_RTCDIV(49)                                /*!< RTCDIV clock select CK_HXTAL / 49 */
#define RCU_RTC_HXTAL_DIV50          CFG0_RTCDIV(50)                                /*!< RTCDIV clock select CK_HXTAL / 50 */
#define RCU_RTC_HXTAL_DIV51          CFG0_RTCDIV(51)                                /*!< RTCDIV clock select CK_HXTAL / 51 */
#define RCU_RTC_HXTAL_DIV52          CFG0_RTCDIV(52)                                /*!< RTCDIV clock select CK_HXTAL / 52 */
#define RCU_RTC_HXTAL_DIV53          CFG0_RTCDIV(53)                                /*!< RTCDIV clock select CK_HXTAL / 53 */
#define RCU_RTC_HXTAL_DIV54          CFG0_RTCDIV(54)                                /*!< RTCDIV clock select CK_HXTAL / 54 */
#define RCU_RTC_HXTAL_DIV55          CFG0_RTCDIV(55)                                /*!< RTCDIV clock select CK_HXTAL / 55 */
#define RCU_RTC_HXTAL_DIV56          CFG0_RTCDIV(56)                                /*!< RTCDIV clock select CK_HXTAL / 56 */
#define RCU_RTC_HXTAL_DIV57          CFG0_RTCDIV(57)                                /*!< RTCDIV clock select CK_HXTAL / 57 */
#define RCU_RTC_HXTAL_DIV58          CFG0_RTCDIV(58)                                /*!< RTCDIV clock select CK_HXTAL / 58 */
#define RCU_RTC_HXTAL_DIV59          CFG0_RTCDIV(59)                                /*!< RTCDIV clock select CK_HXTAL / 59 */
#define RCU_RTC_HXTAL_DIV60          CFG0_RTCDIV(60)                                /*!< RTCDIV clock select CK_HXTAL / 60 */
#define RCU_RTC_HXTAL_DIV61          CFG0_RTCDIV(61)                                /*!< RTCDIV clock select CK_HXTAL / 61 */
#define RCU_RTC_HXTAL_DIV62          CFG0_RTCDIV(62)                                /*!< RTCDIV clock select CK_HXTAL / 62 */
#define RCU_RTC_HXTAL_DIV63          CFG0_RTCDIV(63)                                /*!< RTCDIV clock select CK_HXTAL / 63 */

/* The CK_OUT0 divider */
#define CFG2_CKOUT0DIV(regval)       (BITS(0,3) & ((uint32_t)(regval) << 0U))
#define RCU_CKOUT0_DIV1              CFG2_CKOUT0DIV(1)                              /*!< CK_OUT0 is divided by 1 */
#define RCU_CKOUT0_DIV2              CFG2_CKOUT0DIV(2)                              /*!< CK_OUT0 is divided by 2 */
#define RCU_CKOUT0_DIV3              CFG2_CKOUT0DIV(3)                              /*!< CK_OUT0 is divided by 3 */
#define RCU_CKOUT0_DIV4              CFG2_CKOUT0DIV(4)                              /*!< CK_OUT0 is divided by 4 */
#define RCU_CKOUT0_DIV5              CFG2_CKOUT0DIV(5)                              /*!< CK_OUT0 is divided by 5 */
#define RCU_CKOUT0_DIV6              CFG2_CKOUT0DIV(6)                              /*!< CK_OUT0 is divided by 6 */
#define RCU_CKOUT0_DIV7              CFG2_CKOUT0DIV(7)                              /*!< CK_OUT0 is divided by 7 */
#define RCU_CKOUT0_DIV8              CFG2_CKOUT0DIV(8)                              /*!< CK_OUT0 is divided by 8 */
#define RCU_CKOUT0_DIV9              CFG2_CKOUT0DIV(9)                              /*!< CK_OUT0 is divided by 9 */
#define RCU_CKOUT0_DIV10             CFG2_CKOUT0DIV(10)                             /*!< CK_OUT0 is divided by 10 */
#define RCU_CKOUT0_DIV11             CFG2_CKOUT0DIV(11)                             /*!< CK_OUT0 is divided by 11 */
#define RCU_CKOUT0_DIV12             CFG2_CKOUT0DIV(12)                             /*!< CK_OUT0 is divided by 12 */
#define RCU_CKOUT0_DIV13             CFG2_CKOUT0DIV(13)                             /*!< CK_OUT0 is divided by 13 */
#define RCU_CKOUT0_DIV14             CFG2_CKOUT0DIV(14)                             /*!< CK_OUT0 is divided by 14 */
#define RCU_CKOUT0_DIV15             CFG2_CKOUT0DIV(15)                             /*!< CK_OUT0 is divided by 15 */

/* CKOUT0 Clock source selection */
#define CFG2_CKOUT0SEL(regval)       (BITS(4,6) & ((uint32_t)(regval) << 4U))
#define RCU_CKOUT0SRC_IRC64MDIV      CFG2_CKOUT0SEL(0)                              /*!< internal 64MDIV RC oscillator clock selected */
#define RCU_CKOUT0SRC_LXTAL          CFG2_CKOUT0SEL(1)                              /*!< low speed crystal oscillator clock (LXTAL) selected */
#define RCU_CKOUT0SRC_HXTAL          CFG2_CKOUT0SEL(2)                              /*!< high speed crystal oscillator clock (HXTAL) selected */
#define RCU_CKOUT0SRC_PLL0P          CFG2_CKOUT0SEL(3)                              /*!< CK_PLL0P clock selected */
#define RCU_CKOUT0SRC_IRC48M         CFG2_CKOUT0SEL(4)                              /*!< CK_IRC48M clock selected */
#define RCU_CKOUT0SRC_PER            CFG2_CKOUT0SEL(5)                              /*!< CK_PER clock selected */
#define RCU_CKOUT0SRC_USBHS060M      CFG2_CKOUT0SEL(6)                              /*!< USBHS0 60M clock selected */
#define RCU_CKOUT0SRC_USBHS160M      CFG2_CKOUT0SEL(7)                              /*!< USBHS1 60M clock selected */

/* The CK_OUT1 divider */
#define CFG2_CKOUT1DIV(regval)       (BITS(8,11) & ((uint32_t)(regval) << 8U))
#define RCU_CKOUT1_DIV1              CFG2_CKOUT1DIV(1)                              /*!< CK_OUT1 is divided by 1 */
#define RCU_CKOUT1_DIV2              CFG2_CKOUT1DIV(2)                              /*!< CK_OUT1 is divided by 2 */
#define RCU_CKOUT1_DIV3              CFG2_CKOUT1DIV(3)                              /*!< CK_OUT1 is divided by 3 */
#define RCU_CKOUT1_DIV4              CFG2_CKOUT1DIV(4)                              /*!< CK_OUT1 is divided by 4 */
#define RCU_CKOUT1_DIV5              CFG2_CKOUT1DIV(5)                              /*!< CK_OUT1 is divided by 5 */
#define RCU_CKOUT1_DIV6              CFG2_CKOUT1DIV(6)                              /*!< CK_OUT1 is divided by 6 */
#define RCU_CKOUT1_DIV7              CFG2_CKOUT1DIV(7)                              /*!< CK_OUT1 is divided by 7 */
#define RCU_CKOUT1_DIV8              CFG2_CKOUT1DIV(8)                              /*!< CK_OUT1 is divided by 8 */
#define RCU_CKOUT1_DIV9              CFG2_CKOUT1DIV(9)                              /*!< CK_OUT1 is divided by 9 */
#define RCU_CKOUT1_DIV10             CFG2_CKOUT1DIV(10)                             /*!< CK_OUT1 is divided by 10 */
#define RCU_CKOUT1_DIV11             CFG2_CKOUT1DIV(11)                             /*!< CK_OUT1 is divided by 11 */
#define RCU_CKOUT1_DIV12             CFG2_CKOUT1DIV(12)                             /*!< CK_OUT1 is divided by 12 */
#define RCU_CKOUT1_DIV13             CFG2_CKOUT1DIV(13)                             /*!< CK_OUT1 is divided by 13 */
#define RCU_CKOUT1_DIV14             CFG2_CKOUT1DIV(14)                             /*!< CK_OUT1 is divided by 14 */
#define RCU_CKOUT1_DIV15             CFG2_CKOUT1DIV(15)                             /*!< CK_OUT1 is divided by 15 */

/* CKOUT1 Clock source selection */
#define CFG2_CKOUT1SEL(regval)       (BITS(12,14) & ((uint32_t)(regval) << 12U))
#define RCU_CKOUT1SRC_SYSTEMCLOCK    CFG2_CKOUT1SEL(0)                              /*!< system clock selected */
#define RCU_CKOUT1SRC_PLL1R          CFG2_CKOUT1SEL(1)                              /*!< CK_PLL1R clock selected */
#define RCU_CKOUT1SRC_HXTAL          CFG2_CKOUT1SEL(2)                              /*!< high speed crystal oscillator clock (HXTAL) selected */
#define RCU_CKOUT1SRC_PLL0P          CFG2_CKOUT1SEL(3)                              /*!< CK_PLL0P clock selected */
#define RCU_CKOUT1SRC_LPIRC4M        CFG2_CKOUT1SEL(4)                              /*!< CK_LPIRC4M clock selected */
#define RCU_CKOUT1SRC_IRC32K         CFG2_CKOUT1SEL(5)                              /*!< CK_IRC32K clock selected */
#define RCU_CKOUT1SRC_PLL2R          CFG2_CKOUT1SEL(6)                              /*!< CK_PLL2R clock selected */

/* the divider factor from PLL2R clock */
#define CFG1_PLL2RDIV(regval)        (BITS(16,17) & ((uint32_t)(regval) << 16U))
#define RCU_PLL2R_DIV2               CFG1_PLL2RDIV(0)                               /*!< CK_PLL2RDIV clock select CK_PLL2R / 2 */
#define RCU_PLL2R_DIV4               CFG1_PLL2RDIV(1)                               /*!< CK_PLL2RDIV clock select CK_PLL2R / 4 */
#define RCU_PLL2R_DIV8               CFG1_PLL2RDIV(2)                               /*!< CK_PLL2RDIV clock select CK_PLL2R / 8 */
#define RCU_PLL2R_DIV16              CFG1_PLL2RDIV(3)                               /*!< CK_PLL2RDIV clock select CK_PLL2R / 16 */

/* TIMER clock selection */
#define RCU_TIMER_PSC_MUL2           ((uint32_t)(~RCU_CFG1_TIMERSEL))               /*!< if APB1PSC/APB2PSC in RCU_CFG0 register is 0b0xx(CK_APBx = CK_AHB)
                                                                                            or 0b100(CK_APBx = CK_AHB/2), the TIMER clock is equal to CK_AHB(CK_TIMERx = CK_AHB).
                                                                                            or else, the TIMER clock is twice the corresponding APB clock (TIMER in APB1 domain: CK_TIMERx = 2 x CK_APB1;
                                                                                            TIMER in APB2 domain: CK_TIMERx = 2 x CK_APB2) */
#define RCU_TIMER_PSC_MUL4           RCU_CFG1_TIMERSEL                              /*!< if APB1PSC/APB2PSC in RCU_CFG0 register is 0b0xx(CK_APBx = CK_AHB),
                                                                                            0b100(CK_APBx = CK_AHB/2), or 0b101(CK_APBx = CK_AHB/4), the TIMER clock is equal to CK_AHB(CK_TIMERx = CK_AHB).
                                                                                            or else, the TIMER clock is four timers the corresponding APB clock (TIMER in APB1 domain: CK_TIMERx = 4 x CK_APB1;
                                                                                            TIMER in APB2 domain: CK_TIMERx = 4 x CK_APB2) */

/* RCU_PLL0 register bit define */
/* The PLL0 VCO source clock prescaler */
#define RCU_PLL0PSC_DIV_MIN          ((uint32_t)1U)                                 /*!< PLL0PSC_DIV min value */
#define RCU_PLL0PSC_DIV_MAX          ((uint32_t)63U)                                /*!< PLL0PSC_DIV max value */

/* The PLL0 VCO clock multiplication factor */
#define RCU_PLL0N_MUL_MIN            ((uint32_t)9U)                                 /*!< PLL0N_MUL min value */
#define RCU_PLL0N_MUL_MAX            ((uint32_t)512U)                               /*!< PLL0N_MUL max value */

/* The PLL0P output frequency division factor from PLL0 VCO clock */
#define RCU_PLL0P_DIV_MIN            ((uint32_t)1U)                                 /*!< PLL0P_DIV min value */
#define RCU_PLL0P_DIV_MAX            ((uint32_t)128U)                               /*!< PLL0P_DIV max value */

/* The PLL0R output frequency division factor from PLL0 VCO clock */
#define RCU_PLL0R_DIV_MIN            ((uint32_t)1U)                                 /*!< PLL0R_DIV min value */
#define RCU_PLL0R_DIV_MAX            ((uint32_t)128U)                               /*!< PLL0R_DIV max value */

/* The PLL0Q output frequency division factor from PLL0 VCO clock */
#define RCU_PLL0Q_DIV_MIN            ((uint32_t)1U)                                 /*!< PLL0Q_DIV min value */
#define RCU_PLL0Q_DIV_MAX            ((uint32_t)128U)                               /*!< PLL0Q_DIV max value */

/* PLL Clock Source Selection  */
#define PLLALL_PLLSEL(regval)        (BITS(16,17) & ((uint32_t)(regval) << 16U))
#define RCU_PLLSRC_IRC64MDIV         PLLALL_PLLSEL(0)                               /*!< IRC64MDIV clock selected as source clock of PLL0, PLL1, PLL2 */
#define RCU_PLLSRC_LPIRC4M           PLLALL_PLLSEL(1)                               /*!< LPIRC4M  clock selected as source clock of PLL0, PLL1, PLL2 */
#define RCU_PLLSRC_HXTAL             PLLALL_PLLSEL(2)                               /*!< HXTAL clock selected as source clock of PLL0, PLL1, PLL2 */

#define CHECK_PLL0_PSC_VALID(val)    (((val) >= RCU_PLL0PSC_DIV_MIN) && ((val) <= RCU_PLL0PSC_DIV_MAX))
#define CHECK_PLL0_N_VALID(val)      (((val) >= RCU_PLL0N_MUL_MIN) && ((val) <= RCU_PLL0N_MUL_MAX))
#define CHECK_PLL0_P_VALID(val)      (((val) >= RCU_PLL0P_DIV_MIN) && ((val) <= RCU_PLL0P_DIV_MAX))
#define CHECK_PLL0_Q_VALID(val)      (((val) >= RCU_PLL0Q_DIV_MIN) && ((val) <= RCU_PLL0Q_DIV_MAX))
#define CHECK_PLL0_R_VALID(val)      (((val) >= RCU_PLL0R_DIV_MIN) && ((val) <= RCU_PLL0R_DIV_MAX))

/* RCU_BDCTL register bit define */
/* LXTAL drive capability */
#define BDCTL_LXTALDRI(regval)       (BITS(3,4) & ((uint32_t)(regval) << 3U))
#define RCU_LXTAL_LOWDRI             BDCTL_LXTALDRI(0)                              /*!< lower driving capability */
#define RCU_LXTAL_MED_LOWDRI         BDCTL_LXTALDRI(1)                              /*!< medium low driving capability */
#define RCU_LXTAL_MED_HIGHDRI        BDCTL_LXTALDRI(2)                              /*!< medium high driving capability */
#define RCU_LXTAL_HIGHDRI            BDCTL_LXTALDRI(3)                              /*!< higher driving capability */

/* RTC clock entry selection */
#define BDCTL_RTCSRC(regval)         (BITS(8,9) & ((uint32_t)(regval) << 8U))
#define RCU_RTCSRC_NONE              BDCTL_RTCSRC(0)                                /*!< no clock selected */
#define RCU_RTCSRC_LXTAL             BDCTL_RTCSRC(1)                                /*!< RTC source clock select LXTAL  */
#define RCU_RTCSRC_IRC32K            BDCTL_RTCSRC(2)                                /*!< RTC source clock select IRC32K */
#define RCU_RTCSRC_HXTAL_DIV_RTCDIV  BDCTL_RTCSRC(3)                                /*!< RTC source clock select HXTAL/RTCDIV */

/* RCU_PLL1 register bit define */
/* The PLL1 VCO source clock prescaler */
#define RCU_PLL1PSC_DIV_MIN          ((uint32_t)1U)                                 /*!< PLL1PSC_DIV min value */
#define RCU_PLL1PSC_DIV_MAX          ((uint32_t)63U)                                /*!< PLL1PSC_DIV max value */

/* The PLL1 VCO clock multiplication factor */
#define RCU_PLL1N_MUL_MIN            ((uint32_t)9U)                                 /*!< PLL1N_MUL min value */
#define RCU_PLL1N_MUL_MAX            ((uint32_t)512U)                               /*!< PLL1N_MUL max value */

/* The PLL1P output frequency division factor from PLL1 VCO clock */
#define RCU_PLL1P_DIV_MIN            ((uint32_t)1U)                                 /*!< PLL1P_DIV min value */
#define RCU_PLL1P_DIV_MAX            ((uint32_t)128U)                               /*!< PLL1P_DIV max value */

/* The PLL1Q output frequency division factor from PLL1 VCO clock */
#define RCU_PLL1Q_DIV_MIN            ((uint32_t)1U)                                 /*!< PLL1Q_DIV min value */
#define RCU_PLL1Q_DIV_MAX            ((uint32_t)128U)                               /*!< PLL1Q_DIV max value */

/* The PLL1R output frequency division factor from PLL1 VCO clock */
#define RCU_PLL1R_DIV_MIN            ((uint32_t)1U)                                 /*!< PLL1R_DIV min value */
#define RCU_PLL1R_DIV_MAX            ((uint32_t)128U)                               /*!< PLL1R_DIV max value */

/* RCU_PLL2 register bit define */
/* The PLL2 VCO source clock prescaler */
#define RCU_PLL2PSC_DIV_MIN          ((uint32_t)1U)                                 /*!< PLL2PSC_DIV min value */
#define RCU_PLL2PSC_DIV_MAX          ((uint32_t)63U)                                /*!< PLL2PSC_DIV max value */

/* The PLL2 VCO clock multi factor */
#define RCU_PLL2N_MUL_MIN            ((uint32_t)9U)                                 /*!< PLL2N_MUL min value */
#define RCU_PLL2N_MUL_MAX            ((uint32_t)512U)                               /*!< PLL2N_MUL max value */

/* The PLL2P output frequency division factor from PLL2 VCO clock */
#define RCU_PLL2P_DIV_MIN            ((uint32_t)1U)                                 /*!< PLL2P_DIV min value */
#define RCU_PLL2P_DIV_MAX            ((uint32_t)128U)                               /*!< PLL2P_DIV max value */

/* The PLL2Q output frequency division factor from PLL2 VCO clock */
#define RCU_PLL2Q_DIV_MIN            ((uint32_t)1U)                                 /*!< PLL2Q_DIV min value */
#define RCU_PLL2Q_DIV_MAX            ((uint32_t)128U)                               /*!< PLL2Q_DIV max value */

/* The PLL2R output frequency division factor from PLL2 VCO clock */
#define RCU_PLL2R_DIV_MIN            ((uint32_t)1U)                                 /*!< PLL2R_DIV min value */
#define RCU_PLL2R_DIV_MAX            ((uint32_t)128U)                               /*!< PLL2R_DIV max value */

#define CHECK_PLL1_PSC_VALID(val)    (((val) >= RCU_PLL1PSC_DIV_MIN) && ((val) <= RCU_PLL1PSC_DIV_MAX))
#define CHECK_PLL1_N_VALID(val)      (((val) >= RCU_PLL1N_MUL_MIN) && ((val) <= RCU_PLL1N_MUL_MAX))
#define CHECK_PLL1_P_VALID(val)      (((val) >= RCU_PLL1P_DIV_MIN) && ((val) <= RCU_PLL1P_DIV_MAX))
#define CHECK_PLL1_Q_VALID(val)      (((val) >= RCU_PLL1Q_DIV_MIN) && ((val) <= RCU_PLL1Q_DIV_MAX))
#define CHECK_PLL1_R_VALID(val)      (((val) >= RCU_PLL1R_DIV_MIN) && ((val) <= RCU_PLL1R_DIV_MAX))

#define CHECK_PLL2_PSC_VALID(val)    (((val) >= RCU_PLL2PSC_DIV_MIN) && ((val) <= RCU_PLL2PSC_DIV_MAX))
#define CHECK_PLL2_N_VALID(val)      (((val) >= (RCU_PLL2N_MUL_MIN)) && ((val) <= RCU_PLL2N_MUL_MAX))
#define CHECK_PLL2_P_VALID(val)      (((val) >= RCU_PLL2P_DIV_MIN) && ((val) <= RCU_PLL2P_DIV_MAX))
#define CHECK_PLL2_Q_VALID(val)      (((val) >= RCU_PLL2Q_DIV_MIN) && ((val) <= RCU_PLL2Q_DIV_MAX))
#define CHECK_PLL2_R_VALID(val)      (((val) >= RCU_PLL2R_DIV_MIN) && ((val) <= RCU_PLL2R_DIV_MAX))

/* PLL0 input clock range */
#define PLLALL_PLL0RNG(regval)        (BITS(0,1) & ((uint32_t)(regval) << 0U))
#define RCU_PLL0RNG_1M_2M             PLLALL_PLL0RNG(0)                             /*!< PLL0 input clock frequency: 1-2MHz */
#define RCU_PLL0RNG_2M_4M             PLLALL_PLL0RNG(1)                             /*!< PLL0 input clock frequency: 2-4MHz */
#define RCU_PLL0RNG_4M_8M             PLLALL_PLL0RNG(2)                             /*!< PLL0 input clock frequency: 4-8MHz */
#define RCU_PLL0RNG_8M_16M            PLLALL_PLL0RNG(3)                             /*!< PLL0 input clock frequency: 8-16MHz */

/* PLL1 input clock range */
#define PLLALL_PLL1RNG(regval)       (BITS(4,5) & ((uint32_t)(regval) << 4U))
#define RCU_PLL1RNG_1M_2M            PLLALL_PLL1RNG(0)                              /*!< PLL1 input clock frequency: 1-2MHz */
#define RCU_PLL1RNG_2M_4M            PLLALL_PLL1RNG(1)                              /*!< PLL1 input clock frequency: 2-4MHz */
#define RCU_PLL1RNG_4M_8M            PLLALL_PLL1RNG(2)                              /*!< PLL1 input clock frequency: 4-8MHz */
#define RCU_PLL1RNG_8M_16M           PLLALL_PLL1RNG(3)                              /*!< PLL1 input clock frequency: 8-16MHz */

/* PLL2 input clock range */
#define PLLALL_PLL2RNG(regval)       (BITS(8,9) & ((uint32_t)(regval) << 8U))
#define RCU_PLL2RNG_1M_2M            PLLALL_PLL2RNG(0)                              /*!< PLL2 input clock frequency: 1-2MHz */
#define RCU_PLL2RNG_2M_4M            PLLALL_PLL2RNG(1)                              /*!< PLL2 input clock frequency: 2-4MHz */
#define RCU_PLL2RNG_4M_8M            PLLALL_PLL2RNG(2)                              /*!< PLL2 input clock frequency: 4-8MHz */
#define RCU_PLL2RNG_8M_16M           PLLALL_PLL2RNG(3)                              /*!< PLL2 input clock frequency: 8-16MHz */

/* PLL0 VCO selection */
#define RCU_PLL0VCO_192M_836M        ((uint32_t)0x00000000U)                        /*!< PLL0 select wide VCO, range: 192-836MHz */
#define RCU_PLL0VCO_150M_420M        RCU_PLLALL_PLL0VCOSEL                          /*!< PLL0 select narrow VCO, range: 150-420MHz */

/* PLL1 VCO selection */
#define RCU_PLL1VCO_192M_836M        ((uint32_t)0x00000000U)                        /*!< PLL1 select wide VCO, range: 192-836MHz */
#define RCU_PLL1VCO_150M_420M        RCU_PLLALL_PLL1VCOSEL                          /*!< PLL1 select narrow VCO, range: 150-420MHz */

/* PLL2 VCO selection */
#define RCU_PLL2VCO_192M_836M        ((uint32_t)0x00000000U)                        /*!< PLL2 select wide VCO, range: 192-836MHz */
#define RCU_PLL2VCO_150M_420M        RCU_PLLALL_PLL2VCOSEL                          /*!< PLL2 select narrow VCO, range: 150-420MHz */

/* RCU_ADDCTL0 register bit define */
/* 48MHz clock selection */
#define RCU_CK48MSRC_PLL48M          ((uint32_t)0x00000000U)                        /*!< CK48M source clock select PLL48M */
#define RCU_CK48MSRC_IRC48M          RCU_ADDCTL0_CK48MSEL                           /*!< CK48M source clock select IRC48M */

/* PLL48M clock selection */
#define RCU_PLL48MSRC_PLL0Q           ((uint32_t)0x00000000U)                       /*!< PLL48M source clock select PLL0Q */
#define RCU_PLL48MSRC_PLL2P          RCU_ADDCTL0_PLL48MSEL                          /*!< PLL48M source clock select PLL2P */

/* USBHS clock selection */
#define RCU_USBHSSEL_48M             ((uint32_t)0x00000000U)                        /*!< 48M selected as USBHS source clock */
#define RCU_USBHSSEL_60M             RCU_USBCLKCTL_USBHS0SEL                        /*!< 60M selected as USBHS source clock */

/* PLLUSBHSPRE clock selection */
#define RCU_PLLUSBHSPRE_HXTAL        ((uint32_t)0x00000000U)                        /*!< CK_HATAL selected as PLLUSBHS source clock */
#define RCU_PLLUSBHSPRE_IRC48M       RCU_USBCLKCTL_PLLUSBHS0PRESEL                  /*!< CK_IRC48M selected as PLLUSBHS source clock */

/* PLLUSBHSPREDV division factor */
#define PLLUSBCFG_PLLUSBHSPREDV(regval)   (BITS(0,3) & ((uint32_t)(regval) << 0U))
#define RCU_PLLUSBHSPRE_DIV1              PLLUSBCFG_PLLUSBHSPREDV(1)                /*!< PLLUSBHSPREDV input source clock divided by 1 */
#define RCU_PLLUSBHSPRE_DIV2              PLLUSBCFG_PLLUSBHSPREDV(2)                /*!< PLLUSBHSPREDV input source clock divided by 2 */
#define RCU_PLLUSBHSPRE_DIV3              PLLUSBCFG_PLLUSBHSPREDV(3)                /*!< PLLUSBHSPREDV input source clock divided by 3 */
#define RCU_PLLUSBHSPRE_DIV4              PLLUSBCFG_PLLUSBHSPREDV(4)                /*!< PLLUSBHSPREDV input source clock divided by 4 */
#define RCU_PLLUSBHSPRE_DIV5              PLLUSBCFG_PLLUSBHSPREDV(5)                /*!< PLLUSBHSPREDV input source clock divided by 5 */
#define RCU_PLLUSBHSPRE_DIV6              PLLUSBCFG_PLLUSBHSPREDV(6)                /*!< PLLUSBHSPREDV input source clock divided by 6 */
#define RCU_PLLUSBHSPRE_DIV7              PLLUSBCFG_PLLUSBHSPREDV(7)                /*!< PLLUSBHSPREDV input source clock divided by 7 */
#define RCU_PLLUSBHSPRE_DIV8              PLLUSBCFG_PLLUSBHSPREDV(8)                /*!< PLLUSBHSPREDV input source clock divided by 8 */
#define RCU_PLLUSBHSPRE_DIV9              PLLUSBCFG_PLLUSBHSPREDV(9)                /*!< PLLUSBHSPREDV input source clock divided by 9 */
#define RCU_PLLUSBHSPRE_DIV10             PLLUSBCFG_PLLUSBHSPREDV(10)               /*!< PLLUSBHSPREDV input source clock divided by 10 */
#define RCU_PLLUSBHSPRE_DIV11             PLLUSBCFG_PLLUSBHSPREDV(11)               /*!< PLLUSBHSPREDV input source clock divided by 11 */
#define RCU_PLLUSBHSPRE_DIV12             PLLUSBCFG_PLLUSBHSPREDV(12)               /*!< PLLUSBHSPREDV input source clock divided by 12 */
#define RCU_PLLUSBHSPRE_DIV13             PLLUSBCFG_PLLUSBHSPREDV(13)               /*!< PLLUSBHSPREDV input source clock divided by 13 */
#define RCU_PLLUSBHSPRE_DIV14             PLLUSBCFG_PLLUSBHSPREDV(14)               /*!< PLLUSBHSPREDV input source clock divided by 14 */
#define RCU_PLLUSBHSPRE_DIV15             PLLUSBCFG_PLLUSBHSPREDV(15)               /*!< PLLUSBHSPREDV input source clock divided by 15 */

/* USBHSDV division factor */
#define PLLUSBCFG_USBHSDV(regval)         (BITS(4,6) & ((uint32_t)(regval) << 4U))
#define RCU_USBHS_DIV2                    PLLUSBCFG_USBHSDV(0)                      /*!< USBHSDV input source clock divided by 2 */
#define RCU_USBHS_DIV4                    PLLUSBCFG_USBHSDV(1)                      /*!< USBHSDV input source clock divided by 4 */
#define RCU_USBHS_DIV6                    PLLUSBCFG_USBHSDV(2)                      /*!< USBHSDV input source clock divided by 6 */
#define RCU_USBHS_DIV8                    PLLUSBCFG_USBHSDV(3)                      /*!< USBHSDV input source clock divided by 8 */
#define RCU_USBHS_DIV10                   PLLUSBCFG_USBHSDV(4)                      /*!< USBHSDV input source clock divided by 10 */
#define RCU_USBHS_DIV12                   PLLUSBCFG_USBHSDV(5)                      /*!< USBHSDV input source clock divided by 12 */
#define RCU_USBHS_DIV14                   PLLUSBCFG_USBHSDV(6)                      /*!< USBHSDV input source clock divided by 14 */
#define RCU_USBHS_DIV16                   PLLUSBCFG_USBHSDV(7)                      /*!< USBHSDV input source clock divided by 16 */

/* PLLUSB clock multiplication factor */
#define PLLUSBCFG_PLLUSBHSMF(regval)      (BITS(8,14) & ((uint32_t)(regval) << 8U))
#define RCU_PLLUSBHS_MUL16                PLLUSBCFG_PLLUSBHSMF(16)                  /*!< PLLUSBHS source clock multiply by 16 */
#define RCU_PLLUSBHS_MUL17                PLLUSBCFG_PLLUSBHSMF(17)                  /*!< PLLUSBHS source clock multiply by 17 */
#define RCU_PLLUSBHS_MUL18                PLLUSBCFG_PLLUSBHSMF(18)                  /*!< PLLUSBHS source clock multiply by 18 */
#define RCU_PLLUSBHS_MUL19                PLLUSBCFG_PLLUSBHSMF(19)                  /*!< PLLUSBHS source clock multiply by 19 */
#define RCU_PLLUSBHS_MUL20                PLLUSBCFG_PLLUSBHSMF(20)                  /*!< PLLUSBHS source clock multiply by 20 */
#define RCU_PLLUSBHS_MUL21                PLLUSBCFG_PLLUSBHSMF(21)                  /*!< PLLUSBHS source clock multiply by 21 */
#define RCU_PLLUSBHS_MUL22                PLLUSBCFG_PLLUSBHSMF(22)                  /*!< PLLUSBHS source clock multiply by 22 */
#define RCU_PLLUSBHS_MUL23                PLLUSBCFG_PLLUSBHSMF(23)                  /*!< PLLUSBHS source clock multiply by 23 */
#define RCU_PLLUSBHS_MUL24                PLLUSBCFG_PLLUSBHSMF(24)                  /*!< PLLUSBHS source clock multiply by 24 */
#define RCU_PLLUSBHS_MUL25                PLLUSBCFG_PLLUSBHSMF(25)                  /*!< PLLUSBHS source clock multiply by 25 */
#define RCU_PLLUSBHS_MUL26                PLLUSBCFG_PLLUSBHSMF(26)                  /*!< PLLUSBHS source clock multiply by 26 */
#define RCU_PLLUSBHS_MUL27                PLLUSBCFG_PLLUSBHSMF(27)                  /*!< PLLUSBHS source clock multiply by 27 */
#define RCU_PLLUSBHS_MUL28                PLLUSBCFG_PLLUSBHSMF(28)                  /*!< PLLUSBHS source clock multiply by 28 */
#define RCU_PLLUSBHS_MUL29                PLLUSBCFG_PLLUSBHSMF(29)                  /*!< PLLUSBHS source clock multiply by 29 */
#define RCU_PLLUSBHS_MUL30                PLLUSBCFG_PLLUSBHSMF(30)                  /*!< PLLUSBHS source clock multiply by 30 */
#define RCU_PLLUSBHS_MUL31                PLLUSBCFG_PLLUSBHSMF(31)                  /*!< PLLUSBHS source clock multiply by 31 */
#define RCU_PLLUSBHS_MUL32                PLLUSBCFG_PLLUSBHSMF(32)                  /*!< PLLUSBHS source clock multiply by 32 */
#define RCU_PLLUSBHS_MUL33                PLLUSBCFG_PLLUSBHSMF(33)                  /*!< PLLUSBHS source clock multiply by 33 */
#define RCU_PLLUSBHS_MUL34                PLLUSBCFG_PLLUSBHSMF(34)                  /*!< PLLUSBHS source clock multiply by 34 */
#define RCU_PLLUSBHS_MUL35                PLLUSBCFG_PLLUSBHSMF(35)                  /*!< PLLUSBHS source clock multiply by 35 */
#define RCU_PLLUSBHS_MUL36                PLLUSBCFG_PLLUSBHSMF(36)                  /*!< PLLUSBHS source clock multiply by 36 */
#define RCU_PLLUSBHS_MUL37                PLLUSBCFG_PLLUSBHSMF(37)                  /*!< PLLUSBHS source clock multiply by 37 */
#define RCU_PLLUSBHS_MUL38                PLLUSBCFG_PLLUSBHSMF(38)                  /*!< PLLUSBHS source clock multiply by 38 */
#define RCU_PLLUSBHS_MUL39                PLLUSBCFG_PLLUSBHSMF(39)                  /*!< PLLUSBHS source clock multiply by 39 */
#define RCU_PLLUSBHS_MUL40                PLLUSBCFG_PLLUSBHSMF(40)                  /*!< PLLUSBHS source clock multiply by 40 */
#define RCU_PLLUSBHS_MUL41                PLLUSBCFG_PLLUSBHSMF(41)                  /*!< PLLUSBHS source clock multiply by 41 */
#define RCU_PLLUSBHS_MUL42                PLLUSBCFG_PLLUSBHSMF(42)                  /*!< PLLUSBHS source clock multiply by 42 */
#define RCU_PLLUSBHS_MUL43                PLLUSBCFG_PLLUSBHSMF(43)                  /*!< PLLUSBHS source clock multiply by 43 */
#define RCU_PLLUSBHS_MUL44                PLLUSBCFG_PLLUSBHSMF(44)                  /*!< PLLUSBHS source clock multiply by 44 */
#define RCU_PLLUSBHS_MUL45                PLLUSBCFG_PLLUSBHSMF(45)                  /*!< PLLUSBHS source clock multiply by 45 */
#define RCU_PLLUSBHS_MUL46                PLLUSBCFG_PLLUSBHSMF(46)                  /*!< PLLUSBHS source clock multiply by 46 */
#define RCU_PLLUSBHS_MUL47                PLLUSBCFG_PLLUSBHSMF(47)                  /*!< PLLUSBHS source clock multiply by 47 */
#define RCU_PLLUSBHS_MUL48                PLLUSBCFG_PLLUSBHSMF(48)                  /*!< PLLUSBHS source clock multiply by 48 */
#define RCU_PLLUSBHS_MUL49                PLLUSBCFG_PLLUSBHSMF(49)                  /*!< PLLUSBHS source clock multiply by 49 */
#define RCU_PLLUSBHS_MUL50                PLLUSBCFG_PLLUSBHSMF(50)                  /*!< PLLUSBHS source clock multiply by 50 */
#define RCU_PLLUSBHS_MUL51                PLLUSBCFG_PLLUSBHSMF(51)                  /*!< PLLUSBHS source clock multiply by 51 */
#define RCU_PLLUSBHS_MUL52                PLLUSBCFG_PLLUSBHSMF(52)                  /*!< PLLUSBHS source clock multiply by 52 */
#define RCU_PLLUSBHS_MUL53                PLLUSBCFG_PLLUSBHSMF(53)                  /*!< PLLUSBHS source clock multiply by 53 */
#define RCU_PLLUSBHS_MUL54                PLLUSBCFG_PLLUSBHSMF(54)                  /*!< PLLUSBHS source clock multiply by 54 */
#define RCU_PLLUSBHS_MUL55                PLLUSBCFG_PLLUSBHSMF(55)                  /*!< PLLUSBHS source clock multiply by 55 */
#define RCU_PLLUSBHS_MUL56                PLLUSBCFG_PLLUSBHSMF(56)                  /*!< PLLUSBHS source clock multiply by 56 */
#define RCU_PLLUSBHS_MUL57                PLLUSBCFG_PLLUSBHSMF(57)                  /*!< PLLUSBHS source clock multiply by 57 */
#define RCU_PLLUSBHS_MUL58                PLLUSBCFG_PLLUSBHSMF(58)                  /*!< PLLUSBHS source clock multiply by 58 */
#define RCU_PLLUSBHS_MUL59                PLLUSBCFG_PLLUSBHSMF(59)                  /*!< PLLUSBHS source clock multiply by 59 */
#define RCU_PLLUSBHS_MUL60                PLLUSBCFG_PLLUSBHSMF(60)                  /*!< PLLUSBHS source clock multiply by 60 */
#define RCU_PLLUSBHS_MUL61                PLLUSBCFG_PLLUSBHSMF(61)                  /*!< PLLUSBHS source clock multiply by 61 */
#define RCU_PLLUSBHS_MUL62                PLLUSBCFG_PLLUSBHSMF(62)                  /*!< PLLUSBHS source clock multiply by 62 */
#define RCU_PLLUSBHS_MUL63                PLLUSBCFG_PLLUSBHSMF(63)                  /*!< PLLUSBHS source clock multiply by 63 */
#define RCU_PLLUSBHS_MUL64                PLLUSBCFG_PLLUSBHSMF(64)                  /*!< PLLUSBHS source clock multiply by 64 */
#define RCU_PLLUSBHS_MUL65                PLLUSBCFG_PLLUSBHSMF(65)                  /*!< PLLUSBHS source clock multiply by 65 */
#define RCU_PLLUSBHS_MUL66                PLLUSBCFG_PLLUSBHSMF(66)                  /*!< PLLUSBHS source clock multiply by 66 */
#define RCU_PLLUSBHS_MUL67                PLLUSBCFG_PLLUSBHSMF(67)                  /*!< PLLUSBHS source clock multiply by 67 */
#define RCU_PLLUSBHS_MUL68                PLLUSBCFG_PLLUSBHSMF(68)                  /*!< PLLUSBHS source clock multiply by 68 */
#define RCU_PLLUSBHS_MUL69                PLLUSBCFG_PLLUSBHSMF(69)                  /*!< PLLUSBHS source clock multiply by 69 */
#define RCU_PLLUSBHS_MUL70                PLLUSBCFG_PLLUSBHSMF(70)                  /*!< PLLUSBHS source clock multiply by 70 */
#define RCU_PLLUSBHS_MUL71                PLLUSBCFG_PLLUSBHSMF(71)                  /*!< PLLUSBHS source clock multiply by 71 */
#define RCU_PLLUSBHS_MUL72                PLLUSBCFG_PLLUSBHSMF(72)                  /*!< PLLUSBHS source clock multiply by 72 */
#define RCU_PLLUSBHS_MUL73                PLLUSBCFG_PLLUSBHSMF(73)                  /*!< PLLUSBHS source clock multiply by 73 */
#define RCU_PLLUSBHS_MUL74                PLLUSBCFG_PLLUSBHSMF(74)                  /*!< PLLUSBHS source clock multiply by 74 */
#define RCU_PLLUSBHS_MUL75                PLLUSBCFG_PLLUSBHSMF(75)                  /*!< PLLUSBHS source clock multiply by 75 */
#define RCU_PLLUSBHS_MUL76                PLLUSBCFG_PLLUSBHSMF(76)                  /*!< PLLUSBHS source clock multiply by 76 */
#define RCU_PLLUSBHS_MUL77                PLLUSBCFG_PLLUSBHSMF(77)                  /*!< PLLUSBHS source clock multiply by 77 */
#define RCU_PLLUSBHS_MUL78                PLLUSBCFG_PLLUSBHSMF(78)                  /*!< PLLUSBHS source clock multiply by 78 */
#define RCU_PLLUSBHS_MUL79                PLLUSBCFG_PLLUSBHSMF(79)                  /*!< PLLUSBHS source clock multiply by 79 */
#define RCU_PLLUSBHS_MUL80                PLLUSBCFG_PLLUSBHSMF(80)                  /*!< PLLUSBHS source clock multiply by 80 */
#define RCU_PLLUSBHS_MUL81                PLLUSBCFG_PLLUSBHSMF(81)                  /*!< PLLUSBHS source clock multiply by 81 */
#define RCU_PLLUSBHS_MUL82                PLLUSBCFG_PLLUSBHSMF(82)                  /*!< PLLUSBHS source clock multiply by 82 */
#define RCU_PLLUSBHS_MUL83                PLLUSBCFG_PLLUSBHSMF(83)                  /*!< PLLUSBHS source clock multiply by 83 */
#define RCU_PLLUSBHS_MUL84                PLLUSBCFG_PLLUSBHSMF(84)                  /*!< PLLUSBHS source clock multiply by 84 */
#define RCU_PLLUSBHS_MUL85                PLLUSBCFG_PLLUSBHSMF(85)                  /*!< PLLUSBHS source clock multiply by 85 */
#define RCU_PLLUSBHS_MUL86                PLLUSBCFG_PLLUSBHSMF(86)                  /*!< PLLUSBHS source clock multiply by 86 */
#define RCU_PLLUSBHS_MUL87                PLLUSBCFG_PLLUSBHSMF(87)                  /*!< PLLUSBHS source clock multiply by 87 */
#define RCU_PLLUSBHS_MUL88                PLLUSBCFG_PLLUSBHSMF(88)                  /*!< PLLUSBHS source clock multiply by 88 */
#define RCU_PLLUSBHS_MUL89                PLLUSBCFG_PLLUSBHSMF(89)                  /*!< PLLUSBHS source clock multiply by 89 */
#define RCU_PLLUSBHS_MUL90                PLLUSBCFG_PLLUSBHSMF(90)                  /*!< PLLUSBHS source clock multiply by 90 */
#define RCU_PLLUSBHS_MUL91                PLLUSBCFG_PLLUSBHSMF(91)                  /*!< PLLUSBHS source clock multiply by 91 */
#define RCU_PLLUSBHS_MUL92                PLLUSBCFG_PLLUSBHSMF(92)                  /*!< PLLUSBHS source clock multiply by 92 */
#define RCU_PLLUSBHS_MUL93                PLLUSBCFG_PLLUSBHSMF(93)                  /*!< PLLUSBHS source clock multiply by 93 */
#define RCU_PLLUSBHS_MUL94                PLLUSBCFG_PLLUSBHSMF(94)                  /*!< PLLUSBHS source clock multiply by 94 */
#define RCU_PLLUSBHS_MUL95                PLLUSBCFG_PLLUSBHSMF(95)                  /*!< PLLUSBHS source clock multiply by 95 */
#define RCU_PLLUSBHS_MUL96                PLLUSBCFG_PLLUSBHSMF(96)                  /*!< PLLUSBHS source clock multiply by 96 */
#define RCU_PLLUSBHS_MUL97                PLLUSBCFG_PLLUSBHSMF(97)                  /*!< PLLUSBHS source clock multiply by 97 */
#define RCU_PLLUSBHS_MUL98                PLLUSBCFG_PLLUSBHSMF(98)                  /*!< PLLUSBHS source clock multiply by 98 */
#define RCU_PLLUSBHS_MUL99                PLLUSBCFG_PLLUSBHSMF(99)                  /*!< PLLUSBHS source clock multiply by 99 */
#define RCU_PLLUSBHS_MUL100               PLLUSBCFG_PLLUSBHSMF(100)                 /*!< PLLUSBHS source clock multiply by 100 */
#define RCU_PLLUSBHS_MUL101               PLLUSBCFG_PLLUSBHSMF(101)                 /*!< PLLUSBHS source clock multiply by 101 */
#define RCU_PLLUSBHS_MUL102               PLLUSBCFG_PLLUSBHSMF(102)                 /*!< PLLUSBHS source clock multiply by 102 */
#define RCU_PLLUSBHS_MUL103               PLLUSBCFG_PLLUSBHSMF(103)                 /*!< PLLUSBHS source clock multiply by 103 */
#define RCU_PLLUSBHS_MUL104               PLLUSBCFG_PLLUSBHSMF(104)                 /*!< PLLUSBHS source clock multiply by 104 */
#define RCU_PLLUSBHS_MUL105               PLLUSBCFG_PLLUSBHSMF(105)                 /*!< PLLUSBHS source clock multiply by 105 */
#define RCU_PLLUSBHS_MUL106               PLLUSBCFG_PLLUSBHSMF(106)                 /*!< PLLUSBHS source clock multiply by 106 */
#define RCU_PLLUSBHS_MUL107               PLLUSBCFG_PLLUSBHSMF(107)                 /*!< PLLUSBHS source clock multiply by 107 */
#define RCU_PLLUSBHS_MUL108               PLLUSBCFG_PLLUSBHSMF(108)                 /*!< PLLUSBHS source clock multiply by 108 */
#define RCU_PLLUSBHS_MUL109               PLLUSBCFG_PLLUSBHSMF(109)                 /*!< PLLUSBHS source clock multiply by 109 */
#define RCU_PLLUSBHS_MUL110               PLLUSBCFG_PLLUSBHSMF(110)                 /*!< PLLUSBHS source clock multiply by 110 */
#define RCU_PLLUSBHS_MUL111               PLLUSBCFG_PLLUSBHSMF(111)                 /*!< PLLUSBHS source clock multiply by 111 */
#define RCU_PLLUSBHS_MUL112               PLLUSBCFG_PLLUSBHSMF(112)                 /*!< PLLUSBHS source clock multiply by 112 */
#define RCU_PLLUSBHS_MUL113               PLLUSBCFG_PLLUSBHSMF(113)                 /*!< PLLUSBHS source clock multiply by 113 */
#define RCU_PLLUSBHS_MUL114               PLLUSBCFG_PLLUSBHSMF(114)                 /*!< PLLUSBHS source clock multiply by 114 */
#define RCU_PLLUSBHS_MUL115               PLLUSBCFG_PLLUSBHSMF(115)                 /*!< PLLUSBHS source clock multiply by 115 */
#define RCU_PLLUSBHS_MUL116               PLLUSBCFG_PLLUSBHSMF(116)                 /*!< PLLUSBHS source clock multiply by 116 */
#define RCU_PLLUSBHS_MUL117               PLLUSBCFG_PLLUSBHSMF(117)                 /*!< PLLUSBHS source clock multiply by 117 */
#define RCU_PLLUSBHS_MUL118               PLLUSBCFG_PLLUSBHSMF(118)                 /*!< PLLUSBHS source clock multiply by 118 */
#define RCU_PLLUSBHS_MUL119               PLLUSBCFG_PLLUSBHSMF(119)                 /*!< PLLUSBHS source clock multiply by 119 */
#define RCU_PLLUSBHS_MUL120               PLLUSBCFG_PLLUSBHSMF(120)                 /*!< PLLUSBHS source clock multiply by 120 */
#define RCU_PLLUSBHS_MUL121               PLLUSBCFG_PLLUSBHSMF(121)                 /*!< PLLUSBHS source clock multiply by 121 */
#define RCU_PLLUSBHS_MUL122               PLLUSBCFG_PLLUSBHSMF(122)                 /*!< PLLUSBHS source clock multiply by 122 */
#define RCU_PLLUSBHS_MUL123               PLLUSBCFG_PLLUSBHSMF(123)                 /*!< PLLUSBHS source clock multiply by 123 */
#define RCU_PLLUSBHS_MUL124               PLLUSBCFG_PLLUSBHSMF(124)                 /*!< PLLUSBHS source clock multiply by 124 */
#define RCU_PLLUSBHS_MUL125               PLLUSBCFG_PLLUSBHSMF(125)                 /*!< PLLUSBHS source clock multiply by 125 */
#define RCU_PLLUSBHS_MUL126               PLLUSBCFG_PLLUSBHSMF(126)                 /*!< PLLUSBHS source clock multiply by 126 */
#define RCU_PLLUSBHS_MUL127               PLLUSBCFG_PLLUSBHSMF(127)                 /*!< PLLUSBHS source clock multiply by 127 */

/* USBHS prescaler factor */
#define USBCLKCTL_USBHSPSC(regval)        (BITS(16,18) & ((uint32_t)(regval) << 16U))
#define RCU_USBHSPSC_DIV1                 USBCLKCTL_USBHSPSC(0)                     /*!< USBHS prescaler select CK_PLL1Q / 1 */
#define RCU_USBHSPSC_DIV2                 USBCLKCTL_USBHSPSC(1)                     /*!< USBHS prescaler select CK_PLL1Q / 2 */
#define RCU_USBHSPSC_DIV3                 USBCLKCTL_USBHSPSC(2)                     /*!< USBHS prescaler select CK_PLL1Q / 3 */
#define RCU_USBHSPSC_DIV4                 USBCLKCTL_USBHSPSC(3)                     /*!< USBHS prescaler select CK_PLL1Q / 4 */
#define RCU_USBHSPSC_DIV5                 USBCLKCTL_USBHSPSC(4)                     /*!< USBHS prescaler select CK_PLL1Q / 5 */
#define RCU_USBHSPSC_DIV6                 USBCLKCTL_USBHSPSC(5)                     /*!< USBHS prescaler select CK_PLL1Q / 6 */
#define RCU_USBHSPSC_DIV7                 USBCLKCTL_USBHSPSC(6)                     /*!< USBHS prescaler select CK_PLL1Q / 7 */
#define RCU_USBHSPSC_DIV8                 USBCLKCTL_USBHSPSC(7)                     /*!< USBHS prescaler select CK_PLL1Q / 8 */

/* USBHS 48MHz clock selection */
#define USBCLKCTL_USB48MSEL(regval)       (BITS(5,6) & ((uint32_t)(regval) << 5U))
#define RCU_USB48MSRC_PLL0R                USBCLKCTL_USB48MSEL(0)                   /*!< select PLL0R as USABHS 48MHz clock source */
#define RCU_USB48MSRC_PLLUSBHS            USBCLKCTL_USB48MSEL(1)                    /*!< select PLLUSBHS / USBHSDV as USABHS 48MHz clock source */
#define RCU_USB48MSRC_PLL1Q               USBCLKCTL_USB48MSEL(2)                    /*!< select PLL1Q / USBHSPSC as USABHS 48MHz clock source */
#define RCU_USB48MSRC_IRC48M              USBCLKCTL_USB48MSEL(3)                    /*!< select IRC48M as USABHS 48MHz clock source */

/* function declarations */
/* peripherals clock configure functions */
/* deinitialize the RCU */
void rcu_deinit(void);
/* enable the peripherals clock */
void rcu_periph_clock_enable(rcu_periph_enum periph);
/* disable the peripherals clock */
void rcu_periph_clock_disable(rcu_periph_enum periph);
/* enable the peripherals clock when sleep mode */
void rcu_periph_clock_sleep_enable(rcu_periph_sleep_enum periph);
/* disable the peripherals clock when sleep mode */
void rcu_periph_clock_sleep_disable(rcu_periph_sleep_enum periph);
/* reset the peripherals */
void rcu_periph_reset_enable(rcu_periph_reset_enum periph_reset);
/* disable reset the peripheral */
void rcu_periph_reset_disable(rcu_periph_reset_enum periph_reset);
/* reset the BKP */
void rcu_bkp_reset_enable(void);
/* disable the BKP reset */
void rcu_bkp_reset_disable(void);

/* system and peripherals clock source, system reset configure functions */
/* configure the system clock source */
void rcu_system_clock_source_config(uint32_t ck_sys);
/* get the system clock source */
uint32_t rcu_system_clock_source_get(void);
/* configure the AHB prescaler selection */
void rcu_ahb_clock_config(uint32_t ck_ahb);
/* configure the APB1 prescaler selection */
void rcu_apb1_clock_config(uint32_t ck_apb1);
/* configure the APB2 prescaler selection */
void rcu_apb2_clock_config(uint32_t ck_apb2);
/* configure the APB3 prescaler selection */
void rcu_apb3_clock_config(uint32_t ck_apb3);
/* configure the APB4 prescaler selection */
void rcu_apb4_clock_config(uint32_t ck_apb4);
/* configure the CK_OUT0 clock source and divider */
void rcu_ckout0_config(uint32_t ckout0_src, uint32_t ckout0_div);
/* configure the CK_OUT1 clock source and divider */
void rcu_ckout1_config(uint32_t ckout1_src, uint32_t ckout1_div);

/* configure the PLL input and output clock range */
void rcu_pll_input_output_clock_range_config(pll_idx_enum pll_idx, uint32_t ck_input, uint32_t ck_output);
/* configure fractional part of the multiplication factor for PLL VCO */
void rcu_pll_fractional_config(pll_idx_enum pll_idx, uint32_t pll_fracn);
/* enable PLL fractional latch */
void rcu_pll_fractional_latch_enable(pll_idx_enum pll_idx);
/* disable PLL fractional latch */
void rcu_pll_fractional_latch_disable(pll_idx_enum pll_idx);
/* configure the PLLs clock source selection */
void rcu_pll_source_config(uint32_t pll_src);
/* configure the PLL0 */
ErrStatus rcu_pll0_config(uint32_t pll0_psc, uint32_t pll0_n, uint32_t pll0_p, uint32_t pll0_q, uint32_t pll0_r);
/* configure the PLL1 clock */
ErrStatus rcu_pll1_config(uint32_t pll1_psc, uint32_t pll1_n, uint32_t pll1_p, uint32_t pll1_q, uint32_t pll1_r);
/* configure the PLL2 clock */
ErrStatus rcu_pll2_config(uint32_t pll2_psc, uint32_t pll2_n, uint32_t pll2_p, uint32_t pll2_q, uint32_t pll2_r);
/* enable the pllp pllq pllr divider output */
void rcu_pll_clock_output_enable(uint32_t pllxy);
/* disable the pllp pllq pllr divider output */
void rcu_pll_clock_output_disable(uint32_t pllxy);
/* configure the PLLUSBHS0 clock */
void rcu_pllusb0_config(uint32_t pllusb_presel, uint32_t pllusb_predv, uint32_t pllusb_mf, uint32_t usbhsdv);
/* configure the PLLUSBHS1 clock */
void rcu_pllusb1_config(uint32_t pllusb_presel, uint32_t pllusb_predv, uint32_t pllusb_mf, uint32_t usbhsdv);
/* configure the RTC clock source selection */
void rcu_rtc_clock_config(uint32_t rtc_clock_source);
/* configure the frequency division of RTC clock when HXTAL was selected as its clock source */
void rcu_rtc_div_config(uint32_t rtc_div);
/* configure the CK48M clock selection */
void rcu_ck48m_clock_config(uint32_t ck48m_clock_source);
/* configure the PLL48M clock selection */
void rcu_pll48m_clock_config(uint32_t pll48m_clock_source);
/* configure the IRC64M clock divider selection */
void rcu_irc64mdiv_clock_config(uint32_t ck_irc64mdiv);
/* get the irc64mdiv clock */
uint32_t rcu_irc64mdiv_freq_get(void);
/* configure the TIMER clock prescaler selection */
void rcu_timer_clock_prescaler_config(uint32_t timer_clock_prescaler);
/* configure the SPI clock source selection */
void rcu_spi_clock_config(spi_idx_enum spi_idx, uint32_t ck_spi);
/* configure the SDIO clock source selection */
void rcu_sdio_clock_config(sdio_idx_enum sdio_idx, uint32_t ck_sdio);
/* configure the Deep-sleep wakeup system clock source selection */
void rcu_deepsleep_wakeup_sys_clock_config(uint32_t ck_dspwussel);
/* configure the TLI clock division selection */
void rcu_tli_clock_div_config(uint32_t pll2_r_div);
/* configure the USARTx(x=0,1,2,5) clock source selection */
void rcu_usart_clock_config(usart_idx_enum usart_idx, uint32_t ck_usart);
/* configure the I2Cx(x=0,1,2,3) clock source selection */
void rcu_i2c_clock_config(i2c_idx_enum i2c_idx, uint32_t ck_i2c);
/* configure the CANx(x=0,1,2) clock source selection */
void rcu_can_clock_config(can_idx_enum can_idx, uint32_t ck_can);
/* configure the ADCx(x=0,1,2) clock source selection */
void rcu_adc_clock_config(adc_idx_enum adc_idx, uint32_t ck_adc);
/* configure the SAIx(x=0,1) clock source selection */
void rcu_sai_clock_config(sai_idx_enum sai_idx, uint32_t ck_sai);
/* configure the SAI2Bx(x=0,1) clock source selection */
void rcu_sai2_block_clock_config(sai2b_idx_enum sai2b_idx, uint32_t ck_sai2b);
/* configure the RSPDIF clock source selection */
void rcu_rspdif_clock_config(uint32_t ck_rspdif);
/* configure the EXMC clock source selection */
void rcu_exmc_clock_config(uint32_t ck_exmc);
/* configure the HPDF clock source selection */
void rcu_hpdf_clock_config(uint32_t ck_hpdf);
/* configure the peripheral clock source selection */
void rcu_per_clock_config(uint32_t ck_per);
/* configure the PLL1Q prescaler */
void rcu_usbhs_pll1qpsc_config(usbhs_idx_enum usbhs_idx, uint32_t ck_usbhspsc);
/* configure the USBHS48M clock source selection */
void rcu_usb48m_clock_config(usbhs_idx_enum usbhs_idx, uint32_t ck_usb48m);
/* configure the USBHS clock source selection */
void rcu_usbhs_clock_config(usbhs_idx_enum usbhs_idx, uint32_t ck_usbhs);
/* enable the USBHS clock source selection */
void rcu_usbhs_clock_selection_enable(usbhs_idx_enum usbhs_idx);
/* disable configure the USBHS clock source selection */
void rcu_usbhs_clock_selection_disable(usbhs_idx_enum usbhs_idx);

/* LXTAL, IRC64M, LPIRC4M, PLLs and other oscillator configure functions */
/* configure the LXTAL drive capability */
void rcu_lxtal_drive_capability_config(uint32_t lxtal_dricap);
/* wait for oscillator stabilization flags is SET or oscillator startup is timeout */
ErrStatus rcu_osci_stab_wait(rcu_osci_type_enum osci);
/* turn on the oscillator */
void rcu_osci_on(rcu_osci_type_enum osci);
/* turn off the oscillator */
void rcu_osci_off(rcu_osci_type_enum osci);
/* enable the oscillator bypass mode, HXTALEN or LXTALEN must be reset before it */
void rcu_osci_bypass_mode_enable(rcu_osci_type_enum osci);
/* disable the oscillator bypass mode, HXTALEN or LXTALEN must be reset before it */
void rcu_osci_bypass_mode_disable(rcu_osci_type_enum osci);
/* set the IRC64M adjust value */
void rcu_irc64m_adjust_value_set(uint32_t irc64m_adjval);
/* set the LPIRC4M adjust value */
void rcu_lpirc4m_adjust_value_set(uint32_t lpirc4m_adjval);

/* clock monitor configure functions */
/* enable the HXTAL clock monitor */
void rcu_hxtal_clock_monitor_enable(void);
/* disable the HXTAL clock monitor */
void rcu_hxtal_clock_monitor_disable(void);
/* enable the LXTAL clock monitor */
void rcu_lxtal_clock_monitor_enable(void);
/* disable the LXTAL clock monitor */
void rcu_lxtal_clock_monitor_disable(void);

/* clock frequency get functions */
/* get the system clock, bus and peripheral clock frequency */
uint32_t rcu_clock_freq_get(rcu_clock_freq_enum clock);

/* flag & interrupt functions */
/* get the clock stabilization and periphral reset flags */
FlagStatus rcu_flag_get(rcu_flag_enum flag);
/* clear the reset flag */
void rcu_all_reset_flag_clear(void);
/* enable the stabilization interrupt */
void rcu_interrupt_enable(rcu_int_enum interrupt);
/* disable the stabilization interrupt */
void rcu_interrupt_disable(rcu_int_enum interrupt);
/* get the clock stabilization interrupt and ckm flags */
FlagStatus rcu_interrupt_flag_get(rcu_int_flag_enum int_flag);
/* clear the interrupt flags */
void rcu_interrupt_flag_clear(rcu_int_flag_clear_enum int_flag);

#endif /* GD32H7XX_RCU_H */
