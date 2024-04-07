/*
 * Copyright (c) 2002, Intel Corporation. All rights reserved.
 * Created by:  rolla.n.selbak REMOVE-THIS AT intel DOT com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.

 * Test that pthread_create() creates a new thread with attributes specified
 * by 'attr', within a process.
 *
 * Steps:
 * 1.  Create a thread using pthread_create()
 * 2.  Cancel that thread with pthread_cancel()
 * 3.  If that thread doesn't exist, then it pthread_cancel() will return
 *     an error code.  This would mean that pthread_create() did not create
 *     a thread successfully.
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "posixtest.h"

static void *a_thread_func()
{
    sleep(10);

    /* Shouldn't reach here.  If we do, then the pthread_cancel()
     * function did not succeed. */
    fprintf(stderr, "Could not send cancel request correctly\n");

    return NULL;
}

static int posix_testcase(void)
{
    pthread_t new_th;
    int ret;

    ret = pthread_create(&new_th, NULL, a_thread_func, NULL);
    if (ret) {
        fprintf(stderr, "pthread_create(): %s\n", strerror(ret));
        return PTS_UNRESOLVED;
    }

    /* Try to cancel the newly created thread.  If an error is returned,
     * then the thread wasn't created successfully. */
    ret = pthread_cancel(new_th);
    if (ret) {
        printf("Test FAILED: A new thread wasn't created: %s\n",
               strerror(ret));
        return PTS_FAIL;
    }

    printf("Test PASSED\n");
    return PTS_PASS;
}
#include <rtt_utest_internal.h>
UTEST_TC_EXPORT(testcase, "posix.pthread_create.1-2.c", RT_NULL, RT_NULL, 10);

