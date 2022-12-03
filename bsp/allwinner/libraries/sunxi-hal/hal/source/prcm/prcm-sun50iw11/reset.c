/*
*********************************************************************************************************
*                                                AR100 SYSTEM
*                                     AR100 Software System Develop Kits
*                                         clock control unit module
*
*                                    (c) Copyright 2012-2016, Sunny China
*                                             All Rights Reserved
*
* File    : reset.c
* By      : Sunny
* Version : v1.0
* Date    : 2012-11-22
* Descript: reset control of a module.
* Update  : date                auther      ver     notes
*           2012-11-22 16:55:22 Sunny       1.0     Create this file.
*********************************************************************************************************
*/
#include "ccu_i.h"
#include "hal_prcm.h"
#include "aw_io.h"
#include "aw_common.h"
#include "errno.h"

/*
*********************************************************************************************************
*                                    SET RESET STATUS OF MODULE CLOCK
*
* Description:  set the reset status of a specific module clock.
*
* Arguments  :  mclk    : the module clock ID which we want to set reset status.
*       reset   : the reset status which we want to set, the detail please
*             refer to the clock status of reset.
*
* Returns    :  OK if set module clock reset status succeeded, others if failed.
*********************************************************************************************************
*/
s32 ccu_set_mclk_reset(u32 mclk, s32 reset)
{
    switch (mclk) {
    case CCU_MOD_CLK_MSGBOX0:
        writel(((readl(CCU_MSGBOX_BGR_REG) & (~(0x1 << 16))) |
            (reset << 16)),
               CCU_MSGBOX_BGR_REG);
        break;
    case CCU_MOD_CLK_MSGBOX1:
        writel(((readl(CCU_MSGBOX_BGR_REG) & (~(0x1 << 17))) |
            (reset << 17)),
               CCU_MSGBOX_BGR_REG);
        break;
    case CCU_MOD_CLK_MSGBOXR:
        writel(((readl(CCU_R_MSGBOX_BGR_REG) & (~(0x1 << 16))) |
            (reset << 16)),
               CCU_R_MSGBOX_BGR_REG);
        break;
    case CCU_MOD_CLK_R_DMA_MCLK:
        /* this is nothing to do with it */
        return OK;
    case CCU_MOD_CLK_R_DMA:
        {
            writel(((readl(CCU_R_DMA_BGR_REG) & (~(0x1 << 16))) |
                (reset << 16)),
                   CCU_R_DMA_BGR_REG);
            return OK;
        }
    case CCU_MOD_CLK_R_TWI:
        {
            ccu_reg_addr->r_twi.reset = reset;
            return OK;
        }
    case CCU_MOD_CLK_R_UART:
        {
            ccu_reg_addr->r_uart.reset = reset;
            return OK;
        }
    case CCU_MOD_CLK_R_TIMER0_1:
        {
            ccu_reg_addr->r_timer.reset = reset;
            return OK;
        }
    case CCU_MOD_CLK_R_TWD:
        {
            ccu_reg_addr->r_twd.reset = reset;
            return OK;
        }
    case CCU_MOD_CLK_R_PWM:
        {
            ccu_reg_addr->r_pwm.reset = reset;
            return OK;
        }
    case CCU_MOD_CLK_R_RTC:
        {
            ccu_reg_addr->r_owc.reset = reset;
            return OK;
        }
    case CCU_MOD_CLK_R_RSB:
        {
            ccu_reg_addr->r_rsb.reset = reset;
            return OK;
        }
    case CCU_MOD_CLK_R_CIR:
        {
            ccu_reg_addr->r_ir.reset = reset;
            return OK;
        }
    case CCU_MOD_CLK_VDD_SYS:
        {
            ccu_reg_addr->sys_pwr_rst.module_reset = reset;
            return OK;
        }
    case CCU_MOD_CLK_SPINLOCK:
        {
            writel(((readl(CCU_SPINLOCK_BGR_REG) & (~(0x1 << 16)))
                | (reset << 16)), CCU_SPINLOCK_BGR_REG);
            return OK;
        }
    case CCU_MOD_CLK_MSGBOX:
        {
            writel(((readl(CCU_MSGBOX_BGR_REG) & (~(0x1 << 16)))
                | (reset << 16)), CCU_MSGBOX_BGR_REG);
            return OK;
        }
    case CCU_MOD_CLK_R_AC_ADC:
    case CCU_MOD_CLK_R_AC_DAC:
    case CCU_MOD_CLK_R_AUDIO_CODEC:
        {
            if (reset) {
                ccu_reg_addr->r_ac_gate.reset = reset;
                ccu_reg_addr->r_ac_gate.gate = reset;
            } else {
                ccu_reg_addr->r_ac_gate.gate = reset;
                ccu_reg_addr->r_ac_gate.reset = reset;
            }
            return OK;
        }
    case CCU_MOD_CLK_R_DMIC:
        {
            if (reset) {
                ccu_reg_addr->r_dmic_gate.reset = reset;
                ccu_reg_addr->r_dmic_gate.gate = reset;
            } else {
                ccu_reg_addr->r_dmic_gate.gate = reset;
                ccu_reg_addr->r_dmic_gate.reset = reset;
            }
            return OK;
        }
    case CCU_MOD_CLK_R_I2S0:
        {
            if (reset) {
                writel(((readl(CCU_R_I2S_BGR_REG) & (~(0x1 << 0))) |
                    (reset << 0)), CCU_R_I2S_BGR_REG);
                writel(((readl(CCU_R_I2S_BGR_REG) & (~(0x1 << 16))) |
                    (reset << 16)), CCU_R_I2S_BGR_REG);
            } else {
                writel(((readl(CCU_R_I2S_BGR_REG) & (~(0x1 << 16))) |
                    (reset << 16)), CCU_R_I2S_BGR_REG);
                writel(((readl(CCU_R_I2S_BGR_REG) & (~(0x1 << 0))) |
                    (reset << 0)), CCU_R_I2S_BGR_REG);
            }
            return OK;
        }
    case CCU_MOD_CLK_R_I2S1:
        {
            if (reset) {
                writel(((readl(CCU_R_I2S_BGR_REG) & (~(0x1 << 1))) |
                    (reset << 1)), CCU_R_I2S_BGR_REG);
                writel(((readl(CCU_R_I2S_BGR_REG) & (~(0x1 << 17))) |
                    (reset << 17)), CCU_R_I2S_BGR_REG);
            } else {
                writel(((readl(CCU_R_I2S_BGR_REG) & (~(0x1 << 17))) |
                    (reset << 17)), CCU_R_I2S_BGR_REG);
                writel(((readl(CCU_R_I2S_BGR_REG) & (~(0x1 << 1))) |
                    (reset << 1)), CCU_R_I2S_BGR_REG);
            }
            return OK;
        }
    case CCU_MOD_CLK_R_MAD_CFG:
        {
            if (reset) {
                writel(((readl(CCU_R_MAD_BGR_REG) & (~(0x1 << 1))) |
                    (reset << 1)), CCU_R_MAD_BGR_REG);
                writel(((readl(CCU_R_MAD_BGR_REG) & (~(0x1 << 17))) |
                    (reset << 17)), CCU_R_MAD_BGR_REG);
            } else {
                writel(((readl(CCU_R_MAD_BGR_REG) & (~(0x1 << 17))) |
                    (reset << 17)), CCU_R_MAD_BGR_REG);
                writel(((readl(CCU_R_MAD_BGR_REG) & (~(0x1 << 1))) |
                    (reset << 1)), CCU_R_MAD_BGR_REG);
            }
            return OK;
        }
    case CCU_MOD_CLK_R_MAD:
        {
            if (reset) {
                writel(((readl(CCU_R_MAD_BGR_REG) & (~(0x1 << 0))) |
                    (reset << 0)), CCU_R_MAD_BGR_REG);
                writel(((readl(CCU_R_MAD_BGR_REG) & (~(0x1 << 16))) |
                    (reset << 16)), CCU_R_MAD_BGR_REG);
            } else {
                writel(((readl(CCU_R_MAD_BGR_REG) & (~(0x1 << 16))) |
                    (reset << 16)), CCU_R_MAD_BGR_REG);
                writel(((readl(CCU_R_MAD_BGR_REG) & (~(0x1 << 0))) |
                    (reset << 0)), CCU_R_MAD_BGR_REG);
            }
            return OK;
        }
    case CCU_MOD_CLK_R_MAD_SRAM:
        {
            if (reset) {
                writel(((readl(CCU_R_MAD_BGR_REG) & (~(0x1 << 3))) |
                    (reset << 3)), CCU_R_MAD_BGR_REG);
                writel(((readl(CCU_R_MAD_BGR_REG) & (~(0x1 << 19))) |
                    (reset << 19)), CCU_R_MAD_BGR_REG);
            } else {
                writel(((readl(CCU_R_MAD_BGR_REG) & (~(0x1 << 19))) |
                    (reset << 19)), CCU_R_MAD_BGR_REG);
                writel(((readl(CCU_R_MAD_BGR_REG) & (~(0x1 << 3))) |
                    (reset << 3)), CCU_R_MAD_BGR_REG);
            }
            return OK;
        }
    case CCU_MOD_CLK_R_LPSD:
        {
            if (reset) {
                writel(((readl(CCU_R_MAD_BGR_REG) & (~(0x1 << 18))) |
                    (reset << 18)), CCU_R_MAD_BGR_REG);
            } else {
                writel(((readl(CCU_R_MAD_BGR_REG) & (~(0x1 << 18))) |
                    (reset << 18)), CCU_R_MAD_BGR_REG);
            }
            return OK;
        }
    default:
        {
        pr_warning("invaid module clock id (%d) when set reset\n",
               mclk);
        return -EINVAL;
        }
    }
    /* un-reached */
    return OK;
}

s32 ccu_reset_module(u32 mclk)
{
    /* module reset method: set as reset valid->set as reset invalid */
    ccu_set_mclk_reset(mclk, CCU_CLK_RESET);
    ccu_set_mclk_reset(mclk, CCU_CLK_NRESET);

    return OK;
}
