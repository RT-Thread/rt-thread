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

#ifndef _ULOG_BE_H_
#define _ULOG_BE_H_

#include <ulog.h>

#ifndef ULOG_FILE_PATH_LEN
#define ULOG_FILE_PATH_LEN   128
#endif

struct ulog_file_be
{
    struct ulog_backend parent;
    int cur_log_file_fd;
    rt_size_t file_max_num;
    rt_size_t file_max_size;
    rt_size_t buf_size;
    rt_bool_t enable;

    rt_uint8_t *file_buf;
    rt_uint8_t *buf_ptr_now;

    char cur_log_file_path[ULOG_FILE_PATH_LEN];
    char cur_log_dir_path[ULOG_FILE_PATH_LEN];
};

/* ulog file backend api */
int ulog_file_backend_init(struct ulog_file_be *be, const char *name, const char *dir_path, rt_size_t max_num,
        rt_size_t max_size, rt_size_t buf_size);
int ulog_file_backend_deinit(struct ulog_file_be *be);
void ulog_file_backend_enable(struct ulog_file_be *be);
void ulog_file_backend_disable(struct ulog_file_be *be);

#endif /* _ULOG_BE_H_ */
