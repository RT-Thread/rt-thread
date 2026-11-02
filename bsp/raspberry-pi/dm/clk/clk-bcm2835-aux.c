/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "clk.bcm2835.aux"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <dt-bindings/clock/bcm2835-aux.h>

#define BCM2835_AUXIRQ  0x00
#define BCM2835_AUXENB  0x04

struct bcm2835_aux_clk
{
    struct rt_clk_node parent;

    void *regs;
    struct rt_clk *clk;
};

#define raw_to_bcm2835_aux_clk(raw) rt_container_of(raw, struct bcm2835_aux_clk, parent)

struct aux_clk_gate
{
    struct rt_clk_cell cell;

    rt_uint8_t bit_idx;
};

#define raw_to_aux_clk_gate(raw) rt_container_of(raw, struct aux_clk_gate, cell)

static void bcm2835_aux_clk_endisable(struct rt_clk_cell *cell, int enable)
{
    int set = 0 ^ enable;
    rt_uint32_t value, bit_idx;
    struct aux_clk_gate *gate = raw_to_aux_clk_gate(cell);
    struct bcm2835_aux_clk *aux_clk = raw_to_bcm2835_aux_clk(cell->clk_np);

    bit_idx = gate->bit_idx;

    value = HWREG32(aux_clk->regs);
    if (set)
    {
        value |= RT_BIT(bit_idx);
    }
    else
    {
        value &= ~RT_BIT(bit_idx);
    }
    HWREG32(aux_clk->regs) = value;
}

static rt_err_t bcm2835_aux_clk_enable(struct rt_clk_cell *cell)
{
    bcm2835_aux_clk_endisable(cell, 1);

    return RT_EOK;
}

static void bcm2835_aux_clk_disable(struct rt_clk_cell *cell)
{
    bcm2835_aux_clk_endisable(cell, 0);
}

static rt_bool_t bcm2835_aux_clk_is_enabled(struct rt_clk_cell *cell)
{
    rt_uint32_t value, bit_idx;
    struct aux_clk_gate *gate = raw_to_aux_clk_gate(cell);
    struct bcm2835_aux_clk *aux_clk = raw_to_bcm2835_aux_clk(cell->clk_np);

    bit_idx = gate->bit_idx;

    value = HWREG32(aux_clk->regs + BCM2835_AUXENB);
    value &= RT_BIT(bit_idx);

    return !!value;
}

static rt_ubase_t bcm2835_aux_clk_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    struct bcm2835_aux_clk *aux_clk = raw_to_bcm2835_aux_clk(cell->clk_np);

    return rt_clk_cell_get_rate(aux_clk->clk->cell);
}

const struct rt_clk_ops bcm2835_aux_clk_ops =
{
    .enable = bcm2835_aux_clk_enable,
    .disable = bcm2835_aux_clk_disable,
    .is_enabled = bcm2835_aux_clk_is_enabled,
    .recalc_rate = bcm2835_aux_clk_recalc_rate,
};

static struct aux_clk_gate aux_uart =
{
    .cell.name = "aux_uart",
    .cell.ops = &bcm2835_aux_clk_ops,
    .bit_idx = 0,
};

static struct aux_clk_gate aux_spi1 =
{
    .cell.name = "aux_spi1",
    .cell.ops = &bcm2835_aux_clk_ops,
    .bit_idx = 1,
};

static struct aux_clk_gate aux_spi2 =
{
    .cell.name = "aux_spi2",
    .cell.ops = &bcm2835_aux_clk_ops,
    .bit_idx = 2,
};

static struct rt_clk_cell *bcm2835_aux_clk_cell[] =
{
    [BCM2835_AUX_CLOCK_UART] = &aux_uart.cell,
    [BCM2835_AUX_CLOCK_SPI1] = &aux_spi1.cell,
    [BCM2835_AUX_CLOCK_SPI2] = &aux_spi2.cell,
};

static rt_err_t bcm2835_aux_clk_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct bcm2835_aux_clk *aux_clk = rt_calloc(1, sizeof(*aux_clk));

    if (!aux_clk)
    {
        return -RT_ENOMEM;
    }

    aux_clk->regs = rt_dm_dev_iomap(dev, 0);

    if (!aux_clk->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    aux_clk->clk = rt_clk_get_by_index(dev, 0);

    if (rt_is_err(aux_clk->clk))
    {
        err = rt_ptr_err(aux_clk->clk);
        goto _fail;
    }

    if (aux_clk->clk)
    {
        for (int i = 0; i < RT_ARRAY_SIZE(bcm2835_aux_clk_cell); ++i)
        {
            struct rt_clk_cell *cell = bcm2835_aux_clk_cell[i];

            if (cell)
            {
                cell->parents_nr = 1;
                cell->parent_name = aux_clk->clk->cell->name;
            }
        }
    }

    aux_clk->parent.dev = dev;
    aux_clk->parent.cells = bcm2835_aux_clk_cell;
    aux_clk->parent.cells_nr = RT_ARRAY_SIZE(bcm2835_aux_clk_cell);

    if ((err = rt_clk_register(&aux_clk->parent)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    if (aux_clk->regs)
    {
        rt_iounmap(aux_clk->regs);
    }

    if (!rt_is_err_or_null(aux_clk->clk))
    {
        rt_clk_put(aux_clk->clk);
    }

    rt_free(aux_clk);

    return err;
}

static const struct rt_ofw_node_id bcm2835_aux_clk_ofw_ids[] =
{
    { .compatible = "brcm,bcm2835-aux", },
    { /* sentinel */ }
};

static struct rt_platform_driver bcm2835_aux_clk_driver =
{
    .name = "clk-bcm2835-aux",
    .ids = bcm2835_aux_clk_ofw_ids,

    .probe = bcm2835_aux_clk_probe,
};

static int bcm2835_aux_clk_register(void)
{
    rt_platform_driver_register(&bcm2835_aux_clk_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(bcm2835_aux_clk_register);
