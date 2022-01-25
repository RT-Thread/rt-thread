/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-02     thread-liu   first version
 */

#ifndef __DRV_WM8994_H__
#define __DRV_WM8994_H__

#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

enum{
    GET_ID,
    SET_FREQUENCE,
    SET_VOLUME,
    GET_VOLUME,
    SET_MUTE,
    SET_RESET,
    START_PLAY,
    SET_PLAY_TYPE,
};

/* codec device play type */
#define DEVICE_NONE                           ((uint16_t)0x0000)
#define OUTPUT_DEVICE_SPEAKER                 ((uint16_t)0x0001)
#define OUTPUT_DEVICE_HEADPHONE               ((uint16_t)0x0002)
#define OUTPUT_DEVICE_BOTH                    ((uint16_t)0x0004)
#define OUTPUT_DEVICE_AUTO                    ((uint16_t)0x0008)
#define INPUT_DEVICE_DIGITAL_MICROPHONE_1     ((uint16_t)0x0010)
#define INPUT_DEVICE_DIGITAL_MICROPHONE_2     ((uint16_t)0x0020)
#define INPUT_DEVICE_INPUT_LINE_1             ((uint16_t)0x0040)
#define INPUT_DEVICE_INPUT_LINE_2             ((uint16_t)0x0080)
#define INPUT_DEVICE_DIGITAL_MIC1_MIC2        ((uint16_t)0x0100)

/* volume levels values */
#define DEFAULT_VOLMIN                0x00
#define DEFAULT_VOLMAX                0xFF
#define DEFAULT_VOLSTEP               0x04

#define AUDIO_PAUSE                   0
#define AUDIO_RESUME                  1

/* Codec POWER DOWN modes */
#define CODEC_PDWN_HW                 1
#define CODEC_PDWN_SW                 2

/* MUTE commands */
#define AUDIO_MUTE_ON                 1
#define AUDIO_MUTE_OFF                0

/* AUDIO FREQUENCY */
#define AUDIO_FREQUENCY_192K          ((uint32_t)192000)
#define AUDIO_FREQUENCY_96K           ((uint32_t)96000)
#define AUDIO_FREQUENCY_48K           ((uint32_t)48000)
#define AUDIO_FREQUENCY_44K           ((uint32_t)44100)
#define AUDIO_FREQUENCY_32K           ((uint32_t)32000)
#define AUDIO_FREQUENCY_22K           ((uint32_t)22050)
#define AUDIO_FREQUENCY_16K           ((uint32_t)16000)
#define AUDIO_FREQUENCY_11K           ((uint32_t)11025)
#define AUDIO_FREQUENCY_8K            ((uint32_t)8000)

#define VOLUME_CONVERT(Volume)        (((Volume) > 100)? 100:((uint8_t)(((Volume) * 63) / 100)))
#define VOLUME_IN_CONVERT(Volume)     (((Volume) >= 100)? 239:((uint8_t)(((Volume) * 240) / 100)))

#define WM8994_ID                          0x8994
#define WM8994_CHIPID_ADDR                 0x00

#ifdef __cplusplus
}
#endif

#endif
