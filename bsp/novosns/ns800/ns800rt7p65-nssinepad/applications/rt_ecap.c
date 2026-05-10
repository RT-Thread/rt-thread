#include <rtthread.h>
#include <rtdevice.h>
#include "drv_ecap.h"
#include "rt_ecap.h"

static void ecap_test_thread (void *parameter)
{
    rt_device_t dev;
    struct rt_ecap_capture cap;

    dev = rt_device_find("ecap1");
    if (dev == RT_NULL)
    {
        rt_kprintf("ecap1 not found\n");
        return;
    }

    if (rt_device_open(dev, RT_DEVICE_OFLAG_RDONLY) != RT_EOK)
    {
        rt_kprintf("ecap1 open failed\n");
        return;
    }

    while (1)
    {
        if (rt_device_read(dev, 0, &cap, sizeof(cap)) == sizeof(cap))
        {
            rt_kprintf("cap1=%u cap2=%u cap3=%u cap4=%u high=%u low=%u total=%u\n", cap.cap1, cap.cap2, cap.cap3,
                        cap.cap4, cap.period_high, cap.period_low, cap.period_total);
        }
        else
        {
            rt_kprintf("Capturing...\n");
        }
        rt_thread_mdelay(1000);
    }
}

int rt_ecap_test_init (void)
{
    rt_thread_t tid;

    tid = rt_thread_create("ecap_test", ecap_test_thread, RT_NULL, 2048, 20, 10);

    if (tid != RT_NULL)
    {
        rt_kprintf("create ecap_test thread success\n");
        rt_thread_startup(tid);
    }
    else
    {
        rt_kprintf("create ecap_test thread failed\n");
    }

    return 0;
}
MSH_CMD_EXPORT(rt_ecap_test_init, ecap capture test);

