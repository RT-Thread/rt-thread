/**
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-08-16     Meco Man     First version
 */

#include <rtthread.h>
#include <unistd.h>
#include <sys/errno.h>

/**
 * @brief   Check if a file descriptor is associated with a terminal device.
 *
 * @param   fd  is the file descriptor to be checked.
 *
 * @return  1 if the file descriptor is associated with a terminal device, 0 if it is not.
 *          If the file descriptor is not associated with a terminal device, errno is set to ENOTTY.
 *
 * @note    This function overrides the standard C library's 'isatty' function for RT-Thread.
 */
int isatty(int fd)
{
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    if (fd == STDOUT_FILENO || fd == STDERR_FILENO)
    {
        return 1;
    }
#endif /* defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE) */

#ifdef RT_USING_POSIX_STDIO
    if (fd == STDIN_FILENO)
    {
        return 1;
    }
#endif /* RT_USING_POSIX_STDIO */

    rt_set_errno(ENOTTY);
    return 0;
}
RTM_EXPORT(isatty);
