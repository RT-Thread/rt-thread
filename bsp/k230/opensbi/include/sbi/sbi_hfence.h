/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Atish Patra <atish.patra@wdc.com>
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SBI_FENCE_H__
#define __SBI_FENCE_H__

/** Invalidate Stage2 TLBs for given VMID and guest physical address */
void __sbi_hfence_gvma_vmid_gpa(unsigned long gpa, unsigned long vmid);

/** Invalidate Stage2 TLBs for given VMID */
void __sbi_hfence_gvma_vmid(unsigned long vmid);

/** Invalidate Stage2 TLBs for given guest physical address */
void __sbi_hfence_gvma_gpa(unsigned long gpa);

/** Invalidate all possible Stage2 TLBs */
void __sbi_hfence_gvma_all(void);

/** Invalidate unified TLB entries for given asid and guest virtual address */
void __sbi_hfence_vvma_asid_va(unsigned long va, unsigned long asid);

/** Invalidate unified TLB entries for given ASID for a guest*/
void __sbi_hfence_vvma_asid(unsigned long asid);

/** Invalidate unified TLB entries for a given guest virtual address */
void __sbi_hfence_vvma_va(unsigned long va);

/** Invalidate all possible Stage2 TLBs */
void __sbi_hfence_vvma_all(void);

#endif
