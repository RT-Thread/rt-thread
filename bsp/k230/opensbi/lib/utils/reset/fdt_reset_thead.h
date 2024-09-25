/*
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef __FDT_RESET_THEAD_H__
#define __FDT_RESET_THEAD_H__

#define MAX_CUSTOM_CSR	32

#ifndef __ASSEMBLER__
struct custom_csr {
	unsigned long index;
	unsigned long value;
};

u64  __fdt_reset_thead_csrr(void);

extern struct custom_csr custom_csr[MAX_CUSTOM_CSR];
extern u32 __reset_thead_csr_stub[];

#endif /* __ASSEMBLER__ */

#endif /* __FDT_RESET_THEAD_H__ */
