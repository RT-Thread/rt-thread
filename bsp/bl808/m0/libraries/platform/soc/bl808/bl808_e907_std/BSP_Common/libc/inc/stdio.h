/*
 * stdio.h
 */

#ifndef _STDIO_H
#define _STDIO_H

#include <extern.h>
#include <stdarg.h>
#include <stddef.h>

/* The actual IO functions are not included. */
#if __riscv_xlen == 64
#   include_next <stdio.h>
#else
__extern int sprintf(char *, const char *, ...);
__extern int vsprintf(char *, const char *, va_list);
__extern int snprintf(char *__restrict, size_t, const char *__restrict, ...);
__extern int vsnprintf(char *, size_t, const char *, va_list);
__extern int sscanf(const char *, const char *, ...);
__extern int vsscanf(const char *, const char *, va_list);
#endif /* __riscv_xlen == 64 */

#endif				/* _STDIO_H */
