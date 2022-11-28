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
    snd_pcm_t *pcm;
    unsigned int channels_count;
    int close_slave;
    snd_pcm_t *linked;
} snd_pcm_multi_slave_t;

typedef struct {
    int slave_idx;
    unsigned int slave_channel;
} snd_pcm_multi_channel_t;

typedef struct {
    unsigned int slaves_count;
    unsigned int master_slave;
    snd_pcm_multi_slave_t *slaves;
    unsigned int channels_count;
    snd_pcm_multi_channel_t *channels;
} snd_pcm_multi_t;

static int snd_pcm_multi_close(snd_pcm_t *pcm)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    unsigned int i;
    int ret = 0;
    for (i = 0; i < multi->slaves_count; ++i) {
        snd_pcm_multi_slave_t *slave = &multi->slaves[i];
        if (slave->close_slave) {
            int err = snd_pcm_close(slave->pcm);
            if (err < 0)
                ret = err;
        }
    }
    free(multi->slaves);
    free(multi->channels);
    free(multi);
    return ret;
}

#if 0
static int snd_pcm_multi_nonblock(snd_pcm_t *pcm ATTRIBUTE_UNUSED, int nonblock ATTRIBUTE_UNUSED)
{
    return 0;
}

static int snd_pcm_multi_async(snd_pcm_t *pcm, int sig, pid_t pid)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_pcm_t *slave_0 = multi->slaves[multi->master_slave].pcm;
    return snd_pcm_async(slave_0, sig, pid);
}

static int snd_pcm_multi_poll_descriptors_count(snd_pcm_t *pcm)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_pcm_t *slave_0 = multi->slaves[multi->master_slave].pcm;
    return snd_pcm_poll_descriptors_count(slave_0);
}

static int snd_pcm_multi_poll_descriptors(snd_pcm_t *pcm, struct pollfd *pfds, unsigned int space)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_pcm_t *slave;
    snd_pcm_t *slave_0 = multi->slaves[multi->master_slave].pcm;
    int err;
    unsigned int i;

    for (i = 0; i < multi->slaves_count; ++i) {
        slave = multi->slaves[i].pcm;
        if (slave == slave_0)
            continue;
        err = snd_pcm_poll_descriptors(slave, pfds, space);
        if (err < 0)
            return err;
    }
    /* finally overwrite with master's pfds */
    return snd_pcm_poll_descriptors(slave_0, pfds, space);
}

static int snd_pcm_multi_poll_revents(snd_pcm_t *pcm, struct pollfd *pfds, unsigned int nfds, unsigned short *revents)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_pcm_t *slave_0 = multi->slaves[multi->master_slave].pcm;
    return snd_pcm_poll_descriptors_revents(slave_0, pfds, nfds, revents);
}

static int snd_pcm_multi_info(snd_pcm_t *pcm, snd_pcm_info_t *info)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    int err, n;
    assert(info->subdevice < multi->slaves_count);
    n = info->subdevice;
    info->subdevice = 0;
    err = snd_pcm_info(multi->slaves[n].pcm, info);
    if (err < 0)
        return err;
    info->subdevices_count = multi->slaves_count;
    return 0;
}
#endif

static int snd_pcm_multi_hw_refine_cprepare(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_interval_t access_mask;
    int err;

    awalsa_debug("\n");
    snd_mask_any(&access_mask);
    snd_mask_reset(&access_mask, SND_PCM_ACCESS_MMAP_INTERLEAVED);
    err = _snd_pcm_hw_param_set_mask(params, SND_PCM_HW_PARAM_ACCESS,
                     &access_mask);
    if (err < 0)
        return err;
    err = _snd_pcm_hw_param_set(params, SND_PCM_HW_PARAM_CHANNELS,
                    multi->channels_count, 0);
    if (err < 0)
        return err;
    /*params->info = ~0U;*/
    return 0;
}

static int snd_pcm_multi_hw_refine_sprepare(snd_pcm_t *pcm, unsigned int slave_idx,
                        snd_pcm_hw_params_t *sparams)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_pcm_multi_slave_t *slave = &multi->slaves[slave_idx];
    snd_interval_t saccess_mask = { .mask = SND_PCM_ACCBIT_MMAP };

    _snd_pcm_hw_params_any(sparams);
    _snd_pcm_hw_param_set_mask(sparams, SND_PCM_HW_PARAM_ACCESS,
                   &saccess_mask);
    _snd_pcm_hw_param_set(sparams, SND_PCM_HW_PARAM_CHANNELS,
                  slave->channels_count, 0);
    return 0;
}

