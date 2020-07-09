/*!
    \file  gd32f4xx_pmu.c
    \brief PMU driver
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#include "gd32f4xx_pmu.h"
#include "core_cm4.h"
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
    \param[in]  pmu_lvdt_n:
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
void pmu_lvd_select(uint32_t pmu_lvdt_n)
{
    /* disable LVD */
    PMU_CTL &= ~PMU_CTL_LVDEN;
    /* clear LVDT bits */
    PMU_CTL &= ~PMU_CTL_LVDT;
    /* set LVDT bits according to pmu_lvdt_n */
    PMU_CTL |= pmu_lvdt_n;
    /* enable LVD */
    PMU_CTL |= PMU_CTL_LVDEN;
}

/*!
    \brief      LDO output voltage select
                this bit set by software when the main PLL closed, before closing PLL, change the system clock to IRC16M or HXTAL
    \param[in]  ldo_output:
      \arg        PMU_LDOVS_LOW: low-driver mode enable in deep-sleep mode
      \arg        PMU_LDOVS_MID: low-driver mode disable in deep-sleep mode
      \arg        PMU_LDOVS_HIGH: low-driver mode disable in deep-sleep mode
    \param[out] none
    \retval     none
*/
void pmu_ldo_output_select(uint32_t ldo_output)
{
    PMU_CTL &= ~PMU_CTL_LDOVS;
    PMU_CTL |= ldo_output;
}

/*!
    \brief      low-driver mode enable in deep-sleep mode
    \param[in]  lowdr_mode:
      \arg        PMU_LOWDRIVER_ENABLE: low-driver mode enable in deep-sleep mode
      \arg        PMU_LOWDRIVER_DISABLE: low-driver mode disable in deep-sleep mode
    \param[out] none
    \retval     none
*/
void pmu_low_driver_mode_enable(uint32_t lowdr_mode)
{
    PMU_CTL &= ~PMU_CTL_LDEN;
    PMU_CTL |= lowdr_mode;
}

/*!
    \brief      high-driver mode switch
                this bit set by software only when IRC16M or HXTAL used as system clock
    \param[in]  highdr_switch:
      \arg        PMU_HIGHDR_SWITCH_NONE: no high-driver mode switch
      \arg        PMU_HIGHDR_SWITCH_EN: high-driver mode switch
    \param[out] none
    \retval     none
*/
void pmu_highdriver_switch_select(uint32_t highdr_switch)
{
    /* wait for HDRF flag set */
    while(SET != pmu_flag_get(PMU_FLAG_HDRF)){
    }
    PMU_CTL &= ~PMU_CTL_HDS;
    PMU_CTL |= highdr_switch;
}

/*!
    \brief      enable high-driver mode
                this bit set by software only when IRC16M or HXTAL used as system clock
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_highdriver_mode_enable(void)
{
    PMU_CTL |= PMU_CTL_HDEN;
}

/*!
    \brief      disable high-driver mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_highdriver_mode_disable(void)
{
    PMU_CTL &= ~PMU_CTL_HDEN;
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
    \brief      low-driver mode when use low power LDO
    \param[in]  mode:
      \arg        PMU_NORMALDR_LOWPWR:  normal driver when use low power LDO
      \arg        PMU_LOWDR_LOWPWR:  low-driver mode enabled when LDEN is 11 and use low power LDO
    \param[out] none
    \retval     none
*/
void pmu_lowdriver_lowpower_config(uint32_t mode)
{
    PMU_CTL &= ~PMU_CTL_LDLP;
    PMU_CTL |= mode;
}

/*!
    \brief      low-driver mode when use normal power LDO
    \param[in]  mode:
      \arg        PMU_NORMALDR_NORMALPWR:  normal driver when use low power LDO
      \arg        PMU_LOWDR_NORMALPWR:  low-driver mode enabled when LDEN is 11 and use low power LDO
    \param[out] none
    \retval     none
*/
void pmu_lowdriver_normalpower_config(uint32_t mode)
{
    PMU_CTL &= ~PMU_CTL_LDNP;
    PMU_CTL |= mode;
}

