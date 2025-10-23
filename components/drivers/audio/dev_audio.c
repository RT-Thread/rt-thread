/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-05-09     Urey         first version
 * 2019-07-09     Zero-Free    improve device ops interface and data flows
 * 2025-03-04     wumingzi     add doxygen comments.
 */

#include <stdio.h>
#include <string.h>
#include <rthw.h>
#include <rtdevice.h>

#define DBG_TAG              "audio"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

#ifndef MIN
#define MIN(a, b)         ((a) < (b) ? (a) : (b))
#endif

/**
 * @addtogroup group_drivers_audio
 */

/** @{ */

enum
{
    REPLAY_EVT_NONE  = 0x00,
    REPLAY_EVT_START = 0x01,
    REPLAY_EVT_STOP  = 0x02,
};

/**
 * @brief Send a replay frame to the audio hardware device
 *
 * This function handles sending audio data from the memory queue to the hardware buffer for playback.
 * If there is no data available in the queue, it sends zero frames. Otherwise, it copies data from the memory pool
 * to the hardware device FIFO and manages the read index and position accordingly.
 *
 * @param[in] audio pointer to the audio device structure
 *
 * @return error code, RT_EOK is successful otherwise means failure
 *
 * @note This function may temporarily disable interrupts or perform time-consuming operations like memcpy,
 *       which could affect system responsiveness
 */
static rt_err_t _audio_send_replay_frame(struct rt_audio_device *audio)
{
    rt_err_t result = RT_EOK;
    rt_uint8_t *data;
    rt_size_t dst_size, src_size;
    rt_uint16_t position, remain_bytes = 0, index = 0;
    struct rt_audio_buf_info *buf_info;

    RT_ASSERT(audio != RT_NULL);

    buf_info = &audio->replay->buf_info;
    /* save current pos */
    position = audio->replay->pos;
    dst_size = buf_info->block_size;

    /* check replay queue is empty */
    if (rt_data_queue_peek(&audio->replay->queue, (const void **)&data, &src_size) != RT_EOK)
    {
        /* ack stop event */
        if (audio->replay->event & REPLAY_EVT_STOP)
            rt_completion_done(&audio->replay->cmp);

        /* send zero frames */
        rt_memset(&buf_info->buffer[audio->replay->pos], 0, dst_size);

        audio->replay->pos += dst_size;
        audio->replay->pos %= buf_info->total_size;
    }
    else
    {
        rt_memset(&buf_info->buffer[audio->replay->pos], 0, dst_size);

        /* copy data from memory pool to hardware device fifo */
        while (index < dst_size)
        {
            result = rt_data_queue_peek(&audio->replay->queue, (const void **)&data, &src_size);
            if (result != RT_EOK)
            {
                LOG_D("under run %d, remain %d", audio->replay->pos, remain_bytes);
                audio->replay->pos -= remain_bytes;
                audio->replay->pos += dst_size;
                audio->replay->pos %= buf_info->total_size;
                audio->replay->read_index = 0;
                result = -RT_EEMPTY;
                break;
            }

            remain_bytes = MIN((dst_size - index), (src_size - audio->replay->read_index));
            rt_memcpy(&buf_info->buffer[audio->replay->pos],
                   &data[audio->replay->read_index], remain_bytes);

            index += remain_bytes;
            audio->replay->read_index += remain_bytes;
            audio->replay->pos += remain_bytes;
            audio->replay->pos %= buf_info->total_size;

            if (audio->replay->read_index == src_size)
            {
                /* free memory */
                audio->replay->read_index = 0;
                rt_data_queue_pop(&audio->replay->queue, (const void **)&data, &src_size, RT_WAITING_NO);
                rt_mp_free(data);

                /* notify transmitted complete. */
                if (audio->parent.tx_complete != RT_NULL)
                    audio->parent.tx_complete(&audio->parent, (void *)data);
            }
        }
    }

    if (audio->ops->transmit != RT_NULL)
    {
        if (audio->ops->transmit(audio, &buf_info->buffer[position], RT_NULL, dst_size) != dst_size)
            result = -RT_ERROR;
    }

    return result;
}

