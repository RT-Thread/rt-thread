#!/usr/bin/env python3
# Copyright (c) 2006-2026, RT-Thread Development Team
# SPDX-License-Identifier: Apache-2.0

"""Check formatter side effects using the actual libc wrapper and GNU ld."""

from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest


RTTHREAD_HEADER = r'''
#ifndef TEST_RTTHREAD_H
#define TEST_RTTHREAD_H
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#define RT_ASAN_USING_LIBC
#define RT_TRUE 1
#define RT_FALSE 0
typedef int rt_bool_t;
typedef size_t rt_size_t;
typedef uint32_t rt_uint32_t;
#endif
'''

FORMAT_ONCE_FIXTURE = r'''
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "asan.h"
static char storage[10];
static unsigned int calls;
static size_t native_limit;
rt_bool_t rt_asan_accessible_size(const void *ptr, rt_size_t *size)
{
    uintptr_t address = (uintptr_t)ptr;
    uintptr_t begin = (uintptr_t)storage;
    if (address < begin || address > begin + sizeof(storage)) return RT_FALSE;
    *size = begin + sizeof(storage) - address;
    return RT_TRUE;
}
rt_bool_t rt_asan_check_read(const void *ptr, rt_size_t size)
{
    (void)ptr; (void)size; return RT_TRUE;
}
rt_bool_t rt_asan_check_write(void *ptr, rt_size_t size)
{
    rt_size_t available;
    return !rt_asan_accessible_size(ptr, &available) || size <= available;
}
/* This is the real formatter reached through GNU ld's __real_vsnprintf.
 * Count calls independently of the wrapper, without overlapping arguments.
 */
int vsnprintf(char *dst, size_t size, const char *fmt, va_list args)
{
    const char text[] = "abc";
    size_t i;
    assert(strcmp(fmt, "abc%n") == 0);
    calls++;
    native_limit = size;
    *va_arg(args, int *) = 3;
    if (size)
    {
        for (i = 0; i < 3 && i + 1 < size; i++) dst[i] = text[i];
        dst[i] = 0;
    }
    return 3;
}
int va_format(char *, size_t, int, const char *, ...);
int main(void)
{
    int count = 0;
    assert(snprintf(storage, 100, "abc%n", &count) == 3);
    assert(count == 3 && calls == 1 && native_limit == sizeof(storage));
    assert(strcmp(storage, "abc") == 0);
    calls = 0; count = 0;
    assert(snprintf(NULL, 0, "abc%n", &count) == 3);
    assert(count == 3 && calls == 1 && native_limit == 0);
    calls = 0; count = 0;
    assert(sprintf(storage, "abc%n", &count) == 3);
    assert(count == 3 && calls == 1 && native_limit == sizeof(storage));
    calls = 0; count = 0;
    assert(va_format(storage, 100, 1, "abc%n", &count) == 3);
    assert(count == 3 && calls == 1 && native_limit == sizeof(storage));
    calls = 0; count = 0;
    assert(va_format(storage, 0, 0, "abc%n", &count) == 3);
    assert(count == 3 && calls == 1 && native_limit == sizeof(storage));
    return 0;
}
'''

VA_CALLER_FIXTURE = r'''
#include <stdio.h>
#include <stdarg.h>
/* Separate object: --wrap only redirects unresolved references. */
int va_format(char *dst, size_t size, int bounded, const char *fmt, ...)
{
    int result;
    va_list args;
    va_start(args, fmt);
    result = bounded ? vsnprintf(dst, size, fmt, args) : vsprintf(dst, fmt, args);
    va_end(args);
    return result;
}
'''

