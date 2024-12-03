/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-25     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <drivers/ofw_fdt.h>
#include <drivers/ofw_raw.h>
#include <drivers/core/dm.h>

#include <mm_memblock.h>

#define DBG_TAG "rtdm.ofw"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "ofw_internal.h"

struct rt_fdt_earlycon fdt_earlycon rt_section(".bss.noclean.earlycon");

RT_OFW_SYMBOL_TYPE_RANGE(earlycon, struct rt_fdt_earlycon_id, _earlycon_start = {}, _earlycon_end = {});

#ifndef ARCH_INIT_MEMREGION_NR
#define ARCH_INIT_MEMREGION_NR 128
#endif

static void *_fdt = RT_NULL;
static rt_phandle _phandle_min;
static rt_phandle _phandle_max;
static rt_size_t _root_size_cells;
static rt_size_t _root_addr_cells;

#ifdef ARCH_CPU_64BIT
#define MIN_BIT   16
#else
#define MIN_BIT   8
#endif

const char *rt_fdt_node_name(const char *full_name)
{
    const char *node_name = strrchr(full_name, '/');

    return node_name ? node_name + 1 : full_name;
}

rt_uint64_t rt_fdt_read_number(const fdt32_t *cell, int size)
{
    rt_uint64_t val = 0;

    for (; size--; ++cell)
    {
        val = (val << 32) | fdt32_to_cpu(*cell);
    }

    return val;
}

rt_uint64_t rt_fdt_next_cell(const fdt32_t **cellptr, int size)
{
    const fdt32_t *ptr = *cellptr;

    *cellptr = ptr + size;

    return rt_fdt_read_number(ptr, size);
}

rt_uint64_t rt_fdt_translate_address(void *fdt, int nodeoffset, rt_uint64_t address)
{
    rt_uint64_t ret = address;

    if (fdt && nodeoffset >= 0)
    {
        struct
        {
            rt_uint64_t addr;
            rt_size_t size;
            int addr_cells;
            int size_cells;
        } local, cpu;
        int parent, length = 0, group_len;
        const fdt32_t *ranges = RT_NULL;

        parent = fdt_parent_offset(fdt, nodeoffset);

        if (parent >= 0)
        {
            ranges = fdt_getprop(fdt, parent, "ranges", &length);
        }

        if (ranges && length > 0)
        {
            local.addr_cells = fdt_address_cells(fdt, parent);
            local.size_cells = fdt_size_cells(fdt, parent);
            cpu.addr_cells = fdt_io_addr_cells(fdt, parent);
            cpu.size_cells = fdt_io_size_cells(fdt, parent);

            group_len = local.addr_cells + cpu.addr_cells + local.size_cells;

            while (length > 0)
            {
                local.addr = rt_fdt_next_cell(&ranges, local.addr_cells);
                cpu.addr = rt_fdt_next_cell(&ranges, cpu.addr_cells);
                local.size = rt_fdt_next_cell(&ranges, local.size_cells);

                if (local.addr <= address && local.addr + local.size > address)
                {
                    ret = address - local.addr + cpu.addr;
                    break;
                }

                length -= group_len;
            }
        }
    }

    return ret;
}

rt_bool_t rt_fdt_device_is_available(void *fdt, int nodeoffset)
{
    rt_bool_t ret;

    const char *status = fdt_getprop(fdt, nodeoffset, "status", RT_NULL);

    if (!status)
    {
        ret = RT_TRUE;
    }
    else if (!rt_strcmp(status, "ok") || !rt_strcmp(status, "okay"))
    {
        ret = RT_TRUE;
    }
    else
    {
        ret = RT_FALSE;
    }

    return ret;
}

rt_err_t rt_fdt_prefetch(void *fdt)
{
    rt_err_t err = -RT_ERROR;

    if (fdt)
    {
        _fdt = fdt;

        if (!fdt_check_header(_fdt))
        {
            err = rt_fdt_scan_root();
        }
        else
        {
            err = -RT_EINVAL;
        }
    }

    return err;
}

