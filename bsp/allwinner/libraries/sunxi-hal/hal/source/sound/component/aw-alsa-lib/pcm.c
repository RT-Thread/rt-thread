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
#include <sound/ksound.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <aw-alsa-lib/pcm.h>
#include <aw-alsa-lib/pcm_config.h>
#include "pcm_local.h"
#include <hal_osal.h>
void snd_pcm_version(void)
{
#ifdef CONFIG_KERNEL_FREERTOS
    printf("AW-ALSA-LIB version:%s, compiled on: %s %s\n\n",
        SND_PCM_VERSION, __DATE__, __TIME__);
#else
    printf("AW-ALSA-LIB version:%s\n", SND_PCM_VERSION);
#endif
}

size_t snd_pcm_hw_params_sizeof(void)
{
        return sizeof(snd_pcm_hw_params_t);
}

size_t snd_pcm_sw_params_sizeof(void)
{
    return sizeof(snd_pcm_sw_params_t);
}

static void snd_pcm_link_ptr(snd_pcm_t *pcm, snd_pcm_rbptr_t *pcm_rbptr,
                 snd_pcm_t *slave, snd_pcm_rbptr_t *slave_rbptr)
{
    snd_pcm_t **a, **newa;
    int idx;

    a = slave_rbptr->link_dst;
    for (idx = 0; idx < slave_rbptr->link_dst_count; idx++) {
        if (a[idx] == NULL) {
            a[idx] = pcm;
            goto __found_free_place;
        }
    }
    newa = realloc(a, sizeof(snd_pcm_t *) * (slave_rbptr->link_dst_count + 1));
    if (newa == NULL) {
        pcm_rbptr->ptr = NULL;
        pcm_rbptr->offset = 0UL;
        free(a);
        return;
    }
    a = newa;
    a[slave_rbptr->link_dst_count++] = pcm;
      __found_free_place:
    pcm_rbptr->master = slave_rbptr->master ? slave_rbptr->master : slave;
    pcm_rbptr->ptr = slave_rbptr->ptr;
    pcm_rbptr->offset = slave_rbptr->offset;
    slave_rbptr->link_dst = a;
}

static void snd_pcm_unlink_ptr(snd_pcm_t *pcm, snd_pcm_rbptr_t *pcm_rbptr,
                   snd_pcm_t *slave, snd_pcm_rbptr_t *slave_rbptr)
{
    snd_pcm_t **a;
    int idx;

    a = slave_rbptr->link_dst;
    for (idx = 0; idx < slave_rbptr->link_dst_count; idx++) {
        if (a[idx] == pcm) {
            a[idx] = NULL;
            goto __found;
        }
    }
    /* assert(0); */
    return;

      __found:
    pcm_rbptr->master = NULL;
    pcm_rbptr->ptr = NULL;
    pcm_rbptr->offset = 0UL;
}

static void snd_pcm_set_ptr(snd_pcm_t *pcm, snd_pcm_rbptr_t *rbptr,
            volatile snd_pcm_uframes_t *ptr, int fd, off_t offset)
{
    rbptr->ptr = ptr;
}

void snd_pcm_link_hw_ptr(snd_pcm_t *pcm, snd_pcm_t *slave)
{
    assert(pcm);
    assert(slave);
    snd_pcm_link_ptr(pcm, &pcm->hw, slave, &slave->hw);
}

void snd_pcm_link_appl_ptr(snd_pcm_t *pcm, snd_pcm_t *slave)
{
    assert(pcm);
    assert(slave);
    snd_pcm_link_ptr(pcm, &pcm->appl, slave, &slave->appl);
}

void snd_pcm_unlink_hw_ptr(snd_pcm_t *pcm, snd_pcm_t *slave)
{
    assert(pcm);
    assert(slave);
    snd_pcm_unlink_ptr(pcm, &pcm->hw, slave, &slave->hw);
}

void snd_pcm_unlink_appl_ptr(snd_pcm_t *pcm, snd_pcm_t *slave)
{
    assert(pcm);
    assert(slave);
    snd_pcm_unlink_ptr(pcm, &pcm->appl, slave, &slave->appl);
}

/* fd and offset are not used */
void snd_pcm_set_hw_ptr(snd_pcm_t *pcm, volatile snd_pcm_uframes_t *hw_ptr,
        int fd, off_t offset)
{
    assert(pcm);
    assert(hw_ptr);
    snd_pcm_set_ptr(pcm, &pcm->hw, hw_ptr, fd, offset);
}

/* fd and offset are not used */
void snd_pcm_set_appl_ptr(snd_pcm_t *pcm, volatile snd_pcm_uframes_t *appl_ptr,
        int fd, off_t offset)
{
    assert(pcm);
    assert(appl_ptr);
    snd_pcm_set_ptr(pcm, &pcm->appl, appl_ptr, fd, offset);
}

int snd_pcm_open_config(snd_pcm_t **pcmp, const snd_pcm_config_t *pcm_config,
        snd_pcm_stream_t stream, int mode)
{
    snd_pcm_open_func_t open_func = NULL;

    open_func = snd_pcm_config_get_open_func(pcm_config->type);
    if (!open_func) {
        awalsa_err("open_func of type \"%s\" not found\n", pcm_config->type);
        return -ENODEV;
    }

    return open_func(pcmp, pcm_config, stream, mode);
}

int snd_pcm_open(snd_pcm_t **pcm, const char *name,
        snd_pcm_stream_t stream, int mode)
{
    int ret = 0, res = 0;

    const snd_pcm_config_t *top_config = NULL;
    top_config = snd_pcm_config_get_config(name);
    if (!top_config) {
        awalsa_err("pcm \"%s\": config not found\n", name);
        res = -1;
        goto out;
    }

    ret = snd_pcm_open_config(pcm, top_config, stream, mode);
    if (0 != ret) {
        awalsa_err("pcm \"%s\": snd_pcm_open_config failed (return: %d)\n", name, ret);
        res = ret;
        goto out;
    }

out:
    return res;
}

int snd_pcm_close(snd_pcm_t *pcm)
{
    int ret = 0, res = 0;

    assert(pcm);
    awalsa_debug("\n");
    if (pcm->setup && !pcm->donot_close) {
        snd_pcm_drop(pcm);
        ret = snd_pcm_hw_free(pcm);
        if (ret < 0)
            res = ret;
    }
    if (pcm->mmap_channels)
        snd_pcm_munmap(pcm);
    assert(pcm->ops->close);
    ret = pcm->ops->close(pcm->op_arg);
    if (ret < 0)
        res = ret;
    ret = snd_pcm_free(pcm);
    if (ret < 0)
        res = ret;

    return res;
}

int snd_pcm_hw_params_malloc(snd_pcm_hw_params_t **ptr)
{
    assert(ptr);
    *ptr = calloc(1, sizeof(snd_pcm_hw_params_t));
    if (!*ptr)
        return -ENOMEM;
    return 0;
}

void snd_pcm_hw_params_free(snd_pcm_hw_params_t *obj)
{
    free(obj);
}

int snd_pcm_hw_params_any(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
    assert(pcm);
    awalsa_debug("\n");
    assert(pcm->ops->hw_refine);
    _snd_pcm_hw_params_any(params);
    return snd_pcm_hw_refine(pcm,params);
}

