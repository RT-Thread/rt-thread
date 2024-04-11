/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-25     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/platform.h>
#include <drivers/core/bus.h>
#include <drivers/serial_dm.h>

#define DBG_TAG "rtdm.ofw"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "ofw_internal.h"

struct rt_ofw_stub *rt_ofw_stub_probe_range(struct rt_ofw_node *np,
        const struct rt_ofw_stub *stub_start, const struct rt_ofw_stub *stub_end)
{
    const struct rt_ofw_stub *stub = RT_NULL;

    if (np && stub_start && stub_end &&
        !rt_ofw_node_test_flag(np, RT_OFW_F_READLY) &&
        !rt_ofw_node_test_flag(np, RT_OFW_F_SYSTEM))
    {
        struct rt_ofw_prop *compat_prop = rt_ofw_get_prop(np, "compatible", RT_NULL);

        if (compat_prop)
        {
            rt_ofw_foreach_stub(stub, stub_start, stub_end)
            {
                struct rt_ofw_node_id *id;

                if (!stub->ids)
                {
                    continue;
                }

                id = rt_ofw_prop_match(compat_prop, stub->ids);

                if (id)
                {
                    if (!stub->handler(np, id))
                    {
                        rt_ofw_node_set_flag(np, RT_OFW_F_READLY);
                    }

                    break;
                }
            }
        }
    }

    return (struct rt_ofw_stub *)stub;
}

static const char *ofw_console_serial_find(char *dst_con, struct rt_ofw_node *np)
{
    rt_object_t rt_obj = RT_NULL;
    const char *ofw_name = RT_NULL;
    struct rt_serial_device *rt_serial = rt_ofw_data(np);

    if (rt_serial)
    {
        rt_obj = &rt_serial->parent.parent;
    }

    /*
     * This is a dangerous behavior because rt_data can be modified by other
     * user. But fortunately, we can check if the rt_data is a rt_device or
     * rt_serial_device.
     */
    if (rt_obj && rt_object_get_type(rt_obj) == RT_Object_Class_Device &&
        rt_serial->parent.type == RT_Device_Class_Char)
    {
        ofw_name = np->full_name;
        rt_strncpy(dst_con, rt_obj->name, RT_NAME_MAX);
    }

    return ofw_name;
}

static int tty_device_compare(rt_device_t dev, void *data)
{
    rt_ubase_t *args_list;
    char *dst_con;
    const char *console, **ofw_name;
    const struct rt_ofw_node_id *id;
    struct rt_platform_device *pdev;
    int *tty_idx, tty_id, tty_name_len;

    pdev = rt_container_of(dev, struct rt_platform_device, parent);
    id = pdev->id;

    args_list = data;
    tty_idx = (int *)args_list[0];
    tty_id = args_list[1];
    console = (const char *)args_list[2];
    tty_name_len = args_list[3];
    dst_con = (char *)args_list[4];
    ofw_name = (const char **)args_list[5];

    if (id && id->type[0] && !strncmp(id->type, console, tty_name_len))
    {
        if (*tty_idx == tty_id)
        {
            *ofw_name = ofw_console_serial_find(dst_con, pdev->parent.ofw_node);

            return RT_EOK;
        }

        ++*tty_idx;
    }

    return -RT_EEMPTY;
}

static const char *ofw_console_tty_find(char *dst_con, const char *con)
{
    const char *ofw_name = RT_NULL;
    static rt_bus_t platform_bus = RT_NULL;

    if (!platform_bus)
    {
        platform_bus = rt_bus_find_by_name("platform");
    }

    if (platform_bus)
    {
        rt_ubase_t args_list[6];
        const char *console = con;
        int tty_idx = 0, tty_id = 0, tty_name_len;

        con += sizeof("tty") - 1;

        while (*con && !(*con >= '0' && *con <= '9'))
        {
            ++con;
        }

        tty_name_len = con - console;

        while (*con && *con >= '0' && *con <= '9')
        {
            tty_id *= 10;
            tty_id += *con - '0';

            ++con;
        }

        args_list[0] = (rt_ubase_t)&tty_idx;
        args_list[1] = tty_id;
        args_list[2] = (rt_ubase_t)console;
        args_list[3] = tty_name_len;
        args_list[4] = (rt_ubase_t)dst_con;
        args_list[5] = (rt_ubase_t)&ofw_name;
        rt_bus_for_each_dev(platform_bus, &args_list, tty_device_compare);
    }

    return ofw_name;
}

