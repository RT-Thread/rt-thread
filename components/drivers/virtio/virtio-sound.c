/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 * 2026-06-10     GuEe-GUI     complete driver per VirtIO sound 1.2
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "virtio.dev.sound"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "virtio_config/virtio-sound.h"
#include "virtio_internal.h"

#define QUEUE_CONTROL           0
#define QUEUE_EVENT             1
#define QUEUE_TX                2
#define QUEUE_RX                3

#ifndef VSOUND_PERIOD_BYTES
#define VSOUND_PERIOD_BYTES     RT_AUDIO_REPLAY_MP_BLOCK_SIZE
#endif

#ifndef VSOUND_PERIOD_COUNT
#define VSOUND_PERIOD_COUNT     2
#endif

#ifndef VSOUND_RECYCLE_MAX
#define VSOUND_RECYCLE_MAX      32
#endif

#ifndef VSOUND_REPLAY_POLL_MS
#define VSOUND_REPLAY_POLL_MS   2
#endif


static struct virtio_sound *virtio_sound_replay_notify_dev;

struct virtio_sound_jack
{
    rt_uint32_t nid;
    rt_uint32_t features;
    rt_uint32_t defconf;
    rt_uint32_t caps;
    rt_bool_t connected;
    int type;
};

struct virtio_sound_pcm_stream
{
    rt_uint32_t nid;
    rt_uint32_t sid;
    rt_uint32_t features;
    rt_uint64_t formats;
    rt_uint64_t rates;
    rt_uint8_t direction;
    rt_uint8_t channels_min;
    rt_uint8_t channels_max;
};

struct virtio_sound_ctl_elem
{
    rt_uint32_t id;
    rt_uint32_t role;
    rt_uint32_t type;
    rt_uint32_t count;
    rt_uint32_t min;
    rt_uint32_t max;
};

struct virtio_sound_io_msg
{
    struct virtio_snd_pcm_xfer xfer;
    struct virtio_snd_pcm_status status;
    rt_uint32_t period;
    rt_bool_t pending;
    rt_uint8_t *mp_block;
};

struct virtio_sound_pcm_runtime
{
    struct virtio_sound_pcm_stream *stream;
    rt_uint8_t *buffer;
    rt_uint32_t buffer_bytes;
    rt_uint32_t period_bytes;
    rt_uint32_t period_count;
    struct virtio_sound_io_msg *msgs;
    rt_uint8_t format;
    rt_uint8_t rate;
    rt_uint8_t channels;
    rt_bool_t active;
    rt_bool_t params_set;
};

struct virtio_sound
{
    struct rt_audio_device parent;
    struct rt_audio_configure audio_config;

    struct rt_virtio_device *vdev;

    struct rt_virtqueue *vqs[4];

    struct virtio_snd_event *event_msgs;
    rt_uint32_t event_msgs_nr;

    struct rt_completion ctl_done;
    struct rt_spinlock ctl_lock;

    rt_bool_t playback_mute;
    rt_bool_t capture_mute;
    rt_int32_t playback_volume;
    rt_int32_t capture_volume;

    rt_uint32_t jacks_nr;
    rt_uint32_t chmaps_nr;
    rt_uint32_t substreams_nr;
    rt_uint32_t controls_nr;
    struct virtio_sound_jack *jacks;
    struct virtio_sound_pcm_stream *substreams;
    struct virtio_snd_chmap_info *chmaps;

    struct virtio_sound_pcm_runtime playback;
    struct virtio_sound_pcm_runtime capture;

    struct rt_spinlock tx_lock;
    struct rt_spinlock rx_lock;

    struct rt_semaphore replay_sem;
    struct rt_thread *replay_thread;
    rt_bool_t replay_thread_exit;
    struct rt_mutex replay_push_lock;
};

#define raw_to_virtio_sound(raw) rt_container_of(raw, struct virtio_sound, parent)

static rt_uint32_t virtio_sound_pcm_pending(struct virtio_sound_pcm_runtime *rt);
static rt_err_t virtio_sound_pcm_submit_tx(struct virtio_sound *vsound,
        struct virtio_sound_pcm_runtime *rt, rt_uint32_t period);
static rt_err_t virtio_sound_pcm_submit_rx(struct virtio_sound *vsound,
        struct virtio_sound_pcm_runtime *rt, rt_uint32_t period);

static void virtio_sound_schedule_tx_complete(struct virtio_sound *vsound);
static rt_uint32_t virtio_sound_vq_recycle(struct rt_virtqueue *vq,
        struct virtio_sound *vsound,
        struct virtio_sound_pcm_runtime *rt,
        struct rt_spinlock *lock,
        rt_bool_t is_playback);
static rt_uint32_t virtio_sound_vq_drain_used(struct rt_virtqueue *vq,
        struct virtio_sound *vsound,
        struct virtio_sound_pcm_runtime *rt,
        struct rt_spinlock *lock,
        rt_bool_t is_playback);

static rt_int32_t virtio_sound_find_free_period(struct virtio_sound_pcm_runtime *rt)
{
    if (!rt->msgs)
    {
        return -1;
    }

    for (rt_uint32_t i = 0; i < rt->period_count; ++i)
    {
        if (!rt->msgs[i].pending)
        {
            return (rt_int32_t)i;
        }
    }

    return -1;
}

static void virtio_sound_replay_reset_msgs(struct virtio_sound_pcm_runtime *rt)
{
    if (!rt || !rt->msgs)
    {
        return;
    }

    for (rt_uint32_t i = 0; i < rt->period_count; ++i)
    {
        rt->msgs[i].pending = RT_FALSE;
        rt->msgs[i].mp_block = RT_NULL;
    }
}

/*
 * dev_audio _audio_send_replay_frame() loops while (index < dst_size) with
 * remain_bytes = MIN(..., src_size - read_index).  When read_index is stale
 * and equals src_size, remain_bytes stays 0 and the loop never advances.
 */
static void virtio_sound_replay_queue_reset(struct virtio_sound *vsound)
{
    struct rt_audio_replay *replay = vsound->parent.replay;

    if (!replay)
    {
        return;
    }

    replay->read_index = 0;
    replay->pos = 0;
    replay->write_index = 0;
}

static void virtio_sound_replay_drain_tx(struct virtio_sound *vsound)
{
    struct rt_virtqueue *vq = vsound->vqs[QUEUE_TX];

    if (vq)
    {
        virtio_sound_vq_drain_used(vq, vsound, &vsound->playback,
                &vsound->tx_lock, RT_TRUE);
    }
}

