/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-06-01     tyustli     the first version
 */

#include <rtthread.h>
#include <board.h>

#include <string.h>
#include <stdlib.h>

#define DBG_TAG "gt9147"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "gt9147.h"

static struct rt_i2c_client *gt9147_client;

/* hardware section */
static rt_uint8_t GT9147_CFG_TBL[] =
{
    0X00, 0XE0, 0X01, 0X10, 0X01, 0X05, 0X3C, 0X00, 0X02, 0X08,
    0X1E, 0X08, 0X50, 0X3C, 0X0F, 0X05, 0X00, 0X00, 0XFF, 0X67,
    0X50, 0X00, 0X00, 0X18, 0X1A, 0X1E, 0X14, 0X89, 0X28, 0X0A,
    0X30, 0X2E, 0XBB, 0X0A, 0X03, 0X00, 0X00, 0X02, 0X33, 0X1D,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X32, 0X00, 0X00,
    0X2A, 0X1C, 0X5A, 0X94, 0XC5, 0X02, 0X07, 0X00, 0X00, 0X00,
    0XB5, 0X1F, 0X00, 0X90, 0X28, 0X00, 0X77, 0X32, 0X00, 0X62,
    0X3F, 0X00, 0X52, 0X50, 0X00, 0X52, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X0F,
    0X0F, 0X03, 0X06, 0X10, 0X42, 0XF8, 0X0F, 0X14, 0X00, 0X00,
    0X00, 0X00, 0X1A, 0X18, 0X16, 0X14, 0X12, 0X10, 0X0E, 0X0C,
    0X0A, 0X08, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X29, 0X28, 0X24, 0X22, 0X20, 0X1F, 0X1E, 0X1D,
    0X0E, 0X0C, 0X0A, 0X08, 0X06, 0X05, 0X04, 0X02, 0X00, 0XFF,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
    0XFF, 0XFF, 0XFF, 0XFF,
};

