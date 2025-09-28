/*
 * Copyright (c) mlibc & plct lab
 *
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/8/8   0Bitbiscuits the first version
 */
#ifndef MLIBC_EPOLL_H__
#define MLIBC_EPOLL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/types.h>
#include <fcntl.h>

#include <alltypes.h>

/* The flag of file descriptor */
#define EPOLL_CLOEXEC       O_CLOEXEC
#define EPOLL_NONBLOCK      O_NONBLOCK

/* The event of file descriptor */
enum EPOLL_EVENTS           { __EPOLL_DUMMY };
#define EPOLLIN             0x001
#define EPOLLPRI            0x002
#define EPOLLOUT            0x004
#define EPOLLRDNORM         0x040
#define EPOLLNVAL           0x020
#define EPOLLRDBAND         0x080
#define EPOLLWRNORM         0x100
#define EPOLLWRBAND         0x200
#define EPOLLMSG            0x400
#define EPOLLERR            0x008
#define EPOLLHUP            0x010
#define EPOLLRDHUP          0x2000
#define EPOLLEXCLUSIVE      (1U<<28)
#define EPOLLWAKEUP         (1U<<29)
#define EPOLLONESHOT        (1U<<30)
#define EPOLLET             (1U<<31)

/* The control type of file descriptor */
#define EPOLL_CTL_ADD       1
#define EPOLL_CTL_DEL       2
#define EPOLL_CTL_MOD       3

typedef union epoll_data {
    void *ptr;
    int fd;
    uint32_t u32;
    uint64_t u64;
} epoll_data_t;

struct epoll_event {
    uint32_t events;
    epoll_data_t data;
};

int epoll_create(int);
int epoll_create1(int);
int epoll_ctl(int, int, int, struct epoll_event *);
int epoll_wait(int, struct epoll_event *, int, int);
int epoll_pwait(int, struct epoll_event *, int, int, const sigset_t *);

#ifdef __cplusplus
}
#endif

#endif /* MLIBC_SYS_EPOLL_H__ */