/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-12     Shell        separate argv, envp, aux processing from execve(2).
 *                             Bugs fix for script arguments processing.
 */
#ifndef __LWP_ARGV_H__
#define __LWP_ARGV_H__

#include <rtthread.h>

struct rt_lwp;

enum lwp_args_type {
    LWP_ARGS_TYPE_ARG,
    LWP_ARGS_TYPE_KARG,
    LWP_ARGS_TYPE_ENVP,
    LWP_ARGS_TYPE_KENVP,
    LWP_ARGS_TYPE_NULLPTR
};

struct lwp_string_vector
{
    const char **strvec;
    rt_uint32_t strvec_buflen;
    rt_uint32_t string_count;
};

struct lwp_args_info
{
    int argv0_strlen;
    int strings_length;
    int str_buf_size;

    char *str_buf;
    struct lwp_string_vector argv;
    struct lwp_string_vector envp;
};

rt_err_t lwp_args_init(struct lwp_args_info *ai);
void lwp_args_detach(struct lwp_args_info *ai);
struct process_aux *lwp_argscopy(struct rt_lwp *lwp, struct lwp_args_info *args_info);;
rt_err_t lwp_args_put(struct lwp_args_info *args, const char **strv_addr, enum lwp_args_type atype);
rt_err_t lwp_args_put_argv(struct lwp_args_info *args, const char **argv_uaddr);
rt_err_t lwp_args_put_envp(struct lwp_args_info *args, const char **envp_uaddr);
rt_err_t lwp_args_load_script(struct lwp_args_info *args, const char *filename);
const char *lwp_args_get_argv_0(struct lwp_args_info *ai);
char** lwp_get_envp(struct rt_lwp *lwp, rt_size_t *penvp_counts);
void lwp_print_envp(struct rt_lwp *lwp);

char** lwp_get_command_line_args(struct rt_lwp *lwp);
void lwp_free_command_line_args(char** argv);

#endif /* __LWP_ARGV_H__ */
