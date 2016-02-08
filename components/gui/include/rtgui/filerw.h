/*
 * File      : filerw.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
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
