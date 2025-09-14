/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
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

/**
 * @brief Type of arguments
 */
enum lwp_args_type {
    LWP_ARGS_TYPE_ARG,      /**< User-space arguments */
    LWP_ARGS_TYPE_KARG,     /**< Kernel-space arguments */
    LWP_ARGS_TYPE_ENVP,     /**< User-space environment variables */
    LWP_ARGS_TYPE_KENVP,    /**< Kernel-space environment variables */
    LWP_ARGS_TYPE_NULLPTR   /**< NULL pointer terminator */
};

/**
 * @brief String vector structure
 */
struct lwp_string_vector
{
    const char **strvec;         /**< Pointer to array of strings */
    rt_uint32_t strvec_buflen;   /**< Total buffer length of strvec */
    rt_uint32_t string_count;    /**< Number of strings in strvec */
};

/**
 * @brief Arguments information structure
 *
 * @note str_buf stores all argument strings' content.
 *       argv stores argument strings' pointers in str_buf.
 *       envp stores environment variable strings' pointers in str_buf.
 */
struct lwp_args_info
{
    int argv0_strlen;                  /**< Length of argv[0] */
    int strings_length;                /**< Total length of all argument strings */
    int str_buf_size;                  /**< Total size of str_buf */

    char *str_buf;                     /**< Buffer to store all argument strings */
    struct lwp_string_vector argv;     /**< Vector of argument strings */
    struct lwp_string_vector envp;     /**< Vector of environment variable strings */
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
