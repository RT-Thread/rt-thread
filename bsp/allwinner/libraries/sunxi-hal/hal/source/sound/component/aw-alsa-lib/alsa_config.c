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

#include <aw-alsa-lib/pcm_config.h>
#include <aw-alsa-lib/pcm_plugin.h>

#define SND_PCM_HW_CONFIG(name, device) \
{ \
    .card_name  = #name,  \
    .device_num = device, \
}

#define DEFINE_SND_PCM_HW_CONFIG(name, device) \
    const snd_pcm_hw_config_t snd_##name##_hw_config = \
                SND_PCM_HW_CONFIG(name, device);

static DEFINE_SND_PCM_HW_CONFIG(audiocodec, 0);
static DEFINE_SND_PCM_HW_CONFIG(snddaudio0, 0);
static DEFINE_SND_PCM_HW_CONFIG(snddaudio1, 0);
static DEFINE_SND_PCM_HW_CONFIG(snddaudio2, 0);
static DEFINE_SND_PCM_HW_CONFIG(snddaudio3, 0);
static DEFINE_SND_PCM_HW_CONFIG(snddmic, 0);
static DEFINE_SND_PCM_HW_CONFIG(sndspdif, 0);

static const snd_pcm_softvol_config_t snd_pcm_softvol_config1 = {
    .type       = "softvol",
    .slave = {
        .pcm        = "PlaybackDmix",
    },
    .control = {
        .control_name   = "Soft Volume Control1",
        .card_name  = "audiocodec",
    },
    .min_dB         = -51.0,
    .max_dB         = 0.0,
    .resolution     = 256,
};

static const snd_pcm_softvol_config_t snd_pcm_softvol_config2 = {
    .type       = "softvol",
    .slave = {
        .pcm        = "PlaybackDmix",
    },
    .control = {
        .control_name   = "Soft Volume Control2",
        .card_name  = "audiocodec",
    },
    .min_dB         = -51.0,
    .max_dB         = 0.0,
    .resolution     = 100,
};

static const snd_pcm_dsnoop_config_t snd_pcm_dsnoop_config = {
    .type       = "dsnoop",
    .ipc_key    = 1111,
    .slave = {
        .pcm        = "audiocodec",
        .format     = SND_PCM_FORMAT_S16_LE,
        .rate       = 16000,
        .channels   = 4,
        .period_size    = 2048,
        .periods    = 8,
    },
};

static const snd_pcm_dmix_config_t snd_pcm_dmix_config = {
    .type       = "dmix",
    .ipc_key    = 2222,
    .slave = {
        .pcm        = "audiocodec",
        .format     = SND_PCM_FORMAT_S16_LE,
        .rate       = 48000,
        .channels   = 2,
        .period_size    = 1024,
        .periods    = 8,
    },
};


#define DEFINE_SND_PCM_RATE_CONFIG(name, formats, rates, converters) \
    const snd_pcm_rate_config_t snd_##name##_rate_config = { \
        .type       = "rate", \
        .slave = { \
            .pcm        = #name, \
            .format     = formats, \
            .rate       = rates, \
        }, \
        .converter  = #converters, \
    }

static DEFINE_SND_PCM_RATE_CONFIG(audiocodec, SND_PCM_FORMAT_S16_LE, 48000, speexrate);

static const snd_pcm_asym_config_t snd_pcm_asym_config = {
    .type       = "asym",
    .playback_pcm   = "PlaybackPlug",
    .capture_pcm    = "CaptureDsnoop",
};

static const snd_pcm_route_config_t snd_pcm_route_config = {
    .type = "route",
    .slave = {
        .pcm = "audiocodec",
        .channels = 1,
    },
    .ttable = {
        {0, 0, 0.5},
        {1, 0, 0.5},
        TTABLE_CONFIG_END
    },
};

static const snd_pcm_plug_config_t snd_pcm_plug_config = {
    .type           = "plug",
    .slave          = {
        .pcm        = "PlaybackDmix",
        .format         = SND_PCM_FORMAT_S16_LE,
        .channels       = 2,
        .rate           = 48000,
    },
    .rate_converter = "speexrate",
    .route_policy   = "default",
    .ttable         = {
        TTABLE_CONFIG_END
    },
};

#ifdef CONFIG_AW_ALSA_PLUGINS_SONA_AUDIOAEF
static const snd_pcm_sona_audioaef_config_t snd_pcm_sona_audioaef_config = {
    .type = "sona_audioaef",
    .slave = {
        .pcm = "hw:audiocodec",
    },
    .config_name = "sona_audioaef_example",
    .config_file = NULL,
    .max_frames = 0,
    .runtime_config = 0,
};
#endif

static const snd_pcm_file_config_t snd_pcm_file_pb_config = {
    .type       = "file",
    .slave      = {
        .pcm        = "PlaybackDmix",
    },
    .format     = "raw",
    .mode       = "adb",
    .port       = 20190,
};

static const snd_pcm_file_config_t snd_pcm_file_cap_config = {
    .type       = "file",
    .slave      = {
        .pcm        = "CaptureDsnoop",
    },
    .format     = "raw",
    .mode       = "adb",
    .port       = 20191,
};

const snd_pcm_config_t snd_pcm_global_configs[] = {
    SND_PCM_CONFIG("CaptureDsnoop", "dsnoop", &snd_pcm_dsnoop_config),
    SND_PCM_CONFIG("PlaybackDmix", "dmix", &snd_pcm_dmix_config),
    SND_PCM_CONFIG("Playbackrate", "rate", &snd_audiocodec_rate_config),
    SND_PCM_CONFIG("audiocodec", "hw", &snd_audiocodec_hw_config),
        SND_PCM_CONFIG("snddaudio0", "hw", &snd_snddaudio0_hw_config),
        SND_PCM_CONFIG("snddaudio1", "hw", &snd_snddaudio1_hw_config),
        SND_PCM_CONFIG("snddaudio2", "hw", &snd_snddaudio2_hw_config),
        SND_PCM_CONFIG("snddaudio3", "hw", &snd_snddaudio3_hw_config),
        SND_PCM_CONFIG("snddmic", "hw", &snd_snddmic_hw_config),
        SND_PCM_CONFIG("sndspdif", "hw", &snd_sndspdif_hw_config),
    /* SND_PCM_CONFIG("default", "hw", &snd_pcm_asym_config), */
    SND_PCM_CONFIG("default", "asym", &snd_pcm_asym_config), //pcm.!default
    SND_PCM_CONFIG("ctl.!default", "hw", &snd_audiocodec_hw_config), //ctl.!default
    SND_PCM_CONFIG("PlaybackSoftVol1", "softvol", &snd_pcm_softvol_config1),
    SND_PCM_CONFIG("PlaybackSoftVol2", "softvol", &snd_pcm_softvol_config2),
    SND_PCM_CONFIG("PlaybackRoute", "route", &snd_pcm_route_config),
    SND_PCM_CONFIG("PlaybackPlug", "plug", &snd_pcm_plug_config),
#ifdef CONFIG_AW_ALSA_PLUGINS_SONA_AUDIOAEF
    SND_PCM_CONFIG("PlaybackSona", "sona_audioaef", &snd_pcm_sona_audioaef_config),
#endif
    SND_PCM_CONFIG("PlaybackFile", "file", &snd_pcm_file_pb_config),
    SND_PCM_CONFIG("CaptureFile", "file", &snd_pcm_file_cap_config),
};

REGISTER_SND_PCM_GLOBAL_CONFIGS(snd_pcm_global_configs);
