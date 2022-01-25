/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-24     thread-liu   first version
 */

#ifndef __DRV_OPENAMP_H__
#define __DRV_OPENAMP_H__

#include "board.h"
#ifdef __cplusplus
extern "C" {
#endif

struct rt_openamp
{
    rt_uint8_t   *rbuf;
    rt_uint8_t   *tbuf;
    volatile rt_uint16_t  rbuf_size;
    volatile rt_uint16_t  tbuf_size;
    volatile rt_uint16_t  rbuf_start;
    volatile rt_uint16_t  rbuf_count;
    volatile rt_uint16_t  tbuf_start;
    volatile rt_uint16_t  tbuf_count;
};

#define OPENAMP_THREAD_STACK_SIZE   512
#define OPENAMP_THREAD_PRIORITY     5
#define OPENAMP_THREAD_TIMESLICE    10

#define MAX_BUFFER_SIZE             256

#ifdef __cplusplus
}
#endif

#endif
