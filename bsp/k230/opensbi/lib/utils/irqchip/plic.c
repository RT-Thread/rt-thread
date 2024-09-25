/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#include <sbi/riscv_io.h>
#include <sbi/riscv_encoding.h>
#include <sbi/sbi_console.h>
#include <sbi/sbi_error.h>
#include <sbi/sbi_string.h>
#include <sbi_utils/irqchip/plic.h>

#define PLIC_PRIORITY_BASE 0x0
#define PLIC_PENDING_BASE 0x1000
#define PLIC_ENABLE_BASE 0x2000
#define PLIC_ENABLE_STRIDE 0x80
#define PLIC_CONTEXT_BASE 0x200000
#define PLIC_CONTEXT_STRIDE 0x1000

static void plic_set_priority(struct plic_data *plic, u32 source, u32 val)
{
	volatile void *plic_priority = (void *)plic->addr +
			PLIC_PRIORITY_BASE + 4 * source;
	writel(val, plic_priority);
}

void plic_set_thresh(struct plic_data *plic, u32 cntxid, u32 val)
{
	volatile void *plic_thresh;

	if (!plic)
		return;

	plic_thresh = (void *)plic->addr +
		      PLIC_CONTEXT_BASE + PLIC_CONTEXT_STRIDE * cntxid;
	writel(val, plic_thresh);
}

void plic_set_ie(struct plic_data *plic, u32 cntxid, u32 word_index, u32 val)
{
	volatile void *plic_ie;

	if (!plic)
		return;

	plic_ie = (void *)plic->addr +
		   PLIC_ENABLE_BASE + PLIC_ENABLE_STRIDE * cntxid;
	writel(val, plic_ie + word_index * 4);
}

int plic_warm_irqchip_init(struct plic_data *plic,
			   int m_cntx_id, int s_cntx_id)
{
	size_t i, ie_words;

	if (!plic)
		return SBI_EINVAL;

	ie_words = plic->num_src / 32 + 1;

	/* By default, disable all IRQs for M-mode of target HART */
	if (m_cntx_id > -1) {
		for (i = 0; i < ie_words; i++)
			plic_set_ie(plic, m_cntx_id, i, 0);
	}

	/* By default, disable all IRQs for S-mode of target HART */
	if (s_cntx_id > -1) {
		for (i = 0; i < ie_words; i++)
			plic_set_ie(plic, s_cntx_id, i, 0);
	}

	/* By default, disable M-mode threshold */
	if (m_cntx_id > -1)
		plic_set_thresh(plic, m_cntx_id, 0x7);

	/* By default, disable S-mode threshold */
	if (s_cntx_id > -1)
		plic_set_thresh(plic, s_cntx_id, 0x7);

	return 0;
}

int plic_cold_irqchip_init(struct plic_data *plic)
{
	int i;

	if (!plic)
		return SBI_EINVAL;

	/* Configure default priorities of all IRQs */
	for (i = 1; i <= plic->num_src; i++)
		plic_set_priority(plic, i, 1);

	return 0;
}
