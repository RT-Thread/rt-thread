/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the people's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <aw-alsa-lib/pcm_plugin.h>
#include <aw-alsa-lib/pcm_config.h>
#include "pcm_local.h"
#include "pcm_direct.h"

static int snoop_timestamp(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dsnoop = pcm->private_data;
    snd_pcm_uframes_t ptr1 = -2LL /* invalid value */, ptr2;

    while (1) {
        ptr2 = *dsnoop->spcm->hw.ptr;
        if (ptr1 == ptr2)
            break;
        ptr1 = ptr2;
    }
    dsnoop->slave_hw_ptr = ptr1;
    return 0;
}

static void snoop_areas(snd_pcm_direct_t *dsnoop,
            const snd_pcm_channel_area_t *src_areas,
            const snd_pcm_channel_area_t *dst_areas,
            snd_pcm_uframes_t src_ofs,
            snd_pcm_uframes_t dst_ofs,
            snd_pcm_uframes_t size)
{
    unsigned int chn, schn, channels;
    snd_pcm_format_t format;

    channels = dsnoop->channels;
    format = dsnoop->shmptr->s.format;

    if (dsnoop->spcm->fast_ops->cache_update)
        dsnoop->spcm->fast_ops->cache_update(
            dsnoop->spcm->fast_op_arg, src_ofs, size);
    if (dsnoop->interleaved) {
        unsigned int fbytes = snd_pcm_format_physical_width(format) / 8;
        memcpy(((char *)dst_areas[0].addr) + (dst_ofs * channels * fbytes),
               ((char *)src_areas[0].addr) + (src_ofs * channels * fbytes),
               size * channels * fbytes);
    } else {
#if 0
        awalsa_info("src_ofs:%u(0x%x), size:%u(0x%x)\n",
                src_ofs, src_ofs,
                size, size);
#endif
        for (chn = 0; chn < channels; chn++) {
            schn = dsnoop->bindings ? dsnoop->bindings[chn] : chn;
            snd_pcm_area_copy(&dst_areas[chn], dst_ofs, &src_areas[schn], src_ofs, size, format);
        }
    }
}

static void snd_pcm_dsnoop_sync_area(snd_pcm_t *pcm, snd_pcm_uframes_t slave_hw_ptr, snd_pcm_uframes_t size)
{
    snd_pcm_direct_t *dsnoop = pcm->private_data;
    snd_pcm_uframes_t hw_ptr = dsnoop->hw_ptr;
    snd_pcm_uframes_t transfer;
    const snd_pcm_channel_area_t *src_areas, *dst_areas;

    /* add sample areas here */
    dst_areas = snd_pcm_mmap_areas(pcm);
    src_areas = snd_pcm_mmap_areas(dsnoop->spcm);

    hw_ptr %= pcm->buffer_size;
    slave_hw_ptr %= dsnoop->slave_buffer_size;

    while (size > 0) {
        transfer = hw_ptr + size > pcm->buffer_size ? pcm->buffer_size - hw_ptr : size;
        transfer = slave_hw_ptr + transfer > dsnoop->slave_buffer_size ?
            dsnoop->slave_buffer_size - slave_hw_ptr : transfer;
        size -= transfer;
        snoop_areas(dsnoop, src_areas, dst_areas, slave_hw_ptr, hw_ptr, transfer);
        slave_hw_ptr += transfer;
        slave_hw_ptr %= dsnoop->slave_buffer_size;
        hw_ptr += transfer;
        hw_ptr %= pcm->buffer_size;
    }

}

