/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-02     armink       the first version
 */

#include <stdlib.h>
#include <rtthread.h>

#ifndef ULOG_USING_SYSLOG
#define LOG_TAG              "example"
#define LOG_LVL              LOG_LVL_DBG
#include <ulog.h>
#else
#include <syslog.h>
#endif /* ULOG_USING_SYSLOG */

void ulog_example(void)
{
    int count = 0;

#ifdef ULOG_USING_SYSLOG
    openlog("example1", 0, 0);
#endif

    while (count++ < 50)
    {
#ifndef ULOG_USING_SYSLOG
        /* output different level log by LOG_X API */
        LOG_D("LOG_D(%d): RT-Thread is an open source IoT operating system from China.", count);
        LOG_I("LOG_I(%d): RT-Thread is an open source IoT operating system from China.", count);
        LOG_W("LOG_W(%d): RT-Thread is an open source IoT operating system from China.", count);
        LOG_E("LOG_E(%d): RT-Thread is an open source IoT operating system from China.", count);
        ulog_d("test", "ulog_d(%d): RT-Thread is an open source IoT operating system from China.", count);
        ulog_i("test", "ulog_i(%d): RT-Thread is an open source IoT operating system from China.", count);
        ulog_w("test", "ulog_w(%d): RT-Thread is an open source IoT operating system from China.", count);
        ulog_e("test", "ulog_e(%d): RT-Thread is an open source IoT operating system from China.", count);

#ifdef ULOG_USING_FILTER
        if (count == 20)
        {
            /* Set the global filer level is INFO. All of DEBUG log will stop output */
            ulog_global_filter_lvl_set(LOG_LVL_INFO);
            /* Set the test tag's level filter's level is ERROR. The DEBUG, INFO, WARNING log will stop output. */
            ulog_tag_lvl_filter_set("test", LOG_LVL_ERROR);
        }
        else if (count == 30)
        {
            /* Set the example tag's level filter's level is LOG_FILTER_LVL_SILENT, the log enter silent mode. */
            ulog_tag_lvl_filter_set("example", LOG_FILTER_LVL_SILENT);
            /* Set the test tag's level filter's level is WARNING. The DEBUG, INFO log will stop output. */
            ulog_tag_lvl_filter_set("test", LOG_LVL_WARNING);
        }
        else if (count == 40)
        {
            /* Set the test tag's level filter's level is LOG_FILTER_LVL_ALL. All level log will resume output. */
            ulog_tag_lvl_filter_set("test", LOG_FILTER_LVL_ALL);
            /* Set the global filer level is LOG_FILTER_LVL_ALL. All level log will resume output */
            ulog_global_filter_lvl_set(LOG_FILTER_LVL_ALL);
        }
#endif /* ULOG_USING_FILTER */

#else
        /* output different priority log by syslog API */
        syslog(LOG_INFO, "syslog(%d) LOG_INFO: RT-Thread is an open source IoT operating system from China.", count);
        syslog(LOG_DEBUG, "syslog(%d) LOG_DEBUG: RT-Thread is an open source IoT operating system from China.", count);
        syslog(LOG_WARNING, "syslog(%d) LOG_WARNING: RT-Thread is an open source IoT operating system from China.", count);
        syslog(LOG_ERR, "syslog(%d) LOG_ERR: RT-Thread is an open source IoT operating system from China.", count);
        syslog(LOG_INFO | LOG_MAIL, "syslog(%d) LOG_INFO | LOG_MAIL: RT-Thread is an open source IoT operating system from China.", count);
        syslog(LOG_DEBUG | LOG_DAEMON, "syslog(%d) LOG_DEBUG | LOG_DAEMON: RT-Thread is an open source IoT operating system from China.", count);
        syslog(LOG_WARNING | LOG_AUTH, "syslog(%d) LOG_WARNING | LOG_AUTH: RT-Thread is an open source IoT operating system from China.", count);
        syslog(LOG_ERR | LOG_SYSLOG, "syslog(%d) LOG_ERR | LOG_SYSLOG: RT-Thread is an open source IoT operating system from China.", count);

        if (count == 20)
        {
            /* Set log priority mask. Only output ERR and WARNING log. */
            setlogmask(LOG_MASK(LOG_ERR) | LOG_MASK(LOG_WARNING));
        }
        else if (count == 40)
        {
            /* Set log priority mask. The log which level is less than ERROR will stop output. */
            setlogmask(LOG_UPTO(LOG_ERR));
        }
#endif /* ULOG_USING_SYSLOG */

        rt_thread_delay(rt_tick_from_millisecond(rand() % 1000));
    }
}
MSH_CMD_EXPORT(ulog_example, run ulog example)
