/*
*********************************************************************************************************
*                                                AR100 SYSTEM
*                                     AR100 Software System Develop Kits
*                                         clock control unit module
*
*                                    (c) Copyright 2012-2016, Sunny China
*                                             All Rights Reserved
*
* File    : mclk.c
* By      : Superm
* Version : v1.0
* Date    : 2016-7-13
* Descript: module clock management
* Update  : date                auther      ver     notes
*           2016-7-13 8:43:10   Superm     1.0     Create this file.
*********************************************************************************************************
*/

#include "ccu_i.h"
#include "hal_prcm.h"
#include "errno.h"
#include "aw_io.h"
#include "aw_common.h"
#include "errno.h"
#include "compiler_attributes.h"
#include "notifier.h"
#include "delay.h"

static u32 ccu_log2(u32 m)
{
    u32 n = 0;

    while (m >= 2) {
        m = m >> 1;
        n++;
    }

    return n;
}

void ccu_iosc_freq_update(void)
{
    if (ccu_get_mclk_src(CCU_MOD_CLK_APBS2) == CCU_SYS_CLK_IOSC) {
        notifier_notify(&apbs2_notifier_head, CCU_CLK_CLKCHG_REQ, iosc_freq / ccu_get_mclk_div(CCU_MOD_CLK_APBS2));
        notifier_notify(&apbs2_notifier_head, CCU_CLK_CLKCHG_DONE, iosc_freq / ccu_get_mclk_div(CCU_MOD_CLK_APBS2));
    }
}

