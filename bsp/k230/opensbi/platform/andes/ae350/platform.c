/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Andes Technology Corporation
 *
 * Authors:
 *   Zong Li <zong@andestech.com>
 *   Nylon Chen <nylon7@andestech.com>
 */

#include <sbi/riscv_asm.h>
#include <sbi/riscv_encoding.h>
#include <sbi/sbi_console.h>
#include <sbi/sbi_const.h>
#include <sbi/sbi_ipi.h>
#include <sbi/sbi_platform.h>
#include <sbi/sbi_trap.h>
#include <sbi_utils/fdt/fdt_fixup.h>
#include <sbi_utils/irqchip/plic.h>
#include <sbi_utils/serial/uart8250.h>
#include "platform.h"
#include "plicsw.h"
#include "plmt.h"
#include "cache.h"

static struct plic_data plic = {
	.addr = AE350_PLIC_ADDR,
	.num_src = AE350_PLIC_NUM_SOURCES,
};

/* Platform final initialization. */
static int ae350_final_init(bool cold_boot)
{
	void *fdt;

	/* enable L1 cache */
	uintptr_t mcache_ctl_val = csr_read(CSR_MCACHECTL);

	if (!(mcache_ctl_val & V5_MCACHE_CTL_IC_EN))
		mcache_ctl_val |= V5_MCACHE_CTL_IC_EN;
	if (!(mcache_ctl_val & V5_MCACHE_CTL_DC_EN))
		mcache_ctl_val |= V5_MCACHE_CTL_DC_EN;
	if (!(mcache_ctl_val & V5_MCACHE_CTL_CCTL_SUEN))
		mcache_ctl_val |= V5_MCACHE_CTL_CCTL_SUEN;
	csr_write(CSR_MCACHECTL, mcache_ctl_val);

	/* enable L2 cache */
	uint32_t *l2c_ctl_base = (void *)AE350_L2C_ADDR + V5_L2C_CTL_OFFSET;
	uint32_t l2c_ctl_val = *l2c_ctl_base;

	if (!(l2c_ctl_val & V5_L2C_CTL_ENABLE_MASK))
		l2c_ctl_val |= V5_L2C_CTL_ENABLE_MASK;
	*l2c_ctl_base = l2c_ctl_val;

	if (!cold_boot)
		return 0;

	fdt = sbi_scratch_thishart_arg1_ptr();
	fdt_fixups(fdt);

	return 0;
}

/* Initialize the platform console. */
static int ae350_console_init(void)
{
	return uart8250_init(AE350_UART_ADDR,
			     AE350_UART_FREQUENCY,
			     AE350_UART_BAUDRATE,
			     AE350_UART_REG_SHIFT,
			     AE350_UART_REG_WIDTH);
}

/* Initialize the platform interrupt controller for current HART. */
static int ae350_irqchip_init(bool cold_boot)
{
	u32 hartid = current_hartid();
	int ret;

	if (cold_boot) {
		ret = plic_cold_irqchip_init(&plic);
		if (ret)
			return ret;
	}

	return plic_warm_irqchip_init(&plic, 2 * hartid, 2 * hartid + 1);
}

static struct sbi_ipi_device plicsw_ipi = {
	.name = "ae350_plicsw",
	.ipi_send = plicsw_ipi_send,
	.ipi_clear = plicsw_ipi_clear
};

/* Initialize IPI for current HART. */
static int ae350_ipi_init(bool cold_boot)
{
	int ret;

	if (cold_boot) {
		ret = plicsw_cold_ipi_init(AE350_PLICSW_ADDR,
					   AE350_HART_COUNT);
		if (ret)
			return ret;

		sbi_ipi_set_device(&plicsw_ipi);
	}

	return plicsw_warm_ipi_init();
}

/* Initialize platform timer for current HART. */
static int ae350_timer_init(bool cold_boot)
{
	int ret;

	if (cold_boot) {
		ret = plmt_cold_timer_init(AE350_PLMT_ADDR,
					   AE350_HART_COUNT);
		if (ret)
			return ret;
	}

	return plmt_warm_timer_init();
}

/* Vendor-Specific SBI handler */
static int ae350_vendor_ext_provider(long extid, long funcid,
	const struct sbi_trap_regs *regs, unsigned long *out_value,
	struct sbi_trap_info *out_trap)
{
	int ret = 0;
	switch (funcid) {
	case SBI_EXT_ANDES_GET_MCACHE_CTL_STATUS:
		*out_value = csr_read(CSR_MCACHECTL);
		break;
	case SBI_EXT_ANDES_GET_MMISC_CTL_STATUS:
		*out_value = csr_read(CSR_MMISCCTL);
		break;
	case SBI_EXT_ANDES_SET_MCACHE_CTL:
		ret = mcall_set_mcache_ctl(regs->a0);
		break;
	case SBI_EXT_ANDES_SET_MMISC_CTL:
		ret = mcall_set_mmisc_ctl(regs->a0);
		break;
	case SBI_EXT_ANDES_ICACHE_OP:
		ret = mcall_icache_op(regs->a0);
		break;
	case SBI_EXT_ANDES_DCACHE_OP:
		ret = mcall_dcache_op(regs->a0);
		break;
	case SBI_EXT_ANDES_L1CACHE_I_PREFETCH:
		ret = mcall_l1_cache_i_prefetch_op(regs->a0);
		break;
	case SBI_EXT_ANDES_L1CACHE_D_PREFETCH:
		ret = mcall_l1_cache_d_prefetch_op(regs->a0);
		break;
	case SBI_EXT_ANDES_NON_BLOCKING_LOAD_STORE:
		ret = mcall_non_blocking_load_store(regs->a0);
		break;
	case SBI_EXT_ANDES_WRITE_AROUND:
		ret = mcall_write_around(regs->a0);
		break;
	default:
		sbi_printf("Unsupported vendor sbi call : %ld\n", funcid);
		asm volatile("ebreak");
	}
	return ret;
}

/* Platform descriptor. */
const struct sbi_platform_operations platform_ops = {
	.final_init = ae350_final_init,

	.console_init = ae350_console_init,

	.irqchip_init = ae350_irqchip_init,

	.ipi_init     = ae350_ipi_init,

	.timer_init	   = ae350_timer_init,

	.vendor_ext_provider = ae350_vendor_ext_provider
};

const struct sbi_platform platform = {
	.opensbi_version = OPENSBI_VERSION,
	.platform_version = SBI_PLATFORM_VERSION(0x0, 0x01),
	.name = "Andes AE350",
	.features = SBI_PLATFORM_DEFAULT_FEATURES,
	.hart_count = AE350_HART_COUNT,
	.hart_stack_size = SBI_PLATFORM_DEFAULT_HART_STACK_SIZE,
	.platform_ops_addr = (unsigned long)&platform_ops
};