VARARGS_FIXTURE = r'''
#include <assert.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include "asan.h"
static char source[16] __attribute__((aligned(16)));
static char output[256];
static unsigned int reports;
int __real_vsnprintf(char *, size_t, const char *, va_list);
rt_bool_t rt_asan_accessible_size(const void *ptr, rt_size_t *size)
{
    uintptr_t address = (uintptr_t)ptr, begin = (uintptr_t)source;
    if (address >= begin && address <= begin + sizeof(source))
    {
        *size = address < begin + 10 ? begin + 10 - address : 0;
        return RT_TRUE;
    }
    begin = (uintptr_t)output;
    if (address >= begin && address <= begin + sizeof(output))
    {
        *size = begin + sizeof(output) - address;
        return RT_TRUE;
    }
    return RT_FALSE;
}
rt_bool_t rt_asan_check_read(const void *ptr, rt_size_t size)
{
    rt_size_t available;
    if (size && rt_asan_accessible_size(ptr, &available) && size > available)
    {
        reports++;
        return RT_FALSE;
    }
    return RT_TRUE;
}
rt_bool_t rt_asan_check_write(void *ptr, rt_size_t size)
{
    return rt_asan_check_read(ptr, size);
}
static void parity(const char *fmt, ...)
{
    char expected[256];
    va_list args, copy;
    int native, wrapped;
    va_start(args, fmt);
    va_copy(copy, args);
    native = __real_vsnprintf(expected, sizeof(expected), fmt, copy);
    va_end(copy);
    wrapped = vsnprintf(output, sizeof(output), fmt, args);
    va_end(args);
    assert(wrapped == native);
    if (native >= 0) assert(strcmp(output, expected) == 0);
}
int main(void)
{
    const char *integers = "%jd/%ju/%zd/%zu/%td/%tu/%hhd/%hhu/%hd/%hu/%ld/%lu/%lld/%llu/%s";
    const char *floats = "%.2a/%.2A/%.2e/%.2E/%.2f/%.2F/%.2g/%.2G/%.2Lf/%c/%p/%s";
    strcpy((char *)source, "abc");
    parity(integers, (intmax_t)-1, (uintmax_t)2, (ptrdiff_t)-3, (size_t)4,
        (ptrdiff_t)-5, (size_t)6, (int)-7, (unsigned int)8, (int)-9,
        (unsigned int)10, -11L, 12UL, -13LL, 14ULL, source);
    parity(floats, 1.25, 1.25, 1.25, 1.25, 1.25, 1.25, 1.25, 1.25,
        (long double)1.25, 'x', (void *)source, source);
    parity("%*.*s/%s", -5, 3, source, source);
    parity("%+020lld/%#018llx/%.0d/%-8s", LLONG_MIN, ULLONG_MAX, 0, source);
    parity("%1$.*2$s", source, 2);
    parity("%2$s/%1$d", 7, source);
    parity("%ls/%s", L"wide", source);
    parity("%m/%s", source); /* Unknown extension: preserve host libc behavior. */
    assert(reports == 0);
    memset(source, 'a', 10);
    strcpy(output, "keep");
    assert(snprintf(output, sizeof(output), integers, (intmax_t)-1, (uintmax_t)2,
        (ptrdiff_t)-3, (size_t)4, (ptrdiff_t)-5, (size_t)6, (int)-7,
        (unsigned int)8, (int)-9, (unsigned int)10, -11L, 12UL, -13LL,
        14ULL, source) == -1);
    assert(reports == 1 && strcmp(output, "keep") == 0);
    assert(snprintf(output, sizeof(output), floats, 1.25, 1.25, 1.25, 1.25,
        1.25, 1.25, 1.25, 1.25, (long double)1.25, 'x', (void *)source,
        source) == -1);
    assert(reports == 2 && strcmp(output, "keep") == 0);
    /* Positional syntax anywhere must be discovered before consuming args.
     * Zero precision avoids touching the poisoned source in native libc.
     */
    assert(snprintf(output, sizeof(output), "%1$.*2$s", source + 10, 0) == 0);
    assert(reports == 2);
    /* A positional conversion after an ordinary literal is still pre-scanned. */
    assert(snprintf(output, sizeof(output), "prefix/%1$.*2$s", source + 10, 0) == 7);
    assert(reports == 2);
    /* Every %n length consumes the correct pointer and validates its extent. */
#define CHECK_N(type, fmt) do { \
    unsigned int before = reports; \
    type value = 0; \
    assert(snprintf(NULL, 0, "a" fmt, &value) == 1); \
    assert(value == 1 && reports == before); \
    assert(snprintf(NULL, 0, fmt, (type *)(source + 16)) == -1); \
    assert(reports == before + 1); \
} while (0)
    CHECK_N(signed char, "%hhn");
    CHECK_N(short, "%hn");
    CHECK_N(int, "%n");
    CHECK_N(long, "%ln");
    CHECK_N(long long, "%lln");
    CHECK_N(intmax_t, "%jn");
    CHECK_N(ptrdiff_t, "%zn");
    CHECK_N(ptrdiff_t, "%tn");
#undef CHECK_N
    return 0;
}
'''


@unittest.skipUnless(shutil.which('gcc'), 'requires host GCC and GNU ld')
class AsanLibcHostTest(unittest.TestCase):
    def compile_and_run(self, fixture, caller=None):
        component = (Path(__file__).resolve().parents[2] /
                     'components/utilities/asan')
        with tempfile.TemporaryDirectory(prefix='asan-libc-test-') as directory:
            work = Path(directory)
            (work / 'rtthread.h').write_text(RTTHREAD_HEADER)
            (work / 'check.c').write_text(fixture)
            names = ('memcpy memmove memset strlen strnlen strcpy strncpy strcat '
                     'strncat sprintf vsprintf snprintf vsnprintf').split()
            command = ['gcc', '-std=gnu99', '-O2', '-fno-builtin',
                       '-U_FORTIFY_SOURCE', '-D_FORTIFY_SOURCE=0',
                       '-fsanitize=undefined', '-fno-sanitize-recover=undefined',
                       '-I' + str(work), '-I' + str(component),
                       str(component / 'asan_libc.c'), str(work / 'check.c'),
                       '-o', str(work / 'check')]
            if caller is not None:
                (work / 'caller.c').write_text(caller)
                command.append(str(work / 'caller.c'))
            command.extend('-Wl,--wrap=' + name for name in names)
            result = subprocess.run(command, capture_output=True, text=True,
                                    timeout=30)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            result = subprocess.run([str(work / 'check')], capture_output=True,
                                    text=True, timeout=30)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def test_native_formatter_executes_once(self):
        self.compile_and_run(FORMAT_ONCE_FIXTURE, VA_CALLER_FIXTURE)

    def test_host_varargs_and_format_fallback(self):
        self.compile_and_run(VARARGS_FIXTURE)


if __name__ == '__main__':
    unittest.main()