static rt_bool_t virtio_sound_push_one_period(struct virtio_sound *vsound)
{
    struct rt_audio_device *audio = &vsound->parent;
    struct virtio_sound_pcm_runtime *rt = &vsound->playback;
    struct virtio_sound_io_msg *msg;
    rt_int32_t period;
    rt_uint8_t *data;
    rt_size_t src_size;
    rt_err_t err;

    if (!audio->replay || !rt->active || !rt->buffer || !rt->msgs)
    {
        return RT_FALSE;
    }

    period = virtio_sound_find_free_period(rt);
    if (period < 0)
    {
        return RT_FALSE;
    }

    err = rt_data_queue_peek(&audio->replay->queue, (const void **)&data, &src_size);
    if (err != RT_EOK || src_size == 0 || src_size < rt->period_bytes)
    {
        return RT_FALSE;
    }

    rt_memcpy(rt->buffer + period * rt->period_bytes, data, rt->period_bytes);

    err = rt_data_queue_pop(&audio->replay->queue, (const void **)&data, &src_size,
            RT_WAITING_NO);
    if (err != RT_EOK)
    {
        return RT_FALSE;
    }

    msg = &rt->msgs[period];
    msg->mp_block = data;


    if (virtio_sound_pcm_submit_tx(vsound, rt, (rt_uint32_t)period) != RT_EOK)
    {
        msg->mp_block = RT_NULL;
        rt_mp_free(data);
        return RT_FALSE;
    }

    return RT_TRUE;
}

static void virtio_sound_replay_push(struct virtio_sound *vsound)
{
    struct rt_audio_device *audio = &vsound->parent;
    struct virtio_sound_pcm_runtime *rt = &vsound->playback;
    rt_bool_t rescheduled = RT_FALSE;

    if (!rt->active || !audio->replay || !rt->buffer || !rt->msgs)
    {
        return;
    }

    if (rt_interrupt_get_nest() != 0)
    {
        virtio_sound_schedule_tx_complete(vsound);
        return;
    }

    rt_mutex_take(&vsound->replay_push_lock, RT_WAITING_FOREVER);

    virtio_sound_replay_drain_tx(vsound);

    while (rt->active)
    {
        if (rt_data_queue_len(&audio->replay->queue) == 0)
        {
            break;
        }

        if (virtio_sound_find_free_period(rt) < 0)
        {
            break;
        }


        if (!virtio_sound_push_one_period(vsound))
        {
            break;
        }

        virtio_sound_replay_drain_tx(vsound);
    }

    if (rt->active && audio->replay &&
            rt_data_queue_len(&audio->replay->queue) > 0 &&
            virtio_sound_find_free_period(rt) >= 0)
    {
        rescheduled = RT_TRUE;
    }

    rt_mutex_release(&vsound->replay_push_lock);


    if (rescheduled)
    {
        virtio_sound_schedule_tx_complete(vsound);
    }
}

static void virtio_sound_replay_thread_entry(void *parameter)
{
    struct virtio_sound *vsound = parameter;

    while (!vsound->replay_thread_exit)
    {
        (void)rt_sem_take(&vsound->replay_sem,
                rt_tick_from_millisecond(VSOUND_REPLAY_POLL_MS));

        if (vsound->replay_thread_exit)
        {
            break;
        }

        virtio_sound_replay_push(vsound);
    }
}

static void virtio_sound_schedule_tx_complete(struct virtio_sound *vsound)
{
    rt_sem_release(&vsound->replay_sem);
}

static void virtio_sound_replay_queue_notify(struct rt_data_queue *queue, rt_uint32_t event)
{
    struct virtio_sound *vsound = virtio_sound_replay_notify_dev;

    RT_UNUSED(queue);

    if (event != RT_DATAQUEUE_EVENT_PUSH || vsound == RT_NULL ||
            !vsound->playback.active)
    {
        return;
    }

    virtio_sound_replay_push(vsound);
}

static void virtio_sound_replay_thread_stop(struct virtio_sound *vsound)
{
    if (!vsound->replay_thread)
    {
        return;
    }

    vsound->replay_thread_exit = RT_TRUE;
    rt_sem_release(&vsound->replay_sem);
    rt_thread_mdelay(10);
    rt_thread_delete(vsound->replay_thread);
    vsound->replay_thread = RT_NULL;
}

static rt_err_t virtio_sound_ctl_status(struct virtio_sound *vsound, rt_uint32_t code)
{
    switch (code)
    {
    case VIRTIO_SND_S_OK:
        return RT_EOK;

    case VIRTIO_SND_S_NOT_SUPP:
        return -RT_ENOSYS;

    case VIRTIO_SND_S_BAD_MSG:
        return -RT_EINVAL;

    case VIRTIO_SND_S_IO_ERR:
    default:
        return -RT_EIO;
    }
}

static rt_err_t virtio_sound_ctl_send(struct virtio_sound *vsound,
        void *request, rt_size_t request_size,
        void *response, rt_size_t response_size,
        void *in_extra, rt_size_t in_extra_size)
{
    rt_err_t err;
    rt_ubase_t level;
    rt_uint32_t bufs = in_extra ? 3 : 2;
    struct rt_virtqueue *vq = vsound->vqs[QUEUE_CONTROL];

    rt_virtqueue_wait_prepare(vq, bufs);

    level = rt_spin_lock_irqsave(&vsound->ctl_lock);

    rt_virtqueue_add_outbuf(vq, request, request_size);
    rt_virtqueue_add_inbuf(vq, response, response_size);

    if (in_extra)
    {
        rt_virtqueue_add_inbuf(vq, in_extra, in_extra_size);
    }

    rt_spin_unlock_irqrestore(&vsound->ctl_lock, level);
    rt_virtqueue_kick(vq);


    rt_completion_wait(&vsound->ctl_done, RT_WAITING_FOREVER);

    err = virtio_sound_ctl_status(vsound,
            virtio32_to_cpu(vsound->vdev, ((struct virtio_snd_hdr *)response)->code));


    return err;
}

static rt_err_t virtio_sound_ctl_query_info(struct virtio_sound *vsound,
        int command, int start_id, int count, rt_size_t size, void *info)
{
    struct virtio_snd_query_info query;
    struct virtio_snd_hdr response;

    query.hdr.code = cpu_to_virtio32(vsound->vdev, command);
    query.start_id = cpu_to_virtio32(vsound->vdev, start_id);
    query.count = cpu_to_virtio32(vsound->vdev, count);
    query.size = cpu_to_virtio32(vsound->vdev, size);

    return virtio_sound_ctl_send(vsound, &query, sizeof(query),
            &response, sizeof(response), info, count * size);
}

static rt_err_t virtio_sound_pcm_ctl(struct virtio_sound *vsound,
        struct virtio_sound_pcm_stream *stream, int command,
        void *request, rt_size_t request_size)
{
    struct virtio_snd_pcm_hdr simple;
    struct virtio_snd_hdr response;

    if (!request || request_size < sizeof(struct virtio_snd_pcm_hdr))
    {
        rt_memset(&simple, 0, sizeof(simple));
        simple.hdr.code = cpu_to_virtio32(vsound->vdev, command);
        simple.stream_id = cpu_to_virtio32(vsound->vdev, stream->sid);
        request = &simple;
        request_size = sizeof(simple);
    }

    return virtio_sound_ctl_send(vsound, request, request_size,
            &response, sizeof(response), RT_NULL, 0);
}

