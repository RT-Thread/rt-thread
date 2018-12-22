/*
 * File      : drv_pwm.c
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
#include <rtdevice.h>
//#include "gpio.h"

#include "drv_pwm.h"

#include <rtdef.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/watchdog.h>

#include "gtypes.h"
#include "gd_pwm.h"
#include "platform.h"

#define GK_TEST_PWM
static struct gk_pwm_obj *pwm_drv = NULL;
static struct pwm_driver pwm_drv_table;

static rt_err_t pwm_get_status(rt_uint32_t *status)
{
    rt_uint32_t channel_enable;

    struct gk_pwm_obj *pwm_obj = (struct gk_pwm_obj *)pwm_drv;
    if(status == NULL || pwm_obj->id >= PWM_MAX_CHANNEL)
    {
        rt_kprintf("PWM: > max channel \n");
        return RT_ERROR;
    }

    if (GD_OK != GD_PWM_Get_Status(pwm_obj->id, &channel_enable))
    {
        rt_kprintf("get pwm status failed!\n");
        return RT_ERROR;
    }
    *status = channel_enable;

    return RT_EOK;
}

static rt_err_t pwm_enable(struct gk_pwm_obj *pwm_obj)
{
    rt_uint32_t ret = RT_EOK;

    if (pwm_obj->id >= PWM_MAX_CHANNEL)
    {
        rt_kprintf("PWM: > max channel \n");
        return RT_ERROR;
    }

    ret = GD_PwmOnOff(pwm_obj->id, GTRUE);
    if (ret != GD_OK)
    {
        rt_kprintf("enable pwm device failed!\n");
        return RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t pwm_disable(struct gk_pwm_obj *pwm_obj)
{
    rt_uint32_t ret = RT_EOK;

    if (pwm_obj->id >= PWM_MAX_CHANNEL)
    {
        rt_kprintf("PWM: > max channel \n");
        return RT_ERROR;
    }

    ret = GD_PwmOnOff(pwm_obj->id, GFALSE);
    if (ret != GD_OK)
    {
        rt_kprintf("disable pwm device failed!\n");
        return RT_ERROR;
    }

    return ret;
}

static int pwm_get_duty_cycle_ns(struct pwm_device *pwm)
{
    struct gk_pwm_obj *pwm_obj = (struct gk_pwm_obj *)pwm_drv;
    rt_uint32_t freq, duty;

    if (pwm_obj->id >= PWM_MAX_CHANNEL)
    {
        rt_kprintf("PWM: > max channel \n");
        return -1;
    }

    if (GD_PWM_Get_Param(pwm_obj->id, &freq, &duty))
    {
        rt_kprintf("GD_PWM_Get_Param error.\n");
        return -1;
    }

    rt_kprintf("get duty: %lu%%, freq: %lu\n", duty, freq);

    return 0;
}

static int pwm_set_duty_cycle_ns(struct pwm_device *pwm)
{
    struct gk_pwm_obj *pwm_obj = (struct gk_pwm_obj *)pwm_drv;
    rt_uint32_t range, duty, freq;
    GERR ret = 0;

    if(pwm_obj->id >= PWM_MAX_CHANNEL)
    {
        rt_kprintf("PWM: > max channel \n");
        return -1;
    }

    freq = pwm->freq;
    range = pwm->range;
    duty = pwm->duty;
    //param mode The PWM mode: 0 - Normal Speed Mode; 1 - Sync Speed Mode.
    ret = GD_PWM_Set_Mode(pwm_obj->id, 0);
    if(ret != GD_OK)
    {
        rt_kprintf("Set pwm mode 0 failed!\n");
        return -1;
    }

    ret = GD_PWM_Set_Param(pwm_obj->id, freq, range, duty);
    if (GD_PWM_NO_ERR != ret)
    {
        if (GD_PWM_ERR_NOT_SUPPORTED_CHANNEL == ret)
        {
            rt_kprintf("PWM Set_Param:set[%d %d %d]error *not support channel.\n",
                       (int)freq, (int)range, (int)duty);
        }
        else if(GD_PWM_ERR_NOT_SUPPORTED_FREQUENCY == ret)
        {
            rt_kprintf("PWM Set_Param:set[%d %d %d]error *not support Freq.\n",
                    (int)freq, (int)range, (int)duty);
        }
        else if(GD_PWM_ERR_NOT_SUPPORTED_RANGE == ret)
        {
            rt_kprintf("PWM Set_Param:set[%d %d %d]error *not support Range.\n",
                    (int)freq, (int)range, (int)duty);
        }
        else if(GD_PWM_ERR_WRONG_DUTY_CONFIGURATION == ret)
        {
            rt_kprintf("PWM Set_Param:set[%d %d %d]error *wrong duty.\n",
                    (int)freq, (int)range, (int)duty);
        }
        else if(GD_PWM_ERR_RANGE_EXCEED_LIMIT == ret)
        {
            rt_kprintf("PWM Set_Param:set[%d %d %d]error *exceed Range limit.\n",
                    (int)freq, (int)range, (int)duty);
        }

        return -1;
    }

    return 0;
}

static int pwm_get_vsync_mode_param(rt_uint16_t *speed)
{
    struct gk_pwm_obj *pwm_obj = (struct gk_pwm_obj *)pwm_drv;
    GERR ret = GD_OK;

    if (pwm_obj->id >= PWM_MAX_CHANNEL)
    {
        rt_kprintf("PWM: > max channel \n");
        return -1;
    }

    ret = GD_PWM_Get_Speed(pwm_obj->id, speed);
    if(ret != GD_OK)
    {
        rt_kprintf("Get pwm speed failed!\n");
        return -1;
    }

    rt_kprintf("get speed: %u\n", *speed);

    return 0;
}

static int pwm_set_vsync_mode_param(struct pwm_param_vsync_mode *param)
{
    struct gk_pwm_obj *pwm_obj = (struct gk_pwm_obj *)pwm_drv;
    GERR ret = GD_OK;

    if(pwm_obj->id >= PWM_MAX_CHANNEL)
    {
        rt_kprintf("PWM: > max channel \n");
        return -1;
    }

    //param mode The PWM mode: 0 - Normal Speed Mode; 1 - Sync Speed Mode.
    ret = GD_PWM_Set_Mode(pwm_obj->id, 1);
    if(ret != GD_OK)
    {
        rt_kprintf("Set pwm mode 1 failed!\n");
        return -1;
    }

    ret = GD_PWM_Set_Speed(pwm_obj->id, param->speed);
    if(ret != GD_OK)
    {
        rt_kprintf("Set pwm speed failed!\n");
        return -1;
    }

    ret = GD_PWM_Cycle(pwm_obj->id, param->highLevelCnt, param->lowLevelCnt);
    if(ret != GD_OK)
    {
        rt_kprintf("Set pwm cycle failed!\n");
        return -1;
    }

    return 0;
}

static int pwm_set_clock_divider(int ratio)
{
    struct gk_pwm_obj *pwm_obj = (struct gk_pwm_obj *)pwm_drv;
    rt_uint32_t range, duty, freq;
    GERR ret = 0;

    if (pwm_obj->id >= PWM_MAX_CHANNEL)
    {
        rt_kprintf("PWM: > max channel \n");
        return -1;
    }

	if ((ratio != 1) && (ratio != 2) && (ratio != 3))
	{
	    rt_kprintf("pwm_set_clock_divider:%d wrong param.\n", ratio);
		return -1;
	}

	if (GD_OK != GD_PWM_Set_Clock_Divider(pwm_obj->id, ratio))
	{
		rt_kprintf("gadi_pwm_set_clock_divider:%d set error.\n", ratio);
		return -1;
	}

	return 0;
}

static int pwm_set_active_channel(int id)
{
    GERR ret = 0;

    if (id >= PWM_MAX_CHANNEL)
    {
        rt_kprintf("PWM: > max channel \n");
        return -1;
    }

    if (pwm_drv_table.pwm[id].gpio_id == 0xff)
    {
        rt_kprintf("channel not open \n");
        return -1;
    }

    pwm_drv->id = id;

    return 0;
}

static rt_err_t pwm_start(struct gk_pwm_obj *pwm_obj)
{
    rt_uint32_t pwmStatus = 0;
    rt_uint32_t ret = GD_OK;

    ret = pwm_get_status(&pwmStatus);
    if(ret != RT_EOK)
    {
        return ret;
    }

    if(pwmStatus)
    {
        ret = pwm_disable(pwm_obj);
        if(ret != RT_EOK)
        {
            return ret;
        }
    }

    return pwm_enable(pwm_obj);
}

static rt_err_t gk_pwm_open(rt_device_t dev, rt_uint16_t oflag)
{
    rt_err_t ret = RT_EOK;
    int index;

    for (index=0; index<PWM_MAX_CHANNEL; index++)
    {
        if ((pwm_drv_table.pwm[index].id != 0xff) && (pwm_drv_table.pwm[index].gpio_id != 0xff))
        {
            rt_kprintf("pwm_drv_table.pwm[%d] id= %d, gpio_id = %d\n",
                        index,
                        pwm_drv_table.pwm[index].id,
                        pwm_drv_table.pwm[index].gpio_id);

            ret = GD_PWM_Open(pwm_drv_table.pwm[index].id, pwm_drv_table.pwm[index].gpio_id);
            if(ret != GD_OK)
            {
               rt_kprintf("open pwm device %d channel failed!\n", pwm_drv_table.pwm[index].id);
               continue;
            }
        }
    }

    if (pwm_drv_table.pwm[0].gpio_id != 0xff)
    {
        pwm_drv->id = pwm_drv_table.pwm[0].id;
    }

    return ret;
}

static rt_err_t gk_pwm_close(rt_device_t dev)
{
    struct gk_pwm_obj *pwm_obj = (struct gk_pwm_obj *)pwm_drv;

    if(pwm_obj->id >= PWM_MAX_CHANNEL)
    {
        rt_kprintf("PWM: > max channel \n");
        return RT_ERROR;
    }

    GD_PWM_Close(pwm_obj->id);

    return RT_EOK;
}

static rt_err_t gk_pwm_ioctl(rt_device_t dev, int cmd, void *arg)
{
    int ratio, ret = 0;
    rt_uint16_t *speed = NULL;
    struct pwm_device *pwm = NULL;
    struct pwm_param_vsync_mode *vsync_param = NULL;
    struct gk_pwm_obj *pwm_obj = (struct gk_pwm_obj *)pwm_drv;

    switch (cmd)
    {
        case ENABLE_PWM:
            pwm_start(pwm_obj);
            break;

        case DISABLE_PWM:
            pwm_disable(pwm_obj);
            break;

        case SET_PWM_DUTY_CYCLE:
            pwm = (struct pwm_device *)arg;
            pwm_set_duty_cycle_ns(pwm);
            break;

        case GET_PWM_DUTY_CYCLE:
            pwm = (struct pwm_device *)arg;
            pwm_get_duty_cycle_ns(pwm);
            break;

        case SET_PWM_VSYNC_MODE:
            vsync_param = (struct pwm_param_vsync_mode *)arg;
            pwm_set_vsync_mode_param(vsync_param);
            break;

        case GET_PWM_VSYNC_MODE:
            speed = (rt_uint16_t *)arg;
            pwm_get_vsync_mode_param(speed);
            break;

        case SET_PWM_CLOCK_DIV:
            ratio = *((int*)arg);
            pwm_set_clock_divider(ratio);
            break;

        case SET_PWM_ACT_CHANNEL:
            ratio = *((int*)arg);
            pwm_set_active_channel(ratio);
            break;

        default:
            break;
    }

    return ret;
}

static rt_err_t gk_pwm_init(rt_device_t dev)
{
    rt_err_t ret = RT_EOK;

    ret = (rt_err_t)GD_PWM_Init();

    return ret;
}

int gk_pwm_probe(void *priv_data)
{
    rt_device_t pwm_dev;
    int index;

    for (index=0; index < PWM_MAX_CHANNEL; index++)
    {
        pwm_drv_table.pwm[index].id  = 0xff;
        pwm_drv_table.pwm[index].gpio_id = 0xff;
    }

    for (index=0; index < PWM_MAX_CHANNEL; index++)
    {
        if (((struct pwm_driver *)priv_data)->pwm[index].gpio_id > 0)
        {
            pwm_drv_table.pwm[index].id  = ((struct pwm_driver *)priv_data)->pwm[index].id;
            pwm_drv_table.pwm[index].gpio_id = ((struct pwm_driver *)priv_data)->pwm[index].gpio_id;
        }
    }

    pwm_drv = rt_malloc(sizeof(struct gk_pwm_obj));
    if (pwm_drv == RT_NULL)
    {
        rt_kprintf("ERROR: %s pwm_drv malloc failed\n", __func__);
    }
    rt_memset(pwm_drv, 0, sizeof(struct gk_pwm_obj));

    pwm_dev = rt_malloc(sizeof(struct rt_device));
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("ERROR: %s rt_device malloc failed\n", __func__);
    }
    rt_memset(pwm_dev, 0, sizeof(struct rt_device));

    pwm_dev->user_data = &pwm_drv_table;
    pwm_dev->open      = gk_pwm_open;
    pwm_dev->close     = gk_pwm_close;
    pwm_dev->control   = gk_pwm_ioctl;
    pwm_dev->init      = gk_pwm_init;
    pwm_dev->type      = RT_Device_Class_Miscellaneous;

    rt_device_register(pwm_dev, "pwm", RT_DEVICE_FLAG_RDWR);

    return 0;
}

int gk_pwm_exit(void *priv_data) { return 0; }
struct gk_platform_driver pwm_driver_ops = {
    .name = "pwm", .probe = gk_pwm_probe, .remove = gk_pwm_exit,
};

void rt_hw_pwm_init(void)
{
	gk_platform_driver_init(&pwm_driver_ops);
}

#ifdef GK_TEST_PWM
int gk_pwm_test(void)
{
    rt_device_t pwm_dev;
    struct pwm_device pwm;

    pwm.duty = 50;
    pwm.range = 100;
    pwm.freq = 1000;

    pwm_dev = rt_device_find("pwm");
    if (!pwm_dev)
    {
        rt_kprintf("cann't find the pwm dev\n");
    }

    pwm_dev->init(pwm_dev);
    pwm_dev->open(pwm_dev, 0);
    pwm_dev->control(pwm_dev, SET_PWM_DUTY_CYCLE, &pwm);
    pwm_dev->control(pwm_dev, ENABLE_PWM, NULL);

    return 0;
}
#endif

#ifdef RT_USING_FINSH
#include <finsh.h>
#ifdef GK_TEST_PWM
FINSH_FUNCTION_EXPORT(gk_pwm_test, gk_pwm_test);
#endif
#endif
