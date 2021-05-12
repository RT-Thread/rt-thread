/*  $NetBSD: uaudioreg.h,v 1.15.38.1 2012/06/02 11:09:29 mrg Exp $  */

/*
 * Copyright (c) 1999 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Lennart Augustsson (lennart@augustsson.net) at
 * Carlstedt Research & Technology.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <rtdef.h>

typedef uint8_t  uByte;
typedef uint16_t uWord;

#define UPACKED __attribute__ ((packed))

#define UAUDIO_VERSION      0x100

#define USB_SUBCLASS_AUDIOCONTROL    1
#define USB_SUBCLASS_AUDIOSTREAMING  2
#define USB_SUBCLASS_AUDIOMIDISTREAM 3

#define UDESC_CS_CONFIG     0x22
#define UDESC_CS_STRING     0x23
#define UDESC_CS_INTERFACE  0x24
#define UDESC_CS_ENDPOINT   0x25

#define UDESCSUB_AC_HEADER      1
#define UDESCSUB_AC_INPUT       2
#define UDESCSUB_AC_OUTPUT      3
#define UDESCSUB_AC_MIXER       4
#define UDESCSUB_AC_SELECTOR    5
#define UDESCSUB_AC_FEATURE     6
#define UDESCSUB_AC_PROCESSING  7
#define UDESCSUB_AC_EXTENSION   8

#ifndef AUFMT_MAX_FREQUENCIES
#define AUFMT_MAX_FREQUENCIES   1
#endif

/* The first fields are identical to usb_endpoint_descriptor_t */
typedef struct {
    uByte       bLength;
    uByte       bDescriptorType;
    uByte       bEndpointAddress;
    uByte       bmAttributes;
    uWord       wMaxPacketSize;
    uByte       bInterval;
    /*
     * The following two entries are only used by the Audio Class.
     * And according to the specs the Audio Class is the only one
     * allowed to extend the endpoint descriptor.
     * Who knows what goes on in the minds of the people in the USB
     * standardization?  :-(
     */
    uByte       bRefresh;
    uByte       bSynchAddress;
} UPACKED usb_endpoint_descriptor_audio_t;

/* generic, for iteration */
typedef struct {
    uByte       bLength;
    uByte       bDescriptorType;
    uByte       bDescriptorSubtype;
} UPACKED uaudio_cs_descriptor_t;

struct usb_audio_control_descriptor {
    uByte       bLength;
    uByte       bDescriptorType;
    uByte       bDescriptorSubtype;
    uWord       bcdADC;
    uWord       wTotalLength;
    uByte       bInCollection;
    uByte       baInterfaceNr[1];
} UPACKED;

struct usb_audio_streaming_interface_descriptor {
    uByte       bLength;
    uByte       bDescriptorType;
    uByte       bDescriptorSubtype;
    uByte       bTerminalLink;
    uByte       bDelay;
    uWord       wFormatTag;
} UPACKED;

struct usb_audio_streaming_endpoint_descriptor {
    uByte       bLength;
    uByte       bDescriptorType;
    uByte       bDescriptorSubtype;
    uByte       bmAttributes;
#define UA_SED_FREQ_CONTROL 0x01
#define UA_SED_PITCH_CONTROL    0x02
#define UA_SED_MAXPACKETSONLY   0x80
    uByte       bLockDelayUnits;
    uWord       wLockDelay;
} UPACKED;

struct usb_audio_streaming_type1_descriptor {
    uByte       bLength;
    uByte       bDescriptorType;
    uByte       bDescriptorSubtype;
    uByte       bFormatType;
    uByte       bNrChannels;
    uByte       bSubFrameSize;
    uByte       bBitResolution;
    uByte       bSamFreqType;
#define UA_SAMP_CONTNUOUS 0
    uByte       tSamFreq[3*AUFMT_MAX_FREQUENCIES];
#define UA_GETSAMP(p, n) ((p)->tSamFreq[(n)*3+0] | ((p)->tSamFreq[(n)*3+1] << 8) | ((p)->tSamFreq[(n)*3+2] << 16))
#define UA_SAMP_LO(p) UA_GETSAMP(p, 0)
#define UA_SAMP_HI(p) UA_GETSAMP(p, 1)
} UPACKED;

struct usb_audio_cluster {
    uByte       bNrChannels;
    uWord       wChannelConfig;
#define UA_CHANNEL_LEFT     0x0001
#define UA_CHANNEL_RIGHT    0x0002
#define UA_CHANNEL_CENTER   0x0004
#define UA_CHANNEL_LFE      0x0008
#define UA_CHANNEL_L_SURROUND   0x0010
#define UA_CHANNEL_R_SURROUND   0x0020
#define UA_CHANNEL_L_CENTER 0x0040
#define UA_CHANNEL_R_CENTER 0x0080
#define UA_CHANNEL_SURROUND 0x0100
#define UA_CHANNEL_L_SIDE   0x0200
#define UA_CHANNEL_R_SIDE   0x0400
#define UA_CHANNEL_TOP      0x0800
    uByte       iChannelNames;
} UPACKED;