static int virtio_sound_pick_format_bits(rt_uint64_t formats)
{
    static const rt_uint32_t format_map[] =
    {
        [VIRTIO_SND_PCM_FMT_IMA_ADPCM] = 4,
        [VIRTIO_SND_PCM_FMT_MU_LAW] = 8,
        [VIRTIO_SND_PCM_FMT_A_LAW] = 8,
        [VIRTIO_SND_PCM_FMT_S8] = 8,
        [VIRTIO_SND_PCM_FMT_U8] = 8,
        [VIRTIO_SND_PCM_FMT_S16] = 16,
        [VIRTIO_SND_PCM_FMT_U16] = 16,
        [VIRTIO_SND_PCM_FMT_S18_3] = 18,
        [VIRTIO_SND_PCM_FMT_U18_3] = 18,
        [VIRTIO_SND_PCM_FMT_S20_3] = 20,
        [VIRTIO_SND_PCM_FMT_U20_3] = 20,
        [VIRTIO_SND_PCM_FMT_S24_3] = 24,
        [VIRTIO_SND_PCM_FMT_U24_3] = 24,
        [VIRTIO_SND_PCM_FMT_S20] = 20,
        [VIRTIO_SND_PCM_FMT_U20] = 20,
        [VIRTIO_SND_PCM_FMT_S24] = 24,
        [VIRTIO_SND_PCM_FMT_U24] = 24,
        [VIRTIO_SND_PCM_FMT_S32] = 32,
        [VIRTIO_SND_PCM_FMT_U32] = 32,
        [VIRTIO_SND_PCM_FMT_FLOAT] = 32,
        [VIRTIO_SND_PCM_FMT_FLOAT64] = 64,
        [VIRTIO_SND_PCM_FMT_DSD_U8] = 8,
        [VIRTIO_SND_PCM_FMT_DSD_U16] = 16,
        [VIRTIO_SND_PCM_FMT_DSD_U32] = 32,
        [VIRTIO_SND_PCM_FMT_IEC958_SUBFRAME] = 32
    };

    for (int i = 0; i < RT_ARRAY_SIZE(format_map); ++i)
    {
        if (formats & RT_BIT_ULL(i))
        {
            if (format_map[i])
            {
                return format_map[i];
            }
        }
    }

    return 16;
}

static int virtio_sound_pick_format(rt_uint64_t formats, int samplebits)
{
    static const struct
    {
        int bits;
        int fmt;
    } prefer[] =
    {
        { 16, VIRTIO_SND_PCM_FMT_S16 },
        { 32, VIRTIO_SND_PCM_FMT_S32 },
        { 24, VIRTIO_SND_PCM_FMT_S24 },
        { 8,  VIRTIO_SND_PCM_FMT_S8 },
    };

    if (samplebits > 0)
    {
        for (rt_size_t i = 0; i < RT_ARRAY_SIZE(prefer); ++i)
        {
            if (prefer[i].bits == samplebits &&
                    (formats & RT_BIT_ULL(prefer[i].fmt)))
            {
                return prefer[i].fmt;
            }
        }
    }

    for (int i = 0; i < 64; ++i)
    {
        if (formats & RT_BIT_ULL(i))
        {
            return i;
        }
    }

    return VIRTIO_SND_PCM_FMT_S16;
}

static int virtio_sound_pick_rate(rt_uint64_t rates)
{
    static const rt_uint32_t rate_map[] =
    {
        [VIRTIO_SND_PCM_RATE_5512] = 5512,
        [VIRTIO_SND_PCM_RATE_8000] = 8000,
        [VIRTIO_SND_PCM_RATE_11025] = 11025,
        [VIRTIO_SND_PCM_RATE_16000] = 16000,
        [VIRTIO_SND_PCM_RATE_22050] = 22050,
        [VIRTIO_SND_PCM_RATE_32000] = 32000,
        [VIRTIO_SND_PCM_RATE_44100] = 44100,
        [VIRTIO_SND_PCM_RATE_48000] = 48000,
        [VIRTIO_SND_PCM_RATE_64000] = 64000,
        [VIRTIO_SND_PCM_RATE_88200] = 88200,
        [VIRTIO_SND_PCM_RATE_96000] = 96000,
        [VIRTIO_SND_PCM_RATE_176400] = 176400,
        [VIRTIO_SND_PCM_RATE_192000] = 192000,
        [VIRTIO_SND_PCM_RATE_384000] = 384000,
    };

    for (int i = 0; i < RT_ARRAY_SIZE(rate_map); ++i)
    {
        if (rates & RT_BIT_ULL(i))
        {
            if (rate_map[i])
            {
                return rate_map[i];
            }
        }
    }

    return 44100;
}

static int virtio_sound_pick_rate_index(rt_uint64_t rates, int samplerate)
{
    static const struct
    {
        int hz;
        int idx;
    } prefer[] =
    {
        { 48000, VIRTIO_SND_PCM_RATE_48000 },
        { 44100, VIRTIO_SND_PCM_RATE_44100 },
        { 96000, VIRTIO_SND_PCM_RATE_96000 },
        { 192000, VIRTIO_SND_PCM_RATE_192000 },
        { 8000,  VIRTIO_SND_PCM_RATE_8000 },
        { 16000, VIRTIO_SND_PCM_RATE_16000 },
    };

    if (samplerate > 0)
    {
        for (rt_size_t i = 0; i < RT_ARRAY_SIZE(prefer); ++i)
        {
            if (prefer[i].hz == samplerate &&
                    (rates & RT_BIT_ULL(prefer[i].idx)))
            {
                return prefer[i].idx;
            }
        }
    }

    for (int i = 0; i < 64; ++i)
    {
        if (rates & RT_BIT_ULL(i))
        {
            return i;
        }
    }

    return VIRTIO_SND_PCM_RATE_44100;
}

static struct virtio_sound_pcm_stream *virtio_sound_get_stream(struct virtio_sound *vsound,
        rt_bool_t is_playback)
{
    rt_uint8_t dir = is_playback ? VIRTIO_SND_D_OUTPUT : VIRTIO_SND_D_INPUT;

    for (rt_uint32_t i = 0; i < vsound->substreams_nr; ++i)
    {
        if (vsound->substreams[i].direction == dir)
        {
            return &vsound->substreams[i];
        }
    }

    return RT_NULL;
}

static rt_err_t virtio_sound_pcm_runtime_alloc(struct virtio_sound *vsound,
        struct virtio_sound_pcm_runtime *rt)
{
    if (rt->buffer)
    {
        return RT_EOK;
    }

    rt->period_bytes = VSOUND_PERIOD_BYTES;
    rt->period_count = VSOUND_PERIOD_COUNT;
    rt->buffer_bytes = rt->period_bytes * rt->period_count;

    rt->buffer = rt_malloc(rt->buffer_bytes);
    if (!rt->buffer)
    {
        return -RT_ENOMEM;
    }

    rt_memset(rt->buffer, 0, rt->buffer_bytes);

    rt->msgs = rt_calloc(rt->period_count, sizeof(*rt->msgs));
    if (!rt->msgs)
    {
        rt_free(rt->buffer);
        rt->buffer = RT_NULL;
        return -RT_ENOMEM;
    }

    for (rt_uint32_t i = 0; i < rt->period_count; ++i)
    {
        rt->msgs[i].period = i;
    }

    return RT_EOK;
}

static void virtio_sound_pcm_runtime_free(struct virtio_sound_pcm_runtime *rt)
{
    rt_free(rt->msgs);
    rt_free(rt->buffer);
    rt->msgs = RT_NULL;
    rt->buffer = RT_NULL;
    rt->buffer_bytes = 0;
    rt->params_set = RT_FALSE;
    rt->active = RT_FALSE;
}

