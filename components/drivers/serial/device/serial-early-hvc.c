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

#include <hypercall.h>

static void hvc_early_console_putchar(void *data, char c)
{
    rt_hv_console(c);
}

static rt_err_t hvc_early_setup(struct rt_fdt_earlycon *con, const char *options)
{
    rt_err_t err;
    rt_uint32_t version;

    if ((err = rt_hv_version(&version)))
    {
        return err;
    }

    con->console_putc = hvc_early_console_putchar;

    return err;
}
RT_FDT_EARLYCON_EXPORT(hvc, "hvc", "vmrt-thread,hvc-console", hvc_early_setup);
