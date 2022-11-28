#ifndef _AUDIO_WAV_H
#define _AUDIO_WAV_H
#include <aw_common.h>

#ifdef CONFIG_BUILTIN_WAV_FILE
/*
 * boot_package will larger than 2M if define ALL_WAV_FILE
 */
//#define ALL_WAV_FILE

extern const unsigned char music_16K_16bit_1ch_start;
extern const unsigned char music_16K_16bit_1ch_end;
extern const unsigned char music_8K_16bit_2ch_start;
extern const unsigned char music_8K_16bit_2ch_end;
#ifdef ALL_WAV_FILE
extern const unsigned char music_16K_16bit_2ch_start;
extern const unsigned char music_16K_16bit_2ch_end;
extern const unsigned char music_16K_24bit_2ch_start;
extern const unsigned char music_16K_24bit_2ch_end;
extern const unsigned char music_44K_16bit_2ch_start;
extern const unsigned char music_44K_16bit_2ch_end;
extern const unsigned char music_48K_16bit_2ch_start;
extern const unsigned char music_48K_16bit_2ch_end;
#endif
#endif


typedef struct {
    const char *name;
    const unsigned char *start;
    const unsigned char *end;
} wav_file_t;

#define WAV_FILE_LABEL(constant) \
{ \
    .name   = #constant, \
    .start  = &music_##constant##_start, \
    .end    = &music_##constant##_end, \
}

static wav_file_t wav_file_array[] = {
#ifdef CONFIG_BUILTIN_WAV_FILE
    WAV_FILE_LABEL(16K_16bit_1ch),
    WAV_FILE_LABEL(8K_16bit_2ch),
#ifdef ALL_WAV_FILE
    WAV_FILE_LABEL(16K_16bit_2ch),
    WAV_FILE_LABEL(16K_24bit_2ch),
    WAV_FILE_LABEL(44K_16bit_2ch),
    WAV_FILE_LABEL(48K_16bit_2ch),
#endif
#endif
};

static inline void wav_file_list(void)
{
    int i;
    for (i = 0; i < ARRAY_SIZE(wav_file_array); i++)
        printf("%s\n", wav_file_array[i].name);
}

static inline wav_file_t *find_builtin_wav_file(const char *name)
{
    int i;
    wav_hw_params_t params;
#if 0
    for (i = 0; i < ARRAY_SIZE(wav_file_array); i++) {
        printf("name:%s, start:%p, end:%p\n",
            wav_file_array[i].name,
            wav_file_array[i].start,
            wav_file_array[i].end);
        check_wav_header((wav_header_t *)wav_file_array[i].start, &params);
    }
#endif
    if (!name)
        return &wav_file_array[0];
    for (i = 0; i < ARRAY_SIZE(wav_file_array); i++) {
        if (!strcmp(wav_file_array[i].name, name)) {
            return &wav_file_array[i];
        }
    }
    return NULL;
}

#endif
