#include <string.h>

__attribute__((used))
void *memset(void *s, int c, size_t n)
{
	while (n--)
		*(unsigned char *)s++ = c;

	return s;
}