static int snd_pcm_multi_hw_refine_schange(snd_pcm_t *pcm ATTRIBUTE_UNUSED,
                       unsigned int slave_idx ATTRIBUTE_UNUSED,
                       snd_pcm_hw_params_t *params,
                       snd_pcm_hw_params_t *sparams)
{
    int err;
    unsigned int links = (SND_PCM_HW_PARBIT_FORMAT |
                  SND_PCM_HW_PARBIT_RATE |
                  SND_PCM_HW_PARBIT_PERIOD_SIZE |
                  SND_PCM_HW_PARBIT_PERIOD_TIME |
                  SND_PCM_HW_PARBIT_PERIODS |
                  SND_PCM_HW_PARBIT_BUFFER_SIZE |
                  SND_PCM_HW_PARBIT_BUFFER_TIME);
    const snd_interval_t *access_mask = hw_param_interval(params, SND_PCM_HW_PARAM_ACCESS);
    if (!snd_mask_test(access_mask, SND_PCM_ACCESS_RW_INTERLEAVED) &&
        !snd_mask_test(access_mask, SND_PCM_ACCESS_RW_NONINTERLEAVED) &&
        !snd_mask_test(access_mask, SND_PCM_ACCESS_MMAP_NONINTERLEAVED)) {
        snd_interval_t saccess_mask;
        snd_mask_any(&saccess_mask);
        snd_mask_reset(&saccess_mask, SND_PCM_ACCESS_MMAP_NONINTERLEAVED);
        err = _snd_pcm_hw_param_set_mask(sparams, SND_PCM_HW_PARAM_ACCESS,
                         &saccess_mask);
        if (err < 0)
            return err;
    }
    err = _snd_pcm_hw_params_refine(sparams, links, params);
    if (err < 0)
        return err;
    return 0;
}

static int snd_pcm_multi_hw_refine_cchange(snd_pcm_t *pcm ATTRIBUTE_UNUSED,
                       unsigned int slave_idx ATTRIBUTE_UNUSED,
                       snd_pcm_hw_params_t *params,
                       snd_pcm_hw_params_t *sparams)
{
    int err;
    unsigned int links = (SND_PCM_HW_PARBIT_FORMAT |
                  SND_PCM_HW_PARBIT_RATE |
                  SND_PCM_HW_PARBIT_PERIOD_SIZE |
                  SND_PCM_HW_PARBIT_PERIOD_TIME |
                  SND_PCM_HW_PARBIT_PERIODS |
                  SND_PCM_HW_PARBIT_BUFFER_SIZE |
                  SND_PCM_HW_PARBIT_BUFFER_TIME);
    snd_interval_t access_mask;
    const snd_interval_t *saccess_mask = hw_param_interval(sparams, SND_PCM_HW_PARAM_ACCESS);

    snd_mask_any(&access_mask);
    snd_mask_reset(&access_mask, SND_PCM_ACCESS_MMAP_INTERLEAVED);
    if (!snd_mask_test(saccess_mask, SND_PCM_ACCESS_MMAP_NONINTERLEAVED))
        snd_mask_reset(&access_mask, SND_PCM_ACCESS_MMAP_NONINTERLEAVED);
    if (!snd_mask_test(saccess_mask, SND_PCM_ACCESS_MMAP_COMPLEX) &&
        !snd_mask_test(saccess_mask, SND_PCM_ACCESS_MMAP_INTERLEAVED))
        snd_mask_reset(&access_mask, SND_PCM_ACCESS_MMAP_COMPLEX);
    err = _snd_pcm_hw_param_set_mask(params, SND_PCM_HW_PARAM_ACCESS,
                     &access_mask);
    if (err < 0)
        return err;
    err = _snd_pcm_hw_params_refine(params, links, sparams);
    if (err < 0)
        return err;
    /*params->info &= sparams->info;*/
    return 0;
}

static int snd_pcm_multi_hw_refine_slave(snd_pcm_t *pcm,
                     unsigned int slave_idx,
                     snd_pcm_hw_params_t *sparams)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_pcm_t *slave = multi->slaves[slave_idx].pcm;
    return snd_pcm_hw_refine(slave, sparams);
}

static int snd_pcm_multi_hw_refine(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    unsigned int k;
    snd_pcm_hw_params_t sparams[multi->slaves_count];
    int err;
    unsigned int cmask, changed;

    err = snd_pcm_multi_hw_refine_cprepare(pcm, params);
    if (err < 0)
        return err;
    for (k = 0; k < multi->slaves_count; ++k) {
        err = snd_pcm_multi_hw_refine_sprepare(pcm, k, &sparams[k]);
        if (err < 0) {
            awalsa_err("Slave PCM #%d not usable\n", k);
            return err;
        }
    }
    do {
        cmask = params->cmask;
        params->cmask = 0;
        for (k = 0; k < multi->slaves_count; ++k) {
            err = snd_pcm_multi_hw_refine_schange(pcm, k, params, &sparams[k]);
            if (err >= 0)
                err = snd_pcm_multi_hw_refine_slave(pcm, k, &sparams[k]);
            if (err < 0) {
                snd_pcm_multi_hw_refine_cchange(pcm, k, params, &sparams[k]);
                return err;
            }
            err = snd_pcm_multi_hw_refine_cchange(pcm, k, params, &sparams[k]);
            if (err < 0)
                return err;
        }
        err = snd_pcm_hw_refine_soft(pcm, params);
        changed = params->cmask;
        params->cmask |= cmask;
        if (err < 0)
            return err;
    } while (changed);
    return 0;
}

