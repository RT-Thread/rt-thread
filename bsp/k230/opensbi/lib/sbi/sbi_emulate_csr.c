/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#include <sbi/riscv_asm.h>
#include <sbi/riscv_encoding.h>
#include <sbi/sbi_bitops.h>
#include <sbi/sbi_console.h>
#include <sbi/sbi_emulate_csr.h>
#include <sbi/sbi_error.h>
#include <sbi/sbi_hart.h>
#include <sbi/sbi_scratch.h>
#include <sbi/sbi_timer.h>
#include <sbi/sbi_trap.h>

static bool hpm_allowed(int hpm_num, ulong prev_mode, bool virt)
{
	ulong cen = -1UL;
	struct sbi_scratch *scratch = sbi_scratch_thishart_ptr();

	if (prev_mode <= PRV_S) {
		if (sbi_hart_has_feature(scratch, SBI_HART_HAS_MCOUNTEREN)) {
			cen &= csr_read(CSR_MCOUNTEREN);
			if (virt)
				cen &= csr_read(CSR_HCOUNTEREN);
		} else {
			cen = 0;
		}
	}
	if (prev_mode == PRV_U) {
		if (sbi_hart_has_feature(scratch, SBI_HART_HAS_SCOUNTEREN))
			cen &= csr_read(CSR_SCOUNTEREN);
		else
			cen = 0;
	}

	return ((cen >> hpm_num) & 1) ? TRUE : FALSE;
}

