/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USB_AUDIO_H
#define USB_AUDIO_H

/** Audio Interface Subclass Codes
 * Refer to Table A-2 from audio10.pdf
 */
#define AUDIO_SUBCLASS_UNDEFINED      0x00
#define AUDIO_SUBCLASS_AUDIOCONTROL   0x01
#define AUDIO_SUBCLASS_AUDIOSTREAMING 0x02
#define AUDIO_SUBCLASS_MIDISTREAMING  0x03

#define AUDIO_PROTOCOL_UNDEFINED 0x00
#define AUDIO_PROTOCOLv20        0x20 /* IP version 2.0 */

/** Audio Class-Specific Request Codes
 * Refer to Table A-9 from audio10.pdf
 */
#define AUDIO_REQUEST_UNDEFINED 0x00
#define AUDIO_REQUEST_SET_CUR   0x01
#define AUDIO_REQUEST_GET_CUR   0x81
#define AUDIO_REQUEST_SET_MIN   0x02
#define AUDIO_REQUEST_GET_MIN   0x82
#define AUDIO_REQUEST_SET_MAX   0x03
#define AUDIO_REQUEST_GET_MAX   0x83
#define AUDIO_REQUEST_SET_RES   0x04
#define AUDIO_REQUEST_GET_RES   0x84
#define AUDIO_REQUEST_SET_MEM   0x05
#define AUDIO_REQUEST_GET_MEM   0x85
#define AUDIO_REQUEST_GET_STAT  0xFF

/** Audio Class-Specific Request Codes
 * Refer from audio20_final.pdf
 */
#define AUDIO_REQUEST_CUR   0x01
#define AUDIO_REQUEST_RANGE 0x02
/** Audio Class-Specific Control Interface Descriptor Subtypes
 * Refer to Table A-5 from audio10.pdf
 */
#define AUDIO_CONTROL_UNDEF                0x01U
#define AUDIO_CONTROL_HEADER               0x01U
#define AUDIO_CONTROL_INPUT_TERMINAL       0x02U
#define AUDIO_CONTROL_OUTPUT_TERMINAL      0x03U
#define AUDIO_CONTROL_MIXER_UNIT           0x04U
#define AUDIO_CONTROL_SELECTOR_UNIT        0x05U
#define AUDIO_CONTROL_FEATURE_UNIT         0x06U
#define AUDIO_CONTROL_EFFECT_UNIT          0x07U
#define AUDIO_CONTROL_PROCESSING_UNIT      0x08U
#define AUDIO_CONTROL_EXTENSION_UNIT       0x09U
#define AUDIO_CONTROL_CLOCK_SOURCE         0x0aU
#define AUDIO_CONTROL_CLOCK_SELECTOR       0x0bU
#define AUDIO_CONTROL_CLOCK_MULTIPLIER     0x0cU
#define AUDIO_CONTROL_SAMPLERATE_CONVERTER 0x0dU

/** Audio Class-Specific AS Interface Descriptor Subtypes
 * Refer to Table A-6 from audio10.pdf
 */
#define AUDIO_STREAMING_UNDEFINED   0x00U
#define AUDIO_STREAMING_GENERAL     0x01U
#define AUDIO_STREAMING_FORMAT_TYPE 0x02U
#define AUDIO_STREAMING_ENCODER     0x03U
#define AUDIO_STREAMING_DECODER     0x04U

/* Clock Source Descriptor Clock Types */
#define AUDIO_CLKSRC_EXTERNAL       0x00 /* External clock */
#define AUDIO_CLKSRC_INTERNAL_FIXED 0x01 /* Internal fixed clock */
#define AUDIO_CLKSRC_INTERNAL_VAR   0x02 /* Internal variable clock */
#define AUDIO_CLKSRC_INTERNAL_PROG  0x03 /* Internal programmable clock */

/* Effect Unit Effect Types */
#define AUDIO_EFFECT_UNDEF            0x00
#define AUDIO_EFFECT_PARAM_EQ_SECTION 0x01
#define AUDIO_EFFECT_REVERBERATION    0x02
#define AUDIO_EFFECT_MOD_DELAY        0x03
#define AUDIO_EFFECT_DYN_RANGE_COMP   0x04

/* Processing Unit Process Types */
#define AUDIO_PROCESS_UNDEFINED       0x00
#define AUDIO_PROCESS_UPDOWNMIX       0x01
#define AUDIO_PROCESS_DOLBY_PROLOGIC  0x02
#define AUDIO_PROCESS_STEREO_EXTENDER 0x03

/* Audio Class-Specific Endpoint Descriptor Subtypes */
#define AUDIO_ENDPOINT_UNDEFINED 0x00U
#define AUDIO_ENDPOINT_GENERAL   0x01U

/* Feature Unit Control Bits */
#define AUDIO_CONTROL_MUTE              0x0001
#define AUDIO_CONTROL_VOLUME            0x0002
#define AUDIO_CONTROL_BASS              0x0004
#define AUDIO_CONTROL_MID               0x0008
#define AUDIO_CONTROL_TREBLE            0x0010
#define AUDIO_CONTROL_GRAPHIC_EQUALIZER 0x0020
#define AUDIO_CONTROL_AUTOMATIC_GAIN    0x0040
#define AUDIO_CONTROL_DEALY             0x0080
#define AUDIO_CONTROL_BASS_BOOST        0x0100
#define AUDIO_CONTROL_LOUDNESS          0x0200

/* Encoder Type Codes */
#define AUDIO_ENCODER_UNDEF 0x00
#define AUDIO_ENCODER_OTHER 0x01
#define AUDIO_ENCODER_MPEG  0x02
#define AUDIO_ENCODER_AC3   0x03
#define AUDIO_ENCODER_WMA   0x04
#define AUDIO_ENCODER_DTS   0x05

/* Decoder Type Codes */
#define AUDIO_DECODER_UNDEF 0x00
#define AUDIO_DECODER_OTHER 0x01
#define AUDIO_DECODER_MPEG  0x02
#define AUDIO_DECODER_AC3   0x03
#define AUDIO_DECODER_WMA   0x04
#define AUDIO_DECODER_DTS   0x05

/* Audio Descriptor Types */
#define AUDIO_UNDEFINED_DESCRIPTOR_TYPE     0x20
#define AUDIO_DEVICE_DESCRIPTOR_TYPE        0x21
#define AUDIO_CONFIGURATION_DESCRIPTOR_TYPE 0x22
#define AUDIO_STRING_DESCRIPTOR_TYPE        0x23
#define AUDIO_INTERFACE_DESCRIPTOR_TYPE     0x24
#define AUDIO_ENDPOINT_DESCRIPTOR_TYPE      0x25

/* Audio Data Format Type I Codes */
#define AUDIO_FORMAT_TYPE_I_UNDEFINED 0x0000
#define AUDIO_FORMAT_PCM              0x0001
#define AUDIO_FORMAT_PCM8             0x0002
#define AUDIO_FORMAT_IEEE_FLOAT       0x0003
#define AUDIO_FORMAT_ALAW             0x0004
#define AUDIO_FORMAT_MULAW            0x0005

#define AUDIO_V2_FORMAT_PCM              0x00000001
#define AUDIO_V2_FORMAT_PCM8             0x00000002
#define AUDIO_V2_FORMAT_IEEE_FLOAT       0x00000004
#define AUDIO_V2_FORMAT_ALAW             0x00000008
#define AUDIO_V2_FORMAT_MULAW            0x00000010

/* bmChannelConfig: a bitmap field that indicates which spatial locations
 * are occupied by the channels present in the cluster. The bit allocations
 * are as follows:
 */
