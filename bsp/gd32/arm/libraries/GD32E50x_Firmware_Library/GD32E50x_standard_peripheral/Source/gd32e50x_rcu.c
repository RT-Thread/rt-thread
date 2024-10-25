/*!
    \file    gd32e50x_rcu.c
    \brief   RCU driver

    \version 2023-12-31, V1.4.0, firmware for GD32E50x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

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

#include "gd32e50x_rcu.h"

/* define clock source */
#define SEL_IRC8M                   ((uint16_t)0U)  /* IRC8M is selected as CK_SYS */
#define SEL_HXTAL                   ((uint16_t)1U)  /* HXTAL is selected as CK_SYS */
#define SEL_PLL                     ((uint16_t)2U)  /* PLL is selected as CK_SYS */

/* define startup timeout count */
#define OSC_STARTUP_TIMEOUT         ((uint32_t)0x000FFFFFU)
#define LXTAL_STARTUP_TIMEOUT       ((uint32_t)0x03FFFFFFU)

/* ADC clock prescaler offset */
#define RCU_ADC_PSC_OFFSET          ((uint32_t)14U)

/* RCU IRC8M adjust value mask and offset*/
#define RCU_IRC8M_ADJUST_MASK       ((uint8_t)0x1FU)
#define RCU_IRC8M_ADJUST_OFFSET     ((uint32_t)3U)

/* RCU PLL1 clock multiplication factor offset */
#define RCU_CFG1_PLL1MF_OFFSET      ((uint32_t)8U)
/* RCU PREDV1 division factor offset*/
#define RCU_CFG1_PREDV1_OFFSET      ((uint32_t)4U)

/*!
    \brief      deinitialize the RCU
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_deinit(void)
{
    /* enable IRC8M */
    RCU_CTL |= RCU_CTL_IRC8MEN;
    while(0U == (RCU_CTL & RCU_CTL_IRC8MSTB))
    {
    }
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    /* reset CTL register */
    RCU_CTL &= ~(RCU_CTL_HXTALEN | RCU_CTL_CKMEN | RCU_CTL_PLLEN);
    RCU_CTL &= ~RCU_CTL_HXTALBPS;
#if defined(GD32E50X_CL) || defined(GD32EPRT) || defined(GD32E508)
    RCU_CTL &= ~(RCU_CTL_PLL1EN | RCU_CTL_PLL2EN);
#endif /* GD32E50X_CL and GD32EPRT and GD32E508 */
    /* reset CFG0 register */
#if defined(GD32E50X_HD)
    RCU_CFG0 &= ~(RCU_CFG0_SCS | RCU_CFG0_AHBPSC | RCU_CFG0_APB1PSC | RCU_CFG0_APB2PSC |
                  RCU_CFG0_ADCPSC | RCU_CFG0_PLLSEL | RCU_CFG0_PREDV0 | RCU_CFG0_PLLMF |
                  RCU_CFG0_USBDPSC | RCU_CFG0_CKOUT0SEL | RCU_CFG0_PLLMF_4 | RCU_CFG0_ADCPSC_2 | RCU_CFG0_PLLMF_5 | RCU_CFG0_USBDPSC_2);
#elif defined(GD32E50X_CL) || defined(GD32E508)
    RCU_CFG0 &= ~(RCU_CFG0_SCS | RCU_CFG0_AHBPSC | RCU_CFG0_APB1PSC | RCU_CFG0_APB2PSC |
                  RCU_CFG0_ADCPSC | RCU_CFG0_PLLSEL | RCU_CFG0_PREDV0_LSB | RCU_CFG0_PLLMF |
                  RCU_CFG0_USBHSPSC | RCU_CFG0_CKOUT0SEL | RCU_CFG0_ADCPSC_2 | RCU_CFG0_PLLMF_4 | RCU_CFG0_PLLMF_5 | RCU_CFG0_USBHSPSC_2);
#elif defined(GD32EPRT)
    RCU_CFG0 &= ~(RCU_CFG0_SCS | RCU_CFG0_AHBPSC | RCU_CFG0_APB1PSC | RCU_CFG0_APB2PSC |
                  RCU_CFG0_ADCPSC | RCU_CFG0_PLLSEL | RCU_CFG0_PREDV0_LSB | RCU_CFG0_PLLMF |
                  RCU_CFG0_USBDPSC | RCU_CFG0_CKOUT0SEL | RCU_CFG0_ADCPSC_2 | RCU_CFG0_PLLMF_4 | RCU_CFG0_PLLMF_5 | RCU_CFG0_USBDPSC_2);
#endif /* GD32E50X_HD */

    /* reset INT and CFG1 register */
#if defined(GD32E50X_HD)
    RCU_INT = 0x009f0000U;
    RCU_CFG1 &= ~(RCU_CFG1_ADCPSC_3 | RCU_CFG1_PLLPRESEL);
    RCU_CFG2 &= ~(RCU_CFG2_USART5SEL | RCU_CFG2_I2C2SEL);
#elif defined(GD32E50X_CL) || defined(GD32E508)
    RCU_INT = 0x00ff0000U;
    RCU_ADDINT = 0x00C00000U;
    RCU_ADDCTL &= ~(RCU_ADDCTL_CK48MSEL | RCU_ADDCTL_USBHSSEL | RCU_ADDCTL_USBHSDV | RCU_ADDCTL_USBSWEN | RCU_ADDCTL_PLLUSBEN | RCU_ADDCTL_IRC48MEN);
    RCU_ADDCFG &= ~(RCU_ADDCFG_PLLUSBPREDV | RCU_ADDCFG_PLLUSBPRESEL | RCU_ADDCFG_PLLUSBPREDVSEL | RCU_ADDCFG_PLLUSBMF);

    RCU_CFG1 &= ~(RCU_CFG1_PREDV0 | RCU_CFG1_PREDV1 | RCU_CFG1_PLL1MF | RCU_CFG1_PLL2MF |
                  RCU_CFG1_PREDV0SEL | RCU_CFG1_I2S1SEL | RCU_CFG1_I2S2SEL | RCU_CFG1_SHRTIMERSEL | RCU_CFG1_PLL2MF_5 | RCU_CFG1_ADCPSC_3 |
                  RCU_CFG1_PLLPRESEL | RCU_CFG1_PLL2MF_4);
    RCU_CFG2 &= ~(RCU_CFG2_USART5SEL | RCU_CFG2_I2C2SEL);
#elif defined(GD32EPRT)
    RCU_INT = 0x00ff0000U;
    RCU_ADDINT &= ~ (RCU_ADDINT_IRC48MSTBIC);
    RCU_ADDCTL &= ~(RCU_ADDCTL_CK48MSEL | RCU_ADDCTL_IRC48MEN);

    RCU_CFG1 &= ~(RCU_CFG1_PREDV0 | RCU_CFG1_PREDV1 | RCU_CFG1_PLL1MF | RCU_CFG1_PLL2MF |
                  RCU_CFG1_PREDV0SEL | RCU_CFG1_I2S1SEL | RCU_CFG1_I2S2SEL | RCU_CFG1_PLL2MF_5 | RCU_CFG1_ADCPSC_3 |
                  RCU_CFG1_PLLPRESEL | RCU_CFG1_PLL2MF_4);
    RCU_CFG2 &= ~(RCU_CFG2_USART5SEL | RCU_CFG2_I2C2SEL);

#endif /* GD32E50X_HD */
}

