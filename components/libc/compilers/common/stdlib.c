/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-15     Meco Man     first version
 */

#include <rtthread.h>

#define DBG_TAG    "stdlib"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

void __rt_libc_exit(int status)
{
    rt_thread_t self = rt_thread_self();

    if (self != RT_NULL)
    {
        LOG_E("thread:%s exit:%d!", self->name, status);
        rt_thread_control(self, RT_THREAD_CTRL_CLOSE, RT_NULL);
    }
}

#ifdef RT_USING_MSH
int system(const char *command)
{
    extern int msh_exec(char *cmd, rt_size_t length);

    int ret = -RT_ENOMEM;
    char *cmd = rt_strdup(command);

    if (cmd)
    {
        ret = msh_exec(cmd, rt_strlen(cmd));
        rt_free(cmd);
    }

    return ret;
}
RTM_EXPORT(system);
#endif
