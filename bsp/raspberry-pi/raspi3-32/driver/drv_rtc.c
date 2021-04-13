/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>
#include "drv_rtc.h"

#ifdef BSP_USING_RTC

#define RTC_I2C_BUS_NAME      "i2c0"
#define RTC_ADDR               0x68

static struct rt_device rtc_device;
static struct rt_i2c_bus_device *i2c_bus = RT_NULL;

rt_uint8_t buf[]=
{
    0x00, 0x00, 0x43, 0x15, 0x05, 0x01, 0x03, 0x19
};


rt_uint8_t i2c_write_read_rs(char* cmds, rt_uint32_t cmds_len, char* buf, rt_uint32_t buf_len)
{
    rt_uint32_t remaining = cmds_len;
    rt_uint32_t i = 0;
    rt_uint8_t reason = BCM283X_I2C_REASON_OK;

    /* Clear FIFO */
    BCM283X_BSC_C(BCM283X_BSC0_BASE) |= (BSC_C_CLEAR_1 & BSC_C_CLEAR_1);

    /* Clear Status */
    BCM283X_BSC_S(BCM283X_BSC0_BASE) = BSC_S_CLKT | BSC_S_ERR | BSC_S_DONE;

    /* Set Data Length */
    BCM283X_BSC_DLEN(BCM283X_BSC0_BASE) = cmds_len;

    /* pre populate FIFO with max buffer */
    while (remaining && (i < BSC_FIFO_SIZE))
    {
        BCM283X_BSC_FIFO(BCM283X_BSC0_BASE) = cmds[i];
        i++;
        remaining--;
    }

    /* Enable device and start transfer */
    BCM283X_BSC_C(BCM283X_BSC0_BASE) |= BSC_C_I2CEN | BSC_C_ST;

    /* poll for transfer has started (way to do repeated start, from BCM2835 datasheet) */
    while (!(BCM283X_BSC_S(BCM283X_BSC0_BASE) & BSC_S_TA))
    {
        /* Linux may cause us to miss entire transfer stage */
        if (BCM283X_BSC_S(BCM283X_BSC0_BASE) & BSC_S_DONE)
            break;
    }

    remaining = buf_len;
    i = 0;

    /* Send a repeated start with read bit set in address */
    BCM283X_BSC_DLEN(BCM283X_BSC0_BASE) = buf_len;
    BCM283X_BSC_C(BCM283X_BSC0_BASE) = BSC_C_I2CEN | BSC_C_ST  | BSC_C_READ;

    /* Wait for write to complete and first byte back. */
  //  DELAYMICROS(i2c_byte_wait_us * (cmds_len + 1));

    /* wait for transfer to complete */
    while (!(BCM283X_BSC_S(BCM283X_BSC0_BASE) & BSC_S_DONE))
    {
        /* we must empty the FIFO as it is populated and not use any delay */
        while (remaining && (BCM283X_BSC_S(BCM283X_BSC0_BASE) & BSC_S_RXD))
        {
        /* Read from FIFO, no barrier */
        buf[i] = BCM283X_BSC_FIFO(BCM283X_BSC0_BASE);
        i++;
        remaining--;
        }
    }

    /* transfer has finished - grab any remaining stuff in FIFO */
    while (remaining && (BCM283X_BSC_S(BCM283X_BSC0_BASE) & BSC_S_RXD))
    {
        /* Read from FIFO */
        buf[i] = BCM283X_BSC_FIFO(BCM283X_BSC0_BASE);
        i++;
        remaining--;
    }

    /* Received a NACK */
    if (BCM283X_BSC_S(BCM283X_BSC0_BASE)  & BSC_S_ERR)
    {
        reason = BCM283X_I2C_REASON_ERROR_NACK;
    }

    /* Received Clock Stretch Timeout */
    else if (BCM283X_BSC_S(BCM283X_BSC0_BASE) & BSC_S_CLKT)
    {
        reason = BCM283X_I2C_REASON_ERROR_CLKT;
    }

    /* Not all data is sent */
    else if (remaining)
    {
        reason = BCM283X_I2C_REASON_ERROR_DATA;
    }

    BCM283X_BSC_C(BCM283X_BSC0_BASE) = (BSC_S_DONE &BSC_S_DONE);

    return reason;
}