/*!
    \brief      enable the peripherals clock
    \param[in]  periph: RCU peripherals, refer to rcu_periph_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_GPIOx (x = A,B,C,D,E,F,G): GPIO ports clock
      \arg        RCU_AF : alternate function clock
      \arg        RCU_CRC: CRC clock
      \arg        RCU_DMAx (x = 0,1): DMA clock
      \arg        RCU_ENET: ENET clock(EPRT and CL series available)
      \arg        RCU_ENETTX: ENETTX clock(EPRT and CL series available)
      \arg        RCU_ENETRX: ENETRX clock(EPRT and CL series available)
      \arg        RCU_USBD: USBD clock(HD and EPRT series available)
      \arg        RCU_USBHS: USBHS clock(CL series available)
      \arg        RCU_TMU: TMU clock
      \arg        RCU_SQPI: SQPI clock
      \arg        RCU_EXMC: EXMC clock
      \arg        RCU_TIMERx (x = 0,1,2,3,4,5,6,7,8,9,10,11,12,13,TIMER8..13 are not available for EPRT series): TIMER clock
      \arg        RCU_WWDGT: WWDGT clock
      \arg        RCU_SPIx (x = 0,1,2): SPI clock
      \arg        RCU_USARTx (x = 0,1,2,5): USART clock
      \arg        RCU_UARTx (x = 3,4): UART clock
      \arg        RCU_I2Cx (x = 0,1,2): I2C clock
      \arg        RCU_CANx (x = 0,1,2,CAN2 is only available for CL series,CANx is not avaliable for GD32EPRT): CAN clock
      \arg        RCU_PMU: PMU clock
      \arg        RCU_DAC: DAC clock
      \arg        RCU_RTC: RTC clock
      \arg        RCU_ADCx (x = 0,1,2, ADC2 is not available for CL series): ADC clock
      \arg        RCU_SDIO: SDIO clock(not available for CL and EPRT series)
      \arg        RCU_CTC: CTC clock
      \arg        RCU_BKPI: BKP interface clock
      \arg        RCU_SHRTIMER: (not available for EPRT series):SHRTIMER clock
      \arg        RCU_CMP(CMP is only available for CL series):CMP clock
    \param[out] none
    \retval     none
*/
void rcu_periph_clock_enable(rcu_periph_enum periph)
{
    RCU_REG_VAL(periph) |= BIT(RCU_BIT_POS(periph));
}

/*!
    \brief      disable the peripherals clock
    \param[in]  periph: RCU peripherals, refer to rcu_periph_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_GPIOx (x = A,B,C,D,E,F,G): GPIO ports clock
      \arg        RCU_AF : alternate function clock
      \arg        RCU_CRC: CRC clock
      \arg        RCU_DMAx (x  =0,1): DMA clock
      \arg        RCU_ENET: ENET clock(EPRT and CL series available)
      \arg        RCU_ENETTX: ENETTX clock(EPRT and CL series available)
      \arg        RCU_ENETRX: ENETRX clock(EPRT and CL series available)
      \arg        RCU_USBD: USBD clock(HD and EPRT series available)
      \arg        RCU_USBHS: USBHS clock(CL series available)
      \arg        RCU_TMU: TMU clock
      \arg        RCU_SQPI: SQPI clock
      \arg        RCU_EXMC: EXMC clock
      \arg        RCU_TIMERx (x = 0,1,2,3,4,5,6,7,8,9,10,11,12,13,TIMER8..13 are not available for EPRT series): TIMER clock
      \arg        RCU_WWDGT: WWDGT clock
      \arg        RCU_SPIx (x = 0,1,2): SPI clock
      \arg        RCU_USARTx (x = 0,1,2,5): USART clock
      \arg        RCU_UARTx (x = 3,4): UART clock
      \arg        RCU_I2Cx (x = 0,1,2): I2C clock
      \arg        RCU_CANx (x = 0,1,2,CAN2 is only available for CL series,CANx is not avaliable for GD32EPRT): CAN clock
      \arg        RCU_PMU: PMU clock
      \arg        RCU_DAC: DAC clock
      \arg        RCU_RTC: RTC clock
      \arg        RCU_ADCx (x = 0,1,2,ADC2 is not available for CL series): ADC clock
      \arg        RCU_SDIO: SDIO clock(not available for CL and EPRT series)
      \arg        RCU_CTC: CTC clock
      \arg        RCU_BKPI: BKP interface clock
      \arg        RCU_SHRTIMER: (not available for EPRT series): SHRTIMER clock
      \arg        RCU_CMP(CMP is only available for CL series):CMP clock
    \param[out] none
    \retval     none
*/
void rcu_periph_clock_disable(rcu_periph_enum periph)
{
    RCU_REG_VAL(periph) &= ~BIT(RCU_BIT_POS(periph));
}

/*!
    \brief      enable the peripherals clock when sleep mode
    \param[in]  periph: RCU peripherals, refer to rcu_periph_sleep_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_FMC_SLP: FMC clock
      \arg        RCU_SRAM_SLP: SRAM clock
    \param[out] none
    \retval     none
*/
void rcu_periph_clock_sleep_enable(rcu_periph_sleep_enum periph)
{
    RCU_REG_VAL(periph) |= BIT(RCU_BIT_POS(periph));
}

/*!
    \brief      disable the peripherals clock when sleep mode
    \param[in]  periph: RCU peripherals, refer to rcu_periph_sleep_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_FMC_SLP: FMC clock
      \arg        RCU_SRAM_SLP: SRAM clock
    \param[out] none
    \retval     none
*/
void rcu_periph_clock_sleep_disable(rcu_periph_sleep_enum periph)
{
    RCU_REG_VAL(periph) &= ~BIT(RCU_BIT_POS(periph));
}

/*!
    \brief      reset the peripherals
    \param[in]  periph_reset: RCU peripherals reset, refer to rcu_periph_reset_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_GPIOxRST (x = A,B,C,D,E,F,G): reset GPIO ports
      \arg        RCU_AFRST : reset alternate function clock
      \arg        RCU_ENETRST: reset ENET(EPRT and CL series available)
      \arg        RCU_USBDRST: reset USBD(HD and EPRT series available)
      \arg        RCU_USBHSRST: reset USBHS(CL series available)
      \arg        RCU_TMURST: reset TMU
      \arg        RCU_SQPIRST: reset SQPI
      \arg        RCU_TIMERxRST (x = 0,1,2,3,4,5,6,7,8,9,10,11,12,13,TIMER8..13 are not available for EPRT series): reset TIMER
      \arg        RCU_WWDGTRST: reset WWDGT
      \arg        RCU_SPIxRST (x = 0,1,2): reset SPI
      \arg        RCU_USARTxRST (x = 0,1,2,5): reset USART
      \arg        RCU_UARTxRST (x = 3,4): reset UART
      \arg        RCU_I2CxRST (x = 0,1): reset I2C
      \arg        RCU_PMURST: reset PMU
      \arg        RCU_DACRST: reset DAC
      \arg        RCU_ADCRST (x = 0,1,2,ADC2 is not available for CL series): reset ADC
      \arg        RCU_CTCRST: reset CTC
      \arg        RCU_BKPIRST: reset BKPI
      \arg        RCU_SHRTIMERRST: (not available for EPRT series):reset SHRTIMERRST
      \arg        RCU_CMPRST(CMP is only available for CL series): reset CMP
    \param[out] none
    \retval     none
*/
void rcu_periph_reset_enable(rcu_periph_reset_enum periph_reset)
{
    RCU_REG_VAL(periph_reset) |= BIT(RCU_BIT_POS(periph_reset));
}

/*!
    \brief      disable reset the peripheral
    \param[in]  periph_reset: RCU peripherals reset, refer to rcu_periph_reset_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_GPIOxRST (x = A,B,C,D,E,F,G): reset GPIO ports
      \arg        RCU_AFRST : reset alternate function clock
      \arg        RCU_ENETRST: reset ENET(CL series available)
      \arg        RCU_USBDRST: reset USBD(HD and EPRT series available)
      \arg        RCU_USBHSRST: reset USBHS(CL series available)
      \arg        RCU_TMURST: reset TMU
      \arg        RCU_SQPIRST: reset SQPI
      \arg        RCU_TIMERxRST (x = 0,1,2,3,4,5,6,7,8,9,10,11,12,13,TIMER8..13 are not available for EPRT series): reset TIMER
      \arg        RCU_WWDGTRST: reset WWDGT
      \arg        RCU_SPIxRST (x = 0,1,2): reset SPI
      \arg        RCU_USARTxRST (x = 0,1,2,5): reset USART
      \arg        RCU_UARTxRST (x = 3,4): reset UART
      \arg        RCU_I2CxRST (x = 0,1): reset I2C
      \arg        RCU_PMURST: reset PMU
      \arg        RCU_DACRST: reset DAC
      \arg        RCU_ADCRST (x = 0,1,2,ADC2 is not available for CL series): reset ADC
      \arg        RCU_CTCRST: reset CTC
      \arg        RCU_BKPIRST: reset BKPI
      \arg        RCU_SHRTIMERRST: (not available for EPRT series):reset SHRTIMERRST
      \arg        RCU_CMPRST(CMP is only available for CL series): reset CMP
    \param[out] none
    \retval     none
*/
void rcu_periph_reset_disable(rcu_periph_reset_enum periph_reset)
{
    RCU_REG_VAL(periph_reset) &= ~BIT(RCU_BIT_POS(periph_reset));
}

