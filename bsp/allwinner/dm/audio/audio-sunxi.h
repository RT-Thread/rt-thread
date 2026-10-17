/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __AUDIO_SUNXI_H__
#define __AUDIO_SUNXI_H__

#include <rtthread.h>
#include <rtdevice.h>

#define SUNXI_AUDIO_BUFFER_SIZE       16384
#define SUNXI_AUDIO_BLOCK_SIZE        4096

struct sunxi_audio_output;

struct sunxi_audio_output_ops
{
    rt_err_t (*init)(struct sunxi_audio_output *output);
    rt_err_t (*configure)(struct sunxi_audio_output *output,
            const struct rt_audio_configure *config);
    rt_err_t (*start)(struct sunxi_audio_output *output);
    void (*stop)(struct sunxi_audio_output *output);
    void (*enable_dma)(struct sunxi_audio_output *output, rt_bool_t enable);
};

struct sunxi_audio_output
{
    struct rt_audio_device parent;
    struct rt_device *dev;
    struct rt_dma_chan *dma_tx;
    rt_uint8_t *playback_buffer;
    rt_ubase_t playback_dma;
    rt_ubase_t fifo_dma;
    struct rt_audio_configure config;
    const struct sunxi_audio_output_ops *ops;
    struct rt_work dma_done_work;
    rt_bool_t running;
    rt_bool_t dma_done_work_initialized;
};

#define to_sunxi_audio_output(raw) \
    rt_container_of(raw, struct sunxi_audio_output, parent)

extern const struct rt_audio_ops sunxi_audio_output_audio_ops;

rt_err_t sunxi_audio_output_register(struct sunxi_audio_output *output,
        const char *prefix, void *data);
void sunxi_audio_output_stop(struct sunxi_audio_output *output);
void sunxi_audio_output_dma_done(struct rt_dma_chan *chan, rt_size_t size);
void sunxi_audio_output_release(struct sunxi_audio_output *output);

#endif /* __AUDIO_SUNXI_H__ */
