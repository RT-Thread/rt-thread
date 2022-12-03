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
#include <unistd.h>
#include <stdlib.h>
//#include <FreeRTOS.h>
#include <aw-alsa-lib/pcm.h>
#include "common.h"
#include <hal_timer.h>

unsigned int g_verbose = 0;

int set_param(snd_pcm_t *handle, snd_pcm_format_t format,
            unsigned int rate, unsigned int channels,
            snd_pcm_uframes_t period_size,
            snd_pcm_uframes_t buffer_size)
{
    int ret = 0;
    snd_pcm_hw_params_t *params;
    snd_pcm_sw_params_t *sw_params;
    snd_pcm_uframes_t period_size_tmp = period_size;
    snd_pcm_uframes_t buffer_size_tmp = buffer_size;

    /* HW params */
    snd_pcm_hw_params_alloca(&params);
    ret =  snd_pcm_hw_params_any(handle, params);
    if (ret < 0) {
        printf("no configurations available\n");
        return ret;
    }
    ret = snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    if (ret < 0) {
        printf("failed to set access\n");
        return ret;
    }
    ret = snd_pcm_hw_params_set_format(handle, params, format);
    if (ret < 0) {
        printf("failed to set format\n");
        return ret;
    }
    ret = snd_pcm_hw_params_set_channels(handle, params, channels);
    if (ret < 0) {
        printf("failed to set channels\n");
        return ret;
    }
    ret = snd_pcm_hw_params_set_rate(handle, params, rate, 0);
    if (ret < 0) {
        printf("failed to set rate\n");
        return ret;
    }

    ret = snd_pcm_hw_params_set_period_size_near(handle, params, &period_size_tmp, NULL);
    if (ret < 0) {
        printf("failed to set period size\n");
        return ret;
    }
    if (period_size_tmp != period_size) {
        printf("period size changed (request: %lu, get: %lu)\n",
                period_size, period_size_tmp);
        period_size = period_size_tmp;
    }
    ret = snd_pcm_hw_params_set_buffer_size_near(handle, params, &buffer_size_tmp);
    if (ret < 0) {
        printf("failed to set buffer size\n");
        return ret;
    }
    if (buffer_size_tmp != buffer_size) {
        printf("buffer size changed (request: %lu, get: %lu)\n",
                buffer_size, buffer_size_tmp);
        buffer_size = buffer_size_tmp;
    }
    ret = snd_pcm_hw_params(handle, params);
    if (ret < 0) {
        printf("Unable to install hw prams! (return: %d)\n", ret);
        return ret;
    }

    /* SW params */
    snd_pcm_sw_params_alloca(&sw_params);
    snd_pcm_sw_params_current(handle, sw_params);
    if (snd_pcm_stream(handle) == SND_PCM_STREAM_CAPTURE) {
        snd_pcm_sw_params_set_start_threshold(handle, sw_params, 1);
    } else {
        snd_pcm_uframes_t boundary = 0;
        snd_pcm_sw_params_get_boundary(sw_params, &boundary);
        snd_pcm_sw_params_set_start_threshold(handle, sw_params, buffer_size);
        /* set silence size, in order to fill silence data into ringbuffer */
        snd_pcm_sw_params_set_silence_size(handle, sw_params, boundary);
    }
    snd_pcm_sw_params_set_stop_threshold(handle, sw_params, buffer_size);
    snd_pcm_sw_params_set_avail_min(handle, sw_params, period_size);
    ret = snd_pcm_sw_params(handle ,sw_params);
    if (ret < 0) {
        printf("Unable to install sw prams!\n");
        return ret;
    }

    if (g_verbose)
        snd_pcm_dump(handle);

    return ret;
}

void xrun(snd_pcm_t *handle)
{
    int ret;

    printf("Xrun...\n");
    ret = snd_pcm_prepare(handle);
    if (ret < 0) {
        printf("prepare failed in xrun. return %d\n", ret);
    }
}

void do_pause(snd_pcm_t *handle)
{
    int ret = 0;
    printf("[%s] line:%d pause start...\n", __func__, __LINE__);
    ret = snd_pcm_pause(handle, 1);
    if (ret < 0)
        printf("pause failed!, return %d\n", ret);
    hal_sleep(5);
    ret = snd_pcm_pause(handle, 0);
    if (ret < 0)
        printf("pause release failed!, return %d\n", ret);
    printf("[%s] line:%d pause end...\n", __func__, __LINE__);
}

void do_other_test(snd_pcm_t *handle)
{
    do_pause(handle);
    return;
}

audio_mgr_t *audio_mgr_create(void)
{
    audio_mgr_t *audio_mgr = NULL;

    audio_mgr = malloc(sizeof(audio_mgr_t));
    if (!audio_mgr) {
        printf("no memory\n");
        return NULL;
    }
    memset(audio_mgr, 0, sizeof(audio_mgr_t));
    audio_mgr->format = SND_PCM_FORMAT_S16_LE;
    audio_mgr->rate = 16000;
    audio_mgr->channels = 2;
    audio_mgr->period_size = 1024;
    audio_mgr->buffer_size = 4096;
    return audio_mgr;
}

void audio_mgr_release(audio_mgr_t *mgr)
{
    if (!mgr) {
        printf("%s: mgr null !\n", __func__);
        return;
    }
    free(mgr);
}
