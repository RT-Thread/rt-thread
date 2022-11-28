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
#include <pthread.h>
#include <aw-alsa-lib/plugin/pcm_dmix.h>
#include <aw-alsa-lib/pcm_config.h>
#include "pcm_local.h"
#include "pcm_direct.h"

#include <aw_list.h>
#include <aw_common.h>


/* TODO: whether support STATE_RUN_PENDING ? */
#define USE_STATE_RUN_PENDING 1

#if USE_STATE_RUN_PENDING
/* start is pending - this state happens when rate plugin does a delayed commit */
#define STATE_RUN_PENDING   SND_PCM_STATE_LAST
#endif

typedef struct {
    key_t ipc_key;
    int shm_sum_id;
    signed int *sum_buffer;
    int use_count;
    pthread_mutex_t lock;
    struct list_head list;
} shm_sum_ipc_t;

static LIST_HEAD(g_shm_sum_ipcs);
static pthread_mutex_t g_shm_sum_ipcs_lock;

__attribute__((constructor)) static void shm_sum_ipcs_lock_init(void) {
    int ret;
    ret = pthread_mutex_init(&g_shm_sum_ipcs_lock, NULL);
    if (ret != 0)
        awalsa_err("pthread_mutex_init failed (return: %d)\n", ret);
}

__attribute__((destructor)) static void shm_sum_ipcs_lock_destroy(void) {
    pthread_mutex_destroy(&g_shm_sum_ipcs_lock);
}

static shm_sum_ipc_t *shm_sum_ipc_get(snd_pcm_direct_t *dmix, size_t sum_buffer_size)
{
    int ret = 0;
    shm_sum_ipc_t *ipc = NULL;

    pthread_mutex_lock(&g_shm_sum_ipcs_lock);
    list_for_each_entry(ipc, &g_shm_sum_ipcs, list) {
        if (ipc->ipc_key == dmix->ipc_key) {
            pthread_mutex_unlock(&g_shm_sum_ipcs_lock);
            return ipc;
        }
    }

    ipc = snd_malloc(sizeof(shm_sum_ipc_t));
    if (!ipc) {
        awalsa_err("no memory\n");
        goto err_unlock_ipcs;
    }
    ipc->ipc_key = dmix->ipc_key;
    ipc->use_count = 0;
    awalsa_debug("use_count=%d\n", ipc->use_count);
    ipc->sum_buffer = snd_malloc(sum_buffer_size);
    if (!ipc->sum_buffer) {
        awalsa_err("no memory\n");
        goto err_free_ipc;
    }
    ret = pthread_mutex_init(&ipc->lock, NULL);
    if (ret != 0) {
        awalsa_err("pthread_mutex_init failed (return: %d)\n", ret);
        goto err_free_sum_buffer;
    }

    list_add(&ipc->list, &g_shm_sum_ipcs);
    pthread_mutex_unlock(&g_shm_sum_ipcs_lock);
    return ipc;

err_free_sum_buffer:
    free(ipc->sum_buffer);
err_free_ipc:
    free(ipc);
err_unlock_ipcs:
    pthread_mutex_unlock(&g_shm_sum_ipcs_lock);
    return NULL;
}

static int shm_sum_create_or_connect(snd_pcm_direct_t *dmix)
{
    size_t size;
    shm_sum_ipc_t *ipc = NULL;

    size = dmix->shmptr->s.channels *
        dmix->shmptr->s.buffer_size *
        sizeof(signed int);

    ipc = shm_sum_ipc_get(dmix, size);
    if (!ipc)
        return -1;

    pthread_mutex_lock(&ipc->lock);
    ipc->use_count++;
    awalsa_debug("use_count=%d\n", ipc->use_count);
    pthread_mutex_unlock(&ipc->lock);

    dmix->u.dmix.shm_sum_id = &ipc->shm_sum_id;
    dmix->u.dmix.sum_buffer = ipc->sum_buffer;
    return 0;
}

