/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022/01/20     bernard      the first version
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>

#include <rtthread.h>
#include <msh.h>

int em_init(void)
{
    int count = 5;
    char *em_cmd = "/services/em.elf &";

    while (count --)
    {
        int fd;
        fd = open("/services/em.elf", O_RDONLY);
        if (fd >= 0)
        {
            close(fd);

            msh_exec(em_cmd, rt_strlen(em_cmd) + 1);
            return 0;
        }
        else
        {
            rt_thread_mdelay(500);
        }
    }

    if (count <= 0)
    {
        printf("open em failed!\n");
    }

    return -1;
}
INIT_APP_EXPORT(em_init);
