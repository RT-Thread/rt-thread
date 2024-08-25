/*!
    \file    gd32h7xx_pmu.c
    \brief   PMU driver

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

#include "gd32h7xx_pmu.h"

/* PMU register bit offset */
#define PAR_TSW_IRCCNT_OFFSET               ((uint32_t)0x00000010U)               /*!< bit offset of TSW_HSICNT in PMU_PAR */

/*!
    \brief      reset PMU register
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_deinit(void)
{
    /* reset PMU */
    rcu_periph_reset_enable(RCU_PMURST);
    rcu_periph_reset_disable(RCU_PMURST);
}

/*!
    \brief      select low voltage detector threshold
    \param[in]  lvdt_n:
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVDT_0: voltage threshold is 2.1V
      \arg        PMU_LVDT_1: voltage threshold is 2.3V
      \arg        PMU_LVDT_2: voltage threshold is 2.4V
      \arg        PMU_LVDT_3: voltage threshold is 2.6V
      \arg        PMU_LVDT_4: voltage threshold is 2.7V
      \arg        PMU_LVDT_5: voltage threshold is 2.9V
      \arg        PMU_LVDT_6: voltage threshold is 3.0V
      \arg        PMU_LVDT_7: input analog voltage on PB7 (compared with 0.8V)
    \param[out] none
    \retval     none
*/
void pmu_lvd_select(uint32_t lvdt_n)
{
    uint32_t temp;
    temp = PMU_CTL0;
    /* clear LVDT bits */
    temp &= ~PMU_CTL0_LVDT;
    /* set LVDT bits according to lvdt_n */
    temp |= lvdt_n;
    PMU_CTL0 = temp;
}

/*!
    \brief      enable PMU lvd
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_lvd_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_LVDEN;
}

/*!
    \brief      disable PMU lvd
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_lvd_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_LVDEN;
}

/*!
    \brief      select analog voltage detector threshold
    \param[in]  avdt_n:
                only one parameter can be selected which is shown as below:
      \arg        PMU_VAVDVC_0: voltage threshold of analog voltage detector is 1.7V
      \arg        PMU_VAVDVC_1: voltage threshold of analog voltage detector is 2.1V
      \arg        PMU_VAVDVC_2: voltage threshold of analog voltage detector is 2.5V
      \arg        PMU_VAVDVC_3: voltage threshold of analog voltage detector is 2.8V
    \param[out] none
    \retval     none
*/
void pmu_avd_select(uint32_t avdt_n)
{
    uint32_t temp;
    temp = PMU_CTL0;
    /* clear VAVDVC bits */
    temp &= ~PMU_CTL0_VAVDVC;
    /* set VAVDVC bits according to avdt_n */
    temp |= avdt_n;
    PMU_CTL0 = temp;
}

/*!
    \brief      enable PMU analog voltage detector
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_avd_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_VAVDEN;
}

/*!
    \brief      disable PMU analog voltage detector
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_avd_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_VAVDEN;
}

/*!
    \brief      enable PMU V0.9V core voltage detector
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_cvd_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_VOVDEN;
}

/*!
    \brief      disable PMU V0.9V core voltage detector
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_cvd_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_VOVDEN;
}

/*!
    \brief      control the V0.9V core voltage level
    \param[in]  ldo_n:
                only one parameter can be selected which is shown as below:
      \arg        PMU_LDOVS_0: LDO output voltage 0.8V mode
      \arg        PMU_LDOVS_1: LDO output voltage 0.85V mode
      \arg        PMU_LDOVS_2: LDO output voltage 0.9V mode
      \arg        PMU_LDOVS_3: LDO output voltage 0.95V mode
      \arg        PMU_LDOVS_4: LDO output voltage 0.975V mode
      \arg        PMU_LDOVS_5: LDO output voltage 1V mode
    \param[out] none
    \retval     none
*/
void pmu_ldo_output_select(uint32_t ldo_n)
{
    uint32_t temp;
    temp = PMU_CTL3;
    temp &= ~PMU_CTL3_LDOVS;
    temp |= ldo_n;
    PMU_CTL3 = temp;
}

