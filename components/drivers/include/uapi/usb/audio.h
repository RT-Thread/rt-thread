/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     zyh          the first version
 */

#ifndef __UAPI_USB_AUDIO_H__
#define __UAPI_USB_AUDIO_H__

#include <rtdef.h>

/* bInterfaceProtocol values to denote the version of the standard used */
#define UAC_VERSION_1                   (0x00U)
#define UAC_VERSION_2                   (0x20U)
#define UAC_VERSION_3                   (0x30U)

/* A.2 Audio Interface Subclass Codes */
#define USB_SUBCLASS_AUDIOCONTROL       (0x01U)
#define USB_SUBCLASS_AUDIOSTREAMING     (0x02U)
#define USB_SUBCLASS_MIDISTREAMING      (0x03U)

/* A.5 Audio Class-Specific AC Interface Descriptor Subtypes */
#define UAC_HEADER                      (0x01U)
#define UAC_INPUT_TERMINAL              (0x02U)
#define UAC_OUTPUT_TERMINAL             (0x03U)
#define UAC_MIXER_UNIT                  (0x04U)
#define UAC_SELECTOR_UNIT               (0x05U)
#define UAC_FEATURE_UNIT                (0x06U)
#define UAC1_PROCESSING_UNIT            (0x07U)
#define UAC1_EXTENSION_UNIT             (0x08U)

/* A.6 Audio Class-Specific AS Interface Descriptor Subtypes */
#define UAC_AS_GENERAL                  (0x01U)
#define UAC_FORMAT_TYPE                 (0x02U)
#define UAC_FORMAT_SPECIFIC             (0x03U)

/* A.7 Processing Unit Process Types */
#define UAC_PROCESS_UNDEFINED           (0x00U)
#define UAC_PROCESS_UP_DOWNMIX          (0x01U)
#define UAC_PROCESS_DOLBY_PROLOGIC      (0x02U)
#define UAC_PROCESS_STEREO_EXTENDER     (0x03U)
#define UAC_PROCESS_REVERB              (0x04U)
#define UAC_PROCESS_CHORUS              (0x05U)
#define UAC_PROCESS_DYN_RANGE_COMP      (0x06U)

/* A.8 Audio Class-Specific Endpoint Descriptor Subtypes */
#define UAC_EP_GENERAL                  (0x01U)

/* A.9 Audio Class-Specific Request Codes */
#define UAC_SET_                        (0x00U)
#define UAC_GET_                        (0x80U)

#define UAC__CUR                        (0x01U)
#define UAC__MIN                        (0x02U)
#define UAC__MAX                        (0x03U)
#define UAC__RES                        (0x04U)
#define UAC__MEM                        (0x05U)

#define UAC_SET_CUR                     (UAC_SET_ | UAC__CUR)
#define UAC_GET_CUR                     (UAC_GET_ | UAC__CUR)
#define UAC_SET_MIN                     (UAC_SET_ | UAC__MIN)
#define UAC_GET_MIN                     (UAC_GET_ | UAC__MIN)
#define UAC_SET_MAX                     (UAC_SET_ | UAC__MAX)
#define UAC_GET_MAX                     (UAC_GET_ | UAC__MAX)
#define UAC_SET_RES                     (UAC_SET_ | UAC__RES)
#define UAC_GET_RES                     (UAC_GET_ | UAC__RES)
#define UAC_SET_MEM                     (UAC_SET_ | UAC__MEM)
#define UAC_GET_MEM                     (UAC_GET_ | UAC__MEM)

#define UAC_GET_STAT                    (0xffU)

/* A.10 Control Selector Codes */

/* A.10.1 Terminal Control Selectors */
#define UAC_TERM_COPY_PROTECT           (0x01U)

/* A.10.2 Feature Unit Control Selectors */
#define UAC_FU_MUTE                     (0x01U)
#define UAC_FU_VOLUME                   (0x02U)
#define UAC_FU_BASS                     (0x03U)
#define UAC_FU_MID                      (0x04U)
#define UAC_FU_TREBLE                   (0x05U)
#define UAC_FU_GRAPHIC_EQUALIZER        (0x06U)
#define UAC_FU_AUTOMATIC_GAIN           (0x07U)
#define UAC_FU_DELAY                    (0x08U)
#define UAC_FU_BASS_BOOST               (0x09U)
#define UAC_FU_LOUDNESS                 (0x0aU)

