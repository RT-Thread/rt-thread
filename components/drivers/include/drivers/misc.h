/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __MISC_H__
#define __MISC_H__

#include <rtdef.h>

#ifdef ARCH_CPU_64BIT
#define RT_BITS_PER_LONG 64
#else
#define RT_BITS_PER_LONG 32
#endif
#define RT_BITS_PER_LONG_LONG 64

#define RT_DIV_ROUND_UP(n, d)   (((n) + (d) - 1) / (d))

#define RT_DIV_ROUND_CLOSEST(x, divisor)        \
({                                              \
    typeof(x) __x = x;                          \
    typeof(divisor) __d = divisor;              \
    (((typeof(x))-1) > 0 ||                     \
     ((typeof(divisor))-1) > 0 ||               \
     (((__x) > 0) == ((__d) > 0))) ?            \
            (((__x) + ((__d) / 2)) / (__d)) :   \
            (((__x) - ((__d) / 2)) / (__d));    \
})

#define RT_BIT(n)               (1UL << (n))
#define RT_BIT_ULL(n)           (1ULL << (n))
#define RT_BIT_MASK(nr)         (1UL << ((nr) % RT_BITS_PER_LONG))
#define RT_BIT_WORD(nr)         ((nr) / RT_BITS_PER_LONG)

#define RT_BITS_PER_BYTE        8
#define RT_BITS_PER_TYPE(type)  (sizeof(type) * RT_BITS_PER_BYTE)
#define RT_BITS_TO_BYTES(nr)    RT_DIV_ROUND_UP(nr, RT_BITS_PER_TYPE(char))
#define RT_BITS_TO_LONGS(nr)    RT_DIV_ROUND_UP(nr, RT_BITS_PER_TYPE(long))

#define RT_GENMASK(h, l)        (((~0UL) << (l)) & (~0UL >> (RT_BITS_PER_LONG - 1 - (h))))
#define RT_GENMASK_ULL(h, l)    (((~0ULL) << (l)) & (~0ULL >> (RT_BITS_PER_LONG_LONG - 1 - (h))))

#define RT_ARRAY_SIZE(arr)      (sizeof(arr) / sizeof(arr[0]))

#define rt_min(x, y)            \
({                              \
    typeof(x) _x = (x);         \
    typeof(y) _y = (y);         \
    (void) (&_x == &_y);        \
    _x < _y ? _x : _y;          \
})

#define rt_max(x, y)            \
({                              \
    typeof(x) _x = (x);         \
    typeof(y) _y = (y);         \
    (void) (&_x == &_y);        \
    _x > _y ? _x : _y;          \
})

#define rt_min_t(type, x, y)    \
({                              \
    type _x = (x);              \
    type _y = (y);              \
    _x < _y ? _x: _y;           \
})

#define rt_clamp(val, lo, hi)   rt_min((typeof(val))rt_max(val, lo), hi)

#define rt_do_div(n, base)              \
({                                      \
    rt_uint32_t _base = (base), _rem;   \
    _rem = ((rt_uint64_t)(n)) % _base;  \
    (n) = ((rt_uint64_t)(n)) / _base;   \
    if (_rem > _base / 2)               \
        ++(n);                          \
    _rem;                               \
})

#endif /* __MISC_H__ */
