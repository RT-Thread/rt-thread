/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-08-08     balanceTWK   the first version
 */

#ifndef __PULSE_ENCODER_H__
#define __PULSE_ENCODER_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* pulse_encoder control command */
#define PULSE_ENCODER_CMD_GET_TYPE       (128 + 0)    /* get a pulse_encoder type information */
#define PULSE_ENCODER_CMD_ENABLE         (128 + 1)    /* enable pulse_encoder */
#define PULSE_ENCODER_CMD_DISABLE        (128 + 2)    /* disable pulse_encoder */
#define PULSE_ENCODER_CMD_CLEAR_COUNT    (128 + 3)    /* clear pulse_encoder count */

/* pulse_encoder type */
enum rt_pulse_encoder_type
{
    UNKNOWN_PULSE_ENCODER_TYPE = 0x00,    /* Unknown pulse_encoder type */
    SINGLE_PHASE_PULSE_ENCODER,           /* single phase pulse_encoder */
    AB_PHASE_PULSE_ENCODER                /* two phase pulse_encoder */
};

struct rt_pulse_encoder_device;

struct rt_pulse_encoder_ops
{
    rt_err_t (*init)(struct rt_pulse_encoder_device *pulse_encoder);
    rt_int32_t (*get_count)(struct rt_pulse_encoder_device *pulse_encoder);
    rt_err_t (*clear_count)(struct rt_pulse_encoder_device *pulse_encoder);
    rt_err_t (*control)(struct rt_pulse_encoder_device *pulse_encoder, rt_uint32_t cmd, void *args);
};

struct rt_pulse_encoder_device
{
    struct rt_device parent;
    const struct rt_pulse_encoder_ops *ops;
    enum rt_pulse_encoder_type type;
};

rt_err_t rt_device_pulse_encoder_register(struct rt_pulse_encoder_device *pulse_encoder, const char *name, void *user_data);

#ifdef __cplusplus
}
#endif

#endif /* __PULSE_ENCODER_H__ */