static int snd_pcm_multi_hw_params_slave(snd_pcm_t *pcm,
                     unsigned int slave_idx,
                     snd_pcm_hw_params_t *sparams)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_pcm_t *slave = multi->slaves[slave_idx].pcm;
    int err = snd_pcm_hw_params(slave, sparams);
    if (err < 0)
        return err;
    err = snd_pcm_areas_silence(slave->running_areas, 0, slave->channels, slave->buffer_size, slave->format);
    if (err < 0)
        return err;
    if (slave->stopped_areas) {
        err = snd_pcm_areas_silence(slave->stopped_areas, 0, slave->channels, slave->buffer_size, slave->format);
        if (err < 0)
            return err;
    }
    return 0;
}

/* reset links to the normal state
 * slave #0 = trigger master
 * slave #1-(N-1) = trigger slaves, linked is set to #0
 */
/*TODO pcm_link is inneed by hw_type */
static void reset_links(snd_pcm_multi_t *multi)
{
    unsigned int i;

    for (i = 0; i < multi->slaves_count; ++i) {
        if (multi->slaves[i].linked)
            snd_pcm_unlink(multi->slaves[i].linked);
        multi->slaves[0].linked = NULL;
        if (! i)
            continue;
        if (snd_pcm_link(multi->slaves[0].pcm, multi->slaves[i].pcm) >= 0)
            multi->slaves[i].linked = multi->slaves[0].pcm;
    }
}

static int snd_pcm_multi_hw_params(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    unsigned int i;
    snd_pcm_hw_params_t sparams[multi->slaves_count];
    int err;
    for (i = 0; i < multi->slaves_count; ++i) {
        err = snd_pcm_multi_hw_refine_sprepare(pcm, i, &sparams[i]);
        assert(err >= 0);
        err = snd_pcm_multi_hw_refine_schange(pcm, i, params, &sparams[i]);
        assert(err >= 0);
        err = snd_pcm_multi_hw_params_slave(pcm, i, &sparams[i]);
        if (err < 0) {
            snd_pcm_multi_hw_refine_cchange(pcm, i, params, &sparams[i]);
            return err;
        }
    }
    reset_links(multi);
    return 0;
}

static int snd_pcm_multi_hw_free(snd_pcm_t *pcm)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    unsigned int i;
    int err = 0;
    for (i = 0; i < multi->slaves_count; ++i) {
        snd_pcm_t *slave = multi->slaves[i].pcm;
        int e = snd_pcm_hw_free(slave);
        if (e < 0)
            err = e;
        if (!multi->slaves[i].linked)
            continue;
        e = snd_pcm_unlink(slave);
        if (e < 0)
            err = e;
        multi->slaves[i].linked = NULL;
    }
    return err;
}

static int snd_pcm_multi_sw_params(snd_pcm_t *pcm, snd_pcm_sw_params_t *params)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    unsigned int i;
    int err;
    for (i = 0; i < multi->slaves_count; ++i) {
        snd_pcm_t *slave = multi->slaves[i].pcm;
        err = snd_pcm_sw_params(slave, params);
        if (err < 0)
            return err;
    }
    return 0;
}

#if 0
static int snd_pcm_multi_status(snd_pcm_t *pcm, snd_pcm_status_t *status)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_pcm_t *slave = multi->slaves[multi->master_slave].pcm;
    return snd_pcm_status(slave, status);
}
#endif

static snd_pcm_state_t snd_pcm_multi_state(snd_pcm_t *pcm)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_pcm_t *slave = multi->slaves[multi->master_slave].pcm;
    return snd_pcm_state(slave);
}

static int snd_pcm_multi_hwsync(snd_pcm_t *pcm)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_pcm_t *slave = multi->slaves[multi->master_slave].pcm;
    return snd_pcm_hwsync(slave);
}

static int snd_pcm_multi_delay(snd_pcm_t *pcm, snd_pcm_sframes_t *delayp)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_pcm_t *slave = multi->slaves[multi->master_slave].pcm;
    return snd_pcm_delay(slave, delayp);
}

static snd_pcm_sframes_t snd_pcm_multi_avail_update(snd_pcm_t *pcm)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_pcm_sframes_t ret = LONG_MAX;
    unsigned int i;
    for (i = 0; i < multi->slaves_count; ++i) {
        snd_pcm_sframes_t avail;
        avail = snd_pcm_avail_update(multi->slaves[i].pcm);
        if (avail < 0)
            return avail;
        if (ret > avail)
            ret = avail;
    }
    return ret;
}

#if 0
static int snd_pcm_multi_htimestamp(snd_pcm_t *pcm, snd_pcm_uframes_t *avail,
                    snd_htimestamp_t *tstamp)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_pcm_t *slave = multi->slaves[multi->master_slave].pcm;
    return snd_pcm_htimestamp(slave, avail, tstamp);
}
#endif