static int shm_sum_discard(snd_pcm_direct_t *dmix)
{
    shm_sum_ipc_t *ipc;
    ipc = container_of(dmix->u.dmix.shm_sum_id, shm_sum_ipc_t, shm_sum_id);

    if (!ipc) {
        awalsa_err("can't find shm_sum_ipc\n");
        return -1;
    }

    pthread_mutex_lock(&ipc->lock);
    ipc->use_count--;
    if (ipc->use_count > 0) {
        pthread_mutex_unlock(&ipc->lock);
        dmix->u.dmix.sum_buffer = NULL;
        dmix->u.dmix.shm_sum_id = NULL;
        return 0;
    }

    snd_free(ipc->sum_buffer);
    pthread_mutex_unlock(&ipc->lock);
    pthread_mutex_destroy(&ipc->lock);
    pthread_mutex_lock(&g_shm_sum_ipcs_lock);
    list_del(&ipc->list);
    snd_free(ipc);
    pthread_mutex_unlock(&g_shm_sum_ipcs_lock);

    dmix->u.dmix.sum_buffer = NULL;
    dmix->u.dmix.shm_sum_id = NULL;
    return 0;
}

#include "pcm_dmix_generic.c"
#define mix_select_callbacks(x) generic_mix_select_callbacks(x)

static void mix_areas(snd_pcm_direct_t *dmix,
              const snd_pcm_channel_area_t *src_areas,
              const snd_pcm_channel_area_t *dst_areas,
              snd_pcm_uframes_t src_ofs,
              snd_pcm_uframes_t dst_ofs,
              snd_pcm_uframes_t size)
{
    unsigned int src_step, dst_step;
    unsigned int chn, dchn, channels, sample_size;
    mix_areas_t *do_mix_areas;

    channels = dmix->channels;
    switch (dmix->shmptr->s.format) {
    case SND_PCM_FORMAT_S16_LE:
    case SND_PCM_FORMAT_S16_BE:
        sample_size = 2;
        do_mix_areas = (mix_areas_t *)dmix->u.dmix.mix_areas_16;
        break;
    case SND_PCM_FORMAT_S32_LE:
    case SND_PCM_FORMAT_S32_BE:
        sample_size = 4;
        do_mix_areas = (mix_areas_t *)dmix->u.dmix.mix_areas_32;
        break;
    case SND_PCM_FORMAT_S24_LE:
        sample_size = 4;
        do_mix_areas = (mix_areas_t *)dmix->u.dmix.mix_areas_24;
        break;
#if 0
    case SND_PCM_FORMAT_S24_3LE:
        sample_size = 3;
        do_mix_areas = (mix_areas_t *)dmix->u.dmix.mix_areas_24;
        break;
#endif
    case SND_PCM_FORMAT_U8:
        sample_size = 1;
        do_mix_areas = (mix_areas_t *)dmix->u.dmix.mix_areas_u8;
        break;
    default:
        return;
    }
    if (dmix->interleaved) {
        /*
         * process all areas in one loop
         * it optimizes the memory accesses for this case
         */
        do_mix_areas(size * channels,
                 (unsigned char *)dst_areas[0].addr + sample_size * dst_ofs * channels,
                 (unsigned char *)src_areas[0].addr + sample_size * src_ofs * channels,
                 dmix->u.dmix.sum_buffer + dst_ofs * channels,
                 sample_size,
                 sample_size,
                 sizeof(signed int));
        return;
    }
    for (chn = 0; chn < channels; chn++) {
#if 0
        dchn = dmix->bindings ? dmix->bindings[chn] : chn;
#else
        dchn = chn;
#endif
        if (dchn >= dmix->shmptr->s.channels)
            continue;
        src_step = src_areas[chn].step / 8;
        dst_step = dst_areas[dchn].step / 8;
        do_mix_areas(size,
                 ((unsigned char *)dst_areas[dchn].addr + dst_areas[dchn].first / 8) + dst_ofs * dst_step,
                 ((unsigned char *)src_areas[chn].addr + src_areas[chn].first / 8) + src_ofs * src_step,
                 dmix->u.dmix.sum_buffer + channels * dst_ofs + chn,
                 dst_step,
                 src_step,
                 channels * sizeof(signed int));
    }
}

#define dmix_down_sem(dmix) snd_pcm_direct_semaphore_down(dmix, DIRECT_IPC_SEM_CLIENT)
#define dmix_up_sem(dmix) snd_pcm_direct_semaphore_up(dmix, DIRECT_IPC_SEM_CLIENT)

