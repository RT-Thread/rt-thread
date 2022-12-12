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
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sound/snd_core.h>
#include <sound/snd_pcm.h>
#include <sound/snd_io.h>
#include <sound/snd_misc.h>
#include <hal_osal.h>
#include <interrupt.h>
#include <hal_sem.h>
#include <hal_mem.h>
#include <hal_mutex.h>

static LIST_HEAD(gCardList);

snd_mutex_t snd_mutex_init(void)
{
    snd_mutex_t hal_mutex = NULL;

    hal_mutex = hal_mutex_create();
    if (hal_mutex == NULL) {
        snd_print("hal_mutex_create err.\n");
    }
    return hal_mutex;
}

int snd_mutex_lock_timeout(snd_mutex_t mutex, long ms)
{
    long ret;
    const uint32_t timeout = ms / (1000 / CONFIG_HZ);
    if (!mutex)
        return -1;
    snd_print("\n");
    ret = hal_mutex_timedwait(mutex, timeout);

    return ret;
}

int snd_mutex_lock(snd_mutex_t mutex)
{
    int ret;
    if (!mutex)
        return -1;
    snd_print("\n");
    ret = hal_mutex_timedwait(mutex, 100);

    return ret;
}

void snd_mutex_unlock(snd_mutex_t mutex)
{
    if (!mutex)
        return;
    snd_print("\n");
    hal_mutex_unlock(mutex);
}

void snd_mutex_destroy(snd_mutex_t mutex)
{
    if (!mutex)
        return;
    hal_mutex_delete(mutex);
}

snd_schd_t snd_schd_init(void)
{
    snd_schd_t schd;

    schd = snd_malloc(sizeof(*schd));
    if (!schd)
        return NULL;
    schd->waiting = 0;
    schd->sem = hal_sem_create(0);
    if (schd->sem == NULL) {
        snd_free(schd);
        snd_err("sem init err.\n");
        return NULL;
    }
    return schd;
}

int snd_schd_timeout(snd_schd_t schd, long ms)
{
    int ret;
    const uint32_t timeout = ms / (1000 / CONFIG_HZ);
    if (!schd)
        return -1;
    snd_print("\n");
    schd->waiting = 1;
    ret = hal_sem_timedwait(schd->sem, timeout);
    if (ret == 0)
        return 0;
    return -1;
}

void snd_schd_wakeup(snd_schd_t schd)
{
    int ret;
    /* may call with irq disabled, so use xSemaphoreGiveFromISR */
    if (!schd || !schd->waiting)
        return;
    snd_print("\n");
    ret = hal_sem_post(schd->sem);
    if (ret == 0) {
        return;
    }
}

void snd_schd_destroy(snd_schd_t schd)
{
    if (!schd)
        return;
    snd_print("\n");
    hal_sem_delete(schd->sem);
    snd_free(schd);
}

static void snd_pcm_stream_lock(struct snd_pcm_substream *substream)
{
    hal_spin_lock(&substream->lock);
}

static void snd_pcm_stream_unlock(struct snd_pcm_substream *substream)
{
    hal_spin_unlock(&substream->lock);
}

void snd_pcm_stream_lock_irq(struct snd_pcm_substream *substream)
{
    snd_lock_debug("\n");
    hal_local_irq_disable();
    snd_pcm_stream_lock(substream);
}

void snd_pcm_stream_unlock_irq(struct snd_pcm_substream *substream)
{
    snd_lock_debug("\n");
    snd_pcm_stream_unlock(substream);
    hal_local_irq_enable();
}

hal_irq_state_t _snd_pcm_stream_lock_irqsave(struct snd_pcm_substream *substream)
{
    hal_irq_state_t flags = 0;

    snd_lock_debug("\n");
    hal_local_irq_save(flags);
    snd_pcm_stream_lock(substream);
    return flags;
}

void snd_pcm_stream_unlock_irqrestore(struct snd_pcm_substream *substream,
                    unsigned long flags)
{
    snd_lock_debug("\n");
    snd_pcm_stream_unlock(substream);
    hal_local_irq_restore(flags);
}

void snd_set_runtime_hwparams(struct snd_pcm_substream *substream,
            const struct snd_pcm_hardware *hw)
{
    struct snd_pcm_runtime *runtime = substream->runtime;

    runtime->hw.info = hw->info;
    runtime->hw.formats = hw->formats;
    runtime->hw.period_bytes_min = hw->period_bytes_min;
    runtime->hw.period_bytes_max = hw->period_bytes_max;
    runtime->hw.periods_min = hw->periods_min;
    runtime->hw.periods_max = hw->periods_max;
    runtime->hw.buffer_bytes_max = hw->buffer_bytes_max;
    return;
}

static int soc_pcm_init_runtime_hw_constrains(struct snd_pcm_hardware *hw,
                struct snd_pcm_hw_constrains *cons)
{
    union snd_interval *interval_access = &cons->intervals[SND_PCM_HW_PARAM_ACCESS];
    if (hw->info & SNDRV_PCM_INFO_INTERLEAVED)
        interval_access->mask |= 1 << SND_PCM_ACCESS_RW_INTERLEAVED;
    if (hw->info & SNDRV_PCM_INFO_NONINTERLEAVED)
        interval_access->mask |= 1 << SND_PCM_ACCESS_RW_NONINTERLEAVED;
    if (hw->info & SNDRV_PCM_INFO_MMAP) {
        if (hw->info & SNDRV_PCM_INFO_INTERLEAVED)
            interval_access->mask |= 1 << SND_PCM_ACCESS_MMAP_INTERLEAVED;
        if (hw->info & SNDRV_PCM_INFO_NONINTERLEAVED)
            interval_access->mask |= 1 << SND_PCM_ACCESS_MMAP_NONINTERLEAVED;
    }

