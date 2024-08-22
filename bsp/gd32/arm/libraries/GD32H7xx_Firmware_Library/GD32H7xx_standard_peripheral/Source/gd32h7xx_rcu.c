/*!
    \file    gd32h7xx_rcu.c
    \brief   RCU driver

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

#include "gd32h7xx_rcu.h"

/* define clock source */
#define SEL_IRC64MDIV                ((uint16_t)0U)                /* IRC64M is selected as CK_SYS */
#define SEL_HXTAL                    ((uint16_t)1U)                /* HXTAL is selected as CK_SYS */
#define SEL_LPIRC4M                  ((uint16_t)2U)                /* LPIRC4M is selected as CK_SYS */
#define SEL_PLL0P                    ((uint16_t)3U)                /* PLL0P is selected as CK_SYS */
/* define startup timeout count */
#define OSC_STARTUP_TIMEOUT          ((uint32_t)0x000fffffU)

/* RCU IRC64M and LPIRC4M adjust value mask and offset */
#define RCU_IRC64M_ADJUST_MASK       ((uint8_t)0x7FU)
#define RCU_LPIRC4M_ADJUST_MASK      ((uint8_t)0x3FU)
#define RCU_LPIRC4M_ADJUST_OFFSET    ((uint32_t)2U)
/* RCU_PLLxN, RCU_PLLxP, RCU_PLLxQ, RCU_PLLxR offset */
#define RCU_PLLNOFFSET               ((uint32_t)6U)
#define RCU_PLLPOFFSET               ((uint32_t)16U)
#define RCU_PLLROFFSET               ((uint32_t)24U)
#define RCU_PLL1QOFFSET              ((uint32_t)8U)
#define RCU_PLL2QOFFSET              ((uint32_t)16U)

/* function to calculate the PLL output frequency*/
static uint32_t rcu_pll_clock_freq_cal(uint32_t pllinputfreq, uint32_t pll_psc, uint32_t pll_n, uint32_t fracn, uint32_t pll_pqr);

/*!
    \brief      deinitialize the RCU
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_deinit(void)
{
    /* enable IRC64M */
    RCU_CTL |= RCU_CTL_IRC64MEN;
    while(0U == (RCU_CTL & RCU_CTL_IRC64MSTB))
    {
    }

    RCU_CFG0 &= ~RCU_CFG0_SCS;

    /* reset CFG0 register */
    RCU_CFG0 &= ~(RCU_CFG0_SCS | RCU_CFG0_AHBPSC | RCU_CFG0_APB1PSC | RCU_CFG0_APB2PSC |
                  RCU_CFG0_RTCDIV | RCU_CFG0_APB3PSC | RCU_CFG0_APB4PSC | RCU_CFG0_I2C0SEL);
    /* reset CTL register */
    RCU_CTL &= ~(RCU_CTL_HXTALEN | RCU_CTL_CKMEN | RCU_CTL_PLL0EN | RCU_CTL_PLL1EN
                 | RCU_CTL_PLL2EN);
    RCU_CTL &= ~(RCU_CTL_HXTALBPS);
    /* reset PLL0 register */
    RCU_PLL0 = 0x01002020U;
    /* reset PLL1 register */
    RCU_PLL1 = 0x01012020U;
    /* reset PLL2 register */
    RCU_PLL2 = 0x01012020U;
    /* reset PLLALL register */
    RCU_PLLALL = 0x00000000U;
    /* reset PLL0FRA register */
    RCU_PLL0FRA = 0x00000000U;
    /* reset PLL1FRA register */
    RCU_PLL1FRA = 0x00000000U;
    /* reset PLL2FRA register */
    RCU_PLL2FRA = 0x00000000U;
    /* reset INT register */
    RCU_INT = 0x14ff0000U;
    /* reset ADDINT register */
    RCU_ADDINT = 0x00700000U;
    /* reset CFG1 register */
    RCU_CFG1 = 0x00003F00U;
    /* reset CFG2 register */
    RCU_CFG2 = 0x00000000U;
    /* reset CFG3 register */
    RCU_CFG3 = 0x00000000U;
    /* reset CFG4 register */
    RCU_CFG4 = 0x00000000U;
    /* reset CFG5 register */
    RCU_CFG5 = 0x00000000U;
}

/*!
    \brief      enable the peripherals clock
    \param[in]  periph: RCU peripherals, refer to rcu_periph_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_ENETx (x = 0,1): ENET1x clock
      \arg        RCU_ENETxTX (x = 0,1): ENET1TX xclock
      \arg        RCU_ENETxRX (x = 0,1): ENET1RXx clock
      \arg        RCU_ENETxPTP (x = 0,1): ENET1PTP clock
      \arg        RCU_USBHSx (x = 0,1): USBHS clock
      \arg        RCU_USBHSxULPI (x = 0,1): USBHSULPI clock
      \arg        RCU_DMAx (x = 0,1): DMA clock
      \arg        RCU_DMAMUX: DMAMUX clock
      \arg        RCU_DCI: DCI clock
      \arg        RCU_FAC: FAC clock
      \arg        RCU_SDIOx (x = 0,1): SDIO clock
      \arg        RCU_CAU: CAU clock
      \arg        RCU_HAU: HAU clock
      \arg        RCU_TRNG: TRNG clock
      \arg        RCU_TMU: TMU clock
      \arg        RCU_RAMECCMUx (x = 0,1): RAMECCMU clock
      \arg        RCU_EXMC: EXMC clock
      \arg        RCU_IPA: IPA clock
      \arg        RCU_MDMA: MDMMA clock
      \arg        RCU_OSPIM: OSPIM clock
      \arg        RCU_OSPIx (x = 0,1): OSPI0 clock
      \arg        RCU_RTDECx (x = 0,1): RTDEC0 clock
      \arg        RCU_CPU: CPU clock
      \arg        RCU_GPIOx (x = A,B,C,D,E,F,G,H,J,K): GPIO ports clock
      \arg        RCU_BKPSRAM: BKPSRAM clock
      \arg        RCU_CRC: CRC clock
      \arg        RCU_HWSEM: HWSEM clock
      \arg        RCU_TIMERx (x = 0,1,2,3,4,5,6,7,14,15,16,22,23,30,31,40,41,42,43,44,50,51): TIMER clock
      \arg        RCU_RSPDIF: RSPDIF clock
      \arg        RCU_SPIx (x = 0,1,2,3,4,5): SPI clock
      \arg        RCU_MDIO: MDIO clock
      \arg        RCU_USARTx (x = 0,1,2,5): USART clock
      \arg        RCU_UARTx (x = 3,4,6,7): UART clock
      \arg        RCU_I2Cx (x = 0,1,2,3): I2C clock
      \arg        RCU_CTC: CTC clock
      \arg        RCU_DACHOLD: DACHOLD clock
      \arg        RCU_DAC: DAC clock
      \arg        RCU_ADCx (x = 0,1,2): ADC clock
      \arg        RCU_HPDF: HPDF clock
      \arg        RCU_SAIx (x = 0,1,2): SAI clock
      \arg        RCU_EDOUT: EDOUT clock
      \arg        RCU_TRIGSEL: TRIGSEL clock
      \arg        RCU_TLI: TLI clock
      \arg        RCU_WWDGT: WWDGT clock
      \arg        RCU_SYSCFG: SYSCFG clock
      \arg        RCU_CMP: CMP clock
      \arg        RCU_VREF: VREF clock
      \arg        RCU_LPDTS: LPDTS clock
      \arg        RCU_PMU: PMU clock
      \arg        RCU_RTC: RTC clock
      \arg        RCU_CANx (x = 0,1,2): can clock
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
      \arg        RCU_ENETx (x = 0,1): ENET clock
      \arg        RCU_ENETxTX (x = 0,1): ENETTX clock
      \arg        RCU_ENETxRX (x = 0,1): ENETRX clock
      \arg        RCU_ENETxPTP (x = 0,1): ENETPTP clock
      \arg        RCU_USBHSx (x = 0,1): USBHS clock
      \arg        RCU_USBHSxULPI (x = 0,1): USBHSULPI clock
      \arg        RCU_DMAx (x = 0,1): DMA clock
      \arg        RCU_DMAMUX: DMAMUX clock
      \arg        RCU_DCI: DCI clock
      \arg        RCU_FAC: FAC clock
      \arg        RCU_SDIOx (x = 0,1): SDIO clock
      \arg        RCU_CAU: CAU clock
      \arg        RCU_HAU: HAU clock
      \arg        RCU_TRNG: TRNG clock
      \arg        RCU_TMU: TMU clock
      \arg        RCU_RAMECCMUx (x = 0,1): RAMECCMU clock
      \arg        RCU_EXMC: EXMC clock
      \arg        RCU_IPA: IPA clock
      \arg        RCU_MDMA: MDMMA clock
      \arg        RCU_OSPIM: OSPIM clock
      \arg        RCU_OSPIx (x = 0,1): OSPI0 clock
      \arg        RCU_RTDECx (x = 0,1): RTDEC0 clock
      \arg        RCU_CPU: CPU clock
      \arg        RCU_GPIOx (x = A,B,C,D,E,F,G,H,J,K): GPIO ports clock
      \arg        RCU_BKPSRAM: BKPSRAM clock
      \arg        RCU_CRC: CRC clock
      \arg        RCU_HWSEM: HWSEM clock
      \arg        RCU_TIMERx (x = 0,1,2,3,4,5,6,7,14,15,16,22,23,30,31,40,41,42,43,44,50,51): TIMER clock
      \arg        RCU_RSPDIF: RSPDIF clock
      \arg        RCU_SPIx (x = 0,1,2,3,4,5): SPI clock
      \arg        RCU_MDIO: MDIO clock
      \arg        RCU_USARTx (x = 0,1,2,5): USART clock
      \arg        RCU_UARTx (x = 3,4,6,7): UART clock
      \arg        RCU_I2Cx (x = 0,1,2,3): I2C clock
      \arg        RCU_CTC: CTC clock
      \arg        RCU_DACHOLD: DACHOLD clock
      \arg        RCU_DAC: DAC clock
      \arg        RCU_ADCx (x = 0,1,2): ADC clock
      \arg        RCU_HPDF: HPDF clock
      \arg        RCU_SAIx (x = 0,1,2): SAI clock
      \arg        RCU_EDOUT: EDOUT clock
      \arg        RCU_TRIGSEL: TRIGSEL clock
      \arg        RCU_TLI: TLI clock
      \arg        RCU_WWDGT: WWDGT clock
      \arg        RCU_SYSCFG: SYSCFG clock
      \arg        RCU_CMP: CMP clock
      \arg        RCU_VREF: VREF clock
      \arg        RCU_LPDTS: LPDTS clock
      \arg        RCU_PMU: PMU clock
      \arg        RCU_RTC: RTC clock
      \arg        RCU_CANx (x = 0,1,2): can clock
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
      \arg        RCU_ENETx_SLP (x = 0,1): ENET clock
      \arg        RCU_ENETxTX_SLP (x = 0,1): ENETTX clock
      \arg        RCU_ENETxRX_SLP (x = 0,1): ENETRX clock
      \arg        RCU_ENETxPTP_SLP (x = 0,1): ENETPTP clock
      \arg        RCU_USBHSx_SLP (x = 0,1): USBHS clock
      \arg        RCU_USBHSxULPI_SLP (x = 0,1): USBHSULPI clock
      \arg        RCU_SRAM0_SLP: SRAM0 clock
      \arg        RCU_SRAM1_SLP: SRAM1 clock
      \arg        RCU_DMAx_SLP (x = 0,1): DMA clock
      \arg        RCU_DMAMUX_SLP: DMAMUX clock
      \arg        RCU_DCI_SLP: DCI clock
      \arg        RCU_FAC_SLP: TRNG clock
      \arg        RCU_SDIOx_SLP (x = 0,1): SDIO clock
      \arg        RCU_CAU_SLP: CAU clock
      \arg        RCU_HAU_SLP: HAU clock
      \arg        RCU_TRNG_SLP: TRNG clock
      \arg        RCU_TMU_SLP: TMU clock
      \arg        RCU_RAMECCMUx_SLP (x = 0,1): RAMECCMU clock
      \arg        RCU_EXMC_SLP: EXMC clock
      \arg        RCU_IPA_SLP: IPA clock
      \arg        RCU_SDIOx_SLP (x = 0,1): SDIO clock
      \arg        RCU_MDMA_SLP: MDMMA clock
      \arg        RCU_OSPIM_SLP: OSPIM clock
      \arg        RCU_OSPIx_SLP (x = 0,1): OSPI0 clock
      \arg        RCU_RTDECx_SLP (x = 0,1): RTDEC0 clock
      \arg        RCU_AXISRAM_SLP: AXISRAM clock
      \arg        RCU_FMC_SLP: SRAM1 clock
      \arg        RCU_GPIOx_SLP (x = A,B,C,D,E,F,G,H,J,K): GPIO ports clock
      \arg        RCU_BKPSRAM_SLP: BKPSRAM clock
      \arg        RCU_CRC_SLP: CRC clock
      \arg        RCU_TIMERx_SLP (x = 0,1,2,3,4,5,6,7,14,15,16,22,23,30,31,40,41,42,43,44,50,51): TIMER clock
      \arg        RCU_RSPDIF_SLP: RSPDIF clock
      \arg        RCU_SPIx_SLP (x = 0,1,2,3,4,5): SPI clock
      \arg        RCU_MDIO_SLP: MDIO clock
      \arg        RCU_USARTx_SLP (x = 0,1,2,5): USART clock
      \arg        RCU_UARTx_SLP (x = 3,4,6,7): UART clock
      \arg        RCU_I2Cx_SLP (x = 0,1,2,3): I2C clock
      \arg        RCU_CTC_SLP: CTC clock
      \arg        RCU_DACHOLD_SLP: DACHOLD clock
      \arg        RCU_DAC_SLP: DAC clock
      \arg        RCU_ADCx_SLP (x = 0,1,2): ADC clock
      \arg        RCU_HPDF_SLP: HPDF clock
      \arg        RCU_SAIx_SLP (x = 0,1,2): SAI clock
      \arg        RCU_EDOUT_SLP: EDOUT clock
      \arg        RCU_TRIGSEL_SLP: TRIGSEL clock
      \arg        RCU_TLI_SLP: TLI clock
      \arg        RCU_WWDGT_SLP: WWDGT clock
      \arg        RCU_SYSCFG_SLP: SYSCFG clock
      \arg        RCU_CMP_SLP: CMP clock
      \arg        RCU_VREF_SLP: VREF clock
      \arg        RCU_LPDTS_SLP: LPDTS clock
      \arg        RCU_PMU_SLP: PMU clock
      \arg        RCU_CANx_SLP (x = 0,1,2): can clock
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
      \arg        RCU_ENETx_SLP (x = 0,1): ENET clock
      \arg        RCU_ENETxTX_SLP (x = 0,1): ENETTX clock
      \arg        RCU_ENETxRX_SLP (x = 0,1): ENETRX clock
      \arg        RCU_ENETxPTP_SLP (x = 0,1): ENETPTP clock
      \arg        RCU_USBHSx_SLP (x = 0,1): USBHS clock
      \arg        RCU_USBHSxULPI_SLP (x = 0,1): USBHSULPI clock
      \arg        RCU_SRAM0_SLP: SRAM0 clock
      \arg        RCU_SRAM1_SLP: SRAM1 clock
      \arg        RCU_DMAx_SLP (x = 0,1): DMA clock
      \arg        RCU_DMAMUX_SLP: DMAMUX clock
      \arg        RCU_DCI_SLP: DCI clock
      \arg        RCU_FAC_SLP: TRNG clock
      \arg        RCU_SDIOx_SLP (x = 0,1): SDIO clock
      \arg        RCU_CAU_SLP: CAU clock
      \arg        RCU_HAU_SLP: HAU clock
      \arg        RCU_TRNG_SLP: TRNG clock
      \arg        RCU_TMU_SLP: TMU clock
      \arg        RCU_RAMECCMUx_SLP (x = 0,1): RAMECCMU clock
      \arg        RCU_EXMC_SLP: EXMC clock
      \arg        RCU_IPA_SLP: IPA clock
      \arg        RCU_SDIOx_SLP (x = 0,1): SDIO clock
      \arg        RCU_MDMA_SLP: MDMMA clock
      \arg        RCU_OSPIM_SLP: OSPIM clock
      \arg        RCU_OSPIx_SLP (x = 0,1): OSPI0 clock
      \arg        RCU_RTDECx_SLP (x = 0,1): RTDEC0 clock
      \arg        RCU_AXISRAM_SLP: AXISRAM clock
      \arg        RCU_FMC_SLP: SRAM1 clock
      \arg        RCU_GPIOx_SLP (x = A,B,C,D,E,F,G,H,J,K): GPIO ports clock
      \arg        RCU_BKPSRAM_SLP: BKPSRAM clock
      \arg        RCU_CRC_SLP: CRC clock
      \arg        RCU_TIMERx_SLP (x = 0,1,2,3,4,5,6,7,14,15,16,22,23,30,31,40,41,42,43,44,50,51): TIMER clock
      \arg        RCU_RSPDIF_SLP: RSPDIF clock
      \arg        RCU_SPIx_SLP (x = 0,1,2,3,4,5): SPI clock
      \arg        RCU_MDIO_SLP: MDIO clock
      \arg        RCU_USARTx_SLP (x = 0,1,2,5): USART clock
      \arg        RCU_UARTx_SLP (x = 3,4,6,7): UART clock
      \arg        RCU_I2Cx_SLP (x = 0,1,2,3): I2C clock
      \arg        RCU_CTC_SLP: CTC clock
      \arg        RCU_DACHOLD_SLP: DACHOLD clock
      \arg        RCU_DAC_SLP: DAC clock
      \arg        RCU_ADCx_SLP (x = 0,1,2): ADC clock
      \arg        RCU_HPDF_SLP: HPDF clock
      \arg        RCU_SAIx_SLP (x = 0,1,2): SAI clock
      \arg        RCU_EDOUT_SLP: EDOUT clock
      \arg        RCU_TRIGSEL_SLP: TRIGSEL clock
      \arg        RCU_TLI_SLP: TLI clock
      \arg        RCU_WWDGT_SLP: WWDGT clock
      \arg        RCU_SYSCFG_SLP: SYSCFG clock
      \arg        RCU_CMP_SLP: CMP clock
      \arg        RCU_VREF_SLP: VREF clock
      \arg        RCU_LPDTS_SLP: LPDTS clock
      \arg        RCU_PMU_SLP: PMU clock
      \arg        RCU_CANx_SLP (x = 0,1,2): can clock
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
      \arg        RCU_ENETxRST (x = 0,1): reset ENET
      \arg        RCU_USBHSxRST (x = 0,1): reset USBHS
      \arg        RCU_DMAxRST (x = 0,1): reset DMA
      \arg        RCU_DMAMUXRST: reset DMAMUX
      \arg        RCU_DCIRST: reset DCI
      \arg        RCU_FACRST: reset FAC
      \arg        RCU_SDIOxRST (x = 0,1): reset SDIO
      \arg        RCU_CAURST: reset CAU
      \arg        RCU_HAURST: reset HAU
      \arg        RCU_TRNGRST: reset TRNG
      \arg        RCU_TMURST: reset TMU
      \arg        RCU_EXMCRST: reset EXMC
      \arg        RCU_IPARST: reset IPA
      \arg        RCU_MDMARST: reset MDMA
      \arg        RCU_OSPIMRST (x = 0,1): reset OSPIM
      \arg        RCU_OSPIxRST (x = 0,1): reset OSPI
      \arg        RCU_RTDECxRST (x = 0,1): reset RTDEC
      \arg        RCU_GPIOxRST (x = A,B,C,D,E,F,G,H,J,K): reset GPIO ports
      \arg        RCU_CRCRST: reset CRC
      \arg        RCU_HWSEMRST: reset HWSEM
      \arg        RCU_TIMERxRST (x = 0,1,2,3,4,5,6,7,14,15,16,22,23,30,31,40,41,42,43,44,50,51): reset TIMER
      \arg        RCU_RSPDIFRST: reset RSPDIF
      \arg        RCU_SPIxRST (x = 0,1,2,3,4,5): reset SPI
      \arg        RCU_MDIORST: reset MDIO
      \arg        RCU_USARTxRST (x = 0,1,2,5): reset USART
      \arg        RCU_UARTxRST (x = 3,4,6,7): reset UART
      \arg        RCU_I2CxRST (x = 0,1,2,3): reset I2C
      \arg        RCU_CTCRST: reset CTC
      \arg        RCU_DACHOLDRST: reset DACHOLD
      \arg        RCU_DACRST: reset DAC
      \arg        RCU_ADCxRST (x = 0,1,2): reset ADC
      \arg        RCU_HPDFRST: reset HPDF
      \arg        RCU_SAIxRST (x = 0,1,2): reset SAI
      \arg        RCU_EDOUTRST: reset EDOUT
      \arg        RCU_TRIGSELRST: reset TRIGSEL
      \arg        RCU_TLIRST: reset TLI
      \arg        RCU_WWDGTRST: reset WWDGT
      \arg        RCU_SYSCFGRST: reset SYSCFG
      \arg        RCU_CMPRST: reset CMP
      \arg        RCU_VREFRST: reset VREF
      \arg        RCU_LPDTSRST: reset LPDTS
      \arg        RCU_PMURST: reset PMU
      \arg        RCU_CANxRST (x = 0,1,2): reset CAN
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
      \arg        RCU_ENETxRST (x = 0,1): reset ENET
      \arg        RCU_USBHSxRST (x = 0,1): reset USBHS
      \arg        RCU_DMAxRST (x = 0,1): reset DMA
      \arg        RCU_DMAMUXRST: reset DMAMUX
      \arg        RCU_DCIRST: reset DCI
      \arg        RCU_FACRST: reset FAC
      \arg        RCU_SDIOxRST (x = 0,1): reset SDIO
      \arg        RCU_CAURST: reset CAU
      \arg        RCU_HAURST: reset HAU
      \arg        RCU_TRNGRST: reset TRNG
      \arg        RCU_TMURST: reset TMU
      \arg        RCU_EXMCRST: reset EXMC
      \arg        RCU_IPARST: reset IPA
      \arg        RCU_MDMARST : reset MDMA
      \arg        RCU_OSPIMRST (x = 0,1): reset OSPIM
      \arg        RCU_OSPIxRST (x = 0,1): reset OSPI
      \arg        RCU_RTDECxRST (x = 0,1): reset RTDEC
      \arg        RCU_GPIOxRST (x = A,B,C,D,E,F,G,H,J,K): reset GPIO ports
      \arg        RCU_CRCRST: reset CRC
      \arg        RCU_HWSEMRST: reset HWSEM
      \arg        RCU_TIMERxRST (x = 0,1,2,3,4,5,6,7,14,15,16,22,23,30,31,40,41,42,43,44,50,51): reset TIMER
      \arg        RCU_RSPDIFRST: reset RSPDIF
      \arg        RCU_SPIxRST (x = 0,1,2,3,4,5): reset SPI
      \arg        RCU_MDIORST: reset MDIO
      \arg        RCU_USARTxRST (x = 0,1,2,5): reset USART
      \arg        RCU_UARTxRST (x = 3,4,6,7): reset UART
      \arg        RCU_I2CxRST (x = 0,1,2,3): reset I2C
      \arg        RCU_CTCRST: reset CTC
      \arg        RCU_DACHOLDRST: reset DACHOLD
      \arg        RCU_DACRST: reset DAC
      \arg        RCU_ADCxRST (x = 0,1,2): reset ADC
      \arg        RCU_HPDFRST: reset HPDF
      \arg        RCU_SAIxRST (x = 0,1,2): reset SAI
      \arg        RCU_EDOUTRST: reset EDOUT
      \arg        RCU_TRIGSELRST: reset TRIGSEL
      \arg        RCU_TLIRST: reset TLI
      \arg        RCU_WWDGTRST: reset WWDGT
      \arg        RCU_SYSCFGRST: reset SYSCFG
      \arg        RCU_CMPRST: reset CMP
      \arg        RCU_VREFRST: reset VREF
      \arg        RCU_LPDTSRST: reset LPDTS
      \arg        RCU_PMURST: reset PMU
      \arg        RCU_CANxRST (x = 0,1,2): reset CAN
    \param[out] none
    \retval     none
*/
void rcu_periph_reset_disable(rcu_periph_reset_enum periph_reset)
{
    RCU_REG_VAL(periph_reset) &= ~BIT(RCU_BIT_POS(periph_reset));
}

