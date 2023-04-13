/*
 * COPYRIGHT (C) 2012-2022, Shanghai Real-Thread Technology Co., Ltd
 * All rights reserved.
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread  the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_touch.h"
#include "drv_pin.h"
// #include "lcd_cfg.h"

#ifndef TOUCH_I2C_NAME
#define TOUCH_I2C_NAME "i2c2"
#endif
#define DBG_TAG "TOUCH"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#define COORD_Y_REVERSE (1 << 0)
#define COORD_X_REVERSE (1 << 1)
#define COORD_XY_EXCHANGE (1 << 2)

#ifdef BSP_USING_MANGOPI                             // mango board
#define TP_INT_PIN GET_PIN(GPIO_PORT_D, GPIO_PIN_22) /* GPIO_PORT_D GPIO_PIN_22 */
#elif defined(BSP_USING_M7)
#define TP_INT_PIN GET_PIN(GPIO_PORT_G, GPIO_PIN_14) /* GPIO_PORT_G GPIO_PIN_14 */
#endif

static rt_slist_t _driver_list;
static struct rt_i2c_bus_device *i2c_bus = RT_NULL;
static struct touch_driver *current_driver = RT_NULL;
static struct rt_touch_device touch_device;
static rt_timer_t touch_timer = RT_NULL;
static int tp_convert_flag;
// static const struct lcd_cfg_panel_info *_panel_info;

void touch_coord_convert(int *x, int *y, int range_x, int range_y, int flag)
{
    int xbuf, ybuf;

    if (flag & COORD_XY_EXCHANGE)
    {
        xbuf = range_x;
        range_x = range_y;
        range_y = xbuf;
        xbuf = *y;
        ybuf = *x;

        if (flag & COORD_X_REVERSE)
        {
            ybuf = range_y - ybuf;
        }

        if (flag & COORD_Y_REVERSE)
        {
            xbuf = range_x - xbuf;
        }
    }
    else
    {
        xbuf = *x;
        ybuf = *y;

        if (flag & COORD_X_REVERSE)
        {
            xbuf = range_x - xbuf;
        }

        if (flag & COORD_Y_REVERSE)
        {
            ybuf = range_y - ybuf;
        }
    }

    *x = xbuf;
    *y = ybuf;
}

rt_err_t rt_touch_drivers_register(touch_driver_t drv)
{
    RT_ASSERT(drv != RT_NULL);
    RT_ASSERT(drv->ops != RT_NULL);
    RT_ASSERT(drv->probe != RT_NULL);

    rt_slist_append(&_driver_list, &drv->list);

    return RT_EOK;
}

int rt_touch_list_init(void)
{
    rt_slist_init(&_driver_list);

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_touch_list_init);

static void touch_timeout_handle(void *parameter)
{
    rt_touch_t touch = (rt_touch_t)parameter;
    rt_device_t device = &touch->parent;

    device->control(device, RT_TOUCH_CTRL_ENABLE_INT, RT_NULL); // enable tp irq

    // rt_kprintf("[%s:%d]touch_timeout_handle\n", __FUNCTION__, __LINE__);
}

static rt_err_t tp_irq_handle(rt_touch_t touch)
{
    rt_device_t device;
    device = &touch->parent;

    device->control(device, RT_TOUCH_CTRL_DISABLE_INT, RT_NULL); // disable tp irq

    return RT_EOK;
}

int rt_touch_read(rt_uint16_t addr, void *cmd_buf, size_t cmd_len, void *data_buf, size_t data_len)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr = addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf = cmd_buf;
    msgs[0].len = cmd_len;

    msgs[1].addr = addr;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf = data_buf;
    msgs[1].len = data_len;

    if (rt_i2c_transfer(i2c_bus, msgs, 2) == 2)
        return 0;
    else
        return -1;
}

int rt_touch_write(rt_uint16_t addr, void *data_buf, size_t data_len)
{
    struct rt_i2c_msg msgs[1];

    msgs[0].addr = addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf = data_buf;
    msgs[0].len = data_len;

    if (rt_i2c_transfer(i2c_bus, msgs, 1) == 1)
        return 0;
    else
        return -1;
}

static rt_ssize_t touch_readpoint(struct rt_touch_device *touch, void *buf, rt_size_t touch_num)
{
    rt_device_t device;
    struct rt_touch_data *data = (struct rt_touch_data *)buf;
    int x, y;
    device = &touch->parent;

    current_driver->ops->read_point(data, touch_num);

    /* touch up事件是上次转换后的，所以不需要执行转换 */
    if ((RT_TOUCH_EVENT_NONE != data->event) && (RT_TOUCH_EVENT_UP != data->event))
    {
        x = data->x_coordinate;
        y = data->y_coordinate;
        // touch_coord_convert(&x, &y, _panel_info->width, _panel_info->height, tp_convert_flag);
        data->x_coordinate = x;
        data->y_coordinate = y;
    }

    if ((touch_timer != RT_NULL) && (current_driver->read_interval != 0))
    {
        rt_timer_start(touch_timer);
    }
    else if ((TOUCH_INT_MODE == current_driver->check_mode) && (0 != current_driver->read_interval))
    {
        device->control(device, RT_TOUCH_CTRL_ENABLE_INT, RT_NULL); // enable tp irq
    }
    else
    {
    }

    return 1;
}