    cons->intervals[SND_PCM_HW_PARAM_FORMAT].mask = hw->formats;
    cons->intervals[SND_PCM_HW_PARAM_CHANNELS].range.min = hw->channels_min;
    cons->intervals[SND_PCM_HW_PARAM_CHANNELS].range.max = hw->channels_max;
    cons->intervals[SND_PCM_HW_PARAM_RATE].range.min = hw->rate_min;
    cons->intervals[SND_PCM_HW_PARAM_RATE].range.max = hw->rate_max;
    cons->intervals[SND_PCM_HW_PARAM_PERIOD_BYTES].range.min = hw->period_bytes_min;
    cons->intervals[SND_PCM_HW_PARAM_PERIOD_BYTES].range.max = hw->period_bytes_max;
    cons->intervals[SND_PCM_HW_PARAM_PERIODS].range.min = hw->periods_min;
    cons->intervals[SND_PCM_HW_PARAM_PERIODS].range.max = hw->periods_max;

    cons->intervals[SND_PCM_HW_PARAM_BUFFER_BYTES].range.max = hw->buffer_bytes_max;

    cons->intervals[SND_PCM_HW_PARAM_SAMPLE_BITS].range.min =
            (uint32_t)snd_pcm_format_physical_width(__pcm_ffs(hw->formats));
    cons->intervals[SND_PCM_HW_PARAM_SAMPLE_BITS].range.max =
            (uint32_t)snd_pcm_format_physical_width(__fls(hw->formats));

    return 0;
}

static int soc_pcm_init_runtime_hw(struct snd_pcm_substream *substream)
{
    struct snd_dai *cpu_dai, *codec_dai;
    struct snd_pcm_stream *cpu_stream, *codec_stream;
    struct snd_pcm_runtime *runtime = substream->runtime;
    struct snd_pcm_hardware *hw = &runtime->hw;
    unsigned int rates = (~0U);

    cpu_dai = substream->pcm->card->platform->cpu_dai;
    codec_dai = substream->pcm->card->codec->codec_dai;
    /* ignore multi codecs */
    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        cpu_stream = &cpu_dai->playback;
        codec_stream = &codec_dai->playback;
    } else {
        cpu_stream = &cpu_dai->capture;
        codec_stream = &codec_dai->capture;
    }

    hw->channels_min = max(cpu_stream->channels_min, codec_stream->channels_min);
    hw->channels_max = min(cpu_stream->channels_max, codec_stream->channels_max);
    hw->formats = cpu_stream->formats & codec_stream->formats;
    rates = snd_pcm_rate_mask_intersect(codec_stream->rates, rates);
    hw->rates = snd_pcm_rate_mask_intersect(rates, cpu_stream->rates);
    snd_pcm_limit_hw_rates(runtime);

    hw->rate_min = max(codec_stream->rate_min, cpu_stream->rate_min);
    hw->rate_max = min(codec_stream->rate_max, cpu_stream->rate_max);

    /* fill in hw constrains */
    soc_pcm_init_runtime_hw_constrains(hw, &runtime->hw_constrains);

    return 0;
}

static int soc_pcm_open(struct snd_pcm_substream *substream)
{
    int ret = 0;
    struct snd_dai *cpu_dai, *codec_dai;
    struct snd_platform *platform;

    snd_print("\n");
    platform = substream->pcm->card->platform;
    cpu_dai = platform->cpu_dai;
    codec_dai = substream->pcm->card->codec->codec_dai;
    /* TODO: pinctrl default state */

    /*snd_mutex_lock(runtime->pcm_mutex);*/
    if (cpu_dai->ops->startup) {
        ret = cpu_dai->ops->startup(substream, cpu_dai);
        if (ret < 0) {
            snd_err("cpu_dai startup failed\n");
            goto _end_lock;
        }
    }
    if (platform->ops->open) {
        ret = platform->ops->open(substream);
        if (ret < 0) {
            snd_err("platform open failed\n");
            goto _end_lock;
        }
    }
    if (codec_dai->ops->startup) {
        ret = codec_dai->ops->startup(substream, codec_dai);
        if (ret < 0) {
            snd_err("codec_dai startup failed\n");
            goto _end_lock;
        }
    }
    soc_pcm_init_runtime_hw(substream);

    snd_print("open %s stream\n", substream->stream == SNDRV_PCM_STREAM_PLAYBACK ?
                    "Playback" : "Capture");
_end_lock:
    /*snd_mutex_unlock(runtime->pcm_mutex);*/

    return ret;
}

static int soc_dai_set_sysclk(struct snd_dai *dai, int clk_id,
                unsigned int freq, int dir)
{
    if ((dai == NULL) || (dai->ops == NULL))
        return -EINVAL;
    if (dai->ops->set_sysclk)
        return dai->ops->set_sysclk(dai, clk_id, freq, dir);
    return 0;
}

static int soc_dai_set_pll(struct snd_dai *dai, int pll_id, int source,
                unsigned int freq_in, int freq_out)
{
    if ((dai == NULL) || (dai->ops == NULL))
        return -EINVAL;
    if (dai->ops->set_pll)
        return dai->ops->set_pll(dai, pll_id, source, freq_in, freq_out);
    return 0;
}

int snd_soc_dai_set_fmt(struct snd_dai *dai, unsigned int fmt)
{
    if ((dai == NULL) || (dai->ops == NULL))
        return -EINVAL;
    if (dai->ops->set_fmt)
        return dai->ops->set_fmt(dai, fmt);
    return 0;
}

static int soc_dai_set_clkdiv(struct snd_dai *dai, int div_id, int div)
{
    if ((dai == NULL) || (dai->ops == NULL))
        return -EINVAL;
    if (dai->ops->set_clkdiv)
        return dai->ops->set_clkdiv(dai, div_id, div);
    return 0;
}

