/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __VIRTIO_SOUND_H__
#define __VIRTIO_SOUND_H__

#include <drivers/core/dm.h>

#define VIRTIO_SOUND_F_CTLS     1

struct virtio_snd_config
{
    /* available physical jacks */
    rt_le32_t jacks;
    /* available PCM streams */
    rt_le32_t streams;
    /* available channel maps */
    rt_le32_t chmaps;
    /* available control elements if VIRTIO_SND_F_CTLS has been negotiated */
    rt_le32_t controls;
};

/* supported dataflow directions */
enum
{
    VIRTIO_SND_D_OUTPUT = 0,
    VIRTIO_SND_D_INPUT
};

enum
{
    /* jack control request types */
    VIRTIO_SND_R_JACK_INFO = 1,
    VIRTIO_SND_R_JACK_REMAP,

    /* PCM control request types */
    VIRTIO_SND_R_PCM_INFO = 0x0100,
    VIRTIO_SND_R_PCM_SET_PARAMS,
    VIRTIO_SND_R_PCM_PREPARE,
    VIRTIO_SND_R_PCM_RELEASE,
    VIRTIO_SND_R_PCM_START,
    VIRTIO_SND_R_PCM_STOP,

    /* channel map control request types */
    VIRTIO_SND_R_CHMAP_INFO = 0x0200,

    /* jack event types */
    VIRTIO_SND_EVT_JACK_CONNECTED = 0x1000,
    VIRTIO_SND_EVT_JACK_DISCONNECTED,

    /* PCM event types */
    VIRTIO_SND_EVT_PCM_PERIOD_ELAPSED = 0x1100,
    VIRTIO_SND_EVT_PCM_XRUN,

    /* common status codes */
    VIRTIO_SND_S_OK = 0x8000,
    VIRTIO_SND_S_BAD_MSG,
    VIRTIO_SND_S_NOT_SUPP,
    VIRTIO_SND_S_IO_ERR
};

/* common header */
struct virtio_snd_hdr
{
    rt_le32_t code;
};

/* event notification */
struct virtio_snd_event
{
    /* VIRTIO_SND_EVT_XXX */
    struct virtio_snd_hdr hdr;
    /* optional event data */
    rt_le32_t data;
};

/* common control request to query an item information */
struct virtio_snd_query_info
{
    /* VIRTIO_SND_R_XXX_INFO */
    struct virtio_snd_hdr hdr;
    /* item start identifier */
    rt_le32_t start_id;
    /* item count to query */
    rt_le32_t count;
    /* item information size in bytes */
    rt_le32_t size;
};

/* common item information header */
struct virtio_snd_info
{
    /* function group node id (High Definition Audio Specification 7.1.2) */
    rt_le32_t hda_fn_nid;
};

struct virtio_snd_jack_hdr
{
    /* VIRTIO_SND_R_JACK_XXX */
    struct virtio_snd_hdr hdr;
    /* 0 ... virtio_snd_config::jacks - 1 */
    rt_le32_t jack_id;
};

/* supported jack features */
enum
{
    VIRTIO_SND_JACK_F_REMAP = 0
};

struct virtio_snd_jack_info
{
    /* common header */
    struct virtio_snd_info hdr;
    /* supported feature bit map (1 << VIRTIO_SND_JACK_F_XXX) */
    rt_le32_t features;
    /* pin configuration (High Definition Audio Specification 7.3.3.31) */
    rt_le32_t hda_reg_defconf;
    /* pin capabilities (High Definition Audio Specification 7.3.4.9) */
    rt_le32_t hda_reg_caps;
    /* current jack connection status (0: disconnected, 1: connected) */
    rt_uint8_t connected;

    rt_uint8_t padding[7];
};

/* jack remapping control request */
struct virtio_snd_jack_remap
{
    /* .code = VIRTIO_SND_R_JACK_REMAP */
    struct virtio_snd_jack_hdr hdr;
    /* selected association number */
    rt_le32_t association;
    /* selected sequence number */
    rt_le32_t sequence;
};

struct virtio_snd_pcm_hdr
{
    /* VIRTIO_SND_R_PCM_XXX */
    struct virtio_snd_hdr hdr;
    /* 0 ... virtio_snd_config::streams - 1 */
    rt_le32_t stream_id;
};

