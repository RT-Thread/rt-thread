/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-08-17     Shell        test case for aspace_map(MAP_FIXED)
 */
#include "common.h"
#include "lwp_user_mm.h"
#include "utest_assert.h"
#include <mm_private.h>

#include <rtthread.h>

#define PAGE_SZ     (1 << MM_PAGE_SHIFT)
#define PAGE_COUNT  ('z' - 'a' + 1)
#define FILE_PATH   "/test_mmap"
#define FILE_SZ     (PAGE_COUNT * PAGE_SZ)

static struct rt_lwp *lwp;
static size_t former_vsz;
static size_t former_vcount;
static char page_sz_buf[PAGE_SZ];

static void *vaddr = (void *)0x100000000;
static long pgoffset = 0;
static size_t ex_prot = PROT_NONE;
static size_t ex_flags = MAP_PRIVATE | MAP_ANONYMOUS;

static int _count_vsz(rt_varea_t varea, void *arg)
{
    rt_base_t *pvsz = arg;
    *pvsz += 1;
    return 0;
}

static rt_base_t count_vcount(rt_aspace_t aspace)
{
    rt_base_t vcount = 0;
    rt_aspace_traversal(aspace, _count_vsz, &vcount);
    return vcount;
}

static rt_err_t _lwp_get_user(struct rt_lwp *lwp, char *vaddr, char *buffer)
{
    rt_varea_t varea = _aspace_bst_search(lwp->aspace, vaddr);
    if (varea && varea->mem_obj && varea->mem_obj->page_read)
    {
        struct rt_aspace_io_msg io_msg;
        rt_mm_io_msg_init(&io_msg, MM_PA_TO_OFF(vaddr), vaddr, buffer);
        varea->mem_obj->page_read(varea, &io_msg);
    }
    return RT_EOK;
}

static void _verify_file_content(const char *mmap_buf)
{
    char ch = 'a';
    for (char *read_va = (char *)mmap_buf; read_va < mmap_buf + FILE_SZ; read_va += PAGE_SZ, ch++)
    {
        _lwp_get_user(lwp, read_va, page_sz_buf);
        utest_int_equal(RT_EOK, memtest(page_sz_buf, ch, PAGE_SZ));
    }
}

static void test_mmap_fd(void)
{
    former_vsz = rt_aspace_count_vsz(lwp->aspace);
    former_vcount = count_vcount(lwp->aspace);

    /* create an existed mapping */
    long temp_fd;
    temp_fd = open(FILE_PATH, O_RDONLY);
    LOG_D("New fd=%ld path=%s", temp_fd, FILE_PATH);
    uassert_true(temp_fd >= 0);
    utest_int_equal(
        lwp_mmap2(lwp, vaddr, FILE_SZ, ex_prot, ex_flags, temp_fd, pgoffset),
        vaddr);
    close(temp_fd);

    utest_int_equal(former_vsz + FILE_SZ, rt_aspace_count_vsz(lwp->aspace));
    utest_int_equal(former_vcount + 1, count_vcount(lwp->aspace));

    _verify_file_content(vaddr);

    /* create an override mapping */

    /* close */

    utest_int_equal(RT_EOK, rt_aspace_unmap_range(lwp->aspace, vaddr, FILE_SZ));
}

static void testcase_main(void)
{
    test_mmap_fd();
}

static void _setup_file_content(long fd)
{
    char ch = 'a';

    for (size_t i = 0; i < PAGE_COUNT; i++, ch++)
    {
        memset(page_sz_buf, ch, PAGE_SZ);
        write(fd, page_sz_buf, PAGE_SZ);
    }
}

static rt_err_t utest_tc_init(void)
{
    /* setup file */
    long temp_file_des;
    temp_file_des = open(FILE_PATH, O_RDWR | O_CREAT, 0777);
    LOG_D("New fd=%ld path=%s", temp_file_des, FILE_PATH);
    if (temp_file_des < 0)
        return -RT_ERROR;
    _setup_file_content(temp_file_des);
    close(temp_file_des);

    lwp = lwp_create(0);
    if (lwp)
        lwp_user_space_init(lwp, 1);
    else
        return -RT_ENOMEM;
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    lwp_ref_dec(lwp);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(testcase_main);
}
UTEST_TC_EXPORT(testcase, "testcases.lwp.mman.mmap_fd.basic", utest_tc_init, utest_tc_cleanup, 10);
