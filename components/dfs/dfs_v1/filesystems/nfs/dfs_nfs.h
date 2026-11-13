/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __NFS_H__
#define __NFS_H__

/* Maximum payload in a single NFS READ/WRITE request, also used as the opaque
 * data cap when decoding READ replies, so both limits always change together. */
#define DFS_NFS_MAX_MTU 1024

int nfs_init(void);

#endif
