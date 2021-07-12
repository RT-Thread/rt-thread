/*
 * Copyright (c) 2019-2020, Xim
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#ifndef _ASM_SBI_DEF_H
#define _ASM_SBI_DEF_H

#define SBI_SET_TIMER 0
#define SBI_CONSOLE_PUTCHAR 1
#define SBI_CONSOLE_GETCHAR 2
#define SBI_CLEAR_IPI 3
#define SBI_SEND_IPI 4
#define SBI_REMOTE_FENCE_I 5
#define SBI_REMOTE_SFENCE_VMA 6
#define SBI_REMOTE_SFENCE_VMA_ASID 7
#define SBI_SHUTDOWN 8

#define SBI_CONSOLE_PUTSTR 9

#define SBI_SD_WRITE 10
#define SBI_SD_READ 11
#define SBI_NET_WRITE 12
#define SBI_NET_READ 13

#endif /* _ASM_SBI_DEF_H */
