/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-08-13     balanceTWK   first version.
 */

#ifndef __RT_INPUT_CAPTURE_H__
#define __RT_INPUT_CAPTURE_H__

#include <rtthread.h>
#include <rtdevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/* capture control command */
#define INPUTCAPTURE_CMD_CLEAR_BUF        (128 + 0)    /* clear capture buf */
#define INPUTCAPTURE_CMD_SET_WATERMARK    (128 + 1)    /* Set the callback threshold */

struct rt_inputcapture_data
{
    rt_uint32_t pulsewidth_us;
    rt_bool_t   is_high;
};

struct rt_inputcapture_device
{
    struct rt_device                    parent;

    const struct rt_inputcapture_ops    *ops;
    struct rt_ringbuffer                *ringbuff;
    rt_size_t                           watermark;
};

/**
 * capture operators
 */
struct rt_inputcapture_ops
{
    rt_err_t (*init)(struct rt_inputcapture_device *inputcapture);
    rt_err_t (*open)(struct rt_inputcapture_device *inputcapture);
    rt_err_t (*close)(struct rt_inputcapture_device *inputcapture);
    rt_err_t (*get_pulsewidth)(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us);
};

void rt_hw_capture_isr(struct rt_inputcapture_device *inputcapture, rt_bool_t level);

rt_err_t rt_device_inputcapture_register(struct rt_inputcapture_device *inputcapture,
                                         const char                    *name,
                                         void                          *data);
#ifdef __cplusplus
}
#endif

#endif /* __RT_INPUT_CAPTURE_H__ */
