/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-20     GuEe-GUI     The first version
 */

#ifndef __PAGE_DEF_H__
#define __PAGE_DEF_H__

#include <asm-generic.h>

#ifndef ARCH_PAGE_SHIFT
#define ARCH_PAGE_SHIFT     12
#elif ARCH_PAGE_SHIFT != 12
#warning Make sure you fully understand what you are doing
#endif
#define ARCH_PAGE_SIZE      (_UL(1) << ARCH_PAGE_SHIFT)
#define ARCH_PAGE_MASK      (ARCH_PAGE_SIZE - 1)

#define SUPPER_PAGE_SIZE    0x200000
#define SUPPER_PAGE_MASK    (SUPPER_PAGE_SIZE - 1)

#endif /* __PAGE_DEF_H__ */
