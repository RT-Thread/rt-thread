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

typedef struct {
    int card_num;
    int device_num;
    void *substream;
    /* status,control struct define in snd_core.h */
    /* mmap_status,mmap_control sync from kernel */
    struct snd_pcm_mmap_status mmap_status;
    struct snd_pcm_mmap_control mmap_control;
} snd_pcm_hw_t;

static int snd_pcm_sync_ptr(snd_pcm_t *pcm, snd_pcm_hw_t *hw, unsigned int flags)
{
    return ksnd_pcm_sync_ptr(hw->substream, &hw->mmap_status, &hw->mmap_control, flags);
}

static int snd_pcm_hw_hw_refine(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
    assert(pcm);
    awalsa_debug("\n");
    snd_pcm_hw_t *hw = pcm->private_data;
    /* fill params from hw_constrains */
    return ksnd_pcm_hw_refine(hw->substream, params);
}

static int snd_pcm_hw_hw_params(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
    assert(pcm && params);
    awalsa_debug("\n");

    snd_pcm_hw_t *hw = pcm->private_data;

    /*TODO: dmix can't support pause */
    params->can_paused = 1;

    return ksnd_pcm_hw_params(hw->substream, params);
}

static int snd_pcm_hw_hw_free(snd_pcm_t *pcm)
{
    int ret;

    assert(pcm);
    awalsa_debug("\n");

    snd_pcm_hw_t *hw = pcm->private_data;
    ret = ksnd_pcm_hw_free(hw->substream);
    pcm->setup = 0;

    return ret;
}

static int snd_pcm_hw_sw_params(snd_pcm_t *pcm, snd_pcm_sw_params_t *params)
{
    int ret = 0;

    assert(pcm && params);
    awalsa_debug("\n");

    snd_pcm_hw_t *hw = pcm->private_data;
    ret = ksnd_pcm_sw_params(hw->substream, params);
    if (!ret)
        hw->mmap_control.avail_min = params->avail_min;

    return ret;
}

static int snd_pcm_hw_channel_info(snd_pcm_t *pcm, snd_pcm_channel_info_t *info)
{
    int ret = 0;
    snd_pcm_hw_t *hw = pcm->private_data;
    snd_pcm_channel_info_t i;

    assert(pcm && info);
    awalsa_debug("\n");

    i.channel = info->channel;

    ret = ksnd_pcm_channel_info(hw->substream, &i);
    if (ret < 0)
        return ret;

    info->channel = i.channel;
    info->addr = i.addr;
    info->first = i.first;
    info->step = i.step;
    info->type = SND_PCM_AREA_MMAP;

    return 0;
}

static int snd_pcm_hw_mmap(snd_pcm_t *pcm ATTRIBUTE_UNUSED)
{
    return 0;
}

static int snd_pcm_hw_munmap(snd_pcm_t *pcm ATTRIBUTE_UNUSED)
{
    return 0;
}

static int snd_pcm_hw_close(snd_pcm_t *pcm)
{
    int ret = 0, res = 0;
    snd_pcm_hw_t *hw = pcm->private_data;

    awalsa_debug("\n");
    ret = ksnd_pcm_release(hw->card_num, hw->device_num, pcm->stream);
    if (ret < 0)
        res = ret;

    snd_free(hw);
    return res;
}

static snd_pcm_state_t snd_pcm_hw_state(snd_pcm_t *pcm)
{
    int ret = 0;
    snd_pcm_hw_t *hw = pcm->private_data;

    awalsa_debug("\n");
    ret = snd_pcm_sync_ptr(pcm, hw, SNDRV_PCM_SYNC_PTR_APPL);
    if (ret < 0)
        return ret;

    return (snd_pcm_state_t)hw->mmap_status.state;
}

static int snd_pcm_hw_hwsync(snd_pcm_t *pcm)
{
    int ret = 0;
    snd_pcm_hw_t *hw = pcm->private_data;

    awalsa_debug("\n");
    ret = snd_pcm_sync_ptr(pcm, hw, SNDRV_PCM_SYNC_PTR_HWSYNC);
    if (ret < 0)
        return ret;
    return 0;
}

static int snd_pcm_hw_prepare(snd_pcm_t *pcm)
{
    int ret = 0;

    assert(pcm);
    awalsa_debug("\n");

    snd_pcm_hw_t *hw = pcm->private_data;
    ret = ksnd_pcm_prepare(hw->substream);
    return ret;
}

static int snd_pcm_hw_reset(snd_pcm_t *pcm)
{
    int ret = 0;

    assert(pcm);
    awalsa_debug("\n");

    snd_pcm_hw_t *hw = pcm->private_data;
    ret = ksnd_pcm_reset(hw->substream);
    return ret;
}

static int snd_pcm_hw_start(snd_pcm_t *pcm)
{
    assert(pcm);
    awalsa_debug("\n");

    snd_pcm_hw_t *hw = pcm->private_data;
    return ksnd_pcm_start(hw->substream);
}

