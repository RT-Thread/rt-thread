/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-01-28     greedyhao         first version
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

void hal_rtc_init(void)
{
    time_t sec = 0;
    struct tm tm_new = {0};

    uint8_t temp = irtc_sfr_read(RTCCON0_CMD);
    temp &= ~RTC_CON0_XOSC32K_ENABLE;
    temp |= RTC_CON0_EXTERNAL_32K;
    irtc_sfr_write(RTCCON0_CMD, temp);
    temp = irtc_sfr_read(RTCCON2_CMD);
    irtc_sfr_write(RTCCON2_CMD, temp | RTC_CON2_32K_SELECT);

    temp = irtc_sfr_read(RTCCON0_CMD);
    if (temp & BIT(7)) {
        temp &= ~BIT(7);
        irtc_sfr_write(RTCCON0_CMD, temp); /* First power on */
    }

    tm_new.tm_mday = 29;
    tm_new.tm_mon  = 1 - 1;
    tm_new.tm_year = 2021 - 1900;
    sec = timegm(&tm_new);

    irtc_time_write(RTCCNT_CMD, sec);
}
/************** HAL End *******************/

static time_t get_rtc_timestamp(void)
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

static void rt_rtc_init(void)
{
    hal_rtc_init();
}

static rt_err_t rt_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t result = RT_EOK;
    RT_ASSERT(dev != RT_NULL);
    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        *(rt_uint32_t *)args = get_rtc_timestamp();
        LOG_D("RTC: get rtc_time %x\n", *(rt_uint32_t *)args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        if (set_rtc_time_stamp(*(rt_uint32_t *)args))
        {
            result = -RT_ERROR;
        }
        LOG_D("RTC: set rtc_time %x\n", *(rt_uint32_t *)args);
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
    rt_rtc_control
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
    device->control     = rt_rtc_control;
#endif
    device->type        = RT_Device_Class_RTC;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->user_data   = RT_NULL;

    /* register a character device */
    return rt_device_register(device, name, flag);
}

int rt_hw_rtc_init(void)
{
    rt_err_t result;
    result = rt_hw_rtc_register(&rtc, "rtc", RT_DEVICE_FLAG_RDWR);
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
