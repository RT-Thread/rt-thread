/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>
#ifdef __NEWLIB__
#include <newlib.h>
#endif
#include "asan.h"
#include "utest.h"

/* Volatile function pointers exercise library symbols, including optimized
 * builds, rather than constant-folded builtins in the test itself.
 */
static char *(* volatile copy_string)(char *, const char *) = rt_strcpy;
static char *(* volatile copy_nstring)(char *, const char *, size_t) = rt_strncpy;
static size_t (* volatile string_length)(const char *) = rt_strlen;
static size_t (* volatile bounded_length)(const char *, size_t) = rt_strnlen;
static int (* volatile format_string)(char *, const char *, ...) = rt_sprintf;
static int (* volatile format_nstring)(char *, size_t, const char *, ...) = rt_snprintf;
static int (* volatile format_va)(char *, const char *, va_list) = rt_vsprintf;
static int (* volatile format_nva)(char *, size_t, const char *, va_list) = rt_vsnprintf;
static char *(* volatile libc_copy)(char *, const char *) = strcpy;
static int (* volatile libc_format)(char *, const char *, ...) = sprintf;
static void *(* volatile copy_memory)(void *, const void *, size_t) = rt_memcpy;
static void *(* volatile move_memory)(void *, const void *, size_t) = rt_memmove;
static void *(* volatile set_memory)(void *, int, size_t) = rt_memset;
#ifdef RT_ASAN_USING_LIBC
/* strnlen is hidden by some toolchains' POSIX feature profiles. */
size_t strnlen(const char *src, size_t size);
int __real_vsnprintf(char *dst, size_t size, const char *fmt, va_list args);
#ifdef RT_USING_CPLUSPLUS
void test_asan_libc_cpp(void);
#endif
#endif
static rt_bool_t libc_path;

enum library_operation
{
    COPY_EXACT,
    COPY_TERMINATOR_OVERFLOW,
    COPY_SOURCE_OVERREAD,
    COPY_UAF_SOURCE,
    NCOPY_PAD,
    NCOPY_OVERFLOW,
    NCOPY_BOUNDED,
    NCOPY_ZERO,
    LENGTH_SOURCE_OVERREAD,
    LENGTH_BOUNDED,
    LENGTH_ZERO,
    FORMAT_EXACT,
    FORMAT_OVERFLOW,
    FORMAT_VA_OVERFLOW,
    FORMAT_UAF_SOURCE,
    FORMAT_UAF_DESTINATION,
    FORMAT_SOURCE_OVERREAD,
    FORMAT_FORMAT_OVERREAD,
    NFORMAT_TRUNCATE,
    NFORMAT_LARGE_LIMIT,
    NFORMAT_OVERFLOW,
    NFORMAT_VA_OVERFLOW,
    NFORMAT_ZERO,
    NFORMAT_PRECISION,
    NFORMAT_PRECISION_EXACT,
    NFORMAT_PRECISION_ZERO,
    NFORMAT_PRECISION_NEGATIVE,
    NFORMAT_PRECISION_BARE,
    NFORMAT_WIDTH,
    NFORMAT_WIDTH_PRECISION,
    NFORMAT_WRITEBACK,
    LIBC_COPY_OVERFLOW,
    LIBC_FORMAT_EXACT,
    LIBC_FORMAT_OVERFLOW,
    MEMORY_COPY_WRITE,
    MEMORY_COPY_READ,
    MEMORY_MOVE_WRITE,
    MEMORY_MOVE_READ,
    MEMORY_SET_WRITE,
    MEMORY_UAF_READ,
    MEMORY_UAF_WRITE,
    MEMORY_ZERO,
    MEMORY_EXACT,
    MEMORY_OVERLAP,
    RANGE_CHECKS
};

enum expectation
{
    OBSERVE,
    CLEAN,
    DETECT
};

/* Only the setup bypasses ASan: put a terminator in the first redzone byte
 * so deliberately unterminated sources stop after one invalid byte. The
 * allocator reserves this redzone; no allocator metadata is overwritten.
 */
static __attribute__((no_sanitize_address)) void prepare_source(char *src)
{
    size_t i;
    for (i = 0; i < 10; i++)
    {
        src[i] = 'a';
    }
    src[10] = '\0';
}

#ifdef RT_ASAN_USING_LIBC
/* The allocator reserves at least eight right-redzone bytes. Only these
 * fixture helpers access them; normal test accesses remain instrumented.
 */
static __attribute__((no_sanitize_address)) void set_redzone_byte(char *ptr, unsigned char value)
{
    *(volatile unsigned char *)ptr = value;
}

static __attribute__((no_sanitize_address)) unsigned char get_redzone_byte(const char *ptr)
{
    return *(const volatile unsigned char *)ptr;
}
#endif

static int call_vsprintf(char *dst, const char *fmt, ...)
{
    int result;
    va_list args;
    va_start(args, fmt);
    result = format_va(dst, fmt, args);
    va_end(args);
    return result;
}

static int call_vsnprintf(char *dst, size_t size, const char *fmt, ...)
{
    int result;
    va_list args;
    va_start(args, fmt);
    result = format_nva(dst, size, fmt, args);
    va_end(args);
    return result;
}

