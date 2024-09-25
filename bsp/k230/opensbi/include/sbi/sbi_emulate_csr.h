/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SBI_EMULATE_CSR_H__
#define __SBI_EMULATE_CSR_H__

#include <sbi/sbi_types.h>

struct sbi_trap_regs;

int sbi_emulate_csr_read(int csr_num, struct sbi_trap_regs *regs,
			 ulong *csr_val);

int sbi_emulate_csr_write(int csr_num, struct sbi_trap_regs *regs,
			  ulong csr_val);

#endif