#if 0
int snd_interval_refine(snd_interval_t *i, const snd_interval_t *v)
{
        int changed = 0;

        if (i->range.min < v->range.min) {
                i->range.min = v->range.min;
                changed = 1;
        }
        if (i->range.max > v->range.max) {
                i->range.max = v->range.max;
                changed = 1;
        }
        if (i->mask != v->mask) {
                i->mask = v->mask;
                changed = 1;
        }
        return changed;
}

int hw_param_interval_refine_one(snd_pcm_hw_params_t *params,
                    snd_pcm_hw_param_t var,
                    snd_interval_t *src)
{

}
#endif

int snd_pcm_hw_params_set_format(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, snd_pcm_format_t format)
{
    awalsa_debug("\n");
    return snd_pcm_hw_param_set(pcm, params, SND_TRY, SND_PCM_HW_PARAM_FORMAT, format, 0);
}

int snd_pcm_hw_params_set_rate(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int val, int dir)
{
    awalsa_debug("\n");
    return snd_pcm_hw_param_set(pcm, params, SND_TRY, SND_PCM_HW_PARAM_RATE, val, dir);
}

int snd_pcm_hw_params_set_period_size(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, snd_pcm_uframes_t val, int dir)
{
    awalsa_debug("\n");
    return snd_pcm_hw_param_set(pcm, params, SND_TRY, SND_PCM_HW_PARAM_PERIOD_SIZE, val, dir);
}

int snd_pcm_hw_params_set_period_size_near(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, snd_pcm_uframes_t *val, int *dir)
{
    awalsa_debug("\n");
    unsigned int _val = *val;
    int err = snd_pcm_hw_param_set_near(pcm, params, SND_PCM_HW_PARAM_PERIOD_SIZE, &_val, dir);
    if (err >= 0)
        *val = _val;
    return err;
}

int snd_pcm_hw_params_set_period_time(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int us, int dir)
{
    awalsa_debug("\n");
    return snd_pcm_hw_param_set(pcm, params, SND_TRY, SND_PCM_HW_PARAM_PERIOD_TIME, us, dir);
}

int snd_pcm_hw_params_set_period_time_near(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int *val, int *dir)
{
    awalsa_debug("\n");
    return snd_pcm_hw_param_set_near(pcm, params, SND_PCM_HW_PARAM_PERIOD_TIME, val, dir);
}

int snd_pcm_hw_params_set_buffer_size(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, snd_pcm_uframes_t val)
{
    awalsa_debug("\n");
    return snd_pcm_hw_param_set(pcm, params, SND_TRY, SND_PCM_HW_PARAM_BUFFER_SIZE, val, 0);
}

int snd_pcm_hw_params_set_buffer_size_near(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, snd_pcm_uframes_t *val)
{
    awalsa_debug("\n");
    unsigned int _val = *val;
    int err = snd_pcm_hw_param_set_near(pcm, params, SND_PCM_HW_PARAM_BUFFER_SIZE, &_val, NULL);
    if (err >= 0)
        *val = _val;
    return err;
}

int snd_pcm_hw_params_set_buffer_time(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int us)
{
    awalsa_debug("\n");
    return snd_pcm_hw_param_set(pcm, params, SND_TRY, SND_PCM_HW_PARAM_BUFFER_TIME, us, 0);
}

int snd_pcm_hw_params_set_buffer_time_near(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int *val, int *dir)
{
    awalsa_debug("\n");
    return snd_pcm_hw_param_set_near(pcm, params, SND_PCM_HW_PARAM_BUFFER_TIME, val, dir);
}

int snd_pcm_hw_params_set_channels(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int val)
{
    awalsa_debug("\n");
    return snd_pcm_hw_param_set(pcm, params, SND_TRY, SND_PCM_HW_PARAM_CHANNELS, val, 0);
}

int snd_pcm_hw_params_set_periods(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int val, int dir)
{
    awalsa_debug("\n");
    return snd_pcm_hw_param_set(pcm, params, SND_TRY, SND_PCM_HW_PARAM_PERIODS, val, dir);
}

int snd_pcm_hw_params_set_periods_near(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int *val, int *dir)
{
    awalsa_debug("\n");
    return snd_pcm_hw_param_set_near(pcm, params, SND_PCM_HW_PARAM_PERIODS, val, dir);
}

int snd_pcm_hw_params_set_access(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, snd_pcm_access_t access)
{
    awalsa_debug("\n");
    return snd_pcm_hw_param_set(pcm, params, SND_TRY, SND_PCM_HW_PARAM_ACCESS, access, 0);
}

int snd_pcm_hw_params_get_access(const snd_pcm_hw_params_t *params, snd_pcm_access_t *access)
{
    unsigned int _val;
    int err = snd_pcm_hw_param_get(params, SND_PCM_HW_PARAM_ACCESS, &_val, NULL);
    if (err >= 0)
        *access = _val;
    return err;
}

int snd_pcm_hw_params_get_format(const snd_pcm_hw_params_t *params, snd_pcm_format_t *format)
{
    unsigned int _val;
    int err = snd_pcm_hw_param_get(params, SND_PCM_HW_PARAM_FORMAT, &_val, NULL);
    if (err >= 0)
        *format = _val;
    return err;
}

int snd_pcm_hw_params_get_channels(const snd_pcm_hw_params_t *params, unsigned int *val)
{
    return snd_pcm_hw_param_get(params, SND_PCM_HW_PARAM_CHANNELS, val, NULL);
}

int snd_pcm_hw_params_get_rate(const snd_pcm_hw_params_t *params, unsigned int *val, int *dir)
{
    return snd_pcm_hw_param_get(params, SND_PCM_HW_PARAM_RATE, val, dir);
}

int snd_pcm_hw_params_get_period_time(const snd_pcm_hw_params_t *params, unsigned int *val, int *dir)
{
    return snd_pcm_hw_param_get(params, SND_PCM_HW_PARAM_PERIOD_TIME, val, dir);
}

int snd_pcm_hw_params_get_period_size(const snd_pcm_hw_params_t *params, snd_pcm_uframes_t *val, int *dir)
{
    unsigned int _val;
    int err = snd_pcm_hw_param_get(params, SND_PCM_HW_PARAM_PERIOD_SIZE, &_val, dir);
    if (err >= 0)
        *val = _val;
    return err;
}

int snd_pcm_hw_params_get_buffer_size(const snd_pcm_hw_params_t *params, snd_pcm_uframes_t *val)
{
    unsigned int _val;
    int err = snd_pcm_hw_param_get(params, SND_PCM_HW_PARAM_BUFFER_SIZE, &_val, NULL);
    if (err >= 0)
        *val = _val;
    return err;
}

int snd_pcm_hw_params_get_buffer_time(const snd_pcm_hw_params_t *params, unsigned int *val, int *dir)
{
    return snd_pcm_hw_param_get(params, SND_PCM_HW_PARAM_BUFFER_TIME, val, dir);
}

int snd_pcm_hw_params_get_periods(const snd_pcm_hw_params_t *params, unsigned int *val, int *dir)
{
    return snd_pcm_hw_param_get(params, SND_PCM_HW_PARAM_PERIODS, val, dir);
}

int snd_pcm_hw_params(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
    int ret;
    assert(pcm && params);
    awalsa_debug("\n");
    ret = _snd_pcm_hw_params_internal(pcm, params);
    if (ret < 0)
        return ret;
    ret = snd_pcm_prepare(pcm);
    return ret;
}