#define AUDIO_CHANNEL_M    0         /* Mono */
#define AUDIO_CHANNEL_FL   (1 << 0)  /*  Front Left */
#define AUDIO_CHANNEL_FR   (1 << 1)  /*  Front Right */
#define AUDIO_CHANNEL_FC   (1 << 2)  /*  Front Center */
#define AUDIO_CHANNEL_LFE  (1 << 3)  /*  Low Frequency Effects */
#define AUDIO_CHANNEL_BL   (1 << 4)  /*  Back Left */
#define AUDIO_CHANNEL_BR   (1 << 5)  /*  Back Right */
#define AUDIO_CHANNEL_FLC  (1 << 6)  /*  Front Left of Center */
#define AUDIO_CHANNEL_FRC  (1 << 7)  /*  Front Right of Center */
#define AUDIO_CHANNEL_BC   (1 << 8)  /*  Back Center */
#define AUDIO_CHANNEL_SL   (1 << 9)  /*  Side Left */
#define AUDIO_CHANNEL_SR   (1 << 10) /*  Side Right */
#define AUDIO_CHANNEL_TC   (1 << 11) /*  Top Center */
#define AUDIO_CHANNEL_TFL  (1 << 12) /*  Top Front Left */
#define AUDIO_CHANNEL_TFC  (1 << 13) /*  Top Front Center */
#define AUDIO_CHANNEL_TFR  (1 << 14) /*  Top Front Right */
#define AUDIO_CHANNEL_TBL  (1 << 15) /*  Top Back Left */
#define AUDIO_CHANNEL_TBC  (1 << 16) /*  Top Back Center */
#define AUDIO_CHANNEL_TBR  (1 << 17) /*  Top Back Right */
#define AUDIO_CHANNEL_TFLC (1 << 18) /*  Top Front Left of Center */
#define AUDIO_CHANNEL_TFRC (1 << 19) /*  Top Front Right of Center */
#define AUDIO_CHANNEL_LLFE (1 << 20) /*  Left Low Frequency Effects */
#define AUDIO_CHANNEL_RLFE (1 << 21) /*  Right Low Frequency Effects */
#define AUDIO_CHANNEL_TSL  (1 << 22) /*  Top Side Left */
#define AUDIO_CHANNEL_TSR  (1 << 23) /*  Top Side Right */
#define AUDIO_CHANNEL_BOC  (1 << 24) /*  Bottom Center */
#define AUDIO_CHANNEL_BLC  (1 << 25) /*  Back Left of Center */
#define AUDIO_CHANNEL_BRC  (1 << 26) /*  Back Right of Center */
                                     /* Bits 27-30: Reserved */
#define AUDIO_CHANNEL_RD (1 << 31)   /*  Raw Data */

/* Audio Function Category Codes */
#define AUDIO_CATEGORY_UNDEF      0x00 /* Undefined */
#define AUDIO_CATEGORY_SPEAKER    0x01 /* Desktop speaker */
#define AUDIO_CATEGORY_THEATER    0x02 /* Home theater */
#define AUDIO_CATEGORY_MICROPHONE 0x03 /* Microphone */
#define AUDIO_CATEGORY_HEADSET    0x04 /* Headset */
#define AUDIO_CATEGORY_TELEPHONE  0x05 /* Telephone */
#define AUDIO_CATEGORY_CONVERTER  0x06 /* Converter */
#define AUDIO_CATEGORY_RECORDER   0x07 /* Voice/Sound recorder */
#define AUDIO_CATEGORY_IO_BOX     0x08 /* I/O box */
#define AUDIO_CATEGORY_INSTRUMENT 0x09 /* Musical instrument */
#define AUDIO_CATEGORY_PROAUDIO   0x0a /* Pro-audio */
#define AUDIO_CATEGORY_AV         0x0b /* Audio/video */
#define AUDIO_CATEGORY_CONTROL    0x0c /* Control panel */
#define AUDIO_CATEGORY_OTHER      0xff

/* Clock Source Control Selectors */
#define AUDIO_CS_CONTROL_UNDEF       0x00
#define AUDIO_CS_CONTROL_SAM_FREQ    0x01
#define AUDIO_CS_CONTROL_CLOCK_VALID 0x02

/* Clock Selector Control Selectors */
#define AUDIO_CX_CONTROL_UNDEF    0x00
#define AUDIO_CX_CONTROL_CLOCKSEL 0x01

/* Clock Multiplier Control Selectors */
#define AUDIO_CM_CONTROL_UNDEF       0x00
#define AUDIO_CM_CONTROL_NUMERATOR   0x01
#define AUDIO_CM_CONTROL_DENOMINATOR 0x02

/* Terminal Control Selectors */
#define AUDIO_TE_CONTROL_UNDEF        0x00
#define AUDIO_TE_CONTROL_COPY_PROTECT 0x01
#define AUDIO_TE_CONTROL_CONNECTOR    0x02
#define AUDIO_TE_CONTROL_OVERLOAD     0x03
#define AUDIO_TE_CONTROL_CLUSTER      0x04
#define AUDIO_TE_CONTROL_UNDERFLOW    0x05
#define AUDIO_TE_CONTROL_OVERFLOW     0x06
#define AUDIO_TE_CONTROL_LATENCY      0x07

/* Mixer Control Selectors */
#define AUDIO_MU_CONTROL_UNDEF     0x00
#define AUDIO_MU_CONTROL_MIXER     0x01
#define AUDIO_MU_CONTROL_CLUSTER   0x02
#define AUDIO_MU_CONTROL_UNDERFLOW 0x03
#define AUDIO_MU_CONTROL_OVERFLOW  0x04
#define AUDIO_MU_CONTROL_LATENCY   0x05

/* Selector Control Selectors */
#define AUDIO_SU_CONTROL_UNDEFINE 0x00
#define AUDIO_SU_CONTROL_SELECTOR 0x01
#define AUDIO_SU_CONTROL_LATENCY  0x02

/* Feature Unit Control Selectors */
#define AUDIO_FU_CONTROL_UNDEF        0x00
#define AUDIO_FU_CONTROL_MUTE         0x01
#define AUDIO_FU_CONTROL_VOLUME       0x02
#define AUDIO_FU_CONTROL_BASS         0x03
#define AUDIO_FU_CONTROL_MID          0x04
#define AUDIO_FU_CONTROL_TREBLE       0x05
#define AUDIO_FU_CONTROL_EQUALIZER    0x06
#define AUDIO_FU_CONTROL_AGC          0x07
#define AUDIO_FU_CONTROL_DELAY        0x08
#define AUDIO_FU_CONTROL_BASS_BOOST   0x09
#define AUDIO_FU_CONTROL_LOUDNESS     0x0a
#define AUDIO_FU_CONTROL_INP_GAIN     0x0b
#define AUDIO_FU_CONTROL_INP_GAIN_PAD 0x0c
#define AUDIO_FU_CONTROL_PHASE_INVERT 0x0d
#define AUDIO_FU_CONTROL_UNDERFLOW    0x0e
#define AUDIO_FU_CONTROL_OVERFLOW     0x0f
#define AUDIO_FU_CONTROL_LATENCY      0x10

#define AUDIO_V2_FU_CONTROL_UNDEF        0x00
#define AUDIO_V2_FU_CONTROL_MUTE         (0x03 << 0)
#define AUDIO_V2_FU_CONTROL_VOLUME       (0x03 << 2)
#define AUDIO_V2_FU_CONTROL_BASS         (0x03 << 4)
#define AUDIO_V2_FU_CONTROL_MID          (0x03 << 6)
#define AUDIO_V2_FU_CONTROL_TREBLE       (0x03 << 8)
#define AUDIO_V2_FU_CONTROL_EQUALIZER    (0x03 << 10)
#define AUDIO_V2_FU_CONTROL_AGC          (0x03 << 12)
#define AUDIO_V2_FU_CONTROL_DELAY        (0x03 << 14)
#define AUDIO_V2_FU_CONTROL_BASS_BOOST   (0x03 << 16)
#define AUDIO_V2_FU_CONTROL_LOUDNESS     (0x03 << 18)
#define AUDIO_V2_FU_CONTROL_INP_GAIN     (0x03 << 20)
#define AUDIO_V2_FU_CONTROL_INP_GAIN_PAD (0x03 << 22)
#define AUDIO_V2_FU_CONTROL_PHASE_INVERT (0x03 << 24)
#define AUDIO_V2_FU_CONTROL_UNDERFLOW    (0x03 << 26)
#define AUDIO_V2_FU_CONTROL_OVERFLOW     (0x03 << 28)

/* Parametric Equalizer Section Effect Unit Control Selectors */
#define AUDIO_PE_CONTROL_UNDEF      0x00
#define AUDIO_PE_CONTROL_ENABLE     0x01
#define AUDIO_PE_CONTROL_CENTERFREQ 0x02
#define AUDIO_PE_CONTROL_QFACTOR    0x03
#define AUDIO_PE_CONTROL_GAIN       0x04
#define AUDIO_PE_CONTROL_UNDERFLOW  0x05
#define AUDIO_PE_CONTROL_OVERFLOW   0x06
#define AUDIO_PE_CONTROL_LATENCY    0x07

/* Reverberation Effect Unit Control Selectors */
#define AUDIO_RV_CONTROL_UNDEF      0x00
#define AUDIO_RV_CONTROL_ENABLE     0x01
#define AUDIO_RV_CONTROL_TYPE       0x02
#define AUDIO_RV_CONTROL_LEVEL      0x03
#define AUDIO_RV_CONTROL_TIME       0x04
#define AUDIO_RV_CONTROL_FEEDBACK   0x05
#define AUDIO_RV_CONTROL_PREDELAY   0x06
#define AUDIO_RV_CONTROL_DENSITY    0x07
#define AUDIO_RV_CONTROL_HF_ROLLOFF 0x08
#define AUDIO_RV_CONTROL_UNDERFLOW  0x09
#define AUDIO_RV_CONTROL_OVERFLOW   0x0a
#define AUDIO_RV_CONTROL_LATENCY    0x0b

