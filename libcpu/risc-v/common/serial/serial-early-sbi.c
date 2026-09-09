/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-30     GuEe-GUI     first version
 */

#include <rtdevice.h>

#include <sbi.h>

static void sbi_early_console_putchar(void *data, char c)
{
    sbi_console_putchar(c);
}

static rt_err_t sbi_early_setup(struct rt_fdt_earlycon *con, const char *options)
{
    con->console_putc = sbi_early_console_putchar;

    return RT_EOK;
}
RT_FDT_EARLYCON_EXPORT(sbi, "sbi", "riscv,sbi-console", sbi_early_setup);
