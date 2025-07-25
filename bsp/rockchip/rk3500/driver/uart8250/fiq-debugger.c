/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <ioremap.h>
#include <cpuport.h>

#include "regs.h"
#include "serial_dm.h"

#define UART_USR                    0x1f /* In: UART Status Register */
#define UART_USR_RX_FIFO_FULL       0x10 /* Receive FIFO full */
#define UART_USR_RX_FIFO_NOT_EMPTY  0x08 /* Receive FIFO not empty */
#define UART_USR_TX_FIFO_EMPTY      0x04 /* Transmit FIFO empty */
#define UART_USR_TX_FIFO_NOT_FULL   0x02 /* Transmit FIFO not full */
#define UART_USR_BUSY               0x01 /* UART busy indicator */
#define UART_SRR                    0x22 /* software reset register */

#define FIQ_DEBUGGER_NO_CHAR        -1
#define FIQ_DEBUGGER_BREAK          -2

struct rockchip_fiq_debugger
{
    struct rt_serial_device parent;

    int irq;
    int baudrate;
    void *debug_port_base;
    rt_bool_t break_seen;
};

#define raw_to_fiq_debugger(raw) rt_container_of(raw, struct rockchip_fiq_debugger, parent)

rt_inline void rockchip_fiq_write(struct rockchip_fiq_debugger *t, rt_uint32_t val, int off)
{
    HWREG32(t->debug_port_base + off * 4) = val;
}

rt_inline rt_uint32_t rockchip_fiq_read(struct rockchip_fiq_debugger *t, int off)
{
    return HWREG32(t->debug_port_base + off * 4);
}

rt_inline rt_uint32_t rockchip_fiq_read_lsr(struct rockchip_fiq_debugger *t)
{
    rt_uint32_t ret = rockchip_fiq_read(t, UART_LSR);

    if (ret & UART_LSR_BI)
    {
        t->break_seen = true;
    }

    return ret;
}

static void fiq_debugger_isr(int irqno, void *param)
{
    rt_uint32_t usr;
    struct rt_serial_device *serial = (struct rt_serial_device*)param;
    struct rockchip_fiq_debugger *t = raw_to_fiq_debugger(serial);

    usr = rockchip_fiq_read(t, UART_USR);

    if ((usr & UART_USR_RX_FIFO_NOT_EMPTY) == UART_USR_RX_FIFO_NOT_EMPTY)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }

    if ((usr & UART_USR_BUSY) == UART_USR_BUSY)
    {
        /* Clear the USR */
        (void)rockchip_fiq_read(t, UART_USR);
    }
}

static rt_err_t fiq_debugger_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    int dll = 0, dlm = 0;
    rt_uint32_t count = 10000;
    struct rockchip_fiq_debugger *t = raw_to_fiq_debugger(serial);

    if (rockchip_fiq_read(t, UART_LSR) & UART_LSR_DR)
    {
        (void)rockchip_fiq_read(t, UART_RX);
    }

    while (!(rockchip_fiq_read(t, UART_LSR) & UART_LSR_TEMT) && count--)
    {
        rt_hw_us_delay(10);
    }

    switch (t->baudrate)
    {
    case 1500000:
        dll = 0x1;
        break;
    case 115200:
    default:
        dll = 0xd;
        break;
    }
    /* reset uart */
    rockchip_fiq_write(t, (1 << 1) | (1 << 2), UART_SRR);
    rt_hw_us_delay(10);
    /* set uart to loop back mode */
    rockchip_fiq_write(t, 0x10, UART_MCR);

    rockchip_fiq_write(t, 0x83, UART_LCR);
    /* set baud rate */
    rockchip_fiq_write(t, dll, UART_DLL);
    rockchip_fiq_write(t, dlm, UART_DLM);
    rockchip_fiq_write(t, 0x03, UART_LCR);

    /* enable rx interrupt */
    rockchip_fiq_write(t, UART_IER_RDI, UART_IER);

    /*
     * interrupt on every character when received, but we can enable fifo for TX
     * I found that if we enable the RX fifo, some problem may vanish such as
     * when you continuously input characters in the command line the uart irq
     * may be disable because of the uart irq is served when CPU is at IRQ
     * exception, but it is found unregistered, so it is disable.
     */
    rockchip_fiq_write(t, 0x01, UART_FCR);

    /* disbale loop back mode */
    rockchip_fiq_write(t, 0x0, UART_MCR);

    return RT_EOK;
}

static rt_err_t fiq_debugger_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct rockchip_fiq_debugger *t = raw_to_fiq_debugger(serial);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        rt_pic_irq_mask(t->irq);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        rt_pic_irq_unmask(t->irq);
        break;
    }

    return RT_EOK;
}

static int fiq_debugger_uart_putc(struct rt_serial_device *serial, char c)
{
    struct rockchip_fiq_debugger *t = raw_to_fiq_debugger(serial);
    rt_uint32_t count = 10000;

    while (!(rockchip_fiq_read(t, UART_USR) & UART_USR_TX_FIFO_NOT_FULL) && count--)
    {
        rt_hw_cpu_relax();
    }

    rockchip_fiq_write(t, c, UART_TX);

    return 1;
}

