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
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <tinatest.h>
#include <stdio.h>
#include <aw-alsa-lib/pcm.h>
#include <aw-alsa-lib/control.h>
#include <aw-alsa-lib/common.h>
#include <sound/card.h>

#define AW_ALSA_LIB_TEST_BEGIN()    printf("##### %s BEGIN #####\n", __func__)
#define AW_ALSA_LIB_TEST_END()      printf("##### %s END #####\n", __func__)
#define AW_ALSA_LIB_TEST_OK()       printf("##### %s Successful #####\n", __func__)
#define AW_ALSA_LIB_TEST_FAILED()   printf("##### %s Failed #####\n", __func__)

static int card_info_test(int argc, char *argv[])
{
    int i, ret = 0;

    AW_ALSA_LIB_TEST_BEGIN();
    ret = snd_card_num();
    if (ret < 0) {
        printf("no registered card...\n");
        goto err;
    }
    printf("Card list:\n");
    printf("%8s%20s\n", "card_num", "card_name");
    for (i = 0; i < ret; i++) {
        if (i != snd_card_index(snd_card_name(i))) {
            printf("card_num%d not equal index convert"
                "from name:%s\n", i, snd_card_name(i));
            ret = -1;
            goto err;
        }
        printf("%8d%20s\n", i, snd_card_name(i));
    }
    printf("\n");

    AW_ALSA_LIB_TEST_END();
    AW_ALSA_LIB_TEST_OK();
    return ret;
err:
    AW_ALSA_LIB_TEST_FAILED();
    return ret;
}

extern int sunxi_soundcard_init(void);
static int card_register_test(int argc, char *argv[])
{
    int ret = 0;
    AW_ALSA_LIB_TEST_BEGIN();

    ret = sunxi_soundcard_init();
    if (ret != 0) {
        printf("card register test failed\n");
        goto err;
    }
    AW_ALSA_LIB_TEST_END();
    AW_ALSA_LIB_TEST_OK();
    return ret;
err:
    AW_ALSA_LIB_TEST_FAILED();
    return ret;
}
static int card_unregister_test(int argc, char *argv[])
{
    int ret = 0;
    AW_ALSA_LIB_TEST_BEGIN();

    ret = snd_card_unregister_all();
    if (ret != 0) {
        printf("card unregister test failed\n");
        goto err;
    }
    AW_ALSA_LIB_TEST_END();
    AW_ALSA_LIB_TEST_OK();
    return ret;
err:
    AW_ALSA_LIB_TEST_FAILED();
    return ret;
}

static int card_register_unregister_test(int argc, char *argv[])
{
    int ret = 0;
    int count = 0, loop = 100;

    AW_ALSA_LIB_TEST_BEGIN();
    if (argc >= 2)
        loop = atoi(argv[1]);

    snd_card_unregister_all();
    printf("register/unregister card loop %d times...\n", loop);
    for (count = 0; count < loop; count++) {
        ret = sunxi_soundcard_init();
        if (ret != 0) {
            printf("card register failed, loop count:%d\n", count);
            goto err;
        }
        ret = snd_card_unregister_all();
        if (ret != 0) {
            printf("card unregister failed, loop count:%d\n", count);
            goto err;
        }
    }
    sunxi_soundcard_init();

    AW_ALSA_LIB_TEST_END();
    AW_ALSA_LIB_TEST_OK();
    return ret;
err:
    AW_ALSA_LIB_TEST_FAILED();
}

struct {
    int stream;
    snd_pcm_format_t format;
    unsigned int channels, rate;
    snd_pcm_uframes_t period_frames, buffer_frames;
    unsigned int periods, period_time;
} g_hw_params = {
    .stream     = SND_PCM_STREAM_PLAYBACK,
    .format     = SND_PCM_FORMAT_S16_LE,
    .channels   = 2,
    .rate       = 16000,
    .period_time    = 100000,
    .period_frames  = 512,
    .buffer_frames  = 4096,
    .periods    = 4,
};
struct {
    snd_pcm_uframes_t start_threshold;
    snd_pcm_uframes_t stop_threshold;
    snd_pcm_uframes_t avail_min;
} g_sw_params = {
    .start_threshold = 0,
    .stop_threshold  = 4096,
    .avail_min       = 512,
};


