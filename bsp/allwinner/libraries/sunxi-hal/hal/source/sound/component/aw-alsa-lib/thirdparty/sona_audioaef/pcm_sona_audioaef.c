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
#include <aw-alsa-lib/pcm_config.h>
#include <aw-alsa-lib/pcm_extplug.h>
#include <aw-alsa-lib/plugin/pcm_sona_audioaef.h>
#include "audioaef.h"
#include "sona_config.h"

typedef struct {
    const char *config_name;
    const char *config_file;
    int max_frames;
    int runtime_config;
} sona_audioaef_params_t;

typedef struct {
    snd_pcm_extplug_t ext;
    sona_audioaef_params_t params;
    void *instance;
    void *rpc_handle;
} snd_pcm_sona_audioaef_t;

static inline void *area_addr(const snd_pcm_channel_area_t *area, snd_pcm_uframes_t offset)
{
    unsigned int bitofs = area->first + area->step * offset;
    return (char *) area->addr + bitofs / 8;
}

static snd_pcm_sframes_t sona_audioaef_transfer(snd_pcm_extplug_t *ext,
    const snd_pcm_channel_area_t *dst_areas, snd_pcm_uframes_t dst_offset,
    const snd_pcm_channel_area_t *src_areas, snd_pcm_uframes_t src_offset,
    snd_pcm_uframes_t size)
{
    snd_pcm_sona_audioaef_t *audioaef = (snd_pcm_sona_audioaef_t *)ext->private_data;

    char *src = (char *)area_addr(src_areas, src_offset);
    char *dst = (char *)area_addr(dst_areas, dst_offset);

    int in_channels = ext->channels;
    int out_channls = ext->slave_channels;
    int in_bits = snd_pcm_format_physical_width(ext->format);

    int residue_bytes = in_bits / 8 * in_channels * size;
    int process_bytes_max = in_bits / 8 * audioaef->params.max_frames;
    int process_bytes = 0;

    while (residue_bytes > 0) {
        process_bytes = process_bytes_max < residue_bytes ?
            process_bytes_max : residue_bytes;
        int ret = audioaef_process(audioaef->instance, src,
                process_bytes, in_channels, in_bits, dst, out_channls);
        if (ret < 0) {
            awalsa_err("Error in audioaef_process. "
                    "Maybe max_frames not large enough? "
                    "(max_frames: %d, process_bytes: %d)\n",
                    audioaef->params.max_frames, process_bytes);
            return ret;
        }
        src += process_bytes;
        dst += process_bytes;
        residue_bytes -= process_bytes;
    }

    return size;
}

static int sona_audioaef_hw_params(snd_pcm_extplug_t *ext, snd_pcm_hw_params_t *params)
{
    snd_pcm_sona_audioaef_t *audioaef = (snd_pcm_sona_audioaef_t *)ext->private_data;
    int ret;

    if (audioaef->instance) {
        return 0;
    }

    if (audioaef->params.max_frames <= 0) {
        snd_pcm_uframes_t period_size = 0;
        if (0 != snd_pcm_hw_params_get_period_size(params, &period_size, 0)) {
            awalsa_err("Fail to get period size\n");
        }
        audioaef->params.max_frames = (int)period_size;
    }

    if (audioaef->params.config_name) {
        sona_config_t *config = NULL;
        config = sona_config_find(audioaef->params.config_name);
        if (!config) {
            awalsa_err("sona config \"%s\" not found\n",
                    audioaef->params.config_name);
            ret = -EINVAL;
            goto err_out;
        }
        audioaef->instance = audioaef_create_fromBuffer(ext->rate, ext->rate,
                config->start,
                snd_pcm_format_physical_width(ext->slave_format),
                audioaef->params.max_frames);
    } else if (audioaef->params.config_file) {
        audioaef->instance = audioaef_create(ext->rate, ext->rate,
                audioaef->params.config_file,
                snd_pcm_format_physical_width(ext->slave_format),
                audioaef->params.max_frames);
    } else {
        awalsa_err("config_name or config_file not specified\n");
        ret = -EINVAL;
        goto err_out;
    }
    if (!audioaef->instance) {
        awalsa_err("Fail to create audioaef instance\n");
        ret = -1;
        goto err_out;
    }

    if (audioaef->params.runtime_config) {
        audioaef->rpc_handle = audioRPC_init(audioaef->instance);
        if (!audioaef->rpc_handle) {
            awalsa_err("Fail to init audioaef RPC handle\n");
            return -1;
        }
    }

    return 0;

err_out:
    if (audioaef->rpc_handle) {
        audioRPC_close(audioaef->rpc_handle);
        audioaef->rpc_handle = NULL;
    }
    if (audioaef->instance) {
        audioaef_destroy(audioaef->instance);
        audioaef->instance = NULL;
    }
    return ret;
}

