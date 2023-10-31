/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-01-28     Bernard      First version
 */

#include <rtthread.h>
#include <LowLevelIOInterface.h>
#include <unistd.h>
#include <compiler_private.h>

#define DBG_TAG "dlib.syscall.close"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/**
 * @brief   Custom '__close' function for handling file closing.
 *
 * This function is used to close the file corresponding to the provided 'handle'.
 *
 * @param   handle  The file handle to be closed.
 *
 * @return  0 on success, or a nonzero value on failure.
 *
 * @note    If the 'handle' corresponds to standard input (stdin), standard output (stdout), or standard error (stderr),
 *          this function returns an error. Otherwise, it attempts to close the file handle using the 'close' function.
 *          If RT-Thread's POSIX file system (DFS_USING_POSIX) is enabled, it delegates the close operation to the 'close' function,
 *          otherwise, it logs a warning and returns an error.
 */
#pragma module_name = "?__close"
int __close(int handle)
{
    if (handle == _LLIO_STDOUT ||
        handle == _LLIO_STDERR ||
        handle == _LLIO_STDIN)
    {
        return _LLIO_ERROR;
    }

#ifdef DFS_USING_POSIX
    return close(handle);
#else
    LOG_W(_WARNING_WITHOUT_FS);
    return _LLIO_ERROR;
#endif /* DFS_USING_POSIX */
}
