/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <stdio.h>
#include <stdlib.h>
#include <dfs_fs.h>
#include <rtthread.h>

int main(int argc, char** argv)
{
#ifdef RT_USING_DFS
    if(dfs_mount("flash0", "/", "efm", 0, 0) == 0)
    {
        rt_kprintf("mount efm ok\n");
    }
    else
    {
        rt_kprintf("mount efm fail\n");
    }
#endif
}
