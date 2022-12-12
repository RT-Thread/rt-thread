#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <utest.h>

static int scmp(const void *a, const void *b)
{
    return strcmp(*(char **)a, *(char **)b);
}

static int icmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

static int ccmp(const void *a, const void *b)
{
    return *(char *)a - *(char *)b;
}

/**
 * static int cmp64(const void *a, const void *b)
 * {
 *     const uint64_t *ua = a, *ub = b;
 *     return *ua < *ub ? -1 : *ua != *ub;
 * }
 */

/* 26 items -- even */
static const char *s[] =
{
    "Bob", "Alice", "John", "Ceres",
    "Helga", "Drepper", "Emeralda", "Zoran",
    "Momo", "Frank", "Pema", "Xavier",
    "Yeva", "Gedun", "Irina", "Nono",
    "Wiener", "Vincent", "Tsering", "Karnica",
    "Lulu", "Quincy", "Osama", "Riley",
    "Ursula", "Sam"
};
static const char *s_sorted[] =
{
    "Alice", "Bob", "Ceres", "Drepper",
    "Emeralda", "Frank", "Gedun", "Helga",
    "Irina", "John", "Karnica", "Lulu",
    "Momo", "Nono", "Osama", "Pema",
    "Quincy", "Riley", "Sam", "Tsering",
    "Ursula", "Vincent", "Wiener", "Xavier",
    "Yeva", "Zoran"
};

/* 23 items -- odd, prime */
static int n[] =
{
    879045, 394, 99405644, 33434, 232323, 4334, 5454,
    343, 45545, 454, 324, 22, 34344, 233, 45345, 343,
    848405, 3434, 3434344, 3535, 93994, 2230404, 4334
};
static int n_sorted[] =
{
    22, 233, 324, 343, 343, 394, 454, 3434,
    3535, 4334, 4334, 5454, 33434, 34344, 45345, 45545,
    93994, 232323, 848405, 879045, 2230404, 3434344, 99405644
};

static void str_test(const char **a, const char **a_sorted, int len)
{
    int i;
    qsort(a, len, sizeof * a, scmp);
    for (i = 0; i < len; i++)
    {
        uassert_true(strcmp(a[i], a_sorted[i]) == 0);
    }
}

static void int_test(int *a, int *a_sorted, int len)
{
    int i;
    qsort(a, len, sizeof * a, icmp);
    for (i = 0; i < len; i++)
    {
        uassert_true(a[i] == a_sorted[i]);
    }
}

#define T(a, a_sorted) do { \
    char p[] = a; \
    qsort(p, sizeof p - 1, 1, ccmp); \
    uassert_true(memcmp(p, a_sorted, sizeof p) == 0);\
} while(0)

static void char_test(void)
{
    T("", "");
    T("1", "1");
    T("11", "11");
    T("12", "12");
    T("21", "12");
    T("111", "111");
    T("211", "112");
    T("121", "112");
    T("112", "112");
    T("221", "122");
    T("212", "122");
    T("122", "122");
    T("123", "123");
    T("132", "123");
    T("213", "123");
    T("231", "123");
    T("321", "123");
    T("312", "123");
    T("1423", "1234");
    T("51342", "12345");
    T("261435", "123456");
    T("4517263", "1234567");
    T("37245618", "12345678");
    T("812436597", "123456789");
    T("987654321", "123456789");
    T("321321321", "111222333");
    T("49735862185236174", "11223344556677889");
}

void posix_testcase(void)
{
    str_test(s, s_sorted, sizeof s / sizeof * s);
    int_test(n, n_sorted, sizeof n / sizeof * n);
    char_test();
    /* todo uint64 test */
}
static void testcase(void)
{
    UTEST_UNIT_RUN(posix_testcase);
}
UTEST_TC_EXPORT(testcase, "posix.stdlib_h.qsort_tc.c", RT_NULL, RT_NULL, 10);

