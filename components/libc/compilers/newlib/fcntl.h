/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-02     Meco Man     First version
 */

#ifndef __FCNTL_H__
#define __FCNTL_H__

#include <sys/_default_fcntl.h>

#ifndef O_EXEC
#define O_EXEC      0x400000
#endif

#ifndef O_TMPFILE
#define O_TMPFILE   0x800000
#endif

#ifndef O_BINARY
#define O_BINARY 0x10000
#endif

#ifndef O_NOFOLLOW
#define O_NOFOLLOW 0x100000
#endif

#ifndef O_DIRECTORY
#define O_DIRECTORY 0x200000
#endif

#endif