static int snd_pcm_dsnoop_sync_ptr(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dsnoop = pcm->private_data;
    snd_pcm_uframes_t slave_hw_ptr, old_slave_hw_ptr, avail;
    snd_pcm_sframes_t diff;
    int err;

    switch (snd_pcm_state(dsnoop->spcm)) {
    case SND_PCM_STATE_DISCONNECTED:
        dsnoop->state = SNDRV_PCM_STATE_DISCONNECTED;
        return -ENODEV;
    case SND_PCM_STATE_XRUN:
        if ((err = snd_pcm_direct_slave_recover(dsnoop)) < 0)
            return err;
        break;
    default:
        break;
    }

    if (dsnoop->slowptr)
        snd_pcm_hwsync(dsnoop->spcm);
    old_slave_hw_ptr = dsnoop->slave_hw_ptr;
    snoop_timestamp(pcm);
    slave_hw_ptr = dsnoop->slave_hw_ptr;
    diff = slave_hw_ptr - old_slave_hw_ptr;
    if (diff > pcm->stop_threshold) {
        awalsa_debug("old:%lu, new:%lu\n", old_slave_hw_ptr, slave_hw_ptr);
    }
    if (diff == 0)      /* fast path */
        return 0;
    if (diff < 0) {
        slave_hw_ptr += dsnoop->slave_boundary;
        diff = slave_hw_ptr - old_slave_hw_ptr;
    }
    snd_pcm_dsnoop_sync_area(pcm, old_slave_hw_ptr, diff);
    dsnoop->hw_ptr += diff;
    dsnoop->hw_ptr %= pcm->boundary;
    // printf("sync ptr diff = %li\n", diff);
    if (pcm->stop_threshold >= pcm->boundary)   /* don't care */
        return 0;
    /*awalsa_debug("hw_ptr=%p, appl_ptr=%p, diff=%d, avail=%d, stop_threshold=%u\n",*/
        /*dsnoop->hw_ptr, dsnoop->appl_ptr,*/
        /*diff, snd_pcm_mmap_capture_hw_avail(pcm), pcm->stop_threshold);*/
    if ((avail = snd_pcm_mmap_capture_hw_avail(pcm)) >= pcm->stop_threshold) {
        /*gettimestamp(&dsnoop->trigger_tstamp, pcm->tstamp_type);*/
        dsnoop->state = SND_PCM_STATE_XRUN;
        dsnoop->avail_max = avail;
        return -EPIPE;
    }
    if (avail > dsnoop->avail_max)
        dsnoop->avail_max = avail;
    return 0;


    return 0;
}

static int snd_pcm_dsnoop_close(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dsnoop = pcm->private_data;

    snd_pcm_direct_destroy_poll_index(dsnoop);
    snd_pcm_direct_semaphore_down(dsnoop, DIRECT_IPC_SEM_CLIENT);
    snd_pcm_direct_last_pcm_drop(dsnoop);
    snd_pcm_close(dsnoop->spcm);
    snd_pcm_direct_semaphore_shm_discard(dsnoop);
    pcm->private_data = NULL;
    free(dsnoop);

    return 0;
}

static snd_pcm_state_t snd_pcm_dsnoop_state(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dsnoop = pcm->private_data;

    snd_pcm_state_t state;
    state = snd_pcm_state(dsnoop->spcm);
    switch(state) {
    case SND_PCM_STATE_SUSPENDED:
    case SND_PCM_STATE_DISCONNECTED:
        dsnoop->state = state;
        return state;
    case SND_PCM_STATE_XRUN:
        snd_pcm_direct_slave_recover(dsnoop);
        break;
    default:
        break;
    }
    return dsnoop->state;
}

static int snd_pcm_dsnoop_delay(snd_pcm_t *pcm, snd_pcm_sframes_t *delayp)
{
    snd_pcm_direct_t *dsnoop = pcm->private_data;
    int err;

    switch(dsnoop->state) {
    case SNDRV_PCM_STATE_DRAINING:
    case SNDRV_PCM_STATE_RUNNING:
        err = snd_pcm_dsnoop_sync_ptr(pcm);
        if (err < 0)
            return err;
        /* Fall through */
    case SNDRV_PCM_STATE_PREPARED:
    case SNDRV_PCM_STATE_SUSPENDED:
        *delayp = snd_pcm_mmap_capture_hw_avail(pcm);
        return 0;
    case SNDRV_PCM_STATE_XRUN:
        return -EPIPE;
    case SNDRV_PCM_STATE_DISCONNECTED:
        return -ENODEV;
    default:
        return -EBADFD;
    }
}