/*
 *  synchronize shm ring buffer with hardware
 */
static void snd_pcm_dmix_sync_area(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dmix = pcm->private_data;
    snd_pcm_uframes_t slave_hw_ptr, slave_appl_ptr, slave_size;
    snd_pcm_uframes_t appl_ptr, size, transfer;
    const snd_pcm_channel_area_t *src_areas, *dst_areas;

    /* calculate the size to transfer */
    /* check the available size in the local buffer
     * last_appl_ptr keeps the last updated position
     */
    size = dmix->appl_ptr - dmix->last_appl_ptr;
    if (! size)
        return;
    if (size >= pcm->boundary / 2)
        size = pcm->boundary - size;

    /* the slave_app_ptr can be far behind the slave_hw_ptr */
    /* reduce mixing and errors here - just skip not catched writes */
    if (dmix->slave_hw_ptr <= dmix->slave_appl_ptr)
        slave_size = dmix->slave_appl_ptr - dmix->slave_hw_ptr;
    else
        slave_size = dmix->slave_appl_ptr + (dmix->slave_boundary - dmix->slave_hw_ptr);
    if (slave_size > dmix->slave_buffer_size) {
        transfer = dmix->slave_buffer_size - slave_size;
        if (transfer > size)
            transfer = size;
        dmix->last_appl_ptr += transfer;
        dmix->last_appl_ptr %= pcm->boundary;
        dmix->slave_appl_ptr += transfer;
        dmix->slave_appl_ptr %= dmix->slave_boundary;
        size = dmix->appl_ptr - dmix->last_appl_ptr;
        if (! size)
            return;
        if (size >= pcm->boundary / 2)
            size = pcm->boundary - size;
    }

    /* check the available size in the slave PCM buffer */
    slave_hw_ptr = dmix->slave_hw_ptr;
    /* don't write on the last active period - this area may be cleared
     * by the driver during mix operation...
     */
    slave_hw_ptr -= slave_hw_ptr % dmix->slave_period_size;
    slave_hw_ptr += dmix->slave_buffer_size;
    if (slave_hw_ptr >= dmix->slave_boundary)
        slave_hw_ptr -= dmix->slave_boundary;
    if (slave_hw_ptr < dmix->slave_appl_ptr)
        slave_size = slave_hw_ptr + (dmix->slave_boundary - dmix->slave_appl_ptr);
    else
        slave_size = slave_hw_ptr - dmix->slave_appl_ptr;
    if (slave_size < size)
        size = slave_size;
    if (! size)
        return;

    /* add sample areas here */
    src_areas = snd_pcm_mmap_areas(pcm);
    dst_areas = snd_pcm_mmap_areas(dmix->spcm);
    appl_ptr = dmix->last_appl_ptr % pcm->buffer_size;
    dmix->last_appl_ptr += size;
    dmix->last_appl_ptr %= pcm->boundary;
    slave_appl_ptr = dmix->slave_appl_ptr % dmix->slave_buffer_size;
    dmix->slave_appl_ptr += size;
    dmix->slave_appl_ptr %= dmix->slave_boundary;
    dmix_down_sem(dmix);
    for (;;) {
        transfer = size;
        if (appl_ptr + transfer > pcm->buffer_size)
            transfer = pcm->buffer_size - appl_ptr;
        if (slave_appl_ptr + transfer > dmix->slave_buffer_size)
            transfer = dmix->slave_buffer_size - slave_appl_ptr;
        mix_areas(dmix, src_areas, dst_areas, appl_ptr, slave_appl_ptr, transfer);
        /* flush cache */
        if (dmix->spcm->fast_ops->cache_update)
            dmix->spcm->fast_ops->cache_update(
                    dmix->spcm->fast_op_arg, slave_appl_ptr, transfer);
        size -= transfer;
        if (! size)
            break;
        slave_appl_ptr += transfer;
        slave_appl_ptr %= dmix->slave_buffer_size;
        appl_ptr += transfer;
        appl_ptr %= pcm->buffer_size;
    }
    dmix_up_sem(dmix);
}

/*
 *  synchronize hardware pointer (hw_ptr) with ours
 */
