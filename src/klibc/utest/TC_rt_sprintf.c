/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-22     Meco Man     the first version
 */

/**
 * @author (c) Eyal Rozenberg <eyalroz1@gmx.com>
 *             2021-2022, Haifa, Palestine/Israel
 * @author (c) Marco Paland (info@paland.com)
 *             2014-2019, PALANDesign Hannover, Germany
 *
 * @note Others have made smaller contributions to this file: see the
 * contributors page at https://github.com/eyalroz/printf/graphs/contributors
 * or ask one of the authors. The original code for exponential specifiers was
 * contributed by Martijn Jasperse <m.jasperse@gmail.com>.
 *
 * @brief Small stand-alone implementation of the printf family of functions
 * (`(v)printf`, `(v)s(n)printf` etc., geared towards use on embedded systems with
 * a very limited resources.
 *
 * @note the implementations are thread-safe; re-entrant; use no functions from
 * the standard library; and do not dynamically allocate any memory.
 *
 * @license The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
Unported test cases:
buffer_length
extremal_signed_integer_values
extremal_unsigned_integer_values
*/

#include <rtklibc.h>
#include <utest.h>
#include <math.h>

#define base_buffer_size 100

#define SPRINTF_CHECK(expected, buffer, format, ...)  \
do {                                                  \
    rt_memset(buffer, 0xCC, base_buffer_size);        \
    rt_sprintf(buffer, format, ##__VA_ARGS__);        \
    uassert_str_equal(expected, buffer);              \
} while (0)

#define SPRINTF_TEST_CASE_NAME(testname) TC_##testname
#define SPRINTF_TEST_CASE(testname) static void SPRINTF_TEST_CASE_NAME(testname)(void)

SPRINTF_TEST_CASE(space_flag)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK(" 42",                     buffer, "% d", 42);
    SPRINTF_CHECK("-42",                     buffer, "% d", -42);
    SPRINTF_CHECK("   42",                   buffer, "% 5d", 42);
    SPRINTF_CHECK("  -42",                   buffer, "% 5d", -42);
    SPRINTF_CHECK("             42",         buffer, "% 15d", 42);
    SPRINTF_CHECK("            -42",         buffer, "% 15d", -42);
    SPRINTF_CHECK("            -42",         buffer, "% 15d", -42);
#ifdef RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS
    SPRINTF_CHECK("        -42.987",         buffer, "% 15.3f", -42.987);
    SPRINTF_CHECK("         42.987",         buffer, "% 15.3f", 42.987);
#endif
    SPRINTF_CHECK(" 1024",                   buffer, "% d", 1024);
    SPRINTF_CHECK("-1024",                   buffer, "% d", -1024);
    SPRINTF_CHECK(" 1024",                   buffer, "% i", 1024);
    SPRINTF_CHECK("-1024",                   buffer, "% i", -1024);
}

SPRINTF_TEST_CASE(space_flag__non_standard_format)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("Hello testing",           buffer, "% s", "Hello testing");
    SPRINTF_CHECK("1024",                    buffer, "% u", 1024);
#ifdef RT_KLIBC_USING_VSNPRINTF_MSVC_STYLE_INTEGER_SPECIFIERS
    SPRINTF_CHECK("1024",                    buffer, "% I16u", (uint16_t) 1024);
    SPRINTF_CHECK("1024",                    buffer, "% I32u", (uint32_t) 1024);
    SPRINTF_CHECK("1024",                    buffer, "% I64u", (uint64_t) 1024);
#endif
    SPRINTF_CHECK("4294966272",              buffer, "% u", 4294966272U);
#ifdef RT_KLIBC_USING_VSNPRINTF_MSVC_STYLE_INTEGER_SPECIFIERS
    SPRINTF_CHECK("4294966272",              buffer, "% I32u", (uint32_t) 4294966272U);
    SPRINTF_CHECK("4294966272",              buffer, "% I64u", (uint64_t) 4294966272U);
#endif
    SPRINTF_CHECK("777",                     buffer, "% o", 511);
    SPRINTF_CHECK("37777777001",             buffer, "% o", 4294966785U);
    SPRINTF_CHECK("1234abcd",                buffer, "% x", 305441741);
    SPRINTF_CHECK("edcb5433",                buffer, "% x", 3989525555U);
    SPRINTF_CHECK("1234ABCD",                buffer, "% X", 305441741);
    SPRINTF_CHECK("EDCB5433",                buffer, "% X", 3989525555U);
    SPRINTF_CHECK("x",                       buffer, "% c", 'x');
}

SPRINTF_TEST_CASE(plus_flag)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("+42",                     buffer, "%+d", 42);
    SPRINTF_CHECK("-42",                     buffer, "%+d", -42);
    SPRINTF_CHECK("  +42",                   buffer, "%+5d", 42);
    SPRINTF_CHECK("  -42",                   buffer, "%+5d", -42);
    SPRINTF_CHECK("            +42",         buffer, "%+15d", 42);
    SPRINTF_CHECK("            -42",         buffer, "%+15d", -42);
    SPRINTF_CHECK("+1024",                   buffer, "%+d", 1024);
    SPRINTF_CHECK("-1024",                   buffer, "%+d", -1024);
    SPRINTF_CHECK("+1024",                   buffer, "%+i", 1024);
    SPRINTF_CHECK("-1024",                   buffer, "%+i", -1024);
#ifdef RT_KLIBC_USING_VSNPRINTF_MSVC_STYLE_INTEGER_SPECIFIERS
    SPRINTF_CHECK("+1024",                   buffer, "%+I16d", (int16_t) 1024);
    SPRINTF_CHECK("-1024",                   buffer, "%+I16d", (int16_t) -1024);
    SPRINTF_CHECK("+1024",                   buffer, "%+I32d", (int32_t) 1024);
    SPRINTF_CHECK("-1024",                   buffer, "%+I32d", (int32_t) -1024);
    SPRINTF_CHECK("+1024",                   buffer, "%+I64d", (int64_t) 1024);
    SPRINTF_CHECK("-1024",                   buffer, "%+I64d", (int64_t) -1024);
#endif
    SPRINTF_CHECK("+",                       buffer, "%+.0d", 0);
}

SPRINTF_TEST_CASE(plus_flag__non_standard_format)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("Hello testing",           buffer, "%+s", "Hello testing");
    SPRINTF_CHECK("1024",                    buffer, "%+u", 1024);
#ifdef RT_KLIBC_USING_VSNPRINTF_MSVC_STYLE_INTEGER_SPECIFIERS
    SPRINTF_CHECK("1024",                    buffer, "%+I32u", (uint32_t) 1024);
#endif
    SPRINTF_CHECK("4294966272",              buffer, "%+u", 4294966272U);
#ifdef RT_KLIBC_USING_VSNPRINTF_MSVC_STYLE_INTEGER_SPECIFIERS
    SPRINTF_CHECK("4294966272",              buffer, "%+I32u", (uint32_t) 4294966272U);
#endif
    SPRINTF_CHECK("777",                     buffer, "%+o", 511);
    SPRINTF_CHECK("37777777001",             buffer, "%+o", 4294966785U);
    SPRINTF_CHECK("1234abcd",                buffer, "%+x", 305441741);
    SPRINTF_CHECK("edcb5433",                buffer, "%+x", 3989525555U);
    SPRINTF_CHECK("1234ABCD",                buffer, "%+X", 305441741);
    SPRINTF_CHECK("EDCB5433",                buffer, "%+X", 3989525555U);
    SPRINTF_CHECK("x",                       buffer, "%+c", 'x');
}

SPRINTF_TEST_CASE(zero_flag)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("42",                      buffer, "%0d", 42);
    SPRINTF_CHECK("42",                      buffer, "%0ld", 42L);
    SPRINTF_CHECK("-42",                     buffer, "%0d", -42);
    SPRINTF_CHECK("00042",                   buffer, "%05d", 42);
    SPRINTF_CHECK("-0042",                   buffer, "%05d", -42);
    SPRINTF_CHECK("000000000000042",         buffer, "%015d", 42);
    SPRINTF_CHECK("-00000000000042",         buffer, "%015d", -42);
