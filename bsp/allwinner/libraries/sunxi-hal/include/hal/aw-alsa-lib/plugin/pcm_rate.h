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

#ifndef __AW_ALSA_LIB_PCM_RATE_H
#define __AW_ALSA_LIB_PCM_RATE_H

#include <aw-alsa-lib/pcm.h>
#include <sys/types.h>
#define SND_PCM_RATE_PLUGIN_VERSION 0x010002

#define SND_PCM_RATE_PLUGIN_ENTRY(name) _snd_pcm_rate_##name##_open
#define SND_PCM_RATE_PLUGIN_CONF_ENTRY(name) _snd_pcm_rate_##name##_open_conf

#define SND_PCM_PLUGIN_RATE_MIN 4000
#define SND_PCM_PLUGIN_RATE_MAX 192000

typedef struct _snd_pcm_rate snd_pcm_rate_t;

/** hw_params information for a single side */
typedef struct snd_pcm_rate_side_info {
    snd_pcm_format_t format;
    unsigned int rate;
    snd_pcm_uframes_t buffer_size;
    snd_pcm_uframes_t period_size;
} snd_pcm_rate_side_info_t;

/** hw_params information */
typedef struct snd_pcm_rate_info {
    struct snd_pcm_rate_side_info in;
    struct snd_pcm_rate_side_info out;
    unsigned int channels;
} snd_pcm_rate_info_t;

/** Callback table of rate-converter */
typedef struct snd_pcm_rate_ops {
    /**
     * close the converter; optional
     */
    void (*close)(void *obj);
    /**
     * initialize the converter, called at hw_params
     */
    int (*init)(void *obj, snd_pcm_rate_info_t *info);
    /**
     * free the converter; optional
     */
    void (*free)(void *obj);
    /**
     * reset the converter, called at prepare; optional
     */
    void (*reset)(void *obj);
    /**
     * adjust the pitch, called at sw_params; optional
     */
    int (*adjust_pitch)(void *obj, snd_pcm_rate_info_t *info);
    /**
     * convert the data
     */
    void (*convert)(void *obj,
            const snd_pcm_channel_area_t *dst_areas,
            snd_pcm_uframes_t dst_offset, unsigned int dst_frames,
            const snd_pcm_channel_area_t *src_areas,
            snd_pcm_uframes_t src_offset, unsigned int src_frames);
    /**
     * convert an s16 interleaved-data array; exclusive with convert
     */
    void (*convert_s16)(void *obj, int16_t *dst, unsigned int dst_frames,
                const int16_t *src, unsigned int src_frames);

    void (*convert_s16_fix)(void *obj, int16_t *dst, unsigned int *dst_frames,
                const int16_t *src, unsigned int *src_frames);
    /**
     * compute the frame size for input
     */
    snd_pcm_uframes_t (*input_frames)(void *obj, snd_pcm_uframes_t frames);
    /**
     * compute the frame size for output
     */
    snd_pcm_uframes_t (*output_frames)(void *obj, snd_pcm_uframes_t frames);
    /**
     * the protocol version the plugin supports;
     * new field since version 0x010002
     */
    unsigned int version;
    /**
     * return the supported min / max sample rates;
     * new ops since version 0x010002
     */
    int (*get_supported_rates)(void *obj, unsigned int *rate_min,
                   unsigned int *rate_max);
    /**
     * show some status messages for verbose mode;
     * new ops since version 0x010002
    */
    void (*dump)(void *obj);
} snd_pcm_rate_ops_t;

/** open function type */
typedef int (*snd_pcm_rate_open_func_t)(unsigned int version, void **objp,
                    snd_pcm_rate_ops_t *opsp);

typedef struct {
    const char *pcm;
    snd_pcm_format_t format;
    unsigned int rate;
} snd_pcm_rate_slave_config_t;

typedef struct {
    const char *type;
    snd_pcm_rate_slave_config_t slave;
    const char *converter;
} snd_pcm_rate_config_t;

#endif /* __AW_ALSA_LIB_PCM_RATE_H */