/*!
    \brief      reset the BKP domain
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_bkp_reset_enable(void)
{
    RCU_BDCTL |= RCU_BDCTL_BKPRST;
}

/*!
    \brief      disable the BKP domain reset
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_bkp_reset_disable(void)
{
    RCU_BDCTL &= ~RCU_BDCTL_BKPRST;
}

/*!
    \brief      configure the system clock source
    \param[in]  ck_sys: system clock source select
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKSYSSRC_IRC8M: select CK_IRC8M as the CK_SYS source
      \arg        RCU_CKSYSSRC_HXTAL: select CK_HXTAL as the CK_SYS source
      \arg        RCU_CKSYSSRC_PLL: select CK_PLL as the CK_SYS source
    \param[out] none
    \retval     none
*/
void rcu_system_clock_source_config(uint32_t ck_sys)
{
    uint32_t reg;

    reg = RCU_CFG0;
    /* reset the SCS bits and set according to ck_sys */
    reg &= ~RCU_CFG0_SCS;
    RCU_CFG0 = (reg | ck_sys);
}

/*!
    \brief      get the system clock source
    \param[in]  none
    \param[out] none
    \retval     which clock is selected as CK_SYS source
      \arg        RCU_SCSS_IRC8M: CK_IRC8M is selected as the CK_SYS source
      \arg        RCU_SCSS_HXTAL: CK_HXTAL is selected as the CK_SYS source
      \arg        RCU_SCSS_PLL: CK_PLL is selected as the CK_SYS source
*/
uint32_t rcu_system_clock_source_get(void)
{
    return (RCU_CFG0 & RCU_CFG0_SCSS);
}

/*!
    \brief      configure the AHB clock prescaler selection
    \param[in]  ck_ahb: AHB clock prescaler selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_AHB_CKSYS_DIVx (x = 1, 2, 4, 8, 16, 64, 128, 256, 512): select CK_SYS / x as CK_AHB
    \param[out] none
    \retval     none
*/
void rcu_ahb_clock_config(uint32_t ck_ahb)
{
    uint32_t reg;

    reg = RCU_CFG0;

    /* reset the AHBPSC bits and set according to ck_ahb */
    reg &= ~RCU_CFG0_AHBPSC;
    RCU_CFG0 = (reg | ck_ahb);
}

/*!
    \brief      configure the APB1 clock prescaler selection
    \param[in]  ck_apb1: APB1 clock prescaler selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_APB1_CKAHB_DIV1: select CK_AHB as CK_APB1
      \arg        RCU_APB1_CKAHB_DIV2: select CK_AHB / 2 as CK_APB1
      \arg        RCU_APB1_CKAHB_DIV4: select CK_AHB / 4 as CK_APB1
      \arg        RCU_APB1_CKAHB_DIV8: select CK_AHB / 8 as CK_APB1
      \arg        RCU_APB1_CKAHB_DIV16: select CK_AHB / 16 as CK_APB1
    \param[out] none
    \retval     none
*/
void rcu_apb1_clock_config(uint32_t ck_apb1)
{
    uint32_t reg;

    reg = RCU_CFG0;

    /* reset the APB1PSC and set according to ck_apb1 */
    reg &= ~RCU_CFG0_APB1PSC;
    RCU_CFG0 = (reg | ck_apb1);
}

/*!
    \brief      configure the APB2 clock prescaler selection
    \param[in]  ck_apb2: APB2 clock prescaler selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_APB2_CKAHB_DIV1: select CK_AHB as CK_APB2
      \arg        RCU_APB2_CKAHB_DIV2: select CK_AHB/2 as CK_APB2
      \arg        RCU_APB2_CKAHB_DIV4: select CK_AHB/4 as CK_APB2
      \arg        RCU_APB2_CKAHB_DIV8: select CK_AHB/8 as CK_APB2
      \arg        RCU_APB2_CKAHB_DIV16: select CK_AHB/16 as CK_APB2
    \param[out] none
    \retval     none
*/
void rcu_apb2_clock_config(uint32_t ck_apb2)
{
    uint32_t reg;

    reg = RCU_CFG0;

    /* reset the APB2PSC and set according to ck_apb2 */
    reg &= ~RCU_CFG0_APB2PSC;
    RCU_CFG0 = (reg | ck_apb2);
}

/*!
    \brief      configure the CK_OUT0 clock source
    \param[in]  ckout0_src: CK_OUT0 clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKOUT0SRC_NONE: no clock selected
      \arg        RCU_CKOUT0SRC_CKSYS: system clock selected
      \arg        RCU_CKOUT0SRC_IRC8M: high speed 8M internal oscillator clock selected
      \arg        RCU_CKOUT0SRC_HXTAL: HXTAL selected
      \arg        RCU_CKOUT0SRC_CKPLL_DIV2: CK_PLL/2 selected
      \arg        RCU_CKOUT0SRC_CKPLL1: CK_PLL1 selected (available for CL、EPRT and E508 series)
      \arg        RCU_CKOUT0SRC_CKPLL2_DIV2: CK_PLL2/2 selected (available for CL、EPRT and E508 series)
      \arg        RCU_CKOUT0SRC_EXT1: EXT1 selected (available for CL、EPRT and E508 series)
      \arg        RCU_CKOUT0SRC_CKPLL2: CK_PLL2 clock selected (available for CL、EPRT and E508 series)
      \arg        RCU_CKOUT0SRC_CKIRC48M: CK_IRC48M clock selected (available for CL、EPRT and E508 series)
      \arg        RCU_CKOUT0SRC_CKIRC48M_DIV8: CK_IRC48M/8 clock selected (available for CL、EPRT and E508 series)
      \arg        RCU_CKOUT0SRC_CKPLLUSB_DIV32: CK_PLLUSB/32 clock selected (available for CL and E508 series)
    \param[out] none
    \retval     none
*/
void rcu_ckout0_config(uint32_t ckout0_src)
{
    uint32_t reg;

    reg = RCU_CFG0;

    /* reset the CKOUT0SRC, set according to ckout0_src */
    reg &= ~RCU_CFG0_CKOUT0SEL;
    RCU_CFG0 = (reg | ckout0_src);
}

/*!
    \brief      configure the main PLL clock
    \param[in]  pll_src: PLL clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLLSRC_IRC8M_DIV2: IRC8M/2 clock selected as source clock of PLL
      \arg        RCU_PLLSRC_HXTAL_IRC48M: HXTAL or IRC48M selected as source clock of PLL
    \param[in]  pll_mul: PLL clock multiplication factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLL_MULx (HD series x = 2..63, CL series x = 2..14, 16..64, 6.5): PLL clock * x
    \param[out] none
    \retval     none
*/
void rcu_pll_config(uint32_t pll_src, uint32_t pll_mul)
{
    uint32_t reg = 0U;

    reg = RCU_CFG0;

    /* PLL clock source and multiplication factor configuration */
    reg &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF | RCU_CFG0_PLLMF_4 | RCU_CFG0_PLLMF_5);
    reg |= (pll_src | pll_mul);

    RCU_CFG0 = reg;
}

/*!
    \brief      configure the PLL clock source preselection
    \param[in]  pll_presel: PLL clock source preselection
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLLPRESRC_HXTAL: HXTAL selected as PREDV0 input source clock
      \arg        RCU_PLLPRESRC_IRC48M: CK_PLL selected as PREDV0 input source clock
    \param[out] none
    \retval     none
*/
void rcu_pllpresel_config(uint32_t pll_presel)
{
    uint32_t reg = 0U;

    reg = RCU_CFG1;

    /* PLL clock source preselection */
    reg &= ~RCU_CFG1_PLLPRESEL;
    reg |= pll_presel;

    RCU_CFG1 = reg;
}

#if defined(GD32E50X_HD)
/*!
    \brief      configure the PREDV0 division factor
    \param[in]  predv0_div: PREDV0 division factor
      \arg        RCU_PREDV0_DIVx (x = 1, 2): PREDV0 input source clock is divided x
    \param[out] none
    \retval     none
*/
void rcu_predv0_config(uint32_t predv0_div)
{
    uint32_t reg = 0U;

    reg = RCU_CFG0;
    /* reset PREDV0 bit */
    reg &= ~RCU_CFG0_PREDV0;
    if(RCU_PREDV0_DIV2 == predv0_div)
    {
        /* set the PREDV0 bit */
        reg |= RCU_CFG0_PREDV0;
    }

    RCU_CFG0 = reg;
}
#elif defined(GD32E50X_CL) || defined(GD32EPRT) || defined(GD32E508)
/*!
    \brief      configure the PREDV0 division factor and clock source
    \param[in]  predv0_source: PREDV0 input clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_PREDV0SRC_HXTAL_IRC48M: HXTAL or IRC48M selected as PREDV0 input source clock
      \arg        RCU_PREDV0SRC_CKPLL1: CK_PLL1 selected as PREDV0 input source clock
    \param[in]  predv0_div: PREDV0 division factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_PREDV0_DIVx (x = 1..16): PREDV0 input source clock is divided x
    \param[out] none
    \retval     none
*/
void rcu_predv0_config(uint32_t predv0_source, uint32_t predv0_div)
{
    uint32_t reg = 0U;

    reg = RCU_CFG1;
    /* reset PREDV0SEL and PREDV0 bits */
    reg &= ~(RCU_CFG1_PREDV0SEL | RCU_CFG1_PREDV0);
    /* set the PREDV0SEL and PREDV0 division factor */
    reg |= (predv0_source | predv0_div);

    RCU_CFG1 = reg;
}

