/**
 * @file drv_dma.h
 * @author 100ask development team
 * @brief
 * @version 0.1
 * @date 2022-06-16
 *
 * @copyright Copyright (c) 2022 Chongqing 100ASK Technology Co., LTD
 *
 */

#ifndef __DRV_DMA_H_
#define __DRV_DMA_H_

#include <rtthread.h>
#include "drv_common.h"

#ifdef __cplusplus
extern "C" {
#endif

struct dma_config {
    DMA_Type *dma_port;
    rt_uint32_t dma_req;
    IRQn_Type dma_irq;
    rt_uint32_t dma_rcc;
};

#ifdef __cplusplus
}
#endif

#endif /*__DRV_DMA_H_ */
