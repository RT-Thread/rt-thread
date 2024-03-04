/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <dfs_romfs.h>

static const unsigned char _dummy_dummy_txt[] =
{
    0x74, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x61, 0x20, 0x66, 0x69, 0x6c, 0x65, 0x21, 0x0d, 0x0a,
};

static const struct romfs_dirent _dummy[] =
{
    {ROMFS_DIRENT_FILE, "dummy.txt", _dummy_dummy_txt, sizeof(_dummy_dummy_txt)},
};

static const unsigned char _dummy_txt[] =
{
    0x74, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x61, 0x20, 0x66, 0x69, 0x6c, 0x65, 0x21, 0x0d, 0x0a,
};

rt_weak const struct romfs_dirent _root_dirent[] =
{
    {ROMFS_DIRENT_DIR, "dev", RT_NULL, 0},
    {ROMFS_DIRENT_DIR, "mnt", RT_NULL, 0},
    {ROMFS_DIRENT_DIR, "proc", RT_NULL, 0},
    {ROMFS_DIRENT_DIR, "etc", RT_NULL, 0},
    {ROMFS_DIRENT_DIR, "bin", RT_NULL, 0},
    {ROMFS_DIRENT_DIR, "dummy", (rt_uint8_t *)_dummy, sizeof(_dummy) / sizeof(_dummy[0])},
    {ROMFS_DIRENT_FILE, "dummy.txt", _dummy_txt, sizeof(_dummy_txt)},
};

rt_weak const struct romfs_dirent romfs_root =
{
    ROMFS_DIRENT_DIR, "/", (rt_uint8_t *)_root_dirent, sizeof(_root_dirent) / sizeof(_root_dirent[0])
};
