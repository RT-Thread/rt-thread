/*
 * Copyright (c) 2015, Xilinx Inc. and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * @file	atomic.h
 * @brief	Atomic primitives for libmetal.
 */

#ifndef __METAL_ATOMIC__H__
#define __METAL_ATOMIC__H__

#include <metal/config.h>

#if defined(HAVE_STDATOMIC_H) && !defined (__CC_ARM) && \
    !defined(__STDC_NO_ATOMICS__) && !defined(__cplusplus)

# include <stdatomic.h>

#ifndef atomic_thread_fence
#define atomic_thread_fence(order)
#endif

#elif defined(__GNUC__)
# include <metal/compiler/gcc/atomic.h>
#else
# include <metal/processor/arm/atomic.h>
#endif

#endif /* __METAL_ATOMIC__H__ */
