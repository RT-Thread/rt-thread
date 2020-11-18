/*!
    \file  gd32e230_rcu.h
    \brief definitions for the RCU
    
    \version 2018-06-19, V1.0.0, firmware for GD32E230
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

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

#ifndef GD32E230_RCU_H
#define GD32E230_RCU_H

#include "gd32e230.h"

/* RCU definitions */
#define RCU                         RCU_BASE

/* registers definitions */
#define RCU_CTL0                    REG32(RCU + 0x00U)        /*!< control register 0 */
#define RCU_CFG0                    REG32(RCU + 0x04U)        /*!< configuration register 0 */
#define RCU_INT                     REG32(RCU + 0x08U)        /*!< interrupt register */
#define RCU_APB2RST                 REG32(RCU + 0x0CU)        /*!< APB2 reset register */
#define RCU_APB1RST                 REG32(RCU + 0x10U)        /*!< APB1 reset register */
#define RCU_AHBEN                   REG32(RCU + 0x14U)        /*!< AHB enable register */
#define RCU_APB2EN                  REG32(RCU + 0x18U)        /*!< APB2 enable register */
#define RCU_APB1EN                  REG32(RCU + 0x1CU)        /*!< APB1 enable register  */
#define RCU_BDCTL                   REG32(RCU + 0x20U)        /*!< backup domain control register */
#define RCU_RSTSCK                  REG32(RCU + 0x24U)        /*!< reset source /clock register */
#define RCU_AHBRST                  REG32(RCU + 0x28U)        /*!< AHB reset register */
#define RCU_CFG1                    REG32(RCU + 0x2CU)        /*!< configuration register 1 */
#define RCU_CFG2                    REG32(RCU + 0x30U)        /*!< configuration register 2 */
#define RCU_CTL1                    REG32(RCU + 0x34U)        /*!< control register 1 */
#define RCU_VKEY                    REG32(RCU + 0x100U)       /*!< voltage key register */
#define RCU_DSV                     REG32(RCU + 0x134U)       /*!< deep-sleep mode voltage register */

/* bits definitions */
/* RCU_CTL0 */
#define RCU_CTL0_IRC8MEN            BIT(0)                    /*!< internal high speed oscillator enable */
#define RCU_CTL0_IRC8MSTB           BIT(1)                    /*!< IRC8M high speed internal oscillator stabilization flag */
#define RCU_CTL0_IRC8MADJ           BITS(3,7)                 /*!< high speed internal oscillator clock trim adjust value */
#define RCU_CTL0_IRC8MCALIB         BITS(8,15)                /*!< high speed internal oscillator calibration value register */
#define RCU_CTL0_HXTALEN            BIT(16)                   /*!< external high speed oscillator enable */
#define RCU_CTL0_HXTALSTB           BIT(17)                   /*!< external crystal oscillator clock stabilization flag */
#define RCU_CTL0_HXTALBPS           BIT(18)                   /*!< external crystal oscillator clock bypass mode enable */
#define RCU_CTL0_CKMEN              BIT(19)                   /*!< HXTAL clock monitor enable */
#define RCU_CTL0_PLLEN              BIT(24)                   /*!< PLL enable */
#define RCU_CTL0_PLLSTB             BIT(25)                   /*!< PLL clock stabilization flag */

/* RCU_CFG0 */
#define RCU_CFG0_SCS                BITS(0,1)                 /*!< system clock switch */
#define RCU_CFG0_SCSS               BITS(2,3)                 /*!< system clock switch status */
#define RCU_CFG0_AHBPSC             BITS(4,7)                 /*!< AHB prescaler selection */
#define RCU_CFG0_APB1PSC            BITS(8,10)                /*!< APB1 prescaler selection */
#define RCU_CFG0_APB2PSC            BITS(11,13)               /*!< APB2 prescaler selection */
#define RCU_CFG0_ADCPSC             BITS(14,15)               /*!< ADC clock prescaler selection */
#define RCU_CFG0_PLLSEL             BIT(16)                   /*!< PLL clock source selection */
#define RCU_CFG0_PLLPREDV           BIT(17)                   /*!< divider for PLL source clock selection */
#define RCU_CFG0_PLLMF              (BIT(27) | BITS(18,21))   /*!< PLL multiply factor */
#define RCU_CFG0_CKOUTSEL           BITS(24,26)               /*!< CK_OUT clock source selection */
#define RCU_CFG0_PLLMF4             BIT(27)                   /*!< bit 4 of PLLMF */
#define RCU_CFG0_CKOUTDIV           BITS(28,30)               /*!< CK_OUT divider which the CK_OUT frequency can be reduced */
#define RCU_CFG0_PLLDV              BIT(31)                   /*!< CK_PLL divide by 1 or 2 */

/* RCU_INT */
#define RCU_INT_IRC40KSTBIF         BIT(0)                    /*!< IRC40K stabilization interrupt flag */
#define RCU_INT_LXTALSTBIF          BIT(1)                    /*!< LXTAL stabilization interrupt flag */
#define RCU_INT_IRC8MSTBIF          BIT(2)                    /*!< IRC8M stabilization interrupt flag */
#define RCU_INT_HXTALSTBIF          BIT(3)                    /*!< HXTAL stabilization interrupt flag */
#define RCU_INT_PLLSTBIF            BIT(4)                    /*!< PLL stabilization interrupt flag */
#define RCU_INT_IRC28MSTBIF         BIT(5)                    /*!< IRC28M stabilization interrupt flag */
#define RCU_INT_CKMIF               BIT(7)                    /*!< HXTAL clock stuck interrupt flag */
#define RCU_INT_IRC40KSTBIE         BIT(8)                    /*!< IRC40K stabilization interrupt enable */
#define RCU_INT_LXTALSTBIE          BIT(9)                    /*!< LXTAL stabilization interrupt enable */
#define RCU_INT_IRC8MSTBIE          BIT(10)                   /*!< IRC8M stabilization interrupt enable */
#define RCU_INT_HXTALSTBIE          BIT(11)                   /*!< HXTAL stabilization interrupt enable */
#define RCU_INT_PLLSTBIE            BIT(12)                   /*!< PLL stabilization interrupt enable */
#define RCU_INT_IRC28MSTBIE         BIT(13)                   /*!< IRC28M stabilization interrupt enable */
#define RCU_INT_IRC40KSTBIC         BIT(16)                   /*!< IRC40K stabilization interrupt clear */
#define RCU_INT_LXTALSTBIC          BIT(17)                   /*!< LXTAL stabilization interrupt clear */
#define RCU_INT_IRC8MSTBIC          BIT(18)                   /*!< IRC8M stabilization interrupt clear */
#define RCU_INT_HXTALSTBIC          BIT(19)                   /*!< HXTAL stabilization interrupt clear */
#define RCU_INT_PLLSTBIC            BIT(20)                   /*!< PLL stabilization interrupt clear */
#define RCU_INT_IRC28MSTBIC         BIT(21)                   /*!< IRC28M stabilization interrupt clear */
#define RCU_INT_CKMIC               BIT(23)                   /*!< HXTAL clock stuck interrupt clear */

