/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-03     lizhirui     first version
 */

#ifndef __ARCH_H__
#define __ARCH_H__

#include "riscv_mmu.h"

#define ARCH_PAGE_SIZE PAGE_SIZE
#define ARCH_PAGE_MASK PAGE_OFFSET_MASK
#define ARCH_PAGE_SHIFT PAGE_OFFSET_BIT

#define dsb()

#endif