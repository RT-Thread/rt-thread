#include <rtthread.h>
#include <rtdevice.h>
#include <finsh.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "audio_device.h"

#define BUFSZ   2048

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

static char file_name[32];

void wavplay_thread_entry(void *parameter)
{
    FILE *fp = NULL;
    uint16_t *buffer = NULL;
    struct wav_info *info = NULL;

    fp = fopen(file_name, "rb");
    if (!fp)
    {
        printf("open file failed!\n");
        goto __exit;
    }

    info = (struct wav_info *) malloc(sizeof(*info));
    if (!info) goto __exit;

    if (fread(&(info->header),     sizeof(struct RIFF_HEADER_DEF), 1, fp) != 1) goto __exit;
    if (fread(&(info->fmt_block),  sizeof(struct FMT_BLOCK_DEF),   1, fp) != 1) goto __exit;
    if (fread(&(info->data_block), sizeof(struct DATA_BLOCK_DEF),  1, fp) != 1) goto __exit;

    printf("wav information:\n");
    printf("samplerate %u\n", info->fmt_block.wav_format.SamplesPerSec);
    printf("channel %u\n", info->fmt_block.wav_format.Channels);

    audio_device_init();
    audio_device_open();
    audio_device_set_rate(info->fmt_block.wav_format.SamplesPerSec);

    while (!feof(fp))
    {
        int length;

        buffer = (uint16_t *)audio_device_get_buffer(RT_NULL);

        length = fread(buffer, 1, BUFSZ, fp);
        if (length)
        {
            if (info->fmt_block.wav_format.Channels == 1)
            {
                /* extend to stereo channels */
                int index;
                uint16_t *ptr;

                ptr = (uint16_t *)((uint8_t *)buffer + BUFSZ * 2);
                for (index = 1; index < BUFSZ / 2; index ++)
                {
                    *ptr = *(ptr - 1) = buffer[BUFSZ / 2 - index];
                    ptr -= 2;
                }

                length = length * 2;
            }

            audio_device_write((uint8_t *)buffer, length);
        }
        else
        {
            audio_device_put_buffer((uint8_t *)buffer);
            break;
        }
    }
    audio_device_close();

__exit:
    if (fp) fclose(fp);
    if (info) free(info);
}

int wavplay(int argc, char **argv)
{
    rt_thread_t tid = RT_NULL;

    if (argc != 2)
    {
        printf("Usage:\n");
        printf("wavplay song.wav\n");
        return 0;
    }

    memset(file_name, 0, sizeof(file_name));
    memcpy(file_name, argv[1], strlen(argv[1]));

    tid = rt_thread_create("wayplay",
                           wavplay_thread_entry,
                           RT_NULL,
                           1024 * 8,
                           22,
                           10);
    if (tid != RT_NULL)
        rt_thread_startup(tid);
}

MSH_CMD_EXPORT(wavplay, wavplay song.wav);
