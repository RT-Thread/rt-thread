/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-25     Wayne        the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <nu_bitutil.h>

#define DBG_TAG "ili_tpc"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "ili.h"

#define ILI_MAX_TOUCH         5
#define ILI_ADDRESS           0x41

#define BL_V1_8                     0x108
#define BL_V1_7                     0x107
#define BL_V1_6                     0x106

#define ILITEK_TP_CMD_GET_TP_RES            0x20
#define ILITEK_TP_CMD_GET_SCRN_RES      0x21
#define ILITEK_TP_CMD_SET_IC_SLEEP      0x30
#define ILITEK_TP_CMD_SET_IC_WAKE           0x31
#define ILITEK_TP_CMD_GET_FW_VER            0x40
#define ILITEK_TP_CMD_GET_PRL_VER           0x42
#define ILITEK_TP_CMD_GET_MCU_VER           0x61
#define ILITEK_TP_CMD_GET_IC_MODE           0xC0
#define ILITEK_TP_CMD_RESET                 0x60

#define REPORT_COUNT_ADDRESS                  61

struct ili_protocol_info
{
    rt_uint16_t     ver;
    rt_uint8_t      ver_major;
};

struct ili_ts_data
{
    struct rt_touch_device touch_device;
    struct rt_i2c_client *client;

    rt_base_t       reset_pin;
    rt_base_t       irq_pin;

    struct ili_protocol_info    ptl;
    rt_uint8_t      product_id[30];
    rt_uint16_t     mcu_ver;
    rt_uint8_t      ic_mode;
    rt_uint8_t      firmware_ver[8];

    rt_int32_t      screen_max_x;
    rt_int32_t      screen_max_y;
    rt_int32_t      screen_min_x;
    rt_int32_t      screen_min_y;
    rt_int32_t      max_tp;
};
typedef struct ili_ts_data *ili_ts_data_t;

// Private data
static struct ili_ts_data g_iliTsData;

static rt_err_t ili_i2c_write_and_read(struct rt_i2c_client *psI2cClient,
                                       rt_uint8_t *cmd, int write_len, int delay,
                                       rt_uint8_t *data, int read_len)
{
    struct rt_i2c_msg msgs[] =
    {
        {
            .addr = psI2cClient->client_addr,
            .flags = RT_I2C_WR,
            .len = write_len,
            .buf = cmd,
        },
        {
            .addr = psI2cClient->client_addr,
            .flags = RT_I2C_RD,
            .len = read_len,
            .buf = data,
        },
    };

    if (delay == 0 && write_len > 0 && read_len > 0)
    {
        if (rt_i2c_transfer(psI2cClient->bus, msgs, 2) != 2)
            goto exit_ili_i2c_write_and_read;
    }
    else
    {
        if (write_len > 0)
        {
            if (rt_i2c_transfer(psI2cClient->bus, msgs, 1) != 1)
                goto exit_ili_i2c_write_and_read;
        }

        if (delay > 0)
            rt_thread_mdelay(delay);

        if (read_len > 0)
        {
            if (rt_i2c_transfer(psI2cClient->bus, msgs + 1, 1) != 1)
                goto exit_ili_i2c_write_and_read;
        }
    }

    return RT_EOK;

exit_ili_i2c_write_and_read:

    return -RT_ERROR;
}

static int ili_get_ptl_ver(ili_ts_data_t psIliTs,
                           rt_uint16_t  cmd, rt_uint8_t *inbuf, rt_uint8_t *outbuf)
{
    rt_int32_t error;
    rt_uint8_t buf[64];

    buf[0] = cmd;
    error = ili_i2c_write_and_read(psIliTs->client, buf, 1, 5, outbuf, 3);
    if (error)
        return error;

    psIliTs->ptl.ver = nu_get16_be(outbuf);
    psIliTs->ptl.ver_major = outbuf[0];

    return 0;
}