rt_err_t rt_ofw_console_setup(void)
{
    rt_err_t err = -RT_ENOSYS;
    char con_name[RT_NAME_MAX], *options = RT_NULL;
    const char *ofw_name = RT_NULL, *stdout_path, *con;

    /* chosen.console > chosen.stdout-path > RT_CONSOLE_DEVICE_NAME */

    con = rt_ofw_bootargs_select("console=", 0);

    for (int i = 1; con; ++i)
    {
        if (!rt_strncmp(con, "uart", sizeof("uart") - 1))
        {
            rt_strncpy(con_name, con, RT_NAME_MAX);

            err = RT_EOK;
            break;
        }
        else if (!rt_strncmp(con, "tty", sizeof("tty") - 1))
        {
            ofw_name = ofw_console_tty_find(con_name, con);

            if (ofw_name)
            {
                const char *ch = con;

                while (*ch && *ch != ' ')
                {
                    if (*ch++ == ',')
                    {
                        options = (char *)ch;

                        break;
                    }
                }

                err = RT_EOK;
                break;
            }
        }

        con = rt_ofw_bootargs_select("console=", i);
    }

    if (err == -RT_ENOSYS && !rt_ofw_prop_read_string(ofw_node_chosen, "stdout-path", &stdout_path))
    {
        struct rt_ofw_node *stdout_np = rt_ofw_find_node_by_path(stdout_path);

        if (stdout_np && (ofw_name = ofw_console_serial_find(con_name, stdout_np)))
        {
            err = RT_EOK;
        }
    }

    if (err == -RT_ENOSYS)
    {
        rt_device_t serial = rt_device_find(RT_CONSOLE_DEVICE_NAME);

        if (serial)
        {
            ofw_name = rt_ofw_node_full_name(serial->ofw_node);

            con = RT_CONSOLE_DEVICE_NAME;
        }
        else
        {
            LOG_W("Console will probably fail to setup");
        }
    }
    else
    {
        con = con_name;
    }

    rt_console_set_device(con);

    if (options)
    {
        rt_device_t con_dev = rt_console_get_device();

        if (con_dev)
        {
            struct serial_configure con_conf = serial_cfg_from_args(options);

            rt_device_control(con_dev, RT_DEVICE_CTRL_CONFIG, &con_conf);
        }
    }

    rt_fdt_earlycon_kick(FDT_EARLYCON_KICK_COMPLETED);

    LOG_I("Console: %s (%s)", con, ofw_name ? ofw_name : "<unknown>");

    return err;
}

const char *rt_ofw_bootargs_select(const char *key, int index)
{
    const char *value = RT_NULL;

    if (key && index >= 0)
    {
        static char **values = RT_NULL;
        static rt_size_t bootargs_nr = 1;
        const char *bootargs = RT_NULL, *ch;

        if (bootargs_nr && !values &&
            (bootargs_nr = 0, !rt_ofw_prop_read_string(ofw_node_chosen, "bootargs", &bootargs)) &&
            bootargs && (bootargs = rt_strdup(bootargs)))
        {
            rt_bool_t quotes = RT_TRUE;
            rt_size_t length = rt_strlen(bootargs);
            const char *bootargs_end = bootargs + length;

            for (ch = bootargs; ch < bootargs_end; ++ch)
            {
                if (*ch == '"')
                {
                    quotes = !quotes;
                    continue;
                }

                if (*ch != ' ' || !quotes)
                {
                    continue;
                }

                ++bootargs_nr;

                while (*ch == ' ' && ch < bootargs_end)
                {
                    *(char *)ch++ = '\0';
                }
                --ch;
            }

            if (bootargs_nr)
            {
                /* last arg */
                ++bootargs_nr;
                values = rt_malloc(sizeof(char *) * bootargs_nr);
            }

            if (values)
            {
                int idx = 0;

                for (int i = 0; i < length; ++i)
                {
                    for (; i < length && !bootargs[i]; ++i)
                    {
                    }

                    if (i < length)
                    {
                        values[idx++] = (char *)&bootargs[i];
                    }

                    for (; i < length && bootargs[i]; ++i)
                    {
                    }
                }
            }
            else
            {
                rt_free((char *)bootargs);
            }
        }

        if (values)
        {
            int keylen = rt_strlen(key);

            for (int idx = 0, count = 0; idx < bootargs_nr; ++idx)
            {
                if (!rt_strncmp(values[idx], key, keylen))
                {
                    if (count == index)
                    {
                        value = values[idx] + keylen;

                        break;
                    }

                    ++count;
                }
            }
        }
    }

    return value;
}

#ifdef RT_USING_CONSOLE
static void dts_put_depth(int depth)
{
    while (depth --> 0)
    {
        rt_kputs("    ");
    }
}

static rt_bool_t dts_test_string_list(const void *value, int size)
{
    const char *str, *str_start, *str_end;

    if (!size)
    {
        return RT_FALSE;
    }

    str = value;

    /* String end with '\0' */
    if (str[size - 1] != '\0')
    {
        return RT_FALSE;
    }

    /* Get string list end */
    str_end = str + size;

    while (str < str_end)
    {
        str_start = str;
        /* Before string list end, not '\0' and a printable characters */
        while (str < str_end && *str && ((unsigned char)*str >= ' ' && (unsigned char)*str <= '~'))
        {
            ++str;
        }

        /* Not zero, or not increased */
        if (*str != '\0' || str == str_start)
        {
            return RT_FALSE;
        }

        /* Next string */
        ++str;
    }

    return RT_TRUE;
}

