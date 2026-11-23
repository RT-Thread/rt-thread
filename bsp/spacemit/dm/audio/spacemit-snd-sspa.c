/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#define DBG_TAG "audio.hdmi.spacemit"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <k1x-rproc.h>

#include "spacemit-audio.h"
#include "spacemit-snd-sspa.h"

#define K1_ADMA_HDMI_BYTES_PER_SECOND \
    (HDMI_SSPA_SAMPLE_RATE * 2U * sizeof(rt_uint32_t))
#define K1_ADMA_RPMSG_LOCAL_ADDR       1024
#define K1_ADMA_RPMSG_BOOT_TIMEOUT_MS  3000
#define K1_ADMA_RPMSG_SEND_TIMEOUT_MS  1000
#define K1_ADMA_RPMSG_STARTUP_MSG      "startup"
#define K1_ADMA_RPMSG_STARTUP_OK_MSG   "startup-ok"
struct spacemit_hdmi_audio
{
    struct rt_device *dev;
    struct rt_ofw_node *np;

    void *regs;
    void *clock_regs;
    void *hdmi_regs;
    rt_ubase_t phys;

    struct rt_clk *audio_clk;
    struct rt_clk *hdmi_clk;
    struct rt_reset_control *reset;

    int users;
    rt_bool_t warned_unplugged;
    rt_list_t list;
};

struct spacemit_adma
{
    struct rt_dma_controller parent;
    struct rt_dma_chan channel;
    struct rt_device *dev;

    void *regs;
    void *control;
    void *descriptors;
    rt_ubase_t descriptors_dma;

    rt_ubase_t buffer_dma;
    rt_size_t period_len;
    rt_size_t period_count;
    rt_size_t period_index;
    rt_tick_t period_tick;
    rt_uint32_t period_done_count;
    rt_bool_t allocated;
    rt_bool_t unpack_sample;
    rt_bool_t running;
    rt_bool_t rpmsg_started;
#ifdef RT_USING_RPMSG
    struct rt_rpmsg_device *rpmsg_dev;
    struct rt_rpmsg_endpoint *rpmsg_ept;
    rt_uint32_t rpmsg_remote_addr;
    struct rt_completion rpmsg_startup_done;
    rt_uint32_t rpmsg_rx_count;
    rt_bool_t rpmsg_startup_ready;
#endif
};

static rt_list_t hdmi_nodes = RT_LIST_OBJECT_INIT(hdmi_nodes);
static RT_DEFINE_SPINLOCK(hdmi_nodes_lock);
#ifdef RT_USING_RPMSG
static struct spacemit_adma *spacemit_adma_global;
static RT_DEFINE_SPINLOCK(spacemit_adma_global_lock);

struct spacemit_rpmsg_char_ctrl
{
    struct rt_device parent;
    struct rt_rpmsg_device *rdev;
};
#endif

struct spacemit_hdmi_audio *spacemit_hdmi_audio_find(struct rt_ofw_node *np)
{
    struct spacemit_hdmi_audio *hdmi;

    rt_spin_lock(&hdmi_nodes_lock);
    rt_list_for_each_entry(hdmi, &hdmi_nodes, list)
    {
        if (hdmi->np == np)
        {
            rt_spin_unlock(&hdmi_nodes_lock);
            return hdmi;
        }
    }
    rt_spin_unlock(&hdmi_nodes_lock);

    return RT_NULL;
}

rt_bool_t spacemit_hdmi_audio_connected(struct spacemit_hdmi_audio *hdmi)
{
    return hdmi &&
            (HWREG32((char *)hdmi->hdmi_regs + HDMI_PHY_STATUS) & HDMI_PHY_HPD);
}

