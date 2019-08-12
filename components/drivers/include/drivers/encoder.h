/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-08-08     balanceTWK   the first version
 */

#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <rtthread.h>
#include <rtdevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/* encoder control command */
#define ENCODER_CMD_GET_TYPE       (128 + 0)    /* get a encoder type information */
#define ENCODER_CMD_ENABLE         (128 + 1)    /* enable encoder */
#define ENCODER_CMD_DISABLE        (128 + 2)    /* disable encoder */
#define ENCODER_CMD_CLEAR_COUNT    (128 + 3)    /* clear encoder count */

/* encoder type */
enum rt_encoder_type
{
    UNKNOWN_ENCODER_TYPE = 0x00,    /* Unknown encoder type */
    SINGLE_PHASE_ENCODER,           /* single phase encoder */
    AB_PHASE_ENCODER                /* two phase encoder */
};

struct rt_encoder_device;

struct rt_encoder_ops
{
    rt_err_t (*init)(struct rt_encoder_device *encoder);
    rt_int32_t (*get_count)(struct rt_encoder_device *encoder);
    rt_err_t (*clear_count)(struct rt_encoder_device *encoder);
    rt_err_t (*control)(struct rt_encoder_device *encoder, rt_uint32_t cmd, void *args);
};

struct rt_encoder_device
{
    struct rt_device parent;
    const struct rt_encoder_ops *ops;
    enum rt_encoder_type type;
};

rt_err_t rt_device_encoder_register(struct rt_encoder_device *encoder, const char *name, void *user_data);

#ifdef __cplusplus
}
#endif

#endif /* __ENCODER_H__ */
