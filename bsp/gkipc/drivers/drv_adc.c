/*
 * File      : drv_adc.c
 * This file is part of GK710X BSP for RT-Thread distribution.
 *
 * Copyright (c) 2017 GOKE Microelectronics Co., Ltd.
 * All rights reserved
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
 *  Visit http://www.goke.com to get contact with Goke.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "drv_adc.h"
#ifdef RT_USING_ADC
#include "gtypes.h"
#include "gd_adc.h"
#include "platform.h"

#include <rtdef.h>
#include <rtthread.h>

#define GK_TEST_ADC

#define IOCTL_GET_ADC_DATA 1
#define IOCTL_ADC_POWER_DOWN 0xff
#define ADC_WRAP_BASE (0xf1200000)
#define ADC_IRQn (23)
#define ADC_MAX_CONTROLLER (1)
#define ADC_STATUS_COLESD (0)
#define ADC_STATUS_OPEN (1)

static rt_err_t gk_adc_read_data(struct wrap_adc_obj *adc, rt_uint32_t channel,
                               rt_uint32_t *buf)
{
    rt_err_t ret = RT_EOK;

    ret = GD_ADC_Read((GD_HANDLE*)&(adc->handle), buf);

    return ret;
}

static rt_err_t gk_adc_init(rt_device_t dev)
{
    rt_err_t ret = RT_EOK;

    ret = (rt_err_t)GD_ADC_Init();

    return ret;
}

static rt_err_t gk_adc_open(rt_device_t dev, rt_uint16_t oflag)
{
    rt_err_t ret = RT_EOK;
    GD_ADC_OPEN_PARAMS_S openParams;

    struct wrap_adc_obj *adc_pri = (struct wrap_adc_obj *)dev->user_data;
    rt_memset(&openParams, 0, sizeof(GD_ADC_OPEN_PARAMS_S));
    openParams.channel = adc_pri->active_channel_no;

    ret = (rt_err_t)GD_ADC_Open(&openParams, (GD_HANDLE*)&(adc_pri->handle));

    return ret;
}

static rt_err_t gk_adc_close(rt_device_t dev)
{
    rt_err_t ret = RT_EOK;

    struct wrap_adc_obj *adc_pri = (struct wrap_adc_obj *)dev->user_data;

    ret = (rt_err_t)GD_ADC_Close((GD_HANDLE*)(adc_pri->handle));

    return ret;
}

static rt_err_t gk_adc_ioctl(rt_device_t dev, int cmd, void *arg)
{
    rt_uint32_t control_reg;
    struct wrap_adc_obj *adc_pri = (struct wrap_adc_obj *)dev->user_data;
    rt_uint32_t ad_data;

    ADC_INFO *adc_info = (ADC_INFO *)arg;
    rt_err_t ret;

    switch (cmd)
    {
        case ADC_CMD_READ_RAW_DATA:
            ret = gk_adc_read_data(adc_pri, adc_info->channel, &ad_data);
            if (ret != RT_EOK)
            {
                return ret;
            }

            adc_info->adc_data = ad_data;

            break;

        case ADC_CMD_DISABLE:
            gk_adc_close(dev);

            break;

        default:
            rt_kprintf("wrong para...\n");
            return RT_EIO;
    }

    return RT_EOK;
}

int gk_adc_probe(void *priv_data)
{
    rt_device_t adc_dev;
    // check if the hw is init already...
    // caution this is a read only data...if the driver want to use.malloc and
    // copy it..
    struct wrap_adc_obj *adc_obj = (struct wrap_adc_obj *)priv_data;
    if (adc_obj->init_flag == ADC_INIT_ALREADY) return RT_EFULL;

    // malloc a rt device..
    adc_dev = RT_KERNEL_MALLOC(sizeof(struct rt_device));
    if (!adc_dev)
    {
        return RT_ENOMEM;
    }
    rt_memset(adc_dev, 0, sizeof(struct rt_device));
    rt_kprintf("id:%d\n", adc_obj->id);

    // bind rtdev to obj data...
    // caution ...this is used to free mem when exit....
    // free step:1:get adc obj...2:free adc_obj->rt_dev->user_data..3:free
    // adc_obj->rt_dev 4:adc_obj->rt_dev = NULL
    adc_obj->rt_dev = adc_dev;

    // malloc a private data adc use only...copy data from platform...
    struct wrap_adc_obj *adc_pri =
        RT_KERNEL_MALLOC(sizeof(struct wrap_adc_obj));
    if (!adc_pri)
    {
        RT_KERNEL_FREE(adc_dev);
        return RT_ENOMEM;
    }

    // copy platform data to pri data..
    rt_memcpy(adc_pri, adc_obj, sizeof(struct wrap_adc_obj));

    rt_kprintf("id:%d\n", adc_pri->id);

    // bind pri data to rt_adc_dev...
    adc_dev->user_data = (void *)adc_pri;
    adc_dev->open      = gk_adc_open;
    adc_dev->close     = gk_adc_close;
    adc_dev->control   = gk_adc_ioctl;
    adc_dev->init      = gk_adc_init;
    adc_dev->type      = RT_Device_Class_Miscellaneous;

    rt_device_register(adc_dev, "adc", RT_DEVICE_FLAG_RDWR);

    adc_obj->init_flag = ADC_INIT_ALREADY;

    return RT_EOK;
}

int gk_adc_exit(void *priv_data)
{
    struct wrap_adc_obj *adc_obj = (struct wrap_adc_obj *)priv_data;

    struct wrap_adc_obj *adc_pri = adc_obj->rt_dev->user_data;

    RT_KERNEL_FREE(adc_obj->rt_dev->user_data);

    adc_obj->rt_dev->user_data = RT_NULL;
    RT_KERNEL_FREE(adc_obj->rt_dev);
    adc_obj->rt_dev = RT_NULL;

    GD_ADC_Exit();

    return 0;
}

struct gk_platform_driver adc_driver_ops = {
    .name = "adc", .probe = gk_adc_probe, .remove = gk_adc_exit,
};

void rt_hw_adc_init(void)
{
    gk_platform_driver_init(&adc_driver_ops);
}

#ifdef GK_TEST_ADC
int gk_adc_test(void)
{
    rt_device_t adc_dev;
    ADC_INFO info;
    info.channel   = 0;
    info.adc_data = 0;
    adc_dev       = rt_device_find("adc");
    if (!adc_dev)
    {
        rt_kprintf("cann't find the adc dev\n");
        return -1;
    }
    adc_dev->init(adc_dev);
    adc_dev->open(adc_dev, 0);
    while (1)
    {
        adc_dev->control(adc_dev, ADC_CMD_READ_RAW_DATA, &info);
        rt_kprintf("channel:%d, data:0x%x\n", info.channel, info.adc_data);
    }

    return 0;
}
#endif

#ifdef RT_USING_FINSH
#include <finsh.h>
#ifdef GK_TEST_ADC
FINSH_FUNCTION_EXPORT(gk_adc_test, gk_adc_test);
#endif
#endif

#endif
