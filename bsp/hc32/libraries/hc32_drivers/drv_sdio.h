/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-14     CDT          first version
 */

#ifndef __DRV_SDIO_H__
#define __DRV_SDIO_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtthread.h>
#include "rtdevice.h"
#include "drv_dma.h"
#include "drv_irq.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/* sdio package */
struct sdio_pkg
{
    struct rt_mmcsd_cmd *cmd;
    void *buf;
    rt_uint32_t flag;
};

typedef rt_err_t (*sdio_txconfig)(CM_DMA_TypeDef *dma_instance, rt_uint8_t channel, struct sdio_pkg *pkg);
typedef rt_err_t (*sdio_rxconfig)(CM_DMA_TypeDef *dma_instance, rt_uint8_t channel, struct sdio_pkg *pkg);
typedef rt_uint32_t (*sdio_clk_get)(CM_SDIOC_TypeDef *sdio_instance);

/* hc32 sdio des */
struct hc32_sdio_des
{
    sdio_clk_get  clk_get;
    sdio_txconfig txconfig;
    sdio_rxconfig rxconfig;
};

/* hc32 sdio configure */
struct hc32_sdio_config
{
    const char             *name;
    CM_SDIOC_TypeDef       *instance;
    rt_uint32_t            clock;
    struct hc32_irq_config irq_config;
    struct dma_config      dma_rx;
    struct dma_config      dma_tx;
};

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __DRV_SDIO_H__ */