static rt_err_t virtio_sound_pcm_set_params(struct virtio_sound *vsound,
        struct virtio_sound_pcm_runtime *rt)
{
    struct virtio_snd_pcm_set_params request;
    rt_err_t err;

    RT_ASSERT(rt->stream);

    request.hdr.hdr.code = cpu_to_virtio32(vsound->vdev, VIRTIO_SND_R_PCM_SET_PARAMS);
    request.hdr.stream_id = cpu_to_virtio32(vsound->vdev, rt->stream->sid);
    request.buffer_bytes = cpu_to_virtio32(vsound->vdev, rt->buffer_bytes);
    request.period_bytes = cpu_to_virtio32(vsound->vdev, rt->period_bytes);
    request.features = 0;

    if (rt->stream->features & RT_BIT(VIRTIO_SND_PCM_F_MSG_POLLING))
    {
        request.features = cpu_to_virtio32(vsound->vdev,
                RT_BIT(VIRTIO_SND_PCM_F_MSG_POLLING));
    }

    rt->channels = (rt_uint8_t)vsound->audio_config.channels;
    if (rt->channels < rt->stream->channels_min)
    {
        rt->channels = rt->stream->channels_min;
    }
    if (rt->channels > rt->stream->channels_max)
    {
        rt->channels = rt->stream->channels_max;
    }

    rt->format = (rt_uint8_t)virtio_sound_pick_format(rt->stream->formats,
            vsound->audio_config.samplebits);
    rt->rate = (rt_uint8_t)virtio_sound_pick_rate_index(rt->stream->rates,
            vsound->audio_config.samplerate);

    request.channels = rt->channels;
    request.format = rt->format;
    request.rate = rt->rate;
    request.padding = 0;

    err = virtio_sound_pcm_ctl(vsound, rt->stream, VIRTIO_SND_R_PCM_SET_PARAMS,
            &request, sizeof(request));
    if (err == RT_EOK)
        rt->params_set = RT_TRUE;

    return err;
}

static rt_uint32_t virtio_sound_pcm_pending(struct virtio_sound_pcm_runtime *rt)
{
    rt_uint32_t pending = 0;

    if (!rt->msgs)
    {
        return 0;
    }

    for (rt_uint32_t i = 0; i < rt->period_count; ++i)
    {
        if (rt->msgs[i].pending)
        {
            pending++;
        }
    }

    return pending;
}

static rt_uint32_t virtio_sound_pcm_process_used(struct rt_virtqueue *vq,
        struct virtio_sound *vsound,
        struct virtio_sound_pcm_runtime *rt,
        struct rt_spinlock *lock,
        rt_bool_t is_playback,
        rt_bool_t kick_pipeline)
{
    rt_uint32_t processed = 0;
    rt_ubase_t level;

    if (!vq)
    {
        return 0;
    }

    level = rt_spin_lock_irqsave(lock);

    while (processed < VSOUND_RECYCLE_MAX)
    {
        rt_size_t len;
        void *buf = rt_virtqueue_read_buf(vq, &len);
        struct virtio_sound_io_msg *msg;

        if (!buf)
        {
            break;
        }

        msg = rt_container_of(buf, struct virtio_sound_io_msg, xfer);
        msg->pending = RT_FALSE;
        processed++;

        if (virtio32_to_cpu(vsound->vdev, msg->status.status) != VIRTIO_SND_S_OK)
        {
            LOG_W("PCM I/O period %u status 0x%x",
                    msg->period,
                    virtio32_to_cpu(vsound->vdev, msg->status.status));
        }

        rt_spin_unlock_irqrestore(lock, level);

        if (is_playback && msg->mp_block)
        {
            rt_mp_free(msg->mp_block);
            msg->mp_block = RT_NULL;
        }

        if (rt->active && kick_pipeline)
        {
            if (is_playback)
            {
                virtio_sound_schedule_tx_complete(vsound);
            }
            else
            {
                rt_audio_rx_done(&vsound->parent,
                        rt->buffer + msg->period * rt->period_bytes,
                        rt->period_bytes);
                virtio_sound_pcm_submit_rx(vsound, rt, msg->period);
            }
        }

        level = rt_spin_lock_irqsave(lock);
    }

    rt_spin_unlock_irqrestore(lock, level);

    return processed;
}

static rt_uint32_t virtio_sound_vq_recycle(struct rt_virtqueue *vq,
        struct virtio_sound *vsound,
        struct virtio_sound_pcm_runtime *rt,
        struct rt_spinlock *lock,
        rt_bool_t is_playback)
{
    return virtio_sound_pcm_process_used(vq, vsound, rt, lock, is_playback, RT_FALSE);
}

static rt_uint32_t virtio_sound_vq_drain_used(struct rt_virtqueue *vq,
        struct virtio_sound *vsound,
        struct virtio_sound_pcm_runtime *rt,
        struct rt_spinlock *lock,
        rt_bool_t is_playback)
{
    rt_uint32_t total = 0;

    for (rt_uint32_t n = 0; n < VSOUND_RECYCLE_MAX; n++)
    {
        rt_uint32_t batch = virtio_sound_vq_recycle(vq, vsound, rt, lock, is_playback);

        if (batch == 0)
        {
            break;
        }

        total += batch;
    }

    return total;
}

static rt_bool_t virtio_sound_vq_wait_prepare(struct rt_virtqueue *vq,
        struct virtio_sound *vsound,
        struct virtio_sound_pcm_runtime *rt,
        struct rt_spinlock *lock,
        rt_bool_t is_playback,
        rt_uint32_t nr)
{
    rt_uint32_t retries = 0;

    while (!rt_virtqueue_prepare(vq, nr))
    {
        virtio_sound_vq_recycle(vq, vsound, rt, lock, is_playback);

        if (rt_virtqueue_prepare(vq, nr))
        {
            break;
        }

        rt_thread_yield();
        rt_hw_cpu_relax();

        /*
         * In thread context, keep polling until descriptors are recycled
         * (QEMU virtio-sound may complete TX synchronously on kick).
         */
        if (rt_interrupt_get_nest() != 0)
        {
            if (++retries > 1000)
            {
                LOG_E("virtqueue %s wait timeout", vq->name ? vq->name : "pcm");
                return RT_FALSE;
            }
        }
        else if (++retries > 50000)
        {
            LOG_E("virtqueue %s thread wait timeout", vq->name ? vq->name : "pcm");
            return RT_FALSE;
        }
    }

    return RT_TRUE;
}

static rt_err_t virtio_sound_pcm_submit_tx(struct virtio_sound *vsound,
        struct virtio_sound_pcm_runtime *rt, rt_uint32_t period)
{
    struct virtio_sound_io_msg *msg;
    struct rt_virtqueue *vq;
    rt_ubase_t level;

    if (!rt->active || !rt->msgs || period >= rt->period_count)
    {
        return -RT_EINVAL;
    }

    msg = &rt->msgs[period];
    if (msg->pending)
    {
        return -RT_EBUSY;
    }

    msg->xfer.stream_id = cpu_to_virtio32(vsound->vdev, rt->stream->sid);
    msg->status.status = 0;
    msg->status.latency_bytes = 0;