rt_err_t rt_fdt_scan_root(void)
{
    rt_err_t err = RT_EOK;
    int root = fdt_path_offset(_fdt, "/");

    if (root >= 0)
    {
        const fdt32_t *prop;

        _root_addr_cells = OFW_ROOT_NODE_ADDR_CELLS_DEFAULT;
        _root_size_cells = OFW_ROOT_NODE_SIZE_CELLS_DEFAULT;

        if ((prop = fdt_getprop(_fdt, root, "#address-cells", RT_NULL)))
        {
            _root_addr_cells = fdt32_to_cpu(*prop);
        }

        if ((prop = fdt_getprop(_fdt, root, "#size-cells", RT_NULL)))
        {
            _root_size_cells = fdt32_to_cpu(*prop);
        }
    }
    else
    {
        err = -RT_EEMPTY;
    }

    return err;
}

static rt_err_t fdt_reserved_mem_check_root(int nodeoffset)
{
    rt_err_t err = RT_EOK;
    const fdt32_t *prop = fdt_getprop(_fdt, nodeoffset, "#size-cells", RT_NULL);

    if (!prop || fdt32_to_cpu(*prop) != _root_size_cells)
    {
        err = -RT_EINVAL;
    }

    if (!err)
    {
        prop = fdt_getprop(_fdt, nodeoffset, "#address-cells", RT_NULL);

        if (!prop || fdt32_to_cpu(*prop) != _root_addr_cells)
        {
            err = -RT_EINVAL;
        }
    }

    if (!err && !(prop = fdt_getprop(_fdt, nodeoffset, "ranges", RT_NULL)))
    {
        err = -RT_EINVAL;
    }

    return err;
}

static rt_err_t fdt_reserved_memory_reg(int nodeoffset, const char *uname)
{
    rt_err_t err = RT_EOK;

    rt_ubase_t base, size;
    const fdt32_t *prop;
    int len, t_len = (_root_addr_cells + _root_size_cells) * sizeof(fdt32_t);

    if ((prop = fdt_getprop(_fdt, nodeoffset, "reg", &len)))
    {
        if (len && len % t_len != 0)
        {
            LOG_E("Reserved memory: invalid reg property in '%s', skipping node", uname);
            err = -RT_EINVAL;
        }
        else
        {
            for (; len >= t_len; len -= t_len)
            {
                base = rt_fdt_next_cell(&prop, _root_addr_cells);
                size = rt_fdt_next_cell(&prop, _root_size_cells);

                if (!size)
                {
                    continue;
                }

                rt_bool_t is_nomap = fdt_getprop(_fdt, nodeoffset, "no-map", RT_NULL) ? RT_TRUE : RT_FALSE;
                base = rt_fdt_translate_address(_fdt, nodeoffset, base);

                rt_memblock_reserve_memory(fdt_get_name(_fdt, nodeoffset, RT_NULL),
                        base, base + size, is_nomap);
            }
        }
    }
    else
    {
        err = -RT_EEMPTY;
    }

    return err;
}

static void fdt_scan_reserved_memory(void)
{
    int nodeoffset, child;

    nodeoffset = fdt_path_offset(_fdt, "/reserved-memory");

    if (nodeoffset >= 0)
    {
        if (!fdt_reserved_mem_check_root(nodeoffset))
        {
            fdt_for_each_subnode(child, _fdt, nodeoffset)
            {
                rt_err_t err;
                const char *uname;

                if (!rt_fdt_device_is_available(_fdt, child))
                {
                    continue;
                }

                uname = fdt_get_name(_fdt, child, RT_NULL);
                err = fdt_reserved_memory_reg(child, uname);

                if (err == -RT_EEMPTY && fdt_getprop(_fdt, child, "size", RT_NULL))
                {
                    LOG_E("Allocating reserved memory in setup is not yet supported");
                }
            }
        }
        else
        {
            LOG_E("Reserved memory: unsupported node format, ignoring");
        }
    }
}