/* RCU_APB2RST */
#define RCU_APB2RST_CFGRST          BIT(0)                    /*!< system configuration reset */
#define RCU_APB2RST_ADCRST          BIT(9)                    /*!< ADC reset */
#define RCU_APB2RST_TIMER0RST       BIT(11)                   /*!< TIMER0 reset */
#define RCU_APB2RST_SPI0RST         BIT(12)                   /*!< SPI0 reset */
#define RCU_APB2RST_USART0RST       BIT(14)                   /*!< USART0 reset */
#define RCU_APB2RST_TIMER14RST      BIT(16)                   /*!< TIMER14 reset */
#define RCU_APB2RST_TIMER15RST      BIT(17)                   /*!< TIMER15 reset */
#define RCU_APB2RST_TIMER16RST      BIT(18)                   /*!< TIMER16 reset */

/* RCU_APB1RST */
#define RCU_APB1RST_TIMER2RST       BIT(1)                    /*!< TIMER2 timer reset */
#define RCU_APB1RST_TIMER5RST       BIT(4)                    /*!< TIMER5 timer reset */
#define RCU_APB1RST_TIMER13RST      BIT(8)                    /*!< TIMER13 timer reset */
#define RCU_APB1RST_WWDGTRST        BIT(11)                   /*!< window watchdog timer reset */
#define RCU_APB1RST_SPI1RST         BIT(14)                   /*!< SPI1 reset */
#define RCU_APB1RST_USART1RST       BIT(17)                   /*!< USART1 reset */
#define RCU_APB1RST_I2C0RST         BIT(21)                   /*!< I2C0 reset */
#define RCU_APB1RST_I2C1RST         BIT(22)                   /*!< I2C1 reset */
#define RCU_APB1RST_PMURST          BIT(28)                   /*!< power control reset */

/* RCU_AHBEN */
#define RCU_AHBEN_DMAEN             BIT(0)                    /*!< DMA clock enable */
#define RCU_AHBEN_SRAMSPEN          BIT(2)                    /*!< SRAM interface clock enable */
#define RCU_AHBEN_FMCSPEN           BIT(4)                    /*!< FMC clock enable */
#define RCU_AHBEN_CRCEN             BIT(6)                    /*!< CRC clock enable */
#define RCU_AHBEN_PAEN              BIT(17)                   /*!< GPIO port A clock enable */
#define RCU_AHBEN_PBEN              BIT(18)                   /*!< GPIO port B clock enable */
#define RCU_AHBEN_PCEN              BIT(19)                   /*!< GPIO port C clock enable */
#define RCU_AHBEN_PFEN              BIT(22)                   /*!< GPIO port F clock enable */

/* RCU_APB2EN */
#define RCU_APB2EN_CFGCMPEN         BIT(0)                    /*!< system configuration and comparator clock enable */
#define RCU_APB2EN_ADCEN            BIT(9)                    /*!< ADC interface clock enable */
#define RCU_APB2EN_TIMER0EN         BIT(11)                   /*!< TIMER0 timer clock enable */
#define RCU_APB2EN_SPI0EN           BIT(12)                   /*!< SPI0 clock enable */
#define RCU_APB2EN_USART0EN         BIT(14)                   /*!< USART0 clock enable */
#define RCU_APB2EN_TIMER14EN        BIT(16)                   /*!< TIMER14 timer clock enable */
#define RCU_APB2EN_TIMER15EN        BIT(17)                   /*!< TIMER15 timer clock enable */
#define RCU_APB2EN_TIMER16EN        BIT(18)                   /*!< TIMER16 timer clock enable */
#define RCU_APB2EN_DBGMCUEN         BIT(22)                   /*!< DBGMCU clock enable */

/* RCU_APB1EN */
#define RCU_APB1EN_TIMER2EN         BIT(1)                    /*!< TIMER2 timer clock enable */
#define RCU_APB1EN_TIMER5EN         BIT(4)                    /*!< TIMER5 timer clock enable */
#define RCU_APB1EN_TIMER13EN        BIT(8)                    /*!< TIMER13 timer clock enable */
#define RCU_APB1EN_WWDGTEN          BIT(11)                   /*!< window watchdog timer clock enable */
#define RCU_APB1EN_SPI1EN           BIT(14)                   /*!< SPI1 clock enable */
#define RCU_APB1EN_USART1EN         BIT(17)                   /*!< USART1 clock enable */
#define RCU_APB1EN_I2C0EN           BIT(21)                   /*!< I2C0 clock enable */
#define RCU_APB1EN_I2C1EN           BIT(22)                   /*!< I2C1 clock enable */
#define RCU_APB1EN_PMUEN            BIT(28)                   /*!< power interface clock enable */

/* RCU_BDCTL */
#define RCU_BDCTL_LXTALEN           BIT(0)                    /*!< LXTAL enable */
#define RCU_BDCTL_LXTALSTB          BIT(1)                    /*!< external low-speed oscillator stabilization */
#define RCU_BDCTL_LXTALBPS          BIT(2)                    /*!< LXTAL bypass mode enable */
#define RCU_BDCTL_LXTALDRI          BITS(3,4)                 /*!< LXTAL drive capability */
#define RCU_BDCTL_RTCSRC            BITS(8,9)                 /*!< RTC clock entry selection */
#define RCU_BDCTL_RTCEN             BIT(15)                   /*!< RTC clock enable */
#define RCU_BDCTL_BKPRST            BIT(16)                   /*!< backup domain reset */

/* RCU_RSTSCK */
#define RCU_RSTSCK_IRC40KEN         BIT(0)                    /*!< IRC40K enable */
#define RCU_RSTSCK_IRC40KSTB        BIT(1)                    /*!< IRC40K stabilization */
#define RCU_RSTSCK_V12RSTF          BIT(23)                   /*!< V12 domain power reset flag */
#define RCU_RSTSCK_RSTFC            BIT(24)                   /*!< reset flag clear */
#define RCU_RSTSCK_OBLRSTF          BIT(25)                   /*!< option byte loader reset flag */
#define RCU_RSTSCK_EPRSTF           BIT(26)                   /*!< external pin reset flag */
#define RCU_RSTSCK_PORRSTF          BIT(27)                   /*!< power reset flag */
#define RCU_RSTSCK_SWRSTF           BIT(28)                   /*!< software reset flag */
#define RCU_RSTSCK_FWDGTRSTF        BIT(29)                   /*!< free watchdog timer reset flag */
#define RCU_RSTSCK_WWDGTRSTF        BIT(30)                   /*!< window watchdog timer reset flag */
#define RCU_RSTSCK_LPRSTF           BIT(31)                   /*!< low-power reset flag */

