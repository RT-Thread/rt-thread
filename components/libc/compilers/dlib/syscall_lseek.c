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
#define DBG_TAG    "dlib.syscall.lseek"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

/*
 * The "__lseek" function makes the next file operation (__read or
 * __write) act on a new location.  The parameter "whence" specifies
 * how the "offset" parameter should be interpreted according to the
 * following table:
 *
 *  0 (=SEEK_SET) - Goto location "offset".
 *  1 (=SEEK_CUR) - Go "offset" bytes from the current location.
 *  2 (=SEEK_END) - Go to "offset" bytes from the end.
 *
 * This function should return the current file position, or -1 on
 * failure.
 */

#pragma module_name = "?__lseek"

long __lseek(int handle, long offset, int whence)
{
    if (handle == _LLIO_STDOUT ||
        handle == _LLIO_STDERR ||
        handle == _LLIO_STDIN)
        return _LLIO_ERROR;
#ifdef DFS_USING_POSIX
    return lseek(handle, offset, whence);
#else
    LOG_W(_WARNING_WITHOUT_FS);
    return _LLIO_ERROR;
#endif /* DFS_USING_POSIX */
}
