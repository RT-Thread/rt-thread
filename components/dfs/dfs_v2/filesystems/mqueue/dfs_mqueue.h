/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-04     zhkag        first Version
 */

#ifndef __DFS_MQUEUE_H__
#define __DFS_MQUEUE_H__

#include <rtthread.h>

struct mqueue_file {
    char name[RT_NAME_MAX]; /* file name */
    rt_uint16_t msg_size;   /**< message size of each message */
    rt_uint16_t max_msgs;   /**< max number of messages */
    rt_list_t list;
    rt_uint8_t *data; /* file date ptr */
    rt_size_t size;   /* file size */
};

struct mqueue_file *dfs_mqueue_lookup(const char *path, rt_size_t *size);
void dfs_mqueue_insert_after(rt_list_t *n);

#endif
