/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 *   Atish Patra <atish.patra@wdc.com>
 */

#include <sbi/riscv_asm.h>
#include <sbi/sbi_ecall.h>
#include <sbi/sbi_ecall_interface.h>
#include <sbi/sbi_error.h>
#include <sbi/sbi_hart.h>
#include <sbi/sbi_ipi.h>
#include <sbi/sbi_system.h>
#include <sbi/sbi_timer.h>
#include <sbi/sbi_tlb.h>
#include <sbi/sbi_trap.h>

static int sbi_ecall_time_handler(unsigned long extid, unsigned long funcid,
				  const struct sbi_trap_regs *regs,
				  unsigned long *out_val,
				  struct sbi_trap_info *out_trap)
{
	int ret = 0;

	if (funcid == SBI_EXT_TIME_SET_TIMER) {
#if __riscv_xlen == 32
		sbi_timer_event_start((((u64)regs->a1 << 32) | (u64)regs->a0));
#else
		sbi_timer_event_start((u64)regs->a0);
#endif
	} else
		ret = SBI_ENOTSUPP;

	return ret;
}

struct sbi_ecall_extension ecall_time = {
	.extid_start = SBI_EXT_TIME,
	.extid_end = SBI_EXT_TIME,
	.handle = sbi_ecall_time_handler,
};

static int sbi_ecall_rfence_handler(unsigned long extid, unsigned long funcid,
				    const struct sbi_trap_regs *regs,
				    unsigned long *out_val,
				    struct sbi_trap_info *out_trap)
{
	int ret = 0;
	unsigned long vmid;
	struct sbi_tlb_info tlb_info;
	u32 source_hart = current_hartid();

	if (funcid >= SBI_EXT_RFENCE_REMOTE_HFENCE_GVMA &&
	    funcid <= SBI_EXT_RFENCE_REMOTE_HFENCE_VVMA_ASID)
		if (!misa_extension('H'))
			return SBI_ENOTSUPP;

	switch (funcid) {
	case SBI_EXT_RFENCE_REMOTE_FENCE_I:
		SBI_TLB_INFO_INIT(&tlb_info, 0, 0, 0, 0,
				  sbi_tlb_local_fence_i, source_hart);
		ret = sbi_tlb_request(regs->a0, regs->a1, &tlb_info);
		break;
	case SBI_EXT_RFENCE_REMOTE_HFENCE_GVMA:
		SBI_TLB_INFO_INIT(&tlb_info, regs->a2, regs->a3, 0, 0,
				  sbi_tlb_local_hfence_gvma, source_hart);
		ret = sbi_tlb_request(regs->a0, regs->a1, &tlb_info);
		break;
	case SBI_EXT_RFENCE_REMOTE_HFENCE_GVMA_VMID:
		SBI_TLB_INFO_INIT(&tlb_info, regs->a2, regs->a3, 0, regs->a4,
				  sbi_tlb_local_hfence_gvma_vmid,
				  source_hart);
		ret = sbi_tlb_request(regs->a0, regs->a1, &tlb_info);
		break;
	case SBI_EXT_RFENCE_REMOTE_HFENCE_VVMA:
		vmid = (csr_read(CSR_HGATP) & HGATP_VMID_MASK);
		vmid = vmid >> HGATP_VMID_SHIFT;
		SBI_TLB_INFO_INIT(&tlb_info, regs->a2, regs->a3, 0, vmid,
				  sbi_tlb_local_hfence_vvma, source_hart);
		ret = sbi_tlb_request(regs->a0, regs->a1, &tlb_info);
		break;
	case SBI_EXT_RFENCE_REMOTE_HFENCE_VVMA_ASID:
		vmid = (csr_read(CSR_HGATP) & HGATP_VMID_MASK);
		vmid = vmid >> HGATP_VMID_SHIFT;
		SBI_TLB_INFO_INIT(&tlb_info, regs->a2, regs->a3, regs->a4,
				  vmid, sbi_tlb_local_hfence_vvma_asid,
				  source_hart);
		ret = sbi_tlb_request(regs->a0, regs->a1, &tlb_info);
		break;
	case SBI_EXT_RFENCE_REMOTE_SFENCE_VMA:
		SBI_TLB_INFO_INIT(&tlb_info, regs->a2, regs->a3, 0, 0,
				  sbi_tlb_local_sfence_vma, source_hart);
		ret = sbi_tlb_request(regs->a0, regs->a1, &tlb_info);
		break;
	case SBI_EXT_RFENCE_REMOTE_SFENCE_VMA_ASID:
		SBI_TLB_INFO_INIT(&tlb_info, regs->a2, regs->a3, regs->a4, 0,
				  sbi_tlb_local_sfence_vma_asid, source_hart);
		ret = sbi_tlb_request(regs->a0, regs->a1, &tlb_info);
		break;
	default:
		ret = SBI_ENOTSUPP;
	};

