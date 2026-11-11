/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-07-04     rcitach        init ver.
 */

#ifndef RT_VDSO_KERNEL_INTERNAL_H
#define RT_VDSO_KERNEL_INTERNAL_H

#include <rthw.h>
#include <vdso_data_page.h>

#ifdef __cplusplus
extern "C" {
#endif

extern struct rt_vdso_data_page *rt_vdso_kernel_data_page;

rt_inline struct rt_vdso_data_page *rt_vdso_get_kernel_data_page(void)
{
    return rt_vdso_kernel_data_page;
}

rt_inline void rt_vdso_data_page_write_begin(struct rt_vdso_data_page *data_page)
{
    data_page->seq_counter += 1;
    rt_hw_dmb();
}

rt_inline void rt_vdso_data_page_write_end(struct rt_vdso_data_page *data_page)
{
    rt_hw_dmb();
    data_page->seq_counter += 1;
}

#ifdef __cplusplus
}
#endif

#endif /* RT_VDSO_KERNEL_INTERNAL_H */
