/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "audio-sunxi.h"

static rt_err_t sunxi_audio_output_getcaps(struct rt_audio_device *audio,
        struct rt_audio_caps *caps)
{
    struct sunxi_audio_output *output = to_sunxi_audio_output(audio);

    switch (caps->main_type)
    {
    case AUDIO_TYPE_QUERY:
        if (caps->sub_type != AUDIO_TYPE_QUERY)
        {
            return -RT_ENOSYS;
        }
        caps->udata.mask = AUDIO_TYPE_OUTPUT;
        return RT_EOK;

    case AUDIO_TYPE_OUTPUT:
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            caps->udata.config = output->config;
            return RT_EOK;
        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate = output->config.samplerate;
            return RT_EOK;
        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels = output->config.channels;
            return RT_EOK;
        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits = output->config.samplebits;
            return RT_EOK;
        default:
            return -RT_ENOSYS;
        }

    default:
        return -RT_ENOSYS;
    }
}

static rt_err_t sunxi_audio_output_configure(struct rt_audio_device *audio,
        struct rt_audio_caps *caps)
{
    rt_err_t err;
    struct rt_audio_configure config;
    struct sunxi_audio_output *output = to_sunxi_audio_output(audio);

    if (output->running)
    {
        return -RT_EBUSY;
    }
    if (caps->main_type != AUDIO_TYPE_OUTPUT)
    {
        return -RT_ENOSYS;
    }

    config = output->config;
    switch (caps->sub_type)
    {
    case AUDIO_DSP_PARAM:
        config = caps->udata.config;
        break;
    case AUDIO_DSP_SAMPLERATE:
        config.samplerate = caps->udata.config.samplerate;
        break;
    case AUDIO_DSP_CHANNELS:
        config.channels = caps->udata.config.channels;
        break;
    case AUDIO_DSP_SAMPLEBITS:
        config.samplebits = caps->udata.config.samplebits;
        break;
    default:
        return -RT_ENOSYS;
    }

    err = output->ops->configure(output, &config);
    if (!err)
    {
        output->config = config;
    }

    return err;
}

static rt_err_t sunxi_audio_output_init(struct rt_audio_device *audio)
{
    rt_err_t err;
    struct sunxi_audio_output *output = to_sunxi_audio_output(audio);

    if (output->ops->init)
    {
        err = output->ops->init(output);
        if (err)
        {
            return err;
        }
    }

    return output->ops->configure(output, &output->config);
}

static rt_err_t sunxi_audio_output_start(struct rt_audio_device *audio,
        int stream)
{
    rt_err_t err;
    struct sunxi_audio_output *output = to_sunxi_audio_output(audio);

    if (stream != AUDIO_STREAM_REPLAY)
    {
        return -RT_ENOSYS;
    }

    err = output->ops->start(output);
    if (err)
    {
        return err;
    }

    output->running = RT_TRUE;
    rt_audio_tx_complete(audio);

    return RT_EOK;
}

void sunxi_audio_output_stop(struct sunxi_audio_output *output)
{
    output->running = RT_FALSE;
    rt_dma_chan_stop(output->dma_tx);
    output->ops->stop(output);
}

static rt_err_t sunxi_audio_output_stop_device(struct rt_audio_device *audio,
        int stream)
{
    struct sunxi_audio_output *output = to_sunxi_audio_output(audio);

    if (stream != AUDIO_STREAM_REPLAY)
    {
        return -RT_ENOSYS;
    }

    sunxi_audio_output_stop(output);

    return RT_EOK;
}

