/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     zx.chen      novic table init
 */

#include <csi_config.h>
#include <soc.h>

extern void Default_Handler(void);
extern void SysTick_Handler(void);
extern void TIM4_NMIHandler(void);

void (*g_irqvector[48])(void);
void (*g_nmivector)(void);

void irq_vectors_init(void)
{
    int i;

    for (i = 0; i < 48; i++)
    {
        g_irqvector[i] = Default_Handler;
    }

    g_irqvector[CORET_IRQn] = SysTick_Handler;
    g_nmivector = TIM4_NMIHandler;
}
