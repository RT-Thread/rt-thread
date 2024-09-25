/*
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <sbi/riscv_asm.h>
#include "fdt_reset_thead.h"

/*
 * csrrs rd, csr, rs1
 * |31   20|19   15|14   12|11  7|6       0|
 *    csr     rs1     010     rd   1110011
 */
#define CSR_STUB	addi    x0, x0, 0

	.option norvc
	.align 3
	.global __fdt_reset_thead_csrr
__fdt_reset_thead_csrr:
	csrrs a0, 0, x0
	ret

	.align 3
	.global __thead_pre_start_warm
__thead_pre_start_warm:
	/*
	 * Clear L1 cache & BTB & BHT ...
	 */
	li	t1, 0x70013
	csrw	0x7c2, t1
	fence rw,rw

	lla	t1, custom_csr

	.global __reset_thead_csr_stub
__reset_thead_csr_stub:
.rept	MAX_CUSTOM_CSR
	REG_L	t2, 8(t1)
	CSR_STUB
	addi	t1, t1, 16
.endr
	/*
	 * Clear L1 cache & BTB & BHT ...
	 */
	li	t1, 0x70013
	csrw	0x7c2, t1
	fence rw,rw
	j _start_warm