/* Modulation Delay Effect Unit Control Selectors */
#define AUDIO_MD_CONTROL_UNDEF     0x00
#define AUDIO_MD_CONTROL_ENABLE    0x01
#define AUDIO_MD_CONTROL_BALANCE   0x02
#define AUDIO_MD_CONTROL_RATE      0x03
#define AUDIO_MD_CONTROL_DEPTH     0x04
#define AUDIO_MD_CONTROL_TIME      0x05
#define AUDIO_MD_CONTROL_FEEDBACK  0x06
#define AUDIO_MD_CONTROL_UNDERFLOW 0x07
#define AUDIO_MD_CONTROL_OVERFLOW  0x08
#define AUDIO_MD_CONTROL_LATENCY   0x09

/* Dynamic Range Compressor Effect Unit Control Selectors */
#define AUDIO_DR_CONTROL_UNDEF        0x00
#define AUDIO_DR_CONTROL_ENABLE       0x01
#define AUDIO_DR_CONTROL_COMP_RATE    0x02
#define AUDIO_DR_CONTROL_MAXAMPL      0x03
#define AUDIO_DR_CONTROL_THRESHOLD    0x04
#define AUDIO_DR_CONTROL_ATTACK_TIME  0x05
#define AUDIO_DR_CONTROL_RELEASE_TIME 0x06
#define AUDIO_DR_CONTROL_UNDERFLOW    0x07
#define AUDIO_DR_CONTROL_OVERFLOW     0x08
#define AUDIO_DR_CONTROL_LATENCY      0x09

/* Up/Down-mix Processing Unit Control Selectors */
#define AUDIO_UD_CONTROL_UNDEF       0x00
#define AUDIO_UD_CONTROL_ENABLE      0x01
#define AUDIO_UD_CONTROL_MODE_SELECT 0x02
#define AUDIO_UD_CONTROL_CLUSTER     0x03
#define AUDIO_UD_CONTROL_UNDERFLOW   0x04
#define AUDIO_UD_CONTROL_OVERFLOW    0x05
#define AUDIO_UD_CONTROL_LATENCY     0x06

/* Dolby Prologic?Processing Unit Control Selectors */
#define AUDIO_DP_CONTROL_UNDEF       0x00
#define AUDIO_DP_CONTROL_ENABLE      0x01
#define AUDIO_DP_CONTROL_MODE_SELECT 0x02
#define AUDIO_DP_CONTROL_CLUSTER     0x03
#define AUDIO_DP_CONTROL_UNDERFLOW   0x04
#define AUDIO_DP_CONTROL_OVERFLOW    0x05
#define AUDIO_DP_CONTROL_LATENCY     0x06

/* Stereo Extender Processing Unit Control Selectors */
#define AUDIO_STEXT_CONTROL_UNDEF     0x00
#define AUDIO_STEXT_CONTROL_ENABLE    0x01
#define AUDIO_STEXT_CONTROL_WIDTH     0x02
#define AUDIO_STEXT_CONTROL_UNDERFLOW 0x03
#define AUDIO_STEXT_CONTROL_OVERFLOW  0x04
#define AUDIO_STEXT_CONTROL_LATENCY   0x05

/* Extension Unit Control Selectors */

#define AUDIO_XU_CONTROL_UNDEF     0x00
#define AUDIO_XU_CONTROL_ENABLE    0x01
#define AUDIO_XU_CONTROL_CLUSTER   0x02
#define AUDIO_XU_CONTROL_UNDERFLOW 0x03
#define AUDIO_XU_CONTROL_OVERFLOW  0x04
#define AUDIO_XU_CONTROL_LATENCY   0x05

/* AudioStreaming Interface Control Selectors */

#define AUDIO_AS_CONTROL_UNDEF        0x00
#define AUDIO_AS_CONTROL_ACT_ALT      0x01
#define AUDIO_AS_CONTROL_VAL_ALT      0x02
#define AUDIO_AS_CONTROL_AUDIO_FORMAT 0x03

/* Encoder Control Selectors */

#define AUDIO_EN_CONTROL_UNDEF       0x00
#define AUDIO_EN_CONTROL_BIT_RATE    0x01
#define AUDIO_EN_CONTROL_QUALITY     0x02
#define AUDIO_EN_CONTROL_VBR         0x03
#define AUDIO_EN_CONTROL_TYPE        0x04
#define AUDIO_EN_CONTROL_UNDERFLOW   0x05
#define AUDIO_EN_CONTROL_OVERFLOW    0x06
#define AUDIO_EN_CONTROL_ENCODER_ERR 0x07
#define AUDIO_EN_CONTROL_PARAM1      0x08
#define AUDIO_EN_CONTROL_PARAM2      0x09
#define AUDIO_EN_CONTROL_PARAM3      0x0a
#define AUDIO_EN_CONTROL_PARAM4      0x0b
#define AUDIO_EN_CONTROL_PARAM5      0x0c
#define AUDIO_EN_CONTROL_PARAM6      0x0d
#define AUDIO_EN_CONTROL_PARAM7      0x0e
#define AUDIO_EN_CONTROL_PARAM8      0x0f

/* MPEG Decoder Control Selectors */

#define AUDIO_MPGD_CONTROL_UNDEF      0x00
#define AUDIO_MPGD_CONTROL_DUAL_CHAN  0x01
#define AUDIO_MPGD_CONTROL_2ND_STEREO 0x02
#define AUDIO_MPGD_CONTROL_MULTILING  0x03
#define AUDIO_MPGD_CONTROL_DYN_RANGE  0x04
#define AUDIO_MPGD_CONTROL_SCALING    0x05
#define AUDIO_MPGD_CONTROL_HILO_SCALE 0x06
#define AUDIO_MPGD_CONTROL_UNDERFLOW  0x07
#define AUDIO_MPGD_CONTROL_OVERFLOW   0x08
#define AUDIO_MPGD_CONTROL_DECODE_ERR 0x09

/* AC-3 Decoder Control Selectors */

#define AUDIO_AC3D_CONTROL_UNDEF      0x00
#define AUDIO_AC3D_CONTROL_MODE       0x01
#define AUDIO_AC3D_CONTROL_DYN_RANGE  0x02
#define AUDIO_AC3D_CONTROL_SCALING    0x03
#define AUDIO_AC3D_CONTROL_HILO_SCALE 0x04
#define AUDIO_AC3D_CONTROL_UNDERFLOW  0x05
#define AUDIO_AC3D_CONTROL_OVERFLOW   0x06
#define AUDIO_AC3D_CONTROL_DECODE_ERR 0x07

/* WMA Decoder Control Selectors */

#define AUDIO_WMAD_CONTROL_UNDEF      0x00
#define AUDIO_WMAD_CONTROL_UNDERFLOW  0x01
#define AUDIO_WMAD_CONTROL_OVERFLOW   0x02
#define AUDIO_WMAD_CONTROL_DECODE_ERR 0x03

/* DTS Decoder Control Selectors */

#define AUDIO_DTSD_CONTROL_UNDEF      0x00
#define AUDIO_DTSD_CONTROL_UNDERFLOW  0x01
#define AUDIO_DTSD_CONTROL_OVERFLOW   0x02
#define AUDIO_DTSD_CONTROL_DECODE_ERR 0x03

/* Endpoint Control Selectors */
#define AUDIO_EP_CONTROL_UNDEF        0x00
#define AUDIO_EP_CONTROL_SAMPLING_FEQ 0x01
#define AUDIO_EP_CONTROL_PITCH        0x02

/* Encoder Error Codes */

/* <0: Reserved for vendor extensions */

#define AUDIO_ENCODER_SUCCESS         0  /* No Error */
#define AUDIO_ENCODER_ERROR_NOMEM     1  /* Out of Memory */
#define AUDIO_ENCODER_ERROR_BW        2  /* Out of Bandwidth */
#define AUDIO_ENCODER_ERROR_CYCLE     3  /* Out of Processing Cycles */
#define AUDIO_ENCODER_ERROR_FRAME     4  /* General Format Frame Error */
#define AUDIO_ENCODER_ERROR_TOOSMALL  5  /* Format Frame Too Small */
#define AUDIO_ENCODER_ERROR_TOOBIG    6  /* Format Frame Too Large */
#define AUDIO_ENCODER_ERROR_BADFORMAT 7  /* Bad Data Format */
#define AUDIO_ENCODER_ERROR_NCHAN     8  /* Incorrect Number of Channels */
#define AUDIO_ENCODER_ERROR_RATE      9  /* Incorrect Sampling Rate */
#define AUDIO_ENCODER_ERROR_BITRATE   10 /* Unable to Meet Target Bitrate */
#define AUDIO_ENCODER_ERROR_PARMS     11 /* Inconsistent Set of Parameters */
#define AUDIO_ENCODER_ERROR_NOTREADY  12 /* Not Ready */
#define AUDIO_ENCODER_ERROR_BUSY      13 /* Busy */
                                         /* >13: Reserved */