static int snd_pcm_dmix_sync_ptr0(snd_pcm_t *pcm, snd_pcm_uframes_t slave_hw_ptr)
{
    snd_pcm_direct_t *dmix = pcm->private_data;
    snd_pcm_uframes_t old_slave_hw_ptr, avail;
    snd_pcm_sframes_t diff;

    old_slave_hw_ptr = dmix->slave_hw_ptr;
    dmix->slave_hw_ptr = *dmix->spcm->hw.ptr;
    diff = slave_hw_ptr - old_slave_hw_ptr;
    if (diff == 0)      /* fast path */
        return 0;
    if (dmix->state != SND_PCM_STATE_RUNNING &&
        dmix->state != SND_PCM_STATE_DRAINING)
        /* not really started yet - don't update hw_ptr */
        return 0;
    if (diff < 0) {
        slave_hw_ptr += dmix->slave_boundary;
        diff = slave_hw_ptr - old_slave_hw_ptr;
    }
    dmix->hw_ptr += diff;
    dmix->hw_ptr %= pcm->boundary;
    if (pcm->stop_threshold >= pcm->boundary)   /* don't care */
        return 0;
    avail = snd_pcm_mmap_playback_avail(pcm);
    if (avail > dmix->avail_max)
        dmix->avail_max = avail;
    if (avail >= pcm->stop_threshold) {
#if 0
        snd_timer_stop(dmix->timer);
        gettimestamp(&dmix->trigger_tstamp, pcm->tstamp_type);
#endif
        if (dmix->state == SND_PCM_STATE_RUNNING) {
            dmix->state = SND_PCM_STATE_XRUN;
            awalsa_err("avail=%lu, stop=%lu, slave_hw_ptr=%lu, old=%lu, diff=%ld\n",
                    avail, pcm->stop_threshold,
                    slave_hw_ptr, old_slave_hw_ptr, diff);
            return -EPIPE;
        }
        dmix->state = SND_PCM_STATE_SETUP;
#if 0
        /* clear queue to remove pending poll events */
        snd_pcm_direct_clear_timer_queue(dmix);
#endif
    }
    return 0;
}

static int snd_pcm_dmix_sync_ptr(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dmix = pcm->private_data;
    int err;

    switch (snd_pcm_state(dmix->spcm)) {
    case SND_PCM_STATE_DISCONNECTED:
        dmix->state = SND_PCM_STATE_DISCONNECTED;
        return -ENODEV;
    case SND_PCM_STATE_XRUN:
        if ((err = snd_pcm_direct_slave_recover(dmix)) < 0)
            return err;
        break;
    default:
        break;
    }
    if (snd_pcm_direct_client_chk_xrun(dmix, pcm))
        return -EPIPE;

    if (dmix->slowptr)
        snd_pcm_hwsync(dmix->spcm);

    return snd_pcm_dmix_sync_ptr0(pcm, *dmix->spcm->hw.ptr);
}

/*
 *  plugin implementation
 */

static snd_pcm_state_t snd_pcm_dmix_state(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dmix = pcm->private_data;
    int err;
    snd_pcm_state_t state;

    awalsa_debug("\n");
    state = snd_pcm_state(dmix->spcm);
    switch (state) {
    case SND_PCM_STATE_SUSPENDED:
    case SND_PCM_STATE_DISCONNECTED:
        dmix->state = state;
        return state;
    case SND_PCM_STATE_XRUN:
        if ((err = snd_pcm_direct_slave_recover(dmix)) < 0)
            return err;
        break;
    default:
        break;
    }
    snd_pcm_direct_client_chk_xrun(dmix, pcm);
#if USE_STATE_RUN_PENDING
    if (dmix->state == STATE_RUN_PENDING)
        return SND_PCM_STATE_RUNNING;
#endif
    return dmix->state;
}

