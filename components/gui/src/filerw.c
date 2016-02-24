/*
 * File      : filerw.c
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
#include <rtgui/rtgui_system.h>
#include <rtgui/filerw.h>

#ifdef RTGUI_USING_DFS_FILERW

/* standard file read/write */
struct rtgui_filerw_stdio
{
    /* inherit from rtgui_filerw */
    struct rtgui_filerw parent;

    int fd;
    rt_bool_t eof;
};

static int stdio_seek(struct rtgui_filerw *context, rt_off_t offset, int whence)
{
    struct rtgui_filerw_stdio *stdio_filerw = (struct rtgui_filerw_stdio *)context;
    int stdio_whence[3] = {SEEK_SET, SEEK_CUR, SEEK_END};

    if (whence < RTGUI_FILE_SEEK_SET || whence > RTGUI_FILE_SEEK_END)
    {
        return -1;
    }

    return lseek(stdio_filerw->fd, offset, stdio_whence[whence]);
}

static int stdio_read(struct rtgui_filerw *context, void *ptr, rt_size_t size, rt_size_t maxnum)
{
    int result;

    struct rtgui_filerw_stdio *stdio_filerw = (struct rtgui_filerw_stdio *)context;

    /* end of file */
    if (stdio_filerw->eof == RT_TRUE) return -1;

    result = read(stdio_filerw->fd, ptr, size * maxnum);
    if (result == 0) stdio_filerw->eof = RT_TRUE;

    return result;
}

static int stdio_write(struct rtgui_filerw *context, const void *ptr, rt_size_t size, rt_size_t num)
{
    struct rtgui_filerw_stdio *stdio_filerw = (struct rtgui_filerw_stdio *)context;

    return write(stdio_filerw->fd, (char *)ptr, size * num);
}

static int stdio_tell(struct rtgui_filerw *context)
{
    struct rtgui_filerw_stdio *stdio_filerw = (struct rtgui_filerw_stdio *)context;

    return lseek(stdio_filerw->fd, 0, SEEK_CUR);
}

static int stdio_eof(struct rtgui_filerw *context)
{
    int result;
    struct rtgui_filerw_stdio *stdio_filerw = (struct rtgui_filerw_stdio *)context;

    if (stdio_filerw->eof == RT_TRUE) result = 1;
    else result = -1;

    return result;
}

static int stdio_close(struct rtgui_filerw *context)
{
    struct rtgui_filerw_stdio *stdio_filerw = (struct rtgui_filerw_stdio *)context;

    if (stdio_filerw)
    {
        close(stdio_filerw->fd);
        rtgui_free(stdio_filerw);

        return 0;
    }

    return -1;
}

#endif

/* memory file read/write */
struct rtgui_filerw_mem
{
    /* inherit from rtgui_filerw */
    struct rtgui_filerw parent;

    const rt_uint8_t *mem_base, *mem_position, *mem_end;
};

static int mem_seek(struct rtgui_filerw *context, rt_off_t offset, int whence)
{
    const rt_uint8_t *newpos;
    struct rtgui_filerw_mem *mem = (struct rtgui_filerw_mem *)context;

    RT_ASSERT(mem != RT_NULL);

    switch (whence)
    {
    case RTGUI_FILE_SEEK_SET:
        newpos = mem->mem_base + offset;
        break;

    case RTGUI_FILE_SEEK_CUR:
        newpos = mem->mem_position + offset;
        break;

    case RTGUI_FILE_SEEK_END:
        newpos = mem->mem_end + offset;
        break;

    default:
        return -1;
    }

    if (newpos < mem->mem_base)
        newpos = mem->mem_base;

    if (newpos > mem->mem_end)
        newpos = mem->mem_end;

    mem->mem_position = newpos;
    return mem->mem_position - mem->mem_base;
}

static int mem_read(struct rtgui_filerw *context, void *ptr, rt_size_t size, rt_size_t maxnum)
{
    int total_bytes;
    int mem_available;
    struct rtgui_filerw_mem *mem = (struct rtgui_filerw_mem *)context;

    total_bytes = (maxnum * size);
    if ((maxnum <= 0) || (size <= 0) || ((total_bytes / maxnum) != size))
    {
        return -1;
    }

    mem_available = mem->mem_end - mem->mem_position;
    if (total_bytes > mem_available)
        total_bytes = mem_available;

    rt_memcpy(ptr, mem->mem_position, total_bytes);
    mem->mem_position += total_bytes;

    return (total_bytes / size);
}

static int mem_write(struct rtgui_filerw *context, const void *ptr, rt_size_t size, rt_size_t num)
{
    return 0; /* not support memory write */
}

static int mem_tell(struct rtgui_filerw *context)
{
    struct rtgui_filerw_mem *mem = (struct rtgui_filerw_mem *)context;

    return mem->mem_position - mem->mem_base;
}