/* RCU_AHBRST */
#define RCU_AHBRST_PARST            BIT(17)                   /*!< GPIO port A reset */
#define RCU_AHBRST_PBRST            BIT(18)                   /*!< GPIO port B reset */
#define RCU_AHBRST_PCRST            BIT(19)                   /*!< GPIO port C reset */
#define RCU_AHBRST_PFRST            BIT(22)                   /*!< GPIO port F reset */

/* RCU_CFG1 */
#define RCU_CFG1_PREDV              BITS(0,3)                 /*!< CK_HXTAL divider previous PLL */

/* RCU_CFG2 */
#define RCU_CFG2_USART0SEL          BITS(0,1)                 /*!< CK_USART0 clock source selection */
#define RCU_CFG2_ADCSEL             BIT(8)                    /*!< CK_ADC clock source selection */
#define RCU_CFG2_IRC28MDIV          BIT(16)                   /*!< CK_IRC28M divider 2 or not */
#define RCU_CFG2_ADCPSC2            BIT(31)                   /*!< bit 2 of ADCPSC */

/* RCU_CTL1 */
#define RCU_CTL1_IRC28MEN           BIT(0)                    /*!< IRC28M internal 28M RC oscillator enable */
#define RCU_CTL1_IRC28MSTB          BIT(1)                    /*!< IRC28M internal 28M RC oscillator stabilization flag */
#define RCU_CTL1_IRC28MADJ          BITS(3,7)                 /*!< internal 28M RC oscillator clock trim adjust value */
#define RCU_CTL1_IRC28MCALIB        BITS(8,15)                /*!< internal 28M RC oscillator calibration value register */

/* RCU_VKEY */
#define RCU_VKEY_KEY                BITS(0,31)                /*!< key of RCU_DSV register */

/* RCU_DSV */
#define RCU_DSV_DSLPVS              BITS(0,1)                 /*!< deep-sleep mode voltage select */

/* constants definitions */
/* define the peripheral clock enable bit position and its register index offset */
#define RCU_REGIDX_BIT(regidx, bitpos)      (((uint32_t)(regidx)<<6) | (uint32_t)(bitpos))
#define RCU_REG_VAL(periph)                 (REG32(RCU + ((uint32_t)(periph)>>6)))
#define RCU_BIT_POS(val)                    ((uint32_t)(val) & 0x1FU)
/* define the voltage key unlock value */
#define RCU_VKEY_UNLOCK                     ((uint32_t)0x1A2B3C4D)

/* register index */
typedef enum
{
    /* peripherals enable */
    IDX_AHBEN      = 0x14U, 
    IDX_APB2EN     = 0x18U, 
    IDX_APB1EN     = 0x1CU, 
    /* peripherals reset */
    IDX_AHBRST     = 0x28U, 
    IDX_APB2RST    = 0x0CU, 
    IDX_APB1RST    = 0x10U, 
    /* clock stabilization */
    IDX_CTL0       = 0x00U,
    IDX_BDCTL      = 0x20U,
    IDX_CTL1       = 0x34U,
    /* peripheral reset */
    IDX_RSTSCK     = 0x24U,
    /* clock stabilization and stuck interrupt */
    IDX_INT        = 0x08U,
    /* configuration register */
    IDX_CFG0       = 0x04U,
    IDX_CFG2       = 0x30U
}reg_idx;

/* peripheral clock enable */
typedef enum
{
    /* AHB peripherals */
    RCU_DMA     = RCU_REGIDX_BIT(IDX_AHBEN, 0U),                  /*!< DMA clock */
    RCU_CRC     = RCU_REGIDX_BIT(IDX_AHBEN, 6U),                  /*!< CRC clock */
    RCU_GPIOA   = RCU_REGIDX_BIT(IDX_AHBEN, 17U),                 /*!< GPIOA clock */
    RCU_GPIOB   = RCU_REGIDX_BIT(IDX_AHBEN, 18U),                 /*!< GPIOB clock */
    RCU_GPIOC   = RCU_REGIDX_BIT(IDX_AHBEN, 19U),                 /*!< GPIOC clock */
    RCU_GPIOF   = RCU_REGIDX_BIT(IDX_AHBEN, 22U),                 /*!< GPIOF clock */
    
    /* APB2 peripherals */
    RCU_CFGCMP  = RCU_REGIDX_BIT(IDX_APB2EN, 0U),                 /*!< CFGCMP clock */
    RCU_ADC     = RCU_REGIDX_BIT(IDX_APB2EN, 9U),                 /*!< ADC clock */
    RCU_TIMER0  = RCU_REGIDX_BIT(IDX_APB2EN, 11U),                /*!< TIMER0 clock */
    RCU_SPI0    = RCU_REGIDX_BIT(IDX_APB2EN, 12U),                /*!< SPI0 clock */
    RCU_USART0  = RCU_REGIDX_BIT(IDX_APB2EN, 14U),                /*!< USART0 clock */
    RCU_TIMER14 = RCU_REGIDX_BIT(IDX_APB2EN, 16U),                /*!< TIMER14 clock */
    RCU_TIMER15 = RCU_REGIDX_BIT(IDX_APB2EN, 17U),                /*!< TIMER15 clock */
    RCU_TIMER16 = RCU_REGIDX_BIT(IDX_APB2EN, 18U),                /*!< TIMER16 clock */
    RCU_DBGMCU  = RCU_REGIDX_BIT(IDX_APB2EN, 22U),                /*!< DBGMCU clock */
    
    /* APB1 peripherals */
    RCU_TIMER2  = RCU_REGIDX_BIT(IDX_APB1EN, 1U),                 /*!< TIMER2 clock */
    RCU_TIMER5  = RCU_REGIDX_BIT(IDX_APB1EN, 4U),                 /*!< TIMER5 clock */
    RCU_TIMER13 = RCU_REGIDX_BIT(IDX_APB1EN, 8U),                 /*!< TIMER13 clock */
    RCU_WWDGT   = RCU_REGIDX_BIT(IDX_APB1EN, 11U),                /*!< WWDGT clock */
    RCU_SPI1    = RCU_REGIDX_BIT(IDX_APB1EN, 14U),                /*!< SPI1 clock */
    RCU_USART1  = RCU_REGIDX_BIT(IDX_APB1EN, 17U),                /*!< USART1 clock */
    RCU_I2C0    = RCU_REGIDX_BIT(IDX_APB1EN, 21U),                /*!< I2C0 clock */
    RCU_I2C1    = RCU_REGIDX_BIT(IDX_APB1EN, 22U),                /*!< I2C1 clock */
    RCU_PMU     = RCU_REGIDX_BIT(IDX_APB1EN, 28U),                /*!< PMU clock */
    
    /* Backup domain control(BDCTL) */
    RCU_RTC     = RCU_REGIDX_BIT(IDX_BDCTL, 15U)                  /*!< RTC clock */
}rcu_periph_enum;

