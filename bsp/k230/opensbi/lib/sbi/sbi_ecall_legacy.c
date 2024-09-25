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
#include <sbi/sbi_console.h>
#include <sbi/sbi_domain.h>
#include <sbi/sbi_ecall.h>
#include <sbi/sbi_ecall_interface.h>
#include <sbi/sbi_error.h>
#include <sbi/sbi_hsm.h>
#include <sbi/sbi_ipi.h>
#include <sbi/sbi_platform.h>
#include <sbi/sbi_system.h>
#include <sbi/sbi_timer.h>
#include <sbi/sbi_tlb.h>
#include <sbi/sbi_trap.h>
#include <sbi/sbi_unpriv.h>
#include <sbi/sbi_hart.h>

static int sbi_load_hart_mask_unpriv(ulong *pmask, ulong *hmask,
				     struct sbi_trap_info *uptrap)
{
	ulong mask = 0;

	if (pmask) {
		mask = sbi_load_ulong(pmask, uptrap);
		if (uptrap->cause)
			return SBI_ETRAP;
	} else {
		sbi_hsm_hart_interruptible_mask(sbi_domain_thishart_ptr(),
						0, &mask);
	}
	*hmask = mask;

	return 0;
}

static int sbi_ecall_legacy_handler(unsigned long extid, unsigned long funcid,
				    const struct sbi_trap_regs *regs,
				    unsigned long *out_val,
				    struct sbi_trap_info *out_trap)
{
	int ret = 0;
	struct sbi_tlb_info tlb_info;
	u32 source_hart = current_hartid();
	ulong hmask = 0;

	switch (extid) {
	case SBI_EXT_0_1_SET_TIMER:
#if __riscv_xlen == 32
		sbi_timer_event_start((((u64)regs->a1 << 32) | (u64)regs->a0));
#else
		sbi_timer_event_start((u64)regs->a0);
#endif
		break;
	case SBI_EXT_0_1_CONSOLE_PUTCHAR:
		sbi_putc(regs->a0);
		break;
	case SBI_EXT_0_1_CONSOLE_GETCHAR:
		ret = sbi_getc();
		break;
	case SBI_EXT_0_1_CLEAR_IPI:
		sbi_ipi_clear_smode();
		break;
	case SBI_EXT_0_1_SEND_IPI:
		ret = sbi_load_hart_mask_unpriv((ulong *)regs->a0,
						&hmask, out_trap);
		if (ret != SBI_ETRAP)
			ret = sbi_ipi_send_smode(hmask, 0);
		break;
	case SBI_EXT_0_1_REMOTE_FENCE_I:
		ret = sbi_load_hart_mask_unpriv((ulong *)regs->a0,
						&hmask, out_trap);
		if (ret != SBI_ETRAP) {
			SBI_TLB_INFO_INIT(&tlb_info, 0, 0, 0, 0,
					  sbi_tlb_local_fence_i,
					  source_hart);
			ret = sbi_tlb_request(hmask, 0, &tlb_info);
		}
		break;
	case SBI_EXT_0_1_REMOTE_SFENCE_VMA:
		ret = sbi_load_hart_mask_unpriv((ulong *)regs->a0,
						&hmask, out_trap);
		if (ret != SBI_ETRAP) {
			SBI_TLB_INFO_INIT(&tlb_info, regs->a1, regs->a2, 0, 0,
					  sbi_tlb_local_sfence_vma,
					  source_hart);
			ret = sbi_tlb_request(hmask, 0, &tlb_info);
		}
		break;
	case SBI_EXT_0_1_REMOTE_SFENCE_VMA_ASID:
		ret = sbi_load_hart_mask_unpriv((ulong *)regs->a0,
						&hmask, out_trap);
		if (ret != SBI_ETRAP) {
			SBI_TLB_INFO_INIT(&tlb_info, regs->a1,
					  regs->a2, regs->a3, 0,
					  sbi_tlb_local_sfence_vma_asid,
					  source_hart);
			ret = sbi_tlb_request(hmask, 0, &tlb_info);
		}
		break;
	case SBI_EXT_0_1_SHUTDOWN:
		sbi_system_reset(SBI_SRST_RESET_TYPE_SHUTDOWN,
				 SBI_SRST_RESET_REASON_NONE);
		break;
	default:
		ret = SBI_ENOTSUPP;
	};

	return ret;
}

struct sbi_ecall_extension ecall_legacy = {
	.extid_start = SBI_EXT_0_1_SET_TIMER,
	.extid_end = SBI_EXT_0_1_SHUTDOWN,
	.handle = sbi_ecall_legacy_handler,
};
