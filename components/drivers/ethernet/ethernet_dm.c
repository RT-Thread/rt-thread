/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-25     GuEe-GUI     first version
 */

#include <drivers/core/dm.h>

#include "ethernet_dm.h"

static rt_uint32_t _qrand32(rt_uint32_t seed)
{
    rt_uint32_t ret;
    static rt_uint32_t next = 1;

    next = next * 1103515245 + 12345;

    ret = (rt_uint32_t)(next / 65536) % 32768;

    if (seed)
    {
        ret *= seed;
    }

    return ret;
}

void ethernet_random_addr(struct eth_device *eth, rt_uint8_t *addr)
{
    rt_tick_t tick = rt_tick_get();
    rt_uint32_t rand = (_qrand32(tick) << 16) | _qrand32(tick);
    const char *name = rt_dm_dev_get_name(&eth->parent);

    addr[5] = ((rt_uint8_t *)&rand)[3];
    addr[4] = ((rt_uint8_t *)&rand)[2];
    addr[3] = name[0] & 0xf;
    addr[2] = name[1] & 0xf;
    addr[1] = ((rt_uint8_t *)&rand)[1];
    addr[0] = ((rt_uint8_t *)&rand)[0];

    addr[0] &= 0xfe;    /* Clear multicast bit */
    addr[0] |= 0x02;    /* Set local assignment bit (IEEE802) */
}