static int soc_pcm_hw_params(struct snd_pcm_substream *substream,
                struct snd_pcm_hw_params *params)
{
    int ret;
    unsigned int freq, clk_div;
    struct snd_dai *codec_dai, *cpu_dai;
    struct snd_platform *platform;
    codec_dai = substream->pcm->card->codec->codec_dai;
    platform = substream->pcm->card->platform;
    cpu_dai = platform->cpu_dai;

    snd_print("\n");
    /*snd_mutex_lock(runtime->pcm_mutex);*/
    switch (params_rate(params)) {
    case 8000:
    case 12000:
    case 16000:
    case 24000:
    case 32000:
    case 48000:
    case 64000:
    case 96000:
    case 192000:
        freq = 24576000;
        break;
    case 11025:
    case 22050:
    case 44100:
    case 88200:
        freq = 22579200;
        break;
    default:
        snd_err("unsupport params rate:%d\n", params_rate(params));
        ret = -EINVAL;
        goto _end_lock;
    }

    ret = soc_dai_set_sysclk(cpu_dai, 0, freq, 0);
    if (ret < 0) {
        snd_err("cpu_dai set sysclk failed\n");
        goto _end_lock;
    }
    ret = soc_dai_set_sysclk(codec_dai, 0, freq, 0);
    if (ret < 0) {
        snd_err("codec_dai set sysclk failed\n");
        goto _end_lock;
    }
    ret = soc_dai_set_pll(cpu_dai, 0, 0, freq, freq);
    if (ret < 0) {
        snd_err("cpu_dai set pll failed\n");
        goto _end_lock;
    }
    ret = soc_dai_set_pll(codec_dai, 0, 0, freq, freq);
    if (ret < 0) {
        snd_err("codec_dai set pll failed\n");
        goto _end_lock;
    }
    clk_div = freq / params_rate(params);
    ret = soc_dai_set_clkdiv(cpu_dai, 0, clk_div);
    if (ret < 0) {
        snd_err("cpu_dai set clkdiv failed\n");
        goto _end_lock;
    }
    ret = soc_dai_set_clkdiv(codec_dai, 0, clk_div);
    if (ret < 0) {
        snd_err("codec_dai set clkdiv failed\n");
        goto _end_lock;
    }

    if (codec_dai->ops->hw_params) {
        ret = codec_dai->ops->hw_params(substream, params, codec_dai);
        if (ret < 0) {
            snd_err("codec_dai set hw params failed\n");
            goto _end_lock;
        }
    }
    if (cpu_dai->ops->hw_params) {
        ret = cpu_dai->ops->hw_params(substream, params, cpu_dai);
        if (ret < 0) {
            snd_err("cpu_dai set hw params failed\n");
            goto cpu_dai_err;
        }
    }
    if (platform->ops->hw_params) {
        ret = platform->ops->hw_params(substream, params);
        if (ret < 0) {
            snd_err("platform set hw params failed\n");
            goto platform_err;
        }
    }

    return ret;

platform_err:
    if (cpu_dai->ops->hw_free)
        cpu_dai->ops->hw_free(substream, cpu_dai);
cpu_dai_err:
    if (codec_dai->ops->hw_free)
        codec_dai->ops->hw_free(substream, codec_dai);
_end_lock:
    /*snd_mutex_unlock(runtime->pcm_mutex);*/

    return ret;
}

static int soc_pcm_prepare(struct snd_pcm_substream *substream)
{
    int ret = 0;
    struct snd_dai *codec_dai, *cpu_dai;
    struct snd_platform *platform;

    snd_print("\n");
    /*snd_mutex_lock(runtime->pcm_mutex);*/
    platform = substream->pcm->card->platform;
    codec_dai = substream->pcm->card->codec->codec_dai;
    cpu_dai = platform->cpu_dai;

    if (platform->ops->prepare) {
        ret = platform->ops->prepare(substream);
        if (ret < 0) {
            snd_err("platform prepare failed\n");
            goto _end_lock;
        }
    }

    if (codec_dai->ops->prepare) {
        ret = codec_dai->ops->prepare(substream, codec_dai);
        if (ret < 0) {
            snd_err("codec_dai prepare failed\n");
            goto _end_lock;
        }
    }
    if (cpu_dai->ops->prepare) {
        ret = cpu_dai->ops->prepare(substream, cpu_dai);
        if (ret < 0) {
            snd_err("cpu_dai prepare failed\n");
            goto _end_lock;
        }
    }

    if (codec_dai->ops->dapm_control) {
        ret = codec_dai->ops->dapm_control(substream, codec_dai, 1);
        if (ret < 0) {
            snd_err("codec_dai dapm_control failed\n");
            goto _end_lock;
        }
    }

_end_lock:
    /*snd_mutex_unlock(runtime->pcm_mutex);*/
    return ret;
}

static int soc_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
    int ret = 0;
    struct snd_dai *codec_dai, *cpu_dai;
    struct snd_platform *platform;

    snd_print("\n");
    platform = substream->pcm->card->platform;
    codec_dai = substream->pcm->card->codec->codec_dai;
    cpu_dai = platform->cpu_dai;

    if (codec_dai->ops->trigger) {
        ret = codec_dai->ops->trigger(substream, cmd, codec_dai);
        if (ret < 0) {
            snd_err("codec_dai trigger failed\n");
            return ret;
        }
    }

    if (platform->ops->trigger) {
        ret = platform->ops->trigger(substream, cmd);
        if (ret < 0) {
            snd_err("platform trigger failed\n");
            return ret;
        }
    }

    if (cpu_dai->ops->trigger) {
        ret = cpu_dai->ops->trigger(substream, cmd, cpu_dai);
        if (ret < 0) {
            snd_err("cpu_dai trigger failed\n");
            return ret;
        }
    }
    return ret;
}

