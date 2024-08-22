/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-15     WangShun     The first version
 */

#ifndef REGTYPES_H__
#define REGTYPES_H__
#include <rtconfig.h>
#if defined(RT_USING_RV64ILP32)
typedef unsigned long long rt_uintreg_t;
#else
typedef unsigned long rt_uintreg_t;
#endif
#endif /* REGTYPES_H__ */
