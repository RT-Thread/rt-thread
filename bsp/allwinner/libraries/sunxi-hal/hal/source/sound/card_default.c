#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sound/snd_core.h>
#include <aw_common.h>
#ifndef CONFIG_KERNEL_FREERTOS
#include <init.h>
#endif

#ifdef CONFIG_SND_PLATFORM_SUNXI_CPUDAI
extern struct snd_codec sunxi_audiocodec;
#endif

#ifdef CONFIG_SND_CODEC_AC108
extern struct snd_codec ac108_codec;
#else
extern struct snd_codec dummy_codec;
#endif
#ifdef CONFIG_SND_PLATFORM_SUNXI_DMIC
extern struct snd_codec dmic_codec;
#endif
#ifdef CONFIG_SND_PLATFORM_SUNXI_SPDIF
extern struct snd_codec spdif_codec;
#endif

int sunxi_soundcard_init(void)
{
    int ret = 0;
    char *card_name = NULL;

    //maybe unused for compile warning.
    UNUSED(ret);
    UNUSED(card_name);
/* ------------------------------------------------------------------------- */
/* AUDIOCODEC */
/* ------------------------------------------------------------------------- */
#ifdef CONFIG_SND_PLATFORM_SUNXI_CPUDAI
    struct snd_codec *audio_codec = NULL;

    card_name = "audiocodec";
    audio_codec = &sunxi_audiocodec;

        /* register audiocodec sound card */
    ret = snd_card_register(card_name, audio_codec,
                    SND_PLATFORM_TYPE_CPUDAI);
    if (ret == 0) {
        snd_print("soundcards: audiocodec register success!\n");
    } else {
        snd_err("soundcards: audiocodec register failed!\n");
    }
#endif

/* ------------------------------------------------------------------------- */
/* DAUDIO */
/* ------------------------------------------------------------------------- */
#ifdef CONFIG_SND_PLATFORM_SUNXI_DAUDIO0
#ifdef CONFIG_SND_CODEC_AC108
    card_name = "ac108";
    audio_codec = &ac108_codec;
#else
    card_name = "snddaudio0";
    audio_codec = &dummy_codec;
#endif
        /* register daudio0 sound card */
    ret = snd_card_register("snddaudio0", audio_codec, SND_PLATFORM_TYPE_DAUDIO0);
    if (ret == 0) {
        snd_print("soundcards: %s register success!\n", card_name);
    } else {
        snd_err("soundcards: %s register failed!\n", card_name);
    }
#endif

#ifdef CONFIG_SND_PLATFORM_SUNXI_DAUDIO1
    card_name = "snddaudio1";
    audio_codec = &dummy_codec;
        /* register daudio1 sound card */
    ret = snd_card_register("snddaudio1", audio_codec, SND_PLATFORM_TYPE_DAUDIO1);
    if (ret == 0) {
        snd_print("soundcards: %s register success!\n", card_name);
    } else {
        snd_err("soundcards: %s register failed!\n", card_name);
    }
#endif

#ifdef CONFIG_SND_PLATFORM_SUNXI_DAUDIO2
    card_name = "snddaudio2";
    audio_codec = &dummy_codec;
        /* register daudio2 sound card */
    ret = snd_card_register("snddaudio2", audio_codec, SND_PLATFORM_TYPE_DAUDIO2);
    if (ret == 0) {
        snd_print("soundcards: %s register success!\n", card_name);
    } else {
        snd_err("soundcards: %s register failed!\n", card_name);
    }
#endif

#ifdef CONFIG_SND_PLATFORM_SUNXI_DAUDIO3
    card_name = "snddaudio3";
    audio_codec = &dummy_codec;
        /* register daudio3 sound card */
    ret = snd_card_register("snddaudio3", audio_codec, SND_PLATFORM_TYPE_DAUDIO3);
    if (ret == 0) {
        snd_print("soundcards: %s register success!\n", card_name);
    } else {
        snd_err("soundcards: %s register failed!\n", card_name);
    }
#endif

/* ------------------------------------------------------------------------- */
/* DMIC */
/* ------------------------------------------------------------------------- */
#ifdef CONFIG_SND_PLATFORM_SUNXI_DMIC
    card_name = "snddmic";
    audio_codec = &dmic_codec;
    /* register dmic sound card */
    ret = snd_card_register(card_name, audio_codec,
            SND_PLATFORM_TYPE_DMIC);
    if (ret == 0) {
        snd_print("soundcards: %s register success!\n", card_name);
    } else {
        snd_err("soundcards: %s register failed!\n", card_name);
    }
#endif

/* ------------------------------------------------------------------------- */
/* SPDIF */
/* ------------------------------------------------------------------------- */
#ifdef CONFIG_SND_PLATFORM_SUNXI_SPDIF
    card_name = "sndspdif";
    audio_codec = &spdif_codec;
    /* register spdif sound card */
    ret = snd_card_register(card_name, audio_codec,
            SND_PLATFORM_TYPE_SPDIF);
    if (ret == 0) {
        snd_print("soundcards: %s register success!\n", card_name);
    } else {
        snd_err("soundcards: %s register failed!\n", card_name);
    }
#endif

    /* Sound cards list */
    snd_card_list();

    return 0;
}

#ifndef CONFIG_KERNEL_FREERTOS
late_initcall(sunxi_soundcard_init);
#endif