static int ili_get_mcu_ver(ili_ts_data_t psIliTs,
                           rt_uint16_t  cmd, rt_uint8_t *inbuf, rt_uint8_t *outbuf)
{
    rt_int32_t error;
    rt_uint8_t buf[64];

    buf[0] = cmd;
    error = ili_i2c_write_and_read(psIliTs->client, buf, 1, 5, outbuf, 32);
    if (error)
        return error;

    psIliTs->mcu_ver = nu_get16_le(outbuf);
    rt_memset(psIliTs->product_id, 0, sizeof(psIliTs->product_id));
    rt_memcpy(psIliTs->product_id, outbuf + 6, 26);

    return 0;
}

static int ili_get_fw_ver(ili_ts_data_t psIliTs,
                          rt_uint16_t  cmd, rt_uint8_t *inbuf, rt_uint8_t *outbuf)
{
    rt_int32_t error;
    rt_uint8_t buf[64];

    buf[0] = cmd;
    error = ili_i2c_write_and_read(psIliTs->client, buf, 1, 5, outbuf, 8);
    if (error)
        return error;

    rt_memcpy(psIliTs->firmware_ver, outbuf, 8);

    return 0;
}

static int ili_get_scrn_res(ili_ts_data_t psIliTs,
                            rt_uint16_t  cmd, rt_uint8_t *inbuf, rt_uint8_t *outbuf)
{
    rt_int32_t error;
    rt_uint8_t buf[64];

    buf[0] = cmd;
    error = ili_i2c_write_and_read(psIliTs->client, buf, 1, 5, outbuf, 8);
    if (error)
        return error;

    psIliTs->screen_min_x = nu_get16_le(outbuf);
    psIliTs->screen_min_y = nu_get16_le(outbuf + 2);
    psIliTs->screen_max_x = nu_get16_le(outbuf + 4);
    psIliTs->screen_max_y = nu_get16_le(outbuf + 6);

    return 0;
}

static int ili_get_tp_res(ili_ts_data_t psIliTs,
                          rt_uint16_t  cmd, rt_uint8_t *inbuf, rt_uint8_t *outbuf)
{
    rt_int32_t error;
    rt_uint8_t buf[64];

    buf[0] = cmd;
    error = ili_i2c_write_and_read(psIliTs->client, buf, 1, 5, outbuf, 15);
    if (error)
        return error;

    psIliTs->max_tp = outbuf[8];
    if (psIliTs->max_tp > ILI_MAX_TOUCH)
    {
        return -RT_EINVAL;
    }

    return 0;
}

static int ili_get_ic_mode(ili_ts_data_t psIliTs,
                           rt_uint16_t cmd, rt_uint8_t *inbuf, rt_uint8_t *outbuf)
{
    rt_int32_t error;
    rt_uint8_t buf[64];

    buf[0] = cmd;
    error = ili_i2c_write_and_read(psIliTs->client, buf, 1, 5, outbuf, 2);
    if (error)
        return error;

    psIliTs->ic_mode = outbuf[0];
    return 0;
}

static int ili_send_soft_reset(ili_ts_data_t psIliTs,
                               rt_uint16_t  cmd, rt_uint8_t *inbuf, rt_uint8_t *outbuf)
{
    rt_int32_t error;
    rt_uint8_t buf[64];

    buf[0] = cmd;
    error = ili_i2c_write_and_read(psIliTs->client, buf, 1, 0, RT_NULL, 0);
    if (error)
        return error;

    return 0;
}

static void ili_tpc_reset(ili_ts_data_t psIliTs, int delay_ms)
{
    if (0)
    {
        //FIXME
        /* hw pin init*/
        rt_pin_mode(psIliTs->reset_pin, PIN_MODE_OUTPUT);

        /* Reset */
        rt_pin_write(psIliTs->reset_pin, PIN_HIGH);
        rt_thread_mdelay(10);
        rt_pin_write(psIliTs->reset_pin, PIN_LOW);
    }
    else
    {
        rt_err_t error;
        error = ili_send_soft_reset(psIliTs, ILITEK_TP_CMD_RESET, RT_NULL, RT_NULL);
        if (error)
            return;
    }
    rt_thread_mdelay(delay_ms);
}

