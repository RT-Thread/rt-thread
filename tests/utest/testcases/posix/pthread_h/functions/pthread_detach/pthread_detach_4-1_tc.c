/*
 * Copyright (c) 2002, Intel Corporation. All rights reserved.
 * Created by:  rolla.n.selbak REMOVE-THIS AT intel DOT com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.

 * Test that pthread_detach()
 *
 * Upon failure, it shall return an error number:
 * -[EINVAL] The implemenation has detected that the value specified by
 * 'thread' does not refer to a joinable thread.
 * -[ESRCH] No thread could be found corresponding to that thread

 * It shall not return an error code of [EINTR]
 *
 * STEPS:
 * 1.Create a detached state thread
 * 2.Detach that thread
 * 3.Check the return value and make sure it is EINVAL
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "posixtest.h"

/* Thread function */
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

    /* Set the attribute object to be detached */
    if (pthread_attr_setdetachstate(&new_attr, PTHREAD_CREATE_DETACHED) !=
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
    ret = pthread_detach(new_th);

    /* Cleanup and cancel the thread */
    pthread_cancel(new_th);

    /* Check return value of pthread_detach() */
    if (ret != EINVAL) {
        if (ret == ESRCH) {
            perror("Error detaching thread\n");
            return PTS_UNRESOLVED;
        }

        printf("Test FAILED: Incorrect return code\n");
        return PTS_FAIL;

    }

    printf("Test PASSED\n");
    return PTS_PASS;
}
#include <rtt_utest_internal.h>
UTEST_TC_EXPORT(testcase, "posix.pthread_detach.4-1.c", RT_NULL, RT_NULL, 10);

