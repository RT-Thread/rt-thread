/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-25     GuEe-GUI     first version
 */

#include <rtthread.h>

#include <drivers/pic.h>
#include <drivers/ofw.h>
#include <drivers/ofw_io.h>
#include <drivers/ofw_irq.h>

#define DBG_TAG "rtdm.ofw"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "ofw_internal.h"

static int ofw_interrupt_cells(struct rt_ofw_node *np)
{
    int interrupt_cells = -RT_EEMPTY;

    rt_ofw_prop_read_u32(np, "#interrupt-cells", (rt_uint32_t *)&interrupt_cells);

    return interrupt_cells;
}

int rt_ofw_irq_cells(struct rt_ofw_node *np)
{
    return np ? ofw_interrupt_cells(np) : -RT_EINVAL;
}

static rt_err_t ofw_parse_irq_map(struct rt_ofw_node *np, struct rt_ofw_cell_args *irq_args)
{
    rt_err_t err = RT_EOK;
    rt_phandle ic_phandle = 0;
    rt_ssize_t map_len, map_mask_len;
    struct rt_ofw_node *ic_np = RT_NULL;
    const fdt32_t *addr, *map, *map_mask;
    int child_address_cells, child_interrupt_cells;
    int parent_address_cells, parent_interrupt_cells;
    int addr_cells, pin_cells, icaddr_cells, idx1, idx2, limit;

    /*
     * interrupt-map:
     *  An interrupt-map is a property on a nexus node that bridges one
     *  interrupt domain with a set of parent interrupt domains and specifies
     *  how interrupt specifiers in the child domain are mapped to
     *  their respective parent domains.
     *
     *  The interrupt map is a table where each row is a mapping entry
     *  consisting of five components: child unit address, child interrupt
     *  specifier, interrupt-parent, parent unit address, parent interrupt
     *  specifier.
     *
     *  child unit address
     *      The unit address of the child node being mapped. The number of
     *      32-bit cells required to specify this is described by the
     *      #address-cells property of the bus node on which the child is
     *      located.
     *
     *  child interrupt specifier
     *      The interrupt specifier of the child node being mapped. The number
     *      of 32-bit cells required to specify this component is described by
     *      the #interrupt-cells property of this node-the nexus node containing
     *      the interrupt-map property.
     *
     *  interrupt-parent
     *      A single <phandle> value that points to the interrupt parent to
     *      which the child domain is being mapped.
     *
     *  parent unit address
     *      The unit address in the domain of the interrupt parent. The number
     *      of 32-bit cells required to specify this address is described by the
     *      #address-cells property of the node pointed to by the
     *      interrupt-parent field.
     *
     *  parent interrupt specifier
     *      The interrupt specifier in the parent domain. The number of 32-bit
     *      cells required to specify this component is described by the
     *      #interrupt-cells property of the node pointed to by the
     *      interrupt-parent field.
     *
     *  Lookups are performed on the interrupt mapping table by matching a
     *  unit-address/interrupt specifier pair against the child components in
     *  the interrupt-map. Because some fields in the unit interrupt specifier
     *  may not be relevant, a mask is applied before the lookup is done.
     *  Example:
     *
     *      pic: interrupt-controller@0 {
     *          interrupt-controller;
     *          #address-cells = <0>;   // icaddr (parent unit address)
     *          #interrupt-cells = <1>; // icintr (parent interrupt specifier)
     *      };
     *
     *      gic: interrupt-controller@1 {
     *          interrupt-controller;
     *          #address-cells = <2>;   // icaddr (parent unit address)
     *          #interrupt-cells = <3>; // icintr (parent interrupt specifier)
     *      };
     *
     *      pcie {
     *          #address-cells = <3>;   // addr (child unit address)
     *          #interrupt-cells = <1>; // pin (child interrupt specifier)
     *          interrupt-parent = <&gic>;
     *          interrupt-map-mask = <0x1800 0 0 7>;
     *          interrupt-map =
     *              //     addr pin   ic icintr
     *              <0x0000 0 0   1 &pic      1>, // INTA SOLT 0
     *              <0x0000 0 0   2 &pic      2>, // INTB
     *              <0x0000 0 0   3 &pic      3>, // INTC
     *              <0x0000 0 0   4 &pic      4>, // INTD
     *              <0x0800 0 0   1 &pic      2>, // INTA SOLT 1
     *              <0x0800 0 0   2 &pic      3>, // INTB
     *              <0x0800 0 0   3 &pic      4>, // INTC
     *              <0x0800 0 0   4 &pic      1>, // INTD
     *              //     addr pin   ic icaddr                        icintr
     *              <0x1000 0 0   1 &gic    0 0 GIC_SPI 3 IRQ_TYPE_LEVEL_HIGH>, // INTA SOLT 2
     *              <0x1000 0 0   2 &gic    0 0 GIC_SPI 4 IRQ_TYPE_LEVEL_HIGH>, // INTB
     *              <0x1000 0 0   3 &gic    0 0 GIC_SPI 1 IRQ_TYPE_LEVEL_HIGH>, // INTC
     *              <0x1000 0 0   4 &gic    0 0 GIC_SPI 2 IRQ_TYPE_LEVEL_HIGH>, // INTD
     *              <0x1800 0 0   1 &gic    0 0 GIC_SPI 4 IRQ_TYPE_LEVEL_HIGH>, // INTA SOLT 3
     *              <0x1800 0 0   2 &gic    0 0 GIC_SPI 1 IRQ_TYPE_LEVEL_HIGH>, // INTB
     *              <0x1800 0 0   3 &gic    0 0 GIC_SPI 2 IRQ_TYPE_LEVEL_HIGH>, // INTC
     *              <0x1800 0 0   4 &gic    0 0 GIC_SPI 3 IRQ_TYPE_LEVEL_HIGH>; // INTD
     *      };
     *
     * In fact, basically no SoC will be use multi ic to implemented INTx.
     * before call ofw_parse_irq_map(np, &args):
     *
     *      args.data = addr;
     *      args.args_count = 2 or 3;
     *      args.args[0] = (addr cells);
     *      args.args[1] = (pin cells);
     *      args.args[2] = (icaddr cells);
     *
     * if call with `pcie` in ofw_parse_irq_map(np, &args):
     *
     *      np = &pcie;
     *      args.data = addr = fdt32_t({ (bus << 16) | (device << 11) | (function << 8), 0, 0, pin });
     *      args.args_count = 2;
     *      args.args[0] = 3;
     *      args.args[1] = 1;
     *
     * To perform a lookup of the gic interrupt source number for INTB for IDSEL
     * 0x12 (slot 2), function 0x3, the following steps would be performed:
     *
     *  1.The user addr is value <0x9300 0 0 2>.
     *
     *  2.The encoding of the address includes the bus number (0x0 << 16),
     *    device number (0x12 << 11), and function number (0x3 << 8).
     *
     *  3.The interrupt specifier is 2, which is the encoding for INTB as per
     *    the PCI binding.
     *
     *  4.The interrupt-map-mask value <0x1800 0 0 7> is applied, giving a
     *    result of <0x1000 0 0 2>.
     *
     *  5.That result is looked up in the interrupt-map table, which maps to the
     *    parent interrupt specifier <GIC_SPI 4 IRQ_TYPE_LEVEL_HIGH>.
     */

    do {
        err = -RT_EEMPTY;

        if ((child_address_cells = rt_ofw_bus_addr_cells(np)) < 0)
        {
            LOG_D("%s property %s is undefined", np->full_name, "#address-cells");

            break;
        }

        if ((child_interrupt_cells = ofw_interrupt_cells(np)) < 0)
        {
            LOG_D("%s property %s is undefined", np->full_name, "#interrupt-cells");

            break;
        }

        if (!(map = rt_ofw_prop_read_raw(np, "interrupt-map", &map_len)))
        {
            LOG_D("%s property %s is undefined", np->full_name, "interrupt-map");

            break;
        }

        if (!(map_mask = rt_ofw_prop_read_raw(np, "interrupt-map-mask", &map_mask_len)))
        {
            LOG_D("%s property %s is undefined", np->full_name, "interrupt-map-mask");

            break;
        }

        err = -RT_EINVAL;

        addr = irq_args->data;
        addr_cells = irq_args->args[0];
        pin_cells = irq_args->args[1];
        icaddr_cells = irq_args->args_count == 3 ? irq_args->args[2] : 0;

        if (addr_cells > child_address_cells)
        {
            LOG_D("%s(%d) > %s(%d)", "addr_cells", addr_cells, "child_address_cells", child_address_cells);

            break;
        }

        if (pin_cells > child_interrupt_cells)
        {
            LOG_D("%s(%d) > %s(%d)", "pin_cells", pin_cells, "child_interrupt_cells", child_interrupt_cells);

            break;
        }

        err = -RT_ENOENT;

#define _map_walk_range(_idx, _idx2, _count, ...) \
        for (idx1 = _idx, idx2 = _idx2, limit = idx1 + _count; idx1 < limit __VA_ARGS__; ++idx1, ++idx2)

        _map_walk_range(0, 0, addr_cells)
        {
            /* Applied addr mask */
            ((fdt32_t *)addr)[idx1] &= map_mask[idx2];
        }

        _map_walk_range(addr_cells, child_address_cells, pin_cells)
        {
            /* Applied pin mask */
            ((fdt32_t *)addr)[idx1] &= map_mask[idx2];
        }

        while (map_len > 0)
        {
            rt_bool_t match = RT_TRUE;

            _map_walk_range(0, 0, addr_cells)
            {
                /* Applied mask */
                if (addr[idx1] != map[idx2])
                {
                    match = RT_FALSE;
                    break;
                }
            }

            _map_walk_range(addr_cells, child_address_cells, pin_cells, && match)
            {
                /* Applied mask */
                if (addr[idx1] != map[idx2])
                {
                    match = RT_FALSE;
                    break;
                }
            }

            /* Skip addr, pin */
            map += map_mask_len;

            /* IC is different? */
            if (ic_phandle != fdt32_to_cpu(*map))
            {
                rt_ofw_node_put(ic_np);

                ic_phandle = fdt32_to_cpu(*map);
                ic_np = rt_ofw_find_node_by_phandle(ic_phandle);

                if (!ic_np)
                {
                    LOG_D("%s irq parent phandle = %d is not found", np->full_name, ic_phandle);

                    break;
                }

                if ((parent_address_cells = rt_ofw_bus_addr_cells(ic_np)) < 0)
                {
                    LOG_D("%s property %s is undefined", ic_np->full_name, "#address-cells");

                    break;
                }

                if (icaddr_cells > parent_address_cells)
                {
                    LOG_D("%s(%d) > %s(%d)", "icaddr_cells", icaddr_cells, "parent_address_cells", parent_address_cells);

                    break;
                }

                if ((parent_interrupt_cells = ofw_interrupt_cells(ic_np)) < 0)
                {
                    LOG_D("%s property %s is undefined", ic_np->full_name, "#interrupt-cells");

                    break;
                }

                RT_ASSERT(parent_interrupt_cells <= RT_OFW_MAX_CELL_ARGS);
            }

            /* Skip ic phandle */
            ++map;

            _map_walk_range(addr_cells + pin_cells, 0, icaddr_cells, && match)
            {
                /* Applied ic_addr mask */
                if (addr[idx1] != map[idx2])
                {
                    match = RT_FALSE;
                    break;
                }
            }

            /* Skip icaddr */
            map += parent_address_cells;

            if (match)
            {
                irq_args->data = ic_np;
                irq_args->args_count = parent_interrupt_cells;

                for (int i = 0; i < irq_args->args_count; ++i)
                {
                    irq_args->args[i] = fdt32_to_cpu(*map++);
                }

                err = RT_EOK;

                break;
            }

            /* Skip icintr */
            map += parent_interrupt_cells;

            map_len -= map_mask_len + 1 + parent_address_cells + parent_interrupt_cells;
        }

#undef _map_walk_range
    } while (0);

    return err;
}