/*
*********************************************************************************************************
*                                    SET SOURCE OF MODULE CLOCK
*
* Description:  set the source of a specific module clock.
*
* Arguments  :  mclk    : the module clock ID which we want to set source.
*               sclk    : the source clock ID whick we want to set as source.
*
* Returns    :  OK if set source succeeded, others if failed.
*********************************************************************************************************
*/
s32 ccu_set_mclk_src(u32 mclk, u32 sclk)
{
    switch (mclk) {
    case CCU_MOD_CLK_CPUS: {
        switch (sclk) {
        case CCU_SYS_CLK_HOSC: {
            ccu_reg_addr->cpus_clk_cfg.src_sel = 0;
            return OK;
        }
        case CCU_SYS_CLK_LOSC: {
            ccu_reg_addr->cpus_clk_cfg.src_sel = 1;
            return OK;
        }
        case CCU_SYS_CLK_IOSC: {
            ccu_reg_addr->cpus_clk_cfg.src_sel = 2;
            return OK;
        }
        case CCU_SYS_CLK_AUDIO1_2X: {
            ccu_reg_addr->cpus_clk_cfg.src_sel = 3;
            return OK;
        }
        case CCU_SYS_CLK_AUDIO0_DIV2: {
            ccu_reg_addr->cpus_clk_cfg.src_sel = 4;
            return OK;
        }
        default: {
            /* invalid source id for module clock */
            return -EINVAL;
        }
        }
    }
    case CCU_MOD_CLK_APBS2: {
        u32 src_freq;
        u32 src_sel;
        u32 factor_m;

        switch (sclk) {
        case CCU_SYS_CLK_HOSC: {
            src_freq = CCU_HOSC_FREQ;
            src_sel = 0;
            factor_m = 0;
            break;
        }
        case CCU_SYS_CLK_LOSC: {
            src_freq = losc_freq;
            src_sel = 1;
            factor_m = 0;
            break;
        }
        case CCU_SYS_CLK_IOSC: {
            src_freq = iosc_freq;
            src_sel = 2;
            factor_m = 0;
            break;
        }
            /* apbs max freq is 200MHz */
        case CCU_SYS_CLK_PERI_2X: {
            src_freq = CCU_PERIPH0_FREQ / 3;
            src_sel = 3;
            factor_m = 2;
            break;
        }
        case CCU_SYS_CLK_AUDIO0_DIV2: {
            src_freq = CCU_PERIPH0_FREQ / 3;
            src_sel = 4;
            factor_m = 2;
            return -ENOTSUP;
        }
        default: {
            return -EINVAL;
        }
        }
        notifier_notify(&apbs2_notifier_head, CCU_CLK_CLKCHG_REQ,
                src_freq / ccu_get_mclk_div(CCU_MOD_CLK_APBS2));
        ccu_reg_addr->apbs2_cfg.factor_m = factor_m;
        udelay(2);
        ccu_reg_addr->apbs2_cfg.src_sel = src_sel;
        notifier_notify(&apbs2_notifier_head, CCU_CLK_CLKCHG_DONE,
                src_freq / ccu_get_mclk_div(CCU_MOD_CLK_APBS2));

        return OK;
    }
    case CCU_MOD_CLK_C0: {
        switch (sclk) {
        case CCU_SYS_CLK_HOSC: {
            writel(((readl(CCU_CPU_AXI_CFG_REG) & (~(0x3 << 24))) |
                (0x0 << 24)),
                   CCU_CPU_AXI_CFG_REG);
            return OK;
        }
        case CCU_SYS_CLK_LOSC: {
            writel(((readl(CCU_CPU_AXI_CFG_REG) & (~(0x3 << 24))) |
                (0x1 << 24)),
                   CCU_CPU_AXI_CFG_REG);
            return OK;
        }
        case CCU_SYS_CLK_IOSC: {
            writel(((readl(CCU_CPU_AXI_CFG_REG) & (~(0x3 << 24))) |
                (0x2 << 24)),
                   CCU_CPU_AXI_CFG_REG);
            return OK;
        }
        case CCU_SYS_CLK_CPUX: {
            writel(((readl(CCU_CPU_AXI_CFG_REG) & (~(0x3 << 24))) |
                (0x3 << 24)),
                   CCU_CPU_AXI_CFG_REG);
            return OK;
        }
        case CCU_SYS_CLK_PERI_1X: {
            writel(((readl(CCU_CPU_AXI_CFG_REG) & (~(0x3 << 24))) |
                (0x4 << 24)),
                   CCU_CPU_AXI_CFG_REG);
            return OK;
        }
        case CCU_SYS_CLK_PERI_2X: {
            writel(((readl(CCU_CPU_AXI_CFG_REG) & (~(0x3 << 24))) |
                (0x5 << 24)),
                   CCU_CPU_AXI_CFG_REG);
            return OK;
        }
        case CCU_SYS_CLK_PERI_800M: {
            writel(((readl(CCU_CPU_AXI_CFG_REG) & (~(0x3 << 24))) |
                (0x6 << 24)),
                   CCU_CPU_AXI_CFG_REG);
            return OK;
        }
        default: {
            return -EINVAL;
        }
        }
    }
    case CCU_MOD_CLK_PSI:
    case CCU_MOD_CLK_AHB1:
    case CCU_MOD_CLK_AHB2: {
        switch (sclk) {
        case CCU_SYS_CLK_HOSC: {
            writel(((readl(CCU_PSI_AHB1_AHB2_CFG_REG) &
                 (~(0x3 << 24))) |
                (0x0 << 24)),
                   CCU_PSI_AHB1_AHB2_CFG_REG);
            return OK;
        }
        case CCU_SYS_CLK_LOSC: {
            writel(((readl(CCU_PSI_AHB1_AHB2_CFG_REG) &
                 (~(0x3 << 24))) |
                (0x1 << 24)),
                   CCU_PSI_AHB1_AHB2_CFG_REG);
            return OK;
        }
        case CCU_SYS_CLK_IOSC: {
            writel(((readl(CCU_PSI_AHB1_AHB2_CFG_REG) &
                 (~(0x3 << 24))) |
                (0x2 << 24)),
                   CCU_PSI_AHB1_AHB2_CFG_REG);
            return OK;
        }
        case CCU_SYS_CLK_PERI_1X: {
            writel(((readl(CCU_PSI_AHB1_AHB2_CFG_REG) &
                 (~(0x3 << 24))) |
                (0x3 << 24)),
                   CCU_PSI_AHB1_AHB2_CFG_REG);
            return OK;
        }
        default: {
            return -EINVAL;
        }
        }
    }
    case CCU_MOD_CLK_APB1: {
        switch (sclk) {
        case CCU_SYS_CLK_HOSC: {
            writel(((readl(CCU_APB1_CFG_REG) & (~(0x3 << 24))) |
                (0x0 << 24)),
                   CCU_APB1_CFG_REG);
            return OK;
        }
        case CCU_SYS_CLK_LOSC: {
            writel(((readl(CCU_APB1_CFG_REG) & (~(0x3 << 24))) |
                (0x1 << 24)),
                   CCU_APB1_CFG_REG);
            return OK;
        }
        case CCU_SYS_CLK_PSI: {
            writel(((readl(CCU_APB1_CFG_REG) & (~(0x3 << 24))) |
                (0x2 << 24)),
                   CCU_APB1_CFG_REG);
            return OK;
        }
        case CCU_SYS_CLK_PERI_1X: {
            writel(((readl(CCU_APB1_CFG_REG) & (~(0x3 << 24))) |
                (0x3 << 24)),
                   CCU_APB1_CFG_REG);
            return OK;
        }
        default: {
            return -EINVAL;
        }
        }
    }
    case CCU_MOD_CLK_APB2: {
        switch (sclk) {
        case CCU_SYS_CLK_HOSC: {
            writel(((readl(CCU_APB2_CFG_REG) & (~(0x3 << 24))) |
                (0x0 << 24)),
                   CCU_APB2_CFG_REG);
            return OK;
        }
        case CCU_SYS_CLK_LOSC: {
            writel(((readl(CCU_APB2_CFG_REG) & (~(0x3 << 24))) |
                (0x1 << 24)),
                   CCU_APB2_CFG_REG);
            return OK;
        }
        case CCU_SYS_CLK_PSI: {
            writel(((readl(CCU_APB2_CFG_REG) & (~(0x3 << 24))) |
                (0x2 << 24)),
                   CCU_APB2_CFG_REG);
            return OK;
        }
        case CCU_SYS_CLK_PERI_1X: {
            writel(((readl(CCU_APB2_CFG_REG) & (~(0x3 << 24))) |
                (0x3 << 24)),
                   CCU_APB2_CFG_REG);
            return OK;
        }
        default: {
            return -EINVAL;
        }
        }
    }
    case CCU_MOD_CLK_R_CIR_SP: {
        switch (sclk) {
        case CCU_SYS_CLK_LOSC: {
            ccu_reg_addr->r_ir_clk.src_sel = 0;
            return OK;
        }
        case CCU_SYS_CLK_HOSC: {
            ccu_reg_addr->r_ir_clk.src_sel = 1;
            return OK;
        }
        default: {
            return -EINVAL;
        }
        }
    }
    case CCU_MOD_CLK_R_AC_ADC: {
        switch (sclk) {
        case CCU_SYS_CLK_AUDIO0_DIV5:
            ccu_reg_addr->r_ac_adc.src_sel = 0;
            return OK;
        case CCU_SYS_CLK_AUDIO0_DIV2:
            ccu_reg_addr->r_ac_adc.src_sel = 1;
            return OK;
        case CCU_SYS_CLK_AUDIO1_1X:
            ccu_reg_addr->r_ac_adc.src_sel = 2;
            return OK;
        case CCU_SYS_CLK_AUDIO1_4X:
            ccu_reg_addr->r_ac_adc.src_sel = 3;
            return OK;
        default:
            /* invalid source id for module clock */
            return -EINVAL;
        }
    }
    case CCU_MOD_CLK_R_AC_DAC: {
        switch (sclk) {
        case CCU_SYS_CLK_AUDIO0_DIV5:
            ccu_reg_addr->r_ac_dac.src_sel = 0;
            return OK;
        case CCU_SYS_CLK_AUDIO0_DIV2:
            ccu_reg_addr->r_ac_dac.src_sel = 1;
            return OK;
        case CCU_SYS_CLK_AUDIO1_1X:
            ccu_reg_addr->r_ac_dac.src_sel = 2;
            return OK;
        case CCU_SYS_CLK_AUDIO1_4X:
            ccu_reg_addr->r_ac_dac.src_sel = 3;
            return OK;
        default:
            /* invalid source id for module clock */
            return -EINVAL;
        }
    }
    case CCU_MOD_CLK_R_DMIC: {
        switch (sclk) {
        case CCU_SYS_CLK_AUDIO0_DIV5:
            ccu_reg_addr->r_dmic.src_sel = 0;
            return OK;
        case CCU_SYS_CLK_AUDIO0_DIV2:
            ccu_reg_addr->r_dmic.src_sel = 1;
            return OK;
        case CCU_SYS_CLK_AUDIO1_1X:
            ccu_reg_addr->r_dmic.src_sel = 2;
            return OK;
        case CCU_SYS_CLK_AUDIO1_4X:
            ccu_reg_addr->r_dmic.src_sel = 3;
            return OK;
        default:
            /* invalid source id for module clock */
            return -EINVAL;
        }
    }
    case CCU_MOD_CLK_R_I2S0: {
        switch (sclk) {
        case CCU_SYS_CLK_AUDIO0_DIV5:
            ccu_reg_addr->r_i2s0.src_sel = 0;
            return OK;
        case CCU_SYS_CLK_AUDIO0_DIV2:
            ccu_reg_addr->r_i2s0.src_sel = 1;
            return OK;
        case CCU_SYS_CLK_AUDIO1_1X:
            ccu_reg_addr->r_i2s0.src_sel = 2;
            return OK;
        case CCU_SYS_CLK_AUDIO1_4X:
            ccu_reg_addr->r_i2s0.src_sel = 3;
            return OK;
        default:
            /* invalid source id for module clock */
            return -EINVAL;
        }
    }
    case CCU_MOD_CLK_R_I2S0_ASRC: {
        switch (sclk) {
        case CCU_SYS_CLK_AUDIO0_DIV5:
            ccu_reg_addr->r_i2s0_asrc.src_sel = 0;
            return OK;
        case CCU_SYS_CLK_AUDIO0_DIV2:
            ccu_reg_addr->r_i2s0_asrc.src_sel = 1;
            return OK;
        case CCU_SYS_CLK_AUDIO1_1X:
            ccu_reg_addr->r_i2s0_asrc.src_sel = 2;
            return OK;
        case CCU_SYS_CLK_AUDIO1_4X:
            ccu_reg_addr->r_i2s0_asrc.src_sel = 3;
            return OK;
        default:
            /* invalid source id for module clock */
            return -EINVAL;
        }
    }
    case CCU_MOD_CLK_R_I2S1: {
        switch (sclk) {
        case CCU_SYS_CLK_AUDIO0_DIV5:
            ccu_reg_addr->r_i2s1.src_sel = 0;
            return OK;
        case CCU_SYS_CLK_AUDIO0_DIV2:
            ccu_reg_addr->r_i2s1.src_sel = 1;
            return OK;
        case CCU_SYS_CLK_AUDIO1_1X:
            ccu_reg_addr->r_i2s1.src_sel = 2;
            return OK;
        case CCU_SYS_CLK_AUDIO1_4X:
            ccu_reg_addr->r_i2s1.src_sel = 3;
            return OK;
        default:
            /* invalid source id for module clock */
            return -EINVAL;
        }
    }
    case CCU_MOD_CLK_R_LPSD: {
        switch (sclk) {
        case CCU_SYS_CLK_AUDIO0_DIV5:
            ccu_reg_addr->r_lpsd.src_sel = 0;
            return OK;
        case CCU_SYS_CLK_AUDIO0_DIV2:
            ccu_reg_addr->r_lpsd.src_sel = 1;
            return OK;
        case CCU_SYS_CLK_AUDIO1_1X:
            ccu_reg_addr->r_lpsd.src_sel = 2;
            return OK;
        case CCU_SYS_CLK_AUDIO1_4X:
            ccu_reg_addr->r_lpsd.src_sel = 3;
            return OK;
        default:
            /* invalid source id for module clock */
            return -EINVAL;
        }
    }
    default: {
        pr_warning("invaid module clock id (%d) when set source\n", mclk);
        return -EINVAL;
    }
    }
    /* un-reached */
}