/*!
    \brief      Deep-sleep mode V0.9V core voltage select
    \param[in]  sldo:
                only one parameter can be selected which is shown as below:
      \arg        PMU_SLDOVS_0: SLDOVS scale 0.6V
      \arg        PMU_SLDOVS_1: SLDOVS scale 0.7V
      \arg        PMU_SLDOVS_2: SLDOVS scale 0.8V
      \arg        PMU_SLDOVS_3: SLDOVS scale 0.9V
    \param[out] none
    \retval     none
*/
void pmu_sldo_output_select(uint32_t sldo_n)
{
    uint32_t temp;
    temp = PMU_CTL0;
    temp &= ~PMU_CTL0_SLDOVS;
    temp |= sldo_n;
    PMU_CTL0 = temp;
}

/*!
    \brief      PMU VBAT battery charging resistor selection
    \param[in]  resistor:
                only one parameter can be selected which is shown as below:
      \arg         PMU_VCRSEL_5K: 5kOhms resistor is selected for charing VBAT battery
      \arg         PMU_VCRSEL_1P5K: 1.5kOhms resistor is selected for charing VBAT battery
    \param[out] none
    \retval     none
*/
void pmu_vbat_charging_select(uint32_t resistor)
{
    PMU_CTL2 &= ~PMU_CTL2_VCRSEL;
    PMU_CTL2 |= resistor;
}

/*!
    \brief      enable VBAT battery charging
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vbat_charging_enable(void)
{
    PMU_CTL2 |= PMU_CTL2_VCEN;
}

/*!
    \brief      disable VBAT battery charging
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vbat_charging_disable(void)
{
    PMU_CTL2 &= ~PMU_CTL2_VCEN;
}

/*!
    \brief      enable VBAT and temperature monitoring
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vbat_temp_moniter_enable(void)
{
    PMU_CTL1 |= PMU_CTL1_VBTMEN;
}

/*!
    \brief      disable VBAT and temperature monitoring
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vbat_temp_moniter_disable(void)
{
    PMU_CTL1 &= ~PMU_CTL1_VBTMEN;
}

/*!
    \brief      enable USB regulator
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_usb_regulator_enable(void)
{
    PMU_CTL2 |= PMU_CTL2_USBSEN;
}

/*!
    \brief      disable USB regulator
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_usb_regulator_disable(void)
{
    PMU_CTL2 &= ~PMU_CTL2_USBSEN;
}

/*!
    \brief      enable VDD33USB voltage level detector
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_usb_voltage_detector_enable(void)
{
    PMU_CTL2 |= PMU_CTL2_VUSB33DEN;
}

/*!
    \brief      disable VDD33USB voltage level detector
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_usb_voltage_detector_disable(void)
{
    PMU_CTL2 &= ~PMU_CTL2_VUSB33DEN;
}

/*!
    \brief      power supply configurations
    \param[in]  smpsmode:
                only one parameter can be selected which is shown as below:
      \arg        PMU_LDO_SUPPLY: V0.9V domains are suppplied from the LDO
      \arg        PMU_DIRECT_SMPS_SUPPLY: V0.9V domains are suppplied from the SMPS only
      \arg        PMU_SMPS_1V8_SUPPLIES_LDO: the SMPS 1.8V output supplies the LDO which supplies the V0.9V domains
      \arg        PMU_SMPS_2V5_SUPPLIES_LDO: the SMPS 2.5V output supplies the LDO which supplies the V0.9V domains
      \arg        PMU_SMPS_1V8_SUPPLIES_EXT_AND_LDO: the SMPS 1.8V output supplies an external circuits and the LDO. The V0.9V domains are suppplied from the LDO
      \arg        PMU_SMPS_2V5_SUPPLIES_EXT_AND_LDO: the SMPS 2.5V output supplies an external circuits and the LDO. The V0.9V domains are suppplied from the LDO
      \arg        PMU_SMPS_1V8_SUPPLIES_EXT: the SMPS 1.8V output supplies an external source which supplies the V0.9V domains
      \arg        PMU_SMPS_2V5_SUPPLIES_EXT: the SMPS 2.5V output supplies an external source which supplies the V0.9V domains
      \arg        PMU_BYPASS: the SMPS disabled and the LDO Bypass. The V0.9V domains are supplied from an external source
    \param[out] none
    \retval     none
*/
void pmu_smps_ldo_supply_config(uint32_t smpsmode)
{
    uint32_t temp;
    temp = PMU_CTL2;
    temp &= ~(PMU_CTL2_DVSVC | PMU_CTL2_DVSCFG | PMU_CTL2_DVSEN | PMU_CTL2_LDOEN | PMU_CTL2_BYPASS);
    temp |= smpsmode;
    PMU_CTL2 = temp;

    while(0U == (PMU_CTL3 & PMU_CTL3_VOVRF))
    {
    }

    /* When the SMPS supplies external circuits verify that DVSRF flag is set */
    if((smpsmode == PMU_SMPS_1V8_SUPPLIES_EXT_AND_LDO) ||
            (smpsmode == PMU_SMPS_2V5_SUPPLIES_EXT_AND_LDO)   ||
            (smpsmode == PMU_SMPS_1V8_SUPPLIES_EXT)           ||
            (smpsmode == PMU_SMPS_2V5_SUPPLIES_EXT))
            {
        while(0U == (PMU_CTL2 & PMU_CTL2_DVSRF))
        {
        }
    }
}

