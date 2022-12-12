/*
 * Copyright (c) 2002, Intel Corporation. All rights reserved.
 * Created by:  rolla.n.selbak REMOVE-THIS AT intel DOT com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.

 * Test that pthread_detach()
 *
 * shall detach a thread. It shall indicate to the implementation that storage
 * for 'thread' can be reclaimed when that thread terminates.
 *
 * STEPS:
 * 1. Create a joinable thread
 * 2. Detach that thread with pthread_detach()
 * 3. Try and join the thread to main() using pthread_join()
 * 4. An error should return from the pthread_join() function saying that the
 *    thread is detched.  The test passes.
 * 5. Else, if pthread_join is successful, the test fails.
 */

#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "posixtest.h"

static void *a_thread_func()
{
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    /* If the thread wasn't canceled in 10 seconds, time out */
    sleep(10);

    perror("Thread couldn't be canceled (at cleanup time), timing out\n");
    pthread_exit(0);
    return NULL;
}

static int posix_testcase(void)
{
    pthread_attr_t new_attr;
    pthread_t new_th;
    int ret;

    /* Initialize attribute */
    if (pthread_attr_init(&new_attr) != 0) {
        perror("Cannot initialize attribute object\n");
        return PTS_UNRESOLVED;
    }

    /* Set the attribute object to be joinable */
    if (pthread_attr_setdetachstate(&new_attr, PTHREAD_CREATE_JOINABLE) !=
        0) {
        perror("Error in pthread_attr_setdetachstate()\n");
        return PTS_UNRESOLVED;
    }

    /* Create the thread */
    if (pthread_create(&new_th, &new_attr, a_thread_func, NULL) != 0) {
        perror("Error creating thread\n");
        return PTS_UNRESOLVED;
    }

    /* Detach the thread. */
    if (pthread_detach(new_th) != 0) {
        printf("Error detaching thread\n");
        return PTS_FAIL;
    }

    /* Now try and join it.  This should fail. */
    ret = pthread_join(new_th, NULL);

    /* Cleanup: Cancel the thread */
    pthread_cancel(new_th);

    if (ret == 0) {
        printf("Test FAILED\n");
        return PTS_FAIL;
    } else if (ret == EINVAL) {
        printf("Test PASSED\n");
        return PTS_PASS;
    } else {
        perror("Error in pthread_join\n");
        return PTS_UNRESOLVED;
    }

}
#include <rtt_utest_internal.h>
UTEST_TC_EXPORT(testcase, "posix.pthread_detach.1-1.c", RT_NULL, RT_NULL, 10);