static int fiq_debugger_uart_getc(struct rt_serial_device *serial)
{
    int ch = FIQ_DEBUGGER_NO_CHAR;
    rt_uint32_t lsr, temp;
    static rt_uint32_t n = 0;
    static char buf[32] = {};
    struct rockchip_fiq_debugger *t = raw_to_fiq_debugger(serial);

    /* Clear uart interrupt status */
    rockchip_fiq_read(t, UART_USR);
    lsr = rockchip_fiq_read_lsr(t);

    if (lsr & UART_LSR_DR)
    {
        temp = rockchip_fiq_read(t, UART_RX);
        buf[n & 0x1f] = temp;
        n++;

        if (temp == 'q' && n > 2)
        {
            if ((buf[(n - 2) & 0x1f] == 'i') && (buf[(n - 3) & 0x1f] == 'f'))
            {
                ch = FIQ_DEBUGGER_BREAK;
            }
            else
            {
                ch = temp;
            }
        }
        else
        {
            ch = temp;
        }
    }

    return ch;
}

static const struct rt_uart_ops fiq_debugger_uart_ops =
{
    .configure = fiq_debugger_uart_configure,
    .control = fiq_debugger_uart_control,
    .putc = fiq_debugger_uart_putc,
    .getc = fiq_debugger_uart_getc,
};

struct rockchip_fiq_debugger *rk_serial_debug_init(void *base, rt_ubase_t paddr,
    int irq, int signal_irq, int wakeup_irq, rt_uint32_t baudrate)
{
    struct rockchip_fiq_debugger *t = rt_calloc(1, sizeof(*t));

    if (t)
    {
        const char *name;

        t->parent.ops = &fiq_debugger_uart_ops;
        t->parent.config = (struct serial_configure)RT_SERIAL_CONFIG_DEFAULT;
        t->parent.config.baud_rate = baudrate;
        t->irq = irq;
        t->baudrate = baudrate;
        t->debug_port_base = base;
        t->break_seen = RT_FALSE;

        serial_dev_set_name(&t->parent);
        name = rt_dm_dev_get_name(&t->parent.parent);

        rt_hw_serial_register(&t->parent, name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, t);
        rt_pic_attach_irq(t->irq, fiq_debugger_isr, &t->parent, name, RT_IRQ_F_NONE);
    }

    return t;
}

static rt_err_t rockchip_fiq_debugger_probe(struct rt_platform_device *pdev)
{
    rt_err_t err = RT_EOK;
    void *base;
    rt_uint64_t regs[2];
    struct rt_clk *clk, *pclk;
    rt_bool_t found = RT_FALSE;
    char dev_name[RT_NAME_MAX];
    int irq, signal_irq = -1;
    rt_uint32_t serial_id, baudrate = 0, irq_mode = 0, wake_irq = -1;
    struct rt_ofw_node *np = pdev->parent.ofw_node;

    if (rt_ofw_prop_read_u32(np, "rockchip,serial-id", &serial_id) || serial_id == -1)
    {
        return -RT_EINVAL;
    }

    if (rt_ofw_prop_read_u32(np, "rockchip,irq-mode-enable", &irq_mode))
    {
        irq_mode = -1;
    }

    if (irq_mode == 1)
    {
        signal_irq = -1;
    }
    else if (!(signal_irq = rt_ofw_get_irq(np, 0)))
    {
        return -RT_EINVAL;
    }

    if (rt_ofw_prop_read_u32(np, "rockchip,wake-irq", &wake_irq))
    {
        wake_irq = -1;
    }

    if (rt_ofw_prop_read_u32(np, "rockchip,baudrate", &baudrate))
    {
        baudrate = 1500000;
    }

    rt_snprintf(dev_name, RT_NAME_MAX, "serial%d", serial_id);

    np = RT_NULL;

    do {
        np = rt_ofw_find_node_by_tag(np, "serial");

        if (np && rt_ofw_get_alias_id(np, "serial") == serial_id)
        {
            found = RT_TRUE;
            break;
        }
    } while(np);

    if (!found)
    {
        return -RT_EINVAL;
    }

    rt_memset(regs, 0, sizeof(regs));
    rt_ofw_get_address_array(np, 1, regs);

    pclk = rt_ofw_get_clk_by_name(np, "apb_pclk");
    clk = rt_ofw_get_clk_by_name(np, "baudclk");

    if (!pclk || !clk)
    {
        err = -RT_ERROR;
        goto _fail;
    }

    rt_clk_enable(clk);
    rt_clk_enable(pclk);

    if ((irq = rt_ofw_get_irq(np, 0)) < 0)
    {
        err = -RT_ERROR;
        goto _fail;
    }

    if ((base = rt_ioremap((void *)regs[0], regs[1])))
    {
        struct rockchip_fiq_debugger *t = rk_serial_debug_init(base,
            (rt_ubase_t)regs[0], irq, signal_irq, wake_irq, baudrate);

        if (t)
        {
            rt_dm_dev_bind_fwdata(&t->parent.parent, pdev->parent.ofw_node, &t->parent);
        }
    }

    return err;

_fail:
    if (clk)
    {
        rt_clk_disable(clk);
        rt_clk_put(clk);
    }

    if (pclk)
    {
        rt_clk_disable(pclk);
        rt_clk_put(pclk);
    }

    return err;
}

static const struct rt_ofw_node_id rockchip_fiq_debugger_ofw_ids[] =
{
    { .type = "ttyFIQ", .compatible = "rockchip,fiq-debugger" },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_fiq_debugger_driver =
{
    .name = "rockchip-fiq-debugger",
    .ids = rockchip_fiq_debugger_ofw_ids,

    .probe = rockchip_fiq_debugger_probe,
};

static int rockchip_fiq_debugger_drv_register(void)
{
    rt_platform_driver_register(&rockchip_fiq_debugger_driver);

    return 0;
}
INIT_PLATFORM_EXPORT(rockchip_fiq_debugger_drv_register);