/* peripheral clock enable when sleep mode*/
typedef enum
{
    /* AHB peripherals */
    RCU_SRAM_SLP     = RCU_REGIDX_BIT(IDX_AHBEN, 2U),             /*!< SRAM clock */
    RCU_FMC_SLP      = RCU_REGIDX_BIT(IDX_AHBEN, 4U),             /*!< FMC clock */
}rcu_periph_sleep_enum;

/* peripherals reset */
typedef enum
{
    /* AHB peripherals reset */
    RCU_GPIOARST   = RCU_REGIDX_BIT(IDX_AHBRST, 17U),             /*!< GPIOA reset */
    RCU_GPIOBRST   = RCU_REGIDX_BIT(IDX_AHBRST, 18U),             /*!< GPIOB reset */
    RCU_GPIOCRST   = RCU_REGIDX_BIT(IDX_AHBRST, 19U),             /*!< GPIOC reset */
    RCU_GPIOFRST   = RCU_REGIDX_BIT(IDX_AHBRST, 22U),             /*!< GPIOF reset */
    
    /* APB2 peripherals reset */
    RCU_CFGCMPRST  = RCU_REGIDX_BIT(IDX_APB2RST, 0U),             /*!< CFGCMP reset */
    RCU_ADCRST     = RCU_REGIDX_BIT(IDX_APB2RST, 9U),             /*!< ADC reset */
    RCU_TIMER0RST  = RCU_REGIDX_BIT(IDX_APB2RST, 11U),            /*!< TIMER0 reset */
    RCU_SPI0RST    = RCU_REGIDX_BIT(IDX_APB2RST, 12U),            /*!< SPI0 reset */
    RCU_USART0RST  = RCU_REGIDX_BIT(IDX_APB2RST, 14U),            /*!< USART0 reset */
    RCU_TIMER14RST = RCU_REGIDX_BIT(IDX_APB2RST, 16U),            /*!< TIMER14 reset */
    RCU_TIMER15RST = RCU_REGIDX_BIT(IDX_APB2RST, 17U),            /*!< TIMER15 reset */
    RCU_TIMER16RST = RCU_REGIDX_BIT(IDX_APB2RST, 18U),            /*!< TIMER16 reset */
    
    /* APB1 peripherals reset */
    RCU_TIMER2RST  = RCU_REGIDX_BIT(IDX_APB1RST, 1U),             /*!< TIMER2 reset */
    RCU_TIMER5RST  = RCU_REGIDX_BIT(IDX_APB1RST, 4U),             /*!< TIMER5 reset */
    RCU_TIMER13RST = RCU_REGIDX_BIT(IDX_APB1RST, 8U),             /*!< TIMER13 reset */
    RCU_WWDGTRST   = RCU_REGIDX_BIT(IDX_APB1RST, 11U),            /*!< WWDGT reset */
    RCU_SPI1RST    = RCU_REGIDX_BIT(IDX_APB1RST, 14U),            /*!< SPI1 reset */
    RCU_USART1RST  = RCU_REGIDX_BIT(IDX_APB1RST, 17U),            /*!< USART1 reset */
    RCU_I2C0RST    = RCU_REGIDX_BIT(IDX_APB1RST, 21U),            /*!< I2C0 reset */
    RCU_I2C1RST    = RCU_REGIDX_BIT(IDX_APB1RST, 22U),            /*!< I2C1 reset */
    RCU_PMURST     = RCU_REGIDX_BIT(IDX_APB1RST, 28U),            /*!< PMU reset */
}rcu_periph_reset_enum;

/* clock stabilization and peripheral reset flags */
typedef enum
{
    RCU_FLAG_IRC40KSTB    = RCU_REGIDX_BIT(IDX_RSTSCK, 1U),       /*!< IRC40K stabilization flags */
    RCU_FLAG_LXTALSTB     = RCU_REGIDX_BIT(IDX_BDCTL, 1U),        /*!< LXTAL stabilization flags */
    RCU_FLAG_IRC8MSTB     = RCU_REGIDX_BIT(IDX_CTL0, 1U),         /*!< IRC8M stabilization flags */
    RCU_FLAG_HXTALSTB     = RCU_REGIDX_BIT(IDX_CTL0, 17U),        /*!< HXTAL stabilization flags */
    RCU_FLAG_PLLSTB       = RCU_REGIDX_BIT(IDX_CTL0, 25U),        /*!< PLL stabilization flags */
    RCU_FLAG_IRC28MSTB    = RCU_REGIDX_BIT(IDX_CTL1, 1U),         /*!< IRC28M stabilization flags */

    RCU_FLAG_V12RST       = RCU_REGIDX_BIT(IDX_RSTSCK, 23U),      /*!< V12 reset flags */
    RCU_FLAG_OBLRST       = RCU_REGIDX_BIT(IDX_RSTSCK, 25U),      /*!< OBL reset flags */
    RCU_FLAG_EPRST        = RCU_REGIDX_BIT(IDX_RSTSCK, 26U),      /*!< EPR reset flags */
    RCU_FLAG_PORRST       = RCU_REGIDX_BIT(IDX_RSTSCK, 27U),      /*!< power reset flags */
    RCU_FLAG_SWRST        = RCU_REGIDX_BIT(IDX_RSTSCK, 28U),      /*!< SW reset flags */
    RCU_FLAG_FWDGTRST     = RCU_REGIDX_BIT(IDX_RSTSCK, 29U),      /*!< FWDGT reset flags */
    RCU_FLAG_WWDGTRST     = RCU_REGIDX_BIT(IDX_RSTSCK, 30U),      /*!< WWDGT reset flags */
    RCU_FLAG_LPRST        = RCU_REGIDX_BIT(IDX_RSTSCK, 31U)       /*!< LP reset flags */
}rcu_flag_enum;

/* clock stabilization and ckm interrupt flags */
typedef enum
{
    RCU_INT_FLAG_IRC40KSTB = RCU_REGIDX_BIT(IDX_INT, 0U),         /*!< IRC40K stabilization interrupt flag */
    RCU_INT_FLAG_LXTALSTB  = RCU_REGIDX_BIT(IDX_INT, 1U),         /*!< LXTAL stabilization interrupt flag */
    RCU_INT_FLAG_IRC8MSTB  = RCU_REGIDX_BIT(IDX_INT, 2U),         /*!< IRC8M stabilization interrupt flag */
    RCU_INT_FLAG_HXTALSTB  = RCU_REGIDX_BIT(IDX_INT, 3U),         /*!< HXTAL stabilization interrupt flag */
    RCU_INT_FLAG_PLLSTB    = RCU_REGIDX_BIT(IDX_INT, 4U),         /*!< PLL stabilization interrupt flag */
    RCU_INT_FLAG_IRC28MSTB = RCU_REGIDX_BIT(IDX_INT, 5U),         /*!< IRC28M stabilization interrupt flag */
    RCU_INT_FLAG_CKM       = RCU_REGIDX_BIT(IDX_INT, 7U),         /*!< CKM interrupt flag */
}rcu_int_flag_enum;