/**
 * @brief Write replay frame into audio device replay queue
 *
 * @param[in] audio pointer to audio device
 *
 * @return error code, RT_EOK is successful otherwise means failure
 */
static rt_err_t _audio_flush_replay_frame(struct rt_audio_device *audio)
{
    rt_err_t result = RT_EOK;

    if (audio->replay->write_index)
    {
        result = rt_data_queue_push(&audio->replay->queue,
                                    (const void **)audio->replay->write_data,
                                    audio->replay->write_index,
                                    RT_WAITING_FOREVER);

        audio->replay->write_index = 0;
    }

    return result;
}

/**
 * @brief Replay audio
 *
 * @param[in] audio pointer to audio device
 *
 * @return error code, RT_EOK is successful otherwise means failure
 */
static rt_err_t _aduio_replay_start(struct rt_audio_device *audio)
{
    rt_err_t result = RT_EOK;

    if (audio->replay->activated != RT_TRUE)
    {
        /* start playback hardware device */
        if (audio->ops->start)
            result = audio->ops->start(audio, AUDIO_STREAM_REPLAY);

        audio->replay->activated = RT_TRUE;
        LOG_D("start audio replay device");
    }

    return result;
}

/**
 * @brief Stop replaying audio
 *
 * When audio->replay->queue is empty and the audio->replay->event was set REPLAY_EVT_STOP,
 * _audio_send_replay_frame will send completion to stop replaying audio.
 *
 * @param[in] audio pointer to audio device
 *
 * @return error code, RT_EOK is successful otherwise means failure
 */
static rt_err_t _aduio_replay_stop(struct rt_audio_device *audio)
{
    rt_err_t result = RT_EOK;

    if (audio->replay->activated == RT_TRUE)
    {
        /* flush replay remian frames */
        _audio_flush_replay_frame(audio);

        /* notify irq(or thread) to stop the data transmission */
        audio->replay->event |= REPLAY_EVT_STOP;

        /* waiting for the remaining data transfer to complete */
        rt_completion_init(&audio->replay->cmp);
        rt_completion_wait(&audio->replay->cmp, RT_WAITING_FOREVER);
        audio->replay->event &= ~REPLAY_EVT_STOP;

        /* stop playback hardware device */
        if (audio->ops->stop)
            result = audio->ops->stop(audio, AUDIO_STREAM_REPLAY);

        audio->replay->activated = RT_FALSE;
        LOG_D("stop audio replay device");
    }

    return result;
}

/**
 * @brief Open audio pipe and start to record audio
 *
 * @param[in] audio pointer to audio device
 *
 * @return error code, RT_EOK is successful otherwise means failure
 */
static rt_err_t _audio_record_start(struct rt_audio_device *audio)
{
    rt_err_t result = RT_EOK;

    if (audio->record->activated != RT_TRUE)
    {
        /* open audio record pipe */
        rt_device_open(RT_DEVICE(&audio->record->pipe), RT_DEVICE_OFLAG_RDONLY);

        /* start record hardware device */
        if (audio->ops->start)
            result = audio->ops->start(audio, AUDIO_STREAM_RECORD);

        audio->record->activated = RT_TRUE;
        LOG_D("start audio record device");
    }

    return result;
}

/**
 * @brief stop recording audio and closeaudio pipe
 *
 * @param[in] audio pointer to audio device
 *
 * @return error code, RT_EOK is successful otherwise means failure
 */
static rt_err_t _audio_record_stop(struct rt_audio_device *audio)
{
    rt_err_t result = RT_EOK;

    if (audio->record->activated == RT_TRUE)
    {
        /* stop record hardware device */
        if (audio->ops->stop)
            result = audio->ops->stop(audio, AUDIO_STREAM_RECORD);

        /* close audio record pipe */
        rt_device_close(RT_DEVICE(&audio->record->pipe));

        audio->record->activated = RT_FALSE;
        LOG_D("stop audio record device");
    }

    return result;
}