#ifdef RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS
    SPRINTF_CHECK("000000000042.12",         buffer, "%015.2f", 42.1234);
    SPRINTF_CHECK("00000000042.988",         buffer, "%015.3f", 42.9876);
    SPRINTF_CHECK("-00000042.98760",         buffer, "%015.5f", -42.9876);
#endif
}

SPRINTF_TEST_CASE(minus_flag)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("42",                      buffer, "%-d", 42);
    SPRINTF_CHECK("-42",                     buffer, "%-d", -42);
    SPRINTF_CHECK("42   ",                   buffer, "%-5d", 42);
    SPRINTF_CHECK("-42  ",                   buffer, "%-5d", -42);
    SPRINTF_CHECK("42             ",         buffer, "%-15d", 42);
    SPRINTF_CHECK("-42            ",         buffer, "%-15d", -42);
}

SPRINTF_TEST_CASE(minus_flag_and_non_standard_zero_modifier_for_integers)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("42",                      buffer, "%-0d", 42);
    SPRINTF_CHECK("-42",                     buffer, "%-0d", -42);
    SPRINTF_CHECK("42   ",                   buffer, "%-05d", 42);
    SPRINTF_CHECK("-42  ",                   buffer, "%-05d", -42);
    SPRINTF_CHECK("42             ",         buffer, "%-015d", 42);
    SPRINTF_CHECK("-42            ",         buffer, "%-015d", -42);
    SPRINTF_CHECK("42",                      buffer, "%0-d", 42);
    SPRINTF_CHECK("-42",                     buffer, "%0-d", -42);
    SPRINTF_CHECK("42   ",                   buffer, "%0-5d", 42);
    SPRINTF_CHECK("-42  ",                   buffer, "%0-5d", -42);
    SPRINTF_CHECK("42             ",         buffer, "%0-15d", 42);
    SPRINTF_CHECK("-42            ",         buffer, "%0-15d", -42);

#ifdef RT_KLIBC_USING_VSNPRINTF_STANDARD
#ifdef RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS
    SPRINTF_CHECK("-4.200e+01     ",         buffer, "%0-15.3e", -42.);
    SPRINTF_CHECK("-42            ",         buffer, "%0-15.3g", -42.);
#else
    SPRINTF_CHECK("e",                       buffer, "%0-15.3e", -42.);
    SPRINTF_CHECK("g",                       buffer,  "%0-15.3g", -42.);
#endif /* RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS */
#endif /* RT_KLIBC_USING_VSNPRINTF_STANDARD */
}

SPRINTF_TEST_CASE(sharp_flag)
{
    char buffer[base_buffer_size];
#ifdef RT_KLIBC_USING_VSNPRINTF_STANDARD
    SPRINTF_CHECK("0",                       buffer, "%#o",   0);
    SPRINTF_CHECK("0",                       buffer, "%#0o",  0);
#endif
    SPRINTF_CHECK("0",                       buffer, "%#.0o", 0);
#ifdef RT_KLIBC_USING_VSNPRINTF_STANDARD
    SPRINTF_CHECK("0",                       buffer, "%#.1o", 0);
    SPRINTF_CHECK("   0",                    buffer, "%#4o",  0);
    SPRINTF_CHECK("0000",                    buffer, "%#.4o", 0);
#endif
    SPRINTF_CHECK("01",                      buffer, "%#o",   1);
    SPRINTF_CHECK("01",                      buffer, "%#0o",  1);
#ifdef RT_KLIBC_USING_VSNPRINTF_STANDARD
    SPRINTF_CHECK("01",                      buffer, "%#.0o", 1);
#endif
    SPRINTF_CHECK("01",                      buffer, "%#.1o", 1);
    SPRINTF_CHECK("  01",                    buffer, "%#4o",  1);
#ifdef RT_KLIBC_USING_VSNPRINTF_STANDARD
    SPRINTF_CHECK("0001",                    buffer, "%#.4o", 1);
#endif
    SPRINTF_CHECK("0x1001",                  buffer, "%#04x", 0x1001);
    SPRINTF_CHECK("01001",                   buffer, "%#04o", 01001);
#ifdef RT_KLIBC_USING_VSNPRINTF_STANDARD
    SPRINTF_CHECK("",                        buffer, "%#.0x", 0);
#endif
    SPRINTF_CHECK("0x0000614e",              buffer, "%#.8x", 0x614e);
}

SPRINTF_TEST_CASE(sharp_flag__non_standard_format)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("0b110",                   buffer, "%#b",    6);
    SPRINTF_CHECK("0b11111111",              buffer, "%#010b", 0xff);
    SPRINTF_CHECK("0b011111111",             buffer, "%#011b", 0xff);
    SPRINTF_CHECK("077",                     buffer, "%#03o",  077);
    SPRINTF_CHECK("0077",                    buffer, "%#04o",  077);
}

#ifdef RT_KLIBC_USING_VSNPRINTF_LONGLONG
SPRINTF_TEST_CASE(sharp_flag_with_long_long)
{
    char buffer[base_buffer_size];
#ifdef RT_KLIBC_USING_VSNPRINTF_STANDARD
    SPRINTF_CHECK("0",                       buffer, "%#llo",   (long long) 0);
    SPRINTF_CHECK("0",                       buffer, "%#0llo",  (long long) 0);
#endif /* RT_KLIBC_USING_VSNPRINTF_STANDARD */
    SPRINTF_CHECK("0",                       buffer, "%#.0llo", (long long) 0);
#ifdef RT_KLIBC_USING_VSNPRINTF_STANDARD
    SPRINTF_CHECK("0",                       buffer, "%#.1llo", (long long) 0);
    SPRINTF_CHECK("   0",                    buffer, "%#4llo",  (long long) 0);
    SPRINTF_CHECK("0000",                    buffer, "%#.4llo", (long long) 0);
#endif /* RT_KLIBC_USING_VSNPRINTF_STANDARD */
    SPRINTF_CHECK("01",                      buffer, "%#llo",   (long long) 1);
    SPRINTF_CHECK("01",                      buffer, "%#0llo",  (long long) 1);
#ifdef RT_KLIBC_USING_VSNPRINTF_STANDARD
    SPRINTF_CHECK("01",                      buffer, "%#.0llo", (long long) 1);
#endif /* RT_KLIBC_USING_VSNPRINTF_STANDARD */
    SPRINTF_CHECK("01",                      buffer, "%#.1llo", (long long) 1);
    SPRINTF_CHECK("  01",                    buffer, "%#4llo",  (long long) 1);
#ifdef RT_KLIBC_USING_VSNPRINTF_STANDARD
    SPRINTF_CHECK("0001",                    buffer, "%#.4llo", (long long) 1);
#endif /* RT_KLIBC_USING_VSNPRINTF_STANDARD */
    SPRINTF_CHECK("0x1001",                  buffer, "%#04llx", (long long) 0x1001);
    SPRINTF_CHECK("01001",                   buffer, "%#04llo", (long long) 01001);
#ifdef RT_KLIBC_USING_VSNPRINTF_STANDARD
    SPRINTF_CHECK("",                        buffer, "%#.0llx", (long long) 0);
#endif /* RT_KLIBC_USING_VSNPRINTF_STANDARD */
    SPRINTF_CHECK("0x0000614e",              buffer, "%#.8llx", (long long) 0x614e);
}

SPRINTF_TEST_CASE(sharp_flag_with_long_long__non_standard_format)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("0b110",                   buffer, "%#llb", (long long) 6);
}
#endif /* RT_KLIBC_USING_VSNPRINTF_LONGLONG */

SPRINTF_TEST_CASE(specifier)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("Hello testing",           buffer, "Hello testing");
    SPRINTF_CHECK("Hello testing",           buffer, "%s", "Hello testing");
    SPRINTF_CHECK("(null)",                  buffer, "%s", (const char *) RT_NULL);
    SPRINTF_CHECK("1024",                    buffer, "%d", 1024);