static void check_operation(enum library_operation op, const char *name, enum expectation expected)
{
    char *src = rt_malloc(10);
    /* Keep the destination valid when isolating an unterminated source. */
    char *dst = rt_malloc(op == COPY_SOURCE_OVERREAD ? 32 : 10);
    rt_uint32_t before, reports;
    rt_bool_t src_freed = RT_FALSE, dst_freed = RT_FALSE;
    int result = 0;

    uassert_not_null(src);
    uassert_not_null(dst);
    if (!src || !dst)
    {
        rt_free(src);
        rt_free(dst);
        return;
    }
    prepare_source(src);
    set_memory(dst, 0, op == COPY_SOURCE_OVERREAD ? 32 : 10);
    before = rt_asan_report_count_get();
    switch (op)
    {
    case COPY_EXACT:
        src[9] = '\0';
        copy_string(dst, src);
        break;
    case COPY_TERMINATOR_OVERFLOW:
        copy_string(dst, "1234567890");
        break;
    case COPY_SOURCE_OVERREAD:
        copy_string(dst, src);
        break;
    case COPY_UAF_SOURCE:
        src[9] = '\0';
        rt_free(src);
        src_freed = RT_TRUE;
        copy_string(dst, src);
        break;
    case NCOPY_PAD:
        copy_nstring(dst, "a", 10);
        break;
    case NCOPY_OVERFLOW:
        copy_nstring(dst, "a", 11);
        break;
    case NCOPY_BOUNDED:
        copy_nstring(dst, src, 10);
        break;
    case NCOPY_ZERO:
        copy_nstring(dst + 10, src + 10, 0);
        break;
    case LENGTH_SOURCE_OVERREAD:
        string_length(src);
        break;
    case LENGTH_BOUNDED:
        uassert_int_equal(bounded_length(src, 10), 10);
        break;
    case LENGTH_ZERO:
        uassert_int_equal(bounded_length(src + 10, 0), 0);
        break;
    case FORMAT_EXACT:
        result = format_string(dst, "%s", "123456789");
        break;
    case FORMAT_OVERFLOW:
        format_string(dst, "%s", "1234567890");
        break;
    case FORMAT_VA_OVERFLOW:
        call_vsprintf(dst, "%s", "1234567890");
        break;
    case FORMAT_UAF_SOURCE:
        src[9] = '\0';
        rt_free(src);
        src_freed = RT_TRUE;
        format_nstring(dst, 10, "%s", src);
        break;
    case FORMAT_UAF_DESTINATION:
        rt_free(dst);
        dst_freed = RT_TRUE;
        format_string(dst, "%s", "a");
        break;
    case FORMAT_SOURCE_OVERREAD:
        format_nstring(dst, 10, "%s", src);
        break;
    case FORMAT_FORMAT_OVERREAD:
        format_nstring(dst, 10, src);
        break;
    case NFORMAT_TRUNCATE:
        format_nstring(dst, 10, "%s", "123456789012");
        break;
    case NFORMAT_LARGE_LIMIT:
        format_nstring(dst, 100, "%s", "a");
        break;
    case NFORMAT_OVERFLOW:
        format_nstring(dst, 11, "%s", "1234567890");
        break;
    case NFORMAT_VA_OVERFLOW:
        call_vsnprintf(dst, 11, "%s", "1234567890");
        break;
    case NFORMAT_ZERO:
        format_nstring(dst + 10, 0, "%s", "a");
        break;
    case NFORMAT_PRECISION:
        format_nstring(dst, 10, "%.3s", src);
        break;
    case NFORMAT_PRECISION_EXACT:
        format_nstring(dst, 10, "%.3s", src + 7);
        break;
    case NFORMAT_PRECISION_ZERO:
        format_nstring(dst, 10, "%.0s", src);
        break;
    case NFORMAT_PRECISION_NEGATIVE:
        uassert_int_equal(format_nstring(dst, 10, "%.*s", -1, "abc"), 3);
        uassert_str_equal(dst, "abc");
        uassert_int_equal(format_nstring(dst, 10, "%.*s", INT_MIN, "abc"), 3);
        uassert_str_equal(dst, "abc");
        uassert_int_equal(call_vsnprintf(dst, 10, "%5.*s", -1, "abc"), 5);
        uassert_str_equal(dst, "  abc");
        uassert_int_equal(format_nstring(dst, 10, "%.*d", -1, 0), 1);
        uassert_str_equal(dst, "0");
        break;
    case NFORMAT_PRECISION_BARE:
        uassert_int_equal(format_nstring(dst, 10, "%.s", src), 0);
        uassert_str_equal(dst, "");
        uassert_int_equal(format_nstring(dst, 10, "%.*s", 0, src), 0);
        uassert_str_equal(dst, "");
        break;
    case NFORMAT_WIDTH:
        format_nstring(dst, 10, "%3s", "abcdefg");
        break;
    case NFORMAT_WIDTH_PRECISION:
        format_nstring(dst, 10, "%5.3s", src);
        break;
    case NFORMAT_WRITEBACK:
        format_nstring(dst, 10, "a%n", (int *)(src + 8));
        break;
    case LIBC_COPY_OVERFLOW:
        libc_copy(dst, "1234567890");
        break;
    case LIBC_FORMAT_EXACT:
        result = libc_format(dst, "%s", "123456789");
        break;
    case LIBC_FORMAT_OVERFLOW:
        libc_format(dst, "%s", "1234567890");
        break;
    case MEMORY_COPY_WRITE:
        copy_memory(dst, "123456789012", 13);
        break;
    case MEMORY_COPY_READ:
        copy_memory(dst, src + 8, 3);
        break;
    case MEMORY_MOVE_WRITE:
        move_memory(dst, "123456789012", 13);
        break;
    case MEMORY_MOVE_READ:
        move_memory(dst, src + 8, 3);
        break;
    case MEMORY_SET_WRITE:
        set_memory(dst, 'a', 13);
        break;
    case MEMORY_UAF_READ:
        rt_free(src);
        src_freed = RT_TRUE;
        copy_memory(dst, src, 3);
        break;
    case MEMORY_UAF_WRITE:
        rt_free(dst);
        dst_freed = RT_TRUE;
        set_memory(dst, 'a', 3);
        break;
    case MEMORY_ZERO:
        copy_memory(dst + 10, src + 10, 0);
        move_memory(dst + 10, src + 10, 0);
        set_memory(dst + 10, 0, 0);
        break;
    case MEMORY_EXACT:
        set_memory(dst, 'b', 10);
        copy_memory(dst + 1, src + 1, 9);
        uassert_int_equal(dst[0], 'b');
        uassert_int_equal(dst[9], 'a');
        break;
    case MEMORY_OVERLAP:
        set_memory(dst, 'b', 10);
        dst[0] = 'a';
        move_memory(dst + 1, dst, 9);
        uassert_int_equal(dst[1], 'a');
        uassert_int_equal(dst[9], 'b');
        break;
    case RANGE_CHECKS:
        uassert_true(rt_asan_check_read(src, 10));
        uassert_true(rt_asan_check_write(dst, 10));
        uassert_true(rt_asan_check_read(src + 10, 0));
        uassert_true(rt_asan_check_write(dst + 10, 0));
        uassert_false(rt_asan_check_read(src + 8, 3));
        uassert_false(rt_asan_check_write(dst + 8, 3));
        break;
    }
    reports = rt_asan_report_count_get() - before;
    switch (op)
    {
    case COPY_EXACT:
        uassert_str_equal(dst, "aaaaaaaaa");
        break;
    case FORMAT_EXACT:
    case LIBC_FORMAT_EXACT:
        rt_kprintf("[asan-libc] format exact result=%d\n", result);
        uassert_int_equal(result, 9);
        uassert_str_equal(dst, "123456789");
        break;
    case NFORMAT_TRUNCATE:
        uassert_str_equal(dst, "123456789");
        break;
    case NFORMAT_LARGE_LIMIT:
        uassert_str_equal(dst, "a");
        break;
    case NFORMAT_PRECISION:
    case NFORMAT_PRECISION_EXACT:
        uassert_str_equal(dst, "aaa");
        break;
    case NFORMAT_PRECISION_ZERO:
        uassert_str_equal(dst, "");
        break;
    case NFORMAT_WIDTH:
        uassert_str_equal(dst, "abcdefg");
        break;
    case NFORMAT_WIDTH_PRECISION:
        uassert_str_equal(dst, "  aaa");
        break;
    default:
        break;
    }
    if (!src_freed)
    {
        rt_free(src);
    }
    if (!dst_freed)
    {
        rt_free(dst);
    }
    rt_kprintf("[asan-libc] %s / %s: reports=%lu expected=%s\n", libc_path ? "libc" : "rt", name,
               (unsigned long)reports, expected == OBSERVE ? "observe" : expected == CLEAN ? "clean"
                                                                                           : "detect");
    if (expected == CLEAN)
    {
        uassert_int_equal(reports, 0);
    }
    else if (expected == DETECT)
    {
        uassert_true(reports > 0);
    }
}