/*!
    \brief      configure the PREDV1 division factor
    \param[in]  predv1_div: PREDV1 division factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_PREDV1_DIVx (x = 1..16): PREDV1 input source clock is divided x
    \param[out] none
    \retval     none
*/
void rcu_predv1_config(uint32_t predv1_div)
{
    uint32_t reg = 0U;

    reg = RCU_CFG1;
    /* reset the PREDV1 bits */
    reg &= ~RCU_CFG1_PREDV1;
    /* set the PREDV1 division factor */
    reg |= predv1_div;

    RCU_CFG1 = reg;
}

/*!
    \brief      configure the PLL1 clock
    \param[in]  pll_mul: PLL clock multiplication factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLL1_MULx (x = 8..14,16,20): PLL1 clock * x
    \param[out] none
    \retval     none
*/
void rcu_pll1_config(uint32_t pll_mul)
{
    RCU_CFG1 &= ~RCU_CFG1_PLL1MF;
    RCU_CFG1 |= pll_mul;
}

/*!
    \brief      configure the PLL2 clock
    \param[in]  pll_mul: PLL clock multiplication factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLL2_MULx (x = 8..14,16,20,18..32,40,34..64,80): PLL2 clock * x
    \param[out] none
    \retval     none
*/
void rcu_pll2_config(uint32_t pll_mul)
{
    RCU_CFG1 &= ~RCU_CFG1_PLL2MF;
    RCU_CFG1 |= pll_mul;
}
#endif /* GD32E50X_HD */

#if defined(GD32E50X_CL) || defined(GD32E508)
/*!
    \brief      configure the PLLUSB clock source preselection
    \param[in]  pllusb_presel: PLLUSB clock source preselection
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLLUSBPRESRC_HXTAL: HXTAL selected as PLLUSB source clock
      \arg        RCU_PLLUSBPRESRC_IRC48M: IRC48M clock selected as PLLUSB source clock
    \param[out] none
    \retval     none
*/
void rcu_pllusbpresel_config(uint32_t pllusb_presel)
{
    uint32_t reg = 0U;

    reg = RCU_ADDCFG;

    /* PLLUSB clock source preselection */
    reg &= ~RCU_ADDCFG_PLLUSBPRESEL;
    reg |= pllusb_presel;

    RCU_ADDCFG = reg;
}

/*!
    \brief      configure the PLLUSBPREDV division factor and clock source
    \param[in]  pllusbpredv_source: PLLUSBPREDV input clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLLUSBPREDVSRC_HXTAL_IRC48M: HXTAL or IRC48M selected as PLLUSBPREDV input source clock
      \arg        RCU_PLLUSBPREDVSRC_CKPLL1: CK_PLL1 selected as PLLUSBPREDV input source clock
    \param[in]  pllusbpredv_div: PLLUSBPREDV division factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLLUSBPREDV_DIVx (x = 1..15): PLLUSBPREDV input source clock divided by x
    \param[out] none
    \retval     none
*/
void rcu_pllusbpredv_config(uint32_t pllusbpredv_source, uint32_t pllusbpredv_div)
{
    uint32_t reg = 0U;

    reg = RCU_ADDCFG;
    /* reset PLLUSBPRESEL and PLLUSBPREDV bits */
    reg &= ~(RCU_ADDCFG_PLLUSBPREDVSEL | RCU_ADDCFG_PLLUSBPREDV);
    /* set the PLLUSBPRESEL and PLLUSBPREDV division factor */
    reg |= (pllusbpredv_source | pllusbpredv_div);

    RCU_ADDCFG = reg;
}

/*!
    \brief      configure the PLLUSB clock
    \param[in]  pllusb_mul: PLLUSB clock multiplication factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLLUSB_MULx (x = 16,17..127): PLLUSB source clock multiply by x
    \param[out] none
    \retval     none
*/
void rcu_pllusb_config(uint32_t pllusb_mul)
{
    RCU_ADDCFG &= ~RCU_ADDCFG_PLLUSBMF;
    RCU_ADDCFG |= pllusb_mul;
}

#endif /* GD32E50X_CL and GD32E508 */

/*!
    \brief      configure the ADC prescaler factor
    \param[in]  adc_psc: ADC prescaler factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKADC_CKAPB2_DIV2: ADC prescaler select CK_APB2 / 2
      \arg        RCU_CKADC_CKAPB2_DIV4: ADC prescaler select CK_APB2 / 4
      \arg        RCU_CKADC_CKAPB2_DIV6: ADC prescaler select CK_APB2 / 6
      \arg        RCU_CKADC_CKAPB2_DIV8: ADC prescaler select CK_APB2 / 8
      \arg        RCU_CKADC_CKAPB2_DIV12: ADC prescaler select CK_APB2 / 12
      \arg        RCU_CKADC_CKAPB2_DIV16: ADC prescaler select CK_APB2 / 16
      \arg        RCU_CKADC_CKAHB_DIV5: ADC prescaler select CK_AHB / 5
      \arg        RCU_CKADC_CKAHB_DIV6: ADC prescaler select CK_AHB / 6
      \arg        RCU_CKADC_CKAHB_DIV10: ADC prescaler select CK_AHB / 10
      \arg        RCU_CKADC_CKAHB_DIV20: ADC prescaler select CK_AHB / 20
    \param[out] none
    \retval     none
*/
void rcu_adc_clock_config(uint32_t adc_psc)
{
    uint32_t reg0,reg1;

    /* reset the ADCPSC bits */
    reg0 = RCU_CFG0;
    reg0 &= ~(RCU_CFG0_ADCPSC_2 | RCU_CFG0_ADCPSC);
    reg1 = RCU_CFG1;
    reg1 &= ~RCU_CFG1_ADCPSC_3;

    /* set the ADC prescaler factor */
    switch(adc_psc)
    {
        case RCU_CKADC_CKAPB2_DIV2:
        case RCU_CKADC_CKAPB2_DIV4:
        case RCU_CKADC_CKAPB2_DIV6:
        case RCU_CKADC_CKAPB2_DIV8:
            reg0 |= (adc_psc << RCU_ADC_PSC_OFFSET);
            break;

        case RCU_CKADC_CKAPB2_DIV12:
        case RCU_CKADC_CKAPB2_DIV16:
            adc_psc &= ~BIT(2);
            reg0 |= ((adc_psc << RCU_ADC_PSC_OFFSET) | RCU_CFG0_ADCPSC_2);
            break;

        case RCU_CKADC_CKAHB_DIV5:
        case RCU_CKADC_CKAHB_DIV6:
        case RCU_CKADC_CKAHB_DIV10:
        case RCU_CKADC_CKAHB_DIV20:
            adc_psc &= ~BITS(2,3);
            reg0 |= (adc_psc << RCU_ADC_PSC_OFFSET);
            reg1 |= RCU_CFG1_ADCPSC_3;
            break;

        default:
            break;
    }

    /* set the register */
    RCU_CFG0 = reg0;
    RCU_CFG1 = reg1;
}