#define UAC_CONTROL_BIT(CS)             (0x01U << ((CS) - 1))

/* A.10.3.1 Up/Down-mix Processing Unit Controls Selectors */
#define UAC_UD_ENABLE                   (0x01U)
#define UAC_UD_MODE_SELECT              (0x02U)

/* A.10.3.2 Dolby Prologic (tm) Processing Unit Controls Selectors */
#define UAC_DP_ENABLE                   (0x01U)
#define UAC_DP_MODE_SELECT              (0x02U)

/* A.10.3.3 3D Stereo Extender Processing Unit Control Selectors */
#define UAC_3D_ENABLE                   (0x01U)
#define UAC_3D_SPACE                    (0x02U)

/* A.10.3.4 Reverberation Processing Unit Control Selectors */
#define UAC_REVERB_ENABLE               (0x01U)
#define UAC_REVERB_LEVEL                (0x02U)
#define UAC_REVERB_TIME                 (0x03U)
#define UAC_REVERB_FEEDBACK             (0x04U)

/* A.10.3.5 Chorus Processing Unit Control Selectors */
#define UAC_CHORUS_ENABLE               (0x01U)
#define UAC_CHORUS_LEVEL                (0x02U)
#define UAC_CHORUS_RATE                 (0x03U)
#define UAC_CHORUS_DEPTH                (0x04U)

/* A.10.3.6 Dynamic Range Compressor Unit Control Selectors */
#define UAC_DCR_ENABLE                  (0x01U)
#define UAC_DCR_RATE                    (0x02U)
#define UAC_DCR_MAXAMPL                 (0x03U)
#define UAC_DCR_THRESHOLD               (0x04U)
#define UAC_DCR_ATTACK_TIME             (0x05U)
#define UAC_DCR_RELEASE_TIME            (0x06U)

/* A.10.4 Extension Unit Control Selectors */
#define UAC_XU_ENABLE                   (0x01U)

/* MIDI - A.1 MS Class-Specific Interface Descriptor Subtypes */
#define UAC_MS_HEADER                   (0x01U)
#define UAC_MIDI_IN_JACK                (0x02U)
#define UAC_MIDI_OUT_JACK               (0x03U)

/* MIDI - A.1 MS Class-Specific Endpoint Descriptor Subtypes */
#define UAC_MS_GENERAL                  (0x01U)

/* Terminals - 2.1 USB Terminal Types */
#define UAC_TERMINAL_UNDEFINED          (0x100U)
#define UAC_TERMINAL_STREAMING          (0x101U)
#define UAC_TERMINAL_VENDOR_SPEC        (0x1FFU)

/* Terminal Control Selectors */
/* 4.3.2  Class-Specific AC Interface Descriptor */
struct uac1_ac_header_descriptor {
    rt_uint8_t  bLength;                /* 8 + n */
    rt_uint8_t  bDescriptorType;        /* USB_DT_CS_INTERFACE */
    rt_uint8_t  bDescriptorSubtype;     /* UAC_MS_HEADER */
    rt_le16_t   bcdADC;                 /* 0x0100 */
    rt_le16_t   wTotalLength;           /* includes Unit and Terminal desc. */
    rt_uint8_t  bInCollection;          /* n */
    rt_uint8_t  baInterfaceNr[];        /* [n] */
} __attribute__ ((packed));

#define UAC_DT_AC_HEADER_SIZE(n)        (8 + (n))

/* As above, but more useful for defining your own descriptors: */
#define DECLARE_UAC_AC_HEADER_DESCRIPTOR(n)         \
struct uac1_ac_header_descriptor_##n {              \
    rt_uint8_t  bLength;                            \
    rt_uint8_t  bDescriptorType;                    \
    rt_uint8_t  bDescriptorSubtype;                 \
    rt_le16_t   bcdADC;                             \
    rt_le16_t   wTotalLength;                       \
    rt_uint8_t  bInCollection;                      \
    rt_uint8_t  baInterfaceNr[n];                   \
} __attribute__ ((packed))

