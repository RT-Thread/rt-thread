/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-24     thread-liu   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/statfs.h>

#if defined(BSP_USING_AUDIO) && defined(BSP_USING_SDMMC)
#define BUFSZ   1024
#define SOUND_DEVICE_NAME    "sound0"
static rt_device_t snd_dev;

struct RIFF_HEADER_DEF
{
    char riff_id[4];     // 'R','I','F','F'
    uint32_t riff_size;
    char riff_format[4]; // 'W','A','V','E'
};

struct WAVE_FORMAT_DEF
{
    uint16_t FormatTag;
    uint16_t Channels;
    uint32_t SamplesPerSec;
    uint32_t AvgBytesPerSec;
    uint16_t BlockAlign;
    uint16_t BitsPerSample;
};

struct FMT_BLOCK_DEF
{
    char fmt_id[4];    // 'f','m','t',' '
    uint32_t fmt_size;
    struct WAVE_FORMAT_DEF wav_format;
};

struct DATA_BLOCK_DEF
{
    char data_id[4];     // 'R','I','F','F'
    uint32_t data_size;
};

struct wav_info
{
    struct RIFF_HEADER_DEF header;
    struct FMT_BLOCK_DEF   fmt_block;
    struct DATA_BLOCK_DEF  data_block;
};

int wavplay_sample(int argc, char **argv)
{
    int fd = -1;
    uint8_t *buffer = NULL;
    struct wav_info *info = NULL;
    struct rt_audio_caps caps = {0};

    if (argc != 2)
    {
        rt_kprintf("Usage:\n");
        rt_kprintf("wavplay_sample song.wav\n");
        return 0;
    }

    fd = open(argv[1], O_WRONLY);
    if (fd < 0)
    {
        rt_kprintf("open file failed!\n");
        goto __exit;
    }

    buffer = rt_malloc(BUFSZ);
    if (buffer == RT_NULL)
        goto __exit;

    info = (struct wav_info *) rt_malloc(sizeof * info);
    if (info == RT_NULL)
        goto __exit;

    if (read(fd, &(info->header), sizeof(struct RIFF_HEADER_DEF)) <= 0)
        goto __exit;
    if (read(fd, &(info->fmt_block),  sizeof(struct FMT_BLOCK_DEF)) <= 0)
        goto __exit;
    if (read(fd, &(info->data_block), sizeof(struct DATA_BLOCK_DEF)) <= 0)
        goto __exit;

    rt_kprintf("wav information:\n");
    rt_kprintf("samplerate %d\n", info->fmt_block.wav_format.SamplesPerSec);
    rt_kprintf("channel %d\n", info->fmt_block.wav_format.Channels);

    snd_dev = rt_device_find(SOUND_DEVICE_NAME);

    rt_device_open(snd_dev, RT_DEVICE_OFLAG_WRONLY);

    caps.main_type               = AUDIO_TYPE_OUTPUT;
    caps.sub_type                = AUDIO_DSP_PARAM;
    caps.udata.config.samplerate = info->fmt_block.wav_format.SamplesPerSec;
    caps.udata.config.channels   = info->fmt_block.wav_format.Channels;
    caps.udata.config.samplebits = 16;
    rt_device_control(snd_dev, AUDIO_CTL_CONFIGURE, &caps);

    while (1)
    {
        int length;

        length = read(fd, buffer, BUFSZ);

        if (length <= 0)
            break;

        rt_device_write(snd_dev, 0, buffer, length);
    }

    rt_device_close(snd_dev);

__exit:

    if (fd >= 0)
        close(fd);

    if (buffer)
        rt_free(buffer);

    if (info)
        rt_free(info);

    return 0;
}

MSH_CMD_EXPORT(wavplay_sample,  play wav file);

#endif

#if defined(BSP_USING_AUDIO) && defined(BSP_USING_SDMMC)  && defined(BSP_USING_AUDIO_RECORD)

#define RECORD_TIME_MS      5000
#define RECORD_SAMPLERATE   16000
#define RECORD_CHANNEL      2
#define RECORD_CHUNK_SZ     ((RECORD_SAMPLERATE * RECORD_CHANNEL * 2) * 20 / 1000)

