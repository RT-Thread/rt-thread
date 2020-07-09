/*
 * File      : drv_rtc.c
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
 * 2016/7/28      Urey         the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "board.h"
#include "drv_clock.h"
#include "drv_gpio.h"
#include "drv_ost.h"
#include "drv_rtc.h"

static rt_base_t rtc32k_ref = 0;

void rtc32k_enable(void)
{
    if(++rtc32k_ref == 1)
        gpio_set_func(GPIO_PORT_B,GPIO_Pin_26,GPIO_FUNC_0);
}


void rtc32k_disable(void)
{
    if(--rtc32k_ref == 0)
        gpio_set_func(GPIO_PORT_B,GPIO_Pin_26,GPIO_INPUT);
}

#if 0 /* not enable */
static void jz_rtc_interrupt(int vector,void *param)
{
    if (rtc_read_reg(RTC_RTCCR) & RTC_RTCCR_AF)     /* rtc alarm interrupt */
    {
        rtc_clr_reg(RTC_RTCCR, RTC_RTCCR_AF);

#ifdef AHB_MONITOR_PERIOD
        // Stop and log the data, and the 1st of the data is INVALID.
        MONITOR_LOG();
        // Start the monitor.
        MONITOR_START(MASTER_IPU, MEVENT_BUS_TRANS_CYCLE, MASTER_ALL, MEVENT_BUS_TRANS_CYCLE);

        // Config the RTC alarm for the next time
        rtc_write_reg(RTC_RTCSAR, rtc_read_reg(RTC_RTCSR) + AHB_MONITOR_PERIOD);
#else
        printf("RTC alarm interrupt clean!\n");
        rtc_alarm_handler();
#endif
    }
    else
    {
        rtc_clr_reg(RTC_RTCCR, RTC_RTCCR_1HZ);
    }
}
#endif

void jz_rtc_init(void)
{
    unsigned int tmpx , flag;

    tmpx = rtc_read_reg(RTC_BASE + RTC_HSPR);
    flag = rtc_read_reg(RTC_BASE + RTC_RTCGR) & RTC_RTCGR_NC1HZ_MASK;
    if((tmpx != COLD_BOOT_SIG) || (flag != RTCGR_DIV_1HZ))
    {
        rt_kprintf("rtc is not configured\n");
        rt_kprintf("please configure with set_date and set_time\n");

        rtc_write_reg(RTC_BASE + RTC_RTCGR, RTCGR_DIV_1HZ);
        rtc_write_reg(RTC_BASE + RTC_HSPR, COLD_BOOT_SIG);
        rtc_write_reg(RTC_BASE + RTC_RTCSR, 0x00000000);
        rtc_write_reg(RTC_BASE + RTC_RTCSR, 0);
        rtc_set_reg(RTC_BASE + RTC_RTCCR, RTC_RTCCR_RTCE);
    }
    else
    {
        rt_kprintf("skip init rtc...\n");
    }
}

void jz_rtc_deinit(void)
{
    rtc_clr_reg(RTC_BASE + RTC_RTCCR, RTC_RTCCR_RTCE);
}

static rt_err_t rt_rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
    if (dev->rx_indicate != RT_NULL)
    {
        /* Open Interrupt */
    }

    return RT_EOK;
}

static rt_size_t rt_rtc_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    return 0;
}

static rt_err_t rt_rtc_control(rt_device_t dev, int cmd, void *args)
{
    time_t *time;
    RT_ASSERT(dev != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
    {
        const struct tm* tm_now;
        struct tm tm_new;
        time_t timeNow;
        time = (time_t *)args;

        /* Get the current Time */
        timeNow = rtc_read_reg(RTC_BASE + RTC_RTCSR);
        tm_now = localtime(&timeNow);

        /* 0-99 range              : Years since 1900 */
        rt_memcpy(&tm_new,tm_now,sizeof(struct tm));
        tm_new.tm_year = tm_now->tm_year + 2000 - 1900;

        *time = mktime(&tm_new);
    }
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
    {
        const struct tm* tm_now;
        struct tm tm_new;
        time_t  timeNow;

        time = (time_t *)args;
        tm_now = localtime(time);

        rt_memcpy(&tm_new,tm_now,sizeof(struct tm));

        /* 0-99 range              : Years since 1900 */
        tm_new.tm_year = tm_now->tm_year + 1900 - 2000;

        timeNow = mktime(&tm_new);

         /* upgrade the current Time */
        rtc_write_reg(RTC_BASE + RTC_RTCSR,timeNow);
    }
    break;
    }

    return RT_EOK;
}


int rt_hw_rtc_init(void)
{
    static struct rt_device rtc;

    jz_rtc_init();

    rtc.type    = RT_Device_Class_RTC;
    /* register rtc device */
    rtc.init    = RT_NULL;
    rtc.open    = rt_rtc_open;
    rtc.close   = RT_NULL;
    rtc.read    = rt_rtc_read;
    rtc.write   = RT_NULL;
    rtc.control = rt_rtc_control;

    /* no private */
    rtc.user_data = RT_NULL;

    rt_device_register(&rtc, "rtc", RT_DEVICE_FLAG_RDWR);
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);