static int snd_pcm_dsnoop_hwsync(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dsnoop = pcm->private_data;

    switch(dsnoop->state) {
    case SNDRV_PCM_STATE_DRAINING:
    case SNDRV_PCM_STATE_RUNNING:
        return snd_pcm_dsnoop_sync_ptr(pcm);
    case SNDRV_PCM_STATE_PREPARED:
    case SNDRV_PCM_STATE_SUSPENDED:
        return 0;
    case SNDRV_PCM_STATE_XRUN:
        return -EPIPE;
    case SNDRV_PCM_STATE_DISCONNECTED:
        return -ENODEV;
    default:
        return -EBADFD;
    }
}

static int snd_pcm_dsnoop_reset(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dsnoop = pcm->private_data;
    dsnoop->hw_ptr %= pcm->period_size;
    dsnoop->appl_ptr = dsnoop->hw_ptr;
    dsnoop->slave_appl_ptr = dsnoop->slave_hw_ptr;
    return 0;
}

static int snd_pcm_dsnoop_start(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dsnoop = pcm->private_data;

    awalsa_debug("\n");
    if (dsnoop->state != SND_PCM_STATE_PREPARED)
        return -EBADFD;
    snd_pcm_hwsync(dsnoop->spcm);
    snoop_timestamp(pcm);
    dsnoop->slave_appl_ptr = dsnoop->slave_hw_ptr;
    dsnoop->state = SND_PCM_STATE_RUNNING;

    return 0;
}

static int snd_pcm_dsnoop_drop(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dsnoop = pcm->private_data;
    if (dsnoop->state == SND_PCM_STATE_OPEN)
        return -EBADFD;
    dsnoop->state = SND_PCM_STATE_SETUP;

    awalsa_debug("\n");
    return snd_pcm_direct_last_pcm_drop(dsnoop);
}

static int __snd_pcm_dsnoop_drain(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dsnoop = pcm->private_data;
    snd_pcm_uframes_t stop_threshold;
    int err;

    awalsa_debug("\n");
    if (dsnoop->state == SND_PCM_STATE_OPEN)
        return -EBADFD;
    stop_threshold = pcm->stop_threshold;
    if (pcm->stop_threshold > pcm->buffer_size)
        pcm->stop_threshold = pcm->buffer_size;
    while (dsnoop->state == SND_PCM_STATE_RUNNING) {
        awalsa_debug("\n");
        err = snd_pcm_dsnoop_sync_ptr(pcm);
        if (err < 0)
            break;
        __snd_pcm_wait_in_lock(pcm, -1);
    }
    pcm->stop_threshold = stop_threshold;

    return snd_pcm_dsnoop_drop(pcm);
}

static int snd_pcm_dsnoop_drain(snd_pcm_t *pcm)
{
    int err;

    awalsa_debug("\n");
    snd_pcm_lock(pcm);
    err = __snd_pcm_dsnoop_drain(pcm);
    snd_pcm_unlock(pcm);
    return err;
}

static int snd_pcm_dsnoop_pause(snd_pcm_t *pcm ATTRIBUTE_UNUSED, int enable ATTRIBUTE_UNUSED)
{
    return -EIO;
}

static snd_pcm_sframes_t snd_pcm_dsnoop_writei(snd_pcm_t *pcm ATTRIBUTE_UNUSED, const void *buffer ATTRIBUTE_UNUSED, snd_pcm_uframes_t size ATTRIBUTE_UNUSED)
{
    return -ENODEV;
}

static snd_pcm_sframes_t snd_pcm_dsnoop_avail_update(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dsnoop = pcm->private_data;
    int err;

    if (dsnoop->state == SND_PCM_STATE_RUNNING) {
        err = snd_pcm_dsnoop_sync_ptr(pcm);
        if (err < 0)
            return err;
    }
    if (dsnoop->state == SND_PCM_STATE_XRUN)
        return -EPIPE;

    return snd_pcm_mmap_capture_avail(pcm);
}