/* supported PCM stream features */
enum
{
    VIRTIO_SND_PCM_F_SHMEM_HOST = 0,
    VIRTIO_SND_PCM_F_SHMEM_GUEST,
    VIRTIO_SND_PCM_F_MSG_POLLING,
    VIRTIO_SND_PCM_F_EVT_SHMEM_PERIODS,
    VIRTIO_SND_PCM_F_EVT_XRUNS
};

/* supported PCM sample formats */
enum
{
    /* analog formats (width / physical width) */
    VIRTIO_SND_PCM_FMT_IMA_ADPCM = 0,   /*  4 /  4 bits */
    VIRTIO_SND_PCM_FMT_MU_LAW,          /*  8 /  8 bits */
    VIRTIO_SND_PCM_FMT_A_LAW,           /*  8 /  8 bits */
    VIRTIO_SND_PCM_FMT_S8,              /*  8 /  8 bits */
    VIRTIO_SND_PCM_FMT_U8,              /*  8 /  8 bits */
    VIRTIO_SND_PCM_FMT_S16,             /* 16 / 16 bits */
    VIRTIO_SND_PCM_FMT_U16,             /* 16 / 16 bits */
    VIRTIO_SND_PCM_FMT_S18_3,           /* 18 / 24 bits */
    VIRTIO_SND_PCM_FMT_U18_3,           /* 18 / 24 bits */
    VIRTIO_SND_PCM_FMT_S20_3,           /* 20 / 24 bits */
    VIRTIO_SND_PCM_FMT_U20_3,           /* 20 / 24 bits */
    VIRTIO_SND_PCM_FMT_S24_3,           /* 24 / 24 bits */
    VIRTIO_SND_PCM_FMT_U24_3,           /* 24 / 24 bits */
    VIRTIO_SND_PCM_FMT_S20,             /* 20 / 32 bits */
    VIRTIO_SND_PCM_FMT_U20,             /* 20 / 32 bits */
    VIRTIO_SND_PCM_FMT_S24,             /* 24 / 32 bits */
    VIRTIO_SND_PCM_FMT_U24,             /* 24 / 32 bits */
    VIRTIO_SND_PCM_FMT_S32,             /* 32 / 32 bits */
    VIRTIO_SND_PCM_FMT_U32,             /* 32 / 32 bits */
    VIRTIO_SND_PCM_FMT_FLOAT,           /* 32 / 32 bits */
    VIRTIO_SND_PCM_FMT_FLOAT64,         /* 64 / 64 bits */
    /* digital formats (width / physical width) */
    VIRTIO_SND_PCM_FMT_DSD_U8,          /*  8 /  8 bits */
    VIRTIO_SND_PCM_FMT_DSD_U16,         /* 16 / 16 bits */
    VIRTIO_SND_PCM_FMT_DSD_U32,         /* 32 / 32 bits */
    VIRTIO_SND_PCM_FMT_IEC958_SUBFRAME  /* 32 / 32 bits */
};

/* supported PCM frame rates */
enum
{
    VIRTIO_SND_PCM_RATE_5512 = 0,
    VIRTIO_SND_PCM_RATE_8000,
    VIRTIO_SND_PCM_RATE_11025,
    VIRTIO_SND_PCM_RATE_16000,
    VIRTIO_SND_PCM_RATE_22050,
    VIRTIO_SND_PCM_RATE_32000,
    VIRTIO_SND_PCM_RATE_44100,
    VIRTIO_SND_PCM_RATE_48000,
    VIRTIO_SND_PCM_RATE_64000,
    VIRTIO_SND_PCM_RATE_88200,
    VIRTIO_SND_PCM_RATE_96000,
    VIRTIO_SND_PCM_RATE_176400,
    VIRTIO_SND_PCM_RATE_192000,
    VIRTIO_SND_PCM_RATE_384000
};

struct virtio_snd_pcm_info
{
    /* common header */
    struct virtio_snd_info hdr;
    /* supported feature bit map (1 << VIRTIO_SND_PCM_F_XXX) */
    rt_le32_t features;
    /* supported sample format bit map (1 << VIRTIO_SND_PCM_FMT_XXX) */
    rt_le64_t formats;
    /* supported frame rate bit map (1 << VIRTIO_SND_PCM_RATE_XXX) */
    rt_le64_t rates;
    /* dataflow direction (VIRTIO_SND_D_XXX) */
    rt_uint8_t direction;
    /* minimum # of supported channels */
    rt_uint8_t channels_min;
    /* maximum # of supported channels */
    rt_uint8_t channels_max;

