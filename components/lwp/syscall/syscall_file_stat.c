/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "syscall_internal.h"

/**
 * @brief Retrieves information about a file or directory.
 *
 * This system call obtains metadata about the specified file or directory and stores it in
 * the `buf` structure. The metadata includes attributes such as file size, permissions,
 * ownership, and timestamps.
 *
 * @param[in]  file  A pointer to the path of the file or directory to be queried.
 *                   The path should be a null-terminated string.
 * @param[out] buf   A pointer to a `struct stat` structure where the file's metadata
 *                   will be stored. This structure must be allocated by the caller.
 *
 * @return sysret_t  Returns a status code:
 *                    - `0`: The operation completed successfully, and the metadata
 *                      has been written to `buf`.
 *                    - Other error codes may indicate issues with the file path.
 *
 * @note The `file` path must be valid and accessible by the calling process. Ensure that
 *       the `buf` pointer points to a properly allocated memory region.
 *
 * @warning Passing a `NULL` pointer for `file` or `buf` may result in undefined behavior.
 *          Check all inputs before invoking this function to avoid potential issues.
 */
sysret_t sys_stat(const char *file, struct stat *buf)
{
    int ret = 0;
    size_t len;
    size_t copy_len;
    char *copy_path;
    struct stat statbuff = { 0 };

    if (!lwp_user_accessable((void *)buf, sizeof(struct stat)))
    {
        return -EFAULT;
    }

    len = lwp_user_strlen(file);
    if (len <= 0)
    {
        return -EFAULT;
    }

    copy_path = (char *)rt_malloc(len + 1);
    if (!copy_path)
    {
        return -ENOMEM;
    }

    copy_len = lwp_get_from_user(copy_path, (void *)file, len);
    if (copy_len == 0)
    {
        rt_free(copy_path);
        return -EFAULT;
    }
    copy_path[copy_len] = '\0';

    ret = _SYS_WRAP(stat(copy_path, &statbuff));
    rt_free(copy_path);

    if (ret == 0)
    {
        lwp_put_to_user(buf, &statbuff, sizeof statbuff);
    }

    return ret;
}

/**
 * @brief Retrieves metadata about a file or symbolic link.
 *
 * This system call obtains metadata for the specified file or symbolic link and stores
 * it in the `buf` structure. Unlike `sys_stat`, if the specified path refers to a
 * symbolic link, this function retrieves information about the link itself, not the
 * target it points to.
 *
 * @param[in]  file  A pointer to the path of the file or symbolic link to be queried.
 *                   The path must be a null-terminated string.
 * @param[out] buf   A pointer to a `struct stat` structure where the metadata will be
 *                   stored. This structure must be allocated by the caller.
 *
 * @return sysret_t  Returns a status code:
 *                    - `0`: The operation completed successfully, and the metadata
 *                      has been written to `buf`.
 *                   - Other error codes may indicate issues with the file path.
 *
 * @note This function is particularly useful for handling symbolic links when you want
 *       to get information about the link itself rather than the target file or directory.
 *       The `file` path must be valid and accessible by the calling process.
 *
 * @warning Passing a `NULL` pointer for `file` or `buf` may result in undefined behavior.
 *          Always check inputs for validity before invoking this function.
 */
sysret_t sys_lstat(const char *file, struct stat *buf)
{
    int ret = 0;
    size_t len;
    size_t copy_len;
    char *copy_path;
    struct stat statbuff = { 0 };

    if (!lwp_user_accessable((void *)buf, sizeof(struct stat)))
    {
        return -EFAULT;
    }

    len = lwp_user_strlen(file);
    if (len <= 0)
    {
        return -EFAULT;
    }

    copy_path = (char *)rt_malloc(len + 1);
    if (!copy_path)
    {
        return -ENOMEM;
    }

    copy_len = lwp_get_from_user(copy_path, (void *)file, len);
    if (copy_len == 0)
    {
        rt_free(copy_path);
        return -EFAULT;
    }
    copy_path[copy_len] = '\0';
#ifdef RT_USING_DFS_V2
    ret = _SYS_WRAP(dfs_file_lstat(copy_path, &statbuff));
#else
    ret = _SYS_WRAP(stat(copy_path, &statbuff));
#endif
    rt_free(copy_path);

    if (ret == 0)
    {
        lwp_put_to_user(buf, &statbuff, sizeof statbuff);
    }

    return ret;
}