/* Format Type Codes */

#define AUDIO_FORMAT_TYPE_UNDEF  0x00
#define AUDIO_FORMAT_TYPEI       0x01
#define AUDIO_FORMAT_TYPEII      0x02
#define AUDIO_FORMAT_TYPEIII     0x03
#define AUDIO_FORMAT_TYPEIV      0x04
#define AUDIO_FORMAT_EXT_TYPEI   0x81
#define AUDIO_FORMAT_EXT_TYPEII  0x82
#define AUDIO_FORMAT_EXT_TYPEIII 0x83

/* Audio Data Format Type I Bit Allocations */

#define AUDIO_FORMAT_TYPEI_PCM       (1 << 0)
#define AUDIO_FORMAT_TYPEI_PCM8      (1 << 1)
#define AUDIO_FORMAT_TYPEI_IEEEFLOAT (1 << 2)
#define AUDIO_FORMAT_TYPEI_ALAW      (1 << 3)
#define AUDIO_FORMAT_TYPEI_MULAW     (1 << 4)
#define AUDIO_FORMAT_TYPEI_RAWDATA   (1 << 31)

/* Audio Data Format Type II Bit Allocations */

#define AUDIO_FORMAT_TYPEII_MPEG    (1 << 0)
#define AUDIO_FORMAT_TYPEII_AC3     (1 << 1)
#define AUDIO_FORMAT_TYPEII_WMA     (1 << 2)
#define AUDIO_FORMAT_TYPEII_DTS     (1 << 3)
#define AUDIO_FORMAT_TYPEII_RAWDATA (1 << 31)

/* Audio Data Format Type III Bit Allocations */

#define AUDIO_FORMAT_TYPEIII_IEC61937_AC3            (1 << 0)
#define AUDIO_FORMAT_TYPEIII_IEC61937_MPEG1_L1       (1 << 1)
#define AUDIO_FORMAT_TYPEIII_IEC61937_MPEG1_L2_3     (1 << 1)
#define AUDIO_FORMAT_TYPEIII_IEC61937_MPEG2_NOEXT    (1 << 2)
#define AUDIO_FORMAT_TYPEIII_IEC61937_MPEG2_EXT      (1 << 3)
#define AUDIO_FORMAT_TYPEIII_IEC61937_MPEG2_AAC_ADTS (1 << 4)
#define AUDIO_FORMAT_TYPEIII_IEC61937_MPEG2_L1_LS    (1 << 5)
#define AUDIO_FORMAT_TYPEIII_IEC61937_MPEG2_L2_3_LS  (1 << 6)
#define AUDIO_FORMAT_TYPEIII_IEC61937_DTS_I          (1 << 7)
#define AUDIO_FORMAT_TYPEIII_IEC61937_DTS_II         (1 << 8)
#define AUDIO_FORMAT_TYPEIII_IEC61937_DTS_III        (1 << 9)
#define AUDIO_FORMAT_TYPEIII_IEC61937_ATRAC          (1 << 10)
#define AUDIO_FORMAT_TYPEIII_IEC61937_ATRAC2_3       (1 << 11)
#define AUDIO_FORMAT_TYPEIII_WMA                     (1 << 12)

/* Audio Data Format Type IV Bit Allocations */

#define AUDIO_FORMAT_TYPEIV_PCM                     (1 << 0)
#define AUDIO_FORMAT_TYPEIV_PCM8                    (1 << 1)
#define AUDIO_FORMAT_TYPEIV_IEEE_FLOAT              (1 << 2)
#define AUDIO_FORMAT_TYPEIV_ALAW                    (1 << 3)
#define AUDIO_FORMAT_TYPEIV_MULAW                   (1 << 4)
#define AUDIO_FORMAT_TYPEIV_MPEG                    (1 << 5)
#define AUDIO_FORMAT_TYPEIV_AC3                     (1 << 6)
#define AUDIO_FORMAT_TYPEIV_WMA                     (1 << 7)
#define AUDIO_FORMAT_TYPEIV_IEC61937_AC3            (1 << 8)
#define AUDIO_FORMAT_TYPEIV_IEC61937_MPEG1_L1       (1 << 9)
#define AUDIO_FORMAT_TYPEIV_IEC61937_MPEG1_L2_3     (1 << 10)
#define AUDIO_FORMAT_TYPEIV_IEC61937_MPEG2_NOEXT    (1 << 10)
#define AUDIO_FORMAT_TYPEIV_IEC61937_MPEG2_EXT      (1 << 11)
#define AUDIO_FORMAT_TYPEIV_IEC61937_MPEG2_AAC_ADTS (1 << 12)
#define AUDIO_FORMAT_TYPEIV_IEC61937_MPEG2_L1_LS    (1 << 13)
#define AUDIO_FORMAT_TYPEIV_IEC61937_MPEG2_L2_3_LS  (1 << 14)
#define AUDIO_FORMAT_TYPEIV_IEC61937_DTS_I          (1 << 15)
#define AUDIO_FORMAT_TYPEIV_IEC61937_DTS_II         (1 << 16)
#define AUDIO_FORMAT_TYPEIV_IEC61937_DTS_III        (1 << 17)
#define AUDIO_FORMAT_TYPEIV_IEC61937_ATRAC          (1 << 18)
#define AUDIO_FORMAT_TYPEIV_IEC61937_ATRAC2_3       (1 << 19)
#define AUDIO_FORMAT_TYPEIV_TYPE_III_WMA            (1 << 20)
#define AUDIO_FORMAT_TYPEIV_IEC60958_PCM            (1 << 21)

/* Side Band Protocol Codes */
#define AUDIO_SIDEBAND_PROTOCOL_UNDEF 0x00
#define AUDIO_PRES_TIMESTAMP_PROTOCOL 0x01

/** USB Terminal Types
 * Refer to Table 2-1 - Table 2-4 from termt10.pdf
 */

/* USB Terminal Types */
#define AUDIO_TERMINAL_UNDEF     0x0100
#define AUDIO_TERMINAL_STREAMING 0x0101
#define AUDIO_TERMINAL_VENDOR    0x01ff

/* Input Terminal Types */
#define AUDIO_INTERM_UNDEF          0x0200 /* Undefined Type */
#define AUDIO_INTERM_MIC            0x0201 /* A generic microhpone */
#define AUDIO_INTERM_DESKTOP_MIC    0x0202 /* A desktop microphone */
#define AUDIO_INTERM_PERSONAL_MIC   0x0203 /* Head-mounted or clip-on microphone */
#define AUDIO_INTERM_OMNI_MIC       0x0204 /* Omni-directional microphone */
#define AUDIO_INTERM_MIC_ARRAY      0x0205 /* Microphone array */
#define AUDIO_INTERM_PROC_MIC_ARRAY 0x0206 /* Microphone array with signal processor */

/* Output Terminal Types */
#define AUDIO_OUTTERM_UNDEF       0x0300 /* Undefined Type */
#define AUDIO_OUTTERM_SPEAKER     0x0301 /* Generic speakers */
#define AUDIO_OUTTERM_HEADPHONES  0x0302 /* A head-mounted audio output device */
#define AUDIO_OUTTERM_HEADDISPLAY 0x0303 /* Head Mounted Display Audio */
#define AUDIO_OUTTERM_DESKTOP     0x0304 /* Desktop speaker */
#define AUDIO_OUTTERM_ROOM        0x0305 /* Room speaker */
#define AUDIO_OUTTERM_COMMS       0x0306 /* Communication speaker */
#define AUDIO_OUTTERM_LOFREQ      0x0307 /* Low frequency effects speaker */

/* Bi-directional Terminal Types */
#define AUDIO_BIDITERM_UNDEF        0x0400 /* Undefined Type */
#define AUDIO_BIDITERM_HANDSET      0x0401 /* Hand-held bi-directional audio device */
#define AUDIO_BIDITERM_HEADSET      0x0402 /* Head-mounted bi-directional audio device */
#define AUDIO_BIDITERM_SPEAKERPHONE 0x0403 /* Speakerphone, no echo reduction */
#define AUDIO_BIDITERM_ECHOSUPPRESS 0x0404 /* Echo-suppressing speakerphone */
#define AUDIO_BIDITERM_ECHOCANCEL   0x0405 /* Echo-canceling speakerphone */

