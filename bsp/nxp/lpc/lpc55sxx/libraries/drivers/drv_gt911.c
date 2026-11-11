/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-26     Chushicheng  the first version
 */

#include "drv_gt911.h"

#define LOG_TAG             "drv.gt911"
#include <drv_log.h>

#ifndef BSP_TOUCH_I2C_BUS
#define BSP_TOUCH_I2C_BUS       "i2c1"
#endif
#define CAPT_I2C_ADDR           (0x5D)

#define GT911_REG_RT_CMD            0x8040U
#define GT911_REG_RT_CMD_SW_RST_Pos 2U
#define GT911_REG_RT_CMD_SW_RST_Msk (1U << GT911_REG_RT_CMD_SW_RST_Pos)
#define GT911_REG_RT_CMD_READ_Pos   0U
#define GT911_REG_RT_CMD_READ_Msk   (1U << GT911_REG_RT_CMD_READ_Pos)

#define GT911_REG_CONFIG_VERSION 0x8047U

#define GT911_REG_MODULE_SW1         0x804DU
#define GT911_REG_MODULE_SW1_INT_Pos 0U
#define GT911_REG_MODULE_SW1_INT_Msk (3U << GT911_REG_MODULE_SW1_INT_Pos)

#define GT911_REG_PRODUCT_ID 0x8140U

#define GT911_REG_COORD            0x814EU
#define GT911_REG_COORD_STATUS_Pos 7U
#define GT911_REG_COORD_STATUS_Msk (1U << GT911_REG_COORD_STATUS_Pos)

#define GT911_REG_POINT0 0x814FU

static capt_t capt_obj;

static rt_err_t gt911_ctp_read_reg(gt911_t *ctp, rt_uint16_t reg, rt_uint8_t *data, rt_uint16_t len);
static rt_err_t gt911_ctp_write_reg(gt911_t *ctp, rt_uint16_t reg, rt_uint8_t data);
static rt_err_t gt911_ctp_sw_reset(gt911_t *ctp);
static rt_err_t gt911_ctp_read_config(gt911_t *ctp);
static rt_err_t gt911_ctp_config_interrupt(gt911_t *ctp);
static rt_err_t gt911_ctp_init(gt911_t *ctp);
rt_err_t gt911_ctp_read(gt911_t *ctp, gt911_input_t *input);

static rt_err_t gt911_ctp_init(gt911_t *ctp)
{
    if (ctp->ops.reset)
    {
        if (ctp->ops.reset(ctp->user_data) != RT_EOK)
        {
            return -RT_ERROR;
        }
    }
    if (gt911_ctp_sw_reset(ctp) != RT_EOK)
    {
        return -RT_ERROR;
    }
    if (gt911_ctp_read_config(ctp) != RT_EOK)
    {
        return -RT_ERROR;
    }
    if (gt911_ctp_config_interrupt(ctp) != RT_EOK)
    {
        return -RT_ERROR;
    }
    return RT_EOK;
}

rt_err_t gt911_ctp_read(gt911_t *ctp, gt911_input_t *input)
{
    rt_uint8_t rx_data[40] = {0};

    if (gt911_ctp_read_reg(ctp, GT911_REG_COORD, rx_data, 1) != RT_EOK)
    {
        return -RT_ERROR;
    }
    if ((rx_data[0] & GT911_REG_COORD_STATUS_Msk) == 0)
    {
        input->num_pos = 0U;
        return RT_EOK;
    }
    input->num_pos = rx_data[0] & 0x0F;
    if (gt911_ctp_read_reg(ctp, GT911_REG_POINT0, rx_data, 40) != RT_EOK)
    {
        return -RT_ERROR;
    }
    for (rt_uint8_t i = 0; i < input->num_pos; i++)
    {
        rt_uint8_t point_offset = 8 * i; /* Each point has 8 bytes */

        input->pos[i].id    = rx_data[point_offset];                                         /* 0x00: Track ID */
        input->pos[i].pos_x = rx_data[point_offset + 1] | (rx_data[point_offset + 2] << 8U); /* 0x01-0x02: X coord */
        input->pos[i].pos_y = rx_data[point_offset + 3] | (rx_data[point_offset + 4] << 8U); /* 0x03-0x04: Y coord */
        input->pos[i].size  = rx_data[point_offset + 5] | (rx_data[point_offset + 6] << 8U); /* 0x05-0x06: Size*/
    }
    /* Clear buffer status latch, ready for new data */
    gt911_ctp_write_reg(ctp, GT911_REG_COORD, 0x00);

    return RT_EOK;
}