static rt_err_t fdt_scan_memory(void)
{
    int nodeoffset, no;
    rt_uint64_t base, size;
    rt_err_t err = -RT_EEMPTY;

    /* Process header /memreserve/ fields */
    for (no = 0; ; ++no)
    {
        fdt_get_mem_rsv(_fdt, no, &base, &size);

        if (!size)
        {
            break;
        }

        rt_memblock_reserve_memory("memreserve", base, base + size, MEMBLOCK_NONE);
    }

    fdt_for_each_subnode(nodeoffset, _fdt, 0)
    {
        int len;
        const fdt32_t *reg, *endptr;
        const char *name = fdt_get_name(_fdt, nodeoffset, RT_NULL);
        const char *type = fdt_getprop(_fdt, nodeoffset, "device_type", RT_NULL);

        if (!type || rt_strcmp(type, "memory"))
        {
            continue;
        }

        if (!rt_fdt_device_is_available(_fdt, nodeoffset))
        {
            continue;
        }

        reg = fdt_getprop(_fdt, nodeoffset, "reg", &len);

        if (!reg)
        {
            continue;
        }

        endptr = reg + (len / sizeof(fdt32_t));
        name = name ? name : "memory";

        while ((endptr - reg) >= (_root_addr_cells + _root_size_cells))
        {
            base = rt_fdt_next_cell(&reg, _root_addr_cells);
            size = rt_fdt_next_cell(&reg, _root_size_cells);

            if (!size)
            {
                continue;
            }

            bool is_hotpluggable = fdt_getprop(_fdt, nodeoffset, "hotpluggable", RT_NULL) ? RT_TRUE : RT_FALSE;
            err = rt_memblock_add_memory(name, base, base + size, is_hotpluggable);

            if (!err)
            {
                LOG_I("Memory node(%d) ranges: 0x%.*lx - 0x%.*lx%s", no, MIN_BIT, base, MIN_BIT, base + size, "");
            }
            else
            {
                LOG_W("Memory node(%d) ranges: 0x%.*lx - 0x%.*lx%s", no, MIN_BIT, base, MIN_BIT, base + size, " unable to record");
            }
        }
    }

    if (!err)
    {
        fdt_scan_reserved_memory();
    }

    return err;
}

rt_err_t rt_fdt_scan_memory(void)
{
    rt_err_t err = -RT_EEMPTY;

    if (_fdt)
    {
        err = fdt_scan_memory();
    }

    return err;
}

static rt_err_t fdt_scan_initrd(rt_uint64_t *ranges, const char *name, const char *oem)
{
    char    tmp_name[32];
    rt_err_t err = -RT_EEMPTY;

    if (_fdt && ranges)
    {
        int offset = fdt_path_offset(_fdt, "/chosen");

        if (offset >= 0)
        {
            int s_len, e_len;
            const fdt32_t *start = RT_NULL, *end = RT_NULL;

            rt_snprintf(tmp_name, sizeof(tmp_name), "%s,%s-start", oem, name);
            start = fdt_getprop(_fdt, offset, tmp_name, &s_len);
            rt_snprintf(tmp_name, sizeof(tmp_name), "%s,%s-end", oem, name);
            end = fdt_getprop(_fdt, offset, tmp_name, &e_len);

            if (start && end)
            {
                s_len /= sizeof(*start);
                e_len /= sizeof(*end);

                ranges[0] = rt_fdt_read_number(start, s_len);
                ranges[1] = rt_fdt_read_number(end, e_len);

                err = RT_EOK;
            }
        }

        if (err)
        {
            int len;
            const char *options, *bootargs = fdt_getprop(_fdt, offset, "bootargs", &len);

            rt_snprintf(tmp_name, sizeof(tmp_name), "%s=", name);

            if (bootargs && (options = rt_strstr(bootargs, tmp_name)))
            {
                rt_uint64_t value;

                options += rt_strlen(tmp_name) + sizeof("0x") - 1;
                err      = RT_EOK;

                for (int i = 0; i < 2 && !err; ++i)
                {
                    value = 0;

                    while (*options && *options != ',' && *options != ' ')
                    {
                        /* To lowercase or keep number */
                        char ch = *options | ' ';

                        value *= 16;

                        if (ch >= '0' && ch <= '9')
                        {
                            value += ch - '0';
                        }
                        else if (ch >= 'a' && ch <= 'f')
                        {
                            value += ch - 'a' + 10;
                        }
                        else
                        {
                            err = -RT_EINVAL;
                            break;
                        }

                        ++options;
                    }

                    ranges[i]  = value;
                    options   += sizeof(",0x") - 1;
                }

                /* This is initrd's size, convert to initrd's end */
                ranges[1] += ranges[0];
            }
        }

        if (!err)
        {
            rt_memblock_reserve_memory("initrd", ranges[0], ranges[1], MEMBLOCK_NONE);
        }
    }
    else if (!ranges)
    {
        err = -RT_EINVAL;
    }

    return err;
}

