#include <string.h>

__attribute__((used))
size_t strlen(const char *s)
{
	size_t n = 0;

	while (*s++)
		n++;

	return n;
}

__attribute__((used))
size_t strnlen(const char *s, size_t maxlen)
{
	size_t n = 0;

	while (*s++ && maxlen--)
		n++;

	return n;
}
