/*
 * Copyright (c) 2011-2023, Shanghai Real-Thread Electronic Technology Co.,Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-03     quanzhao     the first version
 */

#include <time.h>
#include <string.h>
#include <rtthread.h>

static struct rt_device null_dev;

static rt_ssize_t null_read    (rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    return 0;
}

static rt_ssize_t null_write   (rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    return size;
}

static rt_err_t  null_control (rt_device_t dev, int cmd, void *args)
{
    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops null_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    null_read,
    null_write,
    null_control
};
#endif

int null_device_init(void)
{
    static rt_bool_t init_ok = RT_FALSE;

    if (init_ok)
    {
        return 0;
    }
    RT_ASSERT(!rt_device_find("null"));
    null_dev.type    = RT_Device_Class_Miscellaneous;

#ifdef RT_USING_DEVICE_OPS
    null_dev.ops     = &null_ops;
#else
    null_dev.init    = RT_NULL;
    null_dev.open    = RT_NULL;
    null_dev.close   = RT_NULL;
    null_dev.read    = null_read;
    null_dev.write   = null_write;
    null_dev.control = null_control;
#endif

    /* no private */
    null_dev.user_data = RT_NULL;

    rt_device_register(&null_dev, "null", RT_DEVICE_FLAG_RDWR);

    init_ok = RT_TRUE;

    return 0;
}
INIT_DEVICE_EXPORT(null_device_init);