int snd_pcm_hw_free(snd_pcm_t *pcm)
{
    int ret;
    assert(pcm);
    awalsa_debug("\n");

    if (!pcm->setup)
        return 0;
    if (pcm->mmap_channels) {
        ret = snd_pcm_munmap(pcm);
        if (ret < 0)
            return ret;
    }

    assert(pcm->ops->hw_free);
    ret = pcm->ops->hw_free(pcm->op_arg);
    pcm->setup = 0;

    return ret;
}

int snd_pcm_sw_params_current(snd_pcm_t *pcm, snd_pcm_sw_params_t *params)
{
    assert(pcm && params);
    params->avail_min = pcm->avail_min;
    params->start_threshold = pcm->start_threshold;
    params->stop_threshold = pcm->stop_threshold;
    params->silence_size = pcm->silence_size;
    params->boundary = pcm->boundary;
    return 0;
}

int snd_pcm_sw_params_set_start_threshold(snd_pcm_t *pcm, snd_pcm_sw_params_t *params, snd_pcm_uframes_t val)
{
    assert(pcm && params);
    params->start_threshold = val;
    return 0;
}

int snd_pcm_sw_params_get_start_threshold(snd_pcm_sw_params_t *params, snd_pcm_uframes_t *val)
{
    assert(params && val);
    *val = params->start_threshold;
    return 0;
}

int snd_pcm_sw_params_set_stop_threshold(snd_pcm_t *pcm, snd_pcm_sw_params_t *params, snd_pcm_uframes_t val)
{
    assert(pcm && params);
    params->stop_threshold = val;
    return 0;
}

int snd_pcm_sw_params_get_stop_threshold(snd_pcm_sw_params_t *params, snd_pcm_uframes_t *val)
{
    assert(params && val);
    *val = params->stop_threshold;
    return 0;
}

int snd_pcm_sw_params_set_silence_size(snd_pcm_t *pcm, snd_pcm_sw_params_t *params, snd_pcm_uframes_t val)
{
    assert(pcm && params);
    params->silence_size = val;
    return 0;
}

int snd_pcm_sw_params_get_silence_size(snd_pcm_sw_params_t *params, snd_pcm_uframes_t *val)
{
    assert(params && val);
    *val = params->silence_size;
    return 0;
}

int snd_pcm_sw_params_set_avail_min(snd_pcm_t *pcm, snd_pcm_sw_params_t *params, snd_pcm_uframes_t val)
{
    assert(pcm && params);
    params->avail_min = val;
    return 0;
}

int snd_pcm_sw_params_get_avail_min(const snd_pcm_sw_params_t *params, snd_pcm_uframes_t *val)
{
    assert(params && val);
    *val = params->avail_min;
    return 0;
}

int snd_pcm_sw_params_get_boundary(const snd_pcm_sw_params_t *params, snd_pcm_uframes_t *val)
{
    assert(params && val);
    *val = params->boundary;
    return 0;
}

int snd_pcm_sw_params(snd_pcm_t *pcm, snd_pcm_sw_params_t *params)
{
    int ret = 0;

    assert(pcm && params);
    /* the hw_params must be set at first!!! */
    if (!pcm->setup) {
        awalsa_err("PCM not set up\n");
        return -EIO;
    }
    if (!params->avail_min) {
        awalsa_err("params->avail_min is 0\n");
        return -EINVAL;
    }

    assert(pcm->ops->sw_params);
    snd_pcm_lock(pcm);
    ret = pcm->ops->sw_params(pcm->op_arg, params);
    if (ret < 0) {
        snd_pcm_unlock(pcm);
        return ret;
    }
    pcm->avail_min = params->avail_min;
    pcm->start_threshold = params->start_threshold;
    pcm->stop_threshold = params->stop_threshold;
    pcm->silence_size = params->silence_size;
    pcm->boundary = params->boundary;
    snd_pcm_unlock(pcm);
    return ret;
}

int snd_pcm_prepare(snd_pcm_t *pcm)
{
    int ret = 0;

    assert(pcm);
    awalsa_debug("\n");

    assert(pcm->fast_ops->prepare);
    snd_pcm_lock(pcm);
    ret = pcm->fast_ops->prepare(pcm->fast_op_arg);
    snd_pcm_unlock(pcm);
    return ret;
}

int snd_pcm_reset(snd_pcm_t *pcm)
{
    int err;

    assert(pcm);
    awalsa_debug("\n");

    assert(pcm->fast_ops->reset);
    if (! pcm->setup) {
        awalsa_err("PCM not set up\n");
        return -EIO;
    }
    snd_pcm_lock(pcm);
    err = pcm->fast_ops->reset(pcm->fast_op_arg);
    snd_pcm_unlock(pcm);
    return err;
}

int snd_pcm_start(snd_pcm_t *pcm)
{
    int ret = 0;

    assert(pcm);
    awalsa_debug("\n");

    assert(pcm->fast_ops->start);
    snd_pcm_lock(pcm);
    ret = pcm->fast_ops->start(pcm->fast_op_arg);
    snd_pcm_unlock(pcm);
    return ret;
}

int snd_pcm_drop(snd_pcm_t *pcm)
{
    int ret = 0;

    assert(pcm);
    awalsa_debug("\n");

    assert(pcm->fast_ops->drop);
    snd_pcm_lock(pcm);
    ret = pcm->fast_ops->drop(pcm->fast_op_arg);
    snd_pcm_unlock(pcm);
    return ret;
}

int snd_pcm_drain(snd_pcm_t *pcm)
{
    assert(pcm);
    awalsa_debug("\n");

    assert(pcm->fast_ops->drain);
    /* do not lock. lock is handled in the callback */
    return pcm->fast_ops->drain(pcm->fast_op_arg);
}

int snd_pcm_pause(snd_pcm_t *pcm, int enable)
{
    int ret = 0;

    assert(pcm);
    awalsa_debug("\n");

    assert(pcm->fast_ops->pause);
    snd_pcm_lock(pcm);
    ret = pcm->fast_ops->pause(pcm->fast_op_arg, enable);
    snd_pcm_unlock(pcm);
    return ret;
}

snd_pcm_state_t snd_pcm_state(snd_pcm_t *pcm)
{
    snd_pcm_state_t state;

    assert(pcm);
    awalsa_debug("\n");

    assert(pcm->fast_ops->state);
    snd_pcm_lock(pcm);
    state = pcm->fast_ops->state(pcm->fast_op_arg);
    snd_pcm_unlock(pcm);

    return state;
}

int snd_pcm_hwsync(snd_pcm_t *pcm)
{
    int err;

    assert(pcm);
    if (!pcm->setup) {
        awalsa_err("PCM not set up\n");
        return -EIO;
    }
    snd_pcm_lock(pcm);
    err = __snd_pcm_hwsync(pcm);
    snd_pcm_unlock(pcm);
    return err;
}

snd_pcm_stream_t snd_pcm_stream(snd_pcm_t *pcm)
{
    assert(pcm);
    return pcm->stream;
}

