/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Andes Technology Corporation
 *
 * Authors:
 *   Nylon Chen <nylon7@andestech.com>
 */

#include <sbi/riscv_asm.h>
#include <sbi/riscv_io.h>
#include <sbi/sbi_types.h>
#include "platform.h"

uintptr_t mcall_set_mcache_ctl(unsigned long input)
{
	csr_clear(CSR_MCACHECTL, V5_MCACHE_CTL_MASK);
	csr_write(CSR_MCACHECTL, input);
	return 0;
}

uintptr_t mcall_set_mmisc_ctl(unsigned long input)
{
	csr_clear(CSR_MMISCCTL, V5_MMISC_CTL_MASK);
	csr_write(CSR_MMISCCTL, input);
	return 0;
}

uintptr_t mcall_icache_op(unsigned int enable)
{
	if (enable) {
		csr_set(CSR_MCACHECTL, V5_MCACHE_CTL_IC_EN);
	} else {
		csr_clear(CSR_MCACHECTL, V5_MCACHE_CTL_IC_EN);
		asm volatile("fence.i\n\t");
	}
	return 0;
}

uintptr_t mcall_dcache_op(unsigned int enable)
{
	if (enable) {
		csr_set(CSR_MCACHECTL, V5_MCACHE_CTL_DC_EN);
	} else {
		csr_clear(CSR_MCACHECTL, V5_MCACHE_CTL_DC_EN);
		csr_write(CSR_MCCTLCOMMAND, V5_UCCTL_L1D_WBINVAL_ALL);
	}
	return 0;
}

uintptr_t mcall_l1_cache_i_prefetch_op(unsigned long enable)
{
	if (enable) {
		csr_set(CSR_MCACHECTL, V5_MCACHE_CTL_L1I_PREFETCH_EN);
	} else {
		csr_clear(CSR_MCACHECTL, V5_MCACHE_CTL_L1I_PREFETCH_EN);
	}
	return 0;
}

uintptr_t mcall_l1_cache_d_prefetch_op(unsigned long enable)
{
	if (enable) {
		csr_set(CSR_MCACHECTL, V5_MCACHE_CTL_L1D_PREFETCH_EN);
	} else {
		csr_clear(CSR_MCACHECTL, V5_MCACHE_CTL_L1D_PREFETCH_EN);
	}
	return 0;
}

uintptr_t mcall_non_blocking_load_store(unsigned long enable)
{
	if (enable) {
		csr_set(CSR_MCACHECTL, V5_MMISC_CTL_NON_BLOCKING_EN);
	} else {
		csr_clear(CSR_MCACHECTL, V5_MMISC_CTL_NON_BLOCKING_EN);
	}
	return 0;
}

uintptr_t mcall_write_around(unsigned long enable)
{
	if (enable) {
		csr_set(CSR_MCACHECTL, V5_MCACHE_CTL_DC_WAROUND_1_EN);
	} else {
		csr_clear(CSR_MCACHECTL, V5_MCACHE_CTL_DC_WAROUND_1_EN);
	}
	return 0;
}
