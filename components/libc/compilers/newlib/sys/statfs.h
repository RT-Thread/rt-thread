/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef __RTT_STATFS_H__
#define __RTT_STATFS_H__

#include <rtthread.h>

struct statfs
{
	rt_size_t f_bsize; 	 /* block size */
	rt_size_t f_blocks;  /* total data blocks in file system */
	rt_size_t f_bfree;	 /* free blocks in file system */
};

#endif
