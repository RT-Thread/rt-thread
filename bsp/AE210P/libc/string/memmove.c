#include <string.h>

__attribute__((used))
void *memmove(void *dest, const void *src, size_t n)
{
	char *destp = dest;
	const char *srcp = src;

	if (srcp < destp)
		while (n--)
			destp[n] = srcp[n];
	else
		while (n--)
			*destp++ = *srcp++;

	return dest;
}