static rt_err_t ili_get_info(ili_ts_data_t psIliTs, struct rt_touch_info *info)
{
    rt_uint8_t outbuf[256];
    rt_err_t error;

    error = ili_get_ptl_ver(psIliTs, ILITEK_TP_CMD_GET_PRL_VER, RT_NULL, outbuf);
    if (error)
        goto exit_ili_get_info;

    error = ili_get_mcu_ver(psIliTs, ILITEK_TP_CMD_GET_MCU_VER, RT_NULL, outbuf);
    if (error)
        goto exit_ili_get_info;

    error = ili_get_fw_ver(psIliTs, ILITEK_TP_CMD_GET_FW_VER, NULL, outbuf);
    if (error)
        goto exit_ili_get_info;

    error = ili_get_scrn_res(psIliTs, ILITEK_TP_CMD_GET_SCRN_RES, NULL, outbuf);
    if (error)
        goto exit_ili_get_info;

    error = ili_get_tp_res(psIliTs, ILITEK_TP_CMD_GET_TP_RES, NULL, outbuf);
    if (error)
        goto exit_ili_get_info;

    error = ili_get_ic_mode(psIliTs, ILITEK_TP_CMD_GET_IC_MODE, NULL, outbuf);
    if (error)
        goto exit_ili_get_info;

    LOG_I("touch device probed");

    return RT_EOK;

exit_ili_get_info:

    return -RT_ERROR;
}

static void ili_info_dump(ili_ts_data_t psIliTs)
{
    rt_kprintf("reset_pin: %d\n", psIliTs->reset_pin);
    rt_kprintf("irq_pin: %d\n", psIliTs->irq_pin);
    rt_kprintf("ptl.ver: %x \n", psIliTs->ptl.ver_major);
    rt_kprintf("mcu_ver: %x\n", psIliTs->mcu_ver);
    rt_kprintf("firmware_ver:[%02X%02X.%02X%02X.%02X%02X.%02X%02X]\n",
               psIliTs->firmware_ver[0],
               psIliTs->firmware_ver[1],
               psIliTs->firmware_ver[2],
               psIliTs->firmware_ver[3],
               psIliTs->firmware_ver[4],
               psIliTs->firmware_ver[5],
               psIliTs->firmware_ver[6],
               psIliTs->firmware_ver[7]);

    rt_kprintf("product_id: %s\n", psIliTs->product_id);

    rt_kprintf("screen_max_x: %d\n", psIliTs->screen_max_x);
    rt_kprintf("screen_max_y: %d\n", psIliTs->screen_max_y);
    rt_kprintf("screen_min_x: %d\n", psIliTs->screen_min_x);
    rt_kprintf("screen_min_y: %d\n", psIliTs->screen_min_y);
    rt_kprintf("max_tp: %d\n", psIliTs->max_tp);
    rt_kprintf("ic_mode: %d\n", psIliTs->ic_mode);
}

static rt_int16_t pre_x[ILI_MAX_TOUCH];
static rt_int16_t pre_y[ILI_MAX_TOUCH];
static rt_int16_t pre_w[ILI_MAX_TOUCH];
static rt_uint8_t s_tp_dowm[ILI_MAX_TOUCH];

static void ili_touch_up(void *buf, int8_t id)
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

static void ili_touch_down(void *buf, int8_t id, int16_t x, int16_t y, int16_t w)
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