/* 4.3.2.1 Input Terminal Descriptor */
struct uac_input_terminal_descriptor {
    rt_uint8_t  bLength;                /* in bytes: 12 */
    rt_uint8_t  bDescriptorType;        /* CS_INTERFACE descriptor type */
    rt_uint8_t  bDescriptorSubtype;     /* INPUT_TERMINAL descriptor subtype */
    rt_uint8_t  bTerminalID;            /* Constant uniquely terminal ID */
    rt_le16_t   wTerminalType;          /* USB Audio Terminal Types */
    rt_uint8_t  bAssocTerminal;         /* ID of the Output Terminal associated */
    rt_uint8_t  bNrChannels;            /* Number of logical output channels */
    rt_le16_t   wChannelConfig;
    rt_uint8_t  iChannelNames;
    rt_uint8_t  iTerminal;
} __attribute__ ((packed));

#define UAC_DT_INPUT_TERMINAL_SIZE                      (12)

/* Terminals - 2.2 Input Terminal Types */
#define UAC_INPUT_TERMINAL_UNDEFINED                    (0x200U)
#define UAC_INPUT_TERMINAL_MICROPHONE                   (0x201U)
#define UAC_INPUT_TERMINAL_DESKTOP_MICROPHONE           (0x202U)
#define UAC_INPUT_TERMINAL_PERSONAL_MICROPHONE          (0x203U)
#define UAC_INPUT_TERMINAL_OMNI_DIR_MICROPHONE          (0x204U)
#define UAC_INPUT_TERMINAL_MICROPHONE_ARRAY             (0x205U)
#define UAC_INPUT_TERMINAL_PROC_MICROPHONE_ARRAY        (0x206U)

/* Terminals - control selectors */

#define UAC_TERMINAL_CS_COPY_PROTECT_CONTROL            (0x01U)

/* 4.3.2.2 Output Terminal Descriptor */
struct uac1_output_terminal_descriptor {
    rt_uint8_t  bLength;                /* in bytes: 9 */
    rt_uint8_t  bDescriptorType;        /* CS_INTERFACE descriptor type */
    rt_uint8_t  bDescriptorSubtype;     /* OUTPUT_TERMINAL descriptor subtype */
    rt_uint8_t  bTerminalID;            /* Constant uniquely terminal ID */
    rt_le16_t   wTerminalType;          /* USB Audio Terminal Types */
    rt_uint8_t  bAssocTerminal;         /* ID of the Input Terminal associated */
    rt_uint8_t  bSourceID;              /* ID of the connected Unit or Terminal*/
    rt_uint8_t  iTerminal;
} __attribute__ ((packed));

#define UAC_DT_OUTPUT_TERMINAL_SIZE                     (9)

/* Terminals - 2.3 Output Terminal Types */
#define UAC_OUTPUT_TERMINAL_UNDEFINED                   (0x300U)
#define UAC_OUTPUT_TERMINAL_SPEAKER                     (0x301U)
#define UAC_OUTPUT_TERMINAL_HEADPHONES                  (0x302U)
#define UAC_OUTPUT_TERMINAL_HEAD_MOUNTED_DISPLAY_AUDIO  (0x303U)
#define UAC_OUTPUT_TERMINAL_DESKTOP_SPEAKER             (0x304U)
#define UAC_OUTPUT_TERMINAL_ROOM_SPEAKER                (0x305U)
#define UAC_OUTPUT_TERMINAL_COMMUNICATION_SPEAKER       (0x306U)
#define UAC_OUTPUT_TERMINAL_LOW_FREQ_EFFECTS_SPEAKER    (0x307U)

/* Terminals - 2.4 Bi-directional Terminal Types */
#define UAC_BIDIR_TERMINAL_UNDEFINED                    (0x400U)
#define UAC_BIDIR_TERMINAL_HANDSET                      (0x401U)
#define UAC_BIDIR_TERMINAL_HEADSET                      (0x402U)
#define UAC_BIDIR_TERMINAL_SPEAKER_PHONE                (0x403U)
#define UAC_BIDIR_TERMINAL_ECHO_SUPPRESSING             (0x404U)
#define UAC_BIDIR_TERMINAL_ECHO_CANCELING               (0x405U)

/* Set bControlSize = 2 as default setting */
#define UAC_DT_FEATURE_UNIT_SIZE(ch)                    (7 + ((ch) + 1) * 2)

