/*
 * Copyright (c) 2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dlfcn.h>
#include "utest.h"
#include "../dlmodule.h"
#include "dlmodule_fixtures.h"

#define TEST_DIR "/dlmutest"

typedef uint32_t *(*probe_fn)(void);
typedef int (*value_fn)(void);

static rt_bool_t in_module(void *handle, const void *address, rt_size_t size)
{
    struct rt_dlmodule *module = handle;
    rt_ubase_t base = (rt_ubase_t)module->mem_space;
    rt_ubase_t value = (rt_ubase_t)address;

    return address != RT_NULL && value >= base && size <= module->mem_size &&
           value - base <= module->mem_size - size;
}

static void fixture_path(char *path, rt_size_t size, unsigned index)
{
    rt_snprintf(path, size, "%s/%s", TEST_DIR, dlmodule_fixtures[index].name);
}

static void *load_fixture(unsigned index)
{
    const struct dlmodule_fixture *fixture = &dlmodule_fixtures[index];
    char path[64];
    unsigned written = 0;
    int fd;

    fixture_path(path, sizeof(path), index);
    fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    uassert_true(fd >= 0);
    if (fd < 0)
    {
        return RT_NULL;
    }

    while (written < fixture->size)
    {
        int count = write(fd, fixture->data + written, fixture->size - written);
        if (count <= 0)
        {
            uassert_true(count > 0);
            close(fd);
            return RT_NULL;
        }
        written += count;
    }
    if (close(fd) != 0)
    {
        uassert_true(0);
        return RT_NULL;
    }

    return dlopen(path, RTLD_NOW);
}

static uint32_t *get_results(void *handle, unsigned count)
{
    probe_fn probe = (probe_fn)dlsym(handle, "probe");
    uint32_t *result;
    rt_bool_t valid;

    valid = in_module(handle, (void *)probe, 4);
    uassert_true(valid);
    if (!valid)
    {
        return RT_NULL;
    }
    result = probe();
    valid = in_module(handle, result, count * sizeof(*result));
    uassert_true(valid);
    return valid ? result : RT_NULL;
}

static void close_fixture(void *handle)
{
    uassert_int_equal(dlclose(handle), RT_TRUE);
}

static void globals_test(unsigned index)
{
    void *handle = load_fixture(index);
    uint32_t *result;

    uassert_not_null(handle);
    if (handle == RT_NULL)
    {
        return;
    }

    result = get_results(handle, 8);
    if (result != RT_NULL)
    {
        rt_bool_t addresses_valid = RT_TRUE;
        for (unsigned i = 0; i < 3; i++)
        {
            rt_bool_t valid = in_module(handle, (void *)result[i], sizeof(uint32_t));
            uassert_true(valid);
            addresses_valid = addresses_valid && valid;
        }
        uassert_int_not_equal(result[0], result[1]);
        uassert_int_not_equal(result[1], result[2]);
        uassert_int_not_equal(result[0], result[2]);
        if (index == 0)
        {
            uassert_int_equal(result[2] & 15, 0);
        }
        uassert_int_equal(result[3], 7);
        uassert_int_equal(result[4], 0);
        uassert_int_equal(result[5], 0);
        uassert_int_equal(result[6], 0);
        uassert_true((void *)result[7] == dlsym(handle, "probe"));
        if (addresses_valid)
        {
            uassert_int_equal(*(uint32_t *)result[0], 0x11223344);
            uassert_int_equal(*(uint32_t *)result[1], 0x55667788);
            uassert_int_equal(*(uint32_t *)result[2], 0x12345678);
        }
    }
    close_fixture(handle);
}

static void globals_rel(void)
{
    globals_test(0);
}

static void globals_dyn(void)
{
    globals_test(1);
}

static void kernel_import(void)
{
    globals_test(2);
}

static void common_target(void)
{
    void *handle = load_fixture(3);
    uint32_t *result;

    uassert_not_null(handle);
    if (handle == RT_NULL)
    {
        return;
    }
    result = get_results(handle, 4);
    if (result != RT_NULL)
    {
        uassert_true(in_module(handle, (void *)result[0], 4));
        uassert_int_equal(result[0], result[1]);
        uassert_int_equal(result[2], 42);
        uassert_int_equal(result[3], 0);
    }
    close_fixture(handle);
}

static void multi_nobits(void)
{
    void *handle = load_fixture(4);
    uint32_t *result;

    uassert_not_null(handle);
    if (handle == RT_NULL)
    {
        return;
    }
    result = get_results(handle, 6);
    if (result != RT_NULL)
    {
        uassert_true(in_module(handle, (void *)result[0], 4));
        uassert_true(in_module(handle, (void *)result[1], 4));
        uassert_int_not_equal(result[0], result[1]);
        uassert_int_equal(result[2], 0);
        uassert_int_equal(result[3], 0);
        uassert_int_equal(result[4], 0x11223344);
        uassert_int_equal(result[5], 0x55667788);
    }
    close_fixture(handle);
}

static void sections_test(unsigned index)
{
    void *handle = load_fixture(index);
    uint32_t *result;

    uassert_not_null(handle);
    if (handle == RT_NULL)
    {
        return;
    }
    result = get_results(handle, 4);
    if (result != RT_NULL)
    {
        uassert_int_equal(result[0], 7);
        uassert_int_equal(result[1], 9);
        uassert_int_equal(result[2], 0);
        uassert_true((void *)result[3] == dlsym(handle, "probe"));
    }
    close_fixture(handle);
}

static void nonzero_sections(void)
{
    sections_test(5);
}

static void debug_sections(void)
{
    sections_test(6);
}

static void multi_text(void)
{
    void *handle = load_fixture(7);
    value_fn first, second;
    rt_bool_t valid;

    uassert_not_null(handle);
    if (handle == RT_NULL)
    {
        return;
    }
    first = (value_fn)dlsym(handle, "first");
    second = (value_fn)dlsym(handle, "second");
    valid = in_module(handle, (void *)first, 4) && in_module(handle, (void *)second, 4);
    uassert_true(valid);
    uassert_true(first != second);
    if (valid)
    {
        uassert_int_equal(first(), 11);
        uassert_int_equal(second(), 22);
    }
    close_fixture(handle);
}

static void undefined_symbol(void)
{
    void *handle = load_fixture(8);
    value_fn present;
    rt_bool_t valid;

    uassert_not_null(handle);
    if (handle == RT_NULL)
    {
        return;
    }
    uassert_null(dlsym(handle, "external_func"));
    present = (value_fn)dlsym(handle, "present");
    valid = in_module(handle, (void *)present, 4);
    uassert_true(valid);
    if (valid)
    {
        uassert_int_equal(present(), 42);
    }
    close_fixture(handle);
}

static void zero_exports(void)
{
    void *handle = load_fixture(9);

    uassert_not_null(handle);
    if (handle == RT_NULL)
    {
        return;
    }
    uassert_int_equal(((struct rt_dlmodule *)handle)->nsym, 0);
    uassert_null(dlsym(handle, "external_func"));
    close_fixture(handle);
}

static rt_err_t test_init(void)
{
    struct stat st;

    if (stat(TEST_DIR, &st) == 0)
    {
        return S_ISDIR(st.st_mode) ? RT_EOK : -RT_ERROR;
    }
    return mkdir(TEST_DIR, 0700) == 0 ? RT_EOK : -RT_ERROR;
}

static rt_err_t test_cleanup(void)
{
    char path[64];

    for (unsigned i = 0; i < sizeof(dlmodule_fixtures) / sizeof(dlmodule_fixtures[0]); i++)
    {
        fixture_path(path, sizeof(path), i);
        unlink(path);
    }
    return rmdir(TEST_DIR) == 0 ? RT_EOK : -RT_ERROR;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(globals_rel);
    UTEST_UNIT_RUN(globals_dyn);
    UTEST_UNIT_RUN(kernel_import);
    UTEST_UNIT_RUN(common_target);
    UTEST_UNIT_RUN(multi_nobits);
    UTEST_UNIT_RUN(nonzero_sections);
    UTEST_UNIT_RUN(debug_sections);
    UTEST_UNIT_RUN(multi_text);
    UTEST_UNIT_RUN(undefined_symbol);
    UTEST_UNIT_RUN(zero_exports);
}

UTEST_TC_EXPORT(testcase, "components.libc.posix.libdl.regression", test_init, test_cleanup, 30);
