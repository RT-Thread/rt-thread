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
<<<<<<< HEAD

int main(int argc, char** argv)
{
    printf("Hello RT-Thread!\n");

    return 0;
=======
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
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
}
