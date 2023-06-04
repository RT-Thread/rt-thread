/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-26     Chushicheng  the first version
 */

#ifndef __DRV_GT911_H
#define __DRV_GT911_H

#include <rtdevice.h>

typedef enum
{
    GT911_INT_MODE_IRQ_RISE = 0x00U,
    GT911_INT_MODE_IRQ_FALL = 0x01U,
    GT911_INT_MODE_POLL     = 0x03U,
} gt911_int_mode_t;

typedef struct
{
    rt_uint8_t  id;
    rt_uint16_t pos_x;
    rt_uint16_t pos_y;
    rt_uint16_t size;
} gt911_point_t;

typedef struct
{
    rt_uint8_t       num_pos;
    gt911_point_t pos[5];
} gt911_input_t;

typedef struct
{
    rt_uint8_t *tx_data;
    rt_uint8_t *rx_data;
    rt_uint16_t tx_len;
    rt_uint16_t rx_len;
} gt911_i2c_xfer_t;

typedef rt_err_t (*gt911_ops_reset_t)(void *handle);
typedef rt_err_t (*gt911_ops_i2c_xfer_t)(void *handle, gt911_i2c_xfer_t *xfer);

typedef struct
{
    gt911_ops_reset_t    reset;
    gt911_ops_i2c_xfer_t xfer;
} gt911_ops_t;

typedef struct
{
    rt_uint16_t         pos_x_max;
    rt_uint16_t         pos_y_max;
    rt_uint8_t          pos_max;
    rt_uint8_t          fw_version;
    gt911_int_mode_t int_mode;
    gt911_ops_t      ops;
    void            *user_data;
} gt911_t;

typedef struct
{
    struct rt_device            parent;
    struct rt_i2c_bus_device   *bus;
    gt911_t                     gt911;
} capt_t;

rt_err_t gt911_ctp_read(gt911_t *ctp, gt911_input_t *input);
int drv_capt_hw_init(void);

#endif /* __DRV_GT911_H */
