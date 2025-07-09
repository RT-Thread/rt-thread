/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * This file defines the libnosys.a syscall functions.
 * After upgraded to ARMGCC 12.2.1 with binutils 2.39, there are build warnings
 * when link the libnosys.a, such as using -lnosys or using --specs=--specs=nosys.specs.
 *
 * The build warnings are like:
 * (libc_a-closer.o): in function `_close_r': closer.c:(.text._close_r+0xc):
 * warning: _close is not implemented and will always fail
 *
 * If you don't want to use the functions in this file, then define SDK_USE_SYSCALL_STUB
 * as 0.
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef SDK_USE_SYSCALL_STUB
#define SDK_USE_SYSCALL_STUB 1
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
#if defined(__GNUC__)

#if SDK_USE_SYSCALL_STUB

#include <stdint.h>
#include <errno.h>
#include <sys/stat.h>

/*
 * When SDK_DEBUGCONSOLE_UART defined, the _write and _read will be defined in
 * fsl_debug_console.
 */
#if !defined(SDK_DEBUGCONSOLE_UART)
int __attribute__((weak)) _write(int handle, char *buffer, int size);
int __attribute__((weak)) _write(int handle, char *buffer, int size)
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak)) _read(int handle, char *buffer, int size);
int __attribute__((weak)) _read(int handle, char *buffer, int size)
{
    errno = ENOSYS;
    return -1;
}
#endif /* SDK_DEBUGCONSOLE_UART */

int __attribute__((weak)) _close(int f);
int __attribute__((weak)) _close(int f)
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak)) _lseek(int f, int ptr, int dir);
int __attribute__((weak)) _lseek(int f, int ptr, int dir)
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak)) _fstat(int fs, struct stat *st);
int __attribute__((weak)) _fstat(int fs, struct stat *st)
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak)) _getpid(void);
int __attribute__((weak)) _getpid(void)
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak)) _isatty(int f);
int __attribute__((weak)) _isatty(int f)
{
    errno = ENOSYS;
    return 0;
}

int __attribute__((weak)) _kill(int pid, int sig);
int __attribute__((weak)) _kill(int pid, int sig)
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak)) _link(const char *path1, const char *path2);
int __attribute__((weak)) _link(const char *path1, const char *path2)
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak)) _unlink(const char *path);
int __attribute__((weak)) _unlink(const char *path)
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak)) _open(const char *filename, int oflag);
int __attribute__((weak)) _open(const char *filename, int oflag)
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak)) _stat (const char *f, struct stat *st);
int __attribute__((weak)) _stat (const char *f, struct stat *st)
{
    errno = ENOSYS;
    return -1;
}

#endif /* SDK_USE_SYSCALL_STUB */

#endif /* __GNUC__ */
