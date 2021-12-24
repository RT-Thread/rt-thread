/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <sys/errno.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define usleep rt_thread_sleep

static void *test_thread(void *v_param) {
    return NULL;
}

int libc_ex6(void) {
    unsigned long count;

    setvbuf(stdout, NULL, _IONBF, 0);

    for (count = 0; count < 2000; ++count) {
        pthread_t thread;
        int status;

        status = pthread_create(&thread, NULL, test_thread, NULL);
        if (status != 0) {
            printf("status = %d, count = %lu: %s\n", status, count, strerror(
                    errno));
            return 1;
        } else {
            printf("count = %lu\n", count);
        }
        /* pthread_detach (thread); */
        pthread_join(thread, NULL);
        usleep(10);
    }
    return 0;
}
#include <finsh.h>
FINSH_FUNCTION_EXPORT(libc_ex6, example 6 for libc);
