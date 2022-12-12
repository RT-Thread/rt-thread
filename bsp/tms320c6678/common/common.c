/*
 * Copyright (c) 2021, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-16     Dystopia     the first version
 */

#include "common.h"

CSL_BootcfgRegs * gp_bootcfg_regs = (CSL_BootcfgRegs *)CSL_BOOT_CFG_REGS;
CSL_CgemRegs * gp_cgem_regs = (CSL_CgemRegs *)CSL_CGEM0_5_REG_BASE_ADDRESS_REGS;
CSL_TmrPlusRegs * gp_timer_regs[9] = {
    (CSL_TmrPlusRegs *)CSL_TIMER_0_REGS,
    (CSL_TmrPlusRegs *)CSL_TIMER_1_REGS,
    (CSL_TmrPlusRegs *)CSL_TIMER_2_REGS,
    (CSL_TmrPlusRegs *)CSL_TIMER_3_REGS,
    (CSL_TmrPlusRegs *)CSL_TIMER_4_REGS,
    (CSL_TmrPlusRegs *)CSL_TIMER_5_REGS,
    (CSL_TmrPlusRegs *)CSL_TIMER_6_REGS,
    (CSL_TmrPlusRegs *)CSL_TIMER_7_REGS,
    (CSL_TmrPlusRegs *)(CSL_TIMER_7_REGS+(CSL_TIMER_7_REGS-CSL_TIMER_6_REGS))
};

void cpu_interrupt_init(void)
{
    //clear interrupt and excpetion events
    ICR = IFR;
    ECR = EFR;
    IER = 3;     //disable all interrupts

    /* disable event combine */
    gp_cgem_regs->EVTMASK[0] = 0xffffffff;
    gp_cgem_regs->EVTMASK[1] = 0xffffffff;
    gp_cgem_regs->EVTMASK[2] = 0xffffffff;
    gp_cgem_regs->EVTMASK[3] = 0xffffffff;

     /*Clear all CPU events*/
    gp_cgem_regs->EVTCLR[0] = 0xFFFFFFFF;
    gp_cgem_regs->EVTCLR[1] = 0xFFFFFFFF;
    gp_cgem_regs->EVTCLR[2] = 0xFFFFFFFF;
    gp_cgem_regs->EVTCLR[3] = 0xFFFFFFFF;

    /*Interrupt Service Table Pointer to begining of LL2 memory*/
    ISTP = 0x800000;
}

void keystone_cpu_init(void)
{
    /* clear all interrupt flag/status, setup ISTP to begining of LL2 */
    cpu_interrupt_init();
}

/*===============================Timer=================================*/
void reset_timer(int timer_num)
{
    if(gp_timer_regs[timer_num]->TGCR)
    {
        gp_timer_regs[timer_num]->TGCR = 0;
        gp_timer_regs[timer_num]->TCR= 0;
    }
}

