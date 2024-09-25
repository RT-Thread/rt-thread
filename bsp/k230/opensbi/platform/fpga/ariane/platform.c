/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2019 FORTH-ICS/CARV
 *				Panagiotis Peristerakis <perister@ics.forth.gr>
 */

#include <sbi/riscv_asm.h>
#include <sbi/riscv_encoding.h>
#include <sbi/riscv_io.h>
#include <sbi/sbi_console.h>
#include <sbi/sbi_const.h>
#include <sbi/sbi_hart.h>
#include <sbi/sbi_platform.h>
#include <sbi_utils/fdt/fdt_fixup.h>
#include <sbi_utils/irqchip/plic.h>
#include <sbi_utils/serial/uart8250.h>
#include <sbi_utils/sys/clint.h>

#define ARIANE_UART_ADDR			0x10000000
#define ARIANE_UART_FREQ			50000000
#define ARIANE_UART_BAUDRATE			115200
#define ARIANE_UART_REG_SHIFT			2
#define ARIANE_UART_REG_WIDTH			4
#define ARIANE_PLIC_ADDR			0xc000000
#define ARIANE_PLIC_NUM_SOURCES			3
#define ARIANE_HART_COUNT			1
#define ARIANE_CLINT_ADDR			0x2000000

static struct plic_data plic = {
	.addr = ARIANE_PLIC_ADDR,
	.num_src = ARIANE_PLIC_NUM_SOURCES,
};

static struct clint_data clint = {
	.addr = ARIANE_CLINT_ADDR,
	.first_hartid = 0,
	.hart_count = ARIANE_HART_COUNT,
	.has_64bit_mmio = TRUE,
};

/*
 * Ariane platform early initialization.
 */
static int ariane_early_init(bool cold_boot)
{
	/* For now nothing to do. */
	return 0;
}

/*
 * Ariane platform final initialization.
 */
static int ariane_final_init(bool cold_boot)
{
	void *fdt;

	if (!cold_boot)
		return 0;

	fdt = sbi_scratch_thishart_arg1_ptr();
	fdt_fixups(fdt);

	return 0;
}

/*
 * Initialize the ariane console.
 */
static int ariane_console_init(void)
{
	return uart8250_init(ARIANE_UART_ADDR,
			     ARIANE_UART_FREQ,
			     ARIANE_UART_BAUDRATE,
			     ARIANE_UART_REG_SHIFT,
			     ARIANE_UART_REG_WIDTH);
}

static int plic_ariane_warm_irqchip_init(int m_cntx_id, int s_cntx_id)
{
	size_t i, ie_words = ARIANE_PLIC_NUM_SOURCES / 32 + 1;

	/* By default, enable all IRQs for M-mode of target HART */
	if (m_cntx_id > -1) {
		for (i = 0; i < ie_words; i++)
			plic_set_ie(&plic, m_cntx_id, i, 1);
	}
	/* Enable all IRQs for S-mode of target HART */
	if (s_cntx_id > -1) {
		for (i = 0; i < ie_words; i++)
			plic_set_ie(&plic, s_cntx_id, i, 1);
	}
	/* By default, enable M-mode threshold */
	if (m_cntx_id > -1)
		plic_set_thresh(&plic, m_cntx_id, 1);
	/* By default, disable S-mode threshold */
	if (s_cntx_id > -1)
		plic_set_thresh(&plic, s_cntx_id, 0);

	return 0;
}

/*
 * Initialize the ariane interrupt controller for current HART.
 */
static int ariane_irqchip_init(bool cold_boot)
{
	u32 hartid = current_hartid();
	int ret;

	if (cold_boot) {
		ret = plic_cold_irqchip_init(&plic);
		if (ret)
			return ret;
	}
	return plic_ariane_warm_irqchip_init(2 * hartid, 2 * hartid + 1);
}

/*
 * Initialize IPI for current HART.
 */
static int ariane_ipi_init(bool cold_boot)
{
	int ret;

	if (cold_boot) {
		ret = clint_cold_ipi_init(&clint);
		if (ret)
			return ret;
	}

	return clint_warm_ipi_init();
}

/*
 * Initialize ariane timer for current HART.
 */
static int ariane_timer_init(bool cold_boot)
{
	int ret;

	if (cold_boot) {
		ret = clint_cold_timer_init(&clint, NULL);
		if (ret)
			return ret;
	}

	return clint_warm_timer_init();
}

/*
 * Platform descriptor.
 */
const struct sbi_platform_operations platform_ops = {
	.early_init = ariane_early_init,
	.final_init = ariane_final_init,
	.console_init = ariane_console_init,
	.irqchip_init = ariane_irqchip_init,
	.ipi_init = ariane_ipi_init,
	.timer_init = ariane_timer_init,
};

const struct sbi_platform platform = {
	.opensbi_version = OPENSBI_VERSION,
	.platform_version = SBI_PLATFORM_VERSION(0x0, 0x01),
	.name = "ARIANE RISC-V",
	.features = SBI_PLATFORM_DEFAULT_FEATURES,
	.hart_count = ARIANE_HART_COUNT,
	.hart_stack_size = SBI_PLATFORM_DEFAULT_HART_STACK_SIZE,
	.platform_ops_addr = (unsigned long)&platform_ops
};
