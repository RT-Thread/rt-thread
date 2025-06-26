/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <rtthread.h>
#include <rthw.h>
#include <stdio.h>
#include "sysctl_pwr.h"
#include "drv_hardlock.h"
#include "ioremap.h"
#include "board.h"

volatile sysctl_pwr_s* sysctl_pwr = (volatile sysctl_pwr_s*)PWR_BASE_ADDR;

/*****************************************************************************************
*                                SET POWER DOMAIN'S TIME
*   powerdomain:power domain
*   timtype: idleReq_to_idleAck, idleAck_to_idle.....
*   tim_value: ack_to_tim, idle_to_tim......
*****************************************************************************************/

/* ack timeout value, lpi idleReq to idleAck */
bool sysctl_pwr_set_ack_to_tim(volatile uint32_t *reg, uint32_t ack_to_tim)
{
    volatile uint32_t *ret = reg;

    if((NULL == reg) || (ack_to_tim > 0x1F))
        return false;
    else
    {
        *ret &= 0xffffffe0;
        *reg = (*ret) | (ack_to_tim << 0);

        return true;
    }
}

/* idle timeout value, lpi idleAck to idle */
bool sysctl_pwr_set_idle_to_tim(volatile uint32_t *reg, uint32_t idle_to_tim)
{
    volatile uint32_t *ret = reg;

    if((NULL == reg) || (idle_to_tim > 0x1F))
        return false;
    else
    {
        *ret &= 0xffffe0ff;
        *reg = (*ret) | (idle_to_tim << 8);

        return true;
    }
}

/* NOC power controller in idle min time, idle to idelReq(inactive) */
bool sysctl_pwr_set_idle_hd_tim(volatile uint32_t *reg, uint32_t idle_hd_tim)
{
    volatile uint32_t *ret = reg;

    if((NULL == reg) || (idle_hd_tim > 0x3F))
        return false;
    else
    {
        *ret &= 0xffc0ffff;
        *reg = (*ret) | (idle_hd_tim << 16);

        return true;
    }
}

/*
 * After turning ISO on/off, you need to wait for a while to ensure that the
 * isolation cells in the power domain are actually enabled/disabled.
 */
bool sysctl_pwr_set_iso_su_tim(volatile uint32_t *reg, uint32_t iso_su_tim)
{
    volatile uint32_t *ret = reg;

    if((NULL == reg) || (iso_su_tim > 0xF))
        return false;
    else
    {
        *ret &= 0xfffffff0;
        *reg = (*ret) | (iso_su_tim << 0);

        return true;
    }
}

/*
 * After powering off a power domain, it takes some time to exit the
 * power-off state.
 */
bool sysctl_pwr_set_pd_hd_tim(volatile uint32_t *reg, uint32_t pd_hd_tim)
{
    volatile uint32_t *ret = reg;

    if((NULL == reg) || (pd_hd_tim > 0xFF))
        return false;
    else
    {
        *ret &= 0xfffff00f;
        *reg = (*ret) | (pd_hd_tim << 4);

        return true;
    }
}

/*
 * After restoring the power supply of a power domain (bringup), you need to
 * wait for a period of time to ensure that the power supply of the power domain
 * is fully restored.
 */
bool sysctl_pwr_set_pwr_su_tim(volatile uint32_t *reg, uint32_t pwr_su_tim)
{
    volatile uint32_t *ret = reg;

    if((NULL == reg) || (pwr_su_tim > 0xFF))
        return false;
    else
    {
        *ret &= 0xfff00fff;
        *reg = (*ret) | (pwr_su_tim << 12);

        return true;
    }
}

/* set cpu1 wait for interrupt time */
bool sysctl_pwr_set_wfi_tim(volatile uint32_t *reg, uint32_t wfi_tim)
{
    volatile uint32_t *ret = reg;

    if((NULL == reg) || (wfi_tim > 0xFFF))
        return false;
    else
    {
        *ret &= 0x000fffff;
        *reg = (*ret) | (wfi_tim << 20);

        return true;
    }
}

