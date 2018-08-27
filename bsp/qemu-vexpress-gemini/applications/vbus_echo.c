#include <stdlib.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <vbus.h>

#define BUFLEN 1024
static char buf[BUFLEN];

static void _vbus_on_tx_cmp(void *p)
{
    struct rt_completion *cmp = p;

    rt_completion_done(cmp);
}

static rt_size_t _vbus_write_sync(rt_device_t dev, void *buf, rt_size_t len)
{
    rt_size_t sd;
    struct rt_completion cmp;
    struct rt_vbus_dev_liscfg liscfg;

    rt_completion_init(&cmp);
    liscfg.event = RT_VBUS_EVENT_ID_TX;
    liscfg.listener = _vbus_on_tx_cmp;
    liscfg.ctx = &cmp;

    rt_device_control(dev, VBUS_IOC_LISCFG, &liscfg);
    sd = rt_device_write(dev, 0, buf, len);

    rt_completion_wait(&cmp, RT_WAITING_FOREVER);

    return sd;
}

static void _rev_str(char *buf, rt_size_t len)
{
    char tmp;
    rt_size_t i, mid;

    RT_ASSERT(buf);

    if (!len)
        return;

    mid = len / 2;
    for (i = 0; i < mid; i++)
    {
        tmp = buf[i];
        buf[i] = buf[len - 1 - i];
        buf[len - 1 - i] = tmp;
    }
}

static void _test_write(void *devname)
{
    int i;
    rt_device_t dev;

    dev = rt_device_find(devname);

    if (!dev)
    {
        rt_kprintf("could not find %s\n", devname);
        return;
    }

again:
    i = rt_device_open(dev, RT_DEVICE_OFLAG_RDWR);
    if (i)
    {
        rt_kprintf("open dev err:%d\n", i);
        return;
    }

    for (i = 0; i < sizeof(buf) - 1;i++)
    {
        int len;

        len = rt_device_read(dev, 0, buf + i, 1);
        if (len != 1 || buf[i] == '\n')
            break;
    }
    buf[i] = '\0';
    rt_kprintf("recv: %s\n", buf);
    /* Don't swap the \n. */
    _rev_str(buf, i - 1);
    /* Don't write the \0. */
    rt_kprintf("write: %s\n", buf);
    _vbus_write_sync(dev, buf, i - 1);

    rt_device_close(dev);
    goto again;
}

int vser_echo_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("vecho", _test_write, "vecho",
                           1024, 0, 20);
    RT_ASSERT(tid);
    return rt_thread_startup(tid);
}

#ifdef RT_USING_COMPONENTS_INIT
INIT_APP_EXPORT(vser_echo_init);
#endif
