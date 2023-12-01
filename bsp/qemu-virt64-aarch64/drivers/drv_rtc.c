/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2021-11-4      GuEe-GUI       first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>
#include <board.h>

#include "drv_rtc.h"

#ifdef BSP_USING_RTC

#define RTC_DR      0x00    /* data read register */
#define RTC_MR      0x04    /* match register */
#define RTC_LR      0x08    /* data load register */
#define RTC_CR      0x0c    /* control register */
#define RTC_IMSC    0x10    /* interrupt mask and set register */
#define RTC_RIS     0x14    /* raw interrupt status register */
#define RTC_MIS     0x18    /* masked interrupt status register */
#define RTC_ICR     0x1c    /* interrupt clear register */

#define RTC_CR_OPEN     1
#define RTC_CR_CLOSE    0

static struct hw_rtc_device rtc_device;
static rt_ubase_t pl031_rtc_base = PL031_RTC_BASE;

rt_inline rt_uint32_t pl031_read32(rt_ubase_t offset)
{
    return (*((volatile unsigned int *)(pl031_rtc_base + offset)));
}

rt_inline void pl031_write32(rt_ubase_t offset, rt_uint32_t value)
{
    (*((volatile unsigned int *)(pl031_rtc_base + offset))) = value;
}

static rt_err_t pl031_rtc_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t pl031_rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
    pl031_write32(RTC_CR, RTC_CR_OPEN);
    return RT_EOK;
}

static rt_err_t pl031_rtc_close(rt_device_t dev)
{
    pl031_write32(RTC_CR, RTC_CR_CLOSE);
    return RT_EOK;
}

static rt_err_t pl031_rtc_control(rt_device_t dev, int cmd, void *args)
{

    RT_ASSERT(dev != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        *(rt_uint32_t *)args = pl031_read32(RTC_DR);
        break;
    case RT_DEVICE_CTRL_RTC_SET_TIME:
        pl031_write32(RTC_LR, *(time_t *)args);
        break;
    default:
        return -RT_EINVAL;
    }
    return RT_EOK;
}

static rt_ssize_t pl031_rtc_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    pl031_rtc_control(dev, RT_DEVICE_CTRL_RTC_GET_TIME, buffer);
    return size;
}

static rt_ssize_t pl031_rtc_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    pl031_rtc_control(dev, RT_DEVICE_CTRL_RTC_SET_TIME, (void *)buffer);
    return size;
}

const static struct rt_device_ops pl031_rtc_ops =
{
    .init = pl031_rtc_init,
    .open = pl031_rtc_open,
    .close = pl031_rtc_close,
    .read = pl031_rtc_read,
    .write = pl031_rtc_write,
    .control = pl031_rtc_control
};

int rt_hw_rtc_init(void)
{
    pl031_rtc_base = (rt_size_t)rt_ioremap((void *)pl031_rtc_base, PL031_RTC_SIZE);

    rt_memset(&rtc_device, 0, sizeof(rtc_device));

    rtc_device.device.type        = RT_Device_Class_RTC;
    rtc_device.device.rx_indicate = RT_NULL;
    rtc_device.device.tx_complete = RT_NULL;
    rtc_device.device.ops         = &pl031_rtc_ops;
    rtc_device.device.user_data   = RT_NULL;

    /* register a rtc device */
    rt_device_register(&rtc_device.device, "rtc0", RT_DEVICE_FLAG_RDWR);
    rt_soft_rtc_set_source("rtc0");
    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);
#endif /* BSP_USING_RTC */
