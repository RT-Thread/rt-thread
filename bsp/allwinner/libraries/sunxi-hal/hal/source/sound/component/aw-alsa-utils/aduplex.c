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
#include <hal_timer.h>
#include <aw-alsa-lib/pcm.h>
#include <aw-alsa-lib/control.h>

#include "common.h"
#include "wav_parser.h"

#undef DUPLEX_FS_WAV

static char *g_pcm_name = "default";

struct duplex_priv {
    rt_mutex_t xMutex;
    audio_mgr_t *playback_mgr;
    audio_mgr_t *capture_mgr;
    char *input_name;
    char *output_name;
};

static int pcm_read(snd_pcm_t *handle, char *data,
        snd_pcm_uframes_t frames_total, unsigned int frame_bytes)
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
        /*hal_usleep(500000);*/
        /*printf("snd_pcm_readi %ld frames\n", frames);*/
        size = snd_pcm_readi(handle, (void *)(data + offset), frames);
        if (size < 0)
            printf("snd_pcm_readi return %ld\n", size);
        if (size == -EAGAIN) {
            /* retry */
            hal_usleep(10000);
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

static int pcm_write(snd_pcm_t *handle, const char *data,
        snd_pcm_uframes_t frames_total, unsigned int frame_bytes)
{
    int ret = 0;
    snd_pcm_sframes_t size;
    snd_pcm_uframes_t frames_loop = 400;
    snd_pcm_uframes_t frames_count = 0;
    snd_pcm_uframes_t frames = 0;

    while (1) {
        if ((frames_total - frames_count) < frames_loop)
            frames = frames_total - frames_count;
        if (frames == 0)
            frames = frames_loop;
        /*hal_usleep(500000);*/
        size = snd_pcm_writei(handle, data, frames);
        if (size != frames) {
            printf("snd_pcm_writei return %ld\n", size);
        }
        if (size == -EAGAIN) {
            hal_usleep(10000);
            continue;
        } else if (size == -EPIPE) {
            xrun(handle);
            continue;
        } else if (size == -ESTRPIPE) {

            continue;
        } else if (size < 0) {
            printf("-----snd_pcm_writei failed!!, return %ld\n", size);
            return size;
        }
        data += (size * frame_bytes);
        frames_count += size;
        frames -= size;
        if (frames_total == frames_count)
            break;
        /*printf("frames_count = %ld, frames_total = %ld\n", frames_count, frames_total);*/
    }

    return frames_count;
}

static int playback_fs_wav(audio_mgr_t *mgr, const char *pcm_name, const char *path)
{
    int ret = 0;
    int fd = 0;
    wav_header_t wav_header;
    wav_hw_params_t wav_hwparams = {16000, SND_PCM_FORMAT_UNKNOWN, 2};
    unsigned int c;
    unsigned int written = 0;
    unsigned int count;
    unsigned int chunk_bytes;
    unsigned int frame_bytes = 0;
    ssize_t r = 0;
    char *audiobuf = NULL;

    if (path == NULL) {
        printf("[%s] path is null.\n", __func__);
        return -1;
    }

    fd = open(path, O_RDONLY);
    if (fd < 0) {
        printf("no such wav file\n");
        ret = -1;
        goto err_fd_open;
    }
    r = read(fd, &wav_header, sizeof(wav_header_t));
    if (r != sizeof(wav_header_t)) {
        printf("read wav file header failed, return %ld\n", (long int)r);
        goto err_fread_wav_header;
    }

    if (check_wav_header(&wav_header, &wav_hwparams) != 0) {
        printf("check wav header failed\n");
        goto err_checkout_wav_header;
    }
    count = wav_header.dataSize;
    if (count == 0) {
        printf("wav data siez is %d.\n", count);
        goto err_checkout_wav_datasize;
    }

    /* open card */
    ret = snd_pcm_open(&mgr->handle, pcm_name, SND_PCM_STREAM_PLAYBACK, 0);
    if (ret < 0) {
        printf("audio open error:%d\n", ret);
        goto err_pcm_open;
    }
    mgr->format = wav_hwparams.format;
    mgr->rate = wav_hwparams.rate;
    mgr->channels = wav_hwparams.channels;

    ret = set_param(mgr->handle, mgr->format, mgr->rate, mgr->channels,
            mgr->period_size, mgr->buffer_size);
    if (ret < 0) {
        printf("audio set param error:%d\n", ret);
        goto err_set_param;
    }

    frame_bytes = snd_pcm_frames_to_bytes(mgr->handle, 1);
    chunk_bytes = snd_pcm_frames_to_bytes(mgr->handle, mgr->period_size);

    audiobuf = malloc(chunk_bytes);
    if (!audiobuf) {
        printf("no memory...\n");
        goto err_malloc;
    }
    while (written < count) {
        c = count - written;
        if (c > chunk_bytes)
            c = chunk_bytes;
        r = read(fd, audiobuf, c);
        if (r < 0 || r != c) {
            printf("read file error, r=%ld,c=%u\n", (long int)r, c);
            break;
        }
        r = pcm_write(mgr->handle, audiobuf, r/frame_bytes, frame_bytes);
        if (r != c/frame_bytes)
            break;
        written += c;
    }
    snd_pcm_drain(mgr->handle);

    free(audiobuf);

err_malloc:
err_set_param:
    /* close card */
    if (mgr->handle != NULL)
        snd_pcm_close(mgr->handle);
err_pcm_open:
err_checkout_wav_datasize:
err_checkout_wav_header:
err_fread_wav_header:
    close(fd);
err_fd_open:
    return ret;
}

static int capture_fs_wav(audio_mgr_t *mgr, const char *pcm_name, const char *path)
{
    unsigned int len = 0;
    int ret = 0;
    int fd = 0;
    wav_header_t header;
    unsigned int written = 0;
    long rest = -1, c = 0;
    char *audiobuf = NULL;
    unsigned int chunk_bytes;
    unsigned int frame_bytes = 0;
    struct stat statbuf;

    if (path == NULL)
        return -1;

    /* open card */
    ret = snd_pcm_open(&mgr->handle, pcm_name, SND_PCM_STREAM_CAPTURE, 0);
    if (ret < 0) {
        printf("audio open error:%d\n", ret);
        return -1;
    }

    ret = set_param(mgr->handle, mgr->format, mgr->rate, mgr->channels,
            mgr->period_size, mgr->buffer_size);
    if (ret < 0)
        goto err;

    frame_bytes = snd_pcm_frames_to_bytes(mgr->handle, 1);
    chunk_bytes = snd_pcm_frames_to_bytes(mgr->handle, mgr->period_size);
    if (mgr->capture_duration > 0)
        rest = mgr->capture_duration * snd_pcm_frames_to_bytes(mgr->handle, mgr->rate);

    create_wav(&header, mgr->format, mgr->rate, mgr->channels);
    if (!stat(path, &statbuf)) {
        if (S_ISREG(statbuf.st_mode))
            remove(path);
    }
    fd = open(path, O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        printf("create wav file failed\n");
        goto err;
    }
    write(fd, &header, sizeof(header));

    audiobuf = malloc(chunk_bytes);
    if (!audiobuf) {
        printf("no memory...\n");
        goto err;
    }
    char *temp_wav_file = NULL;
    unsigned int temp_wav_file_off = 0;
    if (rest < 0) {
        printf("please set capture duration..\n");
        goto err;
    }
    temp_wav_file = malloc(rest);
    if (!temp_wav_file) {
        printf("no memory for temp_wav_file\n");
        goto err;
    }
    while (rest > 0 && !mgr->in_aborting) {
        int f = mgr->period_size;
        if (rest <= chunk_bytes)
            c = rest;
        else
            c = chunk_bytes;
        f = pcm_read(mgr->handle, audiobuf, f, frame_bytes);
        if (f < 0) {
            printf("pcm read error, return %d\n", f);
            break;
        }
        memcpy(temp_wav_file + temp_wav_file_off, audiobuf, c);
        temp_wav_file_off += c;
        if (rest > 0)
            rest -= c;
        written += c;
    }

    ret = snd_pcm_drain(mgr->handle);
    if (ret < 0)
        printf("stop failed!, return %d\n", ret);

err:
    /* close card */
    ret = snd_pcm_close(mgr->handle);
    if (ret < 0) {
        printf("audio close error:%d\n", ret);
        return ret;
    }

    printf("please wait...writing data(%u bytes) into %s\n", temp_wav_file_off, path);
    ret = write(fd, temp_wav_file, temp_wav_file_off);
    if (ret != temp_wav_file_off) {
        printf("write temp_wav_file failed. ret:%d, wav_file_off:%d\n",
            ret, temp_wav_file_off);
        goto err1;
    }
    printf("write finish...\n");
    resize_wav(&header, written);
    lseek(fd, 0, SEEK_SET);
    write(fd, &header, sizeof(header));

err1:
    if (temp_wav_file)
        free(temp_wav_file);

    if (fd > 0)
        close(fd);
    if (audiobuf)
        free(audiobuf);
    return ret;
}

/*
 * arg0: arecord
 * arg1: card
 * arg2: format
 * arg3: rate
 * arg4: channels
 * arg5: data
 * arg6: len
 */
static int arecord(const char *card_name, snd_pcm_format_t format, unsigned int rate,
            unsigned int channels, void *data, unsigned int datalen)
{
    int ret = 0;
    snd_pcm_t *handle;
    int mode = 0;
    snd_pcm_hw_params_t *params;
    snd_pcm_sw_params_t *sw_params;
    snd_pcm_uframes_t period_frames = 1024, buffer_frames = 4096;

    printf("arecord dump args:\n");
    printf("card:      %s\n", card_name);
    printf("format:    %u\n", format);
    printf("rate:      %u\n", rate);
    printf("channels:  %u\n", channels);
    printf("data:      %p\n", data);
    printf("datalen:   %u\n", datalen);

    /* open card */
    ret = snd_pcm_open(&handle, card_name, SND_PCM_STREAM_CAPTURE, mode);
    if (ret < 0) {
        printf("audio open error:%d\n", ret);
        return -1;
    }

    ret = set_param(handle, format, rate, channels, period_frames, buffer_frames);
    if (ret < 0) {
        printf("set param failed!, return %d\n", ret);
        goto err_set_param;
    }
    printf("pcm_read start...\n");
    ret = pcm_read(handle, data, snd_pcm_bytes_to_frames(handle, datalen),
            snd_pcm_frames_to_bytes(handle, 1));
    if (ret < 0) {
        printf("capture error:%d\n", ret);
        goto err_pcm_read;
    }

err_pcm_read:
    ret = snd_pcm_drain(handle);
    if (ret < 0)
        printf("stop failed!, return %d\n", ret);

err_set_param:
    /* close card */
    ret = snd_pcm_close(handle);
    if (ret < 0)
        printf("audio close error:%d\n", ret);

    return ret;
}

/*
 * arg0: aplay
 * arg1: card
 * arg2: format
 * arg3: rate
 * arg4: channels
 * arg5: data
 * arg6: len
 */
static int aplay(const char *card_name, snd_pcm_format_t format, unsigned int rate,
            unsigned int channels, const char *data, unsigned int datalen)
{
    int ret = 0;
    snd_pcm_t *handle;
    int mode = 0;
    snd_pcm_uframes_t period_frames = 1024, buffer_frames = 4096;

    printf("aplay dump args:\n");
    printf("card:        %s\n", card_name);
    printf("format:      %u\n", format);
    printf("rate:        %u\n", rate);
    printf("channels:    %u\n", channels);
    printf("data:        %p\n", data);
    printf("datalen:     %u\n", datalen);
    printf("period_size: %lu\n", period_frames);
    printf("buffer_size: %lu\n", buffer_frames);

    /* open card */
    ret = snd_pcm_open(&handle, card_name, SND_PCM_STREAM_PLAYBACK, mode);
    if (ret < 0) {
        printf("audio open error:%d\n", ret);
        return -1;
    }

    ret = set_param(handle, format, rate, channels, period_frames, buffer_frames);
    if (ret < 0) {
        goto err_set_param;
    }

    ret = pcm_write(handle, (char *)data,
            snd_pcm_bytes_to_frames(handle, datalen),
            snd_pcm_frames_to_bytes(handle, 1));
    if (ret < 0) {
        printf("pcm_write error:%d\n", ret);
        goto err_pcm_write;
    }

err_pcm_write:
    ret = snd_pcm_drain(handle);
    /*ret = snd_pcm_drop(handle);*/
    if (ret < 0)
        printf("stop failed!, return %d\n", ret);

err_set_param:
    /* close card */
    ret = snd_pcm_close(handle);
    if (ret < 0)
        printf("audio close error:%d\n", ret);

    return ret;
}

static int capture_then_play(audio_mgr_t *audio_mgr)
{
    char *capture_data = NULL;
    unsigned int len = 0;

    if (audio_mgr->capture_duration == 0)
        audio_mgr->capture_duration = 3;

    len = snd_pcm_format_size(audio_mgr->format,
               audio_mgr->capture_duration * audio_mgr->rate *
               audio_mgr->channels);
    capture_data = malloc(len);
    if (!capture_data) {
        printf("no memory\n");
        return -1;
    }
    memset(capture_data, 0, len);

    printf("arecord start...\n");
    arecord(g_pcm_name, audio_mgr->format, audio_mgr->rate,
                audio_mgr->channels, capture_data, len);
    printf("aplay start...\n");
    /*snd_ctl_set("audiocodec", "LINEOUT volume", 0x1f);*/
    aplay("hw:audiocodec", audio_mgr->format, audio_mgr->rate,
                audio_mgr->channels, capture_data, len);

    free(capture_data);
    capture_data = NULL;
    return 0;
}

static void arecord_entry(void * arg)
{
    int ret = 0;
    struct duplex_priv * duplex_priv = arg;
    const uint32_t timeout = 1 * 1000;

    ret = rt_mutex_take(duplex_priv->xMutex, timeout);
    if (!ret) {
        printf("[%s] semaphore take failed.\n", __func__);
//      vTaskDelete(NULL);
        return;
    }
#ifdef DUPLEX_FS_WAV
    ret = capture_fs_wav(duplex_priv->capture_mgr, g_pcm_name,
                duplex_priv->input_name);
    if (ret < 0)
        printf("capture_fs_wav error:%d\n", ret);
#else
    capture_then_play(duplex_priv->capture_mgr);
#endif
    rt_mutex_release(duplex_priv->xMutex);

//  vTaskDelete(NULL);
}

static void usage(void)
{
    printf("Usage: aduplex [option]\n");
    printf("-D,      pcm device name\n");
    printf("-r,      sample rate\n");
    printf("-f,      sample bits\n");
    printf("-c,      channels\n");
    printf("-p,      period size\n");
    printf("-b,      buffer size\n");
    printf("-i,      input file path\n");
    printf("-o,      output file path\n");
    printf("-d,      capture duration(second)\n");
    printf("-h,      for help\n");
    printf("\n");
}

int cmd_aduplex(int argc, char ** argv)
{
    int i = 0;
    int c;
    int ret = 0;
    unsigned int bits = 16;
    const uint32_t timeout = 11 * 1000;
//  int priority = configAPPLICATION_NORMAL_PRIORITY;
    uint32_t thread_size = 4 * 1024;
    struct duplex_priv duplex_priv;
//  TaskHandle_t pxCreatedTask;
    unsigned int buf_size;

    g_pcm_name = "hw:snddaudio0";

    duplex_priv.playback_mgr = audio_mgr_create();
    if (!duplex_priv.playback_mgr) {
        printf("playback_mgr malloc failed.\n");
        return -1;
    }

    duplex_priv.capture_mgr = audio_mgr_create();
    if (!duplex_priv.capture_mgr) {
        printf("capture_mgr malloc failed.\n");
        goto err_malloc_capture_mgr;
    }

    /* for init */
    duplex_priv.capture_mgr->capture_duration = 5;
#ifdef DUPLEX_FS_WAV
    duplex_priv.input_name = "/data/connect_success_rec.wav";
#endif
    duplex_priv.output_name = "/data/connect_success.wav";

    optind = 0;
    while ((c = getopt(argc, argv, "i:o:D:r:f:c:p:b:d:h")) != -1) {
        switch (c) {
        case 'i':
            duplex_priv.input_name = optarg;
            break;
        case 'o':
            duplex_priv.output_name = optarg;
            break;
        case 'D':
            g_pcm_name = optarg;
            break;
        case 'r':
            duplex_priv.playback_mgr->rate = atoi(optarg);
            duplex_priv.capture_mgr->rate = atoi(optarg);
            break;
        case 'f':
            bits = atoi(optarg);
            break;
        case 'c':
            duplex_priv.playback_mgr->channels = atoi(optarg);
            duplex_priv.capture_mgr->channels = atoi(optarg);
            break;
        case 'p':
            duplex_priv.playback_mgr->period_size = atoi(optarg);
            duplex_priv.capture_mgr->period_size = atoi(optarg);
            break;
        case 'b':
            duplex_priv.playback_mgr->buffer_size = atoi(optarg);
            duplex_priv.capture_mgr->buffer_size = atoi(optarg);
            break;
        case 'd':
            duplex_priv.capture_mgr->capture_duration = atoi(optarg);
            break;
        case 'h':
        default:
            usage();
            goto err_cmd;
        }
    }

    /* check params */
    if (duplex_priv.capture_mgr->capture_duration > 10)
        duplex_priv.capture_mgr->capture_duration = 10;
    if (duplex_priv.capture_mgr->capture_duration <= 0)
        duplex_priv.capture_mgr->capture_duration = 5;

    if (duplex_priv.output_name == NULL) {
        printf("output name is null.\n");
        goto err_out_filename_null;
    }

#ifdef DUPLEX_FS_WAV
    if (duplex_priv.input_name == NULL) {
        printf("input file name is null.\n");
        goto err_in_filename_null;
    }
#endif

    switch (bits) {
    case 16:
        duplex_priv.playback_mgr->format = SND_PCM_FORMAT_S16_LE;
        duplex_priv.capture_mgr->format = SND_PCM_FORMAT_S16_LE;
        break;
    case 24:
        duplex_priv.playback_mgr->format = SND_PCM_FORMAT_S24_LE;
        duplex_priv.capture_mgr->format = SND_PCM_FORMAT_S24_LE;
        break;
    case 32:
        duplex_priv.playback_mgr->format = SND_PCM_FORMAT_S32_LE;
        duplex_priv.capture_mgr->format = SND_PCM_FORMAT_S32_LE;
        break;
    default:
        printf("%u bits not supprot\n", bits);
        goto err_format;
    }

    duplex_priv.xMutex = rt_mutex_create("sound_mtx", RT_IPC_FLAG_PRIO);
    if(duplex_priv.xMutex == RT_NULL) {
        printf("mutex create failed.\n");
        goto err_create_mutex;
    }

//  ret = xTaskCreate(arecord_entry, (signed portCHAR *) "arecord-thread",
//              thread_size, &duplex_priv, priority, &pxCreatedTask);
//  if (!ret) {
//      printf("arecord-thread create failed.\n");
//      goto err_create_arecord;
//  }

    playback_fs_wav(duplex_priv.playback_mgr, g_pcm_name, duplex_priv.output_name);
    /* wait for capturing finished */
    ret = rt_mutex_take(duplex_priv.xMutex, timeout);
    if (!ret) {
        printf("[%s] semaphore take failed.\n", __func__);
        goto err_arecord_timeout;
    }
    rt_mutex_release(duplex_priv.xMutex);
    rt_mutex_delete(duplex_priv.xMutex);

#ifdef DUPLEX_FS_WAV
    /* after capture finished */
    playback_fs_wav(duplex_priv.playback_mgr, "default", duplex_priv.input_name);
#endif

    audio_mgr_release(duplex_priv.capture_mgr);
    audio_mgr_release(duplex_priv.playback_mgr);
    return 0;

err_arecord_timeout:
//  vTaskDelete(pxCreatedTask);
err_create_arecord:
err_format:
err_create_mutex:
err_in_filename_null:
err_out_filename_null:
err_cmd:
    audio_mgr_release(duplex_priv.capture_mgr);
err_malloc_capture_mgr:
    audio_mgr_release(duplex_priv.playback_mgr);
    return ret;
}
FINSH_FUNCTION_EXPORT_CMD(cmd_aduplex, aduplex, Playback and Record);