/**
 * @brief Init audio pipe
 *
 * In kernel, this function will set replay or record function depending on device
 * flag. For replaying, it will malloc for managing audio replay struct meanwhile
 * creating mempool and dataqueue.For recording, it will creat audio pipe and
 * it's ringbuffer.
 * In driver, this function will only execute hardware driver initialization code
 * and get hardware buffer infomation.
 *
 * @param[in] dev pointer to audio device
 *
 * @return error code, RT_EOK is successful otherwise means failure
 */
static rt_err_t _audio_dev_init(struct rt_device *dev)
{
    rt_err_t result = RT_EOK;
    struct rt_audio_device *audio;

    RT_ASSERT(dev != RT_NULL);
    audio = (struct rt_audio_device *) dev;

    /* initialize replay & record */
    audio->replay = RT_NULL;
    audio->record = RT_NULL;

    /* initialize replay */
    if (dev->flag & RT_DEVICE_FLAG_WRONLY)
    {
        struct rt_audio_replay *replay = (struct rt_audio_replay *) rt_malloc(sizeof(struct rt_audio_replay));

        if (replay == RT_NULL)
            return -RT_ENOMEM;
        rt_memset(replay, 0, sizeof(struct rt_audio_replay));

        /* init memory pool for replay */
        replay->mp = rt_mp_create("adu_mp", RT_AUDIO_REPLAY_MP_BLOCK_COUNT, RT_AUDIO_REPLAY_MP_BLOCK_SIZE);
        if (replay->mp == RT_NULL)
        {
            rt_free(replay);
            LOG_E("create memory pool for replay failed");
            return -RT_ENOMEM;
        }

        /* init queue for audio replay */
        rt_data_queue_init(&replay->queue, CFG_AUDIO_REPLAY_QUEUE_COUNT, 0, RT_NULL);

        /* init mutex lock for audio replay */
        rt_mutex_init(&replay->lock, "replay", RT_IPC_FLAG_PRIO);

        replay->activated = RT_FALSE;
        audio->replay = replay;
    }

    /* initialize record */
    if (dev->flag & RT_DEVICE_FLAG_RDONLY)
    {
        struct rt_audio_record *record = (struct rt_audio_record *) rt_malloc(sizeof(struct rt_audio_record));
        rt_uint8_t *buffer;

        if (record == RT_NULL)
            return -RT_ENOMEM;
        rt_memset(record, 0, sizeof(struct rt_audio_record));

        /* init pipe for record*/
        buffer = rt_malloc(RT_AUDIO_RECORD_PIPE_SIZE);
        if (buffer == RT_NULL)
        {
            rt_free(record);
            LOG_E("malloc memory for for record pipe failed");
            return -RT_ENOMEM;
        }
        rt_audio_pipe_init(&record->pipe, "record",
                           (rt_int32_t)(RT_PIPE_FLAG_FORCE_WR | RT_PIPE_FLAG_BLOCK_RD),
                           buffer,
                           RT_AUDIO_RECORD_PIPE_SIZE);

        record->activated = RT_FALSE;
        audio->record = record;
    }

    /* initialize hardware configuration */
    if (audio->ops->init)
        audio->ops->init(audio);

    /* get replay buffer information */
    if (audio->ops->buffer_info)
        audio->ops->buffer_info(audio, &audio->replay->buf_info);

    return result;
}

/**
 * @brief Start record audio
 *
 * @param[in] dev pointer to audio device
 *
 * @param[in] oflag device flag
 *
 * @return error code, RT_EOK is successful otherwise means failure
 */
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
        if (audio->replay->activated != RT_TRUE)
        {
            LOG_D("open audio replay device, oflag = %x\n", oflag);
            audio->replay->write_index = 0;
            audio->replay->read_index = 0;
            audio->replay->pos = 0;
            audio->replay->event = REPLAY_EVT_NONE;
        }
        dev->open_flag |= RT_DEVICE_OFLAG_WRONLY;
    }

    if (oflag & RT_DEVICE_OFLAG_RDONLY)
    {
        /* open record pipe */
        if (audio->record->activated != RT_TRUE)
        {
            LOG_D("open audio record device ,oflag = %x\n", oflag);

            _audio_record_start(audio);
            audio->record->activated = RT_TRUE;
        }
        dev->open_flag |= RT_DEVICE_OFLAG_RDONLY;
    }

    return RT_EOK;
}