static void ofw_node_dump_dts(struct rt_ofw_node *np, rt_bool_t sibling_too)
{
    int depth = 0;
    struct rt_ofw_prop *prop;
    struct rt_ofw_node *org_np = np;

    while (np)
    {
        dts_put_depth(depth);
        rt_kputs(np->full_name);
        rt_kputs(" {\n");

        prop = np->props;

        /* Print prop start */
        ++depth;

        while (prop)
        {
            dts_put_depth(depth);

            rt_kputs(prop->name);

            /* Have value? */
            if (prop->length > 0)
            {
                int length = prop->length;
                void *value = prop->value;

                rt_kputs(" = ");

                if (dts_test_string_list(value, length))
                {
                    /* String list */
                    char *str = value;

                    do {
                        rt_kputs("\"");
                        rt_kputs(str);
                        rt_kputs("\", ");

                        str += rt_strlen(str) + 1;

                    } while (str < (char *)value + length);

                    rt_kputs("\b\b");
                }
                else if ((length % 4) == 0)
                {
                    /* u32 data in <?> */
                    fdt32_t *cell = value;

                    rt_kputs("<");

                    length /= 4;

                    for (int i = 0; i < length; ++i)
                    {
                        rt_kprintf("0x%02x ", fdt32_to_cpu(cell[i]));
                    }

                    rt_kputs("\b>");
                }
                else
                {
                    /* Byte data in [?] */
                    rt_uint8_t *byte = value;

                    rt_kputs("[");

                    for (int i = 0; i < length; ++i)
                    {
                       rt_kprintf("%02x ", *byte++);
                    }

                    rt_kputs("\b]");
                }
            }

            rt_kputs(";\n");

            prop = prop->next;
        }

        --depth;
        /* Print prop end */

        if (np->child)
        {
            rt_kputs("\n");
            np = np->child;
            ++depth;
        }
        else
        {
            dts_put_depth(depth);
            rt_kputs("};\n");

            if (!sibling_too && org_np == np)
            {
                break;
            }

            while (np->parent && !np->sibling)
            {
                np = np->parent;
                --depth;

                if (depth >= 0)
                {
                    dts_put_depth(depth);
                    rt_kputs("};\n");
                }
            }

            if (!sibling_too && org_np == np)
            {
                break;
            }

            np = np->sibling;

            if (np)
            {
                rt_kputs("\n");
            }
        }
    }
}

void rt_ofw_node_dump_dts(struct rt_ofw_node *np, rt_bool_t sibling_too)
{
    if (np)
    {
        if (!rt_strcmp(np->name, "/"))
        {
            struct fdt_info *header = (struct fdt_info *)np->name;
            struct fdt_reserve_entry *rsvmap = header->rsvmap;

            rt_kprintf("/dts-v%x/;\n\n", fdt_version(header->fdt));

            for (int i = header->rsvmap_nr - 1; i >= 0; --i)
            {
                rt_kprintf("/memreserve/\t%p %p;\n",
                        ofw_static_cast(rt_size_t, fdt64_to_cpu(rsvmap->address)),
                        ofw_static_cast(rt_size_t, fdt64_to_cpu(rsvmap->size)));

                ++rsvmap;
            }

            rt_kputs(np->name);
        }

        ofw_node_dump_dts(np, sibling_too);
    }
}

#ifdef RT_USING_MSH
static void ofw_dts(int argc, char**argv)
{
    if (ofw_node_root)
    {
        if (argc == 1)
        {
            rt_ofw_node_dump_dts(ofw_node_root, RT_TRUE);
        }
        else if (argv[1][0] == '/')
        {
            struct rt_ofw_node *np = rt_ofw_find_node_by_path(argv[1]);

            if (np)
            {
                rt_ofw_node_dump_dts(np, RT_FALSE);
            }
            else
            {
                rt_kprintf("%s not found.\n", argv[1]);
            }
        }
        else if (argc >= 2 && !rt_strcmp(argv[1], "list") && argv[2][0] == '/')
        {
            struct rt_ofw_node *np = rt_ofw_find_node_by_path(argv[2]);

            if (np)
            {
                const char *split = np == ofw_node_root ? "" : "/";

                np = np->child;

                while (np)
                {
                    rt_kprintf("%s%s%s\n", argv[2], split, np->full_name);
                    np = np->sibling;
                }
            }
            else
            {
                rt_kprintf("%s not found.\n", argv[2]);
            }
        }
        else
        {
            rt_kprintf("Usage: %s {list} {path}\n", __func__);
        }
    }
    else
    {
        rt_kprintf("\"/\" path not found.");
    }
}
MSH_CMD_EXPORT(ofw_dts, dump the dts or node for this platform);
#endif /* RT_USING_MSH */
#endif /* RT_USING_CONSOLE */
