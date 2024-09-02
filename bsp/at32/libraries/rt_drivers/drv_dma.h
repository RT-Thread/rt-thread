/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-09     shelton      first version
 * 2023-01-31     shelton      add support f421/f425
 * 2023-04-08     shelton      add support f423
 * 2024-04-12     shelton      add support a403a and a423
 * 2024-08-30     shelton      add support m412 and m416
 */

#ifndef __DRV_DMA_H__
#define __DRV_DMA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rtdevice.h>
#include <rtthread.h>
#include "drv_common.h"

#define DMA_GLO_FLAG                    0x0001U
#define DMA_FDT_FLAG                    0x0002U
#define DMA_HDT_FLAG                    0x0004U
#define DMA_DTE_FLAG                    0x0008U

struct dma_config {
    dma_type *dma_x;
    rt_uint8_t channel_index;
    rt_bool_t dma_done;
    dma_channel_type *dma_channel;
    crm_periph_clock_type dma_clock;
    IRQn_Type dma_irqn;
#if defined (SOC_SERIES_AT32F425)
    rt_uint8_t flex_channel;
    rt_uint32_t request_id;
#endif
#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32F423) || defined (SOC_SERIES_AT32F402) || \
    defined (SOC_SERIES_AT32F405) || defined (SOC_SERIES_AT32A423) || \
    defined (SOC_SERIES_AT32M412) || defined (SOC_SERIES_AT32M416)
    dmamux_channel_type *dmamux_channel;
    rt_uint32_t request_id;
#endif
};

#ifdef __cplusplus
}
#endif

#endif /*__DRV_DMA_H__ */

/************************** end of file ******************/