static snd_pcm_sframes_t snd_pcm_dsnoop_mmap_commit(snd_pcm_t *pcm,
                            snd_pcm_uframes_t offset ATTRIBUTE_UNUSED,
                            snd_pcm_uframes_t size)
{
    snd_pcm_direct_t *dsnoop = pcm->private_data;
    int err;

    switch (snd_pcm_state(dsnoop->spcm)) {
    case SND_PCM_STATE_XRUN:
        if ((err = snd_pcm_direct_slave_recover(dsnoop)) < 0)
            return err;
        break;
    case SND_PCM_STATE_SUSPENDED:
        return -ESTRPIPE;
    default:
        break;
    }
    if (dsnoop->state == SND_PCM_STATE_RUNNING) {
        err = snd_pcm_dsnoop_sync_ptr(pcm);
        if (err < 0)
            return err;
    }

    snd_pcm_mmap_appl_forward(pcm, size);

    return size;
}

static void snd_pcm_dsnoop_dump(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dsnoop = pcm->private_data;

    printf("Direct Snoop PCM\n");
    if (pcm->setup) {
        printf("Its setup is:\n");
        snd_pcm_dump_setup(pcm);
    }
    if (dsnoop->spcm)
        snd_pcm_dump(dsnoop->spcm);
}

static const snd_pcm_ops_t snd_pcm_dsnoop_ops = {
    .close      = snd_pcm_dsnoop_close,
    .hw_refine  = snd_pcm_direct_hw_refine,
    .hw_params  = snd_pcm_direct_hw_params,
    .hw_free    = snd_pcm_direct_hw_free,
    .sw_params  = snd_pcm_direct_sw_params,
    .channel_info   = snd_pcm_direct_channel_info,
    .dump       = snd_pcm_dsnoop_dump,
    .mmap       = snd_pcm_direct_mmap,
    .munmap     = snd_pcm_direct_munmap,
};

static const snd_pcm_fast_ops_t snd_pcm_dsnoop_fast_ops = {
    .state      = snd_pcm_dsnoop_state,
    .hwsync     = snd_pcm_dsnoop_hwsync,
    .delay      = snd_pcm_dsnoop_delay,
    .prepare    = snd_pcm_direct_prepare,
    .reset      = snd_pcm_dsnoop_reset,
    .start      = snd_pcm_dsnoop_start,
    .drop       = snd_pcm_dsnoop_drop,
    .drain      = snd_pcm_dsnoop_drain,
    .pause      = snd_pcm_dsnoop_pause,
    .writei     = snd_pcm_dsnoop_writei,
    .readi      = snd_pcm_mmap_readi,
    .avail_update   = snd_pcm_dsnoop_avail_update,
    .mmap_commit    = snd_pcm_dsnoop_mmap_commit,
    .wait       = snd_pcm_direct_wait,
};

