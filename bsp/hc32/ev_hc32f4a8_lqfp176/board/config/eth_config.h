/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

#ifndef __ETH_CONFIG_H__
#define __ETH_CONFIG_H__

#include <rtthread.h>
#include "irq_config.h"

#ifdef __cplusplus
extern "C" {
#endif


#if defined(BSP_USING_ETH)

#ifndef ETH_IRQ_CONFIG
#define ETH_IRQ_CONFIG                                      \
    {                                                       \
        .irq_num    = BSP_ETH_IRQ_NUM,                      \
        .irq_prio   = BSP_ETH_IRQ_PRIO,                     \
        .int_src    = INT_SRC_ETH_GLB_INT,                  \
    }
#endif /* ETH_IRQ_CONFIG */

#endif


#ifdef __cplusplus
}
#endif

#endif /* __ETH_CONFIG_H__ */
