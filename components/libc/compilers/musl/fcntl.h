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

#include_next <fcntl.h>

#ifndef O_DIRECTORY
#define O_DIRECTORY 0x200000
#endif

#ifndef O_BINARY
#define O_BINARY 0x10000
#endif

#endif
