/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * V861 C907 CLINT at MAPBADDR+0x04000000 (probed: 0x34000000).
 */

#ifndef V861_CLINT_H__
#define V861_CLINT_H__

#include <stdint.h>

#define V861_CLINT_BASE        0x34000000U
#define V861_CLINT_MSIP(n)     (V861_CLINT_BASE + 4U * (n))
#define V861_CLINT_MTIMECMP(n) (V861_CLINT_BASE + 0x4000U + 8U * (n))
#define V861_CLINT_MTIME       (V861_CLINT_BASE + 0xBFF8U)

/* timebase used for tick; same 24 MHz order as UART clock assumption */
#define V861_CLINT_TIMEBASE_HZ 24000000U

void v861_clint_ipi_send(unsigned int hartid);
void v861_clint_ipi_clear(unsigned int hartid);
void v861_clint_set_mtimecmp(unsigned int hartid, uint64_t value);
uint64_t v861_clint_mtime(void);

#endif
