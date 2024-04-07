/*
 * Copyright (c) 2002, Intel Corporation. All rights reserved.
 * Created by:  bing.wei.liu REMOVE-THIS AT intel DOT com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.

 * Test that pthread_cond_init()
 *   shall initialize the condition variable referenced by cond with attributes
 *   referenced by attr. If attr is NULL, the default condition variable
 *   attributes shall be used; the effect is the same as passing the address
 *   of a default condition variable attributes object.

 * NOTE: There is no direct way to judge if two condition variables are equal,
 *       so this test does not cover the statement in the last sentence.
 *
 *
 *  Modified - LK coding style 30/05/2011
 *  Peter W. Morreale <pmorreale AT novell DOT com>
 */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include "posixtest.h"

#define ERR_MSG(f, rc)  printf("Failed: func: %s rc: %s (%u)\n", \
                    f, strerror(rc), rc);

static int posix_testcase(void)
{
    pthread_condattr_t condattr;
    pthread_cond_t cond1;
    pthread_cond_t cond2;
    int rc;
    char *f;
    int status = PTS_UNRESOLVED;

    f = "pthread_condattr_init()";
    rc = pthread_condattr_init(&condattr);
    if (rc)
        goto done;

    status = PTS_FAIL;
    f = "pthread_cond_init() - condattr";
    rc = pthread_cond_init(&cond1, &condattr);
    if (rc)
        goto done;

    f = "pthread_cond_init() - NULL";
    rc = pthread_cond_init(&cond2, NULL);
    if (rc)
        goto done;

    printf("Test PASSED\n");
    return PTS_PASS;

done:
    ERR_MSG(f, rc);
    return status;

}
#include <rtt_utest_internal.h>
UTEST_TC_EXPORT(testcase, "posix.pthread_cond_init.1-1.c", RT_NULL, RT_NULL, 10);

