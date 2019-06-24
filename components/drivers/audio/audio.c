/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-05-09     Urey      first version
 */

#include <stdio.h>
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <drivers/audio.h>

#include "audio_pipe.h"


#define AUDIO_DEBUG   0
#if AUDIO_DEBUG
#define AUDIO_DBG(...)     printf("[AUDIO]:"),printf(__VA_ARGS__)
#else
#define AUDIO_DBG(...)
#endif

static struct rt_audio_pipe audio_pipe;

static rt_err_t _audio_send_replay_frame(struct rt_audio_device *audio)
{
    rt_err_t result = RT_EOK;
    rt_base_t level;
    struct rt_audio_frame frame;

    RT_ASSERT(audio != RT_NULL);

    //check repaly queue is empty
    if (rt_data_queue_peak(&audio->replay->queue, &frame.data_ptr, &frame.data_size) != RT_EOK)
    {
        AUDIO_DBG("TX queue is empty\n");
        result = -RT_EEMPTY;

        level = rt_hw_interrupt_disable();
        audio->replay->activated = RT_FALSE;
        rt_hw_interrupt_enable(level);

        goto _exit;
    }

    if (audio->ops->transmit != RT_NULL)
    {
        AUDIO_DBG("audio transmit...\n");
        if (audio->ops->transmit(audio, frame.data_ptr, RT_NULL, frame.data_size) != frame.data_size)
        {
            result = -RT_EBUSY;

            goto _exit;
        }
    }

    //pop the head frame...
    rt_data_queue_pop(&audio->replay->queue, &frame.data_ptr, &frame.data_size, RT_WAITING_FOREVER);

    _exit: return result;
}

static rt_err_t _audio_flush_replay_frame(struct rt_audio_device *audio)
{
    struct rt_audio_frame frame;

    if (audio->replay == RT_NULL)
        return -RT_EIO;
    while (rt_data_queue_peak(&audio->replay->queue, &frame.data_ptr, &frame.data_size) == RT_EOK)
    {
        //pop the head frame...
        rt_data_queue_pop(&audio->replay->queue, &frame.data_ptr, &frame.data_size, RT_WAITING_FOREVER);

        /* notify transmitted complete. */
        if (audio->parent.tx_complete != RT_NULL)
            audio->parent.tx_complete(&audio->parent, (void *) frame.data_ptr);
    }

    return RT_EOK;
}

static rt_err_t _audio_dev_init(struct rt_device *dev)
{
    rt_err_t result = RT_EOK;
    struct rt_audio_device *audio;

    RT_ASSERT(dev != RT_NULL);
    audio = (struct rt_audio_device *) dev;

    /* initialize replay & record */
    audio->replay = RT_NULL;
    audio->record = RT_NULL;

    /* apply configuration */
    if (audio->ops->init)
        result = audio->ops->init(audio);

    return result;
}