rt_err_t rt_fdt_scan_initrd(rt_uint64_t *ranges)
{
    rt_err_t err;

    err = fdt_scan_initrd(ranges, "cromfs", "rt-thread");

    if (err && err == -RT_EEMPTY)
    {
        err = fdt_scan_initrd(ranges, "initrd", "linux");
    }

    return err;
}


rt_err_t rt_fdt_model_dump(void)
{
    rt_err_t err = RT_EOK;
    int root = fdt_path_offset(_fdt, "/");

    if (root >= 0)
    {
        const char *mach_model = fdt_getprop(_fdt, root, "model", RT_NULL);

        if (!mach_model)
        {
            mach_model = fdt_getprop(_fdt, root, "compatible", RT_NULL);
        }

        LOG_I("Machine model: %s", mach_model ? mach_model : "<undefined>");
    }
    else
    {
        err = -RT_EEMPTY;
    }

    return err;
}

rt_weak rt_err_t rt_fdt_boot_dump(void)
{
    LOG_I("Booting RT-Thread on physical CPU 0x%x", rt_hw_cpu_id());

    return RT_EOK;
}

void rt_fdt_earlycon_output(const char *str)
{
    if (fdt_earlycon.console_putc)
    {
        while (*str)
        {
            fdt_earlycon.console_putc(fdt_earlycon.data, *str);

            if (*str == '\n')
            {
                /* Make sure return */
                fdt_earlycon.console_putc(fdt_earlycon.data, '\r');
            }

            ++str;
        }
    }
    else
    {
        /* We need a byte to save '\0' */
        while (*str && fdt_earlycon.msg_idx < sizeof(fdt_earlycon.msg) - 1)
        {
            fdt_earlycon.msg[fdt_earlycon.msg_idx++] = *str;

            ++str;
        }
        fdt_earlycon.msg[fdt_earlycon.msg_idx] = '\0';
    }
}

void rt_fdt_earlycon_kick(int why)
{
    if (fdt_earlycon.console_kick)
    {
        fdt_earlycon.console_kick(&fdt_earlycon, why);
    }

    if (why == FDT_EARLYCON_KICK_COMPLETED)
    {
        fdt_earlycon.console_putc = RT_NULL;

        if (fdt_earlycon.msg_idx)
        {
            fdt_earlycon.msg_idx = 0;

            /* Dump old messages */
            rt_kputs(fdt_earlycon.msg);
        }
    }
}

