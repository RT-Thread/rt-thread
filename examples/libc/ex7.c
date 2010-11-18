/* ex7
 *
 * Test case that illustrates a timed wait on a condition variable.
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

#define usleep rt_thread_sleep

/* Our event variable using a condition variable contruct. */
typedef struct {
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int flag;
} event_t;

/* Global event to signal main thread the timeout of the child thread. */
event_t main_event;

static void *test_thread(void *ms_param) {
	int status = 0;
	event_t foo;
	struct timespec time;
	struct timeval now;
	long ms = (long) ms_param;

	/* initialize cond var */
	pthread_cond_init(&foo.cond, NULL);
	pthread_mutex_init(&foo.mutex, NULL);
	foo.flag = 0;

	/* set the time out value */
	printf("waiting %ld ms ...\n", ms);
	gettimeofday(&now, NULL);
	time.tv_sec = now.tv_sec + ms / 1000 + (now.tv_usec + (ms % 1000) * 1000)
			/ 1000000;
	time.tv_nsec = ((now.tv_usec + (ms % 1000) * 1000) % 1000000) * 1000;

	/* Just use this to test the time out. The cond var is never signaled. */
	pthread_mutex_lock(&foo.mutex);
	while (foo.flag == 0 && status != ETIMEDOUT) {
		status = pthread_cond_timedwait(&foo.cond, &foo.mutex, &time);
	}
	pthread_mutex_unlock(&foo.mutex);

	/* post the main event */
	pthread_mutex_lock(&main_event.mutex);
	main_event.flag = 1;
	pthread_cond_signal(&main_event.cond);
	pthread_mutex_unlock(&main_event.mutex);

	/* that's it, bye */
	return (void*) status;
}

int libc_ex7(void) {
	unsigned long count;

	setvbuf(stdout, NULL, _IONBF, 0);

	/* initialize main event cond var */
	pthread_cond_init(&main_event.cond, NULL);
	pthread_mutex_init(&main_event.mutex, NULL);
	main_event.flag = 0;

	for (count = 0; count < 20; ++count) {
		pthread_t thread;
		int status;

		/* pass down the milli-second timeout in the void* param */
		status = pthread_create(&thread, NULL, test_thread, (void*) (count
				* 100));
		if (status != 0) {
			printf("status = %d, count = %lu: %s\n", status, count, strerror(
					errno));
			return 1;
		} else {

			/* wait for the event posted by the child thread */
			pthread_mutex_lock(&main_event.mutex);
			while (main_event.flag == 0) {
				pthread_cond_wait(&main_event.cond, &main_event.mutex);
			}
			main_event.flag = 0;
			pthread_mutex_unlock(&main_event.mutex);

			printf("count = %lu\n", count);
		}

		usleep(10);
	}

	return 0;
}
#include <finsh.h>
FINSH_FUNCTION_EXPORT(libc_ex7, example 7 for libc);
