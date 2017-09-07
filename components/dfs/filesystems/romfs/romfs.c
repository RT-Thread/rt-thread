/*
 * File      : romfs.c
 * This file is part of Device File System in RT-Thread RTOS
 * COPYRIGHT (C) 2004-2011, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <dfs_romfs.h>

const static unsigned char _dummy_dummy_txt[] =
{
    0x74,0x68,0x69,0x73,0x20,0x69,0x73,0x20,0x61,0x20,0x66,0x69,0x6c,0x65,0x21,0x0d,0x0a,
};

const static struct romfs_dirent _dummy[] =
{
    {ROMFS_DIRENT_FILE, "dummy.txt", _dummy_dummy_txt, sizeof(_dummy_dummy_txt)},
};

const static unsigned char _dummy_txt[] =
{
    0x74,0x68,0x69,0x73,0x20,0x69,0x73,0x20,0x61,0x20,0x66,0x69,0x6c,0x65,0x21,0x0d,0x0a,
};

const struct romfs_dirent WEAK _root_dirent[] =
{
    {ROMFS_DIRENT_DIR, "dummy", (rt_uint8_t *)_dummy, sizeof(_dummy)/sizeof(_dummy[0])},
    {ROMFS_DIRENT_FILE, "dummy.txt", _dummy_txt, sizeof(_dummy_txt)},
};

const struct romfs_dirent WEAK romfs_root =
{
    ROMFS_DIRENT_DIR, "/", (rt_uint8_t *)_root_dirent, sizeof(_root_dirent)/sizeof(_root_dirent[0])
};

