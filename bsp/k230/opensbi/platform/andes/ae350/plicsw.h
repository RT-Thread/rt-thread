/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Andes Technology Corporation
 *
 * Authors:
 *   Zong Li <zong@andestech.com>
 *   Nylon Chen <nylon7@andestech.com>
 */

#ifndef _AE350_PLICSW_H_
#define _AE350_PLICSW_H_

#define PLICSW_PRIORITY_BASE		0x4

#define PLICSW_PENDING_BASE		0x1000
#define PLICSW_PENDING_PER_HART		0x8

#define PLICSW_ENABLE_BASE		0x2000
#define PLICSW_ENABLE_PER_HART		0x80

#define PLICSW_CONTEXT_BASE		0x200000
#define PLICSW_CONTEXT_PER_HART		0x1000
#define PLICSW_CONTEXT_CLAIM		0x4

#define PLICSW_HART_MASK		0x80808080

struct plicsw {
	u32 source_id;

	volatile uint32_t *plicsw_pending;
	volatile uint32_t *plicsw_enable;
	volatile uint32_t *plicsw_claim;
};

void plicsw_ipi_send(u32 target_hart);

void plicsw_ipi_sync(u32 target_hart);

void plicsw_ipi_clear(u32 target_hart);

int plicsw_warm_ipi_init(void);

int plicsw_cold_ipi_init(unsigned long base, u32 hart_count);

#endif /* _AE350_PLICSW_H_ */