#if INT_MAX >= 2147483647LL
    SPRINTF_CHECK("2147483647",              buffer, "%d", 2147483647);
    SPRINTF_CHECK("4294966272",              buffer, "%u", 4294966272U);
    SPRINTF_CHECK("37777777001",             buffer, "%o", 4294966785U);
    SPRINTF_CHECK("1234abcd",                buffer, "%x", 305441741);
    SPRINTF_CHECK("edcb5433",                buffer, "%x", 3989525555U);
    SPRINTF_CHECK("1234ABCD",                buffer, "%X", 305441741);
    SPRINTF_CHECK("EDCB5433",                buffer, "%X", 3989525555U);
#endif
    SPRINTF_CHECK("-1024",                   buffer, "%d", -1024);
    SPRINTF_CHECK("1024",                    buffer, "%i", 1024);
    SPRINTF_CHECK("-1024",                   buffer, "%i", -1024);
    SPRINTF_CHECK("1024",                    buffer, "%u", 1024);
    SPRINTF_CHECK("777",                     buffer, "%o", 511);
    SPRINTF_CHECK("%",                       buffer, "%%");

#ifdef RT_KLIBC_USING_VSNPRINTF_MSVC_STYLE_INTEGER_SPECIFIERS
    SPRINTF_CHECK("127",                     buffer, "%I8d", (int8_t) 127LL);
#if (SHRT_MAX >= 32767)
    SPRINTF_CHECK("32767",                   buffer, "%I16d", (int16_t) 32767LL);
#endif
#if (LLONG_MAX >= 2147483647)
    SPRINTF_CHECK("2147483647",              buffer, "%I32d", (int32_t) 2147483647LL);
#if (LLONG_MAX >= 9223372036854775807LL)
    SPRINTF_CHECK("9223372036854775807",     buffer, "%I64d", (int64_t) 9223372036854775807LL);
#endif
#endif
#endif /* RT_KLIBC_USING_VSNPRINTF_MSVC_STYLE_INTEGER_SPECIFIERS */
}

SPRINTF_TEST_CASE(width)
{
    char buffer[base_buffer_size];
#ifdef RT_KLIBC_USING_VSNPRINTF_STANDARD
    SPRINTF_CHECK("Hello testing",           buffer, "%1s", "Hello testing");
#endif /* RT_KLIBC_USING_VSNPRINTF_STANDARD */
    SPRINTF_CHECK("1024",                    buffer, "%1d", 1024);
    SPRINTF_CHECK("-1024",                   buffer, "%1d", -1024);
    SPRINTF_CHECK("1024",                    buffer, "%1i", 1024);
    SPRINTF_CHECK("-1024",                   buffer, "%1i", -1024);
    SPRINTF_CHECK("1024",                    buffer, "%1u", 1024);
#ifdef RT_KLIBC_USING_VSNPRINTF_MSVC_STYLE_INTEGER_SPECIFIERS
    SPRINTF_CHECK("1024",                    buffer, "%1I16u", (uint16_t) 1024);
    SPRINTF_CHECK("1024",                    buffer, "%1I32u", (uint32_t) 1024);
    SPRINTF_CHECK("1024",                    buffer, "%1I64u", (uint64_t) 1024);
#endif /* RT_KLIBC_USING_VSNPRINTF_MSVC_STYLE_INTEGER_SPECIFIERS */
    SPRINTF_CHECK("4294966272",              buffer, "%1u", 4294966272U);
#ifdef RT_KLIBC_USING_VSNPRINTF_MSVC_STYLE_INTEGER_SPECIFIERS
    SPRINTF_CHECK("4294966272",              buffer, "%1I32u", (uint32_t) 4294966272U);
    SPRINTF_CHECK("4294966272",              buffer, "%1I64u", (uint64_t) 4294966272U);
#endif /* RT_KLIBC_USING_VSNPRINTF_MSVC_STYLE_INTEGER_SPECIFIERS */
    SPRINTF_CHECK("777",                     buffer, "%1o", 511);
    SPRINTF_CHECK("37777777001",             buffer, "%1o", 4294966785U);
    SPRINTF_CHECK("1234abcd",                buffer, "%1x", 305441741);
    SPRINTF_CHECK("edcb5433",                buffer, "%1x", 3989525555U);
    SPRINTF_CHECK("1234ABCD",                buffer, "%1X", 305441741);
    SPRINTF_CHECK("EDCB5433",                buffer, "%1X", 3989525555U);
    SPRINTF_CHECK("x",                       buffer, "%1c", 'x');
}

SPRINTF_TEST_CASE(width_20)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("               Hello",    buffer, "%20s", "Hello");
    SPRINTF_CHECK("                1024",    buffer, "%20d", 1024);
    SPRINTF_CHECK("               -1024",    buffer, "%20d", -1024);
    SPRINTF_CHECK("                1024",    buffer, "%20i", 1024);
    SPRINTF_CHECK("               -1024",    buffer, "%20i", -1024);
    SPRINTF_CHECK("                   0",    buffer, "%20i", 0);
    SPRINTF_CHECK("                1024",    buffer, "%20u", 1024);
#ifdef RT_KLIBC_USING_VSNPRINTF_MSVC_STYLE_INTEGER_SPECIFIERS
    SPRINTF_CHECK("                1024",    buffer, "%20I16u", (uint16_t) 1024);
    SPRINTF_CHECK("                1024",    buffer, "%20I32u", (uint32_t) 1024);
    SPRINTF_CHECK("                1024",    buffer, "%20I64u", (uint64_t) 1024);
#endif /* RT_KLIBC_USING_VSNPRINTF_MSVC_STYLE_INTEGER_SPECIFIERS */
    SPRINTF_CHECK("          4294966272",    buffer, "%20u", 4294966272U);
#ifdef RT_KLIBC_USING_VSNPRINTF_MSVC_STYLE_INTEGER_SPECIFIERS
    SPRINTF_CHECK("          4294966272",    buffer, "%20I32u", (uint32_t) 4294966272U);
    SPRINTF_CHECK("          4294966272",    buffer, "%20I64u", (uint64_t) 4294966272U);
#endif /* RT_KLIBC_USING_VSNPRINTF_MSVC_STYLE_INTEGER_SPECIFIERS */
    SPRINTF_CHECK("                 777",    buffer, "%20o", 511);
    SPRINTF_CHECK("         37777777001",    buffer, "%20o", 4294966785U);
    SPRINTF_CHECK("            1234abcd",    buffer, "%20x", 305441741);
    SPRINTF_CHECK("            edcb5433",    buffer, "%20x", 3989525555U);
    SPRINTF_CHECK("            1234ABCD",    buffer, "%20X", 305441741);
    SPRINTF_CHECK("            EDCB5433",    buffer, "%20X", 3989525555U);
    SPRINTF_CHECK("                   0",    buffer, "%20X", 0);
    SPRINTF_CHECK("                   0",    buffer, "%20X", 0U);
#ifdef RT_KLIBC_USING_VSNPRINTF_LONGLONG
    SPRINTF_CHECK("                   0",    buffer, "%20llX", 0ULL);
#endif /* RT_KLIBC_USING_VSNPRINTF_LONGLONG */
    SPRINTF_CHECK("                   x",    buffer, "%20c", 'x');
}

SPRINTF_TEST_CASE(width_asterisk_20)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("               Hello",    buffer, "%*s", 20, "Hello");
    SPRINTF_CHECK("                1024",    buffer, "%*d", 20, 1024);
    SPRINTF_CHECK("               -1024",    buffer, "%*d", 20, -1024);
    SPRINTF_CHECK("                1024",    buffer, "%*i", 20, 1024);
    SPRINTF_CHECK("               -1024",    buffer, "%*i", 20, -1024);
    SPRINTF_CHECK("                1024",    buffer, "%*u", 20, 1024);
#ifdef RT_KLIBC_USING_VSNPRINTF_MSVC_STYLE_INTEGER_SPECIFIERS
    SPRINTF_CHECK("                1024",    buffer, "%*I16u", 20, (uint16_t) 1024);
    SPRINTF_CHECK("                1024",    buffer, "%*I32u", 20, (uint32_t) 1024);
    SPRINTF_CHECK("                1024",    buffer, "%*I64u", 20, (uint64_t) 1024);
#endif /* RT_KLIBC_USING_VSNPRINTF_MSVC_STYLE_INTEGER_SPECIFIERS */
    SPRINTF_CHECK("          4294966272",    buffer, "%*u", 20, 4294966272U);