static int snd_pcm_dmix_delay(snd_pcm_t *pcm, snd_pcm_sframes_t *delayp)
{
    snd_pcm_direct_t *dmix = pcm->private_data;
    int err;

    awalsa_debug("\n");
    switch(dmix->state) {
    case SND_PCM_STATE_DRAINING:
    case SND_PCM_STATE_RUNNING:
        err = snd_pcm_dmix_sync_ptr(pcm);
        if (err < 0)
            return err;
        /* fallthru */
    case SND_PCM_STATE_PREPARED:
    case SND_PCM_STATE_SUSPENDED:
#if USE_STATE_RUN_PENDING
    case STATE_RUN_PENDING:
        *delayp = snd_pcm_mmap_playback_hw_avail(pcm);
        return 0;
#endif
    case SND_PCM_STATE_XRUN:
        return -EPIPE;
    case SND_PCM_STATE_DISCONNECTED:
        return -ENODEV;
    default:
        return -EBADFD;
    }
}

static int snd_pcm_dmix_hwsync(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dmix = pcm->private_data;

    awalsa_debug("\n");
    switch(dmix->state) {
    case SND_PCM_STATE_DRAINING:
    case SND_PCM_STATE_RUNNING:
        /* sync slave PCM */
        return snd_pcm_dmix_sync_ptr(pcm);
    case SND_PCM_STATE_PREPARED:
    case SND_PCM_STATE_SUSPENDED:
#if USE_STATE_RUN_PENDING
    case STATE_RUN_PENDING:
        return 0;
#endif
    case SND_PCM_STATE_XRUN:
        return -EPIPE;
    case SND_PCM_STATE_DISCONNECTED:
        return -ENODEV;
    default:
        return -EBADFD;
    }
}

static void reset_slave_ptr(snd_pcm_t *pcm, snd_pcm_direct_t *dmix)
{
    dmix->slave_appl_ptr = dmix->slave_hw_ptr = *dmix->spcm->hw.ptr;
    if (pcm->buffer_size > pcm->period_size * 2)
        return;
    /* If we have too litte periods, better to align the start position
     * to the period boundary so that the interrupt can be handled properly
     * at the right time.
     */
    dmix->slave_appl_ptr = ((dmix->slave_appl_ptr + dmix->slave_period_size - 1)
                / dmix->slave_period_size) * dmix->slave_period_size;
}

static int snd_pcm_dmix_reset(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dmix = pcm->private_data;
    dmix->hw_ptr %= pcm->period_size;
    dmix->appl_ptr = dmix->last_appl_ptr = dmix->hw_ptr;
    reset_slave_ptr(pcm, dmix);
    return 0;
}

static int snd_pcm_dmix_start_timer(snd_pcm_t *pcm, snd_pcm_direct_t *dmix)
{

    snd_pcm_hwsync(dmix->spcm);
    reset_slave_ptr(pcm, dmix);
#if 0
    err = snd_timer_start(dmix->timer);
    if (err < 0)
        return err;
#endif
    dmix->state = SND_PCM_STATE_RUNNING;
    return 0;
}

static snd_pcm_sframes_t snd_pcm_dmix_avail_update(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dmix = pcm->private_data;
    int err;

    awalsa_debug("\n");
    if (dmix->state == SND_PCM_STATE_RUNNING ||
        dmix->state == SND_PCM_STATE_DRAINING) {
        if ((err = snd_pcm_dmix_sync_ptr(pcm)) < 0)
            return err;
    }
    if (dmix->state == SND_PCM_STATE_XRUN)
        return -EPIPE;

    return snd_pcm_mmap_playback_avail(pcm);
}

static snd_pcm_sframes_t snd_pcm_dmix_mmap_commit(snd_pcm_t *pcm,
        snd_pcm_uframes_t offset, snd_pcm_uframes_t size)
{
    snd_pcm_direct_t *dmix = pcm->private_data;
    int err;

    awalsa_debug("\n");
    switch (snd_pcm_state(dmix->spcm)) {
    case SND_PCM_STATE_XRUN:
        if ((err = snd_pcm_direct_slave_recover(dmix)) < 0)
            return err;
        break;
    case SND_PCM_STATE_SUSPENDED:
        return -ESTRPIPE;
    default:
        break;
    }
    if (snd_pcm_direct_client_chk_xrun(dmix, pcm))
        return -EPIPE;
    if (! size)
        return 0;
    snd_pcm_mmap_appl_forward(pcm, size);
#if USE_STATE_RUN_PENDING
    if (dmix->state == STATE_RUN_PENDING) {
        if ((err = snd_pcm_dmix_start_timer(pcm, dmix)) < 0)
            return err;
    } else if (dmix->state == SND_PCM_STATE_RUNNING ||
           dmix->state == SND_PCM_STATE_DRAINING) {
        if ((err = snd_pcm_dmix_sync_ptr(pcm)) < 0)
            return err;
    }
#else
    if (dmix->state == SND_PCM_STATE_RUNNING ||
            dmix->state == SND_PCM_STATE_DRAINING) {
        if ((err = snd_pcm_dmix_sync_ptr(pcm)) < 0)
            return err;
    }
#endif
    if (dmix->state == SND_PCM_STATE_RUNNING ||
        dmix->state == SND_PCM_STATE_DRAINING) {
        /* ok, we commit the changes after the validation of area */
        /* it's intended, although the result might be crappy */
        snd_pcm_dmix_sync_area(pcm);
#if 0
        /* clear timer queue to avoid a bogus return from poll */
        if (snd_pcm_mmap_playback_avail(pcm) < pcm->avail_min)
            snd_pcm_direct_clear_timer_queue(dmix);
#endif
    }
    return size;
}