static int mem_eof(struct rtgui_filerw *context)
{
    struct rtgui_filerw_mem *mem = (struct rtgui_filerw_mem *)context;

    return mem->mem_position >= mem->mem_end;
}

static int mem_close(struct rtgui_filerw *context)
{
    struct rtgui_filerw_mem *mem = (struct rtgui_filerw_mem *)context;

    if (mem != RT_NULL)
    {
        rtgui_free(mem);
        return 0;
    }

    return -1;
}

const rt_uint8_t *rtgui_filerw_mem_getdata(struct rtgui_filerw *context)
{
    struct rtgui_filerw_mem *mem = (struct rtgui_filerw_mem *)context;

    /* check whether it's a memory filerw */
    if (mem->parent.read != mem_read) return RT_NULL;

    return mem->mem_base;
}

/* file read/write public interface */
#ifdef RTGUI_USING_DFS_FILERW
static int parse_mode(const char *mode)
{
    int f = 0;

    for (;;)
    {
        switch (*mode)
        {
        case 0:
            return f;
        case 'b':
            f |= O_BINARY;
            break;
        case 'r':
            f = O_RDONLY;
            break;
        case 'w':
            f = O_WRONLY | O_CREAT | O_TRUNC;
            break;
        case 'a':
            f = O_WRONLY | O_CREAT | O_APPEND;
            break;
        case '+':
            f = (f & (~O_WRONLY)) | O_RDWR;
            break;
        }

        ++mode;
    }
}

struct rtgui_filerw *rtgui_filerw_create_file(const char *filename, const char *mode)
{
    int fd;
    struct rtgui_filerw_stdio *rw;

    RT_ASSERT(filename != RT_NULL);

    rw = RT_NULL;
#ifdef _WIN32_NATIVE
    fd = _open(filename, parse_mode(mode), 0);
#else
    fd = open(filename, parse_mode(mode), 0);
#endif

    if (fd >= 0)
    {
        rw = (struct rtgui_filerw_stdio *) rtgui_malloc(sizeof(struct rtgui_filerw_stdio));
        if (rw != RT_NULL)
        {
            rw->parent.seek  = stdio_seek;
            rw->parent.read  = stdio_read;
            rw->parent.write = stdio_write;
            rw->parent.tell  = stdio_tell;
            rw->parent.close = stdio_close;
            rw->parent.eof   = stdio_eof;

            rw->fd  = fd;
            rw->eof = RT_FALSE;
            return &(rw->parent);
        }

        close(fd);
    }
    else
    {
        rt_kprintf("open:%s failed! errno=%d\n", filename, errno);
    }

    return RT_NULL;
}

int rtgui_filerw_unlink(const char *filename)
{
#ifdef _WIN32_NATIVE
    return _unlink(filename);
#else
#ifndef RT_USING_DFS
    /* no unlink function */
    return -1;
#else
    return unlink(filename);
#endif
#endif
}

#endif

struct rtgui_filerw *rtgui_filerw_create_mem(const rt_uint8_t *mem, rt_size_t size)
{
    struct rtgui_filerw_mem *rw;
    RT_ASSERT(mem != RT_NULL);

    rw = (struct rtgui_filerw_mem *) rtgui_malloc(sizeof(struct rtgui_filerw_mem));
    if (rw != RT_NULL)
    {
        rw->parent.seek  = mem_seek;
        rw->parent.read  = mem_read;
        rw->parent.write = mem_write;
        rw->parent.tell  = mem_tell;
        rw->parent.eof   = mem_eof;
        rw->parent.close = mem_close;

        rw->mem_base = mem;
        rw->mem_position = mem;
        rw->mem_end = mem + size;
    }

    return &(rw->parent);
}

int rtgui_filerw_seek(struct rtgui_filerw *context, rt_off_t offset, int whence)
{
    RT_ASSERT(context != RT_NULL);

    return context->seek(context, offset, whence);
}

int rtgui_filerw_read(struct rtgui_filerw *context, void *buffer, rt_size_t size, rt_size_t count)
{
    RT_ASSERT(context != RT_NULL);

    return context->read(context, buffer, size, count);
}

int rtgui_filerw_write(struct rtgui_filerw *context, const void *buffer, rt_size_t size, rt_size_t count)
{
    RT_ASSERT(context != RT_NULL);

    return context->write(context, buffer, size, count);
}

int rtgui_filerw_eof(struct rtgui_filerw *context)
{
    RT_ASSERT(context != RT_NULL);

    return context->eof(context);
}

int rtgui_filerw_tell(struct rtgui_filerw *context)
{
    RT_ASSERT(context != RT_NULL);

    return context->tell(context);
}

int rtgui_filerw_close(struct rtgui_filerw *context)
{
    int result;

    RT_ASSERT(context != RT_NULL);

    /* close context */
    result = context->close(context);
    if (result != 0)
    {
        /* close file failed */
        return -1;
    }

    return 0;
}