rt_err_t spacemit_hdmi_audio_start(struct spacemit_hdmi_audio *hdmi)
{
    rt_err_t err;
    rt_ubase_t rate;
    rt_uint32_t clock;
    rt_uint32_t value;

    if (!hdmi)
    {
        return -RT_EINVAL;
    }

    if (!hdmi->users)
    {
        if ((err = rt_clk_set_rate(hdmi->audio_clk, HDMI_SSPA_SAMPLE_RATE)))
        {
            LOG_E("failed to set HDMI audio clock: %s", rt_strerror(err));
            return err;
        }
        if ((err = rt_reset_control_deassert(hdmi->reset)))
        {
            LOG_E("failed to deassert HDMI audio reset: %s", rt_strerror(err));
            return err;
        }

        rate = rt_clk_get_rate(hdmi->audio_clk);
        clock = HWREG32((char *)hdmi->clock_regs + HDMI_SSPA_CLOCK_CONTROL);
        if (rate != HDMI_SSPA_SAMPLE_RATE ||
            (clock & HDMI_SSPA_CLOCK_READY) != HDMI_SSPA_CLOCK_READY)
        {
            LOG_E("HDMI audio clock is not ready: rate=%lu ctrl=%08x",
                    (unsigned long)rate, clock);
            return -RT_EIO;
        }

        value = HWREG32((char *)hdmi->hdmi_regs + HDMI_AUDIO_ENABLE);
        HWREG32((char *)hdmi->hdmi_regs + HDMI_AUDIO_ENABLE) =
                value | HDMI_AUDIO_ENABLE_BIT;
        rt_hw_wmb();
        value = HWREG32((char *)hdmi->hdmi_regs + HDMI_AUDIO_ENABLE);
        if (!(value & HDMI_AUDIO_ENABLE_BIT))
        {
            LOG_E("failed to enable HDMI audio path: ctrl=%08x", value);
            return -RT_EIO;
        }

        LOG_D("HDMI path enabled: rate=%lu clk=%08x audio=%08x HPD=%d",
                (unsigned long)rate, clock, value,
                spacemit_hdmi_audio_connected(hdmi));
    }
    ++hdmi->users;

    if (!spacemit_hdmi_audio_connected(hdmi) && !hdmi->warned_unplugged)
    {
        hdmi->warned_unplugged = RT_TRUE;
        LOG_W("HDMI is not connected; audio clock will keep running");
    }

    return RT_EOK;
}

rt_err_t spacemit_hdmi_audio_stop(struct spacemit_hdmi_audio *hdmi)
{
    rt_uint32_t value;

    if (!hdmi)
    {
        return -RT_EINVAL;
    }

    if (hdmi->users > 0 && !--hdmi->users)
    {
        value = HWREG32((char *)hdmi->hdmi_regs + HDMI_AUDIO_ENABLE);
        HWREG32((char *)hdmi->hdmi_regs + HDMI_AUDIO_ENABLE) =
                value & ~HDMI_AUDIO_ENABLE_BIT;
    }

    return RT_EOK;
}

rt_ubase_t spacemit_hdmi_audio_fifo_phys(struct spacemit_hdmi_audio *hdmi)
{
    return hdmi ? hdmi->phys + HDMI_SSPA_TX_DATA : 0;
}

static void spacemit_adma_abort_hw(struct spacemit_adma *adma)
{
    rt_uint32_t control;

    control = HWREG32((char *)adma->regs + K1_ADMA_CONTROL);
    HWREG32((char *)adma->regs + K1_ADMA_CONTROL) = control | K1_ADMA_ABORT;
    rt_hw_us_delay(500);
    control = HWREG32((char *)adma->regs + K1_ADMA_CONTROL);
    HWREG32((char *)adma->regs + K1_ADMA_CONTROL) =
            control & ~K1_ADMA_ENABLE;
    HWREG32((char *)adma->regs + K1_ADMA_INT_ENABLE) = 0;
    HWREG32((char *)adma->regs + K1_ADMA_INT_STATUS) = 0;
    HWREG32(adma->control) = 0;
}

static void spacemit_adma_stop_period(struct spacemit_adma *adma)
{
    adma->running = RT_FALSE;
}

static rt_err_t spacemit_adma_build_ring(struct spacemit_adma *adma)
{
    rt_size_t index;

    if (adma->period_count * K1_ADMA_DESC_STRIDE > 0x400)
    {
        return -RT_EINVAL;
    }

    for (index = 0; index < adma->period_count; ++index)
    {
        void *descriptor = (char *)adma->descriptors +
                index * K1_ADMA_DESC_STRIDE;
        rt_uint32_t next = (rt_uint32_t)(adma->descriptors_dma +
                ((index + 1) % adma->period_count) * K1_ADMA_DESC_STRIDE);

        HWREG32((char *)descriptor + K1_ADMA_DESC_BYTE_COUNT) =
                adma->period_len;
        HWREG32((char *)descriptor + K1_ADMA_DESC_SOURCE_ADDR) =
                (rt_uint32_t)(adma->buffer_dma + index * adma->period_len);
        HWREG32((char *)descriptor + K1_ADMA_DESC_DEST_ADDR) =
                (rt_uint32_t)adma->channel.conf.dst_addr;
        HWREG32((char *)descriptor + K1_ADMA_DESC_NEXT) = next;
        if (index < 4)
        {
            LOG_D("ADMA desc[%u]: BCR=%08x SAR=%08x DAR=%08x NDR=%08x",
                    (unsigned int)index,
                    HWREG32((char *)descriptor + K1_ADMA_DESC_BYTE_COUNT),
                    HWREG32((char *)descriptor + K1_ADMA_DESC_SOURCE_ADDR),
                    HWREG32((char *)descriptor + K1_ADMA_DESC_DEST_ADDR),
                    HWREG32((char *)descriptor + K1_ADMA_DESC_NEXT));
        }
    }
    rt_hw_wmb();

    return RT_EOK;
}