/*
*********************************************************************************************************
*                                    GET SOURCE OF MODULE CLOCK
*
* Description:  get the source of a specific module clock.
*
* Arguments  :  mclk    : the module clock ID which we want to get source.
*
* Returns    :  the source clock ID of source clock.
*********************************************************************************************************
*/
s32 ccu_get_mclk_src(u32 mclk)
{
    switch (mclk) {
    case CCU_MOD_CLK_CPUS:
        {
            switch (ccu_reg_addr->cpus_clk_cfg.src_sel) {
            case 0:
                {
                    return CCU_SYS_CLK_HOSC;
                }
            case 1:
                {
                    return CCU_SYS_CLK_LOSC;
                }
            case 2:
                {
                    return CCU_SYS_CLK_IOSC;
                }
            case 3:
                {
                    return CCU_SYS_CLK_PERI_2X;
                }
            case 4:
                {
                    return CCU_SYS_CLK_AUDIO0_DIV2;
                }
            default:
                {
                    /* invalid source id for module clock */
                    return CCU_SYS_CLK_NONE;
                }
            }
        }
    case CCU_MOD_CLK_C0:
        {
            switch ((readl(CCU_CPU_AXI_CFG_REG) >> 24) & 0x3) {
            case 0:
                {
                    return CCU_SYS_CLK_HOSC;
                }
            case 1:
                {
                    return CCU_SYS_CLK_LOSC;
                }
            case 2:
                {
                    return CCU_SYS_CLK_IOSC;
                }
            case 3:
                {
                    return CCU_SYS_CLK_CPUX;
                }
            case 4:
                {
                    return CCU_SYS_CLK_PERI_1X;
                }
            case 5:
                {
                    return CCU_SYS_CLK_PERI_2X;
                }
            case 6:
                {
                    return CCU_SYS_CLK_PERI_800M;
                }
            default:
                {
                    return -EINVAL;
                }
            }
        }
    case CCU_MOD_CLK_PSI:
    case CCU_MOD_CLK_AHB1:
    case CCU_MOD_CLK_AHB2:
        {
            switch ((readl(CCU_PSI_AHB1_AHB2_CFG_REG) >> 24) & 0x3) {
            case 0:
                {
                    return CCU_SYS_CLK_HOSC;
                }
            case 1:
                {
                    return CCU_SYS_CLK_LOSC;
                }
            case 2:
                {
                    return CCU_SYS_CLK_IOSC;
                }
            case 3:
                {
                    return CCU_SYS_CLK_PERI_1X;
                }
            default:
                {
                    return -EINVAL;
                }
            }
        }
    case CCU_MOD_CLK_APB1:
        {
            switch ((readl(CCU_APB1_CFG_REG) >> 24) & 0x3) {
            case 0:
                {
                    return CCU_SYS_CLK_HOSC;
                }
            case 1:
                {
                    return CCU_SYS_CLK_LOSC;
                }
            case 2:
                {
                    return CCU_SYS_CLK_PSI;
                }
            case 3:
                {
                    return CCU_SYS_CLK_PERI_1X;
                }
            default:
                {
                    return -EINVAL;
                }
            }
        }
    case CCU_MOD_CLK_APB2:
        {
            switch ((readl(CCU_APB2_CFG_REG) >> 24) & 0x3) {
            case 0:
                {
                    return CCU_SYS_CLK_HOSC;
                }
            case 1:
                {
                    return CCU_SYS_CLK_LOSC;
                }
            case 2:
                {
                    return CCU_SYS_CLK_PSI;
                }
            case 3:
                {
                    return CCU_SYS_CLK_PERI_1X;
                }
            default:
                {
                    return -EINVAL;
                }
            }
        }
    case CCU_MOD_CLK_AHBS:
        {
            return CCU_SYS_CLK_CPUS;
        }
    case CCU_MOD_CLK_APBS1:
        {
            switch (ccu_reg_addr->apbs1_cfg.src_sel) {
            case 0:
                {
                    return CCU_SYS_CLK_HOSC;
                }
            case 1:
                {
                    return CCU_SYS_CLK_LOSC;
                }
            case 2:
                {
                    return CCU_SYS_CLK_IOSC;
                }
            case 3:
                {
                    return CCU_SYS_CLK_PERI_2X;
                }
            case 4:
                {
                    return CCU_SYS_CLK_AUDIO0_DIV2;
                }
            default:
                {
                    return CCU_SYS_CLK_NONE;
                }
            }
            return CCU_MOD_CLK_AHBS;
        }
    case CCU_MOD_CLK_APBS2:
        {
            switch (ccu_reg_addr->apbs2_cfg.src_sel) {
            case 0:
                {
                    return CCU_SYS_CLK_HOSC;
                }
            case 1:
                {
                    return CCU_SYS_CLK_LOSC;
                }
            case 2:
                {
                    return CCU_SYS_CLK_IOSC;
                }
            case 3:
                {
                    return CCU_SYS_CLK_PERI_2X;
                }
            case 4:
                {
                    return CCU_SYS_CLK_AUDIO0_DIV2;
                }
            default:
                {
                    return CCU_SYS_CLK_NONE;
                }
            }
        }

    case CCU_MOD_CLK_R_ONEWIRE:
    case CCU_MOD_CLK_R_TIMER0_1:
    case CCU_MOD_CLK_R_CIR:
    case CCU_MOD_CLK_R_PIO:
        {
            return CCU_SYS_CLK_APB1;
        }
    case CCU_MOD_CLK_R_RSB:
    case CCU_MOD_CLK_R_TWI:
    case CCU_MOD_CLK_R_UART:
        {
            return CCU_SYS_CLK_APB2;
        }
    case CCU_MOD_CLK_R_CIR_SP:
        {
            switch (ccu_reg_addr->r_ir_clk.src_sel) {
            case 0:
                {
                    return CCU_SYS_CLK_LOSC;
                }
            case 1:
                {
                    return CCU_SYS_CLK_HOSC;
                }
            default:
                {
                    return CCU_SYS_CLK_NONE;
                }
            }
        }
    default:
        {
        pr_warning("invaid module clock id (%d) when set source\n",
               mclk);
        return CCU_SYS_CLK_NONE;
        }
    }
    /* un-reached */
}

