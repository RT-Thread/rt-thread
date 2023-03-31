/*
 * Copyright (c) 2011-2020, Shanghai Real-Thread Electronic Technology Co.,Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-03     quanzhao     the first version
 */

#include <time.h>
#include <string.h>
#include <rtthread.h>

static struct rt_device zero_dev;

static rt_ssize_t zero_read    (rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_memset(buffer, 0, size);
    return size;
}

static rt_ssize_t zero_write   (rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    return size;
}

static rt_err_t  zero_control (rt_device_t dev, int cmd, void *args)
{
    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops zero_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    zero_read,
    zero_write,
    zero_control
};
#endif

int zero_device_init(void)
{
    static rt_bool_t init_ok = RT_FALSE;

    if (init_ok)
    {
        return 0;
    }
    RT_ASSERT(!rt_device_find("zero"));
    zero_dev.type    = RT_Device_Class_Miscellaneous;

#ifdef RT_USING_DEVICE_OPS
    zero_dev.ops     = &zero_ops;
#else
    zero_dev.init    = RT_NULL;
    zero_dev.open    = RT_NULL;
    zero_dev.close   = RT_NULL;
    zero_dev.read    = zero_read;
    zero_dev.write   = zero_write;
    zero_dev.control = zero_control;
#endif

    /* no private */
    zero_dev.user_data = RT_NULL;

    rt_device_register(&zero_dev, "zero", RT_DEVICE_FLAG_RDWR);

    init_ok = RT_TRUE;

    return 0;
}
INIT_DEVICE_EXPORT(zero_device_init);

