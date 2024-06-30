/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/08/21     ShaoJinchun  firset version
 */

#ifndef  __DFS_CROMFS_H__
#define  __DFS_CROMFS_H__

#include <stdint.h>

int dfs_cromfs_init(void);
uint8_t *cromfs_get_partition_data(uint32_t *len);

#endif  /*__DFS_CROMFS_H__*/