    vq = vsound->vqs[QUEUE_TX];

    if (!virtio_sound_vq_wait_prepare(vq, vsound, rt, &vsound->tx_lock, RT_TRUE, 3))
    {
        return -RT_EBUSY;
    }

    level = rt_spin_lock_irqsave(&vsound->tx_lock);

    if (rt_virtqueue_add_outbuf(vq, &msg->xfer, sizeof(msg->xfer)) != RT_EOK ||
            rt_virtqueue_add_outbuf(vq, rt->buffer + period * rt->period_bytes,
                    rt->period_bytes) != RT_EOK ||
            rt_virtqueue_add_inbuf(vq, &msg->status, sizeof(msg->status)) != RT_EOK)
    {
        rt_spin_unlock_irqrestore(&vsound->tx_lock, level);
        return -RT_EIO;
    }

    msg->pending = RT_TRUE;
    rt_spin_unlock_irqrestore(&vsound->tx_lock, level);

    /*
     * Kick must run without tx_lock: QEMU may invoke tx_done synchronously,
     * which also takes tx_lock and would deadlock.
     */
    rt_virtqueue_kick(vq);

    /*
     * Host may complete the period before the TX ISR runs (QEMU trace shows
     * virtio_snd_handle_tx_xfer immediately).  Poll the used ring from thread
     * context so the pipeline can submit the next period without waiting.
     */
    if (rt_interrupt_get_nest() == 0)
    {
        virtio_sound_pcm_process_used(vq, vsound, rt, &vsound->tx_lock, RT_TRUE, RT_FALSE);
    }
    else if (virtio_sound_vq_recycle(vq, vsound, rt, &vsound->tx_lock, RT_TRUE) > 0)
    {
        virtio_sound_schedule_tx_complete(vsound);
    }

    return RT_EOK;
}

static rt_err_t virtio_sound_pcm_submit_rx(struct virtio_sound *vsound,
        struct virtio_sound_pcm_runtime *rt, rt_uint32_t period)
{
    struct virtio_sound_io_msg *msg;
    struct rt_virtqueue *vq;
    rt_ubase_t level;

    if (!rt->active || !rt->msgs || period >= rt->period_count)
    {
        return -RT_EINVAL;
    }

    msg = &rt->msgs[period];
    if (msg->pending)
    {
        return RT_EOK;
    }

    msg->xfer.stream_id = cpu_to_virtio32(vsound->vdev, rt->stream->sid);
    msg->status.status = 0;
    msg->status.latency_bytes = 0;

    vq = vsound->vqs[QUEUE_RX];

    if (!virtio_sound_vq_wait_prepare(vq, vsound, rt, &vsound->rx_lock, RT_FALSE, 3))
    {
        return -RT_EBUSY;
    }

    level = rt_spin_lock_irqsave(&vsound->rx_lock);

    if (rt_virtqueue_add_outbuf(vq, &msg->xfer, sizeof(msg->xfer)) != RT_EOK ||
            rt_virtqueue_add_inbuf(vq, rt->buffer + period * rt->period_bytes,
                    rt->period_bytes) != RT_EOK ||
            rt_virtqueue_add_inbuf(vq, &msg->status, sizeof(msg->status)) != RT_EOK)
    {
        rt_spin_unlock_irqrestore(&vsound->rx_lock, level);
        return -RT_EIO;
    }

    msg->pending = RT_TRUE;
    rt_spin_unlock_irqrestore(&vsound->rx_lock, level);

    rt_virtqueue_kick(vq);

    virtio_sound_vq_recycle(vq, vsound, rt, &vsound->rx_lock, RT_FALSE);

    return RT_EOK;
}

static rt_err_t virtio_sound_audio_getcaps(struct rt_audio_device *audio,
        struct rt_audio_caps *caps)
{
    struct virtio_sound_pcm_stream *stream;
    struct virtio_sound *vsound = raw_to_virtio_sound(audio);

    switch (caps->main_type)
    {
    case AUDIO_TYPE_QUERY:
        switch (caps->sub_type)
        {
        case AUDIO_TYPE_QUERY:
            caps->udata.mask = AUDIO_TYPE_INPUT | AUDIO_TYPE_OUTPUT | AUDIO_TYPE_MIXER;
            break;

        default:
            return -RT_ENOSYS;
        }
        break;

    case AUDIO_TYPE_OUTPUT:
    case AUDIO_TYPE_INPUT:
        stream = virtio_sound_get_stream(vsound, caps->main_type == AUDIO_TYPE_OUTPUT);

        if (!stream)
        {
            return -RT_ENOSYS;
        }

        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            caps->udata.config.channels = vsound->audio_config.channels;
            caps->udata.config.samplebits = virtio_sound_pick_format_bits(stream->formats);
            caps->udata.config.samplerate = virtio_sound_pick_rate(stream->rates);
            break;

        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate = virtio_sound_pick_rate(stream->rates);
            break;

        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels = vsound->audio_config.channels;
            break;

        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits = virtio_sound_pick_format_bits(stream->formats);
            break;

        default:
            return -RT_ENOSYS;
        }
        break;

    case AUDIO_TYPE_MIXER:
        switch (caps->sub_type)
        {
        case AUDIO_MIXER_QUERY:
            caps->udata.mask = 0;
            caps->udata.mask |= AUDIO_MIXER_VOLUME;
            caps->udata.mask |= AUDIO_MIXER_MUTE;
            break;

        case AUDIO_MIXER_VOLUME:
            caps->udata.value = vsound->playback_volume;
            break;

        case AUDIO_MIXER_MUTE:
            caps->udata.value = vsound->playback_mute ? 1 : 0;
            break;

        default:
            return -RT_ENOSYS;
        }
        break;

    default:
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static rt_err_t virtio_sound_audio_configure(struct rt_audio_device *audio,
        struct rt_audio_caps *caps)
{
    struct virtio_sound *vsound = raw_to_virtio_sound(audio);