#define MIC_DEVICE_NAME    "mic0"
static rt_device_t mic_dev;

struct wav_header
{
    char  riff_id[4];              /* "RIFF" */
    int   riff_datasize;           /* RIFF chunk data size,exclude riff_id[4] and riff_datasize,total - 8 */
    char  riff_type[4];            /* "WAVE" */
    char  fmt_id[4];               /* "fmt " */
    int   fmt_datasize;            /* fmt chunk data size,16 for pcm */
    short fmt_compression_code;    /* 1 for PCM */
    short fmt_channels;            /* 1(mono) or 2(stereo) */
    int   fmt_sample_rate;         /* samples per second */
    int   fmt_avg_bytes_per_sec;   /* sample_rate * channels * bit_per_sample / 8 */
    short fmt_block_align;         /* number bytes per sample, bit_per_sample * channels / 8 */
    short fmt_bit_per_sample;      /* bits of each sample(8,16,32). */
    char  data_id[4];              /* "data" */
    int   data_datasize;           /* data chunk size,pcm_size - 44 */
};

static void wavheader_init(struct wav_header *header, int sample_rate, int channels, int datasize)
{
    memcpy(header->riff_id, "RIFF", 4);
    header->riff_datasize = datasize + 44 - 8;
    memcpy(header->riff_type, "WAVE", 4);
    memcpy(header->fmt_id, "fmt ", 4);
    header->fmt_datasize = 16;
    header->fmt_compression_code = 1;
    header->fmt_channels = channels;
    header->fmt_sample_rate = sample_rate;
    header->fmt_bit_per_sample = 16;
    header->fmt_avg_bytes_per_sec = header->fmt_sample_rate * header->fmt_channels * header->fmt_bit_per_sample / 8;
    header->fmt_block_align = header->fmt_bit_per_sample * header->fmt_channels / 8;
    memcpy(header->data_id, "data", 4);
    header->data_datasize = datasize;
}

int wavrecord_sample(int argc, char **argv)
{
    int fd = -1;
    uint8_t *buffer = NULL;
    struct wav_header header;
    struct rt_audio_caps caps = {0};
    int length, total_length = 0;

    if (argc != 2)
    {
        rt_kprintf("Usage:\n");
        rt_kprintf("wavrecord_sample file.wav\n");
        return -1;
    }

    fd = open(argv[1], O_WRONLY | O_CREAT);
    if (fd < 0)
    {
        rt_kprintf("open file for recording failed!\n");
        return -1;
    }
    write(fd, &header, sizeof(struct wav_header));

    buffer = rt_malloc(RECORD_CHUNK_SZ);
    if (buffer == RT_NULL)
        goto __exit;

    mic_dev = rt_device_find(MIC_DEVICE_NAME);
    if (mic_dev == RT_NULL)
        goto __exit;

    rt_device_open(mic_dev, RT_DEVICE_OFLAG_RDONLY);

    caps.main_type               = AUDIO_TYPE_INPUT;
    caps.sub_type                = AUDIO_DSP_PARAM;
    caps.udata.config.samplerate = RECORD_SAMPLERATE;
    caps.udata.config.channels   = RECORD_CHANNEL;
    caps.udata.config.samplebits = 16;
    rt_device_control(mic_dev, AUDIO_CTL_CONFIGURE, &caps);

    while (1)
    {
        length = rt_device_read(mic_dev, 0, buffer, RECORD_CHUNK_SZ);

        if (length)
        {
            write(fd, buffer, length);
            total_length += length;
        }

        if ((total_length / RECORD_CHUNK_SZ) >  (RECORD_TIME_MS / 20))
            break;
    }

    /* write wav file head */
    wavheader_init(&header, RECORD_SAMPLERATE, RECORD_CHANNEL, total_length);
    lseek(fd, 0, SEEK_SET);
    write(fd, &header, sizeof(struct wav_header));
    close(fd);

    /* close audio mic device */
    rt_device_close(mic_dev);

__exit:
    if (fd >= 0)
        close(fd);

    if (buffer)
        rt_free(buffer);

    return 0;
}
MSH_CMD_EXPORT(wavrecord_sample, record voice to a wav file);

#endif