/* Telephony Terminal Types */
#define AUDIO_TELETERM_UNDEF     0x0500 /* Undefined Type */
#define AUDIO_TELETERM_PHONELINE 0x0501 /* Analog telephone line jack, an ISDN line,
                                                * a proprietary PBX interface, or a wireless link */
#define AUDIO_TELETERM_TELEPHONE 0x0502 /* Device can be used as a telephone */
#define AUDIO_TELETERM_DOWNLINE  0x0503 /* Down Line Phone */

/* External Terminal Types */
#define AUDIO_EXTTERM_UNDEF   0x0600 /* Undefined Type */
#define AUDIO_EXTTERM_ANALOG  0x0601 /* Generic analog connector */
#define AUDIO_EXTTERM_DIGITAL 0x0602 /* Generic digital audio interface */
#define AUDIO_EXTTERM_LINE    0x0603 /* Analog connector at standard line levels */
#define AUDIO_EXTTERM_LEGACY  0x0604 /* Legacy audio line out connector */
#define AUDIO_EXTTERM_SPDIF   0x0605 /* SPDIF interface */
#define AUDIO_EXTTERM_1394DA  0x0606 /* 1394 DA stream */
#define AUDIO_EXTTERM_1394DV  0x0607 /* 1394 DV stream soundtrack */
#define AUDIO_EXTTERM_ADAT    0x0608 /* ADAT Lightpipe */
#define AUDIO_EXTTERM_TDIF    0x0609 /* TDIF  - Tascam Digital Interface */
#define AUDIO_EXTTERM_MADI    0x060a /* MADI - Multi-channel Audio Digital Interface (AES) */

/* Embedded Function Terminal Types */
#define AUDIO_EMBEDTERM_UNDEF        0x0700 /* Undefined Type */
#define AUDIO_EMBEDTERM_CALIBRATION  0x0701 /* Level Calibration Noise Source */
#define AUDIO_EMBEDTERM_EQUALIZATION 0x0702 /* Equalization Noise */
#define AUDIO_EMBEDTERM_CD           0x0703 /* CD player */
#define AUDIO_EMBEDTERM_DAT          0x0704 /* Digital Audio Tape */
#define AUDIO_EMBEDTERM_DCC          0x0705 /* Digital Compact Cassette */
#define AUDIO_EMBEDTERM_COMPRESSED   0x0706 /* Compressed Audio Player */
#define AUDIO_EMBEDTERM_TAPE         0x0707 /* Analog Audio Tape */
#define AUDIO_EMBEDTERM_PHONOGRAPH   0x0708 /* Analog vinyl record player */
#define AUDIO_EMBEDTERM_VCR          0x0709 /* Audio track of VCR */
#define AUDIO_EMBEDTERM_VIDDISC      0x070a /* Audio track of VideoDisc player */
#define AUDIO_EMBEDTERM_DVD          0x070b /* Audio track of DVD player */
#define AUDIO_EMBEDTERM_TVTUNER      0x070c /* Audio track of TV tuner */
#define AUDIO_EMBEDTERM_SATELLITE    0x070d /* Audio track of satellite receiver */
#define AUDIO_EMBEDTERM_CABLETUNER   0x070e /* Audio track of cable tuner */
#define AUDIO_EMBEDTERM_DSS          0x070f /* Audio track of DSS receiver */
#define AUDIO_EMBEDTERM_RADIO        0x0710 /* AM/FM radio receiver */
#define AUDIO_EMBEDTERM_TRANSMITTER  0x0711 /* AM/FM radio transmitter */
#define AUDIO_EMBEDTERM_MULTITRACK   0x0712 /* A multi-track recording system */
#define AUDIO_EMBEDTERM_SYNTHESIZER  0x0713 /* Synthesizer */
#define AUDIO_EMBEDTERM_PIANO        0x0714 /* Piano */
#define AUDIO_EMBEDTERM_GUITAR       0x0715 /* Guitar */
#define AUDIO_EMBEDTERM_PERCUSSON    0x0716 /* Percussion Instrument */
#define AUDIO_EMBEDTERM_INSTRUMENT   0x0717 /* Other Musical Instrument */

#define AUDIO_FORMAT_TYPE_I   0x01
#define AUDIO_FORMAT_TYPE_II  0x02
#define AUDIO_FORMAT_TYPE_III 0x03

struct audio_cs_if_ac_header_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint16_t bcdADC;
    uint16_t wTotalLength;
    uint8_t bInCollection;
    uint8_t baInterfaceNr[];
} __PACKED;

#define AUDIO_SIZEOF_AC_HEADER_DESC(n) (8 + n)

struct audio_cs_if_ac_input_terminal_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bTerminalID;
    uint16_t wTerminalType;
    uint8_t bAssocTerminal;
    uint8_t bNrChannels;
    uint16_t wChannelConfig;
    uint8_t iChannelNames;
    uint8_t iTerminal;
} __PACKED;

#define AUDIO_SIZEOF_AC_INPUT_TERMINAL_DESC (12)

struct audio_cs_if_ac_output_terminal_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bTerminalID;
    uint16_t wTerminalType;
    uint8_t bAssocTerminal;
    uint8_t bSourceID;
    uint8_t iTerminal;
} __PACKED;

#define AUDIO_SIZEOF_AC_OUTPUT_TERMINAL_DESC (9)

struct audio_cs_if_ac_feature_unit_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bUnitID;
    uint8_t bSourceID;
    uint8_t bControlSize;
    uint8_t bmaControls[1];
    uint8_t iFeature;
} __PACKED;

#define AUDIO_SIZEOF_AC_FEATURE_UNIT_DESC(ch, n) (7 + (ch + 1) * n)

struct audio_cs_if_as_general_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bTerminalLink;
    uint8_t bDelay;
    uint16_t wFormatTag;
} __PACKED;

#define AUDIO_SIZEOF_AS_GENERAL_DESC (7)

struct audio_cs_if_as_format_type_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bFormatType;
    uint8_t bNrChannels;
    uint8_t bSubframeSize;
    uint8_t bBitResolution;
    uint8_t bSamFreqType;
    uint8_t tSamFreq[3];
} __PACKED;

#define AUDIO_SIZEOF_FORMAT_TYPE_DESC(n) (8 + 3 * n)

struct audio_ep_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bEndpointAddress;
    uint8_t bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t bInterval;
    uint8_t bRefresh;
    uint8_t bSynchAddress;
} __PACKED;

#define AUDIO_SIZEOF_EP_DESC (9)

struct audio_cs_ep_ep_general_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bmAttributes;
    uint8_t bLockDelayUnits;
    uint16_t wLockDelay;
} __PACKED;

#define AUDIO_SIZEOF_CS_EP_GENERAL_DESC (7)

// clang-format off
#define AUDIO_AC_DESCRIPTOR_INIT(bFirstInterface, bInterfaceCount, wTotalLength, stridx, ...) \
    /* Interface Association Descriptor */                                                                                       \
    0x08,                                                                                                                        \
    USB_DESCRIPTOR_TYPE_INTERFACE_ASSOCIATION,                                                                                   \
    bFirstInterface,                                                                                                             \
    bInterfaceCount,                                                                                                             \
    USB_DEVICE_CLASS_AUDIO,                                                                                                      \
    AUDIO_SUBCLASS_AUDIOCONTROL,                                                                                                 \
    AUDIO_PROTOCOL_UNDEFINED,                                                                                                    \
    0x00,                                                                                                                        \
    /* ------------------ AudioControl Interface ------------------ */\
    0x09,                            /* bLength */                                                                               \
    USB_DESCRIPTOR_TYPE_INTERFACE,   /* bDescriptorType */                                                                       \
    bFirstInterface,                 /* bInterfaceNumber */                                                                      \
    0x00,                            /* bAlternateSetting */                                                                     \
    0x00,                            /* bNumEndpoints */                                                                         \
    USB_DEVICE_CLASS_AUDIO,          /* bInterfaceClass */                                                                       \
    AUDIO_SUBCLASS_AUDIOCONTROL,     /* bInterfaceSubClass */                                                                    \
    AUDIO_PROTOCOL_UNDEFINED,        /* bInterfaceProtocol */                                                                    \
    stridx,                          /* iInterface */                                                                            \
    0x08 + PP_NARG(__VA_ARGS__),     /* bLength */                                                                               \
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType */                                                                       \
    AUDIO_CONTROL_HEADER,            /* bDescriptorSubtype */                                                                    \
    WBVAL(0x0100),                   /* bcdADC */                                                                                \
    WBVAL(wTotalLength),             /* wTotalLength */                                                                          \
    PP_NARG(__VA_ARGS__),            /* bInCollection */                                                                         \
    __VA_ARGS__                      /* baInterfaceNr */