static int8_t pre_id[ILI_MAX_TOUCH];
static rt_uint8_t pre_touch = 0;
static rt_ssize_t ili_read_point(struct rt_touch_device *touch, void *buf, rt_size_t read_num)
{
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))

    struct ili_ts_data *ts = (ili_ts_data_t)touch;
    rt_uint8_t tmpbuf[256] = {0};
    rt_err_t error = 0;
    rt_int32_t packet_len = 5;
    rt_int32_t packet_max_point = 10;
    rt_int8_t touch_num;
    rt_int32_t i, count;
    rt_uint16_t x, y;
    rt_int32_t   tip, point_id;

    RT_ASSERT(touch);
    RT_ASSERT(buf);
    RT_ASSERT(read_num != 0);
    RT_ASSERT(read_num <= ILI_MAX_TOUCH);

    error = ili_i2c_write_and_read(ts->client, NULL, 0, 0, tmpbuf, 64);
    if (error)
    {
        LOG_E("get touch info failed, err:%d\n", error);
        goto exit_ili_read_point;
    }

    touch_num = tmpbuf[REPORT_COUNT_ADDRESS];
    if (touch_num > ts->max_tp)
    {
        LOG_E("FW report max point:%d > panel info. max:%d\n", touch_num, ts->max_tp);
        goto exit_ili_read_point;
    }

    count = DIV_ROUND_UP(touch_num, packet_max_point);
    for (i = 1; i < count; i++)
    {
        error = ili_i2c_write_and_read(ts->client, NULL, 0, 0, tmpbuf + i * 64, 64);
        if (error)
        {
            LOG_E("get touch info. failed, cnt:%d, err:%d\n",   count, error);
            goto exit_ili_read_point;
        }
    }

    if (pre_touch > touch_num)                                       /* point up */
    {
        for (i = 0; i < ILI_MAX_TOUCH; i++)
        {
            rt_uint8_t j;
            for (j = 0; j < touch_num; j++)                          /* this time touch num */
            {
                point_id = tmpbuf[j * packet_len + 1] & 0x3F;

                if (pre_id[i] == point_id)                   /* this id is not free */
                    break;

            }
            if ((j == touch_num) && (pre_id[i] != -1))
            {
                ili_touch_up(buf, pre_id[i]);
                pre_id[i] = -1;
            }
        }
    }

    if (touch_num > 0)
    {
        uint32_t range_x = touch->info.range_x;
        uint32_t range_y = touch->info.range_y;

        for (i = 0; i < touch_num; i++)
        {
            tip = tmpbuf[i * packet_len + 1] & 0x40;
            point_id = tmpbuf[i * packet_len + 1] & 0x3F;
            pre_id[i] = point_id;
            if (!tip)
            {
                // Up
                ili_touch_up(buf, point_id);
                continue;
            }

            x = nu_get16_le(tmpbuf + i * packet_len + 2);
            y = nu_get16_le(tmpbuf + i * packet_len + 4);

            if (x > ts->screen_max_x || x < ts->screen_min_x ||
                    y > ts->screen_max_y || y < ts->screen_min_y)
            {
                LOG_E("invalid position, X[%d,%u,%d], Y[%d,%u,%d]\n",
                      ts->screen_min_x, x, ts->screen_max_x,
                      ts->screen_min_y, y, ts->screen_max_y);
                continue;
            }
            x = (uint16_t)(range_x * x / ts->screen_max_x);
            y = (uint16_t)(range_y * y / ts->screen_max_y);

            ili_touch_down(buf, point_id, x, y, 255);
        }
    }

    pre_touch = touch_num;

    return read_num;

exit_ili_read_point:

    pre_touch = 0;

    return 0;
}

static rt_err_t ili_control(struct rt_touch_device *touch, int cmd, void *arg)
{
    switch (cmd)
    {
    case RT_TOUCH_CTRL_GET_ID:
    {
        RT_ASSERT(arg);
        rt_uint8_t *pu8ID = arg;
        rt_memcpy((void *)pu8ID, (void *)&g_iliTsData.product_id[0], 8);
    }
    break;

    case RT_TOUCH_CTRL_GET_INFO:
    {
        RT_ASSERT(arg);

        touch->info.type      = RT_TOUCH_TYPE_CAPACITANCE;
        touch->info.vendor    = RT_TOUCH_VENDOR_UNKNOWN;
        touch->info.point_num = g_iliTsData.max_tp;

        rt_memcpy(arg, &touch->info, sizeof(struct rt_touch_info));
    }
    break;

    case RT_TOUCH_CTRL_SET_X_RANGE:
    {
        RT_ASSERT(arg);
        uint16_t range_x = *(rt_uint16_t *)arg;
        if (range_x > g_iliTsData.screen_max_x || range_x < g_iliTsData.screen_min_x)
        {
            LOG_E("Set x range failed. %d", range_x);
        }
        else
        {
            touch->info.range_x   = range_x;
        }
    }
    break;

    case RT_TOUCH_CTRL_SET_Y_RANGE:
    {
        RT_ASSERT(arg);
        uint16_t range_y = *(rt_uint16_t *)arg;
        if (range_y > g_iliTsData.screen_max_y || range_y < g_iliTsData.screen_min_y)
        {
            LOG_E("Set y range failed. %d", range_y);
        }
        else
        {
            touch->info.range_y   = range_y;
        }
    }
    break;

    case RT_TOUCH_CTRL_SET_MODE:
    {
        rt_uint16_t trig_type;
        RT_ASSERT(arg);
        trig_type = *(rt_uint16_t *)arg;

        switch (trig_type)
        {
        case RT_DEVICE_FLAG_INT_RX:
            break;
        case RT_DEVICE_FLAG_RDONLY:
            break;
        default:
            break;
        }
    }
    break;

    default:
    {
    }
    break;

    }

    return RT_EOK;
}

