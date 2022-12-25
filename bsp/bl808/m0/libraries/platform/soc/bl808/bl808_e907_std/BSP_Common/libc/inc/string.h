/*
 * string.h
 */

#ifndef _STRING_H
#define _STRING_H

#include <extern.h>
#include <stddef.h>
#include <stdint.h>
#if __riscv_xlen == 64
__extern void memswap(void *m1, void *m2, size_t n);
__extern void *memmem(const void *haystack, size_t n, const void *needle, size_t m);
__extern char *strtok_r(char *, const char *, char **);
__extern char *strsep(char **, const char *);
#   include_next <string.h>
#else
__extern void *memccpy(void *, const void *, int, size_t);
__extern void *memchr(const void *, int, size_t);
__extern void *memrchr(const void *, int, size_t);
__extern int memcmp(const void *, const void *, size_t);
__extern void *memcpy(void *, const void *, size_t);
__extern void *memmove(void *, const void *, size_t);
__extern void *memset(void *, int, size_t);
__extern void *memmem(const void *, size_t, const void *, size_t);
__extern void memswap(void *, void *, size_t);
__extern void bzero(void *, size_t);
__extern int strcasecmp(const char *, const char *);
__extern int strncasecmp(const char *, const char *, size_t);
__extern char *strcat(char *, const char *);
__extern char *strchr(const char *, int);
__extern char *strrchr(const char *, int);
__extern int strcmp(const char *, const char *);
__extern char *strcpy(char *, const char *);
__extern size_t strcspn(const char *, const char *);
__extern size_t strlen(const char *);
__extern size_t strnlen(const char *, size_t);
__extern char *strncat(char *, const char *, size_t);
__extern size_t strlcat(char *, const char *, size_t);
__extern int strncmp(const char *, const char *, size_t);
__extern char *strncpy(char *, const char *, size_t);
__extern size_t strlcpy(char *, const char *, size_t);
__extern char *strpbrk(const char *, const char *);
__extern char *strsep(char **, const char *);
__extern size_t strspn(const char *, const char *);
__extern char *strstr(const char *, const char *);
__extern char *strtok(char *, const char *);
__extern char *strtok_r(char *, const char *, char **);
char *index(const char *s, int c);
#endif /* __riscv_xlen == 64 */

#endif				/* _STRING_H */