static int snd_pcm_hw_drop(snd_pcm_t *pcm)
{
    int ret = 0;
    snd_pcm_hw_t *hw;

    assert(pcm);
    awalsa_debug("\n");

    hw = pcm->private_data;
    ret = ksnd_pcm_drop(hw->substream);
    return ret;
}

static int snd_pcm_hw_drain(snd_pcm_t *pcm)
{
    int ret = 0;

    assert(pcm);
    awalsa_debug("\n");

    snd_pcm_hw_t *hw = pcm->private_data;
    ret = ksnd_pcm_drain(hw->substream);

    return ret;
}

static int snd_pcm_hw_pause(snd_pcm_t *pcm, int enable)
{
    int ret = 0;

    assert(pcm);
    awalsa_debug("\n");

    snd_pcm_hw_t *hw = pcm->private_data;
    ret = ksnd_pcm_pause(hw->substream, enable);
    return ret;
}

static int snd_pcm_hw_delay(snd_pcm_t *pcm, snd_pcm_sframes_t *delayp)
{
    int ret = 0;

    assert(pcm);
    assert(delayp);
    awalsa_debug("\n");

    snd_pcm_hw_t *hw = pcm->private_data;
    ret = ksnd_pcm_delay(hw->substream, delayp);

    return ret;
}

static int snd_pcm_hw_resume(snd_pcm_t *pcm)
{
    assert(pcm);
    awalsa_err("suspend state not supported.\n");
    return -1;
}

static snd_pcm_sframes_t snd_pcm_hw_writei(snd_pcm_t *pcm, const void *buffer,
        snd_pcm_uframes_t size)
{
    snd_pcm_sframes_t ret = 0;

    assert(pcm);
    assert(size == 0 || buffer);
    /*awalsa_debug("\n");*/

    snd_pcm_hw_t *hw = pcm->private_data;
    ret = ksnd_pcm_writei(hw->substream, buffer, size);

    return ret;
}
static snd_pcm_sframes_t snd_pcm_hw_readi(snd_pcm_t *pcm, void *buffer,
        snd_pcm_uframes_t size)
{
    snd_pcm_sframes_t ret = 0;

    assert(pcm);
    assert(size == 0 || buffer);
    awalsa_debug("\n");

    snd_pcm_hw_t *hw = pcm->private_data;
    ret = ksnd_pcm_readi(hw->substream, buffer, size);

    return ret;
}

static snd_pcm_sframes_t snd_pcm_hw_avail_update(snd_pcm_t *pcm)
{
    snd_pcm_hw_t *hw = pcm->private_data;
    snd_pcm_uframes_t avail;

    awalsa_debug("\n");
    snd_pcm_sync_ptr(pcm, hw, 0);
    avail = snd_pcm_mmap_avail(pcm);
    switch (hw->mmap_status.state) {
    case SNDRV_PCM_STATE_RUNNING:
        if (avail >= pcm->stop_threshold) {
            // TODO: notify XRUN to driver?

            /* everything is ok, state == SND_PCM_STATE_XRUN at the moment */
            return -EPIPE;
        }
        break;
    case SNDRV_PCM_STATE_XRUN:
        return -EPIPE;
    default:
        break;
    }
    return avail;
}

static snd_pcm_sframes_t snd_pcm_hw_mmap_commit(snd_pcm_t *pcm, snd_pcm_uframes_t offset,
        snd_pcm_uframes_t size)
{
    snd_pcm_hw_t *hw = pcm->private_data;

    awalsa_debug("\n");

    /* flush/invalidate cache */
    ksnd_pcm_hw_mmap_dcache_update(hw->substream, offset, size);

    snd_pcm_mmap_appl_forward(pcm, size);
    snd_pcm_sync_ptr(pcm, hw, 0);
    return size;
}

static int snd_pcm_hw_may_wait_for_avail_min(snd_pcm_t *pcm, snd_pcm_uframes_t avail)
{
    return 1;
}

/*TODO*/
int snd_pcm_hw_wait_with_index(snd_pcm_t *hw_pcm, int index, int timeout)
{
    snd_pcm_hw_t *hw = hw_pcm->private_data;
    awalsa_debug("\n");
    return ksnd_pcm_wait(hw->substream, index, timeout);
}

int snd_pcm_hw_poll_index_init(snd_pcm_t *hw_pcm)
{
    snd_pcm_hw_t *hw = hw_pcm->private_data;
    awalsa_debug("\n");
    return ksnd_pcm_dsleep_init(hw->substream);
}

int snd_pcm_hw_poll_index_release(snd_pcm_t *hw_pcm, int index)
{
    snd_pcm_hw_t *hw = hw_pcm->private_data;
    awalsa_debug("\n");
    return ksnd_pcm_dsleep_release(hw->substream, index);
}

static int snd_pcm_hw_wait(snd_pcm_t *pcm, int timeout)
{
    snd_pcm_hw_t *hw = pcm->private_data;
    awalsa_debug("\n");
    return ksnd_pcm_wait(hw->substream, 0, timeout);
}

static void snd_pcm_hw_cache_update(snd_pcm_t *pcm, snd_pcm_uframes_t offset,
        snd_pcm_uframes_t size)
{
    snd_pcm_hw_t *hw = pcm->private_data;
    awalsa_debug("\n");
    ksnd_pcm_hw_mmap_dcache_update(hw->substream, offset, size);
}