s32 calc_clk_audio_ratio_nm(u32 div, u32 *n, u32 *m)
{
    if (div < 33) {
        *n = 0;
    } else if (div < 65) {
        *n = 1;
    } else if (div < 129) {
        *n = 2;
    } else if (div < 257) {
        *n = 3;
    } else {
        *n = 0;
        *m = 0;
        printf("audio_ratio: %x\n", div);
        return -EINVAL;
    }
    *m = div / (1 << (*n)) - 1;
    return OK;
}

s32 calc_clk_ratio_nm(u32 div, u32 *n, u32 *m)
{
    if (div < 17) {
        *n = 0;
        *m = div;
    } else if (div < 33) {
        *n = 1;
        *m = (div + 1) / 2;
    } else if (div < 65) {
        *n = 2;
        *m = (div + 3) / 4;
    } else if (div < 129) {
        *n = 3;
        *m = (div + 7) / 8;
    } else {
        pr_err("icd %x\n", div);
        return -EINVAL;
    }

    return OK;
}

/*
*********************************************************************************************************
*                                    SET DIVIDER OF MODULE CLOCK
*
* Description:  set the divider of a specific module clock.
*
* Arguments  :  mclk    : the module clock ID which we want to set divider.
*               div     : the divider whick we want to set as source.
*
* Returns    :  OK if set divider succeeded, others if failed.
*********************************************************************************************************
*/
s32 ccu_set_mclk_div(u32 mclk, u32 div)
{
    switch (mclk) {
    case CCU_MOD_CLK_CPUS:
        {
            ccu_reg_addr->cpus_clk_cfg.factor_n =
                ccu_log2(div);
            return OK;
        }
    case CCU_MOD_CLK_APBS1:
        {
            ccu_reg_addr->apbs1_cfg.factor_m = div - 1;
            return OK;
        }
    case CCU_MOD_CLK_APBS2:
        {
            u32 factor_n;
            u32 factor_m;

            if (calc_clk_ratio_nm(div, &factor_n, &factor_m) != OK) {
                return -EFAULT;
            }
            ccu_reg_addr->apbs2_cfg.factor_n = ccu_log2(factor_n);
            ccu_reg_addr->apbs2_cfg.factor_m = factor_m - 1;
            return OK;
        }
    case CCU_MOD_CLK_R_CIR_SP:
        {
            u32 factor_n;
            u32 factor_m;

            if (calc_clk_ratio_nm(div, &factor_n, &factor_m) != OK) {
                return -EFAULT;
            }
            ccu_reg_addr->r_ir_clk.factor_n = ccu_log2(factor_n);
            ccu_reg_addr->r_ir_clk.factor_m = factor_m - 1;
            return OK;
        }
    case CCU_MOD_CLK_AXI:
        {
            volatile u32 value;
            value = readl(CCU_CPU_AXI_CFG_REG);
            value &= (~(0x3));
            value |= ((div - 1) & 0x3);
            writel(value, CCU_CPU_AXI_CFG_REG);
            return OK;
        }
    case CCU_MOD_CLK_CPU_APB:
        {
            volatile u32 value;
            value = readl(CCU_CPU_AXI_CFG_REG);
            value &= (~(0x3 << 8));
            value |= ((div - 1) & 0x3) << 8;
            writel(value, CCU_CPU_AXI_CFG_REG);
            return OK;
        }
    case CCU_MOD_CLK_PSI:
    case CCU_MOD_CLK_AHB1:
    case CCU_MOD_CLK_AHB2:
        {
            volatile u32 value;
            u32 factor_n;
            u32 factor_m;

            if (calc_clk_ratio_nm(div, &factor_n, &factor_m) != OK) {
                return -EFAULT;
            }
            value = readl(CCU_PSI_AHB1_AHB2_CFG_REG);
            value &= (~(0x3ff << 0));
            value |= (ccu_log2(factor_n) << 8) | (factor_m - 1);
            writel(value, CCU_PSI_AHB1_AHB2_CFG_REG);

            return OK;
        }
    case CCU_MOD_CLK_APB1:
        {
            volatile u32 value;
            u32 factor_n;
            u32 factor_m;

            if (calc_clk_ratio_nm(div, &factor_n, &factor_m) != OK) {
                return -EFAULT;
            }
            value = readl(CCU_APB1_CFG_REG);
            value &= (~(0x3ff << 0));
            value |= (ccu_log2(factor_n) << 8) | (factor_m - 1);
            writel(value, CCU_APB1_CFG_REG);

            return OK;
        }
    case CCU_MOD_CLK_APB2:
        {
            volatile u32 value;
            u32 factor_n;
            u32 factor_m;

            if (calc_clk_ratio_nm(div, &factor_n, &factor_m) != OK) {
                return -EFAULT;
            }
            value = readl(CCU_APB2_CFG_REG);
            value &= (~(0x3ff << 0));
            value |= (ccu_log2(factor_n) << 8) | (factor_m - 1);
            writel(value, CCU_APB2_CFG_REG);

            return OK;
        }
    case CCU_MOD_CLK_R_LPSD:
        {
            u32 factor_n;
            u32 factor_m;

            if (calc_clk_audio_ratio_nm(div, &factor_n, &factor_m) != OK) {
                return -EFAULT;
            }
            ccu_reg_addr->r_lpsd.factor_n = factor_n;
            ccu_reg_addr->r_lpsd.factor_m0 = factor_m;
            return OK;
        }
    case CCU_MOD_CLK_R_AC_ADC:
        {
            u32 factor_n;
            u32 factor_m;

            if (calc_clk_audio_ratio_nm(div, &factor_n, &factor_m) != OK) {
                return -EFAULT;
            }
            ccu_reg_addr->r_ac_adc.factor_n = factor_n;
            ccu_reg_addr->r_ac_adc.factor_m = factor_m;
            return OK;
        }
    case CCU_MOD_CLK_R_AC_DAC:
        {
            u32 factor_n;
            u32 factor_m;

            if (calc_clk_audio_ratio_nm(div, &factor_n, &factor_m) != OK) {
                return -EFAULT;
            }
            ccu_reg_addr->r_ac_dac.factor_n = factor_n;
            ccu_reg_addr->r_ac_dac.factor_m = factor_m;
            return OK;
        }
    case CCU_MOD_CLK_R_I2S0:
        {
            u32 factor_n;
            u32 factor_m;

            if (calc_clk_audio_ratio_nm(div, &factor_n, &factor_m) != OK) {
                return -EFAULT;
            }
            ccu_reg_addr->r_i2s0.factor_n = factor_n;
            ccu_reg_addr->r_i2s0.factor_m = factor_m;
            return OK;
        }
    case CCU_MOD_CLK_R_I2S0_ASRC:
        {
            u32 factor_n;
            u32 factor_m;

            if (calc_clk_audio_ratio_nm(div, &factor_n, &factor_m) != OK) {
                return -EFAULT;
            }
            ccu_reg_addr->r_i2s0_asrc.factor_n = factor_n;
            ccu_reg_addr->r_i2s0_asrc.factor_m = factor_m;
            return OK;
        }
    case CCU_MOD_CLK_R_I2S1:
        {
            u32 factor_n;
            u32 factor_m;

            if (calc_clk_audio_ratio_nm(div, &factor_n, &factor_m) != OK) {
                return -EFAULT;
            }
            ccu_reg_addr->r_i2s1.factor_n = factor_n;
            ccu_reg_addr->r_i2s1.factor_m = factor_m;
            return OK;
        }
    case CCU_MOD_CLK_R_DMIC:
        {
            u32 factor_n;
            u32 factor_m;

            if (calc_clk_audio_ratio_nm(div, &factor_n, &factor_m) != OK) {
                return -EFAULT;
            }
            ccu_reg_addr->r_dmic.factor_n = factor_n;
            ccu_reg_addr->r_dmic.factor_m = factor_m;
            return OK;
        }
    default:
        {
        pr_warning("invaid module clock id (%d) when set divider\n",
               mclk);
        return -EINVAL;
        }
    }
    /* un-reached */
}