snd_pcm_sframes_t snd_pcm_writei(snd_pcm_t *pcm, const void *buffer, snd_pcm_uframes_t size)
{
    snd_pcm_sframes_t ret = 0;

    assert(pcm);
    assert(size == 0 || buffer);
    /*awalsa_debug("\n");*/
    ret = pcm->fast_ops->writei(pcm->fast_op_arg, buffer, size);

    return ret;
}

snd_pcm_sframes_t snd_pcm_readi(snd_pcm_t *pcm, void *buffer, snd_pcm_uframes_t size)
{

    snd_pcm_sframes_t ret = 0;

    assert(pcm);
    assert(size == 0 || buffer);
    awalsa_debug("\n");
    ret = pcm->fast_ops->readi(pcm->fast_op_arg, buffer, size);

    return ret;
}

int snd_pcm_resume(snd_pcm_t *pcm)
{
    assert(pcm);
    awalsa_err("suspend state not supported.\n");
    return -1;
}

int snd_pcm_recover(snd_pcm_t *pcm, int err, int silent)
{
    assert(pcm);
    if (err > 0)
        err = -err;
    if (err == -EPIPE) {
        const char *s = NULL;
        if (snd_pcm_stream(pcm) == SND_PCM_STREAM_PLAYBACK)
            s = "underrun";
        else
            s = "overrun";
        if (!silent)
            awalsa_err("%s occured\n", s);
        err = snd_pcm_prepare(pcm);
        if (err < 0) {
            awalsa_err("cannot recovery from %s, prepare return: %d",
                s, err);
            return err;
        }
        return 0;
    }
    if (err == -ESTRPIPE) {
        awalsa_info("resume...\n");
        while ((err = snd_pcm_resume(pcm)) == -EAGAIN)
            hal_usleep(1000);
        if (err < 0) {
            err = snd_pcm_prepare(pcm);
            awalsa_err("cannot recovery from suspend, prepare return: %d", err);
            return err;
        }
        return 0;
    }
    return err;
}

int snd_pcm_delay(snd_pcm_t *pcm, snd_pcm_sframes_t *delayp)
{
    int ret = 0;

    assert(pcm);
    assert(delayp);

    snd_pcm_lock(pcm);
    ret = pcm->fast_ops->delay(pcm->fast_op_arg, delayp);
    snd_pcm_unlock(pcm);

    return ret;
}

int snd_pcm_dump_hw_setup(snd_pcm_t *pcm)
{
    assert(pcm);
    if (!pcm->setup) {
        awalsa_err("PCM not set up\n");
        return -EIO;
    }
    printf("  stream          : %s\n", snd_pcm_stream_name(pcm->stream));
    printf("  access          : %s\n", snd_pcm_access_name(pcm->access));
    printf("  format          : %s\n", snd_pcm_format_name(pcm->format));
    printf("  channels        : %u\n", pcm->channels);
    printf("  rate            : %u\n", pcm->rate);
    printf("  buffer_size     : %lu\n", pcm->buffer_size);
    printf("  period_size     : %lu\n", pcm->period_size);
    printf("  period_time     : %u\n", pcm->period_time);
    return 0;
}

int snd_pcm_dump_sw_setup(snd_pcm_t *pcm)
{
    assert(pcm);
    if (!pcm->setup) {
        awalsa_err("PCM not set up\n");
        return -EIO;
    }
    printf("  avail_min       : %lu\n", pcm->avail_min);
    printf("  start_threshold : %lu\n", pcm->start_threshold);
    printf("  stop_threshold  : %lu\n", pcm->stop_threshold);
    printf("  silence_size    : %lu\n", pcm->silence_size);
    printf("  boundary        : %lu\n", pcm->boundary);
    return 0;
}

int snd_pcm_dump_setup(snd_pcm_t *pcm)
{
    snd_pcm_dump_hw_setup(pcm);
    snd_pcm_dump_sw_setup(pcm);
    return 0;
}

int snd_pcm_dump(snd_pcm_t *pcm)
{
    assert(pcm);
    if (pcm->ops->dump)
        pcm->ops->dump(pcm->op_arg);
    else
        printf("pcm:%s not support dump.\n", pcm->name);
    return 0;
}

static void dump_one_param(snd_pcm_hw_params_t *params, unsigned int k)
{
    printf("%s: ", snd_pcm_hw_param_name(k));
    snd_pcm_hw_param_dump(params, k);
    printf("\n");
}

int snd_pcm_hw_params_dump(snd_pcm_hw_params_t *params)
{
    unsigned int k;
    for (k = SND_PCM_HW_PARAM_FIRST_INTERVAL; k <= SND_PCM_HW_PARAM_LAST_INTERVAL; k++)
        dump_one_param(params, k);
    return 0;
}

ssize_t snd_pcm_format_size(snd_pcm_format_t format, size_t samples)
{
    int size = 0;
    size = snd_pcm_format_physical_width(format);
    if (size < 0)
        return size;
    return (size * samples / 8);
}

snd_pcm_sframes_t snd_pcm_bytes_to_frames(snd_pcm_t *pcm, ssize_t bytes)
{
    assert(pcm);
    return bytes * 8 / pcm->frame_bits;
}

ssize_t snd_pcm_frames_to_bytes(snd_pcm_t *pcm, snd_pcm_sframes_t frames)
{
    assert(pcm);
    return frames * pcm->frame_bits / 8;
}

int snd_pcm_hw_params_can_pause(const snd_pcm_hw_params_t *params)
{
    assert(params);

    return !!params->can_paused;
}


#define PCMTYPE(v) [SND_PCM_TYPE_##v] = #v
#define STATE(v) [SND_PCM_STATE_##v] = #v
#define STREAM(v) [SND_PCM_STREAM_##v] = #v
#define ACCESS(v) [SND_PCM_ACCESS_##v] = #v
#define FORMAT(v) [SND_PCM_FORMAT_##v] = #v

static const char *const snd_pcm_stream_names[] = {
    STREAM(PLAYBACK),
    STREAM(CAPTURE),
};

static const char *const snd_pcm_state_names[] = {
    STATE(OPEN),
    STATE(SETUP),
    STATE(PREPARED),
    STATE(RUNNING),
    STATE(XRUN),
    STATE(DRAINING),
    STATE(PAUSED),
    STATE(SUSPENDED),
    STATE(DISCONNECTED),
};

static const char *const snd_pcm_access_names[] = {
    ACCESS(MMAP_INTERLEAVED),
    ACCESS(MMAP_NONINTERLEAVED),
    ACCESS(MMAP_COMPLEX),
    ACCESS(RW_INTERLEAVED),
    ACCESS(RW_NONINTERLEAVED),
};

static const char *const snd_pcm_format_names[] = {
    FORMAT(S8),
    FORMAT(U8),
    FORMAT(S16_LE),
    FORMAT(S16_BE),
    FORMAT(U16_LE),
    FORMAT(U16_BE),
    FORMAT(S24_LE),
    FORMAT(S24_BE),
    FORMAT(U24_LE),
    FORMAT(U24_BE),
    FORMAT(S32_LE),
    FORMAT(S32_BE),
    FORMAT(U32_LE),
    FORMAT(U32_BE),
};

static const char *const snd_pcm_type_names[] = {
    PCMTYPE(HW),
    PCMTYPE(MULTI),
    PCMTYPE(LINEAR),
    PCMTYPE(FILE),
    PCMTYPE(RATE),
    PCMTYPE(ROUTE),
    PCMTYPE(PLUG),
    PCMTYPE(DMIX),
    PCMTYPE(DSNOOP),
    PCMTYPE(SOFTVOL),
    PCMTYPE(EXTPLUG),
};

