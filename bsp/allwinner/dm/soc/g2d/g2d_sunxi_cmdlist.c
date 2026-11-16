/*
 * Copyright (c) 2026 Yuzuki Tsuru
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

#include <string.h>

#include <rthw.h>
#include <rtthread.h>

#include "g2d_sunxi_hw.h"

/* one entry of the header area, read by the hardware */
struct g2d_rcq_header {
	/** address of the register image (32 byte aligned) */
	uint32_t addr_low;
	/** [23:0] length in bytes, [31:24] address bits 39:32 */
	uint32_t len;
	/** [0] write this block, [31:16] length of the header area of the next frame */
	uint32_t flags;
	/** register offset from the base of the G2D */
	uint32_t reg_offset;
};

#define RCQ_HEADER_BYTES (G2D_CMDLIST_MAX_BLOCKS * sizeof(struct g2d_rcq_header))
#define RCQ_FLAG_DIRTY RT_BIT(0)

RT_STATIC_ASSERT(g2d_rcq_header_alignment,
        RCQ_HEADER_BYTES % G2D_CMDLIST_ALIGN == 0);

void g2d_cmdlist_init(struct g2d_cmdlist *cl, void *mem, size_t size)
{
    RT_ASSERT(((uintptr_t)mem % G2D_CMDLIST_ALIGN) == 0);

	cl->mem = mem;
	cl->size = size;
	cl->used = RCQ_HEADER_BYTES;
	cl->blocks = 0;
	memset(mem, 0, RCQ_HEADER_BYTES);
}

uint32_t *g2d_cmdlist_block(struct g2d_cmdlist *cl, uint32_t offset, size_t bytes)
{
	struct g2d_rcq_header *hdr = (struct g2d_rcq_header *)cl->mem + cl->blocks;
	size_t span = RT_ALIGN(bytes, G2D_CMDLIST_ALIGN);
	uint8_t *data;

	if (cl->blocks >= G2D_CMDLIST_MAX_BLOCKS || cl->used + span > cl->size) {
		return NULL;
	}

	data = cl->mem + cl->used;
	memset(data, 0, span);
	hdr->addr_low = (uint32_t)(uintptr_t)data;
	hdr->len = bytes;
	hdr->flags = RCQ_FLAG_DIRTY;
	hdr->reg_offset = offset;

	cl->used += span;
	cl->blocks++;
	return (uint32_t *)data;
}

size_t g2d_cmdlist_finish(struct g2d_cmdlist *cl)
{
	if (cl->blocks == 0) {
		return 0;
	}
	/* the hardware reads the headers in pairs; unused entries are zero (not dirty) */
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, cl->mem, cl->used);
	return RT_ALIGN(cl->blocks, 2) * sizeof(struct g2d_rcq_header);
}
