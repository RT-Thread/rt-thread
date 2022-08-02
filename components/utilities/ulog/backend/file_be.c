/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-07     ChenYong     first version
 * 2021-12-20     armink       add multi-instance version
 */

#include <rtthread.h>
#include <dfs_file.h>
#include <unistd.h>

#include <ulog.h>
#include <ulog_be.h>

#ifdef ULOG_BACKEND_USING_FILE

#if defined(ULOG_ASYNC_OUTPUT_THREAD_STACK) && (ULOG_ASYNC_OUTPUT_THREAD_STACK < 2048)
#error "The value of ULOG_ASYNC_OUTPUT_THREAD_STACK must be greater than 2048."
#endif

/* rotate the log file xxx_n-1.log => xxx_n.log, and xxx.log => xxx_0.log */
static rt_bool_t ulog_file_rotate(struct ulog_file_be *be)
{
#define SUFFIX_LEN          10
    /* mv xxx_n-1.log => xxx_n.log, and xxx.log => xxx_0.log */
    static char old_path[ULOG_FILE_PATH_LEN], new_path[ULOG_FILE_PATH_LEN];
    int index = 0, err = 0, file_fd = 0;
    rt_bool_t result = RT_FALSE;
    size_t base_len = 0;

    rt_snprintf(old_path, ULOG_FILE_PATH_LEN, "%s/%s", be->cur_log_dir_path, be->parent.name);
    rt_snprintf(new_path, ULOG_FILE_PATH_LEN, "%s/%s", be->cur_log_dir_path, be->parent.name);
    base_len = rt_strlen(be->cur_log_dir_path) + rt_strlen(be->parent.name) + 1;

    if (be->cur_log_file_fd >= 0)
    {
        close(be->cur_log_file_fd);
    }

    for (index = be->file_max_num - 2; index >= 0; --index)
    {
        rt_snprintf(old_path + base_len, SUFFIX_LEN, index ? "_%d.log" : ".log", index - 1);
        rt_snprintf(new_path + base_len, SUFFIX_LEN, "_%d.log", index);
        /* remove the old file */
        if ((file_fd = open(new_path, O_RDONLY)) >= 0)
        {
            close(file_fd);
            unlink(new_path);
        }
        /* change the new log file to old file name */
        if ((file_fd = open(old_path , O_RDONLY)) >= 0)
        {
            close(file_fd);
            err = dfs_file_rename(old_path, new_path);
        }

        if (err < 0)
        {
            result = RT_FALSE;
            goto __exit;
        }

        result = RT_TRUE;
    }

__exit:
    /* reopen the file */
    be->cur_log_file_fd = open(be->cur_log_file_path, O_CREAT | O_RDWR | O_APPEND);

    return result;
}

static void ulog_file_backend_flush_with_buf(struct ulog_backend *backend)
{
    struct ulog_file_be *be = (struct ulog_file_be *) backend;
    rt_size_t file_size = 0, write_size = 0;

    if (be->enable == RT_FALSE || be->buf_ptr_now == be->file_buf)
    {
        return;
    }
    if (be->cur_log_file_fd < 0)
    {
        /* check log file directory  */
        if (access(be->cur_log_dir_path, 0) < 0)
        {
            mkdir(be->cur_log_dir_path, 0);
        }
        /* open file */
        rt_snprintf(be->cur_log_file_path, ULOG_FILE_PATH_LEN, "%s/%s.log", be->cur_log_dir_path, be->parent.name);
        be->cur_log_file_fd = open(be->cur_log_file_path, O_CREAT | O_RDWR | O_APPEND);
        if (be->cur_log_file_fd < 0)
        {
            rt_kprintf("ulog file(%s) open failed.", be->cur_log_file_path);
            return;
        }
    }

    file_size = lseek(be->cur_log_file_fd, 0, SEEK_END);
    if (file_size >= (be->file_max_size - be->buf_size * 2))
    {
        if (!ulog_file_rotate(be))
        {
            return;
        }
    }

    write_size = (rt_size_t)(be->buf_ptr_now - be->file_buf);
    /* write to the file */
    if (write(be->cur_log_file_fd, be->file_buf, write_size) != write_size)
    {
        return;
    }
    /* flush file cache */
    fsync(be->cur_log_file_fd);

    /* point be->buf_ptr_now at the head of be->file_buf[be->buf_size] */
    be->buf_ptr_now = be->file_buf;
}