static void test_library_boundaries(void)
{
    enum expectation copy_expected = DETECT;
    enum expectation ncopy_expected = DETECT;
    enum expectation length_expected = DETECT;
    enum expectation format_expected = DETECT;
    enum expectation memcpy_expected = DETECT;
    enum expectation memmove_expected = DETECT;
    enum expectation memset_expected = DETECT;
    enum expectation libc_expected = OBSERVE;

#if (defined(RT_KLIBC_USING_LIBC_STRCPY) && !defined(RT_ASAN_USING_LIBC)) || defined(RT_KLIBC_USING_USER_STRCPY)
    copy_expected = OBSERVE;
#endif
#if (defined(RT_KLIBC_USING_LIBC_STRNCPY) && !defined(RT_ASAN_USING_LIBC)) || defined(RT_KLIBC_USING_USER_STRNCPY)
    ncopy_expected = OBSERVE;
#endif
#if defined(RT_KLIBC_USING_LIBC_VSNPRINTF) && !defined(RT_ASAN_USING_LIBC)
    format_expected = OBSERVE;
#endif
#if (defined(RT_KLIBC_USING_LIBC_STRLEN) && !defined(RT_ASAN_USING_LIBC)) || defined(RT_KLIBC_USING_USER_STRLEN)
    length_expected = OBSERVE;
#endif
#ifdef RT_KLIBC_USING_USER_MEMCPY
    memcpy_expected = OBSERVE;
#endif
#ifdef RT_KLIBC_USING_USER_MEMMOVE
    memmove_expected = OBSERVE;
#endif
#ifdef RT_KLIBC_USING_USER_MEMSET
    memset_expected = OBSERVE;
#endif
#ifdef RT_ASAN_USING_LIBC
    libc_expected = DETECT;
    if (libc_path)
    {
        copy_expected = ncopy_expected = length_expected = format_expected = DETECT;
        memcpy_expected = memmove_expected = memset_expected = DETECT;
    }
#endif
    check_operation(COPY_EXACT, "rt_strcpy exact", CLEAN);
    check_operation(COPY_TERMINATOR_OVERFLOW, "rt_strcpy terminator overflow", copy_expected);
    check_operation(COPY_SOURCE_OVERREAD, "rt_strcpy source overread", copy_expected);
    check_operation(NCOPY_PAD, "rt_strncpy padding", CLEAN);
    check_operation(NCOPY_OVERFLOW, "rt_strncpy padding overflow", ncopy_expected);
    check_operation(NCOPY_BOUNDED, "rt_strncpy bounded unterminated source", CLEAN);
    check_operation(NCOPY_ZERO, "rt_strncpy zero", CLEAN);
    check_operation(LENGTH_SOURCE_OVERREAD, "rt_strlen source overread", length_expected);
    check_operation(LENGTH_BOUNDED, "rt_strnlen bounded source", CLEAN);
    check_operation(LENGTH_ZERO, "rt_strnlen zero", CLEAN);
    check_operation(FORMAT_EXACT, "rt_sprintf exact", CLEAN);
    check_operation(FORMAT_OVERFLOW, "rt_sprintf terminator overflow", format_expected);
    check_operation(FORMAT_VA_OVERFLOW, "rt_vsprintf terminator overflow", format_expected);
    check_operation(FORMAT_SOURCE_OVERREAD, "rt_snprintf source overread", format_expected);
    check_operation(FORMAT_FORMAT_OVERREAD, "rt_snprintf format overread", format_expected);
    check_operation(NFORMAT_TRUNCATE, "rt_snprintf truncation", CLEAN);
    check_operation(NFORMAT_LARGE_LIMIT, "rt_snprintf large limit short output", CLEAN);
    check_operation(NFORMAT_OVERFLOW, "rt_snprintf excessive output", format_expected);
    check_operation(NFORMAT_VA_OVERFLOW, "rt_vsnprintf excessive output", format_expected);
    check_operation(NFORMAT_ZERO, "rt_snprintf zero", CLEAN);
    /* A precision-bounded %s must not read beyond its precision, even when
     * the source is not terminated. Keep this a real assertion: it exposes
     * regressions in the formatter's precision handling.
     */
    check_operation(NFORMAT_PRECISION, "rt_snprintf precision bounded source", CLEAN);
    check_operation(NFORMAT_PRECISION_EXACT, "rt_snprintf precision at allocation end", CLEAN);
    check_operation(NFORMAT_PRECISION_ZERO, "rt_snprintf zero precision", CLEAN);
    check_operation(NFORMAT_PRECISION_NEGATIVE, "rt_snprintf negative dynamic precision", CLEAN);
    check_operation(NFORMAT_PRECISION_BARE, "rt_snprintf bare and dynamic zero precision", CLEAN);
    check_operation(NFORMAT_WIDTH, "rt_snprintf width does not truncate", CLEAN);
    check_operation(NFORMAT_WIDTH_PRECISION, "rt_snprintf width with bounded precision", CLEAN);
#if defined(RT_KLIBC_USING_VSNPRINTF_WRITEBACK_SPECIFIER) || defined(RT_KLIBC_USING_LIBC_VSNPRINTF)
    check_operation(NFORMAT_WRITEBACK, "rt_snprintf writeback overflow", format_expected);
#elif defined(RT_ASAN_USING_LIBC)
    if (libc_path)
    {
        check_operation(NFORMAT_WRITEBACK, "snprintf writeback overflow", DETECT);
    }
#endif
    check_operation(LIBC_COPY_OVERFLOW, "libc strcpy overflow", libc_expected);
    check_operation(LIBC_FORMAT_EXACT, "libc sprintf exact", CLEAN);
    check_operation(LIBC_FORMAT_OVERFLOW, "libc sprintf overflow", libc_expected);
    check_operation(MEMORY_COPY_WRITE, "rt_memcpy destination overflow", memcpy_expected);
    check_operation(MEMORY_COPY_READ, "rt_memcpy source overread", memcpy_expected);
    check_operation(MEMORY_MOVE_WRITE, "rt_memmove destination overflow", memmove_expected);
    check_operation(MEMORY_MOVE_READ, "rt_memmove source overread", memmove_expected);
    check_operation(MEMORY_SET_WRITE, "rt_memset destination overflow", memset_expected);
    check_operation(MEMORY_ZERO, "memory functions zero", CLEAN);
    check_operation(MEMORY_EXACT, "memory functions exact unaligned range", CLEAN);
    check_operation(MEMORY_OVERLAP, "rt_memmove valid overlap", CLEAN);
    check_operation(RANGE_CHECKS, "explicit range checks", DETECT);
#if RT_ASAN_HAS_UAF_DETECTION
    check_operation(COPY_UAF_SOURCE, "rt_strcpy freed source", copy_expected);
    check_operation(FORMAT_UAF_SOURCE, "rt_snprintf freed source", format_expected);
    check_operation(FORMAT_UAF_DESTINATION, "rt_sprintf freed destination", format_expected);
    check_operation(MEMORY_UAF_READ, "rt_memcpy freed source", memcpy_expected);
    check_operation(MEMORY_UAF_WRITE, "rt_memset freed destination", memset_expected);
#endif
}