bool sysctl_pwr_set_tim(sysctl_pwr_domain_e powerdomain, sysctl_pwr_tim_e timtype, uint32_t tim_value)
{
    volatile uint32_t *pwr_reg = NULL;
    volatile uint32_t *lpi_reg = NULL;
    volatile uint32_t *wfi_reg = NULL;

    if((powerdomain >= SYSCTL_PD_MAX) || (timtype >= SYSCTL_PWR_MAX_TIM))
        return false;

    switch(powerdomain)
    {
        case SYSCTL_PD_CPU1:
        {
            pwr_reg = (volatile uint32_t *)&sysctl_pwr->cpu1_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->cpu1_lpi_tim;
            wfi_reg = (volatile uint32_t *)&sysctl_pwr->cpu1_pwr_tim;
            break;
        }
        case SYSCTL_PD_AI:
        {
            pwr_reg = (volatile uint32_t *)&sysctl_pwr->ai_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->ai_lpi_tim;
            break;
        }
        case SYSCTL_PD_DISP:
        {
            pwr_reg = (volatile uint32_t *)&sysctl_pwr->disp_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->disp_lpi_tim;
            break;
        }
        case SYSCTL_PD_VPU:
        {
            pwr_reg = (volatile uint32_t *)&sysctl_pwr->vpu_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->vpu_lpi_tim;
            break;
        }
        case SYSCTL_PD_DPU:
        {
            pwr_reg = (volatile uint32_t *)&sysctl_pwr->dpu_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->dpu_lpi_tim;
            break;
        }
        default:
            return false;
    }

    switch(timtype)
    {
        case SYSCTL_PWR_ACK_TO_TIM:
            return sysctl_pwr_set_ack_to_tim(pwr_reg, tim_value);
        case SYSCTL_PWR_IDLE_TO_TIM:
            return sysctl_pwr_set_idle_to_tim(pwr_reg, tim_value);
        case SYSCTL_PWR_IDLE_HD_TIM:
            return sysctl_pwr_set_idle_hd_tim(pwr_reg, tim_value);
        case SYSCTL_PWR_ISO_SU_TIM:
            return sysctl_pwr_set_iso_su_tim(lpi_reg, tim_value);
        case SYSCTL_PWR_PD_HD_TIM:
            return sysctl_pwr_set_pd_hd_tim(lpi_reg, tim_value);
        case SYSCTL_PWR_SU_TIM:
            return sysctl_pwr_set_pwr_su_tim(lpi_reg, tim_value);
        case SYSCTL_PWR_WFI_TIM:
            return sysctl_pwr_set_wfi_tim(wfi_reg,tim_value);
        default:
            return false;
    }
}

/*****************************************************************************************
*                                GET POWER DOMAIN'S TIME
*   powerdomain:power domain
*   timtype: idleReq_to_idleAck, idleAck_to_idle.....
*   tim_value: ack_to_tim, idle_to_tim......
*****************************************************************************************/

/* ack timeout value, lpi idleReq to idleAck */
bool sysctl_pwr_get_ack_to_tim(volatile uint32_t *reg, uint32_t *ack_to_tim)
{
    if((NULL == reg) || (NULL == ack_to_tim))
        return false;

    *ack_to_tim = ((*reg) >> 0) & 0x1F;
    return true;
}

/* idle timeout value, lpi idleAck to idle */
bool sysctl_pwr_get_idle_to_tim(volatile uint32_t *reg, uint32_t *idle_to_tim)
{
    if((NULL == reg) || (NULL == idle_to_tim))
        return false;

    *idle_to_tim = ((*reg) >> 8) & 0x1F;
    return true;
}

/* NOC power controller in idle min time, idle to idelReq(inactive) */
bool sysctl_pwr_get_idle_hd_tim(volatile uint32_t *reg, uint32_t *idle_hd_tim)
{
    if((NULL == reg) || (NULL == idle_hd_tim))
        return false;

    *idle_hd_tim = ((*reg) >> 16) & 0x3F;
    return true;
}

/*
 * After turning ISO on/off, you need to wait for a while to ensure that the
 * isolation cells in the power domain are actually enabled/disabled.
 */
bool sysctl_pwr_get_iso_su_tim(volatile uint32_t *reg, uint32_t *iso_su_tim)
{
    if((NULL == reg) || (NULL == iso_su_tim))
        return false;

    *iso_su_tim = ((*reg) >> 0) & 0xF;
    return true;
}

/*
 * After powering off a power domain, it takes some time to exit the power-off
 * state.
 */
