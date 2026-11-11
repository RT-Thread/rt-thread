/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-17     WangXiaoyao  cache API unit test
 */
#include <rtthread.h>

#ifdef ARCH_RISCV64
#include "test_cache_rv64.h"
#elif defined(ARCH_ARMV8)
#include "test_cache_aarch64.h"
#endif
