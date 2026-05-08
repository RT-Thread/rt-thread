/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-07-04     rcitach        init ver.
 */

#ifndef RT_VDSO_CONSTANTS_H
#define RT_VDSO_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

#define RT_VDSO_DATA_PAGE_COUNT 1
#define RT_VDSO_PAGE_SHIFT      12
#define RT_VDSO_PAGE_SIZE       (1 << RT_VDSO_PAGE_SHIFT)

#ifndef read_barrier_depends
#define read_barrier_depends() \
    do                         \
    {                          \
    } while (0)
#endif

#ifndef smp_read_barrier_depends
#define smp_read_barrier_depends() read_barrier_depends()
#endif

#if defined(__aarch64__)
#define RT_VDSO_IMAGE_PATH "../user/build/aarch64/libvdso.so"
#elif defined(__arm__)
#define RT_VDSO_IMAGE_PATH "../user/build/arm/libvdso.so"
#elif defined(__riscv)
#define RT_VDSO_IMAGE_PATH "../user/build/risc-v/libvdso.so"
#else
#error "Unsupported architecture for vDSO"
#endif

#ifdef __cplusplus
}
#endif

#endif /* RT_VDSO_CONSTANTS_H */