bool sysctl_pwr_get_pd_hd_tim(volatile uint32_t *reg, uint32_t *pd_hd_tim)
{
    if((NULL == reg) || (NULL == pd_hd_tim))
        return false;

    *pd_hd_tim = ((*reg) >> 4) & 0xFF;
    return true;
}

/*
 * After restoring the power supply of a power domain (bringup), you need to
 * wait for a period of time to ensure that the power supply of the power domain
 * is fully restored.
 */
bool sysctl_pwr_get_pwr_su_tim(volatile uint32_t *reg, uint32_t *pwr_su_tim)
{
    if((NULL == reg) || (NULL == pwr_su_tim))
        return false;

    *pwr_su_tim = ((*reg) >> 12) & 0xFF;
    return true;
}

/* cpu1 wait for interrupt time */
bool sysctl_pwr_get_wfi_tim(volatile uint32_t *reg, uint32_t *wfi_tim)
{
    if((NULL == reg) || (NULL == wfi_tim))
        return false;

    *wfi_tim = (*reg >> 20) & 0xFFF;
    return true;
}

bool sysctl_pwr_get_tim(sysctl_pwr_domain_e powerdomain, sysctl_pwr_tim_e timtype, uint32_t *tim_value)
{
    volatile uint32_t *pwr_reg = NULL;
    volatile uint32_t *lpi_reg = NULL;
    volatile uint32_t *wfi_reg = NULL;

    if((powerdomain >= SYSCTL_PD_MAX) || (timtype >= SYSCTL_PWR_MAX_TIM))
        return false;

    switch(powerdomain)
    {
        case SYSCTL_PD_CPU1:
        {
            pwr_reg = (volatile uint32_t *)&sysctl_pwr->cpu1_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->cpu1_lpi_tim;
            wfi_reg = (volatile uint32_t *)&sysctl_pwr->cpu1_pwr_tim;
            break;
        }
        case SYSCTL_PD_AI:
        {
            pwr_reg = (volatile uint32_t *)&sysctl_pwr->ai_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->ai_lpi_tim;
            break;
        }
        case SYSCTL_PD_DISP:
        {
            pwr_reg = (volatile uint32_t *)&sysctl_pwr->disp_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->disp_lpi_tim;
            break;
        }
        case SYSCTL_PD_VPU:
        {
            pwr_reg = (volatile uint32_t *)&sysctl_pwr->vpu_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->vpu_lpi_tim;
            break;
        }
        case SYSCTL_PD_DPU:
        {
            pwr_reg = (volatile uint32_t *)&sysctl_pwr->dpu_pwr_tim;
            lpi_reg = (volatile uint32_t *)&sysctl_pwr->dpu_lpi_tim;
            break;
        }
        default:
            return false;
    }

    switch(timtype)
    {
        case SYSCTL_PWR_ACK_TO_TIM:
            return sysctl_pwr_get_ack_to_tim(pwr_reg, tim_value);
        case SYSCTL_PWR_IDLE_TO_TIM:
            return sysctl_pwr_get_idle_to_tim(pwr_reg, tim_value);
        case SYSCTL_PWR_IDLE_HD_TIM:
            return sysctl_pwr_get_idle_hd_tim(pwr_reg, tim_value);
        case SYSCTL_PWR_ISO_SU_TIM:
            return sysctl_pwr_get_iso_su_tim(lpi_reg, tim_value);
        case SYSCTL_PWR_PD_HD_TIM:
            return sysctl_pwr_get_pd_hd_tim(lpi_reg, tim_value);
        case SYSCTL_PWR_SU_TIM:
            return sysctl_pwr_get_pwr_su_tim(lpi_reg, tim_value);
        case SYSCTL_PWR_WFI_TIM:
            return sysctl_pwr_get_wfi_tim(wfi_reg,tim_value);
        default:
            return false;
    }
}


/*****************************************************************************************
*                                CPU1 KEEP RESET IN POWEROFF MODE
*   powerdomain: power domain
*   enable: poweron, keep reset; poweroff, remove reset
*****************************************************************************************/

