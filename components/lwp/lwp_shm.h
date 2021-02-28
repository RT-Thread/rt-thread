/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-12     Jesven       first version
 */
#ifndef  __LWP_SHM_H__
#define  __LWP_SHM_H__

#include <lwp_avl.h>

#ifdef __cplusplus
extern "C" {
#endif

int lwp_shmget(size_t key, size_t size, int create);
int lwp_shmrm(int id);
void* lwp_shmat(int id, void* shm_vaddr);
int lwp_shmdt(void* shm_vaddr);
void *lwp_shminfo(int id);
int lwp_shm_ref_inc(struct rt_lwp *lwp, void *shm_vaddr);
int lwp_shm_ref_dec(struct rt_lwp *lwp, void *shm_vaddr);

#ifdef __cplusplus
}
#endif

#endif  /*__LWP_SHM_H__*/