static int snd_pcm_multi_prepare(snd_pcm_t *pcm)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    int result = 0, err;
    unsigned int i;
    for (i = 0; i < multi->slaves_count; ++i) {
        /* We call prepare to each slave even if it's linked.
         * This is to make sure to sync non-mmaped control/status.
         */
        err = snd_pcm_prepare(multi->slaves[i].pcm);
        if (err < 0)
            result = err;
    }
    return result;
}

static int snd_pcm_multi_reset(snd_pcm_t *pcm)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    int result = 0, err;
    unsigned int i;
    for (i = 0; i < multi->slaves_count; ++i) {
        /* Reset each slave, as well as in prepare */
        err = snd_pcm_reset(multi->slaves[i].pcm);
        if (err < 0)
            result = err;
    }
    return result;
}

/* when the first slave PCM is linked, it means that the whole multi
 * plugin instance is linked manually to another PCM.  in this case,
 * we need to trigger the master.
 */
static int snd_pcm_multi_start(snd_pcm_t *pcm)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    int err = 0;
    unsigned int i;
    if (multi->slaves[0].linked)
        return snd_pcm_start(multi->slaves[0].linked);
    for (i = 0; i < multi->slaves_count; ++i) {
        if (multi->slaves[i].linked)
            continue;
        err = snd_pcm_start(multi->slaves[i].pcm);
        if (err < 0)
            return err;
    }
    return err;
}

static int snd_pcm_multi_drop(snd_pcm_t *pcm)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    int err = 0;
    unsigned int i;
    if (multi->slaves[0].linked)
        return snd_pcm_drop(multi->slaves[0].linked);
    for (i = 0; i < multi->slaves_count; ++i) {
        if (multi->slaves[i].linked)
            continue;
        err = snd_pcm_drop(multi->slaves[i].pcm);
        if (err < 0)
            return err;
    }
    return err;
}

static int snd_pcm_multi_drain(snd_pcm_t *pcm)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    int err = 0;
    unsigned int i;
    if (multi->slaves[0].linked)
        return snd_pcm_drain(multi->slaves[0].linked);
    for (i = 0; i < multi->slaves_count; ++i) {
        if (multi->slaves[i].linked)
            continue;
        err = snd_pcm_drain(multi->slaves[i].pcm);
        if (err < 0)
            return err;
    }
    return err;
}

static int snd_pcm_multi_pause(snd_pcm_t *pcm, int enable)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    int err = 0;
    unsigned int i;
    if (multi->slaves[0].linked)
        return snd_pcm_pause(multi->slaves[0].linked, enable);
    for (i = 0; i < multi->slaves_count; ++i) {
        if (multi->slaves[i].linked)
            continue;
        err = snd_pcm_pause(multi->slaves[i].pcm, enable);
        if (err < 0)
            return err;
    }
    return err;
}

static int snd_pcm_multi_channel_info(snd_pcm_t *pcm, snd_pcm_channel_info_t *info)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    unsigned int channel = info->channel;
    snd_pcm_multi_channel_t *c = &multi->channels[channel];
    int err;
    if (c->slave_idx < 0)
        return -ENXIO;
    info->channel = c->slave_channel;
    err = snd_pcm_channel_info(multi->slaves[c->slave_idx].pcm, info);
    info->channel = channel;
    return err;
}

#if 0
static snd_pcm_sframes_t snd_pcm_multi_rewindable(snd_pcm_t *pcm)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    unsigned int i;
    snd_pcm_sframes_t frames = LONG_MAX;

    for (i = 0; i < multi->slaves_count; ++i) {
        snd_pcm_sframes_t f = snd_pcm_rewindable(multi->slaves[i].pcm);
        if (f <= 0)
            return f;
        if (f < frames)
            frames = f;
    }

    return frames;

}

static snd_pcm_sframes_t snd_pcm_multi_forwardable(snd_pcm_t *pcm)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    unsigned int i;
    snd_pcm_sframes_t frames = LONG_MAX;

    for (i = 0; i < multi->slaves_count; ++i) {
        snd_pcm_sframes_t f = snd_pcm_forwardable(multi->slaves[i].pcm);
        if (f <= 0)
            return f;
        if (f < frames)
            frames = f;
    }

    return frames;

}

static snd_pcm_sframes_t snd_pcm_multi_rewind(snd_pcm_t *pcm, snd_pcm_uframes_t frames)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    unsigned int i;
    snd_pcm_uframes_t pos[multi->slaves_count];
    memset(pos, 0, sizeof(pos));
    for (i = 0; i < multi->slaves_count; ++i) {
        snd_pcm_t *slave_i = multi->slaves[i].pcm;
        snd_pcm_sframes_t f = snd_pcm_rewind(slave_i, frames);
        if (f < 0)
            return f;
        pos[i] = f;
        frames = f;
    }
    /* Realign the pointers */
    for (i = 0; i < multi->slaves_count; ++i) {
        snd_pcm_t *slave_i = multi->slaves[i].pcm;
        snd_pcm_uframes_t f = pos[i] - frames;
        snd_pcm_sframes_t result;
        if (f > 0) {
            result = INTERNAL(snd_pcm_forward)(slave_i, f);
            if (result < 0)
                return result;
            if ((snd_pcm_uframes_t)result != f)
                return -EIO;
        }
    }
    return frames;
}