    switch (caps->main_type)
    {
    case AUDIO_TYPE_OUTPUT:
        switch (caps->sub_type)
        {
        case AUDIO_DSP_SAMPLERATE:
            vsound->audio_config.samplerate = caps->udata.config.samplerate;
            vsound->playback.params_set = RT_FALSE;
            break;

        case AUDIO_DSP_CHANNELS:
            vsound->audio_config.channels = caps->udata.config.channels;
            vsound->playback.params_set = RT_FALSE;
            break;

        case AUDIO_DSP_SAMPLEBITS:
            vsound->audio_config.samplebits = caps->udata.config.samplebits;
            vsound->playback.params_set = RT_FALSE;
            break;

        case AUDIO_DSP_PARAM:
            vsound->audio_config.samplerate = caps->udata.config.samplerate;
            vsound->audio_config.channels = caps->udata.config.channels;
            vsound->audio_config.samplebits = caps->udata.config.samplebits;
            vsound->playback.params_set = RT_FALSE;
            break;

        default:
            return -RT_ENOSYS;
        }
        break;

    case AUDIO_TYPE_INPUT:
        switch (caps->sub_type)
        {
        case AUDIO_DSP_SAMPLERATE:
            vsound->audio_config.samplerate = caps->udata.config.samplerate;
            vsound->capture.params_set = RT_FALSE;
            break;

        case AUDIO_DSP_CHANNELS:
            vsound->audio_config.channels = caps->udata.config.channels;
            vsound->capture.params_set = RT_FALSE;
            break;

        case AUDIO_DSP_SAMPLEBITS:
            vsound->audio_config.samplebits = caps->udata.config.samplebits;
            vsound->capture.params_set = RT_FALSE;
            break;

        case AUDIO_DSP_PARAM:
            vsound->audio_config.samplerate = caps->udata.config.samplerate;
            vsound->audio_config.channels = caps->udata.config.channels;
            vsound->audio_config.samplebits = caps->udata.config.samplebits;
            vsound->capture.params_set = RT_FALSE;
            break;

        default:
            return -RT_ENOSYS;
        }
        break;

    case AUDIO_TYPE_MIXER:
        switch (caps->sub_type)
        {
        case AUDIO_MIXER_VOLUME:
            vsound->playback_volume = caps->udata.value;
            break;

        case AUDIO_MIXER_MUTE:
            vsound->playback_mute = caps->udata.value ? RT_TRUE : RT_FALSE;
            break;

        default:
            return -RT_ENOSYS;
        }
        break;

    default:
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static rt_err_t virtio_sound_pcm_start(struct virtio_sound *vsound,
        struct virtio_sound_pcm_runtime *rt, rt_bool_t is_playback)
{
    rt_err_t err;

    if (!rt->stream)
    {
        LOG_W("start: no %s stream", is_playback ? "playback" : "capture");
        return -RT_ENOSYS;
    }


    if (is_playback)
    {
        virtio_sound_replay_queue_reset(vsound);
    }

    err = virtio_sound_pcm_runtime_alloc(vsound, rt);
    if (err)
    {
        return err;
    }

    if (!rt->params_set)
    {
        err = virtio_sound_pcm_set_params(vsound, rt);
        if (err)
        {
            return err;
        }
    }

    err = virtio_sound_pcm_ctl(vsound, rt->stream, VIRTIO_SND_R_PCM_PREPARE, RT_NULL, 0);
    if (err)
    {
        return err;
    }

    err = virtio_sound_pcm_ctl(vsound, rt->stream, VIRTIO_SND_R_PCM_START, RT_NULL, 0);
    if (err)
    {
        return err;
    }

    rt->active = RT_TRUE;
    virtio_sound_replay_reset_msgs(rt);

    if (is_playback && vsound->parent.replay &&
            rt_data_queue_len(&vsound->parent.replay->queue) > 0)
    {
        virtio_sound_replay_push(vsound);
    }
    else if (!is_playback)
    {
        for (rt_uint32_t i = 0; i < rt->period_count; ++i)
        {
            err = virtio_sound_pcm_submit_rx(vsound, rt, i);
            if (err)
            {
                break;
            }
        }
    }

    return err;
}

static rt_err_t virtio_sound_pcm_stop(struct virtio_sound *vsound,
        struct virtio_sound_pcm_runtime *rt)
{
    rt_err_t err;
    int timeout = 1000;

    if (!rt->stream || !rt->active)
    {
        return RT_EOK;
    }


    err = virtio_sound_pcm_ctl(vsound, rt->stream, VIRTIO_SND_R_PCM_STOP, RT_NULL, 0);
    if (err)
    {
        LOG_W("PCM STOP failed: %d", err);
    }

    while (virtio_sound_pcm_pending(rt) > 0 && timeout-- > 0)
    {
        if (rt == &vsound->playback)
        {
            virtio_sound_vq_recycle(vsound->vqs[QUEUE_TX], vsound, rt,
                    &vsound->tx_lock, RT_TRUE);
        }
        else
        {
            virtio_sound_vq_recycle(vsound->vqs[QUEUE_RX], vsound, rt,
                    &vsound->rx_lock, RT_FALSE);
        }

        rt_thread_mdelay(1);
    }

    if (rt == &vsound->playback)
    {
        virtio_sound_replay_reset_msgs(rt);
        virtio_sound_replay_queue_reset(vsound);
    }

    rt->active = RT_FALSE;

    err = virtio_sound_pcm_ctl(vsound, rt->stream, VIRTIO_SND_R_PCM_RELEASE, RT_NULL, 0);
    if (err)
    {
        LOG_W("PCM RELEASE failed: %d", err);
    }

    rt->params_set = RT_FALSE;


    return RT_EOK;
}

static rt_err_t virtio_sound_audio_init(struct rt_audio_device *audio)
{
    struct virtio_sound *vsound = raw_to_virtio_sound(audio);

    vsound->audio_config.samplerate = 48000;
    vsound->audio_config.channels = 2;
    vsound->audio_config.samplebits = 16;
    vsound->playback_volume = AUDIO_VOLUME_MAX;
    vsound->capture_volume = AUDIO_VOLUME_MAX;

    vsound->playback.stream = virtio_sound_get_stream(vsound, RT_TRUE);
    vsound->capture.stream = virtio_sound_get_stream(vsound, RT_FALSE);

    return RT_EOK;
}

static rt_err_t virtio_sound_audio_start(struct rt_audio_device *audio, int stream)
{
    struct virtio_sound *vsound = raw_to_virtio_sound(audio);

    if (stream == AUDIO_STREAM_REPLAY)
    {
        return virtio_sound_pcm_start(vsound, &vsound->playback, RT_TRUE);
    }

    if (stream == AUDIO_STREAM_RECORD)
    {
        return virtio_sound_pcm_start(vsound, &vsound->capture, RT_FALSE);
    }

    return -RT_EINVAL;
}

static rt_err_t virtio_sound_audio_stop(struct rt_audio_device *audio, int stream)
{
    struct virtio_sound *vsound = raw_to_virtio_sound(audio);

    if (stream == AUDIO_STREAM_REPLAY)
    {
        return virtio_sound_pcm_stop(vsound, &vsound->playback);
    }

    if (stream == AUDIO_STREAM_RECORD)
    {
        return virtio_sound_pcm_stop(vsound, &vsound->capture);
    }

    return -RT_EINVAL;
}

static rt_ssize_t virtio_sound_audio_transmit(struct rt_audio_device *audio,
        const void *write_buf, void *read_buf, rt_size_t size)
{
    struct virtio_sound *vsound = raw_to_virtio_sound(audio);
    struct virtio_sound_pcm_runtime *rt = &vsound->playback;
    const rt_uint8_t *pcm = write_buf;
    rt_uint32_t period;

    RT_UNUSED(read_buf);

    if (!rt->active || !rt->buffer || !pcm || size == 0)
    {
        return 0;
    }

    if (pcm < rt->buffer || pcm >= rt->buffer + rt->buffer_bytes)
    {
        LOG_E("transmit: bad buffer %p", pcm);
        return 0;
    }

    period = (rt_uint32_t)(pcm - rt->buffer) / rt->period_bytes;
    if (period >= rt->period_count || size != rt->period_bytes)
    {
        LOG_E("transmit: bad period=%u size=%u", period, (rt_uint32_t)size);
        return 0;
    }

    if (virtio_sound_pcm_submit_tx(vsound, rt, period) != RT_EOK)
    {
        return 0;
    }

    return (rt_ssize_t)size;
}

static void virtio_sound_audio_buffer_info(struct rt_audio_device *audio,
        struct rt_audio_buf_info *info)
{
    struct virtio_sound *vsound = raw_to_virtio_sound(audio);
    struct virtio_sound_pcm_runtime *rt = &vsound->playback;

    if (virtio_sound_pcm_runtime_alloc(vsound, rt) != RT_EOK)
    {
        info->buffer = RT_NULL;
        info->total_size = 0;
        info->block_size = 0;
        info->block_count = 0;
        return;
    }

    info->buffer = rt->buffer;
    info->total_size = rt->buffer_bytes;
    info->block_size = (rt_uint16_t)rt->period_bytes;
    info->block_count = (rt_uint16_t)rt->period_count;
}

const static struct rt_audio_ops virtio_sound_audio_ops =
{
    .getcaps = virtio_sound_audio_getcaps,
    .configure = virtio_sound_audio_configure,
    .init = virtio_sound_audio_init,
    .start = virtio_sound_audio_start,
    .stop = virtio_sound_audio_stop,
    .transmit = virtio_sound_audio_transmit,
    .buffer_info = virtio_sound_audio_buffer_info,
};

static void virtio_sound_control_done(struct rt_virtqueue *vq)
{
    rt_ubase_t level;
    struct virtio_sound *vsound = vq->vdev->priv;

    level = rt_spin_lock_irqsave(&vsound->ctl_lock);

    rt_virtqueue_read_buf(vq, RT_NULL);
    rt_completion_done(&vsound->ctl_done);

    rt_spin_unlock_irqrestore(&vsound->ctl_lock, level);
}

static void virtio_sound_event_done(struct rt_virtqueue *vq)
{
    rt_ubase_t level;
    struct virtio_sound *vsound = vq->vdev->priv;
    struct rt_virtqueue *event_vq = vsound->vqs[QUEUE_EVENT];

    level = rt_spin_lock_irqsave(&vsound->ctl_lock);

    while (1)
    {
        rt_size_t len;
        struct virtio_snd_event *event = rt_virtqueue_read_buf(vq, &len);

        if (!event)
        {
            break;
        }

        switch (virtio32_to_cpu(vsound->vdev, event->hdr.code))
        {
        case VIRTIO_SND_EVT_JACK_CONNECTED:
        case VIRTIO_SND_EVT_JACK_DISCONNECTED:
            LOG_I("jack event 0x%x data %u",
                    virtio32_to_cpu(vsound->vdev, event->hdr.code),
                    virtio32_to_cpu(vsound->vdev, event->data));
            break;

        case VIRTIO_SND_EVT_PCM_PERIOD_ELAPSED:
            break;

        case VIRTIO_SND_EVT_PCM_XRUN:
            LOG_W("PCM xrun on stream %u",
                    virtio32_to_cpu(vsound->vdev, event->data));
            break;

        default:
            break;
        }

        rt_virtqueue_add_inbuf(event_vq, event, sizeof(*event));
    }

    rt_virtqueue_kick(event_vq);

    rt_spin_unlock_irqrestore(&vsound->ctl_lock, level);
}

static void virtio_sound_tx_done(struct rt_virtqueue *vq)
{
    struct virtio_sound *vsound = vq->vdev->priv;

    virtio_sound_pcm_process_used(vq, vsound, &vsound->playback,
            &vsound->tx_lock, RT_TRUE, RT_TRUE);
}

static void virtio_sound_rx_done(struct rt_virtqueue *vq)
{
    struct virtio_sound *vsound = vq->vdev->priv;

    virtio_sound_pcm_process_used(vq, vsound, &vsound->capture,
            &vsound->rx_lock, RT_FALSE, RT_TRUE);
}

static rt_err_t virtio_sound_vq_init(struct virtio_sound *vsound)
{
    const char *names[] =
    {
        "control",
        "event",
        "tx",
        "rx",
    };
    rt_virtqueue_callback cbs[] =
    {
        &virtio_sound_control_done,
        &virtio_sound_event_done,
        &virtio_sound_tx_done,
        &virtio_sound_rx_done,
    };

    return rt_virtio_virtqueue_install(vsound->vdev,
            RT_ARRAY_SIZE(names), vsound->vqs, names, cbs);
}

static rt_err_t virtio_sound_event_init(struct virtio_sound *vsound)
{
    struct rt_virtqueue *vq = vsound->vqs[QUEUE_EVENT];
    rt_uint32_t i;

    if (!vq)
    {
        return RT_EOK;
    }

    vsound->event_msgs_nr = rt_virtqueue_get_virtq_size(vq);
    if (!vsound->event_msgs_nr)
    {
        return RT_EOK;
    }

    vsound->event_msgs = rt_calloc(vsound->event_msgs_nr, sizeof(*vsound->event_msgs));
    if (!vsound->event_msgs)
    {
        return -RT_ENOMEM;
    }

    for (i = 0; i < vsound->event_msgs_nr; ++i)
    {
        rt_virtqueue_add_inbuf(vq, &vsound->event_msgs[i], sizeof(vsound->event_msgs[i]));
    }

    rt_virtqueue_kick(vq);

    return RT_EOK;
}

static rt_err_t virtio_sound_jack_init(struct virtio_sound *vsound)
{
    rt_err_t err;
    struct virtio_snd_jack_info *info;

    rt_virtio_read_config(vsound->vdev, struct virtio_snd_config, jacks, &vsound->jacks_nr);
    if (!vsound->jacks_nr)
    {
        return RT_EOK;
    }

    vsound->jacks = rt_calloc(vsound->jacks_nr, sizeof(*vsound->jacks));
    if (!vsound->jacks)
    {
        return -RT_ENOMEM;
    }

    info = rt_calloc(vsound->jacks_nr, sizeof(*info));
    if (!info)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    err = virtio_sound_ctl_query_info(vsound,
            VIRTIO_SND_R_JACK_INFO, 0, vsound->jacks_nr, sizeof(*info), info);
    if (err)
    {
        goto _fail;
    }

    for (rt_uint32_t i = 0; i < vsound->jacks_nr; ++i)
    {
        vsound->jacks[i].nid = virtio32_to_cpu(vsound->vdev, info[i].hdr.hda_fn_nid);
        vsound->jacks[i].features = virtio32_to_cpu(vsound->vdev, info[i].features);
        vsound->jacks[i].defconf = virtio32_to_cpu(vsound->vdev, info[i].hda_reg_defconf);
        vsound->jacks[i].caps = virtio32_to_cpu(vsound->vdev, info[i].hda_reg_caps);
        vsound->jacks[i].connected = info[i].connected ? RT_TRUE : RT_FALSE;
    }

_fail:
    rt_free(info);

    if (err)
    {
        rt_free(vsound->jacks);
        vsound->jacks = RT_NULL;
    }

    return err;
}

static rt_err_t virtio_sound_chmap_init(struct virtio_sound *vsound)
{
    rt_err_t err;

    rt_virtio_read_config(vsound->vdev, struct virtio_snd_config, chmaps, &vsound->chmaps_nr);
    if (!vsound->chmaps_nr)
    {
        return RT_EOK;
    }

    vsound->chmaps = rt_calloc(vsound->chmaps_nr, sizeof(*vsound->chmaps));
    if (!vsound->chmaps)
    {
        return -RT_ENOMEM;
    }

    err = virtio_sound_ctl_query_info(vsound,
            VIRTIO_SND_R_CHMAP_INFO, 0, vsound->chmaps_nr,
            sizeof(*vsound->chmaps), vsound->chmaps);
    if (err)
    {
        rt_free(vsound->chmaps);
        vsound->chmaps = RT_NULL;
    }

    return err;
}

static rt_err_t virtio_sound_pcm_init(struct virtio_sound *vsound)
{
    rt_err_t err;
    struct virtio_snd_pcm_info *info;

    rt_virtio_read_config(vsound->vdev, struct virtio_snd_config, streams, &vsound->substreams_nr);

    if (!vsound->substreams_nr)
    {
        return RT_EOK;
    }

    vsound->substreams = rt_calloc(vsound->substreams_nr, sizeof(*vsound->substreams));

    if (!vsound->substreams)
    {
        return -RT_ENOMEM;
    }

    info = rt_calloc(vsound->substreams_nr, sizeof(*info));

    if (!info)
    {
        err = -RT_ENOMEM;
        goto _end;
    }

    err = virtio_sound_ctl_query_info(vsound,
            VIRTIO_SND_R_PCM_INFO, 0, vsound->substreams_nr, sizeof(*info), info);
    if (err)
    {
        goto _end;
    }

    for (int i = 0; i < vsound->substreams_nr; ++i)
    {
        struct virtio_sound_pcm_stream *vss = &vsound->substreams[i];

        vss->nid = virtio32_to_cpu(vsound->vdev, info[i].hdr.hda_fn_nid);
        vss->sid = i;
        vss->features = virtio32_to_cpu(vsound->vdev, info[i].features);
        vss->formats = virtio64_to_cpu(vsound->vdev, info[i].formats);
        vss->rates = virtio64_to_cpu(vsound->vdev, info[i].rates);
        vss->direction = info[i].direction;
        vss->channels_min = info[i].channels_min;
        vss->channels_max = info[i].channels_max;
    }

    vsound->playback.stream = virtio_sound_get_stream(vsound, RT_TRUE);
    vsound->capture.stream = virtio_sound_get_stream(vsound, RT_FALSE);

_end:
    rt_free(info);

    if (err)
    {
        rt_free(vsound->substreams);
        vsound->substreams = RT_NULL;
    }

    return err;
}

static void virtio_sound_vq_finit(struct virtio_sound *vsound)
{
    if (vsound->vqs[0])
    {
        rt_virtio_virtqueue_release(vsound->vdev);
    }
}

static void virtio_sound_free(struct virtio_sound *vsound)
{
    virtio_sound_replay_thread_stop(vsound);
    virtio_sound_pcm_runtime_free(&vsound->playback);
    virtio_sound_pcm_runtime_free(&vsound->capture);
    rt_free(vsound->event_msgs);
    rt_free(vsound->jacks);
    rt_free(vsound->chmaps);
    rt_free(vsound->substreams);
    rt_free(vsound);
}

static rt_err_t virtio_sound_probe(struct rt_virtio_device *vdev)
{
    rt_err_t err;
    const char *audio_name;
    struct virtio_sound *vsound = rt_calloc(1, sizeof(*vsound));

    if (!vsound)
    {
        return -RT_ENOMEM;
    }

    vdev->priv = vsound;
    vsound->vdev = vdev;
    vdev->parent.user_data = vsound;

    rt_completion_init(&vsound->ctl_done);
    rt_spin_lock_init(&vsound->ctl_lock);
    rt_spin_lock_init(&vsound->tx_lock);
    rt_spin_lock_init(&vsound->rx_lock);
    rt_mutex_init(&vsound->replay_push_lock, "vs_plk", RT_IPC_FLAG_PRIO);
    rt_sem_init(&vsound->replay_sem, "vs_rpl", 0, RT_IPC_FLAG_FIFO);
    vsound->replay_thread = rt_thread_create("vs_rpl",
            virtio_sound_replay_thread_entry, vsound, 16384, 12, 10);
    if (!vsound->replay_thread)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }
    rt_thread_startup(vsound->replay_thread);

    if ((err = virtio_sound_vq_init(vsound)) < 0)
    {
        goto _fail;
    }

    if ((err = virtio_sound_event_init(vsound)))
    {
        goto _fail;
    }

    if ((err = virtio_sound_jack_init(vsound)))
    {
        goto _fail;
    }

    if ((err = virtio_sound_pcm_init(vsound)))
    {
        goto _fail;
    }

    if ((err = virtio_sound_chmap_init(vsound)))
    {
        goto _fail;
    }

    rt_virtio_read_config(vsound->vdev, struct virtio_snd_config, controls, &vsound->controls_nr);

    vsound->audio_config.channels = 2;
    vsound->audio_config.samplerate = 48000;
    vsound->audio_config.samplebits = 16;
    vsound->playback_volume = AUDIO_VOLUME_MAX;

    rt_dm_dev_set_name_auto(&vsound->parent.parent, "sound");
    audio_name = rt_dm_dev_get_name(&vsound->parent.parent);

    vsound->parent.ops = (struct rt_audio_ops *)&virtio_sound_audio_ops;

    if ((err = rt_audio_register(&vsound->parent, audio_name, RT_DEVICE_FLAG_RDWR, vsound)))
    {
        goto _fail;
    }

    if (vsound->parent.replay)
    {
        virtio_sound_replay_notify_dev = vsound;
        vsound->parent.replay->queue.evt_notify = virtio_sound_replay_queue_notify;
    }

    LOG_I("virtio sound: %u streams, %u jacks, %u chmaps",
            vsound->substreams_nr, vsound->jacks_nr, vsound->chmaps_nr);

    return RT_EOK;

_fail:
    virtio_sound_vq_finit(vsound);
    virtio_sound_free(vsound);

    return err;
}

static rt_err_t virtio_sound_remove(struct rt_virtio_device *vdev)
{
    struct virtio_sound *vsound = vdev->parent.user_data;

    if (virtio_sound_replay_notify_dev == vsound)
    {
        virtio_sound_replay_notify_dev = RT_NULL;
    }

    rt_device_unregister(&vsound->parent.parent);
    virtio_sound_vq_finit(vsound);
    virtio_sound_free(vsound);

    return RT_EOK;
}

static const struct rt_virtio_device_id virtio_sound_ids[] =
{
    { VIRTIO_DEVICE_ID_AUDIO, VIRTIO_DEVICE_ANY_ID },
    { /* sentinel */ }
};

static struct rt_virtio_driver virtio_sound_driver =
{
    .ids = virtio_sound_ids,
    .features =
        RT_BIT(VIRTIO_SOUND_F_CTLS)
      | RT_BIT(VIRTIO_F_ANY_LAYOUT),

    .probe = virtio_sound_probe,
    .remove = virtio_sound_remove,
};
RT_VIRTIO_DRIVER_EXPORT(virtio_sound_driver);
