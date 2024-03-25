/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-13     Shell        init ver.
 */

/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2008 Ed Schouten <ed@FreeBSD.org>
 * All rights reserved.
 *
 * Portions of this software were developed under sponsorship from Snow
 * B.V., the Netherlands.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _SYS_TTYDISC_H_
#define _SYS_TTYDISC_H_

#ifndef __LWP_TERMINAL_H__
#error "can only be included through <terminal.h>"
#endif /* !__LWP_TERMINAL_H__ */

#include <rtdef.h>

struct rt_wqueue;
struct rt_thread;
struct lwp_tty;
struct uio;

/* Top half routines. */
void ttydisc_open(struct lwp_tty *tp);
void ttydisc_close(struct lwp_tty *tp);
int ttydisc_read(struct lwp_tty *tp, struct uio *uio, int ioflag);
int ttydisc_write(struct lwp_tty *tp, struct uio *uio, int ioflag);
void ttydisc_optimize(struct lwp_tty *tp);

/* Bottom half routines. */
void ttydisc_modem(struct lwp_tty *tp, int open);
#define ttydisc_can_bypass(tp) ((tp)->t_flags & TF_BYPASS)
int ttydisc_rint(struct lwp_tty *tp, char c, int flags);
size_t ttydisc_rint_simple(struct lwp_tty *tp, const void *buf, size_t len);
size_t ttydisc_rint_bypass(struct lwp_tty *tp, const void *buf, size_t len);
void ttydisc_rint_done(struct lwp_tty *tp);
size_t ttydisc_rint_poll(struct lwp_tty *tp);
size_t ttydisc_getc(struct lwp_tty *tp, void *buf, size_t len);
int ttydisc_getc_uio(struct lwp_tty *tp, struct uio *uio);
size_t ttydisc_getc_poll(struct lwp_tty *tp);

/* Error codes for ttydisc_rint(). */
#define TRE_FRAMING 0x01
#define TRE_PARITY  0x02
#define TRE_OVERRUN 0x04
#define TRE_BREAK   0x08

#endif /* !_SYS_TTYDISC_H_ */