#ifdef RT_KLIBC_USING_VSNPRINTF_MSVC_STYLE_INTEGER_SPECIFIERS
    SPRINTF_CHECK("          4294966272",    buffer, "%*I32u", 20, (uint32_t) 4294966272U);
    SPRINTF_CHECK("          4294966272",    buffer, "%*I64u", 20, (uint64_t) 4294966272U);
#endif /* RT_KLIBC_USING_VSNPRINTF_MSVC_STYLE_INTEGER_SPECIFIERS */
    SPRINTF_CHECK("                 777",    buffer, "%*o", 20, 511);
    SPRINTF_CHECK("         37777777001",    buffer, "%*o", 20, 4294966785U);
    SPRINTF_CHECK("            1234abcd",    buffer, "%*x", 20, 305441741);
    SPRINTF_CHECK("            edcb5433",    buffer, "%*x", 20, 3989525555U);
    SPRINTF_CHECK("            1234ABCD",    buffer, "%*X", 20, 305441741);
    SPRINTF_CHECK("            EDCB5433",    buffer, "%*X", 20, 3989525555U);
    SPRINTF_CHECK("                   x",    buffer, "%*c", 20, 'x');
}

SPRINTF_TEST_CASE(width_minus_20)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("Hello               ",    buffer, "%-20s", "Hello");
    SPRINTF_CHECK("1024                ",    buffer, "%-20d", 1024);
    SPRINTF_CHECK("-1024               ",    buffer, "%-20d", -1024);
    SPRINTF_CHECK("1024                ",    buffer, "%-20i", 1024);
    SPRINTF_CHECK("-1024               ",    buffer, "%-20i", -1024);
    SPRINTF_CHECK("1024                ",    buffer, "%-20u", 1024);
#ifdef RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS
    SPRINTF_CHECK("1024.1234           ",    buffer, "%-20.4f", 1024.1234);
#endif /* RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS */
    SPRINTF_CHECK("4294966272          ",    buffer, "%-20u", 4294966272U);
    SPRINTF_CHECK("777                 ",    buffer, "%-20o", 511);
    SPRINTF_CHECK("37777777001         ",    buffer, "%-20o", 4294966785U);
    SPRINTF_CHECK("1234abcd            ",    buffer, "%-20x", 305441741);
    SPRINTF_CHECK("edcb5433            ",    buffer, "%-20x", 3989525555U);
    SPRINTF_CHECK("1234ABCD            ",    buffer, "%-20X", 305441741);
    SPRINTF_CHECK("EDCB5433            ",    buffer, "%-20X", 3989525555U);
    SPRINTF_CHECK("x                   ",    buffer, "%-20c", 'x');
    SPRINTF_CHECK("|    9| |9 | |    9|",    buffer, "|%5d| |%-2d| |%5d|", 9, 9, 9);
    SPRINTF_CHECK("|   10| |10| |   10|",    buffer, "|%5d| |%-2d| |%5d|", 10, 10, 10);
    SPRINTF_CHECK("|    9| |9           | |    9|", buffer, "|%5d| |%-12d| |%5d|", 9, 9, 9);
    SPRINTF_CHECK("|   10| |10          | |   10|", buffer, "|%5d| |%-12d| |%5d|", 10, 10, 10);
}

SPRINTF_TEST_CASE(width_0_minus_20)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("Hello               ",    buffer, "%0-20s", "Hello");
    SPRINTF_CHECK("1024                ",    buffer, "%0-20d", 1024);
    SPRINTF_CHECK("-1024               ",    buffer, "%0-20d", -1024);
    SPRINTF_CHECK("1024                ",    buffer, "%0-20i", 1024);
    SPRINTF_CHECK("-1024               ",    buffer, "%0-20i", -1024);
    SPRINTF_CHECK("1024                ",    buffer, "%0-20u", 1024);
    SPRINTF_CHECK("4294966272          ",    buffer, "%0-20u", 4294966272U);
    SPRINTF_CHECK("777                 ",    buffer, "%0-20o", 511);
    SPRINTF_CHECK("37777777001         ",    buffer, "%0-20o", 4294966785U);
    SPRINTF_CHECK("1234abcd            ",    buffer, "%0-20x", 305441741);
    SPRINTF_CHECK("edcb5433            ",    buffer, "%0-20x", 3989525555U);
    SPRINTF_CHECK("1234ABCD            ",    buffer, "%0-20X", 305441741);
    SPRINTF_CHECK("EDCB5433            ",    buffer, "%0-20X", 3989525555U);
    SPRINTF_CHECK("x                   ",    buffer, "%0-20c", 'x');
}

SPRINTF_TEST_CASE(padding_20)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("00000000000000001024",    buffer, "%020d", 1024);
    SPRINTF_CHECK("-0000000000000001024",    buffer, "%020d", -1024);
    SPRINTF_CHECK("00000000000000001024",    buffer, "%020i", 1024);
    SPRINTF_CHECK("-0000000000000001024",    buffer, "%020i", -1024);
    SPRINTF_CHECK("00000000000000001024",    buffer, "%020u", 1024);
    SPRINTF_CHECK("00000000004294966272",    buffer, "%020u", 4294966272U);
    SPRINTF_CHECK("00000000000000000777",    buffer, "%020o", 511);
    SPRINTF_CHECK("00000000037777777001",    buffer, "%020o", 4294966785U);
    SPRINTF_CHECK("0000000000001234abcd",    buffer, "%020x", 305441741);
    SPRINTF_CHECK("000000000000edcb5433",    buffer, "%020x", 3989525555U);
    SPRINTF_CHECK("0000000000001234ABCD",    buffer, "%020X", 305441741);
    SPRINTF_CHECK("000000000000EDCB5433",    buffer, "%020X", 3989525555U);
}

SPRINTF_TEST_CASE(padding_dot_20)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("00000000000000001024",    buffer, "%.20d", 1024);
    SPRINTF_CHECK("-00000000000000001024",   buffer, "%.20d", -1024);
    SPRINTF_CHECK("00000000000000001024",    buffer, "%.20i", 1024);
    SPRINTF_CHECK("-00000000000000001024",   buffer, "%.20i", -1024);
    SPRINTF_CHECK("00000000000000001024",    buffer, "%.20u", 1024);
    SPRINTF_CHECK("00000000004294966272",    buffer, "%.20u", 4294966272U);
    SPRINTF_CHECK("00000000000000000777",    buffer, "%.20o", 511);
    SPRINTF_CHECK("00000000037777777001",    buffer, "%.20o", 4294966785U);
    SPRINTF_CHECK("0000000000001234abcd",    buffer, "%.20x", 305441741);
    SPRINTF_CHECK("000000000000edcb5433",    buffer, "%.20x", 3989525555U);
    SPRINTF_CHECK("0000000000001234ABCD",    buffer, "%.20X", 305441741);
    SPRINTF_CHECK("000000000000EDCB5433",    buffer, "%.20X", 3989525555U);
}

SPRINTF_TEST_CASE(padding_sharp_020__non_standard_format)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("00000000000000001024",    buffer, "%#020d", 1024);
    SPRINTF_CHECK("-0000000000000001024",    buffer, "%#020d", -1024);
    SPRINTF_CHECK("00000000000000001024",    buffer, "%#020i", 1024);
    SPRINTF_CHECK("-0000000000000001024",    buffer, "%#020i", -1024);
    SPRINTF_CHECK("00000000000000001024",    buffer, "%#020u", 1024);
    SPRINTF_CHECK("00000000004294966272",    buffer, "%#020u", 4294966272U);
}

SPRINTF_TEST_CASE(padding_sharp_020)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("00000000000000000777",    buffer, "%#020o", 511);
    SPRINTF_CHECK("00000000037777777001",    buffer, "%#020o", 4294966785U);
    SPRINTF_CHECK("0x00000000001234abcd",    buffer, "%#020x", 305441741);
    SPRINTF_CHECK("0x0000000000edcb5433",    buffer, "%#020x", 3989525555U);
    SPRINTF_CHECK("0X00000000001234ABCD",    buffer, "%#020X", 305441741);
    SPRINTF_CHECK("0X0000000000EDCB5433",    buffer, "%#020X", 3989525555U);
}

