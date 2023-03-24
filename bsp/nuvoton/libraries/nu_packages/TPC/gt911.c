/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-13     RiceChen     the first version
 * 2022-02-25     Wayne        optimization
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "gt911"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "gt911.h"

static struct rt_i2c_client gt911_client;

/* hardware section */
static rt_uint8_t GT911_CFG_TBL[] =
{
    0x6b, 0x00, 0x04, 0x58, 0x02, 0x05, 0x0d, 0x00, 0x01, 0x0f,
    0x28, 0x0f, 0x50, 0x32, 0x03, 0x05, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8a, 0x2a, 0x0c,
    0x45, 0x47, 0x0c, 0x08, 0x00, 0x00, 0x00, 0x40, 0x03, 0x2c,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x64, 0x32, 0x00, 0x00,
    0x00, 0x28, 0x64, 0x94, 0xd5, 0x02, 0x07, 0x00, 0x00, 0x04,
    0x95, 0x2c, 0x00, 0x8b, 0x34, 0x00, 0x82, 0x3f, 0x00, 0x7d,
    0x4c, 0x00, 0x7a, 0x5b, 0x00, 0x7a, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x18, 0x16, 0x14, 0x12, 0x10, 0x0e, 0x0c, 0x0a,
    0x08, 0x06, 0x04, 0x02, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x16, 0x18, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21,
    0x22, 0x24, 0x13, 0x12, 0x10, 0x0f, 0x0a, 0x08, 0x06, 0x04,
    0x02, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x79, 0x01,
};
static void gt911_touch_up(void *buf, rt_int8_t id);
static rt_err_t gt911_write_reg(struct rt_i2c_client *dev, rt_uint8_t *data, rt_uint8_t len)
{
    struct rt_i2c_msg msgs;

    msgs.addr  = dev->client_addr;
    msgs.flags = RT_I2C_WR;
    msgs.buf   = data;
    msgs.len   = len;

    if (rt_i2c_transfer(dev->bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}

static rt_err_t gt911_read_regs(struct rt_i2c_client *dev, rt_uint8_t *reg, rt_uint8_t *data, rt_uint8_t len)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr  = dev->client_addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = reg;
    msgs[0].len   = GT911_REGITER_LEN;

    msgs[1].addr  = dev->client_addr;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf   = data;
    msgs[1].len   = len;

    if (rt_i2c_transfer(dev->bus, msgs, 2) == 2)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}

static rt_err_t gt911_get_product_id(struct rt_i2c_client *dev, rt_uint8_t *data, rt_uint8_t len)
{
    rt_uint8_t reg[2];

    reg[0] = (rt_uint8_t)(GT911_PRODUCT_ID >> 8);
    reg[1] = (rt_uint8_t)(GT911_PRODUCT_ID & 0xff);

    if (gt911_read_regs(dev, reg, data, len) != RT_EOK)
    {
        LOG_E("read id failed");
        return -RT_ERROR;
    }
    return RT_EOK;
}

static rt_err_t gt911_get_info(struct rt_i2c_client *dev, struct rt_touch_info *info)
{
    rt_uint8_t reg[2];
    rt_uint8_t out_info[7];
    rt_uint8_t out_len = 7;

    reg[0] = (rt_uint8_t)(GT911_CONFIG_REG >> 8);
    reg[1] = (rt_uint8_t)(GT911_CONFIG_REG & 0xFF);

    if (gt911_read_regs(dev, reg, out_info, out_len) != RT_EOK)
    {
        LOG_E("read info failed");
        return -RT_ERROR;
    }

    info->range_x = (out_info[2] << 8) | out_info[1];
    info->range_y = (out_info[4] << 8) | out_info[3];
    info->point_num = out_info[5] & 0x0f;

    return RT_EOK;
}

static rt_err_t gt911_soft_reset(struct rt_i2c_client *dev)
{
    rt_uint8_t buf[3];

    buf[0] = (rt_uint8_t)(GT911_COMMAND_REG >> 8);
    buf[1] = (rt_uint8_t)(GT911_COMMAND_REG & 0xFF);
    buf[2] = 0x02;

    if (gt911_write_reg(dev, buf, 3) != RT_EOK)
    {
        LOG_E("soft reset failed");
        return -RT_ERROR;
    }
    return RT_EOK;
}

static rt_int16_t pre_x[GT911_MAX_TOUCH];
static rt_int16_t pre_y[GT911_MAX_TOUCH];
static rt_int16_t pre_w[GT911_MAX_TOUCH];
static rt_uint8_t s_tp_dowm[GT911_MAX_TOUCH];

static void gt911_touch_up(void *buf, rt_int8_t id)
{
    struct rt_touch_data *read_data = (struct rt_touch_data *)buf;

    if (s_tp_dowm[id] == 1)
    {
        s_tp_dowm[id] = 0;
        read_data[id].event = RT_TOUCH_EVENT_UP;
    }
    else
    {
        read_data[id].event = RT_TOUCH_EVENT_NONE;
    }

    read_data[id].timestamp = rt_touch_get_ts();
    read_data[id].width = pre_w[id];
    read_data[id].x_coordinate = pre_x[id];
    read_data[id].y_coordinate = pre_y[id];
    read_data[id].track_id = id;

    pre_x[id] = -1;  /* last point is none */
    pre_y[id] = -1;
    pre_w[id] = -1;
}

static void gt911_touch_down(void *buf, rt_int8_t id, rt_int16_t x, rt_int16_t y, rt_int16_t w)
{
    struct rt_touch_data *read_data = (struct rt_touch_data *)buf;

    if (s_tp_dowm[id] == 1)
    {
        read_data[id].event = RT_TOUCH_EVENT_MOVE;

    }
    else
    {
        read_data[id].event = RT_TOUCH_EVENT_DOWN;
        s_tp_dowm[id] = 1;
    }

    read_data[id].timestamp = rt_touch_get_ts();
    read_data[id].width = w;
    read_data[id].x_coordinate = x;
    read_data[id].y_coordinate = y;
    read_data[id].track_id = id;

    pre_x[id] = x; /* save last point */
    pre_y[id] = y;
    pre_w[id] = w;
}

static rt_int8_t pre_id[GT911_MAX_TOUCH];
static rt_uint8_t pre_touch = 0;

static rt_ssize_t gt911_read_point(struct rt_touch_device *touch, void *buf, rt_size_t read_num)
{
    rt_uint8_t point_status = 0;
    rt_uint8_t touch_num = 0;
    rt_uint8_t write_buf[3];
    rt_uint8_t cmd[2];
    rt_uint8_t read_buf[8 * GT911_MAX_TOUCH] = {0};
    rt_uint8_t i;
    rt_int8_t read_id = 0;
    rt_int16_t input_x = 0;
    rt_int16_t input_y = 0;
    rt_int16_t input_w = 0;

    /* point status register */
    cmd[0] = (rt_uint8_t)((GT911_READ_STATUS >> 8) & 0xFF);
    cmd[1] = (rt_uint8_t)(GT911_READ_STATUS & 0xFF);

    if (gt911_read_regs(&gt911_client, cmd, &point_status, 1) != RT_EOK)
    {
        LOG_D("read point failed\n");
        read_num = 0;
        goto exit_;
    }

    if (point_status == 0)             /* no data */
    {
        read_num = 0;
        goto exit_;
    }

    if ((point_status & 0x80) == 0)    /* data is not ready */
    {
        read_num = 0;
        goto exit_;
    }

    touch_num = point_status & 0x0f;  /* get point num */

    if (touch_num > GT911_MAX_TOUCH) /* point num is not correct */
    {
        read_num = 0;
        goto exit_;
    }

    cmd[0] = (rt_uint8_t)((GT911_POINT1_REG >> 8) & 0xFF);
    cmd[1] = (rt_uint8_t)(GT911_POINT1_REG & 0xFF);

    /* read point num is touch_num */
    if (gt911_read_regs(&gt911_client, cmd, read_buf, read_num * GT911_POINT_INFO_NUM) != RT_EOK)
    {
        LOG_D("read point failed\n");
        read_num = 0;
        goto exit_;
    }

    if (pre_touch > touch_num)                                       /* point up */
    {
        for (i = 0; i < GT911_MAX_TOUCH; i++)
        {
            rt_uint8_t j;

            for (j = 0; j < touch_num; j++)                          /* this time touch num */
            {
                read_id = read_buf[j * 8] & 0x0F;

                if (pre_id[i] == read_id)                   /* this id is not free */
                    break;

            }
            if ((j == touch_num) && (pre_id[i] != -1))           /* free this node */
            {
                gt911_touch_up(buf, pre_id[i]);
                pre_id[i] = -1;
            }
        }
    }

    if (touch_num > 0)                                                 /* point down */
    {
        rt_uint8_t off_set;

        for (i = 0; i < touch_num; i++)
        {
            off_set = i * 8;
            read_id = read_buf[off_set] & 0x0f;
            pre_id[i] = read_id;

            input_x = read_buf[off_set + 1] | (read_buf[off_set + 2] << 8); /* x */
            input_y = read_buf[off_set + 3] | (read_buf[off_set + 4] << 8); /* y */
            input_w = read_buf[off_set + 5] | (read_buf[off_set + 6] << 8); /* size */

            gt911_touch_down(buf, read_id, input_x, input_y, input_w);
        }
    }

    pre_touch = touch_num;

exit_:
    write_buf[0] = (rt_uint8_t)((GT911_READ_STATUS >> 8) & 0xFF);
    write_buf[1] = (rt_uint8_t)(GT911_READ_STATUS & 0xFF);
    write_buf[2] = 0x00;
    gt911_write_reg(&gt911_client, write_buf, 3);

    return read_num;
}

static rt_err_t gt911_control(struct rt_touch_device *touch, int cmd, void *arg)
{
    if (cmd == RT_TOUCH_CTRL_GET_ID)
    {
        return gt911_get_product_id(&gt911_client, arg, 6);
    }

    if (cmd == RT_TOUCH_CTRL_GET_INFO)
    {
        return gt911_get_info(&gt911_client, arg);
    }

    rt_uint8_t buf[4];
    rt_uint8_t i = 0;
    rt_uint8_t *config;

    config = (rt_uint8_t *)rt_calloc(1, sizeof(GT911_CFG_TBL) + GT911_REGITER_LEN);
    if (config == RT_NULL)
    {
        LOG_D("malloc config memory failed\n");
        return -RT_ERROR;
    }

    config[0] = (rt_uint8_t)((GT911_CONFIG_REG >> 8) & 0xFF);
    config[1] = (rt_uint8_t)(GT911_CONFIG_REG & 0xFF);

    rt_memcpy(&config[2], GT911_CFG_TBL, sizeof(GT911_CFG_TBL));

    switch (cmd)
    {
    case RT_TOUCH_CTRL_SET_X_RANGE:
    {
        rt_uint16_t x_range;

        x_range = *(rt_uint16_t *)arg;
        config[4] = (rt_uint8_t)(x_range >> 8);
        config[3] = (rt_uint8_t)(x_range & 0xff);

        GT911_CFG_TBL[2] = config[4];
        GT911_CFG_TBL[1] = config[3];
        break;
    }
    case RT_TOUCH_CTRL_SET_Y_RANGE:
    {
        rt_uint16_t y_range;

        y_range = *(rt_uint16_t *)arg;
        config[6] = (rt_uint8_t)(y_range >> 8);
        config[5] = (rt_uint8_t)(y_range & 0xff);

        GT911_CFG_TBL[4] = config[6];
        GT911_CFG_TBL[3] = config[5];
        break;
    }
    case RT_TOUCH_CTRL_SET_X_TO_Y:
    {
        config[8] ^= (1 << 3);
        break;
    }
    case RT_TOUCH_CTRL_SET_MODE:
    {
        rt_uint16_t trig_type;
        trig_type = *(rt_uint16_t *)arg;

        switch (trig_type)
        {
        case RT_DEVICE_FLAG_INT_RX:
            config[8] &= 0xFC;
            break;
        case RT_DEVICE_FLAG_RDONLY:
            config[8] &= 0xFC;
            config[8] |= 0x02;
            break;
        default:
            break;
        }
        break;
    }
    default:
    {
        break;
    }
    }

    if (gt911_write_reg(&gt911_client, config, sizeof(GT911_CFG_TBL) + GT911_ADDR_LEN) != RT_EOK)
    {
        LOG_D("send config failed");
        return -1;
    }

    buf[0] = (rt_uint8_t)((GT911_CHECK_SUM >> 8) & 0xFF);
    buf[1] = (rt_uint8_t)(GT911_CHECK_SUM & 0xFF);
    buf[2] = 0;

    for (i = GT911_ADDR_LEN; i < sizeof(GT911_CFG_TBL) + GT911_ADDR_LEN; i++)
    {
        buf[GT911_ADDR_LEN] += config[i];
    }

    buf[2] = (~buf[2]) + 1;
    buf[3] = 1;

    gt911_write_reg(&gt911_client, buf, 4);
    rt_free(config);

    return RT_EOK;
}

static struct rt_touch_ops gt911_touch_ops =
{
    .touch_readpoint = gt911_read_point,
    .touch_control = gt911_control,
};

int rt_hw_gt911_init(const char *name, struct rt_touch_config *cfg)
{
    struct rt_touch_device *touch_device = RT_NULL;
    rt_uint32_t bus_speed = 400000;

    touch_device = (struct rt_touch_device *)rt_malloc(sizeof(struct rt_touch_device));
    if (touch_device == RT_NULL)
    {
        LOG_E("touch device malloc fail");
        return -RT_ERROR;
    }
    rt_memset((void *)touch_device, 0, sizeof(struct rt_touch_device));

    /* hw init*/
    rt_pin_mode(*(rt_uint8_t *)cfg->user_data, PIN_MODE_OUTPUT);
    rt_pin_mode(cfg->irq_pin.pin, PIN_MODE_OUTPUT);

    rt_pin_write(*(rt_uint8_t *)cfg->user_data, PIN_LOW);
    rt_pin_write(cfg->irq_pin.pin, PIN_LOW);
    rt_thread_delay(10);
    rt_pin_write(*(rt_uint8_t *)cfg->user_data, PIN_HIGH);
    rt_thread_delay(10);
    rt_pin_write(cfg->irq_pin.pin, PIN_MODE_INPUT);
    rt_thread_delay(100);

    gt911_client.bus = (struct rt_i2c_bus_device *)rt_device_find(cfg->dev_name);

    if (gt911_client.bus == RT_NULL)
    {
        LOG_E("Can't find %s device", cfg->dev_name);
        return -RT_ERROR;
    }

    if (rt_device_open((rt_device_t)gt911_client.bus, RT_DEVICE_FLAG_RDWR) != RT_EOK)
    {
        LOG_E("open %s device failed", cfg->dev_name);
        return -RT_ERROR;
    }

    if (rt_device_control((rt_device_t)gt911_client.bus, RT_I2C_DEV_CTRL_CLK, &bus_speed) != RT_EOK)
    {
        LOG_E("control %s device failed", cfg->dev_name);
        return -RT_ERROR;
    }

    gt911_client.client_addr = GT911_ADDRESS_HIGH;
    gt911_soft_reset(&gt911_client);

    rt_memset(&pre_x[0], 0xff,  GT911_MAX_TOUCH * sizeof(rt_int16_t));
    rt_memset(&pre_y[0], 0xff,  GT911_MAX_TOUCH * sizeof(rt_int16_t));
    rt_memset(&pre_w[0], 0xff,  GT911_MAX_TOUCH * sizeof(rt_int16_t));
    rt_memset(&s_tp_dowm[0], 0, GT911_MAX_TOUCH * sizeof(rt_int8_t));
    rt_memset(&pre_id[0], 0xff, GT911_MAX_TOUCH * sizeof(rt_uint8_t));

    /* register touch device */
    touch_device->info.type = RT_TOUCH_TYPE_CAPACITANCE;
    touch_device->info.vendor = RT_TOUCH_VENDOR_GT;
    rt_memcpy(&touch_device->config, cfg, sizeof(struct rt_touch_config));
    touch_device->ops = &gt911_touch_ops;

    rt_hw_touch_register(touch_device, name, RT_DEVICE_FLAG_INT_RX, RT_NULL);

    LOG_I("touch device gt911 init success");

    return RT_EOK;
}