static struct rt_touch_ops ili_touch_ops =
{
    .touch_readpoint = ili_read_point,
    .touch_control = ili_control,
};

int rt_hw_ili_tpc_init(const char *name, struct rt_touch_config *cfg)
{
    struct rt_touch_device *touch_device = RT_NULL;
    rt_uint32_t bus_speed = 400000;

    touch_device = (struct rt_touch_device *)&g_iliTsData.touch_device;
    rt_memset((void *)touch_device, 0, sizeof(struct rt_touch_device));

    g_iliTsData.client = (struct rt_i2c_client *)rt_malloc(sizeof(struct rt_i2c_client));
    if (g_iliTsData.client == RT_NULL)
    {
        LOG_E("touch device malloc fail");
        goto exit_rt_hw_ili_tpc_init;
    }
    rt_memset((void *)g_iliTsData.client, 0, sizeof(struct rt_i2c_client));

    g_iliTsData.reset_pin = *((rt_base_t *)cfg->user_data);
    g_iliTsData.irq_pin   = cfg->irq_pin.pin;

    g_iliTsData.client->client_addr = ILI_ADDRESS;
    g_iliTsData.client->bus = (struct rt_i2c_bus_device *)rt_device_find(cfg->dev_name);
    if (g_iliTsData.client->bus == RT_NULL)
    {
        LOG_E("Can't find %s device", cfg->dev_name);
        goto exit_rt_hw_ili_tpc_init;
    }

    if (rt_device_open((rt_device_t)g_iliTsData.client->bus, RT_DEVICE_FLAG_RDWR) != RT_EOK)
    {
        LOG_E("open %s device failed", cfg->dev_name);
        goto exit_rt_hw_ili_tpc_init;
    }

    rt_memset(&pre_x[0], 0xff, ILI_MAX_TOUCH * sizeof(rt_int16_t));
    rt_memset(&pre_y[0], 0xff, ILI_MAX_TOUCH * sizeof(rt_int16_t));
    rt_memset(&pre_w[0], 0xff, ILI_MAX_TOUCH * sizeof(rt_int16_t));
    rt_memset(&s_tp_dowm[0], 0, ILI_MAX_TOUCH * sizeof(rt_uint8_t));
    rt_memset(&pre_id[0], 0xff,  ILI_MAX_TOUCH * sizeof(rt_uint8_t));

    /* register touch device */
    rt_memcpy(&touch_device->config, cfg, sizeof(struct rt_touch_config));
    touch_device->ops = &ili_touch_ops;
    if (rt_hw_touch_register(touch_device, name, RT_DEVICE_FLAG_INT_RX, RT_NULL) != RT_EOK)
    {
        LOG_E("register %s device failed", name);
        goto exit_rt_hw_ili_tpc_init;
    }

    ili_tpc_reset(&g_iliTsData, 300);

    if (rt_device_control((rt_device_t)g_iliTsData.client->bus, RT_I2C_DEV_CTRL_CLK, &bus_speed) != RT_EOK)
    {
        LOG_E("control %s device failed", cfg->dev_name);
        goto exit_rt_hw_ili_tpc_init;
    }

    /* Probe */
    if (ili_get_info(&g_iliTsData, &touch_device->info) != RT_EOK)
    {
        LOG_E("Get info failed");
        return -RT_ERROR;
    }
    ili_info_dump(&g_iliTsData);


    return 0;

exit_rt_hw_ili_tpc_init:

    if (g_iliTsData.client)
        rt_free(g_iliTsData.client);

    return -RT_ERROR;
}
