/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __SPACEMIT_SND_SSPA_H__
#define __SPACEMIT_SND_SSPA_H__

#include <drivers/misc.h>

#define HDMI_SSPA_TX_DATA              0x80

#define HDMI_PHY_BASE                  0xc0400500UL
#define HDMI_PHY_SIZE                  0x200
#define HDMI_PHY_STATUS                0x0c
#define HDMI_PHY_HPD                   RT_BIT(12)
#define HDMI_AUDIO_ENABLE              0x30
#define HDMI_AUDIO_ENABLE_BIT          RT_BIT(0)

#define HDMI_SSPA_CLOCK_CONTROL        0x44
#define HDMI_SSPA_CLOCK_READY          0x7
#define HDMI_SSPA_SAMPLE_RATE          48000

#define K1_ADMA_BYTE_COUNT             0x00
#define K1_ADMA_SOURCE_ADDR            0x10
#define K1_ADMA_DEST_ADDR              0x20
#define K1_ADMA_NEXT_DESC              0x30
#define K1_ADMA_CONTROL                0x40
#define K1_ADMA_CURRENT_DESC           0x70
#define K1_ADMA_INT_ENABLE             0x80
#define K1_ADMA_INT_STATUS             0xa0

#define K1_ADMA_SAMPLE_BITS(v)         (((v) & 0x7U) << 22)
#define K1_ADMA_ABORT                  RT_BIT(20)
#define K1_ADMA_UNPACK                 RT_BIT(16)
#define K1_ADMA_ACTIVE                 RT_BIT(14)
#define K1_ADMA_FETCH_NEXT_DESC        RT_BIT(13)
#define K1_ADMA_ENABLE                 RT_BIT(12)
#define K1_ADMA_DST_HOLD               (0x2U << 4)
#define K1_ADMA_SRC_INCREMENT          (0x0U << 2)

#define K1_ADMA_HDMI_ENABLE            RT_BIT(0)

#define K1_ADMA_DESC_BYTE_COUNT        0x00
#define K1_ADMA_DESC_SOURCE_ADDR       0x04
#define K1_ADMA_DESC_DEST_ADDR         0x08
#define K1_ADMA_DESC_NEXT              0x0c
#define K1_ADMA_DESC_STRIDE            0x100

#endif /* __SPACEMIT_SND_SSPA_H__ */