static int soc_pcm_hw_free(struct snd_pcm_substream *substream)
{
    int ret = 0;
    struct snd_dai *codec_dai, *cpu_dai;
    struct snd_platform *platform;

    snd_print("\n");
    platform = substream->pcm->card->platform;
    codec_dai = substream->pcm->card->codec->codec_dai;
    cpu_dai = platform->cpu_dai;

    if (platform->ops->hw_free) {
        ret = platform->ops->hw_free(substream);
        if (ret < 0) {
            snd_err("platform hw free failed\n");
            return ret;
        }
    }

    if (codec_dai->ops->hw_free) {
        ret = codec_dai->ops->hw_free(substream, codec_dai);
        if (ret < 0) {
            snd_err("codec_dai hw free failed\n");
            return ret;
        }
    }
    if (cpu_dai->ops->hw_free) {
        ret = cpu_dai->ops->hw_free(substream, cpu_dai);
        if (ret < 0) {
            snd_err("cpu_dai hw free failed\n");
            return ret;
        }
    }

    return ret;
}

static int soc_pcm_close(struct snd_pcm_substream *substream)
{
    struct snd_dai *cpu_dai, *codec_dai;
    struct snd_platform *platform;

    snd_print("\n");
    platform = substream->pcm->card->platform;
    cpu_dai = platform->cpu_dai;
    codec_dai = substream->pcm->card->codec->codec_dai;
    if (cpu_dai->ops->shutdown)
        cpu_dai->ops->shutdown(substream, cpu_dai);
    if (codec_dai->ops->shutdown)
        codec_dai->ops->shutdown(substream, codec_dai);
    if (platform->ops->close)
        platform->ops->close(substream);

    /* dapm stop */
    if (codec_dai->ops->dapm_control)
        codec_dai->ops->dapm_control(substream, codec_dai, 0);

    /* TODO: pinctrl sleep state */

    return 0;
}

static snd_pcm_uframes_t soc_pcm_pointer(struct snd_pcm_substream *substream)
{
    struct snd_platform *platform;
    snd_pcm_uframes_t offset = 0;

    snd_print("\n");
    platform = substream->pcm->card->platform;

    if (platform->ops->pointer)
        offset = platform->ops->pointer(substream);

    return offset;
}

static int soc_pcm_ioctl(struct snd_pcm_substream *substream,
                     unsigned int cmd, void *arg)
{
    struct snd_platform *platform;

    snd_print("\n");
    platform = substream->pcm->card->platform;

        if (platform->ops && platform->ops->ioctl)
                return platform->ops->ioctl(substream, cmd, arg);
    /* FIXME:snd_pcm_lib_ioctl should be called, but it has been called in ksnd_pcm_reset. */
    return -EOPNOTSUPP;
        /* return snd_pcm_lib_ioctl(substream, cmd, arg); */
}

int snd_pcm_new_stream(struct snd_pcm *pcm, int stream, int substream_count)
{
    struct snd_pcm_substream *substream;
    static struct snd_pcm_ops pcm_ops = {
        .open       = soc_pcm_open,
        .hw_params  = soc_pcm_hw_params,
        .prepare    = soc_pcm_prepare,
        .trigger    = soc_pcm_trigger,
        .hw_free    = soc_pcm_hw_free,
        .pointer    = soc_pcm_pointer,
        .close      = soc_pcm_close,
        .ioctl      = soc_pcm_ioctl,
    };

    if (!substream_count)
        return 0;
    substream = snd_malloc(sizeof(struct snd_pcm_substream));
    if (!substream) {
        snd_err("alloc substream failed !\n");
        return -1;
    }
    /* hal_spin_lock_init(&substream->lock); */
    substream->pcm = pcm;
    substream->ops = &pcm_ops;
    substream->stream = stream;
    substream->ref_count = 0;
    pcm->streams[stream] = substream;
    snprintf(substream->name, sizeof(substream->name), "%s %s", pcm->id,
        (stream == SNDRV_PCM_STREAM_PLAYBACK)? "Playback" : "Capture");
    snd_print("new stream\n");
    return 0;
}

static void snd_pcm_free_stream(struct snd_pcm_substream * substream)
{
    snd_print("\n");
    if (!substream)
        return;
    snd_free(substream);
}

static int snd_pcm_free(struct snd_pcm *pcm)
{
    snd_print("\n");
    if (pcm->private_free)
        pcm->private_free(pcm);
    snd_pcm_free_stream(pcm->streams[SNDRV_PCM_STREAM_PLAYBACK]);
    snd_pcm_free_stream(pcm->streams[SNDRV_PCM_STREAM_CAPTURE]);
    list_del(&pcm->list);
    snd_mutex_destroy(pcm->open_mutex);
    /*snd_mutex_destroy(pcm->pcm_mutex);*/
    snd_free(pcm);
    return 0;
}

static int snd_ctl_free(struct snd_card *card)
{
    struct snd_ctl *ctl;
    struct snd_kcontrol *c = NULL, *temp;

    ctl = card->ctl;
    if (!ctl)
        return 0;
    list_for_each_entry_safe(c, temp, &ctl->controls, list) {
        snd_ctl_remove_elem(ctl, c);
    }
    snd_mutex_destroy(ctl->ctl_mutex);
    snd_free(ctl);
    card->ctl = NULL;

    return 0;
}

static int snd_ctl_kcontrol_user_get(struct snd_kcontrol *kcontrol, struct snd_ctl_info *info)
{
    if (!kcontrol->count || !kcontrol->private_data) {
        snd_err("kcontrol count=%d, private_data=%p\n",
            kcontrol->count, kcontrol->private_data);
        return -1;
    }

    info->value = ((unsigned long *)kcontrol->private_data)[0];
    if (info->private_data)
        memcpy(info->private_data, kcontrol->private_data, kcontrol->count * sizeof(unsigned long));
    else
        info->private_data = (unsigned long *)kcontrol->private_data;
    info->id = kcontrol->id;
    info->count  = kcontrol->count;
    info->name = kcontrol->name;
    info->max = kcontrol->max;
    info->min = kcontrol->min;
    snd_info("count=%d, value:0x%x\n", kcontrol->count, info->value);

    return 0;
}

