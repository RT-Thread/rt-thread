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
typedef enum
{
    ENCODER_INFO_GET = 0x01,        /* get a encoder feature information */
    ENCODER_SWITCH_ON,              /* switch on encoder */
    ENCODER_SWITCH_OFF,             /* switch off encoder */
    ENCODER_COUNT_CLEAR,            /* clear encoder count */
} rt_encoder_ctrl_t;

/* encoder type */
typedef enum
{
    SINGLE_PHASE_ENCODER = 0x01,    /* single phase encoder */
    AB_PHASE_ENCODER                /* two phase encoder */
} rt_encoder_type_t;

struct rt_encoder_device;

struct rt_encoder_ops
{
    rt_err_t (*init)(struct rt_encoder_device *encoder);
    rt_int32_t (*get_count)(struct rt_encoder_device *encoder);
    rt_err_t (*control)(struct rt_encoder_device *encoder, rt_uint32_t cmd, void *args);
};

/* Encoder feature information */
struct rt_encoder_info
{
    rt_encoder_type_t type;    /* the type of encoder */
};

typedef struct rt_encoder_device
{
    struct rt_device parent;
    const struct rt_encoder_ops *ops;
    const struct rt_encoder_info *info;
} rt_encoder_t;

rt_err_t rt_device_encoder_register(rt_encoder_t *encoder, const char *name, void *user_data);

#ifdef __cplusplus
}
#endif

#endif /* __ENCODER_H__ */
