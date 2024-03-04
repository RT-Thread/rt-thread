/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-13     Shell        init ver.
 */

#ifndef __TTY_CONFIG_H__
#define __TTY_CONFIG_H__

/* default buffer size of tty siginfo */
#define LWP_TTY_PRBUF_SIZE 256

/*
 * System wide defaults for terminal state.
 */

/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)ttydefaults.h	8.4 (Berkeley) 1/21/94
 */

/*
 * Defaults on "first" open.
 */
#define TTYDEF_IFLAG        (BRKINT | ICRNL | IMAXBEL | IXON | IXANY | IUTF8)
#define TTYDEF_OFLAG        (OPOST | ONLCR)
#define TTYDEF_LFLAG_NOECHO (ICANON | ISIG | IEXTEN)
#define TTYDEF_LFLAG_ECHO \
    (TTYDEF_LFLAG_NOECHO | ECHO | ECHOE | ECHOKE | ECHOCTL)
#define TTYDEF_LFLAG TTYDEF_LFLAG_ECHO
#define TTYDEF_CFLAG (CREAD | CS8 | HUPCL)
#define TTYDEF_SPEED (B9600)

/*
 * Control Character Defaults
 */
/*
 * XXX: A lot of code uses lowercase characters, but control-character
 * conversion is actually only valid when applied to uppercase
 * characters. We just treat lowercase characters as if they were
 * inserted as uppercase.
 */
#define _CONTROL(c) \
    ((c) >= 'a' && (c) <= 'z' ? ((c) - 'a' + 1) : (((c) - 'A' + 1) & 0x7f))
#define CEOF     _CONTROL('D')
#define CEOL     0xff /* XXX avoid _POSIX_VDISABLE */
#define CERASE   0x7f
#define CERASE2  _CONTROL('H')
#define CINTR    _CONTROL('C')
#define CSTATUS  _CONTROL('T')
#define CKILL    _CONTROL('U')
#define CMIN     1
#define CQUIT    _CONTROL('\\')
#define CSUSP    _CONTROL('Z')
#define CTIME    0
#define CDSUSP   _CONTROL('Y')
#define CSTART   _CONTROL('Q')
#define CSTOP    _CONTROL('S')
#define CLNEXT   _CONTROL('V')
#define CDISCARD _CONTROL('O')
#define CWERASE  _CONTROL('W')
#define CREPRINT _CONTROL('R')
#define CEOT     CEOF
/* compat */
#define CBRK   CEOL
#define CRPRNT CREPRINT
#define CFLUSH CDISCARD

/* PROTECTED INCLUSION ENDS HERE */
#endif /* !__TTY_CONFIG_H__ */

/*
 * #define TTY_CONF_INCLUDE_CCHARS to include an array of default control
 * characters.
 */
#ifdef TTY_CONF_INCLUDE_CCHARS
#include <rtdef.h>
#include <termios.h>
#include <unistd.h>

static const cc_t tty_ctrl_charset[NCCS] = {
    [VINTR] = CINTR,
    [VQUIT] = CQUIT,
    [VERASE] = CERASE,
    [VKILL] = CKILL,
    [VEOF] = CEOF,
    [VSTART] = CSTART,
    [VSTOP] = CSTOP,
    [VSUSP] = CSUSP,
    [VREPRINT] = CREPRINT,
    [VDISCARD] = CDISCARD,
    [VWERASE] = CWERASE,
    [VLNEXT] = CLNEXT,
    [VMIN] = CMIN
#undef _CONTROL
};

#undef TTY_CONF_INCLUDE_CCHARS
#endif /* __TTY_CONFIG_H__ */
