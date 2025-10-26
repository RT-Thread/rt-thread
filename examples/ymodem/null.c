/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <ymodem.h>

static enum rym_code _rym_dummy_write(
        struct rym_ctx *ctx,
        rt_uint8_t *buf,
        rt_size_t len)
{
    return RYM_CODE_ACK;
}

#ifdef RT_USING_FINSH
rt_err_t rym_null(char *devname)
{
    struct rym_ctx rctx;
    rt_device_t dev = rt_device_find(devname);
    if (!dev)
    {
        rt_kprintf("could not find device %s\n", devname);
        return -1;
    }

    return rym_recv_on_device(&rctx, dev, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              RT_NULL, _rym_dummy_write, RT_NULL, 1000);
}
#endif

