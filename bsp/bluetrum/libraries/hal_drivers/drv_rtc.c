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
#include <time.h>
#include <sys/time.h>

#ifdef BSP_USING_ONCHIP_RTC

//#define DRV_DEBUG
#define LOG_TAG             "drv.rtc"
#include <drv_log.h>

static struct rt_device rtc;

/************** HAL Start *******************/
#define IRTC_ENTER_CRITICAL()       uint32_t cpu_ie = PICCON & BIT(0); PICCONCLR = BIT(0);
#define IRTC_EXIT_CRITICAL()       PICCON |= cpu_ie

uint8_t get_weekday(struct tm *const _tm)
{
    uint8_t weekday;
    time_t secs = timegm(_tm);

    weekday = (secs / 86400 + 4) % 7;
    return weekday;
}

void irtc_write(uint32_t cmd)
{
    RTCDAT = cmd;
    while (RTCCON & RTC_CON_TRANS_DONE);
}

uint8_t irtc_read(void)
{
    RTCDAT = 0x00;
    while (RTCCON & RTC_CON_TRANS_DONE);
    return (uint8_t)RTCDAT;
}

void irtc_time_write(uint32_t cmd, uint32_t dat)
{
    IRTC_ENTER_CRITICAL();
    RTCCON |= RTC_CON_CHIP_SELECT;
    irtc_write(cmd | RTC_WR);
    irtc_write((uint8_t)(dat >> 24));
    irtc_write((uint8_t)(dat >> 16));
    irtc_write((uint8_t)(dat >>  8));
    irtc_write((uint8_t)(dat >>  0));
    RTCCON &= ~RTC_CON_CHIP_SELECT;
    IRTC_EXIT_CRITICAL();
}

uint32_t irtc_time_read(uint32_t cmd)
{
    uint32_t rd_val;
    IRTC_ENTER_CRITICAL();
    RTCCON |= RTC_CON_CHIP_SELECT;
    irtc_write(cmd | RTC_RD);
    *((uint8_t *)&rd_val + 3) = irtc_read();
    *((uint8_t *)&rd_val + 2) = irtc_read();
    *((uint8_t *)&rd_val + 1) = irtc_read();
    *((uint8_t *)&rd_val + 0) = irtc_read();
    RTCCON &= ~RTC_CON_CHIP_SELECT;
    IRTC_EXIT_CRITICAL();
    return rd_val;
}

void irtc_sfr_write(uint32_t cmd, uint8_t dat)
{
    IRTC_ENTER_CRITICAL();
    RTCCON |= RTC_CON_CHIP_SELECT;
    irtc_write(cmd | RTC_WR);
    irtc_write(dat);
    RTCCON &= ~RTC_CON_CHIP_SELECT;
    IRTC_EXIT_CRITICAL();
}

uint8_t irtc_sfr_read(uint32_t cmd)
{
    uint8_t rd_val;
    IRTC_ENTER_CRITICAL();
    RTCCON |= RTC_CON_CHIP_SELECT;
    irtc_write(cmd | RTC_RD);
    rd_val = irtc_read();
    RTCCON &= ~RTC_CON_CHIP_SELECT;
    IRTC_EXIT_CRITICAL();
}

static void _init_rtc_clock(void)
{
    uint8_t rtccon0;
    uint8_t rtccon2;

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
    uint8_t temp;

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

static time_t get_rtc_time_stamp(void)
{
    time_t sec = 0;

    sec = irtc_time_read(RTCCNT_CMD);
    LOG_D("get rtc time.");

    return sec;
}

static rt_err_t set_rtc_time_stamp(time_t time_stamp)
{
    irtc_time_write(RTCCNT_CMD, time_stamp);

    return RT_EOK;
}

static rt_err_t set_rtc_alarm_stamp(time_t alarm_stamp)
{
    irtc_time_write(RTCALM_CMD, alarm_stamp);

    return RT_EOK;
}

static time_t get_rtc_alarm_stamp(void)
{
    time_t sec = 0;

    sec = irtc_time_read(RTCALM_CMD);

    return sec;
}

static void rt_rtc_init(void)
{
    hal_rtc_init();
}

static rt_err_t ab32_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t result = RT_EOK;
    RT_ASSERT(dev != RT_NULL);
    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        *(rt_uint32_t *)args = get_rtc_time_stamp();
        LOG_D("RTC: get rtc_time %x", *(rt_uint32_t *)args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        if (set_rtc_time_stamp(*(rt_uint32_t *)args))
        {
            result = -RT_ERROR;
        }
        LOG_D("RTC: set rtc_time %x", *(rt_uint32_t *)args);
        break;
    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        if (set_rtc_alarm_stamp(*(rt_uint32_t *)args))
        {
            result = -RT_ERROR;
        }
        LOG_D("RTC: set alarm_stamp %x", *(rt_uint32_t *)args);
        break;
    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        *(rt_uint32_t *)args = get_rtc_alarm_stamp();
        LOG_D("RTC: get alarm_stamp %x", *(rt_uint32_t *)args);
        break;
    }

    return result;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rtc_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    ab32_rtc_control
};
#endif

static rt_err_t rt_hw_rtc_register(rt_device_t device, const char *name, rt_uint32_t flag)
{
    RT_ASSERT(device != RT_NULL);

    rt_rtc_init();
#ifdef RT_USING_DEVICE_OPS
    device->ops         = &rtc_ops;
#else
    device->init        = RT_NULL;
    device->open        = RT_NULL;
    device->close       = RT_NULL;
    device->read        = RT_NULL;
    device->write       = RT_NULL;
    device->control     = ab32_rtc_control;
#endif
    device->type        = RT_Device_Class_RTC;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->user_data   = RT_NULL;

    /* register a character device */
    return rt_device_register(device, name, flag);
}

#ifdef RT_USING_ALARM
RT_SECTION(".irq.rtc")
static void rtc_isr(int vector, void *param)
{
    rt_interrupt_enter();

    if (RTCCON & RTC_CON_ALM_PEND)
    {
        RTCCPND |= RTC_CPND_ALM;
    }

#ifdef RTC_USING_1S_INT
    if (RTCCON & RTC_CON_1S_PEND)
    {
        RTCCPND |= RTC_CPND_1S;
    }
#endif

    rt_interrupt_leave();
}
#endif

int rt_hw_rtc_init(void)
{
    rt_err_t result;

    result = rt_hw_rtc_register(&rtc, "rtc", RT_DEVICE_FLAG_RDWR);
    if (result != RT_EOK)
    {
        LOG_E("rtc register err code: %d", result);
        return result;
    }

#ifdef RT_USING_ALARM
    rt_hw_interrupt_install(IRQ_RTC_VECTOR, rtc_isr, RT_NULL, "rtc_isr");
#endif
    LOG_D("rtc init success");
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /* BSP_USING_ONCHIP_RTC */