#define AUDIO_AC_DESCRIPTOR_INIT_LEN(n) (0x08 + 0x09 + 0x08 + n)

#define AUDIO_AC_INPUT_TERMINAL_DESCRIPTOR_INIT(bTerminalID, wTerminalType, bNrChannels, wChannelConfig) \
    0x0C,                            /* bLength */                                                   \
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType */                                           \
    AUDIO_CONTROL_INPUT_TERMINAL,    /* bDescriptorSubtype */                                        \
    bTerminalID,                     /* bTerminalID */                                               \
    WBVAL(wTerminalType),            /* wTerminalType : Microphone 0x0201 */                         \
    0x00,                            /* bAssocTerminal */                                            \
    bNrChannels,                     /* bNrChannels */                                               \
    WBVAL(wChannelConfig),           /* wChannelConfig : Mono sets no position bits */               \
    0x00,                            /* iChannelNames */                                             \
    0x00                             /* iTerminal */

#define AUDIO_AC_OUTPUT_TERMINAL_DESCRIPTOR_INIT(bTerminalID, wTerminalType, bSourceID) \
    0x09,                            /* bLength */                                  \
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType */                          \
    AUDIO_CONTROL_OUTPUT_TERMINAL,   /* bDescriptorSubtype */                       \
    bTerminalID,                     /* bTerminalID */                              \
    WBVAL(wTerminalType),            /* wTerminalType : USB Streaming */            \
    0x00,                            /* bAssocTerminal */                           \
    bSourceID,                       /* bSourceID */                                \
    0x00                             /* iTerminal */

#define AUDIO_AC_FEATURE_UNIT_DESCRIPTOR_INIT(bUnitID, bSourceID, bControlSize, ...) \
    0x07 + PP_NARG(__VA_ARGS__),     /* bLength */                               \
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType */                       \
    AUDIO_CONTROL_FEATURE_UNIT,      /* bDescriptorSubtype */                    \
    bUnitID,                         /* bUnitID */                               \
    bSourceID,                       /* bSourceID */                             \
    bControlSize,                    /* bControlSize */                          \
    __VA_ARGS__,                     /* bmaControls(0) Mute */                   \
    0x00                             /* iTerminal */

#define AUDIO_AS_DESCRIPTOR_INIT(bInterfaceNumber, bTerminalLink, bNrChannels, bSubFrameSize, bBitResolution, bEndpointAddress, bmAttributes, wMaxPacketSize, bInterval, ...) \
    0x09,                            /* bLength */                                                                       \
    USB_DESCRIPTOR_TYPE_INTERFACE,   /* bDescriptorType */                                                               \
    bInterfaceNumber,                /* bInterfaceNumber */                                                              \
    0x00,                            /* bAlternateSetting */                                                             \
    0x00,                            /* bNumEndpoints */                                                                 \
    USB_DEVICE_CLASS_AUDIO,          /* bInterfaceClass */                                                               \
    AUDIO_SUBCLASS_AUDIOSTREAMING,   /* bInterfaceSubClass */                                                            \
    AUDIO_PROTOCOL_UNDEFINED,        /* bInterfaceProtocol */                                                            \
    0x00,                            /* iInterface */                                                                    \
    0x09,                            /* bLength */                                                                       \
    USB_DESCRIPTOR_TYPE_INTERFACE,   /* bDescriptorType */                                                               \
    bInterfaceNumber,                /* bInterfaceNumber */                                                              \
    0x01,                            /* bAlternateSetting */                                                             \
    0x01,                            /* bNumEndpoints */                                                                 \
    USB_DEVICE_CLASS_AUDIO,          /* bInterfaceClass */                                                               \
    AUDIO_SUBCLASS_AUDIOSTREAMING,   /* bInterfaceSubClass */                                                            \
    AUDIO_PROTOCOL_UNDEFINED,        /* bInterfaceProtocol */                                                            \
    0x00,                            /* iInterface */                                                                    \
    0x07,                            /* bLength */                                                                       \
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType */                                                               \
    AUDIO_STREAMING_GENERAL,         /* bDescriptorSubtype */                                                            \
    bTerminalLink,                   /* bTerminalLink : Unit ID of the Output Terminal*/                                 \
    0x01,                            /* bDelay */                                                                        \
    WBVAL(AUDIO_FORMAT_PCM),         /* wFormatTag : AUDIO_FORMAT_PCM */                                                 \
    0x08 + PP_NARG(__VA_ARGS__),     /* bLength */                                                                       \
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType */                                                               \
    AUDIO_STREAMING_FORMAT_TYPE,     /* bDescriptorSubtype */                                                            \
    AUDIO_FORMAT_TYPE_I,             /* bFormatType */                                                                   \
    bNrChannels,                     /* bNrChannels */                                                                   \
    bSubFrameSize,                   /* bSubFrameSize : Bytes per audio subframe */                                      \
    bBitResolution,                  /* bBitResolution : bits per sample */                                              \
    (PP_NARG(__VA_ARGS__)/3),        /* bSamFreqType : only one frequency supported */                                   \
    __VA_ARGS__,                     /* tSamFreq : Audio sampling frequency coded on 3 bytes */                          \
    0x09,                            /* bLength */                                                                       \
    USB_DESCRIPTOR_TYPE_ENDPOINT,    /* bDescriptorType */                                                               \
    bEndpointAddress,                /* bEndpointAddress : IN endpoint 1 */                                              \
    bmAttributes,                    /* bmAttributes */                                                                  \
    WBVAL(wMaxPacketSize),           /* wMaxPacketSize */                                                                \
    bInterval,                       /* bInterval : one packet per frame */                                              \
    0x00,                            /* bRefresh */                                                                      \
    0x00,                            /* bSynchAddress */                                                                 \
    0x07,                            /* bLength */                                                                       \
    AUDIO_ENDPOINT_DESCRIPTOR_TYPE,  /* bDescriptorType */                                                               \
    AUDIO_ENDPOINT_GENERAL,          /* bDescriptor */                                                                   \
    AUDIO_EP_CONTROL_SAMPLING_FEQ,   /* bmAttributes AUDIO_SAMPLING_FREQ_CONTROL */                                      \
    0x00,                            /* bLockDelayUnits */                                                               \
    0x00,                            /* wLockDelay */                                                                    \
    0x00

#define AUDIO_AS_DESCRIPTOR_INIT_LEN(n) (0x09 + 0x09 + 0x07 + 0x08 + 3 * n + 0x09 + 0x07)

#define AUDIO_MS_STANDARD_DESCRIPTOR_INIT(bInterfaceNumber, bNumEndpoints)                                               \
    0x09,                            /* bLength */                                                                       \
    USB_DESCRIPTOR_TYPE_INTERFACE,   /* bDescriptorType */                                                               \
    bInterfaceNumber,                /* bInterfaceNumber */                                                              \
    0x00,                            /* bAlternateSetting */                                                             \
    bNumEndpoints,                   /* bNumEndpoints */                                                                 \
    USB_DEVICE_CLASS_AUDIO,          /* bInterfaceClass */                                                               \
    AUDIO_SUBCLASS_MIDISTREAMING,    /* bInterfaceSubClass */                                                            \
    AUDIO_PROTOCOL_UNDEFINED,        /* bInterfaceProtocol */                                                            \
    0x00                             /* iInterface */

#define AUDIO_MS_STANDARD_DESCRIPTOR_INIT_LEN 0x09

struct audio_v2_channel_cluster_descriptor {
    uint8_t bNrChannels;
    uint32_t bmChannelConfig;
    uint8_t iChannelNames;
} __PACKED;

#define AUDIO_V2_SIZEOF_CHANNEL_CLUSTER_DESC (6)

struct audio_v2_cs_if_ac_header_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint16_t bcdADC;
    uint8_t bCategory;
    uint16_t wTotalLength;
    uint8_t bmControls;
} __PACKED;

#define AUDIO_V2_SIZEOF_AC_HEADER_DESC (9)

struct audio_v2_cs_if_ac_clock_source_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bClockID;
    uint8_t bmAttributes;
    uint8_t bmControls;
    uint8_t bAssocTerminal;
    uint8_t iClockSource;
} __PACKED;

#define AUDIO_V2_SIZEOF_AC_CLOCK_SOURCE_DESC (8)

struct audio_v2_cs_if_ac_clock_selector_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bClockID;
    uint8_t bNrInPins;
    uint8_t baCSourceID[1];
    uint8_t iClockSelector;
} __PACKED;

#define AUDIO_SIZEOF_AC_CLOCK_SELECTOR_DESC(n) (7 + n)

struct audio_v2_cs_if_ac_clock_multiplier_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bClockID;
    uint8_t bCSourceID;
    uint8_t bmControls;
    uint8_t iClockMultiplier;
} __PACKED;