int _snd_pcm_dsnoop_open(snd_pcm_t **pcmp, const snd_pcm_config_t *pcm_config,
        snd_pcm_stream_t stream, int mode)
{
    const snd_pcm_dsnoop_config_t *dsnoop_config = (const snd_pcm_dsnoop_config_t *)(pcm_config->config);
    int ret = -1, first_instance;
    snd_pcm_t *pcm = NULL, *spcm = NULL;
    snd_pcm_direct_t *dsnoop = NULL;
    const snd_pcm_config_t *sconf = NULL;
    struct slave_params params;

    awalsa_debug("\n");
    if (stream != SND_PCM_STREAM_CAPTURE) {
        awalsa_err("The dsnoop plugin supports only capture stream");
        return -EINVAL;
    }

    sconf = snd_pcm_config_get_config(dsnoop_config->slave.pcm);
    if (!sconf) {
        awalsa_err("can't find pcm slave:%s\n", dsnoop_config->slave.pcm);
        return -EINVAL;
    }
    if (strcmp(sconf->type, "hw") != 0) {
        awalsa_err("unsupport slave type:%s, only support hw\n", sconf->type);
        return -EINVAL;
    }

    params.format = SND_PCM_FORMAT_S16_LE;
        params.rate = 48000;
        params.channels = 2;
        params.period_size = -1;
        params.buffer_size = -1;
        params.period_time = -1;
        params.buffer_time = -1;
    awalsa_debug("\n");

    ret = snd_pcm_slave_conf_hw_params(&dsnoop_config->slave, &params);
    if (ret < 0)
        return ret;

    dsnoop = snd_malloc(sizeof(snd_pcm_direct_t));
    if (!dsnoop) {
        awalsa_err("no memory\n");
        ret = -ENOMEM;
        goto _err_nosem;
    }

    dsnoop->ipc_key = dsnoop_config->ipc_key;

    ret = snd_pcm_new(&pcm, dsnoop->type = SND_PCM_TYPE_DSNOOP, pcm_config->name, stream, mode);
    if (ret < 0) {
        awalsa_err("failed to new hw pcm\n");
        goto _err_nosem;
    }

    first_instance = ret = snd_pcm_direct_semaphore_shm_create_or_connect(dsnoop);
    if (ret < 0) {
        awalsa_err("unable to create IPC semaphore shm instance (return: %d)\n", ret);
        goto _err;
    }

    pcm->ops = &snd_pcm_dsnoop_ops;
    pcm->fast_ops = &snd_pcm_dsnoop_fast_ops;
    pcm->private_data = dsnoop;

    dsnoop->state = SND_PCM_STATE_OPEN;
    dsnoop->sync_ptr = snd_pcm_dsnoop_sync_ptr;

retry:
    if (first_instance) {
        awalsa_debug("first open, dsnoop=%p\n", dsnoop);
        ret = snd_pcm_open_config(&spcm, sconf, stream, mode);
        if (ret < 0) {
            awalsa_err("unable to open slave\n");
            goto _err;
        }
        if (snd_pcm_type(spcm) != SND_PCM_TYPE_HW) {
            awalsa_err("dsnoop plugin can be only connected to hw plugin");
            goto _err;
        }
        ret = snd_pcm_direct_initialize_slave(dsnoop, spcm, &params);
        if (ret < 0) {
            awalsa_err("unable to initialize slave\n");
            goto _err;
        }
        dsnoop->spcm = spcm;

        dsnoop->shmptr->type = spcm->type;
    } else {
        awalsa_debug("second open, dsnoop=%p\n", dsnoop);
        ret = snd_pcm_open_config(&spcm, sconf, stream, mode | SND_PCM_APPEND);
        if (ret < 0) {
            if (ret == -EBADFD) {
                first_instance = 1;
                goto retry;
            }
            awalsa_err("unable to open slave\n");
            goto _err;
        }
        if (snd_pcm_type(spcm) != SND_PCM_TYPE_HW) {
            awalsa_err("dsnoop plugin can be only connected to hw plugin");
            ret = -EINVAL;
            goto _err;
        }
        ret = snd_pcm_direct_initialize_secondary_slave(dsnoop, spcm, &params);
        if (ret < 0) {
            awalsa_err("unable to initialize slave\n");
            goto _err;
        }
        dsnoop->spcm = spcm;
    }

    /* no need init timer */
    ret = snd_pcm_direct_initialize_poll_index(dsnoop);
    if (ret < 0) {
        awalsa_err("unable to initialize poll index\n");
        goto _err;
    }

    snd_pcm_set_hw_ptr(pcm, &dsnoop->hw_ptr, 0, 0);
    snd_pcm_set_appl_ptr(pcm, &dsnoop->appl_ptr, 0, 0);

    pcm->mmap_rw = 1;
    dsnoop->channels = dsnoop->shmptr->s.channels;
    dsnoop->slowptr = 1;
    dsnoop->max_periods = 0;
    dsnoop->var_periodsize = 0;

    snd_pcm_direct_semaphore_up(dsnoop, DIRECT_IPC_SEM_CLIENT);

    *pcmp = pcm;
    return 0;

_err:
    if (spcm)
        snd_pcm_close(spcm);
    snd_pcm_direct_semaphore_shm_discard(dsnoop);

_err_nosem:
    if (dsnoop) {
        snd_free(dsnoop);
    }
    if (pcm)
        snd_pcm_free(pcm);

    return ret;
}
