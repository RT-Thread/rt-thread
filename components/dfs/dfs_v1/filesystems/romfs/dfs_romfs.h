/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019/01/13     Bernard      code cleanup
 */

#ifndef __DFS_ROMFS_H__
#define __DFS_ROMFS_H__

#include <rtthread.h>

#define ROMFS_DIRENT_FILE   0x00
#define ROMFS_DIRENT_DIR    0x01

struct romfs_dirent
{
    rt_uint32_t      type;  /* dirent type */

    const char       *name; /* dirent name */
    const rt_uint8_t *data; /* file date ptr */
    rt_size_t        size;  /* file size */
};

int dfs_romfs_init(void);

#ifndef RT_USING_DFS_ROMFS_USER_ROOT
extern const struct romfs_dirent romfs_root;
#endif /* RT_USING_DFS_ROMFS_USER_ROOT */

#endif /* __DFS_ROMFS_H__ */
