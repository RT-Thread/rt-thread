/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-07-04     rcitach        init ver.
 */

#ifndef RT_VDSO_KERNEL_H
#define RT_VDSO_KERNEL_H

#include <lwp.h>
#include <vdso_constants.h>
#include <vdso_data_page.h>

#ifdef __cplusplus
extern "C" {
#endif

extern char __rt_vdso_image_start[];
extern char __rt_vdso_image_end[];

#define RT_VDSO_IMAGE_ELF_MAGIC     "\177ELF"
#define RT_VDSO_IMAGE_ELF_MAGIC_LEN 4
#define RT_VDSO_DATA_PAGE_ALIGNED                   \
    __attribute__((section(".data.vdso.datapage"))) \
    __attribute__((aligned(RT_VDSO_PAGE_SIZE)))

int rt_vdso_map_process_image(struct rt_lwp *lwp);
void rt_vdso_sync_clock_data(void);
void rt_vdso_set_realtime(const struct timespec *realtime);

#ifdef __cplusplus
}
#endif

#endif /* RT_VDSO_KERNEL_H */
