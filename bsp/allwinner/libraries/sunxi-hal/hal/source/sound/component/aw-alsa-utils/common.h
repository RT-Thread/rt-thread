#ifndef __COMMON_H
#define __COMMON_H

#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    snd_pcm_t *handle;
    snd_pcm_format_t format;
    unsigned int rate;
    unsigned int channels;
    snd_pcm_uframes_t period_size;
    snd_pcm_uframes_t buffer_size;

    snd_pcm_uframes_t frame_bytes;
    snd_pcm_uframes_t chunk_size;

    unsigned in_aborting;
    unsigned int capture_duration;
} audio_mgr_t;

void xrun(snd_pcm_t *handle);
void do_other_test(snd_pcm_t *handle);
void do_pause(snd_pcm_t *handle);

int set_param(snd_pcm_t *handle, snd_pcm_format_t format,
            unsigned int rate, unsigned int channels,
            snd_pcm_uframes_t period_size,
            snd_pcm_uframes_t buffer_size);
audio_mgr_t *audio_mgr_create(void);
void audio_mgr_release(audio_mgr_t *mgr);

#ifdef __cplusplus
};  // extern "C"
#endif
#endif /* __COMMON_H */
