/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
 */

#ifndef __RISCV_H__
#define __RISCV_H__

#include <encoding.h>
#include <rtconfig.h>

#if defined(RT_USING_RV64ILP32)
#define __SIZE(bit) (1ULL << (bit))
#define __MASK(bit) (__SIZE(bit) - 1ULL)
#else
#define __SIZE(bit) (1UL << (bit))
#define __MASK(bit) (__SIZE(bit) - 1UL)
#endif /* RT_USING_RV64ILP32 */
#define __UMASK(bit) (~(__MASK(bit)))
#define __MASKVALUE(value,maskvalue) ((value) & (maskvalue))
#define __UMASKVALUE(value,maskvalue) ((value) & (~(maskvalue)))
#define __CHECKUPBOUND(value,bit_count) (!(((rt_size_t)value) & (~__MASK(bit_count))))
#define __CHECKALIGN(value,start_bit) (!(((rt_size_t)value) & (__MASK(start_bit))))

#define __PARTBIT(value,start_bit,length) (((value) >> (start_bit)) & __MASK(length))

#define __ALIGNUP(value,bit) (((value) + __MASK(bit)) & __UMASK(bit))
#define __ALIGNDOWN(value,bit) ((value) & __UMASK(bit))

#endif