rt_err_t rt_fdt_scan_chosen_stdout(void)
{
    rt_err_t err = RT_EOK;

    int offset;
    int len, options_len = 0;
    const char *options = RT_NULL, *con_type = RT_NULL;

    rt_memset(&fdt_earlycon, 0, sizeof(fdt_earlycon) - sizeof(fdt_earlycon.msg));
    fdt_earlycon.nodeoffset = -1;

    offset = fdt_path_offset(_fdt, "/chosen");

    if (offset >= 0)
    {
        const char *stdout_path = RT_NULL;
        const char *bootargs = fdt_getprop(_fdt, offset, "bootargs", &len);

        if (bootargs && (options = rt_strstr(bootargs, "earlycon")))
        {
            options += sizeof("earlycon") - 1;

            if (*options == '\0' || *options == ' ')
            {
                stdout_path = fdt_getprop(_fdt, offset, "stdout-path", &len);

                if (stdout_path && len)
                {
                    const char *path_split = strchrnul(stdout_path, ':');

                    if (*path_split != '\0')
                    {
                        options = path_split + 1;
                    }

                    len = path_split - stdout_path;

                    /*
                     * Will try 2 styles:
                     *  1: stdout-path = "serialN:bbbbpnf";
                     *  2: stdout-path = "/serial-path";
                     */
                    offset = fdt_path_offset_namelen(_fdt, stdout_path, len);

                    if (offset < 0)
                    {
                        stdout_path = RT_NULL;
                    }
                }
                else if (*options == '=')
                {
                    ++options;
                }
                else
                {
                    /* Maybe is error in bootargs or it is a new arg */
                    options = RT_NULL;
                }

                if (!stdout_path)
                {
                    /* We couldn't know how to setup the earlycon */
                    options = RT_NULL;
                }
            }
            else
            {
                offset = -1;
            }

            if (options)
            {
                int type_len = 0;
                struct rt_fdt_earlycon_id *earlycon_id, *earlycon_id_end, *best_earlycon_id = RT_NULL;

                earlycon_id = (struct rt_fdt_earlycon_id *)&_earlycon_start;
                earlycon_id_end = (struct rt_fdt_earlycon_id *)&_earlycon_end;

                err = -RT_ENOSYS;

                /* Only "earlycon" in bootargs */
                if (stdout_path)
                {
                    const fdt32_t *reg;
                    options = RT_NULL;

                    if ((reg = fdt_getprop(_fdt, offset, "reg", RT_NULL)))
                    {
                        rt_uint64_t address;
                        int addr_cells = fdt_io_addr_cells(_fdt, offset);
                        int size_cells = fdt_io_size_cells(_fdt, offset);

                        address = rt_fdt_read_number(reg, addr_cells);
                        fdt_earlycon.mmio = rt_fdt_translate_address(_fdt, offset, address);
                        fdt_earlycon.size = rt_fdt_read_number(reg + addr_cells, size_cells);
                    }
                }
                else
                {
                    /* Pass split */
                    while (*options && (*options == '=' || *options == ' '))
                    {
                        ++options;
                    }

                    if (*options)
                    {
                        type_len = strchrnul(options, ',') - options;
                    }
                }

                if (options && *options && *options != ' ')
                {
                    options_len = strchrnul(options, ' ') - options;

                    rt_strncpy(fdt_earlycon.options, options, options_len);
                }

                /* console > stdout-path */
                for (int max_score = 0; earlycon_id < earlycon_id_end; ++earlycon_id)
                {
                    int score = 0;

                    if (type_len && earlycon_id->type)
                    {
                        if (!rt_strncmp(earlycon_id->type, options, type_len))
                        {
                            score += 1;
                        }
                    }

                    if (stdout_path && earlycon_id->compatible)
                    {
                        if (!fdt_node_check_compatible(_fdt, offset, earlycon_id->compatible))
                        {
                            score += 2;
                        }
                    }

                    if (score > max_score)
                    {
                        max_score = score;
                        best_earlycon_id = earlycon_id;

                        if (score == 3)
                        {
                            break;
                        }
                    }
                }

                if (best_earlycon_id && best_earlycon_id->setup)
                {
                    const char earlycon_magic[] = { 'O', 'F', 'W', '\0' };

                    if (!con_type)
                    {
                        con_type = best_earlycon_id->type;
                    }
                    fdt_earlycon.fdt = _fdt;
                    fdt_earlycon.nodeoffset = offset;

                    options = &fdt_earlycon.options[options_len + 1];
                    rt_strncpy((void *)options, earlycon_magic, RT_ARRAY_SIZE(earlycon_magic));

                    err = best_earlycon_id->setup(&fdt_earlycon, fdt_earlycon.options);

                    if (rt_strncmp(options, earlycon_magic, RT_ARRAY_SIZE(earlycon_magic)))
                    {
                        const char *option_start = options - 1;

                        while (option_start[-1] != '\0')
                        {
                            --option_start;
                        }

                        rt_memmove(fdt_earlycon.options, option_start, options - option_start);
                    }
                    else
                    {
                        fdt_earlycon.options[0] = '\0';
                    }
                }
            }
        }
        else
        {
            err = -RT_EEMPTY;
        }
    }
    else
    {
        err = -RT_EEMPTY;
    }

    if (fdt_earlycon.msg_idx)
    {
        fdt_earlycon.msg_idx = 0;

        rt_kputs(fdt_earlycon.msg);
    }

    rt_fdt_boot_dump();
    rt_fdt_model_dump();

    if (fdt_earlycon.mmio)
    {
        LOG_I("Earlycon: %s at MMIO/PIO %p (options '%s')",
                con_type, fdt_earlycon.mmio, fdt_earlycon.options);
    }

    return err;
}

