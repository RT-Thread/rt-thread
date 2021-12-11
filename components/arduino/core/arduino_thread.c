/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-10     Meco Man     first version
 */
#include <Arduino.h>

#define DBG_TAG    "Arduino"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>


#ifndef RT_USING_ARDUINO_THREAD_SIZE
#define RT_USING_ARDUINO_THREAD_SIZE     1024
#endif

#ifndef RT_USING_ARDUINO_THREAD_PRIO
#define RT_USING_ARDUINO_THREAD_PRIO     20
#endif

static void arduino_entry(void *parameter)
{
    init();
    initVariant();
    setup();

    while(1)
    {
        loop();
        rt_schedule();
    }
}

static int arduino_thread_init(void)
{
    rt_thread_t tid;
    tid = rt_thread_create("Arduino",
                            arduino_entry, RT_NULL,
                            RT_USING_ARDUINO_THREAD_SIZE,
                            RT_USING_ARDUINO_THREAD_PRIO, 10);

    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
    else
    {
        LOG_E("Arduino thread initialization failed!");
    }

    return 0;
}
INIT_APP_EXPORT(arduino_thread_init);