static int snd_pcm_dmix_start(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dmix = pcm->private_data;
    snd_pcm_sframes_t avail;
    int err;

    awalsa_debug("\n");
    if (dmix->state != SND_PCM_STATE_PREPARED)
        return -EBADFD;
    avail = snd_pcm_mmap_playback_hw_avail(pcm);
    if (avail == 0) {
#if USE_STATE_RUN_PENDING
        dmix->state = STATE_RUN_PENDING;
#else
        return 0;
#endif
    } else if (avail < 0) {
        return 0;
    } else {
        if ((err = snd_pcm_dmix_start_timer(pcm, dmix)) < 0)
            return err;
        snd_pcm_dmix_sync_area(pcm);
    }
#if 0
    gettimestamp(&dmix->trigger_tstamp, pcm->tstamp_type);
#endif
    return 0;
}

static int snd_pcm_dmix_drop(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dmix = pcm->private_data;

    awalsa_debug("\n");
    if (dmix->state == SND_PCM_STATE_OPEN)
        return -EBADFD;
    dmix->state = SND_PCM_STATE_SETUP;

    awalsa_debug("\n");
    return snd_pcm_direct_last_pcm_drop(dmix);
}

/* locked version */
static int __snd_pcm_dmix_drain(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dmix = pcm->private_data;
    snd_pcm_uframes_t stop_threshold;
    int err = 0;

    switch (snd_pcm_state(dmix->spcm)) {
    case SND_PCM_STATE_SUSPENDED:
        return -ESTRPIPE;
    default:
        break;
    }

    if (dmix->state == SND_PCM_STATE_OPEN)
        return -EBADFD;
    if (dmix->state == SND_PCM_STATE_PREPARED) {
        if (snd_pcm_mmap_playback_hw_avail(pcm) > 0)
            snd_pcm_dmix_start(pcm);
        else {
            snd_pcm_dmix_drop(pcm);
            return 0;
        }
    }

    if (dmix->state == SND_PCM_STATE_XRUN) {
        snd_pcm_dmix_drop(pcm);
        return 0;
    }

    stop_threshold = pcm->stop_threshold;
    if (pcm->stop_threshold > pcm->buffer_size)
        pcm->stop_threshold = pcm->buffer_size;
    dmix->state = SND_PCM_STATE_DRAINING;
    do {
        err = snd_pcm_dmix_sync_ptr(pcm);
        if (err < 0) {
            snd_pcm_dmix_drop(pcm);
            goto done;
        }
        if (dmix->state == SND_PCM_STATE_DRAINING) {
            snd_pcm_dmix_sync_area(pcm);
#if 0
            if ((pcm->mode & SND_PCM_NONBLOCK) == 0) {
                snd_pcm_wait_nocheck(pcm, -1);
                snd_pcm_direct_clear_timer_queue(dmix); /* force poll to wait */
            }
#else
            snd_pcm_wait_nocheck(pcm, -1);
#endif

            switch (snd_pcm_state(dmix->spcm)) {
            case SND_PCM_STATE_SUSPENDED:
                err = -ESTRPIPE;
                goto done;
            default:
                break;
            }
        }
#if 0
        if (pcm->mode & SND_PCM_NONBLOCK) {
            if (dmix->state == SND_PCM_STATE_DRAINING) {
                err = -EAGAIN;
                goto done;
            }
        }
#endif
    } while (dmix->state == SND_PCM_STATE_DRAINING);
done:
    pcm->stop_threshold = stop_threshold;
    return err;
}

