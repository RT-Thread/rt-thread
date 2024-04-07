/*
 * Copyright (c) 2004, Bull SA. All rights reserved.
 * Created by:  Laurent.Vivier@bull.net
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 */

 /* test if stdlib.h exists and can be included */

// #define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <sys/time.h>

#ifndef __compar_fn_t_defined
#define __compar_fn_t_defined
typedef int (*__compar_fn_t) (const void *, const void *);
#endif

void                (*test_abort)(void);
int                 (*test_abs)(int);
double              (*test_atof)(const char *__nptr);
int                 (*test_atoi)(const char *__nptr);
long                (*test_atol)(const char *__nptr);
long long           (*test_atoll)(const char *__nptr);
void *              (*test_bsearch)(const void *__key, const void *__base, size_t __nmemb, size_t __size, __compar_fn_t _compar);
void *              (*test_calloc)(size_t, size_t);
div_t               (*test_div)(int __numer, int __denom);
void                (*test_free)(void *);
char *              (*test_getenv)(const char *__string);
long                (*test_labs)(long);
ldiv_t              (*test_ldiv)(long __numer, long __denom);
void *              (*test_malloc)(size_t);
void                (*test_qsort)(void *__base, size_t __nmemb, size_t __size, __compar_fn_t _compar);
int                 (*test_rand)(void);
int                 (*test_rand_r)(unsigned *__seed);
void *              (*test_realloc)(void *, size_t);
int                 (*test_setenv)(const char *__string, const char *__value, int __overwrite);
void                (*test_srand)(unsigned __seed);
double              (*test_strtod)(const char *__restrict __n, char **__restrict __end_PTR);
float               (*test_strtof)(const char *__restrict __n, char **__restrict __end_PTR);
long                (*test_strtol)(const char *__restrict __n, char **__restrict __end_PTR, int __base);
long double         (*test_strtold)(const char *__restrict, char **__restrict);
long long           (*test_strtoll)(const char *__restrict __n, char **__restrict __end_PTR, int __base);
unsigned long       (*test_strtoul)(const char *__restrict __n, char **__restrict __end_PTR, int __base);
unsigned long long  (*test_strtoull)(const char *__restrict __n, char **__restrict __end_PTR, int __base);
int                 (*test_unsetenv)(const char *__string);



__attribute__((unused)) static int test_defined()
{
    test_abort = abort;
    test_abs = abs;
    test_atof = atof;
    test_atoi = atoi;
    test_atol = atol;
    test_atoll = atoll;
    test_bsearch = bsearch;
    test_calloc = calloc;
    test_div = div;
    test_free = free;
    test_getenv = getenv;
    test_labs = labs;
    test_ldiv = ldiv;
    test_malloc = malloc;
    test_qsort = qsort;
    test_rand = rand;
    // test_rand_r = rand_r;
    test_realloc = realloc;
    // test_setenv = setenv;
    test_srand = srand;
    test_strtod = strtod;
    test_strtof = strtof;
    test_strtol = strtol;
    test_strtold = strtold;
    test_strtoll = strtoll;
    test_strtoul = strtoul;
    test_strtoull = strtoull;
    // test_unsetenv = unsetenv;

    return 0;
}

