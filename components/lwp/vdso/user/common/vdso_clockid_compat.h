/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2026-11-12     RT-Thread      add Newlib clock ID fallbacks
 */

#ifndef RT_VDSO_CLOCKID_COMPAT_H
#define RT_VDSO_CLOCKID_COMPAT_H

/*
 * The freestanding vDSO user library only sees the IDs that the C library
 * exposes through <time.h>. Newlib hides the POSIX monotonic and GNU clock IDs
 * behind internal feature macros such as _POSIX_MONOTONIC_CLOCK and
 * __GNU_VISIBLE, so bare-metal toolchains like riscv64-unknown-elf end up
 * without the IDs used by vdso_clock_gettime.c and the library does not build.
 *
 * Fill in the missing IDs with the values from the Linux ABI (include/uapi/
 * linux/time.h), so the vDSO keeps the same clock ID numbers as the kernel and
 * as musl based RT-Smart toolchains. IDs the C library already provides are
 * left untouched.
 */

#ifndef CLOCK_MONOTONIC_RAW
#define CLOCK_MONOTONIC_RAW 4
#endif /* CLOCK_MONOTONIC_RAW */

#ifndef CLOCK_REALTIME_COARSE
#define CLOCK_REALTIME_COARSE 5
#endif /* CLOCK_REALTIME_COARSE */

#ifndef CLOCK_MONOTONIC_COARSE
#define CLOCK_MONOTONIC_COARSE 6
#endif /* CLOCK_MONOTONIC_COARSE */

#ifndef CLOCK_BOOTTIME
#define CLOCK_BOOTTIME 7
#endif /* CLOCK_BOOTTIME */

#endif /* RT_VDSO_CLOCKID_COMPAT_H */
