/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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
#define INPUTCAPTURE_CMD_ENABLE           (128 + 2)    /* enable inputcapture channel */
#define INPUTCAPTURE_CMD_DISABLE          (128 + 3)    /* diable inputcapture channel */

typedef enum {
    INPUTCAPTURE_CH1 = 1,
    INPUTCAPTURE_CH2 = 2,
    INPUTCAPTURE_CH3 = 3,
    INPUTCAPTURE_CH4 = 4,
}inputcapture_ch_t;

struct rt_inputcapture_data 
{
    rt_int32_t          pulsewidth_us;      /* 正表示高电位，负表示低电位 */
    inputcapture_ch_t   channel;            /* 定时捕获脉宽的通道: 1-4 */
};

struct rt_inputcapture_configuration
{
    rt_uint32_t channel; /* 0-n */
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
    rt_err_t (*control)(struct rt_inputcapture_device *device, int cmd, void *arg);
};

void rt_hw_inputcapture_isr(struct rt_inputcapture_device *inputcapture, struct rt_inputcapture_data *data);

rt_err_t rt_device_inputcapture_register(struct rt_inputcapture_device *inputcapture,
                                         const char                         *name,
                                         const struct rt_inputcapture_ops   *ops,
                                         void                               *data);
rt_err_t rt_inputcapture_enable(struct rt_inputcapture_device *device, inputcapture_ch_t channel);
rt_err_t rt_inputcapture_disable(struct rt_inputcapture_device *device, inputcapture_ch_t channel);

#ifdef __cplusplus
}
#endif

#endif /* __RT_INPUT_CAPTURE_H__ */