#ifdef RT_ASAN_USING_LIBC
/* Exercise partial granules and exact 8-byte multiples, with both redzones.
 * Each invalid wrapper call must report before changing the destination.
 */
static void test_libc_memory_sizes(void)
{
    static const size_t sizes[] = { 1, 2, 7, 8, 9, 15, 16, 17, 31, 32, 33 };
    void *(*functions[])(void *, const void *, size_t) = { memcpy, memmove };
    size_t i, j, offset;
    rt_size_t available;
    rt_uint32_t before;
    for (i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++)
    {
        size_t size = sizes[i];
        char *src = rt_malloc(size);
        char *dst = rt_malloc(size);
        uassert_not_null(src);
        uassert_not_null(dst);
        if (!src || !dst)
        {
            rt_free(src);
            rt_free(dst);
            return;
        }
        before = rt_asan_report_count_get();
        memset(src, 'a', size);
        set_redzone_byte(dst + size, 0x5a);
        for (offset = 0; offset <= size; offset++)
        {
            uassert_true(rt_asan_accessible_size(src + offset, &available));
            uassert_int_equal(available, size - offset);
        }
        for (j = 0; j < sizeof(functions) / sizeof(functions[0]); j++)
        {
            memset(dst, 'b', size);
            uassert_true(functions[j](dst, src, size) == dst);
            uassert_int_equal(dst[0], 'a');
            uassert_int_equal(dst[size - 1], 'a');
            uassert_true(functions[j](dst + 1, src + 1, size - 1) == dst + 1);
            uassert_true(functions[j](dst + size, src + size, 0) == dst + size);
            uassert_int_equal(rt_asan_report_count_get(), before);
            memset(dst, 'b', size);
            uassert_true(functions[j](dst, src, size + 1) == dst);
            uassert_true(rt_asan_report_count_get() > before);
            uassert_int_equal(get_redzone_byte(dst + size), 0x5a);
            uassert_int_equal(dst[0], 'b');
            uassert_int_equal(dst[size - 1], 'b');
            before = rt_asan_report_count_get();
            functions[j](dst, src - 1, 1);
            uassert_true(rt_asan_report_count_get() > before);
            uassert_int_equal(get_redzone_byte(dst + size), 0x5a);
            uassert_int_equal(dst[0], 'b');
            before = rt_asan_report_count_get();
            functions[j](dst - 1, src, 1);
            uassert_true(rt_asan_report_count_get() > before);
            uassert_int_equal(get_redzone_byte(dst + size), 0x5a);
            uassert_int_equal(dst[0], 'b');
            before = rt_asan_report_count_get();
            /* Isolate a destination overflow from a valid source. */
            functions[j](dst + size, src, 1);
            uassert_true(rt_asan_report_count_get() > before);
            uassert_int_equal(get_redzone_byte(dst + size), 0x5a);
            before = rt_asan_report_count_get();
        }
        uassert_true(memset(dst, 'c', size) == dst);
        uassert_true(memset(dst + size, 'c', 0) == dst + size);
        uassert_int_equal(rt_asan_report_count_get(), before);
        uassert_true(memset(dst, 'd', size + 1) == dst);
        uassert_true(rt_asan_report_count_get() > before);
        uassert_int_equal(get_redzone_byte(dst + size), 0x5a);
        uassert_int_equal(dst[size - 1], 'c');
        before = rt_asan_report_count_get();
        memset(dst - 1, 'd', 1);
        uassert_true(rt_asan_report_count_get() > before);
        uassert_int_equal(get_redzone_byte(dst + size), 0x5a);
        rt_free(src);
        rt_free(dst);
    }
    /* Overlap must work in both directions; memcpy overlap is not valid. */
    {
        char *p = rt_malloc(8);
        uassert_not_null(p);
        if (!p)
        {
            return;
        }
        before = rt_asan_report_count_get();
        strcpy(p, "abcdefg");
        memmove(p + 1, p, 7);
        uassert_int_equal(p[7], 'g');
        memmove(p, p + 1, 7);
        p[7] = 0;
        uassert_str_equal(p, "abcdefg");
        uassert_int_equal(rt_asan_report_count_get(), before);
        rt_free(p);
    }
}