/*!
    \brief      reset the BKP
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_bkp_reset_enable(void)
{
    RCU_BDCTL |= RCU_BDCTL_BKPRST;
}

/*!
    \brief      disable the BKP reset
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
      \arg        RCU_CKSYSSRC_IRC64MDIV: select CK_IRC64MDIV as the CK_SYS source
      \arg        RCU_CKSYSSRC_HXTAL: select CK_HXTAL as the CK_SYS source
      \arg        RCU_CKSYSSRC_LPIRC4M: select CK_LPIRC4M as the CK_SYS source
      \arg        RCU_CKSYSSRC_PLL0P: select CK_PLL0P as the CK_SYS source
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
      \arg        RCU_SCSS_IRC64MDIV: CK_IRC64MDIV is selected as the CK_SYS source
      \arg        RCU_SCSS_HXTAL: CK_HXTAL is selected as the CK_SYS source
      \arg        RCU_SCSS_LPIRC4M: CK_LPIRC4M is selected as the CK_SYS source
      \arg        RCU_SCSS_PLL0P: CK_PLL0P is selected as the CK_SYS source
*/
uint32_t rcu_system_clock_source_get(void)
{
    return (RCU_CFG0 & RCU_CFG0_SCSS);
}

/*!
    \brief      configure the AHB clock prescaler selection
    \param[in]  ck_ahb: AHB clock prescaler selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_AHB_CKSYS_DIVx: (x = 1, 2, 4, 8, 16, 64, 128, 256, 512): CK_AHB is CK_SYS/x
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
      \arg        RCU_APB2_CKAHB_DIV2: select CK_AHB / 2 as CK_APB2
      \arg        RCU_APB2_CKAHB_DIV4: select CK_AHB / 4 as CK_APB2
      \arg        RCU_APB2_CKAHB_DIV8: select CK_AHB / 8 as CK_APB2
      \arg        RCU_APB2_CKAHB_DIV16: select CK_AHB / 16 as CK_APB2
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
    \brief      configure the APB3 clock prescaler selection
    \param[in]  ck_apb3: APB3 clock prescaler selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_APB3_CKAHB_DIV1: select CK_AHB as CK_APB3
      \arg        RCU_APB3_CKAHB_DIV2: select CK_AHB / 2 as CK_APB3
      \arg        RCU_APB3_CKAHB_DIV4: select CK_AHB / 4 as CK_APB3
      \arg        RCU_APB3_CKAHB_DIV8: select CK_AHB / 8 as CK_APB3
      \arg        RCU_APB3_CKAHB_DIV16: select CK_AHB/ 16 as CK_APB3
    \param[out] none
    \retval     none
*/
void rcu_apb3_clock_config(uint32_t ck_apb3)
{
    uint32_t reg;

    reg = RCU_CFG0;
    /* reset the APB3PSC and set according to ck_apb3 */
    reg &= ~RCU_CFG0_APB3PSC;
    RCU_CFG0 = (reg | ck_apb3);
}

/*!
    \brief      configure the APB4 clock prescaler selection
    \param[in]  ck_apb4: APB4 clock prescaler selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_APB4_CKAHB_DIV1: select CK_AHB as CK_APB4
      \arg        RCU_APB4_CKAHB_DIV2: select CK_AHB / 2 as CK_APB4
      \arg        RCU_APB4_CKAHB_DIV4: select CK_AHB / 4 as CK_APB4
      \arg        RCU_APB4_CKAHB_DIV8: select CK_AHB / 8 as CK_APB4
      \arg        RCU_APB4_CKAHB_DIV16: select CK_AHB / 16 as CK_APB4
    \param[out] none
    \retval     none
*/
void rcu_apb4_clock_config(uint32_t ck_apb4)
{
    uint32_t reg;

    reg = RCU_CFG0;
    /* reset the APB4PSC and set according to ck_apb4 */
    reg &= ~RCU_CFG0_APB4PSC;
    RCU_CFG0 = (reg | ck_apb4);
}

/*!
    \brief      configure the CK_OUT0 clock source and divider
    \param[in]  ckout0_src: CK_OUT0 clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKOUT0SRC_IRC64MDIV: IRC64M selected
      \arg        RCU_CKOUT0SRC_LXTAL: LXTAL selected
      \arg        RCU_CKOUT0SRC_HXTAL: HXTAL selected
      \arg        RCU_CKOUT0SRC_PLL0P: PLL0P selected
      \arg        RCU_CKOUT0SRC_IRC48M: IRC48M selected
      \arg        RCU_CKOUT0SRC_PER: PER selected
      \arg        RCU_CKOUT0SRC_USBHS060M: USBHS0 60M selected
      \arg        RCU_CKOUT0SRC_USBHS160M: USBHS1 60M selected
    \param[in]  ckout0_div: CK_OUT0 divider
      \arg        RCU_CKOUT0_DIVx (x = 1,2,3,...15): CK_OUT0 is divided by x
    \param[out] none
    \retval     none
*/
void rcu_ckout0_config(uint32_t ckout0_src, uint32_t ckout0_div)
{
    uint32_t reg;

    reg = RCU_CFG2;
    /* reset the CKOUT0SRC, CKOUT0DIV and set according to ckout0_src and ckout0_div */
    reg &= ~(RCU_CFG2_CKOUT0SEL | RCU_CFG2_CKOUT0DIV);
    RCU_CFG2 = (reg | ckout0_src | ckout0_div);
}