const char *snd_pcm_stream_name(snd_pcm_stream_t stream)
{
    if (stream > SND_PCM_STREAM_LAST)
        return NULL;
    return snd_pcm_stream_names[stream];
}

const char *snd_pcm_access_name(snd_pcm_access_t acc)
{
    if (acc > SND_PCM_ACCESS_LAST)
        return NULL;
    return snd_pcm_access_names[acc];
}

const char *snd_pcm_format_name(snd_pcm_format_t format)
{
    if (format > SND_PCM_FORMAT_LAST)
        return NULL;
    return snd_pcm_format_names[format];
}

const char *snd_pcm_state_name(snd_pcm_state_t state)
{
    if (state > SND_PCM_STATE_LAST)
        return NULL;
    return snd_pcm_state_names[state];
}

const char *snd_pcm_type_name(snd_pcm_type_t type)
{
    if (type > SND_PCM_TYPE_LAST)
        return NULL;
    return snd_pcm_type_names[type];
}

int snd_pcm_new(snd_pcm_t **pcmp, snd_pcm_type_t type, const char *name, snd_pcm_stream_t stream, int mode)
{
    snd_pcm_t *pcm;

    pcm = snd_malloc(sizeof(snd_pcm_t));
    if (!pcm)
        return -ENOMEM;
    pcm->type = type;
    if (name)
        pcm->name = strdup(name);
    pcm->stream = stream;
    pcm->mode = mode;
    pcm->op_arg = pcm;
    pcm->fast_op_arg = pcm;

    pthread_mutex_init(&pcm->lock, NULL);

    *pcmp = pcm;
    return 0;
}

int snd_pcm_free(snd_pcm_t *pcm)
{
    assert(pcm);
    if (pcm->name)
        free(pcm->name);
    if (pcm->hw.link_dst)
        free(pcm->hw.link_dst);
    if (pcm->appl.link_dst)
        free(pcm->appl.link_dst);
    pthread_mutex_destroy(&pcm->lock);
    snd_free(pcm);
    return 0;
}

void snd_pcm_areas_from_buf(snd_pcm_t *pcm, snd_pcm_channel_area_t *areas, void *buf)
{
    unsigned int channel;
    unsigned int channels;

    snd_pcm_lock(pcm);
    channels = pcm->channels;
    for (channel = 0; channel < channels; ++channel, ++areas) {
        areas->addr = buf;
        areas->first = channel * pcm->sample_bits;
        areas->step = pcm->frame_bits;
    }
    snd_pcm_unlock(pcm);
}

void snd_pcm_areas_from_bufs(snd_pcm_t *pcm, snd_pcm_channel_area_t *areas, void **bufs)
{
    unsigned int channel;
    unsigned int channels;

    snd_pcm_lock(pcm);
    channels = pcm->channels;
    for (channel = 0; channel < channels; ++channel, ++areas, ++bufs) {
        areas->addr = *bufs;
        areas->first = 0;
        areas->step = pcm->sample_bits;
    }
    snd_pcm_unlock(pcm);
}

snd_pcm_sframes_t snd_pcm_read_areas(snd_pcm_t *pcm, const snd_pcm_channel_area_t *areas,
                     snd_pcm_uframes_t offset, snd_pcm_uframes_t size,
                     snd_pcm_xfer_areas_func_t func)
{
    snd_pcm_uframes_t xfer = 0;
    snd_pcm_sframes_t err = 0;
    snd_pcm_state_t state;

    if (size == 0)
        return 0;

    snd_pcm_lock(pcm); /* forced lock */
    while (size > 0) {
        snd_pcm_uframes_t frames;
        snd_pcm_sframes_t avail;
    _again:
        state = __snd_pcm_state(pcm);
        switch (state) {
        case SND_PCM_STATE_PREPARED:
            err = __snd_pcm_start(pcm);
            if (err < 0)
                goto _end;
            break;
        case SND_PCM_STATE_RUNNING:
            err = __snd_pcm_hwsync(pcm);
            if (err < 0)
                goto _end;
            break;
        case SND_PCM_STATE_DRAINING:
        case SND_PCM_STATE_PAUSED:
            break;
        case SND_PCM_STATE_XRUN:
            err = -EPIPE;
            goto _end;
        case SND_PCM_STATE_SUSPENDED:
            err = -ESTRPIPE;
            goto _end;
        case SND_PCM_STATE_DISCONNECTED:
            err = -ENODEV;
            goto _end;
        default:
            err = -EBADFD;
            goto _end;
        }
        avail = __snd_pcm_avail_update(pcm);
        if (avail < 0) {
            err = avail;
            goto _end;
        }
        if (avail == 0) {
            if (state == SND_PCM_STATE_DRAINING)
                goto _end;
#if 0
            if (pcm->mode & SND_PCM_NONBLOCK) {
                err = -EAGAIN;
                goto _end;
            }
#endif
            err = __snd_pcm_wait_in_lock(pcm, -1);
            if (err < 0)
                break;
            goto _again;
        }
        frames = size;
        if (frames > (snd_pcm_uframes_t) avail)
            frames = avail;
        if (! frames)
            break;
        err = func(pcm, areas, offset, frames);
        if (err < 0)
            break;
        frames = err;
        offset += frames;
        size -= frames;
        xfer += frames;
    }
 _end:
    snd_pcm_unlock(pcm);
    return xfer > 0 ? (snd_pcm_sframes_t) xfer : snd_pcm_check_error(pcm, err);
}

