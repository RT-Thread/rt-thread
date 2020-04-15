/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-08-14     Bernard      the first version
 */

#ifndef __STDLIB_H__
#define __STDLIB_H__

#include <sys/types.h>

#if !defined (RT_USING_NEWLIB) && defined (RT_USING_MINILIBC)
int atoi(const char *nptr);
long int atol(const char *nptr);

int rand(void);
int rand_r(unsigned int *seed);
void srand(unsigned int seed);

void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void *calloc(size_t nelem, size_t elsize);
void abort(void);
#endif

#endif
