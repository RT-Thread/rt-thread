/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-07-04     rcitach        init ver.
 */

#ifndef __ASM_VDSO_H
#define __ASM_VDSO_H

#ifdef __cplusplus
extern "C" {
#endif

#define __VVAR_PAGES    2
#define VDSO_PAGE_SHIFT     12
#define VDSO_PAGE_SIZE      (1 << VDSO_PAGE_SHIFT)

#define BIT_MASK(nr)         ((1) << (nr))

#ifndef read_barrier_depends
#define read_barrier_depends()      do { } while (0)
#endif

#ifndef smp_read_barrier_depends
#define smp_read_barrier_depends()  read_barrier_depends()
#endif

#define VDSO_PATH "../user/build/librtos_vdso.so"

#ifdef __cplusplus
}
#endif

#endif  /* __ASM_VDSO_H */
