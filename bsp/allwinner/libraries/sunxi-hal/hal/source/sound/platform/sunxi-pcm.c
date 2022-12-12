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
#include <sound/snd_core.h>
#include <sound/snd_pcm.h>
#include <sound/snd_dma.h>
#include <sound/dma_wrap.h>
#include "sunxi-pcm.h"

#ifndef sunxi_slave_id
#define sunxi_slave_id(d, s) (((d)<<16) | (s))
#endif

/* playback: period_size=2048*(16*2/8)=8K buffer_size=8K*8=64K */
/* capture:  period_size=2048*(16*4/8)=16K buffer_size=16K*8=128K */
static const struct snd_pcm_hardware sunxi_pcm_hardware[2] = {
    {   /* SNDRV_PCM_STREAM_PLAYBACK */
        .info           = SNDRV_PCM_INFO_INTERLEAVED
                    | SNDRV_PCM_INFO_BLOCK_TRANSFER
                    | SNDRV_PCM_INFO_MMAP
                    | SNDRV_PCM_INFO_MMAP_VALID
                    | SNDRV_PCM_INFO_PAUSE
                    | SNDRV_PCM_INFO_RESUME,
        .buffer_bytes_max   = 1024 * 128,
        .period_bytes_min   = 256,
        .period_bytes_max   = 1024 * 64,
        .periods_min        = 2,
        .periods_max        = 16,
    },
    {   /* SNDRV_PCM_STREAM_CAPTURE */
        .info           = SNDRV_PCM_INFO_INTERLEAVED
                    | SNDRV_PCM_INFO_BLOCK_TRANSFER
                    | SNDRV_PCM_INFO_MMAP
                    | SNDRV_PCM_INFO_MMAP_VALID
                    | SNDRV_PCM_INFO_PAUSE
                    | SNDRV_PCM_INFO_RESUME,
        .buffer_bytes_max   = 1024 * 128,
        .period_bytes_min   = 256,
        .period_bytes_max   = 1024 * 64,
        .periods_min        = 2,
        .periods_max        = 16,
    },
};

static int sunxi_pcm_preallocate_dma_buffer(struct snd_pcm *pcm, int stream)
{
    const struct snd_pcm_hardware *hw = NULL;
    struct snd_codec *codec = pcm->card->codec;
    struct snd_dma_buffer *buf = &pcm->streams[stream]->dma_buffer;
    size_t size = 0;

    snd_print("prealloc dma buffer\n");
    if (codec->hw)
        hw = &codec->hw[stream];
    else
        hw = &sunxi_pcm_hardware[stream];
    size = hw->buffer_bytes_max;
    buf->addr = dma_alloc_coherent(size);
    if (!buf->addr)
        return -ENOMEM;
    buf->bytes = size;

    return 0;
}

int sunxi_pcm_new(struct snd_pcm *pcm)
{
    int ret;

    snd_print("\n");
    if (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK]) {
        ret = sunxi_pcm_preallocate_dma_buffer(pcm,
                        SNDRV_PCM_STREAM_PLAYBACK);
        if (ret != 0)
            goto err;
    }
    if (pcm->streams[SNDRV_PCM_STREAM_CAPTURE]) {
        ret = sunxi_pcm_preallocate_dma_buffer(pcm,
                        SNDRV_PCM_STREAM_CAPTURE);
        if (ret != 0)
            goto err;
    }
err:
    return 0;
}

void sunxi_pcm_free(struct snd_pcm *pcm)
{
    struct snd_pcm_substream *substream;
    struct snd_dma_buffer *buf;
    int stream;

    snd_print("\n");
    for (stream = 0; stream < 2; stream++) {
        substream = pcm->streams[stream];
        if (!substream)
            continue;
        buf = &substream->dma_buffer;
        if (!buf->addr)
            continue;
        snd_print("dma free.\n");
        dma_free_coherent(buf->addr);
        buf->addr = NULL;
    }
    return ;
}

static int sunxi_pcm_open(struct snd_pcm_substream *substream)
{
    int ret;
    const struct snd_pcm_hardware *hw = NULL;
    struct snd_codec *codec = substream->pcm->card->codec;

    if (codec->hw)
        hw = &codec->hw[substream->stream];
    else
        hw = &sunxi_pcm_hardware[substream->stream];
    snd_set_runtime_hwparams(substream, hw);
    snd_print("request dma channel\n");
    /* request dma channel */
    ret = snd_dmaengine_pcm_open_request_chan(substream);
    if (ret != 0)
        snd_err("dmaengine pcm open failed with err %d\n", ret);
    return ret;
}

static int sunxi_pcm_close(struct snd_pcm_substream *substream)
{
    snd_print("\n");
    return snd_dmaengine_pcm_close_release_chan(substream);
}