static inline int snd_ctl_kcontrol_user_set_value(struct snd_kcontrol *kcontrol,
                        unsigned long value, int index)
{
    unsigned long *user_value;
    if (value < kcontrol->min || value > kcontrol->max) {
        snd_err("invalid range. min:%d, max:%d, value:%lu\n",
            kcontrol->min, kcontrol->max, value);
        return -1;
    }
    user_value = (unsigned long*)kcontrol->private_data;
    user_value[index] = value;

    return 0;
}

static int snd_ctl_kcontrol_user_set(struct snd_kcontrol *kcontrol, unsigned long val)
{
    unsigned long*user_value;
    int i;
    if (!kcontrol->count || !kcontrol->private_data) {
        snd_err("kcontrol count=%d, private_data=%p\n",
            kcontrol->count, kcontrol->private_data);
        return -1;
    }

    if (kcontrol->count == 1) {
        user_value = (unsigned long *)&val;
        return snd_ctl_kcontrol_user_set_value(kcontrol, *user_value, 0);
    }

    for (i = 0; i < kcontrol->count; i++) {
        user_value = (unsigned long *)val;
        if (snd_ctl_kcontrol_user_set_value(kcontrol, user_value[i], i) < 0)
            return -1;
    }

    return 0;
}

static int snd_ctl_kcontrol_get(struct snd_kcontrol *kcontrol, struct snd_ctl_info *info)
{
    unsigned int val = 0;

    if (kcontrol->private_data_type == SND_MODULE_CODEC) {
        struct snd_codec *codec = kcontrol->private_data;
        val = snd_codec_read(codec, kcontrol->reg);
    } else if (kcontrol->private_data_type == SND_MODULE_PLATFORM) {
        struct snd_platform *platform = kcontrol->private_data;
        val = snd_platform_read(platform, kcontrol->reg);
    } else {
        snd_err("%s invalid kcontrol data type = %d.\n", __func__,
                kcontrol->private_data_type);
    }

    snd_kcontrol_to_snd_ctl_info(kcontrol, info, val);

    return 0;
}

static int snd_ctl_enum_get(struct snd_kcontrol *kcontrol,
                struct snd_ctl_info *info)
{
    unsigned int val = 0;

    if (kcontrol->type != SND_CTL_ELEM_TYPE_ENUMERATED) {
        snd_err("invalid kcontrol type = %d.\n", kcontrol->type);
        return -EINVAL;
    }

    if (kcontrol->private_data_type == SND_MODULE_CODEC) {
        struct snd_codec *codec = kcontrol->private_data;
        val = snd_codec_read(codec, kcontrol->reg);
    } else if (kcontrol->private_data_type == SND_MODULE_PLATFORM) {
        struct snd_platform *platform = kcontrol->private_data;
        val = snd_platform_read(platform, kcontrol->reg);
    } else {
        snd_err("%s invalid kcontrol data type = %d.\n", __func__,
                kcontrol->private_data_type);
    }

    snd_kcontrol_to_snd_ctl_info(kcontrol, info, val);

    return 0;
}

static int snd_ctl_enum_set(struct snd_kcontrol *kcontrol, unsigned long val)
{
    if (kcontrol->type != SND_CTL_ELEM_TYPE_ENUMERATED) {
        snd_err("invalid kcontrol type = %d.\n", kcontrol->type);
        return -EINVAL;
    }

    if (val >= kcontrol->items) {
        snd_err("invalid kcontrol items = %ld.\n", val);
        return -EINVAL;
    }

    if (kcontrol->private_data_type == SND_MODULE_CODEC) {
        struct snd_codec *codec = kcontrol->private_data;
        snd_codec_update_bits(codec, kcontrol->reg,
                (kcontrol->mask << kcontrol->shift),
                ((unsigned int)val << kcontrol->shift));
    } else if (kcontrol->private_data_type == SND_MODULE_PLATFORM) {
        struct snd_platform *platform = kcontrol->private_data;
        snd_platform_update_bits(platform, kcontrol->reg,
                (kcontrol->mask << kcontrol->shift),
                ((unsigned int)val << kcontrol->shift));
    } else {
        snd_err("invalid kcontrol data type = %d.\n",
                kcontrol->private_data_type);
        return -EINVAL;
    }
    kcontrol->value = val & kcontrol->mask;

    snd_info("mask:0x%x, shift:%d, value:0x%x\n",
            kcontrol->mask, kcontrol->shift, kcontrol->value);

    return 0;
}

void snd_kcontrol_to_snd_ctl_info(struct snd_kcontrol *kcontrol,
            struct snd_ctl_info *info, unsigned long value)
{
    info->id = kcontrol->id;
    info->type = kcontrol->type;

    info->value = (unsigned long)((value >> kcontrol->shift) & kcontrol->mask);
    if (info->type == SND_CTL_ELEM_TYPE_ENUMERATED) {
        if (info->value >= kcontrol->items)
            info->value = kcontrol->items - 1;
    } else {
        if (info->value > kcontrol->max)
            info->value = kcontrol->max;
        else if (info->value < kcontrol->min)
            info->value = kcontrol->min;
    }
    info->name = kcontrol->name;
    info->min = kcontrol->min;
    info->max = kcontrol->max;
    info->count = kcontrol->count;
    info->items = kcontrol->items;
    info->texts = kcontrol->texts;
    snd_info("id:%d, type:%d, name:%s, value:0x%x, min:0x%x, max:0x%x, count:0x%x, items:0x%x\n",
        kcontrol->id, kcontrol->type, info->name, info->value,
        info->min, info->max, info->count, info->items);
}


