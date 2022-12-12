/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-01-12     Meco Man     The first version.
 */

#ifndef __POSIX_STRING_H__
#define __POSIX_STRING_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <string.h>

void bzero(void * s, size_t n);
void bcopy(const void * src, void * dest, size_t n);
int bcmp(const void * s1, const void * s2, size_t n);
void explicit_bzero(void * s, size_t n);
char *index(const char * s, int c);
char *rindex(const char * s, int c);
int ffs(int i);
int ffsl(long i);
int ffsll(long long i);
void *memrchr(const void* ptr, int ch, size_t pos);
size_t strnlen(const char *s, size_t maxlen);
char* strchrnul(const char *s, int c);
int strcasecmp(const char * s1, const char * s2);
int strncasecmp(const char * s1, const char * s2, size_t n);
char *strdup(const char *s);
char *strndup(const char *s, size_t size);
char *strtok_r(char *str, const char *delim, char **saveptr);

#ifdef __cplusplus
}
#endif

#endif /* __POSIX_STRING_H__ */
