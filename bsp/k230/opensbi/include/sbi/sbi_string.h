/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Atish Patra <atish.patra@wdc.com>
 */

#ifndef __STRING_H__
#define __STRING_H__

#include <sbi/sbi_types.h>

/*
  Provides sbi_strcmp for the completeness of supporting string functions.
  it is not recommended to use sbi_strcmp() but use sbi_strncmp instead.
*/

int sbi_strcmp(const char *a, const char *b);

int sbi_strncmp(const char *a, const char *b, size_t count);

size_t sbi_strlen(const char *str);

size_t sbi_strnlen(const char *str, size_t count);

char *sbi_strcpy(char *dest, const char *src);

char *sbi_strncpy(char *dest, const char *src, size_t count);

char *sbi_strchr(const char *s, int c);

char *sbi_strrchr(const char *s, int c);

void *sbi_memset(void *s, int c, size_t count);

void *sbi_memcpy(void *dest, const void *src, size_t count);

void *sbi_memmove(void *dest, const void *src, size_t count);

int sbi_memcmp(const void *s1, const void *s2, size_t count);

void *sbi_memchr(const void *s, int c, size_t count);

#endif
