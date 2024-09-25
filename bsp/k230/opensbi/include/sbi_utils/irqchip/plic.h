/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __IRQCHIP_PLIC_H__
#define __IRQCHIP_PLIC_H__

#include <sbi/sbi_types.h>

struct plic_data {
	unsigned long addr;
	unsigned long num_src;
};

int plic_warm_irqchip_init(struct plic_data *plic,
			   int m_cntx_id, int s_cntx_id);

int plic_cold_irqchip_init(struct plic_data *plic);

void plic_set_thresh(struct plic_data *plic, u32 cntxid, u32 val);

void plic_set_ie(struct plic_data *plic, u32 cntxid, u32 word_index, u32 val);

#endif
