/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/10/15     bernard      the first version
 */
#include <rtthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>

#include "libc.h"

int _EXFUN(putenv,(char *__string));
extern char **__environ;

int libc_system_init(void)
{
#if defined(RT_USING_DFS) & defined(RT_USING_DFS_DEVFS)

#if defined(RT_USING_CONSOLE)
    rt_device_t dev_console;

    dev_console = rt_console_get_device();
    if (dev_console)
    {
    #if defined(RT_USING_POSIX)
        libc_stdio_set_console(dev_console->parent.name, O_RDWR);
    #else
        libc_stdio_set_console(dev_console->parent.name, O_WRONLY);
    #endif
    }
#endif

    /* set PATH and HOME */
    putenv("PATH=/bin");
    putenv("HOME=/home");
#endif

    return 0;
}
INIT_COMPONENT_EXPORT(libc_system_init);

#ifdef RT_USING_MUSL
#if !defined(RT_USING_MLIB)
int *__errno_location(void)
{
    return _rt_errno();
}
#endif
int *___errno_location(void)
{
    return _rt_errno();
}

#endif

int env_set(int argc, char** argv)
{
    switch (argc)
    {
    case 1:
        {
            int index;

            /* show all of environment variables */
            for(index = 0; __environ[index]!=NULL; index++)
            {
                printf("%2d.%s\n", index, __environ[index]);
            }
        }
        break;
    case 2:
        {
            char *c = strchr(argv[1], '=');
            if (c)
            {
                /* use setenv to add/update environment variable */
                *c = '\0';
                setenv(argv[1], c + 1, 1);
            }
            else
            {
                const char *value = getenv(argv[1]);
                if (value)
                {
                    printf("%s=%s\n", argv[1], value);
                }
            }
        }
        break;
    default:
        break;
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(env_set, set, set or show environment variable);