static rt_err_t gt911_ctp_read_reg(gt911_t *ctp, rt_uint16_t reg, rt_uint8_t *data, rt_uint16_t len)
{
    rt_uint8_t tx_data[2] = {(reg >> 8U), (reg & 0xFFU)};
    gt911_i2c_xfer_t xfer =
    {
        .tx_data = tx_data,
        .rx_data = data,
        .tx_len  = 2,
        .rx_len  = len,
    };

    return ctp->ops.xfer(ctp->user_data, &xfer);
}

static rt_err_t gt911_ctp_write_reg(gt911_t *ctp, rt_uint16_t reg, rt_uint8_t data)
{
    rt_uint8_t tx_data[3] = {(reg >> 8U), (reg & 0xFFU), data};
    gt911_i2c_xfer_t xfer =
    {
        .tx_data = tx_data,
        .rx_data = NULL,
        .tx_len  = 3,
        .rx_len  = 0,
    };

    return ctp->ops.xfer(ctp->user_data, &xfer);
}

static rt_err_t gt911_ctp_sw_reset(gt911_t *ctp)
{
    return gt911_ctp_write_reg(ctp, GT911_REG_RT_CMD, (GT911_REG_RT_CMD_SW_RST_Msk));
}

static rt_err_t gt911_ctp_read_config(gt911_t *ctp)
{
    rt_uint8_t rx_data[7];
    if (gt911_ctp_read_reg(ctp, GT911_REG_CONFIG_VERSION, rx_data, 7) != RT_EOK)
    {
        return -RT_ERROR;
    }
    ctp->fw_version = rx_data[0];                      /* 0x8047, Config Version */
    ctp->pos_x_max  = rx_data[1] | (rx_data[2] << 8U); /* 0x8048-0x8049, Maximum X */
    ctp->pos_y_max  = rx_data[3] | (rx_data[4] << 8U); /* 0x804A-0x804B, Maximum Y */
    ctp->pos_max    = rx_data[5] & 0x0FU;              /* 0x804C, Maximum positions */

    return RT_EOK;
}

static rt_err_t gt911_ctp_config_interrupt(gt911_t *ctp)
{
    rt_uint8_t mod_sw1 = 0x00U;
    if (gt911_ctp_read_reg(ctp, GT911_REG_MODULE_SW1, &mod_sw1, 0x01) != RT_EOK)
    {
        return -RT_ERROR;
    }
    mod_sw1 &= ~(GT911_REG_MODULE_SW1_INT_Msk);
    mod_sw1 |= (ctp->int_mode & GT911_REG_MODULE_SW1_INT_Msk);

    return gt911_ctp_write_reg(ctp, GT911_REG_MODULE_SW1, mod_sw1);
}

static rt_err_t ctp_impl_xfer(void *handle, gt911_i2c_xfer_t *xfer)
{
    capt_t *capt = (capt_t*)handle;

    if(xfer->tx_len) rt_i2c_master_send(capt->bus, CAPT_I2C_ADDR, 0, xfer->tx_data, xfer->tx_len);
    if(xfer->rx_len) rt_i2c_master_recv(capt->bus, CAPT_I2C_ADDR, 0, xfer->rx_data, xfer->rx_len);

    return RT_EOK;
}

int drv_capt_hw_init(void)
{
    capt_obj.bus = (struct rt_i2c_bus_device*)rt_device_find(BSP_TOUCH_I2C_BUS);
    if(capt_obj.bus == RT_NULL)
    {
        LOG_E("no %s device", BSP_TOUCH_I2C_BUS);
        return -RT_ERROR;
    }

    capt_obj.gt911.user_data = capt_obj.parent.user_data = &capt_obj;
    capt_obj.gt911.ops.xfer = ctp_impl_xfer;
    if(gt911_ctp_init(&capt_obj.gt911) != RT_EOK)
    {
        return -RT_ERROR;
    }
    rt_device_register(&capt_obj.parent, "capt", RT_DEVICE_FLAG_RDWR);

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(drv_capt_hw_init);
