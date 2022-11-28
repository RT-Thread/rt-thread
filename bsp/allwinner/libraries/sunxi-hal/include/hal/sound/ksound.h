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
#ifndef __SOUND_KSOUND_H
#define __SOUND_KSOUND_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pcm_common.h"

typedef struct snd_pcm_substream snd_pcm_substream_t;

/* pcm */
int ksnd_pcm_open(int card_num, int device_num, int stream, int mode, void **substream);
int ksnd_pcm_release(int card_num, int device_num, int stream);
int ksnd_pcm_hw_refine(void *substream, void *params);
int ksnd_pcm_prepare(void *substream_handle);
int ksnd_pcm_reset(void *substream_handle);
int ksnd_pcm_hw_params(void *substream_handle, void *params_wrapper);
int ksnd_pcm_hw_free(void *substream_handle);
snd_pcm_sframes_t ksnd_pcm_writei(void *substream_handle, const void *buffer, snd_pcm_uframes_t size);
snd_pcm_sframes_t ksnd_pcm_readi(void *substream_handle, void *buffer, snd_pcm_uframes_t size);
int ksnd_pcm_start(void *substream_handle);
int ksnd_pcm_drain(void *substream_handle);
int ksnd_pcm_drop(void *substream_handle);
int ksnd_pcm_pause(void *substream_handle, int enable);
int ksnd_pcm_sw_params(void *substream_handle, void *params_wrapper);
int ksnd_pcm_sync_ptr(void *substream_handle, void *status, void *control, unsigned int flags);
int ksnd_pcm_delay(void *substream_handle, void *delay);
int ksnd_pcm_channel_info(void *substream_handle, void *info_wrapper);
void ksnd_pcm_hw_mmap_dcache_update(void *substream_handle, snd_pcm_uframes_t offset,
        snd_pcm_uframes_t size);
int ksnd_pcm_wait(void *substream_handle, int index, int timeout);
int ksnd_pcm_rewind(snd_pcm_substream_t *substream, snd_pcm_uframes_t frames);
int ksnd_pcm_dsleep_init(void *substream_handle);
int ksnd_pcm_dsleep_release(void *substream_handle, int index);

/* ctl */
int ksnd_ctl_num(const char *name);
int ksnd_ctl_get(const char *name, const char *elem, void *info);
int ksnd_ctl_get_bynum(const char *name, const unsigned int elem_num, void *info);
int ksnd_ctl_set(const char *name, const char *elem, unsigned int val);
int ksnd_ctl_set_bynum(const char *name, const unsigned int elem_num, unsigned int val);
int ksnd_ctl_add_elem(const char *name, void *info);
int ksnd_ctl_remove_elem(const char *name, const unsigned int elem_num);

int ksnd_ctl_set_multi_args(const char *name, const char *elem, int num, ...);
#ifdef __cplusplus
}
#endif

#endif /* __SOUND_KSOUND_H */
