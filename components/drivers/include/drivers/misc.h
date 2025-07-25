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
#include <cpuport.h>

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

#define __KEY_PLACEHOLDER_1                     0,
#define ____KEY_ENABLED(__ignored, val, ...)    val
#define ___KEY_ENABLED(arg1_or_junk)            ____KEY_ENABLED(arg1_or_junk 1, 0)
#define __KEY_ENABLED(value)                    ___KEY_ENABLED(__KEY_PLACEHOLDER_##value)
#define RT_KEY_ENABLED(key)                     __KEY_ENABLED(key)

#define RT_FIELD_PREP(mask, val)    (((rt_uint64_t)(val) << (__rt_ffsl((mask)) - 1)) & (mask))
#define RT_FIELD_GET(mask, val)     (((val) & (mask)) >> (__rt_ffsl((mask)) - 1))

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

#define rt_offsetof(s, field)   ((rt_size_t)&((s *)0)->field)

#define rt_err_ptr(err)         ((void *)(rt_base_t)(err))
#define rt_ptr_err(ptr)         ((rt_err_t)(rt_base_t)(ptr))
#define rt_is_err_value(ptr)    ((rt_ubase_t)(void *)(ptr) >= (rt_ubase_t)-4095)
#define rt_is_err(ptr)          rt_is_err_value(ptr)
#define rt_is_err_or_null(ptr)  (!(ptr) || rt_is_err_value((rt_ubase_t)(ptr)))

#define rt_upper_32_bits(n)     ((rt_uint32_t)(((n) >> 16) >> 16))
#define rt_lower_32_bits(n)     ((rt_uint32_t)((n) & 0xffffffff))
#define rt_upper_16_bits(n)     ((rt_uint16_t)((n) >> 16))
#define rt_lower_16_bits(n)     ((rt_uint16_t)((n) & 0xffff))

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

#define rt_max_t(type, x, y)    \
({                              \
    type _x = (x);              \
    type _y = (y);              \
    _x > _y ? _x: _y;           \
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

#define rt_abs(x)                       \
({                                      \
    long ret;                           \
    if (sizeof(x) == sizeof(long))      \
    {                                   \
        long __x = (x);                 \
        ret = (__x < 0) ? -__x : __x;   \
    }                                   \
    else                                \
    {                                   \
        int __x = (x);                  \
        ret = (__x < 0) ? -__x : __x;   \
    }                                   \
    ret;                                \
})

#ifndef rt_ilog2
rt_inline int rt_ilog2(rt_ubase_t v)
{
    int l = 0;

    while ((1UL << l) < v)
    {
        l++;
    }

    return l;
}
#endif /* !rt_ilog2 */

#endif /* __MISC_H__ */
