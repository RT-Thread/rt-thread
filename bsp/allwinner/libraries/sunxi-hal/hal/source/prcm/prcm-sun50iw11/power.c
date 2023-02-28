/*
*********************************************************************************************************
*                                                AR100 SYSTEM
*                                     AR100 Software System Develop Kits
*                                         clock control unit module
*
*                                    (c) Copyright 2012-2016, Sunny China
*                                             All Rights Reserved
*
* File    : power.c
* By      : Sunny
* Version : v1.0
* Date    : 2012-11-22
* Descript: module power manager.
* Update  : date                auther      ver     notes
*           2012-11-22 16:44:06 Sunny       1.0     Create this file.
*********************************************************************************************************
*/

#include "ccu_i.h"
#include "cpucfg_regs.h"
#include "hal_prcm.h"
#include "aw_io.h"
#include "aw_io.h"
#include "aw_common.h"
#include "errno.h"
#include "notifier.h"
#include "delay.h"
#include "platform.h"

static u32 hosc_lock;
static u32 pll_ldo_suspend;
/*
*********************************************************************************************************
*                                    SET POWER OFF STATUS OF HWMODULE
*
* Description:  set the power off gating status of a specific module.
*
* Arguments  :  module  : the module ID which we want to set power off gating status.
*               state   : the power off status which we want to set, the detail please
*                         refer to the status of power-off gating.
*
* Returns    :  OK if set module power off gating status succeeded, others if failed.
*********************************************************************************************************
*/
s32 ccu_set_poweroff_gating_state(s32 module, s32 state)
{
    volatile u32 value;

    switch (module) {
    case PWRCTL_C0CPU0:
        {
            value = readl(C0_CPUX_POWEROFF_GATING_REG);
            value &= (~(0x1 << 0));
            value |= (state & 0x1) << 0;
            writel(value, C0_CPUX_POWEROFF_GATING_REG);
            return OK;
        }
    case PWRCTL_C0CPU1:
        {
            value = readl(C0_CPUX_POWEROFF_GATING_REG);
            value &= (~(0x1 << 1));
            value |= (state & 0x1) << 1;
            writel(value, C0_CPUX_POWEROFF_GATING_REG);
            return OK;
        }
    case PWRCTL_C0CPUX:
        {
            value = readl(C0_CPUX_POWEROFF_GATING_REG);
            value &= (~(0x1 << 4));
            value |= (state & 0x1) << 4;
            writel(value, C0_CPUX_POWEROFF_GATING_REG);
            return OK;
        }
    case PWRCTL_VDD_CPUS:
        {
            ccu_reg_addr->sys_pwroff_gate.vdd_cpus_gate = state;
            return OK;
        }
    case PWRCTL_VDD_AVCC_A:
        {
            ccu_reg_addr->ana_pwroff_gate.avcc_a_gate = state;
            return OK;
        }
    default:
        {
        pr_warning(
            "invaid power control module (%d) when set power-off gating\n",
            module);
        return -EINVAL;
        }
    }
    /* un-reached */
}

struct notifier *hosc_notifier_list = NULL;

s32 ccu_24mhosc_reg_cb(__pNotifier_t pcb)
{
    /* insert call-back to hosc_notifier_list. */
    return notifier_insert(&hosc_notifier_list, pcb);
}

#define XO_CTRL_REG    (SUNXI_R_RTC_PBASE+0x160)
#define DCXO_EN_SHFIT  (1)
s32 ccu_24mhosc_disable(void)
{
    u32 value = 0;

    hosc_lock = 1;

    /* notify 24mhosc will power-off */
    pr_info("broadcast 24mhosc will power-off\n");
    notifier_notify(&hosc_notifier_list, CCU_HOSC_WILL_OFF_NOTIFY, 0);

    /* FIXME: in real board */
    /* disable 24mhosc */
    value = readl(XO_CTRL_REG);
    value &= ~(0x1 << DCXO_EN_SHFIT);
    writel(value, XO_CTRL_REG);

    /* wait 20 cycles */
    udelay(20);

    /* save pll voltage */
    pll_ldo_suspend = (readl(CCU_PLL_CTRL1) >> 16) & 0x7;

    /* power-off pll ldo */
    value = (readl(CCU_PLL_CTRL1) | (0xa7 << 24));
    writel(value, CCU_PLL_CTRL1);
    value = (readl(CCU_PLL_CTRL1) | (0xa7 << 24));
    value &= (~(0x1 << 0));
    writel(value, CCU_PLL_CTRL1);

    return OK;
}

s32 ccu_24mhosc_enable(void)
{
    u32 value = 0;
    volatile int i = 0;

    /* power-on pll ldo */
    value = (readl(CCU_PLL_CTRL1) | (0xa7 << 24));
    writel(value, CCU_PLL_CTRL1);
    value = (readl(CCU_PLL_CTRL1) | (0xa7 << 24));
    value |= (0x1 << 0);
    writel(value, CCU_PLL_CTRL1);

    /* wait 2ms for power-on ready */
    for (i = 64; i; i--) ;

    /* adjust pll voltage */
    value = (readl(CCU_PLL_CTRL1) | (0xa7 << 24));
    writel(value, CCU_PLL_CTRL1);
    value = (readl(CCU_PLL_CTRL1) | (0xa7 << 24));
    value &= (~(0x7 << 16));
    value |= (pll_ldo_suspend << 16);
    writel(value, CCU_PLL_CTRL1);

    /* wait 2ms for voltage ready */
    for (i = 64; i; i--) ;

    /* FIXME: in real board */
    /* enable 24mhosc */
    value = readl(XO_CTRL_REG);
    value |= (0x1 << DCXO_EN_SHFIT);
    writel(value, XO_CTRL_REG);

    /* wait 2ms for 24m hosc ready */
    for (i = 64; i; i--) ;

    /* notify 24mhosc power-on ready */
    pr_info("broadcast 24mhosc power-on ready\n");
    notifier_notify(&hosc_notifier_list, CCU_HOSC_ON_READY_NOTIFY, 0);

    hosc_lock = 0;

    return OK;
}

s32 is_hosc_lock(void)
{
    return hosc_lock;
}