static rt_ssize_t sunxi_audio_output_transmit(struct rt_audio_device *audio,
        const void *write_buf, void *read_buf, rt_size_t size)
{
    rt_err_t err;
    rt_size_t width;
    rt_ubase_t offset;
    const rt_uint8_t *buffer = write_buf;
    struct rt_dma_slave_config config;
    struct rt_dma_slave_transfer transfer;
    struct sunxi_audio_output *output = to_sunxi_audio_output(audio);

    if (!output->running || !write_buf || read_buf || !size ||
            size > SUNXI_AUDIO_BLOCK_SIZE)
    {
        return -RT_EINVAL;
    }
    if (buffer < output->playback_buffer ||
            buffer >= output->playback_buffer + SUNXI_AUDIO_BUFFER_SIZE)
    {
        return -RT_EINVAL;
    }

    offset = buffer - output->playback_buffer;
    if (offset + size > SUNXI_AUDIO_BUFFER_SIZE)
    {
        return -RT_EINVAL;
    }

    width = output->config.samplebits == 16 ? 2 : 4;
    if ((offset % width) || (size % width))
    {
        return -RT_EINVAL;
    }

    rt_memset(&config, 0, sizeof(config));
    config.direction = RT_DMA_MEM_TO_DEV;
    config.src_addr_width = width == 2 ? RT_DMA_SLAVE_BUSWIDTH_2_BYTES :
            RT_DMA_SLAVE_BUSWIDTH_4_BYTES;
    config.dst_addr_width = config.src_addr_width;
    config.src_maxburst = 8;
    config.dst_maxburst = 8;
    config.src_addr = output->playback_dma + offset;
    config.dst_addr = output->fifo_dma;
    err = rt_dma_chan_config(output->dma_tx, &config);
    if (err)
    {
        return err;
    }

    rt_memset(&transfer, 0, sizeof(transfer));
    transfer.buffer = (void *)write_buf;
    transfer.buffer_len = size;
    transfer.src_addr = config.src_addr;
    transfer.dst_addr = config.dst_addr;
    err = rt_dma_prep_single(output->dma_tx, &transfer);
    if (err)
    {
        return err;
    }
    err = rt_dma_chan_start(output->dma_tx);
    if (err)
    {
        return err;
    }

    output->ops->enable_dma(output, RT_TRUE);
    return size;
}

static void sunxi_audio_output_buffer_info(struct rt_audio_device *audio,
        struct rt_audio_buf_info *info)
{
    struct sunxi_audio_output *output = to_sunxi_audio_output(audio);

    info->buffer = output->playback_buffer;
    info->total_size = SUNXI_AUDIO_BUFFER_SIZE;
    info->block_size = SUNXI_AUDIO_BLOCK_SIZE;
    info->block_count = SUNXI_AUDIO_BUFFER_SIZE / SUNXI_AUDIO_BLOCK_SIZE;
}

const struct rt_audio_ops sunxi_audio_output_audio_ops =
{
    .getcaps = sunxi_audio_output_getcaps,
    .configure = sunxi_audio_output_configure,
    .init = sunxi_audio_output_init,
    .start = sunxi_audio_output_start,
    .stop = sunxi_audio_output_stop_device,
    .transmit = sunxi_audio_output_transmit,
    .buffer_info = sunxi_audio_output_buffer_info,
};

rt_err_t sunxi_audio_output_register(struct sunxi_audio_output *output,
        const char *prefix, void *data)
{
    const char *name;

    rt_dm_dev_set_name_auto(&output->parent.parent, prefix);
    name = rt_dm_dev_get_name(&output->parent.parent);
    if (!name)
    {
        return -RT_EINVAL;
    }

    output->parent.ops = (struct rt_audio_ops *)&sunxi_audio_output_audio_ops;
    return rt_audio_register(&output->parent, name, RT_DEVICE_FLAG_WRONLY,
            data);
}

void sunxi_audio_output_dma_done(struct rt_dma_chan *chan, rt_size_t size)
{
    struct sunxi_audio_output *output = chan->priv;

    if (output->running && size)
    {
        rt_audio_tx_complete(&output->parent);
    }
}

void sunxi_audio_output_release(struct sunxi_audio_output *output)
{
    if (!rt_is_err_or_null(output->dma_tx))
    {
        rt_dma_chan_stop(output->dma_tx);
        rt_dma_chan_release(output->dma_tx);
        output->dma_tx = RT_NULL;
    }
    if (output->playback_buffer)
    {
        rt_dma_free_coherent(output->dev, SUNXI_AUDIO_BUFFER_SIZE,
                output->playback_buffer, output->playback_dma);
        output->playback_buffer = RT_NULL;
    }
}