static rt_err_t gt9147_write_reg(struct rt_i2c_client *dev, rt_uint8_t write_len, rt_uint8_t *write_data)
{
    struct rt_i2c_msg msgs;

    msgs.addr  = dev->client_addr;
    msgs.flags = RT_I2C_WR;
    msgs.buf   = write_data;
    msgs.len   = write_len;

    if (rt_i2c_transfer(dev->bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}

static rt_err_t gt9147_read_regs(struct rt_i2c_client *dev, rt_uint8_t *cmd_buf, rt_uint8_t cmd_len, rt_uint8_t read_len, rt_uint8_t *read_buf)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr  = dev->client_addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = cmd_buf;
    msgs[0].len   = cmd_len;

    msgs[1].addr  = dev->client_addr;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf   = read_buf;
    msgs[1].len   = read_len;

    if (rt_i2c_transfer(dev->bus, msgs, 2) == 2)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}

/**
 * This function read the product id
 *
 * @param dev the pointer of device driver structure
 * @param reg the register for gt9xx
 * @param read data len
 * @param read data pointer
 *
 * @return the read status, RT_EOK reprensents  read the value of the register successfully.
 */
static rt_err_t gt9147_get_product_id(struct rt_i2c_client *dev, rt_uint8_t read_len, rt_uint8_t *read_data)
{
    rt_uint8_t cmd_buf[2];

    cmd_buf[0] = (rt_uint8_t)(GT9XX_PRODUCT_ID >> 8);
    cmd_buf[1] = (rt_uint8_t)(GT9XX_PRODUCT_ID & 0xff);

    if (gt9147_read_regs(dev, cmd_buf, 2, read_len, read_data) != RT_EOK)
    {
        LOG_D("read id failed \n");

        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t gt9147_get_info(struct rt_i2c_client *dev, struct rt_touch_info *info)
{
    rt_uint8_t opr_buf[7] = {0};
    rt_uint8_t cmd_buf[2];

    cmd_buf[0] = (rt_uint8_t)(GT9147_CONFIG >> 8);
    cmd_buf[1] = (rt_uint8_t)(GT9147_CONFIG & 0xff);

    if (gt9147_read_regs(dev, cmd_buf, 2, 7, opr_buf) != RT_EOK)
    {
        LOG_D("read id failed \n");

        return -RT_ERROR;
    }

    info->range_x = (opr_buf[2] << 8) + opr_buf[1];
    info->range_y = (opr_buf[4] << 8) + opr_buf[3];
    info->point_num = opr_buf[5] & 0x0f;

    return RT_EOK;

}

static rt_err_t gt9147_soft_reset(struct rt_i2c_client *dev)
{
    rt_uint8_t buf[3];

    buf[0] = (rt_uint8_t)(GT9147_COMMAND >> 8);
    buf[1] = (rt_uint8_t)(GT9147_COMMAND & 0xFF);
    buf[2] = 0x02;

    if (gt9147_write_reg(dev, 3, buf) != RT_EOK)
    {
        LOG_D("soft reset gt9147 failed\n");
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t gt9147_control(struct rt_touch_device *device, int cmd, void *data)
{
    if (cmd == RT_TOUCH_CTRL_GET_ID)
    {
        return gt9147_get_product_id(gt9147_client, 6, data);
    }

    if (cmd == RT_TOUCH_CTRL_GET_INFO)
    {
        return gt9147_get_info(gt9147_client, data);
    }

    rt_uint8_t buf[4];
    rt_uint8_t i = 0;
    rt_uint8_t *config;

    config = (rt_uint8_t *)rt_calloc(1, sizeof(GT9147_CFG_TBL) + GTP_ADDR_LENGTH);

    if (config == RT_NULL)
    {
        LOG_D("malloc config memory failed\n");
        return -RT_ERROR;
    }

    config[0] = (rt_uint8_t)((GT9147_CONFIG >> 8) & 0xFF); /* config reg */
    config[1] = (rt_uint8_t)(GT9147_CONFIG & 0xFF);

    memcpy(&config[2], GT9147_CFG_TBL, sizeof(GT9147_CFG_TBL)); /* config table */

    switch(cmd)
    {
    case RT_TOUCH_CTRL_SET_X_RANGE: /* set x range */
    {
        rt_uint16_t x_ran;

        x_ran = *(rt_uint16_t *)data;
        config[4] = (rt_uint8_t)(x_ran >> 8);
        config[3] = (rt_uint8_t)(x_ran & 0xff);

        GT9147_CFG_TBL[2] = config[4];
        GT9147_CFG_TBL[1] = config[3];

        break;
    }
    case RT_TOUCH_CTRL_SET_Y_RANGE: /* set y range */
    {
        rt_uint16_t y_ran;

        y_ran = *(rt_uint16_t *)data;
        config[6] = (rt_uint8_t)(y_ran >> 8);
        config[5] = (rt_uint8_t)(y_ran & 0xff);

        GT9147_CFG_TBL[4] = config[6];
        GT9147_CFG_TBL[3] = config[5];

        break;
    }
    case RT_TOUCH_CTRL_SET_X_TO_Y: /* change x y */
    {
        config[8] = config[8] ^= (1 << 3);
        break;
    }
    case RT_TOUCH_CTRL_SET_MODE: /* change int trig type */
    {
        rt_uint16_t trig_type;
        trig_type = *(rt_uint16_t *)data;

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

    memcpy(GT9147_CFG_TBL, &config[2], sizeof(GT9147_CFG_TBL));

    if (gt9147_write_reg(gt9147_client, sizeof(GT9147_CFG_TBL) + GTP_ADDR_LENGTH, config) != RT_EOK)  /* send config */
    {
        LOG_D("send config failed\n");
        return -RT_ERROR;
    }

    buf[0] = (rt_uint8_t)((GT9147_CHECK_SUM >> 8) & 0xFF);
    buf[1] = (rt_uint8_t)(GT9147_CHECK_SUM & 0xFF);
    buf[2] = 0;

    for(i = GTP_ADDR_LENGTH; i < sizeof(GT9147_CFG_TBL) + GTP_ADDR_LENGTH; i++)
        buf[GTP_ADDR_LENGTH] += config[i];

    buf[2] = (~buf[2]) + 1;
    buf[3] = 1;

    gt9147_write_reg(gt9147_client, 4, buf);
    rt_free(config);

    return RT_EOK;
}

static int16_t pre_x[GT9147_MAX_TOUCH] = {-1, -1, -1, -1, -1};
static int16_t pre_y[GT9147_MAX_TOUCH] = {-1, -1, -1, -1, -1};
static int16_t pre_w[GT9147_MAX_TOUCH] = {-1, -1, -1, -1, -1};
static rt_uint8_t s_tp_dowm[GT9147_MAX_TOUCH];
static struct rt_touch_data *read_data;

static void gt9147_touch_up(void *buf, int8_t id)
{
    read_data = (struct rt_touch_data *)buf;

    if(s_tp_dowm[id] == 1)
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

static void gt9147_touch_down(void *buf, int8_t id, int16_t x, int16_t y, int16_t w)
{
    read_data = (struct rt_touch_data *)buf;

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

static rt_size_t gt9147_read_point(struct rt_touch_device *touch, void *buf, rt_size_t read_num)
{
    rt_uint8_t point_status = 0;
    rt_uint8_t touch_num = 0;
    rt_uint8_t write_buf[3];
    rt_uint8_t cmd[2];
    rt_uint8_t read_buf[8 * GT9147_MAX_TOUCH] = {0};
    rt_uint8_t read_index;
    int8_t read_id = 0;
    int16_t input_x = 0;
    int16_t input_y = 0;
    int16_t input_w = 0;

    static rt_uint8_t pre_touch = 0;
    static int8_t pre_id[GT9147_MAX_TOUCH] = {0};

    /* point status register */
    cmd[0] = (rt_uint8_t)((GT9147_READ_STATUS >> 8) & 0xFF);
    cmd[1] = (rt_uint8_t)(GT9147_READ_STATUS & 0xFF);

    if (gt9147_read_regs(gt9147_client, cmd, 2, 1, &point_status) != RT_EOK)
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

    if (touch_num > GT9147_MAX_TOUCH) /* point num is not correct */
    {
        read_num = 0;
        goto exit_;
    }

    cmd[0] = (rt_uint8_t)((GT9147_POINT1_REG >> 8) & 0xFF);
    cmd[1] = (rt_uint8_t)(GT9147_POINT1_REG & 0xFF);

    /* read point num is read_num */
    if (gt9147_read_regs(gt9147_client, cmd, 2, read_num * GT9147_POINT_INFO_NUM, read_buf) != RT_EOK)
    {
        LOG_D("read point failed\n");
        read_num = 0;
        goto exit_;
    }

    if (pre_touch > touch_num)                                       /* point up */
    {
        for (read_index = 0; read_index < pre_touch; read_index++)
        {
            rt_uint8_t j;

            for (j = 0; j < touch_num; j++)                          /* this time touch num */
            {
                read_id = read_buf[j * 8] & 0x0F;

                if (pre_id[read_index] == read_id)                   /* this id is not free */
                    break;

                if (j >= touch_num - 1)
                {
                    rt_uint8_t up_id;
                    up_id = pre_id[read_index];
                    gt9147_touch_up(buf, up_id);
                }
            }
        }
    }

    if (touch_num)                                                 /* point down */
    {
        rt_uint8_t off_set;

        for (read_index = 0; read_index < touch_num; read_index++)
        {
            off_set = read_index * 8;
            read_id = read_buf[off_set] & 0x0f;
            pre_id[read_index] = read_id;
            input_x = read_buf[off_set + 1] | (read_buf[off_set + 2] << 8);	/* x */
            input_y = read_buf[off_set + 3] | (read_buf[off_set + 4] << 8);	/* y */
            input_w = read_buf[off_set + 5] | (read_buf[off_set + 6] << 8);	/* size */

            gt9147_touch_down(buf, read_id, input_x, input_y, input_w);
        }
    }
    else if (pre_touch)
    {
        for(read_index = 0; read_index < pre_touch; read_index++)
        {
            gt9147_touch_up(buf, pre_id[read_index]);
        }
    }

    pre_touch = touch_num;

exit_:
    write_buf[0] = (rt_uint8_t)((GT9147_READ_STATUS >> 8) & 0xFF);
    write_buf[1] = (rt_uint8_t)(GT9147_READ_STATUS & 0xFF);
    write_buf[2] = 0x00;
    gt9147_write_reg(gt9147_client, 3, write_buf);
    return read_num;
}

static struct rt_touch_ops touch_ops =
{
    .touch_readpoint = gt9147_read_point,
    .touch_control = gt9147_control,
};

int rt_hw_gt9147_init(const char *name, struct rt_touch_config *cfg)
{
    rt_touch_t touch_device = RT_NULL;

    touch_device = (rt_touch_t)rt_calloc(1, sizeof(struct rt_touch_device));

    if (touch_device == RT_NULL)
        return -RT_ERROR;

    /* hardware init */
    rt_pin_mode(*(rt_uint8_t *)cfg->user_data, PIN_MODE_OUTPUT);
    rt_pin_mode(cfg->irq_pin.pin, PIN_MODE_OUTPUT);
    rt_pin_write(*(rt_uint8_t *)cfg->user_data, PIN_LOW);
    rt_thread_mdelay(10);
    rt_pin_write(*(rt_uint8_t *)cfg->user_data, PIN_HIGH);
    rt_thread_mdelay(10);
    rt_pin_mode(cfg->irq_pin.pin, PIN_MODE_INPUT);
    rt_thread_mdelay(100);

    /* interface bus */
    gt9147_client = (struct rt_i2c_client *)rt_calloc(1, sizeof(struct rt_i2c_client));

    gt9147_client->bus = (struct rt_i2c_bus_device *)rt_device_find(cfg->dev_name);

    if (gt9147_client->bus == RT_NULL)
    {
        LOG_E("Can't find device\n");
        return -RT_ERROR;
    }

    if (rt_device_open((rt_device_t)gt9147_client->bus, RT_DEVICE_FLAG_RDWR) != RT_EOK)
    {
        LOG_E("open device failed\n");
        return -RT_ERROR;
    }

    gt9147_client->client_addr = GT9147_ADDRESS_HIGH;
    gt9147_soft_reset(gt9147_client);

    /* register touch device */
    touch_device->info.type = RT_TOUCH_TYPE_CAPACITANCE;
    touch_device->info.vendor = RT_TOUCH_VENDOR_GT;
    rt_memcpy(&touch_device->config, cfg, sizeof(struct rt_touch_config));
    touch_device->ops = &touch_ops;

    rt_hw_touch_register(touch_device, name, RT_DEVICE_FLAG_INT_RX, RT_NULL);

    LOG_I("touch device gt9147 init success\n");

    return RT_EOK;
}

/************************** end of file ********************************/


