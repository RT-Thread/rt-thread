/* Creates two threads, one printing 10000 "a"s, the other printing
   10000 "b"s.
   Illustrates: thread creation, thread joining. */

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "pthread.h"

static void *process(void * arg)
{
	int i;
	printf("Starting process %s\n", (char *)arg);
	for (i = 0; i < 10000; i++)
		write(1, (char *) arg, 1);
	return NULL;
}

#define sucfail(r) (r != 0 ? "failed" : "succeeded")
int libc_ex1(void)
{
	int pret, ret = 0;
	pthread_t th_a, th_b;
	void *retval;

	ret += (pret = pthread_create(&th_a, NULL, process, (void *)"a"));
	printf("create a %s %d\n", sucfail(pret), pret);
	ret += (pret = pthread_create(&th_b, NULL, process, (void *)"b"));
	printf("create b %s %d\n", sucfail(pret), pret);
	ret += (pret = pthread_join(th_a, &retval));
	printf("join a %s %d\n", sucfail(pret), pret);
	ret += (pret = pthread_join(th_b, &retval));
	printf("join b %s %d\n", sucfail(pret), pret);
	return ret;
}
#include <finsh.h>
FINSH_FUNCTION_EXPORT(libc_ex1, example 1 for libc);
