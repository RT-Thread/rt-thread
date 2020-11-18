/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */


#include "drv_rtc.h"

#ifdef BSP_USING_RTC

static struct rt_rtc_device rtc_device;

rt_uint8_t buf[]=
{
    0x00, 0x00, 0x43, 0x15, 0x05, 0x01, 0x03, 0x19
};

static time_t raspi_get_timestamp(void)
{
    struct tm tm_new = {0};
    buf[0] = 0;
    bcm283x_i2c_write_read_rs((char*)buf, 1, (char*)buf, 7);

    tm_new.tm_year = ((buf[6] / 16) + 0x30) * 10 + (buf[6] % 16) + 0x30;
    tm_new.tm_mon  = ((buf[5] & 0x1F) / 16 + 0x30) + (buf[5] & 0x1F) % 16+ 0x30;
    tm_new.tm_mday = ((buf[4] & 0x3F) / 16 + 0x30) + (buf[4] & 0x3F) % 16+ 0x30;
    tm_new.tm_hour = ((buf[2] & 0x3F) / 16 + 0x30) + (buf[2] & 0x3F) % 16+ 0x30;
    tm_new.tm_min  = ((buf[1] & 0x7F) / 16 + 0x30) + (buf[1] & 0x7F) % 16+ 0x30;
    tm_new.tm_sec  = ((buf[0] & 0x7F) / 16 + 0x30) + (buf[0] & 0x7F) % 16+ 0x30;

    return mktime(&tm_new);
}

static int raspi_set_timestamp(time_t timestamp)
{
    struct tm *tblock;
    tblock = localtime(&timestamp);
    buf[0] = 0;
    buf[1] = tblock->tm_sec;
    buf[2] = tblock->tm_min;
    buf[3] = tblock->tm_hour;
    buf[4] = tblock->tm_wday;
    buf[5] = tblock->tm_mday;
    buf[6] = tblock->tm_mon;
    buf[7] = tblock->tm_year;
    bcm283x_i2c_write((PER_BASE + BCM283X_BSC0_BASE) ,buf, 8);
    return RT_EOK;
}

static rt_err_t raspi_rtc_init(rt_device_t dev)
{
    bcm283x_i2c_setSlaveAddress(0, 0x68);
    bcm283x_i2c_set_baudrate(0, 10000);
    raspi_set_timestamp(0);
    return RT_EOK;
}

static rt_err_t raspi_rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
    bcm283x_i2c_begin(0);
    return RT_EOK;
}

static rt_err_t raspi_rtc_close(rt_device_t dev)
{
    bcm283x_i2c_end(0);
    return RT_EOK;
}

static rt_err_t raspi_rtc_control(rt_device_t dev, int cmd, void *args)
{

    RT_ASSERT(dev != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        *(rt_uint32_t *)args = raspi_get_timestamp();
        break;
    case RT_DEVICE_CTRL_RTC_SET_TIME:
        raspi_set_timestamp(*(time_t *)args);
        break;
    default:
        return RT_EINVAL;
    }
    return RT_EOK;
}

static rt_size_t raspi_rtc_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    raspi_rtc_control(dev, RT_DEVICE_CTRL_RTC_GET_TIME, buffer);
    return size;
}

static rt_size_t raspi_rtc_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    raspi_rtc_control(dev, RT_DEVICE_CTRL_RTC_SET_TIME, (void *)buffer);
    return size;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops raspi_rtc_ops =
{
    .init = raspi_rtc_init,
    .open = raspi_rtc_open,
    .close = raspi_rtc_close,
    .read = raspi_rtc_read,
    .write = raspi_rtc_write,
    .control = raspi_rtc_control
};
#endif

int rt_hw_rtc_init(void)
{
    rt_memset(&rtc_device, 0, sizeof(rtc_device));

    rtc_device.device.type        = RT_Device_Class_RTC;
    rtc_device.device.rx_indicate = RT_NULL;
    rtc_device.device.tx_complete = RT_NULL;
    rtc_device.device.ops         = &raspi_rtc_ops;
    rtc_device.device.user_data   = RT_NULL;

    /* register a rtc device */
    rt_device_register(&rtc_device.device, "rtc", RT_DEVICE_FLAG_RDWR);

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);
#endif /* BSP_USING_RTC */