    rt_uint8_t padding[5];
};

/* set PCM stream format */
struct virtio_snd_pcm_set_params
{
    /* .code = VIRTIO_SND_R_PCM_SET_PARAMS */
    struct virtio_snd_pcm_hdr hdr;
    /* size of the hardware buffer */
    rt_le32_t buffer_bytes;
    /* size of the hardware period */
    rt_le32_t period_bytes;
    /* selected feature bit map (1 << VIRTIO_SND_PCM_F_XXX) */
    rt_le32_t features;
    /* selected # of channels */
    rt_uint8_t channels;
    /* selected sample format (VIRTIO_SND_PCM_FMT_XXX) */
    rt_uint8_t format;
    /* selected frame rate (VIRTIO_SND_PCM_RATE_XXX) */
    rt_uint8_t rate;

    rt_uint8_t padding;
};

/* I/O request header */
struct virtio_snd_pcm_xfer
{
    /* 0 ... virtio_snd_config::streams - 1 */
    rt_le32_t stream_id;
};

/* I/O request status */
struct virtio_snd_pcm_status
{
    /* VIRTIO_SND_S_XXX */
    rt_le32_t status;
    /* current device latency */
    rt_le32_t latency_bytes;
};

struct virtio_snd_chmap_hdr
{
    /* VIRTIO_SND_R_CHMAP_XXX */
    struct virtio_snd_hdr hdr;
    /* 0 ... virtio_snd_config::chmaps - 1 */
    rt_le32_t chmap_id;
};

/* standard channel position definition */
enum
{
    VIRTIO_SND_CHMAP_NONE = 0,  /* undefined */
    VIRTIO_SND_CHMAP_NA,        /* silent */
    VIRTIO_SND_CHMAP_MONO,      /* mono stream */
    VIRTIO_SND_CHMAP_FL,        /* front left */
    VIRTIO_SND_CHMAP_FR,        /* front right */
    VIRTIO_SND_CHMAP_RL,        /* rear left */
    VIRTIO_SND_CHMAP_RR,        /* rear right */
    VIRTIO_SND_CHMAP_FC,        /* front center */
    VIRTIO_SND_CHMAP_LFE,       /* low frequency (LFE) */
    VIRTIO_SND_CHMAP_SL,        /* side left */
    VIRTIO_SND_CHMAP_SR,        /* side right */
    VIRTIO_SND_CHMAP_RC,        /* rear center */
    VIRTIO_SND_CHMAP_FLC,       /* front left center */
    VIRTIO_SND_CHMAP_FRC,       /* front right center */
    VIRTIO_SND_CHMAP_RLC,       /* rear left center */
    VIRTIO_SND_CHMAP_RRC,       /* rear right center */
    VIRTIO_SND_CHMAP_FLW,       /* front left wide */
    VIRTIO_SND_CHMAP_FRW,       /* front right wide */
    VIRTIO_SND_CHMAP_FLH,       /* front left high */
    VIRTIO_SND_CHMAP_FCH,       /* front center high */
    VIRTIO_SND_CHMAP_FRH,       /* front right high */
    VIRTIO_SND_CHMAP_TC,        /* top center */
    VIRTIO_SND_CHMAP_TFL,       /* top front left */
    VIRTIO_SND_CHMAP_TFR,       /* top front right */
    VIRTIO_SND_CHMAP_TFC,       /* top front center */
    VIRTIO_SND_CHMAP_TRL,       /* top rear left */
    VIRTIO_SND_CHMAP_TRR,       /* top rear right */
    VIRTIO_SND_CHMAP_TRC,       /* top rear center */
    VIRTIO_SND_CHMAP_TFLC,      /* top front left center */
    VIRTIO_SND_CHMAP_TFRC,      /* top front right center */
    VIRTIO_SND_CHMAP_TSL,       /* top side left */
    VIRTIO_SND_CHMAP_TSR,       /* top side right */
    VIRTIO_SND_CHMAP_LLFE,      /* left LFE */
    VIRTIO_SND_CHMAP_RLFE,      /* right LFE */
    VIRTIO_SND_CHMAP_BC,        /* bottom center */
    VIRTIO_SND_CHMAP_BLC,       /* bottom left center */
    VIRTIO_SND_CHMAP_BRC        /* bottom right center */
};