/*!
    \brief      configure the USBD/USBHS prescaler factor
    \param[in]  usb_psc: USB prescaler factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKUSB_CKPLL_DIV1_5: USBD / USBHS prescaler select CK_PLL / 1.5
      \arg        RCU_CKUSB_CKPLL_DIV1: USBD / USBHS prescaler select CK_PLL / 1
      \arg        RCU_CKUSB_CKPLL_DIV2_5: USBD / USBHS prescaler select CK_PLL / 2.5
      \arg        RCU_CKUSB_CKPLL_DIV2: USBD / USBHS prescaler select CK_PLL / 2
      \arg        RCU_CKUSB_CKPLL_DIV3: USBD / USBHS prescaler select CK_PLL / 3
      \arg        RCU_CKUSB_CKPLL_DIV3_5: USBD / USBHS prescaler select CK_PLL / 3.5
      \arg        RCU_CKUSB_CKPLL_DIV4: USBD / USBHS prescaler select CK_PLL / 4
    \param[out] none
    \retval     none
*/
void rcu_usb_clock_config(uint32_t usb_psc)
{
    uint32_t reg;

    reg = RCU_CFG0;

    /* configure the USBD/USBHS prescaler factor */
#if (defined(GD32E50X_HD) || defined(GD32EPRT))
    reg &= ~RCU_CFG0_USBDPSC;
#elif defined(GD32E50X_CL) || defined(GD32E508)
    reg &= ~RCU_CFG0_USBHSPSC;
#endif /* GD32E50X_HD and GD32EPRT */

    RCU_CFG0 = (reg | usb_psc);
}

/*!
    \brief      configure the RTC clock source selection
    \param[in]  rtc_clock_source: RTC clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_RTCSRC_NONE: no clock selected
      \arg        RCU_RTCSRC_LXTAL: CK_LXTAL selected as RTC source clock
      \arg        RCU_RTCSRC_IRC40K: CK_IRC40K selected as RTC source clock
      \arg        RCU_RTCSRC_HXTAL_DIV_128: CK_HXTAL/128 selected as RTC source clock
    \param[out] none
    \retval     none
*/
void rcu_rtc_clock_config(uint32_t rtc_clock_source)
{
    uint32_t reg;

    reg = RCU_BDCTL;
    /* reset the RTCSRC bits and set according to rtc_clock_source */
    reg &= ~RCU_BDCTL_RTCSRC;
    RCU_BDCTL = (reg | rtc_clock_source);
}

#ifndef GD32EPRT
/*!
    \brief      configure the SHRTIMER clock source selection
    \param[in]  shrtimer_clock_source: SHRTIMER clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_SHRTIMERSRC_CKAPB2: APB2 clock selected as SHRTIMER source clock
      \arg        RCU_SHRTIMERSRC_CKSYS: system clock selected as SHRTIMER source clock
    \param[out] none
    \retval     none
*/
void rcu_shrtimer_clock_config(uint32_t shrtimer_clock_source)
{
    uint32_t reg;

    reg = RCU_CFG1;
    /* reset the I2S1SEL bit and set according to shrtimer_clock_source */
    reg &= ~RCU_CFG1_SHRTIMERSEL;
    RCU_CFG1 = (reg | shrtimer_clock_source);
}
#endif /* GD32EPRT */

/*!
    \brief      configure the USART5 clock source selection
    \param[in]  usart5_clock_source: USART5 clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_USART5SRC_CKAPB2: APB2 clock selected as USART5 source clock
      \arg        RCU_USART5SRC_CKSYS: system clock selected as USART5 source clock
      \arg        RCU_USART5SRC_LXTAL: LXTAL clock selected as USART5 source clock
      \arg        RCU_USART5SRC_IRC8M: IRC8M clock selected as USART5 source clock
    \param[out] none
    \retval     none
*/
void rcu_usart5_clock_config(uint32_t usart5_clock_source)
{
    uint32_t reg;
    reg = RCU_CFG2;
    /* reset the I2S1SEL bit and set according to usart5_clock_source */
    reg &= ~RCU_CFG2_USART5SEL;
    RCU_CFG2 = (reg | usart5_clock_source);
}

/*!
    \brief      configure the I2C2 clock source selection
    \param[in]  i2c2_clock_source: I2C2 clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_I2C2SRC_CKAPB1: APB1 clock selected as I2C2 source clock
      \arg        RCU_I2C2SRC_CKSYS: System clock selected as I2C2 source clock
      \arg        RCU_I2C2SRCSRC_CKIRC8M: CK_IRC8M clock selected as I2C2 source clock
    \param[out] none
    \retval     none
*/
void rcu_i2c2_clock_config(uint32_t i2c2_clock_source)
{
    uint32_t reg;

    reg = RCU_CFG2;
    /* reset the I2S1SEL bit and set according to i2c2_clock_source */
    reg &= ~RCU_CFG2_I2C2SEL;
    RCU_CFG2 = (reg | i2c2_clock_source);
}

/*!
    \brief      configure the CK48M clock source selection
    \param[in]  ck48m_clock_source: CK48M clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_CK48MSRC_CKPLL: CK_PLL selected as CK48M source clock
      \arg        RCU_CK48MSRC_IRC48M: CK_IRC48M selected as CK48M source clock
      \arg        RCU_CK48MSRC_CKPLLUSB: (not available for EPRT series): CKPLLUSB selected as CK48M source clock
      \arg        RCU_CK48MSRC_CKPLL2: CKPLL2 selected as CK48M source clock
    \param[out] none
    \retval     none
*/
void rcu_ck48m_clock_config(uint32_t ck48m_clock_source)
{
    uint32_t reg;

    reg = RCU_ADDCTL;
    /* reset the CK48MSEL bit and set according to ck48m_clock_source */
    reg &= ~RCU_ADDCTL_CK48MSEL;
    RCU_ADDCTL = (reg | ck48m_clock_source);
}

#if defined(GD32E50X_CL) || defined(GD32EPRT) || defined(GD32E508)
/*!
    \brief      configure the I2S1 clock source selection
    \param[in]  i2s_clock_source: I2S1 clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_I2S1SRC_CKSYS: system clock selected as I2S1 source clock
      \arg        RCU_I2S1SRC_CKPLL2_MUL2: CK_PLL2 * 2 selected as I2S1 source clock
    \param[out] none
    \retval     none
*/
void rcu_i2s1_clock_config(uint32_t i2s_clock_source)
{
    uint32_t reg;

    reg = RCU_CFG1;
    /* reset the I2S1SEL bit and set according to i2s_clock_source */
    reg &= ~RCU_CFG1_I2S1SEL;
    RCU_CFG1 = (reg | i2s_clock_source);
}

/*!
    \brief      configure the I2S2 clock source selection
    \param[in]  i2s_clock_source: I2S2 clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_I2S2SRC_CKSYS: system clock selected as I2S2 source clock
      \arg        RCU_I2S2SRC_CKPLL2_MUL2: CK_PLL2 * 2 selected as I2S2 source clock
    \param[out] none
    \retval     none
*/
void rcu_i2s2_clock_config(uint32_t i2s_clock_source)
{
    uint32_t reg;

    reg = RCU_CFG1;
    /* reset the I2S2SEL bit and set according to i2s_clock_source */
    reg &= ~RCU_CFG1_I2S2SEL;
    RCU_CFG1 = (reg | i2s_clock_source);
}
#endif /* GD32E50X_CL and GD32E50X_EPRT and GD32E508 */

#if defined(GD32E50X_CL) || defined(GD32E508)
/*!
    \brief      configure the USBHSSEL source clock selection
    \param[in]  usbhssel_clock_source: USBHSSEL clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_USBHSSRC_48M: 48M clock selected as USBHS source clock
      \arg        RCU_CK48MSRC_60M: 60M clock selected as USBHS source clock
    \param[out] none
    \retval     none
*/
void rcu_usbhssel_config(uint32_t usbhssel_clock_source)
{
    uint32_t reg = 0U;

    reg = RCU_ADDCTL;

    /* USBHS clock source selection */
    reg &= ~RCU_ADDCTL_USBHSSEL;
    reg |= usbhssel_clock_source;

    RCU_ADDCTL = reg;
}

/*!
    \brief      configure the USBHSDV division factor
    \param[in]  usbhs_dv: USBHSDV division factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_USBHSDV_DIV2: USBHSDV input source clock divided by 2
      \arg        RCU_USBHSDV_DIV4: USBHSDV input source clock divided by 4
      \arg        RCU_USBHSDV_DIV6: USBHSDV input source clock divided by 6
      \arg        RCU_USBHSDV_DIV8: USBHSDV input source clock divided by 8
      \arg        RCU_USBHSDV_DIV10: USBHSDV input source clock divided by 10
      \arg        RCU_USBHSDV_DIV12: USBHSDV input source clock divided by 12
      \arg        RCU_USBHSDV_DIV14: USBHSDV input source clock divided by 14
      \arg        RCU_USBHSDV_DIV16: USBHSDV input source clock divided by 16
    \param[out] none
    \retval     none
*/
void rcu_usbdv_config(uint32_t usbhs_dv)
{
    uint32_t reg = 0U;

    reg = RCU_ADDCTL;

    /* usbhs input clock source division factor */
    reg &= ~RCU_ADDCTL_USBHSDV;
    reg |= usbhs_dv;

    RCU_ADDCTL = reg;
}
#endif /* GD32E50X_CL and GD32E508 */