/*!
    \brief      configure the CK_OUT1 clock source and divider
    \param[in]  ckout1_src: CK_OUT1 clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKOUT1SRC_SYSTEMCLOCK: system clock selected
      \arg        RCU_CKOUT1SRC_PLL1R: PLL1R selected
      \arg        RCU_CKOUT1SRC_HXTAL: HXTAL selected
      \arg        RCU_CKOUT1SRC_PLL0P: PLL0P selected
      \arg        RCU_CKOUT1SRC_LPIRC4M: LPIRC4M selected
      \arg        RCU_CKOUT1SRC_IRC32K: IRC32K selected
      \arg        RCU_CKOUT1SRC_PLL2R: PLL2R selected
    \param[in]  ckout1_div: CK_OUT1 divider
      \arg        RCU_CKOUT1_DIVx (x = 1,2,3,....15): CK_OUT1 is divided by x
    \param[out] none
    \retval     none
*/
void rcu_ckout1_config(uint32_t ckout1_src, uint32_t ckout1_div)
{
    uint32_t reg;

    reg = RCU_CFG2;
    /* reset the CKOUT1SRC, CKOUT1DIV and set according to ckout1_src and ckout1_div */
    reg &= ~(RCU_CFG2_CKOUT1SEL | RCU_CFG2_CKOUT1DIV);
    RCU_CFG2 = (reg | ckout1_src | ckout1_div);
}

