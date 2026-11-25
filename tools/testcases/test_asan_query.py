#!/usr/bin/env python3
# Copyright (c) 2006-2026, RT-Thread Development Team
# SPDX-License-Identifier: Apache-2.0

"""Exercise actual shadow-query code and libc wrappers with IRQ/read counters.

Only the temporary host translation unit substitutes shadow loads with counted
loads. Production code has no measurement hooks or counters.
"""

from pathlib import Path
import unittest

import test_asan_libc_host as host


PREFIX = r'''
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "asan.h"
typedef uintptr_t rt_uintptr_t;
typedef uint8_t rt_uint8_t;
typedef int rt_base_t;
#define RT_NULL NULL
#define ASAN_SHADOW_SCALE 8
#define ASAN_MIN(a,b) ((a) < (b) ? (a) : (b))
static char storage[262160] __attribute__((aligned(8)));
static unsigned char asan_shadow[sizeof(storage) / 8];
static uintptr_t asan_heap_base, asan_heap_limit;
static volatile unsigned int loads, held_loads, max_loads, locks, held, reports;
static rt_base_t asan_lock(void)
{
    assert(!held); held = 1; held_loads = 0; locks++; return 0;
}
static void asan_unlock(rt_base_t level)
{
    (void)level; assert(held); held = 0;
    if (held_loads > max_loads) max_loads = held_loads;
}
static unsigned char shadow_read(size_t index)
{
    assert(held && index < sizeof(asan_shadow));
    loads++; held_loads++; return asan_shadow[index];
}
static rt_bool_t asan_addr_in_range(uintptr_t addr)
{
    return addr >= asan_heap_base && addr < asan_heap_limit;
}
'''

SUFFIX = r'''
rt_bool_t rt_asan_check_read(const void *ptr, rt_size_t size)
{
    if (asan_range_is_poisoned((uintptr_t)ptr, size))
    {
        reports++; return RT_FALSE;
    }
    return RT_TRUE;
}
rt_bool_t rt_asan_check_write(void *ptr, rt_size_t size)
{
    return rt_asan_check_read(ptr, size);
}
static void reset(void)
{
    loads = held_loads = max_loads = locks = held = reports = 0;
}
int main(void)
{
    size_t available, offset, n;
    asan_heap_base = (uintptr_t)storage;
    asan_heap_limit = asan_heap_base + sizeof(storage);
    memset(storage, 'a', sizeof(storage));
    memset(asan_shadow, 0, sizeof(asan_shadow));
    asan_shadow[262144 / 8] = 0xf8;
    reset();
    available = 123;
    assert(!rt_asan_accessible_size(storage, 0, &available));
    assert(available == 123 && locks == 0 && loads == 0);
    assert(!rt_asan_accessible_size(storage, 1, &available));
    assert(loads == 1 && max_loads == 1);
    reset();
    assert(strnlen(storage, 0) == 0 && locks == 0);
    assert(strnlen(storage, 1) == 1 && loads == 1 && locks == 1);
    reset();
    storage[0] = 0;
    assert(strlen(storage) == 0);
    assert(loads == 8 && locks == 1);
    storage[0] = 'a';
    for (n = 1; n <= 129; n++)
    {
        for (offset = 0; offset < 8; offset++)
        {
            reset();
            storage[offset + n] = 0;
            assert(strlen(storage + offset) == n);
            assert(locks == (n + 1 + 63) / 64 && max_loads <= 9);
            storage[offset + n] = 'a';
        }
    }
    /* A terminator before poison in the same chunk must not report. */
    asan_shadow[8] = 1; storage[64] = 0;
    reset(); assert(strlen(storage) == 64 && reports == 0);
    storage[64] = 'a';
    reset(); assert(strnlen(storage, 65) == 65 && reports == 0);
    reset(); assert(strnlen(storage, 66) == 65 && reports == 1);
    reset(); available = 123;
    assert(!rt_asan_accessible_size(storage, 65, &available));
    assert(available == 123);
    assert(rt_asan_accessible_size(storage, 66, &available) && available == 65);
    asan_shadow[8] = 0;
    /* Compare every partial-granule prefix against a byte-level oracle. */
    for (n = 0; n < 8; n++)
    {
        size_t start, limit;
        asan_shadow[2] = n ? n : 0xf8;
        for (start = 0; start < 32; start++)
        {
            for (limit = 0; limit <= 96; limit++)
            {
                size_t expected;
                int found = 0;
                for (expected = 0; expected < limit; expected++)
                {
                    size_t address = start + expected;
                    if (address >= 16 + n && address < 24)
                    {
                        found = 1; break;
                    }
                }
                reset(); available = 999;
                assert(rt_asan_accessible_size(storage + start, limit,
                       &available) == found);
                assert(available == (found ? expected : 999));
                assert(max_loads <= 9 && (!limit ? loads == 0 : 1));
            }
        }
    }
    asan_shadow[2] = 0;
    /* Long range and unbounded destination queries must release the IRQ lock. */
    reset();
    assert(rt_asan_accessible_size(storage + 1, SIZE_MAX, &available));
    assert(available == 262143 && max_loads <= 9 && locks > 4000);
    reset();
    assert(!rt_asan_check_read(storage + 1, SIZE_MAX));
    assert(reports == 1 && max_loads <= 9 && locks > 4000);
    reset();
    assert(snprintf(storage, 1, "abc") == 3 && storage[0] == 0);
    assert(max_loads == 1 && loads == 2 && reports == 0);
    reset();
    assert(sprintf(storage, "abc") == 3 && reports == 0 && max_loads <= 8);
    assert(strcmp(storage, "abc") == 0);
    reset();
    asan_heap_limit = asan_heap_base + 65;
    asan_shadow[8] = 1;
    assert(!rt_asan_accessible_size(storage, SIZE_MAX, &available));
    assert(max_loads <= 8);
    assert(!rt_asan_accessible_size(storage + 65, 1, &available));
    assert(rt_asan_check_read(storage + 65, 1)); /* outside coverage: clean */
    return 0;
}
'''


@unittest.skipUnless(host.shutil.which('gcc'), 'requires host GCC and GNU ld')
class AsanQueryTest(unittest.TestCase):
    def test_bounded_queries_and_string_early_exit(self):
        runtime = (Path(__file__).resolve().parents[2] /
                   'components/utilities/asan/asan.c').read_text()
        begin = runtime.index('static rt_bool_t asan_find_poison(')
        end = runtime.index('\nstatic void asan_locate_block', begin)
        functions = runtime[begin:end]
        begin = runtime.index('rt_bool_t rt_asan_accessible_size(')
        end = runtime.index('\n#endif', begin)
        functions += '\n' + runtime[begin:end]
        functions = functions.replace('asan_shadow[off >> 3]',
                                      'shadow_read(off >> 3)')
        fixture = PREFIX + functions + SUFFIX
        host.AsanLibcHostTest().compile_and_run(fixture)


if __name__ == '__main__':
    unittest.main()