static int snd_ctl_kcontrol_set(struct snd_kcontrol *kcontrol, unsigned long val)
{
    if (kcontrol->private_data_type == SND_MODULE_CODEC) {
        struct snd_codec *codec = kcontrol->private_data;
        snd_codec_update_bits(codec, kcontrol->reg,
                (kcontrol->mask << kcontrol->shift),
                ((unsigned int)val << kcontrol->shift));
    } else {
        struct snd_platform *platform = kcontrol->private_data;
        snd_platform_update_bits(platform, kcontrol->reg,
                (kcontrol->mask << kcontrol->shift),
                ((unsigned int)val << kcontrol->shift));
    }
    snd_info("mask:0x%x, shitf:%d, value:0x%x\n",
            kcontrol->mask, kcontrol->shift, val);
    return 0;
}

static inline void add_controls(struct snd_ctl *ctl, struct snd_kcontrol *control)
{
    if (control->private_data_type == SND_MODULE_USER) {
        struct snd_ctl_info info;

        memset(&info, 0, sizeof(struct snd_ctl_info));
        info.type = control->type;
        info.count = control->count;
        info.name = control->name;
        info.max = control->max;
        info.min = control->min;
        /* initialize value, use reg instead */
        info.value = control->reg;
        if (snd_ctl_add_elem(ctl, &info) < 0)
            snd_err("add user kcontrol(%s) failed\n", control->name);
    } else {
        switch (control->type) {
        case SND_CTL_ELEM_TYPE_INTEGER:
            control->mask = ((1 << __fls(control->max)) - 1);
            if (!control->get)
                control->get = snd_ctl_kcontrol_get;
            if (!control->set)
                control->set = snd_ctl_kcontrol_set;
            break;
        case SND_CTL_ELEM_TYPE_ENUMERATED:
            if (control->mask == SND_CTL_ENUM_AUTO_MASK)
                control->mask = ((1 << __pcm_ffs(control->items)) - 1);
            if (!control->get)
                control->get = snd_ctl_enum_get;
            if (!control->set)
                control->set = snd_ctl_enum_set;
            break;
        default:
            snd_err("kcontrol(%s) type invalid.\n", control->name);
            break;
        }
        control->id = ctl->controls_num++;
        list_add_tail(&control->list, &ctl->controls);
    }
}

static int snd_ctl_add_controls(struct snd_card *card, struct snd_ctl *ctl)
{
    if (card->codec->controls) {
        int i;
        for (i = 0; i < card->codec->num_controls; i++) {
            struct snd_kcontrol *control = NULL;

            control = &card->codec->controls[i];
            if (!control->private_data_type) {
                control->private_data_type = SND_MODULE_CODEC;
                control->private_data = card->codec;
            }
            add_controls(ctl, control);
        }
    }
    if (card->platform->controls) {
        int i;
        for (i = 0; i < card->platform->num_controls; i++) {
            struct snd_kcontrol *control = NULL;

            control = &card->platform->controls[i];
            if (!control->private_data_type) {
                control->private_data_type = SND_MODULE_PLATFORM;
                control->private_data = card->platform;
            }
            add_controls(ctl, control);
        }
    }

    return 0;
}

int snd_ctl_remove_elem(struct snd_ctl *ctl, struct snd_kcontrol *control)
{
    if (control->dynamic != 1)
        return -1;

    list_del(&control->list);
    if (control->name)
        snd_free((void *)control->name);
    if (control->private_data)
        snd_free(control->private_data);
    snd_free(control);
    return 0;
}

int snd_ctl_add_elem(struct snd_ctl *ctl, struct snd_ctl_info *info)
{
    struct snd_kcontrol *control;

    control = snd_malloc(sizeof(struct snd_kcontrol));
    if (!control) {
        snd_err("no memory\n");
        return -ENOMEM;
    }

    if (!info->count) {
        snd_info("unknown count, default 1.\n");
        info->count = 1;
    }
    control->dynamic = 1;
    control->name = (const unsigned char *)snd_strdup((void *)info->name);
    if (!control->name) {
        snd_err("no memory\n");
        goto err;
    }
    control->private_data_type = SND_MODULE_USER;
    control->private_data = snd_malloc(info->count * sizeof(unsigned long));
    if (!control->private_data) {
        snd_err("no memory\n");
        goto err;
    }
    if (info->private_data) {
        memcpy(control->private_data, info->private_data, info->count * sizeof(unsigned long));
    } else {
        unsigned long *user_value;
        int i;
        user_value = (unsigned long *)control->private_data;
        for (i = 0; i < info->count; i++)
            user_value[i] = info->value;
    }
    control->count = info->count;
    control->max = info->max;
    control->min = info->min;
#if 0
    control->mask = ((1 << __fls(control->max)) - 1);
#else
    control->mask = 0;
#endif
    control->id = ctl->controls_num++;
    control->get = snd_ctl_kcontrol_user_get;
    control->set = snd_ctl_kcontrol_user_set;

    list_add_tail(&control->list, &ctl->controls);
    return 0;
err:
    if (control->private_data)
        snd_free(control->private_data);
    if (control->name)
        snd_free(control->name);
    if (control)
        snd_free(control);
    return -1;
}

static int snd_ctl_create(struct snd_card *card)
{
    struct snd_ctl *ctl;
    int ret;

    snd_print("\n");
    ctl = snd_malloc(sizeof(struct snd_ctl));
    if (!ctl) {
        snd_err("no memory\n");
        return -ENOMEM;
    }
    INIT_LIST_HEAD(&ctl->controls);
    ctl->card = card;
    snprintf(ctl->id, sizeof(ctl->id), "CTL %s", card->codec->codec_dai->name);
    ctl->ctl_mutex = snd_mutex_init();
    ret = snd_ctl_add_controls(card, ctl);
    if (ret != 0) {
        snd_free(ctl);
        return ret;
    }

    card->ctl = ctl;
    return 0;
}

