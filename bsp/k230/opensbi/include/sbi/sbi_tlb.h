/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Atish Patra <atish.patra@wdc.com>
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SBI_TLB_H__
#define __SBI_TLB_H__

#include <sbi/sbi_types.h>
#include <sbi/sbi_hartmask.h>

/* clang-format off */

#define SBI_TLB_FLUSH_ALL			((unsigned long)-1)

/* clang-format on */

#define SBI_TLB_FIFO_NUM_ENTRIES		8

struct sbi_scratch;

struct sbi_tlb_info {
	unsigned long start;
	unsigned long size;
	unsigned long asid;
	unsigned long vmid;
	void (*local_fn)(struct sbi_tlb_info *tinfo);
	struct sbi_hartmask smask;
};

void sbi_tlb_local_hfence_vvma(struct sbi_tlb_info *tinfo);
void sbi_tlb_local_hfence_gvma(struct sbi_tlb_info *tinfo);
void sbi_tlb_local_sfence_vma(struct sbi_tlb_info *tinfo);
void sbi_tlb_local_hfence_vvma_asid(struct sbi_tlb_info *tinfo);
void sbi_tlb_local_hfence_gvma_vmid(struct sbi_tlb_info *tinfo);
void sbi_tlb_local_sfence_vma_asid(struct sbi_tlb_info *tinfo);
void sbi_tlb_local_fence_i(struct sbi_tlb_info *tinfo);

#define SBI_TLB_INFO_INIT(__p, __start, __size, __asid, __vmid, __lfn, __src) \
do { \
	(__p)->start = (__start); \
	(__p)->size = (__size); \
	(__p)->asid = (__asid); \
	(__p)->vmid = (__vmid); \
	(__p)->local_fn = (__lfn); \
	SBI_HARTMASK_INIT_EXCEPT(&(__p)->smask, (__src)); \
} while (0)

#define SBI_TLB_INFO_SIZE		sizeof(struct sbi_tlb_info)

int sbi_tlb_request(ulong hmask, ulong hbase, struct sbi_tlb_info *tinfo);

int sbi_tlb_init(struct sbi_scratch *scratch, bool cold_boot);

#endif
