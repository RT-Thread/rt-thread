/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-06-04     ArdaFu      first version
 */
#ifndef __RT_LOW_LEVEL_INIT_H__
#define __RT_LOW_LEVEL_INIT_H__

/*-------- Stack size of CPU modes -------------------------------------------*/
#define UND_STK_SIZE 512
#define SVC_STK_SIZE 4096
#define ABT_STK_SIZE 512
#define IRQ_STK_SIZE 1024
#define FIQ_STK_SIZE 1024
#define SYS_STK_SIZE 512
#define Heap_Size    512
#endif
