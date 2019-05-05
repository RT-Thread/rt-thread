/*
 * Copyright (c) 2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-05     jg1uaa       the first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#define CPU_CLOCK       48000000        // Hz

void rt_hw_board_init(void);

void NVIC_EnableIRQ(rt_int32_t irqno);
void NVIC_DisableIRQ(rt_int32_t irqno);
rt_uint32_t NVIC_GetPendingIRQ(rt_int32_t irqno);
void NVIC_SetPendingIRQ(rt_int32_t irqno);
void NVIC_ClearPendingIRQ(rt_int32_t irqno);
void NVIC_SetPriority(rt_int32_t irqno, rt_uint32_t priority);

#endif /* __BOARD_H__ */
