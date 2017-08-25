#include <string.h>

__attribute__((used))
int strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2) {

		if (!*s1)
			return 0;
		++s1;
		++s2;
	}

	return *(unsigned char *)s1 - *(unsigned char *)s2;
}

__attribute__((used))
int strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 == *s2 && --n) {

		if (!*s1)
			return 0;
		++s1;
		++s2;
	}

	return *(unsigned char *)s1 - *(unsigned char *)s2;
}