/* As above, but more useful for defining your own descriptors: */
#define DECLARE_UAC_FEATURE_UNIT_DESCRIPTOR(ch)         \
struct uac_feature_unit_descriptor_##ch {               \
    rt_uint8_t  bLength;                                \
    rt_uint8_t  bDescriptorType;                        \
    rt_uint8_t  bDescriptorSubtype;                     \
    rt_uint8_t  bUnitID;                                \
    rt_uint8_t  bSourceID;                              \
    rt_uint8_t  bControlSize;                           \
    rt_le16_t   bmaControls[ch + 1];                    \
    rt_uint8_t  iFeature;                               \
} __attribute__ ((packed))

/* 4.3.2.3 Mixer Unit Descriptor */
struct uac_mixer_unit_descriptor {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubtype;
    rt_uint8_t  bUnitID;
    rt_uint8_t  bNrInPins;
    rt_uint8_t  baSourceID[];
} __attribute__ ((packed));

static inline rt_uint8_t uac_mixer_unit_bNrChannels(struct uac_mixer_unit_descriptor *desc)
{
    return desc->baSourceID[desc->bNrInPins];
}

static inline rt_uint32_t uac_mixer_unit_wChannelConfig(struct uac_mixer_unit_descriptor *desc,
                          int protocol)
{
    if (protocol == UAC_VERSION_1)
        return (desc->baSourceID[desc->bNrInPins + 2] << 8) |
            desc->baSourceID[desc->bNrInPins + 1];
    else
        return  (desc->baSourceID[desc->bNrInPins + 4] << 24) |
            (desc->baSourceID[desc->bNrInPins + 3] << 16) |
            (desc->baSourceID[desc->bNrInPins + 2] << 8)  |
            (desc->baSourceID[desc->bNrInPins + 1]);
}

static inline rt_uint8_t uac_mixer_unit_iChannelNames(struct uac_mixer_unit_descriptor *desc,
                        int protocol)
{
    return (protocol == UAC_VERSION_1) ?
        desc->baSourceID[desc->bNrInPins + 3] :
        desc->baSourceID[desc->bNrInPins + 5];
}

static inline rt_uint8_t *uac_mixer_unit_bmControls(struct uac_mixer_unit_descriptor *desc,
                          int protocol)
{
    switch (protocol) {
    case UAC_VERSION_1:
        return &desc->baSourceID[desc->bNrInPins + 4];
    case UAC_VERSION_2:
        return &desc->baSourceID[desc->bNrInPins + 6];
    case UAC_VERSION_3:
        return &desc->baSourceID[desc->bNrInPins + 2];
    default:
        return RT_NULL;
    }
}

static inline rt_uint16_t uac3_mixer_unit_wClusterDescrID(struct uac_mixer_unit_descriptor *desc)
{
    return (desc->baSourceID[desc->bNrInPins + 1] << 8) |
        desc->baSourceID[desc->bNrInPins];
}

static inline rt_uint8_t uac_mixer_unit_iMixer(struct uac_mixer_unit_descriptor *desc)
{
    rt_uint8_t *raw = (rt_uint8_t *) desc;
    return raw[desc->bLength - 1];
}

/* 4.3.2.4 Selector Unit Descriptor */
struct uac_selector_unit_descriptor {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubtype;
    rt_uint8_t  bUintID;
    rt_uint8_t  bNrInPins;
    rt_uint8_t  baSourceID[];
} __attribute__ ((packed));

static inline rt_uint8_t uac_selector_unit_iSelector(struct uac_selector_unit_descriptor *desc)
{
    rt_uint8_t *raw = (rt_uint8_t *) desc;
    return raw[desc->bLength - 1];
}

/* 4.3.2.5 Feature Unit Descriptor */
struct uac_feature_unit_descriptor {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubtype;
    rt_uint8_t  bUnitID;
    rt_uint8_t  bSourceID;
    rt_uint8_t  bControlSize;
    rt_uint8_t  bmaControls[0]; /* variable length */
} __attribute__((packed));

static inline rt_uint8_t uac_feature_unit_iFeature(struct uac_feature_unit_descriptor *desc)
{
    rt_uint8_t *raw = (rt_uint8_t *) desc;
    return raw[desc->bLength - 1];
}