/* clock stabilization and stuck interrupt flags clear */
typedef enum
{
    RCU_INT_FLAG_IRC40KSTB_CLR = RCU_REGIDX_BIT(IDX_INT, 16U),    /*!< IRC40K stabilization interrupt flags clear */
    RCU_INT_FLAG_LXTALSTB_CLR  = RCU_REGIDX_BIT(IDX_INT, 17U),    /*!< LXTAL stabilization interrupt flags clear */
    RCU_INT_FLAG_IRC8MSTB_CLR  = RCU_REGIDX_BIT(IDX_INT, 18U),    /*!< IRC8M stabilization interrupt flags clear */
    RCU_INT_FLAG_HXTALSTB_CLR  = RCU_REGIDX_BIT(IDX_INT, 19U),    /*!< HXTAL stabilization interrupt flags clear */
    RCU_INT_FLAG_PLLSTB_CLR    = RCU_REGIDX_BIT(IDX_INT, 20U),    /*!< PLL stabilization interrupt flags clear */
    RCU_INT_FLAG_IRC28MSTB_CLR = RCU_REGIDX_BIT(IDX_INT, 21U),    /*!< IRC28M stabilization interrupt flags clear */
    RCU_INT_FLAG_CKM_CLR       = RCU_REGIDX_BIT(IDX_INT, 23U),    /*!< CKM interrupt flags clear */
}rcu_int_flag_clear_enum;

/* clock stabilization interrupt enable or disable */
typedef enum
{
    RCU_INT_IRC40KSTB       = RCU_REGIDX_BIT(IDX_INT, 8U),        /*!< IRC40K stabilization interrupt */
    RCU_INT_LXTALSTB        = RCU_REGIDX_BIT(IDX_INT, 9U),        /*!< LXTAL stabilization interrupt */
    RCU_INT_IRC8MSTB        = RCU_REGIDX_BIT(IDX_INT, 10U),       /*!< IRC8M stabilization interrupt */
    RCU_INT_HXTALSTB        = RCU_REGIDX_BIT(IDX_INT, 11U),       /*!< HXTAL stabilization interrupt */
    RCU_INT_PLLSTB          = RCU_REGIDX_BIT(IDX_INT, 12U),       /*!< PLL stabilization interrupt */
    RCU_INT_IRC28MSTB       = RCU_REGIDX_BIT(IDX_INT, 13U),       /*!< IRC28M stabilization interrupt */
}rcu_int_enum;

/* ADC clock source */
typedef enum
{
    RCU_ADCCK_IRC28M_DIV2   = 0U,                                 /*!< ADC clock source select IRC28M/2 */
    RCU_ADCCK_IRC28M,                                             /*!< ADC clock source select IRC28M */
    RCU_ADCCK_APB2_DIV2,                                          /*!< ADC clock source select APB2/2 */
    RCU_ADCCK_AHB_DIV3,                                           /*!< ADC clock source select AHB/3 */
    RCU_ADCCK_APB2_DIV4,                                          /*!< ADC clock source select APB2/4 */
    RCU_ADCCK_AHB_DIV5,                                           /*!< ADC clock source select AHB/5 */
    RCU_ADCCK_APB2_DIV6,                                          /*!< ADC clock source select APB2/6 */
    RCU_ADCCK_AHB_DIV7,                                           /*!< ADC clock source select AHB/7 */
    RCU_ADCCK_APB2_DIV8,                                          /*!< ADC clock source select APB2/8 */
    RCU_ADCCK_AHB_DIV9                                            /*!< ADC clock source select AHB/9 */
}rcu_adc_clock_enum;

/* oscillator types */
typedef enum
{
    RCU_HXTAL   = RCU_REGIDX_BIT(IDX_CTL0, 16U),                  /*!< HXTAL */
    RCU_LXTAL   = RCU_REGIDX_BIT(IDX_BDCTL, 0U),                  /*!< LXTAL */
    RCU_IRC8M   = RCU_REGIDX_BIT(IDX_CTL0, 0U),                   /*!< IRC8M */
    RCU_IRC28M  = RCU_REGIDX_BIT(IDX_CTL1, 0U),                   /*!< IRC28M */
    RCU_IRC40K  = RCU_REGIDX_BIT(IDX_RSTSCK, 0U),                 /*!< IRC40K */
    RCU_PLL_CK  = RCU_REGIDX_BIT(IDX_CTL0, 24U)                   /*!< PLL */
}rcu_osci_type_enum;

/* rcu clock frequency */
typedef enum
{
    CK_SYS      = 0U,                                             /*!< system clock */
    CK_AHB,                                                       /*!< AHB clock */
    CK_APB1,                                                      /*!< APB1 clock */
    CK_APB2,                                                      /*!< APB2 clock */
    CK_ADC,                                                       /*!< ADC clock */
    CK_USART                                                      /*!< USART clock */
}rcu_clock_freq_enum;

/* system clock source select */
#define CFG0_SCS(regval)            (BITS(0,1) & ((uint32_t)(regval) << 0))
#define RCU_CKSYSSRC_IRC8M          CFG0_SCS(0)                   /*!< system clock source select IRC8M */
#define RCU_CKSYSSRC_HXTAL          CFG0_SCS(1)                   /*!< system clock source select HXTAL */
#define RCU_CKSYSSRC_PLL            CFG0_SCS(2)                   /*!< system clock source select PLL */

/* system clock source select status */
#define CFG0_SCSS(regval)           (BITS(2,3) & ((uint32_t)(regval) << 2))
#define RCU_SCSS_IRC8M              CFG0_SCSS(0)                  /*!< system clock source select IRC8M */
#define RCU_SCSS_HXTAL              CFG0_SCSS(1)                  /*!< system clock source select HXTAL */
#define RCU_SCSS_PLL                CFG0_SCSS(2)                  /*!< system clock source select PLL */

