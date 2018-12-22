/*
 * File      : drv_reset.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016Äê7ÔÂ29ÈÕ     Urey         the first version
 */


#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <finsh.h>

#include "board.h"
#include "drv_clock.h"
#include "drv_ost.h"
#include "drv_pmu.h"
#include "drv_rtc.h"

static void udelay(uint32_t x)
{
    volatile uint32_t   n = 1000;

    while(x--)
    {
        for (n = 0; n < 1000; ++n);
    }
}

static void mdelay(uint32_t x)
{
    while(x--)
        udelay(1000);
}

#define RECOVERY_SIGNATURE  (0x001a1a)
#define REBOOT_SIGNATURE    (0x003535)
#define UNMSAK_SIGNATURE    (0x7c0000)//do not use these bits


void wdt_start_count(int msecs)
{
    int time = BOARD_RTC_CLK / 64 * msecs / 1000;
    if(time > 65535)
        time = 65535;

    writel(1 << 16,TCU_BASE + TCU_TSCR);

    writel(0,WDT_BASE + WDT_TCNT);      //counter
    writel(time,WDT_BASE + WDT_TDR);    //data
    writel((3<<3 | 1<<1),WDT_BASE + WDT_TCSR);
    writel(0,WDT_BASE + WDT_TCER);
    writel(1,WDT_BASE + WDT_TCER);
}


void wdt_stop_count(void)
{
    writel(1 << 16,TCU_BASE + TCU_TSCR);
    writel(0,WDT_BASE + WDT_TCNT);      //counter
    writel(65535,WDT_BASE + WDT_TDR);       //data
    writel(1 << 16,TCU_BASE + TCU_TSSR);
}

void wdt_clear(void)
{
    writel(0,WDT_BASE + WDT_TCNT);
}


/*
 * Function: Keep power for CPU core when reset.
 * So that EPC, tcsm and so on can maintain it's status after reset-key pressed.
 */
static int inline reset_keep_power(void)
{
    rtc_write_reg(RTC_BASE + RTC_PWRONCR, rtc_read_reg(RTC_BASE + RTC_PWRONCR) & ~(1 << 0));

    return 0;
}


void x1000_hibernate(void)
{
    uint32_t rtc_rtccr;
    rt_base_t level;

    wdt_stop_count();
    level = rt_hw_interrupt_disable();

    /* Set minimum wakeup_n pin low-level assertion time for wakeup: 1000ms */
    rtc_write_reg(RTC_BASE + RTC_HWFCR, HWFCR_WAIT_TIME(1000));

    /* Set reset pin low-level assertion time after wakeup: must  > 60ms */
    rtc_write_reg(RTC_BASE + RTC_HRCR, HRCR_WAIT_TIME(125));

    /* clear wakeup status register */
    rtc_write_reg(RTC_BASE + RTC_HWRSR, 0x0);

    rtc_write_reg(RTC_BASE + RTC_HWCR, 0x8);

    /* Put CPU to hibernate mode */
    rtc_write_reg(RTC_BASE + RTC_HCR, 0x1);

    /*poweroff the pmu*/
//  jz_notifier_call(NOTEFY_PROI_HIGH, JZ_POST_HIBERNATION, NULL);

    rtc_rtccr = rtc_read_reg(RTC_BASE + RTC_RTCCR);
    rtc_rtccr |= 0x1 << 0;
    rtc_write_reg(RTC_BASE + RTC_RTCCR,rtc_rtccr);

    mdelay(200);

    while(1)
    {
        rt_kprintf("%s:We should NOT come here.%08x\n",__func__, rtc_read_reg(RTC_BASE + RTC_HCR));
    }
}

void x1000_wdt_restart(char *command)
{
    rt_kprintf("Restarting after 4 ms\n");

    if ((command != NULL) && !strcmp(command, "recovery"))
    {
        while (cpm_inl(CPM_CPPSR) != RECOVERY_SIGNATURE)
        {
            rt_kprintf("set RECOVERY_SIGNATURE\n");
            cpm_outl(0x5a5a, CPM_CPSPPR);
            cpm_outl(RECOVERY_SIGNATURE, CPM_CPPSR);
            cpm_outl(0x0, CPM_CPSPPR);
            udelay(100);
        }
    }
    else
    {
        //WDT...
        cpm_outl(0x5a5a, CPM_CPSPPR);
        cpm_outl(REBOOT_SIGNATURE, CPM_CPPSR);
        cpm_outl(0x0, CPM_CPSPPR);
    }

    wdt_start_count(4);
    mdelay(200);
    while(1)
        rt_kprintf("check wdt.\n");
}

