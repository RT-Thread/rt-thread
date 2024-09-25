/*
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <sbi/riscv_encoding.h>
#include <sbi/riscv_io.h>
#include <sbi/sbi_console.h>
#include <sbi/sbi_const.h>
#include <sbi/sbi_hart.h>
#include <sbi/sbi_platform.h>
#include <sbi/sbi_math.h>
#include <sbi_utils/fdt/fdt_helper.h>
#include <sbi_utils/fdt/fdt_fixup.h>
#include <sbi_utils/irqchip/plic.h>
#include <sbi_utils/serial/uart8250.h>
#include <sbi_utils/sys/clint.h>
#include "platform.h"

#define UART_DEFAULT_BAUDRATE       115200
#define UART_CLK                    50000000
#define UART_ADDR                   0x91400000

static size_t plic_base_addr;
static size_t clint_base_addr;

static struct platform_uart_data uart = {
	UART_ADDR,
	UART_CLK,
	UART_DEFAULT_BAUDRATE,
};

static struct plic_data plic = {
	.addr = 0xF00000000,
	.num_src = 200,
};

static struct clint_data clint = {
	.addr = 0xF04000000, /* Updated at cold boot time */
	.first_hartid = 0,
	.hart_count = C908_HART_COUNT,
	.has_64bit_mmio = FALSE,
};

static int c908_early_init(bool cold_boot)
{
	void *fdt;
	struct platform_uart_data uart_data;
	struct plic_data plic_data;
	unsigned long clint_addr;
	int rc;

	if (!cold_boot)
		return 0;

	plic_base_addr = csr_read(CSR_PLIC_BASE);
	clint_base_addr = plic_base_addr + C908_PLIC_CLINT_OFFSET;

	fdt = sbi_scratch_thishart_arg1_ptr();

	rc = fdt_parse_uart8250(fdt, &uart_data, "snps,dw-apb-uart");
	if (!rc)
		uart = uart_data;

	rc = fdt_parse_plic(fdt, &plic_data, "riscv,plic0");
	if (!rc)
		plic = plic_data;

	rc = fdt_parse_compat_addr(fdt, &clint_addr, "riscv,clint0");
	if (!rc)
		clint.addr = clint_addr;

	return 0;
}

static int c908_pmp_region_info(u32 index, ulong *prot, ulong *addr, ulong *log2size)
{
	int ret = 0;

	switch (index) {
	case 0:
		*prot	  = PMP_R | PMP_W | PMP_X;
		*addr	  = 0x00000000;
		*log2size = log2roundup(0x80000000);
		break;
	case 1:
		*prot	  = PMP_R | PMP_W | PMP_X;
		*addr	  = 0x80200000;
		*log2size = log2roundup(0x200000);
		break;
	case 2:
		*prot	  = PMP_R | PMP_W;
		*addr	  = 0x80400000;
		*log2size = log2roundup(0x7fc00000);
		break;
	case 3:
		*prot	  = PMP_R | PMP_W;
		*addr	  = 0xf00000000;
		*log2size = log2roundup(0x10000000);
		break;
	default:
		ret = -1;
		break;
	};

	return ret;
}