static void ulog_file_backend_output_with_buf(struct ulog_backend *backend, rt_uint32_t level,
            const char *tag, rt_bool_t is_raw, const char *log, rt_size_t len)
{
    struct ulog_file_be *be = (struct ulog_file_be *)backend;
    rt_size_t copy_len = 0, free_len = 0;
    const unsigned char *buf_ptr_end = be->file_buf + be->buf_size;

    while (len)
    {
        /* free space length */
        free_len = buf_ptr_end - be->buf_ptr_now;
        /* copy the log to the mem buffer */
        if (len > free_len)
        {
            copy_len = free_len;
        }
        else
        {
            copy_len = len;
        }
        rt_memcpy(be->buf_ptr_now, log, copy_len);
        /* update data pos */
        be->buf_ptr_now += copy_len;
        len -= copy_len;
        log += copy_len;

        RT_ASSERT(be->buf_ptr_now <= buf_ptr_end);
        /* check the log buffer remain size */
        if (buf_ptr_end == be->buf_ptr_now)
        {
            ulog_file_backend_flush_with_buf(backend);
            if (buf_ptr_end == be->buf_ptr_now)
            {
                /* There is no space, indicating that the data cannot be refreshed
                   to the back end of the file Discard data and exit directly */
                break;
            }
        }
    }
}

/* initialize the ulog file backend */
int ulog_file_backend_init(struct ulog_file_be *be, const char *name, const char *dir_path, rt_size_t max_num,
        rt_size_t max_size, rt_size_t buf_size)
{
    be->file_buf = rt_calloc(1, buf_size);
    if (!be->file_buf)
    {
        rt_kprintf("Warning: NO MEMORY for %s file backend\n", name);
        return -RT_ENOMEM;
    }
    /* temporarily store the start address of the ulog file buffer */
    be->buf_ptr_now = be->file_buf;
    be->cur_log_file_fd = -1;
    be->file_max_num = max_num;
    be->file_max_size = max_size;
    be->buf_size = buf_size;
    be->enable = RT_FALSE;
    rt_strncpy(be->cur_log_dir_path, dir_path, ULOG_FILE_PATH_LEN);
    /* the buffer length MUST less than file size */
    RT_ASSERT(be->buf_size < be->file_max_size);

    be->parent.output = ulog_file_backend_output_with_buf;
    be->parent.flush = ulog_file_backend_flush_with_buf;
    ulog_backend_register((ulog_backend_t) be, name, RT_FALSE);

    return 0;
}

/* uninitialize the ulog file backend */
int ulog_file_backend_deinit(struct ulog_file_be *be)
{
    if (be->cur_log_file_fd >= 0)
    {
        /* flush log to file */
        ulog_file_backend_flush_with_buf((ulog_backend_t)be);
        /* close */
        close(be->cur_log_file_fd);
        be->cur_log_file_fd = -1;
    }

    if (!be->file_buf)
    {
        rt_free(be->file_buf);
        be->file_buf = RT_NULL;
    }

    ulog_backend_unregister((ulog_backend_t)be);
    return 0;
}

void ulog_file_backend_enable(struct ulog_file_be *be)
{
    be->enable = RT_TRUE;
}

void ulog_file_backend_disable(struct ulog_file_be *be)
{
    be->enable = RT_FALSE;
}

#endif /* ULOG_BACKEND_USING_FILE */