/* It will not be powered off when not working and can be in a reset state */
bool sysctl_pwr_set_poweroff_keep_reset(sysctl_pwr_domain_e powerdomain, bool enable)
{
    volatile uint32_t ret;

    if(SYSCTL_PD_CPU1 == powerdomain)
    {
        ret = sysctl_pwr->cpu1_pwr_lpi_ctl;
        ret &= 0xfff7fff7;
        if(true == enable)
        {
            sysctl_pwr->cpu1_pwr_lpi_ctl = ret | ((1 << 3) | (1 << 19));
        }
        else
        {
            sysctl_pwr->cpu1_pwr_lpi_ctl = ret | ((0 << 3) | (1 << 19));
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool sysctl_pwr_get_poweroff_keep_reset(sysctl_pwr_domain_e powerdomain, bool *enable)
{
    if(SYSCTL_PD_CPU1 == powerdomain)
    {
        if(sysctl_pwr->cpu1_pwr_lpi_ctl & (1 << 3))
            *enable = true;
        else
            *enable = false;
        return true;
    }
    else
    {
        return false;
    }
}

/*****************************************************************************************
*                                CPU1 AUTO POWERUP OR POWERDOWN
*   powerdomain: power domain
*   enable: poweron, enable power control unit auto control mode; poweroff, disable auto
*****************************************************************************************/

/*
 * In MAIX3, CPU0 and CPU1 power domains support automatic power on and off
 * management.
 */
bool sysctl_pwr_set_auto_pwr(sysctl_pwr_domain_e powerdomain, bool enable)
{
    volatile uint32_t ret;

    if(SYSCTL_PD_CPU1 == powerdomain)
    {
        ret = sysctl_pwr->cpu1_pwr_lpi_ctl;
        ret &= 0xfffbfffb;
        if(true == enable)
        {
            sysctl_pwr->cpu1_pwr_lpi_ctl = ret | ((1 << 2) | (1 << 18));
        }
        else
        {
            sysctl_pwr->cpu1_pwr_lpi_ctl = ret | ((0 << 2) | (1 << 18));
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool sysctl_pwr_get_auto_pwr(sysctl_pwr_domain_e powerdomain, bool *enable)
{
    if(SYSCTL_PD_CPU1 == powerdomain)
    {
        if(sysctl_pwr->cpu1_pwr_lpi_ctl & (1 << 2))
            *enable = true;
        else
            *enable = false;
        return true;
    }
    else
    {
        return false;
    }
}

/*****************************************************************************************
*                                POWER DOMAIN REPAIR
*   powerdomain: power domain
*****************************************************************************************/

/* When powering up, set the power domain to repair */
bool sysctl_pwr_set_repair_enable(sysctl_pwr_domain_e powerdomain)
{
    switch(powerdomain)
    {
        case SYSCTL_PD_AI:
            sysctl_pwr->ai_pwr_lpi_ctl |= (1 << 4) | (1 << 20);
            return true;
        default:
            return false;
    }
}

bool sysctl_pwr_check_repair_done(sysctl_pwr_domain_e powerdomain)
{
    switch(powerdomain)
    {
        case SYSCTL_PD_AI:
            return (sysctl_pwr->repair_status & (1 << 1)) ? true:false;
        case SYSCTL_PD_MAX:
            return (sysctl_pwr->repair_status & (1 << 2)) ? true:false;
        default:
            return false;
    }
}

/*****************************************************************************************
*                                NOC POWER CONTROLLER
*   powerdomain: power domain
*   enable: true, connect noc, exit idle mode; false, disconnect noc, go idle mode.
*****************************************************************************************/

/*
 * Set different power domains to disconnect/connect to NOC and enter/leave
 * idle state.
 */
bool sysctl_pwr_set_lpi(sysctl_pwr_domain_e powerdomain, bool enable)
{
    switch(powerdomain)
    {
        case SYSCTL_PD_CPU1:
        {
            sysctl_pwr->cpu1_pwr_lpi_ctl |= (true == enable) ? ((1 << 5) | (1 << 21)) : ((1 << 4) | (1 << 20));

            /* usleep(500); */
            rt_thread_delay(1);

            if(true == enable)
                return (sysctl_pwr->cpu1_pwr_lpi_state & (1 << 3)) ? true:false;
            else
                return (sysctl_pwr->cpu1_pwr_lpi_state & (1 << 2)) ? true:false;
        }
        case SYSCTL_PD_AI:
        {
            sysctl_pwr->ai_pwr_lpi_ctl |= (true == enable) ? ((1 << 3) | (1 << 19)) : ((1 << 2) | (1 << 18));

            /* usleep(500); */
            rt_thread_delay(1);

            if(true == enable)
                return (sysctl_pwr->ai_pwr_lpi_state & (1 << 3)) ? true:false;
            else
                return (sysctl_pwr->ai_pwr_lpi_state & (1 << 2)) ? true:false;
        }
        case SYSCTL_PD_DISP:
        {
            sysctl_pwr->disp_lpi_ctl |= (true == enable) ? ((1 << 3) | (1 << 19)) : ((1 << 2) | (1 << 18));

            /* usleep(500); */
            rt_thread_delay(1);

            if(true == enable)
                return (sysctl_pwr->disp_lpi_state & (1 << 3)) ? true:false;
            else
                return (sysctl_pwr->disp_lpi_state & (1 << 2)) ? true:false;
        }
        case SYSCTL_PD_VPU:
        {
            sysctl_pwr->vpu_pwr_lpi_ctl |= (true == enable) ? ((1 << 3) | (1 << 19)) : ((1 << 2) | (1 << 18));

            /* usleep(500); */
            rt_thread_delay(1);

            if(true == enable)
                return (sysctl_pwr->vpu_lpi_state & (1 << 3)) ? true:false;
            else
                return (sysctl_pwr->vpu_lpi_state & (1 << 2)) ? true:false;
        }
        case SYSCTL_PD_DPU:
        {
            sysctl_pwr->dpu_pwr_lpi_ctl |= (true == enable) ? ((1 << 3) | (1 << 19)) : ((1 << 2) | (1 << 18));

            /* usleep(500); */
            rt_thread_delay(1);

            if(true == enable)
                return (sysctl_pwr->dpu_pwr_lpi_state & (1 << 3)) ? true:false;
            else
                return (sysctl_pwr->dpu_pwr_lpi_state & (1 << 2)) ? true:false;
        }
        default:
            return false;
    }
}

/*****************************************************************************************
*                                POWER DOMAIN ON OR OFF
*   powerdomain: power domain
*   enable: true for powerup, false for poweroff.
*****************************************************************************************/

bool sysctl_pwr_set_pwr_reg(volatile uint32_t *regctl, volatile uint32_t *regsta, bool enable)
{
    /* enable==true, power on; enable==false, power off */
    uint32_t mask;

    mask = enable ? 0x2 : 0x1;
    if (*regsta & mask)
        return true;

    *regctl = (0x30000 | mask);

    for (int i = 0; i < 100; i++)
    {
        if (*regsta & mask)
            return true;
        for (int j = 0; j < 5000; j++);
    }

    return false;
}

bool sysctl_pwr_set_power(sysctl_pwr_domain_e powerdomain, bool enable)
{
    volatile uint32_t *pwr_ctl_reg = NULL;
    volatile uint32_t *pwr_sta_reg = NULL;

    switch(powerdomain)
    {
        case SYSCTL_PD_CPU1:
        {
            pwr_ctl_reg = (volatile uint32_t *)&sysctl_pwr->cpu1_pwr_lpi_ctl;
            pwr_sta_reg = (volatile uint32_t *)&sysctl_pwr->cpu1_pwr_lpi_state;
            break;
        }
        case SYSCTL_PD_AI:
        {
            pwr_ctl_reg = (volatile uint32_t *)&sysctl_pwr->ai_pwr_lpi_ctl;
            pwr_sta_reg = (volatile uint32_t *)&sysctl_pwr->ai_pwr_lpi_state;
            break;
        }
        case SYSCTL_PD_DISP:
        {
            pwr_ctl_reg = (volatile uint32_t *)&sysctl_pwr->disp_lpi_ctl;
            pwr_sta_reg = (volatile uint32_t *)&sysctl_pwr->disp_lpi_state;
            break;
        }
        case SYSCTL_PD_VPU:
        {
            pwr_ctl_reg = (volatile uint32_t *)&sysctl_pwr->vpu_pwr_lpi_ctl;
            pwr_sta_reg = (volatile uint32_t *)&sysctl_pwr->vpu_lpi_state;
            break;
        }
        case SYSCTL_PD_DPU:
        {
            pwr_ctl_reg = (volatile uint32_t *)&sysctl_pwr->dpu_pwr_lpi_ctl;
            pwr_sta_reg = (volatile uint32_t *)&sysctl_pwr->dpu_pwr_lpi_state;
            break;
        }
        default:
            return false;
    }

    /* repair powerdomain */
    /* only powerup need repair */
    if(true == enable)
    {
        (void)sysctl_pwr_set_repair_enable(powerdomain);
    }

    return sysctl_pwr_set_pwr_reg(pwr_ctl_reg, pwr_sta_reg, enable);
}

bool sysctl_pwr_set_power_multi(sysctl_pwr_domain_e powerdomain, bool enable)
{
    bool ret = true;
    rt_base_t level;
    static uint32_t ref_count[SYSCTL_PD_MAX];
    /*
    1. enable step for non-DISP power domains:
        a. disable interrupt
        b. judge ref_count, if == 0, execute sysctl_pwr_set_pwr_reg
        c. ref_count++, limit UINT32_MAX
        d. enable interrupt
    2. disable step for non-DISP power domains:
        a. disable interrupt
        b. judge ref_count, if == 0, go step d
        c. ref_count--, judge ref_count, if == 0, execute sysctl_pwr_set_pwr_reg
        d. enable interrupt
    3. enable step for DISP power domains:
        a. disable interrupt
        b. judge ref_count, if == 0, execute
            b.1 get HARDLOCK_DISP
            b.2 get HARDLOCK_DISP_CPU1
            b.3 execute sysctl_pwr_set_pwr_reg
            b.4 put HARDLOCK_DISP
        c. ref_count++, limit UINT32_MAX
        d. enable interrupt
    4. disable step for DISP power domains:
        a. disable interrupt
        b. judge ref_count, if == 0, go step e
        c. ref_count--, judge ref_count, if == 0, execute
            c.1 get HARDLOCK_DISP
            c.2 qeury HARDLOCK_DISP_CPU0, if no get, go step c.4
            c.3 put HARDLOCK_DISP_CPU0, execute sysctl_pwr_set_pwr_reg
            c.4 put HARDLOCK_DISP_CPU1
            c.5 put HARDLOCK_DISP
        d. enable interrupt
    */
    level = rt_hw_interrupt_disable();
    if (enable == true)
    {
        if (ref_count[powerdomain] == 0)
        {
            if (powerdomain == SYSCTL_PD_DISP)
            {
                while (kd_hardlock_lock(HARDLOCK_DISP));
                kd_hardlock_lock(HARDLOCK_DISP_CPU1);
                ret = sysctl_pwr_set_power(powerdomain, enable);
                kd_hardlock_unlock(HARDLOCK_DISP);
            } else {
                ret = sysctl_pwr_set_power(powerdomain, enable);
            }
        }
        ref_count[powerdomain]++;
        if (ref_count[powerdomain] == UINT32_MAX)
            rt_kprintf("error: enable too many times\n");
    } else if (ref_count[powerdomain])
    {
        ref_count[powerdomain]--;
        if (ref_count[powerdomain] == 0)
        {
            if (powerdomain == SYSCTL_PD_DISP)
            {
                while (kd_hardlock_lock(HARDLOCK_DISP));
                if (kd_hardlock_lock(HARDLOCK_DISP_CPU0) == 0)
                {
                    kd_hardlock_unlock(HARDLOCK_DISP_CPU0);
                    ret = sysctl_pwr_set_power(powerdomain, enable);
                }
                kd_hardlock_unlock(HARDLOCK_DISP_CPU1);
                kd_hardlock_unlock(HARDLOCK_DISP);
            } else {
                ret = sysctl_pwr_set_power(powerdomain, enable);
            }
        }
    }
    rt_hw_interrupt_enable(level);

    return ret;
}

/* Power Domain Power-up */
bool sysctl_pwr_up(sysctl_pwr_domain_e powerdomain)
{
    return sysctl_pwr_set_power_multi(powerdomain, true);
}

/* Power off a power domain */
bool sysctl_pwr_off(sysctl_pwr_domain_e powerdomain)
{
    return sysctl_pwr_set_power_multi(powerdomain, false);
}

int rt_hw_sysctl_pwr_init(void)
{
    sysctl_pwr = rt_ioremap((void*)PWR_BASE_ADDR, PWR_IO_SIZE);
    if(!sysctl_pwr)
    {
        rt_kprintf("sysctl_pwr ioremap error\n");
        return -1;
    }

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_sysctl_pwr_init);