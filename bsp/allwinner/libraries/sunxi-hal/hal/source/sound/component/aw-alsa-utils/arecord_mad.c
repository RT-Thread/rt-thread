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
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <console.h>
#include <aw-alsa-lib/pcm.h>
#include <aw-alsa-lib/control.h>
#include <hal_cmd.h>

#include "common.h"
#include "wav_parser.h"

static char *g_pcm_name;
static char *g_ctl_name;
static unsigned int loop_count = 5;

#ifdef CONFIG_SUNXI_MAD_DEBUG
extern SemaphoreHandle_t mad_sleep;
extern int sunxi_mad_schd_timeout(SemaphoreHandle_t semaphore, long ms);
#endif

extern int aplay(const char *card_name, snd_pcm_format_t format, unsigned int rate,
            unsigned int channels, const char *data, unsigned int datalen);

static int pcm_read(snd_pcm_t *handle, const char *data, snd_pcm_uframes_t frames_total, unsigned int frame_bytes)
{
    int ret = 0;
    snd_pcm_sframes_t size;
    snd_pcm_uframes_t frames_loop = 400;
    snd_pcm_uframes_t frames_count = 0;
    snd_pcm_uframes_t frames = 0;
    unsigned int offset = 0;

    while (1) {
        if ((frames_total - frames_count) < frames_loop)
            frames = frames_total - frames_count;
        if (frames == 0)
            frames = frames_loop;
        size = snd_pcm_readi(handle, (void *)(data + offset), frames);
        if (size < 0)
            printf("snd_pcm_readi return %ld\n", size);
        if (size == -EAGAIN) {
            /* retry */
            usleep(10000);
            continue;
        } else if (size == -EPIPE) {
            xrun(handle);
            continue;
        } else if (size == -ESTRPIPE) {
            continue;
        } else if (size < 0) {
            printf("-----snd_pcm_readi failed!!, return %ld\n", size);
            ret = (int)size;
            goto err;
        }
        offset += (size * frame_bytes);
        frames_count += size;
        frames -= size;
        if (frames_total == frames_count)
            break;
        /*printf("frames_count = %ld, frames_total = %ld\n", frames_count, frames_total);*/
    }
err:
    return frames_count > 0 ? frames_count : ret;
}

static int amixer_sset_enum_ctl(const char *card_name, const char *ctl_name,
            const char *ctl_val)
{
    int num = 0;
    int ret = 0;
    int i= 0;
    int count = 0;
    snd_ctl_info_t info;

    if ((card_name == NULL) || (!strcmp(card_name, "default")))
        card_name = "audiocodec";

    ret = snd_ctl_get(card_name, ctl_name, &info);
    if (ret < 0) {
        printf("%s get %s elem failed\n", card_name, ctl_name);
        return ret;
    }

    if (info.type == SND_CTL_ELEM_TYPE_ENUMERATED) {
        for (i = 0; i < info.items; i++) {
            if (!strcmp(info.texts[i], ctl_val)) {
                ret = snd_ctl_set(card_name, ctl_name, i);
                if (ret < 0) {
                    printf("get %d elem failed\n", i);
                    return ret;
                }
                printf("[%s] %s set %d elem[%s] succeed.\n",
                    __func__, card_name, i, ctl_name);
                break;
            }
        }
    } else {
        printf("the %s ctl type of %s is not enum.\n", ctl_name, card_name);
    }
    return 0;
}