static int snd_pcm_dmix_drain(snd_pcm_t *pcm)
{
    int err;

    awalsa_debug("\n");
    snd_pcm_lock(pcm);
    err = __snd_pcm_dmix_drain(pcm);
    snd_pcm_unlock(pcm);
    return err;
}

static int snd_pcm_dmix_pause(snd_pcm_t *pcm, int enable)
{
    awalsa_debug("\n");
    return -EIO;
}

static int snd_pcm_dmix_close(snd_pcm_t *pcm)
{
    int ret;
    snd_pcm_direct_t *dmix = pcm->private_data;

    snd_pcm_direct_destroy_poll_index(dmix);
    snd_pcm_direct_semaphore_down(dmix, DIRECT_IPC_SEM_CLIENT);
    snd_pcm_direct_last_pcm_drop(dmix);
    ret = snd_pcm_close(dmix->spcm);
    if (ret < 0)
        return ret;
    ret = shm_sum_discard(dmix);
    if (ret < 0)
        return ret;
    ret = snd_pcm_direct_semaphore_shm_discard(dmix);
    if (ret < 0)
        return ret;

    pcm->private_data = NULL;
    free(dmix);

    return 0;
}

static snd_pcm_sframes_t snd_pcm_dmix_readi(snd_pcm_t *pcm, void *buffer, snd_pcm_uframes_t size)
{
    return -ENODEV;
}

static int snd_pcm_dmix_may_wait_for_avail_min(snd_pcm_t *pcm, snd_pcm_uframes_t avail)
{
    awalsa_debug("\n");
    return 1;
}

static void snd_pcm_dmix_dump(snd_pcm_t *pcm)
{
    snd_pcm_direct_t *dmix = pcm->private_data;

    printf("Direct Stream Mixing PCM\n");
    if (pcm->setup) {
        printf("Its setup is:\n");
        snd_pcm_dump_setup(pcm);
    }
    if (dmix->spcm)
        snd_pcm_dump(dmix->spcm);
}

static const snd_pcm_ops_t snd_pcm_dmix_ops = {
    .close = snd_pcm_dmix_close,
    .hw_refine = snd_pcm_direct_hw_refine,
    .hw_params = snd_pcm_direct_hw_params,
    .hw_free = snd_pcm_direct_hw_free,
    .sw_params = snd_pcm_direct_sw_params,
    .channel_info = snd_pcm_direct_channel_info,
    .dump = snd_pcm_dmix_dump,
    .mmap = snd_pcm_direct_mmap,
    .munmap = snd_pcm_direct_munmap,
};

static const snd_pcm_fast_ops_t snd_pcm_dmix_fast_ops = {
    .state = snd_pcm_dmix_state,
    .hwsync = snd_pcm_dmix_hwsync,
    .delay = snd_pcm_dmix_delay,
    .prepare = snd_pcm_direct_prepare,
    .reset = snd_pcm_dmix_reset,
    .start = snd_pcm_dmix_start,
    .drop = snd_pcm_dmix_drop,
    .drain = snd_pcm_dmix_drain,
    .pause = snd_pcm_dmix_pause,
    //.resume = snd_pcm_direct_resume,
    .writei = snd_pcm_mmap_writei,
    .readi = snd_pcm_dmix_readi,
    .avail_update = snd_pcm_dmix_avail_update,
    .mmap_commit = snd_pcm_dmix_mmap_commit,
    .may_wait_for_avail_min = snd_pcm_dmix_may_wait_for_avail_min,
    .wait = snd_pcm_direct_wait,
};