static void test_libc_extreme_counts(void)
{
    char *src = rt_malloc(16);
    char *dst = rt_malloc(16);
    rt_uint32_t before;
    uassert_not_null(src);
    uassert_not_null(dst);
    if (!src || !dst)
    {
        rt_free(src);
        rt_free(dst);
        return;
    }
    strcpy(src, "a");
    strcpy(dst, "keep");
    before = rt_asan_report_count_get();
    uassert_true(memmove(dst, dst, 16) == dst);
    uassert_int_equal(strnlen(src, (size_t)-1), 1);
    strncat(dst, src, (size_t)-1);
    uassert_str_equal(dst, "keepa");
    uassert_int_equal(rt_asan_report_count_get(), before);
    /* These counts must not wrap the range end into an apparently valid span.
     * The libc operation must be skipped, not called with the enormous count.
     */
    memcpy(dst, src, (size_t)-1);
    uassert_true(rt_asan_report_count_get() > before);
    uassert_str_equal(dst, "keepa");
    before = rt_asan_report_count_get();
    memmove(dst, src, (size_t)-1);
    uassert_true(rt_asan_report_count_get() > before);
    uassert_str_equal(dst, "keepa");
    before = rt_asan_report_count_get();
    memset(dst, 0, (size_t)-1);
    uassert_true(rt_asan_report_count_get() > before);
    uassert_str_equal(dst, "keepa");
    before = rt_asan_report_count_get();
    strncpy(dst, src, (size_t)-1); /* Huge padding after the early NUL. */
    uassert_true(rt_asan_report_count_get() > before);
    uassert_str_equal(dst, "keepa");
    before = rt_asan_report_count_get();
    uassert_false(rt_asan_check_read(src, (rt_size_t)-1));
    uassert_false(rt_asan_check_write(dst, (rt_size_t)-1));
    uassert_true(rt_asan_report_count_get() > before);
    rt_free(src);
    rt_free(dst);
}

static void test_libc_string_sizes(void)
{
    static const size_t sizes[] = { 1, 7, 8, 9, 15, 16, 17 };
    size_t i, offset;
    rt_uint32_t before;
    for (i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++)
    {
        size_t size = sizes[i];
        char *src = rt_malloc(size);
        char *dst = rt_malloc(size);
        uassert_not_null(src);
        uassert_not_null(dst);
        if (!src || !dst)
        {
            rt_free(src);
            rt_free(dst);
            return;
        }
        before = rt_asan_report_count_get();
        memset(src, 'a', size);
        set_redzone_byte(src + size, 0);
        src[size - 1] = 0;
        for (offset = 0; offset < size; offset++)
        {
            uassert_int_equal(strlen(src + offset), size - offset - 1);
            uassert_int_equal(strnlen(src + offset, size + 1), size - offset - 1);
        }
        uassert_true(strcpy(dst, src) == dst);
        uassert_str_equal(dst, src);
        uassert_true(strncpy(dst, "", size) == dst);
        for (offset = 0; offset < size; offset++)
        {
            uassert_int_equal(dst[offset], 0);
        }
        uassert_true(strncpy(dst + size, src + size, 0) == dst + size);
        uassert_int_equal(strnlen(src + size, 0), 0);
        uassert_int_equal(rt_asan_report_count_get(), before);
        strcpy(dst + 1, src);
        uassert_true(rt_asan_report_count_get() > before);
        uassert_int_equal(dst[0], 0);
        before = rt_asan_report_count_get();
        strncpy(dst, "", size + 1);
        uassert_true(rt_asan_report_count_get() > before);
        before = rt_asan_report_count_get();
        strcpy(dst, src - 1);
        uassert_true(rt_asan_report_count_get() > before);
        before = rt_asan_report_count_get();
        memset(src, 'a', size);
        set_redzone_byte(src + size, 0); /* Unterminated, with a poisoned byte next. */
        uassert_int_equal(strnlen(src, size), size);
        uassert_true(strncpy(dst, src, size) == dst);
        uassert_int_equal(dst[size - 1], 'a');
        uassert_int_equal(rt_asan_report_count_get(), before);
        uassert_int_equal(strlen(src), size);
        uassert_true(rt_asan_report_count_get() > before);
        before = rt_asan_report_count_get();
        uassert_int_equal(strnlen(src, size + 1), size);
        uassert_true(rt_asan_report_count_get() > before);
        before = rt_asan_report_count_get();
        memset(dst, 'b', size);
        strcpy(dst, src);
        uassert_true(rt_asan_report_count_get() > before);
        uassert_int_equal(dst[0], 'b');
        before = rt_asan_report_count_get();
        /* A large bound is legal if the source terminates before it. */
        src[0] = 0;
        uassert_int_equal(strnlen(src, (size_t)-1), 0);
        strcat(dst, src); /* The destination is still unterminated. */
        uassert_true(rt_asan_report_count_get() > before);
        uassert_int_equal(dst[0], 'b');
        rt_free(src);
        rt_free(dst);
    }
}

static void test_libc_append(void)
{
    char *dst = rt_malloc(10);
    char *src = rt_malloc(10);
    rt_uint32_t before;
    uassert_not_null(dst);
    uassert_not_null(src);
    if (!dst || !src)
    {
        rt_free(dst);
        rt_free(src);
        return;
    }
    prepare_source(src);
    before = rt_asan_report_count_get();
    strcpy(dst, "abc");
    strcat(dst, "def");
    uassert_str_equal(dst, "abcdef");
    uassert_int_equal(rt_asan_report_count_get(), before);
    strcat(dst, "ghij");
    uassert_true(rt_asan_report_count_get() > before);
    uassert_str_equal(dst, "abcdef");
    before = rt_asan_report_count_get();
    strcat(dst, src);
    uassert_true(rt_asan_report_count_get() > before);
    before = rt_asan_report_count_get();
    strcpy(dst, "a");
    strncat(dst, src, 3);
    uassert_str_equal(dst, "aaaa");
    strncat(dst, "b", 100);
    uassert_str_equal(dst, "aaaab");
    strncat(dst, src + 10, 0);
    uassert_int_equal(rt_asan_report_count_get(), before);
    strncat(dst, src, 10);
    uassert_true(rt_asan_report_count_get() > before);
    rt_free(src);
    rt_free(dst);
}

