#ifndef __PTHREAD_INTERNAL_H__
#define __PTHREAD_INTERNAL_H__

#include <rtthread.h>
#include <pthread.h>

struct _pthread_cleanup
{
	void (*cleanup_func)(void* parameter);
	void* parameter;

	struct _pthread_cleanup* next;
};
typedef struct _pthread_cleanup _pthread_cleanup_t;

#define PTHREAD_MAGIC	0x70746873
struct _pthread_data
{
	rt_uint32_t magic;
	pthread_attr_t attr;
	rt_thread_t tid;

	void* (*thread_entry)(void* parameter);
	void* thread_parameter;

	/* return value */
	void* return_value;

	/* semaphore for joinable thread */
	rt_sem_t joinable_sem;

	_pthread_cleanup_t* cleanup;
	void** tls; /* thread-local storage area */
};
typedef struct _pthread_data _pthread_data_t;

rt_inline _pthread_data_t* _pthread_get_data(pthread_t thread)
{
	RT_ASSERT(thread != RT_NULL);

	return (_pthread_data_t*)thread->user_data;
}

#endif
