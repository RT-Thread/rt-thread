/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-31     lizhirui     first version
 */

#ifndef __PLIC_H__
#define __PLIC_H__

#define PLIC_PRIORITY_BASE 0x0
#define PLIC_PENDING_BASE 0x1000
#define PLIC_ENABLE_BASE 0x2000
#define PLIC_ENABLE_STRIDE 0x80
#define PLIC_CONTEXT_BASE 0x200000
#define PLIC_CONTEXT_STRIDE 0x1000

#define PLIC_BASE_ADDR 0xC000000

void plic_set_priority(rt_uint32_t source,rt_uint32_t val);
void plic_set_thresh(rt_uint32_t val);
void plic_set_ie(rt_uint32_t word_index,rt_uint32_t val);
void plic_init();

#endif