static void test_libc_append_boundaries(void)
{
    char *src = rt_malloc(10);
    char *dst = rt_malloc(10);
    rt_uint32_t before;
    uassert_not_null(src);
    uassert_not_null(dst);
    if (!src || !dst)
    {
        rt_free(src);
        rt_free(dst);
        return;
    }
    prepare_source(src);
    before = rt_asan_report_count_get();
    strcpy(dst, "123456789");
    uassert_true(strcat(dst, "") == dst);
    uassert_true(strncat(dst, src + 10, 0) == dst);
    uassert_int_equal(rt_asan_report_count_get(), before);
    strncat(dst, "a", 1);
    uassert_true(rt_asan_report_count_get() > before);
    uassert_str_equal(dst, "123456789");
    before = rt_asan_report_count_get();
    strcpy(dst, "");
    strncat(dst, src, 9); /* Read exactly nine bytes, then add a terminator. */
    uassert_str_equal(dst, "aaaaaaaaa");
    uassert_int_equal(rt_asan_report_count_get(), before);
    strcpy(dst, "");
    strncat(dst, src, 11);
    uassert_true(rt_asan_report_count_get() > before);
    uassert_str_equal(dst, "");
    before = rt_asan_report_count_get();
    memset(dst, 'b', 10);
    strncat(dst, "a", 0); /* Even zero-count append must scan its destination. */
    uassert_true(rt_asan_report_count_get() > before);
    uassert_int_equal(dst[0], 'b');
    before = rt_asan_report_count_get();
    strcat(dst + 10, "");
    uassert_true(rt_asan_report_count_get() > before);
    before = rt_asan_report_count_get();
    strcpy(dst, "ok");
    strcat(dst, src - 1);
    uassert_true(rt_asan_report_count_get() > before);
    uassert_str_equal(dst, "ok");
    rt_free(src);
    rt_free(dst);
}

static void test_libc_format_boundaries(void)
{
    char *src = rt_malloc(10);
    char *dst = rt_malloc(10);
    rt_uint32_t before;
    uassert_not_null(src);
    uassert_not_null(dst);
    if (!src || !dst)
    {
        rt_free(src);
        rt_free(dst);
        return;
    }
    prepare_source(src);
    set_redzone_byte(dst + 10, 0x5a);
    before = rt_asan_report_count_get();
    uassert_int_equal(format_nstring(NULL, 0, "%s", "abc"), 3);
    uassert_int_equal(call_vsnprintf(NULL, 0, "%s", "abc"), 3);
    uassert_int_equal(format_nstring(dst, 1, "%s", "abc"), 3);
    uassert_str_equal(dst, "");
    uassert_int_equal(format_nstring(dst, 10, "%.*s", 10, src), 10);
    uassert_str_equal(dst, "aaaaaaaaa");
    uassert_int_equal(format_nstring(dst, 10, "%.*s", 0, src + 10), 0);
    uassert_int_equal(format_nstring(dst, 10, "%.*s", 0, src - 1), 0);
    uassert_int_equal(format_nstring(dst + 10, 0, ""), 0);
    uassert_int_equal(format_nstring(dst + 9, 1, ""), 0);
    uassert_int_equal(format_string(dst + 9, ""), 0);
    uassert_int_equal(rt_asan_report_count_get(), before);

    uassert_int_equal(format_string(dst, "%s", "1234567890"), 10);
    uassert_true(rt_asan_report_count_get() > before);
    uassert_str_equal(dst, "123456789");
    uassert_int_equal(get_redzone_byte(dst + 10), 0x5a);
    before = rt_asan_report_count_get();
    uassert_int_equal(format_nstring(dst, 11, "%s", "1234567890"), 10);
    uassert_true(rt_asan_report_count_get() > before);
    uassert_str_equal(dst, "123456789");
    uassert_int_equal(get_redzone_byte(dst + 10), 0x5a);
    before = rt_asan_report_count_get();
    strcpy(dst, "keep");
    uassert_int_equal(format_nstring(dst, 10, "%.*s", 11, src), -1);
    uassert_true(rt_asan_report_count_get() > before);
    uassert_str_equal(dst, "keep");
    before = rt_asan_report_count_get();
    uassert_int_equal(format_nstring(dst, 10, "%.*s", -1, src), -1);
    uassert_true(rt_asan_report_count_get() > before);
    uassert_str_equal(dst, "keep");
    before = rt_asan_report_count_get();
    uassert_int_equal(format_nstring(NULL, 0, "%s", src), -1);
    uassert_true(rt_asan_report_count_get() > before);
    before = rt_asan_report_count_get();
    uassert_int_equal(call_vsnprintf(dst, 10, src), -1);
    uassert_true(rt_asan_report_count_get() > before);
    uassert_str_equal(dst, "keep");
    before = rt_asan_report_count_get();
    uassert_int_equal(call_vsprintf(dst, "%s", src - 1), -1);
    uassert_true(rt_asan_report_count_get() > before);
    uassert_str_equal(dst, "keep");
    before = rt_asan_report_count_get();
    uassert_int_equal(format_string(dst, src - 1), -1);
    uassert_true(rt_asan_report_count_get() > before);
    before = rt_asan_report_count_get();
    uassert_int_equal(format_nstring(dst + 10, 1, ""), -1);
    uassert_true(rt_asan_report_count_get() > before);
    before = rt_asan_report_count_get();
    uassert_int_equal(format_string(dst - 1, ""), -1);
    uassert_true(rt_asan_report_count_get() > before);
    before = rt_asan_report_count_get();
    /* Literal dollar signs and escaped percent signs must not disable checks. */
    uassert_int_equal(format_nstring(dst, 10, "cost $%s", src), -1);
    uassert_true(rt_asan_report_count_get() > before);
    before = rt_asan_report_count_get();
    uassert_int_equal(format_nstring(dst, 10, "%%2$s %s", src), -1);
    uassert_true(rt_asan_report_count_get() > before);
    before = rt_asan_report_count_get();
    /* Precision decimal overflow must saturate rather than wrap to zero. */
    uassert_int_equal(format_nstring(dst, 10, "%.999999999999999999999s", src), -1);
    uassert_true(rt_asan_report_count_get() > before);
    uassert_int_equal(get_redzone_byte(dst + 10), 0x5a);
    rt_free(src);
    rt_free(dst);
}

/* Allocate an aligned target with exactly the required size, then one byte
 * too few. For the one-byte case use its right redzone as the invalid target.
 */
#define CHECK_WRITEBACK(type, conversion)                                            \
    do                                                                               \
    {                                                                                \
        type *value = rt_malloc(sizeof(type));                                       \
        char *small = rt_malloc(sizeof(type) > 1 ? sizeof(type) - 1 : 1);            \
        rt_uint32_t before;                                                          \
        uassert_not_null(value);                                                     \
        uassert_not_null(small);                                                     \
        if (value && small)                                                          \
        {                                                                            \
            *value = 0;                                                              \
            before = rt_asan_report_count_get();                                     \
            uassert_int_equal(format_nstring(NULL, 0, "a" conversion, value), 1);    \
            uassert_int_equal(*value, 1);                                            \
            uassert_int_equal(rt_asan_report_count_get(), before);                   \
            uassert_int_equal(format_nstring(NULL, 0, conversion,                    \
                                             (type *)(small + (sizeof(type) == 1))), \
                              -1);                                                   \
            uassert_true(rt_asan_report_count_get() > before);                       \
        }                                                                            \
        rt_free(value);                                                              \
        rt_free(small);                                                              \
    } while (0)