static void spacemit_adma_period_done(struct spacemit_adma *adma)
{
    if (!adma->running)
    {
        return;
    }

    adma->period_index = (adma->period_index + 1) % adma->period_count;
    adma->period_done_count++;
    if (adma->period_done_count <= 4 ||
        !(adma->period_done_count % 100))
    {
        LOG_D("ADMA period done #%u", adma->period_done_count);
    }
    rt_dma_chan_done(&adma->channel, adma->period_len);
}

#ifdef RT_USING_RPMSG
static struct rt_rpmsg_device *spacemit_adma_get_rpmsg_device(void)
{
    char name[16];
    rt_device_t dev = RT_NULL;

    for (int i = 0; i < 4; ++i)
    {
        struct spacemit_rpmsg_char_ctrl *ctrl;

        rt_snprintf(name, sizeof(name), "rpmsg_char%d", i);
        dev = rt_device_find(name);
        if (dev)
        {
            ctrl = rt_container_of(dev, struct spacemit_rpmsg_char_ctrl,
                    parent);
            if (ctrl->rdev)
            {
                LOG_D("ADMA RPMsg transport found via %s", name);
                return ctrl->rdev;
            }
        }
    }

    LOG_E("ADMA RPMsg control device rpmsg_charN not found");
    return RT_NULL;
}

static rt_bool_t spacemit_adma_get_remote_addr(struct rt_rpmsg_device *rdev,
        rt_uint32_t *addr)
{
    rt_ubase_t level;
    struct rt_rpmsg_endpoint *ept;

    level = rt_spin_lock_irqsave(&rdev->lock);
    rt_list_for_each_entry(ept, &rdev->ept_nodes, list)
    {
        if (ept->info.src == RT_RPMSG_ADDR_ANY &&
            ept->info.dst != RT_RPMSG_ADDR_ANY &&
            !rt_strncmp(ept->info.name, "adma-service", RT_RPMSG_NAME_SIZE))
        {
            *addr = ept->info.dst;
            rt_spin_unlock_irqrestore(&rdev->lock, level);
            return RT_TRUE;
        }
    }
    rt_spin_unlock_irqrestore(&rdev->lock, level);

    return RT_FALSE;
}

static rt_err_t spacemit_adma_rpmsg_rx(struct rt_rpmsg_device *rdev,
        rt_uint32_t src, void *data, rt_size_t len)
{
    rt_ubase_t level;
    struct spacemit_adma *adma;
    rt_bool_t startup_ok = RT_FALSE;
    rt_bool_t period_done = RT_FALSE;

    RT_UNUSED(rdev);

    level = rt_spin_lock_irqsave(&spacemit_adma_global_lock);
    adma = spacemit_adma_global;
    rt_spin_unlock_irqrestore(&spacemit_adma_global_lock, level);

    if (adma && data && len)
    {
        adma->rpmsg_rx_count++;
        startup_ok = len >= sizeof(K1_ADMA_RPMSG_STARTUP_OK_MSG) - 1 &&
                !rt_memcmp(data, K1_ADMA_RPMSG_STARTUP_OK_MSG,
                sizeof(K1_ADMA_RPMSG_STARTUP_OK_MSG) - 1);
        period_done = *(const char *)data == '#';

        if (adma->rpmsg_rx_count <= 8 ||
            !(adma->rpmsg_rx_count % 100))
        {
            LOG_D("ADMA RPMsg rx #%u: src=%u len=%u type=%s running=%d",
                    adma->rpmsg_rx_count, src, (unsigned int)len,
                    startup_ok ? "startup-ok" :
                    (period_done ? "period" : "unknown"), adma->running);
        }
    }

    if (adma && startup_ok)
    {
        adma->rpmsg_startup_ready = RT_TRUE;
        rt_completion_done(&adma->rpmsg_startup_done);
    }
    else if (adma && period_done && adma->running)
    {
        spacemit_adma_period_done(adma);
    }

    return RT_EOK;
}