static snd_pcm_sframes_t snd_pcm_multi_forward(snd_pcm_t *pcm, snd_pcm_uframes_t frames)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    unsigned int i;
    snd_pcm_uframes_t pos[multi->slaves_count];
    memset(pos, 0, sizeof(pos));
    for (i = 0; i < multi->slaves_count; ++i) {
        snd_pcm_t *slave_i = multi->slaves[i].pcm;
        snd_pcm_sframes_t f = INTERNAL(snd_pcm_forward)(slave_i, frames);
        if (f < 0)
            return f;
        pos[i] = f;
        frames = f;
    }
    /* Realign the pointers */
    for (i = 0; i < multi->slaves_count; ++i) {
        snd_pcm_t *slave_i = multi->slaves[i].pcm;
        snd_pcm_uframes_t f = pos[i] - frames;
        snd_pcm_sframes_t result;
        if (f > 0) {
            result = snd_pcm_rewind(slave_i, f);
            if (result < 0)
                return result;
            if ((snd_pcm_uframes_t)result != f)
                return -EIO;
        }
    }
    return frames;
}

static int snd_pcm_multi_resume(snd_pcm_t *pcm)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    int err = 0;
    unsigned int i;
    if (multi->slaves[0].linked)
        return snd_pcm_resume(multi->slaves[0].linked);
    for (i = 0; i < multi->slaves_count; ++i) {
        if (multi->slaves[i].linked)
            continue;
        err = snd_pcm_resume(multi->slaves[i].pcm);
        if (err < 0)
            return err;
    }
    return err;
}

/* if a multi plugin instance is linked as slaves, every slave PCMs
 * including the first one has to be relinked to the given master.
 */
static int snd_pcm_multi_link_slaves(snd_pcm_t *pcm, snd_pcm_t *master)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    unsigned int i;
    int err;

    for (i = 0; i < multi->slaves_count; ++i) {
        snd_pcm_unlink(multi->slaves[i].pcm);
        multi->slaves[i].linked = NULL;
        err = snd_pcm_link(master, multi->slaves[i].pcm);
        if (err < 0) {
            reset_links(multi);
            return err;
        }
        multi->slaves[i].linked = master;
    }
    return 0;
}

/* linking to a multi as a master is easy - simply link to the first
 * slave element as its own slaves are already linked.
 */
static int snd_pcm_multi_link(snd_pcm_t *pcm1, snd_pcm_t *pcm2)
{
    snd_pcm_multi_t *multi = pcm1->private_data;
    if (multi->slaves[0].pcm->fast_ops->link)
        return multi->slaves[0].pcm->fast_ops->link(multi->slaves[0].pcm, pcm2);
    return -ENOSYS;
}

static int snd_pcm_multi_unlink(snd_pcm_t *pcm)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    unsigned int i;

    for (i = 0; i < multi->slaves_count; ++i) {
        if (multi->slaves[i].linked)
            snd_pcm_unlink(multi->slaves[i].linked);
        multi->slaves[0].linked = NULL;
    }
    return 0;
}
#endif

static snd_pcm_sframes_t snd_pcm_multi_mmap_commit(snd_pcm_t *pcm,
                           snd_pcm_uframes_t offset,
                           snd_pcm_uframes_t size)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_pcm_t *slave;
    unsigned int i;
    snd_pcm_sframes_t result;

    for (i = 0; i < multi->slaves_count; ++i) {
        slave = multi->slaves[i].pcm;
        result = snd_pcm_mmap_commit(slave, offset, size);
        if (result < 0)
            return result;
        if ((snd_pcm_uframes_t)result != size)
            return -EIO;
    }
    return size;
}

static int snd_pcm_multi_munmap(snd_pcm_t *pcm)
{
    free(pcm->mmap_channels);
    free(pcm->running_areas);
    pcm->mmap_channels = NULL;
    pcm->running_areas = NULL;
    return 0;
}

static int snd_pcm_multi_mmap(snd_pcm_t *pcm)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    unsigned int c;

    pcm->mmap_channels = calloc(pcm->channels,
                    sizeof(pcm->mmap_channels[0]));
    pcm->running_areas = calloc(pcm->channels,
                    sizeof(pcm->running_areas[0]));
    if (!pcm->mmap_channels || !pcm->running_areas) {
        snd_pcm_multi_munmap(pcm);
        return -ENOMEM;
    }

    /* Copy the slave mmapped buffer data */
    for (c = 0; c < pcm->channels; c++) {
        snd_pcm_multi_channel_t *chan = &multi->channels[c];
        snd_pcm_t *slave;
        if (chan->slave_idx < 0) {
            snd_pcm_multi_munmap(pcm);
            return -ENXIO;
        }
        slave = multi->slaves[chan->slave_idx].pcm;
        pcm->mmap_channels[c] =
            slave->mmap_channels[chan->slave_channel];
        pcm->mmap_channels[c].channel = c;
        pcm->running_areas[c] =
            slave->running_areas[chan->slave_channel];
    }
    return 0;
}

