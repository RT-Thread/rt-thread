/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-01-28     Bernard      first version
 */
#include <rtthread.h>
#include <yfuns.h>
#include <unistd.h>

#pragma module_name = "?remove"
int remove(const char *val)
{
#ifdef RT_USING_POSIX
    return unlink(val);
#else
    return -1;
#endif /* RT_USING_POSIX */
}