static rt_err_t spacemit_adma_create_rpmsg_endpoint(struct spacemit_adma *adma)
{
    struct rt_rpmsg_endpoint_info info;

    if (adma->rpmsg_ept)
    {
        return RT_EOK;
    }

    if (!adma->rpmsg_dev)
    {
        adma->rpmsg_dev = spacemit_adma_get_rpmsg_device();
        if (!adma->rpmsg_dev)
        {
            return -RT_EBUSY;
        }
    }

    rt_memset(&info, 0, sizeof(info));
    rt_strncpy(info.name, "adma-service", RT_RPMSG_NAME_SIZE);
    info.src = K1_ADMA_RPMSG_LOCAL_ADDR;
    info.dst = RT_RPMSG_NS_ADDR;

    adma->rpmsg_ept = rt_rpmsg_create_endpoint(adma->rpmsg_dev,
            &info, spacemit_adma_rpmsg_rx);
    if (rt_is_err(adma->rpmsg_ept))
    {
        rt_err_t err = rt_ptr_err(adma->rpmsg_ept);

        adma->rpmsg_ept = RT_NULL;
        LOG_E("ADMA RPMsg endpoint create failed: %s", rt_strerror(err));
        return err;
    }

    LOG_D("ADMA RPMsg endpoint created: src=%u",
            K1_ADMA_RPMSG_LOCAL_ADDR);

    return RT_EOK;
}

static rt_err_t spacemit_adma_ensure_rpmsg(struct spacemit_adma *adma)
{
    rt_err_t err;
    rt_tick_t deadline;
    rt_uint32_t remote_addr = RT_RPMSG_ADDR_ANY;

#ifdef RT_SOC_SPACEMIT_K1X_RPROC
    err = spacemit_k1x_rproc_boot("esos.elf");
    if (err)
    {
        LOG_E("RCPU firmware is not ready: %s", rt_strerror(err));
        return err;
    }
#else
    LOG_E("ADMA requires K1X RCPU remoteproc");
    return -RT_EBUSY;
#endif

    err = spacemit_adma_create_rpmsg_endpoint(adma);
    if (err)
    {
        LOG_E("ADMA RPMsg endpoint is not ready: %s", rt_strerror(err));
        return err;
    }

    deadline = rt_tick_get() +
            rt_tick_from_millisecond(K1_ADMA_RPMSG_BOOT_TIMEOUT_MS);
    while (!spacemit_adma_get_remote_addr(adma->rpmsg_dev, &remote_addr))
    {
        if ((rt_int32_t)(rt_tick_get() - deadline) >= 0)
        {
            LOG_E("RCPU adma-service is not ready");
            spacemit_k1x_rproc_dump_status();
            return -RT_EBUSY;
        }
        rt_thread_mdelay(10);
    }

    if (adma->rpmsg_remote_addr != remote_addr)
    {
        LOG_D("ADMA RPMsg remote service: dst=%u", remote_addr);
        adma->rpmsg_remote_addr = remote_addr;
        adma->rpmsg_started = RT_FALSE;
        adma->rpmsg_startup_ready = RT_FALSE;
    }

    if (!adma->rpmsg_started)
    {
        rt_completion_init(&adma->rpmsg_startup_done);
        adma->rpmsg_startup_ready = RT_FALSE;
        err = rt_rpmsg_sendto_wait(adma->rpmsg_ept, remote_addr,
                K1_ADMA_RPMSG_STARTUP_MSG,
                sizeof(K1_ADMA_RPMSG_STARTUP_MSG) - 1,
                rt_tick_from_millisecond(K1_ADMA_RPMSG_SEND_TIMEOUT_MS));
        if (err)
        {
            LOG_E("ADMA RPMsg startup failed: %s", rt_strerror(err));
            return err;
        }
        LOG_D("ADMA RPMsg startup sent");

        err = rt_completion_wait(&adma->rpmsg_startup_done,
                rt_tick_from_millisecond(K1_ADMA_RPMSG_SEND_TIMEOUT_MS));
        if (err || !adma->rpmsg_startup_ready)
        {
            LOG_E("ADMA RPMsg startup reply timeout");
            spacemit_k1x_rproc_dump_status();
            return -RT_ETIMEOUT;
        }

        adma->rpmsg_started = RT_TRUE;
        LOG_D("ADMA RPMsg startup acknowledged");
    }

    return RT_EOK;
}
#else
static rt_err_t spacemit_adma_ensure_rpmsg(struct spacemit_adma *adma)
{
    RT_UNUSED(adma);

    LOG_E("ADMA requires RT_USING_RPMSG");
    return -RT_EBUSY;
}
#endif

