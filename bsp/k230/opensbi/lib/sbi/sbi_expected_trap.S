/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#include <sbi/riscv_asm.h>
#include <sbi/sbi_trap.h>

	/*
	 * We assume that faulting instruction is is 4-byte long and blindly
	 * increment SEPC by 4.
	 *
	 * The trap info will be saved as follows:
	 * A3 <- pointer struct sbi_trap_info
	 * A4 <- temporary
	 */

	.align 3
	.global __sbi_expected_trap
__sbi_expected_trap:
	/* Without H-extension so, MTVAL2 and MTINST CSRs not available */
	csrr	a4, CSR_MEPC
	REG_S	a4, SBI_TRAP_INFO_OFFSET(epc)(a3)
	csrr	a4, CSR_MCAUSE
	REG_S	a4, SBI_TRAP_INFO_OFFSET(cause)(a3)
	csrr	a4, CSR_MTVAL
	REG_S	a4, SBI_TRAP_INFO_OFFSET(tval)(a3)
	REG_S	zero, SBI_TRAP_INFO_OFFSET(tval2)(a3)
	REG_S	zero, SBI_TRAP_INFO_OFFSET(tinst)(a3)
	csrr	a4, CSR_MEPC
	addi	a4, a4, 4
	csrw	CSR_MEPC, a4
	mret

	.align 3
	.global __sbi_expected_trap_hext
__sbi_expected_trap_hext:
	/* With H-extension so, MTVAL2 and MTINST CSRs available */
	csrr	a4, CSR_MEPC
	REG_S	a4, SBI_TRAP_INFO_OFFSET(epc)(a3)
	csrr	a4, CSR_MCAUSE
	REG_S	a4, SBI_TRAP_INFO_OFFSET(cause)(a3)
	csrr	a4, CSR_MTVAL
	REG_S	a4, SBI_TRAP_INFO_OFFSET(tval)(a3)
	csrr	a4, CSR_MTVAL2
	REG_S	a4, SBI_TRAP_INFO_OFFSET(tval2)(a3)
	csrr	a4, CSR_MTINST
	REG_S	a4, SBI_TRAP_INFO_OFFSET(tinst)(a3)
	csrr	a4, CSR_MEPC
	addi	a4, a4, 4
	csrw	CSR_MEPC, a4
	mret
