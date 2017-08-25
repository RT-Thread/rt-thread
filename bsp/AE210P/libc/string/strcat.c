#include <string.h>

__attribute__((used))
char *strcat(char *dest, const char *src)
{
	char *destp = dest;

	while (*destp)
		destp++;

	while (*src)
		*destp++ = *src++;

	*destp = '\0';

	return dest;
}

__attribute__((used))
char *strncat(char *dest, const char *src, size_t n)
{
	char *destp = dest;

	while (*destp)
		destp++;

	while (*src && n--)
		*destp++ = *src++;
	
	*destp = '\0';

	return dest;
}
