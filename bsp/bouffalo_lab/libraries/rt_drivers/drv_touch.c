/*
 * COPYRIGHT (C) 2012-2022, Shanghai Real-Thread Technology Co., Ltd
 * All rights reserved.
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-20     Chushicheng  the first version
 */
#include "drv_touch.h"

#ifndef TOUCH_I2C_NAME
#define TOUCH_I2C_NAME "i2c0"
#endif
#define DBG_TAG "TOUCH"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

static struct rt_i2c_bus_device *i2c_bus = RT_NULL;

rt_err_t rt_touch_read(rt_uint16_t addr, rt_uint8_t *cmd_buf, size_t cmd_len, rt_uint8_t *data_buf, size_t data_len)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr = addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf = cmd_buf;
    msgs[0].len = cmd_len;

    msgs[1].addr = addr;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf = data_buf;
    msgs[1].len = data_len;

    if (rt_i2c_transfer(i2c_bus, msgs, 2) == 2)
        return RT_EOK;
    else
        return -RT_ERROR;
}

int rt_touch_write(rt_uint16_t addr, rt_uint8_t *data_buf, size_t data_len)
{
    struct rt_i2c_msg msgs[1];

    msgs[0].addr = addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf = data_buf;
    msgs[0].len = data_len;

    if (rt_i2c_transfer(i2c_bus, msgs, 1) == 1)
        return RT_EOK;
    else
        return -RT_ERROR;
}

static rt_size_t cst816_read_point(struct rt_touch_device *touch, void *buf, rt_size_t read_num)
{
    struct rt_touch_data *result = (struct rt_touch_data *)buf;
    rt_uint8_t cmd_buffer[1] = {0};
    rt_uint8_t rx_data[10] = {0};

    if (rt_pin_read(TOUCH_INT_PIN) == PIN_HIGH)
    {
        result->event = RT_TOUCH_EVENT_NONE;
        read_num = 0;
    }
    else
    {
        result->event = RT_TOUCH_EVENT_DOWN;
        cmd_buffer[0] = CST816X_REG_GESTUREID;
        if(rt_touch_read(CST816X_DEV_ADDR, cmd_buffer, 1, rx_data, 7) == RT_EOK)
        {
            uint8_t status = rx_data[2] >> 4;
            uint16_t pos_x = rx_data[2] & 0x0F;
            pos_x = (pos_x << 8) | rx_data[3];
            uint16_t pos_y = rx_data[4] & 0x0F;
            pos_y = (pos_y << 8) | rx_data[5];
            result->x_coordinate = pos_x;
            result->y_coordinate = pos_y;
        }
    }
    return read_num;
}

static rt_err_t touch_control(struct rt_touch_device *touch, int cmd, void *arg)
{
    return RT_EOK;
}

static struct rt_touch_ops touch_ops =
    {
        .touch_readpoint = cst816_read_point,
        .touch_control = touch_control,
};

int rt_touch_init(void)
{
    rt_touch_t touch_device = NULL;
    touch_device = (rt_touch_t)rt_calloc(1, sizeof(struct rt_touch_device));

    rt_pin_mode(TOUCH_RST_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(TOUCH_RST_PIN, PIN_LOW);
    rt_thread_mdelay(10);
    rt_pin_write(TOUCH_RST_PIN, PIN_HIGH);
    rt_thread_mdelay(50);
    rt_pin_mode(TOUCH_INT_PIN, PIN_MODE_INPUT_PULLUP);
    i2c_bus = rt_i2c_bus_device_find(TOUCH_I2C_NAME);
    RT_ASSERT(i2c_bus);

    if (rt_device_open(&i2c_bus->parent, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
    {
        rt_kprintf("open i2c dvice failed.\n");
        return -RT_EIO;
    } 
    /* touch infomation */
    touch_device->info.type = RT_TOUCH_TYPE_CAPACITANCE;
    touch_device->info.vendor = RT_TOUCH_VENDOR_UNKNOWN;
    touch_device->ops = &touch_ops;
    touch_device->irq_handle = RT_NULL;

    return rt_hw_touch_register(touch_device, "touch", RT_DEVICE_FLAG_INT_RX, RT_NULL);
}
INIT_DEVICE_EXPORT(rt_touch_init);