#define AUDIO_SIZEOF_AC_CLOCK_MULTIPLIER_DESC() (7)

struct audio_v2_cs_if_ac_input_terminal_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bTerminalID;
    uint16_t wTerminalType;
    uint8_t bAssocTerminal;
    uint8_t bCSourceID;
    uint8_t bNrChannels;
    uint32_t wChannelConfig;
    uint8_t iChannelNames;
    uint16_t bmControls;
    uint8_t iTerminal;
} __PACKED;

#define AUDIO_V2_SIZEOF_AC_INPUT_TERMINAL_DESC (17)

struct audio_v2_cs_if_ac_output_terminal_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bTerminalID;
    uint16_t wTerminalType;
    uint8_t bAssocTerminal;
    uint8_t bSourceID;
    uint8_t bCSourceID;
    uint16_t bmControls;
    uint8_t iTerminal;
} __PACKED;

#define AUDIO_V2_SIZEOF_AC_OUTPUT_TERMINAL_DESC (12)

struct audio_v2_cs_if_ac_feature_unit_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bUnitID;
    uint8_t bSourceID;
    uint32_t bmaControls[1];
    uint8_t iFeature;
} __PACKED;

#define AUDIO_V2_SIZEOF_AC_FEATURE_UNIT_DESC(ch) (6 + (ch + 1) * 4)

struct audio_v2_cs_if_as_general_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bTerminalLink;
    uint8_t bmControls;
    uint8_t bFormatType;
    uint32_t bmFormats;
    uint8_t bNrChannels;
    uint32_t bmChannelConfig;
    uint8_t iChannelNames;
} __PACKED;

#define AUDIO_V2_SIZEOF_AS_GENERAL_DESC (16)

struct audio_v2_control_range1_param_block {
    uint16_t wNumSubRanges;
    struct
    {
        uint8_t bMin;
        uint8_t bMax;
        uint8_t bRes;
    }subrange[];
} __PACKED;

struct audio_v2_control_range2_param_block {
    uint16_t wNumSubRanges;
    struct
    {
        uint16_t wMin;
        uint16_t wMax;
        uint16_t wRes;
    }subrange[];
} __PACKED;

struct audio_v2_control_range3_param_block {
    uint16_t wNumSubRanges;
    struct
    {
        uint32_t dMin;
        uint32_t dMax;
        uint32_t dRes;
    }subrange[];
} __PACKED;

#define AUDIO_V2_AC_DESCRIPTOR_INIT(bFirstInterface, bInterfaceCount, wTotalLength, bCategory, bmControls, stridx) \
    /* Interface Association Descriptor */                                                                                       \
    0x08,                                                                                                                        \
    USB_DESCRIPTOR_TYPE_INTERFACE_ASSOCIATION,                                                                                   \
    bFirstInterface,                                                                                                             \
    bInterfaceCount,                                                                                                             \
    USB_DEVICE_CLASS_AUDIO,                                                                                                      \
    AUDIO_SUBCLASS_UNDEFINED,                                                                                                    \
    AUDIO_PROTOCOLv20,                                                                                                           \
    0x00,                                                                                                                        \
    /* ------------------ AudioControl Interface ------------------ */\
    0x09,                            /* bLength */                                                                               \
    USB_DESCRIPTOR_TYPE_INTERFACE,   /* bDescriptorType */                                                                       \
    bFirstInterface,                 /* bInterfaceNumber */                                                                      \
    0x00,                            /* bAlternateSetting */                                                                     \
    0x00,                            /* bNumEndpoints */                                                                         \
    USB_DEVICE_CLASS_AUDIO,          /* bInterfaceClass */                                                                       \
    AUDIO_SUBCLASS_AUDIOCONTROL,     /* bInterfaceSubClass */                                                                    \
    AUDIO_PROTOCOLv20,               /* bInterfaceProtocol */                                                                    \
    stridx,                          /* iInterface */                                                                            \
    0x09,                            /* bLength */                                                                               \
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType */                                                                       \
    AUDIO_CONTROL_HEADER,            /* bDescriptorSubtype */                                                                    \
    WBVAL(0x0200),                   /* bcdADC */                                                                                \
    bCategory,                       /* bCategory */                                                                             \
    WBVAL(wTotalLength),             /* wTotalLength */                                                                          \
    bmControls                       /* bmControls */                                                                            \

#define AUDIO_V2_AC_DESCRIPTOR_INIT_LEN (0x08 + 0x09 + 0x09)

#define AUDIO_V2_AC_CLOCK_SOURCE_DESCRIPTOR_INIT(bClockID, bmAttributes, bmControls) \
    0x08,                            /* bLength */                               \
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType */                       \
    AUDIO_CONTROL_CLOCK_SOURCE,      /* bDescriptorSubtype */                    \
    bClockID,                        /* bClockID */                              \
    bmAttributes,                    /* bmAttributes */                          \
    bmControls,                      /* bmControls */                            \
    0x00,                            /* bAssocTerminal */                        \
    0x00                             /* iClockSource */

#define AUDIO_V2_AC_INPUT_TERMINAL_DESCRIPTOR_INIT(bTerminalID, wTerminalType, bCSourceID, bNrChannels, wChannelConfig, bmControls) \
    0x11,                            /* bLength */                                                                              \
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType */                                                                      \
    AUDIO_CONTROL_INPUT_TERMINAL,    /* bDescriptorSubtype */                                                                   \
    bTerminalID,                     /* bTerminalID */                                                                          \
    WBVAL(wTerminalType),            /* wTerminalType : Microphone 0x0201 */                                                    \
    0x00,                            /* bAssocTerminal */                                                                       \
    bCSourceID,                      /* bCSourceID */                                                                           \
    bNrChannels,                     /* bNrChannels */                                                                          \
    DBVAL(wChannelConfig),           /* wChannelConfig : Mono sets no position bits */                                          \
    0x00,                            /* iChannelNames */                                                                        \
    WBVAL(bmControls),               /* bmControls */                                                                           \
    0x00                             /* iTerminal */

#define AUDIO_V2_AC_OUTPUT_TERMINAL_DESCRIPTOR_INIT(bTerminalID, wTerminalType, bSourceID, bCSourceID, bmControls) \
    0x0c,                            /* bLength */                                                 \
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType */                                         \
    AUDIO_CONTROL_OUTPUT_TERMINAL,   /* bDescriptorSubtype */                                      \
    bTerminalID,                     /* bTerminalID */                                             \
    WBVAL(wTerminalType),            /* wTerminalType : USB Streaming */                           \
    0x00,                            /* bAssocTerminal */                                          \
    bSourceID,                       /* bSourceID */                                               \
    bCSourceID,                      /* bCSourceID */                                              \
    WBVAL(bmControls),               /* bmControls */                                              \
    0x00                             /* iTerminal */

#define AUDIO_V2_AC_FEATURE_UNIT_DESCRIPTOR_INIT(bUnitID, bSourceID, ...) \
    0x06 + (PP_NARG(__VA_ARGS__)),   /* bLength */                    \
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType */            \
    AUDIO_CONTROL_FEATURE_UNIT,      /* bDescriptorSubtype */         \
    bUnitID,                         /* bUnitID */                    \
    bSourceID,                       /* bSourceID */                  \
    __VA_ARGS__,                     /* bmaControls(0) Mute */        \
    0x00                             /* iTerminal */

