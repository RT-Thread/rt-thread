#ifndef __STRING_H__
#define __STRING_H__

#include <stddef.h>

extern void *memcpy(void *dest, const void *src, size_t n);
extern void *memmove(void *dest, const void *src, size_t n);
extern void *memset(void *s, int c, size_t n);
extern void	bzero(void *, size_t);

extern char *strcat(char *dest, const char *src);
extern char *strncat(char *dest, const char *src, size_t n);

extern int strcasecmp(const char *s1, const char *s2);
extern int strncasecmp(const char *s1, const char *s2, size_t n);

extern int strcmp(const char *s1, const char *s2);
extern int strncmp(const char *s1, const char *s2, size_t n);

extern char *strcpy(char *dest, const void *src);
extern char *strncpy(char *dest, const void *src, size_t n);

extern char *strdup(const char *s);
extern char *strndup(const char *s, size_t n);
extern size_t strlen(const char *s);
extern size_t strnlen(const char *s, size_t maxlen);

extern char *strstr(const char *haystack, const char *needle);
extern unsigned long int strtoul(const char *nptr, char **endptr, int base);

extern char *strupr(char *str);
/* wchar_t */
#ifndef WCHAR
typedef unsigned short WCHAR;
#endif  // WCHAR

#ifndef wchar_t
typedef unsigned short wchar_t;
#endif  // wchar

extern wchar_t *wcscat(wchar_t *str_dst, const wchar_t *str_src);
extern int      wcscmp(const wchar_t *string1, const wchar_t *string2);
extern int      wcsncmp(const wchar_t *string1, const wchar_t *string2, int count);
extern wchar_t *wcscpy(wchar_t *str_dst, const wchar_t *str_src);
extern wchar_t *wcsncpy(wchar_t *str_dst, const wchar_t *str_src, int count);
extern int      wcslen(const wchar_t *str);
extern wchar_t *wcsupr(wchar_t *str);
extern wchar_t *wcslwr(wchar_t *str);


#endif /* __STRING_H__ */