static int snd_pcm_multi_may_wait_for_avail_min(snd_pcm_t *pcm, snd_pcm_uframes_t avail ATTRIBUTE_UNUSED)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_pcm_t *slave = multi->slaves[multi->master_slave].pcm;
    return snd_pcm_may_wait_for_avail_min(slave, snd_pcm_mmap_avail(slave));
}

#if 0
static snd_pcm_chmap_query_t **snd_pcm_multi_query_chmaps(snd_pcm_t *pcm)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_pcm_chmap_query_t **slave_maps[multi->slaves_count];
    snd_pcm_chmap_query_t **maps;
    unsigned int i;
    int err = -ENOMEM;

    memset(slave_maps, 0, sizeof(slave_maps));
    maps = calloc(2, sizeof(*maps));
    if (!maps)
        return NULL;
    maps[0] = calloc(multi->channels_count + 2, sizeof(int *));
    if (!maps[0])
        goto error;
    maps[0]->type = SND_CHMAP_TYPE_FIXED;
    maps[0]->map.channels = multi->channels_count;

    for (i = 0; i < multi->slaves_count; i++) {
        slave_maps[i] = snd_pcm_query_chmaps(multi->slaves[i].pcm);
        if (!slave_maps[i])
            goto error;
    }

    for (i = 0; i < multi->channels_count; i++) {
        snd_pcm_multi_channel_t *bind = &multi->channels[i];
        unsigned int slave_channels =
            multi->slaves[bind->slave_idx].channels_count;
        snd_pcm_chmap_query_t **p;

        for (p = slave_maps[bind->slave_idx]; *p; p++) {
            if ((*p)->map.channels == slave_channels) {
                maps[0]->map.pos[i] =
                    (*p)->map.pos[bind->slave_channel];
                break;
            }
        }
    }
    err = 0;

 error:
    for (i = 0; i < multi->slaves_count; i++) {
        if (slave_maps[i])
            snd_pcm_free_chmaps(slave_maps[i]);
    }

    if (err) {
        snd_pcm_free_chmaps(maps);
        return NULL;
    }

    return maps;
}

static snd_pcm_chmap_t *snd_pcm_multi_get_chmap(snd_pcm_t *pcm)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_pcm_chmap_t *map;
    snd_pcm_chmap_t *slave_maps[multi->slaves_count];
    unsigned int i;
    int err = -ENOMEM;

    memset(slave_maps, 0, sizeof(slave_maps));
    map = calloc(multi->channels_count + 1, sizeof(int));
    if (!map)
        return NULL;

    for (i = 0; i < multi->slaves_count; i++) {
        slave_maps[i] = snd_pcm_get_chmap(multi->slaves[i].pcm);
        if (!slave_maps[i])
            goto error;
    }

    map->channels = multi->channels_count;
    for (i = 0; i < multi->channels_count; i++) {
        snd_pcm_multi_channel_t *bind = &multi->channels[i];
        map->pos[i] = slave_maps[bind->slave_idx]->pos[bind->slave_channel];
    }
    err = 0;

 error:
    for (i = 0; i < multi->slaves_count; i++)
        free(slave_maps[i]);

    if (err) {
        free(map);
        return NULL;
    }

    return map;
}

static int snd_pcm_multi_set_chmap(snd_pcm_t *pcm, const snd_pcm_chmap_t *map)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_pcm_chmap_t *slave_maps[multi->slaves_count];
    unsigned int i;
    int err = 0;

    if (map->channels != multi->channels_count)
        return -EINVAL;

    for (i = 0; i < multi->slaves_count; i++) {
        slave_maps[i] = calloc(multi->slaves[i].channels_count + 1,
                       sizeof(int));
        if (!slave_maps[i]) {
            for (i++; i < multi->slaves_count; i++)
                slave_maps[i] = NULL;
            err = -ENOMEM;
            goto error;
        }
    }

    for (i = 0; i < multi->channels_count; i++) {
        snd_pcm_multi_channel_t *bind = &multi->channels[i];
        slave_maps[bind->slave_idx]->pos[bind->slave_channel] =
            map->pos[i];
    }

    for (i = 0; i < multi->slaves_count; i++) {
        err = snd_pcm_set_chmap(multi->slaves[i].pcm, slave_maps[i]);
        if (err < 0)
            goto error;
    }

 error:
    for (i = 0; i < multi->slaves_count; i++)
        free(slave_maps[i]);

    return err;
}
#endif

static void snd_pcm_multi_dump(snd_pcm_t *pcm)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    unsigned int k;
    printf("Multi PCM\n");
    printf("  Channel bindings:\n");
    for (k = 0; k < multi->channels_count; ++k) {
        snd_pcm_multi_channel_t *c = &multi->channels[k];
        if (c->slave_idx < 0)
            continue;
        printf("    %d: slave %d, channel %d\n",
            k, c->slave_idx, c->slave_channel);
    }
    if (pcm->setup) {
        printf("Its setup is:\n");
        snd_pcm_dump_setup(pcm);
    }
    for (k = 0; k < multi->slaves_count; ++k) {
        printf("Slave #%d: ", k);
        snd_pcm_dump(multi->slaves[k].pcm);
    }
}