/*
*********************************************************************************************************
*                                    GET DIVIDER OF MODULE CLOCK
*
* Description:  get the divider of a specific module clock.
*
* Arguments  :  mclk    : the module clock ID which we want to get divider.
*
* Returns    :  the divider of the specific module clock.
*********************************************************************************************************
*/
s32 ccu_get_mclk_div(u32 mclk)
{
    switch (mclk) {
    case CCU_MOD_CLK_CPUS: {
        return 1 << (ccu_reg_addr->cpus_clk_cfg.factor_n);
    }
    case CCU_MOD_CLK_AHBS: {
        return 1;
    }
    case CCU_MOD_CLK_APBS1: {
        return (ccu_reg_addr->apbs1_cfg.factor_m + 1);
    }
    case CCU_MOD_CLK_APBS2: {
        return 1 << (ccu_reg_addr->apbs2_cfg.factor_n);
    }
    case CCU_MOD_CLK_R_RTC:
    case CCU_MOD_CLK_R_CPUSCFG:
    case CCU_MOD_CLK_R_PRCM:
    case CCU_MOD_CLK_R_TIMER0_1:
    case CCU_MOD_CLK_R_WDG:
    case CCU_MOD_CLK_R_TWD:
    case CCU_MOD_CLK_R_PWM:
    case CCU_MOD_CLK_R_INTC:
    case CCU_MOD_CLK_R_PIO:
    case CCU_MOD_CLK_R_CIR:
    case CCU_MOD_CLK_R_ONEWIRE:
    case CCU_MOD_CLK_R_TWI:
    case CCU_MOD_CLK_R_UART:
    case CCU_MOD_CLK_R_RSB: {
        return 1;
    }
    case CCU_MOD_CLK_R_AC_ADC: {
        return (ccu_reg_addr->r_ac_adc.factor_m + 1) *
            ccu_reg_addr->r_ac_adc.factor_n;
    }
    case CCU_MOD_CLK_R_AC_DAC: {
        return (ccu_reg_addr->r_ac_dac.factor_m + 1) *
            ccu_reg_addr->r_ac_dac.factor_n;
    }
    case CCU_MOD_CLK_R_DMIC: {
        return (ccu_reg_addr->r_dmic.factor_m + 1) *
            ccu_reg_addr->r_dmic.factor_n;
    }
    case CCU_MOD_CLK_R_I2S0: {
        return (ccu_reg_addr->r_i2s0.factor_m + 1) *
            ccu_reg_addr->r_i2s0.factor_n;
    }
    case CCU_MOD_CLK_R_I2S0_ASRC: {
        return (ccu_reg_addr->r_i2s0_asrc.factor_m + 1) *
            ccu_reg_addr->r_i2s0_asrc.factor_n;
    }
    case CCU_MOD_CLK_R_I2S1: {
        return (ccu_reg_addr->r_i2s1.factor_m + 1) *
            ccu_reg_addr->r_i2s1.factor_n;
    }
    case CCU_MOD_CLK_R_CIR_SP: {
        return (1 << (ccu_reg_addr->r_ir_clk.factor_n)) *
               (ccu_reg_addr->r_ir_clk.factor_m + 1);
    }
    case CCU_MOD_CLK_AXI: {
        volatile u32 value;
        value = readl(CCU_CPU_AXI_CFG_REG);
        return ((value & 0x3) + 1);
    }
    case CCU_MOD_CLK_CPU_APB: {
        volatile u32 value;
        value = readl(CCU_CPU_AXI_CFG_REG);
        return (((value >> 8) & 0x3) + 1);
    }
    default: {
        pr_warning("invaid module clock id (%d) when get divider\n",
               mclk);
        return -EINVAL;
    }
    }
    /* un-reached */
}

