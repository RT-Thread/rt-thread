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
#include <sound/snd_core.h>
#include <sound/snd_dma.h>
#include <sound/snd_pcm.h>
#include <hal_dma.h>
#include <sound/dma_wrap.h>
#include <hal_cache.h>

struct dmaengine_pcm_runtime_data {
    struct dma_chan *dma_chan;
    /* used for no residue, noneed now */
    uint32_t pos;
};

void snd_pcm_period_elapsed(struct snd_pcm_substream *substream);

static inline struct dmaengine_pcm_runtime_data *substream_to_prtd(
    const struct snd_pcm_substream *substream)
{
    return substream->runtime->private_data;
}

struct dma_chan *snd_dmaengine_pcm_get_chan(struct snd_pcm_substream *substream)
{
        struct dmaengine_pcm_runtime_data *prtd = substream_to_prtd(substream);

        return prtd->dma_chan;
}

int snd_hwparams_to_dma_slave_config(const struct snd_pcm_substream *substream,
                const struct snd_pcm_hw_params *params,
                struct dma_slave_config *slave_config)
{
    enum dma_slave_buswidth buswidth;
        switch (params_format(params)) {
        case SND_PCM_FORMAT_S8:
                buswidth = DMA_SLAVE_BUSWIDTH_1_BYTE;
                break;
        case SND_PCM_FORMAT_S16_LE:
                buswidth = DMA_SLAVE_BUSWIDTH_2_BYTES;
                break;
        case SND_PCM_FORMAT_S24_LE:
        case SND_PCM_FORMAT_S32_LE:
                buswidth = DMA_SLAVE_BUSWIDTH_4_BYTES;
                break;
        default:
                return -EINVAL;
        }

        if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
                slave_config->direction = DMA_MEM_TO_DEV;
                slave_config->dst_addr_width = buswidth;
        } else {
                slave_config->direction = DMA_DEV_TO_MEM;
                slave_config->src_addr_width = buswidth;
        }
    return 0;
}

int snd_dmaengine_pcm_open_request_chan(struct snd_pcm_substream *substream)
{
    struct dma_chan *chan;
    struct dmaengine_pcm_runtime_data *prtd;

    chan = dma_request_channel();
    if (!chan)
        return -ENXIO;
    prtd = snd_malloc(sizeof(struct dmaengine_pcm_runtime_data));
    if (!prtd)
        return -ENOMEM;
    prtd->dma_chan = chan;
    substream->runtime->private_data = prtd;

    return 0;
}

int snd_dmaengine_pcm_close_release_chan(struct snd_pcm_substream *substream)
{
    struct dmaengine_pcm_runtime_data *prtd = substream_to_prtd(substream);

    dma_release_channel(prtd->dma_chan);
    snd_free(prtd);
    substream->runtime->private_data = NULL;
    return 0;
}

snd_pcm_uframes_t snd_dmaengine_pcm_pointer(struct snd_pcm_substream *substream)
{
    struct dmaengine_pcm_runtime_data *prtd = substream_to_prtd(substream);
    uint32_t residue = 0;
    enum dma_status status;
    uint32_t pos = 0;
    uint32_t buf_size;

    status = dmaengine_tx_status(prtd->dma_chan, &residue);
    snd_print("dma status:%u, residue:%u(0x%x) bytes\n", status, residue, residue);
    if (status == DMA_IN_PROGRESS || status == DMA_PAUSED) {
        buf_size = snd_pcm_lib_buffer_bytes(substream);
        if (residue > 0 && residue <= buf_size)
            pos = buf_size - residue;
    }
    snd_print("----pos:0x%x(%u) bytes, pos frames offset:0x%lx\n",
            pos, pos, bytes_to_frames(substream->runtime, pos));
    return bytes_to_frames(substream->runtime, pos);
}

static inline enum dma_transfer_direction
snd_pcm_substream_to_dma_direction(const struct snd_pcm_substream *substream)
{
    if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
        return DMA_MEM_TO_DEV;
    else
        return DMA_DEV_TO_MEM;
}

static void dmaengine_pcm_dma_complete(void *arg)
{
    struct snd_pcm_substream *substream = arg;
    struct dmaengine_pcm_runtime_data *prtd;

    snd_print("=========dma callback start============\n");
    if (!substream->runtime)
        return;
    prtd = substream_to_prtd(substream);
    prtd->pos += snd_pcm_lib_period_bytes(substream);
    if (prtd->pos >= snd_pcm_lib_buffer_bytes(substream))
        prtd->pos = 0;
    snd_pcm_period_elapsed(substream);
    snd_print("==========dma callback finish===========\n");
}

static int dmaengine_pcm_prepare_and_submit(struct snd_pcm_substream *substream)
{
    struct dmaengine_pcm_runtime_data *prtd = substream_to_prtd(substream);
    struct dma_chan *chan = prtd->dma_chan;
    enum dma_transfer_direction direction;
    int ret = 0;
    dma_callback callback;

    direction = snd_pcm_substream_to_dma_direction(substream);

    prtd->pos = 0;

    /* flush ringbuffer */
    hal_dcache_clean_invalidate((unsigned long)(substream->runtime->dma_addr),
                snd_pcm_lib_buffer_bytes(substream));

    ret = dmaengine_prep_dma_cyclic(chan,
        substream->runtime->dma_addr,
        snd_pcm_lib_buffer_bytes(substream),
        snd_pcm_lib_period_bytes(substream), direction);
    if (ret != 0) {
        snd_err("[%s] dma cyclic failed!!!\n", __func__);
        return ret;
    }
    callback = dmaengine_pcm_dma_complete;

    dmaengine_submit(chan, callback, (void *)substream);

    return 0;
}

int snd_dmaengine_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
    struct dmaengine_pcm_runtime_data *prtd = substream_to_prtd(substream);
    int ret;

    snd_print("\n");
    switch (cmd) {
    case SNDRV_PCM_TRIGGER_START:
        ret = dmaengine_pcm_prepare_and_submit(substream);
        if (ret < 0)
            return ret;
        dma_async_issue_pending(prtd->dma_chan);
        break;
    case SNDRV_PCM_TRIGGER_RESUME:
    case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
        dmaengine_resume(prtd->dma_chan);
        break;
    case SNDRV_PCM_TRIGGER_SUSPEND:
#if 0
        if (runtime->info & SNDRV_PCM_INFO_PAUSE)
            dmaengine_pause(prtd->dma_chan);
        else
#endif
            dmaengine_terminate_async(prtd->dma_chan);
        break;
    case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
        dmaengine_pause(prtd->dma_chan);
        break;
    case SNDRV_PCM_TRIGGER_STOP:
        dmaengine_terminate_async(prtd->dma_chan);
        break;
    default:
        return -EINVAL;
    }

    return 0;
}