#define AUDIO_V2_AS_DESCRIPTOR_INIT(bInterfaceNumber, bTerminalLink, bNrChannels, bmChannelConfig, bSubslotSize, bBitResolution, bEndpointAddress, bmAttributes, wMaxPacketSize, bInterval) \
    0x09,                            /* bLength */                                                                                                                        \
    USB_DESCRIPTOR_TYPE_INTERFACE,   /* bDescriptorType */                                                                                                                \
    bInterfaceNumber,                /* bInterfaceNumber */                                                                                                               \
    0x00,                            /* bAlternateSetting */                                                                                                              \
    0x00,                            /* bNumEndpoints */                                                                                                                  \
    USB_DEVICE_CLASS_AUDIO,          /* bInterfaceClass */                                                                                                                \
    AUDIO_SUBCLASS_AUDIOSTREAMING,   /* bInterfaceSubClass */                                                                                                             \
    AUDIO_PROTOCOLv20,               /* bInterfaceProtocol */                                                                                                             \
    0x00,                            /* iInterface */                                                                                                                     \
    0x09,                            /* bLength */                                                                                                                        \
    USB_DESCRIPTOR_TYPE_INTERFACE,   /* bDescriptorType */                                                                                                                \
    bInterfaceNumber,                /* bInterfaceNumber */                                                                                                               \
    0x01,                            /* bAlternateSetting */                                                                                                              \
    0x01,                            /* bNumEndpoints */                                                                                                                  \
    USB_DEVICE_CLASS_AUDIO,          /* bInterfaceClass */                                                                                                                \
    AUDIO_SUBCLASS_AUDIOSTREAMING,   /* bInterfaceSubClass */                                                                                                             \
    AUDIO_PROTOCOLv20,               /* bInterfaceProtocol */                                                                                                             \
    0x00,                            /* iInterface */                                                                                                                     \
    0x10,                            /* bLength */                                                                                                                        \
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType */                                                                                                                \
    AUDIO_STREAMING_GENERAL,         /* bDescriptorSubtype */                                                                                                             \
    bTerminalLink,                   /* bTerminalLink : Unit ID of the Output or Input Terminal*/                                                                         \
    0x00,                            /* bmControls */                                                                                                                     \
    AUDIO_FORMAT_TYPE_I,             /* bFormatType : AUDIO_FORMAT_TYPE_I */                                                                                              \
    DBVAL(AUDIO_V2_FORMAT_PCM),      /* bmFormats PCM */                                                                                                                  \
    bNrChannels,                     /* bNrChannels */                                                                                                                    \
    DBVAL(bmChannelConfig),          /* bmChannelConfig */                                                                                                                \
    0x00,                            /* iChannelNames */                                                                                                                  \
    0x06,                            /* bLength */                                                                                                                        \
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType */                                                                                                                \
    AUDIO_STREAMING_FORMAT_TYPE,     /* bDescriptorSubtype */                                                                                                             \
    AUDIO_FORMAT_TYPE_I,             /* bFormatType */                                                                                                                    \
    bSubslotSize,                    /* bSubslotSize */                                                                                                                   \
    bBitResolution,                  /* bBitResolution */                                                                                                                 \
    0x07,                            /* bLength */                                                                                                                        \
    USB_DESCRIPTOR_TYPE_ENDPOINT,    /* bDescriptorType */                                                                                                                \
    bEndpointAddress,                /* bEndpointAddress 3 out endpoint for Audio */                                                                                      \
    bmAttributes,                    /* bmAttributes */                                                                                                                   \
    WBVAL(wMaxPacketSize),           /* XXXX wMaxPacketSize in Bytes (SampleRate * SlotByteSize * NumChannels) */                                                         \
    bInterval,                       /* bInterval */                                                                                                                      \
    0x08,                            /* bLength */                                                                                                                        \
    AUDIO_ENDPOINT_DESCRIPTOR_TYPE,  /* bDescriptorType */                                                                                                                \
    AUDIO_ENDPOINT_GENERAL,          /* bDescriptor */                                                                                                                    \
    0x00,                            /* bmAttributes */                                                                                                                   \
    0x00,                            /* bmControls */                                                                                                                     \
    0x00,                            /* bLockDelayUnits */                                                                                                                \
    0x00,                            /* wLockDelay */                                                                                                                     \
    0x00

#define AUDIO_V2_AS_FEEDBACK_DESCRIPTOR_INIT(bInterfaceNumber, bTerminalLink, bNrChannels, bmChannelConfig, bSubslotSize, bBitResolution, bEndpointAddress, wMaxPacketSize, bInterval, bFeedbackEndpointAddress) \
    0x09,                            /* bLength */                                                                                                                        \
    USB_DESCRIPTOR_TYPE_INTERFACE,   /* bDescriptorType */                                                                                                                \
    bInterfaceNumber,                /* bInterfaceNumber */                                                                                                               \
    0x00,                            /* bAlternateSetting */                                                                                                              \
    0x00,                            /* bNumEndpoints */                                                                                                                  \
    USB_DEVICE_CLASS_AUDIO,          /* bInterfaceClass */                                                                                                                \
    AUDIO_SUBCLASS_AUDIOSTREAMING,   /* bInterfaceSubClass */                                                                                                             \
    AUDIO_PROTOCOLv20,               /* bInterfaceProtocol */                                                                                                             \
    0x00,                            /* iInterface */                                                                                                                     \
    0x09,                            /* bLength */                                                                                                                        \
    USB_DESCRIPTOR_TYPE_INTERFACE,   /* bDescriptorType */                                                                                                                \
    bInterfaceNumber,                /* bInterfaceNumber */                                                                                                               \
    0x01,                            /* bAlternateSetting */                                                                                                              \
    0x02,                            /* bNumEndpoints */                                                                                                                  \
    USB_DEVICE_CLASS_AUDIO,          /* bInterfaceClass */                                                                                                                \
    AUDIO_SUBCLASS_AUDIOSTREAMING,   /* bInterfaceSubClass */                                                                                                             \
    AUDIO_PROTOCOLv20,               /* bInterfaceProtocol */                                                                                                             \
    0x00,                            /* iInterface */                                                                                                                     \
    0x10,                            /* bLength */                                                                                                                        \
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType */                                                                                                                \
    AUDIO_STREAMING_GENERAL,         /* bDescriptorSubtype */                                                                                                             \
    bTerminalLink,                   /* bTerminalLink : Unit ID of the Output or Input Terminal*/                                                                         \
    0x00,                            /* bmControls */                                                                                                                     \
    AUDIO_FORMAT_TYPE_I,             /* bFormatType : AUDIO_FORMAT_TYPE_I */                                                                                              \
    DBVAL(AUDIO_V2_FORMAT_PCM),      /* bmFormats PCM */                                                                                                                  \
    bNrChannels,                     /* bNrChannels */                                                                                                                    \
    DBVAL(bmChannelConfig),          /* bmChannelConfig */                                                                                                                \
    0x00,                            /* iChannelNames */                                                                                                                  \
    0x06,                            /* bLength */                                                                                                                        \
    AUDIO_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType */                                                                                                                \
    AUDIO_STREAMING_FORMAT_TYPE,     /* bDescriptorSubtype */                                                                                                             \
    AUDIO_FORMAT_TYPE_I,             /* bFormatType */                                                                                                                    \
    bSubslotSize,                    /* bSubslotSize */                                                                                                                   \
    bBitResolution,                  /* bBitResolution */                                                                                                                 \
    0x07,                            /* bLength */                                                                                                                        \
    USB_DESCRIPTOR_TYPE_ENDPOINT,    /* bDescriptorType */                                                                                                                \
    bEndpointAddress,                /* bEndpointAddress 3 out endpoint for Audio */                                                                                      \
    0x05,                            /* bmAttributes: TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data*/                                                \
    WBVAL(wMaxPacketSize),           /* XXXX wMaxPacketSize in Bytes (SampleRate * SlotByteSize * NumChannels) */                                                         \
    bInterval,                       /* bInterval */                                                                                                                      \
    0x08,                            /* bLength */                                                                                                                        \
    AUDIO_ENDPOINT_DESCRIPTOR_TYPE,  /* bDescriptorType */                                                                                                                \
    AUDIO_ENDPOINT_GENERAL,          /* bDescriptor */                                                                                                                    \
    0x00,                            /* bmAttributes */                                                                                                                   \
    0x00,                            /* bmControls */                                                                                                                     \
    0x00,                            /* bLockDelayUnits */                                                                                                                \
    0x00,                            /* wLockDelay */                                                                                                                     \
    0x00,                                                                                                                                                                 \
    0x07,                            /* bLength */                                                                                                                        \
    USB_DESCRIPTOR_TYPE_ENDPOINT,    /* bDescriptorType */                                                                                                                \
    bFeedbackEndpointAddress,        /* bFeedbackEndpointAddress Revise Dir to bEndpointAddress */                                                                        \
    0x11,                            /* bmAttributes: TransferType=Isochronous  SyncType=None  EndpointType=Feedback */                                                   \
    WBVAL(4),                        /* XXXX wMaxPacketSize in Bytes */                                                                                                   \
    bInterval                        /* bInterval */                                                                                                                      \

// clang-format on

#define AUDIO_V2_AS_DESCRIPTOR_INIT_LEN (0x09 + 0x09 + 0x10 + 0x06 + 0x07 + 0x08)
#define AUDIO_V2_AS_FEEDBACK_DESCRIPTOR_INIT_LEN (0x09 + 0x09 + 0x10 + 0x06 + 0x07 + 0x08 + 0x07)

#define AUDIO_SAMPLE_FREQ_NUM(num) (uint8_t)(num), (uint8_t)((num >> 8))
#define AUDIO_SAMPLE_FREQ_3B(frq)  (uint8_t)(frq), (uint8_t)((frq >> 8)), (uint8_t)((frq >> 16))
#define AUDIO_SAMPLE_FREQ_4B(frq)  (uint8_t)(frq), (uint8_t)((frq >> 8)), \
                                  (uint8_t)((frq >> 16)), (uint8_t)((frq >> 24))

#endif /* USB_AUDIO_H */