static int open_close_test(int argc, char *argv[])
{
    int ret = 0;

    snd_pcm_t *handle = NULL;
    AW_ALSA_LIB_TEST_BEGIN();
    ret = snd_pcm_open(&handle, "default", g_hw_params.stream, 0);
    if (ret < 0) {
        printf("snd_pcm_open %s failed\n",
            (g_hw_params.stream == SND_PCM_STREAM_PLAYBACK) ?
            "playback" : "capture");
        goto err;
    }

    ret = snd_pcm_close(handle);
    if (ret < 0) {
        printf("snd_pcm_close %s failed\n",
            (g_hw_params.stream == SND_PCM_STREAM_PLAYBACK) ?
            "playback" : "capture");
        goto err;
    }
    AW_ALSA_LIB_TEST_END();

    AW_ALSA_LIB_TEST_OK();
    return 0;
err:
    if (handle != NULL)
        snd_pcm_close(handle);
    AW_ALSA_LIB_TEST_FAILED();
    return ret;
}

static int play_open_close(int argc, char *argv[])
{
    g_hw_params.stream = SND_PCM_STREAM_PLAYBACK;
    return open_close_test(0, NULL);
}

static int capture_open_close(int argc, char *argv[])
{
    g_hw_params.stream = SND_PCM_STREAM_CAPTURE;
    return open_close_test(0, NULL);
}


static int hw_params_test(int argc, char *argv[])
{
    int ret = 0;
    snd_pcm_t *handle = NULL;
    snd_pcm_hw_params_t *params = NULL;
    snd_pcm_format_t format;
    unsigned int channels, rate;
    snd_pcm_uframes_t period_frames, buffer_frames;
    unsigned int periods, period_time;

    AW_ALSA_LIB_TEST_BEGIN();

    snd_pcm_open(&handle, "audiocodec", g_hw_params.stream, 0);

    snd_pcm_hw_params_alloca(&params);
    ret = snd_pcm_hw_params_any(handle, params);
    if (ret < 0) {
        printf("no configurations available\n");
        goto err;
    }

    printf("Setting:\n");
    printf("format             = %u\n", g_hw_params.format);
    printf("channels           = %u\n", g_hw_params.channels);
    printf("rate               = %u\n", g_hw_params.rate);
    printf("period_frames      = %u\n", g_hw_params.period_frames);
    printf("buffer_frames      = %u\n", g_hw_params.buffer_frames);
    printf("period_time        = %u\n", g_hw_params.period_time);
    printf("periods            = %u\n", g_hw_params.periods);
    printf("\n");
    snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(handle, params, g_hw_params.format);
    snd_pcm_hw_params_set_channels(handle, params, g_hw_params.channels);
    snd_pcm_hw_params_set_rate(handle, params, g_hw_params.rate, 0);
    if (g_hw_params.period_frames != 0)
        snd_pcm_hw_params_set_period_size(handle, params, g_hw_params.period_frames, 0);
    else if (g_hw_params.period_time != 0)
        snd_pcm_hw_params_set_period_time(handle, params, g_hw_params.period_time, 0);
    if (g_hw_params.buffer_frames != 0)
        snd_pcm_hw_params_set_buffer_size(handle, params, g_hw_params.buffer_frames);
    else if (g_hw_params.periods != 0)
        snd_pcm_hw_params_set_periods(handle, params, g_hw_params.periods, 0);
    ret = snd_pcm_hw_params(handle, params);
    if (ret < 0) {
        printf("Unable to install hw prams!\n");
        goto err;
    }
    snd_pcm_hw_params_get_format(params, &format);
    snd_pcm_hw_params_get_channels(params, &channels);
    snd_pcm_hw_params_get_rate(params, &rate, 0);
    snd_pcm_hw_params_get_period_size(params, &period_frames, 0);
    snd_pcm_hw_params_get_buffer_size(params, &buffer_frames);
    snd_pcm_hw_params_get_period_time(params, &period_time, 0);
    snd_pcm_hw_params_get_periods(params, &periods, 0);

    printf("After Setting:\n");
    printf("format             = %u\n", format);
    printf("channels           = %u\n", channels);
    printf("rate               = %u\n", rate);
    printf("period_frames      = %u\n", period_frames);
    printf("buffer_frames      = %u\n", buffer_frames);
    printf("period_time        = %u\n", period_time);
    printf("periods            = %u\n", periods);

    snd_pcm_close(handle);
    AW_ALSA_LIB_TEST_END();
    AW_ALSA_LIB_TEST_OK();
    return ret;
err:
    snd_pcm_close(handle);
    AW_ALSA_LIB_TEST_FAILED();
    return ret;
}