static rt_err_t _audio_dev_open(struct rt_device *dev, rt_uint16_t oflag)
{
    struct rt_audio_device *audio;

    RT_ASSERT(dev != RT_NULL);
    audio = (struct rt_audio_device *) dev;

    /* check device flag with the open flag */
    if ((oflag & RT_DEVICE_OFLAG_RDONLY) && !(dev->flag & RT_DEVICE_FLAG_RDONLY))
        return -RT_EIO;
    if ((oflag & RT_DEVICE_OFLAG_WRONLY) && !(dev->flag & RT_DEVICE_FLAG_WRONLY))
        return -RT_EIO;

    /* get open flags */
    dev->open_flag = oflag & 0xff;

    /* initialize the Rx/Tx structure according to open flag */
    if (oflag & RT_DEVICE_OFLAG_WRONLY)
    {
        AUDIO_DBG("open audio device ,oflag = %x\n",oflag);
        if (audio->replay == RT_NULL)
        {
            struct rt_audio_replay *replay = (struct rt_audio_replay *) rt_malloc(sizeof(struct rt_audio_replay));

            if (replay == RT_NULL)
            {
                AUDIO_DBG("request memory for replay error\n");
                return -RT_ENOMEM;
            }

            //init queue for audio replay
            rt_data_queue_init(&replay->queue, CFG_AUDIO_REPLAY_QUEUE_COUNT, CFG_AUDIO_REPLAY_QUEUE_COUNT / 2, RT_NULL);

            replay->activated = RT_FALSE;
            audio->replay = replay;
        }

        dev->open_flag |= RT_DEVICE_OFLAG_WRONLY;
    }

    if (oflag & RT_DEVICE_OFLAG_RDONLY)
    {
        if (audio->record == RT_NULL)
        {
            struct rt_audio_record *record = (struct rt_audio_record *) rt_malloc(sizeof(struct rt_audio_record));

            if (record == RT_NULL)
            {
                AUDIO_DBG("request memory for record error\n");
                return -RT_ENOMEM;
            }

            //init pipe for record
            {
                rt_uint8_t *buf = (rt_uint8_t *)rt_malloc(CFG_AUDIO_RECORD_PIPE_SIZE);

                if (buf == RT_NULL)
                {
                    rt_free(record);
                    AUDIO_DBG("request pipe memory error\n");

                    return -RT_ENOMEM;
                }
                
                rt_audio_pipe_init(&audio_pipe, "recpipe", (rt_int32_t)(RT_PIPE_FLAG_FORCE_WR | RT_PIPE_FLAG_BLOCK_RD), buf,
                             CFG_AUDIO_RECORD_PIPE_SIZE);
            }

            record->activated = RT_FALSE;
            audio->record = record;
        }

        //open record pipe
        if (audio->record != RT_NULL)
        {
            rt_device_open(RT_DEVICE(&audio_pipe), RT_DEVICE_OFLAG_RDONLY);
        }

        dev->open_flag |= RT_DEVICE_OFLAG_RDONLY;
    }

    return RT_EOK;
}

static rt_err_t _audio_dev_close(struct rt_device *dev)
{
    struct rt_audio_device *audio;
    RT_ASSERT(dev != RT_NULL);
    audio = (struct rt_audio_device *) dev;

    //shutdown the lower device
    if (audio->ops->shutdown != RT_NULL)
        audio->ops->shutdown(audio);

    if (dev->open_flag & RT_DEVICE_OFLAG_WRONLY)
    {
        struct rt_audio_frame frame;
        //stop replay stream
        audio->ops->stop(audio, AUDIO_STREAM_REPLAY);

        //flush all frame
        while (rt_data_queue_peak(&audio->replay->queue, &frame.data_ptr, &frame.data_size) == RT_EOK)
        {
            //pop the head frame...
            rt_data_queue_pop(&audio->replay->queue, &frame.data_ptr, &frame.data_size, RT_WAITING_FOREVER);

            /* notify transmitted complete. */
            if (audio->parent.tx_complete != RT_NULL)
                audio->parent.tx_complete(&audio->parent, (void *) frame.data_ptr);
        }

        dev->open_flag &= ~RT_DEVICE_OFLAG_WRONLY;
    }

    if (dev->open_flag & RT_DEVICE_OFLAG_RDONLY)
    {
        //stop record stream
        audio->ops->stop(audio, AUDIO_STREAM_RECORD);

        //close record pipe
        if (audio->record != RT_NULL)
            rt_device_close(RT_DEVICE(&audio_pipe));

        dev->open_flag &= ~RT_DEVICE_OFLAG_RDONLY;
    }

    return RT_EOK;
}

static rt_size_t _audio_dev_read(struct rt_device *dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    struct rt_audio_device *audio;
    RT_ASSERT(dev != RT_NULL);
    audio = (struct rt_audio_device *) dev;
    if (!(dev->open_flag & RT_DEVICE_OFLAG_RDONLY) || (audio->record == RT_NULL))
        return 0;

    return rt_device_read(RT_DEVICE(&audio_pipe), pos, buffer, size);
}

