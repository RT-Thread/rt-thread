/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-16     GuEe-GUI     first version
 */

#include <rtatomic.h>
#include <drivers/serial_dm.h>

int serial_dev_set_name(struct rt_serial_device *sdev)
{
    int id = -1;
    static int uid_min = -1;
    static volatile rt_atomic_t uid = 0;

    RT_ASSERT(sdev != RT_NULL);

#ifdef RT_USING_OFW
    if (sdev->parent.ofw_node)
    {
        id = rt_ofw_get_alias_id(sdev->parent.ofw_node, "serial");

        if (id < 0)
        {
            id = rt_ofw_get_alias_id(sdev->parent.ofw_node, "uart");
        }

        if (uid_min < 0)
        {
            uid_min = rt_ofw_get_alias_last_id("serial");

            if (uid_min < 0)
            {
                uid_min = rt_ofw_get_alias_last_id("uart");
            }

            uid_min = uid_min < 0 ? 0 : (uid_min + 1);

            rt_hw_atomic_store(&uid, uid_min);
        }
    }
#endif

    if (id < 0)
    {
        id = (int)rt_hw_atomic_add(&uid, 1);
    }

    return rt_dm_dev_set_name(&sdev->parent, "uart%u", id);
}

void *serial_base_from_args(char *str)
{
    rt_ubase_t base = 0;

    while (*str && !(*str == 'x' || *str == 'X'))
    {
        ++str;
    }
    ++str;

    /* The str may get from bootargs that we need check it */
    while (*str)
    {
        if ((*str >= 'a' && *str <= 'f') || (*str >= 'A' && *str <= 'F'))
        {
            base = (base << 4) | (((*str | ' ') - 'a') + 10);
        }
        else if (*str >= '0' && *str <= '9')
        {
            base = (base << 4) | (*str - '0');
        }
        else break;

        ++str;
    }

    return (void *)base;
}

struct serial_configure serial_cfg_from_args(char *_str)
{
    char *str = _str;
    struct serial_configure cfg = RT_SERIAL_CONFIG_DEFAULT;

    /* Format baudrate/parity/bits/flow (BBBBPNF), Default is 115200n8 */
    if (str && *str)
    {
        rt_uint32_t baudrate = 0;

        /* BBBB is the speed */
        while (*str && (*str >= '0' && *str <= '9'))
        {
            baudrate *= 10;
            baudrate += *str - '0';
            ++str;
        }

        if (baudrate)
        {
            cfg.baud_rate = baudrate;
        }

        /* P is parity (n/o/e) */
        switch (*str)
        {
        case 'n':
            cfg.parity = PARITY_NONE;
            break;
        case 'o':
            cfg.parity = PARITY_ODD;
            break;
        case 'e':
            cfg.parity = PARITY_EVEN;
            break;
        default:
            --str;
            break;
        }
        ++str;

        /* N is number of bits */
        if (*str && (*str >= '0' && *str <= '9'))
        {
            cfg.data_bits = *str - '0';
            ++str;
        }

        /* F is flow ontrol ('r' for RTS) */
        if (*str)
        {
            cfg.flowcontrol = (*str == 'r' ? RT_SERIAL_FLOWCONTROL_CTSRTS : RT_SERIAL_FLOWCONTROL_NONE);
            ++str;
        }

    #ifdef RT_USING_OFW
        if (*str == '\0')
        {
            const char earlycon_magic[] = { 'O', 'F', 'W', '\0' };

            if (!rt_strcmp(++str, earlycon_magic))
            {
                /* Is OFW earlycon, we should ACK it */
                rt_memset(str, 0, RT_ARRAY_SIZE(earlycon_magic));
            }
        }
    #endif
    }

    return cfg;
}
