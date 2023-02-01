/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-06     Jesven       first version
 */
#ifndef  __IOREMAP_H__
#define  __IOREMAP_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void *rt_ioremap(void *paddr, size_t size);
void *rt_ioremap_nocache(void *paddr, size_t size);
void *rt_ioremap_cached (void *paddr, size_t size);
void rt_iounmap(volatile void *addr);

extern void *rt_ioremap_start;
extern size_t rt_ioremap_size;

#ifdef __cplusplus
}
#endif

#endif  /*__LWP_IOREMAP_H__*/