void timer64_init(Timer64_Config * tmrCfg)
{
    reset_timer(tmrCfg->timer_num);

    gp_timer_regs[tmrCfg->timer_num]->CNTLO = 0;
    gp_timer_regs[tmrCfg->timer_num]->CNTHI = 0;

    /*please note, in clock mode, two timer periods generate a clock,
    one timer period output high voltage level, the other timer period
    output low voltage level, so, the timer period should be half to the
    desired output clock period*/
    if(TIMER_PERIODIC_CLOCK == tmrCfg->timerMode)
    {
        tmrCfg->period = tmrCfg->period/2;
    }

    /*the value written into period register is the expected value minus one*/
    gp_timer_regs[tmrCfg->timer_num]->PRDLO = _loll(tmrCfg->period-1);
    gp_timer_regs[tmrCfg->timer_num]->PRDHI = _hill(tmrCfg->period-1);
    if(tmrCfg->reload_period>1)
    {
        gp_timer_regs[tmrCfg->timer_num]->RELLO = _loll(tmrCfg->reload_period-1);
        gp_timer_regs[tmrCfg->timer_num]->RELHI = _hill(tmrCfg->reload_period-1);
    }

    if(TIMER_WATCH_DOG == tmrCfg->timerMode)
    {
        gp_timer_regs[tmrCfg->timer_num]->TGCR =
            /*Select watch-dog mode*/
            (CSL_TMR_TIMMODE_WDT << CSL_TMR_TGCR_TIMMODE_SHIFT)
            /*Remove the timer from reset*/
            | (CSL_TMR_TGCR_TIMLORS_MASK)
            | (CSL_TMR_TGCR_TIMHIRS_MASK);
    }
    else if(TIMER_PERIODIC_WAVE == tmrCfg->timerMode)
    {
        gp_timer_regs[tmrCfg->timer_num]->TGCR = TMR_TGCR_PLUSEN_MASK
            /*for plus featuers, dual 32-bit unchained timer mode should be used*/
            | (CSL_TMR_TIMMODE_DUAL_UNCHAINED << CSL_TMR_TGCR_TIMMODE_SHIFT)
            /*Remove the timer from reset*/
            | (CSL_TMR_TGCR_TIMLORS_MASK);

        //in plus mode, interrupt/event must be enabled manually
        gp_timer_regs[tmrCfg->timer_num]->INTCTL_STAT= TMR_INTCTLSTAT_EN_ALL_CLR_ALL;
    }
    else
    {
        gp_timer_regs[tmrCfg->timer_num]->TGCR =
            /*Select 64-bit general timer mode*/
            (CSL_TMR_TIMMODE_GPT << CSL_TMR_TGCR_TIMMODE_SHIFT)
            /*Remove the timer from reset*/
            | (CSL_TMR_TGCR_TIMLORS_MASK)
            | (CSL_TMR_TGCR_TIMHIRS_MASK);
    }

    /*make timer stop with emulation*/
    gp_timer_regs[tmrCfg->timer_num]->EMUMGT_CLKSPD = (gp_timer_regs[tmrCfg->timer_num]->EMUMGT_CLKSPD&
        ~(CSL_TMR_EMUMGT_CLKSPD_FREE_MASK|CSL_TMR_EMUMGT_CLKSPD_SOFT_MASK));

    if(TIMER_WATCH_DOG == tmrCfg->timerMode)
    {
        /*enable watchdog timer*/
        gp_timer_regs[tmrCfg->timer_num]->WDTCR = CSL_TMR_WDTCR_WDEN_MASK
            | (CSL_TMR_WDTCR_WDKEY_CMD1 << CSL_TMR_WDTCR_WDKEY_SHIFT);

        gp_timer_regs[tmrCfg->timer_num]->TCR =
            (CSL_TMR_CLOCK_INP_NOGATE << CSL_TMR_TCR_TIEN_LO_SHIFT)
            | (CSL_TMR_CLKSRC_INTERNAL << CSL_TMR_TCR_CLKSRC_LO_SHIFT)
            /*The timer is enabled continuously*/
            | (CSL_TMR_ENAMODE_CONT << CSL_TMR_TCR_ENAMODE_LO_SHIFT)
            | ((tmrCfg->pulseWidth << CSL_TMR_TCR_PWID_LO_SHIFT)&CSL_TMR_TCR_PWID_LO_MASK)
            /*select pulse mode*/
            | (CSL_TMR_CP_PULSE << CSL_TMR_TCR_CP_LO_SHIFT)
            | (CSL_TMR_INVINP_UNINVERTED << CSL_TMR_TCR_INVINP_LO_SHIFT)
            | (CSL_TMR_INVOUTP_UNINVERTED << CSL_TMR_TCR_INVOUTP_LO_SHIFT)
            | (0 << CSL_TMR_TCR_TSTAT_LO_SHIFT);

        /*active watchdog timer*/
        gp_timer_regs[tmrCfg->timer_num]->WDTCR = CSL_TMR_WDTCR_WDEN_MASK
            | (CSL_TMR_WDTCR_WDKEY_CMD2 << CSL_TMR_WDTCR_WDKEY_SHIFT);
    }
    else if(TIMER_ONE_SHOT_PULSE == tmrCfg->timerMode)
    {
        gp_timer_regs[tmrCfg->timer_num]->TCR =
            (CSL_TMR_CLOCK_INP_NOGATE << CSL_TMR_TCR_TIEN_LO_SHIFT)
            | (CSL_TMR_CLKSRC_INTERNAL << CSL_TMR_TCR_CLKSRC_LO_SHIFT)
            /*The timer is enabled one-shot*/
            | (CSL_TMR_ENAMODE_ENABLE << CSL_TMR_TCR_ENAMODE_LO_SHIFT)
            | ((tmrCfg->pulseWidth << CSL_TMR_TCR_PWID_LO_SHIFT)&CSL_TMR_TCR_PWID_LO_MASK)
            /*select pulse mode*/
            | (CSL_TMR_CP_PULSE << CSL_TMR_TCR_CP_LO_SHIFT)
            | (CSL_TMR_INVINP_UNINVERTED << CSL_TMR_TCR_INVINP_LO_SHIFT)
            | (CSL_TMR_INVOUTP_UNINVERTED << CSL_TMR_TCR_INVOUTP_LO_SHIFT)
            | (0 << CSL_TMR_TCR_TSTAT_LO_SHIFT);
    }
    else if(TIMER_PERIODIC_CLOCK == tmrCfg->timerMode)
    {
        gp_timer_regs[tmrCfg->timer_num]->TCR =
            (CSL_TMR_CLOCK_INP_NOGATE << CSL_TMR_TCR_TIEN_LO_SHIFT)
            | (CSL_TMR_CLKSRC_INTERNAL << CSL_TMR_TCR_CLKSRC_LO_SHIFT)
            /*The timer is enabled continuously*/
            | (CSL_TMR_ENAMODE_CONT << CSL_TMR_TCR_ENAMODE_LO_SHIFT)
            | ((tmrCfg->pulseWidth << CSL_TMR_TCR_PWID_LO_SHIFT)&CSL_TMR_TCR_PWID_LO_MASK)
            /*select clock mode*/
            | (CSL_TMR_CP_CLOCK << CSL_TMR_TCR_CP_LO_SHIFT)
            | (CSL_TMR_INVINP_UNINVERTED << CSL_TMR_TCR_INVINP_LO_SHIFT)
            | (CSL_TMR_INVOUTP_UNINVERTED << CSL_TMR_TCR_INVOUTP_LO_SHIFT)
            | (0 << CSL_TMR_TCR_TSTAT_LO_SHIFT);
    }
    else if(TIMER_PERIODIC_WAVE == tmrCfg->timerMode)
    {
        gp_timer_regs[tmrCfg->timer_num]->TCR =
            (CSL_TMR_CLOCK_INP_NOGATE << CSL_TMR_TCR_TIEN_LO_SHIFT)
            | (CSL_TMR_CLKSRC_INTERNAL << CSL_TMR_TCR_CLKSRC_LO_SHIFT)
            /*The timer is enabled continuously with period reload*/
            | (CSL_TMR_ENAMODE_CONT_RELOAD << CSL_TMR_TCR_ENAMODE_LO_SHIFT)
            | ((tmrCfg->pulseWidth << CSL_TMR_TCR_PWID_LO_SHIFT)&CSL_TMR_TCR_PWID_LO_MASK)
            /*select clock mode*/
            | (CSL_TMR_CP_CLOCK << CSL_TMR_TCR_CP_LO_SHIFT)
            | (CSL_TMR_INVINP_UNINVERTED << CSL_TMR_TCR_INVINP_LO_SHIFT)
            | (CSL_TMR_INVOUTP_UNINVERTED << CSL_TMR_TCR_INVOUTP_LO_SHIFT)
            | (0 << CSL_TMR_TCR_TSTAT_LO_SHIFT);
    }
    else     /*TIMER_PERIODIC_PULSE*/
    {
        gp_timer_regs[tmrCfg->timer_num]->TCR =
            (CSL_TMR_CLOCK_INP_NOGATE << CSL_TMR_TCR_TIEN_LO_SHIFT)
            | (CSL_TMR_CLKSRC_INTERNAL << CSL_TMR_TCR_CLKSRC_LO_SHIFT)
            /*The timer is enabled continuously*/
            | (CSL_TMR_ENAMODE_CONT << CSL_TMR_TCR_ENAMODE_LO_SHIFT)
            | ((tmrCfg->pulseWidth << CSL_TMR_TCR_PWID_LO_SHIFT)&CSL_TMR_TCR_PWID_LO_MASK)
            /*select clock mode*/
            | (CSL_TMR_CP_PULSE << CSL_TMR_TCR_CP_LO_SHIFT)
            | (CSL_TMR_INVINP_UNINVERTED << CSL_TMR_TCR_INVINP_LO_SHIFT)
            | (CSL_TMR_INVOUTP_UNINVERTED << CSL_TMR_TCR_INVOUTP_LO_SHIFT)
            | (0 << CSL_TMR_TCR_TSTAT_LO_SHIFT);
    }
}
