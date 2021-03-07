/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2018-01-15     Liu2guang      the first version.
 */

#include <rtthread.h>
#include <rtdevice.h>

int rtc_test(void)
{
    uint8_t i;
    time_t now;

    rt_err_t ret = RT_EOK;

    rt_kprintf("[RTC Test]RTC Test Start...\n");
    rt_thread_delay(RT_TICK_PER_SECOND);
    rt_kprintf("[RTC Test]Set RTC 2017-04-01 12:30:46\n\n");
    rt_thread_delay(RT_TICK_PER_SECOND);

    ret = set_date(2017, 4, 1);
    if(ret != RT_EOK)
    {
        rt_kprintf("[RTC Test]Set RTC Date failed\n");
        return RT_ERROR;
    }

    rt_thread_delay(RT_TICK_PER_SECOND);

    ret = set_time(12, 30, 46);
    if(ret != RT_EOK)
    {
        rt_kprintf("[RTC Test]Set RTC Time failed\n");
        return RT_ERROR;
    }

    rt_thread_delay(RT_TICK_PER_SECOND);

    for(i = 0; i < 10; i++)
    {
        rt_kprintf("[RTC Test]Read RTC Date and Time: ");
        now = time(RT_NULL);
        rt_kprintf("%s", ctime(&now));

        rt_thread_delay(RT_TICK_PER_SECOND);
    }

    rt_kprintf("\n");

    return RT_EOK;
}
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(rtc_test, rtc drive test. e.g: rtc_test());
MSH_CMD_EXPORT(rtc_test, rtc drive test. e.g: rtc_test());
#endif
