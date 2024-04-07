/*
 * Copyright (c) 2002, Intel Corporation. All rights reserved.
 * Created by:  rolla.n.selbak REMOVE-THIS AT intel DOT com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 *
 * Test that pthread_join()
 *
 * shall suspend the execution of the calling thread until the target
 * 'thread' terminates, unless 'thread' has already terminated.
 *
 * Steps:
 * 1.  Create a new thread.  Have it sleep for 3 seconds.
 * 2.  The main() thread should wait for the new thread to finish
 *     execution before exiting out.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "posixtest.h"

static int end_exec;

static void *a_thread_func()
{
    int i;

    printf("Wait for 3 seconds for thread to finish execution:\n");
    for (i = 1; i < 4; i++) {
        printf("Waited (%d) second\n", i);
        sleep(1);
    }

    /* Indicate that the thread has ended execution. */
    end_exec = 1;

    pthread_exit(0);
    return NULL;
}

static int posix_testcase(void)
{
    pthread_t new_th;

    /* Initialize flag */
    end_exec = 0;

    /* Create a new thread. */
    if (pthread_create(&new_th, NULL, a_thread_func, NULL) != 0) {
        perror("Error creating thread\n");
        return PTS_UNRESOLVED;
    }

    /* Wait for thread to return */
    if (pthread_join(new_th, NULL) != 0) {
        perror("Error in pthread_join()\n");
        return PTS_UNRESOLVED;
    }

    if (end_exec == 0) {
        printf("Test FAILED: When using pthread_join(), "
               "main() did not wait for thread to finish "
               "execution before continuing.\n");
        return PTS_FAIL;
    }

    printf("Test PASSED\n");
    return PTS_PASS;
}
#include <rtt_utest_internal.h>
UTEST_TC_EXPORT(testcase, "posix.pthread_join.1-1.c", RT_NULL, RT_NULL, 10);