SPRINTF_TEST_CASE(padding_sharp_20__non_standard_format)
{
  char buffer[base_buffer_size];
  SPRINTF_CHECK("                1024",      buffer, "%#20d", 1024);
  SPRINTF_CHECK("               -1024",      buffer, "%#20d", -1024);
  SPRINTF_CHECK("                1024",      buffer, "%#20i", 1024);
  SPRINTF_CHECK("               -1024",      buffer, "%#20i", -1024);
  SPRINTF_CHECK("                1024",      buffer, "%#20u", 1024);
  SPRINTF_CHECK("          4294966272",      buffer, "%#20u", 4294966272U);
}

SPRINTF_TEST_CASE(padding_sharp_20)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("                0777",    buffer, "%#20o", 511);
    SPRINTF_CHECK("        037777777001",    buffer, "%#20o", 4294966785U);
    SPRINTF_CHECK("          0x1234abcd",    buffer, "%#20x", 305441741);
    SPRINTF_CHECK("          0xedcb5433",    buffer, "%#20x", 3989525555U);
    SPRINTF_CHECK("          0X1234ABCD",    buffer, "%#20X", 305441741);
    SPRINTF_CHECK("          0XEDCB5433",    buffer, "%#20X", 3989525555U);
}

SPRINTF_TEST_CASE(padding_20_point_5)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("               01024",    buffer, "%20.5d", 1024);
    SPRINTF_CHECK("              -01024",    buffer, "%20.5d", -1024);
    SPRINTF_CHECK("               01024",    buffer, "%20.5i", 1024);
    SPRINTF_CHECK("              -01024",    buffer, "%20.5i", -1024);
    SPRINTF_CHECK("               01024",    buffer, "%20.5u", 1024);
    SPRINTF_CHECK("          4294966272",    buffer, "%20.5u", 4294966272U);
    SPRINTF_CHECK("               00777",    buffer, "%20.5o", 511);
    SPRINTF_CHECK("         37777777001",    buffer, "%20.5o", 4294966785U);
    SPRINTF_CHECK("            1234abcd",    buffer, "%20.5x", 305441741);
    SPRINTF_CHECK("          00edcb5433",    buffer, "%20.10x", 3989525555U);
    SPRINTF_CHECK("            1234ABCD",    buffer, "%20.5X", 305441741);
    SPRINTF_CHECK("          00EDCB5433",    buffer, "%20.10X", 3989525555U);
}

SPRINTF_TEST_CASE(padding_negative_numbers)
{
    char buffer[base_buffer_size];

    /* space padding */
    SPRINTF_CHECK("-5",                      buffer, "% 1d", -5);
    SPRINTF_CHECK("-5",                      buffer, "% 2d", -5);
    SPRINTF_CHECK(" -5",                     buffer, "% 3d", -5);
    SPRINTF_CHECK("  -5",                    buffer, "% 4d", -5);

    /* zero padding */
    SPRINTF_CHECK("-5",                      buffer, "%01d", -5);
    SPRINTF_CHECK("-5",                      buffer, "%02d", -5);
    SPRINTF_CHECK("-05",                     buffer, "%03d", -5);
    SPRINTF_CHECK("-005",                    buffer, "%04d", -5);
}

#if defined(RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS) || \
    defined(RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS)
SPRINTF_TEST_CASE(float_padding_negative_numbers)
{
    char buffer[base_buffer_size];

    /* space padding */
#ifdef RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS
    SPRINTF_CHECK("-5.0",                    buffer, "% 3.1f", -5.);
    SPRINTF_CHECK("-5.0",                    buffer, "% 4.1f", -5.);
    SPRINTF_CHECK(" -5.0",                   buffer, "% 5.1f", -5.);
#endif

#ifdef RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS
    SPRINTF_CHECK("    -5",                  buffer, "% 6.1g", -5.);
    SPRINTF_CHECK("-5.0e+00",                buffer, "% 6.1e", -5.);
    SPRINTF_CHECK("  -5.0e+00",              buffer, "% 10.1e", -5.);
#endif

    /* zero padding */
#ifdef RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS
    SPRINTF_CHECK("-5.0",                    buffer, "%03.1f", -5.);
    SPRINTF_CHECK("-5.0",                    buffer, "%04.1f", -5.);
    SPRINTF_CHECK("-05.0",                   buffer, "%05.1f", -5.);

    /* zero padding no decimal point */
    SPRINTF_CHECK("-5",                      buffer, "%01.0f", -5.);
    SPRINTF_CHECK("-5",                      buffer, "%02.0f", -5.);
    SPRINTF_CHECK("-05",                     buffer, "%03.0f", -5.);
#endif

#ifdef RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS
    SPRINTF_CHECK("-005.0e+00",              buffer, "%010.1e", -5.);
    SPRINTF_CHECK("-05E+00",                 buffer, "%07.0E", -5.);
    SPRINTF_CHECK("-05",                     buffer, "%03.0g", -5.);
#endif
}

SPRINTF_TEST_CASE(infinity_and_not_a_number_values)
{
    char buffer[base_buffer_size];

    /* test special-case floats using math.h macros */
#ifdef RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS
    SPRINTF_CHECK("     nan",                buffer, "%8f", (double) NAN);
    SPRINTF_CHECK("     inf",                buffer, "%8f", (double) INFINITY);
    SPRINTF_CHECK("-inf    ",                buffer, "%-8f", (double) -INFINITY);
#endif /* RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS */
#ifdef RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS
    SPRINTF_CHECK("     nan",                buffer, "%8e", (double) NAN);
    SPRINTF_CHECK("     inf",                buffer, "%8e", (double) INFINITY);
    SPRINTF_CHECK("-inf    ",                buffer, "%-8e", (double) -INFINITY);
#endif /* RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS */
}