rt_uint8_t i2c_write(rt_uint8_t* buf, rt_uint32_t len)
{
    rt_uint32_t remaining = len;
    rt_uint32_t i = 0;
    rt_uint8_t reason = BCM283X_I2C_REASON_OK;

    /* Clear FIFO */
    BCM283X_BSC_C(BCM283X_BSC0_BASE)  |= BSC_C_CLEAR_1 & BSC_C_CLEAR_1;
    /* Clear Status */
    BCM283X_BSC_S(BCM283X_BSC0_BASE) = BSC_S_CLKT | BSC_S_ERR | BSC_S_DONE;
    /* Set Data Length */
    BCM283X_BSC_DLEN(BCM283X_BSC0_BASE) = len;
    /* pre populate FIFO with max buffer */
    while (remaining && (i < BSC_FIFO_SIZE))
    {
        BCM283X_BSC_FIFO(BCM283X_BSC0_BASE) = buf[i];
        i++;
        remaining--;
    }

    /* Enable device and start transfer */
    BCM283X_BSC_C(BCM283X_BSC0_BASE) = BSC_C_I2CEN | BSC_C_ST;

    /* Transfer is over when BCM2835_BSC_S_DONE */
    while (!(BCM283X_BSC_S(BCM283X_BSC0_BASE) & BSC_S_DONE))
    {
        while (remaining && (BCM283X_BSC_S(BCM283X_BSC0_BASE) & BSC_S_TXD))
        {
        /* Write to FIFO */
        BCM283X_BSC_FIFO(BCM283X_BSC0_BASE) = buf[i];
        i++;
        remaining--;
        }
    }

    /* Received a NACK */
    if (BCM283X_BSC_S(BCM283X_BSC0_BASE) & BSC_S_ERR)
    {
        reason = BCM283X_I2C_REASON_ERROR_NACK;
    }

    /* Received Clock Stretch Timeout */
    else if (BCM283X_BSC_S(BCM283X_BSC0_BASE) & BSC_S_CLKT)
    {
        reason = BCM283X_I2C_REASON_ERROR_CLKT;
    }

    /* Not all data is sent */
    else if (remaining)
    {
        reason = BCM283X_I2C_REASON_ERROR_DATA;
    }

    BCM283X_BSC_C(BCM283X_BSC0_BASE) = BSC_S_DONE & BSC_S_DONE;
    return reason;
}


static time_t raspi_get_timestamp(void)
{
    struct tm tm_new = {0};
    buf[0] = 0;

    i2c_write_read_rs((char*)buf, 1, (char*)buf, 7);

    tm_new.tm_year = ((buf[6] / 16) + 0x30) * 10 + (buf[6] % 16) + 0x30;
    tm_new.tm_mon  = ((buf[5] & 0x1F) / 16 + 0x30) + (buf[5] & 0x1F) % 16+ 0x30;
    tm_new.tm_mday = ((buf[4] & 0x3F) / 16 + 0x30) + (buf[4] & 0x3F) % 16+ 0x30;
    tm_new.tm_hour = ((buf[2] & 0x3F) / 16 + 0x30) + (buf[2] & 0x3F) % 16+ 0x30;
    tm_new.tm_min  = ((buf[1] & 0x7F) / 16 + 0x30) + (buf[1] & 0x7F) % 16+ 0x30;
    tm_new.tm_sec  = ((buf[0] & 0x7F) / 16 + 0x30) + (buf[0] & 0x7F) % 16+ 0x30;

    return timegm(&tm_new);
}

static int raspi_set_timestamp(time_t timestamp)
{
    struct tm *tblock;
    tblock = gmtime(&timestamp);
    buf[0] = 0;
    buf[1] = tblock->tm_sec;
    buf[2] = tblock->tm_min;
    buf[3] = tblock->tm_hour;
    buf[4] = tblock->tm_wday;
    buf[5] = tblock->tm_mday;
    buf[6] = tblock->tm_mon;
    buf[7] = tblock->tm_year;

    i2c_write(buf, 8);

    return RT_EOK;
}

static rt_err_t raspi_rtc_init(rt_device_t dev)
{
    i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(RTC_I2C_BUS_NAME);
    raspi_set_timestamp(0);
    return RT_EOK;
}

static rt_err_t raspi_rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
    GPIO_FSEL(BCM_GPIO_PIN_0, BCM283X_GPIO_FSEL_ALT0); /* SDA */
    GPIO_FSEL(BCM_GPIO_PIN_1, BCM283X_GPIO_FSEL_ALT0); /* SCL */
    return RT_EOK;
}

static rt_err_t raspi_rtc_close(rt_device_t dev)
{
    GPIO_FSEL(BCM_GPIO_PIN_0, BCM283X_GPIO_FSEL_INPT); /* SDA */
    GPIO_FSEL(BCM_GPIO_PIN_1, BCM283X_GPIO_FSEL_INPT); /* SCL */
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
    rt_err_t ret = RT_EOK;

    rtc_device.type        = RT_Device_Class_RTC;
    rtc_device.rx_indicate = RT_NULL;
    rtc_device.tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    rtc_device.ops        = &raspi_rtc_ops;
#else
    rtc_device.init    = raspi_rtc_init;
    rtc_device.open    = raspi_rtc_open;
    rtc_device.close   = raspi_rtc_close;
    rtc_device.read    = raspi_rtc_read;
    rtc_device.write   = raspi_rtc_write;
    rtc_device.control = raspi_rtc_control;
#endif

    rtc_device.user_data   = RT_NULL;

    /* register a rtc device */
    ret = rt_device_register(&rtc_device, "rtc", RT_DEVICE_FLAG_RDWR);

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);
#endif /* BSP_USING_RTC */