/* 4.3.2.6 Processing Unit Descriptors */
struct uac_processing_unit_descriptor {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubtype;
    rt_uint8_t  bUnitID;
    rt_le16_t   wProcessType;
    rt_uint8_t  bNrInPins;
    rt_uint8_t  baSourceID[];
} __attribute__ ((packed));

static inline rt_uint8_t uac_processing_unit_bNrChannels(struct uac_processing_unit_descriptor *desc)
{
    return desc->baSourceID[desc->bNrInPins];
}

static inline rt_uint32_t uac_processing_unit_wChannelConfig(struct uac_processing_unit_descriptor *desc,
                               int protocol)
{
    if (protocol == UAC_VERSION_1)
        return (desc->baSourceID[desc->bNrInPins + 2] << 8) |
            desc->baSourceID[desc->bNrInPins + 1];
    else
        return  (desc->baSourceID[desc->bNrInPins + 4] << 24) |
            (desc->baSourceID[desc->bNrInPins + 3] << 16) |
            (desc->baSourceID[desc->bNrInPins + 2] << 8)  |
            (desc->baSourceID[desc->bNrInPins + 1]);
}

static inline rt_uint8_t uac_processing_unit_iChannelNames(struct uac_processing_unit_descriptor *desc,
                             int protocol)
{
    return (protocol == UAC_VERSION_1) ?
        desc->baSourceID[desc->bNrInPins + 3] :
        desc->baSourceID[desc->bNrInPins + 5];
}

static inline rt_uint8_t uac_processing_unit_bControlSize(struct uac_processing_unit_descriptor *desc,
                            int protocol)
{
    switch (protocol) {
    case UAC_VERSION_1:
        return desc->baSourceID[desc->bNrInPins + 4];
    case UAC_VERSION_2:
        return 2; /* in UAC2, this value is constant */
    case UAC_VERSION_3:
        return 4; /* in UAC3, this value is constant */
    default:
        return 1;
    }
}

static inline rt_uint8_t *uac_processing_unit_bmControls(struct uac_processing_unit_descriptor *desc,
                           int protocol)
{
    switch (protocol) {
    case UAC_VERSION_1:
        return &desc->baSourceID[desc->bNrInPins + 5];
    case UAC_VERSION_2:
        return &desc->baSourceID[desc->bNrInPins + 6];
    case UAC_VERSION_3:
        return &desc->baSourceID[desc->bNrInPins + 2];
    default:
        return RT_NULL;
    }
}

static inline rt_uint8_t uac_processing_unit_iProcessing(struct uac_processing_unit_descriptor *desc,
                           int protocol)
{
    rt_uint8_t control_size = uac_processing_unit_bControlSize(desc, protocol);

    switch (protocol) {
    case UAC_VERSION_1:
    case UAC_VERSION_2:
    default:
        return *(uac_processing_unit_bmControls(desc, protocol)
             + control_size);
    case UAC_VERSION_3:
        return 0; /* UAC3 does not have this field */
    }
}

static inline rt_uint8_t *uac_processing_unit_specific(struct uac_processing_unit_descriptor *desc,
                         int protocol)
{
    rt_uint8_t control_size = uac_processing_unit_bControlSize(desc, protocol);

    switch (protocol) {
    case UAC_VERSION_1:
    case UAC_VERSION_2:
    default:
        return uac_processing_unit_bmControls(desc, protocol)
            + control_size + 1;
    case UAC_VERSION_3:
        return uac_processing_unit_bmControls(desc, protocol)
            + control_size;
    }
}

/*
 * Extension Unit (XU) has almost compatible layout with Processing Unit, but
 * on UAC2, it has a different bmControls size (bControlSize); it's 1 byte for
 * XU while 2 bytes for PU.  The last iExtension field is a one-byte index as
 * well as iProcessing field of PU.
 */
static inline rt_uint8_t uac_extension_unit_bControlSize(struct uac_processing_unit_descriptor *desc,
                           int protocol)
{
    switch (protocol) {
    case UAC_VERSION_1:
        return desc->baSourceID[desc->bNrInPins + 4];
    case UAC_VERSION_2:
        return 1; /* in UAC2, this value is constant */
    case UAC_VERSION_3:
        return 4; /* in UAC3, this value is constant */
    default:
        return 1;
    }
}

