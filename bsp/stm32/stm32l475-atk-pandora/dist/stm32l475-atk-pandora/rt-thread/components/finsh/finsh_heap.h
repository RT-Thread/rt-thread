/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-22     Bernard      first version
 */
#include <finsh.h>

#ifndef __FINSH_HEAP_H__
#define __FINSH_HEAP_H__

int finsh_heap_init(void);
void* finsh_heap_allocate(size_t size);
void  finsh_heap_free(void*ptr);

#endif