static int snd_pcm_new(struct snd_card *card)
{
    int ret = 0, playback = 0, capture = 0;
    struct snd_dai *codec_dai, *cpu_dai;
    struct snd_pcm *pcm;

    snd_print("\n");
    /* TODO:create multi pcm device according codec_dai & cpu_dai */
    codec_dai = card->codec->codec_dai;
    cpu_dai = card->platform->cpu_dai;
    if (codec_dai->playback.channels_min != 0
        && cpu_dai->playback.channels_min != 0)
        playback = 1;
    if (codec_dai->capture.channels_min != 0
        && cpu_dai->capture.channels_min != 0)
        capture = 1;
    if (card->codec->playback_only)
        capture = 0;
    if (card->codec->capture_only)
        playback = 0;

    pcm = snd_malloc(sizeof(struct snd_pcm));
    if (!pcm) {
        snd_err("no memory\n");
        return -ENOMEM;
    }

    INIT_LIST_HEAD(&pcm->list);
    pcm->card = card;
    pcm->num = 0;
    snprintf(pcm->id, sizeof(pcm->id), "PCM %s", codec_dai->name);
    ret = snd_pcm_new_stream(pcm, SNDRV_PCM_STREAM_PLAYBACK, playback);
    if (ret != 0) {
        snd_err("snd_pcm_new_stream failed\n");
        goto err;
    }
    ret = snd_pcm_new_stream(pcm, SNDRV_PCM_STREAM_CAPTURE, capture);
    if (ret != 0) {
        snd_err("snd_pcm_new_stream failed\n");
        goto err;
    }


    if (card->platform->pcm_new) {
        ret = card->platform->pcm_new(pcm);
        if (ret != 0) {
            snd_err("platform pcm_new failed\n");
            goto err;
        }
    }
    pcm->private_free = card->platform->pcm_free;
    pcm->open_mutex = snd_mutex_init();
    list_add(&pcm->list, &card->devices);

    snd_print("snd pcm device create finish, return %d\n", ret);
    return ret;
err:
    if (pcm != NULL) {
        if (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK])
            snd_pcm_free_stream(pcm->streams[SNDRV_PCM_STREAM_PLAYBACK]);
        if (pcm->streams[SNDRV_PCM_STREAM_CAPTURE])
            snd_pcm_free_stream(pcm->streams[SNDRV_PCM_STREAM_CAPTURE]);
        snd_free(pcm);
    }
    return ret;
}

static int snd_card_init(struct snd_card *card)
{
    int ret;

    snd_print("\n");

    /* create ctl device */
    ret = snd_ctl_create(card);
    if (ret < 0) {
        snd_err("snd_ctl_create failed, return %d\n", ret);
        return ret;
    }
    /* create pcm device */
    ret = snd_pcm_new(card);
    if (ret < 0) {
        snd_err("snd_pcm_new failed, return %d\n", ret);
        return ret;
    }

    return 0;
}

static int snd_card_release(struct snd_card *card)
{
    struct snd_pcm *p, *temp;

    snd_print("\n");
    /* free pcm device */
    list_for_each_entry_safe(p, temp, &card->devices, list) {
        snd_print("pcm id:%s\n", p->id);
        snd_pcm_free(p);
    }
    list_del_init(&card->devices);

    /* free ctl device */
    snd_ctl_free(card);

    return 0;
}

typedef int (*platform_func_t)(struct snd_platform *, int num);
extern int snd_platform_cpudai_register(struct snd_platform *platform, int arg);
extern int snd_platform_daudio_register(struct snd_platform *platform, int num);
extern int snd_platform_dmic_register(struct snd_platform *platform, int arg);
extern int snd_platform_spdif_register(struct snd_platform *platform, int arg);

#ifndef CONFIG_SND_PLATFORM_SUNXI_CPUDAI
int snd_platform_cpudai_register(struct snd_platform *platform, int arg)
{
    return -1;
}
#endif
#ifndef CONFIG_SND_PLATFORM_SUNXI_DAUDIO
#ifndef CONFIG_SND_PLATFORM_SUN8IW19_DAUDIO
int snd_platform_daudio_register(struct snd_platform *platform, int num)
{
    return -1;
}
#endif
#endif
#ifndef CONFIG_SND_PLATFORM_SUNXI_DMIC
int snd_platform_dmic_register(struct snd_platform *platform, int arg)
{
    return -1;
}
#endif
#ifndef CONFIG_SND_PLATFORM_SUNXI_SPDIF
int snd_platform_spdif_register(struct snd_platform *platform, int arg)
{
    return -1;
}
#endif

static struct snd_platform *snd_platform_register(int type)
{
    int ret = -1;
    struct snd_platform *platform = NULL;
    int arg = 0;

    snd_print(" register type:%d\n", type);

    if (type >= SND_PLATFORM_TYPE_MAX) {
        snd_err("platfrom type:%d is not supported.\n", type);
        return NULL;
    }
    platform = snd_malloc(sizeof(struct snd_platform));
    if (!platform) {
        snd_err("no memory\n");
        return NULL;
    }
    switch (type) {
        case SND_PLATFORM_TYPE_CPUDAI:
            ret = snd_platform_cpudai_register(platform, arg);
            break;
        case SND_PLATFORM_TYPE_DAUDIO0:
        case SND_PLATFORM_TYPE_DAUDIO1:
        case SND_PLATFORM_TYPE_DAUDIO2:
        case SND_PLATFORM_TYPE_DAUDIO3:
            arg = type - SND_PLATFORM_TYPE_DAUDIO0;
            ret = snd_platform_daudio_register(platform, arg);
            break;
        case SND_PLATFORM_TYPE_DMIC:
            ret = snd_platform_dmic_register(platform, arg);
            break;
        case SND_PLATFORM_TYPE_SPDIF:
            ret = snd_platform_spdif_register(platform, arg);
            break;
        default:
            ret = -1;
            break;
    }