static void test_libc_writeback_sizes(void)
{
    CHECK_WRITEBACK(int, "%n");
    CHECK_WRITEBACK(short, "%hn");
    CHECK_WRITEBACK(long, "%ln");
#if !defined(__NEWLIB__) || defined(_WANT_IO_LONG_LONG)
    CHECK_WRITEBACK(long long, "%lln");
#endif
#if !defined(__NEWLIB__) || defined(_WANT_IO_C99_FORMATS)
    CHECK_WRITEBACK(signed char, "%hhn");
    CHECK_WRITEBACK(intmax_t, "%jn");
    CHECK_WRITEBACK(ptrdiff_t, "%zn");
    CHECK_WRITEBACK(ptrdiff_t, "%tn");
#else
    rt_kprintf("[asan-libc] hh/j/z/t writeback unavailable in this Newlib configuration\n");
#endif
}
#undef CHECK_WRITEBACK

static void test_libc_all_uaf_entries(void)
{
#if RT_ASAN_HAS_UAF_DETECTION
    unsigned int operation;
    for (operation = 0; operation < 31; operation++)
    {
        char *dead = rt_malloc(16);
        char *live = rt_malloc(16);
        rt_uint32_t before;
        uassert_not_null(dead);
        uassert_not_null(live);
        if (!dead || !live)
        {
            rt_free(dead);
            rt_free(live);
            return;
        }
        strcpy(dead, "abc");
        strcpy(live, "keep");
        rt_free(dead);
        before = rt_asan_report_count_get();
        /* No allocation here: the dead pointer must not have been reused. */
        switch (operation)
        {
        case 0:
            memcpy(live, dead, 1);
            break;
        case 1:
            memmove(live, dead, 1);
            break;
        case 2:
            memset(dead, 0, 1);
            break;
        case 3:
            uassert_int_equal(strlen(dead), 0);
            break;
        case 4:
            uassert_int_equal(strnlen(dead, 1), 0);
            break;
        case 5:
            strcpy(live, dead);
            break;
        case 6:
            strncpy(live, dead, 1);
            break;
        case 7:
            strcat(live, dead);
            break;
        case 8:
            strncat(live, dead, 1);
            break;
        case 9:
            uassert_int_equal(format_string(dead, "a"), -1);
            break;
        case 10:
            uassert_int_equal(call_vsprintf(dead, "a"), -1);
            break;
        case 11:
            uassert_int_equal(format_nstring(dead, 16, "a"), -1);
            break;
        case 12:
            uassert_int_equal(call_vsnprintf(dead, 16, "a"), -1);
            break;
        case 13:
            memcpy(dead, live, 1);
            break;
        case 14:
            memmove(dead, live, 1);
            break;
        case 15:
            strcpy(dead, live);
            break;
        case 16:
            strncpy(dead, live, 1);
            break;
        case 17:
            strcat(dead, live);
            break;
        case 18:
            strncat(dead, live, 1);
            break;
        case 19:
            uassert_int_equal(format_string(live, "%s", dead), -1);
            break;
        case 20:
            uassert_int_equal(call_vsprintf(live, "%s", dead), -1);
            break;
        case 21:
            uassert_int_equal(format_nstring(live, 16, "%s", dead), -1);
            break;
        case 22:
            uassert_int_equal(call_vsnprintf(live, 16, "%s", dead), -1);
            break;
        case 23:
            uassert_int_equal(format_string(live, dead), -1);
            break;
        case 24:
            uassert_int_equal(call_vsprintf(live, dead), -1);
            break;
        case 25:
            uassert_int_equal(format_nstring(live, 16, dead), -1);
            break;
        case 26:
            uassert_int_equal(call_vsnprintf(live, 16, dead), -1);
            break;
        case 27:
            uassert_int_equal(format_string(live, "%n", (int *)dead), -1);
            break;
        case 28:
            uassert_int_equal(call_vsprintf(live, "%n", (int *)dead), -1);
            break;
        case 29:
            uassert_int_equal(format_nstring(live, 16, "%n", (int *)dead), -1);
            break;
        case 30:
            uassert_int_equal(call_vsnprintf(live, 16, "%n", (int *)dead), -1);
            break;
        }
        uassert_true(rt_asan_report_count_get() > before);
        uassert_str_equal(live, "keep");
        before = rt_asan_report_count_get();
        /* All zero-count operations that do not scan a destination stay clean. */
        memcpy(dead, live + 16, 0);
        memcpy(live + 16, dead, 0);
        memmove(dead, dead, 0);
        memset(dead, 0, 0);
        strncpy(dead, live + 16, 0);
        strncpy(live + 16, dead, 0);
        uassert_int_equal(strnlen(dead, 0), 0);
        uassert_int_equal(format_nstring(dead, 0, ""), 0);
        strncat(live, dead, 0);
        uassert_str_equal(live, "keep");
        uassert_int_equal(format_nstring(live, 16, "%.0s", dead), 0);
        uassert_str_equal(live, "");
        uassert_int_equal(rt_asan_report_count_get(), before);
        rt_free(live);
    }
#else
    rt_kprintf("[asan-libc] all-entry UAF checks unavailable for this heap algorithm\n");
#endif
}

static void compare_libc_format(char *dst, size_t size, const char *fmt, ...)
{
    char expected[64] = { 0 };
    int real_result, wrapped_result;
    va_list args, copy;
    va_start(args, fmt);
    va_copy(copy, args);
    real_result = __real_vsnprintf(expected, sizeof(expected), fmt, copy);
    va_end(copy);
    wrapped_result = vsnprintf(dst, size, fmt, args);
    va_end(args);
    uassert_int_equal(wrapped_result, real_result);
    if (real_result >= 0)
    {
        uassert_str_equal(dst, expected);
    }
}

static int real_format_limit(char *dst, size_t size, const char *fmt, ...)
{
    int result;
    va_list args;
    va_start(args, fmt);
    result = __real_vsnprintf(dst, size, fmt, args);
    va_end(args);
    return result;
}