snd_pcm_sframes_t snd_pcm_write_areas(snd_pcm_t *pcm, const snd_pcm_channel_area_t *areas,
                      snd_pcm_uframes_t offset, snd_pcm_uframes_t size,
                      snd_pcm_xfer_areas_func_t func)
{
    snd_pcm_uframes_t xfer = 0;
    snd_pcm_sframes_t err = 0;
    snd_pcm_state_t state;

    if (size == 0)
        return 0;

    awalsa_debug("\n");
    snd_pcm_lock(pcm); /* forced lock */
    while (size > 0) {
        snd_pcm_uframes_t frames;
        snd_pcm_sframes_t avail;
    _again:
        state = __snd_pcm_state(pcm);
        switch (state) {
        case SND_PCM_STATE_PREPARED:
        case SND_PCM_STATE_PAUSED:
            break;
        case SND_PCM_STATE_RUNNING:
            err = __snd_pcm_hwsync(pcm);
            if (err < 0)
                goto _end;
            break;
        case SND_PCM_STATE_XRUN:
            err = -EPIPE;
            goto _end;
        case SND_PCM_STATE_SUSPENDED:
            err = -ESTRPIPE;
            goto _end;
        case SND_PCM_STATE_DISCONNECTED:
            err = -ENODEV;
            goto _end;
        default:
            err = -EBADFD;
            goto _end;
        }
        avail = __snd_pcm_avail_update(pcm);
        awalsa_debug("size:%ld, avail: %ld, pcm_type=%s, state=%d\n",
            size, avail, snd_pcm_type_name(snd_pcm_type(pcm)), state);
        if (avail < 0) {
            err = avail;
            goto _end;
        }

        /* wait to get avail_min */
#if 1
        if ((state == SND_PCM_STATE_RUNNING &&
                    size > (snd_pcm_uframes_t)avail &&
                    snd_pcm_may_wait_for_avail_min(pcm, avail))) {
            err = snd_pcm_wait_nocheck(pcm, -1);
            if (err < 0)
                break;
            goto _again;
        }
#endif

        frames = size;
        if (frames > (snd_pcm_uframes_t) avail)
            frames = avail;
        if (! frames) {
            awalsa_info("avail=%ld, size=%ld, start=%ld, stop=%ld, xfer=%lu\n",
                avail, size, pcm->start_threshold, pcm->stop_threshold, xfer);
#if 0
            break;
#else
            /* avail is 0 in some case, don't break and return,
             * Now msleep and continue, in order to wait dma consume data,
             * and then avail is larger than 0.
             * */
            usleep(3000);
            continue;
#endif
        }
        err = func(pcm, areas, offset, frames);
        if (err < 0)
            break;
        frames = err;
        if (state == SND_PCM_STATE_PREPARED) {
            snd_pcm_sframes_t hw_avail = pcm->buffer_size - avail;
            hw_avail += frames;
            /* some plugins might automatically start the stream */
            awalsa_debug("hw_avail=%d, start_threshold=%d\n",
                    hw_avail, pcm->start_threshold);
            state = __snd_pcm_state(pcm);
            if (state == SND_PCM_STATE_PREPARED &&
                    hw_avail >= (snd_pcm_sframes_t) pcm->start_threshold) {
                err = __snd_pcm_start(pcm);
                if (err < 0)
                    goto _end;
            }
        }
        offset += frames;
        size -= frames;
        xfer += frames;
    }
 _end:
    snd_pcm_unlock(pcm);
    return xfer > 0 ? (snd_pcm_sframes_t) xfer : snd_pcm_check_error(pcm, err);
}

u_int64_t snd_pcm_format_silence_64(snd_pcm_format_t format)
{
    switch (format) {
    case SND_PCM_FORMAT_S8:
    case SND_PCM_FORMAT_S16_LE:
    case SND_PCM_FORMAT_S16_BE:
    case SND_PCM_FORMAT_S24_LE:
    case SND_PCM_FORMAT_S24_BE:
    case SND_PCM_FORMAT_S32_LE:
    case SND_PCM_FORMAT_S32_BE:
        return 0;
    case SND_PCM_FORMAT_U8:
        return 0x8080808080808080ULL;
    case SND_PCM_FORMAT_U16_LE:
        return 0x8000800080008000ULL;
    case SND_PCM_FORMAT_U24_LE:
        return 0x0080000000800000ULL;
    case SND_PCM_FORMAT_U32_LE:
        return 0x8000000080000000ULL;
    case SND_PCM_FORMAT_U16_BE:
        return 0x0080008000800080ULL;
    case SND_PCM_FORMAT_U24_BE:
        return 0x0000800000008000ULL;
    case SND_PCM_FORMAT_U32_BE:
        return 0x0000008000000080ULL;
    default:
        assert(0);
        return 0;
    }
    return 0;
}

int snd_pcm_area_silence(const snd_pcm_channel_area_t *dst_area, snd_pcm_uframes_t dst_offset,
             unsigned int samples, snd_pcm_format_t format)
{
    /* FIXME: sub byte resolution and odd dst_offset */
    char *dst;
    unsigned int dst_step;
    int width;
    u_int64_t silence;
    if (!dst_area->addr)
        return 0;
    dst = snd_pcm_channel_area_addr(dst_area, dst_offset);
    width = snd_pcm_format_physical_width(format);
    silence = snd_pcm_format_silence_64(format);
#if 0
    /* dst may not be 8bytes align, so can't clear with strdne (64bit operation) */
    if (dst_area->step == (unsigned int) width) {
        unsigned int dwords = samples * width / 64;
        u_int64_t *dstp = (u_int64_t *)dst;
        samples -= dwords * 64 / width;
        while (dwords-- > 0)
            *dstp++ = silence;
        if (samples == 0)
            return 0;
        dst = (char *)dstp;
    }
#endif
    dst_step = dst_area->step / 8;
    switch (width) {
    case 4: {
        u_int8_t s0 = silence & 0xf0;
        u_int8_t s1 = silence & 0x0f;
        int dstbit = dst_area->first % 8;
        int dstbit_step = dst_area->step % 8;
        while (samples-- > 0) {
            if (dstbit) {
                *dst &= 0xf0;
                *dst |= s1;
            } else {
                *dst &= 0x0f;
                *dst |= s0;
            }
            dst += dst_step;
            dstbit += dstbit_step;
            if (dstbit == 8) {
                dst++;
                dstbit = 0;
            }
        }
        break;
    }
    case 8: {
        u_int8_t sil = silence;
        while (samples-- > 0) {
            *dst = sil;
            dst += dst_step;
        }
        break;
    }
    case 16: {
        u_int16_t sil = silence;
        while (samples-- > 0) {
            *(u_int16_t*)dst = sil;
            dst += dst_step;
        }
        break;
    }
    case 24:
        *(dst + 0) = silence >> 0;
        *(dst + 1) = silence >> 8;
        *(dst + 2) = silence >> 16;
        break;
    case 32: {
        u_int32_t sil = silence;
        while (samples-- > 0) {
            *(u_int32_t*)dst = sil;
            dst += dst_step;
        }
        break;
    }
    case 64: {
        while (samples-- > 0) {
            *(u_int64_t*)dst = silence;
            dst += dst_step;
        }
        break;
    }
    default:
        awalsa_err("invalid format width %d", width);
        return -EINVAL;
    }
    return 0;
}

int snd_pcm_areas_silence(const snd_pcm_channel_area_t *dst_areas, snd_pcm_uframes_t dst_offset,
              unsigned int channels, snd_pcm_uframes_t frames, snd_pcm_format_t format)
{
    int width = snd_pcm_format_physical_width(format);
    while (channels > 0) {
        void *addr = dst_areas->addr;
        unsigned int step = dst_areas->step;
        const snd_pcm_channel_area_t *begin = dst_areas;
        int channels1 = channels;
        unsigned int chns = 0;
        int err;
        while (1) {
            channels1--;
            chns++;
            dst_areas++;
            if (channels1 == 0 ||
                dst_areas->addr != addr ||
                dst_areas->step != step ||
                dst_areas->first != dst_areas[-1].first + width)
                break;
        }
        if (chns > 1 && chns * width == step) {
            /* Collapse the areas */
            snd_pcm_channel_area_t d;
            d.addr = begin->addr;
            d.first = begin->first;
            d.step = width;
            err = snd_pcm_area_silence(&d, dst_offset * chns, frames * chns, format);
            channels -= chns;
        } else {
            err = snd_pcm_area_silence(begin, dst_offset, frames, format);
            dst_areas = begin + 1;
            channels--;
        }
        if (err < 0)
            return err;
    }
    return 0;
}