/* AHB prescaler selection */
#define CFG0_AHBPSC(regval)         (BITS(4,7) & ((uint32_t)(regval) << 4))
#define RCU_AHB_CKSYS_DIV1          CFG0_AHBPSC(0)                /*!< AHB prescaler select CK_SYS */
#define RCU_AHB_CKSYS_DIV2          CFG0_AHBPSC(8)                /*!< AHB prescaler select CK_SYS/2 */
#define RCU_AHB_CKSYS_DIV4          CFG0_AHBPSC(9)                /*!< AHB prescaler select CK_SYS/4 */
#define RCU_AHB_CKSYS_DIV8          CFG0_AHBPSC(10)               /*!< AHB prescaler select CK_SYS/8 */
#define RCU_AHB_CKSYS_DIV16         CFG0_AHBPSC(11)               /*!< AHB prescaler select CK_SYS/16 */
#define RCU_AHB_CKSYS_DIV64         CFG0_AHBPSC(12)               /*!< AHB prescaler select CK_SYS/64 */
#define RCU_AHB_CKSYS_DIV128        CFG0_AHBPSC(13)               /*!< AHB prescaler select CK_SYS/128 */
#define RCU_AHB_CKSYS_DIV256        CFG0_AHBPSC(14)               /*!< AHB prescaler select CK_SYS/256 */
#define RCU_AHB_CKSYS_DIV512        CFG0_AHBPSC(15)               /*!< AHB prescaler select CK_SYS/512 */

/* APB1 prescaler selection */
#define CFG0_APB1PSC(regval)        (BITS(8,10) & ((uint32_t)(regval) << 8))
#define RCU_APB1_CKAHB_DIV1         CFG0_APB1PSC(0)               /*!< APB1 prescaler select CK_AHB */
#define RCU_APB1_CKAHB_DIV2         CFG0_APB1PSC(4)               /*!< APB1 prescaler select CK_AHB/2 */
#define RCU_APB1_CKAHB_DIV4         CFG0_APB1PSC(5)               /*!< APB1 prescaler select CK_AHB/4 */
#define RCU_APB1_CKAHB_DIV8         CFG0_APB1PSC(6)               /*!< APB1 prescaler select CK_AHB/8 */
#define RCU_APB1_CKAHB_DIV16        CFG0_APB1PSC(7)               /*!< APB1 prescaler select CK_AHB/16 */

/* APB2 prescaler selection */
#define CFG0_APB2PSC(regval)        (BITS(11,13) & ((uint32_t)(regval) << 11))
#define RCU_APB2_CKAHB_DIV1         CFG0_APB2PSC(0)               /*!< APB2 prescaler select CK_AHB */
#define RCU_APB2_CKAHB_DIV2         CFG0_APB2PSC(4)               /*!< APB2 prescaler select CK_AHB/2 */
#define RCU_APB2_CKAHB_DIV4         CFG0_APB2PSC(5)               /*!< APB2 prescaler select CK_AHB/4 */
#define RCU_APB2_CKAHB_DIV8         CFG0_APB2PSC(6)               /*!< APB2 prescaler select CK_AHB/8 */
#define RCU_APB2_CKAHB_DIV16        CFG0_APB2PSC(7)               /*!< APB2 prescaler select CK_AHB/16 */

/* ADC clock prescaler selection */
#define CFG0_ADCPSC(regval)         (BITS(14,15) & ((uint32_t)(regval) << 14))
#define RCU_ADC_CKAPB2_DIV2         CFG0_ADCPSC(0)                /*!< ADC clock prescaler select CK_APB2/2 */
#define RCU_ADC_CKAPB2_DIV4         CFG0_ADCPSC(1)                /*!< ADC clock prescaler select CK_APB2/4 */
#define RCU_ADC_CKAPB2_DIV6         CFG0_ADCPSC(2)                /*!< ADC clock prescaler select CK_APB2/6 */
#define RCU_ADC_CKAPB2_DIV8         CFG0_ADCPSC(3)                /*!< ADC clock prescaler select CK_APB2/8 */

/* PLL clock source selection */
#define RCU_PLLSRC_IRC8M_DIV2       (uint32_t)0x00000000U         /*!< PLL clock source select IRC8M/2 */
#define RCU_PLLSRC_HXTAL            RCU_CFG0_PLLSEL               /*!< PLL clock source select HXTAL */

/* HXTAL divider for PLL source clock selection */
#define RCU_PLLPREDV                (uint32_t)0x00000000U         /*!< HXTAL clock selected */
#define RCU_PLLPREDV_DIV2           RCU_CFG0_PLLPREDV             /*!< HXTAL/2 clock selected */

/* PLL multiply factor */
#define CFG0_PLLMF(regval)          (BITS(18,21) & ((uint32_t)(regval) << 18))
#define RCU_PLL_MUL2                CFG0_PLLMF(0)                       /*!< PLL source clock multiply by 2 */
#define RCU_PLL_MUL3                CFG0_PLLMF(1)                       /*!< PLL source clock multiply by 3 */
#define RCU_PLL_MUL4                CFG0_PLLMF(2)                       /*!< PLL source clock multiply by 4 */
#define RCU_PLL_MUL5                CFG0_PLLMF(3)                       /*!< PLL source clock multiply by 5 */
#define RCU_PLL_MUL6                CFG0_PLLMF(4)                       /*!< PLL source clock multiply by 6 */
#define RCU_PLL_MUL7                CFG0_PLLMF(5)                       /*!< PLL source clock multiply by 7 */
#define RCU_PLL_MUL8                CFG0_PLLMF(6)                       /*!< PLL source clock multiply by 8 */
#define RCU_PLL_MUL9                CFG0_PLLMF(7)                       /*!< PLL source clock multiply by 9 */
#define RCU_PLL_MUL10               CFG0_PLLMF(8)                       /*!< PLL source clock multiply by 10 */
#define RCU_PLL_MUL11               CFG0_PLLMF(9)                       /*!< PLL source clock multiply by 11 */
#define RCU_PLL_MUL12               CFG0_PLLMF(10)                      /*!< PLL source clock multiply by 12 */
#define RCU_PLL_MUL13               CFG0_PLLMF(11)                      /*!< PLL source clock multiply by 13 */
#define RCU_PLL_MUL14               CFG0_PLLMF(12)                      /*!< PLL source clock multiply by 14 */
#define RCU_PLL_MUL15               CFG0_PLLMF(13)                      /*!< PLL source clock multiply by 15 */
#define RCU_PLL_MUL16               CFG0_PLLMF(14)                      /*!< PLL source clock multiply by 16 */
#define RCU_PLL_MUL17               (RCU_CFG0_PLLMF4 | CFG0_PLLMF(0))   /*!< PLL source clock multiply by 17 */
#define RCU_PLL_MUL18               (RCU_CFG0_PLLMF4 | CFG0_PLLMF(1))   /*!< PLL source clock multiply by 18 */
#define RCU_PLL_MUL19               (RCU_CFG0_PLLMF4 | CFG0_PLLMF(2))   /*!< PLL source clock multiply by 19 */
#define RCU_PLL_MUL20               (RCU_CFG0_PLLMF4 | CFG0_PLLMF(3))   /*!< PLL source clock multiply by 20 */
#define RCU_PLL_MUL21               (RCU_CFG0_PLLMF4 | CFG0_PLLMF(4))   /*!< PLL source clock multiply by 21 */
#define RCU_PLL_MUL22               (RCU_CFG0_PLLMF4 | CFG0_PLLMF(5))   /*!< PLL source clock multiply by 22 */
#define RCU_PLL_MUL23               (RCU_CFG0_PLLMF4 | CFG0_PLLMF(6))   /*!< PLL source clock multiply by 23 */
#define RCU_PLL_MUL24               (RCU_CFG0_PLLMF4 | CFG0_PLLMF(7))   /*!< PLL source clock multiply by 24 */
#define RCU_PLL_MUL25               (RCU_CFG0_PLLMF4 | CFG0_PLLMF(8))   /*!< PLL source clock multiply by 25 */
#define RCU_PLL_MUL26               (RCU_CFG0_PLLMF4 | CFG0_PLLMF(9))   /*!< PLL source clock multiply by 26 */
#define RCU_PLL_MUL27               (RCU_CFG0_PLLMF4 | CFG0_PLLMF(10))  /*!< PLL source clock multiply by 27 */
#define RCU_PLL_MUL28               (RCU_CFG0_PLLMF4 | CFG0_PLLMF(11))  /*!< PLL source clock multiply by 28 */
#define RCU_PLL_MUL29               (RCU_CFG0_PLLMF4 | CFG0_PLLMF(12))  /*!< PLL source clock multiply by 29 */
#define RCU_PLL_MUL30               (RCU_CFG0_PLLMF4 | CFG0_PLLMF(13))  /*!< PLL source clock multiply by 30 */
#define RCU_PLL_MUL31               (RCU_CFG0_PLLMF4 | CFG0_PLLMF(14))  /*!< PLL source clock multiply by 31 */
#define RCU_PLL_MUL32               (RCU_CFG0_PLLMF4 | CFG0_PLLMF(15))  /*!< PLL source clock multiply by 32 */

