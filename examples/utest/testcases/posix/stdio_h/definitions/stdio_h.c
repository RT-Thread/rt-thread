/*
 * Copyright (c) 2004, Bull SA. All rights reserved.
 * Created by:  Laurent.Vivier@bull.net
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 */

 /* test if stdio.h exists and can be included */

// #define _POSIX_C_SOURCE 2

#include <stdio.h>
#include <stdarg.h>

void    (*test_clearerr)(FILE *);
int     (*test_fclose)(FILE *);
FILE *  (*test_fdopen)(int, const char *);
int     (*test_feof)(FILE *);
int     (*test_ferror)(FILE *);
int     (*test_fflush)(FILE *);
int     (*test_fgetc)(FILE *);
char *  (*test_fgets)(char *__restrict, int, FILE *__restrict);
int     (*test_fileno)(FILE *);
void    (*test_flockfile)(FILE *);
FILE *  (*test_fopen)(const char *__restrict _name, const char *__restrict _type);
int     (*test_fprintf)(FILE *__restrict, const char *__restrict, ...);
int     (*test_fputc)(int, FILE *);
int     (*test_fputs)(const char *__restrict, FILE *__restrict);
size_t  (*test_fread)(void *__restrict, size_t _size, size_t _n, FILE *__restrict);
FILE *  (*test_freopen)(const char *__restrict, const char *__restrict, FILE *__restrict);
int     (*test_fscanf)(FILE *__restrict, const char *__restrict, ...);
int     (*test_ftrylockfile)(FILE *);
void    (*test_funlockfile)(FILE *);
size_t  (*test_fwrite)(const void *__restrict , size_t _size, size_t _n, FILE *);
int     (*test_getc)(FILE *);
int     (*test_getc_unlocked)(FILE *);
int     (*test_getchar)(void);
int     (*test_getchar_unlocked)(void);
char *  (*test_gets)(char *);
void    (*test_perror)(const char *);
int     (*test_printf)(const char *__restrict, ...);
int     (*test_putc)(int, FILE *);
int     (*test_putc_unlocked)(int, FILE *);
int     (*test_putchar)(int);
int     (*test_putchar_unlocked)(int);
int     (*test_puts)(const char *);
int     (*test_scanf)(const char *__restrict, ...);
void    (*test_setbuf)(FILE *__restrict, char *__restrict);
int     (*test_setvbuf)(FILE *__restrict, char *__restrict, int, size_t);
int     (*test_snprintf)(char *__restrict, size_t, const char *__restrict, ...);
int     (*test_sprintf)(char *__restrict, const char *__restrict, ...);
int     (*test_sscanf)(const char *__restrict, const char *__restrict, ...);
int     (*test_ungetc)(int, FILE *);

FILE *test_stderr;
FILE *test_stdin;
FILE *test_stdout;

int     (*test_vfprintf)(FILE *restrict, const char *restrict, va_list);
int     (*test_vfscanf)(FILE *restrict, const char *restrict, va_list);
int     (*test_vprintf)(const char *restrict, va_list);
int     (*test_vscanf)(const char *restrict, va_list);
int     (*test_vsnprintf)(char *restrict, size_t, const char *restrict, va_list);
int     (*test_vsprintf)(char *restrict, const char *restrict, va_list);
int     (*test_vsscanf)(const char *restrict, const char *restrict, va_list);

__attribute__((unused)) static int test_defined()
{
    test_clearerr = clearerr;
    test_fclose = fclose;
    // test_fdopen = fdopen;
    test_feof = feof;
    test_ferror = ferror;
    test_fflush = fflush;
    test_fgetc = fgetc;
    test_fgets = fgets;
    // test_fileno = fileno;
    // test_flockfile = flockfile;
    test_fopen = fopen;
    test_fprintf = fprintf;
    test_fputc = fputc;
    test_fputs = fputs;
    test_fread = fread;
    test_freopen = freopen;
    test_fscanf = fscanf;
    // test_ftrylockfile = ftrylockfile;
    // test_funlockfile = funlockfile;
    test_fwrite = fwrite;
    test_getc = getc;
    // test_getc_unlocked = getc_unlocked;
    test_getchar = getchar;
    test_gets = gets;
    test_perror = perror;
    test_printf = printf;
    test_putc = putc;
    // test_putc_unlocked = putc_unlocked;
    test_putchar = putchar;
    // test_putchar_unlocked = putchar_unlocked;
    test_puts = puts;
    test_scanf = scanf;
    test_setbuf = setbuf;
    test_setvbuf = setvbuf;
    test_snprintf = snprintf;
    test_sprintf = sprintf;
    test_sscanf = sscanf;
    test_ungetc = ungetc;

    test_stderr = stderr;
    test_stdin = stdin;
    test_stdout = stdout;

    test_vfprintf = vfprintf;
    test_vfscanf  = vfscanf;
    test_vprintf  = vprintf;
    test_vscanf  = vscanf;
    test_vsnprintf  = vsnprintf;
    test_vsprintf  = vsprintf;
    test_vsscanf  = vsscanf;

    return 0;
}