/*!
    \brief      configure the LXTAL drive capability
    \param[in]  lxtal_dricap: drive capability of LXTAL
                only one parameter can be selected which is shown as below:
      \arg        RCU_LXTAL_LOWDRI: lower driving capability
      \arg        RCU_LXTAL_MED_LOWDRI: medium low driving capability
      \arg        RCU_LXTAL_MED_HIGHDRI: medium high driving capability
      \arg        RCU_LXTAL_HIGHDRI: higher driving capability
    \param[out] none
    \retval     none
*/
void rcu_lxtal_drive_capability_config(uint32_t lxtal_dricap)
{
    uint32_t reg;

    reg = RCU_BDCTL;

    /* reset the LXTALDRI bits and set according to lxtal_dricap */
    reg &= ~RCU_BDCTL_LXTALDRI;
    RCU_BDCTL = (reg | lxtal_dricap);
}

/*!
    \brief      wait for oscillator stabilization flags is SET or oscillator startup is timeout
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator(LXTAL)
      \arg        RCU_IRC8M: internal 8M RC oscillators(IRC8M)
      \arg        RCU_IRC48M: internal 48M RC oscillators(IRC48M)
      \arg        RCU_IRC40K: internal 40K RC oscillator(IRC40K)
      \arg        RCU_PLL_CK: phase locked loop(PLL)
      \arg        RCU_PLL1_CK: phase locked loop 1(CL, EPRT and E508 series available)
      \arg        RCU_PLL2_CK: phase locked loop 2(CL, EPRT and E508 series available)
      \arg        RCU_PLLUSB_CK: phase locked loop USB(CL and E508 series available)
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus rcu_osci_stab_wait(rcu_osci_type_enum osci)
{
    uint32_t stb_cnt = 0U;
    ErrStatus reval = ERROR;
    FlagStatus osci_stat = RESET;

    switch(osci)
    {
    /* wait HXTAL stable */
    case RCU_HXTAL:
        while((RESET == osci_stat) && (HXTAL_STARTUP_TIMEOUT != stb_cnt))
        {
            osci_stat = rcu_flag_get(RCU_FLAG_HXTALSTB);
            stb_cnt++;
        }

        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_HXTALSTB))
        {
            reval = SUCCESS;
        }
        break;

    /* wait LXTAL stable */
    case RCU_LXTAL:
        while((RESET == osci_stat) && (LXTAL_STARTUP_TIMEOUT != stb_cnt))
        {
            osci_stat = rcu_flag_get(RCU_FLAG_LXTALSTB);
            stb_cnt++;
        }

        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_LXTALSTB))
        {
            reval = SUCCESS;
        }
        break;

    /* wait IRC8M stable */
    case RCU_IRC8M:
        while((RESET == osci_stat) && (IRC8M_STARTUP_TIMEOUT != stb_cnt))
        {
            osci_stat = rcu_flag_get(RCU_FLAG_IRC8MSTB);
            stb_cnt++;
        }

        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_IRC8MSTB))
        {
            reval = SUCCESS;
        }
        break;

    /* wait IRC48M stable */
    case RCU_IRC48M:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt))
        {
            osci_stat = rcu_flag_get(RCU_FLAG_IRC48MSTB);
            stb_cnt++;
        }

        /* check whether flag is set or not */
        if (RESET != rcu_flag_get(RCU_FLAG_IRC48MSTB))
        {
            reval = SUCCESS;
        }
        break;

    /* wait IRC40K stable */
    case RCU_IRC40K:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt))
        {
            osci_stat = rcu_flag_get(RCU_FLAG_IRC40KSTB);
            stb_cnt++;
        }

        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_IRC40KSTB))
        {
            reval = SUCCESS;
        }
        break;

    /* wait PLL stable */
    case RCU_PLL_CK:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt))
        {
            osci_stat = rcu_flag_get(RCU_FLAG_PLLSTB);
            stb_cnt++;
        }

        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_PLLSTB))
        {
            reval = SUCCESS;
        }
        break;

#if defined(GD32E50X_CL)  || defined(GD32EPRT) || defined(GD32E508)
    /* wait PLL1 stable */
    case RCU_PLL1_CK:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt))
        {
            osci_stat = rcu_flag_get(RCU_FLAG_PLL1STB);
            stb_cnt++;
        }

        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_PLL1STB))
        {
            reval = SUCCESS;
        }
        break;
    /* wait PLL2 stable */
    case RCU_PLL2_CK:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt))
        {
            osci_stat = rcu_flag_get(RCU_FLAG_PLL2STB);
            stb_cnt++;
        }

        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_PLL2STB))
        {
            reval = SUCCESS;
        }
        break;
#endif /* GD32E50X_CL and GD32E50X_EPRT and GD32E508 */
#if defined(GD32E50X_CL) || defined(GD32E508)
    case RCU_PLLUSB_CK:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt))
        {
            osci_stat = rcu_flag_get(RCU_FLAG_PLLUSBSTB);
            stb_cnt++;
        }

        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_PLLUSBSTB))
        {
            reval = SUCCESS;
        }
        break;
#endif /* GD32E50X_CL and GD32E508 */

    default:
        break;
    }

    /* return value */
    return reval;
}

/*!
    \brief      turn on the oscillator
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator(LXTAL)
      \arg        RCU_IRC8M: internal 8M RC oscillators(IRC8M)
      \arg        RCU_IRC48M: internal 48M RC oscillators(IRC48M)
      \arg        RCU_IRC40K: internal 40K RC oscillator(IRC40K)
      \arg        RCU_PLL_CK: phase locked loop(PLL)
      \arg        RCU_PLL1_CK: phase locked loop 1(CL, EPRT and E508 series available)
      \arg        RCU_PLL2_CK: phase locked loop 2(CL, EPRT and E508 series available)
      \arg        RCU_PLLUSB_CK: phase locked loop USB(CL and E508 series available)
    \param[out] none
    \retval     none
*/
void rcu_osci_on(rcu_osci_type_enum osci)
{
    RCU_REG_VAL(osci) |= BIT(RCU_BIT_POS(osci));
}

/*!
    \brief      turn off the oscillator
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator(LXTAL)
      \arg        RCU_IRC8M: internal 8M RC oscillators(IRC8M)
      \arg        RCU_IRC48M: internal 48M RC oscillators(IRC48M)
      \arg        RCU_IRC40K: internal 40K RC oscillator(IRC40K)
      \arg        RCU_PLL_CK: phase locked loop(PLL)
      \arg        RCU_PLL1_CK: phase locked loop 1(CL, EPRT and E508 series available)
      \arg        RCU_PLL2_CK: phase locked loop 2(CL, EPRT and E508 series available)
      \arg        RCU_PLLUSB_CK: phase locked loop USB(CL and E508 series available)
    \param[out] none
    \retval     none
*/
void rcu_osci_off(rcu_osci_type_enum osci)
{
    RCU_REG_VAL(osci) &= ~BIT(RCU_BIT_POS(osci));
}

/*!
    \brief      enable the oscillator bypass mode, HXTALEN or LXTALEN must be reset before it
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator(LXTAL)
    \param[out] none
    \retval     none
*/
void rcu_osci_bypass_mode_enable(rcu_osci_type_enum osci)
{
    uint32_t reg;

    switch(osci)
    {
    /* enable HXTAL to bypass mode */
    case RCU_HXTAL:
        reg = RCU_CTL;
        RCU_CTL &= ~RCU_CTL_HXTALEN;
        RCU_CTL = (reg | RCU_CTL_HXTALBPS);
        break;
    /* enable LXTAL to bypass mode */
    case RCU_LXTAL:
        reg = RCU_BDCTL;
        RCU_BDCTL &= ~RCU_BDCTL_LXTALEN;
        RCU_BDCTL = (reg | RCU_BDCTL_LXTALBPS);
        break;
    case RCU_IRC8M:
    case RCU_IRC48M:
    case RCU_IRC40K:
    case RCU_PLL_CK:
#if defined(GD32E50X_CL) || defined(GD32EPRT) || defined(GD32E508)
    case RCU_PLL1_CK:
    case RCU_PLL2_CK:
#endif /* GD32E50X_CL and GD32EPRT and GD32E508 */
        break;
    default:
        break;
    }
}

