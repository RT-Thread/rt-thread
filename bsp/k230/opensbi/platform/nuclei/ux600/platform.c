/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) Nuclei Corporation or its affiliates.
 *
 * Authors:
 *   lujun <lujun@nucleisys.com>
 *   hqfang <578567190@qq.com>
 */

#include <libfdt.h>
#include <sbi/riscv_asm.h>
#include <sbi/riscv_io.h>
#include <sbi/riscv_encoding.h>
#include <sbi/sbi_console.h>
#include <sbi/sbi_const.h>
#include <sbi/sbi_platform.h>
#include <sbi/sbi_system.h>
#include <sbi_utils/fdt/fdt_fixup.h>
#include <sbi_utils/irqchip/plic.h>
#include <sbi_utils/serial/sifive-uart.h>
#include <sbi_utils/sys/clint.h>

/* clang-format off */

#define UX600_HART_COUNT		1
#define UX600_TIMER_FREQ		32768

/* Nuclei timer base address */
#define UX600_NUCLEI_TIMER_ADDR		0x2000000
#define UX600_NUCLEI_TIMER_MSFTRST_OFS	0xFF0
#define UX600_NUCLEI_TIMER_MSFTRST_KEY	0x80000A5F
/* The clint compatiable timer offset is 0x1000 against nuclei timer */
#define UX600_CLINT_TIMER_ADDR		(UX600_NUCLEI_TIMER_ADDR + 0x1000)

#define UX600_PLIC_ADDR			0x8000000
#define UX600_PLIC_NUM_SOURCES		0x35
#define UX600_PLIC_NUM_PRIORITIES	7

#define UX600_UART0_ADDR		0x10013000
#define UX600_UART1_ADDR		0x10023000

#define UX600_DEBUG_UART		UX600_UART0_ADDR

#ifndef UX600_UART_BAUDRATE
#define UX600_UART_BAUDRATE		57600
#endif

#define UX600_GPIO_ADDR			0x10012000
#define UX600_GPIO_IOF_EN_OFS		0x38
#define UX600_GPIO_IOF_SEL_OFS		0x3C
#define UX600_GPIO_IOF_UART0_MASK	0x00030000

#define UX600_TIMER_VALUE()		readl((void *)UX600_NUCLEI_TIMER_ADDR)

/* clang-format on */
static u32 ux600_clk_freq = 8000000;

static struct plic_data plic = {
	.addr = UX600_PLIC_ADDR,
	.num_src = UX600_PLIC_NUM_SOURCES,
};

static struct clint_data clint = {
	.addr = UX600_CLINT_TIMER_ADDR,
	.first_hartid = 0,
	.hart_count = UX600_HART_COUNT,
	.has_64bit_mmio = TRUE,
};
static u32 measure_cpu_freq(u32 n)
{
	u32 start_mtime, delta_mtime;
	u32 mtime_freq = UX600_TIMER_FREQ;
	u32 tmp = (u32)UX600_TIMER_VALUE();
	u32 start_mcycle, delta_mcycle, freq;

	/* Don't start measuring until we see an mtime tick */
	do {
		start_mtime = (u32)UX600_TIMER_VALUE();
	} while (start_mtime == tmp);

	start_mcycle = csr_read(mcycle);

	do {
		delta_mtime = (u32)UX600_TIMER_VALUE() - start_mtime;
	} while (delta_mtime < n);

	delta_mcycle = csr_read(mcycle) - start_mcycle;

	freq = (delta_mcycle / delta_mtime) * mtime_freq
		+ ((delta_mcycle % delta_mtime) * mtime_freq) / delta_mtime;

	return freq;
}

static u32 ux600_get_clk_freq(void)
{
	u32 cpu_freq;

	/* warm up */
	measure_cpu_freq(1);
	/* measure for real */
	cpu_freq = measure_cpu_freq(100);

	return cpu_freq;
}

static int ux600_system_reset_check(u32 type, u32 reason)
{
	return 1;
}

static void ux600_system_reset(u32 type, u32 reason)
{
	/* Reset system using MSFTRST register in Nuclei Timer. */
	writel(UX600_NUCLEI_TIMER_MSFTRST_KEY, (void *)(UX600_NUCLEI_TIMER_ADDR
					+ UX600_NUCLEI_TIMER_MSFTRST_OFS));
	while(1);
}

static struct sbi_system_reset_device ux600_reset = {
	.name = "nuclei_ux600_reset",
	.system_reset_check = ux600_system_reset_check,
	.system_reset = ux600_system_reset
};

static int ux600_early_init(bool cold_boot)
{
	u32 regval;

	if (cold_boot)
		sbi_system_reset_set_device(&ux600_reset);

	/* Measure CPU Frequency using Timer */
	ux600_clk_freq = ux600_get_clk_freq();

	/* Init GPIO UART pinmux */
	regval = readl((void *)(UX600_GPIO_ADDR + UX600_GPIO_IOF_SEL_OFS)) &
		 ~UX600_GPIO_IOF_UART0_MASK;
	writel(regval, (void *)(UX600_GPIO_ADDR + UX600_GPIO_IOF_SEL_OFS));
	regval = readl((void *)(UX600_GPIO_ADDR + UX600_GPIO_IOF_EN_OFS)) |
		UX600_GPIO_IOF_UART0_MASK;
	writel(regval, (void *)(UX600_GPIO_ADDR + UX600_GPIO_IOF_EN_OFS));
	return 0;
}

static void ux600_modify_dt(void *fdt)
{
	fdt_fixups(fdt);
}

static int ux600_final_init(bool cold_boot)
{
	void *fdt;

	if (!cold_boot)
		return 0;

	fdt = sbi_scratch_thishart_arg1_ptr();
	ux600_modify_dt(fdt);

	return 0;
}

static int ux600_console_init(void)
{
	return sifive_uart_init(UX600_DEBUG_UART, ux600_clk_freq,
				UX600_UART_BAUDRATE);
}

static int ux600_irqchip_init(bool cold_boot)
{
	int rc;
	u32 hartid = current_hartid();

	if (cold_boot) {
		rc = plic_cold_irqchip_init(&plic);
		if (rc)
			return rc;
	}

	return plic_warm_irqchip_init(&plic, (hartid) ? (2 * hartid - 1) : 0,
				      (hartid) ? (2 * hartid) : -1);
}

static int ux600_ipi_init(bool cold_boot)
{
	int rc;

	if (cold_boot) {
		rc = clint_cold_ipi_init(&clint);
		if (rc)
			return rc;
	}

	return clint_warm_ipi_init();
}

static int ux600_timer_init(bool cold_boot)
{
	int rc;

	if (cold_boot) {
		rc = clint_cold_timer_init(&clint, NULL);
		if (rc)
			return rc;
	}

	return clint_warm_timer_init();
}

const struct sbi_platform_operations platform_ops = {
	.early_init		= ux600_early_init,
	.final_init		= ux600_final_init,
	.console_init		= ux600_console_init,
	.irqchip_init		= ux600_irqchip_init,
	.ipi_init		= ux600_ipi_init,
	.timer_init		= ux600_timer_init,
};

const struct sbi_platform platform = {
	.opensbi_version	= OPENSBI_VERSION,
	.platform_version	= SBI_PLATFORM_VERSION(0x0U, 0x01U),
	.name			= "Nuclei UX600",
	.features		= SBI_PLATFORM_DEFAULT_FEATURES,
	.hart_count		= UX600_HART_COUNT,
	.hart_stack_size	= SBI_PLATFORM_DEFAULT_HART_STACK_SIZE,
	.platform_ops_addr	= (unsigned long)&platform_ops
};