/**
 * @brief Stop record, replay or both.
 *
 * @param[in] dev pointer to audio device
 *
 * @return useless param
 */
static rt_err_t _audio_dev_close(struct rt_device *dev)
{
    struct rt_audio_device *audio;
    RT_ASSERT(dev != RT_NULL);
    audio = (struct rt_audio_device *) dev;

    if (dev->open_flag & RT_DEVICE_OFLAG_WRONLY)
    {
        /* stop replay stream */
        _aduio_replay_stop(audio);
        dev->open_flag &= ~RT_DEVICE_OFLAG_WRONLY;
    }

    if (dev->open_flag & RT_DEVICE_OFLAG_RDONLY)
    {
        /* stop record stream */
        _audio_record_stop(audio);
        dev->open_flag &= ~RT_DEVICE_OFLAG_RDONLY;
    }

    return RT_EOK;
}

/**
 * @brief Read audio device
 *
 * @param[in] dev pointer to device
 *
 * @param[in] pos position when reading
 *
 * @param[out] buffer a data buffer to save the read data
 *
 * @param[in] size buffer size
 *
 * @return the actually read size on successfully, otherwise 0 will be returned.
 *
 * @note
 */
static rt_ssize_t _audio_dev_read(struct rt_device *dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    struct rt_audio_device *audio;
    RT_ASSERT(dev != RT_NULL);
    audio = (struct rt_audio_device *) dev;

    if (!(dev->open_flag & RT_DEVICE_OFLAG_RDONLY) || (audio->record == RT_NULL))
        return 0;

    return rt_device_read(RT_DEVICE(&audio->record->pipe), pos, buffer, size);
}

/**
 * @brief Write data into replay data queue and replay it
 *
 * @param[in] dev pointer to device
 *
 * @param[in] pos useless param
 *
 * @param[in] buffer a data buffer to be written into data queue
 *
 * @param[in] size buffer size
 *
 * @return the actually read size on successfully, otherwise 0 will be returned.
 *
 * @note This function will take mutex.
 */
static rt_ssize_t _audio_dev_write(struct rt_device *dev, rt_off_t pos, const void *buffer, rt_size_t size)
{

    struct rt_audio_device *audio;
    rt_uint8_t *ptr;
    rt_uint16_t block_size, remain_bytes, index = 0;

    RT_ASSERT(dev != RT_NULL);
    audio = (struct rt_audio_device *) dev;

    if (!(dev->open_flag & RT_DEVICE_OFLAG_WRONLY) || (audio->replay == RT_NULL))
        return 0;

    /* push a new frame to replay data queue */
    ptr = (rt_uint8_t *)buffer;
    block_size = RT_AUDIO_REPLAY_MP_BLOCK_SIZE;

    rt_mutex_take(&audio->replay->lock, RT_WAITING_FOREVER);
    while (index < size)
    {
        /* request buffer from replay memory pool */
        if (audio->replay->write_index % block_size == 0)
        {
            audio->replay->write_data = rt_mp_alloc(audio->replay->mp, RT_WAITING_FOREVER);
            rt_memset(audio->replay->write_data, 0, block_size);
        }

        /* copy data to replay memory pool */
        remain_bytes = MIN((block_size - audio->replay->write_index), (size - index));
        rt_memcpy(&audio->replay->write_data[audio->replay->write_index], &ptr[index], remain_bytes);

        index += remain_bytes;
        audio->replay->write_index += remain_bytes;
        audio->replay->write_index %= block_size;

        if (audio->replay->write_index == 0)
        {
            rt_data_queue_push(&audio->replay->queue,
                               audio->replay->write_data,
                               block_size,
                               RT_WAITING_FOREVER);
        }
    }
    rt_mutex_release(&audio->replay->lock);

    /* check replay state */
    if (audio->replay->activated != RT_TRUE)
    {
        _aduio_replay_start(audio);
        audio->replay->activated = RT_TRUE;
    }

    return index;
}