/*!
    \brief      disable the oscillator bypass mode, HXTALEN or LXTALEN must be reset before it
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator(LXTAL)
    \param[out] none
    \retval     none
*/
void rcu_osci_bypass_mode_disable(rcu_osci_type_enum osci)
{
    uint32_t reg;

    switch(osci)
    {
    /* disable HXTAL to bypass mode */
    case RCU_HXTAL:
        reg = RCU_CTL;
        RCU_CTL &= ~RCU_CTL_HXTALEN;
        RCU_CTL = (reg & ~RCU_CTL_HXTALBPS);
        break;
    /* disable LXTAL to bypass mode */
    case RCU_LXTAL:
        reg = RCU_BDCTL;
        RCU_BDCTL &= ~RCU_BDCTL_LXTALEN;
        RCU_BDCTL = (reg & ~RCU_BDCTL_LXTALBPS);
        break;
    case RCU_IRC8M:
    case RCU_IRC48M:
    case RCU_IRC40K:
    case RCU_PLL_CK:
#if defined(GD32E50X_CL) || defined(GD32EPRT) || defined(GD32E508)
    case RCU_PLL1_CK:
    case RCU_PLL2_CK:
#endif /* GD32E50X_CL and GD32EPRT and GD32E508 */
        break;
    default:
        break;
    }
}

/*!
    \brief      set the IRC8M adjust value
    \param[in]  irc8m_adjval: IRC8M adjust value, must be between 0 and 0x1F
      \arg        0x00 - 0x1F
    \param[out] none
    \retval     none
*/
void rcu_irc8m_adjust_value_set(uint32_t irc8m_adjval)
{
    uint32_t reg;

    reg = RCU_CTL;
    /* reset the IRC8MADJ bits and set according to irc8m_adjval */
    reg &= ~RCU_CTL_IRC8MADJ;
    RCU_CTL = (reg | ((irc8m_adjval & RCU_IRC8M_ADJUST_MASK) << RCU_IRC8M_ADJUST_OFFSET));
}

/*!
    \brief      enable the HXTAL clock monitor
    \param[in]  none
    \param[out] none
    \retval     none
*/

void rcu_hxtal_clock_monitor_enable(void)
{
    RCU_CTL |= RCU_CTL_CKMEN;
}

/*!
    \brief      disable the HXTAL clock monitor
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_hxtal_clock_monitor_disable(void)
{
    RCU_CTL &= ~RCU_CTL_CKMEN;
}


/*!
    \brief      deep-sleep mode voltage select
    \param[in]  dsvol: deep sleep mode voltage
                only one parameter can be selected which is shown as below:
      \arg        RCU_DEEPSLEEP_V_1_0: the core voltage is 1.0V
      \arg        RCU_DEEPSLEEP_V_0_9: the core voltage is 0.9V
      \arg        RCU_DEEPSLEEP_V_0_8: the core voltage is 0.8V
      \arg        RCU_DEEPSLEEP_V_0_7: the core voltage is 0.7V
    \param[out] none
    \retval     none
*/
void rcu_deepsleep_voltage_set(uint32_t dsvol)
{
    dsvol &= RCU_DSV_DSLPVS;
    RCU_DSV = dsvol;
}

