#include <sys/time.h>
#include <rtthread.h>

#if defined(RT_USING_DEVICE) && defined(RT_USING_RTC)
int gettimeofday(struct timeval *tp, void *ignore)
{
    time_t time;
    rt_device_t device;

    device = rt_device_find("rtc");
    if (device != RT_NULL)
    {
        rt_device_control(device, RT_DEVICE_CTRL_RTC_GET_TIME, &time);
        if (tp != RT_NULL)
        {
            tp->tv_sec = time;
            tp->tv_usec = 0;
        }

        return time;
    }

    return 0;
}
#endif