SPRINTF_TEST_CASE(floating_point_specifiers_precision_and_flags)
{
    char buffer[base_buffer_size];
#ifdef RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS
    SPRINTF_CHECK("3.1415",                  buffer, "%.4f", 3.1415354);
    SPRINTF_CHECK("30343.142",               buffer, "%.3f", 30343.1415354);
    SPRINTF_CHECK("34",                      buffer, "%.0f", 34.1415354);
    SPRINTF_CHECK("1",                       buffer, "%.0f", 1.3);
    SPRINTF_CHECK("2",                       buffer, "%.0f", 1.55);
    SPRINTF_CHECK("1.6",                     buffer, "%.1f", 1.64);
    SPRINTF_CHECK("42.90",                   buffer, "%.2f", 42.8952);
    SPRINTF_CHECK("42.895200000",            buffer, "%.9f", 42.8952);
    SPRINTF_CHECK("42.8952230000",           buffer, "%.10f", 42.895223);
    SPRINTF_CHECK("42.895223123457",         buffer, "%.12f", 42.89522312345678);
    SPRINTF_CHECK("42477.371093750000000",   buffer, "%020.15f", 42477.37109375);
    SPRINTF_CHECK("42.895223876543",         buffer, "%.12f", 42.89522387654321);
    SPRINTF_CHECK(" 42.90",                  buffer, "%6.2f", 42.8952);
    SPRINTF_CHECK("+42.90",                  buffer, "%+6.2f", 42.8952);
    SPRINTF_CHECK("+42.9",                   buffer, "%+5.1f", 42.9252);
    SPRINTF_CHECK("42.500000",               buffer, "%f", 42.5);
    SPRINTF_CHECK("42.5",                    buffer, "%.1f", 42.5);
    SPRINTF_CHECK("42167.000000",            buffer, "%f", 42167.0);
    SPRINTF_CHECK("-12345.987654321",        buffer, "%.9f", -12345.987654321);
    SPRINTF_CHECK("4.0",                     buffer, "%.1f", 3.999);
    SPRINTF_CHECK("4",                       buffer, "%.0f", 3.5);
    SPRINTF_CHECK("4",                       buffer, "%.0f", 4.5);
    SPRINTF_CHECK("3",                       buffer, "%.0f", 3.49);
    SPRINTF_CHECK("3.5",                     buffer, "%.1f", 3.49);
    SPRINTF_CHECK("a0.5  ",                  buffer, "a%-5.1f", 0.5);
    SPRINTF_CHECK("a0.5  end",               buffer, "a%-5.1fend", 0.5);

    /* %f for double */
    SPRINTF_CHECK("42.895223123457",         buffer, "%.12f", 42.89522312345678);
    /* %F for double */
    SPRINTF_CHECK("42.895223123457",         buffer, "%.12F", 42.89522312345678);
    /* %lf for double */
    SPRINTF_CHECK("42.895223123457",         buffer, "%.12lf", 42.89522312345678);
    /* %Lf for long double */
    // TODO: fix me
    // SPRINTF_CHECK("42.895223123457",         buffer, "%.12Lf", 42.89522312345678l);
    // SPRINTF_CHECK("42.895223123457",         buffer, "%.12Lf", 42.89522312345678L);
#endif /* RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS */

#ifdef RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS
    SPRINTF_CHECK("0.5",                     buffer, "%.4g", 0.5);
    SPRINTF_CHECK("1",                       buffer, "%.4g", 1.0);
    SPRINTF_CHECK("12345.7",                 buffer, "%G", 12345.678);
    SPRINTF_CHECK("12345.68",                buffer, "%.7G", 12345.678);
    SPRINTF_CHECK("1.2346E+08",              buffer, "%.5G", 123456789.);
    SPRINTF_CHECK("12345",                   buffer, "%.6G", 12345.);
    SPRINTF_CHECK("  +1.235e+08",            buffer, "%+12.4g", 123456789.);
    SPRINTF_CHECK("0.0012",                  buffer, "%.2G", 0.001234);
    SPRINTF_CHECK(" +0.001234",              buffer, "%+10.4G", 0.001234);
    SPRINTF_CHECK("+001.234e-05",            buffer, "%+012.4g", 0.00001234);
    /* Note: The following two values are _barely_ normal;
    make their mantissa 1.1 and they lose their normality. */
    SPRINTF_CHECK("-1.23e-308",              buffer, "%.3g", -1.2345e-308);
    SPRINTF_CHECK("+1.230E+308",             buffer, "%+.3E", 1.23e+308);
    SPRINTF_CHECK("1.000e+01",               buffer, "%.3e", 9.9996);
    SPRINTF_CHECK("0",                       buffer, "%g", 0.);
    SPRINTF_CHECK("-0",                      buffer, "%g", -0.);
    SPRINTF_CHECK("+0",                      buffer, "%+g", 0.);
    SPRINTF_CHECK("-0",                      buffer, "%+g", -0.);
    SPRINTF_CHECK("-4e+04",                  buffer, "%.1g", -40661.5);
    SPRINTF_CHECK("-4.e+04",                 buffer, "%#.1g", -40661.5);
    SPRINTF_CHECK("100.",                    buffer, "%#.3g", 99.998580932617187500);
    // TODO: fix me
    // SPRINTF_CHECK("1.e01",                   buffer, "%# 01.1g", 9.8);
    /* Note: The following value is _barely_ normal;
    make the mantissa 1.1 and it loses its normality. */
    SPRINTF_CHECK("1.2345678901e-308",       buffer, "%.10e", 1.2345678901e-308);
    /* Rounding-focused checks */
    SPRINTF_CHECK("4.895512e+04",            buffer, "%e", 48955.125);
    SPRINTF_CHECK("9.2524e+04",              buffer, "%.4e", 92523.5);
    SPRINTF_CHECK("-8.380923438e+04",        buffer, "%.9e", -83809.234375);

    /* %g for double */
    SPRINTF_CHECK("100.",                    buffer, "%#.3g", 99.998580932617187500);
    /* %G for double */
    SPRINTF_CHECK("100.",                    buffer, "%#.3G", 99.998580932617187500);
    /* %lg for double */
    SPRINTF_CHECK("100.",                    buffer, "%#.3lg", 99.998580932617187500);
    /* %Lg for long double */
    // TODO: fix me
    // SPRINTF_CHECK("100.",                    buffer, "%#.3Lg", 99.998580932617187500l);
    // SPRINTF_CHECK("100.",                    buffer, "%#.3Lg", 99.998580932617187500L);

    /* %e for double */
    SPRINTF_CHECK("-8.380923438e+04",        buffer, "%.9e", -83809.234375);
    /* %E for double */
    SPRINTF_CHECK("-8.380923438E+04",        buffer, "%.9E", -83809.234375);
    /* %le for double */
    SPRINTF_CHECK("-8.380923438e+04",        buffer, "%.9le", -83809.234375);
    /* %Le for long double */
    // TODO: fix me
    // SPRINTF_CHECK("-8.380923438e+04",        buffer, "%.9Le", -83809.234375l);
    // SPRINTF_CHECK("-8.380923438e+04",        buffer, "%.9Le", -83809.234375L);
#endif /* RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS */
}

#ifdef RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS
SPRINTF_TEST_CASE(floating_point_specifiers_with_31_to_32_bit_integer_values)
{
    char buffer[base_buffer_size];
#if RT_KLIBC_USING_VSNPRINTF_MAX_INTEGRAL_DIGITS_FOR_DECIMAL >= 10
    SPRINTF_CHECK("2147483647",              buffer, "%.10f", 2147483647.0); /* 2^31 - 1 */
    SPRINTF_CHECK("2147483648",              buffer, "%.10f", 2147483648.0); /* 2^31 */
    SPRINTF_CHECK("4294967295",              buffer, "%.10f", 4294967295.0); /* 2^32 - 1 */
    SPRINTF_CHECK("4294967296",              buffer, "%.10f", 4294967296.0); /* 2^32 */
#else
    SPRINTF_CHECK("2.1474836470e+09",        buffer, "%.10f", 2147483647.0); /* 2^31 - 1 */
    SPRINTF_CHECK("2.1474836480e+09",        buffer, "%.10f", 2147483648.0); /* 2^31 */
    SPRINTF_CHECK("4.2949672950e+09",        buffer, "%.10f", 4294967295.0); /* 2^32 - 1 */
    SPRINTF_CHECK("4.2949672960e+09",        buffer, "%.10f", 4294967296.0); /* 2^32 */
#endif /* RT_KLIBC_USING_VSNPRINTF_MAX_INTEGRAL_DIGITS_FOR_DECIMAL */
    SPRINTF_CHECK("2147483647",              buffer, "%.10g", 2147483647.0); /* 2^31 - 1 */
    SPRINTF_CHECK("2147483648",              buffer, "%.10g", 2147483648.0); /* 2^31 */
    SPRINTF_CHECK("4294967295",              buffer, "%.10g", 4294967295.0); /* 2^32 - 1 */
    SPRINTF_CHECK("4294967296",              buffer, "%.10g", 4294967296.0); /* 2^32 */
}

