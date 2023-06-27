/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/10/7      bernard      the first version
 */
#include <dfs_romfs.h>

static const struct romfs_dirent _romfs_root[] = {
    {ROMFS_DIRENT_DIR, "bin", RT_NULL, 0},
    {ROMFS_DIRENT_DIR, "dev", RT_NULL, 0},
    {ROMFS_DIRENT_DIR, "etc", RT_NULL, 0},
    {ROMFS_DIRENT_DIR, "mnt", RT_NULL, 0},
};

const struct romfs_dirent romfs_root = {
    ROMFS_DIRENT_DIR, "/", (rt_uint8_t *)_romfs_root, sizeof(_romfs_root) / sizeof(_romfs_root[0])};
