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

#include <drivers/ofw.h>
#include <drivers/ofw_io.h>
#include <drivers/ofw_fdt.h>
#include <drivers/misc.h>

#define DBG_TAG "rtdm.ofw"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "ofw_internal.h"

static volatile rt_atomic_t _bus_ranges_idx = 0;
static struct bus_ranges *_bus_ranges[RT_USING_OFW_BUS_RANGES_NUMBER] = {};

static int ofw_bus_addr_cells(struct rt_ofw_node *np)
{
    int res = OFW_ROOT_NODE_ADDR_CELLS_DEFAULT;

    for (rt_uint32_t cells; np; np = np->parent)
    {
        if (!rt_ofw_prop_read_u32(np, "#address-cells", &cells))
        {
            res = cells;
            break;
        }
    }

    return res;
}

static int ofw_bus_size_cells(struct rt_ofw_node *np)
{
    int res = OFW_ROOT_NODE_SIZE_CELLS_DEFAULT;

    for (rt_uint32_t cells; np; np = np->parent)
    {
        if (!rt_ofw_prop_read_u32(np, "#size-cells", &cells))
        {
            res = cells;
            break;
        }
    }

    return res;
}

int rt_ofw_bus_addr_cells(struct rt_ofw_node *np)
{
    return np ? ofw_bus_addr_cells(np) : -RT_EINVAL;
}

int rt_ofw_bus_size_cells(struct rt_ofw_node *np)
{
    return np ? ofw_bus_size_cells(np) : -RT_EINVAL;
}

int rt_ofw_io_addr_cells(struct rt_ofw_node *np)
{
    return np ? ofw_bus_addr_cells(np->parent ? np->parent : np) : -RT_EINVAL;
}

int rt_ofw_io_size_cells(struct rt_ofw_node *np)
{
    return np ? ofw_bus_size_cells(np->parent ? np->parent : np) : -RT_EINVAL;
}

int rt_ofw_get_address_count(struct rt_ofw_node *np)
{
    int count;

    if (np)
    {
        rt_ssize_t len;

        count = 0;

        if (rt_ofw_get_prop(np, "reg", &len))
        {
            count = len / (sizeof(fdt32_t) * (rt_ofw_io_addr_cells(np) + rt_ofw_io_size_cells(np)));
        }
    }
    else
    {
        count = -RT_EINVAL;
    }

    return count;
}