/* Shared by all units and terminals */
struct usb_audio_unit {
    uByte       bLength;
    uByte       bDescriptorType;
    uByte       bDescriptorSubtype;
    uByte       bUnitId;
};

/* UDESCSUB_AC_INPUT */
struct usb_audio_input_terminal {
    uByte       bLength;
    uByte       bDescriptorType;
    uByte       bDescriptorSubtype;
    uByte       bTerminalId;
    uWord       wTerminalType;
    uByte       bAssocTerminal;
    uByte       bNrChannels;
    uWord       wChannelConfig;
    uByte       iChannelNames;
    uByte       iTerminal;
} UPACKED;

/* UDESCSUB_AC_OUTPUT */
struct usb_audio_output_terminal {
    uByte       bLength;
    uByte       bDescriptorType;
    uByte       bDescriptorSubtype;
    uByte       bTerminalId;
    uWord       wTerminalType;
    uByte       bAssocTerminal;
    uByte       bSourceId;
    uByte       iTerminal;
} UPACKED;

/* UDESCSUB_AC_MIXER */
struct usb_audio_mixer_unit {
    uByte       bLength;
    uByte       bDescriptorType;
    uByte       bDescriptorSubtype;
    uByte       bUnitId;
    uByte       bNrInPins;
    uByte       baSourceId[255]; /* [bNrInPins] */
    /* struct usb_audio_mixer_unit_1 */
} UPACKED;
struct usb_audio_mixer_unit_1 {
    uByte       bNrChannels;
    uWord       wChannelConfig;
    uByte       iChannelNames;
    uByte       bmControls[255]; /* [bNrChannels] */
    /*uByte     iMixer;*/
} UPACKED;

/* UDESCSUB_AC_SELECTOR */
struct usb_audio_selector_unit {
    uByte       bLength;
    uByte       bDescriptorType;
    uByte       bDescriptorSubtype;
    uByte       bUnitId;
    uByte       bNrInPins;
    uByte       baSourceId[255]; /* [bNrInPins] */
    /* uByte    iSelector; */
} UPACKED;

/* UDESCSUB_AC_FEATURE */
struct usb_audio_feature_unit {
    uByte       bLength;
    uByte       bDescriptorType;
    uByte       bDescriptorSubtype;
    uByte       bUnitId;
    uByte       bSourceId;
    uByte       bControlSize;
    uByte       bmaControls[2]; /* size for more than enough */
    /* uByte    iFeature; */
} UPACKED;

/* UDESCSUB_AC_PROCESSING */
struct usb_audio_processing_unit {
    uByte       bLength;
    uByte       bDescriptorType;
    uByte       bDescriptorSubtype;
    uByte       bUnitId;
    uWord       wProcessType;
    uByte       bNrInPins;
    uByte       baSourceId[255]; /* [bNrInPins] */
    /* struct usb_audio_processing_unit_1 */
} UPACKED;
struct usb_audio_processing_unit_1{
    uByte       bNrChannels;
    uWord       wChannelConfig;
    uByte       iChannelNames;
    uByte       bControlSize;
    uByte       bmControls[255]; /* [bControlSize] */
#define UA_PROC_ENABLE_MASK 1
} UPACKED;

struct usb_audio_processing_unit_updown {
    uByte       iProcessing;
    uByte       bNrModes;
    uWord       waModes[255]; /* [bNrModes] */
} UPACKED;

/* UDESCSUB_AC_EXTENSION */
struct usb_audio_extension_unit {
    uByte       bLength;
    uByte       bDescriptorType;
    uByte       bDescriptorSubtype;
    uByte       bUnitId;
    uWord       wExtensionCode;
    uByte       bNrInPins;
    uByte       baSourceId[255]; /* [bNrInPins] */
    /* struct usb_audio_extension_unit_1 */
} UPACKED;
struct usb_audio_extension_unit_1 {
    uByte       bNrChannels;
    uWord       wChannelConfig;
    uByte       iChannelNames;
    uByte       bControlSize;
    uByte       bmControls[255]; /* [bControlSize] */
#define UA_EXT_ENABLE_MASK 1
#define UA_EXT_ENABLE 1
    /*uByte     iExtension;*/
} UPACKED;

