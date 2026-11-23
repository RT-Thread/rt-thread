/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __SPACEMIT_SND_I2S_H__
#define __SPACEMIT_SND_I2S_H__

#include <drivers/misc.h>

#define SSPA_TOP_CTRL                  0x00
#define SSPA_FIFO_CTRL                 0x04
#define SSPA_INT_EN                    0x08
#define SSPA_TIMEOUT                   0x0c
#define SSPA_DATA                      0x10
#define SSPA_STATUS                    0x14
#define SSPA_PSP_CTRL                  0x18
#define SSPA_NETWORK_CTRL              0x1c

#define SSPA_TOP_TRAIL_DMA             RT_BIT(13)
#define SSPA_TOP_DATA_WIDTH_MASK       (0x1fU << 5)
#define SSPA_TOP_DATA_WIDTH_32         (0x1fU << 5)
#define SSPA_TOP_FRAME_PSP             (0x3U << 1)
#define SSPA_TOP_ENABLE                RT_BIT(0)

#define SSPA_FIFO_RX_DMA_REQ           RT_BIT(11)
#define SSPA_FIFO_TX_DMA_REQ           RT_BIT(10)
#define SSPA_FIFO_RX_THRESHOLD(v)      ((v) << 5)
#define SSPA_FIFO_TX_THRESHOLD(v)      (v)

#define SSPA_PSP_FRAME_WIDTH(v)        ((v) << 12)
#define SSPA_PSP_FRAME_POLARITY        RT_BIT(4)
#define SSPA_PSP_FRAME_SYNC_RELATIVE   RT_BIT(3)

#endif /* __SPACEMIT_SND_I2S_H__ */