static void test_libc_format_arguments(void)
{
    char *src = rt_malloc(10);
    char *dst = rt_malloc(64);
    int count = 0;
    int real_result, real_errno, wrapped_result;
    char expected[64] = { 0 };
    rt_uint32_t before;

    uassert_not_null(src);
    uassert_not_null(dst);
    if (!src || !dst)
    {
        rt_free(src);
        rt_free(dst);
        return;
    }
    prepare_source(src);
    before = rt_asan_report_count_get();
    snprintf(dst, 64, "%*.*s", 5, 3, src + 7);
    uassert_str_equal(dst, "  aaa");
    src[9] = '\0';
    snprintf(dst, 64, "%.*s", -1, src);
    uassert_str_equal(dst, "aaaaaaaaa");
    compare_libc_format(dst, 64, "%ld/%lu/%lld/%s", 12L, 34UL, 56LL, src);
    compare_libc_format(dst, 64, "%.2f/%s", 1.25, src);
    compare_libc_format(dst, 64, "%+ld/%#lx/%.0d/%-8s", LONG_MIN, ULONG_MAX, 0, src);
    compare_libc_format(dst, 64, "%p", (void *)(src + 10));
    /* Unsupported formats retain this SDK's actual behavior. */
    compare_libc_format(dst, 64, "%zu", (size_t)123);
    compare_libc_format(dst, 64, "%ls", L"abc");
    compare_libc_format(dst, 64, "%2$s/%1$d", 7, src);

    uassert_int_equal(sprintf(dst, "abcd%n", &count), 4);
    uassert_str_equal(dst, "abcd");
    uassert_int_equal(count, 4);
    /* Preserve the SDK's parameter rejection, including errno. */
    errno = 0;
    real_result = real_format_limit(expected, (size_t)INT_MAX + 1, "abc");
    real_errno = errno;
    errno = 0;
    wrapped_result = snprintf(dst, (size_t)INT_MAX + 1, "abc");
    uassert_int_equal(wrapped_result, real_result);
    uassert_int_equal(errno, real_errno);
    uassert_int_equal(rt_asan_report_count_get(), before);

    prepare_source(src);
    snprintf(dst, 64, "%ld/%lu/%.2f/%*.*s", 12L, 34UL, 1.25, 5, 11, src);
    uassert_true(rt_asan_report_count_get() > before);
    before = rt_asan_report_count_get();
    snprintf(dst, 64, "a%ln", (long *)(src + 8));
    uassert_true(rt_asan_report_count_get() > before);
    before = rt_asan_report_count_get();
    uassert_int_equal(sprintf(src, "%s", "1234567890"), 10);
    uassert_true(rt_asan_report_count_get() > before);
    uassert_str_equal(src, "123456789");
    rt_free(src);
    rt_free(dst);
}

static void test_libc_shadow_bounds(void)
{
    char *p = rt_malloc(16);
    static char outside[16];
    rt_size_t available;
    rt_uint32_t before = rt_asan_report_count_get();
    uassert_not_null(p);
    if (!p)
    {
        return;
    }
    uassert_true(rt_asan_accessible_size(p, &available));
    uassert_int_equal(available, 16);
    uassert_true(rt_asan_accessible_size(p + 4, &available));
    uassert_int_equal(available, 12);
    uassert_true(rt_asan_accessible_size(p + 16, &available));
    uassert_int_equal(available, 0);
    uassert_false(rt_asan_accessible_size(outside, &available));
    rt_free(p);

    /* Ending coverage is not evidence of an allocation's end. */
    p = rt_malloc((rt_size_t)RT_ASAN_SHADOW_SIZE * 8 + 64);
    if (p)
    {
        uassert_false(rt_asan_accessible_size(p, &available));
        uassert_int_equal(sprintf(p, "%s", "abc"), 3);
        uassert_str_equal(p, "abc");
        rt_free(p);
    }
    else
    {
        rt_kprintf("[asan-libc] coverage-end allocation skipped: insufficient heap\n");
    }
    uassert_int_equal(rt_asan_report_count_get(), before);
}
#endif

static void testcase(void)
{
    rt_size_t failures;
    libc_path = RT_FALSE;
    UTEST_UNIT_RUN(test_library_boundaries);
    failures = utest_handle_get()->failed_num;
#ifdef RT_ASAN_USING_LIBC
    libc_path = RT_TRUE;
    copy_string = strcpy;
    copy_nstring = strncpy;
    string_length = strlen;
    bounded_length = strnlen;
    format_string = sprintf;
    format_nstring = snprintf;
    format_va = vsprintf;
    format_nva = vsnprintf;
    copy_memory = memcpy;
    move_memory = memmove;
    set_memory = memset;
    UTEST_UNIT_RUN(test_library_boundaries);
    failures += utest_handle_get()->failed_num;
    UTEST_UNIT_RUN(test_libc_memory_sizes);
    failures += utest_handle_get()->failed_num;
    UTEST_UNIT_RUN(test_libc_extreme_counts);
    failures += utest_handle_get()->failed_num;
    UTEST_UNIT_RUN(test_libc_string_sizes);
    failures += utest_handle_get()->failed_num;
    UTEST_UNIT_RUN(test_libc_append);
    failures += utest_handle_get()->failed_num;
    UTEST_UNIT_RUN(test_libc_append_boundaries);
    failures += utest_handle_get()->failed_num;
    UTEST_UNIT_RUN(test_libc_format_boundaries);
    failures += utest_handle_get()->failed_num;
    UTEST_UNIT_RUN(test_libc_writeback_sizes);
    failures += utest_handle_get()->failed_num;
    UTEST_UNIT_RUN(test_libc_all_uaf_entries);
    failures += utest_handle_get()->failed_num;
    UTEST_UNIT_RUN(test_libc_format_arguments);
    failures += utest_handle_get()->failed_num;
    UTEST_UNIT_RUN(test_libc_shadow_bounds);
    failures += utest_handle_get()->failed_num;
#ifdef RT_USING_CPLUSPLUS
    UTEST_UNIT_RUN(test_asan_libc_cpp);
    failures += utest_handle_get()->failed_num;
#endif
    copy_string = rt_strcpy;
    copy_nstring = rt_strncpy;
    string_length = rt_strlen;
    bounded_length = rt_strnlen;
    format_string = rt_sprintf;
    format_nstring = rt_snprintf;
    format_va = rt_vsprintf;
    format_nva = rt_vsnprintf;
    copy_memory = rt_memcpy;
    move_memory = rt_memmove;
    set_memory = rt_memset;
    libc_path = RT_FALSE;
#endif
    uassert_int_equal(failures, 0);
}

UTEST_TC_EXPORT(testcase, "components.asan_libc", RT_NULL, RT_NULL, 1000);
