/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rtthread.h>

#include <csr.h>

static int spacemit_sbi_ipi_init(void)
{
	csr_set(CSR_IE, IE_SIE);

	return 0;
}
INIT_BOARD_EXPORT(spacemit_sbi_ipi_init);

static int spacemit_sbi_ipi_secondary_cpu_init(void)
{
    return spacemit_sbi_ipi_init();
}
INIT_SECONDARY_CPU_EXPORT(spacemit_sbi_ipi_secondary_cpu_init);