static int snd_pcm_multi_wait(snd_pcm_t *pcm, int timeout)
{
    snd_pcm_multi_t *multi = pcm->private_data;
    snd_pcm_t *spcm = multi->slaves[multi->master_slave].pcm;

    return snd_pcm_wait_nocheck(spcm, timeout);
}

static const snd_pcm_ops_t snd_pcm_multi_ops = {
    .close = snd_pcm_multi_close,
    /*.info = snd_pcm_multi_info,*/
    .hw_refine = snd_pcm_multi_hw_refine,
    .hw_params = snd_pcm_multi_hw_params,
    .hw_free = snd_pcm_multi_hw_free,
    .sw_params = snd_pcm_multi_sw_params,
    .channel_info = snd_pcm_multi_channel_info,
    .dump = snd_pcm_multi_dump,
    /*.nonblock = snd_pcm_multi_nonblock,*/
    /*.async = snd_pcm_multi_async,*/
    .mmap = snd_pcm_multi_mmap,
    .munmap = snd_pcm_multi_munmap,
    /*.query_chmaps = snd_pcm_multi_query_chmaps,*/
    /*.get_chmap = snd_pcm_multi_get_chmap,*/
    /*.set_chmap = snd_pcm_multi_set_chmap,*/
};

static const snd_pcm_fast_ops_t snd_pcm_multi_fast_ops = {
    /*.status = snd_pcm_multi_status,*/
    .state = snd_pcm_multi_state,
    .hwsync = snd_pcm_multi_hwsync,
    .delay = snd_pcm_multi_delay,
    .prepare = snd_pcm_multi_prepare,
    .reset = snd_pcm_multi_reset,
    .start = snd_pcm_multi_start,
    .drop = snd_pcm_multi_drop,
    .drain = snd_pcm_multi_drain,
    .pause = snd_pcm_multi_pause,
    .writei = snd_pcm_mmap_writei,
    .readi = snd_pcm_mmap_readi,
    /*.rewindable = snd_pcm_multi_rewindable,*/
    /*.rewind = snd_pcm_multi_rewind,*/
    /*.forwardable = snd_pcm_multi_forwardable,*/
    /*.forward = snd_pcm_multi_forward,*/
    /*.resume = snd_pcm_multi_resume,*/
    /*.link = snd_pcm_multi_link,*/
    /*.link_slaves = snd_pcm_multi_link_slaves,*/
    /*.unlink = snd_pcm_multi_unlink,*/
    .avail_update = snd_pcm_multi_avail_update,
    .mmap_commit = snd_pcm_multi_mmap_commit,
    /*.htimestamp = snd_pcm_multi_htimestamp,*/
    .may_wait_for_avail_min = snd_pcm_multi_may_wait_for_avail_min,
    .wait = snd_pcm_multi_wait,
};

static int snd_pcm_multi_open(snd_pcm_t **pcmp, const char *name,
            unsigned int slaves_count,
            snd_pcm_t **slaves_pcm, unsigned int *schannels_count,
            unsigned int channels_count,
            int *sidxs, unsigned int *schannels,
            int close_slaves)
{
    int err;
    snd_pcm_t *pcm;
    snd_pcm_multi_t *multi;
    unsigned int i;
    snd_pcm_stream_t stream;
    unsigned int master_slave = 0;

    assert(pcmp);
    assert(slaves_count > 0 && slaves_pcm && schannels_count);
    assert(channels_count > 0 && sidxs && schannels);
    assert(master_slave < slaves_count);

    multi = calloc(1, sizeof(snd_pcm_multi_t));
    if (!multi) {
        return -ENOMEM;
    }
    stream = slaves_pcm[0]->stream;
    multi->slaves_count = slaves_count;
    multi->master_slave = master_slave;
    multi->slaves = calloc(slaves_count, sizeof(*multi->slaves));
    if (!multi->slaves) {
        free(multi);
        return -ENOMEM;
    }
    multi->channels_count = channels_count;
    multi->channels = calloc(channels_count, sizeof(*multi->channels));
    if (!multi->channels) {
        free(multi->slaves);
        free(multi);
        return -ENOMEM;
    }
    for (i = 0; i < slaves_count; ++i) {
        snd_pcm_multi_slave_t *slave = &multi->slaves[i];
        assert(slaves_pcm[i]->stream == stream);
        slave->pcm = slaves_pcm[i];
        slave->channels_count = schannels_count[i];
        slave->close_slave = close_slaves;
    }
    for (i = 0; i < channels_count; ++i) {
        snd_pcm_multi_channel_t *bind = &multi->channels[i];
        assert(sidxs[i] < (int)slaves_count);
        assert(schannels[i] < schannels_count[sidxs[i]]);
        bind->slave_idx = sidxs[i];
        bind->slave_channel = schannels[i];
        if (sidxs[i] < 0)
            continue;
    }
    multi->channels_count = channels_count;

    err = snd_pcm_new(&pcm, SND_PCM_TYPE_MULTI, name, stream, multi->slaves[0].pcm->mode);
    if (err < 0) {
        awalsa_err("failed to new multi pcm\n");
        free(multi->slaves);
        free(multi->channels);
        free(multi);
        return err;
    }

    pcm->mmap_rw = 1;
    pcm->mmap_shadow = 1;
    pcm->ops = &snd_pcm_multi_ops;
    pcm->fast_ops = &snd_pcm_multi_fast_ops;
    pcm->private_data = multi;
    snd_pcm_link_hw_ptr(pcm, multi->slaves[master_slave].pcm);
    snd_pcm_link_appl_ptr(pcm, multi->slaves[master_slave].pcm);
    *pcmp = pcm;

    return 0;
}