static int sunxi_pcm_hw_params(struct snd_pcm_substream *substream,
    struct snd_pcm_hw_params *params)
{
    int ret;
    struct snd_card *card = substream->pcm->card;
    struct snd_dai *cpu_dai = card->platform->cpu_dai;
//  struct dmaengine_pcm_runtime_data *prtd = substream->runtime->private_data;
    struct dma_chan *chan = snd_dmaengine_pcm_get_chan(substream);
    struct dma_slave_config slave_config = {0};
    struct sunxi_dma_params *dmap;
#ifdef CONFIG_SND_PLATFORM_SUNXI_MAD
    struct snd_platform *platform = cpu_dai->component;
    unsigned int mad_bind = 0;
#endif

    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
        dmap = cpu_dai->playback_dma_data;
    else
        dmap = cpu_dai->capture_dma_data;

    ret = snd_hwparams_to_dma_slave_config(substream, params, &slave_config);
    if (ret != 0) {
        snd_err("hw params config failed with err %d\n", ret);
        return ret;
    }
    slave_config.dst_maxburst = dmap->dst_maxburst;
    slave_config.src_maxburst = dmap->src_maxburst;
#ifdef CONFIG_SND_PLATFORM_SUNXI_MAD
    if (substream->stream == SNDRV_PCM_STREAM_CAPTURE) {
        if (!strncmp(card->name, "snddmic", 7)) {
            struct sunxi_dmic_info *sunxi_dmic = platform->private_data;
            mad_bind = sunxi_dmic->mad_priv.mad_bind;
        } else if (!strncmp(card->name, "snddaudio0", 10)) {
            struct sunxi_daudio_info *sunxi_daudio = platform->private_data;
            mad_bind = sunxi_daudio->mad_priv.mad_bind;
        }
        printf(SNDRV_LOG_COLOR_BLUE "mad_bind[%s]: %s\n" SNDRV_LOG_COLOR_NONE,
                card->name, mad_bind ? "On":"Off");
        if (mad_bind == 1)
            slave_config.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
    }
#endif

    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        slave_config.dst_addr = (unsigned long)dmap->dma_addr;
        slave_config.src_addr_width = slave_config.dst_addr_width;
        slave_config.slave_id = sunxi_slave_id(dmap->dma_drq_type_num, 0);
    } else {
        slave_config.src_addr = (unsigned long)dmap->dma_addr;
        slave_config.dst_addr_width = slave_config.src_addr_width;
        slave_config.slave_id = sunxi_slave_id(0,
                        dmap->dma_drq_type_num);
    }
    snd_info("src_addr:%p, dst_addr:%p, drq_type:%d\n",
        slave_config.src_addr, slave_config.dst_addr,
        dmap->dma_drq_type_num);

    ret = dmaengine_slave_config(chan, &slave_config);
    if (ret != 0) {
        snd_err("dmaengine_slave_config failed with err %d\n", ret);
        return ret;
    }

    snd_pcm_set_runtime_buffer(substream, &substream->dma_buffer);

    return 0;
}

static int sunxi_pcm_hw_free(struct snd_pcm_substream *substream)
{
    snd_print("\n");
    snd_pcm_set_runtime_buffer(substream, NULL);
    return 0;
}

static int sunxi_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
    snd_print(" stream:%u, cmd:%u\n", substream->stream, cmd);
    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
        switch (cmd) {
        case SNDRV_PCM_TRIGGER_START:
        case SNDRV_PCM_TRIGGER_RESUME:
        case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
            snd_dmaengine_pcm_trigger(substream,
                    SNDRV_PCM_TRIGGER_START);
            break;
        case SNDRV_PCM_TRIGGER_SUSPEND:
        case SNDRV_PCM_TRIGGER_STOP:
        case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
            snd_dmaengine_pcm_trigger(substream,
                    SNDRV_PCM_TRIGGER_STOP);
            break;
        }
    } else {
        switch (cmd) {
        case SNDRV_PCM_TRIGGER_START:
        case SNDRV_PCM_TRIGGER_RESUME:
        case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
            snd_dmaengine_pcm_trigger(substream,
                    SNDRV_PCM_TRIGGER_START);
            break;
        case SNDRV_PCM_TRIGGER_SUSPEND:
        case SNDRV_PCM_TRIGGER_STOP:
        case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
            snd_dmaengine_pcm_trigger(substream,
                    SNDRV_PCM_TRIGGER_STOP);
            break;
        }
    }
    return 0;
}

struct snd_pcm_ops sunxi_pcm_ops = {
    .open       = sunxi_pcm_open,
    .close      = sunxi_pcm_close,
    .hw_params  = sunxi_pcm_hw_params,
    .hw_free    = sunxi_pcm_hw_free,
    .trigger    = sunxi_pcm_trigger,
    .pointer    = snd_dmaengine_pcm_pointer,
};