/*!
    \brief      configure the pll input and output clock range
    \param[in]  pll_idx: IDX_PLL, IDX_PLLx (x = 0,1,2)
    \param[in]  ck_input: input clock range
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLLxRNG_1M_2M (x = 0,1,2): input clock frequency: 1-2MHz
      \arg        RCU_PLLxRNG_2M_4M (x = 0,1,2): input clock frequency: 2-4MHz
      \arg        RCU_PLLxRNG_4M_8M (x = 0,1,2): input clock frequency: 4-8MHz
      \arg        RCU_PLLxRNG_8M_16M: input clock frequency: 8-16MHz
     \param[in]  ck_output: output clock range
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLLxVCO_192M_836M (x = 0,1,2): select wide VCO, range: 192-836MHz
      \arg        RCU_PLLxVCO_150M_420M (x = 0,1,2): select narrow VCO, range: 150-420MHz
    \param[out] none
    \retval     none
*/
void rcu_pll_input_output_clock_range_config(pll_idx_enum pll_idx, uint32_t ck_input, uint32_t ck_output)
{
    switch(pll_idx)
    {
    case IDX_PLL0:
        /* reset the PLLRNG/PLLVCOSEL bits and set according to ck_input/ck_output */
        RCU_PLLALL &= ~(RCU_PLLALL_PLL0RNG | RCU_PLLALL_PLL0VCOSEL);
        RCU_PLLALL |= (ck_input | ck_output);
        break;
    case IDX_PLL1:
        /* reset the PLLRNG/PLLVCOSEL bits and set according to ck_input/ck_output */
        RCU_PLLALL &= ~(RCU_PLLALL_PLL1RNG | RCU_PLLALL_PLL1VCOSEL);
        RCU_PLLALL |= (ck_input | ck_output);
        break;
    case IDX_PLL2:
        /* reset the PLLRNG/PLLVCOSEL bits and set according to ck_input/ck_output */
        RCU_PLLALL &= ~(RCU_PLLALL_PLL2RNG | RCU_PLLALL_PLL2VCOSEL);
        RCU_PLLALL |= (ck_input | ck_output);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure fractional part of the multiplication factor for PLL VCO
    \param[in]  pll_idx: IDX_PLL, IDX_PLLx (x = 0,1,2)
    \param[in]  pll_fracn: fractional part of the multiplication factor
      \arg        this parameter should be selected between 0 and 8191
    \param[out] none
    \retval     none
*/
void rcu_pll_fractional_config(pll_idx_enum pll_idx, uint32_t pll_fracn)
{
    switch(pll_idx)
    {
    case IDX_PLL0:
        /* reset the PLLFRAN and set according to pll_fracn */
        RCU_PLL0FRA &= ~(RCU_PLL0FRA_PLL0FRAN);
        RCU_PLL0FRA |= pll_fracn;
        break;
    case IDX_PLL1:
        /* reset the PLLFRAN and set according to pll_fracn */
        RCU_PLL1FRA &= ~(RCU_PLL1FRA_PLL1FRAN);
        RCU_PLL1FRA |= pll_fracn;
        break;
    case IDX_PLL2:
        /* reset the PLLFRAN and set according to pll_fracn */
        RCU_PLL2FRA &= ~(RCU_PLL2FRA_PLL2FRAN);
        RCU_PLL2FRA |= pll_fracn;
        break;
    default:
        break;
    }
}

/*!
    \brief      PLL fractional latch enable
    \param[in]  pll_idx: IDX_PLL,IDX_PLLx (x = 0,1,2)
    \param[out] none
    \retval     none
*/
void rcu_pll_fractional_latch_enable(pll_idx_enum pll_idx)
{
    switch(pll_idx)
    {
    case IDX_PLL0:
        /* set the PLL0FRAEN */
        RCU_PLL0FRA |= RCU_PLL0FRA_PLL0FRAEN ;
        break;
    case IDX_PLL1:
        /* set the PLL1FRAEN */
        RCU_PLL1FRA |= RCU_PLL1FRA_PLL1FRAEN ;
        break;
    case IDX_PLL2:
        /* set the PLL2FRAEN */
        RCU_PLL2FRA |= RCU_PLL2FRA_PLL2FRAEN ;
        break;
    default:
        break;
    }
}

/*!
    \brief      PLL fractional latch disable
    \param[in]  pll_idx: IDX_PLL, IDX_PLLx (x = 1,2)
    \param[out] none
    \retval     none
*/
void rcu_pll_fractional_latch_disable(pll_idx_enum pll_idx)
{
    switch(pll_idx)
    {
    case IDX_PLL0:
        /* reset the PLL0FRAEN */
        RCU_PLL0FRA &= ~RCU_PLL0FRA_PLL0FRAEN ;
        break;
    case IDX_PLL1:
        /* reset the PLL1FRAEN */
        RCU_PLL1FRA &= ~RCU_PLL1FRA_PLL1FRAEN ;
        break;
    case IDX_PLL2:
        /* reset the PLL2FRAEN */
        RCU_PLL2FRA &= ~RCU_PLL2FRA_PLL2FRAEN ;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure PLL clock source
    \param[in]  pll_src: PLL clock source selection
      \arg        RCU_PLLSRC_IRC64MDIV: select IRC64MDIV as PLL source clock
      \arg        RCU_PLLSRC_LPIRC4M: select LPIRC4M as PLL source clock
      \arg        RCU_PLLSRC_HXTAL: select HXTAL as PLL source clock
    \param[out] none
    \retval     none
*/
void rcu_pll_source_config(uint32_t pll_src)
{
    /* PLL clock source selection */
    RCU_PLLALL &= ~(RCU_PLLALL_PLLSEL);
    RCU_PLLALL |= pll_src;
}

/*!
    \brief      configure the main PLL0 clock
    \param[in]  pll0_psc: the PLL0 VCO source clock prescaler
      \arg         this parameter should be selected between 1 and 63. When pll0_psc=0, the PLL0 VCO source clock prescaler close.
    \param[in]  pll0_n: the PLL0 VCO clock multi factor
      \arg        this parameter should be selected between 9 and 512
    \param[in]  pll0_p: the PLL0P output frequency division factor from PLL0 VCO clock
      \arg        this parameter should be selected between 1 and 128
    \param[in]  pll0_q: the PLL0 Q output frequency division factor from PLL0 VCO clock
      \arg        this parameter should be selected between 1 and 128
    \param[in]  pll0_r: the PLL0 R output frequency division factor from PLL0 VCO clock
      \arg        this parameter should be selected between 1 and 128
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus rcu_pll0_config(uint32_t pll0_psc, uint32_t pll0_n, uint32_t pll0_p, uint32_t pll0_q, uint32_t pll0_r)
{
    /* check the function parameter */
    if(CHECK_PLL0_PSC_VALID(pll0_psc) && CHECK_PLL0_N_VALID(pll0_n) &&
            CHECK_PLL0_P_VALID(pll0_p) && CHECK_PLL0_Q_VALID(pll0_q) &&
            CHECK_PLL0_R_VALID(pll0_r))
            {
        RCU_PLL0 &= ~(RCU_PLL0_PLL0PSC | RCU_PLL0_PLL0N | RCU_PLL0_PLL0P | RCU_PLL0_PLL0R);
        RCU_PLL0 |= pll0_psc | ((pll0_n - 1U) << RCU_PLLNOFFSET) | ((pll0_p - 1U) << RCU_PLLPOFFSET) |
                    ((pll0_r - 1U) << RCU_PLLROFFSET);
        RCU_PLLADDCTL &= ~RCU_PLLADDCTL_PLL0Q;
        RCU_PLLADDCTL |= (pll0_q - 1U);
    } else {
        /* return status */
        return ERROR;
    }

    /* return status */
    return SUCCESS;
}

/*!
    \brief      configure the PLL1 clock
    \param[in]  pll1_psc: the PLL1 VCO source clock prescaler
      \arg         this parameter should be selected between 1 and 63. When pll1_psc = 0,the PLL1 VCO source clock prescaler close.
    \param[in]  pll1_n: the PLL1 VCO clock multi factor
      \arg        this parameter should be selected between 9 and 512
    \param[in]  pll1_p: the PLL1 P output frequency division factor from PLL1 VCO clock
      \arg        this parameter should be selected between 1 and 128
    \param[in]  pll1_q: the PLL1 Q output frequency division factor from PLL1 VCO clock
      \arg        this parameter should be selected between 1 and 128
    \param[in]  pll1_r: the PLL1 R output frequency division factor from PLL1 VCO clock
      \arg        this parameter should be selected between 1 and 128

    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus rcu_pll1_config(uint32_t pll1_psc, uint32_t pll1_n, uint32_t pll1_p, uint32_t pll1_q, uint32_t pll1_r)
{
    /* check the function parameter */
    if(CHECK_PLL1_PSC_VALID(pll1_psc) && CHECK_PLL1_N_VALID(pll1_n) &&
            CHECK_PLL1_P_VALID(pll1_p) && CHECK_PLL1_Q_VALID(pll1_q) &&
            CHECK_PLL1_R_VALID(pll1_r))
            {
        RCU_PLL1 = (pll1_psc | ((pll1_n - 1U) << RCU_PLLNOFFSET) | ((pll1_p - 1U) << RCU_PLLPOFFSET) |
                    ((pll1_r - 1U) << RCU_PLLROFFSET));
        RCU_PLLADDCTL &= ~RCU_PLLADDCTL_PLL1Q;
        RCU_PLLADDCTL |= ((pll1_q - 1U) << RCU_PLL1QOFFSET);
    } else {
        /* return status */
        return ERROR;
    }

    /* return status */
    return SUCCESS;
}

/*!
    \brief      configure the PLL2 clock
    \param[in]  pll2_psc: the PLL2 VCO source clock prescaler
      \arg         this parameter should be selected between 0 and 63. When pll2_psc = 0,the PLL2 VCO source clock prescaler close
    \param[in]  pll2_n: the PLL2 VCO clock multi factor
      \arg        this parameter should be selected between 9 and 512
    \param[in]  pll2_p: the PLL2 P output frequency division factor from PLL2 VCO clock
      \arg        this parameter should be selected between 1 and 128
    \param[in]  pll2_q: the PLL2 Q output frequency division factor from PLL2 VCO clock
      \arg        this parameter should be selected between 1 and 128
    \param[in]  pll2_r: the PLL2 R output frequency division factor from PLL2 VCO clock
      \arg        this parameter should be selected between 1 and 128

    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus rcu_pll2_config(uint32_t pll2_psc, uint32_t pll2_n, uint32_t pll2_p, uint32_t pll2_q, uint32_t pll2_r)
{
    /* check the function parameter */
    if(CHECK_PLL2_PSC_VALID(pll2_psc) && CHECK_PLL2_N_VALID(pll2_n) &&
            CHECK_PLL2_P_VALID(pll2_p) && CHECK_PLL2_R_VALID(pll2_q) &&
            CHECK_PLL2_R_VALID(pll2_r))
            {
        RCU_PLL2 = (pll2_psc | ((pll2_n - 1U) << RCU_PLLNOFFSET) | ((pll2_p - 1U) << RCU_PLLPOFFSET) |
                    ((pll2_r - 1U) << RCU_PLLROFFSET));
        RCU_PLLADDCTL &= ~RCU_PLLADDCTL_PLL2Q;
        RCU_PLLADDCTL |= ((pll2_q - 1U) << RCU_PLL2QOFFSET);
    } else {
        /* return status */
        return ERROR;
    }

    /* return status */
    return SUCCESS;
}

/*!
    \brief      enable the pllp pllq pllr divider output
    \param[in]  pllxy: the output pll enable
      \arg        RCU_PLL0P: PLL0P divider output enable
      \arg        RCU_PLL0Q: PLL0Q divider output enable
      \arg        RCU_PLL0R: PLL0R divider output enable
      \arg        RCU_PLL1P: PLL1P divider output enable
      \arg        RCU_PLL1Q: PLL1Q divider output enable
      \arg        RCU_PLL1R: PLL1R divider output enable
      \arg        RCU_PLL2P: PLL2P divider output enable
      \arg        RCU_PLL2Q: PLL2Q divider output enable
      \arg        RCU_PLL2R: PLL2R divider output enable
    \param[out] none
    \retval     none
*/
void rcu_pll_clock_output_enable(uint32_t pllxy)
{
    /* PLL divider output enable */
    RCU_PLLADDCTL |= pllxy;
}

/*!
    \brief      disable the pllp pllq pllr divider output
    \param[in]  pllxy: the output pll disable
      \arg        RCU_PLL0P: PLL0P divider output disable
      \arg        RCU_PLL0Q: PLL0Q divider output disable
      \arg        RCU_PLL0R: PLL0R divider output disable
      \arg        RCU_PLL1P: PLL1P divider output disable
      \arg        RCU_PLL1Q: PLL1Q divider output disable
      \arg        RCU_PLL1R: PLL1R divider output disable
      \arg        RCU_PLL2P: PLL2P divider output disable
      \arg        RCU_PLL2Q: PLL2Q divider output disable
      \arg        RCU_PLL2R: PLL2R divider output disable
    \param[out] none
    \retval     none
*/
void rcu_pll_clock_output_disable(uint32_t pllxy)
{
    /* PLL divider output disable */
    RCU_PLLADDCTL &= ~(pllxy);
}

/*!
    \brief      configure the PLLUSBHS0 clock
    \param[in]  pllusb_presel: PLLUSBHSPRE clock selection
      \arg        this parameter should be selected RCU_PLLUSBHSPRE_HXTAL or RCU_PLLUSBHSPRE_IRC48M
    \param[in]  pllusb_predv: the divider factor from PLLUSBHS clock
      \arg        this parameter should be selected between RCU_PLLUSBHSPRE_DIVx (x = 1...15)
    \param[in]  pllusb_mf: PLLUSBHS0 clock multiplication factor
      \arg        this parameter should be selected RCU_PLLUSBHS_MULx (x = 16,17...127)
    \param[in]  usbhsdv: the divider factor from USBHSDV clock
      \arg        this parameter should be selected RCU_USBHS_DIVx (x = 2,4...16)

    \param[out] none
    \retval     none
*/
void rcu_pllusb0_config(uint32_t pllusb_presel, uint32_t pllusb_predv, uint32_t pllusb_mf, uint32_t usbhsdv)
{
    /* configure PLLUSBHS source selection */
    RCU_USBCLKCTL &= ~(RCU_USBCLKCTL_PLLUSBHS0PRESEL);
    RCU_USBCLKCTL |= (pllusb_presel);

    RCU_PLLUSBCFG &= ~(RCU_PLLUSBCFG_PLLUSBHS0PREDV | RCU_PLLUSBCFG_USBHS0DV | RCU_PLLUSBCFG_PLLUSBHS0MF);
    RCU_PLLUSBCFG |= (pllusb_predv | usbhsdv | pllusb_mf);
}

/*!
    \brief      configure the PLLUSBHS1 clock
    \param[in]  pllusb_presel: PLLUSBHSPRE clock selection
      \arg        this parameter should be selected RCU_PLLUSBHSPRE_HXTAL or RCU_PLLUSBHSPRE_IRC48M
    \param[in]  pllusb_predv: the divider factor from PLLUSBHS clock
      \arg        this parameter should be selected between RCU_PLLUSBHSPRE_DIVx (x = 1...15)
    \param[in]  pllusb_mf: PLLUSBHS1 clock multiplication factor
      \arg        this parameter should be selected RCU_PLLUSBHS_MULx (x = 16,17..127)
    \param[in]  usbhsdv: the divider factor from USBHSDV clock
      \arg        this parameter should be selected RCU_USBHS_DIVx (x = 2,4...16)

    \param[out] none
    \retval     none
*/
void rcu_pllusb1_config(uint32_t pllusb_presel, uint32_t pllusb_predv, uint32_t pllusb_mf, uint32_t usbhsdv)
{
    /* configure pllusb source selection */
    RCU_USBCLKCTL &= ~(RCU_USBCLKCTL_PLLUSBHS1PRESEL);
    RCU_USBCLKCTL |= ((pllusb_presel << 8U));

    RCU_PLLUSBCFG &= ~(RCU_PLLUSBCFG_PLLUSBHS1PREDV | RCU_PLLUSBCFG_USBHS1DV | RCU_PLLUSBCFG_PLLUSBHS1MF);
    RCU_PLLUSBCFG |= ((pllusb_predv << 16U) | (usbhsdv << 16U) | (pllusb_mf << 16U));
}

/*!
    \brief      configure the RTC clock source selection
    \param[in]  rtc_clock_source: RTC clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_RTCSRC_NONE: no clock selected
      \arg        RCU_RTCSRC_LXTAL: CK_LXTAL selected as RTC source clock
      \arg        RCU_RTCSRC_IRC32K: CK_IRC32K selected as RTC source clock
      \arg        RCU_RTCSRC_HXTAL_DIV_RTCDIV: CK_HXTAL / RTCDIV selected as RTC source clock
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

/*!
    \brief      configure the frequency division of RTC clock when HXTAL was selected as its clock source
    \param[in]  rtc_div: RTC clock frequency division
                only one parameter can be selected which is shown as below:
      \arg        RCU_RTC_HXTAL_NONE: no clock for RTC
      \arg        RCU_RTC_HXTAL_DIVx: RTCDIV clock select CK_HXTAL / x (x = 2,3...63)
    \param[out] none
    \retval     none
*/
void rcu_rtc_div_config(uint32_t rtc_div)
{
    uint32_t reg;

    reg = RCU_CFG0;
    /* reset the RTCDIV bits and set according to rtc_div value */
    reg &= ~RCU_CFG0_RTCDIV;
    RCU_CFG0 = (reg | rtc_div);
}

/*!
    \brief      configure the CK48M clock source selection (need to check the target clock whether to ready before enabling or switching dynamically)
    \param[in]  ck48m_clock_source: CK48M clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_CK48MSRC_PLL48M: CK_PLL48M selected as CK48M source clock
      \arg        RCU_CK48MSRC_IRC48M: CK_IRC48M selected as CK48M source clock
    \param[out] none
    \retval     none
*/
void rcu_ck48m_clock_config(uint32_t ck48m_clock_source)
{
    uint32_t reg;

    reg = RCU_ADDCTL0;
    /* reset the CK48MSEL bit and set according to ck48m_clock_source */
    reg &= ~RCU_ADDCTL0_CK48MSEL;
    RCU_ADDCTL0 = (reg | ck48m_clock_source);
}

/*!
    \brief      configure the PLL48M clock source selection (need to check the target clock whether to ready before enabling or switching dynamically)
    \param[in]  pll48m_clock_source: PLL48M clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLL48MSRC_PLL0Q: CK_PLL0Q selected as PLL48M source clock
      \arg        RCU_PLL48MSRC_PLL2P: CK_PLL2P selected as PLL48M source clock
    \param[out] none
    \retval     none
*/
void rcu_pll48m_clock_config(uint32_t pll48m_clock_source)
{
    uint32_t reg;

    reg = RCU_ADDCTL0;
    /* reset the PLL48MSEL bit and set according to pll48m_clock_source */
    reg &= ~RCU_ADDCTL0_PLL48MSEL;
    RCU_ADDCTL0 = (reg | pll48m_clock_source);
}

/*!
    \brief      configure the IRC64M clock divider selection
    \param[in]  ck_irc64mdiv: IRC64M clock divider selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_IRC64M_DIV1: CK_IRC64M / 1
      \arg        RCU_IRC64M_DIV2: CK_IRC64M / 2
      \arg        RCU_IRC64M_DIV4: CK_IRC64M / 4
      \arg        RCU_IRC64M_DIV8: CK_IRC64M / 8
    \param[out] none
    \retval     none
*/
void rcu_irc64mdiv_clock_config(uint32_t ck_irc64mdiv)
{
    uint32_t reg;

    reg = RCU_ADDCTL1;
    /* reset the IRC64MDIV and set according to ck_irc64mdiv */
    reg &= ~RCU_ADDCTL1_IRC64MDIV;
    RCU_ADDCTL1 = (reg | ck_irc64mdiv);
}
/*!
    \brief    get the irc64mdiv clock
    \param[in]  none
    \param[out] none
    \retval     clock frequency of irc64mdiv: 64000000, 32000000, 16000000, 8000000
*/
uint32_t rcu_irc64mdiv_freq_get(void)
{
    uint32_t irc64m_freq = 0U;

    /* CK_IRC64MDIV = CK_IRC64M/1/2/4/8 */
    if(RCU_IRC64M_DIV1 == (RCU_ADDCTL1 & RCU_ADDCTL1_IRC64MDIV))
    {
        irc64m_freq = IRC64M_VALUE;
    } else if(RCU_IRC64M_DIV2 == (RCU_ADDCTL1 & RCU_ADDCTL1_IRC64MDIV))
    {
        irc64m_freq = IRC64M_VALUE / 2U;
    } else if(RCU_IRC64M_DIV4 == (RCU_ADDCTL1 & RCU_ADDCTL1_IRC64MDIV))
    {
        irc64m_freq = IRC64M_VALUE / 4U;
    } else if(RCU_IRC64M_DIV8 == (RCU_ADDCTL1 & RCU_ADDCTL1_IRC64MDIV))
    {
        irc64m_freq = IRC64M_VALUE / 8U;
    } else {
    }

    return irc64m_freq;
}

/*!
    \brief      configure the TIMER clock prescaler selection
    \param[in]  timer_clock_prescaler: TIMER clock selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_TIMER_PSC_MUL2: if APB1PSC / APB2PSC in RCU_CFG0 register is 0b0xx (CK_APBx = CK_AHB)
                                      or 0b100 (CK_APBx = CK_AHB / 2), the TIMER clock is equal to CK_AHB (CK_TIMERx = CK_AHB).
                                      or else, the TIMER clock is twice the corresponding APB clock (TIMER in APB1 domain: CK_TIMERx = 2 x CK_APB1;
                                      TIMER in APB2 domain: CK_TIMERx = 2 x CK_APB2)
      \arg        RCU_TIMER_PSC_MUL4: if APB1PSC / APB2PSC in RCU_CFG0 register is 0b0xx(CK_APBx = CK_AHB),
                                      0b100 (CK_APBx = CK_AHB / 2), or 0b101 (CK_APBx = CK_AHB / 4), the TIMER clock is equal to CK_AHB (CK_TIMERx = CK_AHB).
                                      or else, the TIMER clock is four timers the corresponding APB clock (TIMER in APB1 domain: CK_TIMERx = 4 x CK_APB1;
                                      TIMER in APB2 domain: CK_TIMERx = 4 x CK_APB2)
    \param[out] none
    \retval     none
*/
void rcu_timer_clock_prescaler_config(uint32_t timer_clock_prescaler)
{
    /* configure the TIMERSEL bit and select the TIMER clock prescaler */
    if(timer_clock_prescaler == RCU_TIMER_PSC_MUL2)
    {
        RCU_CFG1 &= timer_clock_prescaler;
    } else {
        RCU_CFG1 |= timer_clock_prescaler;
    }
}

/*!
    \brief      configure the SPI / I2S clock source selection (need to check the target clock whether to ready before enabling or switching dynamically)
    \param[in]  spi_idx: IDX_SPIx (x = 0,1,2,3,4,5)
    \param[in]  ck_spi: SPI0 / SPI1 / SPI2 clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_SPISRC_PLL0Q: CK_SPI select PLL0Q
      \arg        RCU_SPISRC_PLL1P: CK_SPI select PLL1P
      \arg        RCU_SPISRC_PLL2P: CK_SPI select PLL2P
      \arg        RCU_SPISRC_I2S_CKIN: CK_SPI select I2SCKIN
      \arg        RCU_SPISRC_PER: CK_SPI select PER
    \param[in]  ck_spi: SPI3 / SPI4 / SPI5 clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_SPISRC_APB2: CK_SPI select CKAPB2
      \arg        RCU_SPISRC_PLL1Q: CK_SPI select PLL1Q
      \arg        RCU_SPISRC_PLL2Q: CK_SPI select PLL2Q
      \arg        RCU_SPISRC_IRC64MDIV: CK_SPI select IRC64MDIV
      \arg        RCU_SPISRC_LPIRC4M: CK_SPI select LPIRC4M
      \arg        RCU_SPISRC_HXTAL: CK_SPI select HXTAL
      \arg        RCU_SPI5SRC_I2S_CKIN: CK_SPI select I2SCKIN (only for SPI5)
    \param[out] none
    \retval     none
*/
void rcu_spi_clock_config(spi_idx_enum spi_idx, uint32_t ck_spi)
{
    switch(spi_idx)
    {
    case IDX_SPI0:
        /* reset the SPI0SEL bits and set according to ck_spi */
        RCU_CFG5 &= ~RCU_CFG5_SPI0SEL;
        RCU_CFG5 |= (uint32_t)ck_spi ;
        break;
    case IDX_SPI1:
        /* reset the SPI1SEL bits and set according to ck_spi */
        RCU_CFG5 &= ~RCU_CFG5_SPI1SEL;
        RCU_CFG5 |= (uint32_t)ck_spi << 4U ;
        break;
    case IDX_SPI2:
        /* reset the SPI2SEL bits and set according to ck_spi */
        RCU_CFG5 &= ~RCU_CFG5_SPI2SEL;
        RCU_CFG5 |= (uint32_t)ck_spi << 8U;
        break;
    case IDX_SPI3:
        /* reset the SPI3SEL bits and set according to ck_spi */
        RCU_CFG5 &= ~RCU_CFG5_SPI3SEL;
        RCU_CFG5 |= (uint32_t)ck_spi ;
        break;
    case IDX_SPI4:
        /* reset the SPI4SEL bits and set according to ck_spi */
        RCU_CFG5 &= ~RCU_CFG5_SPI4SEL;
        RCU_CFG5 |= (uint32_t)ck_spi << 4U;
        break;
    case IDX_SPI5:
        /* reset the SPI5SEL bits and set according to ck_spi */
        RCU_CFG5 &= ~RCU_CFG5_SPI5SEL;
        RCU_CFG5 |= (uint32_t)ck_spi << 8U;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure the SDIO clock source selection (need to check the target clock whether to ready before enabling or switching dynamically)
    \param[in]  sdio_idx: IDX_SDIOx (x = 0,1)
    \param[in]  ck_sdio: SDIO clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_SDIO0SRC_PLL0Q: CK_SDIO0 select PLL0Q (only for SDIO0)
      \arg        RCU_SDIO0SRC_PLL1R: CK_SDIO0 select PLL1R (only for SDIO0)
      \arg        RCU_SDIO1SRC_PLL0Q: CK_SDIO1 select PLL0Q (only for SDIO1)
      \arg        RCU_SDIO1SRC_PLL1R: CK_SDIO1 select PLL1R (only for SDIO1)
    \param[out] none
    \retval     none
*/
void rcu_sdio_clock_config(sdio_idx_enum sdio_idx, uint32_t ck_sdio)
{
    switch(sdio_idx)
    {
    case IDX_SDIO0:
        /* reset the SDIO0SEL bits and set according to ck_sdio */
        RCU_CFG4 &= ~RCU_CFG4_SDIO0SEL;
        RCU_CFG4 |= (uint32_t)ck_sdio;
        break;
    case IDX_SDIO1:
        /* reset the SDIO1SEL bits and set according to ck_sdio */
        RCU_CFG3 &= ~RCU_CFG3_SDIO1SEL;
        RCU_CFG3 |= (uint32_t)ck_sdio;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure the Deep-sleep wakeup system clock source selection
    \param[in]  ck_dspwussel: Deep-sleep wakeup system clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_DSPWUSSEL_IRC64MDIV: ck_dspwussel select IRC64MDIV
      \arg        RCU_DSPWUSSEL_LPIRC4M: ck_dspwussel select LPIRC4M
    \param[out] none
    \retval     none
*/
void rcu_deepsleep_wakeup_sys_clock_config(uint32_t ck_dspwussel)
{
    /* reset the DSPWUSSEL bits and set according to ck_dspwussel */
    RCU_CFG3 &= ~RCU_CFG3_DSPWUSSEL;
    RCU_CFG3 |= ck_dspwussel;
}

/*!
    \brief      configure the PLL2R divider used as input of TLI
    \param[in]  pll2_r_div: PLL2R divider used as input of TLI
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLL2R_DIVx (x = 2,4,8,16): PLL2R divided x used as input of TLI
    \param[out] none
    \retval     none
*/
void rcu_tli_clock_div_config(uint32_t pll2_r_div)
{
    uint32_t reg;

    reg = RCU_CFG1;
    /* reset the PLL2RDIV bit and set according to pll2_r_div */
    reg &= ~RCU_CFG1_PLL2RDIV;
    RCU_CFG1 = (reg | pll2_r_div);
}

/*!
    \brief      configure the USARTx (x = 0,1,2,5) clock source selection (need to check the target clock whether to ready before enabling or switching dynamically)
    \param[in]  usart_idx: IDX_USARTx (x = 0,1,2,5)
    \param[in]  ck_usart: USART clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_USARTSRC_APB: CK_USART select CK_APB1(USART1 / USART2) or CK_APB2(USART0 / USART5)
      \arg        RCU_USARTSRC_AHB: CK_USART select CK_AHB
      \arg        RCU_USARTSRC_LXTAL: CK_USART select CK_LXTAL
      \arg        RCU_USARTSRC_IRC64MDIV: CK_USART select CK_IRC64MDIV
    \param[out] none
    \retval     none
*/
void rcu_usart_clock_config(usart_idx_enum usart_idx, uint32_t ck_usart)
{
    switch(usart_idx)
    {
    case IDX_USART0:
        /* reset the USART0SEL bits and set according to ck_usart */
        RCU_CFG1 &= ~RCU_CFG1_USART0SEL;
        RCU_CFG1 |= ck_usart;
        break;
    case IDX_USART1:
        /* reset the USART1SEL bits and set according to ck_usart */
        RCU_CFG1 &= ~RCU_CFG1_USART1SEL;
        RCU_CFG1 |= (uint32_t)ck_usart << 18U;
        break;
    case IDX_USART2:
        /* reset the USART2SEL bits and set according to ck_usart */
        RCU_CFG1 &= ~RCU_CFG1_USART2SEL;
        RCU_CFG1 |= (uint32_t)ck_usart << 20U;
        break;
    case IDX_USART5:
        /* reset the USART5SEL bits and set according to ck_usart */
        RCU_CFG1 &= ~RCU_CFG1_USART5SEL;
        RCU_CFG1 |= (uint32_t)ck_usart << 22U;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure the I2Cx (x = 0,1,2,3) clock source selection (need to check the target clock whether to ready before enabling or switching dynamically)
    \param[in]  i2c_idx: IDX_I2Cx (x = 0,1,2,3)
    \param[in]  ck_i2c: I2C clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_I2CSRC_APB1: CK_I2C select CK_APB1
      \arg        RCU_I2CSRC_PLL2R: CK_I2C select CK_PLL2R
      \arg        RCU_I2CSRC_IRC64MDIV: CK_I2C select CK_IRC64MDIV
      \arg        RCU_I2CSRC_LPIRC4M: CK_I2C select CK_LPIRC4M
    \param[out] none
    \retval     none
*/
void rcu_i2c_clock_config(i2c_idx_enum i2c_idx, uint32_t ck_i2c)
{
    switch(i2c_idx)
    {
    case IDX_I2C0:
        /* reset the I2C0SEL bits and set according to ck_i2c */
        RCU_CFG0 &= ~RCU_CFG0_I2C0SEL;
        RCU_CFG0 |= ck_i2c << 30U;
        break;
    case IDX_I2C1:
        /* reset the I2C1SEL bits and set according to ck_i2c */
        RCU_CFG3 &= ~RCU_CFG3_I2C1SEL;
        RCU_CFG3 |= (uint32_t)ck_i2c;
        break;
    case IDX_I2C2:
        /* reset the I2C2SEL bits and set according to ck_i2c */
        RCU_CFG3 &= ~RCU_CFG3_I2C2SEL;
        RCU_CFG3 |= (uint32_t)ck_i2c << 2U;
        break;
    case IDX_I2C3:
        /* reset the I2C4SEL bits and set according to ck_i2c */
        RCU_CFG3 &= ~RCU_CFG3_I2C3SEL;
        RCU_CFG3 |= (uint32_t)ck_i2c << 4U;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure the CANx (x = 0,1,2) clock source selection (need to check the target clock whether to ready before enabling or switching dynamically)
    \param[in]  can_idx: IDX_CANx (x = 0,1,2)
    \param[in]  ck_can: CAN clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_CANSRC_HXTAL: CK_CAN select CK_HXTAL
      \arg        RCU_CANSRC_APB2: CK_CAN select CK_APB2
      \arg        RCU_CANSRC_APB2_DIV2: CK_CAN select CK_APB2 / 2
      \arg        RCU_CANSRC_IRC64MDIV: CK_CAN select CK_IRC64MDIV
    \param[out] none
    \retval     none
*/
void rcu_can_clock_config(can_idx_enum can_idx, uint32_t ck_can)
{
    switch(can_idx)
    {
    case IDX_CAN0:
        /* reset the CAN0SEL bits and set according to ck_can */
        RCU_CFG1 &= ~RCU_CFG1_CAN0SEL;
        RCU_CFG1 |= ck_can ;
        break;
    case IDX_CAN1:
        /* reset the CAN1SEL bits and set according to ck_can */
        RCU_CFG1 &= ~RCU_CFG1_CAN1SEL;
        RCU_CFG1 |= (uint32_t)ck_can << 2U;
        break;
    case IDX_CAN2:
        /* reset the CAN2SEL bits and set according to ck_can */
        RCU_CFG1 &= ~RCU_CFG1_CAN2SEL;
        RCU_CFG1 |= (uint32_t)ck_can << 4U;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure the ADCx (x = 0,1,2) clock source selection
    \param[in]  adc_idx: IDX_ADCx (x = 0,1,2)
    \param[in]  ck_adc: ADC clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_ADCSRC_PLL1P: CK_ADC select CK_PLL1P
      \arg        RCU_ADCSRC_PLL2R: CK_ADC select CK_PLL2R
      \arg        RCU_ADCSRC_PER: CK_ADC select CK_PER
    \param[out] none
    \retval     none
*/
void rcu_adc_clock_config(adc_idx_enum adc_idx, uint32_t ck_adc)
{
    switch(adc_idx)
    {
    case IDX_ADC0:
    case IDX_ADC1:
        /* reset the ADC0SEL/ADC1SEL bits and set according to ck_adc */
        RCU_CFG3 &= ~RCU_CFG3_ADC01SEL;
        RCU_CFG3 |= ck_adc ;
        break;
    case IDX_ADC2:
        /* reset the ADC2SEL bits and set according to ck_adc */
        RCU_CFG3 &= ~RCU_CFG3_ADC2SEL;
        RCU_CFG3 |= (uint32_t)ck_adc << 2U;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure the SAIx (x = 0,1) clock source selection (need to check the target clock whether to ready before enabling or switching dynamically)
    \param[in]  can_idx: IDX_SAIx (x = 0,1)
    \param[in]  ck_sai: SAI clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_SAISRC_PLL0Q: CK_SAI select CK_PLL0Q
      \arg        RCU_SAISRC_PLL1P: CK_SAI select CK_PLL2R
      \arg        RCU_SAISRC_PLL2P: CK_SAI select CK_PLL2P
      \arg        RCU_SAISRC_I2S_CKIN: CK_SAI select CK_PLL2R
      \arg        RCU_SAISRC_PER: CK_SAI select CK_PER
    \param[out] none
    \retval     none
*/
void rcu_sai_clock_config(sai_idx_enum sai_idx, uint32_t ck_sai)
{
    switch(sai_idx)
    {
    case IDX_SAI0:
        /* reset the SAI0SEL bits and set according to ck_sai */
        RCU_CFG2 &= ~RCU_CFG2_SAI0SEL;
        RCU_CFG2 |= ck_sai ;
        break;
    case IDX_SAI1:
        /* reset the SAI1SEL bits and set according to ck_sai */
        RCU_CFG2 &= ~RCU_CFG2_SAI1SEL;
        RCU_CFG2 |= ck_sai << 4U;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure the SAI2Bx (x = 0,1) clock source selection (need to check the target clock whether to ready before enabling or switching dynamically)
    \param[in]  sai2b_idx: IDX_SAI2Bx (x = 0,1)
    \param[in]  ck_sai2b: SAI clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_SAI2BSRC_PLL0Q: CK_SAI2B select CK_PLL0Q
      \arg        RCU_SAI2BSRC_PLL1P: CK_SAI2B select CK_PLL2R
      \arg        RCU_SAI2BSRC_PLL2P: CK_SAI2B select CK_PLL2P
      \arg        RCU_SAI2BSRC_I2S_CKIN: CK_SAI2B select I2S_CKIN
      \arg        RCU_SAI2BSRC_PER: CK_SAI2B select CK_PER
      \arg        RCU_SAI2BSRC_RSPDIF_SYMB: CK_SAI2B select CK_RSPDIF_SYMB
    \param[out] none
    \retval     none
*/
void rcu_sai2_block_clock_config(sai2b_idx_enum sai2b_idx, uint32_t ck_sai2b)
{
    switch(sai2b_idx)
    {
    case IDX_SAI2B0:
        /* reset the SAI2B0SEL bits and set according to ck_sai2b */
        RCU_CFG2 &= ~RCU_CFG2_SAI2B0SEL;
        RCU_CFG2 |= ck_sai2b ;
        break;
    case IDX_SAI2B1:
        /* reset the SAI2B1SEL bits and set according to ck_sai2b */
        RCU_CFG2 &= ~RCU_CFG2_SAI2B1SEL;
        RCU_CFG2 |= ck_sai2b << 4U ;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure the RSPDIF clock source selection (need to check the target clock whether to ready before enabling or switching dynamically)
    \param[in]  ck_rspdif: RSPDIF clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_RSPDIFSRC_PLL0Q: CK_RSPDIF select CK_PLL0Q
      \arg        RCU_RSPDIFSRC_PLL1R: CK_RSPDIF select CK_PLL1R
      \arg        RCU_RSPDIFSRC_PLL2R: CK_RSPDIF select CK_PLL2R
      \arg        RCU_RSPDIFSRC_IRC64MDIV: CK_RSPDIF select CK_IRC64MDIV
    \param[out] none
    \retval     none
*/
void rcu_rspdif_clock_config(uint32_t ck_rspdif)
{
    /* reset the RSPDIFSEL bits and set according to ck_rspdif */
    RCU_CFG1 &= ~RCU_CFG1_RSPDIFSEL;
    RCU_CFG1 |= ck_rspdif;
}

/*!
    \brief      configure the EXMC clock source selection (need to check the target clock whether to ready before enabling or switching dynamically)
    \param[in]  ck_exmc: EXMC clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_EXMCSRC_AHB: CK_EXMC select CK_AHB
      \arg        RCU_EXMCSRC_PLL0Q: CK_EXMC select CK_PLL0Q
      \arg        RCU_EXMCSRC_PLL1R: CK_EXMC select CK_PLL1R
      \arg        RCU_EXMCSRC_PER: CK_EXMC select CK_PER
    \param[out] none
    \retval     none
*/
void rcu_exmc_clock_config(uint32_t ck_exmc)
{
    /* reset the EXMCSEL bits and set according to ck_exmc */
    RCU_CFG4 &= ~(RCU_CFG4_EXMCSEL);
    RCU_CFG4 |= ck_exmc ;
}

/*!
    \brief      configure the HPDF clock source selection (need to check the target clock whether to ready before enabling or switching dynamically)
    \param[in]  ck_hpdf: HPDF clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_HPDFSRC_APB2: CK_HPDF select CK_APB2
      \arg        RCU_HPDFSRC_AHB: CK_HPDF select CK_AHB
    \param[out] none
    \retval     none
*/
void rcu_hpdf_clock_config(uint32_t ck_hpdf)
{
    /* reset the HPDFSEL bits and set according to ck_hpdf */
    RCU_CFG1 &= ~RCU_CFG1_HPDFSEL;
    RCU_CFG1 |= ck_hpdf ;
}

/*!
    \brief      configure the PER clock source selection
    \param[in]  ck_per: PER clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_PERSRC_IRC64MDIV: CK_PER select CK_IRC64MDIV
      \arg        RCU_PERSRC_LPIRC4M: CK_PER select CK_LPIRC4M
      \arg        RCU_PERSRC_HXTAL: CK_PER select CK_HXTAL
    \param[out] none
    \retval     none
*/
void rcu_per_clock_config(uint32_t ck_per)
{
    /* reset the PERSEL bits and set according to ck_per */
    RCU_CFG1 &= ~RCU_CFG1_PERSEL;
    RCU_CFG1 |= ck_per ;
}

/*!
    \brief      configure the PLL1Q prescaler
    \param[in]  usbhs_idx: IDX_USBHSx (x = 0,1)
    \param[in]  ck_usbhspsc: USBHS clock prescaler from CK_PLL1Q
                only one parameter can be selected which is shown as below:
      \arg        RCU_USBHSPSC_DIV1: CK_PLL1Q / 1
      \arg        RCU_USBHSPSC_DIV2: CK_PLL1Q / 2
      \arg        RCU_USBHSPSC_DIV3: CK_PLL1Q / 3
      \arg        RCU_USBHSPSC_DIV4: CK_PLL1Q / 4
      \arg        RCU_USBHSPSC_DIV5: CK_PLL1Q / 5
      \arg        RCU_USBHSPSC_DIV6: CK_PLL1Q / 6
      \arg        RCU_USBHSPSC_DIV7: CK_PLL1Q / 7
      \arg        RCU_USBHSPSC_DIV8: CK_PLL1Q / 8
    \param[out] none
    \retval     none
*/
void rcu_usbhs_pll1qpsc_config(usbhs_idx_enum usbhs_idx, uint32_t ck_usbhspsc)
{
    switch(usbhs_idx)
    {
    case IDX_USBHS0:
        /* reset the USBHS0PSC bits and set according to ck_usbhspsc */
        RCU_USBCLKCTL &= ~RCU_USBCLKCTL_USBHS0PSC;
        RCU_USBCLKCTL |= ck_usbhspsc ;
        break;
    case IDX_USBHS1:
        /* reset the USBHS1PSC bits and set according to ck_usbhspsc */
        RCU_USBCLKCTL &= ~RCU_USBCLKCTL_USBHS1PSC;
        RCU_USBCLKCTL |= (ck_usbhspsc << 3U) ;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure the USBHS48MSEL clock source selection
    \param[in]  usbhs_idx: IDX_USBHSx (x = 0,1)
    \param[in]  ck_usb48m: USBHS48MSEL clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_USB48MSRC_PLL0R: CK_USB48M select CK_PLL0R
      \arg        RCU_USB48MSRC_PLLUSBHS: CK_USB48M select CK_PLLUSBHSx / USBHxSDV
      \arg        RCU_USB48MSRC_PLL1Q: CK_USB48M select CK_PLL1Q / USBHSxPSC
      \arg        RCU_USB48MSRC_IRC48M: CK_USB48M select CK_IRC48M
    \param[out] none
    \retval     none
*/
void rcu_usb48m_clock_config(usbhs_idx_enum usbhs_idx, uint32_t ck_usb48m)
{
    switch(usbhs_idx)
    {
    case IDX_USBHS0:
        /* reset the USB048MSEL bits and set according to ck_usb48m */
        RCU_USBCLKCTL &= ~RCU_USBCLKCTL_USBHS048MSEL;
        RCU_USBCLKCTL |= ck_usb48m ;
        break;
    case IDX_USBHS1:
        /* reset the USB148MSEL bits and set according to ck_usb48m */
        RCU_USBCLKCTL &= ~RCU_USBCLKCTL_USBHS148MSEL;
        RCU_USBCLKCTL |= (ck_usb48m << 8U) ;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure the USBHSSEL clock source selection
    \param[in]  usbhs_idx: IDX_USBHSx (x = 0,1)
    \param[in]  ck_usbhs: USBHSSEL clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_USBHSSEL_48M: CK_USBHS select 48M
      \arg        RCU_USBHSSEL_60M: CK_USBHS select 60M
    \param[out] none
    \retval     none
*/
void rcu_usbhs_clock_config(usbhs_idx_enum usbhs_idx, uint32_t ck_usbhs)
{
    switch(usbhs_idx)
    {
    case IDX_USBHS0:
        /* reset the USBHS0SEL bits and set according to ck_usbhs */
        RCU_USBCLKCTL &= ~RCU_USBCLKCTL_USBHS0SEL;
        RCU_USBCLKCTL |= ck_usbhs ;
        break;
    case IDX_USBHS1:
        /* reset the USBHS1SEL bits and set according to ck_usbhs */
        RCU_USBCLKCTL &= ~RCU_USBCLKCTL_USBHS1SEL;
        RCU_USBCLKCTL |= (ck_usbhs << 8U) ;
        break;
    default:
        break;
    }
}

/*!
    \brief      enable the USBHS clock source selection
    \param[in]  usbhs_idx: IDX_USBHSx (x = 0,1)
    \param[out] none
    \retval     none
*/
void rcu_usbhs_clock_selection_enable(usbhs_idx_enum usbhs_idx)
{
    switch(usbhs_idx)
    {
    case IDX_USBHS0:
        /* set the USB0SWEN bit  */
        RCU_USBCLKCTL |= RCU_USBCLKCTL_USBHS0SWEN;
        break;
    case IDX_USBHS1:
        /* set the USB1SWEN bit */
        RCU_USBCLKCTL |= RCU_USBCLKCTL_USBHS1SWEN;
        break;
    default:
        break;
    }
}

/*!
    \brief      disable the USBHS clock source selection
    \param[in]  usbhs_idx: IDX_USBxHS (x = 0,1)
    \param[out] none
    \retval     none
*/
void rcu_usbhs_clock_selection_disable(usbhs_idx_enum usbhs_idx)
{
    switch(usbhs_idx)
    {
    case IDX_USBHS0:
        /* reset the USB0SWEN bit  */
        RCU_USBCLKCTL &= ~RCU_USBCLKCTL_USBHS0SWEN;
        break;
    case IDX_USBHS1:
        /* reset the USB1SWEN bit */
        RCU_USBCLKCTL &= ~RCU_USBCLKCTL_USBHS1SWEN;
        break;
    default:
        break;
    }
}

/*!
    \brief      configure the LXTAL drive capability
    \param[in]  lxtal_dricap: drive capability of LXTAL
                only one parameter can be selected which is shown as below:
      \arg        RCU_LXTAL_LOWDRI: lower driving capability
      \arg        RCU_LXTAL_MED_LOWDRI: middle driving capability
      \arg        RCU_LXTAL_MED_HIGHDRI: higher driving capability
      \arg        RCU_LXTAL_HIGHDRI: stronger driving capability
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
      \arg        RCU_HXTAL: HXTAL
      \arg        RCU_LXTAL: LXTAL
      \arg        RCU_IRC64M: IRC64M
      \arg        RCU_IRC48M: IRC48M
      \arg        RCU_IRC32K: IRC32K
      \arg        RCU_LPIRC4M: LPIRC4M
      \arg        RCU_PLL0_CK: PLL0
      \arg        RCU_PLL1_CK: PLL1
      \arg        RCU_PLL2_CK: PLL2
      \arg        RCU_PLLUSBHS0_CK: PLLUSBHS0
      \arg        RCU_PLLUSBHS1_CK: PLLUSBHS1
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

        /* check whether flag is set */
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

        /* check whether flag is set */
        if(RESET != rcu_flag_get(RCU_FLAG_LXTALSTB))
        {
            reval = SUCCESS;
        }
        break;
    /* wait IRC64M stable */
    case RCU_IRC64M:
        while((RESET == osci_stat) && (IRC64M_STARTUP_TIMEOUT != stb_cnt))
        {
            osci_stat = rcu_flag_get(RCU_FLAG_IRC64MSTB);
            stb_cnt++;
        }

        /* check whether flag is set */
        if(RESET != rcu_flag_get(RCU_FLAG_IRC64MSTB))
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

        /* check whether flag is set */
        if(RESET != rcu_flag_get(RCU_FLAG_IRC48MSTB))
        {
            reval = SUCCESS;
        }
        break;
    /* wait IRC32K stable */
    case RCU_IRC32K:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt))
        {
            osci_stat = rcu_flag_get(RCU_FLAG_IRC32KSTB);
            stb_cnt++;
        }

        /* check whether flag is set */
        if(RESET != rcu_flag_get(RCU_FLAG_IRC32KSTB))
        {
            reval = SUCCESS;
        }
        break;
    /* wait LPIRC4M stable */
    case RCU_LPIRC4M:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt))
        {
            osci_stat = rcu_flag_get(RCU_FLAG_LPIRC4MSTB);
            stb_cnt++;
        }

        /* check whether flag is set */
        if(RESET != rcu_flag_get(RCU_FLAG_LPIRC4MSTB))
        {
            reval = SUCCESS;
        }
        break;
    /* wait PLL0 stable */
    case RCU_PLL0_CK:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt))
        {
            osci_stat = rcu_flag_get(RCU_FLAG_PLL0STB);
            stb_cnt++;
        }

        /* check whether flag is set */
        if(RESET != rcu_flag_get(RCU_FLAG_PLL0STB))
        {
            reval = SUCCESS;
        }
        break;
    /* wait PLL1 stable */
    case RCU_PLL1_CK:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt))
        {
            osci_stat = rcu_flag_get(RCU_FLAG_PLL1STB);
            stb_cnt++;
        }

        /* check whether flag is set */
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

        /* check whether flag is set */
        if(RESET != rcu_flag_get(RCU_FLAG_PLL2STB))
        {
            reval = SUCCESS;
        }
        break;
    /* wait PLLUSBHS0 stable */
    case RCU_PLLUSBHS0_CK:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt))
        {
            osci_stat = rcu_flag_get(RCU_FLAG_PLLUSBHS0STB);
            stb_cnt++;
        }

        /* check whether flag is set */
        if(RESET != rcu_flag_get(RCU_FLAG_PLLUSBHS0STB))
        {
            reval = SUCCESS;
        }
        break;
    /* wait PLLUSBHS1 stable */
    case RCU_PLLUSBHS1_CK:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt))
        {
            osci_stat = rcu_flag_get(RCU_FLAG_PLLUSBHS1STB);
            stb_cnt++;
        }

        /* check whether flag is set */
        if(RESET != rcu_flag_get(RCU_FLAG_PLLUSBHS1STB))
        {
            reval = SUCCESS;
        }
        break;
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
      \arg        RCU_HXTAL: HXTAL
      \arg        RCU_LXTAL: LXTAL
      \arg        RCU_IRC64M: IRC64M
      \arg        RCU_IRC48M: IRC48M
      \arg        RCU_IRC32K: IRC32K
      \arg        RCU_LPIRC4M: LPIRC4M
      \arg        RCU_PLL0_CK: PLL0
      \arg        RCU_PLL1_CK: PLL1
      \arg        RCU_PLL2_CK: PLL2
      \arg        RCU_PLLUSBHS0_CK: PLLUSBHS0
      \arg        RCU_PLLUSBHS1_CK: PLLUSBHS1
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
      \arg        RCU_HXTAL: HXTAL
      \arg        RCU_LXTAL: LXTAL
      \arg        RCU_IRC64M: IRC64M
      \arg        RCU_IRC48M: IRC48M
      \arg        RCU_IRC32K: IRC32K
      \arg        RCU_LPIRC4M: LPIRC4M
      \arg        RCU_PLL0_CK: PLL
      \arg        RCU_PLL1_CK: PLL1
      \arg        RCU_PLL2_CK: PLL2
      \arg        RCU_PLLUSBHS0_CK: PLLUSBHS0
      \arg        RCU_PLLUSBHS1_CK: PLLUSBHS1
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
      \arg        RCU_HXTAL: high speed crystal oscillator (HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator (LXTAL)
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
    default:
        break;
    }
}

/*!
    \brief      disable the oscillator bypass mode, HXTALEN or LXTALEN must be reset before it
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator (HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator (LXTAL)
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
    default:
        break;
    }
}

/*!
    \brief      set the IRC64M adjust value
    \param[in]  irc64M_adjval: IRC64M adjust value, must be between 0 and 0x7F
      \arg        0x00 - 0x7F
    \param[out] none
    \retval     none
*/
void rcu_irc64m_adjust_value_set(uint32_t irc64m_adjval)
{
    uint32_t reg;

    reg = RCU_CTL;
    /* reset the IRC64MADJ bits and set according to irc64m_adjval */
    reg &= ~RCU_CTL_IRC64MADJ;
    RCU_CTL = (reg | ((irc64m_adjval & RCU_IRC64M_ADJUST_MASK)));
}

/*!
    \brief      set the LPIRC4M adjust value
    \param[in]  lpirc4M_adjval: LPIRC4M adjust value, must be between 0 and 0x3F
      \arg        0x00 - 0x3F
    \param[out] none
    \retval     none
*/
void rcu_lpirc4m_adjust_value_set(uint32_t lpirc4m_adjval)
{
    uint32_t reg;

    reg = RCU_ADDCTL1;
    /* reset the LPIRC4MTRIM bits and set according to lpirc4M_adjval */
    reg &= ~RCU_ADDCTL1_LPIRC4MTRIM;
    RCU_ADDCTL1 = (reg | ((lpirc4m_adjval & RCU_LPIRC4M_ADJUST_MASK) << RCU_LPIRC4M_ADJUST_OFFSET));
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
    \brief      enable the LXTAL clock monitor
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_lxtal_clock_monitor_enable(void)
{
    RCU_BDCTL |= RCU_BDCTL_LCKMEN;
}

/*!
    \brief      disable the LXTAL clock monitor
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_lxtal_clock_monitor_disable(void)
{
    RCU_BDCTL &= ~RCU_BDCTL_LCKMEN;
}

/*!
    \brief      function to calculate the PLL output frequency
    \param[in]  pllinputfreq: PLL0 / PLL1 / PLL2 input frequency
      \arg        this parameter should be selected between HXTAL_VALUE,irc64mdiv_freq or LPIRC4M_VALUE
    \param[in]  pll_psc: the PLL0 / PLL1 / PLL2 source clock prescaler
      \arg         this parameter should be selected between 1 and 63.
    \param[in]  pll_n: the PLL0 / PLL1 / PLL2 clock multi factor
      \arg        this parameter should be selected between 9 and 512
    \param[in]  fracn: Fractional part of the multiplication factor for PLL0 / PLL1 / PLL2 VCO
      \arg        this parameter should be selected between 0 and 0x1FFF
    \param[in]  pll_pqr: the PLL P / Q / R output frequency division factor from PLL0 / PLL1 / PLL2 VCO clock
      \arg        this parameter should be selected between 1 and 128

    \param[out] none
    \retval     uint32_t: PLL clock frequency
*/
static uint32_t rcu_pll_clock_freq_cal(uint32_t pllinputfreq, uint32_t pll_psc, uint32_t pll_n, uint32_t fracn, uint32_t pll_pqr)
{
    float freq;

    freq = ((float)pllinputfreq / (float)pll_psc) * ((float)pll_n + ((float)fracn / (float)0x2000));

    freq = freq / (float)pll_pqr;

    return (uint32_t)freq;
}

/*!
    \brief    get the system clock, bus and peripheral clock frequency
    \param[in]  clock: the clock frequency which to get
                only one parameter can be selected which is shown as below:
      \arg        CK_SYS: system clock frequency
      \arg        CK_AHB: AHB clock frequency
      \arg        CK_APB1: APB1 clock frequency
      \arg        CK_APB2: APB2 clock frequency
      \arg        CK_APB3: APB3 clock frequency
      \arg        CK_APB4: APB4 clock frequency
      \arg        CK_PLL0P: PLL0P clock frequency
      \arg        CK_PLL0Q: PLL0Q clock frequency
      \arg        CK_PLL0R: PLL0R clock frequency
      \arg        CK_PLL1P: PLL1P clock frequency
      \arg        CK_PLL1Q: PLL1Q clock frequency
      \arg        CK_PLL1R: PLL1R clock frequency
      \arg        CK_PLL2P: PLL1P clock frequency
      \arg        CK_PLL2Q: PLL1Q clock frequency
      \arg        CK_PLL2R: PLL1R clock frequency
      \arg        CK_PER: PER clock frequency
      \arg        CK_USART0: USART0 clock frequency
      \arg        CK_USART1: USART1 clock frequency
      \arg        CK_USART2: USART2 clock frequency
      \arg        CK_USART5: USART5 clock frequency
      \arg        CK_IRC64MDIV: IRC64MDIV clock frequency
      \arg        CK_HXTAL: HXTAL clock frequency
      \arg        CK_LPIRC4M: LPIRC4M clock frequency
    \param[out] none
    \retval     uint32_t: clock frequency of system, AHB, APB1, APB2, APB3, APB4, PLL, PER, USART, IRC64MDIV, HXTAL, LPIRC4M
*/
uint32_t rcu_clock_freq_get(rcu_clock_freq_enum clock)
{
    uint32_t sws, ck_freq = 0U, irc64mdiv_freq = 0U, fracn = 0U;
    uint32_t cksys_freq, ahb_freq, apb1_freq, apb2_freq, apb3_freq, apb4_freq;
    uint32_t pll0p_freq, pll0q_freq, pll0r_freq, pll1p_freq, pll1q_freq, pll1r_freq, pll2p_freq, pll2q_freq, pll2r_freq, per_freq, persel;
    uint32_t pll0psc, pll1psc, pll2psc, pll0n, pll1n, pll2n, pllsel, pll0p, pll0q, pll0r, pll1p, pll1q, pll1r, pll2p, pll2q, pll2r, ck_src, idx, clk_exp;
    uint32_t usart_freq = 0U;

    /* exponent of AHB, APB1 and APB2 clock divider */
    const uint8_t ahb_exp[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
    const uint8_t apb1_exp[8] = {0, 0, 0, 0, 1, 2, 3, 4};
    const uint8_t apb2_exp[8] = {0, 0, 0, 0, 1, 2, 3, 4};
    const uint8_t apb3_exp[8] = {0, 0, 0, 0, 1, 2, 3, 4};
    const uint8_t apb4_exp[8] = {0, 0, 0, 0, 1, 2, 3, 4};

    irc64mdiv_freq = rcu_irc64mdiv_freq_get();
    sws = GET_BITS(RCU_CFG0, 2, 3);

    switch(sws)
    {
    /* IRC64MDIV is selected as CK_SYS */
    case SEL_IRC64MDIV:
        cksys_freq = irc64mdiv_freq;
        break;
    /* LPIRC4M is selected as CK_SYS */
    case SEL_LPIRC4M:
        cksys_freq = LPIRC4M_VALUE;
        break;
    /* HXTAL is selected as CK_SYS */
    case SEL_HXTAL:
        cksys_freq = HXTAL_VALUE;
        break;
    /* PLL0P is selected as CK_SYS */
    case SEL_PLL0P:
        /* get the value of PLL0PSC[5:0] */
        pll0psc = GET_BITS(RCU_PLL0, 0U, 5U);
        pll0n = (GET_BITS(RCU_PLL0, 6U, 14U) + 1U);
        pll0p = (GET_BITS(RCU_PLL0, 16U, 22U) + 1U);

        if((RCU_PLL0FRA & RCU_PLL0FRA_PLL0FRAEN) != 0U)
        {
            fracn = GET_BITS(RCU_PLL0FRA, 0U, 12U);
        }

        /* PLL clock source selection, HXTAL or IRC64MDIV */
        pllsel = (RCU_PLLALL & RCU_PLLALL_PLLSEL);

        if(RCU_PLLSRC_HXTAL == pllsel)
        {
            ck_src = HXTAL_VALUE;
        } else if(RCU_PLLSRC_IRC64MDIV == pllsel)
        {
            ck_src = irc64mdiv_freq;
        } else {
            ck_src = LPIRC4M_VALUE;
        }

        cksys_freq = rcu_pll_clock_freq_cal(ck_src, pll0psc, pll0n, fracn, pll0p);
        break;
    /* IRC64MDIV is selected as CK_SYS */
    default:
        cksys_freq = irc64mdiv_freq;
        break;
    }

    /* calculate AHB clock frequency */
    idx = GET_BITS(RCU_CFG0, 4, 7);
    clk_exp = ahb_exp[idx];
    ahb_freq = cksys_freq >> clk_exp;

    /* calculate APB1 clock frequency */
    idx = GET_BITS(RCU_CFG0, 10, 12);
    clk_exp = apb1_exp[idx];
    apb1_freq = ahb_freq >> clk_exp;

    /* calculate APB2 clock frequency */
    idx = GET_BITS(RCU_CFG0, 13, 15);
    clk_exp = apb2_exp[idx];
    apb2_freq = ahb_freq >> clk_exp;

    /* calculate APB3 clock frequency */
    idx = GET_BITS(RCU_CFG0, 27, 29);
    clk_exp = apb3_exp[idx];
    apb3_freq = ahb_freq >> clk_exp;

    /* calculate APB4 clock frequency */
    idx = GET_BITS(RCU_CFG0, 24, 26);
    clk_exp = apb4_exp[idx];
    apb4_freq = ahb_freq >> clk_exp;

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
    case CK_APB3:
        ck_freq = apb3_freq;
        break;
    case CK_APB4:
        ck_freq = apb4_freq;
        break;
    case CK_PLL0P:
        pll0p_freq = 0U;
        /* calculate pllp clock frequency */
        pll0psc = GET_BITS(RCU_PLL0, 0U, 5U);
        pll0n = (GET_BITS(RCU_PLL0, 6U, 14U) + 1U);
        pll0p = (GET_BITS(RCU_PLL0, 16U, 22U) + 1U);

        if((RCU_PLL0FRA & RCU_PLL0FRA_PLL0FRAEN) != 0U)
        {
            fracn = GET_BITS(RCU_PLL0FRA, 0U, 12U);
        }

        /* PLL clock source selection (HXTAL, IRC64MDIV or LPIRC4M) */
        pllsel = (RCU_PLLALL & RCU_PLLALL_PLLSEL);

        if(RCU_PLLSRC_HXTAL == pllsel)
        {
            ck_src = HXTAL_VALUE;
        } else if(RCU_PLLSRC_IRC64MDIV == pllsel)
        {
            ck_src = irc64mdiv_freq;
        } else {
            ck_src = LPIRC4M_VALUE;
        }

        if((pll0psc != 0U) && (ck_src != 0U))
        {
            if((RCU_PLLADDCTL & RCU_PLLADDCTL_PLL0PEN) != 0U)
            {
                pll0p_freq = rcu_pll_clock_freq_cal(ck_src, pll0psc, pll0n, fracn, pll0p);
            }
        }

        ck_freq = pll0p_freq;
        break;
    case CK_PLL0R:
        pll0r_freq = 0U;
        /* calculate pllr clock frequency */
        pll0psc = GET_BITS(RCU_PLL0, 0U, 5U);
        pll0n = (GET_BITS(RCU_PLL0, 6U, 14U) + 1U);
        pll0r = (GET_BITS(RCU_PLL0, 24U, 30U) + 1U);

        if((RCU_PLL0FRA & RCU_PLL0FRA_PLL0FRAEN) != 0U)
        {
            fracn = GET_BITS(RCU_PLL0FRA, 0U, 12U);
        }

        /* PLL clock source selection (HXTAL, IRC64MDIV or LPIRC4M) */
        pllsel = (RCU_PLLALL & RCU_PLLALL_PLLSEL);

        if(RCU_PLLSRC_HXTAL == pllsel)
        {
            ck_src = HXTAL_VALUE;
        } else if(RCU_PLLSRC_IRC64MDIV == pllsel)
        {
            ck_src = irc64mdiv_freq;
        } else {
            ck_src = LPIRC4M_VALUE;
        }

        if((pll0psc != 0U) && (ck_src != 0U))
        {
            if((RCU_PLLADDCTL & RCU_PLLADDCTL_PLL0REN) != 0U)
            {
                pll0r_freq = rcu_pll_clock_freq_cal(ck_src, pll0psc, pll0n, fracn, pll0r);
            }
        }

        ck_freq = pll0r_freq;
        break;
    case CK_PLL0Q:
        pll0q_freq = 0U;
        /* calculate pllq clock frequency */
        pll0psc = GET_BITS(RCU_PLL0, 0U, 5U);
        pll0n = (GET_BITS(RCU_PLL0, 6U, 14U) + 1U);
        pll0q = (GET_BITS(RCU_PLLADDCTL, 0U, 6U) + 1U);

        if((RCU_PLL0FRA & RCU_PLL0FRA_PLL0FRAEN) != 0U)
        {
            fracn = GET_BITS(RCU_PLL0FRA, 0U, 12U);
        }

        /* PLL clock source selection (HXTAL, IRC64MDIV or LPIRC4M) */
        pllsel = (RCU_PLLALL & RCU_PLLALL_PLLSEL);

        if(RCU_PLLSRC_HXTAL == pllsel)
        {
            ck_src = HXTAL_VALUE;
        } else if(RCU_PLLSRC_IRC64MDIV == pllsel)
        {
            ck_src = irc64mdiv_freq;
        } else {
            ck_src = LPIRC4M_VALUE;
        }

        if((pll0psc != 0U) && (ck_src != 0U))
        {
            if((RCU_PLLADDCTL & RCU_PLLADDCTL_PLL0QEN) != 0U)
            {
                pll0q_freq = rcu_pll_clock_freq_cal(ck_src, pll0psc, pll0n, fracn, pll0q);
            }
        }

        ck_freq = pll0q_freq;
        break;
    case CK_PLL1P:
        pll1p_freq = 0U;
        /* calculate pll1p clock frequency */
        pll1psc = GET_BITS(RCU_PLL1, 0U, 5U);
        pll1n = (GET_BITS(RCU_PLL1, 6U, 14U) + 1U);
        pll1p = (GET_BITS(RCU_PLL1, 16U, 22U) + 1U);

        if((RCU_PLL1FRA & RCU_PLL1FRA_PLL1FRAEN) != 0U)
        {
            fracn = GET_BITS(RCU_PLL1FRA, 0U, 12U);
        }

        /* PLL clock source selection (HXTAL, IRC64MDIV or LPIRC4M) */
        pllsel = (RCU_PLLALL & RCU_PLLALL_PLLSEL);

        if(RCU_PLLSRC_HXTAL == pllsel)
        {
            ck_src = HXTAL_VALUE;
        } else if(RCU_PLLSRC_IRC64MDIV == pllsel)
        {
            ck_src = irc64mdiv_freq;
        } else {
            ck_src = LPIRC4M_VALUE;
        }

        if((pll1psc != 0U) && (ck_src != 0U))
        {
            if((RCU_PLLADDCTL & RCU_PLLADDCTL_PLL1PEN) != 0U)
            {
                pll1p_freq = rcu_pll_clock_freq_cal(ck_src, pll1psc, pll1n, fracn, pll1p);
            }
        }

        ck_freq = pll1p_freq;
        break;
    case CK_PLL1R:
        pll1r_freq = 0U;
        /* calculate pll1r clock frequency */
        pll1psc = GET_BITS(RCU_PLL1, 0U, 5U);
        pll1n = (GET_BITS(RCU_PLL1, 6U, 14U) + 1U);
        pll1r = (GET_BITS(RCU_PLL1, 24U, 30U) + 1U);

        if((RCU_PLL1FRA & RCU_PLL1FRA_PLL1FRAEN) != 0U)
        {
            fracn = GET_BITS(RCU_PLL1FRA, 0U, 12U);
        }

        /* PLL clock source selection (HXTAL, IRC64MDIV or LPIRC4M) */
        pllsel = (RCU_PLLALL & RCU_PLLALL_PLLSEL);

        if(RCU_PLLSRC_HXTAL == pllsel)
        {
            ck_src = HXTAL_VALUE;
        } else if(RCU_PLLSRC_IRC64MDIV == pllsel)
        {
            ck_src = irc64mdiv_freq;
        } else {
            ck_src = LPIRC4M_VALUE;
        }

        if((pll1psc != 0U) && (ck_src != 0U))
        {
            if((RCU_PLLADDCTL & RCU_PLLADDCTL_PLL1REN) != 0U)
            {
                pll1r_freq = rcu_pll_clock_freq_cal(ck_src, pll1psc, pll1n, fracn, pll1r);
            }
        }

        ck_freq = pll1r_freq;
        break;
    case CK_PLL1Q:
        pll1q_freq = 0U;
        /* calculate pll1q clock frequency */
        pll1psc = GET_BITS(RCU_PLL1, 0U, 5U);
        pll1n = (GET_BITS(RCU_PLL1, 6U, 14U) + 1U);
        pll1q = (GET_BITS(RCU_PLLADDCTL, 8U, 14U) + 1U);

        if((RCU_PLL1FRA & RCU_PLL1FRA_PLL1FRAEN) != 0U)
        {
            fracn = GET_BITS(RCU_PLL1FRA, 0U, 12U);
        }

        /* PLL clock source selection (HXTAL, IRC64MDIV or LPIRC4M) */
        pllsel = (RCU_PLLALL & RCU_PLLALL_PLLSEL);

        if(RCU_PLLSRC_HXTAL == pllsel)
        {
            ck_src = HXTAL_VALUE;
        } else if(RCU_PLLSRC_IRC64MDIV == pllsel)
        {
            ck_src = irc64mdiv_freq;
        } else {
            ck_src = LPIRC4M_VALUE;
        }

        if((pll1psc != 0U) && (ck_src != 0U))
        {
            if((RCU_PLLADDCTL & RCU_PLLADDCTL_PLL1QEN) != 0U)
            {
                pll1q_freq = rcu_pll_clock_freq_cal(ck_src, pll1psc, pll1n, fracn, pll1q);
            }
        }

        ck_freq = pll1q_freq;
        break;
    case CK_PLL2P:
        pll2p_freq = 0U;
        /* calculate pll2p clock frequency */
        pll2psc = GET_BITS(RCU_PLL2, 0U, 5U);
        pll2n = (GET_BITS(RCU_PLL2, 6U, 14U) + 1U);
        pll2p = (GET_BITS(RCU_PLL2, 16U, 22U) + 1U);

        if((RCU_PLL2FRA & RCU_PLL2FRA_PLL2FRAEN) != 0U)
        {
            fracn = GET_BITS(RCU_PLL2FRA, 0U, 12U);
        }

        /* PLL clock source selection (HXTAL, IRC64MDIV or LPIRC4M) */
        pllsel = (RCU_PLLALL & RCU_PLLALL_PLLSEL);

        if(RCU_PLLSRC_HXTAL == pllsel)
        {
            ck_src = HXTAL_VALUE;
        } else if(RCU_PLLSRC_IRC64MDIV == pllsel)
        {
            ck_src = irc64mdiv_freq;
        } else {
            ck_src = LPIRC4M_VALUE;
        }

        if((pll2psc != 0U) && (ck_src != 0U))
        {
            if((RCU_PLLADDCTL & RCU_PLLADDCTL_PLL2PEN) != 0U)
            {
                pll2p_freq = rcu_pll_clock_freq_cal(ck_src, pll2psc, pll2n, fracn, pll2p);
            }
        }

        ck_freq = pll2p_freq;
        break;
    case CK_PLL2R:
        pll2r_freq = 0U;
        /* calculate pll2r clock frequency */
        pll2psc = GET_BITS(RCU_PLL2, 0U, 5U);
        pll2n = (GET_BITS(RCU_PLL2, 6U, 14U) + 1U);
        pll2r = (GET_BITS(RCU_PLL2, 24U, 30U) + 1U);

        if((RCU_PLL2FRA & RCU_PLL2FRA_PLL2FRAEN) != 0U)
        {
            fracn = GET_BITS(RCU_PLL2FRA, 0U, 12U);
        }

        /* PLL clock source selection (HXTAL, IRC64MDIV or LPIRC4M) */
        pllsel = (RCU_PLLALL & RCU_PLLALL_PLLSEL);

        if(RCU_PLLSRC_HXTAL == pllsel)
        {
            ck_src = HXTAL_VALUE;
        } else if(RCU_PLLSRC_IRC64MDIV == pllsel)
        {
            ck_src = irc64mdiv_freq;
        } else {
            ck_src = LPIRC4M_VALUE;
        }

        if((pll2psc != 0U) && (ck_src != 0U))
        {
            if((RCU_PLLADDCTL & RCU_PLLADDCTL_PLL2REN) != 0U)
            {
                pll2r_freq = rcu_pll_clock_freq_cal(ck_src, pll2psc, pll2n, fracn, pll2r);
            }
        }

        ck_freq = pll2r_freq;
        break;
    case CK_PLL2Q:
        pll2q_freq = 0U;
        /* calculate pll2q clock frequency */
        pll2psc = GET_BITS(RCU_PLL2, 0U, 5U);
        pll2n = (GET_BITS(RCU_PLL2, 6U, 14U) + 1U);
        pll2q = (GET_BITS(RCU_PLLADDCTL, 16U, 22U) + 1U);

        if((RCU_PLL2FRA & RCU_PLL2FRA_PLL2FRAEN) != 0U)
        {
            fracn = GET_BITS(RCU_PLL2FRA, 0U, 12U);
        }

        /* PLL clock source selection (HXTAL, IRC64MDIV or LPIRC4M) */
        pllsel = (RCU_PLLALL & RCU_PLLALL_PLLSEL);

        if(RCU_PLLSRC_HXTAL == pllsel)
        {
            ck_src = HXTAL_VALUE;
        } else if(RCU_PLLSRC_IRC64MDIV == pllsel)
        {
            ck_src = irc64mdiv_freq;
        } else {
            ck_src = LPIRC4M_VALUE;
        }

        if((pll2psc != 0U) && (ck_src != 0U))
        {
            if((RCU_PLLADDCTL & RCU_PLLADDCTL_PLL2QEN) != 0U)
            {
                pll2q_freq = rcu_pll_clock_freq_cal(ck_src, pll2psc, pll2n, fracn, pll2q);
            }
        }

        ck_freq = pll2q_freq;
        break;
    case CK_PER:
        /* calculate peripheral clock frequency */
        persel = (RCU_CFG1 & RCU_CFG1_PERSEL);

        if(RCU_PERSRC_HXTAL == persel)
        {
            per_freq = HXTAL_VALUE;
        } else if(RCU_PLLSRC_IRC64MDIV == persel)
        {
            per_freq = irc64mdiv_freq;
        } else {
            per_freq = LPIRC4M_VALUE;
        }

        ck_freq = per_freq;
        break;
    case CK_USART0:
        /* calculate USART0 clock frequency */
        if(RCU_USARTSRC_APB == (RCU_CFG1 & RCU_CFG1_USART0SEL))
        {
            usart_freq = apb2_freq;
        } else if(RCU_USARTSRC_AHB == (RCU_CFG1 & RCU_CFG1_USART0SEL))
        {
            usart_freq = ahb_freq;
        } else if(RCU_USARTSRC_LXTAL == (RCU_CFG1 & RCU_CFG1_USART0SEL))
        {
            usart_freq = LXTAL_VALUE;
        } else if(RCU_USARTSRC_IRC64MDIV == (RCU_CFG1 & RCU_CFG1_USART0SEL))
        {
            usart_freq = irc64mdiv_freq;
        } else {
        }

        ck_freq = usart_freq;
        break;
    case CK_USART1:
        /* calculate USART1 clock frequency */
        if((RCU_USARTSRC_APB << 18U) == (RCU_CFG1 & RCU_CFG1_USART1SEL))
        {
            usart_freq = apb1_freq;
        } else if((RCU_USARTSRC_AHB << 18U) == (RCU_CFG1 & RCU_CFG1_USART1SEL))
        {
            usart_freq = ahb_freq;
        } else if((RCU_USARTSRC_LXTAL << 18U) == (RCU_CFG1 & RCU_CFG1_USART1SEL))
        {
            usart_freq = LXTAL_VALUE;
        } else if((RCU_USARTSRC_IRC64MDIV << 18U) == (RCU_CFG1 & RCU_CFG1_USART1SEL))
        {
            usart_freq = irc64mdiv_freq;
        } else {
        }

        ck_freq = usart_freq;
        break;
    case CK_USART2:
        /* calculate USART2 clock frequency */
        if((RCU_USARTSRC_APB << 20U) == (RCU_CFG1 & RCU_CFG1_USART2SEL))
        {
            usart_freq = apb1_freq;
        } else if((RCU_USARTSRC_AHB << 20U) == (RCU_CFG1 & RCU_CFG1_USART2SEL))
        {
            usart_freq = ahb_freq;
        } else if((RCU_USARTSRC_LXTAL << 20U) == (RCU_CFG1 & RCU_CFG1_USART2SEL))
        {
            usart_freq = LXTAL_VALUE;
        } else if((RCU_USARTSRC_IRC64MDIV << 20U) == (RCU_CFG1 & RCU_CFG1_USART2SEL))
        {
            usart_freq = irc64mdiv_freq;
        } else {
        }

        ck_freq = usart_freq;
        break;
    case CK_USART5:
        /* calculate USART5 clock frequency */
        if((RCU_USARTSRC_APB << 22U) == (RCU_CFG1 & RCU_CFG1_USART5SEL))
        {
            usart_freq = apb2_freq;
        } else if((RCU_USARTSRC_AHB << 22U) == (RCU_CFG1 & RCU_CFG1_USART5SEL))
        {
            usart_freq = ahb_freq;
        } else if((RCU_USARTSRC_LXTAL << 22U) == (RCU_CFG1 & RCU_CFG1_USART5SEL))
        {
            usart_freq = LXTAL_VALUE;
        } else if((RCU_USARTSRC_IRC64MDIV << 22U) == (RCU_CFG1 & RCU_CFG1_USART5SEL))
        {
            usart_freq = irc64mdiv_freq;
        } else {
        }

        ck_freq = usart_freq;
        break;
    case CK_IRC64MDIV:
        ck_freq = irc64mdiv_freq;
        break;
    case CK_HXTAL:
        ck_freq = HXTAL_VALUE;
        break;
    case CK_LPIRC4M:
        ck_freq = LPIRC4M_VALUE;
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
      \arg        RCU_FLAG_IRC64MSTB: IRC64M stabilization flag
      \arg        RCU_FLAG_HXTALSTB: HXTAL stabilization flag
      \arg        RCU_FLAG_PLL0STB: PLL0 stabilization flag
      \arg        RCU_FLAG_PLL1STB: PLL1 stabilization flag
      \arg        RCU_FLAG_PLL2STB: PLL2 stabilization flag
      \arg        RCU_FLAG_LXTALSTB: LXTAL stabilization flag
      \arg        RCU_FLAG_IRC32KSTB: IRC32K stabilization flag
      \arg        RCU_FLAG_IRC48MSTB: IRC48M stabilization flag
      \arg        RCU_FLAG_LPIRC4MSTB: LPIRC4M stabilization flag
      \arg        RCU_FLAG_PLLUSBHS0STB: PLLUSBHS0 stabilization flag
      \arg        RCU_FLAG_PLLUSBHS1STB: PLLUSBHS1 stabilization flag
      \arg        RCU_FLAG_LCKMD: LXTAL clock failure detection flags
      \arg        RCU_FLAG_BORRST: BOR reset flags
      \arg        RCU_FLAG_EPRST: external PIN reset flag
      \arg        RCU_FLAG_PORRST: Power reset flag
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
    } else {
        return RESET;
    }
}

/*!
    \brief    clear all the reset flag
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_all_reset_flag_clear(void)
{
    RCU_RSTSCK |= RCU_RSTSCK_RSTFC;
}

/*!
    \brief      enable the stabilization interrupt
    \param[in]  interrupt: clock stabilization interrupt, refer to rcu_int_enum
                Only one parameter can be selected which is shown as below:
      \arg        RCU_INT_IRC32KSTB: IRC32K stabilization interrupt enable
      \arg        RCU_INT_LXTALSTB: LXTAL stabilization interrupt enable
      \arg        RCU_INT_IRC64MSTB: IRC64M stabilization interrupt enable
      \arg        RCU_INT_HXTALSTB: HXTAL stabilization interrupt enable
      \arg        RCU_INT_PLL0STB: PLL0 stabilization interrupt enable
      \arg        RCU_INT_PLL1STB: PLL1 stabilization interrupt enable
      \arg        RCU_INT_PLL2STB: PLL2 stabilization interrupt enable
      \arg        RCU_INT_IRC48MSTB: IRC48M stabilization interrupt enable
      \arg        RCU_INT_LPIRC4MSTB: LPIRC4M stabilization interrupt enable
      \arg        RCU_INT_PLLUSBHS0STB: PLLUSBHS0 stabilization interrupt enable
      \arg        RCU_INT_PLLUSBHS1STB: PLLUSBHS1 stabilization interrupt enable
    \param[out] none
    \retval     none
*/
void rcu_interrupt_enable(rcu_int_enum interrupt)
{
    RCU_REG_VAL(interrupt) |= BIT(RCU_BIT_POS(interrupt));
}


/*!
    \brief      disable the stabilization interrupt
    \param[in]  interrupt: clock stabilization interrupt, refer to rcu_int_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_IRC32KSTB: IRC32K stabilization interrupt disable
      \arg        RCU_INT_LXTALSTB: LXTAL stabilization interrupt disable
      \arg        RCU_INT_IRC64MSTB: IRC64M stabilization interrupt disable
      \arg        RCU_INT_HXTALSTB: HXTAL stabilization interrupt disable
      \arg        RCU_INT_PLL0STB: PLL0 stabilization interrupt disable
      \arg        RCU_INT_PLL1STB: PLL1 stabilization interrupt disable
      \arg        RCU_INT_PLL2STB: PLL2 stabilization interrupt disable
      \arg        RCU_INT_IRC48MSTB: IRC48M stabilization interrupt disable
      \arg        RCU_INT_LPIRC4MSTB: LPIRC4M stabilization interrupt disable
      \arg        RCU_INT_PLLUSBHS0STB: PLLUSBHS0 stabilization interrupt disable
      \arg        RCU_INT_PLLUSBHS1STB: PLLUSBHS1 stabilization interrupt disable
    \param[out] none
    \retval     none
*/
void rcu_interrupt_disable(rcu_int_enum interrupt)
{
    RCU_REG_VAL(interrupt) &= ~BIT(RCU_BIT_POS(interrupt));
}

/*!
    \brief      get the clock stabilization interrupt and ckm flags
    \param[in]  int_flag: interrupt and ckm flags, refer to rcu_int_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_FLAG_IRC32KSTB: IRC32K stabilization interrupt flag
      \arg        RCU_INT_FLAG_LXTALSTB: LXTAL stabilization interrupt flag
      \arg        RCU_INT_FLAG_IRC64MSTB: IRC64M stabilization interrupt flag
      \arg        RCU_INT_FLAG_HXTALSTB: HXTAL stabilization interrupt flag
      \arg        RCU_INT_FLAG_PLL0STB: PLL0 stabilization interrupt flag
      \arg        RCU_INT_FLAG_PLL1STB: PLL1 stabilization interrupt flag
      \arg        RCU_INT_FLAG_PLL2STB: PLL2 stabilization interrupt flag
      \arg        RCU_INT_FLAG_CKM: HXTAL clock stuck interrupt flag
      \arg        RCU_INT_FLAG_LCKM: LXTAL clock stuck interrupt flag
      \arg        RCU_INT_FLAG_LPIRC4MSTB: LPIRC4M stabilization interrupt flag
      \arg        RCU_INT_FLAG_IRC48MSTB: IRC48M stabilization interrupt flag
      \arg        RCU_INT_FLAG_PLLUSBHS0STB: PLLUSBHS0 stabilization interrupt flag
      \arg        RCU_INT_FLAG_PLLUSBHS1STB: PLLUSBHS1 stabilization interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus rcu_interrupt_flag_get(rcu_int_flag_enum int_flag)
{
    /* get the rcu interrupt flag */
    if(RESET != (RCU_REG_VAL(int_flag) & BIT(RCU_BIT_POS(int_flag))))
    {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear the interrupt flags
    \param[in]  int_flag: clock stabilization and stuck interrupt flags clear, refer to rcu_int_flag_clear_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_FLAG_IRC32KSTB_CLR: IRC32K stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_LXTALSTB_CLR: LXTAL stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_IRC64MSTB_CLR: IRC64M stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_HXTALSTB_CLR: HXTAL stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_PLL0STB_CLR: PLL0 stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_PLL1STB_CLR: PLL1 stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_PLL2STB_CLR: PLL2 stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_CKM_CLR: clock stuck interrupt flag clear
      \arg        RCU_INT_FLAG_LCKM: LXTAL clock stuck interrupt flag clear
      \arg        RCU_INT_FLAG_LPIRC4MSTB_CLR: LPIRC4M stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_IRC48MSTB_CLR: IRC48M stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_PLLUSBHS0STB_CLR: PLLUSBHS0 stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_PLLUSBHS1STB_CLR: PLLUSBHS1 stabilization interrupt flag clear
    \param[out] none
    \retval     none
*/
void rcu_interrupt_flag_clear(rcu_int_flag_clear_enum int_flag)
{
    RCU_REG_VAL(int_flag) |= BIT(RCU_BIT_POS(int_flag));
}
