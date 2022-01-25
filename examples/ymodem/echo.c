/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <ymodem.h>

static rt_device_t _odev;

static enum rym_code _rym_echo_data(
        struct rym_ctx *ctx,
        rt_uint8_t *buf,
        rt_size_t len)
{
    rt_device_write(_odev, 0, buf, len);
    return RYM_CODE_ACK;
}

rt_err_t rym_cat_to_dev(rt_device_t idev, rt_device_t odev)
{
    struct rym_ctx rctx;
    rt_err_t res;
    _odev = odev;

    rt_kprintf("entering RYM mode\n");
    odev->flag &= ~RT_DEVICE_FLAG_STREAM;
    res = rt_device_open(odev, 0);
    if (res != RT_EOK)
    {
        rt_kprintf("open output device error: 0x%x", -res);
        return res;
    }
    res = rym_recv_on_device(&rctx, idev, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                             RT_NULL, _rym_echo_data, RT_NULL, 1000);
    rt_device_close(_odev);
    rt_kprintf("leaving RYM mode with code %X\n", res);
    return res;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void rym_cat_vcom(void)
{
    extern rt_err_t rym_cat_to_dev(rt_device_t idev, rt_device_t odev);
    rt_device_t idev, odev;

    rt_thread_delay(RT_TICK_PER_SECOND*10);

    idev = rt_device_find("uart1");
    if (!idev)
    {
        rt_kprintf("could not find idev\n");
    }
    odev = rt_device_find("vcom");
    if (!odev)
    {
        rt_kprintf("could not find odev\n");
    }

    rym_cat_to_dev(idev, odev);
}
FINSH_FUNCTION_EXPORT(rym_cat_vcom, test the YModem);
#endif

