/*
 * Channel on VMM Bus
 *
 * COPYRIGHT (C) 2013-2015, Shanghai Real-Thread Technology Co., Ltd
 *      http://www.rt-thread.com
 *
 *  This file is part of RT-Thread (http://www.rt-thread.org)
 *
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-11-04     Grissiom     add comment
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "vbus.h"

static void _rx_indicate(void *ctx)
{
    rt_device_t dev = ctx;

    if (dev->rx_indicate)
        dev->rx_indicate(dev, 0);
}

static void _tx_complete(void *ctx)
{
    rt_device_t dev = ctx;

    if (dev->tx_complete)
        dev->tx_complete(dev, 0);
}

static rt_err_t _open(rt_device_t dev, rt_uint16_t oflag)
{
    int chnr;
    struct rt_vbus_dev *vdev = dev->user_data;

    if (vdev->chnr)
        return RT_EOK;

    /* FIXME: request the same name for twice will crash */
    chnr = rt_vbus_request_chn(&vdev->req, RT_WAITING_FOREVER);
    if (chnr < 0)
        return chnr;

    vdev->chnr = chnr;
    rt_vbus_register_listener(chnr, RT_VBUS_EVENT_ID_RX, _rx_indicate, dev);
    rt_vbus_register_listener(chnr, RT_VBUS_EVENT_ID_TX, _tx_complete, dev);

    return RT_EOK;
}

static rt_err_t _close(rt_device_t dev)
{
    struct rt_vbus_dev *vdev = dev->user_data;

    RT_ASSERT(vdev->chnr != 0);

    rt_vbus_close_chn(vdev->chnr);
    vdev->chnr = 0;

    return RT_EOK;
}

static rt_size_t _read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_size_t outsz = 0;
    struct rt_vbus_dev *vdev = dev->user_data;

    RT_ASSERT(vdev->chnr != 0);

    if (vdev->act == RT_NULL)
    {
        vdev->act = rt_vbus_data_pop(vdev->chnr);
        vdev->pos = 0;
    }

    while (1)
    {
        rt_err_t err;

        while (vdev->act)
        {
            rt_size_t cpysz;

            if (size - outsz > vdev->act->size - vdev->pos)
                cpysz = vdev->act->size - vdev->pos;
            else
                cpysz = size - outsz;

            rt_memcpy((char*)buffer + outsz, ((char*)(vdev->act+1)) + vdev->pos, cpysz);
            vdev->pos += cpysz;

            outsz += cpysz;
            if (outsz == size)
            {
                return outsz;
            }
            else if (outsz > size)
                RT_ASSERT(0);

            /* free old and get new */
            rt_free(vdev->act);
            vdev->act = rt_vbus_data_pop(vdev->chnr);
            vdev->pos = 0;
        }

        /* TODO: We don't want to touch the rx_indicate here. But this lead to
         * some duplication. Maybe we should find a better way to handle this.
         */
        if (rt_interrupt_get_nest() == 0)
        {
            err = rt_vbus_listen_on(vdev->chnr, RT_WAITING_FOREVER);
        }
        else
        {
            err = rt_vbus_listen_on(vdev->chnr, 0);
        }
        if (err != RT_EOK)
        {
            rt_set_errno(err);
            return outsz;
        }
        vdev->act = rt_vbus_data_pop(vdev->chnr);
        vdev->pos = 0;
    }
}

static rt_size_t _write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_err_t err;
    struct rt_vbus_dev *vdev = dev->user_data;

    RT_ASSERT(vdev->chnr != 0);

    if (rt_interrupt_get_nest() == 0)
    {
        /* Thread context. */
        err = rt_vbus_post(vdev->chnr, vdev->req.prio,
                           buffer, size, RT_WAITING_FOREVER);
    }
    else
    {
        /* Interrupt context. */
        err = rt_vbus_post(vdev->chnr, vdev->req.prio,
                           buffer, size, 0);
    }

    if (err)
    {
        rt_set_errno(err);
        return 0;
    }

    return size;
}

rt_err_t  _control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
    RT_ASSERT(dev);

    switch (cmd) {
    case VBUS_IOC_LISCFG: {
        struct rt_vbus_dev *vdev = dev->user_data;
        struct rt_vbus_dev_liscfg *liscfg = args;

        RT_ASSERT(vdev->chnr != 0);
        if (!liscfg)
            return -RT_ERROR;

        rt_vbus_register_listener(vdev->chnr, liscfg->event,
                                  liscfg->listener, liscfg->ctx);
        return RT_EOK;
    }
        break;
#ifdef RT_VBUS_USING_FLOW_CONTROL
    case VBUS_IOCRECV_WM: {
        struct rt_vbus_dev *vdev = dev->user_data;
        struct rt_vbus_wm_cfg *cfg;

        RT_ASSERT(vdev->chnr != 0);

        if (!args)
            return -RT_ERROR;

        cfg = (struct rt_vbus_wm_cfg*)args;
        if (cfg->low > cfg->high)
            return -RT_ERROR;

        rt_vbus_set_recv_wm(vdev->chnr, cfg->low, cfg->high);
        return RT_EOK;
    }
        break;
    case VBUS_IOCPOST_WM: {
        struct rt_vbus_dev *vdev = dev->user_data;
        struct rt_vbus_wm_cfg *cfg;

        RT_ASSERT(vdev->chnr != 0);

        if (!args)
            return -RT_ERROR;

        cfg = (struct rt_vbus_wm_cfg*)args;
        if (cfg->low > cfg->high)
            return -RT_ERROR;

        rt_vbus_set_post_wm(vdev->chnr, cfg->low, cfg->high);
        return RT_EOK;
    }
        break;
#endif
    default:
        break;
    };

    return -RT_ENOSYS;
}

rt_uint8_t rt_vbus_get_chnnr(rt_device_t dev)
{
    struct rt_vbus_dev *vdev;

    RT_ASSERT(dev);

    vdev = dev->user_data;

    return vdev->chnr;
}

void rt_vbus_chnx_register_disconn(rt_device_t dev,
                                   rt_vbus_event_listener indi,
                                   void *ctx)
{
    struct rt_vbus_dev *vdev = dev->user_data;

    RT_ASSERT(vdev->chnr != 0);

    if (vdev)
        rt_vbus_register_listener(vdev->chnr, RT_VBUS_EVENT_ID_DISCONN,
                                  indi, ctx);
}

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

extern struct rt_vbus_dev rt_vbus_chn_devx[];
static struct rt_device _devx[32];

rt_err_t rt_vbus_chnx_init(void)
{
    int i;
    struct rt_vbus_dev *p;

    for (i = 0,                   p = rt_vbus_chn_devx;
         i < ARRAY_SIZE(_devx) && p->req.name;
         i++,                     p++)
    {
        _devx[i].type      = RT_Device_Class_Char;
        _devx[i].open      = _open;
        _devx[i].close     = _close;
        _devx[i].read      = _read;
        _devx[i].write     = _write;
        _devx[i].control   = _control;
        _devx[i].user_data = p;
        rt_device_register(&_devx[i], p->req.name, RT_DEVICE_FLAG_RDWR);
    }

    return RT_EOK;
}