/*
*********************************************************************************************************
*                                    SET ON-OFF STATUS OF MODULE CLOCK
*
* Description:  set the on-off status of a specific module clock.
*
* Arguments  :  mclk    : the module clock ID which we want to set on-off status.
*               onoff   : the on-off status which we want to set, the detail please
*                         refer to the clock status of on-off.
*
* Returns    :  OK if set module clock on-off status succeeded, others if failed.
*********************************************************************************************************
*/
s32 ccu_set_mclk_onoff(u32 mclk, s32 onoff)
{
    switch (mclk) {
    case CCU_MOD_CLK_MSGBOX0:
        writel(((readl(CCU_MSGBOX_BGR_REG) & (~(0x1 << 0))) |
            (onoff << 0)),
               CCU_MSGBOX_BGR_REG);
        break;
    case CCU_MOD_CLK_MSGBOX1:
        writel(((readl(CCU_MSGBOX_BGR_REG) & (~(0x1 << 1))) |
            (onoff << 1)),
               CCU_MSGBOX_BGR_REG);
        break;
    case CCU_MOD_CLK_MSGBOXR:
        writel(((readl(CCU_R_MSGBOX_BGR_REG) & (~(0x1 << 0))) |
            (onoff << 0)),
               CCU_R_MSGBOX_BGR_REG);
        break;
    case CCU_MOD_CLK_R_DMA:
        /* bus gating */
        writel(((readl(CCU_R_DMA_BGR_REG) & (~(0x1 << 0))) |
            (onoff << 0)),
               CCU_R_DMA_BGR_REG);
        /* mclk gating */
        writel(((readl(CCU_MBUS_MASTER_CLK_REG) & (~(0x1 << 3))) |
            (onoff << 3)),
               CCU_MBUS_MASTER_CLK_REG);
        return OK;
    case CCU_MOD_CLK_R_TWI: {
        ccu_reg_addr->r_twi.gate = onoff;
        return OK;
    }
    case CCU_MOD_CLK_R_UART: {
        ccu_reg_addr->r_uart.gate = onoff;
        return OK;
    }
    case CCU_MOD_CLK_R_TIMER0_1: {
        ccu_reg_addr->r_timer.gate = onoff;
        return OK;
    }
    case CCU_MOD_CLK_R_TWD: {
        ccu_reg_addr->r_twd.gate = onoff;
        return OK;
    }
    case CCU_MOD_CLK_R_PWM: {
        ccu_reg_addr->r_pwm.gate = onoff;
        return OK;
    }
    /* case CCU_MOD_CLK_R_ONEWIRE: { */
        /* ccu_reg_addr->r_owc.gate = onoff; */
        /* return OK; */
    /* } */
    case CCU_MOD_CLK_R_RTC: {
        ccu_reg_addr->r_rtc.gate = onoff;
        return OK;
    }
    case CCU_MOD_CLK_R_RSB: {
        ccu_reg_addr->r_rsb.gate = onoff;
        return OK;
    }
    case CCU_MOD_CLK_R_CIR: {
        ccu_reg_addr->r_ir.gate = onoff;
        return OK;
    }
    case CCU_MOD_CLK_R_CIR_SP: {
        ccu_reg_addr->r_ir_clk.sclk_gate = onoff;
        return OK;
    }
    case CCU_MOD_CLK_SPINLOCK: {
        writel(((readl(CCU_SPINLOCK_BGR_REG) & (~(0x1 << 0))) |
            (onoff << 0)),
               CCU_SPINLOCK_BGR_REG);
        return OK;
    }
    case CCU_MOD_CLK_MSGBOX: {
        writel(((readl(CCU_MSGBOX_BGR_REG) & (~(0x1 << 0))) |
            (onoff << 0)),
               CCU_MSGBOX_BGR_REG);
        return OK;
    }
    case CCU_MOD_CLK_R_AC_ADC: {
        ccu_reg_addr->r_ac_adc.sclk_gate = onoff;
        return OK;
    }
    case CCU_MOD_CLK_R_AC_DAC: {
        ccu_reg_addr->r_ac_dac.sclk_gate = onoff;
        return OK;
    }
    case CCU_MOD_CLK_R_DMIC: {
        ccu_reg_addr->r_dmic.sclk_gate = onoff;
        return OK;
    }
    case CCU_MOD_CLK_R_I2S0: {
        ccu_reg_addr->r_i2s0.sclk_gate = onoff;
        return OK;
    }
    case CCU_MOD_CLK_R_I2S0_ASRC: {
        ccu_reg_addr->r_i2s0_asrc.sclk_gate = onoff;
        return OK;
    }
    case CCU_MOD_CLK_R_I2S1: {
        ccu_reg_addr->r_i2s1.sclk_gate = onoff;
        return OK;
    }
    case CCU_MOD_CLK_R_LPSD: {
        ccu_reg_addr->r_lpsd.sclk_gate = onoff;
        return OK;
    }
    default: {
        pr_warning("invaid module clock id (%d) when set divider\n",
               mclk);
        return -EINVAL;
    }
    }
    /* un-reached */
    return OK;
}

