#include <string.h>

__attribute__((used))
void *memcpy(void *dest, const void *src, size_t n)
{
	while (n--)
		*(unsigned char *)dest++ = *(const unsigned char *)src++;

	return dest;
}