/* CK_OUT clock source selection */
#define CFG0_CKOUTSEL(regval)       (BITS(24,26) & ((uint32_t)(regval) << 24))
#define RCU_CKOUTSRC_NONE           CFG0_CKOUTSEL(0)                    /*!< no clock selected */
#define RCU_CKOUTSRC_IRC28M         CFG0_CKOUTSEL(1)                    /*!< CK_OUT clock source select IRC28M */
#define RCU_CKOUTSRC_IRC40K         CFG0_CKOUTSEL(2)                    /*!< CK_OUT clock source select IRC40K */
#define RCU_CKOUTSRC_LXTAL          CFG0_CKOUTSEL(3)                    /*!< CK_OUT clock source select LXTAL */
#define RCU_CKOUTSRC_CKSYS          CFG0_CKOUTSEL(4)                    /*!< CK_OUT clock source select CKSYS */
#define RCU_CKOUTSRC_IRC8M          CFG0_CKOUTSEL(5)                    /*!< CK_OUT clock source select IRC8M */
#define RCU_CKOUTSRC_HXTAL          CFG0_CKOUTSEL(6)                    /*!< CK_OUT clock source select HXTAL */
#define RCU_CKOUTSRC_CKPLL_DIV1     (RCU_CFG0_PLLDV | CFG0_CKOUTSEL(7)) /*!< CK_OUT clock source select CK_PLL */
#define RCU_CKOUTSRC_CKPLL_DIV2     CFG0_CKOUTSEL(7)                    /*!< CK_OUT clock source select CK_PLL/2 */

/* CK_OUT divider */
#define CFG0_CKOUTDIV(regval)       (BITS(28,30) & ((uint32_t)(regval) << 28))
#define RCU_CKOUT_DIV1              CFG0_CKOUTDIV(0)                    /*!< CK_OUT is divided by 1 */
#define RCU_CKOUT_DIV2              CFG0_CKOUTDIV(1)                    /*!< CK_OUT is divided by 2 */
#define RCU_CKOUT_DIV4              CFG0_CKOUTDIV(2)                    /*!< CK_OUT is divided by 4 */
#define RCU_CKOUT_DIV8              CFG0_CKOUTDIV(3)                    /*!< CK_OUT is divided by 8 */
#define RCU_CKOUT_DIV16             CFG0_CKOUTDIV(4)                    /*!< CK_OUT is divided by 16 */
#define RCU_CKOUT_DIV32             CFG0_CKOUTDIV(5)                    /*!< CK_OUT is divided by 32 */
#define RCU_CKOUT_DIV64             CFG0_CKOUTDIV(6)                    /*!< CK_OUT is divided by 64 */
#define RCU_CKOUT_DIV128            CFG0_CKOUTDIV(7)                    /*!< CK_OUT is divided by 128 */

/* CK_PLL divide by 1 or 2 for CK_OUT */
#define RCU_PLLDV_CKPLL_DIV2        (uint32_t)0x00000000U               /*!< CK_PLL divide by 2 for CK_OUT */
#define RCU_PLLDV_CKPLL             RCU_CFG0_PLLDV                      /*!< CK_PLL divide by 1 for CK_OUT */

/* LXTAL drive capability */
#define BDCTL_LXTALDRI(regval)      (BITS(3,4) & ((uint32_t)(regval) << 3))
#define RCU_LXTAL_LOWDRI            BDCTL_LXTALDRI(0)                   /*!< lower driving capability */
#define RCU_LXTAL_MED_LOWDRI        BDCTL_LXTALDRI(1)                   /*!< medium low driving capability */
#define RCU_LXTAL_MED_HIGHDRI       BDCTL_LXTALDRI(2)                   /*!< medium high driving capability */
#define RCU_LXTAL_HIGHDRI           BDCTL_LXTALDRI(3)                   /*!< higher driving capability */

/* RTC clock entry selection */
#define BDCTL_RTCSRC(regval)        (BITS(8,9) & ((uint32_t)(regval) << 8))
#define RCU_RTCSRC_NONE             BDCTL_RTCSRC(0)                     /*!< no clock selected */
#define RCU_RTCSRC_LXTAL            BDCTL_RTCSRC(1)                     /*!< LXTAL selected as RTC source clock */
#define RCU_RTCSRC_IRC40K           BDCTL_RTCSRC(2)                     /*!< IRC40K selected as RTC source clock */
#define RCU_RTCSRC_HXTAL_DIV32      BDCTL_RTCSRC(3)                     /*!< HXTAL/32 selected as RTC source clock */