/*!
    \brief      enter sleep mode
    \param[in]  sleepmodecmd:
                only one parameter can be selected which is shown as below:
      \arg          WFI_CMD: use WFI command
      \arg          WFE_CMD: use WFE command
    \param[out] none
    \retval     none
*/
void pmu_to_sleepmode(uint8_t sleepmodecmd)
{
    /* clear sleepdeep bit of Cortex-M7 system control register */
    SCB->SCR &= ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);

    /* select WFI or WFE command to enter sleep mode */
    if(WFI_CMD == sleepmodecmd)
    {
        __WFI();
    } else {
        __WFE();
        __WFE();
    }
}

/*!
    \brief      enter deepsleep mode
    \param[in]  deepsleepmodecmd:
                only one parameter can be selected which is shown as below:
      \arg          WFI_CMD: use WFI command
      \arg          WFE_CMD: use WFE command
    \param[out] none
    \retval     none
*/
void pmu_to_deepsleepmode(uint8_t deepsleepmodecmd)
{
    /* clear standby mode */
    PMU_CTL0 &= ~((uint32_t)(PMU_CTL0_STBMOD));

    /* set sleepdeep bit of Cortex-M7 system control register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* select WFI or WFE command to enter deepsleep mode */
    if(WFI_CMD == deepsleepmodecmd)
    {
        __WFI();
    } else {
        __SEV();
        __WFE();
        __WFE();
    }
    /* reset sleepdeep bit of Cortex-M7 system control register */
    SCB->SCR &= ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
}

/*!
    \brief      enter standby mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_to_standbymode(void)
{
    /* set stbmod bit */
    PMU_CTL0 |= PMU_CTL0_STBMOD;

    /* reset wakeup flag */
    PMU_CTL0 |= PMU_CTL0_WURST;

    /* set sleepdeep bit of Cortex-M7 system control register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    REG32( 0xE000E010U ) &= 0x00010004U;
    REG32( 0xE000E180U )  = 0xFFFFFFF3U;
    REG32( 0xE000E184U )  = 0xFFFFFDFFU;
    REG32( 0xE000E188U )  = 0xFFFFFFFFU;
    REG32( 0xE000E18CU )  = 0xFFFFFFFFU;
    REG32( 0xE000E190U )  = 0xFFFFFFFFU;
    REG32( 0xE000E194U )  = 0xFFFFFFFFU;

    /* enter standby mode */
    __WFI();
}

/*!
    \brief      enable PMU wakeup pin
    \param[in]  wakeup_pin:
                only one parameter can be selected which is shown as below:
      \arg        PMU_WAKEUP_PIN0: WKUP Pin 0
      \arg        PMU_WAKEUP_PIN1: WKUP Pin 1
      \arg        PMU_WAKEUP_PIN3: WKUP Pin 3
      \arg        PMU_WAKEUP_PIN5: WKUP Pin 5
    \param[out] none
    \retval     none
*/
void pmu_wakeup_pin_enable(uint32_t wakeup_pin)
{
    PMU_CS |= wakeup_pin;
}