static int capture_then_play(audio_mgr_t *audio_mgr)
{
    char *capture_data = NULL;
    snd_pcm_t *handle;
    int mode = 0;
    int ret = 0;
    int fd = 0;
    unsigned int temp_wav_file_off = 0;
    unsigned int len = 0;
    char *path = "/data/rec_mad.pcm";
    struct stat statbuf;
    snd_pcm_uframes_t period_frames = 1024, buffer_frames = 4096;

    if (audio_mgr->capture_duration == 0)
        audio_mgr->capture_duration = 5;

    len = snd_pcm_format_size(audio_mgr->format,
            audio_mgr->capture_duration * audio_mgr->rate * audio_mgr->channels);
    capture_data = malloc(len);
    if (!capture_data) {
        printf("no memory\n");
        ret = -ENOMEM;
        goto err_malloc_capture_data;
    }

#ifdef CONFIG_SND_PLATFORM_SUNXI_MAD
    amixer_sset_enum_ctl(g_ctl_name, "bind mad function", "mad_bind");
#endif
    printf("\narecord start...\n");
    printf("dump args:\n");
    printf("card:      %s\n", g_pcm_name);
    printf("format:    %u\n", audio_mgr->format);
    printf("rate:      %u\n", audio_mgr->rate);
    printf("channels:  %u\n", audio_mgr->channels);
    printf("data:      %p\n", capture_data);
    printf("datalen:   %u\n", len);

    if (!stat(path, &statbuf)) {
        printf("have wav file:%s\n", path);
        if (S_ISREG(statbuf.st_mode)) {
            printf("remove wav file:%s\n", path);
            remove(path);
        }
    }
    if (!access(path, R_OK)) {
        printf("wav file:%s\n", path);
        fd = open(path, O_WRONLY | O_TRUNC);
        if (fd < 0) {
            printf("create wav file failed\n");
            goto err_fopen;
        }
    } else {
        printf("create wav file:%s\n", path);
        fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fd < 0) {
            printf("create wav file failed\n");
            goto err_fopen;
        }
    }

    /* open card */
    ret = snd_pcm_open(&handle, g_pcm_name, SND_PCM_STREAM_CAPTURE, mode);
    if (ret < 0) {
        printf("audio open error:%d\n", ret);
        ret = -EFAULT;
        goto err_pcm_open;
    }
    printf("pcm_set_param...\n");
    ret = set_param(handle, audio_mgr->format, audio_mgr->rate,
               audio_mgr->channels, period_frames, buffer_frames);
    if (ret < 0) {
        printf("audio set param error:%d\n", ret);
        ret = -EINVAL;
        goto err_set_param;
    }

    do {
        memset(capture_data, 0, len);

        ret = snd_pcm_prepare(handle);
        if (ret < 0) {
            printf("pcm_read error:%d\n", ret);
            goto err_pcm_prepare;
        }
        printf("pcm_read start...\n");
        ret = pcm_read(handle, capture_data,
            snd_pcm_bytes_to_frames(handle, len),
            snd_pcm_frames_to_bytes(handle, 1));
        if (ret < 0) {
            printf("pcm_read error:%d\n", ret);
            goto err_pcm_read;
        }

        ret = snd_pcm_drop(handle);
        if (ret < 0) {
            printf("stop failed!, return %d\n", ret);
            goto err_pcm_drop;
        }
#if 1
        printf("aplay start...\n");
        /*snd_ctl_set("audiocodec", "LINEOUT volume", 0x1f);*/
        aplay("default", audio_mgr->format, audio_mgr->rate,
                    audio_mgr->channels, capture_data, len);
#else
        printf("save start...\n");
        if (write(fd, capture_data, len) != len) {
            printf("write wav_file failed\n");
            goto err_fwrite;
        }
#endif
#ifdef CONFIG_SUNXI_MAD_DEBUG
        amixer_sset_enum_ctl(g_ctl_name, "sunxi mad standby test", "SUSPEND");
        usleep(100 * 1000);
        if (sunxi_mad_schd_timeout(mad_sleep, 1000 * 10) == 0)
            printf("wakeup by sunxi mad...\n");
        else
            amixer_sset_enum_ctl(g_ctl_name, "sunxi mad standby test", "RESUME");
#endif
    } while (--loop_count);

    /* close card */
    ret = snd_pcm_close(handle);
    if (ret < 0) {
        printf("audio close error:%d\n", ret);
    }
    fsync(fd);
    close(fd);
    free(capture_data);
    capture_data = NULL;
    return 0;

err_fwrite:
err_pcm_drop:
err_pcm_read:
err_pcm_prepare:
err_set_param:
    ret = snd_pcm_close(handle);
    if (ret < 0)
        printf("audio close error:%d\n", ret);
err_pcm_open:
    if (fd > 0) {
        fsync(fd);
        close(fd);
    }
err_fopen:
    free(capture_data);
err_malloc_capture_data:
    capture_data = NULL;
    return ret;
}

static void usage(void)
{
    printf("Usage: arecord [option]\n");
    printf("-D,      pcm device name\n");
    printf("-r,      sample rate\n");
    printf("-f,      sample bits\n");
    printf("-c,      channels\n");
    printf("-p,      period size\n");
    printf("-b,      buffer size\n");
    printf("-d,      capture duration(second)\n");
    printf("\n");
}

int cmd_arecord_mad(int argc, char ** argv)
{
    int i = 0, c;
    unsigned int bits = 16;
    audio_mgr_t *audio_mgr = NULL;

    g_pcm_name = strdup("hw:snddaudio0");
    g_ctl_name = strdup("snddaudio0");
    loop_count = 5;

    audio_mgr = audio_mgr_create();
    if (!audio_mgr)
        return -1;
    optind = 0;
    while ((c = getopt(argc, argv, "D:r:f:c:p:b:d:khlsv")) != -1) {
        switch (c) {
        case 'D':
            free(g_pcm_name);
            g_pcm_name = NULL;
            g_pcm_name = strdup(optarg);
            free(g_ctl_name);
            g_ctl_name = NULL;
            g_ctl_name = strdup(g_pcm_name + 3);
            printf("pcm_name:%s, ctl_name:%s\n", g_pcm_name, g_ctl_name);
            break;
        case 'r':
            audio_mgr->rate = atoi(optarg);
            break;
        case 'f':
            bits = atoi(optarg);
            break;
        case 'c':
            audio_mgr->channels = atoi(optarg);
            break;
        case 'p':
            audio_mgr->period_size = atoi(optarg);
            break;
        case 'b':
            audio_mgr->buffer_size = atoi(optarg);
            break;
        case 'd':
            audio_mgr->capture_duration = atoi(optarg);
            break;
        case 'l':
            loop_count = atoi(optarg);
            break;
        default:
            usage();
            goto err;
        }
    }

    switch (bits) {
    case 16:
        audio_mgr->format = SND_PCM_FORMAT_S16_LE;
        break;
    case 24:
        audio_mgr->format = SND_PCM_FORMAT_S24_LE;
        break;
    default:
        printf("%u bits not supprot\n", bits);
        return -1;
    }

    capture_then_play(audio_mgr);

    free(g_ctl_name);
    g_ctl_name = NULL;
    free(g_pcm_name);
    g_pcm_name = NULL;
err:
    audio_mgr_release(audio_mgr);

    return 0;
}
FINSH_FUNCTION_EXPORT_CMD(cmd_arecord_mad, arecord_mad, Record voice mad);