/**
 * @brief Control audio device
 *
 * @param[in] dev pointer to device
 *
 * @param[in] cmd audio cmd, it can be one of value in @ref group_audio_control
 *
 * @param[in] args command argument
 *
 * @return error code, RT_EOK is successful otherwise means failure
 */
static rt_err_t _audio_dev_control(struct rt_device *dev, int cmd, void *args)
{
    rt_err_t result = RT_EOK;
    struct rt_audio_device *audio;
    RT_ASSERT(dev != RT_NULL);
    audio = (struct rt_audio_device *) dev;

    /* dev stat...*/
    switch (cmd)
    {
    case AUDIO_CTL_GETCAPS:
    {
        struct rt_audio_caps *caps = (struct rt_audio_caps *) args;

        LOG_D("AUDIO_CTL_GETCAPS: main_type = %d,sub_type = %d", caps->main_type, caps->sub_type);
        if (audio->ops->getcaps != RT_NULL)
        {
            result = audio->ops->getcaps(audio, caps);
        }

        break;
    }

    case AUDIO_CTL_CONFIGURE:
    {
        struct rt_audio_caps *caps = (struct rt_audio_caps *) args;

        LOG_D("AUDIO_CTL_CONFIGURE: main_type = %d,sub_type = %d", caps->main_type, caps->sub_type);
        if (audio->ops->configure != RT_NULL)
        {
            result = audio->ops->configure(audio, caps);
        }

        break;
    }

    case AUDIO_CTL_START:
    {
        int stream = *(int *) args;

        LOG_D("AUDIO_CTL_START: stream = %d", stream);
        if (stream == AUDIO_STREAM_REPLAY)
        {
            result = _aduio_replay_start(audio);
        }
        else
        {
            result = _audio_record_start(audio);
        }

        break;
    }

    case AUDIO_CTL_STOP:
    {
        int stream = *(int *) args;

        LOG_D("AUDIO_CTL_STOP: stream = %d", stream);
        if (stream == AUDIO_STREAM_REPLAY)
        {
            result = _aduio_replay_stop(audio);
        }
        else
        {
            result = _audio_record_stop(audio);
        }

        break;
    }

    default:
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

/**
 * @brief Register and initialize audio device
 *
 * @param[in] audio pointer to audio deive
 *
 * @param[in] name device name
 *
 * @param[in] flag device flags
 *
 * @param[in] data user data
 *
 * @return error code, RT_EOK is successful otherwise means failure
 */
rt_err_t rt_audio_register(struct rt_audio_device *audio, const char *name, rt_uint32_t flag, void *data)
{
    rt_err_t result = RT_EOK;
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

    /* register a character device */
    result = rt_device_register(device, name, flag | RT_DEVICE_FLAG_REMOVABLE);

    /* initialize audio device */
    if (result == RT_EOK)
        result = rt_device_init(device);

    return result;
}

/**
 * @brief Set audio sample rate
 *
 * @param[in] bitValue audio sample rate, it can be one of value in @ref group_audio_samp_rates
 *
 * @return speed has been set
 */
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

/**
 * @brief Send a replay frame to the audio hardware device
 *
 * See _audio_send_replay_frame for details
 *
 * @param[in] audio pointer to audio device
 */
void rt_audio_tx_complete(struct rt_audio_device *audio)
{
    /* try to send next frame */
    _audio_send_replay_frame(audio);
}

/**
 * @brief Receive recording from audio device
 *
 * @param[in] audio pointer to audio device
 *
 * @param[in] pbuf pointer ro data to be received
 *
 * @param[in] len buffer size
 */
void rt_audio_rx_done(struct rt_audio_device *audio, rt_uint8_t *pbuf, rt_size_t len)
{
    /* save data to record pipe */
    rt_device_write(RT_DEVICE(&audio->record->pipe), 0, pbuf, len);

    /* invoke callback */
    if (audio->parent.rx_indicate != RT_NULL)
        audio->parent.rx_indicate(&audio->parent, len);
}

/** @} group_drivers_audio */