/*!
    \brief      get the system clock, bus and peripheral clock frequency
    \param[in]  clock: the clock frequency which to get
                only one parameter can be selected which is shown as below:
      \arg        CK_SYS: system clock frequency
      \arg        CK_AHB: AHB clock frequency
      \arg        CK_APB1: APB1 clock frequency
      \arg        CK_APB2: APB2 clock frequency
      \arg        CK_USART: USART5 clock frequency
    \param[out] none
    \retval     clock frequency of system, AHB, APB1, APB2
*/
uint32_t rcu_clock_freq_get(rcu_clock_freq_enum clock)
{
    uint32_t sws, ck_freq = 0U;
    uint32_t cksys_freq, ahb_freq, apb1_freq, apb2_freq;
    uint32_t usart_freq = 0U;
    uint32_t pllsel, pllpresel, predv0sel, pllmf,ck_src, idx, clk_exp;
#if defined(GD32E50X_CL) || defined(GD32EPRT) || defined(GD32E508)
    uint32_t predv0, predv1, pll1mf;
#endif /* GD32E50X_CL and GD32EPRT and GD32E508*/

    /* exponent of AHB, APB1 and APB2 clock divider */
    uint8_t ahb_exp[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
    uint8_t apb1_exp[8] = {0, 0, 0, 0, 1, 2, 3, 4};
    uint8_t apb2_exp[8] = {0, 0, 0, 0, 1, 2, 3, 4};

    sws = GET_BITS(RCU_CFG0, 2, 3);
    switch(sws)
    {
    /* IRC8M is selected as CK_SYS */
    case SEL_IRC8M:
        cksys_freq = IRC8M_VALUE;
        break;
    /* HXTAL is selected as CK_SYS */
    case SEL_HXTAL:
        cksys_freq = HXTAL_VALUE;
        break;
    /* PLL is selected as CK_SYS */
    case SEL_PLL:
        /* PLL clock source selection, HXTAL, IRC48M or IRC8M/2 */
        pllsel = (RCU_CFG0 & RCU_CFG0_PLLSEL);

        if(RCU_PLLSRC_HXTAL_IRC48M == pllsel)
        {
            /* PLL clock source is HXTAL or IRC48M */
            pllpresel = (RCU_CFG1 & RCU_CFG1_PLLPRESEL);

            if(RCU_PLLPRESRC_HXTAL == pllpresel)
            {
                /* PLL clock source is HXTAL */
                ck_src = HXTAL_VALUE;
            }else{
                /* PLL clock source is IRC48 */
                ck_src = IRC48M_VALUE;
            }

#if defined(GD32E50X_HD)
            predv0sel = (RCU_CFG0 & RCU_CFG0_PREDV0);
            /* PREDV0 input source clock divided by 2 */
            if(RCU_CFG0_PREDV0 == predv0sel)
            {
                ck_src = HXTAL_VALUE/2U;
            }
#elif defined(GD32E50X_CL) || defined(GD32EPRT) || defined(GD32E508)
            predv0sel = (RCU_CFG1 & RCU_CFG1_PREDV0SEL);
            /* source clock use PLL1 */
            if(RCU_PREDV0SRC_CKPLL1 == predv0sel)
            {
                predv1 = ((RCU_CFG1 & RCU_CFG1_PREDV1) >> RCU_CFG1_PREDV1_OFFSET) + 1U;
                pll1mf = (uint32_t)((RCU_CFG1 & RCU_CFG1_PLL1MF) >> RCU_CFG1_PLL1MF_OFFSET) + 2U;
                if(17U == pll1mf)
                {
                    pll1mf = 20U;
                }
                ck_src = (ck_src/predv1)*pll1mf;
            }
            predv0 = (RCU_CFG1 & RCU_CFG1_PREDV0) + 1U;
            ck_src /= predv0;
#endif /* GD32E50X_HD */
        }else{
            /* PLL clock source is IRC8M/2 */
            ck_src = IRC8M_VALUE/2U;
        }

        /* PLL multiplication factor */
        pllmf = GET_BITS(RCU_CFG0, 18, 21);
        if((RCU_CFG0 & RCU_CFG0_PLLMF_4))
        {
            pllmf |= 0x10U;
        }
        if((RCU_CFG0 & RCU_CFG0_PLLMF_5))
        {
            pllmf |= 0x20U;
        }
        if(pllmf < 15U)
        {
            pllmf += 2U;
        }else if((pllmf >= 15U) && (pllmf <= 64U))
        {
            pllmf += 1U;
        }
        cksys_freq = ck_src*pllmf;
#if defined(GD32E50X_CL) || defined(GD32EPRT) || defined(GD32E508)
        if(15U == pllmf)
        {
            cksys_freq = ck_src*6U + ck_src/2U;
        }
#endif /* GD32E50X_CL and GD32EPRT and GD32E508 */

        break;
    /* IRC8M is selected as CK_SYS */
    default:
        cksys_freq = IRC8M_VALUE;
        break;
    }

    /* calculate AHB clock frequency */
    idx = GET_BITS(RCU_CFG0, 4, 7);
    clk_exp = ahb_exp[idx];
    ahb_freq = cksys_freq >> clk_exp;

    /* calculate APB1 clock frequency */
    idx = GET_BITS(RCU_CFG0, 8, 10);
    clk_exp = apb1_exp[idx];
    apb1_freq = ahb_freq >> clk_exp;

    /* calculate APB2 clock frequency */
    idx = GET_BITS(RCU_CFG0, 11, 13);
    clk_exp = apb2_exp[idx];
    apb2_freq = ahb_freq >> clk_exp;

    /* return the clocks frequency */
    switch(clock)
    {
    case CK_SYS:
        ck_freq = cksys_freq;
        break;
    case CK_AHB:
        ck_freq = ahb_freq;
        break;
    case CK_APB1:
        ck_freq = apb1_freq;
        break;
    case CK_APB2:
        ck_freq = apb2_freq;
        break;
    case CK_USART:
        /* calculate USART5 clock frequency */
        if(RCU_USART5SRC_CKAPB2 == (RCU_CFG2 & RCU_CFG2_USART5SEL))
        {
            usart_freq = apb2_freq;
        }else if(RCU_USART5SRC_CKSYS == (RCU_CFG2 & RCU_CFG2_USART5SEL))
        {
            usart_freq = cksys_freq;
        }else if(RCU_USART5SRC_LXTAL == (RCU_CFG2 & RCU_CFG2_USART5SEL))
        {
            usart_freq = LXTAL_VALUE;
        }else if(RCU_USART5SRC_IRC8M == (RCU_CFG2 & RCU_CFG2_USART5SEL))
        {
            usart_freq = IRC8M_VALUE;
        }else{
        }
        ck_freq = usart_freq;
        break;
    default:
        break;
    }
    return ck_freq;
}

/*!
    \brief      get the clock stabilization and periphral reset flags
    \param[in]  flag: the clock stabilization and periphral reset flags, refer to rcu_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_FLAG_IRC8MSTB: IRC8M stabilization flag
      \arg        RCU_FLAG_HXTALSTB: HXTAL stabilization flag
      \arg        RCU_FLAG_PLLSTB: PLL stabilization flag
      \arg        RCU_FLAG_PLLUSBSTB: PLLUSB stabilization flag(CL and E508 series available)
      \arg        RCU_FLAG_PLL1STB: PLL1 stabilization flag(CL, EPRT and E508 series available)
      \arg        RCU_FLAG_PLL2STB: PLL2 stabilization flag(CL, EPRT and E508 series available)
      \arg        RCU_FLAG_LXTALSTB: LXTAL stabilization flag
      \arg        RCU_FLAG_IRC40KSTB: IRC40K stabilization flag
      \arg        RCU_FLAG_IRC48MSTB: IRC48M stabilization flag
      \arg        RCU_FLAG_BORRST: BOR reset flag
      \arg        RCU_FLAG_EPRST: external PIN reset flag
      \arg        RCU_FLAG_PORRST: power reset flag
      \arg        RCU_FLAG_SWRST: software reset flag
      \arg        RCU_FLAG_FWDGTRST: free watchdog timer reset flag
      \arg        RCU_FLAG_WWDGTRST: window watchdog timer reset flag
      \arg        RCU_FLAG_LPRST: low-power reset flag
    \param[out] none
    \retval     none
*/
FlagStatus rcu_flag_get(rcu_flag_enum flag)
{
    /* get the rcu flag */
    if(RESET != (RCU_REG_VAL(flag) & BIT(RCU_BIT_POS(flag))))
    {
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear all the reset flag
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_all_reset_flag_clear(void)
{
    RCU_RSTSCK |= RCU_RSTSCK_RSTFC;
}

/*!
    \brief      get the clock stabilization interrupt and ckm flags
    \param[in]  int_flag: interrupt and ckm flags, refer to rcu_int_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_FLAG_IRC40KSTB: IRC40K stabilization interrupt flag
      \arg        RCU_INT_FLAG_LXTALSTB: LXTAL stabilization interrupt flag
      \arg        RCU_INT_FLAG_IRC8MSTB: IRC8M stabilization interrupt flag
      \arg        RCU_INT_FLAG_HXTALSTB: HXTAL stabilization interrupt flag
      \arg        RCU_INT_FLAG_PLLSTB: PLL stabilization interrupt flag
      \arg        RCU_INT_FLAG_PLL1STB: PLL1 stabilization interrupt flag(CL, EPRT and E508 series available)
      \arg        RCU_INT_FLAG_PLL2STB: PLL2 stabilization interrupt flag(CL, EPRT and E508 series available)
      \arg        RCU_INT_FLAG_PLLUSBSTB: PLLUSB stabilization interrupt flag(CL and E508 series available)
      \arg        RCU_INT_FLAG_CKM: HXTAL clock stuck interrupt flag
      \arg        RCU_INT_FLAG_IRC48MSTB: IRC48M stabilization interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus rcu_interrupt_flag_get(rcu_int_flag_enum int_flag)
{
    /* get the rcu interrupt flag */
    if(RESET != (RCU_REG_VAL(int_flag) & BIT(RCU_BIT_POS(int_flag))))
    {
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear the interrupt flags
    \param[in]  int_flag: clock stabilization and stuck interrupt flags clear, refer to rcu_int_flag_clear_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_FLAG_IRC40KSTB_CLR: IRC40K stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_LXTALSTB_CLR: LXTAL stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_IRC8MSTB_CLR: IRC8M stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_HXTALSTB_CLR: HXTAL stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_PLLSTB_CLR: PLL stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_PLL1STB_CLR: PLL1 stabilization interrupt flag clear(CL, EPRT and E508 series available)
      \arg        RCU_INT_FLAG_PLL2STB_CLR: PLL2 stabilization interrupt flag clear(CL, EPRT and E508 series available)
      \arg        RCU_INT_FLAG_PLLUSBSTB_CLR: PLLUS stabilization interrupt flag clear(CL and E508 series available)
      \arg        RCU_INT_FLAG_CKM_CLR: clock stuck interrupt flag clear
      \arg        RCU_INT_FLAG_IRC48MSTB_CLR: IRC48M stabilization interrupt flag clear
    \param[out] none
    \retval     none
*/
void rcu_interrupt_flag_clear(rcu_int_flag_clear_enum int_flag)
{
    RCU_REG_VAL(int_flag) |= BIT(RCU_BIT_POS(int_flag));
}

/*!
    \brief      enable the stabilization interrupt
    \param[in]  interrupt clock stabilization interrupt, refer to rcu_int_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_IRC40KSTB: IRC40K stabilization interrupt enable
      \arg        RCU_INT_LXTALSTB: LXTAL stabilization interrupt enable
      \arg        RCU_INT_IRC8MSTB: IRC8M stabilization interrupt enable
      \arg        RCU_INT_HXTALSTB: HXTAL stabilization interrupt enable
      \arg        RCU_INT_PLLSTB: PLL stabilization interrupt enable
      \arg        RCU_INT_PLL1STB: PLL1 stabilization interrupt enable(CL, EPRT and E508 series available)
      \arg        RCU_INT_PLL2STB: PLL2 stabilization interrupt enable(CL, EPRT and E508 series available)
      \arg        RCU_INT_PLLUSBSTB: PLLUSB stabilization interrupt enable(CL and E508 series available)
      \arg        RCU_INT_IRC48MSTB: IRC48M stabilization interrupt enable
    \param[out] none
    \retval     none
*/
void rcu_interrupt_enable(rcu_int_enum interrupt)
{
    RCU_REG_VAL(interrupt) |= BIT(RCU_BIT_POS(interrupt));
}

/*!
    \brief      disable the stabilization interrupt
    \param[in]  interrupt clock stabilization interrupt, refer to rcu_int_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_IRC40KSTB: IRC40K stabilization interrupt enable
      \arg        RCU_INT_LXTALSTB: LXTAL stabilization interrupt enable
      \arg        RCU_INT_IRC8MSTB: IRC8M stabilization interrupt enable
      \arg        RCU_INT_HXTALSTB: HXTAL stabilization interrupt enable
      \arg        RCU_INT_PLLSTB: PLL stabilization interrupt enable
      \arg        RCU_INT_PLL1STB: PLL1 stabilization interrupt enable(CL, EPRT and E508 series available)
      \arg        RCU_INT_PLL2STB: PLL2 stabilization interrupt enable(CL, EPRT and E508 series available)
      \arg        RCU_INT_PLLUSBSTB: PLLUSB stabilization interrupt enable(CL and E508 series available)
      \arg        RCU_INT_IRC48MSTB: IRC48M stabilization interrupt enable
    \param[out] none
    \retval     none
*/
void rcu_interrupt_disable(rcu_int_enum interrupt)
{
    RCU_REG_VAL(interrupt) &= ~BIT(RCU_BIT_POS(interrupt));
}
