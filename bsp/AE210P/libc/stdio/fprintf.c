#include <stdio.h>

__attribute__((used))
int fprintf(FILE *stream, const char *fmt, ...)
{
	va_list args;
	int ret_val;

	va_start(args, fmt);
	ret_val = vprintf(fmt, args);
	va_end(args);

	return ret_val;
}