/*
*********************************************************************************************************
*                                     REGISTER MODULE CB
*
* Description:  register call-back for module clock, when the source frequency
*               of the module clock changed, it will use this call-back to notify
*               module driver.
*
* Arguments  :  mclk    : the module clock ID which we want to register call-back.
*               pcb     : the call-back which we want to register.
*
* Returns    :  OK if register call-back succeeded, others if failed.
*********************************************************************************************************
*/
s32 ccu_reg_mclk_cb(__maybe_unused u32 mclk, __pNotifier_t pcb)
{
    /*
     * we just support apb module clock notifier now.
     * by sunny at 2012-11-23 14:36:14.
     */

    /* insert call-back to apb_notifier_head. */
    return notifier_insert(&apbs2_notifier_head, pcb);
}

/*
*********************************************************************************************************
*                                     UNREGISTER MODULE CB
*
* Description:  unregister call-back for module clock.
*
* Arguments  :  mclk    : the module clock ID which we want to unregister call-back.
*               pcb     : the call-back which we want to unregister.
*
* Returns    :  OK if unregister call-back succeeded, others if failed.
*********************************************************************************************************
*/
s32 ccu_unreg_mclk_cb(__maybe_unused u32 mclk, __pNotifier_t pcb)
{
    /* delete call-back to apb_notifier_head. */
    return notifier_delete(&apbs2_notifier_head, pcb);
}

s32 ccu_set_cpus_src(u32 sclk)
{
    u32 src_freq;
    u32 src_sel;

    switch (sclk) {
    case CCU_SYS_CLK_HOSC:
        {
            src_freq = losc_freq;
            src_sel = 0;
            break;
        }
    case CCU_SYS_CLK_LOSC:
        {
            src_freq = CCU_HOSC_FREQ;
            src_sel = 1;
            break;
        }
    case CCU_SYS_CLK_IOSC:
        {
            src_freq = iosc_freq;
            src_sel = 2;
            break;
        }
    case CCU_SYS_CLK_PLL3:
        {
            src_freq = CCU_CPUS_POST_DIV;
            src_sel = 3;
            break;
        }
    default:
        {
            return -EINVAL;
        }
    }

    /* set cpus clock source */
    ccu_reg_addr->cpus_clk_cfg.src_sel = src_sel;

    return OK;
}
