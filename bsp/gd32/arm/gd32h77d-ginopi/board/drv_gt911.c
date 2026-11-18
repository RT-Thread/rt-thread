/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-23     CYFS         add GT911 touch support with reset configuration polling
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <board.h>
#include <gt911.h>

#define DBG_TAG "drv.gt911.port"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define GT911_DEVICE_NAME       "gt911"
#define GT911_I2C_BUS_NAME      "hwi2c3"
#define GT911_RESET_PIN         GET_PIN(H, 3)
#define GT911_INT_PIN           GET_PIN(H, 5)
#define GT911_STARTUP_DELAY_MS  50U
#define GT911_CONFIG_TIMEOUT_MS 500U

static rt_uint8_t gt911_reset_pin = GT911_RESET_PIN;
static struct rt_touch_config gt911_config;

int rt_hw_gt911_port_init(void)
{
    struct rt_touch_info info;
    rt_device_t touch_device;
    char product_id[6] = {0};
    rt_err_t result;
    rt_tick_t start;

    if (rt_device_find(GT911_DEVICE_NAME) != RT_NULL)
    {
        return RT_EOK;
    }

    rt_memset(&gt911_config, 0, sizeof(gt911_config));
    gt911_config.dev_name = GT911_I2C_BUS_NAME;
    gt911_config.irq_pin.pin = GT911_INT_PIN;
    gt911_config.irq_pin.mode = PIN_MODE_INPUT_PULLUP;
    gt911_config.user_data = &gt911_reset_pin;

    result = rt_hw_gt911_init(GT911_DEVICE_NAME, &gt911_config);

    /* The package selects address 0x5d with INT low, then must release INT. */
    rt_pin_mode(GT911_INT_PIN, PIN_MODE_INPUT_PULLUP);

    if (result != RT_EOK)
    {
        LOG_E("GT911 package init failed: %d", result);
        return result;
    }

    rt_thread_mdelay(GT911_STARTUP_DELAY_MS);
    touch_device = rt_device_find(GT911_DEVICE_NAME);
    if (touch_device == RT_NULL)
    {
        LOG_E("touch device %s was not registered", GT911_DEVICE_NAME);
        return -RT_ERROR;
    }

    rt_memset(&info, 0, sizeof(info));
    start = rt_tick_get();
    do
    {
        result = rt_device_control(touch_device, RT_TOUCH_CTRL_GET_INFO, &info);
        if (result != RT_EOK)
        {
            LOG_E("get GT911 information failed: %d", result);
            return result;
        }
        if (info.range_x != 0 && info.range_y != 0 && info.point_num != 0)
        {
            break;
        }
        /* The controller restores its configuration after the soft reset. */
        rt_thread_mdelay(20);
    }
    while (rt_tick_get() - start < rt_tick_from_millisecond(GT911_CONFIG_TIMEOUT_MS));

    if (info.range_x == 0 || info.range_y == 0 || info.point_num == 0)
    {
        LOG_E("GT911 configuration is not ready after reset");
        return -RT_ETIMEOUT;
    }

    if (rt_device_control(touch_device, RT_TOUCH_CTRL_GET_ID, product_id) != RT_EOK)
    {
        rt_strncpy(product_id, "GT911", sizeof(product_id));
    }
    else
    {
        product_id[4] = '\0';
    }
    product_id[sizeof(product_id) - 1] = '\0';

    LOG_I("%s ready, id=%s, range=%dx%d, points=%d", GT911_DEVICE_NAME,
          product_id, info.range_x, info.range_y, info.point_num);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_gt911_port_init);
