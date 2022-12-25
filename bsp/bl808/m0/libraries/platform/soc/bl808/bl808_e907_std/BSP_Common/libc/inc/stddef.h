/*
 * stddef.h
 */

#ifndef _STDDEF_H
#define _STDDEF_H

#define _SIZE_T
typedef unsigned long size_t;

#define _PTRDIFF_T
typedef signed int ptrdiff_t;

#ifndef __ICCARM__
#define _WINT_T
typedef signed int wint_t;
#endif

#undef NULL
#ifdef __cplusplus
# define NULL 0
#else
# define NULL ((void *)0)
#endif

#undef offsetof
#define offsetof(t,m) ((size_t)&((t *)0)->m)

#endif				/* _STDDEF_H */
