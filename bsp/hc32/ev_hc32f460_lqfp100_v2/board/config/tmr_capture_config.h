/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-10     CDT          first version
 */

#ifndef __IC_CONFIG_H__
#define __IC_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined (BSP_USING_INPUT_CAPTURE_TMR6_1)
#define IC1_NAME "ic1"
#define INPUT_CAPTURE_CFG_TMR6_1                                                \
{                                                                               \
    .name = IC1_NAME,                                                           \
    .ch = TMR6_CH_A,                                                            \
    .clk_div = TMR6_CLK_DIV4,                                                   \
    .first_edge = TMR6_CAPT_COND_PWMA_FALLING,                                  \
    .irq_num_cap = BSP_INPUT_CAPTURE_TMR6_1_CAP_IRQ_NUM,                        \
    .irq_prio_cap = BSP_INPUT_CAPTURE_TMR6_1_CAP_IRQ_PRIO,                      \
    .irq_num_ovf = BSP_INPUT_CAPTURE_TMR6_1_OVF_IRQ_NUM,                        \
    .irq_prio_ovf = BSP_INPUT_CAPTURE_TMR6_1_OVF_IRQ_PRIO,                      \
}
#endif

#if defined (BSP_USING_INPUT_CAPTURE_TMR6_2)
#define IC2_NAME "ic2"
#define INPUT_CAPTURE_CFG_TMR6_2                                                \
{                                                                               \
    .name = IC2_NAME,                                                           \
    .ch = TMR6_CH_A,                                                            \
    .clk_div = TMR6_CLK_DIV8,                                                   \
    .first_edge = TMR6_CAPT_COND_TRIGB_RISING,                                  \
    .irq_num_cap = BSP_INPUT_CAPTURE_TMR6_2_CAP_IRQ_NUM,                        \
    .irq_prio_cap = BSP_INPUT_CAPTURE_TMR6_2_CAP_IRQ_PRIO,                      \
    .irq_num_ovf = BSP_INPUT_CAPTURE_TMR6_2_OVF_IRQ_NUM,                        \
    .irq_prio_ovf = BSP_INPUT_CAPTURE_TMR6_2_OVF_IRQ_PRIO,                      \
}
#endif

#if defined (BSP_USING_INPUT_CAPTURE_TMR6_3)
#define IC3_NAME "ic3"
#define INPUT_CAPTURE_CFG_TMR6_3                                                \
{                                                                               \
    .name = IC3_NAME,                                                           \
    .ch = TMR6_CH_B,                                                            \
    .clk_div = TMR6_CLK_DIV16,                                                  \
    .first_edge = TMR6_CAPT_COND_TRIGA_FALLING,                                 \
    .irq_num_cap = BSP_INPUT_CAPTURE_TMR6_3_CAP_IRQ_NUM,                        \
    .irq_prio_cap = BSP_INPUT_CAPTURE_TMR6_3_CAP_IRQ_PRIO,                      \
    .irq_num_ovf = BSP_INPUT_CAPTURE_TMR6_3_OVF_IRQ_NUM,                        \
    .irq_prio_ovf = BSP_INPUT_CAPTURE_TMR6_3_OVF_IRQ_PRIO,                      \
}
#endif

#ifdef __cplusplus
}
#endif

#endif /* __IC_CONFIG_H__ */