	return ret;
}

struct sbi_ecall_extension ecall_rfence = {
	.extid_start = SBI_EXT_RFENCE,
	.extid_end = SBI_EXT_RFENCE,
	.handle = sbi_ecall_rfence_handler,
};

static int sbi_ecall_ipi_handler(unsigned long extid, unsigned long funcid,
				 const struct sbi_trap_regs *regs,
				 unsigned long *out_val,
				 struct sbi_trap_info *out_trap)
{
	int ret = 0;

	if (funcid == SBI_EXT_IPI_SEND_IPI)
		ret = sbi_ipi_send_smode(regs->a0, regs->a1);
	else
		ret = SBI_ENOTSUPP;

	return ret;
}

struct sbi_ecall_extension ecall_ipi = {
	.extid_start = SBI_EXT_IPI,
	.extid_end = SBI_EXT_IPI,
	.handle = sbi_ecall_ipi_handler,
};

static int sbi_ecall_srst_handler(unsigned long extid, unsigned long funcid,
				  const struct sbi_trap_regs *regs,
				  unsigned long *out_val,
				  struct sbi_trap_info *out_trap)
{
	if (funcid == SBI_EXT_SRST_RESET) {
		if ((((u32)-1U) <= ((u64)regs->a0)) ||
		    (((u32)-1U) <= ((u64)regs->a1)))
			return SBI_EINVAL;

		switch (regs->a0) {
		case SBI_SRST_RESET_TYPE_SHUTDOWN:
		case SBI_SRST_RESET_TYPE_COLD_REBOOT:
		case SBI_SRST_RESET_TYPE_WARM_REBOOT:
			break;
		default:
			return SBI_ENOTSUPP;
		}

		switch (regs->a1) {
		case SBI_SRST_RESET_REASON_NONE:
		case SBI_SRST_RESET_REASON_SYSFAIL:
			break;
		default:
			return SBI_ENOTSUPP;
		}

		if (sbi_system_reset_supported(regs->a0, regs->a1))
			sbi_system_reset(regs->a0, regs->a1);
	}

	return SBI_ENOTSUPP;
}

static int sbi_ecall_srst_probe(unsigned long extid, unsigned long *out_val)
{
	u32 type, count = 0;

	/*
	 * At least one standard reset types should be supported by
	 * the platform for SBI SRST extension to be usable.
	 */

	for (type = 0; type <= SBI_SRST_RESET_TYPE_LAST; type++) {
		if (sbi_system_reset_supported(type,
					SBI_SRST_RESET_REASON_NONE))
			count++;
	}

	*out_val = (count) ? 1 : 0;
	return 0;
}

struct sbi_ecall_extension ecall_srst = {
	.extid_start = SBI_EXT_SRST,
	.extid_end = SBI_EXT_SRST,
	.handle = sbi_ecall_srst_handler,
	.probe = sbi_ecall_srst_probe,
};