#define SND_MULTI_BINDINGS_MAX  (20)
int _snd_pcm_multi_open(snd_pcm_t **pcmp, const snd_pcm_config_t *pcm_config,
        snd_pcm_stream_t stream, int mode)
{
    int err, i;
    const snd_pcm_multi_config_t *multi_config = (const snd_pcm_multi_config_t *)(pcm_config->config);
    const char **slaves_id = NULL;
    const snd_pcm_config_t **slaves_conf = NULL;
    snd_pcm_t **slaves_pcm = NULL;
    unsigned int *slaves_channels = NULL;
    int *channels_sidx = NULL;
    unsigned int *channels_schannel = NULL;
    unsigned int slaves_count = 0;
    unsigned int channels_count = 0;

    if (!multi_config->slaves) {
        awalsa_err("slaves is not defined\n");
        return -EINVAL;
    }
    if (!multi_config->bindings) {
        awalsa_err("bindings is not defined\n");
        return -EINVAL;
    }
    for (i = 0; i < ALSA_PCM_MULTI_SLAVES_MAX; i++) {
        if (!multi_config->slaves[i].pcm_alias)
            break;
        ++slaves_count;
    }
    if (i == ALSA_PCM_MULTI_SLAVES_MAX) {
        awalsa_err("slave number unknown\n");
        return -EINVAL;
    }
    for (i = 0; i < SND_MULTI_BINDINGS_MAX; i++) {
        int cchannel = multi_config->bindings[i].cchannel;
        if (cchannel < 0)
            break;
        if (cchannel >= channels_count)
            channels_count = cchannel + 1;
    }
    if (i == SND_MULTI_BINDINGS_MAX) {
        awalsa_err("bindings cchannel unknown\n");
        return -EINVAL;
    }

    slaves_id = calloc(slaves_count, sizeof(*slaves_id));
    slaves_conf  = calloc(slaves_count, sizeof(*slaves_conf));
    slaves_pcm = calloc(slaves_count, sizeof(*slaves_pcm));
    slaves_channels = calloc(slaves_count, sizeof(*slaves_channels));
    channels_sidx = calloc(channels_count, sizeof(*channels_sidx));
    channels_schannel = calloc(channels_count, sizeof(*channels_schannel));
    if (!slaves_id || !slaves_conf || !slaves_pcm || !slaves_channels ||
        !channels_sidx || !channels_schannel) {
        err = -ENOMEM;
        goto _free;
    }
    for (i = 0; i < channels_count; i++)
        channels_sidx[i] = -1;

    for (i = 0; i < slaves_count; i++) {
        slaves_id[i] = multi_config->slaves[i].pcm_alias;
        slaves_conf[i] = snd_pcm_config_get_config(multi_config->slaves[i].pcm);
        if (!slaves_conf[i]) {
            err = -EINVAL;
            goto _free;
        }
        slaves_channels[i] = multi_config->slaves[i].channels;
    }

    for (i = 0; i < channels_count; i++) {
        int cchannel = -1, slave = -1, schannel = -1;
        int j;
        const char *str;
        cchannel = multi_config->bindings[i].cchannel;
        str = multi_config->bindings[i].pcm_alias;
        for (j = 0; j < slaves_count; j++) {
            if (!strcmp(slaves_id[j], str))
                slave = j;
        }
        schannel = multi_config->bindings[i].schannel;
        channels_sidx[cchannel] = slave;
        channels_schannel[cchannel] = schannel;
    }
    for (i = 0; i < slaves_count; i++) {
        err = snd_pcm_open_config(&slaves_pcm[i], slaves_conf[i], stream, mode);
        if (err < 0)
            goto _free;
        slaves_conf[i] = NULL;
    }
    err = snd_pcm_multi_open(pcmp, pcm_config->name, slaves_count,
                slaves_pcm, slaves_channels,
                channels_count,
                channels_sidx, channels_schannel, 1);
_free:
    if (err < 0)
        free(slaves_conf);
    free(slaves_pcm);
    free(slaves_channels);
    free(channels_sidx);
    free(channels_schannel);
    free(slaves_id);
    return err;
}
