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

#pragma module_name = "?__lseek"
long __lseek(int handle, long offset, int whence)
{
    if (handle == _LLIO_STDOUT ||
        handle == _LLIO_STDERR ||
        handle == _LLIO_STDIN)
        return _LLIO_ERROR;

#ifdef RT_USING_DFS
    return lseek(handle, offset, whence);
#else
    return _LLIO_ERROR;
#endif
}