static struct rt_dma_chan *spacemit_adma_request(struct rt_dma_controller *controller,
        struct rt_device *slave, void *fw_data)
{
    struct spacemit_adma *adma = rt_container_of(controller,
            struct spacemit_adma, parent);

    RT_UNUSED(slave);
    RT_UNUSED(fw_data);

    if (adma->allocated)
    {
        return rt_err_ptr(-RT_EBUSY);
    }

    adma->allocated = RT_TRUE;
    return &adma->channel;
}

static rt_err_t spacemit_adma_release(struct rt_dma_chan *channel)
{
    struct spacemit_adma *adma = rt_container_of(channel,
            struct spacemit_adma, channel);

    spacemit_adma_stop_period(adma);
    adma->allocated = RT_FALSE;

    return RT_EOK;
}

static rt_err_t spacemit_adma_config(struct rt_dma_chan *channel,
        struct rt_dma_slave_config *config)
{
    LOG_D("ADMA config: dir=%d src=%08lx dst=%08lx sw=%u dw=%u burst=%u/%u",
            config->direction,
            (unsigned long)config->src_addr,
            (unsigned long)config->dst_addr,
            (unsigned int)config->src_addr_width,
            (unsigned int)config->dst_addr_width,
            (unsigned int)config->src_maxburst,
            (unsigned int)config->dst_maxburst);
    if (config->direction != RT_DMA_MEM_TO_DEV ||
        config->dst_addr_width != RT_DMA_SLAVE_BUSWIDTH_4_BYTES)
    {
        LOG_E("ADMA config rejected");
        return -RT_EINVAL;
    }

    RT_UNUSED(channel);
    return RT_EOK;
}

static rt_err_t spacemit_adma_prep_cyclic(struct rt_dma_chan *channel,
        rt_ubase_t buffer, rt_size_t length, rt_size_t period,
        enum rt_dma_transfer_direction direction)
{
    rt_size_t count;
    struct spacemit_adma *adma = rt_container_of(channel,
            struct spacemit_adma, channel);

    LOG_D("ADMA prep cyclic: buf=%08lx len=%u period=%u dir=%d dst=%08lx",
            (unsigned long)buffer, (unsigned int)length,
            (unsigned int)period, direction,
            (unsigned long)channel->conf.dst_addr);
    if (direction != RT_DMA_MEM_TO_DEV || !period || length % period ||
        buffer > 0xffffffffUL || channel->conf.dst_addr > 0xffffffffUL)
    {
        LOG_E("ADMA prep rejected");
        return -RT_EINVAL;
    }

    count = length / period;
    if (!count)
    {
        return -RT_EINVAL;
    }

    adma->buffer_dma = buffer;
    adma->period_len = period;
    adma->period_count = count;
    adma->period_index = 0;
    adma->period_tick = (rt_tick_t)(((rt_uint64_t)period *
            RT_TICK_PER_SECOND + K1_ADMA_HDMI_BYTES_PER_SECOND - 1U) /
            K1_ADMA_HDMI_BYTES_PER_SECOND);
    if (!adma->period_tick)
    {
        adma->period_tick = 1;
    }
    LOG_D("ADMA prep done: count=%u tick=%u",
            (unsigned int)adma->period_count,
            (unsigned int)adma->period_tick);

    return RT_EOK;
}