static int sona_audioaef_hw_free(snd_pcm_extplug_t *ext)
{
    snd_pcm_sona_audioaef_t *audioaef = (snd_pcm_sona_audioaef_t *)ext->private_data;

    if (!audioaef) {
        return 0;
    }
    if (audioaef->rpc_handle) {
        audioRPC_close(audioaef->rpc_handle);
        audioaef->rpc_handle = NULL;
    }
    if (audioaef->instance) {
        audioaef_destroy(audioaef->instance);
        audioaef->instance = NULL;
    }
    return 0;
}

static int sona_audioaef_close(snd_pcm_extplug_t *ext)
{
    snd_pcm_sona_audioaef_t *audioaef = (snd_pcm_sona_audioaef_t *)ext->private_data;

    if (audioaef->rpc_handle) {
        audioRPC_close(audioaef->rpc_handle);
        audioaef->rpc_handle = NULL;
    }
    if (audioaef->instance) {
        audioaef_destroy(audioaef->instance);
        audioaef->instance = NULL;
    }
    audioaef->params.config_name = NULL;
    audioaef->params.config_file = NULL;
    free(audioaef);
    return 0;
}

static const snd_pcm_extplug_callback_t sona_audioaef_callback = {
    .transfer = sona_audioaef_transfer,
    .hw_params = sona_audioaef_hw_params,
    .hw_free = sona_audioaef_hw_free,
    .close = sona_audioaef_close,
};

int _snd_pcm_sona_audioaef_open(snd_pcm_t **pcmp, const snd_pcm_config_t *pcm_config,
        snd_pcm_stream_t stream, int mode)
{
    int ret = 0;
    snd_pcm_t *pcm = NULL;
    const snd_pcm_sona_audioaef_config_t *audioaef_config =
        (const snd_pcm_sona_audioaef_config_t *)(pcm_config->config);
    snd_pcm_sona_audioaef_t *audioaef = NULL;

    awalsa_debug("\n");

    audioaef = calloc(1, sizeof(snd_pcm_sona_audioaef_t));
    if (!audioaef) {
        awalsa_err("no memory\n");
        ret = -ENOMEM;
        goto err_out;
    }

    if (audioaef_config->config_name) {
        audioaef->params.config_name = audioaef_config->config_name;
        audioaef->params.config_file = NULL;
    } else if (audioaef_config->config_file) {
        audioaef->params.config_name = NULL;
        audioaef->params.config_file = audioaef_config->config_file;
    } else {
        awalsa_err("config_name or config_file not specified\n");
        ret = -EINVAL;
        goto err_free_audioaef;
    }

    audioaef->ext.name = "Sona Audio Effect Plugin";
    audioaef->ext.callback = &sona_audioaef_callback;
    audioaef->ext.private_data = audioaef;
    audioaef->params.max_frames = audioaef_config->max_frames;
    audioaef->params.runtime_config = audioaef_config->runtime_config;
    audioaef->instance = NULL;
    audioaef->rpc_handle = NULL;

    ret = snd_pcm_extplug_create(&audioaef->ext, pcm_config->name,
            audioaef_config->slave.pcm, stream, mode);
    if (ret < 0) {
        goto err_free_audioaef;
    }

    // TODO: param constraints are not complete
    snd_pcm_extplug_set_param(&audioaef->ext, SND_PCM_EXTPLUG_HW_CHANNELS, 1);
    snd_pcm_extplug_set_slave_param(&audioaef->ext, SND_PCM_EXTPLUG_HW_CHANNELS, 1);
    snd_pcm_extplug_set_param(&audioaef->ext, SND_PCM_EXTPLUG_HW_FORMAT,
        SND_PCM_FORMAT_S16_LE);
    snd_pcm_extplug_set_slave_param(&audioaef->ext, SND_PCM_EXTPLUG_HW_FORMAT,
        SND_PCM_FORMAT_S16_LE);

    *pcmp = audioaef->ext.pcm;
    return 0;

err_free_audioaef:
    free(audioaef);
err_out:
    return ret;
}
