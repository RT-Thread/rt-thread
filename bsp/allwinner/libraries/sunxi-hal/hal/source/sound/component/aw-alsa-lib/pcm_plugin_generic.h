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

#ifndef __AW_ALSA_PCM_PLUGIN_GENERIC_H
#define __AW_ALSA_PCM_PLUGIN_GENERIC_H

#include "pcm_generic.h"

typedef snd_pcm_uframes_t (*snd_pcm_slave_xfer_areas_func_t)
    (snd_pcm_t *pcm,
    const snd_pcm_channel_area_t *areas, snd_pcm_uframes_t offset,
    snd_pcm_uframes_t size,
    const snd_pcm_channel_area_t *slave_areas,
    snd_pcm_uframes_t slave_offset,
    snd_pcm_uframes_t *slave_sizep);

typedef snd_pcm_sframes_t (*snd_pcm_slave_xfer_areas_undo_func_t)
    (snd_pcm_t *pcm,
    const snd_pcm_channel_area_t *res_areas,    /* result areas */
    snd_pcm_uframes_t res_offset,       /* offset of result areas */
    snd_pcm_uframes_t res_size,     /* size of result areas */
    snd_pcm_uframes_t slave_undo_size);

typedef struct {
    snd_pcm_generic_t gen;
    snd_pcm_slave_xfer_areas_func_t read;
    snd_pcm_slave_xfer_areas_func_t write;
    snd_pcm_slave_xfer_areas_undo_func_t undo_read;
    snd_pcm_slave_xfer_areas_undo_func_t undo_write;
    int (*init)(snd_pcm_t *pcm);
    snd_pcm_uframes_t appl_ptr, hw_ptr;
} snd_pcm_plugin_t;

void snd_pcm_plugin_init(snd_pcm_plugin_t *plugin);
int snd_pcm_plugin_may_wait_for_avail_min(snd_pcm_t *pcm, snd_pcm_uframes_t avail);
int snd_pcm_plugin_wait(snd_pcm_t *pcm, int timeout);

extern const snd_pcm_fast_ops_t snd_pcm_plugin_fast_ops;

snd_pcm_sframes_t snd_pcm_plugin_undo_read_generic
     (snd_pcm_t *pcm,
      const snd_pcm_channel_area_t *res_areas,  /* result areas */
      snd_pcm_uframes_t res_offset,     /* offset of result areas */
      snd_pcm_uframes_t res_size,       /* size of result areas */
      snd_pcm_uframes_t slave_undo_size);

snd_pcm_sframes_t snd_pcm_plugin_undo_write_generic
     (snd_pcm_t *pcm,
      const snd_pcm_channel_area_t *res_areas,  /* result areas */
      snd_pcm_uframes_t res_offset,     /* offset of result areas */
      snd_pcm_uframes_t res_size,       /* size of result areas */
      snd_pcm_uframes_t slave_undo_size);

int snd_pcm_linear_get_index(snd_pcm_format_t src_format, snd_pcm_format_t dst_format);
int snd_pcm_linear_put_index(snd_pcm_format_t src_format, snd_pcm_format_t dst_format);
int snd_pcm_linear_convert_index(snd_pcm_format_t src_format, snd_pcm_format_t dst_format);

#endif /* __AW_ALSA_PCM_PLUGIN_GENERIC_H */