    if (ret != 0) {
        snd_err("platform type:%d register failed\n", type);
        snd_free(platform);
        return NULL;
    }
    platform->type = type;

    return platform;
}

static int snd_platform_unregister(struct snd_platform *platform)
{
    if (!platform)
        return -1;
    if (platform->controls)
        snd_free(platform->controls);
    if (platform->cpu_dai)
        snd_free(platform->cpu_dai);
    snd_free(platform->name);
    snd_free(platform);
    return 0;
}

struct snd_pcm *snd_card_find_pcm(struct snd_card *card, int device_num)
{
    struct snd_pcm *p;

    list_for_each_entry(p, &card->devices, list) {
        if (p->num == device_num)
            return p;
    }
    return NULL;
}

struct snd_card *snd_card_find_by_name(const char *name)
{
    struct snd_card *c;
    list_for_each_entry(c, &gCardList, list) {
        if (strlen(c->name) == strlen(name) && !strcmp(c->name, name))
            return c;
    }
    return NULL;
}

struct snd_card *snd_card_find_by_platform_type(int type)
{
    struct snd_card *c;
    list_for_each_entry(c, &gCardList, list) {
        if (!c->platform)
            continue;
        if (c->platform->type == type)
            return c;
    }
    return NULL;
}

struct snd_card *snd_card_find_by_num(int num)
{
    struct snd_card *c = NULL;

    list_for_each_entry(c, &gCardList, list) {
        if (c->num == num)
            return c;
    }
    return NULL;
}

int snd_card_get_number(void)
{
    struct snd_card *c = NULL;
    struct list_head *list;

    list = gCardList.next;
    if (list == &gCardList)
        return 0;
    c = container_of(list, struct snd_card, list);
    return (c->num + 1);
}

int snd_card_register(const char *name,
        snd_codec_t *codec,
        int platform_type)
{
    int ret = 0;
    struct snd_card *card= NULL;
    struct snd_platform *platform = NULL;

    snd_print("\n");
    if (!codec)
        return -1;

    card = snd_card_find_by_name(name);
    if (card != NULL) {
        snd_err("card:%s already registered\n", name);
        return -1;
    }
    card = snd_card_find_by_platform_type(platform_type);
    if (card != NULL) {
        snd_err("card:%s already registered with platform type:%d\n",
             card->name, platform_type);
        return -1;
    }

    platform = snd_platform_register(platform_type);
    if (!platform) {
        snd_err("platform register failed\n");
        return -1;
    }

    card = snd_malloc(sizeof(struct snd_card));
    if (!card) {
        snd_err("no memory\n");
        ret = -ENOMEM;
        goto err1;
    }
    if (!name)
        card->name = strdup("unknown");
    else
        card->name = strdup(name);

    INIT_LIST_HEAD(&card->devices);
    INIT_LIST_HEAD(&card->list);
    card->codec = codec;
    card->platform = platform;

    /* codec & platform probe */
    if (codec->probe) {
        ret = codec->probe(codec);
        if (ret != 0) {
            snd_err("codec[%s] probe failed\n", codec->name);
            goto err2;
        }
    }

    if (codec->codec_dai->probe) {
        ret = codec->codec_dai->probe(codec->codec_dai);
        if (ret != 0) {
            snd_err("codec_dai[%s] probe failed\n", codec->codec_dai->name);
            goto err2;
        }
    }

    if (platform->probe) {
        ret = platform->probe(platform);
        if (ret != 0) {
            snd_err("platform[%s] probe failed\n", platform->name);
            goto err2;
        }
    }

    if (platform->cpu_dai->probe) {
        ret = platform->cpu_dai->probe(platform->cpu_dai);
        if (ret != 0) {
            snd_err("cpu_dai[%s] probe failed\n", platform->cpu_dai->name);
            goto err2;
        }
    }

    /* card initialization */
    ret = snd_card_init(card);
    if (ret != 0) {
        snd_err("card init failed\n");
        goto err2;
    }

    card->num = snd_card_get_number();
    list_add(&card->list, &gCardList);

    snd_print("register card:%s success.\n", name);

    return ret;
err2:
    snd_free(card->name);
    snd_free(card);
err1:
    snd_platform_unregister(platform);
    return ret;
}

int snd_card_unregister(struct snd_card *card)
{
    if (!card)
        return 0;
    list_del(&card->list);
    if (card->codec->remove)
        card->codec->remove(card->codec);
    if (card->platform->remove)
        card->platform->remove(card->platform);
    snd_card_release(card);
    snd_platform_unregister(card->platform);
    snd_free(card->name);
    snd_free(card);
    return 0;
}

int snd_card_unregister_all(void)
{
    struct snd_card *c = NULL, *temp = NULL;

    list_for_each_entry_safe(c, temp, &gCardList, list) {
        snd_print("card name:%s\n", c->name);
        snd_card_unregister(c);
    }
    snd_print("\n");
    return 0;
}

void snd_card_list(void)
{
    int i = 0;
    int card_num = 0;
    struct snd_card *card = NULL;

    snd_print("======== Sound Card List ========\n");
    card_num = snd_card_get_number();
    if (card_num <= 0) {
        snd_print("\tno registered card...\n");
        return;
    }

    snd_print("%8s%20s\n", "card_num", "card_name");
    for (i = 0; i < card_num; i++) {
        card = snd_card_find_by_num(i);
        if (!card) {
            snd_print("card_num:%d not find.\n", i);
            return;
        }
        snd_print("%8d%20s\n", i, card->name);
    }
    snd_print("\n");
}

void snd_core_version(void)
{
#ifdef CONFIG_KERNEL_FREERTOS
    snd_print("AW-SOUND-CORE version:%s, compiled on: %s %s\n",
        SND_CORE_VERSION, __DATE__, __TIME__);
#else
    snd_print("AW-SOUND-CORE version:%s\n", SND_CORE_VERSION);
#endif
}