int sbi_emulate_csr_read(int csr_num, struct sbi_trap_regs *regs,
			 ulong *csr_val)
{
	int ret = 0;
	struct sbi_scratch *scratch = sbi_scratch_thishart_ptr();
	ulong prev_mode = (regs->mstatus & MSTATUS_MPP) >> MSTATUS_MPP_SHIFT;
#if __riscv_xlen == 32
	bool virt = (regs->mstatusH & MSTATUSH_MPV) ? TRUE : FALSE;
#else
	bool virt = (regs->mstatus & MSTATUS_MPV) ? TRUE : FALSE;
#endif

	switch (csr_num) {
	case CSR_HTIMEDELTA:
		if (prev_mode == PRV_S && !virt)
			*csr_val = sbi_timer_get_delta();
		else
			ret = SBI_ENOTSUPP;
		break;
	case CSR_CYCLE:
		if (!hpm_allowed(csr_num - CSR_CYCLE, prev_mode, virt))
			return SBI_ENOTSUPP;
		*csr_val = csr_read(CSR_MCYCLE);
		break;
	case CSR_TIME:
		/*
		 * We emulate TIME CSR for both Host (HS/U-mode) and
		 * Guest (VS/VU-mode).
		 *
		 * Faster TIME CSR reads are critical for good performance
		 * in S-mode software so we don't check CSR permissions.
		 */
		*csr_val = (virt) ? sbi_timer_virt_value():
				    sbi_timer_value();
		break;
	case CSR_INSTRET:
		if (!hpm_allowed(csr_num - CSR_CYCLE, prev_mode, virt))
			return SBI_ENOTSUPP;
		*csr_val = csr_read(CSR_MINSTRET);
		break;

#if __riscv_xlen == 32
	case CSR_HTIMEDELTAH:
		if (prev_mode == PRV_S && !virt)
			*csr_val = sbi_timer_get_delta() >> 32;
		else
			ret = SBI_ENOTSUPP;
		break;
	case CSR_CYCLEH:
		if (!hpm_allowed(csr_num - CSR_CYCLEH, prev_mode, virt))
			return SBI_ENOTSUPP;
		*csr_val = csr_read(CSR_MCYCLEH);
		break;
	case CSR_TIMEH:
		/* Refer comments on TIME CSR above. */
		*csr_val = (virt) ? sbi_timer_virt_value() >> 32:
				    sbi_timer_value() >> 32;
		break;
	case CSR_INSTRETH:
		if (!hpm_allowed(csr_num - CSR_CYCLEH, prev_mode, virt))
			return SBI_ENOTSUPP;
		*csr_val = csr_read(CSR_MINSTRETH);
		break;
#endif

#define switchcase_hpm(__uref, __mref, __csr)				\
	case __csr:							\
		if ((sbi_hart_mhpm_count(scratch) + 3) <= (__csr - __uref))\
			return SBI_ENOTSUPP;				\
		if (!hpm_allowed(__csr - __uref, prev_mode, virt))	\
			return SBI_ENOTSUPP;				\
		*csr_val = csr_read(__mref + __csr - __uref);		\
		break;
#define switchcase_hpm_2(__uref, __mref, __csr)			\
	switchcase_hpm(__uref, __mref, __csr + 0)			\
	switchcase_hpm(__uref, __mref, __csr + 1)
#define switchcase_hpm_4(__uref, __mref, __csr)			\
	switchcase_hpm_2(__uref, __mref, __csr + 0)			\
	switchcase_hpm_2(__uref, __mref, __csr + 2)
#define switchcase_hpm_8(__uref, __mref, __csr)			\
	switchcase_hpm_4(__uref, __mref, __csr + 0)			\
	switchcase_hpm_4(__uref, __mref, __csr + 4)
#define switchcase_hpm_16(__uref, __mref, __csr)			\
	switchcase_hpm_8(__uref, __mref, __csr + 0)			\
	switchcase_hpm_8(__uref, __mref, __csr + 8)

	switchcase_hpm(CSR_CYCLE, CSR_MCYCLE, CSR_HPMCOUNTER3)
	switchcase_hpm_4(CSR_CYCLE, CSR_MCYCLE, CSR_HPMCOUNTER4)
	switchcase_hpm_8(CSR_CYCLE, CSR_MCYCLE, CSR_HPMCOUNTER8)
	switchcase_hpm_16(CSR_CYCLE, CSR_MCYCLE, CSR_HPMCOUNTER16)

#if __riscv_xlen == 32
	switchcase_hpm(CSR_CYCLEH, CSR_MCYCLEH, CSR_HPMCOUNTER3H)
	switchcase_hpm_4(CSR_CYCLEH, CSR_MCYCLEH, CSR_HPMCOUNTER4H)
	switchcase_hpm_8(CSR_CYCLEH, CSR_MCYCLEH, CSR_HPMCOUNTER8H)
	switchcase_hpm_16(CSR_CYCLEH, CSR_MCYCLEH, CSR_HPMCOUNTER16H)
#endif

#undef switchcase_hpm_16
#undef switchcase_hpm_8
#undef switchcase_hpm_4
#undef switchcase_hpm_2
#undef switchcase_hpm

	default:
		ret = SBI_ENOTSUPP;
		break;
	};

	if (ret)
		sbi_dprintf("%s: hartid%d: invalid csr_num=0x%x\n",
			    __func__, current_hartid(), csr_num);

	return ret;
}

int sbi_emulate_csr_write(int csr_num, struct sbi_trap_regs *regs,
			  ulong csr_val)
{
	int ret = 0;
	ulong prev_mode = (regs->mstatus & MSTATUS_MPP) >> MSTATUS_MPP_SHIFT;
#if __riscv_xlen == 32
	bool virt = (regs->mstatusH & MSTATUSH_MPV) ? TRUE : FALSE;
#else
	bool virt = (regs->mstatus & MSTATUS_MPV) ? TRUE : FALSE;
#endif

	switch (csr_num) {
	case CSR_HTIMEDELTA:
		if (prev_mode == PRV_S && !virt)
			sbi_timer_set_delta(csr_val);
		else
			ret = SBI_ENOTSUPP;
		break;
#if __riscv_xlen == 32
	case CSR_HTIMEDELTAH:
		if (prev_mode == PRV_S && !virt)
			sbi_timer_set_delta_upper(csr_val);
		else
			ret = SBI_ENOTSUPP;
		break;
#endif
	default:
		ret = SBI_ENOTSUPP;
		break;
	};

	if (ret)
		sbi_dprintf("%s: hartid%d: invalid csr_num=0x%x\n",
			    __func__, current_hartid(), csr_num);

	return ret;
}