rt_err_t rt_ofw_parse_irq_map(struct rt_ofw_node *np, struct rt_ofw_cell_args *irq_args)
{
    rt_err_t err;

    if (np && irq_args && irq_args->data)
    {
        err = ofw_parse_irq_map(np, irq_args);
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

static rt_err_t ofw_parse_irq_cells(struct rt_ofw_node *np, int index, struct rt_ofw_cell_args *out_irq_args)
{
    rt_err_t err;

    /*
     * interrupts-extended:
     *
     *  The interrupts-extended property lists the interrupt(s) generated by a
     *  device. interrupts-extended should be used instead of interrupts when a
     *  device is connected to multiple interrupt controllers as it encodes a
     *  parent phandle with each interrupt specifier. Example:
     *
     *      pic: interrupt-controller@0 {
     *          interrupt-controller;
     *          #interrupt-cells = <1>;
     *      };
     *
     *      gic: interrupt-controller@1 {
     *          interrupt-controller;
     *          #interrupt-cells = <3>;
     *      };
     *
     *      node: node {
     *          interrupts-extended = <&pic 9>, <&gic GIC_SPI 1 IRQ_TYPE_LEVEL_HIGH>;
     *      };
     *
     *  call `rt_ofw_parse_phandle_cells` to get irq info;
     */

    err = rt_ofw_parse_phandle_cells(np, "interrupts-extended", "#interrupt-cells", index, out_irq_args);

    do {
        int interrupt_cells;
        const fdt32_t *cell;
        rt_ssize_t interrupt_len;
        struct rt_ofw_node *ic_np;

        if (!err)
        {
            break;
        }

        /*
         * interrupts (old style):
         *
         *  The interrupts property of a device node defines the interrupt or
         *  interrupts that are generated by the device. The value of the
         *  interrupts property consists of an arbitrary number of interrupt
         *  specifiers. The format of an interrupt specifier is defined by the
         *  binding of the interrupt domain root.
         *  interrupts is overridden by the interrupts-extended property and
         *  normally only one or the other should be used. Example:
         *
         *      pic: interrupt-controller@0 {
         *          interrupt-controller;
         *          #interrupt-cells = <1>;
         *      };
         *
         *      gic: interrupt-controller@1 {
         *          interrupt-controller;
         *          #interrupt-cells = <3>;
         *      };
         *
         *      node0: node0 {
         *          interrupt-parent = <&pic>;
         *          interrupts = <9>;
         *      };
         *
         *      node1: node1 {
         *          interrupt-parent = <&gic>;
         *          interrupts = <GIC_SPI 1 IRQ_TYPE_LEVEL_HIGH>;
         *      };
         */

        cell = rt_ofw_prop_read_raw(np, "interrupts", &interrupt_len);

        if (!cell)
        {
            err = -RT_ERROR;
            break;
        }

        ic_np = rt_ofw_find_irq_parent(np, &interrupt_cells);

        if (!ic_np)
        {
            err = -RT_ERROR;
            break;
        }

        RT_ASSERT(interrupt_cells <= RT_OFW_MAX_CELL_ARGS);

        if (index >= interrupt_len / (interrupt_cells * sizeof(*cell)))
        {
            err = -RT_EINVAL;
            break;
        }

        cell += index * interrupt_cells;

        out_irq_args->data = ic_np;
        out_irq_args->args_count = interrupt_cells;

        for (int idx = 0; idx < interrupt_cells; ++idx, ++cell)
        {
            out_irq_args->args[idx] = fdt32_to_cpu(*cell);
        }

        err = RT_EOK;
    } while (0);

    return err;
}

rt_err_t rt_ofw_parse_irq_cells(struct rt_ofw_node *np, int index, struct rt_ofw_cell_args *out_irq_args)
{
    rt_err_t err;

    if (np && index >= 0 && out_irq_args)
    {
        err = ofw_parse_irq_cells(np, index, out_irq_args);
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

struct rt_ofw_node *rt_ofw_find_irq_parent(struct rt_ofw_node *np, int *out_interrupt_cells)
{
    rt_ofw_foreach_parent_node(np)
    {
        rt_phandle ic_phandle;

        if (!rt_ofw_prop_read_u32(np, "interrupt-parent", (rt_uint32_t *)&ic_phandle))
        {
            int interrupt_cells;
            struct rt_ofw_node *ic_np = rt_ofw_find_node_by_phandle(ic_phandle);

            if (ic_np && (interrupt_cells = ofw_interrupt_cells(ic_np)) >= 0)
            {
                np = ic_np;

                if (out_interrupt_cells)
                {
                    *out_interrupt_cells = interrupt_cells;
                }

                break;
            }

            rt_ofw_node_put(ic_np);
        }
    }

    return np;
}

static int ofw_map_irq(struct rt_ofw_cell_args *irq_args)
{
    int irq;
    struct rt_ofw_node *ic_np = irq_args->data;
    struct rt_pic *pic = rt_ofw_data(ic_np);

    /* args.data is "interrupt-controller" */
    if (pic)
    {
        struct rt_pic_irq pirq;

        if (!pic->ops->irq_parse)
        {
            LOG_E("Master pic MUST implemented irq_parse");
            RT_ASSERT(0);
        }

        if (!pic->ops->irq_map)
        {
            LOG_E("Master pic MUST implemented irq_map");
            RT_ASSERT(0);
        }

        irq = pic->ops->irq_parse(pic, irq_args, &pirq);

        if (!irq)
        {
            irq = pic->ops->irq_map(pic, pirq.hwirq, pirq.mode);
        }
    }
    else
    {
        LOG_E("Master pic %s not support", ic_np->full_name);
        irq = -RT_EIO;
    }

    rt_ofw_node_put(ic_np);

    return irq;
}

int rt_ofw_map_irq(struct rt_ofw_cell_args *irq_args)
{
    int irq;

    if (irq_args && irq_args->data && irq_args->args_count > 0)
    {
        irq = ofw_map_irq(irq_args);
    }
    else
    {
        irq = -RT_EINVAL;
    }

    return irq;
}

int rt_ofw_get_irq_count(struct rt_ofw_node *np)
{
    int count;

    if (np)
    {
        struct rt_ofw_cell_args irq_args;

        count = 0;

        while (!ofw_parse_irq_cells(np, count, &irq_args))
        {
            ++count;
        }
    }
    else
    {
        count = -RT_EINVAL;
    }

    return count;
}

int rt_ofw_get_irq(struct rt_ofw_node *np, int index)
{
    int irq;

    if (np && index >= 0)
    {
        struct rt_ofw_cell_args irq_args;

        irq = ofw_parse_irq_cells(np, index, &irq_args);

        if (irq >= 0)
        {
            irq = ofw_map_irq(&irq_args);
        }
    }
    else
    {
        irq = -RT_EINVAL;
    }

    return irq;
}

int rt_ofw_get_irq_by_name(struct rt_ofw_node *np, const char *name)
{
    int irq;

    if (np && name)
    {
        int index = rt_ofw_prop_index_of_string(np, "interrupt-names", name);

        if (index >= 0)
        {
            irq = rt_ofw_get_irq(np, index);
        }
        else
        {
            irq = -1;
        }
    }
    else
    {
        irq = -RT_EINVAL;
    }

    return irq;
}