/* maximum possible number of channels */
#define VIRTIO_SND_CHMAP_MAX_SIZE   18

struct virtio_snd_chmap_info
{
    /* common header */
    struct virtio_snd_info hdr;
    /* dataflow direction (VIRTIO_SND_D_XXX) */
    rt_uint8_t direction;
    /* # of valid channel position values */
    rt_uint8_t channels;
    /* channel position values (VIRTIO_SND_CHMAP_XXX) */
    rt_uint8_t positions[VIRTIO_SND_CHMAP_MAX_SIZE];
};

enum
{
    VIRTIO_SND_CTL_ROLE_UNDEFINED = 0,
    VIRTIO_SND_CTL_ROLE_VOLUME,
    VIRTIO_SND_CTL_ROLE_MUTE,
    VIRTIO_SND_CTL_ROLE_GAIN
};

enum
{
    VIRTIO_SND_CTL_TYPE_BOOLEAN = 0,
    VIRTIO_SND_CTL_TYPE_INTEGER,
    VIRTIO_SND_CTL_TYPE_INTEGER64,
    VIRTIO_SND_CTL_TYPE_ENUMERATED,
    VIRTIO_SND_CTL_TYPE_BYTES,
    VIRTIO_SND_CTL_TYPE_IEC958
};

enum
{
    VIRTIO_SND_CTL_ACCESS_READ = 0,
    VIRTIO_SND_CTL_ACCESS_WRITE,
    VIRTIO_SND_CTL_ACCESS_VOLATILE,
    VIRTIO_SND_CTL_ACCESS_INACTIVE,
    VIRTIO_SND_CTL_ACCESS_TLV_READ,
    VIRTIO_SND_CTL_ACCESS_TLV_WRITE,
    VIRTIO_SND_CTL_ACCESS_TLV_COMMAND
};

struct virtio_snd_ctl_info
{
    struct virtio_snd_info hdr;
    rt_le32_t role;
    rt_le32_t type;
    rt_le32_t access; /* 1 << VIRTIO_SND_CTL_ACCESS_XXX */
    rt_le32_t count;
    rt_le32_t index;
    rt_uint8_t name[44];
    union
    {
        struct
        {
            rt_le32_t min;
            rt_le32_t max;
            rt_le32_t step;
        } integer;
        struct
        {
            rt_le64_t min;
            rt_le64_t max;
            rt_le64_t step;
        } integer64;
        struct
        {
            rt_le32_t items;
        } enumerated;
    } value;
};

struct virtio_snd_ctl_enum_item
{
    rt_uint8_t item[64];
};

struct virtio_snd_ctl_iec958
{
    rt_uint8_t status[24];      /* AES/IEC958 channel status bits */
    rt_uint8_t subcode[147];    /* AES/IEC958 subcode bits */
    rt_uint8_t pad;             /* nothing */
    rt_uint8_t dig_subframe[4]; /* AES/IEC958 subframe bits */
};

struct virtio_snd_ctl_value
{
    union
    {
        rt_le32_t integer[128];
        rt_le64_t integer64[64];
        rt_le32_t enumerated[128];
        rt_uint8_t bytes[512];
        struct virtio_snd_ctl_iec958 iec958;
    } value;
};

struct virtio_snd_ctl_tlv
{
    rt_le32_t type;
    rt_le32_t length;
    rt_le32_t value[];
};

enum
{
    VIRTIO_SND_CTL_EVT_MASK_VALUE = 0,
    VIRTIO_SND_CTL_EVT_MASK_INFO,
    VIRTIO_SND_CTL_EVT_MASK_TLV
};

struct virtio_snd_ctl_event
{
    struct virtio_snd_hdr hdr; /* .code = VIRTIO_SND_EVT_CTL_NOTIFY */
    rt_le16_t control_id;
    rt_le16_t mask; /* 1 << VIRTIO_SND_CTL_EVT_MASK_XXX */
};

#endif /* __VIRTIO_SOUND_H__ */
