#include <string.h>
#include <stdlib.h>

__attribute__((used))
char *strdup(const char *s)
{
	int len = strlen(s);
	char *buf = malloc(len + 1);

	if (buf) {

		strncpy(buf, s, len);
		buf[len] = '\0';
	}

	return buf;
}

__attribute__((used))
char *strndup(const char *s, size_t n)
{
	int len = strnlen(s, n);
	char *buf = malloc(len + 1);
	
	if (buf) {

		strncpy(buf, s, len);
		buf[len] = '\0';
	}

	return buf;
}
