/*
 * Copyright (C) 2021, lizhengyang
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2021-09-02      lizhengyang     first version
 */

#ifndef __DRV_IRQ_H__
#define __DRV_IRQ_H__

#include <rtdef.h>
#include "hc32_ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif
struct hc32_irq_config
{
    IRQn_Type    irq;
    uint32_t     irq_prio;
    en_int_src_t int_src;
};

rt_err_t hc32_install_irq_handler(struct hc32_irq_config *irq_config,
                                  void (*irq_hdr)(void),
                                  rt_bool_t irq_enable);

#ifdef __cplusplus
}
#endif

#endif
