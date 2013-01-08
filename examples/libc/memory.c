/*
 * memory.c
 *
 *  Created on: 2010-11-17
 *      Author: bernard
 */
#include <stdio.h>
#include <stdlib.h>
#include <finsh.h>
#include <errno.h>

static int errors = 0;
static void merror(const char *msg)
{
	++errors;
	printf("Error: %s\n", msg);
}

int libc_mem(void)
{
	void *p;
	int save;

	errno = 0;

	p = malloc(-1);
	save = errno;

	if (p != NULL)
		merror("malloc (-1) succeeded.");

	if (p == NULL && save != ENOMEM)
		merror("errno is not set correctly");

	p = malloc(10);
	if (p == NULL)
		merror("malloc (10) failed.");

	/* realloc (p, 0) == free (p).  */
	p = realloc(p, 0);
	if (p != NULL)
		merror("realloc (p, 0) failed.");

	p = malloc(0);
	if (p == NULL)
	{
		printf("malloc(0) returns NULL\n");
	}

	p = realloc(p, 0);
	if (p != NULL)
		merror("realloc (p, 0) failed.");

	return errors != 0;
}
FINSH_FUNCTION_EXPORT(libc_mem, memory test for libc);