static rt_err_t ofw_get_address(struct rt_ofw_node *np, int index, rt_uint64_t *out_address, rt_uint64_t *out_size)
{
    rt_ssize_t len;
    rt_err_t err = RT_EOK;
    int addr_cells = rt_ofw_io_addr_cells(np);
    int size_cells = rt_ofw_io_size_cells(np);
    int skip_cells = (addr_cells + size_cells) * index;
    const fdt32_t *cell = rt_ofw_prop_read_raw(np, "reg", &len);

    if (cell && skip_cells < (len / sizeof(*cell)))
    {
        cell += skip_cells;
        *out_address = rt_fdt_next_cell(&cell, addr_cells);
        *out_address = rt_ofw_translate_address(np, RT_NULL, *out_address);
        *out_size = rt_fdt_read_number(cell, size_cells);
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

rt_err_t rt_ofw_get_address(struct rt_ofw_node *np, int index, rt_uint64_t *out_address, rt_uint64_t *out_size)
{
    rt_err_t err;

    if (np && index >= 0 && (out_address || out_size))
    {
        rt_uint64_t address, size;

        err = ofw_get_address(np, index, &address, &size);

        if (!err)
        {
            if (out_address)
            {
                *out_address = address;
            }
            if (out_size)
            {
                *out_size = size;
            }
        }
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

static rt_err_t ofw_get_address_by_name(struct rt_ofw_node *np, const char *name,
        rt_uint64_t *out_address, rt_uint64_t *out_size)

{
    int index = 0;
    rt_err_t err = -RT_EEMPTY;
    const char *reg_name;
    struct rt_ofw_prop *prop;

    rt_ofw_foreach_prop_string(np, "reg-names", prop, reg_name)
    {
        if (!rt_strcmp(name, reg_name))
        {
            err = rt_ofw_get_address(np, index, out_address, out_size);

            break;
        }

        ++index;
    }

    return err;
}

rt_err_t rt_ofw_get_address_by_name(struct rt_ofw_node *np, const char *name,
        rt_uint64_t *out_address, rt_uint64_t *out_size)
{
    rt_err_t err;

    if (np && name && (out_address || out_size))
    {
        rt_uint64_t address, size;

        err = ofw_get_address_by_name(np, name, &address, &size);

        if (!err)
        {
            if (out_address)
            {
                *out_address = address;
            }
            if (out_size)
            {
                *out_size = size;
            }
        }
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

int rt_ofw_get_address_array(struct rt_ofw_node *np, int nr, rt_uint64_t *out_regs)
{
    int count;

    if (np && nr > 0 && out_regs)
    {
        rt_ssize_t len;
        int max_nr;
        int addr_cells = rt_ofw_io_addr_cells(np);
        int size_cells = rt_ofw_io_size_cells(np);
        const fdt32_t *cell = rt_ofw_prop_read_raw(np, "reg", &len);

        max_nr = len / (sizeof(*cell) * (addr_cells + size_cells));

        if (nr > max_nr)
        {
            nr = max_nr;
        }

        count = nr;

        while (nr --> 0)
        {
            *out_regs = rt_fdt_next_cell(&cell, addr_cells);
            *out_regs = rt_ofw_translate_address(np, RT_NULL, *out_regs);
            ++out_regs;

            *out_regs = rt_fdt_next_cell(&cell, size_cells);
            ++out_regs;
        }
    }
    else
    {
        count = -RT_EINVAL;
    }

    return count;
}

static struct bus_ranges *ofw_bus_ranges(struct rt_ofw_node *np, struct rt_ofw_prop *prop)
{
    int id;
    const fdt32_t *cell;
    struct bus_ranges *ranges = RT_NULL;
    int child_address_cells, child_size_cells, parent_address_cells, groups;
    rt_uint64_t *child_addr, *parent_addr, *child_size;

    /*
     * Address Translation Example:
     *
     *  / {
     *      #address-cells = <1>;
     *      #size-cells = <1>;
     *
     *      soc {
     *          compatible = "simple-bus";
     *          #address-cells = <1>;
     *          #size-cells = <1>;
     *          ranges = <0x0 0xe0000000 0x00100000>;
     *
     *          serial@4600 {
     *              device_type = "serial";
     *              reg = <0x4600 0x100>;
     *              clock-frequency = <0>;
     *          };
     *      };
     *  }
     *
     * The soc node specifies a ranges property of <0x0 0xe0000000 0x00100000>;
     * This property value specifies that for a 1024 KB range of address space, a
     * child node addressed at physical 0x0 maps to a parent address of physical
     * 0xe0000000. With this mapping, the serial device node can be addressed by a
     * load or store at address 0xe0004600, an offset of 0x4600 (specified in reg)
     * plus the 0xe0000000 mapping specified in ranges:
     *
     *      bus-address = parent-bus-address + (reg-address - child-bus-address)
     */

    do {
        child_address_cells = rt_ofw_bus_addr_cells(np);
        child_size_cells = rt_ofw_bus_size_cells(np);
        parent_address_cells = rt_ofw_io_addr_cells(np);

        if (child_address_cells < 0 || child_size_cells < 0 || parent_address_cells < 0)
        {
            LOG_D("%s read address/size cells fail: child[%d, %d] parent[%d]",
                    np->full_name, child_address_cells, child_size_cells, parent_address_cells);

            break;
        }

        groups = prop->length / sizeof(*cell);
        groups /= child_address_cells + child_size_cells + parent_address_cells;

        ranges = rt_malloc(sizeof(*ranges) + sizeof(rt_uint64_t) * 3 * groups);

        if (!ranges)
        {
            break;
        }

        ranges->nr = groups;
        ranges->child_addr = (void *)ranges + sizeof(*ranges);
        ranges->parent_addr = &ranges->child_addr[groups];
        ranges->child_size = &ranges->parent_addr[groups];

        cell = prop->value;

        child_addr = ranges->child_addr;
        parent_addr = ranges->parent_addr;
        child_size = ranges->child_size;

        while (groups --> 0)
        {
            *child_addr++ = rt_fdt_next_cell(&cell, child_address_cells);
            *parent_addr++ = rt_fdt_next_cell(&cell, parent_address_cells);
            *child_size++ = rt_fdt_next_cell(&cell, child_size_cells);
        }

        ranges->np = np;

        id = (int)rt_atomic_add(&_bus_ranges_idx, 1);
        RT_ASSERT(id < RT_ARRAY_SIZE(_bus_ranges));

        _bus_ranges[id] = ranges;
    } while (0);

    return ranges;
}

rt_uint64_t rt_ofw_translate_address(struct rt_ofw_node *np, const char *range_type, rt_uint64_t address)
{
    rt_uint64_t cpu_addr = address;

    if (!range_type)
    {
        range_type = "ranges";
    }

    rt_ofw_foreach_parent_node(np)
    {
        rt_ssize_t len;
        struct rt_ofw_prop *prop;
        struct bus_ranges *ranges = RT_NULL;

        prop = rt_ofw_get_prop(np, range_type, &len);

        if (!prop || !len)
        {
            continue;
        }

        for (int i = 0; i < RT_ARRAY_SIZE(_bus_ranges); ++i)
        {
            if (!_bus_ranges[i])
            {
                break;
            }

            if (_bus_ranges[i]->np == np)
            {
                ranges = _bus_ranges[i];
                break;
            }
        }

        if (!ranges)
        {
            ranges = ofw_bus_ranges(np, prop);
        }

        if (ranges)
        {
            for (int i = 0; i < ranges->nr; ++i)
            {
                rt_uint64_t child_addr = ranges->child_addr[i];
                rt_uint64_t child_size = ranges->child_size[i];

                if (address >= child_addr && address < child_addr + child_size)
                {
                    cpu_addr = address + (ranges->parent_addr[i] - child_addr);

                    break;
                }
            }
        }
        else
        {
            cpu_addr = ~0ULL;
        }

        rt_ofw_node_put(np);

        break;
    }

    return cpu_addr;
}

rt_uint64_t rt_ofw_reverse_address(struct rt_ofw_node *np, const char *range_type, rt_uint64_t address)
{
    rt_uint64_t bus_addr = address;

    if (!range_type)
    {
        range_type = "ranges";
    }

    rt_ofw_foreach_parent_node(np)
    {
        rt_ssize_t len;
        struct rt_ofw_prop *prop;
        struct bus_ranges *ranges = RT_NULL;

        prop = rt_ofw_get_prop(np, range_type, &len);

        if (!prop || !len)
        {
            continue;
        }

        for (int i = 0; i < RT_ARRAY_SIZE(_bus_ranges); ++i)
        {
            if (!_bus_ranges[i])
            {
                break;
            }

            if (_bus_ranges[i]->np == np)
            {
                ranges = _bus_ranges[i];
                break;
            }
        }

        if (!ranges)
        {
            ranges = ofw_bus_ranges(np, prop);
        }

        if (ranges)
        {
            for (int i = 0; i < ranges->nr; ++i)
            {
                rt_uint64_t parent_addr = ranges->parent_addr[i];
                rt_uint64_t child_size = ranges->child_size[i];

                if (address >= parent_addr && address < parent_addr + child_size)
                {
                    bus_addr = ranges->child_addr[i] + (address - parent_addr);

                    break;
                }
            }
        }
        else
        {
            bus_addr = ~0ULL;
        }

        rt_ofw_node_put(np);

        break;
    }

    return bus_addr;
}

#ifdef ARCH_CPU_64BIT
#define ofw_address_cpu_cast(np, address) (void *)(address)
#else
#define ofw_address_cpu_cast(np, address)                       \
({                                                              \
    if (((address) >> 32))                                      \
    {                                                           \
        LOG_W("%s find 64 bits address = %x%x",                 \
                rt_ofw_node_full_name(np),                      \
                ofw_static_cast(rt_ubase_t, (address) >> 32),   \
                ofw_static_cast(rt_ubase_t, (address)));        \
    }                                                           \
    (void *)ofw_static_cast(rt_ubase_t, (address));             \
})
#endif

void *rt_ofw_iomap(struct rt_ofw_node *np, int index)
{
    void *iomem = RT_NULL;

    if (np)
    {
        rt_uint64_t regs[2];

        if (!ofw_get_address(np, index, &regs[0], &regs[1]))
        {
            iomem = rt_ioremap(ofw_address_cpu_cast(np, regs[0]), (size_t)regs[1]);
        }
    }

    return iomem;
}

void *rt_ofw_iomap_by_name(struct rt_ofw_node *np, const char *name)
{
    void *iomem = RT_NULL;

    if (np)
    {
        rt_uint64_t regs[2];

        if (!ofw_get_address_by_name(np, name, &regs[0], &regs[1]))
        {
            iomem = rt_ioremap(ofw_address_cpu_cast(np, regs[0]), (size_t)regs[1]);
        }
    }

    return iomem;
}
