/*
 * Copyright (c) 2011-2023, Shanghai Real-Thread Electronic Technology Co.,Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-18     quanzhao     the first version
 */

#include <time.h>
#include <string.h>
#include <rtthread.h>

static struct rt_device random_dev;
static unsigned long seed;

static rt_uint16_t calc_random(void)
{
    seed = 214013L * seed + 2531011L;
    return (seed >> 16) & 0x7FFF;   /* return bits 16~30 */
}

static rt_ssize_t random_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_uint16_t rand = calc_random();
    ssize_t ret = sizeof(rand);
    rt_memcpy(buffer, &rand, ret);
    return ret;
}

static rt_ssize_t random_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    ssize_t ret = sizeof(seed);
    rt_memcpy(&seed, buffer, ret);
    return ret;
}

static rt_err_t  random_control(rt_device_t dev, int cmd, void *args)
{
    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops random_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    random_read,
    random_write,
    random_control
};
#endif

int random_device_init(void)
{
    static rt_bool_t init_ok = RT_FALSE;

    if (init_ok)
    {
        return 0;
    }
    RT_ASSERT(!rt_device_find("random"));
    random_dev.type    = RT_Device_Class_Miscellaneous;

#ifdef RT_USING_DEVICE_OPS
    random_dev.ops     = &random_ops;
#else
    random_dev.init    = RT_NULL;
    random_dev.open    = RT_NULL;
    random_dev.close   = RT_NULL;
    random_dev.read    = random_read;
    random_dev.write   = random_write;
    random_dev.control = random_control;
#endif

    /* no private */
    random_dev.user_data = RT_NULL;

    rt_device_register(&random_dev, "random", RT_DEVICE_FLAG_RDWR);

    init_ok = RT_TRUE;

    return 0;
}
INIT_DEVICE_EXPORT(random_device_init);

static struct rt_device urandom_dev;
static unsigned long useed;

static rt_uint16_t calc_urandom(void)
{
    useed = 214013L * useed + 2531011L;
    return (useed >> 16) & 0x7FFF;   /* return bits 16~30 */
}

static rt_ssize_t random_uread(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_uint16_t rand = calc_urandom();
    ssize_t ret = sizeof(rand);
    rt_memcpy(buffer, &rand, ret);
    return ret;
}

static rt_ssize_t random_uwrite(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    ssize_t ret = sizeof(useed);
    rt_memcpy(&useed, buffer, ret);
    return ret;
}

static rt_err_t random_ucontrol(rt_device_t dev, int cmd, void *args)
{
    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops urandom_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    random_uread,
    random_uwrite,
    random_ucontrol
};
#endif

int urandom_device_init(void)
{
    static rt_bool_t init_ok = RT_FALSE;

    if (init_ok)
    {
        return 0;
    }
    RT_ASSERT(!rt_device_find("urandom"));
    urandom_dev.type    = RT_Device_Class_Miscellaneous;

#ifdef RT_USING_DEVICE_OPS
    urandom_dev.ops     = &urandom_ops;
#else
    urandom_dev.init    = RT_NULL;
    urandom_dev.open    = RT_NULL;
    urandom_dev.close   = RT_NULL;
    urandom_dev.read    = random_uread;
    urandom_dev.write   = random_uwrite;
    urandom_dev.control = random_ucontrol;
#endif

    /* no private */
    urandom_dev.user_data = RT_NULL;

    rt_device_register(&urandom_dev, "urandom", RT_DEVICE_FLAG_RDWR);

    init_ok = RT_TRUE;

    return 0;
}
INIT_DEVICE_EXPORT(urandom_device_init);
