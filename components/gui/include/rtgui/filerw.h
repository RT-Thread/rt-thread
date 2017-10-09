/*
 * File      : filerw.h
 * This file is part of RT-Thread GUI Engine
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
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
 * 2009-10-16     Bernard      first version
 */
#ifndef __RTGUI_FILERW_H__
#define __RTGUI_FILERW_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RTGUI_USING_DFS_FILERW
#ifdef _WIN32_NATIVE
#pragma warning(disable: 4996)
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#else
#include <dfs_posix.h>
#endif
#endif

#include <rtgui/rtgui.h>

#define RTGUI_FILE_SEEK_SET 0
#define RTGUI_FILE_SEEK_CUR 1
#define RTGUI_FILE_SEEK_END 2

struct rtgui_filerw
{
    int (*seek)(struct rtgui_filerw *context, rt_off_t offset, int whence);
    int (*read)(struct rtgui_filerw *context, void *buffer, rt_size_t size, rt_size_t count);
    int (*write)(struct rtgui_filerw *context, const void *buffer, rt_size_t size, rt_size_t count);
    int (*tell)(struct rtgui_filerw *context);
    int (*eof)(struct rtgui_filerw *context);
    int (*close)(struct rtgui_filerw *context);
};
typedef struct rtgui_filerw rtgui_filerw_t;

struct rtgui_filerw *rtgui_filerw_create_file(const char *filename, const char *mode);
struct rtgui_filerw *rtgui_filerw_create_mem(const rt_uint8_t *mem, rt_size_t size);

int rtgui_filerw_seek(struct rtgui_filerw *context, rt_off_t offset, int whence);
int rtgui_filerw_read(struct rtgui_filerw *context, void *buffer, rt_size_t size, rt_size_t count);
int rtgui_filerw_write(struct rtgui_filerw *context, const void *buffer, rt_size_t size, rt_size_t count);
int rtgui_filerw_tell(struct rtgui_filerw *context);
int rtgui_filerw_eof(struct rtgui_filerw *context);
int rtgui_filerw_close(struct rtgui_filerw *context);
int rtgui_filerw_unlink(const char *filename);

/* get memory data from filerw memory object */
const rt_uint8_t *rtgui_filerw_mem_getdata(struct rtgui_filerw *context);

#ifdef __cplusplus
}
#endif

#endif