/*!
    \brief      PMU work at sleep mode
    \param[in]  sleepmodecmd:
      \arg        WFI_CMD: use WFI command
      \arg        WFE_CMD: use WFE command
    \param[out] none
    \retval     none
*/
void pmu_to_sleepmode(uint8_t sleepmodecmd)
{
    /* clear sleepdeep bit of Cortex-M4 system control register */
    SCB->SCR &= ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
    
    /* select WFI or WFE command to enter sleep mode */
    if(WFI_CMD == sleepmodecmd){
        __WFI();
    }else{
        __WFE();
    }
}

/*!
    \brief      PMU work at deepsleep mode
    \param[in]  pmu_ldo
      \arg        PMU_LDO_NORMAL: LDO normal work when pmu enter deepsleep mode
      \arg        PMU_LDO_LOWPOWER: LDO work at low power mode when pmu enter deepsleep mode
    \param[in]  deepsleepmodecmd: 
      \arg        WFI_CMD: use WFI command
      \arg        WFE_CMD: use WFE command
    \param[out] none
    \retval     none
*/
void pmu_to_deepsleepmode(uint32_t pmu_ldo,uint8_t deepsleepmodecmd)
{
    /* clear stbmod and ldolp bits */
    PMU_CTL &= ~((uint32_t)(PMU_CTL_STBMOD | PMU_CTL_LDOLP));
    
    /* set ldolp bit according to pmu_ldo */
    PMU_CTL |= pmu_ldo;
    
    /* set sleepdeep bit of Cortex-M4 system control register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    
    /* select WFI or WFE command to enter deepsleep mode */
    if(WFI_CMD == deepsleepmodecmd){
        __WFI();
    }else{
        __SEV();
        __WFE();
        __WFE();
    }
    /* reset sleepdeep bit of Cortex-M4 system control register */
    SCB->SCR &= ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
}

/*!
    \brief      pmu work at standby mode
    \param[in]  standbymodecmd:
      \arg        WFI_CMD: use WFI command
      \arg        WFE_CMD: use WFE command
    \param[out] none
    \retval     none
*/
void pmu_to_standbymode(uint8_t standbymodecmd)
{
    /* set sleepdeep bit of Cortex-M4 system control register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* set stbmod bit */
    PMU_CTL |= PMU_CTL_STBMOD;
        
    /* reset wakeup flag */
    PMU_CTL |= PMU_CTL_WURST;
    
    /* select WFI or WFE command to enter standby mode */
    if(WFI_CMD == standbymodecmd){
        __WFI();
    }else{
        __WFE();
    }
}

/*!
    \brief      backup SRAM LDO on
    \param[in]  bkp_ldo:
      \arg        PMU_BLDOON_OFF: backup SRAM LDO closed
      \arg        PMU_BLDOON_ON: open the backup SRAM LDO
    \param[out] none
    \retval     none
*/
void pmu_backup_ldo_config(uint32_t bkp_ldo)
{
    PMU_CS &= ~PMU_CS_BLDOON;
    PMU_CS |= bkp_ldo;
}

/*!
    \brief      reset flag bit
    \param[in]  flag_reset:
      \arg        PMU_FLAG_RESET_WAKEUP: reset wakeup flag
      \arg        PMU_FLAG_RESET_STANDBY: reset standby flag
    \param[out] none
    \retval     none
*/
void pmu_flag_reset(uint32_t flag_reset)
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

/*!
    \brief      get flag status
    \param[in]  pmu_flag:
      \arg        PMU_FLAG_WAKEUP: wakeup flag status
      \arg        PMU_FLAG_STANDBY: standby flag status
      \arg        PMU_FLAG_LVD: lvd flag status
      \arg        PMU_FLAG_BLDORF: backup SRAM LDO ready flag
      \arg        PMU_FLAG_LDOVSRF: LDO voltage select ready flag
      \arg        PMU_FLAG_HDRF: high-driver ready flag
      \arg        PMU_FLAG_HDSRF: high-driver switch ready flag
      \arg        PMU_FLAG_LDRF: low-driver mode ready flag 
    \param[out] none
    \retval     FlagStatus SET or RESET
*/
FlagStatus pmu_flag_get(uint32_t pmu_flag )
{
    if(PMU_CS & pmu_flag){
        return  SET;
    }
    return  RESET;
}

/*!
    \brief      enable backup domain write
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_backup_write_enable(void)
{
    PMU_CTL |= PMU_CTL_BKPWEN;
}

/*!
    \brief      disable backup domain write
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_backup_write_disable(void)
{
    PMU_CTL &= ~PMU_CTL_BKPWEN;
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
