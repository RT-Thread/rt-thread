/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-07-04     rcitach        init ver.
 */

#ifndef _VDSO_H
#define _VDSO_H

#include <lwp.h>
#include <mmu.h>
#include <vdso_config.h>
#include <vdso_datapage.h>

#ifdef __cplusplus
extern "C" {
#endif

extern char __vdso_text_start[];
extern char __vdso_text_end[];

#define ELF_HEAD "\177ELF"
#define ELF_HEAD_LEN 4
#define MAX_PAGES 5

#define __page_aligned_data	__attribute__((section(".data.vdso.datapage"))) __attribute__((aligned(VDSO_PAGE_SIZE)))

int arch_setup_additional_pages(struct rt_lwp *lwp);
void rt_vdso_update_glob_time(void);

#ifdef __cplusplus
}
#endif

#endif /* _VDSO_H */
