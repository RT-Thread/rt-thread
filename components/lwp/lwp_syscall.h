/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-12     Jesven       the first version
 */

#ifndef __LWP_SYSCALL_H__
#define __LWP_SYSCALL_H__

#include <stdint.h>
#include <rtthread.h>
#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h> /* rename() */
#include <sys/stat.h>
#include <sys/statfs.h> /* statfs() */
#include <poll.h>
#include <sys/time.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef long suseconds_t;       /* microseconds (signed) */
typedef uint32_t id_t;          /* may contain pid, uid or gid */

/*
 * Process priority specifications to get/setpriority.
 */
#define	PRIO_MIN	    (-20)
#define	PRIO_MAX	    20

#define	PRIO_PROCESS	0       /* only support lwp process */
#define	PRIO_PGRP	    1
#define	PRIO_USER	    2

const char *lwp_get_syscall_name(rt_uint32_t number);
const void *lwp_get_sys_api(rt_uint32_t number);

void sys_exit(int value);
ssize_t sys_read(int fd, void *buf, size_t nbyte);
ssize_t sys_write(int fd, const void *buf, size_t nbyte);
off_t sys_lseek(int fd, off_t offset, int whence);
int sys_open(const char *name, int mode, ...);
int sys_close(int fd);
int sys_ioctl(int fd, unsigned long cmd, void* data);
int sys_fstat(int file, struct stat *buf);
int sys_poll(struct pollfd *fds, nfds_t nfds, int timeout);
int sys_nanosleep(const struct timespec *rqtp, struct timespec *rmtp);
int sys_gettimeofday(struct timeval *tp, struct timezone *tzp);
int sys_settimeofday(const struct timeval *tv, const struct timezone *tzp);
int sys_exec(char *filename, int argc, char **argv, char **envp);
int sys_kill(int pid, int sig);
int sys_getpid(void);
int sys_getpriority(int which, id_t who);
int sys_setpriority(int which, id_t who, int prio);
rt_sem_t sys_sem_create(const char *name, rt_uint32_t value, rt_uint8_t flag);
rt_err_t sys_sem_delete(rt_sem_t sem);
rt_err_t sys_sem_take(rt_sem_t sem, rt_int32_t time);
rt_err_t sys_sem_release(rt_sem_t sem);
rt_mutex_t sys_mutex_create(const char *name, rt_uint8_t flag);
rt_err_t sys_mutex_delete(rt_mutex_t mutex);
rt_err_t sys_mutex_take(rt_mutex_t mutex, rt_int32_t time);
rt_err_t sys_mutex_release(rt_mutex_t mutex);
rt_event_t sys_event_create(const char *name, rt_uint8_t flag);
rt_err_t sys_event_delete(rt_event_t event);
rt_err_t sys_event_send(rt_event_t event, rt_uint32_t set);
rt_err_t sys_event_recv(rt_event_t event, rt_uint32_t set, rt_uint8_t opt, rt_int32_t timeout, rt_uint32_t *recved);
rt_mailbox_t sys_mb_create(const char *name, rt_size_t size, rt_uint8_t flag);
rt_err_t sys_mb_delete(rt_mailbox_t mb);
rt_err_t sys_mb_send(rt_mailbox_t mb, rt_ubase_t value);
rt_err_t sys_mb_send_wait(rt_mailbox_t mb, rt_ubase_t value, rt_int32_t timeout);
rt_err_t sys_mb_recv(rt_mailbox_t mb, rt_ubase_t *value, rt_int32_t timeout);
rt_mq_t sys_mq_create(const char *name, rt_size_t msg_size, rt_size_t max_msgs, rt_uint8_t flag);
rt_err_t sys_mq_delete(rt_mq_t mq);
rt_err_t sys_mq_send(rt_mq_t mq, void *buffer, rt_size_t size);
rt_err_t sys_mq_urgent(rt_mq_t mq, void *buffer, rt_size_t size);
rt_err_t sys_mq_recv(rt_mq_t mq, void *buffer, rt_size_t size, rt_int32_t timeout);
rt_thread_t sys_thread_create(void *arg[]);
rt_err_t sys_thread_delete(rt_thread_t thread);
rt_err_t sys_thread_startup(rt_thread_t thread);
rt_thread_t sys_thread_self(void);
int sys_channel_open(const char *name, int flags);
rt_err_t sys_channel_close(int fd);
rt_err_t sys_channel_send(int fd, rt_channel_msg_t data);
rt_err_t sys_channel_send_recv(int fd, rt_channel_msg_t data, rt_channel_msg_t data_ret);
rt_err_t sys_channel_reply(int fd, rt_channel_msg_t data);
rt_err_t sys_channel_recv(int fd, rt_channel_msg_t data);
void sys_enter_critical(void);
void sys_exit_critical(void);

int sys_log(const char* log, int size);

#ifdef __cplusplus
}
#endif

#endif
