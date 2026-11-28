/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Minimal FDT parse for Avaota F2 UART0 (milestone-1 DT drivers).
 * Uses libfdt only; full RT_USING_OFW is not enabled yet.
 */

#include <rthw.h>
#include <rtthread.h>
#include <string.h>

#include <libfdt.h>

#include "board.h"
#include "drv_fdt.h"

extern const unsigned char rt_hw_builtin_fdt[];
extern const unsigned char rt_hw_builtin_fdt_end[];

static const void *fdt_blob(void)
{
    return rt_hw_builtin_fdt;
}

static int fdt_blob_size(void)
{
    return (int)(rt_hw_builtin_fdt_end - rt_hw_builtin_fdt);
}

static uint32_t prop_u32(const void *fdt, int node, const char *name, uint32_t def)
{
    int len = 0;
    const fdt32_t *p = fdt_getprop(fdt, node, name, &len);

    if (!p || len < 4)
    {
        return def;
    }
    return fdt32_to_cpu(p[0]);
}

static int prop_u32_pair(const void *fdt, int node, const char *name, uint32_t *a, uint32_t *b)
{
    int len = 0;
    const fdt32_t *p = fdt_getprop(fdt, node, name, &len);

    if (!p || len < 8)
    {
        return -1;
    }
    *a = fdt32_to_cpu(p[0]);
    *b = fdt32_to_cpu(p[1]);
    return 0;
}

int rt_hw_fdt_load_uart(struct v861_uart_fdt *out)
{
    const void *fdt;
    int root;
    int chosen;
    int uart;
    int len;
    const char *stdout_path;
    const char *compat;
    const fdt32_t *pins;
    int i;

    memset(out, 0, sizeof(*out));
    fdt = fdt_blob();
    if (fdt_check_header(fdt) != 0)
    {
        return -1;
    }

    root = fdt_path_offset(fdt, "/");
    compat = fdt_getprop(fdt, root, "compatible", &len);
    if (compat && len > 0)
    {
        rt_strncpy(out->compatible, compat, sizeof(out->compatible) - 1);
    }

    chosen = fdt_path_offset(fdt, "/chosen");
    stdout_path = fdt_getprop(fdt, chosen, "stdout-path", &len);
    if (!stdout_path || len <= 0)
    {
        stdout_path = "/soc/serial@2500000";
    }
    rt_strncpy(out->stdout_path, stdout_path, sizeof(out->stdout_path) - 1);

    uart = fdt_path_offset(fdt, stdout_path);
    if (uart < 0)
    {
        return -2;
    }

    out->reg = prop_u32(fdt, uart, "reg", 0x02500000U);
    out->irq = prop_u32(fdt, uart, "interrupts", V861_UART0_IRQ);
    out->baud = prop_u32(fdt, uart, "current-speed", 115200U);
    out->clk_hz = prop_u32(fdt, uart, "clock-frequency", 24000000U);
    if (prop_u32_pair(fdt, uart, "allwinner,clock-gate", &out->gate_reg, &out->gate_bit) != 0)
    {
        out->gate_reg = 0x0200190cU;
        out->gate_bit = 0;
    }
    if (prop_u32_pair(fdt, uart, "allwinner,reset", &out->reset_reg, &out->reset_bit) != 0)
    {
        out->reset_reg = 0x0200190cU;
        out->reset_bit = 16;
    }

    pins = fdt_getprop(fdt, uart, "allwinner,pins", &len);
    if (pins && len >= 24)
    {
        out->pin_count = 2;
        for (i = 0; i < 2; i++)
        {
            out->pin_port[i] = fdt32_to_cpu(pins[i * 3 + 0]);
            out->pin_num[i] = fdt32_to_cpu(pins[i * 3 + 1]);
            out->pin_func[i] = fdt32_to_cpu(pins[i * 3 + 2]);
        }
    }
    else
    {
        out->pin_count = 2;
        out->pin_port[0] = 7;
        out->pin_num[0] = 9;
        out->pin_func[0] = 5;
        out->pin_port[1] = 7;
        out->pin_num[1] = 10;
        out->pin_func[1] = 5;
    }

    out->valid = 1;
    RT_UNUSED(fdt_blob_size);
    return 0;
}

void rt_hw_fdt_print_uart(const struct v861_uart_fdt *cfg)
{
    if (!cfg || !cfg->valid)
    {
        rt_kprintf("DT: uart load FAILED\n");
        return;
    }

    rt_kprintf("DT: compatible=%s\n", cfg->compatible);
    rt_kprintf("DT: stdout %s reg=0x%08x irq=%u baud=%u clk=%u\n",
               cfg->stdout_path, cfg->reg, cfg->irq, cfg->baud, cfg->clk_hz);
    rt_kprintf("DT: gate=0x%08x:%u reset=0x%08x:%u\n",
               cfg->gate_reg, cfg->gate_bit, cfg->reset_reg, cfg->reset_bit);
    if (cfg->pin_count >= 2)
    {
        rt_kprintf("DT: pinctrl P%u.%u/fn%u P%u.%u/fn%u\n",
                   cfg->pin_port[0], cfg->pin_num[0], cfg->pin_func[0],
                   cfg->pin_port[1], cfg->pin_num[1], cfg->pin_func[1]);
    }
}