SPRINTF_TEST_CASE(fallback_from_decimal_to_exponential)
{
    char buffer[base_buffer_size];

    /* Check for 1 * 1000 */
    if (RT_KLIBC_USING_VSNPRINTF_MAX_INTEGRAL_DIGITS_FOR_DECIMAL < 3) {
        SPRINTF_CHECK("1e+3", buffer, "%.0f", (double) ((int64_t) 1 * 1000));
    } else {
        SPRINTF_CHECK("1000", buffer, "%.0f", (double) ((int64_t) 1 * 1000));
    }

    /* Check for 1 * 1000 * 1000 */
    if (RT_KLIBC_USING_VSNPRINTF_MAX_INTEGRAL_DIGITS_FOR_DECIMAL < 6) {
        SPRINTF_CHECK("1e+6", buffer, "%.0f", (double) ((int64_t) 1 * 1000 * 1000));
    } else {
        SPRINTF_CHECK("1000000", buffer, "%.0f", (double) ((int64_t) 1 * 1000 * 1000));
    }

    /* Check for 1 * 1000 * 1000 * 1000 */
    if (RT_KLIBC_USING_VSNPRINTF_MAX_INTEGRAL_DIGITS_FOR_DECIMAL < 9) {
        SPRINTF_CHECK("1e+9", buffer, "%.0f", (double) ((int64_t) 1 * 1000 * 1000 * 1000));
    } else {
        SPRINTF_CHECK("1000000000", buffer, "%.0f", (double) ((int64_t) 1 * 1000 * 1000 * 1000));
    }

    /* Check for 1 * 1000 * 1000 * 1000 * 1000 */
    if (RT_KLIBC_USING_VSNPRINTF_MAX_INTEGRAL_DIGITS_FOR_DECIMAL < 12) {
#ifdef RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS
        SPRINTF_CHECK("1e+12", buffer, "%.0f", (double) ((int64_t) 1 * 1000 * 1000 * 1000 * 1000));
#else
        SPRINTF_CHECK("", buffer, "%.0f", (double) ((int64_t) 1 * 1000 * 1000 * 1000 * 1000));
#endif
    } else {
        SPRINTF_CHECK("1000000000000", buffer, "%.0f", (double) ((int64_t) 1 * 1000 * 1000 * 1000 * 1000));
    }

    /* Check for 1 * 1000 * 1000 * 1000 * 1000 * 1000 */
    if (RT_KLIBC_USING_VSNPRINTF_MAX_INTEGRAL_DIGITS_FOR_DECIMAL < 15) {
#ifdef RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS
        SPRINTF_CHECK("1e+15", buffer, "%.0f", (double) ((int64_t) 1 * 1000 * 1000 * 1000 * 1000 * 1000));
#else
        SPRINTF_CHECK("", buffer, "%.0f", (double) ((int64_t) 1 * 1000 * 1000 * 1000 * 1000 * 1000));
#endif
    } else {
        SPRINTF_CHECK("1000000000000000", buffer, "%.0f", (double) ((int64_t) 1 * 1000 * 1000 * 1000 * 1000 * 1000));
    }

    /* Check for a value which should definitely be out of range for float */
#ifdef RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS
    SPRINTF_CHECK("1.0e+20", buffer, "%.1f", 1E20);
#else
    SPRINTF_CHECK("", buffer, "%.1f", 1E20);
#endif
}
#endif /* RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS */

#ifdef RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS
SPRINTF_TEST_CASE(tiny_floating_point_values)
{
    char buffer[base_buffer_size];

    SPRINTF_CHECK("1e-23",                   buffer, "%.0e",  1.380651569e-23);
    SPRINTF_CHECK("1.4e-23",                 buffer, "%.1e",  1.380651569e-23);
    SPRINTF_CHECK("1.38e-23",                buffer, "%.2e",  1.380651569e-23);
    SPRINTF_CHECK("1.381e-23",               buffer, "%.3e",  1.380651569e-23);
    SPRINTF_CHECK("1.3807e-23",              buffer, "%.4e",  1.380651569e-23);
    SPRINTF_CHECK("1.38065e-23",             buffer, "%.5e",  1.380651569e-23);
    SPRINTF_CHECK("1.380652e-23",            buffer, "%.6e",  1.380651569e-23);
    SPRINTF_CHECK("1.3806516e-23",           buffer, "%.7e",  1.380651569e-23);
    SPRINTF_CHECK("1.38065157e-23",          buffer, "%.8e",  1.380651569e-23);
    SPRINTF_CHECK("1.380651569e-23",         buffer, "%.9e",  1.380651569e-23);
    SPRINTF_CHECK("1.3806515690e-23",        buffer, "%.10e", 1.380651569e-23);
    SPRINTF_CHECK("1.38065156900e-23",       buffer, "%.11e", 1.380651569e-23);
}
#endif /* RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS */
#endif /* RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS || RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS */

#ifdef RT_KLIBC_USING_VSNPRINTF_STANDARD
SPRINTF_TEST_CASE(length)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("",                        buffer, "%.0s", "Hello testing");
    SPRINTF_CHECK("                    ",    buffer, "%20.0s", "Hello testing");
    SPRINTF_CHECK("",                        buffer, "%.s", "Hello testing");
    SPRINTF_CHECK("                    ",    buffer, "%20.s", "Hello testing");
    SPRINTF_CHECK("                1024",    buffer, "%20.0d", 1024);
    SPRINTF_CHECK("               -1024",    buffer, "%20.0d", -1024);
    SPRINTF_CHECK("                    ",    buffer, "%20.d", 0);
    SPRINTF_CHECK("                1024",    buffer, "%20.0i", 1024);
    SPRINTF_CHECK("               -1024",    buffer, "%20.i", -1024);
    SPRINTF_CHECK("                    ",    buffer, "%20.i", 0);
    SPRINTF_CHECK("                1024",    buffer, "%20.u", 1024);
    SPRINTF_CHECK("          4294966272",    buffer, "%20.0u", 4294966272U);
    SPRINTF_CHECK("                    ",    buffer, "%20.u", 0U);
    SPRINTF_CHECK("                 777",    buffer, "%20.o", 511);
    SPRINTF_CHECK("         37777777001",    buffer, "%20.0o", 4294966785U);
    SPRINTF_CHECK("                    ",    buffer, "%20.o", 0U);
    SPRINTF_CHECK("            1234abcd",    buffer, "%20.x", 305441741);
    SPRINTF_CHECK("                                          1234abcd",
                                              buffer, "%50.x", 305441741);
    SPRINTF_CHECK("                                          1234abcd     12345",
                                              buffer, "%50.x%10.u", 305441741, 12345);
    SPRINTF_CHECK("            edcb5433",    buffer, "%20.0x", 3989525555U);
    SPRINTF_CHECK("                    ",    buffer, "%20.x", 0U);
    SPRINTF_CHECK("            1234ABCD",    buffer, "%20.X", 305441741);
    SPRINTF_CHECK("            EDCB5433",    buffer, "%20.0X", 3989525555U);
    SPRINTF_CHECK("                    ",    buffer, "%20.X", 0U);
}

SPRINTF_TEST_CASE(length__non_standard_format)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("  ",                      buffer, "%02.0u", 0U);
    SPRINTF_CHECK("  ",                      buffer, "%02.0d", 0);
}

SPRINTF_TEST_CASE(unknown_flag__non_standard_format)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("kmarco",                  buffer, "%kmarco", 42, 37);
}

SPRINTF_TEST_CASE(string_length__non_standard_format)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK(".2s",                     buffer, "%.4.2s", "123456");
}
#endif /* RT_KLIBC_USING_VSNPRINTF_STANDARD */

SPRINTF_TEST_CASE(integer_types)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("0",                       buffer, "%i", 0);
    SPRINTF_CHECK("1234",                    buffer, "%i", 1234);
    SPRINTF_CHECK("32767",                   buffer, "%i", 32767);
    SPRINTF_CHECK("-32767",                  buffer, "%i", -32767);
    SPRINTF_CHECK("30",                      buffer, "%li", 30L);
    SPRINTF_CHECK("-2147483647",             buffer, "%li", -2147483647L);
    SPRINTF_CHECK("2147483647",              buffer, "%li", 2147483647L);
#ifdef RT_KLIBC_USING_VSNPRINTF_LONGLONG
    SPRINTF_CHECK("30",                      buffer, "%lli", 30LL);
#ifdef RT_KLIBC_USING_VSNPRINTF_STANDARD
    SPRINTF_CHECK("-9223372036854775807",    buffer, "%lli", -9223372036854775807LL);
    SPRINTF_CHECK("9223372036854775807",     buffer, "%lli", 9223372036854775807LL);
#endif /* RT_KLIBC_USING_VSNPRINTF_STANDARD */
#endif /* RT_KLIBC_USING_VSNPRINTF_LONGLONG */
    SPRINTF_CHECK("100000",                  buffer, "%lu", 100000L);
    SPRINTF_CHECK("4294967295",              buffer, "%lu", 0xFFFFFFFFL);
#ifdef RT_KLIBC_USING_VSNPRINTF_LONGLONG
    SPRINTF_CHECK("281474976710656",         buffer, "%llu", 281474976710656LLU);
    SPRINTF_CHECK("18446744073709551615",    buffer, "%llu", 18446744073709551615LLU);