/* CK_HXTAL divider previous PLL */
#define CFG1_PREDV(regval)         (BITS(0,3) & ((uint32_t)(regval) << 0))
#define RCU_PLL_PREDV1              CFG1_PREDV(0)                       /*!< PLL not divided */
#define RCU_PLL_PREDV2              CFG1_PREDV(1)                       /*!< PLL divided by 2 */
#define RCU_PLL_PREDV3              CFG1_PREDV(2)                       /*!< PLL divided by 3 */
#define RCU_PLL_PREDV4              CFG1_PREDV(3)                       /*!< PLL divided by 4 */
#define RCU_PLL_PREDV5              CFG1_PREDV(4)                       /*!< PLL divided by 5 */
#define RCU_PLL_PREDV6              CFG1_PREDV(5)                       /*!< PLL divided by 6 */
#define RCU_PLL_PREDV7              CFG1_PREDV(6)                       /*!< PLL divided by 7 */
#define RCU_PLL_PREDV8              CFG1_PREDV(7)                       /*!< PLL divided by 8 */
#define RCU_PLL_PREDV9              CFG1_PREDV(8)                       /*!< PLL divided by 9 */
#define RCU_PLL_PREDV10             CFG1_PREDV(9)                       /*!< PLL divided by 10 */
#define RCU_PLL_PREDV11             CFG1_PREDV(10)                      /*!< PLL divided by 11 */
#define RCU_PLL_PREDV12             CFG1_PREDV(11)                      /*!< PLL divided by 12 */
#define RCU_PLL_PREDV13             CFG1_PREDV(12)                      /*!< PLL divided by 13 */
#define RCU_PLL_PREDV14             CFG1_PREDV(13)                      /*!< PLL divided by 14 */
#define RCU_PLL_PREDV15             CFG1_PREDV(14)                      /*!< PLL divided by 15 */
#define RCU_PLL_PREDV16             CFG1_PREDV(15)                      /*!< PLL divided by 16 */

/* USART0 clock source selection */
#define CFG2_USART0SEL(regval)      (BITS(0,1) & ((uint32_t)(regval) << 0))
#define RCU_USART0SRC_CKAPB2        CFG2_USART0SEL(0)                   /*!< CK_USART0 select CK_APB2 */
#define RCU_USART0SRC_CKSYS         CFG2_USART0SEL(1)                   /*!< CK_USART0 select CK_SYS */
#define RCU_USART0SRC_LXTAL         CFG2_USART0SEL(2)                   /*!< CK_USART0 select LXTAL */
#define RCU_USART0SRC_IRC8M         CFG2_USART0SEL(3)                   /*!< CK_USART0 select IRC8M */

/* ADC clock source selection */
#define RCU_ADCSRC_IRC28M           (uint32_t)0x00000000U               /*!< ADC clock source select */
#define RCU_ADCSRC_AHB_APB2DIV      RCU_CFG2_ADCSEL                     /*!< ADC clock source select */

/* IRC28M clock divider for ADC */
#define RCU_ADC_IRC28M_DIV2         (uint32_t)0x00000000U               /*!< IRC28M/2 select to ADC clock */
#define RCU_ADC_IRC28M_DIV1         RCU_CFG2_IRC28MDIV                  /*!< IRC28M select to ADC clock */

/* Deep-sleep mode voltage */
#define DSV_DSLPVS(regval)          (BITS(0,1) & ((uint32_t)(regval) << 0))
#define RCU_DEEPSLEEP_V_1_0         DSV_DSLPVS(0)                       /*!< core voltage is 1.0V in deep-sleep mode */
#define RCU_DEEPSLEEP_V_0_9         DSV_DSLPVS(1)                       /*!< core voltage is 0.9V in deep-sleep mode */
#define RCU_DEEPSLEEP_V_0_8         DSV_DSLPVS(2)                       /*!< core voltage is 0.8V in deep-sleep mode */
#define RCU_DEEPSLEEP_V_1_2         DSV_DSLPVS(3)                       /*!< core voltage is 1.2V in deep-sleep mode */

/* function declarations */
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
/* configure the ADC clock source and prescaler selection */
void rcu_adc_clock_config(rcu_adc_clock_enum ck_adc);
/* configure the CK_OUT clock source and divider */
void rcu_ckout_config(uint32_t ckout_src, uint32_t ckout_div);

/* configure the PLL clock source selection and PLL multiply factor */
void rcu_pll_config(uint32_t pll_src, uint32_t pll_mul);
/* configure the USART clock source selection */
void rcu_usart_clock_config(uint32_t ck_usart);
/* configure the RTC clock source selection */
void rcu_rtc_clock_config(uint32_t rtc_clock_source);
/* configure the HXTAL divider used as input of PLL */
void rcu_hxtal_prediv_config(uint32_t hxtal_prediv);
/* configure the LXTAL drive capability */
void rcu_lxtal_drive_capability_config(uint32_t lxtal_dricap);

/* get the clock stabilization and periphral reset flags */
FlagStatus rcu_flag_get(rcu_flag_enum flag);
/* clear the reset flag */
void rcu_all_reset_flag_clear(void);
/* get the clock stabilization interrupt and ckm flags */
FlagStatus rcu_interrupt_flag_get(rcu_int_flag_enum int_flag);
/* clear the interrupt flags */
void rcu_interrupt_flag_clear(rcu_int_flag_clear_enum int_flag_clear);
/* enable the stabilization interrupt */
void rcu_interrupt_enable(rcu_int_enum stab_int);
/* disable the stabilization interrupt */
void rcu_interrupt_disable(rcu_int_enum stab_int);

/* wait until oscillator stabilization flags is SET */
ErrStatus rcu_osci_stab_wait(rcu_osci_type_enum osci);
/* turn on the oscillator */
void rcu_osci_on(rcu_osci_type_enum osci);
/* turn off the oscillator */
void rcu_osci_off(rcu_osci_type_enum osci);
/* enable the oscillator bypass mode */
void rcu_osci_bypass_mode_enable(rcu_osci_type_enum osci);
/* disable the oscillator bypass mode */
void rcu_osci_bypass_mode_disable(rcu_osci_type_enum osci);
/* enable the HXTAL clock monitor */
void rcu_hxtal_clock_monitor_enable(void);
/* disable the HXTAL clock monitor */
void rcu_hxtal_clock_monitor_disable(void);

/* set the IRC8M adjust value */
void rcu_irc8m_adjust_value_set(uint8_t irc8m_adjval);
/* set the IRC28M adjust value */
void rcu_irc28m_adjust_value_set(uint8_t irc28m_adjval);
/* unlock the voltage key */
void rcu_voltage_key_unlock(void);
/* set the deep sleep mode voltage */
void rcu_deepsleep_voltage_set(uint32_t dsvol);

/* get the system clock, bus and peripheral clock frequency */
uint32_t rcu_clock_freq_get(rcu_clock_freq_enum clock);

#endif /* GD32E230_RCU_H */
