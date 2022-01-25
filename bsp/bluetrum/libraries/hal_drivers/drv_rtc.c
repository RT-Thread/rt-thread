/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-01-28     greedyhao         first version
 * 2021-03-19     iysheng           modify just set time first power up
 * 2021-03-26     iysheng           add alarm and 1s interrupt support
 */

#include "board.h"
#include <sys/time.h>

#ifdef BSP_USING_ONCHIP_RTC

#if RTTHREAD_VERSION < 40004
#error "RTTHREAD_VERSION is less than 4.0.4"
#endif

//#define DRV_DEBUG
#define LOG_TAG             "drv.rtc"
#include <drv_log.h>

static struct rt_device rtc;

/************** HAL Start *******************/
#define IRTC_ENTER_CRITICAL()       uint32_t cpu_ie = PICCON & BIT(0); PICCONCLR = BIT(0);
#define IRTC_EXIT_CRITICAL()        PICCON |= cpu_ie

rt_uint8_t get_weekday(struct tm *const _tm)
{
    rt_uint8_t weekday;
    time_t secs = timegm(_tm);

    weekday = (secs / 86400 + 4) % 7;
    return weekday;
}

void irtc_write(rt_uint32_t cmd)
{
    RTCDAT = cmd;
    while (RTCCON & RTC_CON_TRANS_DONE);
}

rt_uint8_t irtc_read(void)
{
    RTCDAT = 0x00;
    while (RTCCON & RTC_CON_TRANS_DONE);
    return (rt_uint8_t)RTCDAT;
}

void irtc_time_write(rt_uint32_t cmd, rt_uint32_t dat)
{
    IRTC_ENTER_CRITICAL();
    RTCCON |= RTC_CON_CHIP_SELECT;
    irtc_write(cmd | RTC_WR);
    irtc_write((rt_uint8_t)(dat >> 24));
    irtc_write((rt_uint8_t)(dat >> 16));
    irtc_write((rt_uint8_t)(dat >>  8));
    irtc_write((rt_uint8_t)(dat >>  0));
    RTCCON &= ~RTC_CON_CHIP_SELECT;
    IRTC_EXIT_CRITICAL();
}

rt_uint32_t irtc_time_read(rt_uint32_t cmd)
{
    rt_uint32_t rd_val;
    IRTC_ENTER_CRITICAL();
    RTCCON |= RTC_CON_CHIP_SELECT;
    irtc_write(cmd | RTC_RD);
    *((rt_uint8_t *)&rd_val + 3) = irtc_read();
    *((rt_uint8_t *)&rd_val + 2) = irtc_read();
    *((rt_uint8_t *)&rd_val + 1) = irtc_read();
    *((rt_uint8_t *)&rd_val + 0) = irtc_read();
    RTCCON &= ~RTC_CON_CHIP_SELECT;
    IRTC_EXIT_CRITICAL();
    return rd_val;
}

void irtc_sfr_write(rt_uint32_t cmd, rt_uint8_t dat)
{
    IRTC_ENTER_CRITICAL();
    RTCCON |= RTC_CON_CHIP_SELECT;
    irtc_write(cmd | RTC_WR);
    irtc_write(dat);
    RTCCON &= ~RTC_CON_CHIP_SELECT;
    IRTC_EXIT_CRITICAL();
}

rt_uint8_t irtc_sfr_read(rt_uint32_t cmd)
{
    rt_uint8_t rd_val;
    IRTC_ENTER_CRITICAL();
    RTCCON |= RTC_CON_CHIP_SELECT;
    irtc_write(cmd | RTC_RD);
    rd_val = irtc_read();
    RTCCON &= ~RTC_CON_CHIP_SELECT;
    IRTC_EXIT_CRITICAL();
}

static void _init_rtc_clock(void)
{
    rt_uint8_t rtccon0;
    rt_uint8_t rtccon2;

    rtccon0 = irtc_sfr_read(RTCCON0_CMD);
    rtccon2 = irtc_sfr_read(RTCCON2_CMD);
#ifdef RTC_USING_INTERNAL_CLK
    rtccon0 &= ~RTC_CON0_XOSC32K_ENABLE;
    rtccon0 |= RTC_CON0_INTERNAL_32K;
    rtccon2 | RTC_CON2_32K_SELECT;
#else
    rtccon0 |= RTC_CON0_XOSC32K_ENABLE;
    rtccon0 &= ~RTC_CON0_INTERNAL_32K;
    rtccon2 & ~RTC_CON2_32K_SELECT;
#endif
    irtc_sfr_write(RTCCON0_CMD, rtccon0);
    irtc_sfr_write(RTCCON2_CMD, rtccon2);
}

void hal_rtc_init(void)
{
    time_t sec = 0;
    struct tm tm_new = {0};
    rt_uint8_t temp;

    _init_rtc_clock();
    temp = irtc_sfr_read(RTCCON0_CMD);
    if (temp & RTC_CON0_PWRUP_FIRST) {
        temp &= ~RTC_CON0_PWRUP_FIRST;
        irtc_sfr_write(RTCCON0_CMD, temp); /* First power on */
        tm_new.tm_mday = 29;
        tm_new.tm_mon  = 1 - 1;
        tm_new.tm_year = 2021 - 1900;
        sec = timegm(&tm_new);

        irtc_time_write(RTCCNT_CMD, sec);
    }
#ifdef RT_USING_ALARM
    RTCCON |= RTC_CON_ALM_INTERRUPT;
#ifdef RTC_USING_1S_INT
    RTCCON |= RTC_CON_1S_INTERRUPT;
#endif
#endif
}
/************** HAL End *******************/

static rt_err_t ab32_rtc_get_secs(void *args)
{
    *(rt_uint32_t *)args = irtc_time_read(RTCCNT_CMD);
    LOG_D("RTC: get rtc_time %x\n", *(rt_uint32_t *)args);

    return RT_EOK;
}

static rt_err_t ab32_rtc_set_secs(void *args)
{
    irtc_time_write(RTCCNT_CMD, *(rt_uint32_t *)args);

    return RT_EOK;
}

static rt_err_t ab32_rtc_get_alarm(void *args)
{
    *(rt_uint32_t *)args = irtc_time_read(RTCALM_CMD);

    return RT_EOK;
}

static rt_err_t ab32_rtc_set_alarm(void *args)
{
    irtc_time_write(RTCALM_CMD, *(rt_uint32_t *)args);

    return RT_EOK;
}

static rt_err_t ab32_rtc_init(void)
{
    hal_rtc_init();

    return RT_EOK;
}

static const struct rt_rtc_ops ab32_rtc_ops =
{
    ab32_rtc_init,
    ab32_rtc_get_secs,
    ab32_rtc_set_secs,
    ab32_rtc_get_alarm,
    ab32_rtc_set_alarm,
    RT_NULL,
    RT_NULL,
};

static rt_rtc_dev_t ab32_rtc_dev;

static int rt_hw_rtc_init(void)
{
    rt_err_t result;

    ab32_rtc_dev.ops = &ab32_rtc_ops;
    result = rt_hw_rtc_register(&ab32_rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("rtc register err code: %d", result);
        return result;
    }
    LOG_D("rtc init success");

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /* BSP_USING_ONCHIP_RTC */
