/*
 * stdlib.h
 */

#ifndef _STDLIB_H
#define _STDLIB_H

#include <extern.h>
#include <libc_compiler.h>
#include <stddef.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

static __inline int abs(int __n)
{
	return (__n < 0) ? -__n : __n;
}

#if __riscv_xlen == 64
#   include_next <stdio.h>
__extern long jrand48(unsigned short *);
#else
__extern int atoi(const char *);
__extern double atof(const char *);
__extern long atol(const char *);
__extern long long atoll(const char *);
static __inline long labs(long __n)
{
	return (__n < 0L) ? -__n : __n;
}

static __inline long long llabs(long long __n)
{
	return (__n < 0LL) ? -__n : __n;
}

__extern long strtol(const char *, char **, int);
__extern long long strtoll(const char *, char **, int);
__extern unsigned long strtoul(const char *, char **, int);
__extern unsigned long long strtoull(const char *, char **, int);

typedef int (*__comparefunc_t) (const void *, const void *);
__extern void *bsearch(const void *, const void *, size_t, size_t,
		       __comparefunc_t);
__extern void qsort(void *, size_t, size_t, __comparefunc_t);

__extern long jrand48(unsigned short *);
__extern long mrand48(void);
__extern long nrand48(unsigned short *);
__extern long lrand48(void);
__extern unsigned short *seed48(unsigned short *);
__extern void srand48(long);

#define RAND_MAX 0x7fffffff
__extern int rand(void);
__extern void srand(unsigned int __s);
__extern long random(void);
__extern void srandom(unsigned int __s);
#endif /* __riscv_xlen == 64 */

#endif				/* _STDLIB_H */
