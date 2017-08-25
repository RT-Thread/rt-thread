#include <string.h>

__attribute__((used))
char *strcpy(char *dest, const void *src)
{
	char *destp = dest;
	char *srcp = (char *)src;

	while (*srcp)
		*destp++ = *srcp++;

	*destp = '\0';

	return dest;
}

__attribute__((used))
char *strncpy(char *dest, const void *src, size_t n)
{
	char *destp = dest;
	char *srcp = (char *)src;

	while (*srcp && n--)
		*destp++ = *srcp++;

	if (n)
		*destp = '\0';

	return dest;
}