/* USB terminal types */
#define UAT_UNDEFINED       0x0100
#define UAT_STREAM      0x0101
#define UAT_VENDOR      0x01ff
/* input terminal types */
#define UATI_UNDEFINED      0x0200
#define UATI_MICROPHONE     0x0201
#define UATI_DESKMICROPHONE 0x0202
#define UATI_PERSONALMICROPHONE 0x0203
#define UATI_OMNIMICROPHONE 0x0204
#define UATI_MICROPHONEARRAY    0x0205
#define UATI_PROCMICROPHONEARR  0x0206
/* output terminal types */
#define UATO_UNDEFINED      0x0300
#define UATO_SPEAKER        0x0301
#define UATO_HEADPHONES     0x0302
#define UATO_DISPLAYAUDIO   0x0303
#define UATO_DESKTOPSPEAKER 0x0304
#define UATO_ROOMSPEAKER    0x0305
#define UATO_COMMSPEAKER    0x0306
#define UATO_SUBWOOFER      0x0307
/* bidir terminal types */
#define UATB_UNDEFINED      0x0400
#define UATB_HANDSET        0x0401
#define UATB_HEADSET        0x0402
#define UATB_SPEAKERPHONE   0x0403
#define UATB_SPEAKERPHONEESUP   0x0404
#define UATB_SPEAKERPHONEECANC  0x0405
/* telephony terminal types */
#define UATT_UNDEFINED      0x0500
#define UATT_PHONELINE      0x0501
#define UATT_TELEPHONE      0x0502
#define UATT_DOWNLINEPHONE  0x0503
/* external terminal types */
#define UATE_UNDEFINED      0x0600
#define UATE_ANALOGCONN     0x0601
#define UATE_DIGITALAUIFC   0x0602
#define UATE_LINECONN       0x0603
#define UATE_LEGACYCONN     0x0604
#define UATE_SPDIF      0x0605
#define UATE_1394DA     0x0606
#define UATE_1394DV     0x0607
/* embedded function terminal types */
#define UATF_UNDEFINED      0x0700
#define UATF_CALIBNOISE     0x0701
#define UATF_EQUNOISE       0x0702
#define UATF_CDPLAYER       0x0703
#define UATF_DAT        0x0704
#define UATF_DCC        0x0705
#define UATF_MINIDISK       0x0706
#define UATF_ANALOGTAPE     0x0707
#define UATF_PHONOGRAPH     0x0708
#define UATF_VCRAUDIO       0x0709
#define UATF_VIDEODISCAUDIO 0x070a
#define UATF_DVDAUDIO       0x070b
#define UATF_TVTUNERAUDIO   0x070c
#define UATF_SATELLITE      0x070d
#define UATF_CABLETUNER     0x070e
#define UATF_DSS        0x070f
#define UATF_RADIORECV      0x0710
#define UATF_RADIOXMIT      0x0711
#define UATF_MULTITRACK     0x0712
#define UATF_SYNTHESIZER    0x0713


#define SET_CUR 0x01
#define GET_CUR 0x81
#define SET_MIN 0x02
#define GET_MIN 0x82
#define SET_MAX 0x03
#define GET_MAX 0x83
#define SET_RES 0x04
#define GET_RES 0x84
#define SET_MEM 0x05
#define GET_MEM 0x85
#define GET_STAT 0xff

#define MUTE_CONTROL    0x01
#define VOLUME_CONTROL  0x02
#define BASS_CONTROL    0x03
#define MID_CONTROL 0x04
#define TREBLE_CONTROL  0x05
#define GRAPHIC_EQUALIZER_CONTROL   0x06
#define AGC_CONTROL 0x07
#define DELAY_CONTROL   0x08
#define BASS_BOOST_CONTROL 0x09
#define LOUDNESS_CONTROL 0x0a

#define FU_MASK(u) (1 << ((u)-1))

#define MASTER_CHAN 0

#define AS_GENERAL  1
#define FORMAT_TYPE 2
#define FORMAT_SPECIFIC 3

#define UA_FMT_PCM  1
#define UA_FMT_PCM8 2
#define UA_FMT_IEEE_FLOAT 3
#define UA_FMT_ALAW 4
#define UA_FMT_MULAW    5
#define UA_FMT_MPEG 0x1001
#define UA_FMT_AC3  0x1002

#define SAMPLING_FREQ_CONTROL   0x01
#define PITCH_CONTROL       0x02

#define FORMAT_TYPE_UNDEFINED 0
#define FORMAT_TYPE_I 1
#define FORMAT_TYPE_II 2
#define FORMAT_TYPE_III 3

#define UA_PROC_MASK(n) (1<< ((n)-1))
#define PROCESS_UNDEFINED       0
#define  XX_ENABLE_CONTROL          1
#define UPDOWNMIX_PROCESS       1
#define  UD_ENABLE_CONTROL          1
#define  UD_MODE_SELECT_CONTROL         2
#define DOLBY_PROLOGIC_PROCESS      2
#define  DP_ENABLE_CONTROL          1
#define  DP_MODE_SELECT_CONTROL         2
#define P3D_STEREO_EXTENDER_PROCESS 3
#define  P3D_ENABLE_CONTROL         1
#define  P3D_SPACIOUSNESS_CONTROL       2
#define REVERBATION_PROCESS     4
#define  RV_ENABLE_CONTROL          1
#define  RV_LEVEL_CONTROL           2
#define  RV_TIME_CONTROL            3
#define  RV_FEEDBACK_CONTROL            4
#define CHORUS_PROCESS          5
#define  CH_ENABLE_CONTROL          1
#define  CH_LEVEL_CONTROL           2
#define  CH_RATE_CONTROL            3
#define  CH_DEPTH_CONTROL           4
#define DYN_RANGE_COMP_PROCESS      6
#define  DR_ENABLE_CONTROL          1
#define  DR_COMPRESSION_RATE_CONTROL        2
#define  DR_MAXAMPL_CONTROL         3
#define  DR_THRESHOLD_CONTROL           4
#define  DR_ATTACK_TIME_CONTROL         5
#define  DR_RELEASE_TIME_CONTROL        6