#endif /* RT_KLIBC_USING_VSNPRINTF_LONGLONG */
    SPRINTF_CHECK("2147483647",              buffer, "%zu", (size_t) 2147483647UL);
    SPRINTF_CHECK("2147483647",              buffer, "%zd", (size_t) 2147483647UL);
    SPRINTF_CHECK("-2147483647",             buffer, "%zi", (ssize_t) -2147483647L);
    SPRINTF_CHECK("165140",                  buffer, "%o", 60000);
    SPRINTF_CHECK("57060516",                buffer, "%lo", 12345678L);
    SPRINTF_CHECK("12345678",                buffer, "%lx", 0x12345678L);
#ifdef RT_KLIBC_USING_VSNPRINTF_LONGLONG
    SPRINTF_CHECK("1234567891234567",        buffer, "%llx", 0x1234567891234567LLU);
#endif /* RT_KLIBC_USING_VSNPRINTF_LONGLONG */
    SPRINTF_CHECK("abcdefab",                buffer, "%lx", 0xabcdefabL);
    SPRINTF_CHECK("ABCDEFAB",                buffer, "%lX", 0xabcdefabL);
    SPRINTF_CHECK("v",                       buffer, "%c", 'v');
    SPRINTF_CHECK("wv",                      buffer, "%cv", 'w');
    SPRINTF_CHECK("A Test",                  buffer, "%s", "A Test");
#ifdef RT_KLIBC_USING_VSNPRINTF_STANDARD
    SPRINTF_CHECK("255",                     buffer, "%hhu", (unsigned char) 0xFFU);
#endif /* RT_KLIBC_USING_VSNPRINTF_STANDARD */
    SPRINTF_CHECK("4660",                    buffer, "%hu", (unsigned short) 0x1234u);
    SPRINTF_CHECK("Test100 65535",           buffer, "%s%hhi %hu", "Test", (char) 100, (unsigned short) 0xFFFF);
#ifdef RT_KLIBC_USING_VSNPRINTF_STANDARD
    SPRINTF_CHECK("a",                       buffer, "%tx", &buffer[10] - &buffer[0]);
    SPRINTF_CHECK("-2147483647",             buffer, "%ji", (intmax_t) -2147483647L);
#endif /* RT_KLIBC_USING_VSNPRINTF_STANDARD */
}

SPRINTF_TEST_CASE(types__non_standard_format)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("1110101001100000",        buffer, "%b", 60000);
    SPRINTF_CHECK("101111000110000101001110", buffer, "%lb", 12345678L);
}

SPRINTF_TEST_CASE(pointer)
{
    char buffer[base_buffer_size];

    /* Test for pointer value 0x1234U */
    SPRINTF_CHECK((sizeof(void *) == 4U) ? "0x00001234" : "0x0000000000001234",
                  buffer, "%p", (void *) 0x1234U);

    /* Test for pointer value 0x12345678U */
    SPRINTF_CHECK((sizeof(void *) == 4U) ? "0x12345678" : "0x0000000012345678",
                  buffer, "%p", (void *) 0x12345678U);

    /* Test for pointer range 0x12345678U to 0x7EDCBA98U */
    SPRINTF_CHECK((sizeof(void *) == 4U) ? "0x12345678-0x7edcba98" : "0x0000000012345678-0x000000007edcba98",
                  buffer, "%p-%p", (void *) 0x12345678U, (void *) 0x7EDCBA98U);

    /* Test for maximum uintptr_t value 0xFFFFFFFFU */
    if (sizeof(uintptr_t) == sizeof(uint64_t)) {
        SPRINTF_CHECK("0x00000000ffffffff", buffer, "%p", (void *) (uintptr_t) 0xFFFFFFFFU);
    } else {
        SPRINTF_CHECK("0xffffffff", buffer, "%p", (void *) (uintptr_t) 0xFFFFFFFFU);
    }

#ifdef RT_KLIBC_USING_VSNPRINTF_STANDARD
    /* Test for NULL pointer */
    SPRINTF_CHECK("(nil)", buffer, "%p", (const void *)RT_NULL);
#endif /* RT_KLIBC_USING_VSNPRINTF_STANDARD */
}

SPRINTF_TEST_CASE(string_length)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("This",                    buffer, "%.4s", "This is a test");
    SPRINTF_CHECK("test",                    buffer, "%.4s", "test");
    SPRINTF_CHECK("123",                     buffer, "%.7s", "123");
    SPRINTF_CHECK("",                        buffer, "%.7s", "");
    SPRINTF_CHECK("1234ab",                  buffer, "%.4s%.2s", "123456", "abcdef");
    SPRINTF_CHECK("123",                     buffer, "%.*s", 3, "123456");
#ifdef RT_KLIBC_USING_VSNPRINTF_STANDARD
    SPRINTF_CHECK("(null)",                  buffer, "%.*s", 3, (const char *) RT_NULL);
#else
    SPRINTF_CHECK("(nu",                  buffer, "%.*s", 3, (const char *) RT_NULL);
#endif /* RT_KLIBC_USING_VSNPRINTF_STANDARD */
}

SPRINTF_TEST_CASE(misc)
{
    char buffer[base_buffer_size];
    SPRINTF_CHECK("53000atest-20 bit",       buffer, "%u%u%ctest%d %s", 5, 3000, 'a', -20, "bit");
#ifdef RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS
    SPRINTF_CHECK("0.33",                    buffer, "%.*f", 2, 0.33333333);
    SPRINTF_CHECK("1",                       buffer, "%.*d", -1, 1);
    SPRINTF_CHECK("foo",                     buffer, "%.3s", "foobar");
    SPRINTF_CHECK(" ",                       buffer, "% .0d", 0);
    SPRINTF_CHECK("     00004",              buffer, "%10.5d", 4);
    SPRINTF_CHECK("hi x",                    buffer, "%*sx", -3, "hi");
    SPRINTF_CHECK("00123               ",    buffer, "%-20.5i", 123);
    SPRINTF_CHECK("-67224.546875000000000000", buffer, "%.18f", -67224.546875);
#endif /* RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS */
#ifdef RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS
    SPRINTF_CHECK("0.33",                    buffer, "%.*g", 2, 0.33333333);
    SPRINTF_CHECK("3.33e-01",                buffer, "%.*e", 2, 0.33333333);
    SPRINTF_CHECK("0.000000e+00",            buffer, "%e", 0.0);
    SPRINTF_CHECK("-0.000000e+00",           buffer, "%e", -0.0);
#endif /* RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS */
}

static void utest_do_tc(void)
{
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(space_flag));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(space_flag__non_standard_format));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(plus_flag));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(plus_flag__non_standard_format));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(zero_flag));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(minus_flag));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(minus_flag_and_non_standard_zero_modifier_for_integers));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(sharp_flag));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(sharp_flag__non_standard_format));
#ifdef RT_KLIBC_USING_VSNPRINTF_LONGLONG
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(sharp_flag_with_long_long));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(sharp_flag_with_long_long__non_standard_format));
#endif /* RT_KLIBC_USING_VSNPRINTF_LONGLONG */
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(specifier));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(width));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(width_20));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(width_asterisk_20));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(width_minus_20));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(width_0_minus_20));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(padding_20));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(padding_dot_20));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(padding_sharp_020__non_standard_format));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(padding_sharp_020));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(padding_sharp_20__non_standard_format));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(padding_sharp_20));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(padding_20_point_5));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(padding_negative_numbers));
#if defined(RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS) || \
    defined(RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS)
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(float_padding_negative_numbers));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(infinity_and_not_a_number_values));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(floating_point_specifiers_precision_and_flags));
#ifdef RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(floating_point_specifiers_with_31_to_32_bit_integer_values));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(fallback_from_decimal_to_exponential));
#endif /* RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS */
#ifdef RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(tiny_floating_point_values));
#endif /* RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS */
#endif /* RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS || RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS */
#ifdef RT_KLIBC_USING_VSNPRINTF_STANDARD
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(length));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(length__non_standard_format));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(unknown_flag__non_standard_format));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(string_length__non_standard_format));
#endif /* RT_KLIBC_USING_VSNPRINTF_STANDARD */
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(integer_types));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(types__non_standard_format));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(pointer));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(string_length));
    UTEST_UNIT_RUN(SPRINTF_TEST_CASE_NAME(misc));
}

UTEST_TC_EXPORT(utest_do_tc, "klibc.rt_sprintf", RT_NULL, RT_NULL, 1000);
