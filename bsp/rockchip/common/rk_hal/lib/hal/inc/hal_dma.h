/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup DMA
 *  @{
 */

#ifndef _HAL_DMA_H
#define _HAL_DMA_H

#include "hal_def.h"

/***************************** MACRO Definition ******************************/
/** @defgroup DMA_Exported_Definition_Group1 Basic Definition
 *  @{
 */

/***************************** Structure Definition **************************/
/**
 * enum DMA_TRANSFER_DIRECTION - dma transfer mode and direction indicator
 */
typedef enum {
    DMA_MEM_TO_MEM, /**< Async/Memcpy mode */
    DMA_MEM_TO_DEV, /**< Slave mode & From Memory to Device */
    DMA_DEV_TO_MEM, /**< Slave mode & From Device to Memory */
    DMA_DEV_TO_DEV, /**< Slave mode & From Device to Device */
    DMA_TRANS_NONE,
} eDMA_TRANSFER_DIRECTION;

/**
 * enum DMA_SLAVE_BUSWIDTH - defines bus width of the DMA slave
 * device, source or target buses
 */
typedef enum {
    DMA_SLAVE_BUSWIDTH_UNDEFINED = 0,
    DMA_SLAVE_BUSWIDTH_1_BYTE    = 1,
    DMA_SLAVE_BUSWIDTH_2_BYTES   = 2,
    DMA_SLAVE_BUSWIDTH_3_BYTES   = 3,
    DMA_SLAVE_BUSWIDTH_4_BYTES   = 4,
    DMA_SLAVE_BUSWIDTH_8_BYTES   = 8,
    DMA_SLAVE_BUSWIDTH_16_BYTES  = 16,
    DMA_SLAVE_BUSWIDTH_32_BYTES  = 32,
    DMA_SLAVE_BUSWIDTH_64_BYTES  = 64,
} eDMA_SLAVE_BUSWIDTH;

/**
 * struct DMA_SLAVE_CONFIG - dma slave channel runtime config
 */
struct DMA_SLAVE_CONFIG {
    eDMA_TRANSFER_DIRECTION direction; /**< Transfer direction. */
    eDMA_SLAVE_BUSWIDTH srcAddrWidth; /**< The width in bytes of the source,
                                        *  Legal values: 1, 2, 4, 8.
                                        */
    eDMA_SLAVE_BUSWIDTH dstAddrWidth; /**< The same as srcAddrWidth. */
    uint32_t srcAddr; /**< The source physical address. */
    uint32_t dstAddr; /**< The destination physical address. */
    uint16_t srcMaxBurst; /**< The maximum number of words (note: words, as in
                            *  units of the srcAddrWidth member, not bytes) that
                            *  can be sent in one burst to the device, Typically
                            *  something like half the FIFO depth on I/O peri so
                            *  you don't overflow it.
                            */
    uint16_t dstMaxBurst; /**< The same as srcMaxBurst for destination. */
    uint16_t srcInterlaceSize; /**< The interlace size for src mem increase */
    uint16_t dstInterlaceSize; /**< The interlace size for dst mem increase */
};

/**
 * dma complete callback.
 */
typedef void (*DMA_Callback)(void *cparam);

/** @} */

/********************* Public Function Definition ****************************/
/** @defgroup DMA_Exported_Functions_Group5 Other Functions
 *  @{
*/

__STATIC_INLINE bool HAL_DMA_IsSlaveDirection(eDMA_TRANSFER_DIRECTION direction)
{
    return (direction == DMA_MEM_TO_DEV) || (direction == DMA_DEV_TO_MEM);
}

/** @} */

#endif

/** @} */

/** @} */
