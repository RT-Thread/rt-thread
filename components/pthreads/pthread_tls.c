#include <pthread.h>

void *pthread_getspecific(pthread_key_t key)
{
}

int pthread_setspecific(pthread_key_t key, const void *value)
{
}

int pthread_key_create(pthread_key_t *key, void (*destructor)(void*))
{
	return 0;
}

int pthread_key_delete(pthread_key_t key)
{
	return 0;
}
