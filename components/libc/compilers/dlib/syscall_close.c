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
#include <compiler_private.h>
#define DBG_TAG    "dlib.syscall.close"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

/*
 * The "__close" function should close the file corresponding to
 * "handle".  It should return 0 on success and nonzero on failure.
 */

#pragma module_name = "?__close"

int __close(int handle)
{
    if (handle == _LLIO_STDOUT ||
        handle == _LLIO_STDERR ||
        handle == _LLIO_STDIN)
        return _LLIO_ERROR;
#ifdef DFS_USING_POSIX
    return close(handle);
#else
    LOG_W(_WARNING_WITHOUT_FS);
    return _LLIO_ERROR;
#endif /* DFS_USING_POSIX */
}