static void snd_pcm_hw_dump(snd_pcm_t *pcm)
{
    snd_pcm_hw_t *hw = pcm->private_data;
    awalsa_debug("\n");

    printf("Hardware PCM card %d '%s'\n",
        hw->card_num, ksnd_card_name(hw->card_num));
    if (pcm->setup) {
        printf("Its setup is:\n");
        snd_pcm_dump_setup(pcm);
        printf("  appl_ptr        : %li\n", hw->mmap_control.appl_ptr);
        printf("  hw_ptr          : %li\n", hw->mmap_status.hw_ptr);
    }
    return;
}

static snd_pcm_sframes_t snd_pcm_hw_rewind(snd_pcm_t *pcm, snd_pcm_uframes_t frames)
{
    snd_pcm_hw_t *hw = pcm->private_data;
    int err;

    if (ksnd_pcm_rewind(hw->substream, frames) < 0) {
        err = -errno;
        awalsa_err("SNDRV_PCM_IOCTL_REWIND failed (%i)", err);
        return err;
    }
    err = snd_pcm_sync_ptr(pcm, hw, SNDRV_PCM_SYNC_PTR_APPL);
    if (err < 0)
        return err;
    return frames;
}

static const snd_pcm_ops_t snd_pcm_hw_ops = {
    .close = snd_pcm_hw_close,
    .hw_refine = snd_pcm_hw_hw_refine,
    .hw_params = snd_pcm_hw_hw_params,
    .hw_free = snd_pcm_hw_hw_free,
    .sw_params = snd_pcm_hw_sw_params,
    .channel_info = snd_pcm_hw_channel_info,
    .dump = snd_pcm_hw_dump,
    .mmap = snd_pcm_hw_mmap,
    .munmap = snd_pcm_hw_munmap,
};

static const snd_pcm_fast_ops_t snd_pcm_hw_fast_ops = {
    .state = snd_pcm_hw_state,
    .hwsync = snd_pcm_hw_hwsync,
    .delay = snd_pcm_hw_delay,
    .prepare = snd_pcm_hw_prepare,
    .reset = snd_pcm_hw_reset,
    .start = snd_pcm_hw_start,
    .drop = snd_pcm_hw_drop,
    .rewind = snd_pcm_hw_rewind,
    .drain = snd_pcm_hw_drain,
    .pause = snd_pcm_hw_pause,
    .resume = snd_pcm_hw_resume,
    .writei = snd_pcm_hw_writei,
    .readi = snd_pcm_hw_readi,
    .avail_update = snd_pcm_hw_avail_update,
    .mmap_commit = snd_pcm_hw_mmap_commit,
    .may_wait_for_avail_min = snd_pcm_hw_may_wait_for_avail_min,
    .wait = snd_pcm_hw_wait,
    .cache_update = snd_pcm_hw_cache_update,
};

int _snd_pcm_hw_open(snd_pcm_t **pcmp, const snd_pcm_config_t *pcm_config,
        snd_pcm_stream_t stream, int mode)
{
    const snd_pcm_hw_config_t *hw_config = (const snd_pcm_hw_config_t *)(pcm_config->config);
    int card_num = 0;
    int ret = 0;
    snd_pcm_t *pcm = NULL;
    void *substream = NULL;
    snd_pcm_hw_t *hw = NULL;

    awalsa_debug("\n");
    card_num = ksnd_card_index(hw_config->card_name);
    if (card_num < 0) {
        awalsa_err("no such card:%s\n", hw_config->card_name);
        ret = -ENODEV;
        goto err_out;
    }

    awalsa_debug("\n");

    ret = snd_pcm_new(&pcm, SND_PCM_TYPE_HW, pcm_config->name, stream, mode);
    if (ret < 0) {
        awalsa_err("failed to new hw pcm\n");
        goto err_out;
    }
    pcm->ops = &snd_pcm_hw_ops;
    pcm->fast_ops = &snd_pcm_hw_fast_ops;

    hw = snd_malloc(sizeof(snd_pcm_hw_t));
    if (!hw) {
        awalsa_err("no memory\n");
        ret = -ENOMEM;
        goto free_pcm;
    }

    ret = ksnd_pcm_open(card_num, hw_config->device_num, stream, mode, &substream);
    if (ret != 0) {
        goto free_hw;
    }
    hw->card_num = card_num;
    hw->device_num = hw_config->device_num;
    hw->substream = substream;

    snd_pcm_set_hw_ptr(pcm, &hw->mmap_status.hw_ptr, 0, 0);
    snd_pcm_set_appl_ptr(pcm, &hw->mmap_control.appl_ptr, 0, 0);
    /* sync control, status */
    snd_pcm_sync_ptr(pcm, hw, 0);

    pcm->private_data = hw;

    *pcmp = pcm;
    return 0;

free_hw:
    snd_free(hw);
free_pcm:
    snd_pcm_free(pcm);
err_out:
    return ret;
}
