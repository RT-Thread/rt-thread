/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-6-27      GuEe-GUI     first version
 */

#ifndef __UTIL_BITMAP_H__
#define __UTIL_BITMAP_H__

#include <rtdef.h>

typedef rt_ubase_t rt_bitmap_t;

#define RT_BITMAP_BITS_MIN              (sizeof(rt_bitmap_t) * 8)
#define RT_BITMAP_LEN(bits)             (((bits) + (RT_BITMAP_BITS_MIN) - 1) / (RT_BITMAP_BITS_MIN))
#define RT_BITMAP_BIT_LEN(nr)           (nr * RT_BITMAP_BITS_MIN)
#define RT_DECLARE_BITMAP(name, bits)   rt_bitmap_t name[RT_BITMAP_LEN(bits)]

rt_inline void rt_bitmap_set_bit(rt_bitmap_t *bitmap, rt_uint32_t bit)
{
    bitmap[bit / RT_BITMAP_BITS_MIN] |= (1UL << (bit & (RT_BITMAP_BITS_MIN - 1)));
}

rt_inline rt_bool_t rt_bitmap_test_bit(rt_bitmap_t *bitmap, rt_uint32_t bit)
{
    return !!(bitmap[bit / RT_BITMAP_BITS_MIN] & (1UL << (bit & (RT_BITMAP_BITS_MIN - 1))));
}

rt_inline void rt_bitmap_clear_bit(rt_bitmap_t *bitmap, rt_uint32_t bit)
{
    bitmap[bit / RT_BITMAP_BITS_MIN] &= ~(1UL << (bit & (RT_BITMAP_BITS_MIN - 1)));
}

rt_inline rt_size_t rt_bitmap_next_set_bit(rt_bitmap_t *bitmap, rt_size_t start, rt_size_t limit)
{
    rt_size_t bit;

    for (bit = start; bit < limit && !rt_bitmap_test_bit(bitmap, bit); ++bit)
    {
    }

    return bit;
}

rt_inline rt_size_t rt_bitmap_next_clear_bit(rt_bitmap_t *bitmap, rt_size_t start, rt_size_t limit)
{
    rt_size_t bit;

    for (bit = start; bit < limit && rt_bitmap_test_bit(bitmap, bit); ++bit)
    {
    }

    return bit;
}

#define rt_bitmap_for_each_bit_from(state, bitmap, from, bit, limit)        \
    for ((bit) = rt_bitmap_next_##state##_bit((bitmap), (from), (limit));   \
         (bit) < (limit);                                                   \
         (bit) = rt_bitmap_next_##state##_bit((bitmap), (bit + 1), (limit)))

#define rt_bitmap_for_each_set_bit_from(bitmap, from, bit, limit) \
    rt_bitmap_for_each_bit_from(set, bitmap, from, bit, limit)

#define rt_bitmap_for_each_set_bit(bitmap, bit, limit) \
    rt_bitmap_for_each_set_bit_from(bitmap, 0, bit, limit)

#define rt_bitmap_for_each_clear_bit_from(bitmap, from, bit, limit) \
    rt_bitmap_for_each_bit_from(clear, bitmap, from, bit, limit)

#define rt_bitmap_for_each_clear_bit(bitmap, bit, limit) \
    rt_bitmap_for_each_clear_bit_from(bitmap, 0, bit, limit)

#endif /* __UTIL_BITMAP_H__ */
