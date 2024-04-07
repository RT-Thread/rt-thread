#include <utest.h>
#include <pthread.h>
static void posix_unit_test(void)
{
    pthread_t new_th;   /* Create a new thread. */
    int err_val;

    if (pthread_create(&new_th, NULL, (void *(*)(void *))posix_testcase, NULL) != 0) {
        perror("Error creating thread\n");
    }

    /* Wait for thread to return */
    if (pthread_join(new_th, (void*)&err_val) != 0) {
        perror("Error in pthread_join()\n");
    }

    rt_thread_mdelay(1000);

    uassert_true(err_val == 0);
}
static void testcase(void)
{
    UTEST_UNIT_RUN(posix_unit_test);
}