int snd_pcm_area_copy(const snd_pcm_channel_area_t *dst_area, snd_pcm_uframes_t dst_offset,
              const snd_pcm_channel_area_t *src_area, snd_pcm_uframes_t src_offset,
              unsigned int samples, snd_pcm_format_t format)
{
    /* FIXME: sub byte resolution and odd dst_offset */
    const char *src;
    char *dst;
    int width;
    int src_step, dst_step;
    if (dst_area == src_area && dst_offset == src_offset)
        return 0;
    if (!src_area->addr)
        return snd_pcm_area_silence(dst_area, dst_offset, samples, format);
    src = snd_pcm_channel_area_addr(src_area, src_offset);
    if (!dst_area->addr)
        return 0;
    dst = snd_pcm_channel_area_addr(dst_area, dst_offset);
    width = snd_pcm_format_physical_width(format);
    if (src_area->step == (unsigned int) width &&
        dst_area->step == (unsigned int) width) {
        size_t bytes = samples * width / 8;
        samples -= bytes * 8 / width;
        assert(src < dst || src >= dst + bytes);
        assert(dst < src || dst >= src + bytes);
        memcpy(dst, src, bytes);
        if (samples == 0)
            return 0;
    }
    src_step = src_area->step / 8;
    dst_step = dst_area->step / 8;
    switch (width) {
    case 4: {
        int srcbit = src_area->first % 8;
        int srcbit_step = src_area->step % 8;
        int dstbit = dst_area->first % 8;
        int dstbit_step = dst_area->step % 8;
        while (samples-- > 0) {
            unsigned char srcval;
            if (srcbit)
                srcval = *src & 0x0f;
            else
                srcval = *src & 0xf0;
            if (dstbit)
                *dst &= 0xf0;
            else
                *dst &= 0x0f;
            *dst |= srcval;
            src += src_step;
            srcbit += srcbit_step;
            if (srcbit == 8) {
                src++;
                srcbit = 0;
            }
            dst += dst_step;
            dstbit += dstbit_step;
            if (dstbit == 8) {
                dst++;
                dstbit = 0;
            }
        }
        break;
    }
    case 8: {
        while (samples-- > 0) {
            *dst = *src;
            src += src_step;
            dst += dst_step;
        }
        break;
    }
    case 16: {
        while (samples-- > 0) {
            *(u_int16_t*)dst = *(const u_int16_t*)src;
            src += src_step;
            dst += dst_step;
        }
        break;
    }
    case 24:
        while (samples-- > 0) {
            *(dst + 0) = *(src + 0);
            *(dst + 1) = *(src + 1);
            *(dst + 2) = *(src + 2);
            src += src_step;
            dst += dst_step;
        }
        break;
    case 32: {
        while (samples-- > 0) {
            *(u_int32_t*)dst = *(const u_int32_t*)src;
            src += src_step;
            dst += dst_step;
        }
        break;
    }
    case 64: {
        while (samples-- > 0) {
            *(u_int64_t*)dst = *(const u_int64_t*)src;
            src += src_step;
            dst += dst_step;
        }
        break;
    }
    default:
        awalsa_err("invalid format width %d", width);
        return -EINVAL;
    }
    return 0;
}

int snd_pcm_areas_copy(const snd_pcm_channel_area_t *dst_areas, snd_pcm_uframes_t dst_offset,
               const snd_pcm_channel_area_t *src_areas, snd_pcm_uframes_t src_offset,
               unsigned int channels, snd_pcm_uframes_t frames, snd_pcm_format_t format)
{
    int width = snd_pcm_format_physical_width(format);
    assert(dst_areas);
    assert(src_areas);
    if (! channels) {
        awalsa_err("invalid channels %d\n", channels);
        return -EINVAL;
    }
    if (! frames) {
        awalsa_err("invalid frames %ld\n", frames);
        return -EINVAL;
    }
    while (channels > 0) {
        unsigned int step = src_areas->step;
        void *src_addr = src_areas->addr;
        const snd_pcm_channel_area_t *src_start = src_areas;
        void *dst_addr = dst_areas->addr;
        const snd_pcm_channel_area_t *dst_start = dst_areas;
        int channels1 = channels;
        unsigned int chns = 0;
        while (dst_areas->step == step) {
            channels1--;
            chns++;
            src_areas++;
            dst_areas++;
            if (channels1 == 0 ||
                src_areas->step != step ||
                src_areas->addr != src_addr ||
                dst_areas->addr != dst_addr ||
                src_areas->first != src_areas[-1].first + width ||
                dst_areas->first != dst_areas[-1].first + width)
                break;
        }
        if (chns > 1 && chns * width == step) {
            if (src_offset != dst_offset ||
                src_start->addr != dst_start->addr ||
                src_start->first != dst_start->first) {
                /* Collapse the areas */
                snd_pcm_channel_area_t s, d;
                s.addr = src_start->addr;
                s.first = src_start->first;
                s.step = width;
                d.addr = dst_start->addr;
                d.first = dst_start->first;
                d.step = width;
                snd_pcm_area_copy(&d, dst_offset * chns,
                        &s, src_offset * chns,
                        frames * chns, format);
            }
            channels -= chns;
        } else {
            snd_pcm_area_copy(dst_start, dst_offset,
                    src_start, src_offset,
                    frames, format);
            src_areas = src_start + 1;
            dst_areas = dst_start + 1;
            channels--;
        }
    }
    return 0;
}

/* This function is called inside pcm lock. */
int snd_pcm_wait_nocheck(snd_pcm_t *pcm, int timeout)
{
    assert(pcm);
    if (pcm->fast_ops->wait)
        return pcm->fast_ops->wait(pcm->fast_op_arg, timeout);
    else
        awalsa_err("pcm_type=%s, no wait\n", snd_pcm_type_name(snd_pcm_type(pcm)));
    return 0;
}

int __snd_pcm_wait_in_lock(snd_pcm_t *pcm, int timeout)
{
#if 1
    awalsa_debug("\n");
    if (!snd_pcm_may_wait_for_avail_min(pcm, snd_pcm_mmap_avail(pcm))) {
        /* check more precisely */
        switch (__snd_pcm_state(pcm)) {
        case SND_PCM_STATE_XRUN:
            return -EPIPE;
        case SND_PCM_STATE_SUSPENDED:
            return -ESTRPIPE;
        case SND_PCM_STATE_DISCONNECTED:
            return -ENODEV;
        default:
            return 1;
        }
    }
    return snd_pcm_wait_nocheck(pcm, timeout);
#else
    switch (__snd_pcm_state(pcm)) {
    case SND_PCM_STATE_XRUN:
        return -EPIPE;
    case SND_PCM_STATE_SUSPENDED:
        return -ESTRPIPE;
    case SND_PCM_STATE_DISCONNECTED:
        return -ENODEV;
    default:
        return 1;
    }
#endif
}

int snd_pcm_wait(snd_pcm_t *pcm, int timeout)
{
    int err;
    awalsa_debug("\n");

    snd_pcm_lock(pcm); /* forced lock */
    err = __snd_pcm_wait_in_lock(pcm, timeout);
    snd_pcm_unlock(pcm);
    return err;
}

snd_pcm_sframes_t snd_pcm_avail_update(snd_pcm_t *pcm)
{
    snd_pcm_sframes_t result;
    awalsa_debug("\n");

    snd_pcm_lock(pcm);
    result = __snd_pcm_avail_update(pcm);
    snd_pcm_unlock(pcm);
    return result;
}

