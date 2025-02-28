/*
 * Copyright (c) mlibc & plct lab
 *
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/8/8   0Bitbiscuits the first version
 */
#ifndef MLIBC_SYS_SIGNALFD_H__
#define MLIBC_SYS_SIGNALFD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <fcntl.h>
#include <alltypes.h>

/* Signal file descriptor state */
#define SFD_CLOEXEC O_CLOEXEC
#define SFD_NONBLOCK O_NONBLOCK

struct signalfd_siginfo {
    uint32_t  ssi_signo;
    int32_t   ssi_errno;
    int32_t   ssi_code;
    uint32_t  ssi_pid;
    uint32_t  ssi_uid;
    int32_t   ssi_fd;
    uint32_t  ssi_tid;
    uint32_t  ssi_band;
    uint32_t  ssi_overrun;
    uint32_t  ssi_trapno;
    int32_t   ssi_status;
    int32_t   ssi_int;
    uint64_t  ssi_ptr;
    uint64_t  ssi_utime;
    uint64_t  ssi_stime;
    uint64_t  ssi_addr;
    uint16_t  ssi_addr_lsb;
    uint16_t  __pad2;
    int32_t   ssi_syscall;
    uint64_t  ssi_call_addr;
    uint32_t  ssi_arch;
    uint8_t   __pad[128-14*4-5*8-2*2];
};

int signalfd(int, const sigset_t *, int);

#ifdef __cplusplus
}
#endif

#endif /* MLIBC_SYS_SIGNALFD_H__ */