#define hw_params_test_detail(type) \
    int i; \
    for (i = 0; i < ARRAY_SIZE(type##_array); i++) { \
        printf(#type" %u test:\n", type##_array[i]); \
        g_hw_params.type = type##_array[i]; \
        ret = hw_params_test(0, NULL); \
        if (ret < 0) { \
            printf(#type" %u test failed\n", type##_array[i]); \
            goto err; \
        } \
    }

static int hw_params_format(int argc, char *argv[])
{
    int ret = 0;
    snd_pcm_format_t format_bak = g_hw_params.format;
    snd_pcm_format_t format_array[] = {
        SND_PCM_FORMAT_S16_LE,
        SND_PCM_FORMAT_S24_LE,
    };
    hw_params_test_detail(format);
err:
    g_hw_params.format = format_bak;
    return ret;
}

static int hw_params_channels(int argc, char *argv[])
{
    int ret = 0;
    unsigned int channels_bak = g_hw_params.channels;
    unsigned int channels_array[] = {
        1,2,3,4,5
    };

    hw_params_test_detail(channels);
err:
    g_hw_params.channels = channels_bak;
    return ret;
}

static int hw_params_rate(int argc, char *argv[])
{
    int ret = 0;
    unsigned int rate_bak = g_hw_params.rate;
    unsigned int rate_array[] = {
        8000,16000,48000,44100,
    };

    hw_params_test_detail(rate);
err:
    g_hw_params.rate = rate_bak;
    return ret;
}

static int hw_params_period_size(int argc, char *argv[])
{
    int ret = 0;
    unsigned int period_frames_bak = g_hw_params.period_frames;
    unsigned int buffer_frames_bak = g_hw_params.buffer_frames;
    unsigned int period_time_bak = g_hw_params.period_time;
    unsigned int period_frames_array[] = {
        256,512,1024,2048,
    };
    g_hw_params.period_time = 0;
    g_hw_params.buffer_frames = 0;

    hw_params_test_detail(period_frames);
err:
    g_hw_params.period_frames = period_frames_bak;
    g_hw_params.buffer_frames = buffer_frames_bak;
    g_hw_params.period_time = period_time_bak;
    return ret;
}

static int hw_params_period_time(int argc, char *argv[])
{
    int ret = 0;
    unsigned int period_frames_bak = g_hw_params.period_frames;
    unsigned int buffer_frames_bak = g_hw_params.buffer_frames;
    unsigned int period_time_bak = g_hw_params.period_time;
    unsigned int period_time_array[] = {
        50000,70000,100000,
    };
    g_hw_params.period_frames = 0;
    g_hw_params.buffer_frames = 0;

    hw_params_test_detail(period_time);
err:
    g_hw_params.period_frames = period_frames_bak;
    g_hw_params.buffer_frames = buffer_frames_bak;
    g_hw_params.period_time = period_time_bak;
    return ret;
}

static int hw_params_buffer_size(int argc, char *argv[])
{
    int ret = 0;
    unsigned int buffer_frames_bak = g_hw_params.buffer_frames;
    unsigned int periods_bak = g_hw_params.periods;
    unsigned int buffer_frames_array[] = {
        1024,2048,4096,
    };

    g_hw_params.periods = 0;
    hw_params_test_detail(buffer_frames);
err:
    g_hw_params.buffer_frames = buffer_frames_bak;
    g_hw_params.periods = periods_bak;
    return ret;
}

static int hw_params_periods(int argc, char *argv[])
{
    int ret = 0;
    unsigned int buffer_frames_bak = g_hw_params.buffer_frames;
    unsigned int periods_bak = g_hw_params.periods;
    unsigned int periods_array[] = {
        2,3,4,5,6,7,8,
    };

    g_hw_params.buffer_frames = 0;
    hw_params_test_detail(periods);
err:
    g_hw_params.buffer_frames = buffer_frames_bak;
    g_hw_params.periods = periods_bak;
    return ret;
}

static int sw_params_test(int argc, char *argv[])
{
    int ret = 0;
    snd_pcm_t *handle = NULL;
    snd_pcm_sw_params_t *sw_params = NULL;
    snd_pcm_hw_params_t *params = NULL;
    snd_pcm_format_t format;
    unsigned int channels, rate;
    snd_pcm_uframes_t period_frames, buffer_frames;
    snd_pcm_uframes_t start_threshold;
    snd_pcm_uframes_t stop_threshold;
    snd_pcm_uframes_t avail_min;

    AW_ALSA_LIB_TEST_BEGIN();

    snd_pcm_open(&handle, "audiocodec", g_hw_params.stream, 0);

    snd_pcm_hw_params_alloca(&params);
    ret = snd_pcm_hw_params_any(handle, params);
    if (ret < 0) {
        printf("no configurations available\n");
        goto err;
    }

    printf("HW Setting:\n");
    printf("format             = %u\n", g_hw_params.format);
    printf("channels           = %u\n", g_hw_params.channels);
    printf("rate               = %u\n", g_hw_params.rate);
    printf("period_frames      = %u\n", g_hw_params.period_frames);
    printf("buffer_frames      = %u\n", g_hw_params.buffer_frames);
    printf("\n");
    snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(handle, params, g_hw_params.format);
    snd_pcm_hw_params_set_channels(handle, params, g_hw_params.channels);
    snd_pcm_hw_params_set_rate(handle, params, g_hw_params.rate, 0);
    snd_pcm_hw_params_set_period_size(handle, params, g_hw_params.period_frames, 0);
    snd_pcm_hw_params_set_buffer_size(handle, params, g_hw_params.buffer_frames);
    ret = snd_pcm_hw_params(handle, params);
    if (ret < 0) {
        printf("Unable to install hw prams!\n");
        goto err;
    }

    printf("SW Setting:\n");
    printf("start_threshold    = %u\n", g_sw_params.start_threshold);
    printf("stop_threshold     = %u\n", g_sw_params.stop_threshold);
    printf("avail_min          = %u\n", g_sw_params.avail_min);
    printf("\n");
    snd_pcm_sw_params_alloca(&sw_params);
    snd_pcm_sw_params_current(handle, sw_params);
    if (g_sw_params.start_threshold == 0) {
        snd_pcm_sw_params_set_start_threshold(handle,
            sw_params, (g_hw_params.stream == SND_PCM_STREAM_PLAYBACK) ?
            g_hw_params.period_frames : 1);
    } else {
        snd_pcm_sw_params_set_start_threshold(handle, sw_params, g_sw_params.start_threshold);
    }
    snd_pcm_sw_params_set_stop_threshold(handle, sw_params, g_sw_params.stop_threshold);
    snd_pcm_sw_params_set_avail_min(handle, sw_params, g_sw_params.avail_min);
    ret = snd_pcm_sw_params(handle ,sw_params);
    if (ret < 0) {
        printf("Unable to install sw prams!\n");
        goto err;
    }

    snd_pcm_hw_params_get_format(params, &format);
    snd_pcm_hw_params_get_channels(params, &channels);
    snd_pcm_hw_params_get_rate(params, &rate, 0);
    snd_pcm_hw_params_get_period_size(params, &period_frames, 0);
    snd_pcm_hw_params_get_buffer_size(params, &buffer_frames);

    snd_pcm_sw_params_get_start_threshold(sw_params, &start_threshold);
    snd_pcm_sw_params_get_stop_threshold(sw_params, &stop_threshold);
    snd_pcm_sw_params_get_avail_min(sw_params, &avail_min);

    printf("After Setting:\n");
    printf("format             = %u\n", format);
    printf("channels           = %u\n", channels);
    printf("rate               = %u\n", rate);
    printf("period_frames      = %u\n", period_frames);
    printf("buffer_frames      = %u\n", buffer_frames);
    printf("start_threshold    = %u\n", start_threshold);
    printf("stop_threshold     = %u\n", stop_threshold);
    printf("avail_min          = %u\n", avail_min);

    snd_pcm_close(handle);
    AW_ALSA_LIB_TEST_END();
    AW_ALSA_LIB_TEST_OK();
    return ret;
err:
    snd_pcm_close(handle);
    AW_ALSA_LIB_TEST_FAILED();
    return ret;
}

#define sw_params_test_detail(type) \
    int i; \
    for (i = 0; i < ARRAY_SIZE(type##_array); i++) { \
        printf(#type" %u test:\n", type##_array[i]); \
        g_sw_params.type = type##_array[i]; \
        ret = sw_params_test(0, NULL); \
        if (ret < 0) { \
            printf(#type" %u test failed\n", type##_array[i]); \
            goto err; \
        } \
    }
static int sw_params_start_threshold(int argc, char *argv[])
{
    int ret = 0;
    snd_pcm_uframes_t start_threshold_bak = g_sw_params.start_threshold;
    snd_pcm_uframes_t start_threshold_array[] = {
        1, 256, 512, 1024,
    };

    sw_params_test_detail(start_threshold);
err:
    g_sw_params.start_threshold = start_threshold_bak;
    return ret;
}

static int sw_params_stop_threshold(int argc, char *argv[])
{
    int ret = 0;
    snd_pcm_uframes_t stop_threshold_bak = g_sw_params.stop_threshold;
    snd_pcm_uframes_t stop_threshold_array[] = {
        512, 1024, 2048, 4096, 8192,
    };

    sw_params_test_detail(stop_threshold);
err:
    g_sw_params.stop_threshold = stop_threshold_bak;
    return ret;
}

static int sw_params_avail_min(int argc, char *argv[])
{
    int ret = 0;
    snd_pcm_uframes_t avail_min_bak = g_sw_params.avail_min;
    snd_pcm_uframes_t avail_min_array[] = {
        512, 1024, 2048
    };

    sw_params_test_detail(avail_min);
err:
    g_sw_params.avail_min = avail_min_bak;
    return ret;
}

static int pcm_state_test(int argc, char *argv[])
{
    int ret = 0;
    snd_pcm_t *handle = NULL;
    snd_pcm_sw_params_t *sw_params = NULL;
    snd_pcm_hw_params_t *params = NULL;
    snd_pcm_state_t state = -1;
    snd_pcm_uframes_t boundary = 0;
    snd_pcm_sframes_t delay = 0;

    /* open, setup, prepare, running, pause, drain */
    AW_ALSA_LIB_TEST_BEGIN();

    snd_pcm_open(&handle, "audiocodec", SND_PCM_STREAM_PLAYBACK, 0);
    state = snd_pcm_state(handle);
    printf("After snd_pcm_open, state is %d\n", state);

    snd_pcm_hw_params_alloca(&params);
    ret = snd_pcm_hw_params_any(handle, params);
    if (ret < 0) {
        printf("no configurations available\n");
        goto err;
    }

    snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(handle, params, g_hw_params.format);
    snd_pcm_hw_params_set_channels(handle, params, g_hw_params.channels);
    snd_pcm_hw_params_set_rate(handle, params, g_hw_params.rate, 0);
    snd_pcm_hw_params_set_period_size(handle, params, g_hw_params.period_frames, 0);
    snd_pcm_hw_params_set_periods(handle, params, g_hw_params.periods, 0);

    ret = snd_pcm_hw_params(handle, params);
    if (ret < 0) {
        printf("Unable to install hw prams!\n");
        goto err;
    }
    state = snd_pcm_state(handle);
    /* alsalib snd_pcm_hw_params alsa perform snd_pcm_prepare */
    printf("After snd_pcm_hw_params, state is %d\n", state);

    snd_pcm_sw_params_alloca(&sw_params);
    snd_pcm_sw_params_current(handle, sw_params);

    snd_pcm_sw_params_get_boundary(sw_params, &boundary);
    snd_pcm_sw_params_set_start_threshold(handle, sw_params, g_hw_params.period_frames);
    snd_pcm_sw_params_set_avail_min(handle, sw_params, g_sw_params.avail_min);
    snd_pcm_sw_params_set_stop_threshold(handle, sw_params, boundary);
    snd_pcm_sw_params_set_silence_size(handle, sw_params, boundary);

    ret = snd_pcm_sw_params(handle ,sw_params);
    if (ret < 0) {
        printf("Unable to install sw prams!\n");
        goto err;
    }

    snd_pcm_start(handle);
    state = snd_pcm_state(handle);
    printf("After snd_pcm_start, state is %d\n", state);

    hal_usleep(100000);
    ret = snd_pcm_delay(handle, &delay);
    if (ret < 0)
        printf("snd_pcm_delay failed, return %d\n", delay);
    printf("pcm delay:%d\n", delay);
    hal_usleep(100000);
    ret = snd_pcm_delay(handle, &delay);
    if (ret < 0)
        printf("snd_pcm_delay failed, return %d\n", delay);
    printf("pcm delay:%d\n", delay);
    hal_usleep(200000);
    ret = snd_pcm_delay(handle, &delay);
    if (ret < 0)
        printf("snd_pcm_delay failed, return %d\n", delay);
    printf("pcm delay:%d\n", delay);

    ret = snd_pcm_hw_params_can_pause(params);
    printf("%sSupport pause...\n", ret ? "" : "Can't ");

    snd_pcm_pause(handle, 1);
    state = snd_pcm_state(handle);
    printf("After snd_pcm_pause push, state is %d\n", state);
#if 1
    snd_pcm_pause(handle, 0);
    state = snd_pcm_state(handle);
    printf("After snd_pcm_pause release, state is %d\n", state);
#endif

#if 1
    snd_pcm_drain(handle);
    state = snd_pcm_state(handle);
    printf("After snd_pcm_drain, state is %d\n", state);
#endif
#if 0
    snd_pcm_drop(handle);
    state = snd_pcm_state(handle);
    printf("After snd_pcm_drop, state is %d\n", state);
#endif

    snd_pcm_close(handle);
    AW_ALSA_LIB_TEST_END();
    AW_ALSA_LIB_TEST_OK();
    return ret;
err:
    snd_pcm_close(handle);
    AW_ALSA_LIB_TEST_FAILED();
    return ret;
}

static int ctl_info_test(int argc, char *argv[])
{
    int num, i, ret = 0;
    snd_ctl_info_t info;

    AW_ALSA_LIB_TEST_BEGIN();
    num = snd_ctl_num("audiocodec");
    if (num <= 0)
        goto err;

    for (i = 0; i < num;i ++) {
        memset(&info, 0, sizeof(snd_ctl_info_t));
        ret = snd_ctl_get_bynum("audiocodec", i, &info);
        if (ret < 0) {
            printf("get %d elem failed\n", i);
            goto err;
        }
        printf("numid=%u, name=\'%s\'\n", info.id, info.name);
        printf("value=%u, min=%u, max=%u\n",
                info.value, info.min, info.max);
    }
    AW_ALSA_LIB_TEST_END();
    AW_ALSA_LIB_TEST_OK();
    return ret;
err:
    AW_ALSA_LIB_TEST_FAILED();
    return ret;
}

static int ctl_get_test(int argc, char *argv[])
{
    int ret = 0;
    int numid = 0;
    snd_ctl_info_t info0, info1;

    AW_ALSA_LIB_TEST_BEGIN();
    ret = snd_ctl_get_bynum("audiocodec", numid, &info0);
    if (ret < 0) {
        printf("get %d elem failed\n", numid);
        goto err;
    }
    ret = snd_ctl_get("audiocodec", info0.name, &info1);
    if (ret < 0) {
        printf("get %s elem failed\n", info0.name);
        goto err;
    }

    if (info0.id != info1.id) {
        printf("info id not equal. something error...\n");
        goto err;
    }

    AW_ALSA_LIB_TEST_END();
    AW_ALSA_LIB_TEST_OK();
    return ret;
err:
    AW_ALSA_LIB_TEST_FAILED();
    return ret;
}

static int ctl_set_test(int argc, char *argv[])
{
    int ret = 0;
    int numid = 0;
    snd_ctl_info_t info0, info1;

    AW_ALSA_LIB_TEST_BEGIN();
    ret = snd_ctl_get_bynum("audiocodec", numid, &info0);
    if (ret < 0) {
        printf("get %d elem failed\n", numid);
        goto err;
    }
    ret = snd_ctl_set_bynum("audiocodec", info0.id, !info0.value);
    if (ret < 0) {
        printf("set %d elem failed\n", numid);
        goto err;
    }

    ret = snd_ctl_get_bynum("audiocodec", numid, &info1);
    if (ret < 0) {
        printf("get %d elem failed\n", numid);
        goto err;
    }

    if (info0.value == info1.value) {
        printf("info id equal. something error...\n");
        goto err;
    }
    /* recover ctl elem value */
    snd_ctl_set("audiocodec", info0.name, info0.value);

    AW_ALSA_LIB_TEST_END();
    AW_ALSA_LIB_TEST_OK();
    return ret;
err:
    AW_ALSA_LIB_TEST_FAILED();
    return ret;
}

static int ctl_add_test(int argc, char *argv[])
{
    int ret;
    snd_ctl_info_t info0 = {
        .name   = "Ctl Test 0",
        .value  = 3,
        .min    = 0,
        .max    = 100,
    };
    unsigned long array[3] = {5, 6, 7};
    snd_ctl_info_t info1 = {
        .name       = "Ctl Test 1",
        .min        = 1,
        .max        = 10,
        .count      = ARRAY_SIZE(array),
        .private_data   = array,
    };
    snd_ctl_info_t info;

    AW_ALSA_LIB_TEST_BEGIN();
    ret = snd_ctl_add("audiocodec", &info0);
    if (ret < 0) {
        printf("add ctl info0 failed\n");
        goto err;
    }
    ret = snd_ctl_add("audiocodec", &info1);
    if (ret < 0) {
        printf("add ctl info1 failed\n");
        goto err;
    }

    ret = snd_ctl_get("audiocodec", info0.name, &info);
    if (ret < 0) {
        printf("get %s elem failed\n", info0.name);
        goto err;
    }
    printf("info0 numid=%d, name:%s\n", info.id, info.name);
    printf("value=%d, min=%d, max=%d\n", info.value, info.min, info.max);
    printf("\n");

    printf("try to set value 1\n");
    ret = snd_ctl_set("audiocodec", info.name, 1);
    if (ret < 0) {
        printf("set %s elem failed\n", info.name);
        goto err;
    }

    ret = snd_ctl_set_multi_args("audiocodec", info1.name, 3, 7, 8, 9);
    if (ret < 0) {
        printf("set %s elem failed\n", info1.name);
        goto err;
    }

    ret = snd_ctl_get("audiocodec", info1.name, &info);
    if (ret < 0) {
        printf("get %s elem failed\n", info0.name);
        goto err;
    }
    printf("info0 numid=%d, name:%s\n", info.id, info.name);
    printf("value=%d, min=%d, max=%d\n", info.value, info.min, info.max);
    if (info.count > 1) {
        int i;
        for (i = 0; i < info.count; i++)
            printf("value[%d]=%lu ", i, info.private_data[i]);
        printf("\n");
    }
    printf("\n");

    AW_ALSA_LIB_TEST_END();
    AW_ALSA_LIB_TEST_OK();
    return ret;
err:
    AW_ALSA_LIB_TEST_FAILED();
    return ret;
}

static int ctl_remove_test(int argc, char *argv[])
{
    int ret;
    snd_ctl_info_t info = {
        .name   = "Ctl Remove Test",
        .value  = 1,
        .min    = 0,
        .max    = 1,
    };
    snd_ctl_info_t info_read;

    AW_ALSA_LIB_TEST_BEGIN();
    ret = snd_ctl_add("audiocodec", &info);
    if (ret < 0) {
        printf("add ctl info0 failed\n");
        goto err;
    }

    ret = snd_ctl_get("audiocodec", info.name, &info_read);
    if (ret < 0) {
        printf("get %s elem failed\n", info.name);
        goto err;
    }

    ret = snd_ctl_remove("audiocodec", info_read.id);
    if (ret != 0) {
        printf("ctl remove failed\n");
        goto err;
    }

    AW_ALSA_LIB_TEST_END();
    AW_ALSA_LIB_TEST_OK();
    return ret;
err:
    AW_ALSA_LIB_TEST_FAILED();
    return ret;

}

tt_funclist_t tt_alsalib_funclist[] = {
    {"card info",               card_info_test},
    {"card register",           card_register_test},
    {"card unregister",             card_unregister_test},
    {"card register/unregister loop",   card_register_unregister_test},
    {"play_open_close",         play_open_close},
    {"capture_open_close",          capture_open_close},
    {"hw_params",               hw_params_test},
    {"format",              hw_params_format},
    {"channels",                hw_params_channels},
    {"rate",                hw_params_rate},
    {"period_size",             hw_params_period_size},
    {"period_time",             hw_params_period_time},
    {"buffer_size",             hw_params_buffer_size},
    {"periods",             hw_params_periods},
    {"sw_params",               sw_params_test},
    {"start_threshold",         sw_params_start_threshold},
    {"stop_threshold",          sw_params_stop_threshold},
    {"avail_min",               sw_params_avail_min},
    {"pcm state",               pcm_state_test},
    {"ctl info",                ctl_info_test},
    {"ctl get",                 ctl_get_test},
    {"ctl set",                 ctl_set_test},
    {"ctl add",                 ctl_add_test},
    {"ctl remove",              ctl_remove_test},
};

testcase_init_with_funclist(tt_alsalib_funclist, alsalib, aw alsa lib api test);
