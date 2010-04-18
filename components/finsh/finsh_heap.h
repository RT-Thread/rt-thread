/*
 * File      : finsh_heap.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
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