int __snd_pcm_mmap_begin(snd_pcm_t *pcm, const snd_pcm_channel_area_t **areas,
               snd_pcm_uframes_t *offset, snd_pcm_uframes_t *frames)
{
    snd_pcm_uframes_t cont;
    snd_pcm_uframes_t f;
    snd_pcm_uframes_t avail;
    const snd_pcm_channel_area_t *xareas;
    assert(pcm && areas && offset && frames);

    awalsa_debug("\n");

    xareas = snd_pcm_mmap_areas(pcm);
    if (xareas == NULL)
        return -EBADFD;
    *areas = xareas;
    *offset = *pcm->appl.ptr % pcm->buffer_size;
    avail = snd_pcm_mmap_avail(pcm);
    if (avail > pcm->buffer_size)
        avail = pcm->buffer_size;
    cont = pcm->buffer_size - *offset;
    f = *frames;
    if (f > avail)
        f = avail;
    if (f > cont)
        f = cont;
    *frames = f;
    return 0;
}

int snd_pcm_mmap_begin(snd_pcm_t *pcm,
               const snd_pcm_channel_area_t **areas,
               snd_pcm_uframes_t *offset,
               snd_pcm_uframes_t *frames)
{
    int err;
    awalsa_debug("\n");

    snd_pcm_lock(pcm);
    err = __snd_pcm_mmap_begin(pcm, areas, offset, frames);
    snd_pcm_unlock(pcm);
    return err;
}

snd_pcm_sframes_t __snd_pcm_mmap_commit(snd_pcm_t *pcm,
                    snd_pcm_uframes_t offset,
                    snd_pcm_uframes_t frames)
{
    assert(pcm);
    awalsa_debug("\n");

    if (offset != *pcm->appl.ptr % pcm->buffer_size) {
        awalsa_err("commit offset (%ld) doesn't match with appl_ptr (%ld) %% buf_size (%ld)\n",
               offset, *pcm->appl.ptr, pcm->buffer_size);
        return -EPIPE;
    }
    if (frames > snd_pcm_mmap_avail(pcm)) {
        awalsa_err("commit frames (%ld) overflow (avail = %ld)\n", frames,
               snd_pcm_mmap_avail(pcm));
        return -EPIPE;
    }
    return pcm->fast_ops->mmap_commit(pcm->fast_op_arg, offset, frames);
}

snd_pcm_sframes_t snd_pcm_mmap_commit(snd_pcm_t *pcm,
                      snd_pcm_uframes_t offset,
                      snd_pcm_uframes_t frames)
{
    snd_pcm_sframes_t result;
    awalsa_debug("\n");

    snd_pcm_lock(pcm);
    result = __snd_pcm_mmap_commit(pcm, offset, frames);
    snd_pcm_unlock(pcm);
    return result;
}

snd_pcm_type_t snd_pcm_type(snd_pcm_t *pcm)
{
    assert(pcm);
    return pcm->type;
}


static int chmap_equal(const snd_pcm_chmap_t *a, const snd_pcm_chmap_t *b)
{
    if (a->channels != b->channels)
        return 0;
    return !memcmp(a->pos, b->pos, a->channels * sizeof(a->pos[0]));
}

/**
 * \!brief Query the available channel maps
 * \param pcm PCM handle to query
 * \return the NULL-terminated array of integer pointers, each of
 * which contains the channel map. A channel map is represented by an
 * integer array, beginning with the channel map type, followed by the
 * number of channels, and the position of each channel.
 *
 * Note: the caller is requested to release the returned value via
 * snd_pcm_free_chmaps().
 */
snd_pcm_chmap_query_t **snd_pcm_query_chmaps(snd_pcm_t *pcm)
{
    if (!pcm->ops->query_chmaps)
        return NULL;
    return pcm->ops->query_chmaps(pcm);
}

/**
 * \!brief Release the channel map array allocated via #snd_pcm_query_chmaps
 * \param maps the array pointer to release
 */
void snd_pcm_free_chmaps(snd_pcm_chmap_query_t **maps)
{
    snd_pcm_chmap_query_t **p;
    if (!maps)
        return;
    for (p = maps; *p; p++)
        free(*p);
    free(maps);
}

/**
 * \!brief Get the current channel map
 * \param pcm PCM instance
 * \return the current channel map, or NULL if error
 *
 * Note: the caller is requested to release the returned value via free()
 */
snd_pcm_chmap_t *snd_pcm_get_chmap(snd_pcm_t *pcm)
{
    if (!pcm->ops->get_chmap)
        return NULL;
    return pcm->ops->get_chmap(pcm);
}

/**
 * \!brief Configure the current channel map
 * \param pcm PCM instance
 * \param map the channel map to write
 * \return zero if succeeded, or a negative error code
 */
int snd_pcm_set_chmap(snd_pcm_t *pcm, const snd_pcm_chmap_t *map)
{
    const snd_pcm_chmap_t *oldmap = snd_pcm_get_chmap(pcm);
    if (oldmap && chmap_equal(oldmap, map))
        return 0;

    if (!pcm->ops->set_chmap)
        return -ENXIO;
    return pcm->ops->set_chmap(pcm, map);
}

/* copy a single channel map with the fixed type to chmap_query pointer */
static int _copy_to_fixed_query_map(snd_pcm_chmap_query_t **dst,
                    const snd_pcm_chmap_t *src)
{
    *dst = malloc((src->channels + 2) * sizeof(int));
    if (!*dst)
        return -ENOMEM;
    (*dst)->type = SND_CHMAP_TYPE_FIXED;
    memcpy(&(*dst)->map, src, (src->channels + 1) * sizeof(int));
    return 0;
}

/* make a chmap_query array from a single channel map */
snd_pcm_chmap_query_t **_snd_pcm_make_single_query_chmaps(const snd_pcm_chmap_t *src)
{
    snd_pcm_chmap_query_t **maps;

    maps = calloc(2, sizeof(*maps));
    if (!maps)
        return NULL;
    if (_copy_to_fixed_query_map(maps, src)) {
        free(maps);
        return NULL;
    }
    return maps;
}

snd_pcm_sframes_t snd_pcm_rewind(snd_pcm_t *pcm, snd_pcm_uframes_t frames)
{
    snd_pcm_sframes_t result = 0;

    assert(pcm);
    if (! pcm->setup) {
        awalsa_err("PCM not set up");
        return -EIO;
    }
    if (frames == 0)
        return 0;
    //if (bad_pcm_state(pcm, P_STATE_RUNNABLE))
    //  return -EBADFD;
    snd_pcm_lock(pcm);
#if 0
    result = pcm->fast_ops->rewind(pcm->fast_op_arg, frames);
#else
    awalsa_err("rewind is not supported\n");
#endif
    snd_pcm_unlock(pcm);
    return result;
}

int snd_pcm_link(snd_pcm_t *pcm1, snd_pcm_t *pcm2)
{
    assert(pcm1);
    assert(pcm2);
    if (pcm1->fast_ops->link)
        return pcm1->fast_ops->link(pcm1, pcm2);
    return -ENOSYS;
}

int snd_pcm_unlink(snd_pcm_t *pcm)
{
    assert(pcm);
    if (pcm->fast_ops->unlink)
        return pcm->fast_ops->unlink(pcm);
    return -ENOSYS;
}

#ifdef AW_ALSA_LIB_API_TEST
#include "test/tt-aw-alsa-lib.c"
#endif