/*!
    \brief      disable PMU wakeup pin
    \param[in]  wakeup_pin:
                only one parameter can be selected which is shown as below:
      \arg        PMU_WAKEUP_PIN0: WKUP Pin 0
      \arg        PMU_WAKEUP_PIN1: WKUP Pin 1
      \arg        PMU_WAKEUP_PIN3: WKUP Pin 3
      \arg        PMU_WAKEUP_PIN5: WKUP Pin 5
    \param[out] none
    \retval     none
*/
void pmu_wakeup_pin_disable(uint32_t wakeup_pin)
{
    PMU_CS &= ~(wakeup_pin);
}

/*!
    \brief      enable backup domain write
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_backup_write_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_BKPWEN;
}

/*!
    \brief      disable backup domain write
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_backup_write_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_BKPWEN;
}

/*!
    \brief      enable backup voltage stabilizer
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_backup_voltage_stabilizer_enable(void)
{
    PMU_CTL1 |= PMU_CTL1_BKPVSEN;
    while(RESET == (PMU_CTL1 & PMU_CTL1_BKPVSRF))
    {
    }
}

/*!
    \brief      disable backup voltage stabilizer
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_backup_voltage_stabilizer_disable(void)
{
    PMU_CTL1 &= ~PMU_CTL1_BKPVSEN;
}

/*!
    \brief      configure IRC counter before enter Deep-sleep mode
    \param[in]  wait_time: 0x0~0x1F, IRC counter before enter Deep-sleep mode
    \param[out] none
    \retval     none
*/
void pmu_enter_deepsleep_wait_time_config(uint32_t wait_time)
{
    uint32_t temp;
    temp = PMU_PAR;
    temp &= ~PMU_PAR_TSW_IRCCNT;
    temp |= (uint32_t)(wait_time << PAR_TSW_IRCCNT_OFFSET);
    PMU_PAR = temp;
}

/*!
    \brief      configure IRC counter before exit Deep-sleep mode
    \param[in]  wait_time: 0x0~0xFFF, IRC counter before exit Deep-sleep mode
    \param[out] none
    \retval     none
*/
void pmu_exit_deepsleep_wait_time_config(uint32_t wait_time)
{
    uint32_t temp;
    temp = PMU_PAR;
    temp &= ~PMU_PAR_CNT;
    temp |= (uint32_t)(wait_time);
    PMU_PAR = temp;
}

/*!
    \brief      get flag state
    \param[in]  flag:
                only one parameter can be selected which is shown as below:
      \arg          PMU_FLAG_WAKEUP: wakeup flag
      \arg          PMU_FLAG_STANDBY: standby flag
      \arg          PMU_FLAG_LVDF: low voltage detector status flag
      \arg          PMU_FLAG_VAVDF: VDDA analog voltage detector voltage output on VDDA flag
      \arg          PMU_FLAG_VOVDF: peripheral voltage on VDDA detector flag
      \arg          PMU_FLAG_VBATLF: VBAT level monitoring versus low threshold
      \arg          PMU_FLAG_VBATHF: VBAT level monitoring versus high threshold
      \arg          PMU_FLAG_TEMPLF: temperature level monitoring versus low threshold
      \arg          PMU_FLAG_TEMPHF: temperature level monitoring versus high threshold
      \arg          PMU_FLAG_DVSRF: step-down voltage stabilizer ready flag bit
      \arg          PMU_FLAG_USB33RF: USB supply ready flag bit
      \arg          PMU_FLAG_PWRRF: power Ready flag bit.
    \param[out] none
    \retval     FlagStatus SET or RESET
*/
FlagStatus pmu_flag_get(uint32_t flag)
{
    if(PMU_REG_VAL(flag) & BIT(PMU_BIT_POS(flag)))
    {
        return  SET;
    } else {
        return  RESET;
    }
}

/*!
    \brief      clear flag bit
    \param[in]  flag_reset:
      \arg        PMU_FLAG_WAKEUP: wakeup flag
      \arg        PMU_FLAG_STANDBY: standby flag
    \param[out] none
    \retval     none
*/
void pmu_flag_clear(uint32_t flag_reset)
{
    if(PMU_FLAG_WAKEUP == flag_reset)
    {
        PMU_CTL0 |= PMU_CTL0_WURST;
    } else {
        if(PMU_FLAG_STANDBY == flag_reset)
        {
            PMU_CTL0 |= PMU_CTL0_STBRST;
        }
    }
}