static int c908_final_init(bool cold_boot)
{
	// void *fdt;
	unsigned long exceptions;
	u32 i;
	ulong prot, addr, log2size;

	if (!cold_boot)
		return 0;

	// fdt = sbi_scratch_thishart_arg1_ptr();
	// fdt_fixups(fdt);

	/* Delegate 0 ~ 7 exceptions to S-mode */
	exceptions = csr_read(CSR_MEDELEG);
	exceptions |= ((1U << CAUSE_MISALIGNED_FETCH) | (1U << CAUSE_FETCH_ACCESS) |
		(1U << CAUSE_ILLEGAL_INSTRUCTION) | (1U << CAUSE_BREAKPOINT) |
		(1U << CAUSE_MISALIGNED_LOAD) | (1U << CAUSE_LOAD_ACCESS) |
		(1U << CAUSE_MISALIGNED_STORE) | (1U << CAUSE_STORE_ACCESS));
	csr_write(CSR_MEDELEG, exceptions);

	csr_write(CSR_MIDELEG, 0x222);
	csr_write(CSR_MEDELEG, 0xb1ff);
	csr_write(CSR_MHCR, 0x11ff);
	csr_write(CSR_MCOR, 0x70013);
	csr_write(CSR_MCCR2, 0xe0410009);
	csr_write(CSR_MHINT, 0x16e30c);
	csr_write(0x7f3, 0x1);

	csr_write(0x7d9, csr_read(0x7d9) | 1);

	// enable vs externsion
	csr_write(CSR_MSTATUS, (csr_read(CSR_MSTATUS) & (~(3 << 9))) | (1 << 9));

	for (i = 0; i < 4; i++) {
		if (c908_pmp_region_info(i, &prot, &addr, &log2size))
			continue;
		pmp_set(i, prot, addr, log2size);
	}

	sbi_printf("pmpcfg0: %lx\r\n", csr_read(CSR_PMPCFG0));
	sbi_printf("pmpaddr0: %lx\r\n", csr_read(CSR_PMPADDR0));
	sbi_printf("pmpaddr1: %lx\r\n", csr_read(CSR_PMPADDR1));
	sbi_printf("pmpaddr2: %lx\r\n", csr_read(CSR_PMPADDR2));
	sbi_printf("pmpaddr3: %lx\r\n", csr_read(CSR_PMPADDR3));
	sbi_printf("pmpaddr4: %lx\r\n", csr_read(CSR_PMPADDR4));
	sbi_printf("pmpaddr5: %lx\r\n", csr_read(CSR_PMPADDR5));

	return 0;
}

static int c908_irqchip_init(bool cold_boot)
{
	int ret;

	if (cold_boot) {
		/* Delegate plic enable into S-mode */
		writel(C908_PLIC_DELEG_ENABLE, (void *)(plic_base_addr + C908_PLIC_DELEG_OFFSET));
		ret = plic_cold_irqchip_init(&plic);
		if (ret)
			return ret;
	}

	return 0;
}

static int c908_ipi_init(bool cold_boot)
{
	int rc;

	if (cold_boot) {
		rc = clint_cold_ipi_init(&clint);
		if (rc)
			return rc;
	}

	return clint_warm_ipi_init();
}

static int c908_timer_init(bool cold_boot)
{
	int ret;

	if (cold_boot) {
		ret = clint_cold_timer_init(&clint, NULL);
		if (ret)
			return ret;
	}

	return clint_warm_timer_init();
}

int c908_hart_start(u32 hartid, ulong saddr)
{
	csr_write(CSR_MRVBR, saddr);
	csr_write(CSR_MRMR, csr_read(CSR_MRMR) | (1 << hartid));

	return 0;
}

static int c908_console_init(void)
{
	return uart8250_init(UART_ADDR,
						UART_CLK,
						UART_DEFAULT_BAUDRATE,
						2,
						4);
}

const struct sbi_platform_operations platform_ops = {
	.early_init          = c908_early_init,
	.final_init          = c908_final_init,
	.irqchip_init        = c908_irqchip_init,
	.console_init        = c908_console_init,
	.ipi_init            = c908_ipi_init,
	.timer_init          = c908_timer_init,
};

const struct sbi_platform platform = {
	.opensbi_version     = OPENSBI_VERSION,
	.platform_version    = SBI_PLATFORM_VERSION(0x0, 0x01),
	.name                = "T-HEAD Xuantie c908",
	.features            = SBI_THEAD_FEATURES,
	.hart_count          = C908_HART_COUNT,
	.hart_stack_size     = SBI_PLATFORM_DEFAULT_HART_STACK_SIZE,
	.platform_ops_addr   = (unsigned long)&platform_ops
};
