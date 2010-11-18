/*
 * env.c
 *
 *  Created on: 2010-11-17
 *      Author: bernard
 */
#include <stdio.h>
#include <stdlib.h>
#include <finsh.h>

int libc_env()
{
	printf("PATH=%s\n", getenv("PATH"));
	putenv("foo=bar");
	printf("foo=%s\n", getenv("foo"));
	return 0;
}
FINSH_FUNCTION_EXPORT(libc_env, get/set_env test);