static rt_err_t spacemit_adma_start(struct rt_dma_chan *channel)
{
    rt_err_t err;
    rt_uint32_t control;
    struct spacemit_adma *adma = rt_container_of(channel,
            struct spacemit_adma, channel);

    LOG_D("ADMA start begin");
    if ((err = spacemit_adma_ensure_rpmsg(adma)))
    {
        LOG_E("ADMA remote service failed: %s", rt_strerror(err));
        return err;
    }

    control = HWREG32((char *)adma->regs + K1_ADMA_CONTROL);
    LOG_D("ADMA start hw state: BCR=%08x SAR=%08x DAR=%08x NDR=%08x "
          "DCR=%08x CUR=%08x IER=%08x ISR=%08x CTRL=%08x",
            HWREG32((char *)adma->regs + K1_ADMA_BYTE_COUNT),
            HWREG32((char *)adma->regs + K1_ADMA_SOURCE_ADDR),
            HWREG32((char *)adma->regs + K1_ADMA_DEST_ADDR),
            HWREG32((char *)adma->regs + K1_ADMA_NEXT_DESC),
            control,
            HWREG32((char *)adma->regs + K1_ADMA_CURRENT_DESC),
            HWREG32((char *)adma->regs + K1_ADMA_INT_ENABLE),
            HWREG32((char *)adma->regs + K1_ADMA_INT_STATUS),
            HWREG32(adma->control));
    if (control & K1_ADMA_ENABLE)
    {
        HWREG32((char *)adma->regs + K1_ADMA_CONTROL) =
                control | K1_ADMA_ABORT;
        rt_hw_us_delay(500);
        HWREG32((char *)adma->regs + K1_ADMA_CONTROL) =
                control & ~K1_ADMA_ENABLE;
    }

    HWREG32((char *)adma->regs + K1_ADMA_INT_ENABLE) = 0;
    HWREG32((char *)adma->regs + K1_ADMA_INT_STATUS) = 0;
    control = K1_ADMA_SAMPLE_BITS(5) | K1_ADMA_ABORT |
            K1_ADMA_DST_HOLD | K1_ADMA_SRC_INCREMENT;
    if (adma->unpack_sample)
    {
        control |= K1_ADMA_UNPACK;
    }
    adma->period_index = 0;
    adma->period_done_count = 0;
    LOG_D("ADMA build ring begin");
    if ((err = spacemit_adma_build_ring(adma)))
    {
        LOG_E("ADMA build ring failed: %s", rt_strerror(err));
        return err;
    }
    LOG_D("ADMA build ring done");

    HWREG32((char *)adma->regs + K1_ADMA_NEXT_DESC) =
            (rt_uint32_t)adma->descriptors_dma;
    HWREG32((char *)adma->regs + K1_ADMA_CONTROL) = control;
    HWREG32(adma->control) = adma->unpack_sample ? 0 : K1_ADMA_HDMI_ENABLE;
    HWREG32((char *)adma->regs + K1_ADMA_DEST_ADDR) =
            (rt_uint32_t)adma->channel.conf.dst_addr;
    HWREG32((char *)adma->regs + K1_ADMA_INT_ENABLE) = 1;
    rt_hw_wmb();

    /* ABORT is a command bit and clears itself. Reads DCR back before
     * enabling the channel so ABORT is not asserted together with CH_EN. */
    adma->running = RT_TRUE;
    control = HWREG32((char *)adma->regs + K1_ADMA_CONTROL);
    HWREG32((char *)adma->regs + K1_ADMA_CONTROL) = control |
            K1_ADMA_FETCH_NEXT_DESC | K1_ADMA_ENABLE;
    rt_hw_wmb();

    LOG_D("ADMA started: DCR=%08x CUR=%08x NDR=%08x CTRL=%08x",
            HWREG32((char *)adma->regs + K1_ADMA_CONTROL),
            HWREG32((char *)adma->regs + K1_ADMA_CURRENT_DESC),
            HWREG32((char *)adma->regs + K1_ADMA_NEXT_DESC),
            HWREG32(adma->control));
    return RT_EOK;
}

static rt_err_t spacemit_adma_stop(struct rt_dma_chan *channel)
{
    struct spacemit_adma *adma = rt_container_of(channel,
            struct spacemit_adma, channel);

    spacemit_adma_stop_period(adma);

    spacemit_adma_abort_hw(adma);

    return RT_EOK;
}

static const struct rt_dma_controller_ops spacemit_adma_ops =
{
    .request_chan = spacemit_adma_request,
    .release_chan = spacemit_adma_release,
    .start = spacemit_adma_start,
    .stop = spacemit_adma_stop,
    .config = spacemit_adma_config,
    .prep_cyclic = spacemit_adma_prep_cyclic,
};

