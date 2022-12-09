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

#ifndef __AW_ALSA_PCM_ROUTE_H
#define __AW_ALSA_PCM_ROUTE_H

/* ROUTE_FLOAT should be set to 0 for machines without FP unit - like iPAQ */
#define SND_PCM_PLUGIN_ROUTE_FLOAT 1

#define SND_PCM_PLUGIN_ROUTE_RESOLUTION 16 /**< integer resolution for route plugin */

#if SND_PCM_PLUGIN_ROUTE_FLOAT
/** route ttable entry type */
typedef float snd_pcm_route_ttable_entry_t;
#define SND_PCM_PLUGIN_ROUTE_HALF 0.5   /**< half value */
#define SND_PCM_PLUGIN_ROUTE_FULL 1.0   /**< full value */
#else
/** route ttable entry type */
typedef int snd_pcm_route_ttable_entry_t;
#define SND_PCM_PLUGIN_ROUTE_HALF (SND_PCM_PLUGIN_ROUTE_RESOLUTION / 2) /**< half value */
#define SND_PCM_PLUGIN_ROUTE_FULL SND_PCM_PLUGIN_ROUTE_RESOLUTION   /**< full value */
#endif

typedef struct {
    const char *pcm;
    int channels;
} snd_pcm_route_slave_config_t;

typedef struct {
    int cchannel;
    int schannel;
#if SND_PCM_PLUGIN_ROUTE_FLOAT
    float route_value;
#else
    int route_value;
#endif
} snd_pcm_route_ttable_config_t;

typedef struct {
    const char *type;
    snd_pcm_route_slave_config_t slave;
    snd_pcm_route_ttable_config_t ttable[];
} snd_pcm_route_config_t;

#define TTABLE_CONFIG_END {-1, -1, 0}

static inline int snd_pcm_route_is_ttable_config_end(const snd_pcm_route_ttable_config_t *entry)
{
    if (entry->cchannel == -1 && entry->schannel == -1)
        return 1;
    return 0;
}

#endif /* __AW_ALSA_PCM_ROUTE_H */
