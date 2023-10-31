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

#define DBG_TAG "dlib.syscall.lseek"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/**
 * @brief   Custom '__lseek' function for changing the file position.
 *
 * This function is used to change the file position for the specified 'handle' according to the 'offset' and 'whence' parameters.
 *
 * @param   handle  The file handle for which the position should be changed.
 * @param   offset  The offset value used to determine the new position.
 * @param   whence  A parameter specifying how the 'offset' should be interpreted (SEEK_SET, SEEK_CUR, or SEEK_END).
 *
 * @return  The current file position after the change, or -1 on failure.
 *
 * @note    If the 'handle' corresponds to standard input (stdin), standard output (stdout), or standard error (stderr),
 *          this function returns an error. Otherwise, it attempts to change the file position using the 'lseek' function.
 *          If RT-Thread's POSIX file system (DFS_USING_POSIX) is enabled, it delegates the lseek operation to the 'lseek' function,
 *          otherwise, it logs a warning and returns an error.
 */
#pragma module_name = "?__lseek"
long __lseek(int handle, long offset, int whence)
{
    if (handle == _LLIO_STDOUT ||
        handle == _LLIO_STDERR ||
        handle == _LLIO_STDIN)
    {
        return _LLIO_ERROR;
    }

#ifdef DFS_USING_POSIX
    return lseek(handle, offset, whence);
#else
    LOG_W(_WARNING_WITHOUT_FS);
    return _LLIO_ERROR;
#endif /* DFS_USING_POSIX */
}
