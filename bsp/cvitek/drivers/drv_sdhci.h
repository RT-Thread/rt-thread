/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/04/05     flyingcys    first version
 */
#ifndef __DRV_SDHCI_H__
#define __DRV_SDHCI_H__

#include "mmio.h"
#include "dw_sdmmc.h"
#include "dw_mmc_reg.h"

#ifndef BIT
#define BIT(nr)      (UINT64_C(1) << (nr))
#endif

typedef enum {
    SDIF_CHAIN_DMA_MODE = 0x01U, ///< one descriptor with one buffer,but one descriptor point to another
    SDIF_DUAL_DMA_MODE  = 0x02U,  ///< dual mode is one descriptor with two buffer
} sdhci_dma_mode_e;

typedef struct {
    bool            enable_fix_burst_len;           ///< fix burst len enable/disable flag,When set, the AHB will
    ///  use only SINGLE, INCR4, INCR8 or INCR16 during start of
    ///  normal burst transfers. When reset, the AHB will use SINGLE
    ///  and INCR burst transfer operations

    sdhci_dma_mode_e mode;                           ///< define the DMA mode */


    rt_ubase_t      dma_des_buffer_start_addr;     ///< internal DMA descriptor start address
    uint32_t        dma_des_buffer_len;             ///  internal DMA buffer descriptor buffer len ,user need to pay attention to the
    ///  dma descriptor buffer length if it is bigger enough for your transfer
    uint8_t         dma_dws_skip_len;               ///< define the descriptor skip length ,the length between two descriptor
    ///  this field is special for dual DMA mode
} sdhci_dma_config_t;

#endif /* __DRV_SDHCI_H__ */