static inline rt_uint8_t uac_extension_unit_iExtension(struct uac_processing_unit_descriptor *desc,
                         int protocol)
{
    rt_uint8_t control_size = uac_extension_unit_bControlSize(desc, protocol);

    switch (protocol) {
    case UAC_VERSION_1:
    case UAC_VERSION_2:
    default:
        return *(uac_processing_unit_bmControls(desc, protocol)
             + control_size);
    case UAC_VERSION_3:
        return 0; /* UAC3 does not have this field */
    }
}

/* 4.5.2 Class-Specific AS Interface Descriptor */
struct uac1_as_header_descriptor {
    rt_uint8_t  bLength;                    /* in bytes: 7 */
    rt_uint8_t  bDescriptorType;            /* USB_DT_CS_INTERFACE */
    rt_uint8_t  bDescriptorSubtype;         /* AS_GENERAL */
    rt_uint8_t  bTerminalLink;              /* Terminal ID of connected Terminal */
    rt_uint8_t  bDelay;                     /* Delay introduced by the data path */
    rt_le16_t   wFormatTag;                 /* The Audio Data Format */
} __attribute__ ((packed));

#define UAC_DT_AS_HEADER_SIZE               (7)

/* Formats - A.1.1 Audio Data Format Type I Codes */
#define UAC_FORMAT_TYPE_I_UNDEFINED         (0x00U)
#define UAC_FORMAT_TYPE_I_PCM               (0x01U)
#define UAC_FORMAT_TYPE_I_PCM8              (0x02U)
#define UAC_FORMAT_TYPE_I_IEEE_FLOAT        (0x03U)
#define UAC_FORMAT_TYPE_I_ALAW              (0x04U)
#define UAC_FORMAT_TYPE_I_MULAW             (0x05U)

struct uac_format_type_i_continuous_descriptor {
    rt_uint8_t  bLength;                    /* in bytes: 8 + (ns * 3) */
    rt_uint8_t  bDescriptorType;            /* USB_DT_CS_INTERFACE */
    rt_uint8_t  bDescriptorSubtype;         /* FORMAT_TYPE */
    rt_uint8_t  bFormatType;                /* FORMAT_TYPE_1 */
    rt_uint8_t  bNrChannels;                /* physical channels in the stream */
    rt_uint8_t  bSubframeSize;              /* */
    rt_uint8_t  bBitResolution;
    rt_uint8_t  bSamFreqType;
    rt_uint8_t  tLowerSamFreq[3];
    rt_uint8_t  tUpperSamFreq[3];
} __attribute__ ((packed));

#define UAC_FORMAT_TYPE_I_CONTINUOUS_DESC_SIZE    14

struct uac_format_type_i_discrete_descriptor {
    rt_uint8_t  bLength;                    /* in bytes: 8 + (ns * 3) */
    rt_uint8_t  bDescriptorType;            /* USB_DT_CS_INTERFACE */
    rt_uint8_t  bDescriptorSubtype;         /* FORMAT_TYPE */
    rt_uint8_t  bFormatType;                /* FORMAT_TYPE_1 */
    rt_uint8_t  bNrChannels;                /* physical channels in the stream */
    rt_uint8_t  bSubframeSize;              /* */
    rt_uint8_t  bBitResolution;
    rt_uint8_t  bSamFreqType;
    rt_uint8_t  tSamFreq[][3];
} __attribute__ ((packed));

#define DECLARE_UAC_FORMAT_TYPE_I_DISCRETE_DESC(n)          \
struct uac_format_type_i_discrete_descriptor_##n {          \
    rt_uint8_t  bLength;                                    \
    rt_uint8_t  bDescriptorType;                            \
    rt_uint8_t  bDescriptorSubtype;                         \
    rt_uint8_t  bFormatType;                                \
    rt_uint8_t  bNrChannels;                                \
    rt_uint8_t  bSubframeSize;                              \
    rt_uint8_t  bBitResolution;                             \
    rt_uint8_t  bSamFreqType;                               \
    rt_uint8_t  tSamFreq[n][3];                             \
} __attribute__ ((packed))