static rt_err_t spacemit_adma_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint64_t address;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_adma *adma = rt_calloc(1, sizeof(*adma));

    if (!adma)
    {
        return -RT_ENOMEM;
    }

    adma->dev = dev;
    adma->regs = rt_dm_dev_iomap(dev, 0);
    adma->control = rt_dm_dev_iomap(dev, 1);
    adma->descriptors = rt_dm_dev_iomap(dev, 2);
    if (!adma->regs || !adma->control || !adma->descriptors ||
        rt_dm_dev_get_address(dev, 2, &address, RT_NULL) ||
        address > 0xffffffffULL)
    {
        err = -RT_EIO;
        goto _fail;
    }
    adma->descriptors_dma = (rt_ubase_t)address;
    adma->unpack_sample = !rt_dm_dev_prop_read_bool(dev, "hdmi-sample");
#ifdef RT_USING_RPMSG
    adma->rpmsg_remote_addr = RT_RPMSG_ADDR_ANY;
    rt_completion_init(&adma->rpmsg_startup_done);
#endif

    adma->parent.dev = dev;
    adma->parent.ops = &spacemit_adma_ops;
    rt_dma_controller_add_direction(&adma->parent, RT_DMA_MEM_TO_DEV);
    rt_dma_controller_set_addr_mask(&adma->parent, RT_DMA_ADDR_MASK(32));
    if ((err = rt_dma_controller_register(&adma->parent)))
    {
        goto _fail;
    }

    dev->user_data = adma;
#ifdef RT_USING_RPMSG
    rt_spin_lock(&spacemit_adma_global_lock);
    spacemit_adma_global = adma;
    rt_spin_unlock(&spacemit_adma_global_lock);
#endif
    LOG_D("K1 HDMI ADMA ready in cyclic descriptor mode, hdmi-sample=%d",
            !adma->unpack_sample);

    return RT_EOK;

_fail:
    if (adma->regs)
    {
        rt_iounmap(adma->regs);
    }
    if (adma->control)
    {
        rt_iounmap(adma->control);
    }
    if (adma->descriptors)
    {
        rt_iounmap(adma->descriptors);
    }
    rt_free(adma);
    return err;
}

