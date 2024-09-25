/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Andes Technology Corporation
 *
 * Authors:
 *   Zong Li <zong@andestech.com>
 *   Nylon Chen <nylon7@andestech.com>
 */

#include <sbi/riscv_asm.h>
#include <sbi/riscv_io.h>
#include <sbi/sbi_types.h>
#include "plicsw.h"
#include "platform.h"

static u32 plicsw_ipi_hart_count;
static struct plicsw plicsw_dev[AE350_HART_COUNT];

static inline void plicsw_claim(void)
{
	u32 source_hart = current_hartid();

	plicsw_dev[source_hart].source_id =
		readl(plicsw_dev[source_hart].plicsw_claim);
}

static inline void plicsw_complete(void)
{
	u32 source_hart = current_hartid();
	u32 source = plicsw_dev[source_hart].source_id;

	writel(source, plicsw_dev[source_hart].plicsw_claim);
}

static inline u32 plicsw_get_pending(u32 source_hart, u32 target_hart)
{
	return readl(plicsw_dev[source_hart].plicsw_pending)
	       & (PLICSW_HART_MASK >> target_hart);
}

static inline void plic_sw_pending(u32 target_hart)
{
	/*
	 * The pending array registers are w1s type.
	 * IPI pending array mapping as following:
	 *
	 * Pending array start address: base + 0x1000
	 * -------------------------------------
	 * | hart 3 | hart 2 | hart 1 | hart 0 |
	 * -------------------------------------
	 * Each hart X can send IPI to another hart by setting the
	 * corresponding bit in hart X own region(see the below).
	 *
	 * In each hart region:
	 * -----------------------------------------------
	 * | bit 7 | bit 6 | bit 5 | bit 4 | ... | bit 0 |
	 * -----------------------------------------------
	 * The bit 7 is used to send IPI to hart 0
	 * The bit 6 is used to send IPI to hart 1
	 * The bit 5 is used to send IPI to hart 2
	 * The bit 4 is used to send IPI to hart 3
	 */
	u32 source_hart = current_hartid();
	u32 target_offset = (PLICSW_PENDING_PER_HART - 1) - target_hart;
	u32 per_hart_offset = PLICSW_PENDING_PER_HART * source_hart;
	u32 val = 1 << target_offset << per_hart_offset;

	writel(val, plicsw_dev[source_hart].plicsw_pending);
}

void plicsw_ipi_send(u32 target_hart)
{
	if (plicsw_ipi_hart_count <= target_hart)
		return;

	/* Set PLICSW IPI */
	plic_sw_pending(target_hart);
}

void plicsw_ipi_clear(u32 target_hart)
{
	if (plicsw_ipi_hart_count <= target_hart)
		return;

	/* Clear CLINT IPI */
	plicsw_claim();
	plicsw_complete();
}

int plicsw_warm_ipi_init(void)
{
	u32 hartid = current_hartid();

	if (!plicsw_dev[hartid].plicsw_pending
	    && !plicsw_dev[hartid].plicsw_enable
	    && !plicsw_dev[hartid].plicsw_claim)
		return -1;

	/* Clear PLICSW IPI */
	plicsw_ipi_clear(hartid);

	return 0;
}

int plicsw_cold_ipi_init(unsigned long base, u32 hart_count)
{
	/* Setup source priority */
	uint32_t *priority = (void *)base + PLICSW_PRIORITY_BASE;

	for (int i = 0; i < AE350_HART_COUNT*PLICSW_PENDING_PER_HART; i++)
		writel(1, &priority[i]);

	/* Setup target enable.*/
	uint32_t enable_mask = PLICSW_HART_MASK;

	for (int i = 0; i < AE350_HART_COUNT; i++) {
		uint32_t *enable = (void *)base + PLICSW_ENABLE_BASE
			+ PLICSW_ENABLE_PER_HART * i;
		writel(enable_mask, &enable[0]);
		enable_mask >>= 1;
	}

	/* Figure-out PLICSW IPI register address */
	plicsw_ipi_hart_count = hart_count;

	for (u32 hartid = 0; hartid < AE350_HART_COUNT; hartid++) {
		plicsw_dev[hartid].source_id = 0;
		plicsw_dev[hartid].plicsw_pending =
			(void *)base
			+ PLICSW_PENDING_BASE
			+ ((hartid / 4) * 4);
		plicsw_dev[hartid].plicsw_enable  =
			(void *)base
			+ PLICSW_ENABLE_BASE
			+ PLICSW_ENABLE_PER_HART * hartid;
		plicsw_dev[hartid].plicsw_claim   =
			(void *)base
			+ PLICSW_CONTEXT_BASE
			+ PLICSW_CONTEXT_CLAIM
			+ PLICSW_CONTEXT_PER_HART * hartid;
	}

	return 0;
}
