/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#ifndef __JPEGD_H__
#define __JPEGD_H__

#include <stdint.h>
#include <sys/ioctl.h>

#define JPEGD_REG_NUM           42
#define JPEGD_NAME              "jpegd"

/*
 * Standalone JPEG decode request.
 *
 * Input:  reg[] must contain a full register set prepared for the hardware.
 *         DMA buffer addresses (register indices 9-13) should use IOVA from
 *         rt_dma_alloc_coherent() on the jpegd device.
 * Output: reg[] is updated with post-decode register values; irq_status
 *         reports the raw interrupt status word.
 */
struct jpegd_req
{
    uint32_t reg[JPEGD_REG_NUM];
    uint32_t irq_status;
};

#define JPEGD_IOC_MAGIC         'J'

#define JPEGD_RUN               _IOWR(JPEGD_IOC_MAGIC, 0, struct jpegd_req)
#define JPEGD_GET_HW_ID         _IOR(JPEGD_IOC_MAGIC, 1, uint32_t)

#endif /* __JPEGD_H__ */
