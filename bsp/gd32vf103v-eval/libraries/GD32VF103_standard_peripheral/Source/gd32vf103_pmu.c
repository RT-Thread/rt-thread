/*!
    \file    gd32vf103_pmu.c
    \brief   PMU driver

    \version 2019-6-5, V1.0.0, firmware for GD32VF103
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

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

#include "gd32vf103_pmu.h"
#include "riscv_encoding.h"

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
      \arg        PMU_LVDT_0: voltage threshold is 2.2V
      \arg        PMU_LVDT_1: voltage threshold is 2.3V
      \arg        PMU_LVDT_2: voltage threshold is 2.4V
      \arg        PMU_LVDT_3: voltage threshold is 2.5V
      \arg        PMU_LVDT_4: voltage threshold is 2.6V
      \arg        PMU_LVDT_5: voltage threshold is 2.7V
      \arg        PMU_LVDT_6: voltage threshold is 2.8V
      \arg        PMU_LVDT_7: voltage threshold is 2.9V
    \param[out] none
    \retval     none
*/
void pmu_lvd_select(uint32_t lvdt_n)
{
	/* disable LVD */
	PMU_CTL &= ~PMU_CTL_LVDEN;
	/* clear LVDT bits */
	PMU_CTL &= ~PMU_CTL_LVDT;
	/* set LVDT bits according to lvdt_n */
	PMU_CTL |= lvdt_n;
	/* enable LVD */
	PMU_CTL |= PMU_CTL_LVDEN;
}

/*!
    \brief      disable PMU lvd
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_lvd_disable(void)
{
	/* disable LVD */
	PMU_CTL &= ~PMU_CTL_LVDEN;
}

/*!
    \brief      PMU work at sleep mode
    \param[in]  sleepmodecmd:
                only one parameter can be selected which is shown as below:
      \arg        WFI_CMD: use WFI command
      \arg        WFE_CMD: use WFE command
    \param[out] none
    \retval     none
*/
void pmu_to_sleepmode(uint8_t sleepmodecmd)
{
    /* clear sleepdeep bit of Cortex-M3 system control register */
	clear_csr(0x811, 0x1);

    /* select WFI or WFE command to enter sleep mode */
    if(WFI_CMD == sleepmodecmd){
        __WFI();
    }else{
    	clear_csr(mstatus, MSTATUS_MIE);
    	set_csr(0x810, 0x1);
    	__WFI();
    	clear_csr(0x810, 0x1);
    	set_csr(mstatus, MSTATUS_MIE);
    }
}

/*!
    \brief      PMU work at deepsleep mode
    \param[in]  ldo:
                only one parameter can be selected which is shown as below:
      \arg        PMU_LDO_NORMAL: LDO work at normal power mode when pmu enter deepsleep mode
      \arg        PMU_LDO_LOWPOWER: LDO work at low power mode when pmu enter deepsleep mode
    \param[in]  deepsleepmodecmd:
                only one parameter can be selected which is shown as below:
      \arg        WFI_CMD: use WFI command
      \arg        WFE_CMD: use WFE command
    \param[out] none
    \retval     none
*/
void pmu_to_deepsleepmode(uint32_t ldo,uint8_t deepsleepmodecmd)
{
	/* clear stbmod and ldolp bits */
    PMU_CTL &= ~((uint32_t)(PMU_CTL_STBMOD | PMU_CTL_LDOLP));
    /* set ldolp bit according to pmu_ldo */
    PMU_CTL |= ldo;
    /* set CSR_SLEEPVALUE bit of RISC-V system control register */
    set_csr(0x811, 0x1);
    /* select WFI or WFE command to enter deepsleep mode */
    if(WFI_CMD == deepsleepmodecmd){
        __WFI();
    }else{
    	clear_csr(mstatus, MSTATUS_MIE);
    	set_csr(0x810, 0x1);
    	__WFI();
    	clear_csr(0x810, 0x1);
    	set_csr(mstatus, MSTATUS_MIE);
    }
    /* reset sleepdeep bit of RISC-V system control register */
    clear_csr(0x811, 0x1);
}

/*!
    \brief      pmu work at standby mode
    \param[in]  standbymodecmd:
                only one parameter can be selected which is shown as below:
      \arg        WFI_CMD: use WFI command
      \arg        WFE_CMD: use WFE command
    \param[out] none
    \retval     none
*/
void pmu_to_standbymode(uint8_t standbymodecmd)
{
    /* set CSR_SLEEPVALUE bit of RISC-V system control register */
	set_csr(0x811, 0x1);

    /* set stbmod bit */
    PMU_CTL |= PMU_CTL_STBMOD;

    /* reset wakeup flag */
    PMU_CTL |= PMU_CTL_WURST;

    /* select WFI or WFE command to enter standby mode */
    if(WFI_CMD == standbymodecmd){
        __WFI();
    }else{
    	clear_csr(mstatus, MSTATUS_MIE);
    	set_csr(0x810, 0x1);
    	__WFI();
    	clear_csr(0x810, 0x1);
    	set_csr(mstatus, MSTATUS_MIE);
    }
    clear_csr(0x811, 0x1);
}

/*!
    \brief      enable wakeup pin
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_wakeup_pin_enable(void)
{
	PMU_CS |= PMU_CS_WUPEN;
}

/*!
    \brief      disable wakeup pin
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_wakeup_pin_disable(void)
{
	PMU_CS &= ~PMU_CS_WUPEN;
}

/*!
    \brief      enable write access to the registers in backup domain
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_backup_write_enable(void)
{
    PMU_CTL |= PMU_CTL_BKPWEN;
}

/*!
    \brief      disable write access to the registers in backup domain
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_backup_write_disable(void)
{
    PMU_CTL &= ~PMU_CTL_BKPWEN;
}

/*!
    \brief      get flag state
    \param[in]  flag:
                only one parameter can be selected which is shown as below:
      \arg        PMU_FLAG_WAKEUP: wakeup flag
      \arg        PMU_FLAG_STANDBY: standby flag
      \arg        PMU_FLAG_LVD: lvd flag
    \param[out] none
    \retval     FlagStatus SET or RESET
*/
FlagStatus pmu_flag_get(uint32_t flag)
{
    if(PMU_CS & flag){
        return  SET;
    }else{
        return  RESET;
    }
}

/*!
    \brief      clear flag bit
    \param[in]  flag_reset:
                only one parameter can be selected which is shown as below:
      \arg        PMU_FLAG_RESET_WAKEUP: reset wakeup flag
      \arg        PMU_FLAG_RESET_STANDBY: reset standby flag
    \param[out] none
    \retval     none
*/
void pmu_flag_clear(uint32_t flag_reset)
{
    switch(flag_reset){
    case PMU_FLAG_RESET_WAKEUP:
        /* reset wakeup flag */
        PMU_CTL |= PMU_CTL_WURST;
        break;
    case PMU_FLAG_RESET_STANDBY:
        /* reset standby flag */
        PMU_CTL |= PMU_CTL_STBRST;
        break;
    default :
        break;
    }
}