rt_err_t rt_fdt_bootargs_select(const char *key, int index, const char **out_result)
{
    rt_err_t err;

    if (key && index >= 0 && out_result)
    {
        int offset = fdt_path_offset(_fdt, "/chosen");

        if (offset >= 0)
        {
            int len, key_len = rt_strlen(key);
            const char *bootargs = fdt_getprop(_fdt, offset, "bootargs", &len), *end;

            end = bootargs + len;
            err = -RT_EEMPTY;

            for (int i = 0; bootargs < end; ++i)
            {
                bootargs = rt_strstr(bootargs, key);

                if (!bootargs)
                {
                    break;
                }

                bootargs += key_len;

                if (i == index)
                {
                    *out_result = bootargs;

                    err = -RT_EOK;
                    break;
                }
            }
        }
        else
        {
            err = -RT_ERROR;
        }
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

static void system_node_init_flag(struct rt_ofw_node *np)
{
    if (np)
    {
        rt_ofw_node_set_flag(np, RT_OFW_F_READLY);
        rt_ofw_node_set_flag(np, RT_OFW_F_SYSTEM);
    }
}

rt_err_t rt_fdt_unflatten(void)
{
    rt_err_t err = RT_EOK;

    if (_fdt)
    {
        _phandle_min = OFW_PHANDLE_MAX;
        _phandle_max = OFW_PHANDLE_MIN;

        ofw_node_root = rt_fdt_unflatten_single(_fdt);

        if (ofw_node_root)
        {
            ofw_node_cpus = rt_ofw_find_node_by_path("/cpus");
            ofw_node_chosen = rt_ofw_find_node_by_path("/chosen");
            ofw_node_aliases = rt_ofw_find_node_by_path("/aliases");
            ofw_node_reserved_memory = rt_ofw_find_node_by_path("/reserved-memory");

            RT_ASSERT(ofw_node_cpus != RT_NULL);

            system_node_init_flag(ofw_node_root);
            system_node_init_flag(ofw_node_cpus);
            system_node_init_flag(ofw_node_chosen);
            system_node_init_flag(ofw_node_aliases);
            system_node_init_flag(ofw_node_reserved_memory);

            if (ofw_node_aliases)
            {
                err = ofw_alias_scan();
            }

            err = err ? : ofw_phandle_hash_reset(_phandle_min, _phandle_max);
        }
    }
    else
    {
        err = -RT_ERROR;
    }

    return err;
}

static rt_err_t fdt_unflatten_props(struct rt_ofw_node *np, int node_off)
{
    rt_err_t err = RT_EOK;
    struct rt_ofw_prop *prop;
    int prop_off = fdt_first_property_offset(_fdt, node_off);

    if (prop_off >= 0)
    {
        np->props = rt_malloc(sizeof(struct rt_ofw_prop));
    }

    prop = np->props;

    while (prop_off >= 0)
    {
        if (!prop)
        {
            err = -RT_ENOMEM;
            break;
        }

        prop->value = (void *)fdt_getprop_by_offset(_fdt, prop_off, &prop->name, &prop->length);

        if (prop->name && !rt_strcmp(prop->name, "name"))
        {
            np->name = prop->value;
        }

        prop_off = fdt_next_property_offset(_fdt, prop_off);

        if (prop_off < 0)
        {
            prop->next = RT_NULL;
            break;
        }

        prop->next = rt_malloc(sizeof(struct rt_ofw_prop));
        prop = prop->next;
    }

    return err;
}

static rt_err_t fdt_unflatten_single(struct rt_ofw_node *np, int node_off)
{
    int depth = 0;
    rt_err_t err = RT_EOK;
    struct rt_ofw_node *np_stack[OFW_NODE_MAX_DEPTH], *parent = RT_NULL;

    do {
        if (!np)
        {
            err = -RT_ENOMEM;
            break;
        }

        np->name = "<NULL>";
        np->full_name = fdt_get_name(_fdt, node_off, RT_NULL);
        np->phandle = fdt_get_phandle(_fdt, node_off);

        if (np->phandle >= OFW_PHANDLE_MIN)
        {
            if (np->phandle < _phandle_min)
            {
                _phandle_min = np->phandle;
            }

            if (np->phandle > _phandle_max)
            {
                _phandle_max = np->phandle;
            }
        }

        if ((err = fdt_unflatten_props(np, node_off)))
        {
            break;
        }

        np->parent = parent;

        rt_ref_init(&np->ref);
        np->flags = 0;

        if (!np->child)
        {
            /* Save node offset temp */
            rt_ofw_data(np) = (void *)(rt_ubase_t)node_off;

            /* Check children */
            node_off = fdt_first_subnode(_fdt, node_off);

            if (node_off >= 0)
            {
                parent = np;

                np_stack[depth++] = np;

                np->child = rt_calloc(1, sizeof(struct rt_ofw_node));
                np = np->child;

                continue;
            }
        }

        while (depth >= 0)
        {
            /* Restore node offset temp */
            node_off = (long)rt_ofw_data(np);
            rt_ofw_data(np) = RT_NULL;

            /* Next step */
            node_off = fdt_next_subnode(_fdt, node_off);

            if (node_off < 0)
            {
                np->sibling = RT_NULL;

                np = np_stack[--depth];
            }
            else
            {
                parent = np->parent;

                np->sibling = rt_calloc(1, sizeof(struct rt_ofw_node));
                np = np->sibling;

                break;
            }
        }
    } while (depth >= 0);

    return err;
}

struct rt_ofw_node *rt_fdt_unflatten_single(void *fdt)
{
    int root_off;
    struct fdt_info *header;
    struct rt_ofw_node *root = RT_NULL;

    if (fdt && (root_off = fdt_path_offset(fdt, "/")) >= 0)
    {
        root = rt_calloc(1, sizeof(struct fdt_info) + sizeof(struct rt_ofw_node));
    }

    if (root)
    {
        header = (void *)root + sizeof(struct rt_ofw_node);

        rt_strncpy(header->name, "/", sizeof("/"));

        header->fdt = fdt;

        header->rsvmap = (struct fdt_reserve_entry *)((void *)fdt + fdt_off_mem_rsvmap(fdt));
        header->rsvmap_nr = fdt_num_mem_rsv(fdt);

        if (!fdt_unflatten_single(root, root_off))
        {
            root->name = (const char *)header;
        }
        else
        {
            rt_ofw_node_destroy(root);

            root = RT_NULL;
        }
    }

    return root;
}