#define UAC_FORMAT_TYPE_I_DISCRETE_DESC_SIZE(n)             (8 + (n * 3))

struct uac_format_type_i_ext_descriptor {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubtype;
    rt_uint8_t  bFormatType;
    rt_uint8_t  bSubslotSize;
    rt_uint8_t  bBitResolution;
    rt_uint8_t  bHeaderLength;
    rt_uint8_t  bControlSize;
    rt_uint8_t  bSideBandProtocol;
} __attribute__((packed));

/* Formats - Audio Data Format Type I Codes */

#define UAC_FORMAT_TYPE_II_MPEG         (0x1001U)
#define UAC_FORMAT_TYPE_II_AC3          (0x1002U)

struct uac_format_type_ii_discrete_descriptor {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubtype;
    rt_uint8_t  bFormatType;
    rt_le16_t   wMaxBitRate;
    rt_le16_t   wSamplesPerFrame;
    rt_uint8_t  bSamFreqType;
    rt_uint8_t  tSamFreq[][3];
} __attribute__((packed));

struct uac_format_type_ii_ext_descriptor {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubtype;
    rt_uint8_t  bFormatType;
    rt_le16_t   wMaxBitRate;
    rt_le16_t   wSamplesPerFrame;
    rt_uint8_t  bHeaderLength;
    rt_uint8_t  bSideBandProtocol;
} __attribute__((packed));

/* type III */
#define UAC_FORMAT_TYPE_III_IEC1937_AC3                 (0x2001U)
#define UAC_FORMAT_TYPE_III_IEC1937_MPEG1_LAYER1        (0x2002U)
#define UAC_FORMAT_TYPE_III_IEC1937_MPEG2_NOEXT         (0x2003U)
#define UAC_FORMAT_TYPE_III_IEC1937_MPEG2_EXT           (0x2004U)
#define UAC_FORMAT_TYPE_III_IEC1937_MPEG2_LAYER1_LS     (0x2005U)
#define UAC_FORMAT_TYPE_III_IEC1937_MPEG2_LAYER23_LS    (0x2006U)

/* Formats - A.2 Format Type Codes */
#define UAC_FORMAT_TYPE_UNDEFINED                       (0x00U)
#define UAC_FORMAT_TYPE_I                               (0x01U)
#define UAC_FORMAT_TYPE_II                              (0x02U)
#define UAC_FORMAT_TYPE_III                             (0x03U)
#define UAC_EXT_FORMAT_TYPE_I                           (0x81U)
#define UAC_EXT_FORMAT_TYPE_II                          (0x82U)
#define UAC_EXT_FORMAT_TYPE_III                         (0x83U)

struct uac_iso_endpoint_descriptor {
    rt_uint8_t  bLength;                /* in bytes: 7 */
    rt_uint8_t  bDescriptorType;        /* USB_DT_CS_ENDPOINT */
    rt_uint8_t  bDescriptorSubtype;     /* EP_GENERAL */
    rt_uint8_t  bmAttributes;
    rt_uint8_t  bLockDelayUnits;
    rt_le16_t   wLockDelay;
} __attribute__((packed));
#define UAC_ISO_ENDPOINT_DESC_SIZE      (7)

#define UAC_EP_CS_ATTR_SAMPLE_RATE      (0x01U)
#define UAC_EP_CS_ATTR_PITCH_CONTROL    (0x02U)
#define UAC_EP_CS_ATTR_FILL_MAX         (0x80U)

/* status word format (3.7.1.1) */

#define UAC1_STATUS_TYPE_ORIG_MASK                  (0x0fU)
#define UAC1_STATUS_TYPE_ORIG_AUDIO_CONTROL_IF      (0x00U)
#define UAC1_STATUS_TYPE_ORIG_AUDIO_STREAM_IF       (0x01U)
#define UAC1_STATUS_TYPE_ORIG_AUDIO_STREAM_EP       (0x02U)

#define UAC1_STATUS_TYPE_IRQ_PENDING                (0x01U << 7)
#define UAC1_STATUS_TYPE_MEM_CHANGED                (0x01U << 6)

struct uac1_status_word {
    rt_uint8_t  bStatusType;
    rt_uint8_t  bOriginator;
} __attribute__((packed));


#endif /* __UAPI_USB_AUDIO_H__ */