static rt_err_t touch_control(struct rt_touch_device *touch, int cmd, void *arg)
{
    return RT_EOK;
}

static struct rt_touch_ops touch_ops =
    {
        .touch_readpoint = touch_readpoint,
        .touch_control = touch_control,
};

static void touch_poll_entry(void *parameter)
{
    rt_tick_t read_interval = current_driver->read_interval;

    if (0 == read_interval)
    {
        read_interval = rt_tick_from_millisecond(20);
    }

    while (1)
    {
        rt_thread_delay(read_interval);
        if (RT_NULL != touch_device.parent.rx_indicate)
        {
            /* Notify the application layer to get data */
            touch_device.parent.rx_indicate(&touch_device.parent, 1);
        }
    }
}

int rt_touch_init(void)
{
    rt_slist_t *driver_list = RT_NULL;
    rt_uint16_t irq_pin = TP_INT_PIN;
    int range_x, range_y;

    i2c_bus = rt_i2c_bus_device_find(TOUCH_I2C_NAME);
    RT_ASSERT(i2c_bus);

    if (rt_device_open(&i2c_bus->parent, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
    {
        rt_kprintf("[TP] open i2c dvice failed.\n");
        return -RT_EIO;
    }

    rt_slist_for_each(driver_list, &_driver_list)
    {
        current_driver = (struct touch_driver *)driver_list;
        if (current_driver->probe(i2c_bus) == RT_TRUE)
        {
            break;
        }
        current_driver = RT_NULL;
    }

    if (current_driver == RT_NULL)
    {
        rt_kprintf("[TP] No touch pad or driver.\n");
        rt_device_close((rt_device_t)i2c_bus);
        return -RT_EIO;
    }

    if ((TOUCH_INT_MODE == current_driver->check_mode) && (0 != current_driver->read_interval))
    {
        touch_timer = rt_timer_create("touch", touch_timeout_handle,
                                      &touch_device, current_driver->read_interval,
                                      RT_TIMER_FLAG_ONE_SHOT);
        if (touch_timer == RT_NULL)
        {
            rt_kprintf("[TP] touch timer create failed.\n");
            rt_device_close((rt_device_t)i2c_bus);
            return -RT_EIO;
        }
    }
    else if (TOUCH_POLL_MODE == current_driver->check_mode)
    {
        rt_thread_t thread;
        irq_pin = PIN_IRQ_PIN_NONE; // No interrupt pins are used
        thread = rt_thread_create("touch", touch_poll_entry, RT_NULL, 2048, 16, 20);
        if (thread == RT_NULL)
        {
            rt_kprintf("[TP] touch poll thread create failed.\n");
            rt_device_close((rt_device_t)i2c_bus);
            return -RT_ERROR;
        }
        rt_thread_startup(thread);
    }

    /* loading the touchscreen configuration */
    // _panel_info = load_lcd_config_from_xml();
    // range_x = _panel_info->width;
    // range_y = _panel_info->height;
    // tp_convert_flag = 0;
    // /* touch screen xy swap */
    // if (_panel_info->ctp_flag & COORD_XY_EXCHANGE)
    // {
    //     tp_convert_flag |= COORD_XY_EXCHANGE;
    //     touch_coord_convert(&range_x, &range_y, _panel_info->width, _panel_info->height, COORD_XY_EXCHANGE);
    // }

    // if (_panel_info->ctp_flag & COORD_Y_REVERSE)
    // {
    //     tp_convert_flag |= COORD_Y_REVERSE;
    // }

    // if (_panel_info->ctp_flag & COORD_X_REVERSE)
    // {
    //     tp_convert_flag |= COORD_X_REVERSE;
    // }

    current_driver->ops->init(i2c_bus);

    /* touch infomation */
    touch_device.info.type = RT_TOUCH_TYPE_CAPACITANCE;
    touch_device.info.vendor = RT_TOUCH_VENDOR_UNKNOWN;
    touch_device.info.point_num = 1;
    touch_device.info.range_x = 480;
    touch_device.info.range_y = 272;
    touch_device.config.user_data = RT_NULL;
    touch_device.ops = &touch_ops;
    touch_device.irq_handle = tp_irq_handle;
    touch_device.config.irq_pin.pin = irq_pin;
    touch_device.config.irq_pin.mode = PIN_MODE_INPUT_PULLUP;

    return rt_hw_touch_register(&touch_device, "touch", RT_DEVICE_FLAG_INT_RX, RT_NULL);
}
INIT_ENV_EXPORT(rt_touch_init);
