/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-01-28     Bernard      first version
 */
#include <rtthread.h>
#ifdef RT_USING_DFS
#include <dfs_posix.h>
#endif
#include <yfuns.h>

#pragma module_name = "?remove"
int remove(const char *val)
{
#ifndef RT_USING_DFS
    return -1;
#else
    return unlink(val);
#endif
}
