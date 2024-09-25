/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Atish Patra <atish.patra@wdc.com>
 */

/*
 * Simple libc functions. These are not optimized at all and might have some
 * bugs as well. Use any optimized routines from newlib or glibc if required.
 */

#include <sbi/sbi_string.h>

/*
  Provides sbi_strcmp for the completeness of supporting string functions.
  it is not recommended to use sbi_strcmp() but use sbi_strncmp instead.
*/
int sbi_strcmp(const char *a, const char *b)
{
	/* search first diff or end of string */
	for (; *a == *b && *a != '\0'; a++, b++)
		;

	return *a - *b;
}

int sbi_strncmp(const char *a, const char *b, size_t count)
{
	/* search first diff or end of string */
	for (; count > 0 && *a == *b && *a != '\0'; a++, b++, count--)
		;

	return *a - *b;
}

size_t sbi_strlen(const char *str)
{
	unsigned long ret = 0;

	while (*str != '\0') {
		ret++;
		str++;
	}

	return ret;
}

size_t sbi_strnlen(const char *str, size_t count)
{
	unsigned long ret = 0;

	while (*str != '\0' && ret < count) {
		ret++;
		str++;
		count--;
	}

	return ret;
}

char *sbi_strcpy(char *dest, const char *src)
{
	char *ret = dest;

	while (*src != '\0') {
		*dest++ = *src++;
	}

	return ret;
}

char *sbi_strncpy(char *dest, const char *src, size_t count)
{
	char *ret = dest;

	while (count-- && *src != '\0') {
		*dest++ = *src++;
	}

	return ret;
}

char *sbi_strchr(const char *s, int c)
{
	while (*s != '\0' && *s != (char)c)
		s++;

	if (*s == '\0')
		return NULL;
	else
		return (char *)s;
}

char *sbi_strrchr(const char *s, int c)
{
	const char *last = s + sbi_strlen(s);

	while (last > s && *last != (char)c)
		last--;

	if (*last != (char)c)
		return NULL;
	else
		return (char *)last;
}
void *sbi_memset(void *s, int c, size_t count)
{
	char *temp = s;

	while (count > 0) {
		count--;
		*temp++ = c;
	}

	return s;
}

void *sbi_memcpy(void *dest, const void *src, size_t count)
{
	char *temp1	  = dest;
	const char *temp2 = src;

	while (count > 0) {
		*temp1++ = *temp2++;
		count--;
	}

	return dest;
}

void *sbi_memmove(void *dest, const void *src, size_t count)
{
	char *temp1	  = (char *)dest;
	const char *temp2 = (char *)src;

	if (src == dest)
		return dest;

	if (dest < src) {
		while (count > 0) {
			*temp1++ = *temp2++;
			count--;
		}
	} else {
		temp1 = dest + count - 1;
		temp2 = src + count - 1;

		while (count > 0) {
			*temp1-- = *temp2--;
			count--;
		}
	}

	return dest;
}

int sbi_memcmp(const void *s1, const void *s2, size_t count)
{
	const char *temp1 = s1;
	const char *temp2 = s2;

	for (; count > 0 && (*temp1 == *temp2); count--) {
		temp1++;
		temp2++;
	}

	if (count > 0)
		return *(unsigned char *)temp1 - *(unsigned char *)temp2;
	else
		return 0;
}

void *sbi_memchr(const void *s, int c, size_t count)
{
	const unsigned char *temp = s;

	while (count > 0) {
		if ((unsigned char)c == *temp++) {
			return (void *)(temp - 1);
		}
		count--;
	}

	return NULL;
}
