/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <sys/socket.h>

#include "utest.h"

static void TC_sal_socket_failure_cleanup(void)
{
    rt_size_t used_before;
    rt_size_t used_after;
    int i;

    /* Warm up the descriptor and SAL tables before measuring the heap. */
    uassert_int_equal(socket(-1, SOCK_STREAM, 0), -1);
    rt_memory_info(RT_NULL, &used_before, RT_NULL);

    for (i = 0; i < 32; i++)
    {
        uassert_int_equal(socket(-1, SOCK_STREAM, 0), -1);
    }

    rt_memory_info(RT_NULL, &used_after, RT_NULL);
    LOG_I("heap used before: %lu, after: %lu",
          (unsigned long)used_before, (unsigned long)used_after);
    uassert_int_equal(used_after, used_before);
}

static void utest_do_tc(void)
{
    UTEST_UNIT_RUN(TC_sal_socket_failure_cleanup);
}
UTEST_TC_EXPORT(utest_do_tc, "components.net.sal.socket_failure_cleanup", RT_NULL, RT_NULL, 5);
