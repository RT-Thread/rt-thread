/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Vijai Kumar K <vijai@behindbytes.com>
 *
 */

#include <sbi_utils/fdt/fdt_helper.h>
#include <sbi_utils/serial/fdt_serial.h>
#include <sbi_utils/serial/shakti-uart.h>

static int serial_shakti_init(void *fdt, int nodeoff,
				const struct fdt_match *match)
{
	int rc;
	struct platform_uart_data uart;

	rc = fdt_parse_shakti_uart_node(fdt, nodeoff, &uart);
	if (rc)
		return rc;

	return shakti_uart_init(uart.addr, uart.freq, uart.baud);
}

static const struct fdt_match serial_shakti_match[] = {
	{ .compatible = "shakti,uart0" },
	{ },
};

struct fdt_serial fdt_serial_shakti = {
	.match_table = serial_shakti_match,
	.init = serial_shakti_init
};
