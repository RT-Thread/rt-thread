/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Atish Patra <atish.patra@wdc.com>
 */

#ifndef __SBI_CSR_DETECT__H
#define __SBI_CSR_DETECT__H

#include <sbi/riscv_encoding.h>
#include <sbi/sbi_hart.h>
#include <sbi/sbi_trap.h>

#define csr_read_allowed(csr_num, trap)					\
	({								\
	register ulong tinfo asm("a3") = (ulong)trap;			\
	register ulong ttmp asm("a4");					\
	register ulong mtvec = sbi_hart_expected_trap_addr();		\
	register ulong ret = 0;						\
	((struct sbi_trap_info *)(trap))->cause = 0;			\
	asm volatile(							\
		"add %[ttmp], %[tinfo], zero\n"				\
		"csrrw %[mtvec], " STR(CSR_MTVEC) ", %[mtvec]\n"	\
		"csrr %[ret], %[csr]\n"					\
		"csrw " STR(CSR_MTVEC) ", %[mtvec]"			\
	    : [mtvec] "+&r"(mtvec), [tinfo] "+&r"(tinfo),		\
	      [ttmp] "+&r"(ttmp), [ret] "=&r" (ret)			\
	    : [csr] "i" (csr_num)					\
	    : "memory");						\
	ret;								\
	})								\

#define csr_write_allowed(csr_num, trap, value)				\
	({								\
	register ulong tinfo asm("a3") = (ulong)trap;			\
	register ulong ttmp asm("a4");					\
	register ulong mtvec = sbi_hart_expected_trap_addr();		\
	((struct sbi_trap_info *)(trap))->cause = 0;			\
	asm volatile(							\
		"add %[ttmp], %[tinfo], zero\n"				\
		"csrrw %[mtvec], " STR(CSR_MTVEC) ", %[mtvec]\n"	\
		"csrw %[csr], %[val]\n"					\
		"csrw " STR(CSR_MTVEC) ", %[mtvec]"			\
	    : [mtvec] "+&r"(mtvec),					\
	      [tinfo] "+&r"(tinfo), [ttmp] "+&r"(ttmp)			\
	    : [csr] "i" (csr_num), [val] "r" (value)			\
	    : "memory");						\
	})								\

#endif
