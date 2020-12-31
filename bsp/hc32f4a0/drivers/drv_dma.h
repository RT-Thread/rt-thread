/*
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-30     CDT          first version
 */

#ifndef __DRV_DMA_H__
#define __DRV_DMA_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtthread.h>
#include "hc32_ddl.h"
#include "drv_irq.h"

#ifdef __cplusplus
extern "C" {
#endif

struct dma_config {
    M4_DMA_TypeDef  *Instance;
    rt_uint32_t     channel;

    en_event_src_t  trigger_evt_src;

    struct hc32_irq_config irq_config;
};
                                   
#ifdef __cplusplus
}
#endif

#endif /* __DRV_DMA_H__ */