int _snd_pcm_dmix_open(snd_pcm_t **pcmp, const snd_pcm_config_t *pcm_config,
        snd_pcm_stream_t stream, int mode)
{
    const snd_pcm_dmix_config_t *dmix_config =
        (const snd_pcm_dmix_config_t *)(pcm_config->config);
    snd_pcm_t *pcm = NULL, *spcm = NULL;
    snd_pcm_direct_t *dmix = NULL;
    const snd_pcm_config_t *sconf = NULL;
    struct slave_params params;
    int ret = -1;
    int first_instance;

    awalsa_debug("\n");
    if (stream != SND_PCM_STREAM_PLAYBACK) {
        awalsa_err("The dmix plugin supports only playback stream");
        return -EINVAL;
    }

    sconf = snd_pcm_config_get_config(dmix_config->slave.pcm);
    if (!sconf) {
        awalsa_err("can't find pcm slave:%s\n", dmix_config->slave.pcm);
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

    ret = snd_pcm_slave_conf_hw_params(&dmix_config->slave, &params);
    if (ret < 0)
        return ret;

    dmix = snd_malloc(sizeof(snd_pcm_direct_t));
    if (!dmix) {
        awalsa_err("no memory\n");
        ret = -ENOMEM;
        goto _err_nosem;
    }

    dmix->ipc_key = dmix_config->ipc_key;
    dmix->type = SND_PCM_TYPE_DMIX;

    ret = snd_pcm_new(&pcm, dmix->type, pcm_config->name, stream, mode);
    if (ret < 0) {
        awalsa_err("failed to new dmix pcm\n");
        goto _err_nosem;
    }

    ret = snd_pcm_direct_semaphore_shm_create_or_connect(dmix);
    if (ret < 0) {
        awalsa_err("unable to create IPC semaphore shm instance (return: %d)\n", ret);
        goto _err;
    }

    first_instance = ret;

    pcm->ops = &snd_pcm_dmix_ops;
    pcm->fast_ops = &snd_pcm_dmix_fast_ops;
    pcm->private_data = dmix;

    // TODO: is complete?
    dmix->state = SND_PCM_STATE_OPEN;
    dmix->sync_ptr = snd_pcm_dmix_sync_ptr;

retry:
    if (first_instance) {
        awalsa_debug("first open, dmix=%p\n", dmix);
        ret = snd_pcm_open_config(&spcm, sconf, stream, mode);
        if (ret < 0) {
            awalsa_err("unable to open slave\n");
            goto _err;
        }
        if (snd_pcm_type(spcm) != SND_PCM_TYPE_HW) {
            awalsa_err("dmix plugin can be only connected to hw plugin\n");
            goto _err;
        }
        ret = snd_pcm_direct_initialize_slave(dmix, spcm, &params);
        if (ret < 0) {
            awalsa_err("unable to initialize slave\n");
            goto _err;
        }
        dmix->spcm = spcm;
        dmix->shmptr->type = spcm->type;
    } else {
        awalsa_debug("second open, dmix=%p\n", dmix);
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
            awalsa_err("dmix plugin can be only connected to hw plugin\n");
            ret = -EINVAL;
            goto _err;
        }
        ret = snd_pcm_direct_initialize_secondary_slave(dmix, spcm, &params);
        if (ret < 0) {
            awalsa_err("unable to initialize slave\n");
            goto _err;
        }
        dmix->spcm = spcm;
    }

    ret = shm_sum_create_or_connect(dmix);
    if (ret < 0) {
        awalsa_err("unable to initialize sum ring buffer\n");
        goto _err;
    }

    mix_select_callbacks(dmix);

    ret = snd_pcm_direct_initialize_poll_index(dmix);
    if (ret < 0) {
        awalsa_err("unable to initialize poll index\n");
        goto _err;
    }

    pcm->mmap_rw = 1;
    snd_pcm_set_hw_ptr(pcm, &dmix->hw_ptr, 0, 0);
    snd_pcm_set_appl_ptr(pcm, &dmix->appl_ptr, 0, 0);
    dmix->slowptr = 1;
    dmix->max_periods = 0;
    dmix->var_periodsize = 0;

    dmix->channels = dmix->shmptr->s.channels;

    snd_pcm_direct_semaphore_up(dmix, DIRECT_IPC_SEM_CLIENT);

    *pcmp = pcm;
    return 0;

_err:
    if (spcm)
        snd_pcm_close(spcm);
    snd_pcm_direct_semaphore_shm_discard(dmix);

_err_nosem:
    if (dmix)
        snd_free(dmix);
    return ret;
}