static rt_size_t _audio_dev_write(struct rt_device *dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_err_t result = RT_EOK;
    rt_base_t level;
    struct rt_audio_device *audio;

    RT_ASSERT(dev != RT_NULL);
    audio = (struct rt_audio_device *) dev;

    if (!(dev->open_flag & RT_DEVICE_OFLAG_WRONLY) || (audio->replay == RT_NULL))
        return 0;

    AUDIO_DBG("audio write : pos = %d,buffer = %x,size = %d\n",pos,(rt_uint32_t)buffer,size);
    //push a new frame to tx queue
    {
        result = rt_data_queue_push(&audio->replay->queue, buffer, size,
        RT_WAITING_FOREVER);
        if (result != RT_EOK)
        {
            AUDIO_DBG("TX frame queue push error\n");
            rt_set_errno(-RT_EFULL);
            return 0;
        }
    }

    //check tx state...
    level = rt_hw_interrupt_disable();
    if (audio->replay->activated != RT_TRUE)
    {
        audio->replay->activated = RT_TRUE;
        rt_hw_interrupt_enable(level);

        _audio_send_replay_frame(audio);
    }
    else
    {
        rt_hw_interrupt_enable(level);
    }

    return size;
}

static rt_err_t _audio_dev_control(struct rt_device *dev, int cmd, void *args)
{
    rt_err_t result = RT_EOK;
    struct rt_audio_device *audio;
    RT_ASSERT(dev != RT_NULL);
    audio = (struct rt_audio_device *) dev;

    //dev stat...
    switch (cmd)
    {
        case AUDIO_CTL_GETCAPS:
        {
            struct rt_audio_caps *caps = (struct rt_audio_caps *) args;

            AUDIO_DBG("AUDIO_CTL_GETCAPS: main_type = %d,sub_type = %d\n",caps->main_type,caps->sub_type);
            if (audio->ops->getcaps != RT_NULL)
            {
                result = audio->ops->getcaps(audio, caps);
            }
        }
        break;
        case AUDIO_CTL_CONFIGURE:
        {
            struct rt_audio_caps *caps = (struct rt_audio_caps *) args;

            AUDIO_DBG("AUDIO_CTL_CONFIGURE: main_type = %d,sub_type = %d\n",caps->main_type,caps->sub_type);
            if (audio->ops->configure != RT_NULL)
            {
                result = audio->ops->configure(audio, caps);
            }
        }

        break;
        case AUDIO_CTL_SHUTDOWN:
        {
            AUDIO_DBG("AUDIO_CTL_SHUTDOWN\n");

            if (audio->ops->shutdown != RT_NULL)
                result = audio->ops->shutdown(audio);

            //flush replay frame...
            _audio_flush_replay_frame(audio);
        }
        break;

        case AUDIO_CTL_START:
        {
            int stream = *(int *) args;

            AUDIO_DBG("AUDIO_CTL_START: stream = %d\n",stream);
            if (audio->ops->start != RT_NULL)
                result = audio->ops->start(audio, stream);
        }
        break;
        case AUDIO_CTL_STOP:
        {
            int stream = *(int *) args;

            AUDIO_DBG("AUDIO_CTL_STOP: stream = %d\n",stream);
            if (audio->ops->start != RT_NULL)
                result = audio->ops->stop(audio, stream);

            if (stream == AUDIO_STREAM_REPLAY)
            {
                _audio_flush_replay_frame(audio);
            }
        }
        break;
        case AUDIO_CTL_PAUSE:
        {
            int stream = *(int *) args;

            AUDIO_DBG("AUDIO_CTL_PAUSE: stream = %d\n",stream);
            if (audio->ops->start != RT_NULL)
                result = audio->ops->suspend(audio, stream);
        }
        break;
        case AUDIO_CTL_RESUME:
        {
            int stream = *(int *) args;

            AUDIO_DBG("AUDIO_CTL_RESUME: stream = %d\n",stream);
            if (audio->ops->start != RT_NULL)
                result = audio->ops->resume(audio, stream);

            //resume tx frame...
            if (stream == AUDIO_STREAM_REPLAY)
                _audio_send_replay_frame(audio);
        }
        break;
        case AUDIO_CTL_ALLOCBUFFER:
        {
            struct rt_audio_buf_desc *desc = (struct rt_audio_buf_desc *) args;

            if (desc)
            {
                desc->data_size = AUDIO_DEVICE_DECODE_MP_BLOCK_SZ * 2;
                desc->data_ptr = (rt_uint8_t *)rt_mp_alloc(&audio->mp, RT_WAITING_FOREVER);

                result = RT_EOK;
            }
            else result = -RT_EIO;
        }
        break;
        case AUDIO_CTL_FREEBUFFER:
        {
            rt_uint8_t *data_ptr = (rt_uint8_t *) args;
            if (data_ptr)
                rt_mp_free(data_ptr);
        }
        break;
        default:
            result = audio->ops->control(audio, cmd, args);
        break;
    }

    return result;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops audio_ops =
{
    _audio_dev_init,
    _audio_dev_open,
    _audio_dev_close,
    _audio_dev_read,
    _audio_dev_write,
    _audio_dev_control
};
#endif

rt_err_t rt_audio_register(struct rt_audio_device *audio, const char *name, rt_uint32_t flag, void *data)
{
    struct rt_device *device;
    RT_ASSERT(audio != RT_NULL);
    device = &(audio->parent);

    device->type = RT_Device_Class_Sound;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->ops  = &audio_ops;
#else
    device->init    = _audio_dev_init;
    device->open    = _audio_dev_open;
    device->close   = _audio_dev_close;
    device->read    = _audio_dev_read;
    device->write   = _audio_dev_write;
    device->control = _audio_dev_control;
#endif
    device->user_data = data;

    //init memory pool for replay
    {
        rt_uint8_t *mempool = (rt_uint8_t *)rt_malloc(AUDIO_DEVICE_DECODE_MP_SZ);
        rt_mp_init(&audio->mp, "adu_mp", mempool, AUDIO_DEVICE_DECODE_MP_SZ,
        AUDIO_DEVICE_DECODE_MP_BLOCK_SZ * 2);
    }

    /* register a character device */
    return rt_device_register(device, name, flag | RT_DEVICE_FLAG_REMOVABLE);
}

int rt_audio_samplerate_to_speed(rt_uint32_t bitValue)
{
    int speed = 0;
    switch (bitValue)
    {
        case AUDIO_SAMP_RATE_8K:
            speed = 8000;
        break;
        case AUDIO_SAMP_RATE_11K:
            speed = 11052;
        break;
        case AUDIO_SAMP_RATE_16K:
            speed = 16000;
        break;
        case AUDIO_SAMP_RATE_22K:
            speed = 22050;
        break;
        case AUDIO_SAMP_RATE_32K:
            speed = 32000;
        break;
        case AUDIO_SAMP_RATE_44K:
            speed = 44100;
        break;
        case AUDIO_SAMP_RATE_48K:
            speed = 48000;
        break;
        case AUDIO_SAMP_RATE_96K:
            speed = 96000;
        break;
        case AUDIO_SAMP_RATE_128K:
            speed = 128000;
        break;
        case AUDIO_SAMP_RATE_160K:
            speed = 160000;
        break;
        case AUDIO_SAMP_RATE_172K:
            speed = 176400;
        break;
        case AUDIO_SAMP_RATE_192K:
            speed = 192000;
        break;
        default:

        break;
    }

    return speed;
}

rt_uint32_t rt_audio_format_to_bits(rt_uint32_t format)
{
    switch (format)
    {
        case AUDIO_FMT_PCM_U8:
        case AUDIO_FMT_PCM_S8:
            return 8;
        case AUDIO_FMT_PCM_S16_LE:
        case AUDIO_FMT_PCM_S16_BE:
        case AUDIO_FMT_PCM_U16_LE:
        case AUDIO_FMT_PCM_U16_BE:
            return 16;
        default:
            return 32;
    };
}

void rt_audio_tx_complete(struct rt_audio_device *audio, rt_uint8_t *pbuf)
{
    rt_err_t result;
    AUDIO_DBG("audio tx complete ptr=%x...\n",(rt_uint32_t)pbuf);

    //try to send all frame
    do
    {
        result = _audio_send_replay_frame(audio);
    } while (result == RT_EOK);

    /* notify transmitted complete. */
    if (audio->parent.tx_complete != RT_NULL)
        audio->parent.tx_complete(&audio->parent, (void *) pbuf);
}

void rt_audio_rx_done(struct rt_audio_device *audio, rt_uint8_t *pbuf, rt_size_t len)
{
    //save data to record pipe
    rt_device_write(RT_DEVICE(RT_DEVICE(&audio_pipe)), 0, pbuf, len);

    /* invoke callback */
    if (audio->parent.rx_indicate != RT_NULL)
        audio->parent.rx_indicate(&audio->parent, len);
}

