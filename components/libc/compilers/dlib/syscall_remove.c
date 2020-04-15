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
#include <dfs_file.h>
#endif
#include <yfuns.h>

#pragma module_name = "?remove"
int remove(const char *val)
{
#ifdef RT_USING_DFS
    dfs_file_unlink(val);
#endif

    return 0;
}
