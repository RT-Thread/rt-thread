/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-02-23     Jesven         first version.
 */

#ifndef LWP_PID_H__
#define LWP_PID_H__

#ifdef __cplusplus
extern "C" {
#endif

struct rt_lwp;

struct rt_lwp* lwp_new(void);
void lwp_free(struct rt_lwp* lwp);

void lwp_ref_inc(struct rt_lwp *lwp);
void lwp_ref_dec(struct rt_lwp *lwp);

struct rt_lwp* lwp_from_pid(pid_t pid);
pid_t lwp_to_pid(struct rt_lwp* lwp);

int32_t lwp_name2pid(const char* name);
char* lwp_pid2name(int32_t pid);

int lwp_getpid(void);

pid_t waitpid(pid_t pid, int *status, int options);
long list_process(void);

#ifdef __cplusplus
}
#endif

#endif
