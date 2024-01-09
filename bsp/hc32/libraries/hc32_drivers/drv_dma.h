/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

#ifndef __DRV_DMA_H__
#define __DRV_DMA_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtthread.h>
#include "drv_irq.h"

#ifdef __cplusplus
extern "C" {
#endif

struct dma_config
{
    CM_DMA_TypeDef          *Instance;
    rt_uint32_t             channel;
    rt_uint32_t             clock;
    rt_uint32_t             trigger_select;
    en_event_src_t          trigger_event;
    rt_uint32_t             flag;
    struct hc32_irq_config  irq_config;
    func_ptr_t              irq_callback;
};

#ifdef __cplusplus
}
#endif

#endif /* __DRV_DMA_H__ */