void x1000_hibernate_restart(char *command)
{
    rt_base_t level;
    uint32_t rtc_rtcsr,rtc_rtccr;

    level = rt_hw_interrupt_disable();

    if ((command != NULL) && !strcmp(command, "recovery"))
    {
        x1000_wdt_restart(command);
    }

    /*  hibernate_restart */
    while(!(rtc_read_reg(RTC_BASE + RTC_RTCCR) & RTCCR_WRDY));

    rtc_rtcsr = rtc_read_reg(RTC_BASE + RTC_RTCSR);
    rtc_rtccr = rtc_read_reg(RTC_BASE + RTC_RTCCR);

    rtc_write_reg(RTC_RTCSAR,rtc_rtcsr + 5);
    rtc_rtccr &= ~(1 << 4 | 1 << 1);
    rtc_rtccr |= 0x3 << 2;
    rtc_write_reg(RTC_BASE + RTC_RTCCR,rtc_rtccr);

    /* Clear reset status */
    cpm_outl(0,CPM_RSR);

    /* Set minimum wakeup_n pin low-level assertion time for wakeup: 1000ms */
    rtc_write_reg(RTC_BASE + RTC_HWFCR, HWFCR_WAIT_TIME(1000));

    /* Set reset pin low-level assertion time after wakeup: must  > 60ms */
    rtc_write_reg(RTC_BASE + RTC_HRCR, HRCR_WAIT_TIME(125));

    /* clear wakeup status register */
    rtc_write_reg(RTC_BASE + RTC_HWRSR, 0x0);

    rtc_write_reg(RTC_BASE + RTC_HWCR, 0x9);
    /* Put CPU to hibernate mode */
    rtc_write_reg(RTC_BASE + RTC_HCR, 0x1);

    rtc_rtccr = rtc_read_reg(RTC_BASE + RTC_RTCCR);
    rtc_rtccr |= 0x1 << 0;
    rtc_write_reg(RTC_BASE + RTC_RTCCR,rtc_rtccr);

    mdelay(200);
    while(1)
        rt_kprintf("%s:We should NOT come here.%08x\n",__func__, rtc_read_reg(RTC_BASE + RTC_HCR));
}

uint32_t x1000_get_last_reset(void)
{
    return (cpm_inl(CPM_RSR) & 0x0000000F);
}

/* ============================wdt control proc end =============================== */
/* ============================reset proc=================================== */
const char *reset_command[] = {"wdt","hibernate","recovery"};
#define ARRAY_SIZE(arr)     (sizeof(arr) / sizeof((arr)[0]))

int x1000_reset(const char *reset_cmd)
{
    rt_base_t level;
    int command_size = 0;
    int i;

    command_size = ARRAY_SIZE(reset_command);
    for (i = 0; i < command_size; i++)
    {
        if (!strncmp(reset_cmd, reset_command[i], strlen(reset_command[i])))
            break;
    }

    if(i == command_size)
        return -RT_ERROR;

    level = rt_hw_interrupt_disable();
    switch(i)
    {
    case 0:
        x1000_wdt_restart("wdt");
        break;
    case 1:
        x1000_hibernate_restart("hibernate");
        break;
    case 2:
        x1000_wdt_restart("recovery");
        break;
    default:
        rt_kprintf("not support command %d\n", i);
    }

    rt_hw_interrupt_enable(level);
    return RT_EOK;
}


struct wdt_reset
{
    int msecs;
};


static struct wdt_reset _wdt_param =
{
    .msecs = 1000,
};

rt_err_t _wdt_init(rt_watchdog_t *wdt)
{
    return RT_EOK;
}

rt_err_t _wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    switch (cmd)
    {
        case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        {
            int msecs = *(int *)arg * 1000;

            if(msecs < 1000) msecs = 1000;
            if(msecs > 30000) msecs = 30000;

            _wdt_param.msecs = msecs;

            rt_kprintf("WDT timeout = %d\n",msecs);
        }
            break;
        case RT_DEVICE_CTRL_WDT_START:
            wdt_start_count(_wdt_param.msecs + 1000);
            break;
        case RT_DEVICE_CTRL_WDT_STOP:
            wdt_stop_count();
            break;
        case RT_DEVICE_CTRL_WDT_KEEPALIVE:
            wdt_clear();
            break;
        default:
            break;
    }
    return RT_EOK;
}

const struct rt_watchdog_ops _wdt_ops =
{
    .init       = _wdt_init,
    .control    = _wdt_control
};

static struct rt_watchdog_device _wdt_device =
{
    .ops        = (struct rt_watchdog_ops *)&_wdt_ops,
};

int reboot(void)
{
    rt_hw_cpu_reset();

    return 0;
}
MSH_CMD_EXPORT(reboot,reboot system...);

int shutdown(void)
{
    rt_hw_cpu_shutdown();
}
MSH_CMD_EXPORT(shutdown,shutdown system...);

int rt_hw_wdt_init(void)
{
    rt_hw_watchdog_register(&_wdt_device,"WDT",RT_DEVICE_FLAG_STANDALONE,&_wdt_param);

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_wdt_init);

void rt_hw_cpu_reset()
{
    /* Disable Base_board */
    drv_pmu_power_down();

    x1000_reset("wdt");
}

void rt_hw_cpu_shutdown()
{
    /* Disable Base_board */
    drv_pmu_power_down();

    x1000_hibernate();
}
