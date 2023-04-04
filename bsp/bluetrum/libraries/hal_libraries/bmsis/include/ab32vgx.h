/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef PROUGENGX_H__
#define PROUGENGX_H__

#include "ab32vg1.h"

#ifndef UINT_MAX
#define UINT_MAX                0xffffffff
#endif // UINT_MAX

#define BIT(n)                  (1UL << (n))

#define AT(x)                   __attribute__((section(#x)))
#define ALIGNED(n)              __attribute__((aligned(n)))
#define DMA_ADR(x)              ((uint32_t)x)
#define ALWAYS_INLINE           __attribute__((always_inline)) inline
#define NO_INLINE               __attribute__((noinline))
#define WEAK                    __attribute__((weak))
#define PACKED                  __attribute__((packed))

#define BYTE0(n)                ((unsigned char)(n))
#define BYTE1(n)                ((unsigned char)((n)>>8))
#define BYTE2(n)                ((unsigned char)((n)>>16))
#define BYTE3(n)                ((unsigned char)((n)>>24))

#define GET_LE16(ptr)           (uint16_t)(*(uint16_t*)(uint8_t*)(ptr))
#define GET_LE32(ptr)           (uint32_t)(*(uint32_t*)(uint8_t*)(ptr))
#define PUT_LE16(ptr, val)      *(uint16_t*)(uint8_t*)(ptr) = (uint16_t)(val)
#define PUT_LE32(ptr, val)      *(uint32_t*)(uint8_t*)(ptr) = (uint32_t)(val)

#define GET_BE16(ptr)           get_be16(ptr)
#define GET_BE32(ptr)           get_be32(ptr)
#define PUT_BE16(ptr, val)      put_be16(ptr, val)
#define PUT_BE32(ptr, val)      put_be32(ptr, val)

#include "ab32vg1_hal.h"

#endif
