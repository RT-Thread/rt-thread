/*
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <libfdt.h>
#include <sbi/riscv_io.h>
#include <sbi/sbi_bitops.h>
#include <sbi/sbi_hart.h>
#include <sbi/sbi_scratch.h>
#include <sbi/sbi_system.h>
#include <sbi_utils/fdt/fdt_helper.h>
#include <sbi_utils/reset/fdt_reset.h>

#include "fdt_reset_thead.h"

struct custom_csr custom_csr[MAX_CUSTOM_CSR];

#define CSR_OPCODE 0x39073
static void clone_csrs(int cnt)
{
	unsigned long i;

	for (i = 0; i < cnt; i++) {
		/* Write csr BIT[31 - 20] to stub */
		__reset_thead_csr_stub[3*i + 1] =
				CSR_OPCODE | (custom_csr[i].index << 20);

		/* Mask csr BIT[31 - 20] */
		*(u32 *)&__fdt_reset_thead_csrr &= BIT(20) - 1;
		smp_mb();

		/* Write csr BIT[31 - 20] to __fdt_reset_thead_csrr */
		*(u32 *)&__fdt_reset_thead_csrr |= custom_csr[i].index << 20;
		smp_mb();

		RISCV_FENCE_I;

		custom_csr[i].value = __fdt_reset_thead_csrr();
	}
}

static int thead_system_reset_check(u32 type, u32 reason)
{
	return 1;
}

static void thead_system_reset(u32 type, u32 reason)
{
	ebreak();
}

static struct sbi_system_reset_device thead_reset = {
	.name = "thead_reset",
	.system_reset_check = thead_system_reset_check,
	.system_reset = thead_system_reset
};

extern void __thead_pre_start_warm(void);
static int thead_reset_init(void *fdt, int nodeoff,
				 const struct fdt_match *match)
{
	void *p;
	const fdt64_t *val;
	const fdt32_t *val_w;
	int len, i, cnt = 0;
	u32 t, tmp = 0;

	/* Prepare clone csrs */
	val_w = fdt_getprop(fdt, nodeoff, "csr-copy", &len);
	if (len > 0 && val_w) {
		cnt = len / sizeof(fdt32_t);

		if (cnt > MAX_CUSTOM_CSR)
			sbi_hart_hang();

		for (i = 0; i < cnt; i++) {
			custom_csr[i].index = fdt32_to_cpu(val_w[i]);
		}
	}

	if (cnt)
		clone_csrs(cnt);

	/* Delegate plic enable regs for S-mode */
	val = fdt_getprop(fdt, nodeoff, "plic-delegate", &len);
	if (len > 0 && val) {
		p = (void *)(ulong)fdt64_to_cpu(*val);
		writel(BIT(0), p);
	}

	/* Old reset method for secondary harts */
	if (fdt_getprop(fdt, nodeoff, "using-csr-reset", &len)) {
		csr_write(0x7c7, (ulong)&__thead_pre_start_warm);
		csr_write(0x7c6, -1);
	}

	/* Custom reset method for secondary harts */
	val = fdt_getprop(fdt, nodeoff, "entry-reg", &len);
	if (len > 0 && val) {
		p = (void *)(ulong)fdt64_to_cpu(*val);

		val_w = fdt_getprop(fdt, nodeoff, "entry-cnt", &len);
		if (len > 0 && val_w) {
			tmp = fdt32_to_cpu(*val_w);

			for (i = 0; i < tmp; i++) {
				t = (ulong)&__thead_pre_start_warm;
				writel(t, p + (8 * i));
				t = (u64)(ulong)&__thead_pre_start_warm >> 32;
				writel(t, p + (8 * i) + 4);
			}
		}

		val = fdt_getprop(fdt, nodeoff, "control-reg", &len);
		if (len > 0 && val) {
			p = (void *)(ulong)fdt64_to_cpu(*val);

			val_w = fdt_getprop(fdt, nodeoff, "control-val", &len);
			if (len > 0 && val_w) {
				tmp = fdt32_to_cpu(*val_w);
				tmp |= readl(p);
				writel(tmp, p);
			}
		}
	}

	sbi_system_reset_set_device(&thead_reset);

	return 0;
}

static const struct fdt_match thead_reset_match[] = {
	{ .compatible = "thead,reset-sample" },
	{ },
};

struct fdt_reset fdt_reset_thead = {
	.match_table = thead_reset_match,
	.init = thead_reset_init
};
