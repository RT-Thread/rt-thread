/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#include <sbi_utils/fdt/fdt_helper.h>
#include <sbi_utils/serial/fdt_serial.h>
#include <sbi_utils/serial/sifive-uart.h>

static int serial_sifive_init(void *fdt, int nodeoff,
				const struct fdt_match *match)
{
	int rc;
	struct platform_uart_data uart;

	rc = fdt_parse_sifive_uart_node(fdt, nodeoff, &uart);
	if (rc)
		return rc;

	return sifive_uart_init(uart.addr, uart.freq, uart.baud);
}

static const struct fdt_match serial_sifive_match[] = {
	{ .compatible = "sifive,fu540-c000-uart" },
	{ .compatible = "sifive,uart0" },
	{ },
};

struct fdt_serial fdt_serial_sifive = {
	.match_table = serial_sifive_match,
	.init = serial_sifive_init
};