static rt_err_t spacemit_adma_remove(struct rt_platform_device *pdev)
{
    struct spacemit_adma *adma = pdev->parent.user_data;

    if (!adma)
    {
        return RT_EOK;
    }

    if (rt_dma_controller_unregister(&adma->parent))
    {
        return -RT_EBUSY;
    }

    spacemit_adma_stop_period(adma);
#ifdef RT_USING_RPMSG
    rt_spin_lock(&spacemit_adma_global_lock);
    if (spacemit_adma_global == adma)
    {
        spacemit_adma_global = RT_NULL;
    }
    rt_spin_unlock(&spacemit_adma_global_lock);
    if (adma->rpmsg_dev && adma->rpmsg_ept)
    {
        rt_rpmsg_destroy_endpoint(adma->rpmsg_dev, adma->rpmsg_ept);
    }
#endif
    rt_iounmap(adma->regs);
    rt_iounmap(adma->control);
    rt_iounmap(adma->descriptors);
    rt_free(adma);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_adma_ofw_ids[] =
{
    { .compatible = "spacemit,k1x-adma" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_adma_driver =
{
    .name = "spacemit-hdmi-adma",
    .ids = spacemit_adma_ofw_ids,
    .probe = spacemit_adma_probe,
    .remove = spacemit_adma_remove,
};

static int spacemit_adma_register(void)
{
    rt_platform_driver_register(&spacemit_adma_driver);
    return 0;
}
INIT_SUBSYS_EXPORT(spacemit_adma_register);

static void spacemit_hdmi_audio_free(struct spacemit_hdmi_audio *hdmi)
{
    if (!hdmi)
    {
        return;
    }

    if (!rt_is_err_or_null(hdmi->reset))
    {
        rt_reset_control_assert(hdmi->reset);
        rt_reset_control_put(hdmi->reset);
    }
    if (!rt_is_err_or_null(hdmi->audio_clk))
    {
        rt_clk_disable_unprepare(hdmi->audio_clk);
        rt_clk_put(hdmi->audio_clk);
    }
    if (!rt_is_err_or_null(hdmi->hdmi_clk))
    {
        rt_clk_disable_unprepare(hdmi->hdmi_clk);
        rt_clk_put(hdmi->hdmi_clk);
    }
    if (hdmi->regs)
    {
        rt_iounmap(hdmi->regs);
    }
    if (hdmi->clock_regs)
    {
        rt_iounmap(hdmi->clock_regs);
    }
    if (hdmi->hdmi_regs)
    {
        rt_iounmap(hdmi->hdmi_regs);
    }
    rt_free(hdmi);
}

static rt_err_t spacemit_hdmi_audio_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint64_t address;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_hdmi_audio *hdmi = rt_calloc(1, sizeof(*hdmi));

    if (!hdmi)
    {
        return -RT_ENOMEM;
    }

    hdmi->dev = dev;
    hdmi->np = dev->ofw_node;
    hdmi->regs = rt_dm_dev_iomap(dev, 0);
    hdmi->clock_regs = rt_dm_dev_iomap(dev, 1);
    hdmi->hdmi_regs = rt_ioremap((void *)HDMI_PHY_BASE, HDMI_PHY_SIZE);
    if (!hdmi->regs || !hdmi->clock_regs || !hdmi->hdmi_regs ||
        rt_dm_dev_get_address(dev, 0, &address, RT_NULL))
    {
        err = -RT_EIO;
        goto _fail;
    }
    hdmi->phys = (rt_ubase_t)address;

    hdmi->audio_clk = rt_clk_get_by_index(dev, 0);
    if (rt_is_err(hdmi->audio_clk))
    {
        err = rt_ptr_err(hdmi->audio_clk);
        goto _fail;
    }
    if ((err = rt_clk_set_rate(hdmi->audio_clk, HDMI_SSPA_SAMPLE_RATE)))
    {
        goto _fail;
    }
    if ((err = rt_clk_prepare_enable(hdmi->audio_clk)))
    {
        goto _fail;
    }

    hdmi->hdmi_clk = rt_clk_get_by_index(dev, 1);
    if (!rt_is_err(hdmi->hdmi_clk))
    {
        if ((err = rt_clk_prepare_enable(hdmi->hdmi_clk)))
        {
            goto _fail;
        }
    }

    hdmi->reset = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(hdmi->reset))
    {
        err = rt_ptr_err(hdmi->reset);
        goto _fail;
    }
    if ((err = rt_reset_control_deassert(hdmi->reset)))
    {
        goto _fail;
    }

    LOG_D("%s: clock=%lu Hz ctrl=%08x", rt_dm_dev_get_name(dev),
            (unsigned long)rt_clk_get_rate(hdmi->audio_clk),
            HWREG32((char *)hdmi->clock_regs + HDMI_SSPA_CLOCK_CONTROL));

    rt_spin_lock(&hdmi_nodes_lock);
    rt_list_insert_before(&hdmi_nodes, &hdmi->list);
    rt_spin_unlock(&hdmi_nodes_lock);

    dev->user_data = hdmi;
    rt_dm_dev_bind_fwdata(dev, RT_NULL, hdmi);

    LOG_D("%s: HDMI SSPA ready, HPD=%d", rt_dm_dev_get_name(dev),
            spacemit_hdmi_audio_connected(hdmi));

    return RT_EOK;

_fail:
    spacemit_hdmi_audio_free(hdmi);
    return err;
}

static rt_err_t spacemit_hdmi_audio_remove(struct rt_platform_device *pdev)
{
    struct spacemit_hdmi_audio *hdmi = pdev->parent.user_data;

    if (!hdmi)
    {
        return RT_EOK;
    }

    rt_spin_lock(&hdmi_nodes_lock);
    rt_list_remove(&hdmi->list);
    rt_spin_unlock(&hdmi_nodes_lock);

    rt_dm_dev_unbind_fwdata(&pdev->parent, RT_NULL);
    spacemit_hdmi_audio_free(hdmi);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_hdmi_audio_ofw_ids[] =
{
    { .compatible = "spacemit,spacemit-snd-sspa" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_hdmi_audio_driver =
{
    .name = "spacemit-hdmi-audio",
    .ids = spacemit_hdmi_audio_ofw_ids,
    .probe = spacemit_hdmi_audio_probe,
    .remove = spacemit_hdmi_audio_remove,
};

static int spacemit_hdmi_audio_register(void)
{
    rt_platform_driver_register(&spacemit_hdmi_audio_driver);
    return 0;
}
INIT_DEVICE_EXPORT(spacemit_hdmi_audio_register);
