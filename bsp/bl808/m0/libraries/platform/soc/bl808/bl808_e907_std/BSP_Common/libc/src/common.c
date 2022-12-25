/*
 * Derived from:
 * http://www.kernel.org/pub/linux/libs/klibc/
 */
//#include <stdio.h>

void __assert_func(const char *file, int line,
		   const char *func, const char *failedexpr)
{
#if 0
	printf("assertion \"%s\" failed: file \"%s\", line %d%s%s\n",
		 failedexpr, file, line, func ? ", function: " : "",
		 func ? func : "");

	/* Ensure that nothing runs after this */
	while (1)
		;
#endif
}

float strtof(const char *nptr, char **endptr)
{
//	printf("Float print not supported yet!\r\n");
	return 0;
}
