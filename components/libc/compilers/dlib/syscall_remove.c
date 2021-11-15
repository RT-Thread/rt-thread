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
#include <LowLevelIOInterface.h>
#include <unistd.h>

/*
 * The "remove" function should remove the file named "filename".  It
 * should return 0 on success and nonzero on failure.
 */

#pragma module_name = "?remove"

int remove(const char *filename)
{
#ifdef DFS_USING_POSIX
    return unlink(filename);
#else
    return _LLIO_ERROR;
#endif /* DFS_USING_POSIX */
}
